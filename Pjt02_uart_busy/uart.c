#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>

void uart_init()
{
   UBRR0H = 0x00; // 115.2KBPS
   UBRR0L = 0x07; // 115.2KBPS
   sbi(UCSR0A, U2X0); // TX enable
   sbi(UCSR0B, TXEN0);
}

void uart_putchar(char ch)
{
   if(ch == '\n') {
   		uart_putchar('\r');
	}
   _delay_ms(100);
   UDR0 = ch;
}

void uart_putstr(char *sp)
{
	for( ; *sp; sp++)
		uart_putchar(*sp);
}
