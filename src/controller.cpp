#include "controller.hpp"

namespace minify {

auto send_bad_request = [](int client_socket) {
        HTTPResponse response;
        std::string http_response;
        response.status_code = 400;
        response.status_message = "Bad Request";
        http_response = response.generate_response();
        send(client_socket, http_response.c_str(), http_response.length(), 0);
    };

    auto send_internal_server_error = [](int client_socket) {
        HTTPResponse response;
        std::string http_response;
        response.status_code = 500;
        response.status_message = "Internal Server Error";
        http_response = response.generate_response();
        send(client_socket, http_response.c_str(), http_response.length(), 0);
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~ Helper Function (Print Request) ~~~~~~~~~~~~~~~~~~~~~~~
    std::ostream& operator<<(std::ostream& os, const HTTPRequest& req) {
        os << "Method: " << req.method << "\n";
        os << "URI: " << req.URI << "\n";
        os << "Version: " << req.version << "\n";
        os << "Headers:\n";

        for (const auto& header : req.headers) 
            os << "  " << std::setw(20) << std::left << header.first << ": " << header.second << "\n";

        os << "Cookies:\n";

        for (const auto& cookie : req.cookies) 
            os << "  " << std::setw(20) << std::left << cookie.first << ": " << cookie.second << "\n";
        
        os << "Body: " << req.body << "\n";

        return os;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~ Helper Function (URL Decode) ~~~~~~~~~~~~~~~~~~~~~~~
    std::string url_decode(const std::string& str) {
        int i = 0;
        std::stringstream decoded;

        while (i < str.length()) {
            if (str[i] == '%') {
                if (i + 2 < str.length()) {
                    int hexValue;
                    std::istringstream(str.substr(i + 1, 2)) >> std::hex >> hexValue;
                    decoded << static_cast<char>(hexValue);
                    i += 3;
                } else {
                    // If '%' is at the end of the string, leave it unchanged
                    decoded << '%';
                    i++;
                }
            } else if (str[i] == '+') {
                decoded << ' ';
                i++;
            } else {
                decoded << str[i];
                i++;
            }
        }
        return decoded.str();
    }

     auto sendNotFoundResponse(int client_socket) -> void {
        HTTPResponse response {};
        response.status_code = 400;
        response.status_message = "Bad Request";
        std::string http_response = response.generate_response();
        send(client_socket, http_response.c_str(), http_response.length(), 0);

    }

    auto serveStaticFile(const std::string& file_path, int client_socket) -> void {
        std::ifstream file(file_path);

        if (file.good()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string content = buffer.str();

            std::string response = "HTTP/1.1 200 OK\r\nContent-Length: "
                                    + std::to_string(content.length())
                                    + "\r\n\r\n"
                                    + content;

            send(client_socket, response.c_str(), response.length(), 0);
        }
        else
            sendNotFoundResponse(client_socket);
    }
    
    auto get_form_field(const std::string& body, const std::string& field_name) -> std::string {
        std::string field_value;
        size_t pos = body.find(field_name + "=");
        if (pos != std::string::npos) {
            pos += field_name.length() + 1;
            size_t end_pos = body.find("&", pos);
            end_pos = (end_pos == std::string::npos) ? body.length() : end_pos;
            field_value = body.substr(pos, end_pos - pos);
        }
        return url_decode(field_value);
    }


    auto generate_min_str(size_t length) -> std::string {
        std::string random_string;
        random_string.reserve(length);
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> dist(0, alphabet.size() - 1);
        for (size_t i = 0; i < length; ++i) 
            random_string += alphabet[dist(generator)];
        return random_string;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ controllers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    auto handle_get_home(HTTPRequest& req, int client_socket) -> void {
        serveStaticFile("./public/index.html", client_socket);
    }

    auto handle_post_shorten(HTTPRequest& req, int client_socket) -> void {
        HTTPResponse response;
        std::string http_response;
        std::string url = req.body.substr(req.body.find(':') + 1);
        std::string min_str;
        minify::LRU_Cache& cache = minify::LRU_Cache::get_instance();

        min_str = cache.get_url(url);
        if (min_str.empty()) {
            min_str = generate_min_str(8);
            cache.put(url, min_str);
        }

        response.status_code = 200;
        response.status_message = "OK";
        response.body = R"(
                            <div class="alert alert-success">
                                <strong>Original URL:</strong> <a href=")" + url + R"(" target="_blank">)" + url + R"(</a><br>
                                <strong>Shortened URL:</strong> <a href="http://localhost:8080/)" + min_str + R"(" target="_blank">http://localhost:8080/)" + min_str + R"(</a><br>
                                <button class="btn btn-secondary mt-2 copy-button" data-url="http://localhost:8080/)" + min_str + R"("">Copy to Clipboard</button>
                            </div>
                        )";
        http_response = response.generate_response();

        send(client_socket, http_response.c_str(), http_response.length(), 0);
    }

    auto handle_get_redirect(HTTPRequest& req, int client_socket) -> void {
        HTTPResponse response;
        std::string http_response;
        std::string min_str = req.URI.substr(1);

        LRU_Cache cache = LRU_Cache::get_instance();
        std::string original_url = cache.get_min(min_str);

        if(original_url.empty()) {
            send_bad_request(client_socket);
            return;
        } else {
            response.status_code = 302;
            response.status_message = "Found";
            response.location = original_url;
            response.body = "Redirecting to " + original_url;
            http_response = response.generate_response();
            send(client_socket, http_response.c_str(), http_response.length(), 0);
        }
       
    }
}