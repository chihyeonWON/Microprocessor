#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <avr/interrupt.h>

int main()
{
	int i;
	uart_init();
	sei();
	txend = 0;
	for(i=0; i < 10; i++) {
		uart_putstart("I love you.\n");
			while(!txend); txend = 0;
		uart_putstart("You love me.\n");
			while(!txend); txend = 0;
		uart_putstart("He loves her.\n");
			while(!txend);
	}
	uart_putstart("End !!!\n");
	while(1); return 0;
}
