#include <unordered_set>
#include <string>

#ifndef MINIFY_LRU_CACHE_HPP
#define MINIFY_LRU_CACHE_HPP

namespace minify {

    struct Node {
        std::string key {};
        std::string val {};
        Node* next {};
        Node* prev {};
        Node(std::string key, std::string val, Node* next=nullptr, Node* prev = nullptr)
            : key(key), val(val), next(next), prev(prev) {};
    };

    class LRU_Cache {
    private:
        size_t cap {};
        size_t size {};
        std::unordered_map<std::string, Node*> addr_map_url;
        std::unordered_map<std::string, Node*> addr_map_min;
        Node* head {};
        Node* tail {};
    public:
        LRU_Cache(size_t cap) : cap(cap) {};
        ~LRU_Cache();
        static LRU_Cache& get_instance();
        void put(std::string key, std::string val);
        std::string get_url (std::string key);
        std::string get_min (std::string key);
        void remove (std::string key);
    };


}

#endif