/*
 * File      : drv_sdram.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      The first version for LPC40xx
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

#include <board.h>

#define SDRAM_CONFIG_16BIT     //use the 16 bitSDRAM
//#define SDRAM_CONFIG_32BIT    //use the 32 bitSDRAM

#ifdef SDRAM_CONFIG_16BIT
#define SDRAM_SIZE               0x2000000  // 256Mbit
#elif defined SDRAM_CONFIG_32BIT     //
#define SDRAM_SIZE               0x4000000  // 512Mbit
#else
error Wrong SDRAM config, check ex_sdram.h
#endif

#define SDRAM_BASE               0xA0000000    /* CS0 */

void lpc_sdram_hw_init(void);

#endif
