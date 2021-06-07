// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#include "vga.h"

int top_line_num = 0;

void draw_line_nums();

// screen text functions

void clear_screen(int print_line_nums) {
  int pos;
  for (uint32_t y = 0; y < CHAR_HEIGHT; y++) {
    for (uint32_t x = 0; x < CHAR_WIDTH; x++) {
      pos = (y * CHAR_WIDTH) + x;
      uint8_t* loc = (uint8_t*) VIDEO_MEM + (pos * 2);
      *loc = ' ';
    }
  }

  if (print_line_nums) draw_line_nums();
}

void draw_line_nums() {
  for (int y = 0; y < CHAR_HEIGHT; y++) {
    char str[5] = "    ";
    uint32_t line_num = top_line_num + y;

    int_to_ascii(line_num, str);
    for (uint32_t i = 0; i < 4; i++) {
      if (str[i] == '\0') {
        str[i] = 'a';
      }
    }
    str[3] = '|';
    kprint_at(str, 0, y, 0, 0, 0);
  }
}

// prints string starting at cursor location, and updates cursor location, assumes line nums should be drawn
void kprint(char *msg) {
  kprint_at(msg, -1 , -1, 0, 1, 1);
}

// prints a string starting at x, y. if either are -1, they are set to the cursor location
void kprint_at(char *msg, uint32_t x, uint32_t y, uint8_t attr, int update_cursor_loc, int print_line_nums) {
  if (!attr) attr = WHITE_ON_BLACK;

  if (x == -1 || y == -1) {
    uint32_t pos = get_cursor_pos();
    y = pos / CHAR_WIDTH;
    x = pos % CHAR_WIDTH;
  }

  int i = 0;
  while (msg[i] != '\0') {
    if (x >= CHAR_WIDTH) {
      y++;
      x = 0;
    }

    if (y >= CHAR_HEIGHT) {
      scroll(1, print_line_nums);
      y--;
    }

    if (msg[i] == '\n') {
      y++;
      x = 0;
      i++;
      continue;
    }

    print_char(msg[i], x, y, 0, 0);
    x++;
    i++;
  }

  if (update_cursor_loc) {
    set_cursor_pos(x, y);
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

  // error indicator if x/y out of bounds
  if (x >= CHAR_WIDTH || y > CHAR_HEIGHT) { // wont error is one line past char_height as will scroll then later
    show_error_mark();
    return;
  }

  uint32_t pos = ((y * CHAR_WIDTH) + x) * 2;
  vid_mem[pos] = ch;
  vid_mem[pos + 1] = attr;

  if (update_cursor_loc) {
    set_cursor_pos(x, y);
  }
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
// use:
// y = pos / CHAR_WIDTH;
// x = pos % CHAR_WIDTH;
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

void scroll(int lines, int print_line_nums) {
  top_line_num += lines;

  // move all lines up 'lines' amount
  for (int i = 0; i < CHAR_HEIGHT; i++) {
    uint8_t *line_start = ((uint8_t*) VIDEO_MEM + (i * CHAR_WIDTH * 2));
    uint8_t *line_prev_start = ((uint8_t*) VIDEO_MEM + ((i - lines) * CHAR_WIDTH * 2));
    mem_copy(line_start, line_prev_start, CHAR_WIDTH*2);
  }

  // clear new lines
  for (int i = 0; i < lines; i++) {
    uint8_t *last_line = ((uint8_t *) VIDEO_MEM + ((CHAR_HEIGHT - (lines - i)) * CHAR_WIDTH * 2));
    for (int j = 0; j < CHAR_WIDTH * 2; j++) {
      last_line[j] = 0;
      last_line[j + 1] = WHITE_ON_BLACK;
    }
  }

  // update line nums
  if (print_line_nums) draw_line_nums();
}