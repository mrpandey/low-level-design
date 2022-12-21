#include <iostream>
#include <thread>
#include <chrono>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Subscriber.h"

boost::uuids::random_generator Subscriber::rg;

Subscriber::Subscriber(std::string name) : name(name)
{
    id = boost::uuids::to_string(Subscriber::rg());
}

std::string Subscriber::getId() const
{
    return id;
}

void Subscriber::consumeMessage(Message msg)
{
    std::cout << "Sub " << name << " consuming... " << msg.getMessage() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Sub " << name << " got message: " << msg.getMessage() << std::endl;
}
