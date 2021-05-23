#include "doctest.h"
#include "commandlineparser.hpp"
#include <stdexcept>
#include <sstream>

using namespace mylink;

class MockCollection : public Collection {
public:
    void add(const Bookmark bookmark) override {
        add_calls_.push_back(bookmark);
    }

    const std::vector<Bookmark>& readAddCalls() {
        return add_calls_;
    }

private:
    std::vector<Bookmark> add_calls_;
};

class TestParser {
public:
    TestParser() : collection_{}, stdout_{}, parser_{collection_, stdout_} {}
    std::string get_stdout() { return stdout_.str(); }
    MockCollection& collection() { return collection_; }
    void parse(int argc, const char **argv) { parser_.parse(argc, argv); }
    void parse(const std::vector<std::string> args) {
        const int ARGC = args.size();
        const char* ARGV[ARGC];
        for(size_t i = 0; i < args.size(); ++i) {
            ARGV[i] = args[i].c_str();
        }
        parser_.parse(ARGC, ARGV);
    }

private:
    MockCollection collection_;
    std::stringstream stdout_;
    CommandLineParser parser_;
};


SCENARIO("Invalid command line")
{
    TestParser parser;

    GIVEN("argc == 0") {
        int argc = 0;
        const char **argv = nullptr;

        WHEN("The parser is called") {
            THEN("An exception is thrown") {
                CHECK_THROWS_AS(parser.parse(argc, argv), std::invalid_argument);
            }
        }
    }

    GIVEN("argc == 1") {
        std::vector<std::string> args = {"mylink"};

        WHEN("The parser is called") {
            parser.parse(args);

            THEN("The usage string is printed") {
                CHECK_EQ(parser.get_stdout(), commandline_usage());
            }
        }
    }

    GIVEN("A non-existing command") {
        std::vector<std::string> args = {"mylink", "nope"};

        WHEN("The parser is called") {
            parser.parse(args);

            THEN("The usage string is printed") {
                CHECK_EQ(parser.get_stdout(), commandline_usage());
            }
        }
    }
}
