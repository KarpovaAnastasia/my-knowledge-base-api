cmake_minimum_required(VERSION 4.0)
project(knowledge-base-api)

set (CMAKE_CXX_STANDARD 20)

add_executable(knowledge-base-api apps/knowledge-base-service/src/main.cpp)