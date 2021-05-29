#include <httplib.h>
#include <markdown_collection.h>
#include <json.hpp>

using namespace httplib;
using namespace mylink;
using namespace nlohmann;

int main(void)
{
    MarkdownCollection collection("links.md");
    Server svr;

    svr.Options(R"(/add_bookmark)", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Max-Age", "86400");
        res.status = 204;
    });


    svr.Post(R"(/add_bookmark)", [&](const Request& req, Response& res) {
        json richiesta = json::parse(req.body);
        collection.add(Bookmark{richiesta["url"]});
        res.set_header("Access-Control-Allow-Origin", "*");
        //res.set_content(richiesta["url"], "text/plain");
        res.status = 200;
    });

    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
    });

    svr.listen("localhost", 1234);
}
