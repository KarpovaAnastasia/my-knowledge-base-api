#include "kb/api/HealthController.h"
#include <drogon/drogon.h>

namespace kb::api {

    void registerHealthEndpoint() {
        drogon::app().registerHandler(
            "/api/v1/health",
            [](const drogon::HttpRequestPtr&,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

                    Json::Value body;
                    body["status"] = "ok";
                    body["service"] = "knowledge-base-api";

                    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
                    callback(resp);
            },
            { drogon::Get }
        );
    }

}