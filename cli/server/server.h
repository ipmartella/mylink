#ifndef SERVER_H
#define SERVER_H
#include <httplib.h>
#include <stdexcept>
#include <collection_storage.h>


namespace mylink {
/**
 * @brief mylink::Server allows you to interact with a BookmarkCollection via HTTP requests.
 *
 * The server exposes a HTTP endpoint at <server_default_host>:<server_default_port>/<server_url_bookmarks>.
 * The endpoint currently support the following HTTP methods:
 * - GET :: Gets all Bookmarks from the BookmarkCollection. See Server::handle_get_bookmark_request_ for details.
 * - POST :: Adds a new Bookmark to the BookmarkCollection. See Server::handle_add_bookmark_request_ for details.
 * - OPTIONS :: Allows Cross Origin Resource Sharing (CORS) from any domain. This is needed if you want to interact with the server using bookmarklets
 *
 * The server can be stopped by issuing a HTTP GET request at <server_default_host>:<server_default_port>/<server_url_stop>.
 *
 * The BookmarkCollection manipulated by the server is loaded/saved using the given BookmarkCollectionStorageBackend.
 */
class Server
{
public:
    Server(BookmarkCollectionStorageBackend& backend);
    void start();
    void stop();
    bool is_started() const;

private:
    BookmarkCollectionStorageBackend& backend_;
    httplib::Server http_server_;
    void handle_add_bookmark_request_(const httplib::Request& request, httplib::Response& response);
    void handle_get_bookmark_request_(const httplib::Request& request, httplib::Response& response);
};

const std::string server_default_host{"localhost"};
constexpr int server_default_port = 1234;
const std::string server_url_bookmarks{"/bookmarks"};
const std::string server_url_stop{"/stop"};
const std::string server_web_resources_path{"./www"};

class ServerSetupError : public std::logic_error {
public:
    ServerSetupError() : std::logic_error("Failed to setup server") {}
};

} //namespace mylink

#endif // SERVER_H
