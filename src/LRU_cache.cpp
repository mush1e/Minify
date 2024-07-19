#include "LRU_cache.hpp"

namespace minify {

    auto LRU_Cache::get_min(std::string val) -> std::string {
        if (addr_map_min.find(val) == addr_map_min.end())
            return NULL;
        std::string key = addr_map_min[val]->key;
        put (key, val);
        return key;
    }

    auto LRU_Cache::get_url(std::string key) -> std::string{
        if (addr_map_url.find(key) == addr_map_url.end())
            return NULL;
        std::string val = addr_map_url[key]->val;
        put(key, val);
        return val;
    }

    auto LRU_Cache::remove(std::string key) -> void {
        if (addr_map_url.find(key) == addr_map_url.end())
            return;
        std::string mini_val = addr_map_url[key]->val;
        Node* curr_node = addr_map_url[key];
        Node* prev_node = curr_node->prev;
        Node* next_node = curr_node->next;
        
        if (next_node)
            next_node->prev = prev_node;
        else
            tail = prev_node;
        
        if (prev_node)
            prev_node->next = next_node;
        else
            head = next_node;

        delete curr_node;

        addr_map_url.erase(key);
        addr_map_url.erase(mini_val);
        size--;
    }

    auto LRU_Cache::put(std::string key, std::string val) -> void {
            Node* new_node = new Node(key, val);
            remove(key);
            addr_map_url[key] = new_node;
            addr_map_min[val] = new_node;
            new_node->next = head;
            if (head)
                head->prev = new_node;
            head = new_node;
            if (!tail)
                tail = new_node;
            size++;
            if (size > cap)
                remove(tail->key);
    }

}