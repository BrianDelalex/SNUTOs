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
# include <kernel/memory/alloc.hpp>

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

static uintptr_t clear_addr_ctrl_bits(uintptr_t addr)
{
    return addr & ~0xFFF;
}

static uintptr_t virt2phys(uintptr_t virt)
{
    return virt - ((uintptr_t)KERNEL_VIRT_START);
}

static pml4_entry* get_pml4_entry(virtaddr_t virtaddr)
{
    return &(((struct pml4_s*) PML4)->entries[virtaddr.bitfield.pml4_offset]);
}

static pdp_entry* get_pdp_entry(virtaddr_t virtaddr, pml4_entry *pml4e = nullptr)
{
    if (!pml4e)
        pml4e = get_pml4_entry(virtaddr);
    struct pdp_s* pdp = (struct pdp_s*)(pml4e->addr & ~0xFFF);

    return &pdp->entries[virtaddr.bitfield.pdp_offset];
}

static pd_entry* get_pd_entry(virtaddr_t virtaddr, pdp_entry* pdpe = nullptr)
{
    if (!pdpe)
        pdpe = get_pdp_entry(virtaddr);
    struct pd_s* pd = (struct pd_s*)(pdpe->addr & ~0xFFF);

    return &pd->entries[virtaddr.bitfield.pd_offset];
}

static pt_entry* get_pt_entry(virtaddr_t virtaddr, pd_entry* pde = nullptr)
{
    if (!pde)
        pde = get_pd_entry(virtaddr);
    struct pt_s* pt = (struct pt_s*)(pde->addr & ~0xFFF);

    return &pt->entries[virtaddr.bitfield.pt_offset];
}

static pml4_entry* set_pml4_entry(virtaddr_t virtaddr, uintptr_t pml4e)
{
    struct pml4_s* pml4 = (struct pml4_s*) PML4;
    pml4->entries[virtaddr.bitfield.pml4_offset].addr = pml4e;

    return &pml4->entries[virtaddr.bitfield.pml4_offset];
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

void map_vmem(uintptr_t vaddr)
{
    SerialStream serial;
    virtaddr_t virtaddr;
    virtaddr.addr = vaddr;
    assert_msg(is_page_aligned(virtaddr), "map_vmem: virtaddr not aligned.");

    pml4_entry* pml4e;
    pdp_entry* pdpe;
    pd_entry* pde;
    pt_entry* pte;

    pml4e = get_pml4_entry(virtaddr);
    if (!pml4e->bits.p) {
        if (pml4e->addr == 0x0) {
            void* pdp = map_bootstrap_page();
            pml4e = set_pml4_entry(virtaddr, virt2phys(((uintptr_t)pdp)));
        }
        pml4e->bits.p = 0b1;
        pml4e->bits.r_w = 0b1;
    }

    struct pdp_s* pdp = (struct pdp_s*)clear_addr_ctrl_bits((uintptr_t)pml4e->addr);
    pdpe = &pdp->entries[virtaddr.bitfield.pdp_offset];
    if (!pdpe->bits.p) {
        if (pdpe->addr == 0x0) {
            void *pd = map_bootstrap_page();
            pdpe->addr = virt2phys((uintptr_t)pd);
        }
        pdpe->bits.p = 0b1;
        pdpe->bits.r_w = 0b1;
    }

    struct pd_s *pd = (struct pd_s*)clear_addr_ctrl_bits((uintptr_t)pdpe->addr);
    pde = &pd->entries[virtaddr.bitfield.pd_offset];
    if (!pde->bits.p) {
        if (pde->addr == 0x0) {
            void *pt = map_bootstrap_page();
            pde->addr = virt2phys((uintptr_t)pt);
        }
        pde->bits.p = 0b1;
        pde->bits.r_w = 0b1;
    }

    struct pt_s* pt = (struct pt_s*)clear_addr_ctrl_bits((uintptr_t)pde->addr);
    pte = &pt->entries[virtaddr.bitfield.pt_offset];
    if (!pte->bits.p) {
        if (pte->addr == 0x0) {
            void *page = kalloc_page_frame();
            pte->addr = (uintptr_t)page;
        }
        pte->bits.p = 0b1;
        pte->bits.r_w = 0b1;
    }
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
    pte->addr = virt2phys(virtaddr.addr);
    pte->bits.p = 0b1;
    pte->bits.r_w = 0b1;
    return (void*)virtaddr.addr;
}

bool is_address_mapped(void *addr)
{
    virtaddr_t virtaddr;
    virtaddr.addr = (uintptr_t)addr;

    pml4_entry* pml4e = get_pml4_entry(virtaddr);
    if (!pml4e->bits.p)
        return false;

    pdp_entry* pdpe = get_pdp_entry(virtaddr, pml4e);
    if (!pdpe->bits.p)
        return false;

    pd_entry* pde = get_pd_entry(virtaddr, pdpe);
    if (!pde->bits.p)
        return false;
    // If page_size is set the address is mapped to a 2MiB page.
    if (pde->bits.page_size)
        return true;


    pt_entry* pte = get_pt_entry(virtaddr, pde);
    if (!pte->bits.p)
        return false;

    return true;
}

/*
 * Unmapped memory after KERNEL_VIRT_END.
 */
static void unmap_vmem_kernel_bootstrap()
{
    SerialStream serial;
    virtaddr_t virtaddr;
    virtaddr.addr = (uintptr_t)KERNEL_VIRT_END;
    g_early_virtaddr_spc.start = virtaddr.addr;
    uint32_t unmappedBytes = 0;

    while (virtaddr.addr < (uintptr_t)BOOTSTRAP_MAPPING_END) {
        unmap_vmem(virtaddr, UNMAP_NOFREE);
        unmappedBytes += 4096;
        virtaddr.addr = virtaddr.addr + PAGE_SIZE;
    }
    serial << "unmappedBytes " << unmappedBytes << "\n";
    g_early_virtaddr_spc.end = virtaddr.addr - PAGE_SIZE;
    serial << "g_early_virtaddr_spc.end: " << HEX << g_early_virtaddr_spc.end << "\n";
}

VirtualMemoryManager::VirtualMemoryManager() {}

void VirtualMemoryManager::Init()
{
    m_virt_spaces_used = &g_reserved_kheap_data_virtaddr_spc;

    virtaddr_space_list_t* unused =
        (virtaddr_space_list_t*) kmalloc(sizeof(virtaddr_space_list_t));
    unused->space.start = BOOTSTRAP_MAPPING_END;
    unused->space.end = MAX_VIRT_ADDRESS;
    unused->next = nullptr;

    m_virt_spaces_free = unused;
    ShowState();
}

void* VirtualMemoryManager::Map(size_t size)
{
    size_t aligned = align(size, PAGE_SIZE);
    virtaddr_space_list_t* ptr = m_virt_spaces_free;

    while (ptr) {
        if (ptr->space.end - ptr->space.start > aligned) {
            virtaddr_space_list_t* new_spc =
                (virtaddr_space_list_t*) kmalloc(sizeof(virtaddr_space_list_t));
            new_spc->space.start = ptr->space.start;
            new_spc->space.end = new_spc->space.start + aligned;
            ptr->space.start = new_spc->space.end;
            AppendUsedSpace(new_spc);
            for (uintptr_t addr = new_spc->space.start; addr != new_spc->space.end; addr += PAGE_SIZE) {
                map_vmem(addr);
            }
            return (void*)new_spc->space.start;
        }

        if (align(ptr->space.end - ptr->space.start, PAGE_SIZE) == aligned) {
            AppendUsedSpace(ptr);
            RemoveFreeSpace(ptr, false);
            for (uintptr_t addr = ptr->space.start; addr != ptr->space.end; addr = addr + PAGE_SIZE) {
                map_vmem(addr);
            }
            return (void*)ptr->space.start;
        }
        ptr = ptr->next;
    }
    panic("VirtualMemoryManager::Map: Out of Virtual address space");
    return nullptr;
}

void VirtualMemoryManager::ShowState()
{
    SerialStream serial;
    serial << "Used virtual address spaces:\n";
    virtaddr_space_list_t* ptr = m_virt_spaces_used;
    while (ptr) {
        serial << "[ " << HEX << ptr->space.start << \
            " -> " << HEX << ptr->space.end << " ]\n";
        ptr = ptr->next;
    }
    serial << "Free virtual address space:\n";
    ptr = m_virt_spaces_free;
    while (ptr) {
        serial << "[ " << HEX << ptr->space.start << \
            " -> " << HEX << ptr->space.end << " ]\n";
        ptr = ptr->next;
    }
}

void VirtualMemoryManager::AppendUsedSpace(virtaddr_space_list_t* space)
{
    virtaddr_space_list_t* ptr = m_virt_spaces_used;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = space;
}

void VirtualMemoryManager::RemoveFreeSpace(virtaddr_space_list_t* space, bool free)
{
    virtaddr_space_list_t* ptr = m_virt_spaces_free;
    virtaddr_space_list_t* last = ptr;

    if (ptr == space) {
        m_virt_spaces_free = ptr->next;
        if (free)
            kfree(ptr);
    }

    while (ptr) {
        if (ptr == space) {
            last->next = ptr->next;
            if (free)
                kfree(ptr);
        }
        last = ptr;
        ptr = ptr->next;
    }
}

void kheap_init();
void init_virtual_memory_manager()
{
    unmap_vmem_kernel_bootstrap();

    kheap_init();
    // Removing identity mapping
    struct pml4_s* pml4 = (struct pml4_s*) PML4;
    //pml4->entries[0].bits.p = 0;
}
