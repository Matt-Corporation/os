#pragma once

#include "../serial.h"
#include "../vga.h"
#include "string.h"

inline int puts(const char *s) {
  terminal_writestring(s);
  terminal_writestring("\n");

  serial_writestring(s);
  serial_writestring("\n");

  return strlen(s);
}

inline int putchar(int c) {
  terminal_putchar(c);
  serial_putchar(c);

  return c;
}
