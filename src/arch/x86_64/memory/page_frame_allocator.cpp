/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "arch/x86_64/memory/page_frame_allocator.hpp"

# include "drivers/serial/serial.hpp"

# include <kernel/core/panic.hpp>

extern char KERNEL_VIRT_START[];
extern char KERNEL_VIRT_END[];
const int kernel_frame_map_size = 512 * 512;
page_frame_t kframe_map[kernel_frame_map_size];

void init_kernel_frame_map()
{
    const uint64_t kernel_phys_end = BOOTSTRAP_MAPPING_END - (uint64_t)KERNEL_VIRT_START;
    for (int i = 0; i < kernel_frame_map_size; i++) {
        kframe_map[i].address = i * PAGE_SIZE;
        if (kframe_map[i].address < kernel_phys_end)
            kframe_map[i].address = SET_USED_BIT(kframe_map[i].address);
    }
}

bool is_page_used(void *page_frame)
{
    if (((uint64_t)page_frame) % PAGE_SIZE != 0) {
        write_serial("[ERROR] kfree_page_frame: address is not page alligned.\n");
        return false;
    }
    return CHECK_USED_BIT(kframe_map[(uint64_t)page_frame / PAGE_SIZE].address);
}

void *kalloc_page_frame()
{
    for (int i = 0; i < kernel_frame_map_size; i++) {
        if (!(kframe_map[i].address & 0b1)) {
            kframe_map[i].address = SET_USED_BIT(kframe_map[i].address);
            return (void*)(CLEAR_USED_BIT(kframe_map[i].address));
        }
    }
    panic("kalloc_page_frame: out of page frame.");
    return NULL;
}

void kfree_page_frame(void* page_frame)
{
    if (((uint64_t)page_frame) % PAGE_SIZE != 0) {
        write_serial("[ERROR] kfree_page_frame: address is not page alligned.\n");
        return;
    }
    unsigned int index = (uint64_t)page_frame / PAGE_SIZE;
    if (!(CHECK_USED_BIT(kframe_map[index].address))) {
        write_serial("[ERROR] kfree_page_frame: double free/freeing unallocated page.\n");
        return;
    }
    kframe_map[index].address = CLEAR_USED_BIT(kframe_map[index].address);
}
