#ifndef SERVER_H
#define SERVER_H
#include <httplib.h>
#include <collection_storage.h>


namespace mylink {
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
};

const std::string server_default_host{"localhost"};
constexpr int server_default_port = 1234;
const std::string server_url_bookmarks{"/bookmarks"};

} //namespace mylink

#endif // SERVER_H
