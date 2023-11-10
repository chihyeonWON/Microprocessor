#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "interrupt.h"
#include "queue.h"
#include "linkedlist.h"

int uart_putchar(char ch, FILE *stream), uart_getchar(FILE* stream);

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void uart_init()
{
	stdout = &Mystdout;
	stdin = &Mystdin;
	uart_busy = 0; // false
	q_init();
	UBRR0H = 0x00;
	UBRR0L = 0x07; // 115.2KBPS
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0); // RX enable
	sbi(UCSR0B, RXCIE0);
}

int uart_putchar(char ch, FILE *stream)
{
	if(ch == '\n')
		uart_putchar('\r', stream);
	
	cli();

	if(!uart_busy)
	{
		UDR0 = ch;
		uart_busy = 1;
	}
	else
	{
		while(qo_insert(ch) == 0)
		{
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();

	return 1;
}

int uart_getchar(FILE *stream)
{
	char ch;

	do
	{
		cli();
		ch = qi_delete();
		sei();
	}while(ch == 0);

	if(ch == EOT)
		return -1;
	else
		return ch;

	if(ch == BS)
		ch = ch-1;
		return ch;
}

void uart_echo(char ch)
{
	if(ch == '\n')
		uart_echo('\r');
	if(!uart_busy)
	{
		UDR0 = ch;
		uart_busy = 1;
	}
	else
		qo_insert(ch);
}

int qi_peek()
{
	if(fi == ri)
		return 0;
	else
		return(qi[(fi + 1) % QI_SIZE]);
}

int uart_peek()
{
	return(qi_peek());
}
