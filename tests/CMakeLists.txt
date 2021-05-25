add_executable(bookmark_tests
    test_runner.cc
    test_argh.cc
    test_add.cpp
    test_cmdline.cc
    test_markdown_format.cpp
    utils/ram_storage.cpp
    )
target_include_directories(bookmark_tests PRIVATE ${PROJECT_SOURCE_DIR}/doctest)
target_include_directories(bookmark_tests PRIVATE ${PROJECT_SOURCE_DIR}/argh)
target_link_libraries(bookmark_tests PRIVATE booklib)
