add_library(booklib STATIC markdown_collection.cc commandlineparser.cc)
target_include_directories(booklib PRIVATE ${PROJECT_SOURCE_DIR}/argh)
target_include_directories(booklib PUBLIC .)

#set_property(
#    TARGET booklib
#    PROPERTY PUBLIC_HEADER
#    ${CMAKE_CURRENT_SOURCE_DIR}/collection.hpp
#    )

