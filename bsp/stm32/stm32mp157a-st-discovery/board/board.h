/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2019-04-09     WillianChan  add stm32f469-st-disco bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "stm32mp1xx.h"
#include "stm32mp1xx_hal.h"
#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STM32_FLASH_START_ADRESS     ((uint32_t)0x10000000)  
#if defined(BSP_USING_OPENAMP)
#define STM32_FLASH_SIZE             (64 * 1024)
#else
#define STM32_FLASH_SIZE             (256 * 1024)    
#endif
#define STM32_FLASH_END_ADDRESS      ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

    
#if defined(BSP_USING_OPENAMP)    
#define STM32_SRAM_BEGIN             (uint32_t)0x10020000 
#else
#define STM32_SRAM_BEGIN             (uint32_t)0x2FFF0000     
#endif
#define STM32_SRAM_SIZE              (64)    
#define STM32_SRAM_END               (STM32_SRAM_BEGIN + (STM32_SRAM_SIZE * 1024))

#define HEAP_BEGIN                    STM32_SRAM_BEGIN
#define HEAP_END                      STM32_SRAM_END

#define HEAP_END        STM32_SRAM_END

void SystemClock_Config(void);

extern void _Error_Handler(char *s, int num);

#ifdef __cplusplus
}
#endif

#endif

