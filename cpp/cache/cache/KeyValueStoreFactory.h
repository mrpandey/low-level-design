#pragma once

#include "KeyValueStore.h"
#include "LRUPolicy.h"

template <typename K, typename V>
class KeyValueStoreFactory
{
public:
    KeyValueStore<K, V> getDefaultStore(const int &capacity);

    KeyValueStore<K, V> getStoreWithLRU(const int &capacity);
};

template <typename K, typename V>
inline KeyValueStore<K, V> KeyValueStoreFactory<K, V>::getDefaultStore(const int &capacity)
{
    return getStoreWithLRU(capacity);
}

template <typename K, typename V>
inline KeyValueStore<K, V> KeyValueStoreFactory<K, V>::getStoreWithLRU(const int &capacity)
{
    std::unique_ptr<IStorage<K, V>> storage_ptr = std::make_unique<UnorderedMapStorage<K, V>>(capacity);
    std::unique_ptr<IEvictionPolicy<K>> policy_ptr = std::make_unique<LRUPolicy<K>>();

    return KeyValueStore<K, V>(storage_ptr, policy_ptr);
}
