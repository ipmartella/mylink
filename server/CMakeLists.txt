add_executable(mylinkserver server.cpp)
target_link_libraries(mylinkserver PRIVATE booklib cpp-httplib pthread json)
