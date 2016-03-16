#include <sys/types.h>

#ifndef task_h_
#define task_h_

typedef struct Task {
  number_t nr;
  path_t path;
  register_t regs;
  struct task_t *next;
} task_t;

#endif task_h_