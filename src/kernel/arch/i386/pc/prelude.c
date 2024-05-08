#include <stdint.h>
#include "cpu/paging.h"

static page_directory_t identity_page_directory;
static page_table_t identity_page_table;

void prelude(void)
{
  for (uint16_t i = 0; i < 1024; i++)
  {
    identity_page_directory[i] = 0b00000010;
    identity_page_table[i] = (i * 0x1000) | 3;
  }
  identity_page_directory[0] = ((uint32_t)identity_page_table) | 3;

  page_directory_load(identity_page_directory);
  paging_enable();
}
