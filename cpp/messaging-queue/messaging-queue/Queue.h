#pragma once

#include <set>
#include <boost/asio/thread_pool.hpp>

#include "Topic.h"

class Queue
{
private:
    std::set<std::shared_ptr<Topic>, TopicCompare> topics;
    boost::asio::thread_pool thread_pool;
public:
    Queue();
    ~Queue();
    std::shared_ptr<Topic> createTopic(std::string);
    void subscribe(std::shared_ptr<Topic>, std::shared_ptr<ISubscriber>);
    void publish(std::shared_ptr<Topic>, Message &);
};