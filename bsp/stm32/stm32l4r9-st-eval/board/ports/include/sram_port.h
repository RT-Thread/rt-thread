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
/* Bank1 */
#define SRAM_TARGET_BANK                1
/* stm32f4 Bank1:0x60000000 */
#define SRAM_BANK_ADDR                  ((uint32_t)0x60000000)
/* data width: 8, 16, 32 */
#define SRAM_DATA_WIDTH                 16
/* sram size */
#define SRAM_SIZE                       ((uint32_t)0x200000)

/* Timing configuration for IS61WV102416BLL-10MLI */
#define ADDRESSSETUPTIME                2
#define ADDRESSHOLDTIME                 1
#define DATASETUPTIME                   1
#define DATAHOLDTIME                    1
#define BUSTURNAROUNDDURATION           0
#define CLKDIVISION                     2
#define DATALATENCY                     2
#define ACCESSMODE                      FMC_ACCESS_MODE_A
/* Timing configuration for IS61WV102416BLL-10MLI */

#endif
