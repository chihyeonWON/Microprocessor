#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "queue.h"
#include "q.h"
#include <avr/interrupt.h>

int main()
{
	char cmd[128], ch;
	int n = 0;
	uart_init();
	sei();
	printf("$ ");
	while(1) {
		cli();
		ch = qi_delete();
		sei();
		if(ch) { 
			if(ch == '\r') continue;
			if(ch == '\n') {
				cmd[n] = 0;
				int num = cmd[3];
				if(num <= 10 && num >=0) {
					if(num == 0) app_prime(2000);
				} else app_prime(cmd[3] * 100);
				n = 0;
				printf("$ ");
			}
			else 
				cmd[n++] = ch;
		}	
	}
	return 0;	
}
