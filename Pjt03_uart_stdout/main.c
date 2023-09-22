#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "uart.h"
#include "app-prime.h"

int main()
{
   int i;

   uart_init();
   for(i=3; i<=2000; i++) {
   	if(is_prime(i)) { printf("%d is a prime number !!\n", i); led_on_all(); }
	else	{ printf("%d is not a prime number !!!\n", i); led_off_all(); }
   }
   printf("The end !!!\n");
   while(1); // must not return !!!
   return 0;
}
