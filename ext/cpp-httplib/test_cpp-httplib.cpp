#include <doctest.h>
#include "httplib_include_helper.h"

SCENARIO("Tests with file mounting") {
    GIVEN("A cpp-httplib server") {
        httplib::Server server;
        WHEN("I try to mount a folder that exists") {
            THEN("I get true as a return value") {
                CHECK(server.set_mount_point("/", "/opt"));
            }
        }

        WHEN("I try to mount a folder that does not exist") {
            THEN("I get false as a return value") {
                CHECK_FALSE(server.set_mount_point("/", "/non_existing_path"));
            }
        }
    }
}
