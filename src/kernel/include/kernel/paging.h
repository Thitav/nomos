#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>

typedef uint32_t page_directory_t[1024] __attribute__((aligned(4096)));
typedef uint32_t page_table_t[1024] __attribute__((aligned(4096)));

extern void page_directory_load(page_directory_t page_directory);
extern void paging_enable(void);

#endif
