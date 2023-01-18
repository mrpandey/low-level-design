#pragma once

#include <unordered_map>
#include <list>
#include <stdexcept>

#include "IEvictionPolicy.h"

/// @brief Evict the least frequently used key. If multiple keys have the least frequency, then remove the one which was used least recently.
/// @tparam K The type of key.
template <typename K>
class LFUPolicy : public IEvictionPolicy<K>
{
    using listitr = typename std::list<K>::iterator;

private:
    int min_freq;
    std::unordered_map<K, int> key_freq;
    std::unordered_map<K, listitr> key_itrs;
    // stores keys in LRU order for given frequency: least recent to most recent
    std::unordered_map<int, std::list<K>> freq_keys;

    void removeKey(const K &key);
    void addKey(const K &key, int freq);

public:
    LFUPolicy();
    void accessedKey(const K &key);
    K evictKey();
};

template <typename K>
inline void LFUPolicy<K>::removeKey(const K &key)
{
    int freq = key_freq[key];
    auto itr = key_itrs[key];

    freq_keys[freq].erase(itr);
    key_freq.erase(key);
    key_itrs.erase(key);
}

template <typename K>
inline void LFUPolicy<K>::addKey(const K &key, int freq)
{
    key_freq[key] = freq;
    freq_keys[freq].push_back(key);
    key_itrs[key] = --freq_keys[freq].end();
}

template <typename K>
inline LFUPolicy<K>::LFUPolicy() : min_freq(0) {}

template <typename K>
inline void LFUPolicy<K>::accessedKey(const K &key)
{
    if (key_freq.find(key) == key_freq.end())
    {
        addKey(key, 1);
        min_freq = 1;
        return;
    }

    int freq = key_freq[key];
    removeKey(key);
    addKey(key, freq + 1);

    if (min_freq == freq && freq_keys[min_freq].empty())
    {
        min_freq++;
    }
}

template <typename K>
inline K LFUPolicy<K>::evictKey()
{
    if (key_freq.empty())
    {
        throw std::logic_error("There are no keys to evict.");
    }

    while (freq_keys[min_freq].empty())
    {
        min_freq++;
    }

    K key = freq_keys[min_freq].front();
    removeKey(key);

    /*
        Update min_freq? Not needed.
        Right now min_freq may be in two states: correct or incorrect.
        Three things can happen after this evictKey() call:
        1. accessedKey() is called with an existing key
            - this will modify min_freq only if min_freq is correct
        2. accessedKey() is called with a new key
            - the min_freq will be updated to 1, min_freq is correct now
        3. evictKey() is called again
            - new min_freq will be found in linear time if there is a key
            - evict the key, now we are back in the same situation :)

        Usually, eviction happens before case 2. So another approach is
        that we enforce this by throwing errors in cases 1 and 3.
    */

    return key;
}
