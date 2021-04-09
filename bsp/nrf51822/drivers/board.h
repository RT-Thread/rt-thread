/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __BOARD_H__
#define __BOARD_H__

// <o> Internal SRAM memory size[Kbytes] <16 or 32>
//  <i>Default: 16
#define NRF_SRAM_BEGIN  (0x20000000)
#define NRF_SRAM_SIZE   (16 * 1024)
#define NRF_SRAM_END    (NRF_SRAM_BEGIN + NRF_SRAM_SIZE)
//#endif


void rt_hw_board_init(void);

#endif
