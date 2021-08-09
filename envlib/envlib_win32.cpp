#include "envlib.h"
#include <libloaderapi.h>
#include <string>
#include <array>


std::string mylink::utils::get_current_executable_path() {
    constexpr HMODULE current_module = 0;
    constexpr size_t buffer_size = 2048;
    std::array<TCHAR, buffer_size> buffer;

    const auto used = GetModuleFileNameA(current_module, buffer.data(), buffer.size());
    /*
     * Source: https://docs.microsoft.com/it-it/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamea?redirectedfrom=MSDN
     *
     * Return value
     *
     * If the function succeeds, the return value is the length of the string that is copied to the buffer, in characters,
     * not including the terminating null character. If the buffer is too small to hold the module name, the string is truncated
     * to nSize characters including the terminating null character, the function returns nSize, and the function sets the last
     * error to ERROR_INSUFFICIENT_BUFFER.
     *
     * Windows XP:  If the buffer is too small to hold the module name, the function returns nSize. The last error code remains ERROR_SUCCESS. If nSize is zero, the return value is zero and the last error code is ERROR_SUCCESS.
     *
     * If the function fails, the return value is 0 (zero). To get extended error information, call GetLastError.
     */

    if(used <= 0 || used >= buffer.size()) {
        return std::string{}; //Empty string
    } else {
        return std::string{buffer.data(), used};
    }
}

std::string mylink::utils::get_system_temporary_directory() {
    constexpr const char* tmp_environment_variable = "TMP";
    static std::string temporary_directory = []{
        std::string path{std::getenv(tmp_environment_variable)};
        return path + std::string{"\\"}; //Add trailing backslash
    }();

    return temporary_directory;
}
