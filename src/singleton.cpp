//
// Created by Chow on 2019/5/16.
//

#include "singleton.h"

int main() {
    Singleton1* pInstance = Singleton1::getInstance();
    Singleton2 &singleton2 = Singleton2::getInstance();
}
