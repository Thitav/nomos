#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/font.h>
#include <kernel/multiboot.h>

// static gdt_entry_t kernel_gdt[5];

// void init_gdt(void)
// {
//   gdt_entry_t kernel_code = {
//       .base = 0,
//       .limit = 0xfffff,
//       .access_byte = 0b10011010,
//       .flags = 0b1100};
//   gdt_entry_t kernel_data = {
//       .base = 0,
//       .limit = 0xfffff,
//       .access_byte = 0b10010010,
//       .flags = 0b1100};
//   gdt_entry_t user_code = {
//       .base = 0,
//       .limit = 0xfffff,
//       .access_byte = 0b11111010,
//       .flags = 0b1100};
//   gdt_entry_t user_data = {
//       .base = 0,
//       .limit = 0xfffff,
//       .access_byte = 0b11110010,
//       .flags = 0b1100};

//   gdt_entry((uint8_t *)&kernel_gdt[0], (gdt_entry_t){0, 0, 0, 0}); // Null descriptor
//   gdt_entry((uint8_t *)&kernel_gdt[1], kernel_code);
//   gdt_entry((uint8_t *)&kernel_gdt[2], kernel_data);
//   gdt_entry((uint8_t *)&kernel_gdt[3], user_code);
//   gdt_entry((uint8_t *)&kernel_gdt[4], user_data);
//   gdt_set((uint16_t)sizeof(kernel_gdt), (uint32_t)kernel_gdt);
// }

void kernel_entry(uint32_t mb_magic, multiboot_info_t *mb_info)
{
  if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    // Should be kernel panic
    return;
  }

  vga_init(mb_info->framebuffer_width, mb_info->framebuffer_height);
  tty_init(mb_info->framebuffer_width, mb_info->framebuffer_height, VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK, &font_univga);

  printf("Hello from kernel!\n");
  printf("Have a nice day!\n");
}
