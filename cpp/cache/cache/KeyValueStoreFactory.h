#pragma once

#include "KeyValueStore.h"
#include "LRUPolicy.h"
#include "LFUPolicy.h"

template <typename K, typename V>
class KeyValueStoreFactory
{
    using StoragePtr = std::unique_ptr<IStorage<K, V>>;
    using EvictionPolicyPtr = std::unique_ptr<IEvictionPolicy<K>>;

public:
    KeyValueStore<K, V> getDefaultStore(const int &capacity);

    KeyValueStore<K, V> getLRUStore(const int &capacity);

    KeyValueStore<K, V> getLFUStore(const int &capacity);
};

template <typename K, typename V>
inline KeyValueStore<K, V> KeyValueStoreFactory<K, V>::getDefaultStore(const int &capacity)
{
    return getLRUStore(capacity);
}

template <typename K, typename V>
inline KeyValueStore<K, V> KeyValueStoreFactory<K, V>::getLRUStore(const int &capacity)
{
    StoragePtr storage_ptr = std::make_unique<UnorderedMapStorage<K, V>>(capacity);
    EvictionPolicyPtr policy_ptr = std::make_unique<LRUPolicy<K>>();

    return KeyValueStore<K, V>(storage_ptr, policy_ptr);
}

template <typename K, typename V>
inline KeyValueStore<K, V> KeyValueStoreFactory<K, V>::getLFUStore(const int &capacity)
{
    StoragePtr storage_ptr = std::make_unique<UnorderedMapStorage<K, V>>(capacity);
    EvictionPolicyPtr policy_ptr = std::make_unique<LFUPolicy<K>>();

    return KeyValueStore<K, V>(storage_ptr, policy_ptr);
}
