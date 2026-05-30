#include <iostream>
#include "LRUCache.h"


int main(){
    LRUCache<int, int> cache(3);
    int arr[]{1, 2, 3, 4};
    for(int i = 0; i < 4; i++){
        for(int j = 4; j < 9; j++){
            cache.put(i, j);
            print_cache(cache);
        }
    }
    cache.cache_info();

}