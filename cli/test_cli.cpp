#include <doctest.h>
#include "cli.h"
#include "actions.h"
#include <sstream>
#include <vector>
#include "../tests/mock_storage_backend.h"

using namespace mylink;
using namespace mylink::cli;
using namespace mylink::test;

namespace {


struct CommandResult {
    CommandResult(int return_code, std::string output, MockStorageBackend backend) :
        return_code{return_code}, output{output}, backend{backend} {}

    int return_code;
    std::string output;
    MockStorageBackend backend;
};

CommandResult run_mylink_with_args(std::vector<std::string> args,
                                   const BookmarkCollection& existing_collection = BookmarkCollection{}) {
    std::ostringstream command_output_stream;
    const int argc = args.size() + 1;
    const char* argv[argc];

    argv[0] = "mylink";
    for(int i = 1; i < argc; ++i) {
        argv[i] = args[i - 1].c_str();
    }

    MockStorageBackend backend(existing_collection);

    auto return_code = command_line_shell(argc, argv, backend, command_output_stream);
    return CommandResult{return_code, command_output_stream.str(), backend};
}



} //namespace


SCENARIO("Invalid command lines") {
    GIVEN("Command line: mylink") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({});

            THEN("The usage string is printed") {
                CHECK_EQ(result.output, basic_usage());
            }
        }
    }

    GIVEN("Command line with non existing command: mylink nope") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"nope"});

            THEN("The usage string is printed") {
                CHECK_EQ(result.output, basic_usage());
            }
        }
    }
}

SCENARIO("Add bookmark") {
    GIVEN("Command line: mylink add") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add"});

            THEN("The usage string for 'add' is printed") {
                CHECK_EQ(result.output, action_add_usage());
            }
        }
    }
    GIVEN("Command line: mylink add -h") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add", "-h"});

            THEN("The usage string for 'add' is printed") {
                CHECK_EQ(result.output, action_add_usage());
            }
        }
    }
    GIVEN("Command line: mylink add --help") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add", "-h"});

            THEN("The usage string for 'add' is printed") {
                CHECK_EQ(result.output, action_add_usage());
            }
        }
    }

    GIVEN("Command line: mylink add 'http://www.url1.org'") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add", "http://www.url1.org"});

            THEN("The stored collection contains http://www.url1.org") {
                auto collection = result.backend.get_saved_collection();
                REQUIRE(collection);
                CHECK(collection->contains("http://www.url1.org"));
                CHECK_EQ(result.return_code, 0);
            }
        }
    }

    GIVEN("Command line: mylink add 'http://www.url1.org' -t Title1") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add", "http://www.url1.org", "-t", "Title1"});

            THEN("The stored collection contains http://www.url1.org with title Title1") {
                auto collection = result.backend.get_saved_collection();
                REQUIRE(collection);
                CHECK(collection->contains("http://www.url1.org"));
                CHECK_EQ((*collection)["http://www.url1.org"].get_title(), "Title1");
                CHECK_EQ(result.return_code, 0);
            }
        }
    }

    GIVEN("Command line: mylink add 'http://www.url1.org' --title Title1") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add", "http://www.url1.org", "--title", "Title1"});

            THEN("The stored collection contains http://www.url1.org with title Title1") {
                auto collection = result.backend.get_saved_collection();
                REQUIRE(collection);
                CHECK(collection->contains("http://www.url1.org"));
                CHECK_EQ((*collection)["http://www.url1.org"].get_title(), "Title1");
                CHECK_EQ(result.return_code, 0);
            }
        }
    }

    GIVEN("Command line: mylink add --title Title1") {
        WHEN("I run the executable") {
            auto result = run_mylink_with_args({"add", "--title", "Title1"});
            THEN("The usage string for 'add' is printed") {
                CHECK_EQ(result.output, action_add_usage());
            }
        }
    }

}
