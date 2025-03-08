#include "Headers/conn_thread_pool.h"
#include <iostream>

ConnThreadPool::ConnThreadPool()
{
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
    {
        num_threads = 2;
    }
    for (unsigned int i = 0; i < num_threads; i++)
    {
        conn_threads.emplace_back(&ConnThreadPool::worker, this);
    }
    enqueue_thread([this]()
                   { connection_queue.main_server_management(); });
}

ConnThreadPool::~ConnThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop_ = true;
    }
    cv.notify_all();
    for (std::thread &worker : conn_threads)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

void ConnThreadPool::enqueue_thread(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(task);
    }
    cv.notify_one();
}

void ConnThreadPool::worker()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this]
                    { return !tasks.empty() || stop_; });
            if (stop_ && tasks.empty())
                return;
            task = tasks.front();
            tasks.pop();
        }
        task();
    }
}
