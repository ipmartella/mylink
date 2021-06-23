#include "../actions.h"

/**
 * @brief mylink "add" subcommand implementation
 *
 * The "add" subcommand adds a Bookmark to the collection file, by parsing URL and metadata from the command line.
 * Command syntax is:
 * mylink add <url> [-h] [-t <title>]
 *
 * -h, --help			Show usage documentation and exits
 * -t, --title <title>	Adds <title> as title for the new Bookmark
 *
 * If a URL already exists in the collection, this command does nothing.
 *
 * @param argc Number of command line arguments (as specified in standard C)
 * @param argv Array of command line arguments (as specified in standard C)
 * @param backend Storage backend to use for saving/loading the BookmarkCollection
 * @param stdout Output stream to use as standard output
 * @return -1 if the command line is invalid. 0 otherwise
 */
int mylink::cli::action_add(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& stdout) {
    constexpr int positional_idx_url = 2;

    try {
        //Parse command line
        ParsedCommandLine cmd_line(argc, argv);
        std::string url = cmd_line.getPositional(positional_idx_url);

        auto collection = backend.load();
        collection.add(Bookmark{url});
        backend.save(collection);

        return 0;
    } catch(std::out_of_range&) {
        stdout << action_add_usage();
    } catch(std::invalid_argument&) {
        stdout << action_add_usage();
    }
    return -1;
}


std::string mylink::cli::action_add_usage() {
    return "Usage: mylink add <url> [--title <title>]\n"
           "\n"
           "Adds <url> to the default bookmark collection file\n"
           "\n"
            "Options:\n"
            "\t-h,--help			Show usage documentation and exits"
            "\t-t,--title <title>	Sets bookmark title to <title>"
            "\n"
            ;
}
