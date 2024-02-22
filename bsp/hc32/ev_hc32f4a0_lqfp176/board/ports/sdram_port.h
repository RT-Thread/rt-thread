/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-24     CDT          first version
 * 2024-02-20     CDT          modify timing configuration for using exclk clock frequency 30MHz
 *                             add t_rcd/t_rfc/t_rp configuration macros-definition
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

/* parameters for sdram peripheral */

/* chip#0/1/2/3: EXMC_DMC_CHIP0/1/2/3 */
#define SDRAM_CHIP                      EXMC_DMC_CHIP1
/* bank address */
#define SDRAM_BANK_ADDR                 (0x80000000UL)
/* size(kbyte):8MB = 8*1024*1KBytes */
#define SDRAM_SIZE                      (8UL * 1024UL * 1024UL)
/* auto precharge pin: EXMC_DMC_AUTO_PRECHARGE_A8/10 */
#define SDRAM_AUTO_PRECHARGE_PIN        EXMC_DMC_AUTO_PRECHARGE_A10
/* data width: EXMC_DMC_MEMORY_WIDTH_16BIT, EXMC_DMC_MEMORY_WIDTH_32BIT */
#define SDRAM_DATA_WIDTH                EXMC_DMC_MEMORY_WIDTH_16BIT
/* column bit numbers: EXMC_DMC_COLUMN_BITS_NUM8/9/10/11/12 */
#define SDRAM_COLUMN_BITS               EXMC_DMC_COLUMN_BITS_NUM8
/* row bit numbers: EXMC_DMC_ROW_BITS_NUM11/12/13/14/15/16 */
#define SDRAM_ROW_BITS                  EXMC_DMC_ROW_BITS_NUM12
/* cas latency clock number: 2, 3 */
#define SDRAM_CAS_LATENCY               2UL
/* burst length: EXMC_DMC_BURST_1BEAT/2BEAT/4BEAT/8BEAT/16BEAT */
#define SDRAM_BURST_LENGTH              EXMC_DMC_BURST_1BEAT

/* operating mode: SDRAM_MODEREG_OPERATING_MODE_STANDARD */
#define SDRAM_MODEREG_OPERATING_MODE    SDRAM_MODEREG_OPERATING_MODE_STANDARD
/* burst type: SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL/INTERLEAVED */
#define SDRAM_MODEREG_BURST_TYPE        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL
/* write burst mode: SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED/SINGLE */
#define SDRAM_MODEREG_WRITEBURST_MODE   SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED

/* timing configuration(EXCLK clock frequency: 30MHz) for IS42S16400J-7TLI */
/* refresh rate counter (EXCLK clock) */
#define SDRAM_REFRESH_COUNT             (450U)
/* TMDR: mode register command time (EXCLK clock) */
#define SDRAM_TMDR                      2U
/* TRAS: RAS to precharge delay time (EXCLK clock) */
#define SDRAM_TRAS                      2U
/* TRC:  active bank x to active bank x delay time (EXCLK clock) */
#define SDRAM_TRC                       2U
/* TRCD: RAS to CAS minimum delay time (EXCLK clock) */
#define SDRAM_TRCD_B                    3U
#define SDRAM_TRCD_P                    0U
/* TRFC: autorefresh command time (EXCLK clock) */
#define SDRAM_TRFC_B                    3U
#define SDRAM_TRFC_P                    0U
/* TRP:  precharge to RAS delay time (EXCLK clock) */
#define SDRAM_TRP_B                     3U
#define SDRAM_TRP_P                     0U
/* TRRD: active bank x to active bank y delay time (EXCLK clock) */
#define SDRAM_TRRD                      1U
/* TWR: write to precharge delay time (EXCLK clock). */
#define SDRAM_TWR                       2U
/* TWTR: write to read delay time (EXCLK clock). */
#define SDRAM_TWTR                      1U
/* TXP: exit power-down command time (EXCLK clock). */
#define SDRAM_TXP                       1U
/* TXSR: exit self-refresh command time (EXCLK clock). */
#define SDRAM_TXSR                      5U
/* TESR: self-refresh command time (EXCLK clock). */
#define SDRAM_TESR                      5U

/* memory mode register */
#define SDRAM_MODEREG_BURST_LENGTH_1              (0x0000U)
#define SDRAM_MODEREG_BURST_LENGTH_2              (0x0001U)
#define SDRAM_MODEREG_BURST_LENGTH_4              (0x0002U)
#define SDRAM_MODEREG_BURST_LENGTH_8              (0x0004U)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL       (0x0000U)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED      (0x0008U)
#define SDRAM_MODEREG_CAS_LATENCY_2               (0x0020U)
#define SDRAM_MODEREG_CAS_LATENCY_3               (0x0030U)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD     (0x0000U)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED  (0x0000U)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE      (0x0200U)

#endif
