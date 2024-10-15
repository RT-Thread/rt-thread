/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>

#include "clock_config.h"
#include "fsl_gpio.h"

#if defined(__ARMCC_VERSION)
extern int Image$$ARM_LIB_HEAP$$ZI$$Base;
extern int Image$$ARM_LIB_STACK$$ZI$$Base;
#define HEAP_BEGIN  ((void *)&Image$$ARM_LIB_HEAP$$ZI$$Base)
#define HEAP_END    ((void*)&Image$$ARM_LIB_STACK$$ZI$$Base)
#elif defined(__ICCARM__)
#pragma section="HEAP"
#define HEAP_BEGIN          (__segment_end("HEAP"))
extern void __RTT_HEAP_END;
#define HEAP_END            (&__RTT_HEAP_END)
#elif defined(__GNUC__)
extern int __HeapBase;
extern int __HeapLimit;
#define HEAP_BEGIN  ((void *)&__HeapBase)
#define HEAP_END  ((void *)&__HeapLimit)
#endif

void rt_hw_board_init(void);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
