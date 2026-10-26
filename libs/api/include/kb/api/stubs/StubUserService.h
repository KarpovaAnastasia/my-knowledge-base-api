#pragma once

#include <string>
#include <optional>

namespace kb::api::stubs {
    // фиктивный пользователь
    struct StubUser {
        std::string id;
        std::string login;
        std::string displayName;
        std::string email;
        std::string role;
    };

    class StubUserService {
    public:
        
        std::optional<StubUser> authenticate(const std::string& login, const std::string& password);// проверка логина и пароля

        std::optional<StubUser> getUserById(const std::string& id);// получение пользователя по ID
    };
}