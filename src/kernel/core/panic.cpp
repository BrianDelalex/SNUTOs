/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "drivers/vga/vga.hpp"

extern VGA vga;

void panic(const char *msg)
{
    vga.Clear();
    vga.SetColor(VGA_COLOR_WHITE, VGA_COLOR_RED);
    vga << "Kernel panic: " << msg << "\n";
    vga << "At: " << HEX << (uintptr_t)__builtin_return_address(1) << "\n";
    vga << "At: " << HEX << (uintptr_t)__builtin_return_address(2) << "\n";
    vga << "At: " << HEX << (uintptr_t)__builtin_return_address(3) << "\n";

    while (1);
}
