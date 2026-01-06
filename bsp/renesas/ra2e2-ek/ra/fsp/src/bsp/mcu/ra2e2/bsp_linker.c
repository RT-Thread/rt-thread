/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "bsp_api.h"

/* UNCRUSTIFY-OFF */

/* boot loaded applications cannot set ofs registers (only do so in the boot loader) */
#ifndef BSP_BOOTLOADED_APPLICATION
/** configuration register output to sections */
#if defined BSP_CFG_OPTION_SETTING_OFS0
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_cfg_option_setting_ofs0[] = {BSP_CFG_OPTION_SETTING_OFS0};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1") g_bsp_cfg_option_setting_ofs1[] = {BSP_CFG_OPTION_SETTING_OFS1};
#endif
#if defined BSP_CFG_OPTION_SETTING_SECMPU
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_secmpu") g_bsp_cfg_option_setting_secmpu[] = {BSP_CFG_OPTION_SETTING_SECMPU};
#endif
#if defined BSP_CFG_OPTION_SETTING_OSIS
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_osis") g_bsp_cfg_option_setting_osis[] = {BSP_CFG_OPTION_SETTING_OSIS};
#endif
#endif // BSP_BOOTLOADED_APPLICATION

/******************************/
/* the init tables are located in bsp_linker_info.h */
#define BSP_LINKER_C
#include "bsp_linker_info.h"

/* UNCRUSTIFY-ON */
