/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     zylx         The first version for STM32F4xx
 * 2023-08-20     yuanzihao    adapter gd32f4xx
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

/* parameters for sdram peripheral */
#define SDRAM_DEVICE    EXMC_SDRAM_DEVICE0
/* Bank1 or Bank2 */
#define SDRAM_TARGET_BANK               1
/* stm32h7 Bank1:0XC0000000  Bank2:0XD0000000 */
#define SDRAM_BANK_ADDR                 ((uint32_t)0XC0000000)
/* data width: 8, 16, 32 */
#define SDRAM_DATA_WIDTH_IN_NUMBER      16
#define SDRAM_DATA_WIDTH                EXMC_SDRAM_DATABUS_WIDTH_16B
/* column bit numbers: 8, 9, 10, 11 */
#define SDRAM_COLUMN_BITS               EXMC_SDRAM_COW_ADDRESS_9
/* row bit numbers: 11, 12, 13 */
#define SDRAM_ROW_BITS                  EXMC_SDRAM_ROW_ADDRESS_13
/* cas latency clock number: 1, 2, 3 */
#define SDRAM_CAS_LATENCY               EXMC_CAS_LATENCY_3_SDCLK
/* read pipe delay: 0, 1, 2 */
#define SDRAM_RPIPE_DELAY               EXMC_PIPELINE_DELAY_2_HCLK
/* clock divid: 2, 3 */
#define SDCLOCK_PERIOD                  EXMC_SDCLK_PERIODS_3_HCLK
/* refresh rate counter */
#define SDRAM_REFRESH_COUNT             ((uint32_t)0x02A5)
#define SDRAM_SIZE                      ((uint32_t)0x2000000)
#define SDRAM_TIMEOUT                   ((uint32_t)0x0000FFFF)

/* Timing configuration for W9825G6KH-6 */
/* 100 MHz of HCKL3 clock frequency (200MHz/2) */
/* TMRD: 2 Clock cycles */
#define LOADTOACTIVEDELAY               2
/* TXSR: 8x10ns */
#define EXITSELFREFRESHDELAY            8
/* TRAS: 5x10ns */
#define SELFREFRESHTIME                 7
/* TRC:  7x10ns */
#define ROWCYCLEDELAY                   5
/* TWR:  2 Clock cycles */
#define WRITERECOVERYTIME               2
/* TRP:  2x10ns */
#define RPDELAY                         3
/* TRCD: 2x10ns */
#define RCDDELAY                        3

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
