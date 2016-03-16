#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>

extern void initTasking();
extern void createTask(Task*, void(*)(), uint32_t, uint32_t*);

extern void preempt();
// Switch task frontend
extern void switchTask(Registers *old, Registers *new);
// The function which actually switches

#endif /* __TASK_H__ */