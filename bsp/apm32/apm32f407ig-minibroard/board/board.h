/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2022-03-28     Abbcc          first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <apm32f4xx.h>

#include "apm32f4xx_gpio.h"
#include "apm32f4xx_syscfg.h"
#include "apm32f4xx_rcm.h"
#include "apm32f4xx_misc.h"
#include "apm32f4xx_rcm.h"
#include "apm32f4xx_eint.h"
#include "apm32f4xx_usart.h"

#if defined(RT_USING_ADC)
    #include "apm32f4xx_adc.h"
#endif
#if defined(RT_USING_DAC)
    #include "apm32f4xx_dac.h"
#endif
#if defined(RT_USING_RTC)
    #include "apm32f4xx_rtc.h"
    #include "apm32f4xx_pmu.h"
#endif
#if defined(RT_USING_SPI)
    #include "apm32f4xx_spi.h"
#endif
#if defined(RT_USING_HWTIMER) || defined(RT_USING_PWM)
    #include "apm32f4xx_tmr.h"
#endif
#if defined(RT_USING_WDT)
    #include "apm32f4xx_iwdt.h"
    #include "apm32f4xx_wwdt.h"
#endif
#if defined(RT_USING_CAN)
    #include "apm32f4xx_can.h"
#endif

#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define APM32_FLASH_SIZE             (1024 * 1024)
#define APM32_FLASH_END_ADDRESS      ((uint32_t)(APM32_FLASH_START_ADRESS + APM32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <6-128>, Default: 128 */
#define APM32_SRAM_SIZE      128
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
