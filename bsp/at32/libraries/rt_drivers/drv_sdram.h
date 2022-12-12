/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-08     shelton      first version
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

#include <rtthread.h>

/* parameters for sdram peripheral */
/* bank1 or bank2 */
#define SDRAM_TARGET_BANK               1
/* at32f435 bank1:0xc0000000  bank2:0xd0000000 */
#define SDRAM_BANK_ADDR                 ((uint32_t)0xC0000000)
/* data width: 8, 16, 32 */
#define SDRAM_DATA_WIDTH                16
/* column bit numbers: 8, 9, 10, 11 */
#define SDRAM_COLUMN_BITS               9
/* row bit numbers: 11, 12, 13 */
#define SDRAM_ROW_BITS                  13
/* cas latency clock number: 1, 2, 3 */
#define SDRAM_CAS_LATENCY               3
/* read pipe delay: 0, 1, 2 */
#define SDRAM_RPIPE_DELAY               1
/* clock divid: 2, 3 */
#define SDCLOCK_PERIOD                  3
/* refresh rate counter */
/* counter = (refresh_count * 1000 * SDCLK) / row - 20 */
/* counter = (64ms * 1000 * 144MHz) / 2^13 - 20 */
#define SDRAM_REFRESH_COUNT             ((uint32_t)0x0451)
#define SDRAM_SIZE                      ((uint32_t)0x1000000)

/* tmrd */
#define LOADTOACTIVEDELAY               XMC_DELAY_CYCLE_2
/* txsr */
#define EXITSELFREFRESHDELAY            XMC_DELAY_CYCLE_11
/* tras */
#define SELFREFRESHTIME                 XMC_DELAY_CYCLE_7
/* trc */
#define ROWCYCLEDELAY                   XMC_DELAY_CYCLE_9
/* twr */
#define WRITERECOVERYTIME               XMC_DELAY_CYCLE_2
/* trp */
#define RPDELAY                         XMC_DELAY_CYCLE_3
/* trcd */
#define RCDDELAY                        XMC_DELAY_CYCLE_3

/* memory mode register */
#define SDRAM_BURST_LEN_1               ((uint16_t)0x0000)
#define SDRAM_BURST_LEN_2               ((uint16_t)0x0001)
#define SDRAM_BURST_LEN_4               ((uint16_t)0x0002)
#define SDRAM_BURST_LEN_8               ((uint16_t)0x0004)
#define SDRAM_BURST_SEQUENTIAL          ((uint16_t)0x0000)
#define SDRAM_BURST_INTERLEAVED         ((uint16_t)0x0008)
#define SDRAM_CAS_LATENCY_1             ((uint16_t)0x0010)
#define SDRAM_CAS_LATENCY_2             ((uint16_t)0x0020)
#define SDRAM_CAS_LATENCY_3             ((uint16_t)0x0030)
#define SDRAM_OPERATING_MODE_STANDARD   ((uint16_t)0x0000)
#define SDRAM_WR_BURST_PROGRAMMED       ((uint16_t)0x0000)
#define SDRAM_WR_BURST_SINGLE           ((uint16_t)0x0200)

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SDRAM_H__ */
