#include "kinit.h"

#define KERN_INFO "[INFO]"
#define KERN_PANIC "[PANIC]"

void terminal_initialize() { 
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) { 
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = make_vgaentry(' ', terminal_color);
    }
  } 
}

void terminal_setcolor(uint8_t color) {
  terminal_color = color; 
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) { 
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
      terminal_row = 0; 
    }
  }
}

void terminal_writestring(const char* data) {
  size_t datalen = strlen(data);
  for (size_t i = 0; i < datalen; i++)
    terminal_putchar(data[i]);
}

void printk(const char* data) {
  terminal_writestring(data);
}

void kinfo(const char* data) {
  terminal_writestring(KERN_INFO data);
}

volatile void panic(const char* data) {
  exitProtected();
  terminal_writestring(KERN_PANIC data);
  clint();
  for(;;);
}