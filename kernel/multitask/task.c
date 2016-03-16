#include "task.h"
#include <sys/task.h>
#include <printk.c>

static Task *runningTask;
static Task mainTask;
static Task otherTask;

static void otherMain() {
  printk("Task B"); // Not implemented here...
  preempt();
}

void initTasking()
{
  // Get EFLAGS and CR3
  asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(mainTask.register_t.cr3)::"%eax");
  
  asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(mainTask.register_t.eflags)::"%eax");
  
  createTask(&otherTask, otherMain, mainTask.register_t.eflags, (uint32_t*)mainTask.register_t.cr3);
  mainTask.next = &otherTask;
  otherTask.next = &mainTask;
  
  runningTask = &mainTask;
}

void createTask(task_t *task, void (*main)(), uint32_t flags, uint32_t *pagedir)
{
  task->register_t.eax = 0;
  task->register_t.ebx = 0;
  task->register_t.ecx = 0;
  task->register_t.edx = 0;
  task->register_t.esi = 0;
  task->register_t.edi = 0;
  task->register_t.eflags = flags;
  task->register_t.eip = (uint32_t) main;
  task->register_t.cr3 = (uint32_t) pagedir;
  task->register_t.esp = (uint32_t) allocPage() + 0x1000;
  // Not implemented here
  task->next = 0;
}

void preempt()
{
  task_t *last = runningTask;
  runningTask = runningTask->next;
  switchTask(&last->register_t, &runningTask->register_t);
}