/*******************************************************************\
**
**  This file is part of SNUTOs project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef MULTIBOOT_INFO
#define MULTIBOOT_INFO

# include <cstdint>

# define MULTIBOOT_INFO_ALIGN                    0x00000008

/* Multiboot tags macros */
# define MULTIBOOT_TAG_ALIGN                  8
# define MULTIBOOT_TAG_TYPE_END               0
# define MULTIBOOT_TAG_TYPE_CMDLINE           1
# define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
# define MULTIBOOT_TAG_TYPE_MODULE            3
# define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
# define MULTIBOOT_TAG_TYPE_BOOTDEV           5
# define MULTIBOOT_TAG_TYPE_MMAP              6
# define MULTIBOOT_TAG_TYPE_VBE               7
# define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
# define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
# define MULTIBOOT_TAG_TYPE_APM               10
# define MULTIBOOT_TAG_TYPE_EFI32             11
# define MULTIBOOT_TAG_TYPE_EFI64             12
# define MULTIBOOT_TAG_TYPE_SMBIOS            13
# define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
# define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
# define MULTIBOOT_TAG_TYPE_NETWORK           16
# define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
# define MULTIBOOT_TAG_TYPE_EFI_BS            18
# define MULTIBOOT_TAG_TYPE_EFI32_IH          19
# define MULTIBOOT_TAG_TYPE_EFI64_IH          20
# define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR    21


/* Hold pointer to usefull tags */
struct multiboot_info_tags {
    struct mb_memory_map_tag *mmap;
};

struct multiboot_tag {
    uint32_t type;
    uint32_t size;
} __attribute__((packed));

struct multiboot_info {
    uint32_t total_size;
    uint32_t reserved;
    struct multiboot_tag tags[0];
} __attribute__((packed));

struct mb_boot_cmd_line_tag {
    uint32_t type; // = 1
    uint32_t size;
    uint8_t string[0];
};

struct mb_bootloader_name_tag {
    uint32_t type; // = 2
    uint32_t size;
    uint8_t string[0];
};

struct mb_boot_module_tag {
    uint32_t type; // = 3
    uint32_t size;
    uint32_t mod_start;
    uint32_t mod_end;
    uint8_t string[0];
};

struct mb_basic_mem_info_tag {
    uint32_t type; // = 4
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
};

struct mb_bios_boot_device_tag {
    uint32_t type; // = 5
    uint32_t size;
    uint32_t biosdev;
    uint32_t partition;
    uint32_t sub_partition;
};

struct mb_memory_map_entry {
    uint64_t base_addr;
    uint64_t lenght;
# define MULTIBOOT_MEMORY_AVAILABLE              1
# define MULTIBOOT_MEMORY_RESERVED               2
# define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
# define MULTIBOOT_MEMORY_NVS                    4
# define MULTIBOOT_MEMORY_BADRAM                 5
    uint32_t type;
    uint32_t reserved;
} __attribute__((packed));

struct mb_memory_map_tag {
    uint32_t type; // = 6
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
    struct mb_memory_map_entry entries[0];
} __attribute__((packed));

struct mb_vbe_info_tag {
    uint32_t type; // = 7
    uint32_t size;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint8_t vbe_control_info[512];
    uint8_t vbe_mode_info[256];
};

struct mb_framebuffer_info_tag_common {
    uint32_t type; // = 8
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
# define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED      0
# define MULTIBOOT_FRAMEBUFFER_TYPE_RGB          1
# define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
    uint8_t framebuffer_type;
    uint8_t reserved;
};

struct mb_color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct mb_framebuffer_info_tag {
    struct mb_framebuffer_info_tag_common common;
    union {
        struct {
            uint16_t framebuffer_palette_num_colors;
            struct mb_color framebuffer_palette[0];
        };
        struct {
            uint8_t framebuffer_red_field_position;
            uint8_t framebuffer_red_mask_size;
            uint8_t framebuffer_green_field_position;
            uint8_t framebuffer_green_mask_size;
            uint8_t framebuffer_blue_field_position;
            uint8_t framebuffer_blue_mask_size;
        };
    };
};

struct mb_elf_symbols_tag {
    uint32_t type; // = 9
    uint32_t size;
    uint16_t num;
    uint16_t entsize;
    uint16_t shndx;
    uint16_t reserved;
    uint8_t section[0];
};

struct mb_apm_tag {
    uint32_t type; // = 10
    uint32_t size;
    uint16_t version;
    uint16_t cseg;
    uint32_t offset;
    uint16_t cseg_16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t cseg_len;
    uint16_t cseg_16_len;
    uint16_t dseg_len;
};

struct mb_efi32_tag {
    uint32_t type; // = 11
    uint32_t size;
    uint32_t pointer;
};

struct mb_efi64_tag {
    uint32_t type; // = 12
    uint32_t size;
    uint64_t pointer;
};

struct mb_smbios_tag {
    uint32_t type; // = 13
    uint32_t size;
    uint8_t major;
    uint8_t minor;
    uint8_t reserved[6];
    uint8_t smbios_tables[0];
};

struct mb_old_acpi_tag {
    uint32_t type; // = 14
    uint32_t size;
    uint8_t rsdp[0];
};

struct mb_new_acpi_tag {
    uint32_t type; // = 15
    uint32_t size;
    uint8_t rsdp[0];
};

struct mb_networking_info_tag {
    uint32_t type; // = 16
    uint32_t size;
    uint8_t dhcpack[0];
};

struct mb_efi_mmap_tag {
    uint32_t type; // = 17
    uint32_t size;
    uint32_t descr_size;
    uint32_t descr_vers;
    uint8_t efi_mmap[0];
};

struct mb_efi_boot_not_terminated_tag {
    uint32_t type; // = 18
    uint32_t size;
};

struct mb_efi32_ih_tag {
  uint32_t type; // = 19
  uint32_t size;
  uint32_t pointer;
};

struct mb_efi64_ih_tag {
  uint32_t type; // = 20
  uint32_t size;
  uint64_t pointer;
};

struct mb_img_base_phy_addr_tag {
    uint32_t type; // = 21
    uint32_t size;
    uint32_t load_base_addr;
};

#endif //!MULTIBOOT_INFO