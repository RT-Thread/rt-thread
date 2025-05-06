/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 * 2013-12-18     Bernard      porting to LPC4088 bsp
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__


#include <stdint.h>

#include <rtthread.h>

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_reset.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "fsl_edma.h"

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// </RDTConfigurator>
#if defined(__ARMCC_VERSION)
extern int Image$$ARM_LIB_HEAP$$ZI$$Base;
extern int Image$$ARM_LIB_STACK$$ZI$$Base;
#define HEAP_BEGIN  ((void *)&Image$$ARM_LIB_HEAP$$ZI$$Base)
#define HEAP_END    ((void*)&Image$$ARM_LIB_STACK$$ZI$$Base)
#elif defined(__ICCARM__)
#pragma section="HEAP"
#define HEAP_BEGIN          (__section_begin("HEAP"))
#define HEAP_END            (__section_end("HEAP"))
#elif defined(__GNUC__)
extern int __HeapBase;
extern int __HeapLimit;
#define HEAP_BEGIN  ((void *)&__HeapBase)
#define HEAP_END  ((void *)&__HeapLimit)
#endif

void rt_hw_board_init(void);


#endif


