/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     Bernard      first version
 * 2011-05-15     lgnq         modified according bernard's implementaion.
 */

#ifndef __FM3_UART_H__
#define __FM3_UART_H__

#include <rtthread.h>
#include "mb9bf506r.h"

#define SMR_SOE          0x01U
#define SMR_BDS          0x04U
#define SMR_SBL          0x08U
#define SMR_WUCR         0x10U
#define SMR_MD_UART      0x00U
#define SMR_MD_UART_MP   0x20U
#define SMR_MD_SIO       0x40U
#define SMR_MD_LIN       0x60U
#define SMR_MD_I2C       0x80U

#define SCR_TXE          0x01U
#define SCR_RXE          0x02U
#define SCR_TBIE         0x04U
#define SCR_TIE          0x08U
#define SCR_RIE          0x10U
#define SCR_UPGL         0x80U

#define SSR_TBI          0x01U
#define SSR_TDRE         0x02U
#define SSR_RDRF         0x04U
#define SSR_ORE          0x08U
#define SSR_FRE          0x10U
#define SSR_PE           0x20U
#define SSR_REC          0x80U

#define ESCR_P           0x08U
#define ESCR_PEN         0x10U
#define ESCR_INV         0x20U
#define ESCR_ESBL        0x40U
#define ESCR_FLWEN       0x80U
#define ESCR_DATABITS_8  0x00U
#define ESCR_DATABITS_5  0x01U
#define ESCR_DATABITS_6  0x02U
#define ESCR_DATABITS_7  0x03U
#define ESCR_DATABITS_9  0x04U

#define FIFO_SIZE       16

/*
 *  Enable/DISABLE Interrupt Controller
 */
/* deviation from MISRA-C:2004 Rule 19.7 */
#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

struct uart03_device
{
    FM3_MFS03_UART_TypeDef *uart_regs;
    /* irq number */
    IRQn_Type rx_irq;
    IRQn_Type tx_irq;
};

struct uart47_device
{
    FM3_MFS47_UART_TypeDef *uart_regs;
    /* irq number */
    IRQn_Type rx_irq;
    IRQn_Type tx_irq;
    rt_uint8_t fifo_size;
};

void rt_hw_serial_init(void);

#endif
