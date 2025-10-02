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

multiboot_info *mb_info = nullptr;

void show_memory_map_infos();
void parse_multiboot_infos_tags();
void show_memory_multiboot_tags();
extern VGA vga;

extern char KERNEL_END[];
extern char KERNEL_VIRT_START[];

extern "C" void kmain(__attribute__((unused)) uint32_t mb_magic, uint32_t mb_addr)
{
    const char bootSequenceDone[] = "Boot sequence done\n";
    const char welcomeMsg[] = "Welcome to SNUTOs\n";
    vga.Clear();
    vga.Write(bootSequenceDone);
    vga.Write(welcomeMsg);
    mb_info = (multiboot_info *)((uintptr_t)mb_addr);
    vga.Write("Kernel virtual start: ");
    vga.WriteAddress((uint64_t)KERNEL_VIRT_START);
    vga.Write("\n");
    vga.Write("Kernel virtual end: ");
    vga.WriteAddress((uint64_t)KERNEL_END);
    vga.Write("\n");
    vga.Write("Kernel size: ");
    vga.Write(((uint64_t)KERNEL_END) - (uint64_t)KERNEL_VIRT_START);
    vga.Write("\n");

    while (1) {
        asm volatile("hlt");
    }
}
