/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */


#ifndef __BOARD_H__
#define __BOARD_H__


#define     XTAL_FREQUENCY (12000000L)
#define     ICLK_MUL (8)
#define     PCLK_MUL (4)
#define     BCLK_MUL (2)

#define RX62N_SRAM_END 0x0000ffff

#define RT_USING_UART2

void rt_hw_board_init(void);
void rt_hw_system_freq_init(void);
#endif
