#include "idt.h"

extern void *isr_stub_table[];
__attribute__((aligned(0x10))) static idt_entry_t idt_entries[256];
static idtr_t idtr;

void idt_entry(uint8_t index, void *isr, uint8_t flags)
{
  idt_entry_t *descriptor = &idt_entries[index];

  descriptor->isr_low = (uint32_t)isr & 0xFFFF;
  descriptor->kernel_cs = 0x08; // offset for kernel code selector in GDT
  descriptor->attributes = flags;
  descriptor->isr_high = (uint32_t)isr >> 16;
  descriptor->reserved = 0;
}

void idt_init(void)
{
  idtr.base = (uint32_t)&idt_entries[0];
  idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

  for (uint8_t i = 0; i < 32; i++)
  {
    idt_entry(i, isr_stub_table[i], 0x8E);
  }

  __asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
  __asm__ volatile("sti");                   // set the interrupt flag
}
