//
// Created by Chow on 2019/5/16.
//
#include <string>
#include <iostream>
using namespace std;

#include "threadsafe_hashmap.h"

int main() {
    threadsafe_hashmap<std::string, std::string> hashmap;
    hashmap.put("aa", "aa");
    
    const string key("aa");
    std::string value;
    hashmap.get(key, value);
    cout << "key aa: vlaue: " << value << endl;
}
