#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define CLIENT

#include <stdio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <time.h>
#include <stdint.h>

#include "socket.h" 
#include "handler.h"

#define PORT 3000
#define ADDRESS "127.0.0.1"

int main() {

	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char r_msg[30];

	uint8_t s_msg[30];
	uint8_t flag[3];

	int strLen;
	
	hSocket = socket_env_ready(PORT, ADDRESS);
	//strLen = recv(hSocket, message, sizeof(message) - 1, 0);
	//if (strLen == -1)
	//	ErrorHandling("read() error");

	//printf("Message from server:%s\n", message);

	//printf("Ű ���� : y | n : "); // 121 , 110
	//gets(flag);
	//send(hSocket, flag, sizeof(flag) - 1, 0);

	printf("��ȣȭ �� ���ڿ� �Է� : ");

	gets(s_msg);

	send(hSocket, s_msg, sizeof(s_msg)-1, 0);

	closesocket(hSocket); //���� ���̺귯�� ����
	WSACleanup();

	system("pause");
	return 0;
}