/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#if defined(SOC_GD32H77DIW) && !defined(GD32H77DXW)
#define GD32H77DXW
#endif

#include "gd32h77x_78x.h"
#include "drv_usart.h"
#include "drv_gpio.h"

#include "gd32h77x_78x_exti.h"

#define EXT_SDRAM_BEGIN    (0xC0000000U) /* the begining address of external SDRAM */
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + (32U * 1024 * 1024)) /* the end address of external SDRAM */
#define EXT_SDRAM_LCD_RESERVED_SIZE    (3U * 1024U * 1024U)
#define EXT_SDRAM_OV7670_PREVIEW_BEGIN (EXT_SDRAM_BEGIN + (2U * 1024U * 1024U))

#ifdef BSP_USING_LCD_MIPI
#define SDRAM_HEAP_BEGIN    (EXT_SDRAM_BEGIN + EXT_SDRAM_LCD_RESERVED_SIZE)
#else
#define SDRAM_HEAP_BEGIN    EXT_SDRAM_BEGIN
#endif
#define SDRAM_HEAP_SIZE     (EXT_SDRAM_END - SDRAM_HEAP_BEGIN)

#define BSP_USB_HOST_VBUS_PORT_RCC    RCU_GPIOF
#define BSP_USB_HOST_VBUS_PORT        GPIOF
#define BSP_USB_HOST_VBUS_PIN         GPIO_PIN_2

/* <o> Internal SRAM memory size[Kbytes] <8-768>*/
/* <i>Default: 768*/
#ifdef __ICCARM__
/* Use *.icf ram symbal, to avoid hardcode.*/
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define GD32_SRAM_SIZE         768
#define GD32_SRAM_END          (0x24000000 + GD32_SRAM_SIZE * 1024)
#endif

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          GD32_SRAM_END

#endif /* __BOARD_H__ */
