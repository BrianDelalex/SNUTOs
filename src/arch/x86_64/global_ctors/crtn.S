/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

.section .init
	/* gcc will nicely put the contents of crtend.o's .init section here. */
	popq %rbp
	ret

.section .fini
	/* gcc will nicely put the contents of crtend.o's .fini section here. */
	popq %rbp
	ret