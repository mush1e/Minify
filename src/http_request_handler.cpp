

#include "http_request_handler.hpp"

namespace minify {
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~ Router ~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto handle_request(HTTPRequest& req, int client_socket) -> void {
        if (req.method == "GET") {
            if (req.URI == "/")             handle_get_home(req, client_socket);
        } else if (req.method == "POST") 
            if(req.URI == "/shorten")       handle_post_shorten(req, client_socket); 
    }

}