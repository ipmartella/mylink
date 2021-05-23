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
    void parse(int argc, char **argv) { parser_.parse(argc, argv); }

private:
    MockCollection collection_;
    std::stringstream stdout_;
    CommandLineParser parser_;
};


SCENARIO("Invalid command line")
{
    GIVEN("argc == 0") {
        int argc = 0;
        char **argv = nullptr;

        WHEN("The parser is called") {
            TestParser parser;

            THEN("An exception is thrown") {
                CHECK_THROWS_AS(parser.parse(argc, argv), std::invalid_argument);
            }
        }
    }

    GIVEN("argc == 1") {
        int argc = 1;
        char **argv = nullptr;

        WHEN("The parser is called") {
            TestParser parser;
            parser.parse(argc, argv);

            THEN("The usage string is printed") {
                CHECK_EQ(parser.get_stdout(), commandline_usage());
            }
        }
    }
}
