// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#include "vga.h"

// private function declarations

void enable_cursor();
void disable_cursor();
unsigned int get_cursor_pos();
void set_cursor_pos (int, int);

// screen text functions

void clear_screen() {
  int pos;
  for (int x = 0; x < CHAR_WIDTH; ++x) {
    for (int y = 0; y < CHAR_HEIGHT; ++y) {
      pos = (y * CHAR_HEIGHT) + x;
      char* loc = (char*) VIDEO_MEM + (pos * 2);
      *loc = ' ';
    }
  }
}

// prints string starting at cursor location, and updates cursor location
void kprint(char* str) {
  kprint_at(str, -1 , -1, 1);
}

// prints a string starting at x, y. if either are -1, they are set to the cursor location
void kprint_at(char* str, int x, int y, int update_cursor_loc) {
  if (x == -1 || y == -1) {
    int pos = get_cursor_pos();
    y = pos / CHAR_WIDTH;
    x = pos % CHAR_WIDTH;
  }

  int str_len = sizeof(*str) / sizeof(char);

  for (int i = 0; i < str_len; ++i) {
    print_char(str[i], x, y, 0); // dont update cursor till string complete
    x++;
  }

  if (update_cursor_loc) {
    set_cursor_pos(x, y);
  }
}

// prints a char at x, y. if either are -1, they are set to the cursor location
void print_char(char ch, int x, int y, int update_cursor_loc) {
  if (x == -1 || y == -1) {
    int pos = get_cursor_pos();
    y = pos / CHAR_WIDTH;
    x = pos % CHAR_WIDTH;
  }

  if (ch == '\n') {
    y++;
    x = 0;
  }

  int pos = (y * CHAR_HEIGHT) + x;
  char* loc = (char*) VIDEO_MEM + (pos * 2);
  *loc = ch;

  if (update_cursor_loc) {
    set_cursor_pos(x, y);
  }
}

// cursor functions

void enable_cursor() {
  // set cursor start to 0
  port_write_byte(VGA_CTRL_REG, 0x0A); // ie set to edit lower cursor shape register
  char vga_data_new_val = (port_read_byte(VGA_DATA_REG) & 0xC0) | 0;
  port_write_byte(VGA_DATA_REG,  vga_data_new_val);

  // set cursor end to 15 (max scan line)
  port_write_byte(VGA_CTRL_REG, 0x0B); // ie set to edit upper??? cursor shape register
  vga_data_new_val = (port_read_byte(VGA_DATA_REG) & 0xE0) | 15;
  port_write_byte(VGA_DATA_REG,  vga_data_new_val);
}

void disable_cursor() {
  port_write_byte(VGA_CTRL_REG, 0x0A);
  port_write_byte(VGA_DATA_REG, 0x20); // bit 5 disables cursor, bits 0-4 control cursor shape
}

// returns y * CHAR_HEIGHT + x
unsigned int get_cursor_pos() {
  int pos = 0;

  port_write_byte(VGA_CTRL_REG, 0x0F);
  pos |= port_read_byte(VGA_DATA_REG);

  port_write_byte(VGA_CTRL_REG, 0x0E);
  pos |= ((int) port_read_byte(VGA_DATA_REG)) << 8;

  return pos;
}

void set_cursor_pos(int x, int y) {
  unsigned int pos = y * CHAR_WIDTH + x;

  port_write_byte(VGA_CTRL_REG, 0x0F);
  port_write_byte(VGA_DATA_REG, (char) (pos & 0xFF)); // write lower pos

  port_write_byte(VGA_CTRL_REG, 0x0E);
  port_write_byte(VGA_DATA_REG, (char) ((pos >> 8) & 0xFF)); // write upper pos
}