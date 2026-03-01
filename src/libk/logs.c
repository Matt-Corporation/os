#include <logs.h>
#include <stdio.h>
#include <terminal.h>

void msgf(status_t *status, const char *format, ...) {
  if (status->add_parentheses) {
    putchar('[');
  }

  setcolor(status->color);
  printf("%s", status->msg);
  setcolor(VGA_COLOR_LIGHT_GREY);

  if (status->add_parentheses) {
    putchar(']');
  }

  char buffer[256];
  va_list args;

  va_start(args, format);
  vsprintf(buffer, format, args);

  putchar(' ');
  puts(buffer);
}
