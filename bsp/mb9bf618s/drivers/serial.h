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

#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

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

#define BPS                 115200  /* serial baudrate */

#define UART_RX_BUFFER_SIZE     64
#define UART_TX_BUFFER_SIZE     64

struct serial_int_rx
{
    rt_uint8_t  rx_buffer[UART_RX_BUFFER_SIZE];
    rt_uint32_t read_index, save_index;
};

struct serial_int_tx
{
    rt_uint8_t  tx_buffer[UART_TX_BUFFER_SIZE];
    rt_uint32_t write_index, save_index;
};

/*
 *  Enable/DISABLE Interrupt Controller
 */
/* deviation from MISRA-C:2004 Rule 19.7 */
#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

struct serial_device
{
    FM3_MFS03_UART_TypeDef* uart_device;
    /* irq number */
    IRQn_Type rx_irq, tx_irq;

    /* rx structure */
    struct serial_int_rx* int_rx;
    /* tx structure */
    struct serial_int_tx* int_tx;
};

void rt_hw_serial_isr(rt_device_t device);
void rt_hw_serial_init(void);

#endif
