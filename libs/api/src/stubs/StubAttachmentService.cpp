#include "kb/api/stubs/StubAttachmentService.h"
#include <chrono>

namespace kb::api::stubs {

    std::string StubAttachmentService::saveFile(const std::string& fileName,
        const std::string& base64Content) {
        // заглушка: не сохраняем реальный файл,просто генерируем фиктивный айди 
        // позже заменю на реальный AttachmentService из kb-attachments

        auto now = std::chrono::system_clock::now().time_since_epoch().count();
        return "stub-attachment-" + std::to_string(now);
    }

}