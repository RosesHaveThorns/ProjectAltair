// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#ifndef ALTAIR_VGA_H
#define ALTAIR_VGA_H

#include "../drivers/ports.h"

#include <stdint.h>

#define VIDEO_MEM 0xb8000

#define WHITE_ON_BLACK 0x0f // character colour byte
#define RED_ON_WHITE 0xf4 // error colour byte
#define BLUE_ON_WHITE 0xf1 // warn colour byte

#define VGA_CTRL_REG 0x3d4
#define VGA_DATA_REG 0x3d5

#define CHAR_WIDTH 80
#define CHAR_HEIGHT 25

void clear_screen();

void show_error_mark();
void show_warn_mark();

void kprint(char*);
void kprint_at(char*, uint32_t , uint32_t, uint8_t, int);
void print_char(char, uint32_t, uint32_t, uint8_t, int);

void enable_cursor();
void disable_cursor();
uint32_t get_cursor_pos();
void set_cursor_pos(uint32_t x, uint32_t y);

#endif //ALTAIR_VGA_H
