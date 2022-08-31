/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define MM32_FLASH_SIZE             (512 * 1024)
#define MM32_FLASH_END_ADDRESS      ((uint32_t)(MM32_FLASH_START_ADRESS + MM32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <8-128>, Default: 128*/
#define MM32_SRAM_SIZE              128
#define MM32_SRAM_END               (0x20000000 + MM32_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END            MM32_SRAM_END

#define LSI_VALUE           (40000)
#define HSI_VALUE           (8000000)
#define HSE_VALUE           (12000000)

#define __USE_HSE           (0)
#define __USE_HSE_PLL       (1)
#define __USE_HSI_PLL       (0)

#define RCC_CFGR_SWS_Pos                     (2U)
#define RCC_CFGR_SWS_Msk                     (0x3UL << RCC_CFGR_SWS_Pos)        /*!< 0x0000000C */

#define RCC_CFGR_SWS_HSI                     0x00000000U                       /*!< HSI oscillator used as system clock */
#define RCC_CFGR_SWS_HSE                     0x00000004U                       /*!< HSE oscillator used as system clock */
#define RCC_CFGR_SWS_PLL                     0x00000008U                       /*!< PLL used as system clock */
#define RCC_CFGR_SWS_LSI                     0x0000000CU                       /*!< LSI used as system clock */

#define RCC_SYSCLKSOURCE_STATUS_HSI         RCC_CFGR_SWS_HSI            /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE         RCC_CFGR_SWS_HSE            /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK      RCC_CFGR_SWS_PLL            /*!< PLL used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_LSI         RCC_CFGR_SWS_LSI            /*!< LSI used as system clock */

uint32_t HAL_GetSysClockFreq(void);
uint32_t HAL_Get_AHB_Clock(void);
uint32_t HAL_Get_APB1_Clock(void);
uint32_t HAL_Get_APB2_Clock(void);
void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
