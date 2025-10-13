/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef MEM_CONSTANTS_HPP
#define MEM_CONSTANTS_HPP

# define NULL ((void*)0)

# define PAGE_SIZE 0x1000

extern char KERNEL_VIRT_END[];

extern char KERNEL_VIRT_START[];

# define VGA_MEMORY_START ((uintptr_t)KERNEL_VIRT_START + 0xb8000)

# define BOOTSTRAP_PAGE_END      (PAGE_SIZE * PAGE_PER_PAGE_TABLE * BOOTSTRAP_PAGE_TABLE_NBR)

# define BOOTSTRAP_PAGE_TABLE_NBR   20
# define PAGE_PER_PAGE_TABLE        512
# define BOOTSTRAP_MAPPING_END      (PAGE_SIZE * PAGE_PER_PAGE_TABLE * BOOTSTRAP_PAGE_TABLE_NBR) + ((uint64_t) KERNEL_VIRT_START)


#endif//!MEM_CONSTANTS_HPP
