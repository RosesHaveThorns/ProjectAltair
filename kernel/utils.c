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

void int_to_ascii(uint32_t n, char str[]) {
  uint32_t max_len = str_len(str);
  uint32_t n_orig = n;

  // find digit length of int
  uint32_t req_len = 0;
  uint32_t n_temp = n;
  do {
    req_len++;
  } while ((n_temp /= 10) > 0);

  // create a temp string which is exactly length required
  char temp_str[req_len];

  // put string version of int in temp_str, it will be backwards
  uint32_t i = 0;
  do {
    temp_str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  // check if int is longer than max length of string, if it is fill the string with x
  if (i >= max_len) {
    for (uint32_t j = 0; j < i; ++j) {
      str[j] = 'x';
    }
    str[max_len] = '\0';
    return;
  }

  // if int is not a single digit, flip it
  if (!(n_orig >= 0 && n_orig <= 9)) { // ie if it is not single digit
    str_flip(temp_str);
  }

  for (int j = 0; j < req_len; ++j) {
    str[j] = temp_str[j]; // move final int from temp_str to str
  }
  
  str[max_len] = '\0';
}

void str_flip(char *str) {
  uint32_t i;
  uint32_t j;
  char a;
  uint32_t len = str_len(str);
  for (i = 0, j = len - 1; i < j; i++, j--)
  {
    a = str[i];
    str[i] = str[j];
    str[j] = a;
  }
}

uint32_t str_len(const char str[]) {
  uint32_t count = 0;
  while(*str!='\0')
  {
    count++;
    str++;
  }
  return count;
}

void str_copy(char *dest, char *src) {
  mem_copy((uint8_t*)dest, (uint8_t*)src, str_len(src)+1);
}