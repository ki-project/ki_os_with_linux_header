#ifndef shell_h_

#define MAX_COMMANDS 100

typedef struct {
  char *name;
  char *description;
  void *function;
} command_table_t;

extern void add_new_command();
extern void help_command();
extern void _start_ki();

#endif