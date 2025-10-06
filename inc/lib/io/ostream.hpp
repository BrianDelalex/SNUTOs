/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef SNUTOS_OSTREAM_HPP
#define SNUTOS_OSTREAM_HPP

# include <stdint.h>

# define OSTREAM_MODE_HEX 0x01
# define OSTREAM_MODE(x) io::ostream_mode(x)
# define HEX OSTREAM_MODE(OSTREAM_MODE_HEX)

namespace io {
    typedef struct ostream_mode_s {
        uint8_t value;
        ostream_mode_s(uint8_t _v) : value(_v) {}
    }ostream_mode;


    class ostream {
    protected:
        ostream_mode m_mode;
    public:
        ostream() : m_mode(0) {};
    private:
        virtual void Write(const char*) = 0;
        virtual void Write(uint64_t);
        virtual void Write(uint32_t);
        virtual void Write(int32_t);
        virtual void WriteHex(uint64_t);
        virtual void WriteHex(uint32_t);
        void Write(const ostream_mode& mode);

        template <class T>
        friend ostream& operator<<(ostream &os, const T&t);
    };

    template<class T>
    ostream& operator<<(ostream &os, const T&t)
    {
        os.Write(t);

        return os;
    }

}
#endif//!SNUTOS_OSTREAM_HPP
