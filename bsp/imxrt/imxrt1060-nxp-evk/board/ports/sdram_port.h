/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-05     zylx         The first version for STM32F4xx
 * 2019-4-25      misonyo      port to IMXRT
 */

#ifndef SDRAM_PORT_H__
#define SDRAM_PORT_H__

/* parameters for sdram peripheral */

#define SDRAM_BANK_ADDR                 ((uint32_t)0x80000000U)
/* region#0/1/2/3: kSEMC_SDRAM_CS0/1/2/3 */
#define SDRAM_REGION                    kSEMC_SDRAM_CS0
/* CS pin: kSEMC_MUXCSX0/1/2/3 */
#define SDRAM_CS_PIN                    kSEMC_MUXCSX0
/* size(kbyte):32MB = 32*1024*1KBytes */
#define SDRAM_SIZE                      ((uint32_t)0x8000)
/* data width: kSEMC_PortSize8Bit,kSEMC_PortSize16Bit */
#define SDRAM_DATA_WIDTH                kSEMC_PortSize16Bit
/* column bit numbers: kSEMC_SdramColunm_9/10/11/12bit */
#define SDRAM_COLUMN_BITS               kSEMC_SdramColunm_9bit
/* cas latency clock number: kSEMC_LatencyOne/Two/Three */
#define SDRAM_CAS_LATENCY               kSEMC_LatencyThree

/* Timing configuration for W9825G6KH */
/* TRP:precharge to active command time (ns) */
#define SDRAM_TRP                       18
/* TRCD:active to read/write command delay time (ns) */
#define SDRAM_TRCD                      18
/* The time between two refresh commands,Use the maximum of the (Trfc , Txsr).(ns) */
#define SDRAM_REFRESH_RECOVERY          67
/* TWR:write recovery time (ns). */
#define SDRAM_TWR                       12
/* TRAS:active to precharge command time (ns). */
#define SDRAM_TRAS       42
/* TRC time (ns). */
#define SDRAM_TRC                       60
/* active to active time (ns). */
#define SDRAM_ACT2ACT                   60
/* refresh time (ns). 64ms */
#define SDRAM_REFRESH_ROW               64 * 1000000 / 8192

#endif /* SDRAM_PORT_H__ */
