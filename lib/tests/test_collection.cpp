#include <collection.h>
#include <doctest.h>

using namespace mylink;

SCENARIO("Add Bookmark") {
    Bookmark bm{"https://www.wikipedia.org"};

    GIVEN("A empty collection") {
        BookmarkCollection collection;
        REQUIRE_EQ(collection.size(), 0);

        WHEN("I add a new Bookmark") {
            collection.add(bm);

            THEN("The Bookmark is part of the collection") {
                CHECK_EQ(collection.size(), 1);
                CHECK_EQ(collection["https://www.wikipedia.org"], bm);
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
                CHECK_EQ(collection["https://www.wikipedia.org"], bm);
            }
        }

        WHEN("I add a Bookmark with the same URL") {
            collection.add(Bookmark(bm.get_url(), "Something else"));

            THEN("The collection is not modified") {
                CHECK_EQ(collection.size(), 1);
                CHECK_EQ(collection["https://www.wikipedia.org"], bm);
            }
        }
    }
}
