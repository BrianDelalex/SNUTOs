/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */

OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

PROVIDE(KERNEL_VIRT_START = 0xFFFFFFFF80000000);

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
    . = 2M;

    /* Multiboot2 header */
    .multiboot BLOCK(4K) : ALIGN(4K)
    {
        /* link the multiboot struct here */
        KEEP(*(.multiboot))
    }

    .boot.text BLOCK(4K) : ALIGN(4K)
    {
        *(.boot.text)
        *(.boot.bss)
        *(.boot.rodata)
        *(.boot.data)
    }

    . += KERNEL_VIRT_START;
    .text BLOCK(4K) : AT(ADDR(.text) - KERNEL_VIRT_START) ALIGN(4K)
    {
        *(.init)
        *(.ctors)
        *(.text)
        *(.dtors)
        *(.fini)
    }

    .rodata BLOCK(4K) : AT(ADDR(.rodata) - KERNEL_VIRT_START) ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : AT(ADDR(.data) - KERNEL_VIRT_START) ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : AT(ADDR(.bss) - KERNEL_VIRT_START) ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

    . = ALIGN(0x1000);
    PROVIDE(KERNEL_VIRT_END = .);
}
