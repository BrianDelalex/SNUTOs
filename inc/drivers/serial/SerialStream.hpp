/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef SERIAL_STREAM_HPP
#define SERIAL_STREAM_HPP

# include <io/ostream.hpp>

class SerialStream : public io::ostream {
public:
    SerialStream();
    void Write(const char *str) override;
};

#endif//SERIAL_STREAM_HPP
