;********************************************************************
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;********************************************************************

global enabling_long_mode
extern starting_long_mode
section .text
bits 32
enabling_long_mode:
    push edi
    push esi
    call set_up_page_tables
    call enable_paging
    lgdt [gdt64.pointer]
    pop esi
    pop edi

    jmp gdt64.code:starting_long_mode

    hlt

enable_paging:
    ; load P4 to cr3 register (cpu uses this to access the P4 table)
    mov eax, PML4
    mov cr3, eax

    ; setting bit 5 of CR4 (enabling physical address extension)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; set the long mode bit in the EFER MSR (model specific register)
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    
    ; enable paging in the cr0 register
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

; Mapping kernel's first gigabytes by using a 512 2MiB pages.
set_up_page_tables:
    ; map first PML4 entry to PDP table
    mov eax, PDP
    or eax, 0b11 ; present + writable
    mov [PML4], eax

    ; map first PDP entry to PD table
    mov eax, PD
    or eax, 0b11 ; present + writable
    mov [PDP], eax

    ; map each PD entry to a huge 2MiB page
    mov ecx, 0         ; counter variable
.map_pd_table:
    ; map ecx-th P2 entry to a huge page that starts at address 2MiB*ecx
    mov eax, 0x200000  ; 2MiB
    mul ecx            ; start address of ecx-th page
    or eax, 0b10000011 ; present + writable + huge
    mov [PD + ecx * 8], eax ; map ecx-th entry

    inc ecx            ; increase counter
    cmp ecx, 512       ; if counter == 512, the whole P2 table is mapped
    jne .map_pd_table  ; else map the next entry

    ret

section .bss
align 4096
PML4:
    resb 4096
PDP:
    resb 4096
PD:
    resb 4096

section .rodata
gdt64:
    dq 0;
.code: equ $ - gdt64
    dq (1<<41) | (1<<43) | (1<<44) | (1<<47) | (1<<53) | (1<<55); code segment (Access byte = 0x9A, Flags 0xA)
.data: equ $ - gdt64
    dq (1<<41) | (1<<44) | (1<<47) | (1<<54) | (1<<55); data segment (Access byte = 0x92, Flags 0xC)
.user_code: equ $ - gdt64
    dq (1<<41) | (1<<43) | (1<<44) | (1<<45) | (1<<46) | (1<<47) | (1<<53) | (1<<55); user code segment (Access byte = 0xFA, Flags 0xA)
.user_data: equ $ - gdt64
    dq (1<<41) | (1<<44) | (1<<45)| (1<<46) | (1<<47) | (1<<54) | (1<<55); user data segment (Access byte = 0xF2, Flags 0xC)
;TODO add Take State segment (TSS)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64