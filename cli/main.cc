#include <string>
#include "cli.h"
#include <markdown_storage.h>

int main(int argc, const char **argv)
{
    mylink::MarkdownStorageBackend backend("links.md");
    return mylink::cli::command_line_shell(argc, argv, backend);
}
