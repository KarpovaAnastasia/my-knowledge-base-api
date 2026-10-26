#include "kb/api/AuthHelper.h"
#include "kb/api/stubs/StubSessionService.h"

namespace kb::api {
    // создаем экземпляр сервиса сессий (тот же, что в AuthController)
    static stubs::StubSessionService stubSessionService;

    std::optional<std::string> getCurrentUserId(const drogon::HttpRequestPtr& req) {
        std::string authHeader = req->getHeader("authorization");
        if (authHeader.rfind("Bearer ", 0) == 0) {
            std::string token = authHeader.substr(7);
            return stubSessionService.validateSession(token);
        }
        return std::nullopt;
    }
}