// PROJECT ALTAIR
// Created by Rose Awen Brindle on 27/05/2021.
//

#include "idt.h"

// internal function declarations
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

// table representations
idt_entry_table idt_entries[256];
idt_ptr_table idt_ptr;

// functions
void init_idt() {
  // set IDT pntr
  idt_ptr.limit = sizeof(idt_entry_table) * 256 - 1;
  idt_ptr.base = (uint32_t) &idt_entries;

  //memset(&idt_entries, 0 , sizeof(idt_entry_table)*256);

  // set ISRs
  idt_set_gate(0, (uint32_t) isr0, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(1, (uint32_t) isr1, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(2, (uint32_t) isr2, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(3, (uint32_t) isr3, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(4, (uint32_t) isr4, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(5, (uint32_t) isr5, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(6, (uint32_t) isr6, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(7, (uint32_t) isr7, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(8, (uint32_t) isr8, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(9, (uint32_t) isr9, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(10, (uint32_t) isr10, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(11, (uint32_t) isr11, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(12, (uint32_t) isr12, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(13, (uint32_t) isr13, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(14, (uint32_t) isr14, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(15, (uint32_t) isr15, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(16, (uint32_t) isr16, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(17, (uint32_t) isr17, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(18, (uint32_t) isr18, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(19, (uint32_t) isr19, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(20, (uint32_t) isr20, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(21, (uint32_t) isr21, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(22, (uint32_t) isr22, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(23, (uint32_t) isr23, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(24, (uint32_t) isr24, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(25, (uint32_t) isr25, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(26, (uint32_t) isr26, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(27, (uint32_t) isr27, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(28, (uint32_t) isr28, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(29, (uint32_t) isr29, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(30, (uint32_t) isr30, KERNEL_CODE_SEG, 0x8e);
  idt_set_gate(31, (uint32_t) isr31, KERNEL_CODE_SEG, 0x8e);

  // load IDT
  __asm__ __volatile__ ("lidt (%0)" : : "r" (&idt_ptr));
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt_entries[num].base_low = base & 0xFFFF;
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;

  idt_entries[num].sel = sel;
  idt_entries[num].always0 = 0;

  idt_entries[num].flags = flags; // add '| 0x60' once in user mode (ie set privilege level to 3)
}