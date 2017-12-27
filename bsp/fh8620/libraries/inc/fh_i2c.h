/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef FH_I2C_H_
#define FH_I2C_H_

#include "fh_def.h"

#define     OFFSET_I2C_CON             (0x0000)
#define     OFFSET_I2C_TAR             (0x0004)
#define     OFFSET_I2C_SAR             (0x0008)
#define     OFFSET_I2C_HS_MADDR        (0x000C)
#define     OFFSET_I2C_DATA_CMD        (0x0010)
#define     OFFSET_I2C_SS_SCL_HCNT     (0x0014)
#define     OFFSET_I2C_SS_SCL_LCNT     (0x0018)
#define     OFFSET_I2C_FS_SCL_HCNT     (0x001C)
#define     OFFSET_I2C_FS_SCL_LCNT     (0x0020)
#define     OFFSET_I2C_HS_SCL_HCNT     (0x0024)
#define     OFFSET_I2C_HS_SCL_LCNT     (0x0028)
#define     OFFSET_I2C_INTR_STAT       (0x002c)
#define     OFFSET_I2C_INTR_MASK       (0x0030)
#define     OFFSET_I2C_RAW_INTR_STAT   (0x0034)
#define     OFFSET_I2C_RX_TL           (0x0038)
#define     OFFSET_I2C_TX_TL           (0x003c)
#define     OFFSET_I2C_CLR_INTR        (0x0040)
#define     OFFSET_I2C_CLR_RX_UNDER    (0x0044)
#define     OFFSET_I2C_CLR_RX_OVER     (0x0048)
#define     OFFSET_I2C_CLR_TX_OVER     (0x004c)
#define     OFFSET_I2C_CLR_RD_REQ      (0x0050)
#define     OFFSET_I2C_CLR_TX_ABRT     (0x0054)
#define     OFFSET_I2C_CLR_RX_DONE     (0x0058)
#define     OFFSET_I2C_CLR_ACTIVITY    (0x005c)
#define     OFFSET_I2C_CLR_STOP_DET    (0x0060)
#define     OFFSET_I2C_CLR_START_DET   (0x0064)
#define     OFFSET_I2C_CLR_GEN_CALL    (0x0068)
#define     OFFSET_I2C_ENABLE          (0x006c)
#define     OFFSET_I2C_STATUS          (0x0070)
#define     OFFSET_I2C_TXFLR           (0x0074)
#define     OFFSET_I2C_RXFLR           (0x0078)
#define     OFFSET_I2C_DMA_CR          (0x0088)
#define     OFFSET_I2C_DMA_TDLR        (0x008c)
#define     OFFSET_I2C_DMA_RDLR        (0x0090)
#define     OFFSET_I2C_COMP_PARAM1     (0x00f4)
#define     OFFSET_I2C_TX_ABRT_SOURCE  (0x0080)

#define I2C_M_TEN       0x0100  /* this is a ten bit chip address */
#define I2C_M_RD        0x0001  /* read data, from slave to master */
#define I2C_M_NOSTART       0x4000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR  0x2000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK    0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK     0x0800  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN      0x0400  /* length will be first received byte */

#define DW_IC_CON_MASTER        0x1
#define DW_IC_CON_SPEED_STD     0x2
#define DW_IC_CON_SPEED_FAST        0x4
#define DW_IC_CON_10BITADDR_MASTER  0x10
#define DW_IC_CON_RESTART_EN        0x20
#define DW_IC_CON_SLAVE_DISABLE     0x40

#define DW_IC_INTR_RX_UNDER 0x001
#define DW_IC_INTR_RX_OVER  0x002
#define DW_IC_INTR_RX_FULL  0x004
#define DW_IC_INTR_TX_OVER  0x008
#define DW_IC_INTR_TX_EMPTY 0x010
#define DW_IC_INTR_RD_REQ   0x020
#define DW_IC_INTR_TX_ABRT  0x040
#define DW_IC_INTR_RX_DONE  0x080
#define DW_IC_INTR_ACTIVITY 0x100
#define DW_IC_INTR_STOP_DET 0x200
#define DW_IC_INTR_START_DET    0x400
#define DW_IC_INTR_GEN_CALL 0x800

#define DW_IC_INTR_DEFAULT_MASK     (DW_IC_INTR_RX_FULL | \
                     DW_IC_INTR_TX_EMPTY | \
                     DW_IC_INTR_TX_ABRT | \
                     DW_IC_INTR_STOP_DET)

#define DW_IC_STATUS_ACTIVITY   0x1
#define DW_IC_STATUS_MASTER_ACTIVITY   0x20

#define DW_IC_ERR_TX_ABRT   0x1

/*
 * status codes
 */
#define STATUS_IDLE         0x0
#define STATUS_WRITE_IN_PROGRESS    0x1
#define STATUS_READ_IN_PROGRESS     0x2

#define TIMEOUT         20 /* ms */

/*
 * hardware abort codes from the DW_IC_TX_ABRT_SOURCE register
 *
 * only expected abort codes are listed here
 * refer to the datasheet for the full list
 */
#define ABRT_7B_ADDR_NOACK  0
#define ABRT_10ADDR1_NOACK  1
#define ABRT_10ADDR2_NOACK  2
#define ABRT_TXDATA_NOACK   3
#define ABRT_GCALL_NOACK    4
#define ABRT_GCALL_READ     5
#define ABRT_SBYTE_ACKDET   7
#define ABRT_SBYTE_NORSTRT  9
#define ABRT_10B_RD_NORSTRT 10
#define ABRT_MASTER_DIS     11
#define ARB_LOST        12

#define DW_IC_TX_ABRT_7B_ADDR_NOACK (1UL << ABRT_7B_ADDR_NOACK)
#define DW_IC_TX_ABRT_10ADDR1_NOACK (1UL << ABRT_10ADDR1_NOACK)
#define DW_IC_TX_ABRT_10ADDR2_NOACK (1UL << ABRT_10ADDR2_NOACK)
#define DW_IC_TX_ABRT_TXDATA_NOACK  (1UL << ABRT_TXDATA_NOACK)
#define DW_IC_TX_ABRT_GCALL_NOACK   (1UL << ABRT_GCALL_NOACK)
#define DW_IC_TX_ABRT_GCALL_READ    (1UL << ABRT_GCALL_READ)
#define DW_IC_TX_ABRT_SBYTE_ACKDET  (1UL << ABRT_SBYTE_ACKDET)
#define DW_IC_TX_ABRT_SBYTE_NORSTRT (1UL << ABRT_SBYTE_NORSTRT)
#define DW_IC_TX_ABRT_10B_RD_NORSTRT    (1UL << ABRT_10B_RD_NORSTRT)
#define DW_IC_TX_ABRT_MASTER_DIS    (1UL << ABRT_MASTER_DIS)
#define DW_IC_TX_ARB_LOST       (1UL << ARB_LOST)

#define DW_IC_TX_ABRT_NOACK     (DW_IC_TX_ABRT_7B_ADDR_NOACK | \
                     DW_IC_TX_ABRT_10ADDR1_NOACK | \
                     DW_IC_TX_ABRT_10ADDR2_NOACK | \
                     DW_IC_TX_ABRT_TXDATA_NOACK | \
                     DW_IC_TX_ABRT_GCALL_NOACK)

static char *abort_sources[] = {
    [ABRT_7B_ADDR_NOACK] =
    "slave address not acknowledged (7bit mode)",
    [ABRT_10ADDR1_NOACK] =
    "first address byte not acknowledged (10bit mode)",
    [ABRT_10ADDR2_NOACK] =
    "second address byte not acknowledged (10bit mode)",
    [ABRT_TXDATA_NOACK] =
    "data not acknowledged",
    [ABRT_GCALL_NOACK] =
    "no acknowledgement for a general call",
    [ABRT_GCALL_READ] =
    "read after general call",
    [ABRT_SBYTE_ACKDET] =
    "start byte acknowledged",
    [ABRT_SBYTE_NORSTRT] =
    "trying to send start byte when restart is disabled",
    [ABRT_10B_RD_NORSTRT] =
    "trying to read when restart is disabled (10bit mode)",
    [ABRT_MASTER_DIS] =
    "trying to use disabled adapter",
    [ARB_LOST] =
    "lost arbitration",
};
/* i2c interrput definition */
#define M_GEN_CALL      (1<<11)
#define M_START_DET     (1<<10)
#define M_STOP_DET      (1<<9)
#define M_ACTIVITY      (1<<8)
#define M_RX_DONE       (1<<7)
#define M_TX_ABRT       (1<<6)
#define M_RD_REQ        (1<<5)
#define M_TX_EMPTY      (1<<4)
#define M_TX_OVER       (1<<3)
#define M_RX_FULL       (1<<2)
#define M_RX_OVER       (1<<1)
#define M_RX_UNDER      (1<<0)
#define M_NONE          (0)


struct i2c_config
{
    int speed_mode;
    UINT32 tx_fifo_depth;
    UINT32 rx_fifo_depth;
};

struct fh_i2c_obj
{
    UINT32        id;
    UINT32        irq;
    UINT32        base;
    UINT32        input_clock;
    UINT32        abort_source;
    struct i2c_config config;


};

rt_inline UINT32 I2C_SetTransmitThreshold(struct fh_i2c_obj *i2c_obj, int txtl)
{
    return SET_REG(i2c_obj->base + OFFSET_I2C_TX_TL, txtl);
}

rt_inline UINT32 I2C_GetReceiveFifoLevel(struct fh_i2c_obj *i2c_obj)
{
    return GET_REG(i2c_obj->base + OFFSET_I2C_RXFLR);
}

rt_inline UINT32 I2C_GetTransmitFifoLevel(struct fh_i2c_obj *i2c_obj)
{
    return GET_REG(i2c_obj->base + OFFSET_I2C_TXFLR);
}

rt_inline void I2C_SetSlaveAddress(struct fh_i2c_obj *i2c_obj, rt_uint16_t addr)
{
    UINT32 reg;
    reg = GET_REG(i2c_obj->base + OFFSET_I2C_TAR);
    reg &= ~(0x3ff);
    reg |= addr & 0x3ff;
    SET_REG(i2c_obj->base + OFFSET_I2C_TAR, reg);
}

rt_inline void I2C_Enable(struct fh_i2c_obj *i2c_obj, int enable)
{
    SET_REG(i2c_obj->base + OFFSET_I2C_ENABLE, enable);
}

rt_inline UINT8 I2C_GetData(struct fh_i2c_obj *i2c_obj)
{
    return GET_REG(i2c_obj->base + OFFSET_I2C_DATA_CMD) & 0xff;
}

rt_inline void I2C_SetDataCmd(struct fh_i2c_obj *i2c_obj, UINT32 reg)
{
    SET_REG(i2c_obj->base + OFFSET_I2C_DATA_CMD, reg);
}

rt_inline void I2C_SetInterruptMask(struct fh_i2c_obj *i2c_obj, UINT32 mask)
{
    SET_REG(i2c_obj->base + OFFSET_I2C_INTR_MASK, mask);
}

rt_inline UINT32 I2C_GetInterruptMask(struct fh_i2c_obj *i2c_obj)
{
    return GET_REG(i2c_obj->base + OFFSET_I2C_INTR_MASK);
}

void I2C_Init(struct fh_i2c_obj *i2c_obj);
int I2C_HandleTxAbort(struct fh_i2c_obj *i2c_obj);
UINT32 I2C_ClearAndGetInterrupts(struct fh_i2c_obj *i2c_obj);
int I2C_WaitMasterIdle(struct fh_i2c_obj *i2c_obj);
int I2C_WaitDeviceIdle(struct fh_i2c_obj *i2c_obj);

#endif /* FH_I2C_H_ */
