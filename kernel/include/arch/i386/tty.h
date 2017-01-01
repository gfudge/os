#ifndef _TTY_H
#define _TTY_H

#include <kernel/ktypes.h>

// VGA Colors
typedef enum vga_color_e
{
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
} vga_color;

// TTY Terminal Methods
void tty_init(void);
void tty_putchar(const k_char_t c);
void tty_write(const k_char_t* data, k_size_t size);
void tty_writestr(const k_char_t* data);
void tty_writestr_color(const k_char_t* data, vga_color color);
void tty_newline();

#endif /* _TTY_H */
