/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PAGING_HPP
#define PAGING_HPP

# include <stdint.h>

struct pml4_s {
    uint64_t entries[512];
};

static_assert(sizeof(struct pml4_s) == 4096, "struct pml4_s invalid size");

struct pdp_s {
    uint64_t entries[512];
};

static_assert(sizeof(struct pdp_s) == 4096, "struct pdp_s invalid size");

struct pd_s {
    uint64_t entries[512];
};

static_assert(sizeof(struct pd_s) == 4096, "struct pd_s invalid size");
struct __attribute__((__packed__)) pt_entry_s {
        uint8_t p : 1;
        uint8_t r_w : 1;
        uint8_t u_s : 1;
        uint8_t pwt : 1;
        uint8_t pcd : 1;
        uint8_t a : 1;
        uint8_t d : 1;
        uint8_t pat : 1;
        uint8_t g : 1;
        uint8_t avl_1 : 3;
        uint64_t addr : 37;
        uint8_t reserved : 4;
        uint8_t avl_2 : 6;
        uint8_t pk : 4;
        uint8_t xd : 1;
};

union pt_entry_u {
    uint64_t entry;
    struct pt_entry_s bits;
};

struct pt_s {
    union pt_entry_u entries[512];
};

static_assert(sizeof(struct pt_entry_s) == 8, "struct pt_entry_s invalid size");

static_assert(sizeof(union pt_entry_u) == 8, "union pt_entry_u invalid size");

static_assert(sizeof(struct pt_s) == 4096, "struct pt_s invalid size");

#endif//!PAGING_HPP
