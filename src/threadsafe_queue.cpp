//
// Created by Chow on 2019/5/15.
//

#include <string>
#include <iostream>

using namespace std;

#include "threadsafe_queue.h"

int main() {
    threadsafe_queue<std::string> queue;
    queue.push("abc");
    string value;
    queue.try_pop(value);
    cout << "queue first: " << value << endl;
}



