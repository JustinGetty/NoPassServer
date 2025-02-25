#include "/infinite/Projects/NoPass/Server/NoPassServer/Headers/databaseq.h"

void send_get_query(const char* query) {
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un server_addr;

	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, GET_SOCKET_PATH);

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Connection failed\n");
		exit(1);
	}

	send(sock, query, strlen(query), 0);

	//read back data here, prob convert to JSON
	/*
	char response[1024];
	read(sock, response, sizeof(response));
	printf("Response: %s\n", response);
	*/

	close(sock);
}

void send_post_query(const char* query) {
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un server_addr;

	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, POST_SOCKET_PATH);

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Connection failed\n");
		exit(1);
	}

	send(sock, query, strlen(query), 0);

	//read back status here
	/*
	char response[1024];
	read(sock, response, sizeof(response));
	printf("Response: %s\n", response);
	*/

	close(sock);
}

int main() {
	char *query = malloc(sizeof(char) * 20);
	while (1){
		printf(">>>");
		if(fgets(query, 25, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		query[strcspn(query, "\n")] = '\0';

		send_query(query);
	}
	return 0;
}
