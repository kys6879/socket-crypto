#include "socket.h"
#include "handler.h"
#include <WinSock2.h>

int Init(WSADATA *wsaData) {
	if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0) { // Init
		return 1;
	}
	else {
		return 0;
	}
}

SOCKET Create() {
	return socket(PF_INET, SOCK_STREAM, 0);
}

int Bind(SOCKET hServSock, SOCKADDR_IN servAddr) {

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) { // bind
		return 1;
	}
	else {
		return 0;
	}
}

int Listen(SOCKET hServSock) {
	if (listen(hServSock, 5) == SOCKET_ERROR) { // listen
		ErrorHandling("listen() error");
	}
}

SOCKET Accept(SOCKET hServSock, SOCKADDR_IN clntAddr) {
	return 	accept(hServSock, (SOCKADDR*)&clntAddr, sizeof(clntAddr));
}


SOCKET socket_env_ready(int port,HANDLE *hMutex) {
	int errCode;
	WSADATA wsaData;
	SOCKADDR_IN servAddr;
	SOCKET hServSock;
	
	errCode = Init(&wsaData);
	if (errCode) {
		ErrorHandling("InitSocket() error!");
	}

	*hMutex = CreateMutex(NULL, FALSE, NULL);



	hServSock = Create(); // Create
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("CreateSocket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	errCode = Bind(hServSock, servAddr);
	if (errCode) {
		ErrorHandling("BindSocket() error!");
	}

	errCode = Listen(hServSock);
	if (errCode) {
		ErrorHandling("ListenSocket() error!");
	}

	return hServSock;

}