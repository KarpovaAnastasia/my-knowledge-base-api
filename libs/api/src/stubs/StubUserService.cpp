#include "kb/api/stubs/StubUserService.h"

namespace kb::api::stubs {

    std::optional<StubUser> StubUserService::authenticate(const std::string& login, const std::string& password) {
        // пока разрешаем вход только админу с паролем "admin"
        // позже заменю на реальную проверку хеша пароля из базы
        if (login == "admin" && password == "admin") {
            return StubUser{
                "user-123",
                "admin",
                "Главный Администратор",
                "admin@example.com",
                "Administrator"
            };
        }
        return std::nullopt; // если логин/пароль неверные
    }

    std::optional<StubUser> StubUserService::getUserById(const std::string& id) {
        //возвращаем того же админа, если запрашивают его ID
        if (id == "user-123") {
            return StubUser{
                "user-123",
                "admin",
                "Главный Администратор",
                "admin@example.com",
                "Administrator"
            };
        }
        return std::nullopt;
    }
}
