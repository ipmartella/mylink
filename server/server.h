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
};

const std::string SERVER_ADD_BOOKMARK_URL{"/add_bookmark"};

} //namespace mylink

#endif // SERVER_H
