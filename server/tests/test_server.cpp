#include <httplib.h>
#include <thread>
#include <doctest.h>
#include "../server.h"
#include "../../tests/mock_storage_backend.h"

using namespace mylink;
using namespace mylink::test;

namespace {

enum HttpErrorCode {
    OK = 200,
    BAD_REQUEST = 400,
};


std::thread start_server_in_another_thread(Server &server) {
    std::thread server_thread([&]{ server.start(); });
    while(!server.is_started()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return server_thread;
}

void stop_server_and_thread(Server& server, std::thread& thread) {
    server.stop();
    thread.join();
}


} // namespace


SCENARIO("Add bookmark") {
    GIVEN("A MylinkServer") {
        MockStorageBackend backend;
        Server server(backend);

        std::thread server_thread = start_server_in_another_thread(server);
        httplib::Client client{server_default_host, server_default_port};

        WHEN("I send an empty POST request to add bookmark") {
            auto result = client.Post(server_url_bookmarks.c_str(), "", "text/json");

            THEN("A Bad Request HTTP error code is returned") {
                REQUIRE_EQ(result.error(), httplib::Error::Success);
                CHECK_EQ(result->status, HttpErrorCode::BAD_REQUEST);
                CHECK_FALSE(backend.get_saved_collection());
            }
        }

        WHEN("I send an non JSON request to add bookmark") {
            auto result = client.Post(server_url_bookmarks.c_str(), "ciao", "text/json");

            THEN("A Bad Request HTTP error code is returned") {
                REQUIRE_EQ(result.error(), httplib::Error::Success);
                CHECK_EQ(result->status, HttpErrorCode::BAD_REQUEST);
                CHECK_FALSE(backend.get_saved_collection());
            }
        }

        WHEN("I send a JSON request without the url field") {
            auto result = client.Post(server_url_bookmarks.c_str(),
                                      R"({"answer":42})",
                                      "text/json");
            THEN("A Bad Request HTTP error code is returned") {
                REQUIRE_EQ(result.error(), httplib::Error::Success);
                CHECK_EQ(result->status, HttpErrorCode::BAD_REQUEST);
                CHECK_FALSE(backend.get_saved_collection());
            }
        }


        WHEN("I send a POST request for adding a bookmark with just the URL") {
            auto result = client.Post(server_url_bookmarks.c_str(),
                                      R"({"url":"https://www.wikipedia.org"})",
                                      "text/json");

            THEN("The bookmark is added to the collection without title") {
                REQUIRE_EQ(result.error(), httplib::Error::Success);
                CHECK_EQ(result->status, HttpErrorCode::OK);
                auto collection = backend.get_saved_collection();
                REQUIRE(collection);
                CHECK_EQ(collection->size(), 1);
                CHECK_EQ((*collection)["https://www.wikipedia.org"].get_title(), "");
            }
        }

        WHEN("I send a POST request for adding a bookmark with URL and title") {
            auto result = client.Post(server_url_bookmarks.c_str(),
                                      R"({"url":"https://www.wikipedia.org", "title": "Wikipedia"})",
                                      "text/json");

            THEN("The bookmark is added to the collection with the specified title") {
                REQUIRE_EQ(result.error(), httplib::Error::Success);
                CHECK_EQ(result->status, HttpErrorCode::OK);
                auto collection = backend.get_saved_collection();
                REQUIRE(collection);
                CHECK_EQ(collection->size(), 1);
                CHECK_EQ((*collection)["https://www.wikipedia.org"].get_title(), "Wikipedia");
            }
        }

        stop_server_and_thread(server, server_thread);
    }
}
