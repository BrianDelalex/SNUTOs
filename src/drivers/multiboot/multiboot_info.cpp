/*********************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <drivers/multiboot/multiboot_info.hpp>
# include <drivers/vga/vga.hpp>
# include <bitwise_op.hpp>

extern multiboot_info *mb_info;
multiboot_info_tags mb_info_tags;
extern VGA vga;

void show_memory_map_infos()
{
    mb_memory_map_tag *map = mb_info_tags.mmap;
    vga.Clear();
    vga << "Memory map:\n";
    vga << "size: " << map->size << " entry_size: " << map->entry_size << " entry_version: " << map->entry_version << "\n";

    int count = (map->size) / map->entry_size;
    for (int i = 0; i < count; i++) {
        vga << "base_addr: " << HEX << ((uintptr_t)map->entries[i].base_addr);
        vga << " lenght: " << HEX << ((uintptr_t)map->entries[i].lenght);
        vga << " type: " << map->entries[i].type << "\n";
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
    vga << mb_info->total_size << "\n";

    multiboot_tag *tag = mb_info->tags;
    for (int i = 0; tag->type != MULTIBOOT_TAG_TYPE_END; i++) {
        vga << "Tag addr: " << HEX << (uintptr_t) tag;
        vga << " Tag type: " << tag->type << " Tag Size: " << tag->size << "\n";
        tag = (multiboot_tag*) ((uintptr_t)tag + align(tag->size, 8));
    }
}
