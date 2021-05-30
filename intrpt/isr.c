// PROJECT ALTAIR
// Created by Rose Awen Brindle on 28/05/2021.
//

#include "isr.h"
#include "../drivers/vga.h"

void isr_print(char*, int, int);

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_print(char *str, int x, int y) {
  uint8_t *vid_mem = (uint8_t*) 0xb8000;

  uint32_t i = 0;
  while (str[i] != '\0') {
    uint32_t pos = ((y * 80) + (x + i)) * 2;

    vid_mem[pos] = str[i];
    vid_mem[pos + 1] = 0xf1;

    i++;
  }
}

void isr_handler(registers_t regs) {
  char s0[19] = "INTERRUPT RECEIVED";
  kprint_at(s0, 20, 10, BLUE_ON_WHITE, 0);

  char s1[3];
  int_to_ascii(regs.intrpt_num, s1);
  isr_print(s1, 20, 11);

  isr_print(exception_messages[regs.intrpt_num], 25, 11);

  char s2[3];
  int_to_ascii(regs.err_code, s2);
  isr_print(s2, 20, 12);
}