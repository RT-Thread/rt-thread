/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-21     seteiro      CH32V203C8T6-EVT-R0: D6, 20K SRAM, heap from linker
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "ch32v20x.h"
#include "drv_gpio.h"
#include "drv_pwm.h"

/* LQFP48 encoding uses port*16+pin; 64 covers GPIOA-D on this part. */
#define ch32v20x_PIN_NUMBERS   64

/* CH32V203C8T6: 20KB SRAM, 64KB zero-wait Flash (datasheet C8 row). */
#define SRAM_SIZE  20
#define SRAM_END (0x20000000 + SRAM_SIZE * 1024)

extern int _ebss, _susrstack;
#define HEAP_BEGIN  ((void *)&_ebss)
#define HEAP_END    ((void *)&_susrstack)

void rt_hw_board_init(void);

#ifdef BSP_USING_USBD
#include "ch32v20x_usb.h"
/* Chip headers define these as macros. drv_usbd.c wants a pointer variable. */
#undef USBOTG_FS
#undef USBFSD
typedef USBFSD_TypeDef USBOTG_FS_TypeDef;
#define USBOTG_FS          ((USBOTG_FS_TypeDef *)USBFS_BASE)
#define OTG_FS_IRQn        USBFS_IRQn
#define USBD_IRQHandler    USBFS_IRQHandler
#endif

#endif /* __BOARD_H__ */
