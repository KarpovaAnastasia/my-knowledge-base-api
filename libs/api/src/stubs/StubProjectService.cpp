#include "kb/api/stubs/StubProjectService.h"
#include <chrono>

namespace kb::api::stubs {

    StubProject StubProjectService::createProject(const std::string& name,
        const std::string& description,
        const std::string& attachmentId,
        const std::string& fileName) {
        //генерируем фиктивный ID проекта
        auto now = std::chrono::system_clock::now().time_since_epoch().count();

        StubProject project;
        project.id = "stub-project-" + std::to_string(now);
        project.name = name;
        project.description = description;
        project.attachmentId = attachmentId;
        project.fileName = fileName;
        return project;
    }

    std::optional<StubProject> StubProjectService::getProject(const std::string& id) {
        // симулирем 404
        if (id == "not-found") {
            return std::nullopt;
        }

        // инче фиктивный проект
        StubProject project;
        project.id = id;
        project.name = "Тестовый проект " + id;
        project.description = "Это заглушка. Позже заменим на реальный вызов kb-content.";
        project.attachmentId = "stub-attachment-123";
        project.fileName = "test-file.pdf";
        return project;
    }

}