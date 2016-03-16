#include <asm/gdt.h>
#include <asm/idt.h>

#ifndef descriptor_tables_h_
#define descriptor_tables_h_

void init_descriptor_tables()
{
  init_gdt();
  init_idt();
}

#endif //descriptor_tables_h_