#include "path_utils.h"

#include <regex>
#include <array>
#include <unistd.h>

/**
 * @brief Returns the absolute path of the process currently being executed
 * @return the absolute path of the process currently being executed
 */
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

/**
 * @brief Returns the absolute path of the folder where process currently being executed is located (trailing / is included)
 * @return the absolute path here process currently being executed is located (trailing / is included)
 */
std::string mylink::utils::get_current_executable_directory() {
    static const std::regex s_regex_extractpath(R"((.*\/).+)");

    const std::string executable_path = get_current_executable_path();

    std::smatch sm;
    if(std::regex_match(executable_path, sm, s_regex_extractpath)) {
        return sm[1];
    } else {
        return "";
    }
}
