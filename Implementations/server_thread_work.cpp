#include <iostream>
#include "Headers/connection_data_queue.h"

void ConnectionQueue::main_server_management()
{
    while (true)
    {
        ConnectionData data;
        {
            std::unique_lock<std::mutex> lock(conn_mutex);
            if (isEmpty())
            {
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            // get connection data
            data = dequeue();
        }
        processConnectionData(data);
    }
}

void processConnectionData(ConnectionData data)
{
    return;
}
