/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-28     luobeihai    first version
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

/* parameters for sdram peripheral */
/* Bank1 or Bank2 */
#define SDRAM_TARGET_BANK               1
/* apm32f407 Bank Addr: 0x60000000 */
#define SDRAM_BANK_ADDR                 ((uint32_t)0x60000000)
/* data width: 8, 16, 32 */
#define SDRAM_DATA_WIDTH                16
/* column bit numbers */
#define SDRAM_COLUMN_BITS               DMC_COL_WIDTH_8
/* row bit numbers */
#define SDRAM_ROW_BITS                  DMC_ROW_WIDTH_11

#define SDRAM_MEMORY_SIZE               DMC_MEMORY_SIZE_2MB

#define SDRAM_SIZE                      ((uint32_t)0x200000)

/* memory mode register */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#endif
