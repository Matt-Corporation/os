#include <panic.h>
#include <serial.h>
#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <terminal.h>

#define PORT 0x3f8 // COM1

int serial_initialize() {
  outb(PORT + 1, 0x00); // Disable all interrupts
  outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  outb(PORT + 1, 0x00); //                  (hi byte)
  outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
  outb(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip
  outb(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial
                        // returns same byte)

  // Check if serial is faulty (i.e: not same byte as sent)
  if (inb(PORT + 0) != 0xAE) {
    return 1;
  }

  // If serial is not faulty set it in normal operation mode
  // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
  outb(PORT + 4, 0x0F);

  return 0;
}

int serial_received() { return inb(PORT + 5) & 1; }

char serial_read() {
  while (serial_received() == 0)
    ;

  return inb(PORT);
}

int serial_is_transmit_empty() { return inb(PORT + 5) & 0x20; }

void serial_putchar(char a) {
  while (serial_is_transmit_empty() == 0)
    ;

  outb(PORT, a);
}

void serial_writestring(const char *s) {
  for (int i = 0; i < (int)strlen(s); i++) {
    serial_putchar(s[i]);
  }
}

static uint8_t vga_color_to_ansi(uint8_t vga) {
  switch (vga) {
    case VGA_COLOR_BLACK:
      return 30;
    case VGA_COLOR_BLUE:
      return 34;
    case VGA_COLOR_GREEN:
      return 32;
    case VGA_COLOR_CYAN:
      return 36;
    case VGA_COLOR_RED:
      return 31;
    case VGA_COLOR_MAGENTA:
      return 35;
    case VGA_COLOR_BROWN:
      return 33;
    case VGA_COLOR_LIGHT_GREY:
      return 37;
    case VGA_COLOR_WHITE:
      return 97;
    case VGA_COLOR_DARK_GREY:
      return 90;
    case VGA_COLOR_LIGHT_BLUE:
      return 94;
    case VGA_COLOR_LIGHT_GREEN:
      return 92;
    case VGA_COLOR_LIGHT_CYAN:
      return 96;
    case VGA_COLOR_LIGHT_RED:
      return 91;
    case VGA_COLOR_LIGHT_MAGENTA:
      return 95;
    case VGA_COLOR_LIGHT_BROWN:
      return 93;
    default: {
      panicf("cannot convert VGA color to ANSI escape sequence: unknown VGA "
             "color %d",
             vga);
    }
  }
}

void serial_setcolor(uint8_t color) {
  char buf[50];

  snprintf(buf, 50, "\033[%dm", vga_color_to_ansi(color));

  serial_writestring(buf);
}
