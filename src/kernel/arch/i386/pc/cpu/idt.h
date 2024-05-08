#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct
{
  uint16_t isr_low;   // Lower 16 bits of the ISR address
  uint16_t kernel_cs; // GDT segment selector that will be loaded into CS before calling the ISR
  uint8_t reserved;   // Set to zero
  uint8_t attributes; // Type and attributes
  uint16_t isr_high;  // Higher 16 bits of the ISR address
} __attribute__((packed)) idt_entry_t;

typedef struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idtr_t;

void idt_entry(uint8_t index, void *isr, uint8_t flags);
void idt_init(void);

#endif
