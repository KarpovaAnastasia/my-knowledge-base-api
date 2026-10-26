#pragma once

#include <string>
#include <optional>

namespace kb::api::stubs {
    class StubSessionService {
    public:
         std::string createSession(const std::string& userId); // создание сессии 
        
        std::optional<std::string> validateSession(const std::string& token);// проверка существующей сессии 

        void deleteSession(const std::string& token); // завершение сессии
    };
}