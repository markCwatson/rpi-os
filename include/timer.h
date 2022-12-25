#ifndef	_TIMER_H
#define	_TIMER_H

void timer_init(unsigned int id, unsigned int interval);
void timer_cancel(unsigned int id);
void timer_irq_handler(unsigned int type);

#endif