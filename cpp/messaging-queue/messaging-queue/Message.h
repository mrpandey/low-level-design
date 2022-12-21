#pragma once
#include <string>
#include <chrono>

class Message {
    std::string message;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
public:
    Message(std::string);
    std::string getMessage() const;
};