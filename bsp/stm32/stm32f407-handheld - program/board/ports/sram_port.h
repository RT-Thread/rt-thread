/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Malongwei    first version
 */

#ifndef __SRAM_PORT_H__
#define __SRAM_PORT_H__

/* parameters for sram peripheral */
/* stm32f4 Bank3:0X68000000 */
#define SRAM_BANK_ADDR       ((uint32_t)0X68000000)
/* data width: 8, 16, 32 */
#define SRAM_DATA_WIDTH      16
/* sram size */
#define SRAM_SIZE            ((uint32_t)0x00100000)

#endif
