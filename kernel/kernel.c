// PROJECT ALTAIR
// Created by Rose Awen Brindle on 19/05/2021
//

// NOTE: create strings using char str[x] = "foo" format

#include "../drivers/vga.h"
#include "../intrpt/idt.h"

void debugPrint(char);

void kernel_main() {

  debugPrint('X');


  init_idt(); // load ISRs

  clear_screen();

  debugPrint('Y');

  //print_char('Y', 79, 0, 0, 0);
  //print_char('Z', 1, 24, 0, 0);

  //char message[5] = "Rose";
  //kprint(message);

  //print_char('A', 0, 0, 0, 0);
}

void debugPrint(char ch) {
  unsigned char *vid_mem = (unsigned char*) 0xb8000;
  vid_mem[0] = ch;
  vid_mem[1] = 0xf1;
}