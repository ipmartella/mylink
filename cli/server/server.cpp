#include "server.h"
#include <httplib.h>
#include <functional>
#include "bookmark_json_converter.h"

using namespace mylink;

namespace {

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
    http_server_.Get(server_url_bookmarks.c_str(), [&](const httplib::Request& request, httplib::Response& response) {
        handle_get_bookmark_request_(request, response);
    });


    //Load Web resources to show MyLinks web page
    http_server_.set_mount_point("/", server_web_resources_path.c_str());
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
 * The body of the request must comply with the format specified in the documentation of mylink::server_utils::parse_bookmark_from_json.
 *
 * If the request has a valid format, and the new Bookmark has been added to the BookmarkCollection, the HTTP result code will be set to HTTP_CREATED.
 * If the request has a valid format, but the Bookmark already exists in the BookmarkCollection, the HTTP result code will be set to HTTP_CONFLICT.
 * If the request does not have a valid format, or the Bookmark is invalid,  the HTTP result code will be set to HTTP_BAD_REQUEST.
 *
 * @param request HTTP Request to process
 * @param response HTTP Response to return to the client
 */
void Server::handle_add_bookmark_request_(const httplib::Request& request, httplib::Response& response){
    setup_response_to_allow_cors(response);
    try {
        Bookmark bookmark_to_add = server_utils::parse_bookmark_from_json(request.body);

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
    } catch(std::invalid_argument&) {
        //Invalid request format or invalid Bookmark
        response.status = HttpErrorCode::BAD_REQUEST;
    }
}

/**
 * @brief Handles GET HTTP requests to read all Bookmarks from this server BookmarkCollection.
 *
 * The HTTP response will be formatted as (a possibly empty) JSON array of Bookmark objects.
 * Each Bookmark object is formatted according to the format described in the documentation of mylink::server_utils::parse_bookmark_from_json.
 *
 * HTTP GET request parameters (URL params) are ignored by this method.
 * The response code is always HTTP_OK (unless major server errors occur).
 *
 * @param request HTTP Request to process
 * @param response HTTP Response to return to the client
 */
void Server::handle_get_bookmark_request_(const httplib::Request&, httplib::Response& response){
    constexpr const char* content_type_json = "application/json";

    response.set_content(
                server_utils::covert_collection_to_json(backend_.load()),
                content_type_json);
    response.status = HttpErrorCode::OK;
}
