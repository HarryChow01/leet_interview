//
// Created by Chow on 2019/5/15.
//

#ifndef CPP11_LRUCACHE_H
#define CPP11_LRUCACHE_H

#include <unordered_map>
#include <list>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;

template <typename Key, typename Value>
class LRUCache {
public:
    using Iterator = typename std::list<std::pair<Key, Value>>::iterator;
    static const uint32_t kCapacity = 1024;
    explicit LRUCache(uint32_t capacity = kCapacity) : capacity_(capacity) {}

    bool get(const Key& key, Value& value) {
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
    std::list<std::pair<Key, Value>> dataList_;
    std::unordered_map<Key, Iterator> entrys_;
};





#endif //CPP11_LRUCACHE_H
