#include <sys/types.h>
#include <asm/lowlevel.h>
#include <printk.c>

#ifndef panic_h_
#define panic_h_

volatile void panic(const char* data) {
  exitProtected();
  terminal_writestring(KERN_PANIC data);
  clint();
  for(;;);
}

#define PANIC(var) panic(var)

#endif