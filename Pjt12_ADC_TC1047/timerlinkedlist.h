#include <stdlib.h>
#define MAX_TASK 16

struct task {
	void (*fun)(char *);
	char arg[8];
};

struct task Task_q[MAX_TASK];
volatile int Task_f, Task_r;

struct timer {
	int time;
	struct task task;
	struct timer *link;
};

struct timer *get_timer();

extern struct timer *Thead;
struct timer *get_timer();

void insert_timer(struct task *tskp, int ms);
void tour_timer(), free_timer();


