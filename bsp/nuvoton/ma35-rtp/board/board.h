/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-7-19       Wayne        First version
*
******************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "NuMicro.h"

// <o> Internal SRAM memory size[Kbytes] <8-64>
#define BOARD_SDRAM_START   0x00000000
#define BOARD_SDRAM_SIZE    (4*1024*1024)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
    //    extern int Image$$ER_IROM1$$ZI$$Limit;
    //    #define BOARD_HEAP_START    ((void *)&Image$$ER_IROM1$$ZI$$Limit)
    extern uint32_t __initial_sp;
    #define BOARD_HEAP_START    ((void *)&__initial_sp)
#elif __ICCARM__
    #pragma section="CSTACK"
    #define BOARD_HEAP_START    (__segment_end("CSTACK"))
#else
    extern int __bss_end;
    #define BOARD_HEAP_START    ((void *)&__bss_end)
#endif

#define BOARD_HEAP_END      ((void*)(BOARD_SDRAM_START+BOARD_SDRAM_SIZE))

void rt_hw_board_init(void);
void rt_hw_cpu_reset(void);
void nu_pin_init(void);

#endif /* BOARD_H_ */
