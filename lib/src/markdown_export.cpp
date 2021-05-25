#include <markdown_storage.h>
#include <sstream>

using namespace mylink;

std::string mylink::convert_to_markdown_line(const Bookmark& bookmark) {
    std::stringstream markdown_line_builder;
    markdown_line_builder << "- " << bookmark.url;
    return markdown_line_builder.str();
}
