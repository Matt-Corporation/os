#include "../tests/main.h"
#include "drivers/fs/tarfs.h"
#include "hal.h"
#include "hal/multiboot2.h"
#include <panic.h>
#include <serial.h>
#include <stdio.h>
#include <terminal.h>

// Check if the compiler thinks you are targeting the wrong OS
#if defined(__linux__) || defined(__mac__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// This OS only works with 32-bit ix86 targets
#if !defined(__i386__)
#error "mattOS needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(multiboot2_info_t *multiboot2_info,
                 uint32_t multiboot2_magic) {
  if (multiboot2_magic != 0x36d76289) {
    panicf("Expected the magic number for multiboot2 (0x36d76289), got 0x%x",
           multiboot2_magic);
  }

  terminal_initialize(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  serial_initialize();

  // printf("memory: reserved: %lu; total size: %lu\n",
  //        (unsigned long)multiboot2_info->reserved,
  //        (unsigned long)multiboot2_info->total_size);

  multiboot2_tag_module_t *tarinit =
      multiboot2_find_tag(3, multiboot2_info->tags);

  const unsigned char *archive = (unsigned char *)tarinit->mod_start;
  const char *name = tar_read(archive, "tarinit/name.txt");
  const char *version = tar_read(archive, "tarinit/version.txt");

  printf("Welcome to ");
  setcolor(VGA_COLOR_WHITE);
  printf("%s %s", name, version);
  setcolor(VGA_COLOR_LIGHT_GREY);
  puts("!\n");
  hal_initialize();
  putchar('\n');

  // TODO: tarinit/test should have a signature, don't compare only one
  // character
  if ((tar_read(archive, "tarinit/test"))[0] == '#') {
    start_tests();
  } else {
    puts("The OS doesn't have anything to do.\nWhy didn't you run `make test` "
         "to run tests?");
  }
}
