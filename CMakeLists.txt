cmake_minimum_required(VERSION 3.5)

project(opp_cpp_cmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(CBenchmark)
add_subdirectory(Binary)

