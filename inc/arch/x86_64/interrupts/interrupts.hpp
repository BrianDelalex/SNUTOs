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

# include <cstdint>

# define GATE_TYPE_INTERRUPT    0xE
# define GATE_TYPE_TRAP         0xF

struct IDT_entry  {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};

struct __attribute__((packed)) IDTDesc {
    uint16_t size;
    uint64_t addr;
};

extern "C" int load_idt(void *idt_addr);
extern "C" int exception0();
extern "C" int exception1();
extern "C" int exception2();
extern "C" int exception3();
extern "C" int exception4();
extern "C" int exception5();
extern "C" int exception6();
extern "C" int exception7();
extern "C" int exception8();
extern "C" int exception9();
extern "C" int exception10();
extern "C" int exception11();
extern "C" int exception12();
extern "C" int exception13();
extern "C" int exception14();
extern "C" int exception15();
extern "C" int exception16();
extern "C" int exception17();
extern "C" int exception18();
extern "C" int exception19();
extern "C" int exception20();
extern "C" int exception21();
extern "C" int exception22();
extern "C" int exception23();
extern "C" int exception24();
extern "C" int exception25();
extern "C" int exception26();
extern "C" int exception27();
extern "C" int exception28();
extern "C" int exception29();
extern "C" int exception30();
extern "C" int exception31();
extern "C" int irq0();
extern "C" int irq1();
extern "C" int irq2();
extern "C" int irq3();
extern "C" int irq4();
extern "C" int irq5();
extern "C" int irq6();
extern "C" int irq7();
extern "C" int irq8();
extern "C" int irq9();
extern "C" int irq10();
extern "C" int irq11();
extern "C" int irq12();
extern "C" int irq13();
extern "C" int irq14();
extern "C" int irq15();

#endif //!INTERRUPTS_HPP