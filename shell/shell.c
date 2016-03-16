#include "shell.h"

void init_shell() {
  add_new_command("help", "Shell Help.", help_command);
  add_new_command("_start_ki", "KI Start", _start_ki);
}

void help_command () {
  puts("Shell (for kiOS) v0.1\n");
  puts("Enter _start_ki to start the ai.\n");
  return;
}

command_table_t CommandTable[MAX_COMMANDS];

void add_new_command(char *name, char* description, void *function) {
  if(NumberOfCommands + 1 < MAX_COMMANDS) {
    NumberOfCommands++; 
    CommandTable[NumberOfCommands].name = name;
    CommandTable[NumberOfCommands].description = description;
    CommandTable[NumberOfCommands].function = function;
  }
  return;
}

void shell() {
  puts("\nMy_Prompt>");
  gets(input_string);
  int i = findCommand(input_string);
  if(i >= 0) {
    command_function = CommandTable[i].function command_function();
  } else {
    return;
  }
  return;
  void (*command_run)(void);
}

int findCommand(char* command) {
  int i;
  int ret;
  
  for(i = 0; i < NumberOfCommands + 1; i++) {
    ret = strcmp(command, CommandTable[i].name);
    if(ret == 0) return i;
    else return -1;
  }
}