/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-00-30     thread-liu   first version
 */

#ifndef __DRV_NAND_H__
#define __DRV_NAND_H__

#include "board.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define NAND_MAX_PAGE_SIZE              4096
#define NAND_ECC_SECTOR_SIZE            512

#define NAND_TWHR_DELAY                 25
#define NAND_TBERS_DELAY                4

#define MT29F8G08ABACAH4                0x64A690D3 /* id */

#define NAND_ADDR                       ((rt_uint32_t)0x80000000) /* nand base address */
#define NAND_ADDR_AREA                  (*(__IO rt_uint8_t *)NAND_ADDR)
#define NAND_CMD_AREA                   (*(__IO rt_uint8_t *)(NAND_ADDR | 1 << 16))  /*  command */
#define NAND_DATA_AREA                  (*(__IO rt_uint8_t *)(NAND_ADDR | 1 << 17)) /*  data */

/* nand flash command */
#define NAND_READID                     0x90
#define NAND_FEATURE                    0xEF
#define NAND_RESET                      0xFF
#define NAND_READSTA                    0x70
#define NAND_AREA_A                     0x00
#define NAND_AREA_TRUE1                 0x30
#define NAND_WRITE0                     0x80
#define NAND_WRITE_TURE1                0x10
#define NAND_ERASE0                     0x60
#define NAND_ERASE1                     0xD0
#define NAND_MOVEDATA_CMD0              0x00
#define NAND_MOVEDATA_CMD1              0x35
#define NAND_MOVEDATA_CMD2              0x85
#define NAND_MOVEDATA_CMD3              0x10

/* nand flash status */
#define NAND_READY                      0x40 /* read */
#define NAND_ECC1BITERR                 0x03 /* ECC 1bit err */
#define NAND_ECC2BITERR                 0x04 /* ECC 2bit or more err */

#ifdef __cplusplus
}
#endif

#endif
