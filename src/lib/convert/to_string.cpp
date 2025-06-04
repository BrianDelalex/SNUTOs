/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <convert/to_string.hpp>

char *to_string(uint32_t nb, char *str, uint32_t max_char_size, uint32_t base)
{
    int i = max_char_size - 1;
    if (nb == 0) {
        str[i] = '0';
        return (&(str[i]));
    }
    for (; i >= 0 && nb > 0; i--) {
        str[i] = ((char)(nb % base) + 48);
        nb = nb / base;
    }

    str[max_char_size] = 0;
    return (&(str[i + 1]));
}


char *to_string(int32_t nb, char *str, uint32_t max_char_size, uint32_t base)
{
    int i = max_char_size - 1;
    bool neg = nb < 0;
    if (nb == 0) {
        str[i] = '0';
        return (&(str[i]));
    }
    if (neg)
        nb = nb * -1;
    for (; i >= 0 && nb > 0; i--) {
        str[i] = ((char)(nb % base) + 48);
        nb = nb / base;
    }
    if (neg) {
        str[i] = '-';
        i--;
    }

    str[max_char_size] = 0;
    return (&(str[i + 1]));
}

static char dec_to_hex_char(uint8_t dec)
{
    if (dec >= 10)
        return (((char)dec + 55));
    else
        return (((char)dec + 48));
}

static char *to_hex_string(uintptr_t nb, char *str, uint32_t max_char_size)
{
    for (int i = max_char_size - 1; i >= 0; i--) {
        str[i] = dec_to_hex_char((uint8_t(nb % 16)));
        nb = nb / 16;
    }
    str[max_char_size] = 0;
    return str;
}

char *to_hex_string(uintptr_t nb, char *str)
{
    return to_hex_string(nb, str, 16);
}

char *to_hex_string(uint32_t nb, char *str)
{
    return to_hex_string((uintptr_t)nb, str, 8);
}