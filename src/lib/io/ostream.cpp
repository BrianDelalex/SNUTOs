/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <lib/io/ostream.hpp>
# include <lib/convert/to_string.hpp>

namespace io {
    void ostream::Write(const ostream_mode& mode)
    {
        m_mode = mode;
    }


    void ostream::Write(int32_t nb)
    {
        int max_char_size = 11;
        char str[max_char_size + 1];
        char *str2 = to_string(nb, str, max_char_size, 10);
        Write(str2);
    }

    void ostream::Write(uint32_t nb)
    {
        if (m_mode.value & OSTREAM_MODE_HEX) {
            WriteHex(nb);
            m_mode.value = 0;
            return;
        }

        int max_char_size = 10;
        char str[max_char_size + 1];
        char *str2 = to_string(nb, str, max_char_size, 10);
        Write(str2);
    }

    void ostream::Write(uint64_t nb)
    {
        if (m_mode.value & OSTREAM_MODE_HEX) {
            WriteHex(nb);
            m_mode.value = 0;
            return;
        }
        int max_char_size = 20;
        char str[max_char_size + 1];
        char *str2 = to_string(nb, str, max_char_size, 10);
        Write(str2);
    }

    void ostream::WriteHex(uint32_t addr)
    {
        Write("0x");
        char str[9];
        char *str2 = to_hex_string(addr, str);
        Write(str2);
    }

    void ostream::WriteHex(uint64_t addr)
    {
        Write("0x");
        char str[17];
        char *str2 = to_hex_string(addr, str);
        Write(str2);
    }
}
