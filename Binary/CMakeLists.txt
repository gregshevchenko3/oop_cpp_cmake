cmake_minimum_required(VERSION 3.5)

project(Binary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Binary main.cpp Binary.hpp Binary.cpp)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Source dir: ${CMAKE_CURRENT_SOURCE_DIR}/..")
target_include_directories(Binary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../CBenchmark)
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_dependencies(Binary CBenchmark)
    target_link_directories(Binary PRIVATE ${CMAKE_BINARY_DIR}/CBenchmark)
    target_link_libraries(Binary CBenchmark.lib)
endif()

