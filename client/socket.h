#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
SOCKET socket_env_ready(int port , char *address);
void clear_socket(SOCKET *hSocket);