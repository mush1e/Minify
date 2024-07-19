#include "http.hpp"
#include "controller.hpp"

#ifndef MINIFY_HTTP_REQUEST_HANDLER_HPP
#define MINIFY_HTTP_REQUEST_HANDLER_HPP

namespace minify {

    void handle_request(HTTPRequest& req, int client_socket);

}

#endif