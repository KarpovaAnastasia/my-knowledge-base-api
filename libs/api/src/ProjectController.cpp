#include "kb/api/ProjectController.h"
#include "kb/api/stubs/StubProjectService.h"
#include "kb/api/stubs/StubAttachmentService.h"
#include "kb/api/AuthHelper.h" 
#include <drogon/drogon.h>

namespace kb::api {

    static stubs::StubProjectService stubProjectService; // имитация работы с проектами
    static stubs::StubAttachmentService stubAttachmentService; // имитация сохранения файлов

    void registerProjectEndpoints() {
        drogon::app().registerHandler(
            "/api/v1/projects",
            [](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

                    //проверка авторизации
                    auto userId = getCurrentUserId(req);
                    if (!userId) {
                        Json::Value error;
                        error["error"]["code"] = "UNAUTHORIZED";
                        error["error"]["message"] = "Authentication required";
                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k401Unauthorized);
                        callback(resp);
                        return; //прерываем выполнение, если не авторизован
                    }

                    // чтение и валидация
                    auto json = req->getJsonObject();
                    if (!json) {
                        Json::Value error;
                        error["error"]["code"] = "VALIDATION_ERROR";
                        error["error"]["message"] = "Request body must be JSON";
                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k400BadRequest);
                        callback(resp);
                        return;
                    }

                    auto name = (*json)["name"].asString();
                    auto description = (*json)["description"].asString();
                    auto fileName = (*json)["file_name"].asString();
                    auto fileBase64 = (*json)["file_base64"].asString();

                    // проверка обязательного поля
                    if (name.empty()) {
                        Json::Value error;
                        error["error"]["code"] = "VALIDATION_ERROR";
                        error["error"]["message"] = "Name must not be empty";
                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k400BadRequest);
                        callback(resp);
                        return;
                    }

                    // сохранение
                    std::string attachmentId;
                    if (!fileBase64.empty()) {
                        attachmentId = stubAttachmentService.saveFile(fileName, fileBase64);
                    }

                    auto project = stubProjectService.createProject(
                        name, description, attachmentId, fileName);

                    // ответ
                    Json::Value body;
                    body["id"] = project.id;
                    body["name"] = project.name;
                    body["description"] = project.description;
                    body["attachment_id"] = project.attachmentId;
                    body["file_name"] = project.fileName;

                    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
                    resp->setStatusCode(drogon::k201Created);
                    callback(resp);
            },
            { drogon::Post }
        );


        drogon::app().registerHandler(
            "/api/v1/projects/{id}",
            [](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                std::string id) {

                    // проверка авторизации
                    auto userId = getCurrentUserId(req);
                    if (!userId) {
                        Json::Value error;
                        error["error"]["code"] = "UNAUTHORIZED";
                        error["error"]["message"] = "Authentication required";
                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k401Unauthorized);
                        callback(resp);
                        return;
                    }

                    // получение данных
                    auto project = stubProjectService.getProject(id);

                    if (!project) {
                        Json::Value error;
                        error["error"]["code"] = "PROJECT_NOT_FOUND";
                        error["error"]["message"] = "Project not found";
                        auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
                        resp->setStatusCode(drogon::k404NotFound);
                        callback(resp);
                        return;
                    }

                    // ответ
                    Json::Value body;
                    body["id"] = project->id;
                    body["name"] = project->name;
                    body["description"] = project->description;
                    body["attachment_id"] = project->attachmentId;
                    body["file_name"] = project->fileName;

                    callback(drogon::HttpResponse::newHttpJsonResponse(body));
            },
            { drogon::Get }
        );
    }
}