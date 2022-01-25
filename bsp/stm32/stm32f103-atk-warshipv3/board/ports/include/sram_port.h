/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-05     linyiyang    first version
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

/* parameters for sdram peripheral */
/* stm32f1 Bank1:0x68000000 */
#define EXTERNAL_SRAM_BANK_ADDR         ((uint32_t)0x68000000)
/* data width: 8, 16, 32 */
#define EXTERNAL_SRAM_DATA_WIDTH        16
/* sram size */
#define EXTERNAL_SRAM_SIZE              ((uint32_t)0x100000)

#endif
