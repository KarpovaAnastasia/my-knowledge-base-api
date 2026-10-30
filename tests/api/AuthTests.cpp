#include <gtest/gtest.h>
#include "kb/api/stubs/StubUserService.h"
#include "kb/api/stubs/StubSessionService.h"

using namespace kb::api::stubs;

// Тест 1: Успешный вход с правильным паролем
TEST(AuthTest, SuccessfulLogin) {
    StubUserService userService;
    auto user = userService.authenticate("admin", "admin");

    ASSERT_TRUE(user.has_value()); // Проверяем, что пользователь найден
    EXPECT_EQ(user->login, "admin");
    EXPECT_EQ(user->role, "Administrator");
}

// Тест 2: Отказ во входе при неверном пароле 
TEST(AuthTest, FailedLoginWrongPassword) {
    StubUserService userService;
    auto user = userService.authenticate("admin", "wrong_password");

    ASSERT_FALSE(user.has_value()); // Проверяем, что пользователь не найден
}

// Тест 3: Создание и проверка сессии 
TEST(AuthTest, CreateAndValidateSession) {
    StubSessionService sessionService;

    // Создаем сессию
    std::string token = sessionService.createSession("user-123");
    ASSERT_FALSE(token.empty()); // Токен не пустой

    // Проверяем валидность
    auto userId = sessionService.validateSession(token);
    ASSERT_TRUE(userId.has_value());
    EXPECT_EQ(*userId, "user-123");
}

// Тест 4: Удаление сессии 
TEST(AuthTest, DeleteSession) {
    StubSessionService sessionService;

    std::string token = sessionService.createSession("user-123");
    sessionService.deleteSession(token); // Удаляем сессию

    // Пытаемся проверить удаленную сессию. должно вернуться nullopt
    auto userId = sessionService.validateSession(token);
    ASSERT_FALSE(userId.has_value());
}

// Тест 5: Проверка невалидного токена
TEST(AuthTest, ValidateInvalidToken) {
    StubSessionService sessionService;
    auto userId = sessionService.validateSession("fake-token-12345");
    ASSERT_FALSE(userId.has_value());
}