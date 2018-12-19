#include "handler.h"
#include <stdio.h>

void ErrorHandling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	system("pause");
	exit(1);
}

