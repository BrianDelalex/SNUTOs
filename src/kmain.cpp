/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/vga/vga.hpp>
# include <drivers/multiboot/multiboot_info.hpp>

# include <climits>

extern VGA vga;
multiboot_info *mb_info = nullptr;

void show_memory_map_infos();
void parse_multiboot_infos_tags();
void show_memory_multiboot_tags();

extern "C" void kmain(uint32_t mb_magic, uint32_t mb_addr)
{
    vga_driver_initialize();

    mb_info = (multiboot_info *)((uintptr_t)mb_addr);
    parse_multiboot_infos_tags();
    show_memory_map_infos();

    while(1);
}