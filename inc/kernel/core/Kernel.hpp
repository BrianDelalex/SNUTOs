/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef SNUTOS_KERNEL_HPP
# define SNUTOS_KERNEL_HPP

# include <arch/x86_64/memory/kheap.hpp>
# include <arch/x86_64/memory/virtual_memory.hpp>

class Kernel {
    KHeap m_kheap;
    VirtualMemoryManager m_vmm;
public:
    Kernel() = default;
    void Init();
    KHeap &KHeap(void);
    VirtualMemoryManager &Vmm(void);
private:
    void InitVMM();
};

#endif//!SNUTOS_KERNEL_HPP
