/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/vga/vga.hpp>
# include <convert/to_string.hpp>

VGA vga;


int strlen(const char *str);

int strlen(const char *str)
{
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

VGA::VGA() : io::ostream()
{
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
        if (str[i] == '\n') {
            NewLinePosition();
        } else {
            WriteChar(str[i]);
            IncrementPosition();
        }
    }
}

void VGA::SetPosition(uint8_t x, uint8_t y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void VGA::SetColor(uint8_t bg, uint8_t fg)
{
    m_bg = bg;
    m_fg = fg;
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

void VGA::NewLinePosition()
{
    if (m_pos.y + 1 >= VGA_HEIGHT) {
        m_pos.y = 0;
        m_pos.x = 0;
    } else {
        m_pos.y++;
        m_pos.x = 0;
    }
}
