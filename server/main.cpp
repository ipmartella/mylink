#include "server.h"
#include <markdown_storage.h>

using namespace mylink;

int main(void)
{
    MarkdownStorageBackend backend("links.md");
    Server svr{backend};

    svr.start();
    return 0;
}
