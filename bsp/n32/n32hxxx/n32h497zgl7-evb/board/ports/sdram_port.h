/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-14     ox-horse     first version for N32H497ZGL7-EVB (M12L64164A)
 */
/*
 * SDRAM Chip: M12L64164A
 *   4 Banks x 1M x 16 bits = 8 MB
 *   12 row address bits, 8 column address bits
 *
 *
 * N32H49x SDRAM Controller:
 *   SDRAM1 base: 0x98000000
 *   SDRAM2 base: 0x9C000000
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

#include "board.h"

/*============================================================================
 * Part 0: N32cube SDRAM clock and GPIO Configuration
 *============================================================================*/
/* clock config in RCC_Configuration()*/
/* gpio config in GPIO_Configuration()*/

/*============================================================================
 * Part 1: SDRAM Device Configuration
 *============================================================================*/

/* Bank select: 1 = SDRAM1 (0x98000000), 2 = SDRAM2 (0x9C000000) */
#ifdef BSP_SDRAM_BANK1
#define SDRAM_BANK_ADDR ((uint32_t)0x98000000)
#endif /* BSP_SDRAM_BANK1 */
#ifdef BSP_SDRAM_BANK2
#define SDRAM_BANK_ADDR ((uint32_t)0x9C000000)
#endif /* BSP_SDRAM_BANK2 */

/* Data bus width: 8 / 16 / 32 */
#ifdef BSP_SDRAM_DATA_WIDTH_8
#define SDRAM_DATA_WIDTH 8
#endif /* BSP_SDRAM_DATA_WIDTH_8 */
#ifdef BSP_SDRAM_DATA_WIDTH_16
#define SDRAM_DATA_WIDTH 16
#endif /* BSP_SDRAM_DATA_WIDTH_16 */
#ifdef BSP_SDRAM_DATA_WIDTH_32
#define SDRAM_DATA_WIDTH 32
#endif /* BSP_SDRAM_DATA_WIDTH_32 */


/* Column address bits: 8-256 / 9-512 / 10-1024 / 11-2048 */
#ifdef BSP_SDRAM_COLUMN_BIT_8
#define SDRAM_COLUMN_BITS 8
#endif /* BSP_SDRAM_COLUMN_BIT_8 */
#ifdef BSP_SDRAM_COLUMN_BIT_9
#define SDRAM_COLUMN_BITS 9
#endif /* BSP_SDRAM_COLUMN_BIT_9 */
#ifdef BSP_SDRAM_COLUMN_BIT_10
#define SDRAM_COLUMN_BITS 10
#endif /* BSP_SDRAM_COLUMN_BIT_10 */
#ifdef BSP_SDRAM_COLUMN_BIT_11
#define SDRAM_COLUMN_BITS 11
#endif /* BSP_SDRAM_COLUMN_BIT_11 */

/* Row address bits: 11-2048 / 12-4096 / 13-8192 */
#ifdef BSP_SDRAM_ROW_BIT_11
#define SDRAM_ROW_BITS 11
#endif /* BSP_SDRAM_ROW_BIT_11 */
#ifdef BSP_SDRAM_ROW_BIT_12
#define SDRAM_ROW_BITS 12
#endif /* BSP_SDRAM_ROW_BIT_12 */
#ifdef BSP_SDRAM_ROW_BIT_13
#define SDRAM_ROW_BITS 13
#endif /* BSP_SDRAM_ROW_BIT_13 */

/* Address mask for device chip-select matching */
#define SDRAM_ADDRESS_MASK ((uint32_t)(0xFFFFFFFF - ((BSP_SDRAM_SIZE * 1024U * 1024U) - 1)))

/*============================================================================
 * Part 2: Timing Parameters  (unit: SDRAM clock cycles)
 * These are the values validated on this board in hardware. Each line keeps
 * the M12L64164A datasheet minimum it covers, so they can be recomputed if
 * the SDRAM clock changes.
 *============================================================================*/

/* tRAS: Row Active Time   (datasheet min 42ns) */
#define SELFREFRESHTIME 7

/* tRC:  Row Cycle Time    (datasheet min 60ns) */
#define ROWCYCLEDELAY 9

/* tRP:  Precharge Time    (datasheet min 18ns) */
#define RPDELAY 4

/* tWR:  Write Recovery    (datasheet min 12ns) */
#define WRITERECOVERYTIME 3

/* tRCD: RAS to CAS Delay  (datasheet min 18ns) */
#define RCDDELAY 4

/* tRRD: Row Activate to Row Activate delay  (datasheet min 12ns) */
#define SDRAM_RP_DELAY 3

/* tRFC: Refresh Cycle Time  (datasheet min 67.5ns) */
#define SDRAM_REFRESH_CYCLE 9

/* Auto-refresh interval counter value
 *   Formula: RefreshInterval = SDRAM_CLK_MHz * tREF_ms * 1000 / Nrows
 *   For example: SDRAM_CLK=80MHz, tREF=64ms, rows=4096:
 *     = 80 * 64 * 1000 / 4096 ≈ 0x04E2
 *   Adjust based on actual SDRAMMEMCLK configuration. */
#define SDRAM_REFRESH_COUNT ((uint32_t)0x04A0) /* whichever is smaller */

/*============================================================================
 * Part 3: SDRAM Chip Mode Register Value  (sent via LOADMODE command)
 * These macros are also defined internally in drv_sdram.c.
 *============================================================================*/
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

#endif /* __SDRAM_PORT_H__ */
