#include "kb/api/Router.h"
#include "kb/api/HealthController.h"
#include "kb/api/PageController.h"
#include "kb/api/ProjectController.h"
#include "kb/api/AuthController.h"

namespace kb::api {

    void registerAllRoutes() {
        registerHealthEndpoint();   // health endpoint

        registerPageEndpoints();    // endpoints для страниц 
        registerProjectEndpoints(); // endpoints для проектов 

        registerAuthEndpoints();    //endpoints для аутентификации 
    }

}
