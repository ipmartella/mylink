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
