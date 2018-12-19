#include <stdio.h>
#include <WinSock2.h>
#define PORT 3000

int main() {

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	int i;
	char send_message[] = "i am server!";
	char recive_message[30];

	printf("PORT : %d\n", PORT);


	return 0;
}