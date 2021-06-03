#ifndef SERVER_H
#define SERVER_H
#include <collection.h>
#include <httplib.h>


namespace mylink {
class Server
{
public:
    Server(Collection& collection);
    void start();
    void stop();
    bool is_started() const;

private:
    Collection& collection_;
    httplib::Server http_server_;
    void handle_add_bookmark_request_(const httplib::Request& request, httplib::Response& response);

};

const std::string SERVER_ADD_BOOKMARK_URL{"/bookmarks"};
const std::string DEFAULT_HOST{"localhost"};
constexpr int DEFAULT_PORT = 1234;

} //namespace mylink

#endif // SERVER_H
