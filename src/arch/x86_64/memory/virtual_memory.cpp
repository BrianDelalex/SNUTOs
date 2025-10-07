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

# include <drivers/serial/SerialStream.hpp>

# include <bitwise_op.hpp>

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
static void unmap_vmem_kernel()
{
    virtaddr_t virtaddr;
    virtaddr.addr = align((uintptr_t)KERNEL_VIRT_END, PAGE_SIZE);
    g_early_virtaddr_spc.start = virtaddr.addr;

    while (virtaddr.addr < (uint64_t)BOOTSTRAP_MAPPING_END) {
        unmap_vmem(virtaddr, UNMAP_NOFREE);
        virtaddr.addr = virtaddr.addr + PAGE_SIZE;
    }
    g_early_virtaddr_spc.end = virtaddr.addr - PAGE_SIZE;
}

static pml4_entry* get_pml4_entry(virtaddr_t virtaddr)
{
    return &(((struct pml4_s*) PML4)->entries[virt2pml4Idx(virtaddr)]);
}

static pdp_entry* get_pdp_entry(virtaddr_t virtaddr, pml4_entry *pml4_entry = nullptr)
{
    if (!pml4_entry)
        pml4_entry = get_pml4_entry(virtaddr);
    struct pdp_s* pdp = (struct pdp_s*)(pml4_entry->addr & ~0xFFF);

    return &pdp->entries[virt2pdpIdx(virtaddr)];
}

static pd_entry* get_pd_entry(virtaddr_t virtaddr, pdp_entry* pdp_entry = nullptr)
{
    if (!pdp_entry)
        pdp_entry = get_pdp_entry(virtaddr);
    struct pd_s* pd = (struct pd_s*)(pdp_entry->addr & ~0xFFF);

    return &pd->entries[virt2pdIdx(virtaddr)];
}

static pt_entry* get_pt_entry(virtaddr_t virtaddr, pd_entry* pd_entry = nullptr)
{
    if (!pd_entry)
        pd_entry = get_pd_entry(virtaddr);
    struct pt_s* pt = (struct pt_s*)(pd_entry->addr & ~0xFFF);

    return &pt->entries[virt2ptIdx(virtaddr)];
}

void unmap_vmem(virtaddr_t virtaddr, unmap_flags flags)
{
    if (!is_page_aligned(virtaddr))
        return;

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

void init_virtual_memory_manager()
{
    unmap_vmem_kernel();
}
