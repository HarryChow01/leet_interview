#include <iostream>

#include "LRUCache.h"

using namespace std;

int main() {

    LRUCache<int, int> lruCache(4);
    lruCache.put(1, 1);
    lruCache.put(2, 2);
    lruCache.put(3, 3);
    lruCache.put(4, 4);
    lruCache.put(5, 5);

    int value = 0;
    lruCache.get(3, value);
    cout << "get key 3: " << "value: " << value << endl;
    lruCache.printDataList();
}



