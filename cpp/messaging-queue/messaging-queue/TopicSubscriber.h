#pragma once

#include <memory>
#include <atomic>
#include <functional>
#include "Subscriber.h"

class TopicSubscriber
{
private:
    std::atomic<int> offset;
    std::shared_ptr<Subscriber> sub_ptr;

public:
    TopicSubscriber(std::shared_ptr<Subscriber>, int offset = 0);
    int getOffset() const;
    std::shared_ptr<Subscriber> getSubscriber() const;
    void setOffset(int);
    void incrementOffset();
};


struct TopicSubscriberCompare {
    bool operator()(const std::shared_ptr<TopicSubscriber> & ts_ptr_1, const std::shared_ptr<TopicSubscriber> & ts_ptr_2) const {
        return ts_ptr_1->getSubscriber() < ts_ptr_2->getSubscriber();
    }
};