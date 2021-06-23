set(MYLINK_COMMON_SOURCES
    cli.cpp
    actions/add.cpp
    parser/parser_impl.cpp
    )


add_executable(mylink main.cc ${MYLINK_COMMON_SOURCES})
target_link_libraries(mylink PRIVATE booklib argh)


add_library(cli_tests OBJECT ${MYLINK_COMMON_SOURCES} test_cli.cpp)
target_link_libraries(cli_tests PRIVATE $<TARGET_PROPERTY:mylink,LINK_LIBRARIES> doctest)
target_include_directories(cli_tests PUBLIC $<TARGET_PROPERTY:mylink,INCLUDE_DIRECTORIES>)
target_compile_definitions(cli_tests PRIVATE MYLINK_TEST_IN_CODE)
