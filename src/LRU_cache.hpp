#ifndef MINIFY_LRU_CACHE_HPP
#define MINIFY_LRU_CACHE_HPP

#include <unordered_map>
#include <string>
#include <iostream>

namespace minify {

    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    struct Node {
        std::string key;
        std::string val;
        Node* next;
        Node* prev;
        Node(std::string key, std::string val, Node* next=nullptr, Node* prev=nullptr)
            : key(key), val(val), next(next), prev(prev) {}
    };

    class LRU_Cache {
    private:
        size_t cap;
        size_t size;
        std::unordered_map<std::string, Node*> addr_map_url;
        std::unordered_map<std::string, Node*> addr_map_min;
        Node* head;
        Node* tail;

        void move_to_front(Node* node);

        void remove_tail() {
            if (!tail) return;
            if (tail->prev) tail->prev->next = nullptr;
            else head = nullptr;
            addr_map_url.erase(tail->key);
            addr_map_min.erase(tail->val);
            Node* old_tail = tail;
            tail = tail->prev;
            delete old_tail;
            size--;
        }

    public:
        LRU_Cache(size_t cap) : cap(cap), size(0), head(nullptr), tail(nullptr) {}
        ~LRU_Cache();
        static LRU_Cache& get_instance();
        void put(std::string key, std::string val);
        std::string get_url(std::string key);
        std::string get_min(std::string val);
        void remove(std::string key);
    };

}

#endif
