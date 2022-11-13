cmake_minimum_required(VERSION 3.22)
project(lab_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        lab_1 main.cpp
        bigint.cpp
        bigint.h
gtest_main.cpp bigint_unittest.cpp)

add_subdirectory(lib/googletests)
include_directories(lib/googletests/include)
target_link_libraries(lab_1 gtest gtest_main)
