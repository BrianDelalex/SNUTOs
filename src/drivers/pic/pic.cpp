/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/pic/pic.hpp>

# include <sys/io.h>

void PIC_remap(uint8_t offset1, uint8_t offset2)
{
    // starts the initialization sequence (in cascade mode)
    outb(ICW1_INIT | ICW1_ICW4, PIC_MASTER_COMMAND);
    outb(ICW1_INIT | ICW1_ICW4, PIC_SLAVE_COMMAND);

    // ICW2: Master PIC vector offset
    outb(offset1, PIC_MASTER_DATA);
    // ICW2: Slave PIC vector offset
    outb(offset2, PIC_SLAVE_DATA);

    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(0x4, PIC_MASTER_DATA);
    // ICW3: tell Slave PIC its cascade identity (0000 0010)
    outb(0x2, PIC_SLAVE_DATA);

    // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    outb(ICW4_8086, PIC_MASTER_DATA);
    outb(ICW4_8086, PIC_SLAVE_DATA);

    // Unmask both PICs.
    outb(0, PIC_MASTER_DATA);
    outb(0, PIC_SLAVE_DATA);
}