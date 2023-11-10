#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"
#include "app.h"
#include "queue.h"
#include "linkedlist.h"
#include "timerlinkedlist.h"


int main()
{
	char cmd[128], *cp, *ap, *fp, *rp;
	int n = 0;
	int a, b, c;
	char front[100], rear[100];
	int x, y;
	char k;

	char *sp = "123*456";

	scanf(sp, "%d%c%d", &x, &k, &y);

	uart_init();	
	sei();

	while(1)
	{
		printf("$ ");

		if(fgets(cmd, sizeof(cmd), stdin)== NULL)
			break;
		if((cp = strtok(cmd, "\n\r\t ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t ");
		if(!strcmp(cmd,"prime")) app_prime(ap);
		else if(!strcmp(cp, "list")) app_list(ap);
		else if(!strcmp(cp, "timer")) app_timer(ap);
		else if(!strcmp(cp, "cal")) {
			app_cal(ap);
		}
		else printf("Unknown commamnd...\n");


	}

	printf("logout, good bye !!!\n");

	while(1);

	return 0;
}
