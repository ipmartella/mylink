#include <doctest.h>
#include "cli.h"
#include <sstream>

using namespace mylink::cli;

SCENARIO("Invalid command lines") {
    std::ostringstream command_output_stream;

    GIVEN("Command line: mylink") {
        const int argc = 1;
        const char* argv[] = {"mylink"};

        WHEN("I run the executable") {
            command_line_shell(argc, argv, command_output_stream);

            THEN("The usage string is printed") {
                CHECK_EQ(command_output_stream.str(), commandline_usage());
            }
        }
    }

    GIVEN("Command line with non existing command: mylink nope") {
        const int argc = 2;
        const char* argv[] = {"mylink", "nope"};

        WHEN("I run the executable") {
            command_line_shell(argc, argv, command_output_stream);

            THEN("The usage string is printed") {
                CHECK_EQ(command_output_stream.str(), commandline_usage());
            }
        }
    }
}
