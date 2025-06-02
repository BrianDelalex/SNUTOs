/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/vga/vga.hpp>

extern "C" void kmain()
{
    vga_driver_initialize();
    while(1);
}