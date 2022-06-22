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

#include "NuMicro.h"
#include "drv_sys.h"

#if defined(__CC_ARM)
    extern int Image$$RW_RAM1$$ZI$$Limit;
    #define BOARD_HEAP_START    (void*)&Image$$RW_RAM1$$ZI$$Limit
#else
    extern int __bss_end;
    #define BOARD_HEAP_START    ((void *)&__bss_end)
#endif

#define BOARD_SDRAM_START   0x0
#define BOARD_SDRAM_SIZE    0x04000000
#define BOARD_HEAP_END      ((void*)BOARD_SDRAM_SIZE)

#if defined(RT_USING_MTD_NAND)
    #include <drivers/mtd_nand.h>
    #define MTD_SPINAND_PARTITION_NUM 3
    extern struct rt_mtd_nand_device mtd_partitions[MTD_SPINAND_PARTITION_NUM];
#endif

extern void rt_hw_board_init(void);
extern void nu_clock_init(void);
extern void nu_clock_deinit(void);
extern void nu_pin_init(void);
extern void nu_pin_deinit(void);

#endif /* BOARD_H_ */
