cmake_minimum_required(VERSION 3.5)

project(mylink LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(custom_commands_macros.cmake)
add_subdirectory(ext)
add_subdirectory(envlib)
add_subdirectory(lib)
add_subdirectory(cli)
add_subdirectory(tests)

