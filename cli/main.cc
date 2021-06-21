#include <string>
#include "cli.h"

int main(int argc, const char **argv)
{
    return mylink::cli::command_line_shell(argc, argv, std::cout);
}
