#pragma once

#include <list>
#include <unordered_map>
#include "IEvictionPolicy.h"

template <typename K>
class LRUPolicy : public IEvictionPolicy<K>
{
private:
    std::list<K> keys;
    std::unordered_map<K, typename std::list<K>::iterator> key_itrs;

public:
    void accessedKey(const K &key) override;
    K evictKey() override;
};

template <typename K>
inline void LRUPolicy<K>::accessedKey(const K &key)
{
    auto it = key_itrs.find(key);
    if (it != key_itrs.end())
    {
        auto key_it = it->second;
        keys.erase(key_it);
    }
    keys.push_back(key);
    key_itrs[key] = --keys.end();
}

template <typename K>
inline K LRUPolicy<K>::evictKey()
{
    K key = keys.front();
    key_itrs.erase(key);
    keys.pop_front();
    return key;
}
