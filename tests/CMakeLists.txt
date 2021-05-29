
add_executable(bookmark_tests
    test_runner.cc
    test_argh.cc
    test_cmdline.cc
    test_bookmark.cpp
    $<TARGET_OBJECTS:booklib_with_tests>
    )

target_link_libraries(bookmark_tests PRIVATE doctest)
target_link_libraries(bookmark_tests PRIVATE argh)
target_include_directories(bookmark_tests PRIVATE $<TARGET_PROPERTY:booklib,INTERFACE_INCLUDE_DIRECTORIES>)
