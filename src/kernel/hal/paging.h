#pragma once

#include <stdint.h>

#define PAGE_SIZE 0x1000

void invlpg(uintptr_t virtual_address);
void paging_initialize();
