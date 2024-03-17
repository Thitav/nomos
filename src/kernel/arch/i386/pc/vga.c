#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static struct vga_terminal terminal;

void vga_init(void)
{
  terminal.row = 0;
  terminal.column = 0;
  terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal.buffer = VGA_MEMORY;
  for (size_t y = 0; y < VGA_HEIGHT; y++)
  {
    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
      const size_t index = y * VGA_WIDTH + x;
      terminal.buffer[index] = vga_entry(' ', terminal.color);
    }
  }
}

void vga_setcolor(uint8_t color)
{
  terminal.color = color;
}

void vga_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal.buffer[index] = vga_entry(c, color);
}

void vga_putchar(char c)
{
  unsigned char uc = c;
  vga_putentryat(uc, terminal.color, terminal.column, terminal.row);
  if (++terminal.column == VGA_WIDTH)
  {
    terminal.column = 0;
    if (++terminal.row == VGA_HEIGHT)
      terminal.row = 0;
  }
}

void vga_write(const char *data, size_t size)
{
  for (size_t i = 0; i < size; i++)
    vga_putchar(data[i]);
}

void vga_writestring(const char *data)
{
  vga_write(data, strlen(data));
}
