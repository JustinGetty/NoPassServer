#include <App.h>

typedef struct
{
    std::string username;
    int connection_id;
    uWS::WebSocket<false, true, int> *ws;
} ConnectionData;