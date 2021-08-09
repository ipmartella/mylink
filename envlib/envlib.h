#ifndef PATH_UTILS_H
#define PATH_UTILS_H
#include <string>

namespace mylink {
namespace utils {

/**
 * @brief Returns the absolute path of the process currently being executed
 * @return the absolute path of the process currently being executed
 */
std::string get_current_executable_path();

/**
 * @brief Returns the absolute path of the folder where process currently being executed is located (trailing / is included)
 * @return the absolute path here process currently being executed is located (trailing / or \ is included)
 */
std::string get_current_executable_directory();

/**
 * @brief Returns the absolute path of the folder where the system stores temporary files (trailing / or \ is included)
 * @return the absolute path here process currently being executed is located (trailing / or \ is included)
 */
std::string get_system_temporary_directory();

} //namespace utils
} //namespace mylink

#endif // PATH_UTILS_H
