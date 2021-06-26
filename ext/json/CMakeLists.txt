add_library(json INTERFACE)
target_include_directories(json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(json_tests OBJECT test_json.cpp)
target_link_libraries(json_tests PUBLIC doctest)
