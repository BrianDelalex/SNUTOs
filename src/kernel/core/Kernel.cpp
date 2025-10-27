/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <kernel/core/Kernel.hpp>

# include <arch/x86_64/memory/virtual_memory.hpp>

void Kernel::Init()
{
    InitVMM();
}

KHeap &Kernel::KHeap()
{
    return m_kheap;
}

VirtualMemoryManager &Kernel::Vmm()
{
    return m_vmm;
}

void Kernel::InitVMM()
{
    unmap_vmem_kernel_bootstrap();
    m_kheap.Init();

    m_vmm.Init();
}
