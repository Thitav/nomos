#include "gdt.h"

void gdt_entry(uint8_t *target, gdt_entry_t source)
{
  // Check limit to make sure that it can be encoded
  // if (source.limit > 0xFFFFF)
  // {
  //  kerror("GDT cannot encode limits larger than 0xFFFFF");
  // }

  // Encode limit
  target[0] = source.limit & 0xFF;
  target[1] = (source.limit >> 8) & 0xFF;
  target[6] = (source.limit >> 16) & 0x0F;

  // Encode base
  target[2] = source.base & 0xFF;
  target[3] = (source.base >> 8) & 0xFF;
  target[4] = (source.base >> 16) & 0xFF;
  target[7] = (source.base >> 24) & 0xFF;

  // Encode access byte
  target[5] = source.access_byte;

  // Encode flags
  target[6] |= (source.flags << 4);
}
