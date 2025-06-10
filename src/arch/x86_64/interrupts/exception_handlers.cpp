/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <cstdint>
# include <sys/io.h>

# include <drivers/vga/vga.hpp>
# include <drivers/pic/constants.hpp>

extern VGA vga;


# define SET_VGA_PANIC_COLOR() vga.SetColor(VGA_COLOR_WHITE, VGA_COLOR_RED)

extern "C" void exception0_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write("Divide Error at: ");
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception1_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception2_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception3_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception4_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception5_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception6_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception7_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception8_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception9_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception10_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception11_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception12_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception13_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception14_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception15_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception16_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception17_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception18_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception19_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception20_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception21_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception22_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception23_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception24_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception25_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception26_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception27_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception28_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception29_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception30_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}

extern "C" void exception31_handler(uint64_t exceptionAddr)
{
    END_OF_INTERRUPT();
    SET_VGA_PANIC_COLOR();
    vga.Clear();
    vga.Write(__FUNCTION__);
    vga.WriteAddress(exceptionAddr);
    asm volatile("cli; hlt");
}