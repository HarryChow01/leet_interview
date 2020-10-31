//
// Created by Chow on 2019/5/16.
//

#ifndef LEET_INTERVIEW_THREADSAFE_HASHMAP_H
#define LEET_INTERVIEW_THREADSAFE_HASHMAP_H

#include <mutex>
#include <unordered_map>
#include <string>
#include <vector>

template<typename Key, typename Value>
class biglock_hashmap {
public:
    biglock_hashmap() {}

    void put(const Key &key, const Value &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        //map_.emplace(key, value);
        map_[key] = value;
    }

    bool get(const Key &key, Value &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = map_.find(key);
        if (it != map_.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    void erase(const Key &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (map_.find(key) != map_.end()) {
            map_.erase(key);
        }
    }

private:
    std::mutex mutex_;
    std::unordered_map<Key, Value> map_;
};


template<typename Key, typename Value>
class threadsafe_hashmap {
public:
    threadsafe_hashmap(size_t shard_num = kDefaultShardNum) : mask_(shard_num - 1), shards_(shard_num) {
        if (shard_num < 1 || (shard_num & mask_) != 0)
            throw std::runtime_error("shard_num must be a power of two");
    }

    void put(const Key &key, Value value) {
        get_shard(key).put(key, value);
    }

    bool get(const Key &key, Value &value) {
        return get_shard(key).get(key, value);
    }

    void erase(const Key &key) {
        get_shard(key).erase(key);
    }

private:
    static const size_t kDefaultShardNum = 16;
    const size_t mask_;
    std::vector<biglock_hashmap<Key, Value>> shards_;

    biglock_hashmap<Key, Value> &get_shard(const Key &key) {
        std::hash<Key> hash_fn;
        size_t h = hash_fn(key);
        return shards_[h & mask_];
    }
};

#endif //LEET_INTERVIEW_THREADSAFE_HASHMAP_H
