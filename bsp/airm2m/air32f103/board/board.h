/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <air32f10x_conf.h>
#include "drv_common.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AIR32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE              (64)
#define AIR32_FLASH_SIZE             (128 * 1024)
#define AIR32_FLASH_END_ADDRESS      ((uint32_t)(AIR32_FLASH_START_ADRESS + AIR32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] , Default: 96*/
#define AIR32_SRAM_SIZE      96
#define AIR32_SRAM_END       (0x20000000 + AIR32_SRAM_SIZE * 1024)

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

#define HEAP_END        AIR32_SRAM_END

void SystemClock_Config(void);

#ifdef BSP_USING_UART
void air32_usart_clock_and_io_init(USART_TypeDef *usartx);
#endif

#ifdef BSP_USING_SPI
void air32_spi_clock_and_io_init(SPI_TypeDef* spix);
rt_uint32_t air32_spi_clock_get(SPI_TypeDef* spix);
#endif

#ifdef BSP_USING_TIM
void air32_tim_clock_init(TIM_TypeDef *timx);
rt_uint32_t air32_tim_clock_get(TIM_TypeDef *timx);
#endif

#ifdef BSP_USING_TIM
struct rt_hwtimer_info* air32_hwtimer_info_config_get(TIM_TypeDef *timx);
#endif

#ifdef BSP_USING_PWM
void air32_pwm_io_init(TIM_TypeDef *timx, rt_uint8_t channel);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
