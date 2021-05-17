cmake_minimum_required(VERSION 3.5)

project(bookmarkmanager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bookmarkmanager main.cpp)

add_executable(bookmark_tests tests/test_runner.cc tests/test_argh.cc)
target_include_directories(bookmark_tests PRIVATE ${PROJECT_SOURCE_DIR}/doctest)
target_include_directories(bookmark_tests PRIVATE ${PROJECT_SOURCE_DIR}/argh)
