/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-10      Sherman      first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "hal_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RA_SRAM_SIZE    1872 /* The SRAM size of the chip needs to be modified */
#define RA_SRAM_END     (0x22000000 + RA_SRAM_SIZE * 1024)

#ifdef __ARMCC_VERSION
extern int Image$$RAM_END$$ZI$$Base;
#define HEAP_BEGIN  ((void *)&Image$$RAM_END$$ZI$$Base)
#elif __ICCARM__
#pragma section="ram_BLOCK"
#define HEAP_BEGIN      (__segment_end("ram_BLOCK"))
#else
extern int __RAM_segment_used_end__;
#define HEAP_BEGIN      (&__RAM_segment_used_end__)
#endif

#define HEAP_END        RA_SRAM_END

#ifdef __cplusplus
}
#endif

#endif
