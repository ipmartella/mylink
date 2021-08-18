# Makes sure the www folder is copied in the build folder of <target_name>, before <target_name> is built.
macro(copy_www_with_target target_name)
        add_custom_command(TARGET ${target_name} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_SOURCE_DIR}/www/ $<TARGET_FILE_DIR:${target_name}>/www)
endmacro()
