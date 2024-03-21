#include <kernel/tty.h>

void tty_putchar(struct tty_terminal *terminal, char ch)
{
  if (ch == '\n')
  {
    terminal->cursor_x = 0;
    terminal->cursor_y += terminal->font->height;
    return;
  }

  vga_drawchar(terminal->screen, terminal->font, ch, terminal->cursor_x, terminal->cursor_y, terminal->color_fg, terminal->color_bg);
  terminal->cursor_x += terminal->font->width;

  if (terminal->cursor_x >= terminal->screen->width)
  {
    terminal->cursor_x = 0;
    terminal->cursor_y += terminal->font->height;
    if (terminal->cursor_y >= terminal->screen->height)
    {
      // Implement terminal scroll
      terminal->cursor_y = terminal->font->height;
    }
  }
}

void tty_write(struct tty_terminal *terminal, const char *data, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    tty_putchar(terminal, data[i]);
  }
}

void tty_writestr(struct tty_terminal *terminal, const char *str)
{
  tty_write(terminal, str, strlen(str));
}
