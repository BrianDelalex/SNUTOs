/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/serial/SerialStream.hpp>
# include <drivers/serial/serial.hpp>

# include <convert/to_string.hpp>

SerialStream::SerialStream() : io::ostream() {}

void SerialStream::Write(const char* str)
{
    write_serial(str);
}
