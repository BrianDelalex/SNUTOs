global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

%include "arch/x86_64/interrupts/irq_handlers.inc"

%macro pushaq 0
    push rax
    push rcx
    push rdx
    push rbx
    push rsp
    push rbp
    push rsi
    push rdi
%endmacro

%macro popaq 0
    pop rdi
    pop rsi
    pop rbp
    pop rsp
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro

irq0:
  pushaq
  call irq0_handler
  popaq
  iretq

irq1:
  pushaq
  call irq1_handler
  popaq
  iretq

irq2:
  pushaq
  call irq2_handler
  popaq
  iretq

irq3:
  pushaq
  call irq3_handler
  popaq
  iretq

irq4:
  pushaq
  call irq4_handler
  popaq
  iretq

irq5:
  pushaq
  call irq5_handler
  popaq
  iretq

irq6:
  pushaq
  call irq6_handler
  popaq
  iretq

irq7:
  pushaq
  call irq7_handler
  popaq
  iretq

irq8:
  pushaq
  call irq8_handler
  popaq
  iretq

irq9:
  pushaq
  call irq9_handler
  popaq
  iretq

irq10:
  pushaq
  call irq10_handler
  popaq
  iretq

irq11:
  pushaq
  call irq11_handler
  popaq
  iretq

irq12:
  pushaq
  call irq12_handler
  popaq
  iretq

irq13:
  pushaq
  call irq13_handler
  popaq
  iretq

irq14:
  pushaq
  call irq14_handler
  popaq
  iretq

irq15:
  pushaq
  call irq15_handler
  popaq
  iretq