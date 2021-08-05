add_library(cpp-httplib INTERFACE)
target_include_directories(cpp-httplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_HOST_WIN32)
    target_link_libraries(cpp-httplib INTERFACE wsock32 ws2_32)
endif()

add_library(cpp-httplib_tests OBJECT test_cpp-httplib.cpp)
target_link_libraries(cpp-httplib_tests PUBLIC doctest cpp-httplib)
