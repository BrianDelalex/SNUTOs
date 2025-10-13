/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef SNUTOS_ALLOC_HPP
#define SNUTOS_ALLOC_HPP

# include <stdint.h>

typedef uint64_t size_t;

void* kmalloc(size_t size);
void kfree(void* addr);

#endif//!SNUTOS_ALLOC_HPP
