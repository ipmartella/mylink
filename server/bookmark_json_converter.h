#ifndef BOOKMARKJSONCONVERTER_H
#define BOOKMARKJSONCONVERTER_H

#include <collection.h>
#include <stdexcept>

namespace mylink {
namespace server_utils {

using JsonConversionException = std::invalid_argument;

Bookmark parse_bookmark_from_json(const std::string& json_string);

BookmarkCollection parse_collection_from_json(const std::string& json_string);
std::string covert_collection_to_json(const BookmarkCollection& collection);


} // namespace server_utils
} //namespace mylink

#endif // BOOKMARKJSONCONVERTER_H
