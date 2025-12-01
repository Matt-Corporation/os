#include "vga.h"
#include "panic.h"
#include "product.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "mattOS needs to be compiled with a ix86-elf compiler"
#endif

void kmain()
{
  terminal_initialize();
  terminal_writestring("shh...");
  terminal_writestring("\ndont leak our hard work :)");
  panic("yo");
}
