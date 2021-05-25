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

void line_is_parsed_with_url(const std::string& line, const std::string& expected_url) {
    WHEN("The Markdown line is parsed")
    {
        INFO("Line:<", line, ">");
        auto bookmark = parse_markdown_line(line);

        THEN("A bookmark will be created") {
            CHECK_EQ(bookmark.url, expected_url);
        }
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

    GIVEN("Variations of <- https://www.wikipedia.org>")
    {
        std::vector<std::string> empty_lines = {
            "- https://www.wikipedia.org",
            " - https://www.wikipedia.org  ",
            "  \t - \thttps://www.wikipedia.org  ",
            "\t-https://www.wikipedia.org",
            "-https://www.wikipedia.org\r\n",
            "-https://www.wikipedia.org \n",
        };

        for (const auto& line : empty_lines) {
            line_is_parsed_with_url(line, "https://www.wikipedia.org");
        }
    }
    GIVEN("Variations of <* https://www.wikipedia.org>")
    {
        std::vector<std::string> empty_lines = {
            "* https://www.wikipedia.org",
            " * https://www.wikipedia.org  ",
            "  \t * \thttps://www.wikipedia.org  ",
            "\t*https://www.wikipedia.org",
            "*https://www.wikipedia.org\r\n",
            "*https://www.wikipedia.org \n",
        };

        for (const auto& line : empty_lines) {
            line_is_parsed_with_url(line, "https://www.wikipedia.org");
        }
    }
}
