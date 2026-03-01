#include <serial.h>
#include <stdio.h>
#include <terminal.h>

int puts(const char *s) {
  serial_writestring(s);
  terminal_writestring(s);
  serial_putchar('\n');
  terminal_putchar('\n');

  return 0;
}

int putchar(char ch) {
  serial_putchar(ch);
  terminal_putchar(ch);

  return (int)ch;
}

void setcolor(uint8_t color) {
  terminal_setcolor(color);
  serial_setcolor(color);
}
