/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fi2c_master.c
 * Date: 2021-11-01 14:53:42
 * LastEditTime: 2022-02-18 08:36:46
 * Description:  This file is for i2c master drivers
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/2/18  add poll mode and intr mode
 */

/***************************** Include Files *********************************/

#include "fio.h"
#include "fsleep.h"
#include "fdebug.h"
#include "fi2c_hw.h"
#include "fi2c.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FI2C_DEBUG_TAG "I2C_MASTER"
#define FI2C_ERROR(format, ...) FT_DEBUG_PRINT_E(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_INFO(format, ...) FT_DEBUG_PRINT_I(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_DEBUG(format, ...) FT_DEBUG_PRINT_D(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)

#define FI2C_TIMEOUT 500

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FI2cMasterStartTrans
 * @msg: I2C主机开始传输
 * @return {*}
 * @param {FI2c} *instance_p, I2C驱动实例数据
 * @param {u32} mem_addr, 从机的片内偏移
 * @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
 * @param {u8} flag ,for cmd reg STOP,RESTART.
 */
static FError FI2cMasterStartTrans(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u16 flag)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FI2C_SUCCESS;
    u32 addr_len = mem_byte_len;

    ret = FI2cWaitBusBusy(base_addr);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    ret = FI2cSetTar(base_addr, instance_p->config.slave_addr); /* 设备地址 */
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    while (addr_len)
    {
        ret = FI2cWaitStatus(base_addr, FI2C_STATUS_TFNF);
        if (FI2C_SUCCESS != ret)
        {
            break;
        }
        if (FI2C_GET_STATUS(base_addr) & FI2C_STATUS_TFNF)
        {
            addr_len--;
            if (addr_len != 0)
            {
                FI2C_WRITE_REG32(base_addr, FI2C_DATA_CMD_OFFSET,
                                 (mem_addr >> (addr_len * BITS_PER_BYTE)) & FI2C_DATA_MASK); /* word address */
            }
            else
            {
                FI2C_WRITE_REG32(base_addr, FI2C_DATA_CMD_OFFSET,
                                 ((mem_addr >> (addr_len * BITS_PER_BYTE)) & FI2C_DATA_MASK) + flag); /* word address */
            }
        }
    }
    return ret;
}

/**
 * @name: FI2cMasterStopTrans
 * @msg: I2C主机结束传输
 * @return {*}
 * @param {FI2c} *instance_p, I2C驱动实例数据
 */
static FError FI2cMasterStopTrans(FI2c *instance_p)
{
    FASSERT(instance_p);
    FError ret = FI2C_SUCCESS;
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    u32 timeout = 0;

    FI2C_INFO("GET MASTER STOP, stat: 0x%x, 0x%x", FI2C_READ_INTR_STAT(base_addr),
              FI2C_READ_RAW_INTR_STAT(base_addr));

    while (TRUE)
    {
        if (FI2C_READ_RAW_INTR_STAT(base_addr) & FI2C_INTR_STOP_DET)
        {
            reg_val = FI2C_READ_REG32(base_addr, FI2C_CLR_STOP_DET_OFFSET); /* read to clr intr status */
            break;
        }
        else if (FI2C_TIMEOUT < ++timeout)
        {
            break; /* wait timeout, but no error code ret */
        }
    }

    ret = FI2cWaitBusBusy(base_addr);
    if (FI2C_SUCCESS == ret)
    {
        ret = FI2cFlushRxFifo(base_addr);
    }

    return ret;
}

/**
 * @name: FI2cMasterReadPoll
 * @msg: I2C主机读，阻塞直到完成读操作或失败
 * @return {FError *} 返回错误码
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} mem_addr 从机的内部偏移地址
 * @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
 * @param {u8} *buf_p 读目的缓冲区
 * @param {int} buf_len 读目的缓冲区长度
 */
FError FI2cMasterReadPoll(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u8 *buf_p, u32 buf_len)
{
    FError ret = FI2C_SUCCESS;
    FASSERT(instance_p);
    u32 mask;
    u32 reg_val;
    u32 tx_len = buf_len;
    u32 rx_len = buf_len;
    u32 rx_limit, tx_limit;
    u32 trans_timeout = 0;
    uintptr base_addr = instance_p->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FI2C_ERROR("i2c driver is not ready.");
        return FI2C_ERR_NOT_READY;
    }

    if (FI2C_MASTER != instance_p->config.work_mode)
    {
        FI2C_ERROR("i2c work mode shall be master.");
        return FI2C_ERR_INVAL_STATE;
    }

    ret = FI2cMasterStartTrans(instance_p, mem_addr, mem_byte_len, FI2C_DATA_CMD_WRITE);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    /*for trigger rx intr*/
    while (tx_len > 0 || rx_len > 0)
    {
        /* code */
        rx_limit = FI2C_IIC_FIFO_MAX_LV - FI2C_READ_REG32(base_addr, FI2C_RXFLR_OFFSET);
        tx_limit = FI2C_IIC_FIFO_MAX_LV - FI2C_READ_REG32(base_addr, FI2C_TXFLR_OFFSET);

        while (tx_len > 0 & rx_limit > 0 & tx_limit > 0)
        {
            /* code */
            if (tx_len == 1)
            {

                reg_val = FI2C_DATA_CMD_READ | FI2C_DATA_CMD_STOP;
                FI2C_WRITE_REG32(instance_p->config.base_addr, FI2C_DATA_CMD_OFFSET, reg_val);
            }
            else
            {
                reg_val = FI2C_DATA_CMD_READ;
                FI2C_WRITE_REG32(instance_p->config.base_addr, FI2C_DATA_CMD_OFFSET, reg_val);
            }
            tx_len--;
            rx_limit--;
            tx_limit--;
        }

        u8 rx_tem = FI2C_READ_REG32(base_addr, FI2C_RXFLR_OFFSET);
        while (rx_tem > 0 & rx_len > 0)
        {
            /* code */
            if (FI2C_GET_STATUS(base_addr) & FI2C_STATUS_RFNE)
            {
                /* trans one byte */
                *buf_p++ = FI2C_READ_DATA(base_addr);
                rx_len--;
                rx_tem--;
                trans_timeout = 0;
            }
            else if (FI2C_TIMEOUT < (++trans_timeout))
            {
                ret = FI2C_ERR_TIMEOUT;
                FI2C_ERROR("timeout in i2c master read.");
                break;
            }
        }
    }
    if (FI2C_SUCCESS == ret)
    {
        ret = FI2cMasterStopTrans(instance_p);
    }
    return ret;
}

/**
 * @name: FI2cMasterWritePoll
 * @msg: I2C主机写，阻塞直到完成写操作或失败
 * @return {FError *} 返回错误码
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} mem_addr 从机的内部偏移地址
 * @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
 * @param {u8} *buf_p 写源缓冲区
 * @param {size_t} buf_len 写源缓冲区长度
 */
FError FI2cMasterWritePoll(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, const u8 *buf_p, u32 buf_len)
{
    FASSERT(instance_p && buf_p);
    FError ret = FI2C_SUCCESS;
    u32 buf_idx = buf_len;
    u32 tx_limit;
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    u32 trans_timeout = 0;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FI2C_ERROR("i2c driver is not ready.");
        return FI2C_ERR_NOT_READY;
    }
    if (FI2C_MASTER != instance_p->config.work_mode)
    {
        FI2C_ERROR("i2c work mode shall be master.");
        return FI2C_ERR_INVAL_STATE;
    }

    ret = FI2cMasterStartTrans(instance_p, mem_addr, mem_byte_len, FI2C_DATA_CMD_WRITE);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    while (buf_idx)
    {
        tx_limit = FI2C_IIC_FIFO_MAX_LV - FI2C_READ_REG32(base_addr, FI2C_TXFLR_OFFSET);
        while (tx_limit > 0 & buf_idx > 0)
        {
            if (FI2C_GET_STATUS(base_addr) & FI2C_STATUS_TFNF)
            {
                if (1 == buf_idx)
                {
                    reg_val = (FI2C_DATA_MASK & *buf_p) |
                              FI2C_DATA_CMD_WRITE |
                              FI2C_DATA_CMD_STOP;
                    FI2C_INFO("Write Stop Singal.");
                }
                else
                {
                    reg_val = (FI2C_DATA_MASK & *buf_p) |
                              FI2C_DATA_CMD_WRITE;
                }
                buf_idx--;
                tx_limit--;
                FI2C_WRITE_REG32(base_addr, FI2C_DATA_CMD_OFFSET, reg_val);
                buf_p++;
                trans_timeout = 0;
            }
            else if (FI2C_TIMEOUT < ++trans_timeout)
            {
                ret = FI2C_ERR_TIMEOUT;
                FI2C_ERROR("Timeout in i2c master write.");
                break;
            }
        }
    }
    if (FI2C_SUCCESS == ret)
    {
        ret = FI2cMasterStopTrans(instance_p);
    }
    return ret;
}

/**
 * @name: FI2cMasterReadIntr
 * @msg: I2C主机读，中断完成读操作或失败
 * @return {FError *} 返回错误码
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} mem_addr 从机的内部偏移地址
 * @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
 * @param {u8} *buf_p 读目的缓冲区
 * @param {int} buf_len 读目的缓冲区长度
 */
FError FI2cMasterReadIntr(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u8 *buf_p, u32 buf_len)
{
    FError ret = FI2C_SUCCESS;
    FASSERT(instance_p);
    u32 mask;
    u32 reg_val;
    u32 trans_timeout;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FI2C_ERROR("i2c driver is not ready.");
        return FI2C_ERR_NOT_READY;
    }
    if (FI2C_MASTER != instance_p->config.work_mode)
    {
        FI2C_ERROR("i2c work mode shall be master.");
        return FI2C_ERR_INVAL_STATE;
    }

    while (instance_p->status != STATUS_IDLE)
    {
        /* code */
        fsleep_millisec(1);
        if (FI2C_TIMEOUT < (++trans_timeout))
        {
            ret = FI2C_ERR_TIMEOUT;
            FI2C_ERROR("Timeout in i2c master read intr.");
            break;
        }
    }
    instance_p->rxframe.data_buff = buf_p;
    instance_p->rxframe.rx_total_num = buf_len;
    instance_p->txframe.tx_total_num = buf_len;
    instance_p->rxframe.rx_cnt = 0;
    FI2C_SET_RX_TL(instance_p->config.base_addr, 0);/* 0 表示接收缓冲区大于等于 1 时触发中断 */
    ret = FI2cMasterStartTrans(instance_p, mem_addr, mem_byte_len, FI2C_DATA_CMD_WRITE);
    instance_p->status = STATUS_READ_IN_PROGRESS;
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    mask = FI2C_GET_INTRRUPT_MASK(instance_p->config.base_addr);
    mask |= FI2C_INTR_MASTER_RD_MASK;
    ret = FI2cMasterSetupIntr(instance_p, mask);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    return ret;
}

/**
 * @name: FI2cMasterWriteIntr
 * @msg: I2C主机写，中断写操作或失败
 * @return {FError *} 返回错误码
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} mem_addr 从机的内部偏移地址
 * @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
 * @param {u8} *buf_p 写源缓冲区
 * @param {size_t} buf_len 写源缓冲区长度
 */
FError FI2cMasterWriteIntr(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, const u8 *buf_p, u32 buf_len)
{
    FError ret = FI2C_SUCCESS;
    FASSERT(instance_p);
    u32 mask;
    u32 trans_timeout = 0;
    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FI2C_ERROR("i2c driver is not ready.");
        return FI2C_ERR_NOT_READY;
    }

    if (FI2C_MASTER != instance_p->config.work_mode)
    {
        FI2C_ERROR("i2c work mode shall be master.");
        return FI2C_ERR_INVAL_STATE;
    }
    while (instance_p->status != STATUS_IDLE)
    {
        /* code */
        fsleep_millisec(1);
        if (FI2C_TIMEOUT < (++trans_timeout))
        {
            ret = FI2C_ERR_TIMEOUT;
            FI2C_ERROR("Timeout in i2c master write intr.");
            break;
        }
    }
    instance_p->txframe.data_buff = buf_p;
    instance_p->txframe.tx_total_num = buf_len;
    instance_p->txframe.tx_cnt = 0;
    ret = FI2cMasterStartTrans(instance_p, mem_addr, mem_byte_len, FI2C_DATA_CMD_WRITE);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    instance_p->status = STATUS_WRITE_IN_PROGRESS;
    mask = FI2C_GET_INTRRUPT_MASK(instance_p->config.base_addr);
    mask |= FI2C_INTR_MASTER_WR_MASK;
    ret = FI2cMasterSetupIntr(instance_p, mask);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }
    return ret;
}
