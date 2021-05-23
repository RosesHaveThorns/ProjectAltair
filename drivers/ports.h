// PROJECT ALTAIR
// Created by Rose Awen Brindle on 23/05/2021.
//

#ifndef MAIN_PORTS_H
#define MAIN_PORTS_H

// function declarations
unsigned char port_read_byte (unsigned short port);
void port_write_byte (unsigned short port, unsigned char data);

unsigned short port_read_word (unsigned short port);
void port_write_word (unsigned short port, unsigned short data);

#endif //MAIN_PORTS_H
