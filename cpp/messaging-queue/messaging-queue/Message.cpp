#include "Message.h"

Message::Message(std::string message): message(message)
{
    timestamp = std::chrono::system_clock::now();
}

std::string Message::getMessage() const
{
    return message;
}
