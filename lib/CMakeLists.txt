set(mylinklib_sources
    src/markdown_storage.cpp
    src/bookmark.cpp
    src/collection.cpp
    src/collection_iterator.cpp
)

set(mylinklib_private_libs argh doctest)
set(mylinklib_public_include include)

add_library(mylinklib STATIC ${mylinklib_sources} )
target_link_libraries(mylinklib PRIVATE ${mylinklib_private_libs})
target_include_directories(mylinklib PUBLIC ${mylinklib_public_include})

add_library(mylinklib_test_utils INTERFACE)
target_include_directories(mylinklib_test_utils INTERFACE tests/test_utils)

add_library(mylinklib_tests OBJECT $<TARGET_PROPERTY:mylinklib,SOURCES>
    tests/test_bookmark.cpp
    tests/test_markdown_storage.cpp
    tests/test_collection.cpp
    )
target_link_libraries(mylinklib_tests PRIVATE $<TARGET_PROPERTY:mylinklib,LINK_LIBRARIES> doctest mylinklib_test_utils envlib)
target_include_directories(mylinklib_tests PUBLIC $<TARGET_PROPERTY:mylinklib,INCLUDE_DIRECTORIES>)
target_compile_definitions(mylinklib_tests PRIVATE MYLINK_TEST_IN_CODE)
