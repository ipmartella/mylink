#include "cli.h"
#include "actions.h"
#include "parser/parser_impl.h"

using namespace mylink;

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
 * @param backend Storage backend to use for saving/loading the BookmarkCollection
 * @param out_stream Output stream to use as standard output
 * @return 0 (for now)
 */
int mylink::cli::command_line_shell(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& out_stream) {
    const auto action = parse_action_from_command_line(argc, argv);

    if(action == "add") {
        return action_add(argc, argv, backend, out_stream);
    } else if(action == "server" ) {
        return action_server(argc, argv, backend, out_stream);
    } else {
        out_stream << basic_usage();
    }

    return 0;
}


std::string mylink::cli::basic_usage() {
    static const std::string usage =  \
            "MyLink v" + std::to_string(MYLINK_VERSION_MAJOR) + "." + std::to_string(MYLINK_VERSION_MINOR) + "." + std::to_string(MYLINK_VERSION_PATCH) + "\n"
           "Usage: mylink <command> [<args>]\n"
           "\n"
           "Available commands:\n"
           "add\tAdds a bookmark to a collection\n"
           "server\tMakes your MyLink collection available to web browsers\n"
           "\n";

    return usage;
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

    GIVEN("Command line: mylink server") {
        int argc = 2;
        const char* argv[] = {"mylink", "server"};

        WHEN("I get the action") {
            auto action = parse_action_from_command_line(argc, argv);

            THEN("I get 'server'") {
                CHECK_EQ(action, "server");
            }
        }
    }
}

#endif
