#include "/infinite/Projects/NoPass/Server/NoPassServer/Headers/sqldaemon.h"

sqlite3* db;


//more error handling here
void init_db() {
	if (sqlite3_open("database.db". &db) != SQLITE_OK) {
		printf("Failed to open database: %s\n", sqlite3_errmsg(db));
		exit(1);
	}
}

//send back success or error, send 0/-1
void handle_insert_query(const char* sql_statement, int client_sock) {
	char* errMsg = NULL;

	if (sqlite3_exec(db, sql_statement, NULL, NULL, &errMsg) != SQL_OK) {
		int err = -1;
		send(client_sock, &err, sizeof(int), 0);
		sqlite3_free(errMsg);
	} else {
		printf("Query executed successfully\n");
		//check this may send char instead of int
		int success = 0;
		send(client_sock, &success, sizeof(int), 0);
	}
}

void start_server() {
	int server_fd, client_sock;
	struct sockaddr_un address;
	char buffer[1024];
	
	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;
	strcpy(address.sunpath, SOCKET_PATH);
	
	unlink(SOCKET_PATH);
	bind(server_fd, (struct sockaddr*)&address, sizeof(address));
	listen(server_fd, 5);

	printf("SQLite daemon running on UNIX sock: %s\n", SOCKET_PATH);

	while (1) {
		client_sock = accept(server_fd, NULL, NULL);
		
		//need to receive/handle diff types for post/get. could even be seperate daemons, or buff meta data
		read(client_sock, buffer, 1024);
		handle_insert_query(buffer, client_sock);


		close(client_sock);
	}	
}


int main() {
	init_db();
	start_server();
	sqlite3_close(db);
	return 0
}
