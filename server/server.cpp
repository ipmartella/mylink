#include "server.h"
#include <httplib.h>
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
    CREATED = 201,
    NO_CONTENT = 204,
    BAD_REQUEST = 400,
    CONFLICT = 409,
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

/**
 * @brief Builds a new mylink::Server, which loads/saves its Bookmarks using the provided <backend>
 * @param backend BookmarkCollectionStorageBacked to use for loading/saving Bookmarks
 */
Server::Server(BookmarkCollectionStorageBackend &backend) : backend_{backend}, http_server_{}
{
    http_server_.Options(server_url_bookmarks.c_str(), allow_cors_from_any_origin);

    http_server_.Post(server_url_bookmarks.c_str(), [&](const httplib::Request& request, httplib::Response& response) {
        handle_add_bookmark_request_(request, response);
    });

}

/**
 * @brief Starts listening for HTTP requests.This method blocks until the server is stopped (by calling Server::stop).
 */
void Server::start()
{
    http_server_.listen(server_default_host.c_str(), server_default_port);
}

/**
 * @brief Stops listening for HTTP requests.
 */
void Server::stop()
{
    http_server_.stop();
}

/**
 * @brief Returns true if the server is currently listening for HTTP requests.
 * @return true if the server is currently listening for HTTP requests. False otherwise
 */
bool Server::is_started() const
{
    return http_server_.is_running();
}

/**
 * @brief Handles POST HTTP requests to add a Bookmark to this server BookmarkCollection.
 *
 * The body of the request must be a JSON object with at least the following fields (additional fields will be ignored):
 * - url: (string - mandatory) URL of the Bookmark
 * - title: (string - optional) Title of the Bookmark. By default it will be an empty string
 *
 * If the request has a valid format, and the new Bookmark has been added to the BookmarkCollection, the HTTP result code will be set to HTTP_CREATED.
 * If the request has a valid format, but the Bookmark already exists in the BookmarkCollection, the HTTP result code will be set to HTTP_CONFLICT.
 * If the request does not have a valid format, or the Bookmark is invalid,  the HTTP result code will be set to HTTP_BAD_REQUEST.
 *
 * @param request
 * @param response
 */
void Server::handle_add_bookmark_request_(const httplib::Request& request, httplib::Response& response){
    setup_response_to_allow_cors(response);
    try {
        Bookmark bookmark_to_add = build_bookmark_from_add_request(request.body);

        auto collection = backend_.load();

        const auto size_before_add = collection.size();
        collection.add(bookmark_to_add);
        const auto size_after_add = collection.size();

        if(size_after_add > size_before_add) {
            backend_.save(collection);
            response.status = HttpErrorCode::CREATED;
        } else {
            //Bookmark already exists
            response.status = HttpErrorCode::CONFLICT;
        }
    } catch(HttpParseException&) {
        //HTTP Request format is not valid
        response.status = HttpErrorCode::BAD_REQUEST;
    } catch(std::invalid_argument&) {
        //Bookmark format is not valid
        response.status = HttpErrorCode::BAD_REQUEST;
    }
}
