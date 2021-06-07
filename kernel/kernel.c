// PROJECT ALTAIR
// Created by Rose Awen Brindle on 19/05/2021
//

// NOTE: create strings using char str[x] = "foo" format

#include "../drivers/vga.h"
#include "../intrpt/idt.h"

void kernel_main() {
  init_idt(); // load ISRs

  clear_screen(1);

  //scroll(1, 1);

  //char message[7] = "Rose";
  //kprint_at(message, 4, 0, 0, 1);
//  kprint(message);
//  kprint(message);
}