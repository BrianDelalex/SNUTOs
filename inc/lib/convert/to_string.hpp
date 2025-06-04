/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef TO_STRING_HPP
# define TO_STRING_HPP

# include <cstdint>

char *to_string(uint32_t nb, char *str, uint32_t max_char_size, uint32_t base);
char *to_string(int32_t nb, char *str, uint32_t max_char_size, uint32_t base);
char *to_hex_string(uintptr_t nb, char *str);
char *to_hex_string(uint32_t nb, char *str);

#endif //!TO_STRING_HPP