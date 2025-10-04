;/*******************************************************************\
;**
;**  This file is part of SNUTOs project, and is made available under
;**  the terms of the GNU General Public License version 3.
;**
;**  Copyright (C) 2025 - Brian DELALEX-FONDU
;**
;\*******************************************************************/

%ifndef BOOT_INC
%define BOOT_INC

%define KERNEL_VIRT_START         0xFFFFFFFF80000000
%define VIRT2PHYS(x) (x - KERNEL_VIRT_START)

%define PAGE_SIZE 0x1000
%define PAGE_TABLE_SIZE 0x1000
%define PAGE_TABLE_NBR 512

%endif ;//!BOOT_INC
