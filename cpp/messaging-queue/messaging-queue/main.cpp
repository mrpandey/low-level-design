#include <memory>
#include <chrono>

#include "Queue.h"
#include "Topic.h"
#include "Subscriber.h"
#include "Message.h"

int main(){
    Queue msg_queue;
    
    auto t1 = msg_queue.createTopic("topic 1");
    auto t2 = msg_queue.createTopic("topic 2");
    
    auto s1 = std::make_shared<Subscriber>("sub1");
    auto s2 = std::make_shared<Subscriber>("sub2");
    auto s3 = std::make_shared<Subscriber>("sub3");
    auto s4 = std::make_shared<Subscriber>("sub4");

    // msg_queue.subscribe(t1, s1);
    msg_queue.subscribe(t1, s2);
    // msg_queue.subscribe(t1, s3);

    msg_queue.subscribe(t2, s2);
    // msg_queue.subscribe(t2, s3);

    Message m1("message 1"), m2("message 2"), m3("message 3");

    msg_queue.publish(t1, m1);
    msg_queue.publish(t2, m2);
    // msg_queue.publish(t1, m3);
}