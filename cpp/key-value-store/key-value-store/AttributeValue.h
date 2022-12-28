#pragma once

#include <variant>
#include <string>

using AllowedType = std::variant<int, double, bool, std::string>;

class AllowedTypeStringConverter {
public:
    std::string operator()(const std::string &s) const {
        return s;
    }

    std::string operator()(const int &i) const {
        return std::to_string(i);
    }

    std::string operator()(const double &d) const {
        return std::to_string(d);
    }

    std::string operator()(const bool &b) const {
        return b ? "true" : "false";
    }
};

class AttributeValue
{
private:
    AllowedType attr_value;
    static AllowedTypeStringConverter string_converter;
public:
    AttributeValue();
    AttributeValue(const AllowedType &attr_value);
    std::string toString() const;
    bool hasSameType(const AttributeValue &other) const;
    bool operator==(const AttributeValue &other) const;
};