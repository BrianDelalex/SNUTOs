/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef VGA_DRIVER_HPP
# define VGA_DRIVER_HPP

# include <cstdint>

# define VGA_WIDTH 80
# define VGA_HEIGHT 25
# define VGA_MEMORY_START 0xb8000
# define VGA_MEMORY_END VGA_MEMORY_START + (VGA_WIDTH * VGA_HEIGHT * sizeof(uint16_t))

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

struct pos8_s {
    uint8_t x;
    uint8_t y;
};

typedef struct pos8_s pos8_t;

class VGA {
    uint8_t m_bg = VGA_COLOR_BLACK;
    uint8_t m_fg = VGA_COLOR_WHITE;
    pos8_t m_pos = {0, 0};
public:
    VGA(void) {};
    void Clear(void);
    void WriteChar(const char c);
    void Write(const char *str);
    void Write(uint32_t nb);
    void Write(int32_t nb);
    void WriteAddress(uintptr_t ptr);
    void WriteAddress(uint32_t ptr);
    void SetPosition(uint8_t x, uint8_t y);
private:
    void WriteToBuffer(uint16_t ch);
    void IncrementPosition(void);
    void NewLinePosition(void);
};

extern "C" void vga_driver_initialize(void);
extern "C" void vga_driver_clear(void);

#endif //!VGA_DRIVER_HPP