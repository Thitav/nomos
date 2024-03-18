#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kernel/vga.h>

static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

void kernel_main(void)
{
  vga_init();
  VGA_MEMORY[strlen("AAAA")] = 0x0F00 | 'H';
  printf("Hello");
  unsigned char *location = (unsigned char *)0xA0000 + 320 * 5 + 10;
  *location = 0x0F00;
}
