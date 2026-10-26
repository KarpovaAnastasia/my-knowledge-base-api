#pragma once

#include <drogon/HttpRequest.h>
#include <optional>
#include <string>

namespace kb::api {
    // Вспомогательная функция: берет заголовок Authorization, проверяет токен
    // и возвращает ID пользователя, если всё ок. Если токен невалидный возвращает nullopt
    std::optional<std::string> getCurrentUserId(const drogon::HttpRequestPtr& req);
}