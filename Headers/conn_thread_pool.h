#ifndef CONN_THREAD_POOL_H
#define CONN_THREAD_POOL_H

#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>
#include "connection_data_queue.h" // If you need access to the connection queue

class ConnThreadPool
{
private:
    std::vector<std::thread> conn_threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop_ = false;

    ConnectionQueue connection_queue;

    void worker();

public:
    ConnThreadPool();
    ~ConnThreadPool();

    // Add a new task to the thread pool.
    void enqueue_thread(std::function<void()> task);
};

#endif // CONN_THREAD_POOL_H
