/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef INTERRUPTS_HPP
# define INTERRUPTS_HPP

# include <stdint.h>

# define GATE_TYPE_INTERRUPT    0xE
# define GATE_TYPE_TRAP         0xF

struct __attribute__((packed)) IDT_entry  {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};

static_assert(sizeof(struct IDT_entry) == 16, "struct IDT_entry invalid size!");

struct __attribute__((packed)) IDTDesc {
    uint16_t size;
    uint64_t addr;
};

static_assert(sizeof(struct IDTDesc) == 10, "struct IDTDesc invalid size!");

extern "C" int load_idt(void *idt_addr);
extern "C" void exception0();
extern "C" void exception1();
extern "C" void exception2();
extern "C" void exception3();
extern "C" void exception4();
extern "C" void exception5();
extern "C" void exception6();
extern "C" void exception7();
extern "C" void exception8();
extern "C" void exception9();
extern "C" void exception10();
extern "C" void exception11();
extern "C" void exception12();
extern "C" void exception13();
extern "C" void exception14();
extern "C" void exception15();
extern "C" void exception16();
extern "C" void exception17();
extern "C" void exception18();
extern "C" void exception19();
extern "C" void exception20();
extern "C" void exception21();
extern "C" void exception22();
extern "C" void exception23();
extern "C" void exception24();
extern "C" void exception25();
extern "C" void exception26();
extern "C" void exception27();
extern "C" void exception28();
extern "C" void exception29();
extern "C" void exception30();
extern "C" void exception31();
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

#endif //!INTERRUPTS_HPP
