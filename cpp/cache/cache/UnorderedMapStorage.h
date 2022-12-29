#pragma once

#include <stdexcept>
#include <utility>
#include <unordered_map>

#include "IStorage.h"

template <typename K, typename V>
class UnorderedMapStorage : public IStorage<K, V>
{
private:
    std::unordered_map<K, V> storage;
    int capacity;

public:
    UnorderedMapStorage(const int capacity);

    V get(const K &key) const override;
    void put(const K &key, const V &value) override;
    void remove(const K &key) override;
};

template <typename K, typename V>
inline UnorderedMapStorage<K, V>::UnorderedMapStorage(const int capacity) : capacity(capacity)
{
    if(capacity<=0){
        throw std::invalid_argument("Capacity of storage must be positive.");
    }
}

template <typename K, typename V>
inline V UnorderedMapStorage<K, V>::get(const K &key) const
{
    auto it = storage.find(key);
    if (it != storage.end())
    {
        return it->second;
    }
    else
    {
        throw std::invalid_argument("The requested key does not exist.");
    }
}

template <typename K, typename V>
inline void UnorderedMapStorage<K, V>::put(const K &key, const V &value)
{
    if (storage.size() == capacity)
    {
        throw std::length_error("Storage is full. Cannot add new key.");
    }
    storage[key] = value;
}

template <typename K, typename V>
inline void UnorderedMapStorage<K, V>::remove(const K &key)
{
    storage.erase(key);
}
