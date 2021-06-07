// PROJECT ALTAIR
// Created by Rose Awen Brindle on 28/05/2021.
//
#ifndef ALTAIR_ISR_H
#define ALTAIR_ISR_H

#include <stdint.h>
#include "../kernel/utils.h"

typedef struct {
  uint32_t ds; // data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
  uint32_t intrpt_num, err_code;
  uint32_t eip, cs, eflags, useresp, ss; // pushed by processor automaticly
} registers_t;

void isr_handler(registers_t);

#endif //ALTAIR_ISR_H
