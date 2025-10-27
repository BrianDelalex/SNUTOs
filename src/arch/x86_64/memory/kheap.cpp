/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <arch/x86_64/memory/kheap.hpp>
# include <arch/x86_64/memory/virtual_memory.hpp>
# include <arch/x86_64/memory/paging.h>
# include <arch/x86_64/memory/page_frame_allocator.hpp>

# include <kernel/assert.hpp>
# include <drivers/serial/SerialStream.hpp>

io::ostream &operator<<(io::ostream &os, kheap_block_list_t *block)
{
    os << HEX << (uintptr_t) block << " [ addr: " << HEX << block->block.addr << ", size:" << block->block.size << ", used: " << (block->block.allocated ? "true" : "false") << "]\n";
    return os;
}

KHeap::KHeap() {}

void KHeap::Init()
{
    m_data.Init();
    m_pages = map_bootstrap_page();
    void *page2 = map_bootstrap_page();
    assert_msg(((uint64_t)m_pages) + PAGE_SIZE == (uint64_t) page2, "KHeap::Init: mapped pages are not continuous.");
    m_pages_nbr = 2;
    m_blocks = GetNode();
    m_blocks->block.addr = m_data.m_virtaddr_space.start;
    m_blocks->block.size = m_data.GetMappedSize();
    m_blocks->block.allocated = false;
    m_blocks->next = nullptr;
}

void *KHeap::Alloc(size_t size)
{
    kheap_block_list_t* blocks = m_blocks;
    kheap_block_list_t* last_block;

    while (blocks) {
        if (blocks->block.allocated) {
            blocks = blocks->next;
            continue;
        }
        if (blocks->block.size >= size) {
            return AllocBlock(blocks, size);
        }
        last_block = blocks;
        blocks = blocks->next;
    }

    uint32_t page_nbr = size / PAGE_SIZE + 1;
    m_data.MapPages(page_nbr);
    kheap_block_list_t* new_block = GetNode();
    new_block->block.addr = last_block->block.addr + last_block->block.size;
    new_block->block.size = page_nbr * PAGE_SIZE;
    new_block->block.allocated = false;
    new_block->next = nullptr;
    last_block->next = new_block;
    if (!last_block->block.allocated) {
        MergeFreeBlocks();
        return AllocBlock(last_block, size);
    } else {
        return AllocBlock(new_block, size);
    }
}

void KHeap::Free(void* addr)
{
    kheap_block_list_t *blocks = m_blocks;
    bool last_block_allocated = true;

    while (blocks) {
        if (blocks->block.addr == (uintptr_t)addr) {
            if (!blocks->block.allocated) {
                panic("KHeap::Free: Double free/Free unallocated value.");
                return;
            }
            blocks->block.allocated = false;
            if (!last_block_allocated)
                MergeFreeBlocks();
            return;
        }
        last_block_allocated = blocks->block.allocated;
        blocks = blocks->next;
    }
    panic("KHeap::Free: Double free/Free unallocated value.");
}

void KHeap::MergeFreeBlocks()
{
    kheap_block_list_t* blocks = m_blocks;

    while (blocks && blocks->next) {
        if (!blocks->block.allocated && !blocks->next->block.allocated) {
            kheap_block_list_t* next = blocks->next;
            blocks->block.size += next->block.size;
            blocks->next = next->next;
            ReleaseNode(next);
            continue;
        }
        blocks = blocks->next;
    }
}

void KHeap::ShowBlocks(io::ostream &os)
{
    kheap_block_list_s* ptr = m_blocks;

    os << "---- KHEAP BLOCKS ----\n";
    while (ptr) {
        os << ptr;
        ptr = ptr->next;
    }
    os << "\n";
}

void *KHeap::AllocBlock(kheap_block_list_t* block, size_t size)
{
    if (block->block.size == size) {
        block->block.allocated = true;
        return (void*)block->block.addr;
    }

    // If block.size > size split block to allocate only requested size.
    kheap_block_list_t* new_block = GetNode();
    new_block->block.addr = block->block.addr + size;
    new_block->block.size = block->block.size - size;
    new_block->block.allocated = false;
    new_block->next = block->next;

    block->block.allocated = true;
    block->block.size = size;
    block->next = new_block;
    return (void*)block->block.addr;
}

kheap_block_list_t* KHeap::GetNode(void)
{
    uint32_t node_nbr = m_pages_nbr * PAGE_SIZE / sizeof(kheap_block_list_t);
    kheap_block_list_t* blocks = (kheap_block_list_t*) m_pages;

    for (unsigned int i = 0; i < node_nbr; i++) {
        if (!blocks[i].used) {
            blocks[i].used = true;
            return &(blocks[i]);
        }
    }

    return nullptr;
}

void KHeap::ReleaseNode(kheap_block_list_t* node)
{
    assert_msg(((uint64_t) node) % sizeof(kheap_block_list_t) == 0, "KHeap::ReleaseNode: node is not aligned on sizeof(kheap_block_list_t).");

    node->used = false;
    node->next = nullptr;
}

extern char PDP[];
/*
 * Create page-translation-tables for the whole KHeap virtual address space and
 * map KHeapData::m_initial_pages Pages at the start of KHeap virtual address space.
 */
void KHeapData::Init()
{
    m_virtaddr_space = {
        .start = m_kheap_virt_start,
        // KHeap data uses a 512 pages within 512 page tables, within 1 page directory. For a total size of 1GiB.
        .end = m_kheap_virt_start + (512 * 512 - 1) * PAGE_SIZE
    };

    m_pd = (struct pd_s*)map_bootstrap_page();
    struct pdp_s* pdp = (struct pdp_s*)PDP;
    uint32_t pdp_index = virt2pdpIdx(m_kheap_virt_start);
    pdp->entries[pdp_index].addr = (uintptr_t)m_pd - (uintptr_t)KERNEL_VIRT_START;
    pdp->entries[pdp_index].bits.p = 0b1;
    pdp->entries[pdp_index].bits.r_w = 0b1;

    for (int pd_index = 0; pd_index < 512; pd_index++) {
        struct pt_s* pt = (struct pt_s*)map_bootstrap_page();
        m_pd->entries[pd_index].addr = (uintptr_t)pt - (uintptr_t)KERNEL_VIRT_START;
        m_pd->entries[pd_index].bits.p = 0b1;
        m_pd->entries[pd_index].bits.r_w = 0b1;
        for (int pt_index = 0; pt_index < 512; pt_index++) {
            pt->entries[pt_index].addr = 0x0;
        }
    }

    MapPages(m_initial_pages);
}

/*
 * Map page_nbr pages into the KHeap virtual address space. The mapping is linear.
 */
void KHeapData::MapPages(uint32_t page_nbr)
{
    assert_msg(page_nbr + m_mapped_pages < 512 * 512, "KHeapData::MapPages: The mapping requested will get out of bound of the KHeap's virtual address space.");

    int pd_index = m_mapped_pages / 512;
    int pt_index = m_mapped_pages % 512;
    uint32_t page_count = 0;

    for (; pd_index < 512; pd_index++) {
        struct pt_s*pt = (struct pt_s*)((m_pd->entries[pd_index].addr & ~0xFFF) + (uintptr_t)KERNEL_VIRT_START);
        for (; pt_index < 512; pt_index++) {
            uintptr_t page = (uintptr_t)kalloc_page_frame();
            pt->entries[pt_index].addr = page;
            pt->entries[pt_index].bits.p = 0b1;
            pt->entries[pt_index].bits.r_w = 0b1;
            page_count++;
            if (page_count == page_nbr) {
                m_mapped_pages += page_nbr;
                return;
            }
        }
    }
}

uint32_t KHeapData::GetMappedSize()
{
    return PAGE_SIZE * m_mapped_pages;
}
