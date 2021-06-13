#include "server.h"
#include <httplib.h>
#include <markdown_collection.h>
#include <json.hpp>
#include <functional>

using namespace mylink;
using namespace nlohmann;

namespace {

const std::string json_field_url = "url";
const std::string json_field_title = "title";

class HttpParseException : public std::invalid_argument {
public:
    HttpParseException(std::string msg) : std::invalid_argument(msg) {}
};

enum HttpErrorCode {
    OK = 200,
    NO_CONTENT = 204,
    BAD_REQUEST = 400
};

void setup_response_to_allow_cors(httplib::Response& response) {
    response.set_header("Access-Control-Allow-Origin", "*");
}

void allow_cors_from_any_origin(const httplib::Request&, httplib::Response& response){
    response.set_header("Access-Control-Allow-Origin", "*");
    response.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
    response.set_header("Access-Control-Allow-Headers", "Content-Type");
    response.set_header("Access-Control-Max-Age", "86400");
    response.status = HttpErrorCode::NO_CONTENT;
}


Bookmark build_bookmark_from_add_request(const std::string& add_request_body) {
    json add_request;
    try {
        add_request = json::parse(add_request_body);
    } catch(json::parse_error) {
        throw HttpParseException("Invalid JSON format");
    }

    if(!add_request.contains(json_field_url)) {
        throw HttpParseException("The request MUST contain the 'url' field");
    }


    return Bookmark{add_request[json_field_url], add_request.value(json_field_title, "")};
}


} //namespace

Server::Server(Collection &collection) : collection_{collection}, http_server_{}
{
    http_server_.Options(SERVER_ADD_BOOKMARK_URL.c_str(), allow_cors_from_any_origin);

    http_server_.Post(SERVER_ADD_BOOKMARK_URL.c_str(), [&](const httplib::Request& request, httplib::Response& response) {
        handle_add_bookmark_request_(request, response);
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

void Server::handle_add_bookmark_request_(const httplib::Request& request, httplib::Response& response){
    setup_response_to_allow_cors(response);
    try {
        Bookmark bookmark_to_add = build_bookmark_from_add_request(request.body);
        collection_.add(bookmark_to_add);
        response.status = HttpErrorCode::OK;
    } catch(HttpParseException) {
        response.status = HttpErrorCode::BAD_REQUEST;
    }
}
