#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "interrupt.h"
#include "linkedlist.h"
#include "queue.h"
#include "task.h"
#include "timer.h"
#include "timerlinkedlist.h"
#include "uart.h"



int main()
{
	int tag;
	struct task task;

	uart_init();
	task_init();
	timer_init();

	printf("$ ");

	while(1) {
		cli();
			tag = task_delete(&task);
			sei();
			if(tag)
				(*(task.fun))(task.arg);
	}
	return(0);
}
