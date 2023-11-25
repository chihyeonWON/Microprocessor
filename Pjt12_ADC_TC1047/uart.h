#include <stdio.h>
#define EOT 0x04
#define ESC 0x1B
#define BS 0x08
void uart_init();
int uart_putchar(char ch, FILE *stream);
int uart_getchar(FILE* stream);
void uart_echo(char ch);
char uart_busy;
int qi_peek();
int uart_peek();
