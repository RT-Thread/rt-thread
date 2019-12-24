/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-16    bluebear233   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

// <o> Internal SRAM memory size[Kbytes] <8-64>
#define SRAM_SIZE         (160)
#define SRAM_END          (0x20000000 + SRAM_SIZE * 1024)

void rt_hw_board_init(void);
void rt_hw_cpu_reset(void);

#endif /* BOARD_H_ */
