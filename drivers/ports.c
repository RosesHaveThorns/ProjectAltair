// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

// !!! Inline ASM has src and dest params backwards to NASM () !!!

#include "ports.h"

uint8_t port_read_byte (uint16_t port){
  uint8_t result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port)); // do 'in edx, eal', set edx to port and eax to result (eal = lower val of eax)
  return result;
}

void port_write_byte (uint16_t port, uint8_t data) {
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t port_read_word (uint16_t port) {
  uint8_t result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void port_write_word (uint16_t port, uint16_t data) {
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}