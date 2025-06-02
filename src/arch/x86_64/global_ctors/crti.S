/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

.section .init
.global _init
.type _init, @function
_init:
	push %rbp
	movq %rsp, %rbp
	/* gcc will nicely put the contents of crtbegin.o's .init section here. */

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %rbp
	movq %rsp, %rbp
	/* gcc will nicely put the contents of crtbegin.o's .fini section here. */