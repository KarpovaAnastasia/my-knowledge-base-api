#include "kb/api/PageController.h"
#include "kb/api/stubs/StubPageService.h"
#include <drogon/drogon.h>

namespace kb::api {
    // позже заменю на реальный PageService из kb-content.
    static stubs::StubPageService stubPageService;

    void registerPageEndpoints() {
        // GET /api/v1/pages/{id}
        drogon::app().registerHandler(
            "/api/v1/pages/{id}",
            [](const drogon::HttpRequestPtr&,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                std::string id) {

                    auto page = stubPageService.getPage(id);

                    // страница не найдена
                    if (!page) {
                        Json::Value error;
                        error["error"]["code"] = "PAGE_NOT_FOUND";
                        error["error"]["message"] = "Page not found";

                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k404NotFound);
                        callback(resp);
                        return;
                    }

                    // страница найдена
                    Json::Value body;
                    body["id"] = page->id;
                    body["title"] = page->title;
                    body["content"] = page->content;
                    body["version"] = page->version;

                    callback(drogon::HttpResponse::newHttpJsonResponse(body));
            },
            { drogon::Get }
        );
        // POST /api/v1/pages
        drogon::app().registerHandler(
            "/api/v1/pages",
            [](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

                    auto json = req->getJsonObject();

                    // проверка тела запроса
                    if (!json) {
                        Json::Value error;
                        error["error"]["code"] = "VALIDATION_ERROR";
                        error["error"]["message"] = "Request body must be JSON";

                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k400BadRequest);
                        callback(resp);
                        return;
                    }

                    auto title = (*json)["title"].asString();
                    auto content = (*json)["content"].asString();

                    // проверка полей
                    if (title.empty()) {
                        Json::Value error;
                        error["error"]["code"] = "VALIDATION_ERROR";
                        error["error"]["message"] = "Title must not be empty";

                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k400BadRequest);
                        callback(resp);
                        return;
                    }

                    // создаем
                    auto page = stubPageService.createPage(title, content);

                    Json::Value body;
                    body["id"] = page.id;
                    body["title"] = page.title;
                    body["content"] = page.content;
                    body["version"] = page.version;

                    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
                    resp->setStatusCode(drogon::k201Created);
                    callback(resp);
            },
            { drogon::Post }
        );
    }

}
