/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/multiboot/multiboot_info.hpp>
# include <drivers/vga/vga.hpp>


extern VGA vga;
extern multiboot_info *mb_info;
multiboot_info_tags mb_info_tags;

uintptr_t align(uintptr_t size, uint32_t bytes)
{
    uint32_t n = bytes - 1;
    return ((size + n) & ~n);
}

void show_memory_map_infos()
{
    mb_memory_map_tag *map = mb_info_tags.mmap;
    vga.Clear();
    vga.Write("Memory map:\n");
    vga.Write("size: ");
    vga.Write(map->size);
    vga.Write(" entry_size: ");
    vga.Write(map->entry_size);
    vga.Write(" entry_version: ");
    vga.Write(map->entry_version);
    vga.Write("\n");

    int count = (map->size) / map->entry_size;
    for (int i = 0; i < count; i++) {
        vga.Write("base_addr: ");
        vga.WriteAddress(((uintptr_t)map->entries[i].base_addr));
        vga.Write(" lenght: ");
        vga.WriteAddress(((uintptr_t)map->entries[i].lenght));
        vga.Write(" type: ");
        vga.Write(map->entries[i].type);
        vga.Write("\n");
    }
}

void parse_multiboot_infos_tags()
{
    multiboot_tag *tag = mb_info->tags;
    for (int i = 0; tag->type != MULTIBOOT_TAG_TYPE_END; i++) {
        switch (tag->type) {
        case MULTIBOOT_TAG_TYPE_MMAP:
            mb_info_tags.mmap = (mb_memory_map_tag *) tag;
            break;
        default:
            break;
        }
        tag = (multiboot_tag*) ((uintptr_t)tag + align(tag->size, 8));
    }
}

void show_memory_multiboot_tags()
{
    vga.Write(mb_info->total_size);
    vga.Write("\n");

    multiboot_tag *tag = mb_info->tags;
    for (int i = 0; tag->type != MULTIBOOT_TAG_TYPE_END; i++) {
        vga.Write("Tag addr: ");
        vga.WriteAddress((uintptr_t) tag);
        vga.Write(" Tag type: ");
        vga.Write(tag->type);
        vga.Write(" Tag Size: ");
        vga.Write(tag->size);
        vga.Write("\n");
        tag = (multiboot_tag*) ((uintptr_t)tag + align(tag->size, 8));
    }
}