#pragma once
#include <unordered_map>
#include <string>
#include <variant>
#include <vector>

#include "AttributeValue.h"

class Dictionary
{
private:
    std::unordered_map<std::string, AttributeValue> dict;

public:
    Dictionary();
    Dictionary(const std::vector<std::pair<std::string, AttributeValue>> &attrs);

    bool hasAttr(const std::string attr) const;
    AttributeValue getAttrValue(const std::string attr) const;
    std::vector<std::string> getKeys() const;
    std::string toString();
    void addAttr(const std::string attr, const AttributeValue value);
};
