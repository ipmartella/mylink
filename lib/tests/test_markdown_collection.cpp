#include <doctest.h>
#include <markdown_collection.h>
#include "../src/markdown/markdown_storage.h"

using namespace mylink;

SCENARIO("Adding bookmarks to files") {

    GIVEN("A empty file") {
        const std::string test_file = "/tmp/mylink_test1";
        std::remove(test_file.c_str());

        MarkdownCollection collection{test_file};

        WHEN("I add a bookmark in Markdown format") {
            Bookmark new_bookmark{"http://www.wikipedia.org"};
            collection.add(new_bookmark);

            THEN("The stream contains the bookmark") {
                auto saved_bookmarks = read_bookmarks_from_file(test_file);
                CHECK_EQ(saved_bookmarks.size(), 1);
                CHECK_EQ(saved_bookmarks[0].get_url(), "http://www.wikipedia.org");
            }
        }
    }

    GIVEN("A populated stream") {
        const std::string test_file = "/tmp/mylink_test2";
        std::remove(test_file.c_str());
        std::vector<Bookmark> initial_bookmarks{
            Bookmark("http://www.wikipedia.org"),
            Bookmark("http://www.myurl.org"),
        };
        write_bookmarks_to_file(initial_bookmarks, test_file);

        MarkdownCollection collection{test_file};

        WHEN("I add a new bookmark in Markdown format") {
            Bookmark new_bookmark{"http://www.test.org"};
            collection.add(new_bookmark);

            THEN("The stream contains the bookmark + all the previous ones") {
                auto saved_bookmarks = read_bookmarks_from_file(test_file);
                CHECK_EQ(saved_bookmarks.size(), 3);
                CHECK(saved_bookmarks[0].is_url_same_as(initial_bookmarks[0]));
                CHECK(saved_bookmarks[1].is_url_same_as(initial_bookmarks[1]));
                CHECK(saved_bookmarks[2].is_url_same_as(new_bookmark));
            }
        }

        WHEN("I add an existing bookmark in Markdown format") {
            collection.add(initial_bookmarks[0]);
            collection.add(initial_bookmarks[1]);

            THEN("The stream contains only the initial bookmarks") {
                auto saved_bookmarks = read_bookmarks_from_file(test_file);
                CHECK_EQ(saved_bookmarks.size(), 2);
                CHECK(saved_bookmarks[0].is_url_same_as(initial_bookmarks[0]));
                CHECK(saved_bookmarks[1].is_url_same_as(initial_bookmarks[1]));
            }
        }
    }

}

SCENARIO("Reading bookmarks from a file") {
    GIVEN("A empty file") {
        const std::string test_file = "/tmp/mylink_test3";
        std::remove(test_file.c_str());

        MarkdownCollection collection{test_file};

        WHEN("I read the size of the collection") {
            THEN("I get zero") {
                CHECK_EQ(collection.size(), 0);
            }
        }
    }
}
