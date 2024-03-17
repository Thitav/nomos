#include <stdio.h>
#include <stdint.h>
#include <kernel/vga.h>

static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

void kernel_main(void)
{
  VGA_MEMORY[2] = ((uint16_t)'A' | (uint16_t)0x0F << 8);
  // vga_init();
  // putchar('t');
}
