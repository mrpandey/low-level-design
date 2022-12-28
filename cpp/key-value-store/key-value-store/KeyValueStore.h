#pragma once

#include <stdexcept>
#include <utility>
#include <mutex>
#include <shared_mutex>

#include "Dictionary.h"
#include "AttributeValue.h"

template <typename K>
class KeyValueStore
{
private:
    std::unordered_map<K, Dictionary> storage;
    std::unordered_map<std::string, AttributeValue> attr_representative;
    mutable std::shared_mutex sh_mtx;

public:
    Dictionary get(const K &key) const;
    std::vector<K> getKeys() const;
    std::vector<K> search(const std::string &, const AttributeValue &) const;
    // void put(const K &key, const Dictionary &value);
    void put(const K &key, const std::vector<std::pair<std::string, AttributeValue>> &attrs);
    void remove(const K &key);
};

template <typename K>
inline Dictionary KeyValueStore<K>::get(const K &key) const
{
    std::shared_lock<std::shared_mutex> sh_lock(sh_mtx);
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

template <typename K>
inline std::vector<K> KeyValueStore<K>::getKeys() const
{
    std::shared_lock<std::shared_mutex> sh_lock(sh_mtx);
    std::vector<K> key_list(storage.size());
    int i = 0;
    for (auto it : storage)
    {
        key_list[i++] = it.first;
    }
    return key_list;
}

template <typename K>
inline std::vector<K> KeyValueStore<K>::search(const std::string &attr, const AttributeValue &attr_val) const
{
    std::shared_lock<std::shared_mutex> sh_lock(sh_mtx);
    std::vector<K> keys;
    for (auto it : storage)
    {
        if (it.second.hasAttr(attr) && it.second.getAttrValue(attr) == attr_val)
        {
            keys.push_back(it.first);
        }
    }
    return keys;
}

/// @brief Add new key-value entry or replaces value if key already exists.
/// Existing attributes of will be lost if key exists.
// template <typename K>
// inline void KeyValueStore<K>::put(const K &key, const Dictionary &value)
// {
//     std::unique_lock<std::shared_mutex> lock(sh_mtx);
//     storage[key] = value;
// }

/// @brief Adds/updates multiple attribute-value entries. Existing attributes in value are not lost.
template <typename K>
inline void KeyValueStore<K>::put(const K &key, const std::vector<std::pair<std::string, AttributeValue>> &attrs)
{
    bool wrong_type = false;
    std::unique_lock<std::shared_mutex> lock(sh_mtx);
    // TODO: also check if attributes are unique
    for (auto p : attrs)
    {
        std::string attr = p.first;
        AttributeValue attr_val = p.second;
        if (attr_representative.find(attr) != attr_representative.end() && !attr_representative[attr].hasSameType(attr_val))
        {
            wrong_type = true;
            break;
        }
    }

    if (wrong_type)
    {
        throw std::logic_error("One or more attribute types invalid while adding key.");
    }

    if (storage.find(key) == storage.end())
    {
        storage[key] = Dictionary();
    }

    for (auto p : attrs)
    {
        storage[key].addAttr(p.first, p.second);
        if (attr_representative.find(p.first) == attr_representative.end())
        {
            attr_representative[p.first] = p.second;
        }
    }
}

template <typename K>
inline void KeyValueStore<K>::remove(const K &key)
{
    std::unique_lock<std::shared_mutex> lock(sh_mtx);
    storage.erase(key);
}
