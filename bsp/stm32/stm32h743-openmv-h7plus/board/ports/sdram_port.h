/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-14     supperthomas The first version for STM32H7xx
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

/* parameters for sdram peripheral */
/* Bank1 or Bank2 */
#define SDRAM_TARGET_BANK               1
/* stm32h7 Bank1:0XC0000000  Bank2:0XD0000000 */
#define SDRAM_BANK_ADDR                 ((uint32_t)0XC0000000)
/* data width: 8, 16, 32 */
#define SDRAM_DATA_WIDTH                32
/* column bit numbers: 8, 9, 10, 11 */
#define SDRAM_COLUMN_BITS               9
/* row bit numbers: 11, 12, 13 */
#define SDRAM_ROW_BITS                  12
/* cas latency clock number: 1, 2, 3 */
#define SDRAM_CAS_LATENCY               2
/* read pipe delay: 0, 1, 2 */
#define SDRAM_RPIPE_DELAY               0
/* clock divid: 2, 3 */
#define SDCLOCK_PERIOD                  2
/* refresh rate counter */
#define SDRAM_REFRESH_RATE                          (64) // ms
#define SDRAM_FREQUENCY                             (100000) // 100 MHz
#define SDRAM_REFRESH_CYCLES                        4096
#define SDRAM_REFRESH_COUNT             (SDRAM_REFRESH_RATE * SDRAM_FREQUENCY / SDRAM_REFRESH_CYCLES - 20) //((uint32_t)0x02A5)
#define SDRAM_SIZE                      (32 * 1024 * 1024)

/* Timing configuration for W9825G6KH-6 */
/* 100 MHz of HCKL3 clock frequency (200MHz/2) */
/* TMRD: 2 Clock cycles */
#define LOADTOACTIVEDELAY               2
/* TXSR: 8x10ns */
#define EXITSELFREFRESHDELAY            7
/* TRAS: 5x10ns */
#define SELFREFRESHTIME                 5
/* TRC:  7x10ns */
#define ROWCYCLEDELAY                   6
/* TWR:  2 Clock cycles */
#define WRITERECOVERYTIME               3
/* TRP:  2x10ns */
#define RPDELAY                         2
/* TRCD: 2x10ns */
#define RCDDELAY                        2

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
