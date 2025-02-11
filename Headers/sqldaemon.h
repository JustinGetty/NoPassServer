#ifndef SQLDAEMON_H
#define SQLDAEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/sqlite_daemon.sock"

void init_db();
void handle_insert_query(const char* sql, int client_sock);
void handle_get_query(const char* sql, int client_sock);
void start_server();





#endif
