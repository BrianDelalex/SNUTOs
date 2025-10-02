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

%endif ;//!BOOT_INC
