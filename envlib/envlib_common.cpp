#include "envlib.h"
#include <regex>

std::string mylink::utils::get_current_executable_directory() {
#if defined(__WIN32)
    static const std::regex s_regex_extractpath(R"((.*\\).+)");
#else
    static const std::regex s_regex_extractpath(R"((.*\/).+)");
#endif

    const std::string executable_path = get_current_executable_path();

    std::smatch sm;
    if(std::regex_match(executable_path, sm, s_regex_extractpath)) {
        return sm[1];
    } else {
        return "";
    }
}
