#pragma once
#include <string>
#include "Message.h"

class ISubscriber {
public:
    virtual std::string getId() const = 0;
    virtual void consumeMessage(Message msg) = 0;
};