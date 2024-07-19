#include "server.hpp"

auto main() -> int {
    minify::HTTP_Server server(8080);
    server.start();
    return 0;
}