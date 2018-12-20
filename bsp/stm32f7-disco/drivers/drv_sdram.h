/*
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-08-03     xiaonong     The first version for STM32F7
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

#include <rtthread.h>
#include <board.h>
#define SDRAM_BANK_ADDR                           ((uint32_t)0xC0000000)

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1              ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2              ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4              ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8              ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL       ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED      ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2               ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3               ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD     ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED  ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE      ((uint16_t)0x0200)

#define SDRAM_SIZE  (16UL * 1024UL * 1024UL)
#define SDRAM_BEGIN SDRAM_BANK_ADDR
#define SDRAM_END   (SDRAM_BANK_ADDR + SDRAM_SIZE)

extern int bsp_sdram_hw_init(void);

#endif
