#include "LRU_cache.hpp"

namespace minify {

    LRU_Cache::~LRU_Cache() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    auto LRU_Cache::get_instance() -> LRU_Cache& {
        static LRU_Cache instance(10);
        return instance;
    }

    auto LRU_Cache::get_min(std::string val) -> std::string {
        if (addr_map_min.find(val) == addr_map_min.end())
            return "";
        Node* node = addr_map_min[val];
        move_to_front(node);
        return node->key;
    }

    auto LRU_Cache::get_url(std::string key) -> std::string {
        if (addr_map_url.find(key) == addr_map_url.end())
            return "";
        Node* node = addr_map_url[key];
        move_to_front(node);
        return node->val;
    }

    auto LRU_Cache::remove(std::string key) -> void {
        if (addr_map_url.find(key) == addr_map_url.end())
            return;
        Node* node = addr_map_url[key];
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;
        if (node == tail) tail = node->prev;
        addr_map_url.erase(node->key);
        addr_map_min.erase(node->val);
        delete node;
        size--;
    }

    auto LRU_Cache::put(std::string key, std::string val) -> void {
        if (addr_map_url.find(key) != addr_map_url.end()) {
            Node* node = addr_map_url[key];
            node->val = val;
            move_to_front(node);
            return;
        }
        if (size == cap) {
            remove(tail->key);
        }
        Node* new_node = new Node(key, val);
        new_node->next = head;
        if (head) head->prev = new_node;
        head = new_node;
        if (!tail) tail = new_node;
        addr_map_url[key] = new_node;
        addr_map_min[val] = new_node;
        size++;
    }

}
