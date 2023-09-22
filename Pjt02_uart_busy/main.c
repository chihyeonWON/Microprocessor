#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "uart.h"

int main()
{
   char c;
   uart_init();
   for(int i=0; i<10; i++) {
      for(c = 'A'; c <= 'Z'; c++)
	      uart_putchar(c);
		  uart_putchar('\n');
		  uart_putstr("ABCD\n");
   }
   while(1) {
   	led_on_all();
	_delay_ms(200);
	led_off_all();
   }
   return 0;
}
