/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_WDT_H__
#define AB32VG1_HAL_WDT_H__

#include "ab32vg1_hal_def.h"

#define WDT_CLR()               WDTCON = 0xa
#define WDT_EN()                WDTCON = 0x110
#define WDT_DIS()               WDTCON = 0xaa0
#define WDT_RST()               WDTCON = 0xa000110; while (1)
#define WDT_RST_DELAY()         WDTCON = 0xa100110; while (1)

#endif
