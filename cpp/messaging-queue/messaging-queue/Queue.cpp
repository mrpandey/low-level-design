#include <thread>
#include <iostream>
#include "Queue.h"

Queue::Queue(): thread_pool(boost::asio::thread_pool(std::thread::hardware_concurrency()))
{
    std::cout << "queue initiated with " << std::thread::hardware_concurrency() << " threads" << std::endl;
}

Queue::~Queue()
{
    thread_pool.join();
}

std::shared_ptr<Topic> Queue::createTopic(std::string topic_name)
{
    std::shared_ptr<Topic> topic = std::make_shared<Topic>(topic_name);
    auto topic_it = topics.find(topic);
    if(topic_it == topics.end()){
        topics.insert(topic);
        return topic;
    }
    return *topic_it;
}

void Queue::subscribe(std::shared_ptr<Topic> topic_ptr, std::shared_ptr<ISubscriber> subscriber)
{
    if(topics.find(topic_ptr) != topics.end()){
        topic_ptr->addSubscriber(subscriber);
    }
}

void Queue::publish(std::shared_ptr<Topic> topic_ptr, Message &message)
{
    if(topics.find(topic_ptr) != topics.end()){
        topic_ptr->addMessage(message, thread_pool);
    }
}
