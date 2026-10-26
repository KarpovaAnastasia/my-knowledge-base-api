#pragma once

#include <string>

namespace kb::api::stubs {
    // заглушка файлового хранилища.Пока не подключён kb-attachments,"сохраняет" файл в никуда и возвращает фиктивный ID
    class StubAttachmentService {
    public:
        // принимает имя файла + содержимое (base64), возвращает фиктивный ID вложения
        std::string saveFile(const std::string& fileName, const std::string& base64Content);
    };

}