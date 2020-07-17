cmake_minimum_required(VERSION 3.5)

project(CBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/CBenchmark.cpp)
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/CBenchmark.cpp)

add_library(CBenchmark OBJECT CBenchmark.cpp CBenchmark.hpp)

