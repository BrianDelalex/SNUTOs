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
# include <arch/x86_64/memory/page_frame_allocator.hpp>
# include <drivers/serial/SerialStream.hpp>

multiboot_info *mb_info = nullptr;

void show_memory_map_infos();
void parse_multiboot_infos_tags();
void show_memory_multiboot_tags();
extern VGA vga;

extern char KERNEL_VIRT_END[];
extern char KERNEL_VIRT_START[];

extern "C" void kmain(__attribute__((unused)) uint32_t mb_magic, uint32_t mb_addr)
{
    SerialStream serial;
    const char bootSequenceDone[] = "Boot sequence done\n";
    const char welcomeMsg[] = "Welcome to SNUTOs\n";
    vga.Clear();
    vga << bootSequenceDone << welcomeMsg;
    serial << bootSequenceDone << welcomeMsg;
    mb_info = (multiboot_info *)((uintptr_t)mb_addr);
    vga << "Kernel virtual start: " << HEX << (uint64_t) KERNEL_VIRT_START << "\n";

    vga << "Kernel virtual end: " << HEX << ((uint64_t)KERNEL_VIRT_END) << "\n";

    vga << "Kernel size: " << HEX << ((uint64_t)KERNEL_VIRT_END) - ((uint64_t)KERNEL_VIRT_START) << "\n";

    while (1) {
        asm volatile("hlt");
    }
}
