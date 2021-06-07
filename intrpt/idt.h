// PROJECT ALTAIR
// Created by Rose Awen Brindle on 27/05/2021.
//

#ifndef ALTAIR_IDT_H
#define ALTAIR_IDT_H

#include <stdint.h>

// -- GENERAL DEFINITIONS --

void init_idt();

#define KERNEL_CODE_SEG 0x08
#define KERNEL_DATA_SEG 0x10

// -- IDT DEFINITIONS --

// describes single interrupt gate
struct idt_entry_struct {
  uint16_t base_low;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_table;

// describes pointer to array of interrupt handlers
struct idt_ptr_struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_table;

// link to ISR handlers: all call back to isr.c
// these are are reserved for CPU exceptions
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif //ALTAIR_IDT_H
