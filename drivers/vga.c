// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#include "vga.h"

// screen text functions

void clear_screen() {
  //show_error_mark();
  //show_warn_mark();
  int pos;
  for (uint32_t x = 0; x < CHAR_WIDTH; ++x) {
    for (uint32_t y = 0; y < CHAR_HEIGHT; ++y) {
      pos = (y * CHAR_WIDTH) + x;
      uint8_t* loc = (uint8_t*) VIDEO_MEM + (pos * 2);
      *loc = ' ';
    }
  }
}

// prints string starting at cursor location, and updates cursor location
void kprint(char *msg) {
  kprint_at(msg, -1 , -1, 0, 1);
}

// prints a string starting at x, y. if either are -1, they are set to the cursor location
void kprint_at(char *msg, uint32_t x, uint32_t y, uint8_t attr, int update_cursor_loc) {
  if (!attr) attr = WHITE_ON_BLACK;

  if (x == -1 || y == -1) {
    uint32_t pos = get_cursor_pos();
    y = pos / CHAR_WIDTH;
    x = pos % CHAR_WIDTH;
  }

  uint32_t i = 0;
  while (msg[i] != '\0') {
    print_char(msg[i], x + i, y, 0, 0);
    i++;
  }


  if (update_cursor_loc) {
    set_cursor_pos(x+i, y);
  }
}

// prints a char at x, y. if either are -1, they are set to the cursor location
// if attr == 0, default to white on black
void print_char(char ch, uint32_t x, uint32_t y, uint8_t attr, int update_cursor_loc) {
  if (x == -1 || y == -1) {
    uint32_t pos = get_cursor_pos();
    y = pos / CHAR_WIDTH;
    x = pos % CHAR_WIDTH;
  }

  uint8_t *vid_mem = (uint8_t*) VIDEO_MEM;
  if (!attr) attr = WHITE_ON_BLACK;

//  // error indicator if x/y out of bounds
//  if (x >= CHAR_WIDTH || y >= CHAR_HEIGHT) {
//    //show_error_mark(); todo: re-add
//    return;
//  }

  if (ch == '\n') {
    y++;
    x = 0;
  }

  uint32_t pos = ((y * CHAR_WIDTH) + x)*2;
  vid_mem[pos] = ch;
  vid_mem[pos + 1] = attr;

//  if (update_cursor_loc) {
//    set_cursor_pos(x, y);
//  }
}

// cursor functions
void set_cursor_pos(uint32_t x, uint32_t y) {
  uint32_t pos = y * CHAR_WIDTH + x;

  port_write_byte(VGA_CTRL_REG, 14);
  port_write_byte(VGA_DATA_REG, (uint8_t)(pos >> 8)); // write lower pos

  port_write_byte(VGA_CTRL_REG, 15);
  port_write_byte(VGA_DATA_REG, (uint8_t)(pos & 0xff)); // write upper pos
}

// returns y * CHAR_HEIGHT + x
uint32_t get_cursor_pos() {
  uint32_t pos = 0;

  port_write_byte(VGA_CTRL_REG, 14);
  pos = port_read_byte(VGA_DATA_REG) << 8; // read high byte

  port_write_byte(VGA_CTRL_REG, 15);
  pos += port_read_byte(VGA_DATA_REG);

  return pos;
}

void show_error_mark() {
  print_char('E', 79, 24, RED_ON_WHITE, 0);
}
void show_warn_mark() {
  print_char('W', 78, 24, BLUE_ON_WHITE, 0);
}
