#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadPool
{
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
    std::mutex mtx;
    std::condition_variable cv;

public:
    ThreadPool();
    int getSize() const;
    void push(std::function<void()>);
    void start();
    void stop();
};