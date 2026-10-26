
add_library(kb-api STATIC
    src/HealthController.cpp
    src/Router.cpp
    src/PageController.cpp
    src/ProjectController.cpp
    src/AuthController.cpp
    src/AuthHelper.cpp             
    src/stubs/StubPageService.cpp
    src/stubs/StubProjectService.cpp
    src/stubs/StubAttachmentService.cpp
    src/stubs/StubUserService.cpp
    src/stubs/StubSessionService.cpp
)

target_include_directories(kb-api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(kb-api
    PUBLIC
        Drogon::Drogon
        jsoncpp_lib
)