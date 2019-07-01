//
// Created by Chow on 2019/5/15.
//

#ifndef CPP11_LRUCACHE_H
#define CPP11_LRUCACHE_H

#include <unordered_map>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

template <typename Key, typename Value>
class LRUCache {
public:
    using Iterator = typename list<pair<Key, Value>>::iterator;
    static const uint32_t kCapacity = 1024;
    explicit LRUCache(uint32_t capacity = kCapacity) : capacity_(capacity) {}

    bool get(const Key& key, Value &value) {
        if (entrys_.find(key) != entrys_.end()){
            dataList_.splice(dataList_.begin(), dataList_, entrys_[key]);
            value = entrys_[key]->second;
            return true;
        } else {
            return false;
        }
    }

    void put(const Key& key, const Value& value) {
        if (entrys_.find(key) != entrys_.end()) {
            dataList_.splice(dataList_.begin(), dataList_, entrys_[key]);
            entrys_[key]->second = value;
        } else {
            while (dataList_.size() >= capacity_) {
                entrys_.erase(dataList_.back().first);
                dataList_.pop_back();
            }
            dataList_.push_front({ key, value });
            entrys_[key] = dataList_.begin();
        }
    }

    void printDataList() {
        cout << "dataList: " << endl;
        for (const auto& item : dataList_) {
            cout << "key: " << item.first << " value: " << item.second << endl;
        }
    }
private:
    uint32_t capacity_ = kCapacity;
    list<pair<Key, Value>> dataList_;
    unordered_map<int, Iterator> entrys_;
    //typename unordered_map<int, list<pair<typename Key, typename Value>::iterator> entrys_;
};





#endif //CPP11_LRUCACHE_H
