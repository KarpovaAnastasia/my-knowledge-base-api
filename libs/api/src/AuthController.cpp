#include "kb/api/AuthController.h"
#include "kb/api/stubs/StubUserService.h"
#include "kb/api/stubs/StubSessionService.h"
#include <drogon/drogon.h>

namespace kb::api {
    static stubs::StubUserService stubUserService;
    static stubs::StubSessionService stubSessionService;

    void registerAuthEndpoints() {
        drogon::app().registerHandler(
            "/api/v1/auth/login",
            [](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

                    auto json = req->getJsonObject();

                    // проверка, что тело запроса это JSON и там есть поля login/password
                    if (!json || !(*json)["login"].isString() || !(*json)["password"].isString()) {
                        Json::Value error;
                        error["error"]["code"] = "VALIDATION_ERROR";
                        error["error"]["message"] = "Missing login or password";

                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k400BadRequest);
                        callback(resp);
                        return;
                    }

                    std::string login = (*json)["login"].asString();
                    std::string password = (*json)["password"].asString();

                    // пытаемся аутентифицировать пользователя через заглушку
                    auto user = stubUserService.authenticate(login, password);

                    // если неверный логин или пароль
                    if (!user) {
                        Json::Value error;
                        error["error"]["code"] = "INVALID_CREDENTIALS";
                        error["error"]["message"] = "Invalid login or password";

                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k401Unauthorized);
                        callback(resp);
                        return;
                    }

                    // создаем сессию и получаем токен
                    std::string token = stubSessionService.createSession(user->id);

                    // формируем ответ
                    Json::Value body;
                    body["session_id"] = token; // токен, который клиент должен сохранить
                    body["user"]["id"] = user->id;
                    body["user"]["login"] = user->login;
                    body["user"]["display_name"] = user->displayName;

                    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
                    resp->setStatusCode(drogon::k200OK);
                    callback(resp);
            },
            { drogon::Post }
        );

        //выход
        drogon::app().registerHandler(
            "/api/v1/auth/logout",
            [](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

                    // клиент должен передать токен в заголовке "Authorization: Bearer <токен>"
                    std::string authHeader = req->getHeader("authorization");

                    // проверяем, что заголовок есть и начинается с "Bearer "
                    if (authHeader.rfind("Bearer ", 0) == 0) {
                        std::string token = authHeader.substr(7); // отрезаем слово "Bearer "
                        stubSessionService.deleteSession(token);  // удаляем сессию
                    }

                    // возвращаем 204 No Content (успешно, но нечего возвращать)
                    auto resp = drogon::HttpResponse::newHttpResponse();
                    resp->setStatusCode(drogon::k204NoContent);
                    callback(resp);
            },
            { drogon::Post }
        );

        //получаем пользователя
        drogon::app().registerHandler(
            "/api/v1/users/me",
            [](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

                    std::string authHeader = req->getHeader("authorization");
                    std::string token = "";
                    if (authHeader.rfind("Bearer ", 0) == 0) {
                        token = authHeader.substr(7);
                    }

                    // проверяем валидность токена
                    auto userId = stubSessionService.validateSession(token);

                    // если токена нет или он просрочен
                    if (!userId) {
                        Json::Value error;
                        error["error"]["code"] = "UNAUTHORIZED";
                        error["error"]["message"] = "Invalid or expired session";

                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k401Unauthorized);
                        callback(resp);
                        return;
                    }

                    // токен валиден, получаем данные пользователя
                    auto user = stubUserService.getUserById(*userId);

                    Json::Value body;
                    body["id"] = user->id;
                    body["login"] = user->login;
                    body["email"] = user->email;
                    body["display_name"] = user->displayName;
                    body["role"] = user->role;

                    callback(drogon::HttpResponse::newHttpJsonResponse(body));
            },
            { drogon::Get }
        );
    }
}