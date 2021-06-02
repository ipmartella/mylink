add_library(argh INTERFACE)
target_include_directories(argh INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(argh_tests OBJECT test_argh.cc)
target_link_libraries(argh_tests PUBLIC doctest)
