#include "cli.h"

namespace  {

/**
 * @brief Parse command line arguments and returns the action to execute.
 *
 * The 'action' is the second command line parameter (i.e. add, remove, etc.).
 * If no action can be found, this functions returns an empty string.
 *
 * @param argc Number of command line arguments (as specified in standard C)
 * @param argv Array of command line arguments (as specified in standard C)
 * @return Action parsed from the command line, or empty string
 */
std::string parse_action_from_command_line(int argc, const char** argv) {
    constexpr int argument_index_action = 1;

    if(argc > argument_index_action) {
        return std::string{argv[argument_index_action]};
    } else {
        return "";
    }
}


} //namespace


/**
 * @brief Main thread of execution for the mylink CLI.
 *
 * This function implements all functionalities of the mylink CLI.
 * It exists only to make it easier to run automated tests.
 *
 * @param argc Number of command line arguments (as specified in standard C)
 * @param argv Array of command line arguments (as specified in standard C)
 * @param stdout Output stream to use as standard output
 * @return 0 (for now)
 */
int mylink::cli::command_line_shell(int argc, const char** argv, std::ostream& stdout) {
    const auto action = parse_action_from_command_line(argc, argv);

    if(action.empty()) {
        stdout << commandline_usage();
    } else {
        stdout << action << "\n";
    }

    return 0;
}

std::string mylink::cli::commandline_usage() {
    return "Usage: mylink <command> [<args>]\n"
           "\n"
           "Available commands:\n"
           "add\tAdds a bookmark to a collection\n"
           "\n";
}

#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>

SCENARIO("First level command line argument parsing") {
    GIVEN("Command line: mylink") {
        int argc = 1;
        const char* argv[] = {"mylink"};

        WHEN("I get the action") {
            auto action = parse_action_from_command_line(argc, argv);

            THEN("I get an empty string") {
                CHECK(action.empty());
            }
        }
    }

    GIVEN("Command line: mylink add") {
        int argc = 2;
        const char* argv[] = {"mylink", "add"};

        WHEN("I get the action") {
            auto action = parse_action_from_command_line(argc, argv);

            THEN("I get 'add'") {
                CHECK_EQ(action, "add");
            }
        }
    }
}

#endif
