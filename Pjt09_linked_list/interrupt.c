#include <avr/interrupt.h>
#include "interrupt.h"
#include "uart.h"

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
	if(ch != EOT)
	{
		if(ch == '\r')
			ch = '\n';
		uart_echo(ch);
	}


	qi_insert(ch);
}
