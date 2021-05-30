// PROJECT ALTAIR
// Created by Rose Awen Brindle on 28/05/2021.
//
#ifndef ALTAIR_UTILS_H
#define ALTAIR_UTILS_H

#include <stdint.h>

void mem_copy (uint8_t *source, uint8_t *dest, uint32_t nbytes);
void mem_set(uint8_t *dest, uint8_t val, uint32_t nbytes);
void int_to_ascii(int n, char str[]);

#endif //ALTAIR_UTILS_H
