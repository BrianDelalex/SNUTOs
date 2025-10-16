# SNUTOs
SNUTOs is a kernel targeting the x86_64 architecture. Developed using x86_64 assembly (nasm syntax) and C++. It is built purely for the joy of learning about operating system at a low level.

# Roadmap
 - [x] Boot
    - [x] Multiboot2
    - [x] Paging setup
    - [x] GDT setup
    - [x] IDT setup (interrupts handling)
    - [x] Init PIC
    - [x] Init Serial ports
    - [x] Loading kernel in higher half
 - [ ] Functionnality
    - [x] VGA
    - [x] Basic Memory manager
        - [x] Basic Physical memory manager
        - [x] Basic Virtual memory manager
        - [x] KHeap/kmalloc/kfree
    - [ ] Scheduler
    - [ ] Filesystem
    - [ ] Timer
    - [ ] PS/2 Keyboard
