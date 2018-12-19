#define _CRT_SECURE_NO_WARNINGS

#include "log.h"
#include <time.h>
#include <stdio.h>

void printCurrentTime() {
	struct tm *date;
	const time_t t = time(NULL);
	date = localtime(&t);

	printf("%d/%d/%d %d:%d:%d\n", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec);

}

