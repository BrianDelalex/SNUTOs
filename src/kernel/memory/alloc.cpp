/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <kernel/memory/alloc.hpp>

# include <arch/x86_64/memory/kheap.hpp>

extern KHeap g_kheap;

/*
    Allocate a size bytes and returns a pointer to allocated memory.
    Rounds the size of allocation up to the next multiple of the system page size.
*/
//void* pvalloc(size_t size)
//{

//}

void* kmalloc(size_t size)
{
    return g_kheap.Alloc(size);
}

void kfree(void* addr)
{
    g_kheap.Free(addr);
}
