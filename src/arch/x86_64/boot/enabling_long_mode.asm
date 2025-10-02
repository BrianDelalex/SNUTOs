;********************************************************************
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;********************************************************************

%include "arch/x86_64/boot/boot.inc"

bits 32
global enabling_long_mode
extern starting_long_mode
extern setup_paging

section .boot.text
enabling_long_mode:
    push edi
    push esi
    call set_up_page_tables

    call enable_paging


    mov eax, gdt64_phys_ptr
    lgdt [eax]

    pop esi
    pop edi

    jmp gdt64.code:(VIRT2PHYS(starting_long_mode))

    mov dword [0xb8000], 0x04520445
    mov dword [0xb8004], 0x043a0452
    mov byte  [0xb800a], al
    hlt


enable_paging:

    ; load P4 to cr3 register (cpu uses this to access the P4 table)
    mov eax, VIRT2PHYS(PML4)
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
    mov eax, VIRT2PHYS(PDP)
    or eax, 0b11 ; present + writable
    mov [VIRT2PHYS(PML4)], eax
    mov [VIRT2PHYS(PML4) + 8 * 511], eax

    ; map first PDP entry to PD table
    mov eax, VIRT2PHYS(PD)
    or eax, 0b11 ; present + writable
    mov [VIRT2PHYS(PDP)], eax
    mov [VIRT2PHYS(PDP) + 8 * 510], eax

    ; map each PD entry to a huge 2MiB page
    mov ecx, 0         ; counter variable
.map_pd_table:
    ; map ecx-th P2 entry to a huge page that starts at address 2MiB*ecx
    mov eax, 0x200000  ; 2MiB
    mul ecx            ; start address of ecx-th page
    or eax, 0b10000011 ; present + writable + huge
    mov [VIRT2PHYS(PD) + ecx * 8], eax ; map ecx-th entry

    inc ecx            ; increase counter
    cmp ecx, 512       ; if counter == 512, the whole P2 table is mapped
    jne .map_pd_table  ; else map the next entry

    ret

section .bss
global PML4
global PDP
global PD
global PT
align 4096
PML4:
    resb 4096
PDP:
    resb 4096
PD:
    resb 4096
PT:
    resb 2097152

global gdt64
global gdt64.pointer
global gdt64.data
section .rodata
align 16
gdt64:
    dq 0;
.code: equ $ - gdt64
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10011010b
    ;;   5: 64-bit code segment flag indicates that this segment contains 64-bit code
    ;;   6: must be zero if L bit (bit 5) is set
    db 10101111b
    db 0x00
.data: equ $ - gdt64
    dw 0xffff
    dw 0x0000
    db 0x00
    ;; 0-3: segment type that specifies a read/write data segment
    db 10010010b
    db 10101111b
    db 0x00
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

section .boot.rodata
gdt64_phys_ptr:
    dw gdt64.pointer - gdt64 - 1
    dq VIRT2PHYS(gdt64)
