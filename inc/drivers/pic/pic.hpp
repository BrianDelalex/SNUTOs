/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PIC_HPP
#define PIC_HPP

# include <cstdint>

# include <drivers/pic/constants.hpp>

void PIC_remap(uint8_t offset1, uint8_t offset2);

#endif //!PIC_HPP