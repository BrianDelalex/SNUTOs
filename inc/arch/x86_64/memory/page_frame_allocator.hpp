/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PAGE_FRAME_ALLOCATOR_HPP
#define PAGE_FRAME_ALLOCATOR_HPP

# include <stdint.h>

# include <arch/x86_64/memory/constants.hpp>

typedef struct page_frame_s {
    uint64_t address;
    bool used;
}page_frame_t;

void init_kernel_frame_map(void);
void *kalloc_page_frame();
void kfree_page_frame(void* page_frame);
bool is_page_used(void *page_frame);

#endif//!PAGE_FRAME_ALLOCATOR_HPP
