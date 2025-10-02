;********************************************************************
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;********************************************************************

bits 64

global starting_long_mode
global load_idt

extern _init
extern kmain
extern init_serial
extern initialize_IDT
extern stack_top
extern gdt64.pointer
extern gdt64.data
extern PML4

section .text
starting_long_mode:
    cli
    mov ax, gdt64.data
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov rax, higher_half
    jmp rax

higher_half:
    mov rsp, stack_top
    push rdi
    push rsi
    mov rax, gdt64.pointer
    lgdt [rax]
    call init_serial
    cmp rax, 0
    jne print_init_failed
    call initialize_IDT
    call load_idt
    call _init
    pop rsi
    pop rdi
    jmp kmain

dead_loop:
    hlt
    jmp dead_loop

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
    lidt [IDT_DESC]
    sti
    ret

print_init_failed:
    mov dword [0xb8000], 0x04520445
    mov dword [0xb8004], 0x043a0452
    mov byte  [0xb800a], al
    hlt

global IDT
global IDT_DESC
section .bss
IDT:
    resb 16 * 256
section .rodata
IDT_DESC:
    dw 16 * 256 - 1
    dq IDT
