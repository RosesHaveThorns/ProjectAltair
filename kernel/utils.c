// PROJECT ALTAIR
// Created by Rose Awen Brindle on 28/05/2021.
//

#include "utils.h"

// note char = uint8_t, int = uint32_t

void mem_copy (uint8_t *source, uint8_t *dest, uint32_t nbytes) {
  int i;
  for (int i = 0; i < nbytes; ++i) {
    *(dest + i) = *(source + i);
  }
}

void mem_set(uint8_t *dest, uint8_t val, uint32_t nbytes) {
  uint8_t  *temp = (uint8_t*) dest;
  for (int i = nbytes; i > 0; --i) {
    *temp++ = val;
  }
}

void int_to_ascii(int n, char str[]) {
  int i, sign;
  if ((sign = n) < 0) n = -n;

  i = 0;
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) str[i++] = '-';

  str[i] = '\0';
}