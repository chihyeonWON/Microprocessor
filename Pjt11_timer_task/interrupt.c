#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interrupt.h"
#include "uart.h"
#include "timerlinkedlist.h"
#include "queue.h"
#include "task.h"
#include "timer.h"
#define ESC 0x1B

void task_cmd(char *arg);
static int echo_mode = 1;

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
	struct task task;
	char ch;

	ch = UDR0;

	if(ch == ESC) {
		echo_mode = (echo_mode +1) & 0x01;
		return;
	}

	if(ch != EOT)
	{
		if(ch == '\r')	ch = '\n';
		if(echo_mode) uart_echo(ch);
	}
	qi_insert(ch);
	if(ch == EOT || ch == '\n') {
		task.fun = task_cmd;
		strcpy(task.arg, "");
		task_insert(&task);
	}
}

ISR(TIMER2_OVF_vect)
{
	if(!Thead)
		return;
	if(--Thead->time == 0)
		timer_expire();
}
