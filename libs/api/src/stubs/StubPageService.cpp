#include "kb/api/stubs/StubPageService.h"

namespace kb::api::stubs {

    std::optional<StubPage> StubPageService::getPage(const std::string& id) {
        // симулируем 404
        if (id == "not-found") {
            return std::nullopt;
        }
        //иначе фиктивная страница
        StubPage page;
        page.id = id;
        page.title = "Testing page" + id;
        page.content = "Not real";
        page.version = 1;
        return page;
    }

    StubPage StubPageService::createPage(const std::string& title, const std::string& content) {
        StubPage page;
        page.id = "stub-" + title;
        page.title = title;
        page.content = content;
        page.version = 1;
        return page;
    }

}