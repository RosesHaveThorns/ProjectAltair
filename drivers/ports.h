// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#ifndef ALTAIR_PORTS_H
#define ALTAIR_PORTS_H

#include <stdint.h>

// function declarations
uint8_t port_read_byte (uint16_t port);
void port_write_byte (uint16_t port, uint8_t data);

uint16_t port_read_word (uint16_t port);
void port_write_word (uint16_t port, uint16_t data);

#endif //ALTAIR_PORTS_H
