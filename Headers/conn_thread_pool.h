#ifndef CONN_THREAD_POOL_H
#define CONN_THREAD_POOL_H

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <condition_variable>
#include <functional>

class ConnThreadPool
{
private:
    std::vector<std::thread> conn_threads;
    std::condition_variable cv;
    bool stop_ = false;

public:
};

#endif