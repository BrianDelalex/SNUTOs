/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef SNUTOS_ASSERT_HPP
#define SNUTOS_ASSERT_HPP

# include <kernel/core/panic.hpp>

# define assert_msg(expr, msg) \
        if (!(expr))    \
            panic(msg);

#endif//!SNUTOS_ASSERT_HPP
