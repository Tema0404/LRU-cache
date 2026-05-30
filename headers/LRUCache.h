#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

template<typename Key, typename Value>
class LRUCache{
    using ListIterator = typename std::list<std::pair<Key, Value>>::iterator;
    std::list<std::pair<Key, Value>> lst_elements;
    std::unordered_map<Key, ListIterator> map_elements;
    struct Info{
        long hits = 0;
        long misses = 0;
        size_t max_size = 0;
        size_t current_size = 0;
    } info;
public:
    LRUCache(size_t max_size);

    void cache_info();
    void cache_clear();
    Value* get(const Key& key); 
    void put(Key key, Value value); 
    
    template<typename K, typename V>
    friend void print_cache(LRUCache<K, V>& cache);
};

template<typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t max_size){
    if(max_size < 1)
        throw std::invalid_argument("incorrect argument");
    info.max_size = max_size;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::cache_info(){
        std::cout << "hits: " << info.hits <<
        "; misses: " << info.misses << 
        "; maxsize: " << info.max_size << 
        "; currsize: " << info.current_size << '\n';
    }

template<typename Key, typename Value>
void LRUCache<Key, Value>::cache_clear(){
    lst_elements.clear();
    map_elements.clear();
    info.current_size = 0;
}
        
template<typename Key, typename Value>
Value* LRUCache<Key, Value>::get(const Key& key){
    auto find_it = map_elements.find(key);
    if(find_it != map_elements.end()){
        info.hits++;
        auto val = find_it->second;
        lst_elements.splice(lst_elements.begin(), lst_elements, val);
        return &lst_elements.begin()->second;
    }
    else{
        info.misses++;
        return nullptr;
    }
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::put(Key key, Value value){
    auto insert_el = this->get(key);
    if(insert_el != nullptr){
        *insert_el = value;
    }
    else{
        info.current_size++;
        lst_elements.push_front({key, value});
        map_elements[key] = lst_elements.begin();
        if(lst_elements.size() > info.max_size){
            auto last_el = lst_elements.back();
            map_elements.erase(last_el.first);
            lst_elements.pop_back();
            
            info.current_size--;
        }
    }
} 

template<typename Key, typename Value>
void print_cache(LRUCache<Key, Value>& cache){
    for(auto& el: cache.lst_elements){
        std::cout << '{' << el.first << ", " << el.second << "} -> ";
    }
    std::cout << '\n';
}