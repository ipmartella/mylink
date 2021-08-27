#include "../actions.h"
#include "../actions_priv.h"
#include "../server/server.h"

using namespace mylink;
using namespace mylink::cli;

/**
 * @brief mylink "server" subcommand implementation
 *
 * The "server" subcommand runs a webserver (http://localhost:1234 by default), so that you can access your MyLink collection from your browser.
 *
 * Command syntax is:
 * mylink server [-h] [-p <path>]
 *
 * -h, --help			Show usage documentation and exits
 * -p, --path <path>	File path where to load/store links. If not path is specified, 'links.md' will be used
 *
 * @param argc Number of command line arguments (as specified in standard C)
 * @param argv Array of command line arguments (as specified in standard C)
 * @param backend Storage backend to use for saving/loading the BookmarkCollection
 * @param out_stream Output stream to use as standard output
 * @return -1 if the command line is invalid. 0 otherwise
 */
int mylink::cli::action_server(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& out_stream) {
    //Parse command line
    const ParsedCommandLine cmd_line(argc, argv, {std_parameter_path});
    backend.set_path(cmd_line.getParameter(std_parameter_path, default_links_path));

    if(cmd_line.hasFlag(std_flag_help)) {
        out_stream << action_server_usage();
        return -1;
    }

    try {
        Server svr{backend};
        out_stream << "MyLink server starting on http://localhost:1234\n";
        svr.start();
        return 0;
    } catch(mylink::ServerSetupError) {
        out_stream << "ERROR: Could not load web resources. Is the 'www' folder available in the same path as the executable?\n";
        return -2;
    }
}

std::string mylink::cli::action_server_usage() {
    return "Usage: mylink server [-h] [-p <path>]\n"
           "\n"
           "Starts a webserver so that the MyLink collection is accessible through the browser\n"
           "\n"
            "Options:\n"
            "\t-h,--help			Show usage documentation and exits\n"
            "\t-p,--path			File path where to store links. If not path is specified, 'links.md' will be used\n"
            "\n"
            ;
}
