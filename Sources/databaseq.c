#include "/infinite/Projects/NoPass/Server/NoPassServer/Headers/databaseq.h"

void send_query(const char* query) {
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un server_addr;

	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, SOCKET_PATH);

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Connection failed\n");
		exit(1);
	}

	send(sock, query, strlen(query), 0);
	/*
	char response[1024];
	read(sock, response, sizeof(response));
	printf("Response: %s\n", response);
	*/

	close(sock);
}

int main() {
	send_query("Hello World!");
	return 0;
}
