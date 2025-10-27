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
# include <arch/x86_64/memory/virtual_memory.hpp>

# include <kernel/core/Kernel.hpp>

extern Kernel g_kernel;

/*
    Allocate a size bytes and returns a pointer to allocated memory.
    Rounds the size of allocation up to the next multiple of the system page size.
*/
void* pvalloc(size_t size)
{
    return g_kernel.Vmm().Map(size);
}

/*
    Free memory allocated using pvalloc.
 */
void pvfree(void* ptr)
{
    return g_kernel.Vmm().Unmap(ptr);
}

/*
    Allocate 'size' bytes using kernel Heap and return a pointer to allocated memory.
 */
void* kmalloc(size_t size)
{
    return g_kernel.KHeap().Alloc(size);
}

/*
    Free kernel heap memory allocated using kmalloc.
 */
void kfree(void* addr)
{
    g_kernel.KHeap().Free(addr);
}
