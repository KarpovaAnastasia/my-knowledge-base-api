
find_package(GTest REQUIRED)

add_executable(kb-api-tests
    api/AuthTests.cpp
    api/ContentTests.cpp
)

target_link_libraries(kb-api-tests
    PRIVATE
        kb-api
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(kb-api-tests)