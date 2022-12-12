/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-25     Bernard      first version
 */

#ifndef __NAND_H__
#define __NAND_H__

#include <rtthread.h>

#define IO_NF_PFR     FM3_GPIO->PFR3
#define IO_NF_DDR     FM3_GPIO->DDR3
#define IO_NF_PDOR    FM3_GPIO->PDOR3

#define NF_EN         0x0008
#define NF_DATA_DIR   0x0004

#define EXT_BUS_BASE_ADDR    0x60000000
#define EXT_CS7_OFFSET       0x0E000000
#define EXT_CS7_SIZE         0x02000000

#define NF_FLASH_BASE_ADDR   (EXT_BUS_BASE_ADDR+EXT_CS7_OFFSET)

#define NF_ALE_OFFSET        0x00003000
#define NF_ADDR_OFFSET       0x00002000
#define NF_CMD_OFFSET        0x00001000
#define NF_DATA_OFFSET       0x00000000

/* NAND command */
#define NAND_CMD_READ0     0x00
#define NAND_CMD_READ1     0x01
#define NAND_CMD_PAGEPROG  0x10
#define NAND_CMD_READOOB   0x50
#define NAND_CMD_ERASE1    0x60
#define NAND_CMD_STATUS    0x70
#define NAND_CMD_SEQIN     0x80
#define NAND_CMD_READID    0x90
#define NAND_CMD_READID1   0x91
#define NAND_CMD_ERASE2    0xd0
#define NAND_CMD_RESET     0xff

#define FLASH_OK           0
#define FLASH_NG           1

/* nand flash device initialization */
void rt_hw_nand_init(void);

#endif
