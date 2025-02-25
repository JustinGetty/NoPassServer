#ifndef  DATABASEQ_H
#define DATABASEQ_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define GET_SOCKET_PATH "/tmp/sqlite_GET_daemon.sock"
#define POST_SOCKET_PATH "/tmp/sqlite_POST_daemon.sock"

typedef struct datastruct
{
	char** rows;
	char** values;
} datastruct;

int insertByUserRowVals(int argc, char* username, char** argr, char** argv);

datastruct getByUserRowsVals(int argc, char* username, char** argr);

void send_get_query(const char* query);

void send_post_query(const char* query);

#endif
