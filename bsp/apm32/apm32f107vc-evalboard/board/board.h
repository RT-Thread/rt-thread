/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2022-12-28     luobeihai    first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <apm32f10x.h>

#include "apm32f10x_gpio.h"
#include "apm32f10x_rcm.h"
#include "apm32f10x_misc.h"
#include "apm32f10x_rcm.h"
#include "apm32f10x_eint.h"
#include "apm32f10x_usart.h"

#if defined(RT_USING_ADC)
    #include "apm32f10x_adc.h"
#endif
#if defined(RT_USING_DAC)
    #include "apm32f10x_dac.h"
#endif
#if defined(RT_USING_RTC)
    #include "apm32f10x_rtc.h"
    #include "apm32f10x_pmu.h"
#endif
#if defined(RT_USING_SPI)
    #include "apm32f10x_spi.h"
#endif
#if defined(RT_USING_HWTIMER) || defined(RT_USING_PWM)
    #include "apm32f10x_tmr.h"
#endif
#if defined(RT_USING_WDT)
    #include "apm32f10x_iwdt.h"
    #include "apm32f10x_wwdt.h"
#endif
#if defined(BSP_USING_ETH)
    #include "apm32f10x_eth.h"
#endif
#if defined(BSP_USING_ON_CHIP_FLASH)
    #include "apm32f10x_fmc.h"
#endif
#if defined(RT_USING_CAN)
    #include "apm32f10x_can.h"
#endif

#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define APM32_FLASH_SIZE             (256 * 1024)
#define APM32_FLASH_END_ADDRESS      ((uint32_t)(APM32_FLASH_START_ADRESS + APM32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <6-128>, Default: 64 */
#define APM32_SRAM_SIZE      64
#define APM32_SRAM_END       (0x20000000 + APM32_SRAM_SIZE * 1024)

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

#define HEAP_END        APM32_SRAM_END

void SystemClock_Config(void);

void apm32_usart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
