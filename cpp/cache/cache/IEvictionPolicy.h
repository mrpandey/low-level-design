#pragma once

template <typename K>
class IEvictionPolicy
{
public:
    virtual void accessedKey(const K &key) = 0;
    virtual K evictKey() = 0;
    virtual ~IEvictionPolicy() {}
};
