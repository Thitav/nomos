#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#include <stddef.h>

void vga_init(void);
void vga_putchar(char c);
void vga_write(const char *data, size_t size);
void vga_writestring(const char *data);

#endif
