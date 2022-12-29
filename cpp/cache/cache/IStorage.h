#pragma once

template <typename K, typename V>
class IStorage
{
public:
    virtual V get(const K&) const = 0;
    virtual void put(const K&, const V&) = 0;
    virtual void remove(const K&) = 0;
    virtual ~IStorage() {}
};