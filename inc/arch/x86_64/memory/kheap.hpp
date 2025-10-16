/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef KHEAP_HPP
#define KHEAP_HPP

# include <stdint.h>
# include <arch/x86_64/memory/virtual_memory.hpp>
# include <lib/io/ostream.hpp>

typedef uint64_t size_t;

typedef struct kheap_block_s {
    uintptr_t addr;
    uint32_t size;
    bool allocated;
}kheap_block_t;

typedef struct kheap_block_list_s {
    kheap_block_t block;
    struct kheap_block_list_s* next;
    bool used;
}kheap_block_list_t;

io::ostream &operator<<(io::ostream &os, kheap_block_list_t block);

static_assert(sizeof(kheap_block_list_t) == 32, "struct kheap_block_list_s size is invalid");

class KHeapData {
    const uint64_t m_kheap_virt_start = 0xFFFFFFFF40000000;
    const uint32_t m_initial_pages = 20;
    struct pd_s* m_pd;
    virtaddr_space_t m_virtaddr_space;
    uint32_t m_mapped_pages = 0;
public:
    KHeapData() = default;
    void Init();
    uint32_t GetMappedSize(void);
private:
    void MapPages(uint32_t page_nbr);

    friend class KHeap;
};

class KHeap {
    virtaddr_space_t m_virtaddr_space;
    kheap_block_list_t* m_blocks;
    void* m_pages;
    uint32_t m_pages_nbr;
    KHeapData m_data;
public:
    KHeap();
    void Init();

    void* Alloc(size_t size);
    void Free(void* addr);
    void MergeFreeBlocks(void);

    void ShowBlocks(io::ostream &os);
private:
    void *AllocBlock(kheap_block_list_t* block, size_t size);
    kheap_block_list_t* GetNode(void);
    void ReleaseNode(kheap_block_list_t* node);
};


#endif//!KHEAP_HPP
