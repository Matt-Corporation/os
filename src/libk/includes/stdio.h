#pragma once

#include <printf/printf.h>
#include <stdint.h>

int puts(const char *s);
int putchar(char ch);
void setcolor(uint8_t color);

#define printf printf_
#define sprintf sprintf_
#define vsprintf vsprintf_
#define snprintf snprintf_
#define vsnprintf vsnprintf_
#define vprintf vprintf_
