set(MYLINK_COMMON_SOURCES
    cli.cpp
    actions/add.cpp
    actions/server.cpp
    parser/parser_impl.cpp
    server/server.cpp
    server/bookmark_json_converter.cpp
    )


add_executable(mylink main.cpp ${MYLINK_COMMON_SOURCES})
target_link_libraries(mylink PRIVATE booklib envlib argh cpp-httplib pthread json)


add_library(cli_tests OBJECT ${MYLINK_COMMON_SOURCES}
     tests/test_cli.cpp
     tests/test_server.cpp
     )
target_link_libraries(cli_tests PRIVATE $<TARGET_PROPERTY:mylink,LINK_LIBRARIES> doctest)
target_include_directories(cli_tests PUBLIC $<TARGET_PROPERTY:mylink,INCLUDE_DIRECTORIES>)
target_compile_definitions(cli_tests PRIVATE MYLINK_TEST_IN_CODE)
