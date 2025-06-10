/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <sys/io.h>

# include <drivers/pic/constants.hpp>
# include <drivers/vga/vga.hpp>

extern VGA vga;

/* Programmable Interrupt Timer */
extern "C" void irq0_handler()
{
    END_OF_INTERRUPT();
}

/* Keyboard */
extern "C" void irq1_handler()
{
    END_OF_INTERRUPT();
}

/* Cascade (used internally by the two PICs. never raised) */
extern "C" void irq2_handler()
{
    END_OF_INTERRUPT();
}

/* COM2 (if enabled) */
extern "C" void irq3_handler()
{
    END_OF_INTERRUPT();
}

/* COM1 (if enabled) */
extern "C" void irq4_handler()
{
    END_OF_INTERRUPT();
}

/* LPT2 (if enabled)*/
extern "C" void irq5_handler()
{
    END_OF_INTERRUPT();
}

/* Floppy disk */
extern "C" void irq6_handler()
{
    END_OF_INTERRUPT();
}

/* LPT1 */
extern "C" void irq7_handler()
{
    END_OF_INTERRUPT();
}

/* CMOS real-time clock (if enabled) */
extern "C" void irq8_handler()
{
    END_OF_INTERRUPT();
}

/* Free for peripherals / legacy SCSI / NIC */
extern "C" void irq9_handler()
{
    END_OF_INTERRUPT();
}

/* Free for peripherals / SCSI / NIC */
extern "C" void irq10_handler()
{
    END_OF_INTERRUPT();
}

/* Free for peripherals / SCSI / NIC */
extern "C" void irq11_handler()
{
    END_OF_INTERRUPT();
}

/* PS2 Mouse */
extern "C" void irq12_handler()
{
    END_OF_INTERRUPT();
}

/* FPU / Coprocessor / Inter-processor */
extern "C" void irq13_handler()
{
    END_OF_INTERRUPT();
}

/* Primary ATA Hard Disk */
extern "C" void irq14_handler()
{
    END_OF_INTERRUPT();
}

/* Secondary ATA Hard Disk */
extern "C" void irq15_handler()
{
    END_OF_INTERRUPT();
}