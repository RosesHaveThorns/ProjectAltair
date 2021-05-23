// PROJECT ALTAIR
// Created by Rose Awen Brindle on 19/05/2021
//

#include "../drivers/vga.h"

void kernel_main() {
  clear_screen();
  enable_cursor();
  print_char('Y', 0, 0, 0);
}