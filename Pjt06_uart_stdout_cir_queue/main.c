#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "queue.h"
#include "q.h"
#include <avr/interrupt.h>

int main()
{
	uart_init();
	sei();
	app_prime(2000);
	while(1);
	return 0;	
}
