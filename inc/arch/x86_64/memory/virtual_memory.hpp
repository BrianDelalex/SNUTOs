/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef VIRTUAL_MEMORY_HPP
# define VIRTUAL_MEMORY_HPP

# include <stdint.h>
# include <arch/x86_64/memory/constants.hpp>

# define BOOTSTRAP_PAGE_TABLE_NBR   20
# define PAGE_PER_PAGE_TABLE        512
# define BOOTSTRAP_MAPPING_END      (PAGE_SIZE * PAGE_PER_PAGE_TABLE * BOOTSTRAP_PAGE_TABLE_NBR) + ((uint64_t) KERNEL_VIRT_START)

struct __attribute__((packed)) virtaddr_bitfields_s {
   uint16_t phys_page_offset    : 12;
   uint16_t pt_offset           : 9;
   uint16_t pd_offset           : 9;
   uint16_t pdp_offset          : 9;
   uint16_t pml4_offset         : 9;
   uint16_t sign_ext            : 16;
};

typedef union virtaddr_u {
    uint64_t addr;
    struct virtaddr_bitfields_s bitfield;
}virtaddr_t;

inline uint32_t virt2pml4Idx(virtaddr_t addr)
{
    return (uint32_t) (((uintptr_t)addr.addr) >> 39 & 0x1FF);
}

inline uint32_t virt2pdpIdx(virtaddr_t addr)
{
    return (uint32_t) (((uintptr_t)addr.addr) >> 30 & 0x1FF);
}

inline uint32_t virt2pdIdx(virtaddr_t addr)
{
    return (uint32_t) (((uintptr_t)addr.addr) >> 21 & 0x1FF);
}

inline uint32_t virt2ptIdx(virtaddr_t addr)
{
    return (uint32_t) (((uintptr_t)addr.addr) >> 12 & 0x1FF);
}

inline uint32_t virt2physIdx(virtaddr_t addr)
{
    return (uint32_t) (((uintptr_t)addr.addr) & 0xFFF);
}

typedef struct virtaddr_space_s {
    uint64_t start;
    uint64_t end;
}virtaddr_space_t;

typedef uint8_t unmap_flags;

# define UNMAP_NOFREE 0b1

void unmap_vmem(virtaddr_t virtaddr, unmap_flags flags);

#endif//!VIRTUAL_MEMORY_HPP
