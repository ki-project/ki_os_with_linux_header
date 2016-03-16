#include "kinit.h"
#include "term_opts.c"
#include <sys/types.h>
#include <sys/timer.h>
#include <asm/io.h>
#include "pic_setup.c"
#include <printk.c>
#include "../kernel/init.c"
#include <asm/descriptor_tables.h>

#if defined(__cplusplus)
extern "C"
  /* Use C linkage for kernel_main. */ 
#endif

void kernel_init(struct multiboot *mboot_ptr) { 
  
  //Reprogram PICs
  cli();
  init_pics(0x20, 0x28);
  sti();
  
  //Initialize Terminal
  terminal_initialize();
  
  kinfo("Enable A20 Gate (if not already done)\n");
  //Enable A20 Gate if it is not already enabled.
  if (checkA20() = 0)
    enableA20();
  
  //Check if A20 is REALLY enabled
  if (checkA20() = 0)
    panic("Enabling A20 Gate");
  
  //Enable the timer and setting it to 50hz
  kinfo("Enable Timer (50hz)");
  init_timer(50);
  
  //Initiate the descriptor tables (gdt and idt)
  init_descriptor_tables();
  
  //Enter the protected mode
  kinfo("Enter protected mode");
  enterProtected();
  
  //Spawning the init process with argument *mboot_ptr
  kinfo("Spawning Init process...");
  init(*mboot_ptr);
  
  //The init process should NEVER die.
  //If it dies
  kerror("Init Process terminated... make a kernel panic...");
  panic("Unendable Process ended.");
}