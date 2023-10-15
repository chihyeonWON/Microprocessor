#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "q.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#define E0T 0x04 // ^D: End of Text

int uart_putchar(char ch, FILE *stream);

int uart_getchar(FILE *stream)
{
	char ch;

	do {
		cli();
		ch = qi_delete();
		sei();
	} while(ch == 0);

	if(ch == E0T) return(-1);
	else return(ch);
}

int uart_putchar(char ch, FILE *stream)
{
	if(ch == '\n')
		uart_putchar('\r', stream);
	cli();

	if(!uart_busy) {
		UDR0 = ch;
		uart_busy = 1;
	}
	else {
		while(qo_insert(ch) == 0) {
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();

	return(1);
}

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);


char uart_busy;

void uart_init()
{
	stdin = &Mystdin;
	stdout = &Mystdout;
	q_init();
	uart_busy = 0;

	UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
}

void uart_echo(char ch)
{
	if(ch == '\n') uart_echo('\r');
	if(!uart_busy) {
		UDR0 = ch;
		uart_busy = 1;
	}
	else 
		qo_insert(ch);
}


ISR(USART0_TX_vect)
{
	char ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}

ISR(USART0_RX_vect)
{
	char ch;

	ch = UDR0;
	if(ch != E0T) {
		if(ch == '\r') ch = '\n';
		uart_echo(ch);
	}
	qi_insert(ch);
}


