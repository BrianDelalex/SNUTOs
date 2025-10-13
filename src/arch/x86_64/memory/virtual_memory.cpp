/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <arch/x86_64/memory/virtual_memory.hpp>
# include <arch/x86_64/memory/page_frame_allocator.hpp>
# include <arch/x86_64/memory/constants.hpp>
# include <arch/x86_64/memory/paging.h>

# include <kernel/assert.hpp>

# include <drivers/serial/SerialStream.hpp>

# include <bitwise_op.hpp>

extern "C" void tlb_flush(void);

extern char KERNEL_VIRT_END[];
extern char KERNEL_VIRT_START[];
extern char PML4[];
extern char PDP[];
extern char PD[];
extern char PT[];

virtaddr_space_t g_early_virtaddr_spc = {0, 0};

inline bool is_page_aligned(virtaddr_t virtaddr)
{
    return virtaddr.addr % PAGE_SIZE == 0;
}

/*
 * Unmapped memory after KERNEL_VIRT_END.
 */
static void unmap_vmem_kernel_bootstrap()
{
    SerialStream serial;
    virtaddr_t virtaddr;
    virtaddr.addr = align((uintptr_t)KERNEL_VIRT_END, PAGE_SIZE);
    g_early_virtaddr_spc.start = virtaddr.addr;
    uint32_t unmappedBytes = 0;

    while (virtaddr.addr < (uint64_t)BOOTSTRAP_MAPPING_END) {
        unmap_vmem(virtaddr, UNMAP_NOFREE);
        unmappedBytes += 4096;
        virtaddr.addr = virtaddr.addr + PAGE_SIZE;
    }
    serial << "unmappedBytes " << unmappedBytes << "\n";
    g_early_virtaddr_spc.end = virtaddr.addr - PAGE_SIZE;
}

static pml4_entry* get_pml4_entry(virtaddr_t virtaddr)
{
    return &(((struct pml4_s*) PML4)->entries[virt2pml4Idx(virtaddr.addr)]);
}

static pdp_entry* get_pdp_entry(virtaddr_t virtaddr, pml4_entry *pml4e = nullptr)
{
    if (!pml4e)
        pml4e = get_pml4_entry(virtaddr);
    struct pdp_s* pdp = (struct pdp_s*)(pml4e->addr & ~0xFFF);

    return &pdp->entries[virt2pdpIdx(virtaddr.addr)];
}

static pd_entry* get_pd_entry(virtaddr_t virtaddr, pdp_entry* pdpe = nullptr)
{
    if (!pdpe)
        pdpe = get_pdp_entry(virtaddr);
    struct pd_s* pd = (struct pd_s*)(pdpe->addr & ~0xFFF);

    return &pd->entries[virt2pdIdx(virtaddr.addr)];
}

static pt_entry* get_pt_entry(virtaddr_t virtaddr, pd_entry* pde = nullptr)
{
    if (!pde)
        pde = get_pd_entry(virtaddr);
    struct pt_s* pt = (struct pt_s*)(pde->addr & ~0xFFF);

    return &pt->entries[virt2ptIdx(virtaddr.addr)];
}

void unmap_vmem(virtaddr_t virtaddr, unmap_flags flags)
{
    assert_msg(is_page_aligned(virtaddr), "unmap_vmem: virtaddr not aligned.");

    pml4_entry* pml4;
    pdp_entry* pdp;
    pd_entry* pd;
    pt_entry* pt;

    pml4 = get_pml4_entry(virtaddr);
    if (!pml4->bits.p)
        return;

    pdp = get_pdp_entry(virtaddr, pml4);
    if (!pdp->bits.p)
        return;

    pd = get_pd_entry(virtaddr, pdp);
    if (!pd->bits.p)
        return;

    pt = get_pt_entry(virtaddr, pd);
    if (!pt->bits.p)
        return;

    if (!(flags & UNMAP_NOFREE))
        kfree_page_frame((void*)(pt->addr & ~0xFFF));

    pt->addr = 0x0;
}

/*
 *  Remap a page within virtual address space [KERNEL_VIRT_END, BOOTSTRAP_MAPPING_END].
 *  The return address is a virtual address egal to physical address + KERNEL_VIRT_START.
 *  Mainly use in early stage to allocate page-translation-tables (eg. Page Directory or Page Table).
 */
void *map_bootstrap_page()
{
    assert_msg((g_early_virtaddr_spc.start < g_early_virtaddr_spc.end), "map_bootstrap_page: OUT OF BOOTSTRAP MEM.");

    virtaddr_t virtaddr = {.addr = g_early_virtaddr_spc.start};
    g_early_virtaddr_spc.start = virtaddr.addr + PAGE_SIZE;

    pml4_entry* pml4e = get_pml4_entry(virtaddr);
    if (!pml4e->bits.p)
        pml4e->bits.p = 0b1;
    pdp_entry* pdpe = get_pdp_entry(virtaddr, pml4e);
    if (!pdpe->bits.p)
        pdpe->bits.p = 0b1;
    pd_entry* pde = get_pd_entry(virtaddr, pdpe);
    if (!pde->bits.p)
        pdpe->bits.p = 0b1;
    pt_entry* pte = get_pt_entry(virtaddr, pde);
    pte->addr = virtaddr.addr - (uint64_t)KERNEL_VIRT_START;
    pte->bits.p = 0b1;
    pte->bits.r_w = 0b1;
    return (void*)virtaddr.addr;
}

bool is_address_mapped(void *addr)
{
    SerialStream stream;
    virtaddr_t virtaddr;
    virtaddr.addr = (uintptr_t)addr;

    stream << "Checking virtaddr " << HEX << (uintptr_t)addr << "\n";
    pml4_entry* pml4e = get_pml4_entry(virtaddr);
    stream << "PML4[" << virt2pml4Idx(virtaddr.addr) << "]:" << HEX << pml4e->addr << "\n";
    if (!pml4e->bits.p)
        return false;
    pdp_entry* pdpe = get_pdp_entry(virtaddr, pml4e);
    stream << "PDP[" << virt2pdpIdx(virtaddr.addr) << "]:" << HEX << pdpe->addr << "\n";
    if (!pdpe->bits.p)
        return false;
    pd_entry* pde = get_pd_entry(virtaddr, pdpe);
    stream << "PD[" << virt2pdIdx(virtaddr.addr) << "]:" << HEX << pde->addr << "\n";
    if (!pde->bits.p)
        return false;
    pt_entry* pte = get_pt_entry(virtaddr, pde);
    stream << "PT[" << virt2ptIdx(virtaddr.addr) << "]:" << HEX << pte->addr << "\n";
    if (!pte->bits.p)
        return false;
    return true;
}


void kheap_init();


void init_virtual_memory_manager()
{
    unmap_vmem_kernel_bootstrap();

    kheap_init();

    // Removing identity mapping
    struct pml4_s* pml4 = (struct pml4_s*) PML4;
    pml4->entries[0].bits.p = 0;
}
