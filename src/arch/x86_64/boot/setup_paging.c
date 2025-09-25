/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# define BOOT 1

# include "arch/x86_64/memory/paging.h"

asm(".code32");

void setup_paging()
{
    extern const char PML4[];
    extern const char PDP[];
    extern const char PD[];
    extern const char PT[];

    struct pml4_s* pml4 = (struct pml4_s*)PML4;
    struct pdp_s* pdp = (struct pdp_s*)PDP;
    struct pd_s* pd = (struct pd_s*)PD;
    struct pt_s* pt = (struct pt_s*)PT;
    uint64_t pdp_addr = (uint32_t)pdp;
    uint64_t pd_addr = (uint32_t)pd;
    uint64_t pt_addr;

    // present + writable
    pdp_addr = pdp_addr | 0b11;
    pml4->entries[0] = pdp_addr;

    // present + writable
    pd_addr = pd_addr | 0b11;
    pdp->entries[0] = pd_addr;

    for (int pt_index = 0; pt_index < 512; pt_index++) {
        pt_addr = ((uint32_t)PT) + 4096 * pt_index;
        pt_addr |= 0b11;
        pd->entries[pt_index] = pt_addr;

        for (int i = 0; i < 512; i++) {
            union pt_entry_u page_base_addr;
            page_base_addr.entry = 4096 * i + (512 * pt_index * 4096);
            page_base_addr.bits.p |= 0b1;
            page_base_addr.bits.r_w |= 0b1;

            pt[pt_index].entries[i] = page_base_addr;
        }
    }
}
