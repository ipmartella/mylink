#include <markdown_collection.h>
#include "server.h"

using namespace mylink;

int main(void)
{
    MarkdownCollection collection("links.md");
    Server svr{collection};

    svr.start();
    return 0;
}
