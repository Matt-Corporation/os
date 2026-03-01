#include "../kernel/hal/interrupts.h"
#include <cursor.h>
#include <panic.h>
#include <serial.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <terminal.h>

void __panicf(const char *format, ...) {
  char buffer[256];

  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);

  setcolor(VGA_COLOR_WHITE);

  if (strlen(buffer) > 0) {
    puts(buffer);
  } else {
    puts("<no panic message provided>");
  }

  disable_cursor();

  setcolor(VGA_COLOR_LIGHT_GREY);
  printf("For further information, "
         "visit: ");

  setcolor(VGA_COLOR_LIGHT_BROWN);
  puts("http://localhost:3000/panic");

  serial_setcolor(VGA_COLOR_WHITE);

  va_end(args);

  disable_interrupts();

  for (;;) {
    __asm__("hlt");
  }
}
