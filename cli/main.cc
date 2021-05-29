#include <commandlineparser.h>
#include <markdown_collection.h>

using namespace mylink;

int main(int argc, const char **argv)
{
    MarkdownCollection collection("links.md");
    CommandLineParser parser(collection, std::cout);
    parser.parse(argc, argv);

    return 0;
}
