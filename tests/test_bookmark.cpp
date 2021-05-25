#include <doctest.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <bookmark.h>

using namespace mylink;

namespace {

void bookmark_cannot_be_created_with_url(const std::string& url) {
    INFO("URL is \"", url, "\"");
    CHECK_THROWS_AS(Bookmark{url}, std::invalid_argument);
}

void bookmark_is_created_with_url(const std::string& url, const std::string& actual_url) {
    INFO("URL is \"", url, "\"");
    Bookmark bookmark{url};
    CHECK_EQ(bookmark.url(), actual_url);
}

} //namespace

SCENARIO("Create a bookmark from a URL") {
    GIVEN("A 'empty' URL") {
        std::vector<std::string> empty_urls = {"", " ", "\t", "\n", "\r\n", " \t    "};
        for (const auto& url : empty_urls) {
            bookmark_cannot_be_created_with_url(url);
        }
    }

    GIVEN("Variations of a plain URL like http://www.wikipedia.org") {
        const std::string actual_url{"https://www.wikipedia.org"};
        std::vector<std::string> plain_url_variations = {
            "https://www.wikipedia.org",
            "   https://www.wikipedia.org",
            "https://www.wikipedia.org   ",
            "   https://www.wikipedia.org   ",
            " \t https://www.wikipedia.org   \r\n",
            " \t https://www.wikipedia.org   \n",
        };

        for (const auto& url : plain_url_variations) {
            bookmark_is_created_with_url(url, actual_url);
        }
    }
}

SCENARIO("Check that two Bookmarks are the same") {
    GIVEN("Two bookmarks with different URLs") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://en.cppreference.org"};

        WHEN("They are compared") {
            THEN("They should be marked as not-equal") {
                CHECK_FALSE(bookmark1.same_url_as(bookmark2));
            }
        }
    }
    GIVEN("Two bookmarks with the same URL (case sensitive)") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://www.wikipedia.org"};

        WHEN("They are compared") {
            THEN("They should be marked as equal") {
                CHECK(bookmark1.same_url_as(bookmark2));
                CHECK(bookmark1.same_url_as(bookmark1));
            }
        }
    }
    GIVEN("Two bookmarks with the same URL (case insensitive)") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://wWw.WIKIpedia.org"};
        WHEN("They are compared") {
            THEN("They should be marked as equal") {
                CHECK(bookmark1.same_url_as(bookmark2));
            }
        }
    }
}
