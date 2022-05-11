/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-02     FMD-AE       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <ft32f0xx.h>
#include "drv_gpio.h"
#include <rthw.h>
#include <ft32f0xx_gpio.h>
#include <ft32f0xx_exti.h>
#include <ft32f0xx_usart.h>
#include <ft32f0xx_dma.h>
#include <ft32f0xx_rcc.h>
#include <ft32f0xx_syscfg.h>
#ifdef RT_USING_DEVICE
    #include <rtdevice.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define FT32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define FT32_FLASH_SIZE             (128 * 1024)
#define FT32_FLASH_END_ADDRESS      ((uint32_t)(FT32_FLASH_START_ADRESS + FT32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <8-64>, Default: 64*/
#define FT32_SRAM_SIZE      24
#define FT32_SRAM_END       (0x20000000 + FT32_SRAM_SIZE * 1024)

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

#define HEAP_END        FT32_SRAM_END

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
