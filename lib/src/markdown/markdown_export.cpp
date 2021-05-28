#include "markdown_storage.h"
#include <sstream>

using namespace mylink;

std::string mylink::convert_to_markdown_line(const Bookmark& bookmark) {
    std::stringstream markdown_line_builder;
    markdown_line_builder << "- " << bookmark.url();
    return markdown_line_builder.str();
}

void mylink::write_bookmarks_to_stream(const std::vector<Bookmark>& bookmarks, std::ostream& stream) {
    for(const auto& bookmark : bookmarks) {
        stream << convert_to_markdown_line(bookmark) << '\n';
    }
}


#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>
#include <sstream>

using namespace mylink;

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

SCENARIO("Convert vector of Bookmarks to Markdown stream") {
    GIVEN("A empty vector of bookmarks") {
        std::vector<Bookmark> bookmarks;
        WHEN("The bookmarks are written to a stream") {
            std::stringstream stream;
            write_bookmarks_to_stream(bookmarks, stream);

            THEN("The stream is empty") {
                CHECK(stream.str().empty());
            }
        }
    }

    GIVEN("A vector of bookmarks") {
        std::vector<Bookmark> bookmarks{
            Bookmark{"http://www.wikipedia.org"},
            Bookmark{"http://www.url.org"},
            Bookmark{"http://www.mytesturl.org/test/index"},
        };
        WHEN("The bookmarks are written to a stream") {
            std::stringstream stream;
            write_bookmarks_to_stream(bookmarks, stream);

            THEN("The stream contains the URL in Markdown format") {
                CHECK_EQ(stream.str(),
                         "- http://www.wikipedia.org\n"
                         "- http://www.url.org\n"
                         "- http://www.mytesturl.org/test/index\n");

            }
        }
    }
}

#endif
