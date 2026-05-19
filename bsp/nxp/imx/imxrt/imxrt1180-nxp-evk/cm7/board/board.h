/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_common.h"
#include "fsl_rgpio.h"
#include "fsl_clock.h"

#if defined(__ARMCC_VERSION)
extern int Image$$ARM_LIB_HEAP$$ZI$$Base;
extern int Image$$ARM_LIB_HEAP$$ZI$$Limit;
#define HEAP_BEGIN  ((void *)&Image$$ARM_LIB_HEAP$$ZI$$Base)
#define HEAP_END    ((void*)&Image$$ARM_LIB_HEAP$$ZI$$Limit)
#elif defined(__ICCARM__)
#pragma section="HEAP"
#define HEAP_BEGIN    (__section_begin("HEAP"))
#define HEAP_END      (__section_end("HEAP"))
#elif defined(__GNUC__)
extern int __HeapBase;
extern int __HeapLimit;
#define HEAP_BEGIN  ((void *)&__HeapBase)
#define HEAP_END  ((void *)&__HeapLimit)
#endif

/*! @brief The board flash size */
#define BOARD_FLASH_SIZE (0x1000000U)

void rt_hw_board_init(void);

#endif

