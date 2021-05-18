/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-21     shelton      first version
 */

#ifndef __DRV_SRAM__
#define __DRV_SRAM__

#include <rtthread.h>
#include "at32f4xx.h"

#define SRAM_LENGTH           ((uint32_t)0x100000)
#define EXT_SRAM_BEGIN        ((uint32_t)0x68000000)
#define EXT_SRAM_END          (EXT_SRAM_BEGIN + SRAM_LENGTH)

#define RT_BUFFER_SIZE        0x400
#define RT_WRITE_READ_ADDR    0x8000

#endif // __DRV_SRAM__
