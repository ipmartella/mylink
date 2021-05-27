set(booklib_sources
    src/command_line_parser/command_line_parser.cpp
    src/command_line_parser/parser_impl.cpp
    src/command_line_parser/action_add.cpp
    src/stored_collection.cpp
    src/markdown/markdown_import.cpp
    src/markdown/markdown_export.cpp
    src/bookmark.cpp
)

set(booklib_private_libs argh doctest)
set(booklib_public_include include)


add_library(booklib_with_tests OBJECT ${booklib_sources})
target_link_libraries(booklib_with_tests PRIVATE ${booklib_private_libs} doctest)
target_include_directories(booklib_with_tests PUBLIC ${booklib_public_include})
target_compile_definitions(booklib_with_tests PRIVATE MYLINK_TEST_IN_CODE)

add_library(booklib STATIC ${booklib_sources} )
target_link_libraries(booklib PRIVATE ${booklib_private_libs})
target_include_directories(booklib PUBLIC ${booklib_public_include})
