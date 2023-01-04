/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-6-1        Wayne        First version
*
******************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include "NuMicro.h"
#include "drv_sys.h"
#include "nutool_pincfg.h"

#define BOARD_SDRAM_START   0x80400000
#define BOARD_SDRAM_SIZE    0x07C00000

#define BOARD_HEAP_END      ((void*)(BOARD_SDRAM_START+BOARD_SDRAM_SIZE))
#define BOARD_HEAP_START    ((void *)&__bss_end)

extern int __bss_end;

#if defined(RT_USING_MTD_NAND)
    #include <drivers/mtd_nand.h>
    #define MTD_SPINAND_PARTITION_NUM 3
    extern struct rt_mtd_nand_device mtd_partitions[MTD_SPINAND_PARTITION_NUM];

    #define MTD_NFI_PARTITION_NUM 3
    extern struct rt_mtd_nand_device mtd_partitions_nfi[MTD_NFI_PARTITION_NUM];
#endif
extern void rt_hw_board_init(void);
extern void nu_clock_init(void);
extern void nu_clock_deinit(void);
extern void nu_pin_init(void);
extern void nu_pin_deinit(void);

#endif /* BOARD_H_ */
