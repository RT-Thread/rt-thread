/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-28     bigmagic       first version
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <rthw.h>

#define BSC_C(BASE)         __REG32(BASE + 0x0000)    /* BSC Master Control */
#define BSC_S(BASE)         __REG32(BASE + 0x0004)    /* BSC Master Status */
#define BSC_DLEN(BASE)      __REG32(BASE + 0x0008)    /* BSC Master Data Length */
#define BSC_A(BASE)         __REG32(BASE + 0x000c)    /* BSC Master Slave Address */
#define BSC_FIFO(BASE)      __REG32(BASE + 0x0010)    /* BSC Master Data FIFO */
#define BSC_DIV(BASE)       __REG32(BASE + 0x0014)    /* BSC Master Clock Divider */
#define BSC_DEL(BASE)       __REG32(BASE + 0x0018)    /* BSC Master Data Delay */
#define BSC_CLKT(BASE)      __REG32(BASE + 0x001c)    /* BSC Master Clock Stretch Timeout */

/* Register masks for C Register */
#define BSC_C_I2CEN         (0x00008000) /* I2C Enable, 0 = disabled, 1 = enabled */
#define BSC_C_INTR          (0x00000400) /* Interrupt on RX */
#define BSC_C_INTT          (0x00000200) /* Interrupt on TX */
#define BSC_C_INTD          (0x00000100) /* Interrupt on DONE */
#define BSC_C_ST            (0x00000080) /* Start transfer, 1 = Start a new transfer */
#define BSC_C_CLEAR_1       (0x00000020) /* Clear FIFO Clear */
#define BSC_C_CLEAR_2       (0x00000010) /* Clear FIFO Clear */
#define BSC_C_READ          (0x00000001) /* Read transfer */

/* Register masks for S Register */
#define BSC_S_CLKT          (0x00000200) /* Clock stretch timeout */
#define BSC_S_ERR           (0x00000100) /* ACK error */
#define BSC_S_RXF           (0x00000080) /* RXF FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BSC_S_TXE           (0x00000040) /* TXE FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BSC_S_RXD           (0x00000020) /* RXD FIFO contains data */
#define BSC_S_TXD           (0x00000010) /* TXD FIFO can accept data */
#define BSC_S_RXR           (0x00000008) /* RXR FIFO needs reading (full) */
#define BSC_S_TXW           (0x00000004) /* TXW FIFO needs writing (full) */
#define BSC_S_DONE          (0x00000002) /* Transfer DONE */
#define BSC_S_TA            (0x00000001) /* Transfer Active */

#define BSC_FIFO_SIZE  (16)  /* BSC FIFO size */

typedef enum
{
    I2C_REASON_OK           = 0x00,      /* Success */
    I2C_REASON_ERROR_NACK   = 0x01,      /* Received a NACK */
    I2C_REASON_ERROR_CLKT   = 0x02,      /* Received Clock Stretch Timeout */
    I2C_REASON_ERROR_DATA   = 0x04       /* Not all data is sent / received */
} i2c_reason_codes;

int rt_hw_i2c_init(void);

#endif
