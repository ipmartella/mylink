#include "bookmark_json_converter.h"
#include <json.hpp>
#include <vector>

using namespace mylink;
using namespace nlohmann;

namespace {

const std::string json_field_url = "url";
const std::string json_field_title = "title";

struct BookmarkStruct {
    std::string url;
    std::string title = "";
};


void from_json(const json& j, BookmarkStruct& bookmark_struct) {
    j.at(json_field_url).get_to(bookmark_struct.url);
    if(j.contains(json_field_title)){
        j.at(json_field_title).get_to(bookmark_struct.title);
    }
}

void to_json(json& j, const BookmarkStruct& bookmark_struct) {
    j = json {
        {json_field_url, bookmark_struct.url},
        {json_field_title, bookmark_struct.title},
    };
}

Bookmark bookmark_from_struct(const BookmarkStruct& bookmark_struct) {
    return Bookmark(bookmark_struct.url, bookmark_struct.title);
}

BookmarkStruct bookmark_to_struct(const Bookmark& bookmark) {
    return BookmarkStruct{bookmark.get_url(), bookmark.get_title()};
}


} // namespace



/**
 * @brief Converts a JSON object to a Bookmark
 *
 * The JSON object must contain at least the following fields (additional fields will be ignored):
 * - url: (string - mandatory) URL of the Bookmark
 * - title: (string - optional) Title of the Bookmark. By default it will be an empty string
 *
 * If the format of the JSON object is not correct, or if the JSON string cannot be converted to
 * a Bookmark, then this function throws a JsonConversionException.
 *
 * @param json_string JSON string to convert
 * @return Bookmark converted from the JSON object
 * @throws JsonConversionException if the provided string has an invalid format
 */
mylink::Bookmark mylink::server_utils::parse_bookmark_from_json(const std::string &json_string)
{
    try {
        auto bookmark_struct = json::parse(json_string).get<BookmarkStruct>();
        return bookmark_from_struct(bookmark_struct);
    } catch(json::exception& ex) {
        throw JsonConversionException{ex.what()};
    }
}

/**
 * @brief Converts a list of JSON objects to a BookmarkCollection
 *
 * This functions expects a JSON list of Bookmark JSON objects as an input.
 * For details about Bookmark JSON objects see mylink::server_utils::parse_bookmark_from_json.
 *
 * If the format of the JSON object is not correct, or if the JSON string cannot be converted to
 * a BookmarkCollection, then this function throws a JsonConversionException.
 *
 * @param json_string JSON string to convert
 * @return Bookmark converted from the JSON object
 * @throws JsonConversionException if the provided string has an invalid format
 */
BookmarkCollection server_utils::parse_collection_from_json(const std::string &json_string)
{
    try {
        const auto vec_of_bookmark_struct = json::parse(json_string).get<std::vector<BookmarkStruct>>();

        BookmarkCollection collection;

        for(const auto &bookmark_struct: vec_of_bookmark_struct) {
            collection.add(bookmark_from_struct(bookmark_struct));
        }

        return collection;
    } catch(json::exception& ex) {
        throw JsonConversionException{ex.what()};
    }
}

/**
 * @brief Converts a BookmarkCollection to JSON
 *
 * The JSON string returned by this function is a JSON array of Bookmark JSON objects.
 * For details about Bookmark JSON objects see mylink::server_utils::parse_bookmark_from_json.
 *
 * @param collection BookmarkCollection to convert
 * @return JSON string representing the BookmarkCollection
 */

std::string server_utils::covert_collection_to_json(const BookmarkCollection& collection)
{
    std::vector<BookmarkStruct> vec_of_bookmark_struct;
    for(const auto& bookmark : collection) {
        vec_of_bookmark_struct.push_back(bookmark_to_struct(bookmark));
    }

    json j = vec_of_bookmark_struct;
    return j.dump();
}
