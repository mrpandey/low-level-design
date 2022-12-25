#include "Topic.h"
#include <boost/asio/post.hpp>

Topic::Topic(std::string name) : name(name)
{
}

std::string Topic::getName() const
{
    return name;
}

void Topic::addSubscriber(std::shared_ptr<ISubscriber> sub_ptr)
{
    auto ts = std::make_shared<TopicSubscriber>(sub_ptr);
    std::lock_guard<std::mutex> lck(sub_mtx);
    if (topic_subscribers.find(ts) == topic_subscribers.end())
    {
        topic_subscribers.insert(ts);
    }
}

void Topic::removeSubscriber(std::shared_ptr<ISubscriber> sub_ptr)
{
    auto ts = std::make_shared<TopicSubscriber>(sub_ptr);
    std::lock_guard<std::mutex> lck(sub_mtx);
    auto it = topic_subscribers.find(ts);
    if(it != topic_subscribers.end()){
        topic_subscribers.erase(it);
    }
}

void Topic::addMessage(Message message, boost::asio::thread_pool &thread_pool)
{
    {
        std::lock_guard<std::mutex> lck(msg_mtx);
        messages.push_back(message);
    }
    publishMessages(thread_pool);
}

void Topic::publishMessages(boost::asio::thread_pool &thread_pool)
{
    boost::asio::post(thread_pool, [this](){
        std::scoped_lock lck(sub_mtx, msg_mtx);

        for(auto it = topic_subscribers.begin(); it!= topic_subscribers.end(); it++){
            int offset = (*it)->getOffset();

            while(offset < messages.size()){
                (*it)->getSubscriber()->consumeMessage(messages[offset]);
                offset++;
                (*it)->incrementOffset();
            }
        }
    });
}
