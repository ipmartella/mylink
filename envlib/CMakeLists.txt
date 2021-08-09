set(envlib_platform_sources)

if(CMAKE_HOST_WIN32)
    set(envlib_platform_sources envlib_win32.cpp)
endif()

if(CMAKE_HOST_UNIX)
    set(envlib_platform_sources envlib_unix.cpp)
endif()

add_library(envlib STATIC envlib_common.cpp ${envlib_platform_sources})
target_include_directories(envlib PUBLIC .)
