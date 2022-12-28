#include "AttributeValue.h"

AllowedTypeStringConverter AttributeValue::string_converter;

AttributeValue::AttributeValue()
{
}

AttributeValue::AttributeValue(const AllowedType &attr_value) : attr_value(attr_value)
{
}

std::string AttributeValue::toString() const
{
    return std::visit(string_converter, attr_value);
    // if(std::holds_alternative<int>(attr_value)){
    //     return std::to_string(int(attr_value));
    // }
}

bool AttributeValue::operator==(const AttributeValue &other) const
{
    return attr_value == other.attr_value;
}

bool AttributeValue::hasSameType(const AttributeValue &other) const
{
    return attr_value.index() == other.attr_value.index();
}
