add_library(booklib STATIC src/markdown_collection.cpp src/commandlineparser.cpp)
target_include_directories(booklib PRIVATE ${PROJECT_SOURCE_DIR}/argh)
target_include_directories(booklib PUBLIC include)

#set_property(
#    TARGET booklib
#    PROPERTY PUBLIC_HEADER
#    ${CMAKE_CURRENT_SOURCE_DIR}/collection.hpp
#    )

