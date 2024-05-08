#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

typedef struct
{
  uint32_t base;
  uint32_t limit;
  uint8_t access_byte;
  uint8_t flags;
} __attribute__((packed)) gdt_entry_t;

typedef struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdtr_t;

void gdt_set(uint16_t gdt_limit, uint32_t gdt_start);
void gdt_entry(uint8_t *target, gdt_entry_t source);

#endif
