/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     zylx         The first version for STM32F4xx
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

/* parameters for sdram peripheral */
/* Bank1 or Bank2 */
#define SDRAM_TARGET_BANK               2
/* stm32f4 Bank1:0XC0000000  Bank2:0XD0000000 */
#define SDRAM_BANK_ADDR                 ((uint32_t)0XD0000000)
/* data width: 8, 16, 32 */
#define SDRAM_DATA_WIDTH                16
/* column bit numbers: 8, 9, 10, 11 */
#define SDRAM_COLUMN_BITS               8
/* row bit numbers: 11, 12, 13 */
#define SDRAM_ROW_BITS                  12
/* cas latency clock number: 1, 2, 3 */
#define SDRAM_CAS_LATENCY               3
/* read pipe delay: 0, 1, 2 */
#define SDRAM_RPIPE_DELAY               1
/* clock divid: 2, 3 */
#define SDCLOCK_PERIOD                  2
/* refresh rate counter */
#define SDRAM_REFRESH_COUNT             ((uint32_t)0x056A)
#define SDRAM_SIZE                      ((uint32_t)0x800000)

/* Timing configuration for IS42S16400J */
/* 90 MHz of SD clock frequency (180MHz/2) */
/* TMRD: 2 Clock cycles */
#define LOADTOACTIVEDELAY               2
/* TXSR: 7x11.90ns */
#define EXITSELFREFRESHDELAY            7
/* TRAS: 4x11.90ns */
#define SELFREFRESHTIME                 4
/* TRC:  7x11.90ns */
#define ROWCYCLEDELAY                   7
/* TWR:  2 Clock cycles */
#define WRITERECOVERYTIME               2
/* TRP:  2x11.90ns */
#define RPDELAY                         2
/* TRCD: 2x11.90ns */
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
