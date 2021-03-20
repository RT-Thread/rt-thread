/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_GPIO_EX_H__
#define AB32VG1_HAL_GPIO_EX_H__

/* Alternate function */
#define GPIO_AF_MAP_Gx(AF, Gx)  ((uint32_t)((Gx) << (AF)))
#define GPIO_AF_MAP_CLR(AF)     ((uint32_t)(0xfu << (AF)))

#define GPIO_AF_G1              (1u)
#define GPIO_AF_G2              (2u)
#define GPIO_AF_G3              (3u)
#define GPIO_AF_G4              (4u)
#define GPIO_AF_G5              (5u)
#define GPIO_AF_G6              (6u)
#define GPIO_AF_G7              (7u)

/**
 * UART0:
 * G1: tx:PA7 rx:PA6
 * G2: tx:PB2 rx:PB1
 * G3: tx:PB3 rx:PB4
 * G4: tx:PE7 rx:PE6
 * G5: tx:PA1 rx:PA0
 * G6: tx:PE0 rx:PE1
 * G7: tx:PF2 rx:map to tx
 *
 * UART1:
 * G1: tx:PA7 rx:PA6
 * G2: tx:PA4 rx:PA3
 * G3: tx:PF2 rx:map to tx
 * 
 * UART2:
 * G1: tx:PE3 rx:PE2
 * G2: tx:PB2 rx:PB1
 */

#define UT2RXMAP_AF             (8u)
#define UT2TXMAP_AF             (4u)

#define UT1RXMAP_AF             (28u)
#define UT1TXMAP_AF             (24u)
#define HSUTRXMAP_AF            (20u)
#define HSUTTXMAP_AF            (16u)
#define UT0RXMAP_AF             (12u)
#define UT0TXMAP_AF             ( 8u)
#define SPI0MAP_AF              ( 4u)
#define SD0MAP_AF               ( 0u)

#define UT1RXMAP_TX             ((uint32_t)(0x3u << (UT1RXMAP_AF)))
#define UT0RXMAP_TX             ((uint32_t)(0x7u << (UT0RXMAP_AF)))

/**
 * LPWM3:
 * G1: PE7
 * G2: PF2
 * G3: PA3
 *
 * LPWM2:
 * G1: PE6
 * G2: PE0
 * G3: PA2
 *
 * LPWM1:
 * G1: PE5
 * G2: PB4
 * G3: PA1
 *
 * LPWM0:
 * G1: PE4
 * G2: PB3
 * G3: PA0
 */
#define LPWM3MAP_AF             (28u)
#define LPWM2MAP_AF             (24u)
#define LPWM1MAP_AF             (20u)
#define LPWM0MAP_AF             (16u)

/**
 * TMR5:
 * G1: PE1 PE2 PE3
 *
 * TMR4:
 * G1: PA5 PA6 PA7
 *
 * TMR3:
 * G1: PB0 PB1 PB2
 */
#define TMR5MAP_AF              (16u)
#define TMR4MAP_AF              (12u)
#define TMR3MAP_AF              ( 8u)

#endif
