#include <doctest.h>
#include <markdown_storage.h>
#include <string>
#include <vector>

using namespace mylink;

namespace {

} //namespace

SCENARIO("Convert Bookmark to Markdown line") {

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
