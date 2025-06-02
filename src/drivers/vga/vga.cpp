/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/vga/vga.hpp>
# include <convert.hpp>

VGA vga;

int strlen(const char *str)
{
    int i = 0;
    while (str[i]);
    return i;
}

extern "C" void vga_driver_initialize()
{
    const char *welcomeMsg = "Welcome to SNUTOs";
    vga.Clear();
    vga.SetPosition(VGA_WIDTH / 2 - strlen(welcomeMsg) / 2, VGA_HEIGHT / 2);
    vga.Write(welcomeMsg);
}

extern "C" void vga_driver_clear()
{
    vga.Clear();
}

void VGA::Clear()
{
    uint16_t *buffer = (uint16_t *) VGA_MEMORY_START;

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        *buffer = 0x0000;
        buffer = ((uint16_t *)((uintptr_t)buffer + sizeof(uint16_t)));
    }
    m_pos = {0, 0};
}

void VGA::WriteToBuffer(uint16_t ch)
{
    uint16_t *buffer = (uint16_t *) ((uintptr_t)VGA_MEMORY_START + ((m_pos.y * VGA_WIDTH + m_pos.x) * sizeof(uint16_t)));
    *buffer = ch;
}

void VGA::WriteChar(const char c)
{
    uint16_t _ch;
    _ch = (m_bg & 0xf) << 12;
    _ch = _ch + ((m_fg & 0xf) << 8);
    _ch = _ch + (c & 0xff);
    WriteToBuffer(_ch);
}

void VGA::Write(const char *str)
{
    for (int i = 0; str[i]; i++) {
        WriteChar(str[i]);
        IncrementPosition();
    }
}

void VGA::WriteAddress(uintptr_t ptr)
{
    Write("0x");
    char str[9];
    char c;
    for (int i = 7; i >= 0; i--) {
        c = ptr % 16;
        if (c > 10)
            c += 55;
        else
            c += 48;
        str[i] = c;
        ptr = ptr / 16;
    }
    str[8] = 0;
    Write(str);
}

void VGA::SetPosition(uint8_t x, uint8_t y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void VGA::IncrementPosition()
{
    if (m_pos.x + 1 >= VGA_WIDTH) {
        m_pos.x = 0;
        m_pos.y++;
    } else {
        m_pos.x++;
    }
}