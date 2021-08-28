add_executable(mylink_tests
    test_runner.cc
    mock_storage_backend.cpp
    $<TARGET_OBJECTS:mylinklib_tests>
    $<TARGET_OBJECTS:argh_tests>
    $<TARGET_OBJECTS:json_tests>
    $<TARGET_OBJECTS:cpp-httplib_tests>
    $<TARGET_OBJECTS:cli_tests>
    )

target_link_libraries(mylink_tests PRIVATE doctest)
target_link_libraries(mylink_tests PRIVATE argh)

if(CMAKE_HOST_UNIX)
    target_link_libraries(mylink_tests PRIVATE pthread)
endif()

target_link_libraries(mylink_tests PRIVATE envlib)
target_link_libraries(mylink_tests PRIVATE $<TARGET_PROPERTY:cpp-httplib_tests,INTERFACE_LINK_LIBRARIES>)
target_include_directories(mylink_tests PRIVATE
    $<TARGET_PROPERTY:mylinklib,INTERFACE_INCLUDE_DIRECTORIES>
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

copy_www_with_target(mylink_tests)
