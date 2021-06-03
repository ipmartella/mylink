add_executable(mylinkserver main.cpp server.cpp)
target_link_libraries(mylinkserver PRIVATE booklib cpp-httplib pthread json)

add_library(mylinkserver_tests OBJECT
    # Server sources
    server.cpp
    # Tests
    tests/test_server.cpp)
target_link_libraries(mylinkserver_tests PRIVATE doctest $<TARGET_PROPERTY:mylinkserver,LINK_LIBRARIES> booklib_test_utils)
