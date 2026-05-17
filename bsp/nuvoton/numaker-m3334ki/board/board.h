/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
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
#define SRAM_SIZE         (320)
#define SRAM_END          (0x20000000 + SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
    extern int Image$$RW_RAM$$ZI$$Limit;
    #define HEAP_BEGIN      ((void *)&Image$$RW_RAM$$ZI$$Limit)
#elif __ICCARM__
    #pragma section="CSTACK"
    #define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
    extern int __bss_end__;
    #define HEAP_BEGIN      ((void *)&__bss_end__)
#endif

#define HEAP_END        (void *)SRAM_END


void rt_hw_board_init(void);
void rt_hw_cpu_reset(void);

#endif /* BOARD_H_ */
