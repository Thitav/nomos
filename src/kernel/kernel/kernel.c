#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/font/univga.h>

void kernel_main(void)
{
  struct vga_screen screen = {320, 200};
  struct tty_terminal terminal = {VGA_COLOR_WHITE, VGA_COLOR_BLACK, 0, 0, &screen, &font_univga};

  // for (uint32_t y = 0; y < screen.height; y++)
  //   for (uint32_t x = 0; x < screen.width; x++)
  //     vga_putpixel(&screen, x, y, VGA_COLOR_RED);

  tty_setcursor(&terminal, 10, 0);

  char s[] = "Hello World!";
  for (uint32_t i = 0; i < strlen(s); i++)
  {
    tty_putchar(&terminal, s[i]);
    tty_setcursor(&terminal, 10, i + 1);
  }
}
