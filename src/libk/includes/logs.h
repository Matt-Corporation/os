#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <terminal.h>

typedef struct status {
  uint8_t color;
  char *msg;
  bool add_parentheses;
} status_t;

#define STATUS_OK                                                              \
  &(status_t) {                                                                \
    .color = VGA_COLOR_LIGHT_GREEN, .msg = "  OK  ", .add_parentheses = true   \
  }

#define STATUS_BLANK                                                           \
  &(status_t) {                                                                \
    .color = VGA_COLOR_BLACK, .msg = "        ", .add_parentheses = false      \
  }

void msgf(status_t *status, const char *format, ...);
