add_library(cpp-httplib INTERFACE)
target_include_directories(cpp-httplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(cpp-httplib_tests OBJECT test_cpp-httplib.cpp)
target_link_libraries(cpp-httplib_tests PUBLIC doctest)
