/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

// <o> Internal SRAM memory size[Kbytes] <8-64>
#define SRAM_SIZE         (160)
#define SRAM_END          (0x20000000 + SRAM_SIZE * 1024)

#define EE_TYPE     AT24C64

void rt_hw_board_init(void);
void rt_hw_cpu_reset(void);

#endif /* __BOARD_H__ */
