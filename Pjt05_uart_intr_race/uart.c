#include <avr/io.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include <stdio.h>
#include <string.h>


char buf[64];
int volatile bufi, txend=1;

void uart_init()
{
	UBRR0H = 0x00; UBRR0L = 0x07;
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << TXCIE0);
}


void uart_putstart(char str[])
{
	char ch; int n = strlen(str);
	while(sizeof(buf) - strlen(buf + bufi) - 1 < n);
	cli();
	strcpy(buf, buf + bufi); strcat(buf, str); 
	bufi = 0;
	if(txend) {
		txend = 0; ch = buf[bufi++];
		UDR0 = ch;
	}
	sei();
}


ISR(USART0_TX_vect)
{
	char ch = buf[bufi];
	if(!ch) {
		bufi = buf[0] = 0;
		txend = 1; 
		return;
	}
	if(ch == '\n') buf[bufi] = '\r';
	else bufi++;
	UDR0 = ch;
}

