#ifndef  DATABASEQ_H
#define DATABASEQ_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/sqlite_daemon.sock"

typedef struct datastruct
{
	char** rows;
	char** values;
} datastruct;

int insertByUserRowVals(int argc, char* username, char** argr, char** argv);

datastruct getByUserRowsVals(int argc, char* username, char** argr);

void send_query(const char* query);

#endif
