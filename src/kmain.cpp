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
void write_serial(const char *str);
void test_pml4();

extern char KERNEL_END[];
uint64_t KERNEL_START = 0x200000;

extern "C" void kmain(__attribute__((unused)) uint32_t mb_magic, uint32_t mb_addr)
{
    vga_driver_initialize();
    mb_info = (multiboot_info *)((uintptr_t)mb_addr);
    parse_multiboot_infos_tags();
    //show_memory_map_infos();
    vga.Clear();
    vga.Write("\n");
    vga.WriteAddress((uint64_t)KERNEL_START);
    vga.Write("\n");
    vga.WriteAddress((uint64_t)KERNEL_END);
    vga.Write("\n");
    write_serial("test");
    vga.Write((((uint64_t)KERNEL_END) - KERNEL_START));
    test_pml4();

    while (1) {
        asm volatile("hlt");
    }
}
