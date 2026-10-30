cmake_minimum_required(VERSION 3.20)
project(knowledge-base-api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
add_subdirectory(libs/api)
add_subdirectory(apps/knowledge-base-service)
enable_testing()
add_subdirectory(tests)