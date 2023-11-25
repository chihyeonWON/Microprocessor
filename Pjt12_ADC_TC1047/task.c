#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "timerlinkedlist.h"
#include "app.h"
#include "uart.h"
#include "adc.h"

void task_init()
{
	Task_f = Task_r = 0;
}

int task_insert(struct task *tskp)
{
	if((Task_r + 1) % MAX_TASK == Task_f)
		return(0);
	Task_r = (Task_r + 1) % MAX_TASK;
	Task_q[Task_r] = *tskp;
	return(1);
}

int task_delete(struct task *tskp)
{
	if(Task_r == Task_f)
		return(0);
	Task_f = (Task_f + 1) % MAX_TASK;
	*tskp = Task_q[Task_f];
	return(1);
}

void task_cmd(char *arg)
{
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	int ms;

	if(!uart_peek()) return;

	if(gets(buf) == NULL) {
		printf("logout, good bye !!!\n");
		while(1);
	}

	cp0 = strtok(buf, " \t\n\r");
	cp1 = strtok(NULL, " \t\n\r");
	cp2 = strtok(NULL, " \t\n\r");
	cp3 = strtok(NULL, " \t\n\r");

	if(cp0 == NULL) {
		// printf("!!!-111\n");
		printf( "$ "); return;
	}

	if(!strcmp(cp0, "prime"))
		task_prime(cp1);
	else if(!strcmp(cp0, "timer")) {
		if(cp1 == NULL) {
			printf("!!!-222\n");
			printf("$ ");
			return;
		}
		ms = atoi(cp1)/256;
		if(!strcmp(cp2, "prime")) {
			task.fun = task_prime;
			if(cp3) strcpy(task.arg, cp3);
			else strcpy(task.arg, "");
			cli();
			insert_timer(&task, ms);
			sei();
		}
		else printf("!!!-333\n"); 
	} else if(!strcmp(cp0, "tc1047")) {
		task_tc1047("");
	}
	else printf("Unknown command...\n");

	printf("$ ");
}
	
void task_tc1047(char *arg)
{
	static int value;
	static int volatile in_adc = 0;

	if(!strcmp(arg, "")) {
		adc_start(); in_adc = 1; while(in_adc);
		printf("Current temperature is %d degree.\n", value);
	}
	else {
		value = atoi(arg) * (1.1/1023) * 1000;
		value = (value - 500) / 10;
		in_adc = 0;
	}
}






