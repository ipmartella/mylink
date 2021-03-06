#include "doctest.h"
#include "argh.h"

TEST_CASE("CMD: positional argument") {
    argh::parser parser;
    const char* argv[3] = {"mylink", "add", "https://github.com/ipmartella"};
    parser.parse(3, argv);

    CHECK_EQ(parser[0], "mylink");
    CHECK_EQ(parser[1], "add");
    CHECK_EQ(parser[2], "https://github.com/ipmartella");
}

TEST_CASE("CMD: short parameters") {
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"mylink", "add", "https://github.com/ipmartella", "-h", "My Github"};
    parser.parse(5, argv);

    CHECK_EQ(parser({"h", "header"}).str(), "My Github");
}

TEST_CASE("CMD: short parameters repeated") {
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"mylink", "add", "https://github.com/ipmartella", "-h", "My Test", "-h", "My Github"};
    parser.parse(7, argv);

    CHECK_EQ(parser({"h", "header"}).str(), "My Test");
}

TEST_CASE("CMD: long parameters") {
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"mylink", "add", "https://github.com/ipmartella", "--header", "My Github"};
    parser.parse(5, argv);

    CHECK_EQ(parser({"h", "header"}).str(), "My Github");
}

TEST_CASE("CMD: parameters and default values")
{
    argh::parser parser;
    parser.add_params({"-h", "--header"});
    const char* argv[] = {"mylink", "add", "https://github.com/ipmartella"};
    parser.parse(3, argv);

    CHECK_EQ(parser({"h", "header"}, "My Github").str(), "My Github");
    CHECK_EQ(parser("h", "My Github").str(), "My Github");
    CHECK_EQ(parser("header", "My Github").str(), "My Github");
}

TEST_CASE("CMD: short flags") {
    argh::parser parser;
    const char* argv[] = {"mylink", "add", "https://github.com/ipmartella", "-v"};
    parser.parse(4, argv);

    CHECK(parser[{"v", "verbose"}]);
}

TEST_CASE("CMD: long flags") {
    argh::parser parser;
    const char* argv[] = {"mylink", "add", "https://github.com/ipmartella", "--verbose"};
    parser.parse(4, argv);

    CHECK(parser[{"v", "verbose"}]);
}

TEST_CASE("CMD: Check positional parameters exist")
{
    argh::parser parser;
    const char* argv[] = {"mylink", "add"};
    parser.parse(2, argv);

    CHECK(parser(0));
    CHECK(parser(1));
    CHECK_FALSE(parser(2));
}
