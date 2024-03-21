#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/font/font.h>
#include <kernel/vga.h>

struct tty_terminal
{
  uint8_t color_fg, color_bg;
  uint32_t cursor_x, cursor_y;
  const struct vga_screen *screen;
  const struct bitmap_font *font;
};

void tty_putchar(struct tty_terminal *terminal, char ch);
void tty_write(struct tty_terminal *terminal, const char *data, size_t size);
void tty_writestr(struct tty_terminal *terminal, const char *str);

#endif
