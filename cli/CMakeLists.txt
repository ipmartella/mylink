add_executable(mylink main.cc)
target_include_directories(mylink PRIVATE ${PROJECT_SOURCE_DIR}/argh)
target_link_libraries(mylink PRIVATE booklib)
