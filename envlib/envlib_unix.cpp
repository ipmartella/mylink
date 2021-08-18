#include "envlib.h"
#include <unistd.h>
#include <array>

std::string mylink::utils::get_current_executable_path() {
    constexpr const char* introspection_file = "/proc/self/exe";
    constexpr size_t buffer_size = 2048;

    std::array<char, buffer_size> buffer;

    const size_t used = readlink(introspection_file, buffer.data(), buffer.size());
    /*
     * From readlink manpage:
     * On success, readlink() returns the number of bytes placed in buf. On error, -1 is returned and errno is set to indicate the error.
     */
    if(used < 0 || used > buffer.size()) {
        return std::string{}; //Empty string
    } else {
        return std::string{buffer.data(), used};
    }
}

std::string mylink::utils::get_system_temporary_directory() {
    static std::string temporary_directory{"/tmp/"};
    return temporary_directory;
}
