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
#define BUF_SIZE 100
#define NAME_SIZE 20

char msg[BUF_SIZE];
char inputName[NAME_SIZE];

unsigned WINAPI SendMsg(void* arg);
unsigned WINAPI RecvMsg(void* arg);

int main() {

	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char r_msg[30];

	uint8_t s_msg[30];
	uint8_t flag[3];

	int strLen;

	HANDLE sendThread, recvThread;

	printf("Input your name : ");
	gets(inputName);
	sprintf(inputName, "[%s]", inputName);

	
	hSocket = socket_env_ready(PORT, ADDRESS);

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSocket, 0, NULL);//�޽��� ���ۿ� �����尡 ����ȴ�.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSocket, 0, NULL);//�޽��� ���ſ� �����尡 ����ȴ�.


	closesocket(hSocket); //���� ���̺귯�� ����
	WSACleanup();

	system("pause");
	return 0;
}