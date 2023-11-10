#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "task.h"
#include "timer.h"
#include "timerlinkedlist.h"
#include "uart.h"
#include "interrupt.h"
#include "queue.h"
#include "linkedlist.h"

void timer_init() {
	TCNT2 = 0;
	sbi(ASSR, AS2);
	sbi(TIMSK2, TOIE2);
	sbi(TCCR2B, CS20); 
	sbi(TCCR2B, CS21);
}


void timer_expire(void)
{
	struct timer *tp;

	for( ; Thead != NULL && !Thead->time; ) {
		tp = Thead, Thead = tp->link;
		
		task_insert(&tp->task);
		
		free(tp);
	}
} 
