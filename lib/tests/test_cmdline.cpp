#include "doctest.h"
#include <commandlineparser.h>
#include <stdexcept>
#include <sstream>

using namespace mylink;

class MockCollection : public Collection {
public:
    virtual void add(const Bookmark& bookmark) override {
        add_calls_.push_back(bookmark);
    }

    const std::vector<Bookmark>& readAddCalls() { return add_calls_; }

private:
    std::vector<Bookmark> add_calls_;
};

class TestParser {
public:
    TestParser() : collection_{}, stdout_{}, parser_{collection_, stdout_} {}
    std::string get_stdout() { return stdout_.str(); }
    MockCollection& collection() { return collection_; }
    void parse(int argc, const char **argv) { parser_.parse(argc, argv); }
    void parse(const std::vector<std::string> &args) {
        const int ARGC = args.size();
        const char* ARGV[ARGC];
        for(size_t i = 0; i < args.size(); ++i) {
            ARGV[i] = args[i].c_str();
        }
        parser_.parse(ARGC, ARGV);
    }

    void parse_command_and_args(const std::vector<std::string> &command_and_args) {
        std::vector<std::string> actual_args {"mylink"};
        actual_args.insert(actual_args.end(), command_and_args.begin(), command_and_args.end());
        parse(actual_args);
    }

private:
    MockCollection collection_;
    std::stringstream stdout_;
    CommandLineParser parser_;
};

SCENARIO("Invalid command line")
{
    GIVEN("A parser") {
        TestParser parser;

        WHEN("argc == 0") {
            int argc = 0;
            const char **argv = nullptr;

            THEN("An exception is thrown") {
                CHECK_THROWS_AS(parser.parse(argc, argv), std::invalid_argument);
            }
        }

        WHEN("It's called without arguments") {
            std::vector<std::string> args = {"mylink"};
            parser.parse(args);

            THEN("The usage string is printed") {
                CHECK_EQ(parser.get_stdout(), commandline_usage());
            }
        }

        WHEN("It's called with a non-existing command") {
            parser.parse_command_and_args({"nope"});

            THEN("The usage string is printed") {
                CHECK_EQ(parser.get_stdout(), commandline_usage());
            }
        }

    }
}

SCENARIO("Add command")
{
    GIVEN("A parser") {
        TestParser parser;

        WHEN("It's called with 'add'") {
            parser.parse_command_and_args({"add"});

            THEN("The usage string for add is printed") {
                CHECK_EQ(parser.get_stdout(), commandline_add_usage());
            }
        }

        WHEN("It's called with 'add <url>'") {
            parser.parse_command_and_args({"add", "https://wikipedia.org"});

            THEN("Collection.Add is called with <url>") {
                CHECK_EQ(parser.collection().readAddCalls()[0].get_url(), "https://wikipedia.org");
            }
        }
    }
}

