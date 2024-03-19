#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>
#include "font/font.h"
#include "vga.h"

struct tty_terminal
{
  uint8_t color_fg, color_bg;
  uint32_t cursor_x, cursor_y;
  const struct vga_screen *screen;
  const struct bitmap_font *font;
};

void tty_setcursor(struct tty_terminal *terminal, uint32_t row, uint32_t column);
void tty_putchar(struct tty_terminal *terminal, uint8_t ch);

#endif
