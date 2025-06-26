/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-23     liYony       first version
 * 2024-01-06     GSunwinder   add define LED pins
 */

/* <<< Use Configuration Wizard in Context Menu >>> */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "ch32v30x.h"
#include "drv_gpio.h"
#include "drv_pwm.h"

/* board configuration */
#define SRAM_SIZE  64
#define SRAM_END (0x20000000 + SRAM_SIZE * 1024)

#define CH32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define CH32_FLASH_SIZE             (256 * 1024)
#define CH32_FLASH_END_ADDRESS      ((uint32_t)(CH32_FLASH_START_ADRESS + CH32_FLASH_SIZE))

extern int _ebss, _susrstack;
#define HEAP_BEGIN  ((void *)&_ebss)
#define HEAP_END    ((void *)&_susrstack)

/* defined the LED pin */
#define LED_BLUE              rt_pin_get("PB.4")
#define LED_RED               rt_pin_get("PA.15")


void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
