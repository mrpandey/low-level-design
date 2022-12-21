#pragma once

#include <string>
#include <vector>
#include <set>
#include <mutex>
#include <memory>
#include <boost/uuid/random_generator.hpp>
#include <boost/asio/thread_pool.hpp>

#include "Message.h"
#include "TopicSubscriber.h"

class Topic
{
private:
    std::string name;
    std::mutex sub_mtx, msg_mtx;
    std::vector<Message> messages;
    std::set<std::shared_ptr<TopicSubscriber>, TopicSubscriberCompare> topic_subscribers;
    static boost::uuids::random_generator rg;

    void publishMessages(boost::asio::thread_pool &);

public:
    Topic(std::string);
    std::string getName() const;
    void addSubscriber(std::shared_ptr<Subscriber>);
    void removeSubscriber(std::shared_ptr<Subscriber>);
    void addMessage(Message, boost::asio::thread_pool &);
};


struct TopicCompare {
    bool operator()(const std::shared_ptr<Topic> & tptr1, const std::shared_ptr<Topic> & tptr2) const {
        return tptr1->getName() < tptr2->getName();
    }
};