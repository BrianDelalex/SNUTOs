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

typedef uint64_t size_t;

struct __attribute__((packed)) virtaddr_bitfields_s {
   uint16_t phys_page_offset    : 12;
   uint16_t pt_offset           : 9;
   uint16_t pd_offset           : 9;
   uint16_t pdp_offset          : 9;
   uint16_t pml4_offset         : 9;
   uint16_t sign_ext            : 16;
};

typedef union virtaddr_u {
    uintptr_t addr;
    struct virtaddr_bitfields_s bitfield;
}virtaddr_t;

inline uint32_t virt2pml4Idx(uintptr_t addr)
{
    return (uint32_t) (addr >> 39 & 0x1FF);
}

inline uint32_t virt2pdpIdx(uintptr_t addr)
{
    return (uint32_t) (addr >> 30 & 0x1FF);
}

inline uint32_t virt2pdIdx(uintptr_t addr)
{
    return (uint32_t) (addr >> 21 & 0x1FF);
}

inline uint32_t virt2ptIdx(uintptr_t addr)
{
    return (uint32_t) (addr >> 12 & 0x1FF);
}

inline uint32_t virt2physIdx(uintptr_t addr)
{
    return (uint32_t) (addr & 0xFFF);
}

inline uintptr_t phys2virt(uintptr_t phys)
{
    return phys - ((uintptr_t)KERNEL_VIRT_START);
}

inline uintptr_t virt2phys(uintptr_t virt)
{
    return virt - ((uintptr_t)KERNEL_VIRT_START);
}

typedef struct virtaddr_space_s {
    uintptr_t start;
    uintptr_t end;
}virtaddr_space_t;

typedef struct virtaddr_space_list_s {
    virtaddr_space_t space;
    struct virtaddr_space_list_s* next;
    bool reserved;
}virtaddr_space_list_t;


static virtaddr_space_list_t g_reserved_bs_mapping_spc = {
    .space = {
        .start = (uintptr_t)KERNEL_VIRT_END,
        .end = BOOTSTRAP_MAPPING_END,
    },
    .next = nullptr,
    .reserved = true
};

static virtaddr_space_list_t g_reserved_kernel_spc = {
    .space = {
        .start = (uintptr_t)KERNEL_VIRT_START,
        .end = (uintptr_t)KERNEL_VIRT_END
    },
    .next = &g_reserved_bs_mapping_spc,
    .reserved = true
};

static virtaddr_space_list_t g_reserved_kheap_data_virtaddr_spc = {
    .space = {
        .start = KHEAP_DATA_VIRT_START,
        .end = KHEAP_DATA_VIRT_END
    },
    .next = &g_reserved_kernel_spc,
    .reserved = true
};

class VirtualMemoryManager {
    virtaddr_space_list_t* m_virt_spaces_used;
    virtaddr_space_list_t* m_virt_spaces_free;
public:
    VirtualMemoryManager(void);
    void Init(void);
    void *Map(size_t size);
    void Unmap(void *ptr);
    void ShowState(void);
private:
    void AppendSpace(virtaddr_space_list_t* list, virtaddr_space_list_t* space);
    void RemoveSpace(virtaddr_space_list_t* list, virtaddr_space_list_t* space, bool free);
};

typedef uint8_t unmap_flags;

# define UNMAP_NOFREE 0b1

void map_vmem(uintptr_t vaddr);
void unmap_vmem(uintptr_t vaddr, unmap_flags flags);
bool is_address_mapped(void *addr);
void *map_bootstrap_page(void);
void unmap_identity_mapping(void);
void unmap_vmem_kernel_bootstrap(void);

#endif//!VIRTUAL_MEMORY_HPP
