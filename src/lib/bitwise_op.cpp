/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdint.h>

uintptr_t align(uintptr_t size, uint64_t bytes)
{
    return ((size + (bytes - 1)) & ~(bytes - 1));
}
