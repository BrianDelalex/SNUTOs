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

static struct IDT_entry IDT[256];

static struct IDT_entry create_entry(uint64_t hdl_addr, uint8_t gate_type)
{
    struct IDT_entry ent;

    ent.offset_1 = hdl_addr & 0xffff;
    ent.selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    ent.ist = 0x00;
    ent.zero = 0;
    ent.type_attr = gate_type & 0xf; /* INTERRUPT_GATE or TRAP_GATE */
    ent.type_attr = ent.type_attr | 0x80; /* PRESENT bit. DPL. 0 bit*/
    ent.offset_2 = (hdl_addr & 0xffff0000) >> 16;
    ent.offset_3 = (hdl_addr & 0xffff00000000) >> 32;

    return (ent);
}

extern "C" void initialize_IDT()
{
    uint64_t IDT_addr = (uint64_t) IDT;
    struct IDTDesc idt_desc;
    idt_desc.size = ((sizeof (struct IDT_entry) * 256) + ((IDT_addr & 0xffff) << 16)) - 1;
    idt_desc.addr = IDT_addr;

    /* Create entries for exceptions */
    IDT[0] = create_entry((uint64_t) exception0, GATE_TYPE_INTERRUPT);
    IDT[1] = create_entry((uint64_t) exception1, GATE_TYPE_INTERRUPT);
    IDT[2] = create_entry((uint64_t) exception2, GATE_TYPE_INTERRUPT);
    IDT[3] = create_entry((uint64_t) exception3, GATE_TYPE_INTERRUPT);
    IDT[4] = create_entry((uint64_t) exception4, GATE_TYPE_INTERRUPT);
    IDT[5] = create_entry((uint64_t) exception5, GATE_TYPE_INTERRUPT);
    IDT[6] = create_entry((uint64_t) exception6, GATE_TYPE_INTERRUPT);
    IDT[7] = create_entry((uint64_t) exception7, GATE_TYPE_INTERRUPT);
    IDT[8] = create_entry((uint64_t) exception8, GATE_TYPE_INTERRUPT);
    IDT[9] = create_entry((uint64_t) exception9, GATE_TYPE_INTERRUPT);
    IDT[10] = create_entry((uint64_t) exception10, GATE_TYPE_INTERRUPT);
    IDT[11] = create_entry((uint64_t) exception11, GATE_TYPE_INTERRUPT);
    IDT[12] = create_entry((uint64_t) exception12, GATE_TYPE_INTERRUPT);
    IDT[13] = create_entry((uint64_t) exception13, GATE_TYPE_INTERRUPT);
    IDT[14] = create_entry((uint64_t) exception14, GATE_TYPE_INTERRUPT);
    IDT[15] = create_entry((uint64_t) exception15, GATE_TYPE_INTERRUPT);
    IDT[16] = create_entry((uint64_t) exception16, GATE_TYPE_INTERRUPT);
    IDT[17] = create_entry((uint64_t) exception17, GATE_TYPE_INTERRUPT);
    IDT[18] = create_entry((uint64_t) exception18, GATE_TYPE_INTERRUPT);
    IDT[19] = create_entry((uint64_t) exception19, GATE_TYPE_INTERRUPT);
    IDT[20] = create_entry((uint64_t) exception20, GATE_TYPE_INTERRUPT);
    IDT[21] = create_entry((uint64_t) exception21, GATE_TYPE_INTERRUPT);
    IDT[22] = create_entry((uint64_t) exception22, GATE_TYPE_INTERRUPT);
    IDT[23] = create_entry((uint64_t) exception23, GATE_TYPE_INTERRUPT);
    IDT[24] = create_entry((uint64_t) exception24, GATE_TYPE_INTERRUPT);
    IDT[25] = create_entry((uint64_t) exception25, GATE_TYPE_INTERRUPT);
    IDT[26] = create_entry((uint64_t) exception26, GATE_TYPE_INTERRUPT);
    IDT[27] = create_entry((uint64_t) exception27, GATE_TYPE_INTERRUPT);
    IDT[28] = create_entry((uint64_t) exception28, GATE_TYPE_INTERRUPT);
    IDT[29] = create_entry((uint64_t) exception29, GATE_TYPE_INTERRUPT);
    IDT[30] = create_entry((uint64_t) exception30, GATE_TYPE_INTERRUPT);
    IDT[31] = create_entry((uint64_t) exception31, GATE_TYPE_INTERRUPT);

    /* Changing PIC's offsets so that IRQs use non-reserved vectors. */
    PIC_remap(0x20, 0x28);

    /* Create entries for irqs */
    IDT[32] = create_entry((uint64_t) irq0, GATE_TYPE_INTERRUPT);
    IDT[33] = create_entry((uint64_t) irq1, GATE_TYPE_INTERRUPT);
    IDT[34] = create_entry((uint64_t) irq2, GATE_TYPE_INTERRUPT);
    IDT[35] = create_entry((uint64_t) irq3, GATE_TYPE_INTERRUPT);
    IDT[36] = create_entry((uint64_t) irq4, GATE_TYPE_INTERRUPT);
    IDT[37] = create_entry((uint64_t) irq5, GATE_TYPE_INTERRUPT);
    IDT[38] = create_entry((uint64_t) irq6, GATE_TYPE_INTERRUPT);
    IDT[39] = create_entry((uint64_t) irq7, GATE_TYPE_INTERRUPT);
    IDT[40] = create_entry((uint64_t) irq8, GATE_TYPE_INTERRUPT);
    IDT[41] = create_entry((uint64_t) irq9, GATE_TYPE_INTERRUPT);
    IDT[42] = create_entry((uint64_t) irq10, GATE_TYPE_INTERRUPT);
    IDT[43] = create_entry((uint64_t) irq11, GATE_TYPE_INTERRUPT);
    IDT[44] = create_entry((uint64_t) irq12, GATE_TYPE_INTERRUPT);
    IDT[45] = create_entry((uint64_t) irq13, GATE_TYPE_INTERRUPT);
    IDT[46] = create_entry((uint64_t) irq14, GATE_TYPE_INTERRUPT);
    IDT[47] = create_entry((uint64_t) irq15, GATE_TYPE_INTERRUPT);

    load_idt(&idt_desc);
}