#include <stdexcept>
#include "Dictionary.h"

Dictionary::Dictionary()
{
}

Dictionary::Dictionary(const std::vector<std::pair<std::string, AttributeValue>> &attrs)
{
    for(auto p: attrs){
        dict[p.first] = p.second;
    }
}

bool Dictionary::hasAttr(const std::string attr) const
{
    if(dict.find(attr)!=dict.end()){
        return true;
    }
    return false;
}

AttributeValue Dictionary::getAttrValue(const std::string attr) const
{
    if(hasAttr(attr)){
        return dict.at(attr);
    }
    else {
        throw std::invalid_argument("The requested attribute does not exist.");
    }
}

std::vector<std::string> Dictionary::getKeys() const
{
    std::vector<std::string> keys(dict.size());
    int i = 0;
    for(auto it: dict){
        keys[i++] = it.first;
    }
    return keys;
}

std::string Dictionary::toString()
{
    std::string ret;
    ret.reserve(dict.size()*30);
    int i = 0;
    for(auto it: dict){
        if(i++){
            ret += ", ";
        }
        ret += it.first + ": ";
        ret += it.second.toString();
    }
    return ret;
}

void Dictionary::addAttr(const std::string attr, const AttributeValue value)
{
    dict[attr] = value;
}
