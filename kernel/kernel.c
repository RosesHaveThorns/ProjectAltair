// PROJECT ALTAIR
// Created by Rose on 19/05/2021
//

/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
  char* video_memory = (char*) 0xb8000; // 0xb8000 is video mem address
  *video_memory = 'X';
}