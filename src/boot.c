#include "kmod.h"
#include "logs.h"
#include "modules/azerbaijan_virus.h"
#include "product.h"
#include "serial.h"
#include "vga.h"

#if defined(__linux__)
#error \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "mattOS needs to be compiled with a ix86-elf compiler"
#endif

void kmain()
{
  serial_initialize();
  terminal_initialize();

  terminal_writestring("Welcome to ");
  terminal_setcolor(VGA_COLOR_WHITE);
  terminal_writestring(PRODUCT_NAME);
  terminal_writestring(" ");
  terminal_writestring(PRODUCT_VERSION);
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminal_writestring("!\n\n");

  puts_status(status_map[STATUS_OK], "Booted into the kernel");

  add_mod(azerbaijan_virus);
}
