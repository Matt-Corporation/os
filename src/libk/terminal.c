#include <cursor.h>
#include <stddef.h>
#include <string.h>
#include <terminal.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(uint8_t color) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = color;
  terminal_buffer = (uint16_t *)0xB8000;

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll_up() {
  if (terminal_row >= VGA_HEIGHT) {
    for (size_t row = 0; row < VGA_HEIGHT - 1; row++) {
      for (size_t column = 0; column < VGA_WIDTH; column++) {
        terminal_buffer[row * VGA_WIDTH + column] =
            terminal_buffer[(row + 1) * VGA_WIDTH + column];
      }
    }

    for (size_t column = 0; column < VGA_WIDTH; column++) {
      terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + column] = vga_entry(
          ' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    }

    terminal_row = VGA_HEIGHT - 1;
  }
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_row++;
    terminal_column = 0;

    if (terminal_row >= VGA_HEIGHT) {
      terminal_scroll_up();

      terminal_column = 0;
    }

    update_cursor(terminal_column, terminal_row);

    return;
  }

  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    terminal_row++;

    if (terminal_row >= VGA_HEIGHT) {
      terminal_scroll_up();
      terminal_column = 0;
      update_cursor(terminal_column, terminal_row);
    }
  }

  update_cursor(terminal_column, terminal_row);
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
}
