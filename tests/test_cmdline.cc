#include "doctest.h"
#include "commandlineparser.hpp"
#include <stdexcept>

using namespace mylink;

CommandLineParser buildTestParser() {
    return CommandLineParser{};
}


SCENARIO("Invalid command line")
{
    GIVEN("argc == 0") {
        int argc = 0;
        char **argv = nullptr;

        WHEN("The parser is called") {
            CommandLineParser parser = buildTestParser();

            THEN("An exception is thrown") {
                CHECK_THROWS_AS(parser.parse(argc, argv), std::invalid_argument);
            }
        }
    }
}
