/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25     Bernard        first version
 * 2011-08-08     lgnq             modified for Loongson LS1B
 * 2015-07-06     chinesebear   modified for Loongson LS1C
 * 2019-12-04     Jiaxun Yang   Add board config defines
 */

#ifndef __BOARD_H__
#define __BOARD_H__
#include <rtconfig.h>

#ifndef __ASSEMBLY__
void rt_hw_board_init(void);
#endif

/*
* SDRAM config
*
* Take IS42S16400 SDRAM chip as a example
* The specfication is
* Size 8MB
* WIDTH: 16 bits
* COL WIDTH: 8 bits, so we should take the 8 power of 2, it's 256
* ROW WIDTH: 12 bits, so we take the 12 power of 2, it's 4K
*
* Please reference macro SD_PARA0 and SDRAM registers intruduction
* in user's manual to edit the SDRAM config.
*/

#if defined(RT_LS1C_BAICAIBOARD)
/* 8MByte IS42S16400 appeared in bacai_board V1.x V2.x */
#define MEM_SIZE        (0x800000)
#define SDRAM_WIDTH     (WIDTH_16)
#define SDRAM_COL       (COL_256)
#define SDRAM_ROW       (ROW_4K)
#elif defined(RT_LS1C_OPENLOONGSON)
/* 32MByte appeared in SmartLoong board */
#define MEM_SIZE        (0x2000000)
#define SDRAM_WIDTH     (WIDTH_16)
#define SDRAM_COL       (COL_512)
#define SDRAM_ROW       (ROW_8K)
#else
#error Unknown Board
#endif

/* Early Debug config */
#define EARLY_DEBUG /* UART2 serial print debug in early stage */
#define EARLY_DEBUG_BAUD  (115200)

/* Clock config */
#define CPU_HZ            (252 * 1000000)
#define PLL_MULT          (0x54)  /* When external clock is 24Mhz PLL=504Mhz */
#define SDRAM_DIV         (0)     /* SDRAM is CPU divided by 2*/
#define CPU_DIV           (2)     /* CPU clock is PLL divided by 2 */

#endif
