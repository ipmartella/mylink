#include "../actions.h"
#include "../server/server.h"

using namespace mylink;
using namespace mylink::cli;

/**
 * @brief mylink "server" subcommand implementation
 *
 * The "server" subcommand runs a webserver (http://localhost:1234 by default), so that you can access your MyLink collection from your browser.
 *
 * Command syntax is:
 * mylink server [-h]
 *
 * -h, --help			Show usage documentation and exits
 *
 * @param argc Number of command line arguments (as specified in standard C)
 * @param argv Array of command line arguments (as specified in standard C)
 * @param backend Storage backend to use for saving/loading the BookmarkCollection
 * @param stdout Output stream to use as standard output
 * @return -1 if the command line is invalid. 0 otherwise
 */
int mylink::cli::action_server(int , const char** , BookmarkCollectionStorageBackend& backend, std::ostream& stdout) {
    Server svr{backend};

    stdout << "MyLink server starting on http://localhost:1234\n";
    svr.start();
    return 0;
}

std::string mylink::cli::action_server_usage() {
    return "Usage: mylink server\n"
           "\n"
           "Starts a webserver so that the MyLink collection is accessible through the browser\n"
           "\n"
            "Options:\n"
            "\t-h,--help			Show usage documentation and exits"
            "\n"
            ;
}
