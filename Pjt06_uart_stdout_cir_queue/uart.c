#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>

void uart_putchar(char ch, FILE *stream)
{
	if(ch == '\n')
		uart_putchar('\r', stream);
	cli();

	if(!uart_busy) {
		UDR0 = ch;
		uart_busy = 1;
	}
	else {
		while(q_insert(ch) == 0) {
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();

	return(1);
}

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


char uart_busy;

void uart_init()
{
	stdout = &Mystdout;
	uart_busy = 0;
	q_init();
	UBRR0H = 0x00; UBRR0L = 0x07;
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << TXCIE0);
}


ISR(USART0_TX_vect)
{
	char ch;

	if((ch = q_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}

