global exception0:function
global exception1:function
global exception2:function
global exception3:function
global exception4:function
global exception5:function
global exception6:function
global exception7:function
global exception8:function
global exception9:function
global exception10:function
global exception11:function
global exception12:function
global exception13:function
global exception14:function
global exception15:function
global exception16:function
global exception17:function
global exception18:function
global exception19:function
global exception20:function
global exception21:function
global exception22:function
global exception23:function
global exception24:function
global exception25:function
global exception26:function
global exception27:function
global exception28:function
global exception29:function
global exception30:function
global exception31:function

%include "arch/x86_64/interrupts/exception_handlers.inc"

%macro pushaq 0
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi
%endmacro

%macro popaq 0
    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro

exception0:
    mov rdi, [rsp]
    pushaq
    call exception0_handler
    popaq
    iretq

exception1:
    mov rdi, [rsp]
    pushaq
    call exception1_handler
    popaq
    iretq

exception2:
    mov rdi, [rsp]
    pushaq
    call exception2_handler
    popaq
    iretq

exception3:
    mov rdi, [rsp]
    pushaq
    call exception3_handler
    popaq
    iretq

exception4:
    mov rdi, [rsp]
    pushaq
    call exception4_handler
    popaq
    iretq

exception5:
    mov rdi, [rsp]
    pushaq
    call exception5_handler
    popaq
    iretq

exception6:
    mov rdi, [rsp]
    pushaq
    call exception6_handler
    popaq
    iretq

exception7:
    mov rdi, [rsp]
    pushaq
    call exception7_handler
    popaq
    iretq

exception8:
    mov rdi, [rsp + 8]
    pushaq
    call exception8_handler
    popaq
    iretq

exception9:
    mov rdi, [rsp]
    pushaq
    call exception9_handler
    popaq
    iretq

exception10:
    mov rdi, [rsp + 8]
    pushaq
    call exception10_handler
    popaq
    iretq

exception11:
    mov rdi, [rsp + 8]
    pushaq
    call exception11_handler
    popaq
    iretq

exception12:
    mov rdi, [rsp + 8]
    pushaq
    call exception12_handler
    popaq
    iretq

exception13:
    mov rdi, [rsp + 8]
    pushaq
    call exception13_handler
    popaq
    iretq

exception14:
    mov rdi, [rsp + 8]
    mov rsi, [rsp]
    pushaq
    call exception14_handler
    popaq
    iretq

exception15:
    pushaq
    call exception15_handler
    popaq
    iretq

exception16:
    mov rdi, [rsp]
    pushaq
    call exception16_handler
    popaq
    iretq

exception17:
    mov rdi, [rsp + 8]
    pushaq
    call exception17_handler
    popaq
    iretq

exception18:
    mov rdi, [rsp]
    pushaq
    call exception18_handler
    popaq
    iretq

exception19:
    mov rdi, [rsp]
    pushaq
    call exception19_handler
    popaq
    iretq

exception20:
    mov rdi, [rsp]
    pushaq
    call exception20_handler
    popaq
    iretq

exception21:
    pushaq
    call exception21_handler
    popaq
    iretq

exception22:
    pushaq
    call exception22_handler
    popaq
    iretq

exception23:
    pushaq
    call exception23_handler
    popaq
    iretq

exception24:
    pushaq
    call exception24_handler
    popaq
    iretq

exception25:
    pushaq
    call exception25_handler
    popaq
    iretq

exception26:
    pushaq
    call exception26_handler
    popaq
    iretq

exception27:
    pushaq
    call exception27_handler
    popaq
    iretq

exception28:
    pushaq
    call exception28_handler
    popaq
    iretq

exception29:
    pushaq
    call exception29_handler
    popaq
    iretq

exception30:
    mov rdi, [rsp + 8]
    pushaq
    call exception30_handler
    popaq
    iretq

exception31:
    pushaq
    call exception31_handler
    popaq
    iretq
