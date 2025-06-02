;********************************************************************
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;********************************************************************

global starting_long_mode
extern kmain
extern _init
section .text
bits 64
starting_long_mode:
    call clear_data_segment_reg
    call _init
    call kmain
    hlt

clear_data_segment_reg:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ret