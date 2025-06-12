/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/serial/serial.hpp>

# include <sys/io.h>

extern "C" int init_serial()
{
    outb(0x00, IOPORT_COM1 + 1);    // Disable all interrupts
    outb(0x80, IOPORT_COM1 + 3);    // Enable DLAB(set baut rate divisor)
    outb(0x03, IOPORT_COM1);        //Set divisor to 3 (lo byte) 38400 baud
    outb(0x00, IOPORT_COM1 + 1);    //                 (hi byte)
    outb(0x03, IOPORT_COM1 + 3);    // 8 bits, no parity, one stop bit
    outb(0xC7, IOPORT_COM1 + 2);    // Enable FIFO, clear them, with 14-byte thresold
    outb(0x0B, IOPORT_COM1 + 4);    // IRQs enabled, RTS/DSR set
    outb(0x1E, IOPORT_COM1 + 4);    // Set in loopback mode, test the serial chip
    outb(0xAE, IOPORT_COM1);        // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty
    if (inb(IOPORT_COM1) != 0xAE) {
        return 1;
    }
    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(0x0F, IOPORT_COM1 + 4);
    return 0;
}

/*
    Check the THRE bit (Transmitter holding register empty).
    If it is set that mean the transmission buffer is empty (data can be sent)  
*/
int is_transmit_empty()
{
    return (inb(IOPORT_COM1 + 5) & 0x20);
}

void write_serial(char *str)
{
    for (int i = 0; str[i]; i++) {
        while (is_transmit_empty() == 0); // Wait until the transmission buffer is empty.
        outb(str[i], IOPORT_COM1);
    }
}