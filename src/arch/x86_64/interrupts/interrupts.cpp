/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <arch/x86_64/interrupts/interrupts.hpp>

# include <drivers/pic/pic.hpp>

//static struct IDT_entry IDT[256];
//struct IDTDesc idt_desc;

extern char IDT[];


void create_entry(struct IDT_entry* ent, uint64_t hdl_addr, uint8_t gate_type);

void create_entry(struct IDT_entry* ent, uint64_t hdl_addr, uint8_t gate_type)
{

    ent->offset_1 = ((uint16_t)hdl_addr & 0xffff);
    ent->selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    ent->ist = 0x00;
    ent->zero = 0;
    ent->type_attr = gate_type & 0xf; /* INTERRUPT_GATE or TRAP_GATE */
    ent->type_attr = ent->type_attr | 0x80; /* PRESENT bit. DPL. 0 bit*/
    ent->offset_2 = (uint16_t)(hdl_addr >> 16);
    ent->offset_3 = (uint32_t)(hdl_addr >> 32);
}

extern "C" void initialize_IDT()
{
    //idt_desc.size = (sizeof (IDT_entry) * 256) - 1;
    //idt_desc.addr = (uint64_t)IDT;
    struct IDT_entry* idt = (struct IDT_entry*) IDT;

    /* Create entries for exceptions */
    create_entry(&(idt[0]),(uint64_t) exception0, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[1]),(uint64_t) exception1, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[2]),(uint64_t) exception2, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[3]),(uint64_t) exception3, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[4]),(uint64_t) exception4, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[5]),(uint64_t) exception5, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[6]),(uint64_t) exception6, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[7]),(uint64_t) exception7, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[8]),(uint64_t) exception8, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[9]),(uint64_t) exception9, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[10]),(uint64_t) exception10, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[11]),(uint64_t) exception11, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[12]),(uint64_t) exception12, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[13]),(uint64_t) exception13, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[14]),(uint64_t) exception14, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[15]),(uint64_t) exception15, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[16]),(uint64_t) exception16, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[17]),(uint64_t) exception17, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[18]),(uint64_t) exception18, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[19]),(uint64_t) exception19, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[20]),(uint64_t) exception20, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[21]),(uint64_t) exception21, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[22]),(uint64_t) exception22, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[23]),(uint64_t) exception23, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[24]),(uint64_t) exception24, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[25]),(uint64_t) exception25, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[26]),(uint64_t) exception26, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[27]),(uint64_t) exception27, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[28]),(uint64_t) exception28, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[29]),(uint64_t) exception29, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[30]),(uint64_t) exception30, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[31]),(uint64_t) exception31, GATE_TYPE_INTERRUPT);

    /* Changing PIC's offsets so that IRQs use non-reserved vectors. */
    PIC_remap(0x20, 0x28);

    /* Create entries for irqs */
    create_entry(&(idt[32]), (uint64_t) irq0, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[33]), (uint64_t) irq1, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[34]), (uint64_t) irq2, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[35]), (uint64_t) irq3, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[36]), (uint64_t) irq4, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[37]), (uint64_t) irq5, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[38]), (uint64_t) irq6, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[39]), (uint64_t) irq7, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[40]), (uint64_t) irq8, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[41]), (uint64_t) irq9, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[42]), (uint64_t) irq10, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[43]), (uint64_t) irq11, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[44]), (uint64_t) irq12, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[45]), (uint64_t) irq13, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[46]), (uint64_t) irq14, GATE_TYPE_INTERRUPT);
    create_entry(&(idt[47]), (uint64_t) irq15, GATE_TYPE_INTERRUPT);
}
