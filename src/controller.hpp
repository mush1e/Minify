#include <regex>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <sys/socket.h>
#include <unordered_map>

#include "http.hpp"
#include "LRU_cache.hpp"

#ifndef MINIFY_CONTROLLER_HPP
#define MINIFY_CONTRILLER_HPP

namespace minify {

    // helpers
    void sendNotFoundResponse(int client_socket);
    void serveStaticFile(const std::string& file_path, int client_socket);
    std::unordered_map<std::string, std::string> parse_parameters(std::string uri);
    std::ostream& operator<<(std::ostream& os, const HTTPRequest& req);
    std::string get_form_field(const std::string& body, const std::string& field_name);
    std::string url_decode(const std::string& str);
    std::string generate_min_str(size_t length);


    // controllers
    void handle_get_home(HTTPRequest& req, int client_socket);
    void handle_get_redirect(HTTPRequest& req, int client_socket);
    void handle_post_shorten(HTTPRequest& req, int client_socket);
}

#endif