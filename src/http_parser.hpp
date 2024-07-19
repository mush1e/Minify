#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <unordered_map>

#include "http_request_handler.hpp"

#ifndef minify_HTTP_PARSER_HPP
#define minify_HTTP_PARSER_HPP

namespace minify {
    


    void handle_client(int client_socket);
    void parse_request(HTTPRequest& req, const std::string& req_str);
    void parse_form_data(const std::string& form_data, HTTPRequest& req);

}

#endif