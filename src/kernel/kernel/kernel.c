#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/paging.h>
#include <kernel/font.h>
#include <kernel/multiboot.h>

void kernel_main(uint32_t mb_magic, multiboot_info_t *mb_info)
{
  if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    // Should be kernel panic
    return;
  }

  page_directory_t identity_page_directory;
  page_table_t identity_page_table;

  for (uint16_t i = 0; i < 1024; i++)
  {
    identity_page_directory[i] = 0b00000010;
    identity_page_table[i] = (i * 0x1000) | 3;
  }
  identity_page_directory[0] = ((uint32_t)identity_page_table) | 3;

  page_directory_load(identity_page_directory);
  paging_enable();

  struct vga_screen screen = {.width = 320, .height = 200};
  struct tty_terminal terminal = {
      .color_fg = VGA_COLOR_LIGHT_BLUE,
      .color_bg = VGA_COLOR_BLACK,
      .cursor_x = 0,
      .cursor_y = font_univga.height,
      .screen = &screen,
      .font = &font_univga};

  tty_writestr(&terminal, "AAAA");

  terminal.cursor_x = mb_info->framebuffer_width - (font_univga.width * 4);
  terminal.cursor_y = mb_info->framebuffer_height;

  tty_writestr(&terminal, "BBBB");
}
