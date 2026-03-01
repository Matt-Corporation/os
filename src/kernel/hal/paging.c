#include "paging.h"
#include <logs.h>

void invlpg(uintptr_t virtual_address) {
  __asm__ volatile("invlpg (%0)" ::"r"(virtual_address) : "memory");
}

extern void load_page_directory(unsigned int *);
extern void enable_paging();

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void first_page_initialize() {
  // we will fill all 1024 entries in the table, mapping 4 megabytes
  for (unsigned int i = 0; i < 1024; i++) {
    // As the address is page aligned, it will always leave 12 bits zeroed.
    // Those bits are used by the attributes ;)
    first_page_table[i] =
        (i * PAGE_SIZE) |
        3; // attributes: supervisor level, read/write, present.
  }
}

void paging_initialize() {
  msgf(STATUS_BLANK, "Initializing paging...");

  for (int i = 0; i < 1024; i++) {
    // This sets the following flags to the pages:
    // - Supervisor: Only kernel-mode can access them
    // - Write Enabled: It can be both read from and written to
    // - Not Present: The page table is not present
    page_directory[i] = 0x00000002;
  }

  first_page_initialize();

  page_directory[0] = ((unsigned int)first_page_table) | 3;

  load_page_directory((unsigned int *)page_directory);
  enable_paging();

  msgf(STATUS_OK, "Initialized paging.");
}
