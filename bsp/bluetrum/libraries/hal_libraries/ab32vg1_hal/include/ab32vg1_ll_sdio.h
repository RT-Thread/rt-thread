/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_SDIO_H__
#define AB32VG1_HAL_SDIO_H__

#include "ab32vg1_hal_def.h"

struct sdio_init
{
    uint32_t clock_power_save;      /*!< Specifies whether SDMMC Clock output is enabled or
                                        disabled when the bus is idle.                                      */
    uint32_t clock_div;             /*!< Specifies the clock frequency of the SDMMC controller.
                                      This parameter can be a value between Min_Data = 0 and Max_Data = 255 */
};
typedef struct sdio_init* sdio_init_t;

#define SDMMC_CLOCK_POWER_SAVE_DISABLE      (0x00u)
#define SDMMC_CLOCK_POWER_SAVE_ENABLE       (0x01u)

enum
{
    SDxCON = 0, /* [20]:BUSY [19:17]:CRCS [16]:DCRCE [15]:NRPS [1]:Data bus width [0]:SD enable */
    SDxCPND,
    SDxBAUD,
    SDxCMD,
    SDxARG3,
    SDxARG2,
    SDxARG1,
    SDxARG0,
    SDxDMAADR,
    SDxDMACNT,
};

#endif
