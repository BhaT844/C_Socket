#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <sys/types.h>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4996)

#define BUFF_SIZE 1024

int main(int argc, char **argv)
{
	int client_socket;

	struct sockaddr_in server_addr;

	char buff[BUFF_SIZE + 5];

	if (argc < 2)
	{
		printf("사용법: %s (messege)", argv[0]);
		exit(1);
	}

	WSADATA wsaData = { 0 };

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == -1)
	{
		printf("socket 생성 실패\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("접속 실패\n");
		exit(1);
	}

	send(client_socket, argv[1], strlen(argv[1]) + 1, 0);

	recv(client_socket, buff, BUFF_SIZE, 0);
	printf("%s\n", buff);
	closesocket(client_socket);

	return 0;
}