#pragma once

#include <stdint.h>

int serial_initialize();
int serial_received();
char serial_read();
int serial_is_transmit_empty();
void serial_putchar(char a);
void serial_writestring(const char *s);
void serial_setcolor(uint8_t color);
