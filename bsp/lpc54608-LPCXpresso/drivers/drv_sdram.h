/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      The first version for LPC40xx
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

#include <board.h>

#define IOCON_PIO_DIGITAL_EN        0x0100u   /*!< Enables digital function */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC6               0x06u   /*!< Selects pin function 6 */
#define IOCON_PIO_INPFILT_OFF       0x0200u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_FAST         0x0400u   /*!< Fast mode, slew rate control is disabled */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port 0 */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port 0 */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port 0 */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port 0 */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port 0 */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port 0 */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port 0 */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port 0 */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port 1 */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port 1 */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port 1 */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port 1 */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port 1 */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port 0 */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port 1 */
#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port 0 */
#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port 0 */
#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port 0 */
#define PIN21_IDX                       21u   /*!< Pin number for pin 21 in a port 0 */
#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port 1 */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port 1 */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port 1 */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port 1 */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port 1 */
#define PIN28_IDX                       28u   /*!< Pin number for pin 28 in a port 1 */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port 0 */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port 0 */
#define PIN31_IDX                       31u   /*!< Pin number for pin 31 in a port 1 */
#define PORT0_IDX                        0u   /*!< Port index */
#define PORT1_IDX                        1u   /*!< Port index */
#define PORT3_IDX                        3u   /*!< Port index */

/* The SDRAM timing. */
#define SDRAM_REFRESHPERIOD_NS (64 * 1000000 / 4096) /* 4096 rows/ 64ms */
#define SDRAM_TRP_NS (18u)
#define SDRAM_TRAS_NS (42u)
#define SDRAM_TSREX_NS (67u)
#define SDRAM_TAPR_NS (18u)
#define SDRAM_TWRDELT_NS (6u)
#define SDRAM_TRC_NS (60u)
#define SDRAM_RFC_NS (60u)
#define SDRAM_XSR_NS (67u)
#define SDRAM_RRD_NS (12u)
#define SDRAM_MRD_NCLK (2u)
#define SDRAM_RAS_NCLK (2u)
#define SDRAM_MODEREG_VALUE (0x23u)
#define SDRAM_DEV_MEMORYMAP (0x09u) /* 128Mbits (8M*16, 4banks, 12 rows, 9 columns)*/

void lpc_sdram_hw_init(void);

#endif
