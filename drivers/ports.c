// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//
// Contains functions for reading and writing from/to ports

// !!! Inline ASM has src and dest params backwards to NASM () !!!

#include "ports.h"

unsigned char port_read_byte (unsigned short port){
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port)); // do 'in edx, eal', set edx to port and eax to result (eal = lower val of eax)
  return result;
}

void port_write_byte (unsigned short port, unsigned char data) {
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port))
}

unsigned short port_read_word (unsigned short port) {
  unsigned char result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void port_write_word (unsigned short port, unsigned short data) {
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port))
}