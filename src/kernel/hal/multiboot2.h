#pragma once

#include <stdint.h>

typedef struct multiboot2_tag {
  uint32_t type;
  uint32_t size;
} multiboot2_tag_t;

typedef struct multiboot2_info {
  uint32_t total_size;
  uint32_t reserved;
  multiboot2_tag_t tags[0];
} multiboot2_info_t;

typedef struct multiboot2_tag_command_line {
  uint32_t type;
  uint32_t size;
  uint8_t string[];
} multiboot2_tag_command_line_t;

typedef struct multiboot2_tag_bootloader {
  uint32_t type;
  uint32_t size;
  uint8_t string[];
} multiboot2_tag_bootloader_t;

typedef struct multiboot2_tag_module {
  uint32_t type;
  uint32_t size;
  uint32_t mod_start;
  uint32_t mod_end;
  uint8_t string[];
} multiboot2_tag_module_t;

void *multiboot2_find_tag(uint32_t type, multiboot2_tag_t *tags);
