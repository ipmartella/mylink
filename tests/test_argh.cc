#include "doctest.h"
#include "argh.h"

TEST_CASE("CMD: positional argument") {
    argh::parser parser;
    const char* argv[3] = {"bookm", "add", "https://github.com/ipmart"};
    parser.parse(3, argv);

    CHECK_EQ(parser[0], "bookm");
    CHECK_EQ(parser[1], "add");
    CHECK_EQ(parser[2], "https://github.com/ipmart");
}

TEST_CASE("CMD: short parameters") {
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"bookm", "add", "https://github.com/ipmart", "-h", "My Github"};
    parser.parse(5, argv);

    CHECK_EQ(parser({"h", "header"}).str(), "My Github");
}


TEST_CASE("CMD: long parameters") {
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"bookm", "add", "https://github.com/ipmart", "--header", "My Github"};
    parser.parse(5, argv);

    CHECK_EQ(parser({"h", "header"}).str(), "My Github");
}

TEST_CASE("CMD: parameters and default values")
{
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"bookm", "add", "https://github.com/ipmart"};
    parser.parse(3, argv);

    CHECK_EQ(parser({"h", "header"}, "My Github").str(), "My Github");
    CHECK_EQ(parser("h", "My Github").str(), "My Github");
    CHECK_EQ(parser("header", "My Github").str(), "My Github");
}

TEST_CASE("CMD: short flags") {
    argh::parser parser;
    const char* argv[] = {"bookm", "add", "https://github.com/ipmart", "-v"};
    parser.parse(4, argv);

    CHECK(parser[{"v", "verbose"}]);
}

TEST_CASE("CMD: long flags") {
    argh::parser parser;
    const char* argv[] = {"bookm", "add", "https://github.com/ipmart", "--verbose"};
    parser.parse(4, argv);

    CHECK(parser[{"v", "verbose"}]);
}

TEST_CASE("CMD: Check positional parameters exist")
{
    argh::parser parser;
    const char* argv[] = {"bookm", "add"};
    parser.parse(2, argv);

    CHECK(parser(0));
    CHECK(parser(1));
    CHECK_FALSE(parser(2));
}
