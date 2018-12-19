#include "socket.h"
#include "handler.h"
#include <WinSock2.h>
#include <stdio.h>

SOCKET socket_env_ready(int port, char *address) {
	SOCKET hSocket;

	WSADATA wsaData;
	SOCKADDR_IN servAddr;
	printf("PORT : %d\nADDRESS : %s\n", port, address);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Init
		ErrorHandling("WSAStartup() error!");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0); // Create
	if (hSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(address);
	servAddr.sin_port = htons(port);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("connect() error!");
	}

	return hSocket;

}
