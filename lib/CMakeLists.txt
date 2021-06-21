set(booklib_sources
    src/markdown_storage.cpp
    src/bookmark.cpp
    src/collection.cpp
    src/collection_iterator.cpp
)

set(booklib_private_libs argh doctest)
set(booklib_public_include include)

add_library(booklib STATIC ${booklib_sources} )
target_link_libraries(booklib PRIVATE ${booklib_private_libs})
target_include_directories(booklib PUBLIC ${booklib_public_include})

add_library(booklib_test_utils INTERFACE)
target_include_directories(booklib_test_utils INTERFACE tests/test_utils)

add_library(booklib_tests OBJECT $<TARGET_PROPERTY:booklib,SOURCES>
    tests/test_bookmark.cpp
    tests/test_markdown_storage.cpp
    tests/test_collection.cpp
    )
target_link_libraries(booklib_tests PRIVATE $<TARGET_PROPERTY:booklib,LINK_LIBRARIES> doctest booklib_test_utils)
target_include_directories(booklib_tests PUBLIC $<TARGET_PROPERTY:booklib,INCLUDE_DIRECTORIES>)
target_compile_definitions(booklib_tests PRIVATE MYLINK_TEST_IN_CODE)
