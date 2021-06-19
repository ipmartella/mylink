
message(STATUS "TESTS: ${MYLINK_TEST_OBJECTS}")
add_executable(bookmark_tests
    test_runner.cc
    $<TARGET_OBJECTS:booklib_tests>
    $<TARGET_OBJECTS:argh_tests>
    #$<TARGET_OBJECTS:mylinkserver_tests>
    )

target_link_libraries(bookmark_tests PRIVATE doctest)
target_link_libraries(bookmark_tests PRIVATE argh)
target_link_libraries(bookmark_tests PRIVATE pthread)
target_include_directories(bookmark_tests PRIVATE $<TARGET_PROPERTY:booklib,INTERFACE_INCLUDE_DIRECTORIES>)
