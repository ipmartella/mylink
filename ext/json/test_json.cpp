#include <doctest.h>
#include "json.hpp"

using namespace nlohmann;

struct example_struct {
    std::string f1;
    std::string f2;
};


void from_json(const json& j, example_struct& p) {
    j.at("f1").get_to(p.f1);
    j.at("f2").get_to(p.f2);
}

void to_json(json& j, const example_struct& p) {
    j = json{{"f1", p.f1}, {"f2", p.f2}};
}


SCENARIO("Deserialization examples") {
    GIVEN("A empty JSON array") {
        std::string json_input{"[]"};

        WHEN("I deserialize it") {
            auto json_obj = json::parse(json_input);
            std::vector<example_struct> values = json_obj.get<std::vector<example_struct>>();

            THEN("I get a empty json") {
                CHECK_EQ(values.size(), 0);
            }
        }
    }

    GIVEN("A JSON array of example structs") {
        std::string json_input{R"([{"f1":"ciao", "f2": "mondo"}, {"f2":"world", "f1":"hello"}])"};

        WHEN("I deserialize it") {
            auto json_obj = json::parse(json_input);
            std::vector<example_struct> values = json_obj.get<std::vector<example_struct>>();

            THEN("I get a empty json") {
                CHECK_EQ(values.size(), 2);
                CHECK_EQ(values[0].f1, "ciao");
                CHECK_EQ(values[0].f2, "mondo");
                CHECK_EQ(values[1].f1, "hello");
                CHECK_EQ(values[1].f2, "world");
            }
        }
    }

    GIVEN("An invalid JSON string") {
        std::string json_input{R"([ciao[ciao)"};
        WHEN("I deserialize it") {
            THEN("A json.exception.parse_error is thrown") {
                CHECK_THROWS_AS(auto _ = json::parse(json_input), json::exception);
            }
        }
    }

    GIVEN("A JSON array of random stuff") {
        std::string json_input{R"(["ciao", 1, 2, {"f1":"ciao"}])"};
        WHEN("I deserialize it as vector of example structs") {
            auto json_obj = json::parse(json_input);
            THEN("A json.exception is thrown") {
                CHECK_THROWS_AS(auto _ = json_obj.get<std::vector<example_struct>>(), json::exception);
            }
        }
    }

}
