// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#ifndef ALTAIR_VGA_H
#define ALTAIR_VGA_H

#include "../drivers/ports.h"

#define VIDEO_MEM 0xb8000
#define WHITE_ON_BLACK 0x0f // character colour byte

#define VGA_CTRL_REG 0x3d4
#define VGA_DATA_REG 0x3d5

#define CHAR_WIDTH 80
#define CHAR_HEIGHT 25

void clear_screen();

void kprint(char*);
void kprint_at(char*, int, int, int);
void print_char(char, int, int, int);

void enable_cursor();
void disable_cursor();
void set_cursor_pos(int, int);
unsigned int get_cursor_pos();

#endif //ALTAIR_VGA_H
