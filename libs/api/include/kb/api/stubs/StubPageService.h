#pragma once

#include <string>
#include <optional>

namespace kb::api::stubs {
    // фиктивная страница для заглушки
    struct StubPage {
        std::string id;
        std::string title;
        std::string content;
        int version;
    };
    class StubPageService {
    public:
        std::optional<StubPage> getPage(const std::string& id);
        StubPage createPage(const std::string& title, const std::string& content);
    };

}