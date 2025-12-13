#pragma once

#include "serial.h"
#include "vga.h"
#include <stdio.h>

typedef struct status {
  const char *text;
  const vga_color_t color;
} status_t;

#define STATUS_OK 0
#define STATUS_WAIT 1
#define STATUS_FAIL 2

inline void output_writestring(const char *s) {
  terminal_writestring(s);
  serial_writestring(s);
}

const status_t status_map[] = {{"  OK  ", VGA_COLOR_GREEN},
                               {"", VGA_COLOR_BLACK},
                               {" FAIL ", VGA_COLOR_LIGHT_RED}};

inline void puts_status(const status_t status, const char *message) {
  if (status.text != status_map[STATUS_WAIT].text) {
    putchar('[');
    terminal_setcolor(status.color);
    output_writestring(status.text);
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    putchar(']');
    putchar(' ');
  } else {
    output_writestring("         ");
  }

  puts(message);
}
