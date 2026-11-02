/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "bsp_api.h"

/* UNCRUSTIFY-OFF */

/* boot loaded applications cannot set ofs registers (only do so in the boot loader) */
#ifndef BSP_BOOTLOADED_APPLICATION
/** configuration register output to sections */
#endif // BSP_BOOTLOADED_APPLICATION

/******************************/
/* the init tables are located in bsp_linker_info.h */
#define BSP_LINKER_C
#include "bsp_linker_info.h"

/* UNCRUSTIFY-ON */
