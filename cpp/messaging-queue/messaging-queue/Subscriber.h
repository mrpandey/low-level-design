#pragma once
#include "ISubscriber.h"
#include <boost/uuid/random_generator.hpp>

class Subscriber : public ISubscriber
{
private:
    static boost::uuids::random_generator rg;
    std::string id;
    std::string name;

public:
    Subscriber(std::string);
    std::string getId() const override;
    // question: what happens if multiple threads of different topics call consume() of same instance?
    // answer: the threads will execute the method concurrently, so expect interleaving operations
    // it is fine as long there is no data race
    // in our case it is just cout statements (no modification of shared data)
    void consumeMessage(Message msg) override;
};