#pragma once

#include <string>
#include <optional>

namespace kb::api::stubs {
    // Фиктивный проект для заглушки
    struct StubProject {
        std::string id;
        std::string name;
        std::string description;
        std::string attachmentId;  // ID файла (если приложен)
        std::string fileName;      // оригинальное имя файла
    };

    class StubProjectService {
    public:
        StubProject createProject(const std::string& name, const std::string& description, const std::string& attachmentId, const std::string& fileName);// создать проект

        std::optional<StubProject> getProject(const std::string& id);// получить проект по ID
    };

}