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
    }
}

SCENARIO("Get Bookmark by URL") {
    Bookmark bm{"https://www.wikipedia.org", "Wikipedia"};

    GIVEN("A collection with one Bookmark") {
        BookmarkCollection collection;
        collection.add(bm);

        WHEN("I get the existing Bookmark by URL") {
            THEN("Then I get the Bookmark") {
                CHECK_EQ(collection[bm.get_url()], bm);
            }
        }

        WHEN("I get the Bookmark for a non existing URL") {
            THEN("Then it throws std::out_of_range") {
                CHECK_THROWS_AS(collection["http://nope.nope"], std::out_of_range);
            }
        }
    }

}
