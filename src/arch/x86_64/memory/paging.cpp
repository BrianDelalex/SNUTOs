/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "arch/x86_64/memory/paging.h"

# include "drivers/vga/vga.hpp"

extern const char PML4[];
extern const char PT[];
extern VGA vga;

void test_pml4()
{
    struct pml4_s* pml4 = (struct pml4_s*)PML4;
    struct pt_s* pt = (struct pt_s*)PT;
    vga.Clear();

    vga.Write("Phys. page at addr: ");
    vga.WriteAddress(pt[511].entries[511].entry);
    vga.Write("\n");

}
