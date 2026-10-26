#include "kb/api/stubs/StubSessionService.h"
#include <unordered_map>
#include <chrono>
#include <random>

namespace kb::api::stubs {
    struct SimpleSession {
        std::string userId;
        std::chrono::system_clock::time_point expiresAt;
    };

    
    static std::unordered_map<std::string, SimpleSession> activeSessions;// словарь, где храним активные сессии 

    std::string StubSessionService::createSession(const std::string& userId) {
        // генерируем простой случайный токен (просто рандомное число в виде строки)
        std::random_device rd;
        std::string token = "token-" + std::to_string(rd());

        // запоминаем, что этот токен принадлежит юзеру и живет 24 часа
        activeSessions[token] = SimpleSession{
            userId,
            std::chrono::system_clock::now() + std::chrono::hours(24)
        };

        return token;
    }

    std::optional<std::string> StubSessionService::validateSession(const std::string& token) {
        // ищем токен в словаре
        auto it = activeSessions.find(token);

        // если нашли и время еще не вышло
        if (it != activeSessions.end()) {
            if (std::chrono::system_clock::now() < it->second.expiresAt) {
                return it->second.userId; // возвращаем ID пользователя
            }
            else {
                activeSessions.erase(it); // если время вышло, удаляем сессию
            }
        }
        return std::nullopt; // токен невалидный
    }

    void StubSessionService::deleteSession(const std::string& token) {
        // просто удаляем токен из словаря при выходе
        activeSessions.erase(token);
    }
}