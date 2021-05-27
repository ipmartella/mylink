#include "markdown_storage.h"
#include <sstream>

using namespace mylink;

std::string mylink::convert_to_markdown_line(const Bookmark& bookmark) {
    std::stringstream markdown_line_builder;
    markdown_line_builder << "- " << bookmark.url();
    return markdown_line_builder.str();
}

#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>

using namespace mylink;

SCENARIO("Convert Bookmark to Markdown line") {
    MESSAGE("Hi there!");

    GIVEN("A bookmark with a plain URL") {
        Bookmark plain_url_bookmark("http://www.wikipedia.org");

        WHEN("The bookmark is exported") {
            std::string markdown_line = convert_to_markdown_line(plain_url_bookmark);
            THEN("The line is like: - http://www.url.org") {
                CHECK_EQ(markdown_line, "- http://www.wikipedia.org");
            }
        }
    }
}

#endif
