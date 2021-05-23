// PROJECT ALTAIR
// Created by Rose Awen Brindle on 19/05/2021
//

void kernel_main() {
  char* video_memory = (char*) 0xb8000; // 0xb8000 is video mem address
  *video_memory = 'X';
}