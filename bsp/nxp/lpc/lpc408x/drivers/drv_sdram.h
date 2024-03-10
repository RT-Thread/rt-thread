/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      The first version for LPC40xx
 */

#ifndef DRV_SDRAM_H__
#define DRV_SDRAM_H__

#include <board.h>

#define SDRAM_CONFIG_16BIT     /* use the 16 bitSDRAM */
//#define SDRAM_CONFIG_32BIT   /* use the 32 bitSDRAM */

#ifdef SDRAM_CONFIG_16BIT
    #define EXT_SDRAM_SIZE               0x2000000  /* 256Mbit */
#elif defined SDRAM_CONFIG_32BIT
    #define EXT_SDRAM_SIZE               0x4000000  /* 512Mbit */
#else
    error Wrong SDRAM config, check ex_sdram.h
#endif

#define EXT_SDRAM_BEGIN               0xA0000000    /* CS0 */
#define EXT_SDRAM_END         (EXT_SDRAM_BEGIN + EXT_SDRAM_SIZE)

void rt_hw_sdram_init(void);

#endif    /* DRV_SDRAM_H__ */
