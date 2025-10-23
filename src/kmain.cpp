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
# include <arch/x86_64/memory/virtual_memory.hpp>
# include <arch/x86_64/memory/paging.h>
# include <arch/x86_64/memory/kheap.hpp>
# include <kernel/memory/alloc.hpp>


extern KHeap g_kheap;
multiboot_info *mb_info = nullptr;

void show_memory_map_infos();
void parse_multiboot_infos_tags();
void show_memory_multiboot_tags();
void init_virtual_memory_manager();
extern VGA vga;

extern char PD[];
extern char PT[];

void count_mapped_page()
{
    int page_allocated = 0;
    struct pt_s* pt = (struct pt_s*)PT;
    uint64_t first_page_mapped = 0xFFFFFFFFFFFFFFFF;
    uint64_t last_page_mapped;

    for (int i = 0; i < BOOTSTRAP_PAGE_TABLE_NBR ; i++) {
        for (int j = 0; j < 512; j++) {
            if (pt[i].entries[j].addr != 0) {
                if (pt[i].entries[j].bits.p) {
                    if (pt[i].entries[j].addr < first_page_mapped)
                        first_page_mapped = pt[i].entries[j].addr;
                    page_allocated++;
                    last_page_mapped = pt[i].entries[j].addr;
                }
            }
        }
    }
    vga << "Page mapped " << page_allocated << " from " << HEX << \
        first_page_mapped << " to " << HEX << last_page_mapped << " size " << \
        (last_page_mapped - first_page_mapped) / 1024 / 1024 << " MB." << "\n";
}

bool is_address_mapped(void *addr);
extern "C" void kmain(__attribute__((unused)) uint32_t mb_magic, uint32_t mb_addr)
{
    SerialStream serial;
    const char bootSequenceDone[] = "Boot sequence done\n";
    const char welcomeMsg[] = "Welcome to SNUTOs\n";
    vga.Clear();
    vga << bootSequenceDone << welcomeMsg;
    serial << bootSequenceDone << welcomeMsg;
    mb_info = (multiboot_info *)((uintptr_t)mb_addr + KERNEL_VIRT_START);
    vga << "Kernel virtual start: " << HEX << (uint64_t) KERNEL_VIRT_START << "\n";

    vga << "Kernel virtual end: " << HEX << ((uint64_t)KERNEL_VIRT_END) << "\n";

    vga << "Kernel size: " << ((uint64_t)KERNEL_VIRT_END) - ((uint64_t)KERNEL_VIRT_START) << "\n";
    serial << "Kernel size: " << ((uint64_t)KERNEL_VIRT_END) - ((uint64_t)KERNEL_VIRT_START) << "\n";

    init_kernel_frame_map();

    count_mapped_page();
    init_virtual_memory_manager();
    count_mapped_page();

    parse_multiboot_infos_tags();

    while (1) {
        asm volatile("hlt");
    }
}
