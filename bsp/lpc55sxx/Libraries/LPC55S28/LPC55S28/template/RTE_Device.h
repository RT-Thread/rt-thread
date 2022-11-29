/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, UART0-UART9. */
/* User needs to provide the implementation of USARTX_GetFreq/USARTX_InitPins/USARTX_DeinitPins for the enabled USART
 * instance. */
#define RTE_USART0        0
#define RTE_USART0_DMA_EN 0
#define RTE_USART1        0
#define RTE_USART1_DMA_EN 0
#define RTE_USART2        0
#define RTE_USART2_DMA_EN 0
#define RTE_USART3        0
#define RTE_USART3_DMA_EN 0
#define RTE_USART4        0
#define RTE_USART4_DMA_EN 0
#define RTE_USART5        0
#define RTE_USART5_DMA_EN 0
#define RTE_USART6        0
#define RTE_USART6_DMA_EN 0
#define RTE_USART7        0
#define RTE_USART7_DMA_EN 0

/* USART configuration. */
#define USART_RX_BUFFER_LEN     64
#define USART0_RX_BUFFER_ENABLE 0
#define USART1_RX_BUFFER_ENABLE 0
#define USART2_RX_BUFFER_ENABLE 0
#define USART3_RX_BUFFER_ENABLE 0
#define USART4_RX_BUFFER_ENABLE 0
#define USART5_RX_BUFFER_ENABLE 0
#define USART6_RX_BUFFER_ENABLE 0
#define USART7_RX_BUFFER_ENABLE 0

#define RTE_USART0_PIN_INIT        USART0_InitPins
#define RTE_USART0_PIN_DEINIT      USART0_DeinitPins
#define RTE_USART0_DMA_TX_CH       5
#define RTE_USART0_DMA_TX_DMA_BASE DMA0
#define RTE_USART0_DMA_RX_CH       4
#define RTE_USART0_DMA_RX_DMA_BASE DMA0

#define RTE_USART1_PIN_INIT        USART1_InitPins
#define RTE_USART1_PIN_DEINIT      USART1_DeinitPins
#define RTE_USART1_DMA_TX_CH       7
#define RTE_USART1_DMA_TX_DMA_BASE DMA0
#define RTE_USART1_DMA_RX_CH       6
#define RTE_USART1_DMA_RX_DMA_BASE DMA0

#define RTE_USART2_PIN_INIT        USART2_InitPins
#define RTE_USART2_PIN_DEINIT      USART2_DeinitPins
#define RTE_USART2_DMA_TX_CH       8
#define RTE_USART2_DMA_TX_DMA_BASE DMA0
#define RTE_USART2_DMA_RX_CH       9
#define RTE_USART2_DMA_RX_DMA_BASE DMA0

#define RTE_USART3_PIN_INIT        USART3_InitPins
#define RTE_USART3_PIN_DEINIT      USART3_DeinitPins
#define RTE_USART3_DMA_TX_CH       10
#define RTE_USART3_DMA_TX_DMA_BASE DMA0
#define RTE_USART3_DMA_RX_CH       11
#define RTE_USART3_DMA_RX_DMA_BASE DMA0

#define RTE_USART4_PIN_INIT        USART4_InitPins
#define RTE_USART4_PIN_DEINIT      USART4_DeinitPins
#define RTE_USART4_DMA_TX_CH       13
#define RTE_USART4_DMA_TX_DMA_BASE DMA0
#define RTE_USART4_DMA_RX_CH       12
#define RTE_USART4_DMA_RX_DMA_BASE DMA0

#define RTE_USART5_PIN_INIT        USART5_InitPins
#define RTE_USART5_PIN_DEINIT      USART5_DeinitPins
#define RTE_USART5_DMA_TX_CH       15
#define RTE_USART5_DMA_TX_DMA_BASE DMA0
#define RTE_USART5_DMA_RX_CH       14
#define RTE_USART5_DMA_RX_DMA_BASE DMA0

#define RTE_USART6_PIN_INIT        USART6_InitPins
#define RTE_USART6_PIN_DEINIT      USART6_DeinitPins
#define RTE_USART6_DMA_TX_CH       17
#define RTE_USART6_DMA_TX_DMA_BASE DMA0
#define RTE_USART6_DMA_RX_CH       16
#define RTE_USART6_DMA_RX_DMA_BASE DMA0

#define RTE_USART7_PIN_INIT        USART7_InitPins
#define RTE_USART7_PIN_DEINIT      USART7_DeinitPins
#define RTE_USART7_DMA_TX_CH       19
#define RTE_USART7_DMA_TX_DMA_BASE DMA0
#define RTE_USART7_DMA_RX_CH       18
#define RTE_USART7_DMA_RX_DMA_BASE DMA0

/* I2C Select, I2C0 -I2C9*/
/* User needs to provide the implementation of I2CX_GetFreq/I2CX_InitPins/I2CX_DeinitPins for the enabled I2C instance.
 */
#define RTE_I2C0        0
#define RTE_I2C0_DMA_EN 0
#define RTE_I2C1        0
#define RTE_I2C1_DMA_EN 0
#define RTE_I2C2        0
#define RTE_I2C2_DMA_EN 0
#define RTE_I2C3        0
#define RTE_I2C3_DMA_EN 0
#define RTE_I2C4        0
#define RTE_I2C4_DMA_EN 0
#define RTE_I2C5        0
#define RTE_I2C5_DMA_EN 0
#define RTE_I2C6        0
#define RTE_I2C6_DMA_EN 0
#define RTE_I2C7        0
#define RTE_I2C7_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C0_Master_DMA_BASE DMA0
#define RTE_I2C0_Master_DMA_CH   1

#define RTE_I2C1_Master_DMA_BASE DMA0
#define RTE_I2C1_Master_DMA_CH   3

#define RTE_I2C2_Master_DMA_BASE DMA0
#define RTE_I2C2_Master_DMA_CH   5

#define RTE_I2C3_Master_DMA_BASE DMA0
#define RTE_I2C3_Master_DMA_CH   7

#define RTE_I2C4_Master_DMA_BASE DMA0
#define RTE_I2C4_Master_DMA_CH   9

#define RTE_I2C5_Master_DMA_BASE DMA0
#define RTE_I2C5_Master_DMA_CH   11

#define RTE_I2C6_Master_DMA_BASE DMA0
#define RTE_I2C6_Master_DMA_CH   13

#define RTE_I2C7_Master_DMA_BASE DMA0
#define RTE_I2C7_Master_DMA_CH   15

/* SPI select, SPI0 - SPI9.*/
/* User needs to provide the implementation of SPIX_GetFreq/SPIX_InitPins/SPIX_DeinitPins for the enabled SPI instance.
 */
#define RTE_SPI0        0
#define RTE_SPI0_DMA_EN 0
#define RTE_SPI1        0
#define RTE_SPI1_DMA_EN 0
#define RTE_SPI2        0
#define RTE_SPI2_DMA_EN 0
#define RTE_SPI3        0
#define RTE_SPI3_DMA_EN 0
#define RTE_SPI4        0
#define RTE_SPI4_DMA_EN 0
#define RTE_SPI5        0
#define RTE_SPI5_DMA_EN 0
#define RTE_SPI6        0
#define RTE_SPI6_DMA_EN 0
#define RTE_SPI7        0
#define RTE_SPI7_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI0_PIN_INIT        SPI0_InitPins
#define RTE_SPI0_PIN_DEINIT      SPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH       1
#define RTE_SPI0_DMA_TX_DMA_BASE DMA0
#define RTE_SPI0_DMA_RX_CH       0
#define RTE_SPI0_DMA_RX_DMA_BASE DMA0

#define RTE_SPI1_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI1_PIN_INIT        SPI1_InitPins
#define RTE_SPI1_PIN_DEINIT      SPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH       3
#define RTE_SPI1_DMA_TX_DMA_BASE DMA0
#define RTE_SPI1_DMA_RX_CH       2
#define RTE_SPI1_DMA_RX_DMA_BASE DMA0

#define RTE_SPI2_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI2_PIN_INIT        SPI2_InitPins
#define RTE_SPI2_PIN_DEINIT      SPI2_DeinitPins
#define RTE_SPI2_DMA_TX_CH       5
#define RTE_SPI2_DMA_TX_DMA_BASE DMA0
#define RTE_SPI2_DMA_RX_CH       4
#define RTE_SPI2_DMA_RX_DMA_BASE DMA0

#define RTE_SPI3_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI3_PIN_INIT        SPI3_InitPins
#define RTE_SPI3_PIN_DEINIT      SPI3_DeinitPins
#define RTE_SPI3_DMA_TX_CH       7
#define RTE_SPI3_DMA_TX_DMA_BASE DMA0
#define RTE_SPI3_DMA_RX_CH       6
#define RTE_SPI3_DMA_RX_DMA_BASE DMA0

#define RTE_SPI4_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI4_PIN_INIT        SPI4_InitPins
#define RTE_SPI4_PIN_DEINIT      SPI4_DeinitPins
#define RTE_SPI4_DMA_TX_CH       9
#define RTE_SPI4_DMA_TX_DMA_BASE DMA0
#define RTE_SPI4_DMA_RX_CH       8
#define RTE_SPI4_DMA_RX_DMA_BASE DMA0

#define RTE_SPI5_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI5_PIN_INIT        SPI5_InitPins
#define RTE_SPI5_PIN_DEINIT      SPI5_DeinitPins
#define RTE_SPI5_DMA_TX_CH       11
#define RTE_SPI5_DMA_TX_DMA_BASE DMA0
#define RTE_SPI5_DMA_RX_CH       10
#define RTE_SPI5_DMA_RX_DMA_BASE DMA0

#define RTE_SPI6_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI6_PIN_INIT        SPI6_InitPins
#define RTE_SPI6_PIN_DEINIT      SPI6_DeinitPins
#define RTE_SPI6_DMA_TX_CH       13
#define RTE_SPI6_DMA_TX_DMA_BASE DMA0
#define RTE_SPI6_DMA_RX_CH       12
#define RTE_SPI6_DMA_RX_DMA_BASE DMA0

#define RTE_SPI7_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI7_PIN_INIT        SPI7_InitPins
#define RTE_SPI7_PIN_DEINIT      SPI7_DeinitPins
#define RTE_SPI7_DMA_TX_CH       15
#define RTE_SPI7_DMA_TX_DMA_BASE DMA0
#define RTE_SPI7_DMA_RX_CH       14
#define RTE_SPI7_DMA_RX_DMA_BASE DMA0

#endif /* _RTE_DEVICE_H */
