;********************************************************************
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;********************************************************************

global start

extern enabling_long_mode

section .text
bits 32
start:
    mov esp, stack_top
    push eax
    push ebx
    call check_multiboot2_magic_number
    call check_cpuid
    call check_long_mode
    pop esi
    pop edi
    call enabling_long_mode

check_multiboot2_magic_number:
    cmp eax, 0x36D76289
    jne .no_mulitboot
    ret
.no_mulitboot:
    mov al, "0"
    jmp print_error

check_cpuid:
    ; Check if CPUID is supported by attempting to flip the ID bit (bit 21)
    ; in the FLAGS register. If we can flip it, CPUID is available.

    pushfd
    pop eax

    mov ecx, eax

    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    cmp eax, ecx
    je .no_cpuid
    ret
.no_cpuid:
    mov al, "1"
    jmp print_error

check_long_mode:
    ; test if extended processor info in available
    mov eax, 0x80000000    ; implicit argument for cpuid
    cpuid                  ; get highest supported argument
    cmp eax, 0x80000001    ; it needs to be at least 0x80000001
    jb .no_long_mode       ; if it's less, the CPU is too old for long mode

    ; use extended info to test if long mode is available
    mov eax, 0x80000001    ; argument for extended processor info
    cpuid                  ; returns various feature bits in ecx and edx
    test edx, 1 << 29      ; test if the LM-bit is set in the D-register
    jz .no_long_mode       ; If it's not set, there is no long mode
    ret
.no_long_mode:
    mov al, "2"
    jmp print_error

print_error:
    mov dword [0xb8000], 0x04520445
    mov dword [0xb8004], 0x043a0452
    mov byte  [0xb800a], al
    hlt

section .bss
align 4096
stack_bottom:
    RESB 0x1000
stack_top: