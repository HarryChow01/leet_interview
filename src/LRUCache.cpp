#include <iostream>

#include "LRUCache.h"

using namespace std;

int main() {

    LRUCache<std::string, int> lruCache(4);
    lruCache.put("aa", 1);
    lruCache.put("bb", 2);
    lruCache.put("cc", 3);
    lruCache.put("dd", 4);
    lruCache.put("ee", 5);

    int value = 0;
    lruCache.get("dd", value);
    cout << "get key dd: " << "value: " << value << endl;
    lruCache.printDataList();
}



