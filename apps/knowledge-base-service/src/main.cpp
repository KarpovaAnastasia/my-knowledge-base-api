#include <drogon/drogon.h>
#include "kb/api/Router.h"

int main() {
    kb::api::registerAllRoutes();// регистрируем все endpoints
  
    drogon::app()
        .addListener("0.0.0.0", 8080) //cлушаем порт 8080 на всех сетевых интерфейсах
        .setThreadNum(4)  //кол-во потоков для обработкит запросов 
        .setDocumentRoot("/app/static") //говорим куда смотреть, если придет не апи запрос
        .setClientMaxBodySize(50 * 1024 * 1024)   //максимальный размер данных, которые клиент передает в теле запроса
        .run();
    return 0;
}