#include <App.h>
#include <iostream>
#include "/infinite/Projects/NoPass/Server/NoPassServer/Headers/connection_data_queue.h"

#define EMPTY_USERNAME "NOTSET"

/*
 TODO

 - setup proxy to load balance event loop threads - single port delegates to other open ports
 - increase ulimit -n (file descriptor limit)
 - adjust net.core.somaxconn for maximum connections
 - set fs.file-max for max open files
 - thread pool to handle connections

 Avoid Threads Plan:
 - Client site to websocket connection, connection managed by uWebSockets
 - Websocket data stored, request to data daemon made and websock to phone made via uWebSocket
 - Keep both ws connections in data structure, note not signed in yet, unique id.
 - When user approves, update data structure to "ready to approve", send approval to client site
 - No threads

 */

struct WebSocketBehavior
{
    static void open(uWS::WebSocket<false, true, int> *ws)
    {
        // getUserData() returns empty memory space for particular conn data
        // fix cast here
        ConnectionData *connData = (ConnectionData *)ws->getUserData();
        connData->username = EMPTY_USERNAME;
        connData->connection_id = -1;
        std::cout << "Client connected!" << std::endl;
    }

    // for inbound message
    // first false is for ssl - false = no ssl
    static void message(uWS::WebSocket<false, true, int> *ws, std::string_view message, uWS::OpCode opCode)
    {
        std::cout << "Received: " << message << std::endl;
        ws->send(message, opCode);
    }

    static void close(uWS::WebSocket<false, true, int> *ws, int code, std::string_view message)
    {
        std::cout << "Client disconnected!" << std::endl;
    }
};

int main()
{
    uWS::App app;

    // Attach WebSocket route
    // equivalant to app.open = XX, app.close = XX
    app.ws<int>("/*", {.open = &WebSocketBehavior::open,
                       .message = &WebSocketBehavior::message,
                       .close = &WebSocketBehavior::close});

    // lambda taking no parameters, token points to listening socket
    app.listen(8443, [](auto *token)
               {
        if (token) {
            std::cout << "Server is running on port 8443" << std::endl;
        } else {
            std::cerr << "Failed to start server" << std::endl;
        } });

    // event loop
    app.run();
    return 0;
}
