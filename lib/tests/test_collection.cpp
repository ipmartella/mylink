#include <collection.h>
#include <doctest.h>
#include <stdexcept>

using namespace mylink;

SCENARIO("Add Bookmark") {
    Bookmark bm{"https://www.wikipedia.org", "Wikipedia"};

    GIVEN("A empty collection") {
        BookmarkCollection collection;
        REQUIRE_EQ(collection.size(), 0);

        WHEN("I add a new Bookmark") {
            collection.add(bm);

            THEN("The Bookmark is part of the collection") {
                CHECK_EQ(collection.size(), 1);
                CHECK_EQ(collection[bm.get_url()], bm);
            }
        }
    }

    GIVEN("A collection with one Bookmark") {
        BookmarkCollection collection;
        collection.add(bm);

        WHEN("I add an existing Bookmark") {
            collection.add(bm);

            THEN("The collection is not modified") {
                CHECK_EQ(collection.size(), 1);
                CHECK_EQ(collection[bm.get_url()], bm);
            }
        }

        WHEN("I add a Bookmark with the same URL") {
            collection.add(Bookmark(bm.get_url(), "Something else"));

            THEN("The collection is not modified") {
                CHECK_EQ(collection.size(), 1);
                CHECK_EQ(collection[bm.get_url()], bm);
            }
        }

        WHEN("I add a Bookmark with the same URL (different-case)") {
            collection.add(Bookmark("https://wwW.WIkipeDIA.org"));

            THEN("The collection is not modified") {
                CHECK_EQ(collection.size(), 1);
                CHECK_EQ(collection[bm.get_url()], bm);
            }
        }
    }
}

SCENARIO("Get Bookmark by URL") {
    Bookmark bm{"https://www.wikipedia.org", "Wikipedia"};

    GIVEN("A collection with one Bookmark") {
        BookmarkCollection collection;
        collection.add(bm);

        WHEN("I get the existing Bookmark by URL") {
            THEN("I get the Bookmark") {
                CHECK_EQ(collection[bm.get_url()], bm);
            }
        }

        WHEN("I get the existing Bookmark by URL (different case)") {
            THEN("I get the Bookmark") {
                CHECK_EQ(collection["https://wWW.WikipeDIA.ORg"], bm);
            }
        }

        WHEN("I get the Bookmark for a non existing URL") {
            THEN("It throws std::out_of_range") {
                CHECK_THROWS_AS(collection["http://nope.nope"], std::out_of_range);
            }
        }
    }

}

SCENARIO("Check that Bookmark is inside collection") {
    Bookmark bm{"https://www.wikipedia.org", "Wikipedia"};

    GIVEN("A collection with one Bookmark") {
        BookmarkCollection collection;
        collection.add(bm);

        WHEN("I check if the existing URL is contained in the collection") {
            THEN("The URL is found") {
                CHECK(collection.contains(bm.get_url()));
            }
        }

        WHEN("I check if the existing URL is contained in the collection (different case)") {
            THEN("The URL is found") {
                CHECK(collection.contains("https://wWW.WikipeDIA.ORg"));
            }
        }

        WHEN("I check if a different URL is contained in the collection") {
            THEN("Then the URL cannot be found") {
                CHECK_FALSE(collection.contains("http://nope.nope"));
            }
        }
    }

}
