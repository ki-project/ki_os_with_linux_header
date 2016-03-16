#if !defined(__cplusplus) 
#include <stdbool.h>
/* C doesn't have booleans by default. */ 
#endif
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <strlen.c>

#ifndef kinit_h_
#define kinit_h_

extern int enableA20();
extern int checkA20();
extern void enterProtected();
extern void exitProtected();
extern void clint();

/* Hardware text mode color constants. */
enum vga_color { 
  COLOR_BLACK = 0,
  COLOR_BLUE = 1,
  COLOR_GREEN = 2,
  COLOR_CYAN = 3, 
  COLOR_RED = 4, 
  COLOR_MAGENTA = 5,
  COLOR_BROWN = 6,
  COLOR_LIGHT_GREY = 7,
  COLOR_DARK_GREY = 8,
  COLOR_LIGHT_BLUE = 9,
  COLOR_LIGHT_GREEN = 10,
  COLOR_LIGHT_CYAN = 11,
  COLOR_LIGHT_RED = 12,
  COLOR_LIGHT_MAGENTA = 13, 
  COLOR_LIGHT_BROWN = 14, 
  COLOR_WHITE = 15, 
};

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4; 
}

uint16_t make_vgaentry(char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color; 
  return c16 | color16 << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

#endif // kinit_h_