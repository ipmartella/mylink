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
    CHECK_EQ(bookmark.get_url(), actual_url);
}

} //namespace

SCENARIO("Create a bookmark from a URL") {
    GIVEN("A 'empty' string") {
        std::vector<std::string> empty_urls = {"", " ", "\t", "\n", "\r\n", " \t    "};
        for (const auto& url : empty_urls) {
            bookmark_cannot_be_created_with_url(url);
        }
    }

    GIVEN("A non-empty string not containing at least 1 ASCII letter") {
        std::vector<std::string> invalid_urls = {
            "_INVALID_",
            "**********************",
            "- --------------------- -"
        };

        for (const auto& url : invalid_urls) {
            bookmark_cannot_be_created_with_url(url);
        }
    }

    GIVEN("A non-empty string not starting with a ASCII letter or a number") {
        std::vector<std::string> invalid_urls = {
            "_INVALID_",
            "*********aa************",
            "-12-------------------- -"
        };

        for (const auto& url : invalid_urls) {
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

    GIVEN("A localhost URL") {
        bookmark_is_created_with_url("localhost", "http://localhost");
        bookmark_is_created_with_url("http://localhost", "http://localhost");
        bookmark_is_created_with_url("http://localhost:3128", "http://localhost:3128");
        bookmark_is_created_with_url("http://localhost:8080", "http://localhost:8080");
    }

    GIVEN("A IP address URL") {
        bookmark_is_created_with_url("127.0.0.1", "http://127.0.0.1");
        bookmark_is_created_with_url("127.0.0.1:8080", "http://127.0.0.1:8080");
        bookmark_is_created_with_url("http://127.0.0.1:8080", "http://127.0.0.1:8080");
        bookmark_is_created_with_url("http://127.0.0.1:8080/phpmyadmin", "http://127.0.0.1:8080/phpmyadmin");
    }
}

SCENARIO("URL title") {
    GIVEN("A bookmark with a URL and no title specified") {
        Bookmark bookmark{"https://www.wikipedia.org"};
        WHEN("You read the title") {
            auto title = bookmark.get_title();

            THEN("The title will be empty") {
                CHECK_EQ(title, "");
            }
        }
    }
    GIVEN("A bookmark with a URL and a title") {
        Bookmark bookmark{"https://www.wikipedia.org", "Wikipedia"};
        WHEN("You read the title") {
            auto title = bookmark.get_title();

            THEN("The title will be equal to the one you set") {
                CHECK_EQ(title, "Wikipedia");
            }
        }
    }

}

SCENARIO("Check that two Bookmarks have the same URL") {
    GIVEN("Two bookmarks with different URLs") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://en.cppreference.org"};

        WHEN("Their URLs are compared") {
            THEN("They should be marked as not-equal") {
                CHECK_FALSE(bookmark1.is_url_same_as(bookmark2));
            }
        }
    }
    GIVEN("Two bookmarks with the same URL (case sensitive)") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://www.wikipedia.org"};

        WHEN("Their URLs are compared") {
            THEN("They should be marked as equal") {
                CHECK(bookmark1.is_url_same_as(bookmark2));
                CHECK(bookmark1.is_url_same_as(bookmark1));
            }
        }
    }
    GIVEN("Two bookmarks with the same URL (case insensitive)") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://wWw.WIKIpedia.org"};
        WHEN("Their URLs are compared") {
            THEN("They should be marked as equal") {
                CHECK(bookmark1.is_url_same_as(bookmark2));
            }
        }
    }
    GIVEN("Two bookmarks with the same URL, but different titles") {
        Bookmark bookmark1{"https://www.wikipedia.org", "Title"};
        Bookmark bookmark2{"https://www.wikipedia.org", "Wikipedia"};
        WHEN("Their URLs are compared") {
            THEN("They should be marked as equal") {
                CHECK(bookmark1.is_url_same_as(bookmark2));
            }
        }
    }
}

SCENARIO("Bookmark equality") {
    GIVEN("Two Bookmarks with the same URL") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://www.wikipedia.org"};

        WHEN("They are compared") {
            THEN("They are equal") {
                CHECK_EQ(bookmark1, bookmark2);
            }
        }
    }

    GIVEN("Two Bookmarks with the same URL (case-insensitive)") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://www.WIKipeDIa.org"};

        WHEN("They are compared") {
            THEN("They are equal") {
                CHECK_EQ(bookmark1, bookmark2);
            }
        }
    }

    GIVEN("Two Bookmarks with different URL") {
        Bookmark bookmark1{"https://www.wikipedia.org"};
        Bookmark bookmark2{"https://en.cppreference.org"};

        WHEN("They are compared") {
            THEN("They are equal") {
                CHECK_NE(bookmark1, bookmark2);
            }
        }
    }

}
