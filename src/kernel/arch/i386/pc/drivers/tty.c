#include <kernel/tty.h>

void tty_cursorset_column(struct tty_terminal *terminal, uint32_t column)
{
  terminal->cursor_x = column * terminal->font->width;
}

void tty_cursorset_row(struct tty_terminal *terminal, uint32_t row)
{
  terminal->cursor_y = row * terminal->font->height;
}

void tty_cursorset(struct tty_terminal *terminal, uint32_t row, uint32_t column)
{
  tty_cursorset_row(terminal, row);
  tty_cursorset_column(terminal, column);
}

void tty_putchar(struct tty_terminal *terminal, uint8_t ch)
{
  vga_drawchar(terminal->screen, terminal->font, ch, terminal->cursor_x, terminal->cursor_y, terminal->color_fg, terminal->color_bg);

  // if (++terminal->cursor_x == terminal->screen->width)
  // {
  // terminal.cursor_column = 0;
  // if (++terminal.cursor_row == terminal.rows)
  //{
  //   terminal.cursor_row = 0;
  // }
  // }
}
