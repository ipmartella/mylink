#include <doctest.h>
#include <markdown_storage.h>
#include <string>
#include <vector>

using namespace mylink;

void line_is_parsed_but_no_result(const std::string& line)
{
    WHEN("The line is parsed")
    {
        CAPTURE(line);
        auto bookmark = parse_markdown_line(line);
        THEN("No bookmark will be created") { CHECK_EQ(bookmark.url, INVALID_BOOKMARK.url); }
    }
}

SCENARIO("Covert Markdown to bookmark")
{
    GIVEN("A empty line")
    {
        std::vector<std::string> empty_lines = {"", " ", "\t", "\n", "\r\n", " \t     "};
        for (const auto& line : empty_lines) {
            line_is_parsed_but_no_result(line);
        }
    }

    GIVEN("- https://www.wikipedia.org")
    {
        WHEN("The Markdown line is parsed")
        {
            THEN("A bookmark will be created") {}
        }
    }
}
