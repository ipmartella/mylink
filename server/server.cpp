#include "server.h"
#include <httplib.h>
#include <markdown_collection.h>
#include <json.hpp>

using namespace mylink;
using namespace nlohmann;

namespace {

enum HttpErrorCode {
    OK = 200,
    NO_CONTENT = 204,
    BAD_REQUEST = 400
};


} //namespace

Server::Server(Collection &collection) : collection_{collection}, http_server_{}
{
    http_server_.Options(SERVER_ADD_BOOKMARK_URL.c_str(), [&](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Max-Age", "86400");
        res.status = HttpErrorCode::NO_CONTENT;
    });

    http_server_.Post(SERVER_ADD_BOOKMARK_URL.c_str(), [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        try {
            json add_request = json::parse(req.body);
            if(!add_request.contains("url")) {
                throw std::out_of_range("The request MUST contain the 'url' field");
            }

            collection.add(Bookmark{add_request["url"]});
            res.status = HttpErrorCode::OK;
        } catch(json::parse_error) {
            res.status = HttpErrorCode::BAD_REQUEST;
        } catch(std::out_of_range) {
            res.status = HttpErrorCode::BAD_REQUEST;
        }
    });

}

void Server::start()
{
    http_server_.listen("localhost", 1234);

}

void Server::stop()
{
    http_server_.stop();
}

bool Server::is_started() const
{
    return http_server_.is_running();
}
