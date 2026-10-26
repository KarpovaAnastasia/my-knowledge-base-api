add_executable(knowledge-base-service
    src/main.cpp
)

target_link_libraries(knowledge-base-service
    PRIVATE
        kb-api
        Drogon::Drogon
        jsoncpp_lib
)