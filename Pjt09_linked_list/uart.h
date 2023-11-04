#include <stdio.h>
#define EOT 0x04
#define BS 0x08
void uart_init();
int uart_putchar(char ch, FILE *stream);
int uart_getchar(FILE* stream);
void uart_echo(char ch);
char uart_busy;
