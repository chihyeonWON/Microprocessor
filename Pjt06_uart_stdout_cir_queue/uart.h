#include <stdio.h>
FILE Mystdout;
char uart_busy;
void uart_init();
void uart_putchar(char ch, FILE *stream);
