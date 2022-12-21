#include "TopicSubscriber.h"

TopicSubscriber::TopicSubscriber(std::shared_ptr<Subscriber> sub_ptr, int offset) : sub_ptr(sub_ptr), offset(offset)
{
}

int TopicSubscriber::getOffset() const
{
    return offset.load();
}

std::shared_ptr<Subscriber> TopicSubscriber::getSubscriber() const
{
    return sub_ptr;
}

void TopicSubscriber::setOffset(int offset)
{
    this->offset.store(offset);
}

void TopicSubscriber::incrementOffset()
{
    offset++;
}