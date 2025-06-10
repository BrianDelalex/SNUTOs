;********************************************************************
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;********************************************************************

global starting_long_mode
global load_idt
extern kmain
extern _init
extern initialize_IDT
section .text
bits 64
starting_long_mode:
    push rdi
    push rsi
    call clear_data_segment_reg
    call _init
    call initialize_IDT
    pop rsi
    pop rdi
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

load_idt:
    cli
    lidt [rdi]
    sti
    ret