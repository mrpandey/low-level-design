#pragma once

#include <memory>
#include <mutex>
#include <shared_mutex>

#include "UnorderedMapStorage.h"
#include "IEvictionPolicy.h"

template <typename K, typename V>
class KeyValueStore
{
    using StoragePtr = std::unique_ptr<IStorage<K, V>>;
    using EvictionPolicyPtr = std::unique_ptr<IEvictionPolicy<K>>;

private:
    StoragePtr storage_ptr;
    EvictionPolicyPtr eviction_policy_ptr;
    mutable std::shared_mutex mutex;

public:
    KeyValueStore(StoragePtr &storage_ptr, EvictionPolicyPtr &eviction_policy_ptr);
    V get(const K &key) const;
    void put(const K &key, const V &value);
    void remove(const K &key);
};

template <typename K, typename V>
inline KeyValueStore<K, V>::KeyValueStore(StoragePtr &storage_ptr, EvictionPolicyPtr &eviction_policy_ptr) : storage_ptr(std::move(storage_ptr)), eviction_policy_ptr(std::move(eviction_policy_ptr))
{
}

template <typename K, typename V>
inline V KeyValueStore<K, V>::get(const K &key) const
{
    std::shared_lock<std::shared_mutex> lock(mutex);
    V value = storage_ptr->get(key);
    // # TODO: the accessedKey() method is not const. It modifies stuff. So not thread-safe.
    eviction_policy_ptr->accessedKey(key);
    return value;
}

template <typename K, typename V>
inline void KeyValueStore<K, V>::put(const K &key, const V &value)
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    try
    {
        storage_ptr->put(key, value);
        eviction_policy_ptr->accessedKey(key);
    }
    catch (std::length_error &e)
    {
        K evicted_key = eviction_policy_ptr->evictKey();
        storage_ptr->remove(evicted_key);
        storage_ptr->put(key, value);
        eviction_policy_ptr->accessedKey(key);
    }
}

template <typename K, typename V>
inline void KeyValueStore<K, V>::remove(const K &key)
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    storage_ptr->remove(key);
    eviction_policy_ptr->evictKey();
}
