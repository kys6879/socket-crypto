#pragma once
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <WinSock2.h>
int Init(WSADATA *wsaData);

SOCKET Create();

int Bind(SOCKET hServSock, SOCKADDR_IN servAddr);
int Listen(SOCKET hServSock);

SOCKET Accept(SOCKET hServSock, SOCKADDR_IN clntAddr);

SOCKET socket_env_ready(int port);
#endif