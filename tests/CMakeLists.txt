
message(STATUS "TESTS: ${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(bookmark_tests
    test_runner.cc
    mock_storage_backend.cpp
    $<TARGET_OBJECTS:booklib_tests>
    $<TARGET_OBJECTS:argh_tests>
    $<TARGET_OBJECTS:json_tests>
    $<TARGET_OBJECTS:cpp-httplib_tests>
    $<TARGET_OBJECTS:cli_tests>
    )

target_link_libraries(bookmark_tests PRIVATE doctest)
target_link_libraries(bookmark_tests PRIVATE argh)
target_link_libraries(bookmark_tests PRIVATE pthread)
target_link_libraries(bookmark_tests PRIVATE $<TARGET_PROPERTY:cpp-httplib_tests,INTERFACE_LINK_LIBRARIES>)
target_include_directories(bookmark_tests PRIVATE
    $<TARGET_PROPERTY:booklib,INTERFACE_INCLUDE_DIRECTORIES>
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
