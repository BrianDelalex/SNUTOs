/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PIC_CONSTANTS_HPP
#define PIC_CONSTANTS_HPP

# define PIC_MASTER          0x20        /* IO base address for master PIC */
# define PIC_SLAVE           0xA0        /* IO base address for slave PIC */
# define PIC_MASTER_COMMAND  PIC_MASTER
# define PIC_MASTER_DATA     (PIC_MASTER+1)
# define PIC_SLAVE_COMMAND   PIC_SLAVE
# define PIC_SLAVE_DATA      (PIC_SLAVE+1)

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

# define PIC_EOI		0x20		/* End-of-interrupt command code */

# define END_OF_INTERRUPT() outb(PIC_EOI, PIC_MASTER_COMMAND)

#endif //!PIC_CONSTANTS_HPP