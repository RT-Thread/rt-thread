/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-05     mazhiyuan   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__
#include <rtthread.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SRAM_SIZE 0x5000

#define SRAM_END (SRAM_BASE + SRAM_SIZE)
#ifdef __CC_ARM
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section = "HEAP"
    #define HEAP_BEGIN (__segment_end("HEAP"))
#else
    extern int __bss_end;
    #define HEAP_BEGIN ((void *)&__bss_end)
#endif
#define HEAP_END SRAM_END
#define HEAP_SIZE (HEAP_END - (rt_uint32_t)HEAP_BEGIN)

#define LSI_VALUE           (40000)
#define HSI_VALUE           (8000000)
#define HSE_VALUE           (12000000)

#define RCC_CFGR_SWS_Pos                     (2U)
#define RCC_CFGR_SWS_Msk                     (0x3UL << RCC_CFGR_SWS_Pos)

#define RCC_CFGR_SWS_HSI                     0x00000000U
#define RCC_CFGR_SWS_HSE                     0x00000004U
#define RCC_CFGR_SWS_PLL                     0x00000008U
#define RCC_CFGR_SWS_LSI                     0x0000000CU

#define RCC_SYSCLKSOURCE_STATUS_HSI         RCC_CFGR_SWS_HSI
#define RCC_SYSCLKSOURCE_STATUS_HSE         RCC_CFGR_SWS_HSE
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK      RCC_CFGR_SWS_PLL
#define RCC_SYSCLKSOURCE_STATUS_LSI         RCC_CFGR_SWS_LSI

uint32_t HAL_GetSysClockFreq(void);
uint32_t HAL_Get_AHB_Clock(void);
uint32_t HAL_Get_APB1_Clock(void);
uint32_t HAL_Get_APB2_Clock(void);
void SystemClock_Config(void);
extern void rt_hw_board_init(void);

#ifdef __cplusplus
}
#endif

#endif
