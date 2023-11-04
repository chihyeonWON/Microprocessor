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



int main()
{
	char cmd[128], *cp, *ap;
	int n = 0;

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
		else printf("Unknown commamnd...\n");
	}

	printf("logout, good bye !!!\n");

	while(1);

	return 0;
}
