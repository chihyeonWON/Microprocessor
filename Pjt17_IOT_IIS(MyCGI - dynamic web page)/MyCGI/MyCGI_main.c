#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include "MyCGI_web.h"

int main()
{
	char data[64];

	time_t t = time(&t);
	char *tp = ctime(&t);

	//printf("%s\n", tp);

	MyCGI_web(tp);

	//sprintf_s(data, 64, "Current temperature is 10 degree.");
	//MyCGI_web(data);

	return 0;
}