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
 * FilePath: fi2c_intr.c
 * Date: 2021-11-01 14:53:42
 * LastEditTime: 2022-02-18 08:36:38
 * Description:  This file is for I2C interrupt operation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/02/18  add fi2c_master interrupt and support slave mode
 */

/***************************** Include Files *********************************/
#include <string.h>
#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fdrivers_port.h"
#include "fi2c_hw.h"
#include "fi2c.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FI2C_DEBUG_TAG "I2C"
#define FI2C_ERROR(format, ...) FT_DEBUG_PRINT_E(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_INFO(format, ...) FT_DEBUG_PRINT_I(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_DEBUG(format, ...) FT_DEBUG_PRINT_D(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Variable Definitions *****************************/

/*****************************************************************************/

/************************** Function Prototypes ******************************/
static inline void FI2cMasterCallEvtHandler(FI2c *instance_p, u32 evt, void *para)
{
    FASSERT(instance_p);
    FASSERT(evt < FI2C_MASTER_INTR_EVT_NUM);

    if (instance_p->master_evt_handlers[evt])
    {
        instance_p->master_evt_handlers[evt](instance_p, para);
    }
}

static inline void FI2cSlaveCallEvtHandler(FI2c *instance_p, u32 evt, void *para)
{
    FASSERT(instance_p);
    FASSERT(evt < FI2C_SLAVE_INTR_EVT_NUM);
    FASSERT(para);

    if (instance_p->slave_evt_handlers[evt])
    {
        instance_p->slave_evt_handlers[evt](instance_p, para);
    }
}

/**
 * @name: FI2cStubHandler
 * @msg: 主机模式下的I2C中断默认回调函数
 * @return {*}
 * @param {void} *instance_p I2C驱动实例数据
 * @param {void} *param, 中断输入参数
 */
static void FI2cStubHandler(void *instance_p, void *param)
{
    FASSERT(instance_p);
    FI2c *instance = (FI2c *)(instance_p);
    uintptr base_addr = instance->config.base_addr;

    FI2C_INFO("id: %d ,intr cause: 0x%x",
              instance->config.instance_id,
              FI2C_READ_INTR_STAT(base_addr));
}

/**
 * @name: FI2cMasterIntrTxEmptyHandler
 * @msg: 主机模式下的I2C TX_FIFO空中断处理函数
 * @return {*}
 * @param {void} *instance_p I2C驱动实例数据
 */
static void FI2cMasterIntrTxEmptyHandler(FI2c *instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    const u8 *buf_p = instance_p->txframe.data_buff;

    u32 intr_mask;
    u32 buf_len;
    u32 reg_val;
    u32 rx_limit, tx_limit;

    buf_len = instance_p->txframe.tx_total_num - instance_p->txframe.tx_cnt;

    rx_limit = FI2C_IIC_FIFO_MAX_LV - FI2C_READ_REG32(base_addr, FI2C_RXFLR_OFFSET);
    tx_limit = FI2C_IIC_FIFO_MAX_LV - FI2C_READ_REG32(base_addr, FI2C_TXFLR_OFFSET);
    while (buf_len > 0 & rx_limit > 0 & tx_limit > 0)
    {
        if (1 == buf_len)
        {
            if (instance_p->status == STATUS_WRITE_IN_PROGRESS)
            {
                reg_val = (FI2C_DATA_MASK & *((u8 *)(instance_p->txframe.data_buff))) |
                          FI2C_DATA_CMD_WRITE |
                          FI2C_DATA_CMD_STOP;
                instance_p->txframe.data_buff++;
                FI2C_INFO("Write Stop Singal.");
            }
            else if (instance_p->status == STATUS_READ_IN_PROGRESS)
            {
                reg_val = FI2C_DATA_CMD_READ | FI2C_DATA_CMD_STOP;
            }
        }
        else
        {
            if (instance_p->status == STATUS_WRITE_IN_PROGRESS)
            {
                reg_val = (FI2C_DATA_MASK & *((u8 *)(instance_p->txframe.data_buff))) |
                          FI2C_DATA_CMD_WRITE;
                instance_p->txframe.data_buff++;
            }
            else if (instance_p->status == STATUS_READ_IN_PROGRESS)
            {
                reg_val = FI2C_DATA_CMD_READ;
            }
        }
        FI2C_WRITE_REG32(base_addr, FI2C_DATA_CMD_OFFSET, reg_val);
        rx_limit--;
        tx_limit--;
        buf_len--;
    }
    instance_p->txframe.tx_cnt = instance_p->txframe.tx_total_num - buf_len;
    /*tx over.*/
    if (instance_p->txframe.tx_cnt == instance_p->txframe.tx_total_num)
    {
        instance_p->txframe.tx_cnt = 0;
        if (instance_p->status == STATUS_WRITE_IN_PROGRESS)
        {
            instance_p->status = STATUS_IDLE;
        }
        intr_mask = FI2C_GET_INTRRUPT_MASK(instance_p->config.base_addr);
        intr_mask &= ~(FI2C_INTR_TX_EMPTY);
        FI2C_SET_INTRRUPT_MASK(instance_p->config.base_addr, intr_mask);
    }
}

/**
 * @name: FI2cMasterIntrRxFullHandler
 * @msg: 主机模式下的I2C RX_FIFO满处理函数，可通过FI2C_SET_RX_TL(address,level);设置触发level
 * @return {*}
 * @param {void} *instance_p I2C驱动实例数据
 */
static void FI2cMasterIntrRxFullHandler(FI2c *instance_p)
{
    FASSERT(instance_p);
    u32 intr_mask;
    uintptr base_addr = instance_p->config.base_addr;
    u8 emptyfifo = FI2C_READ_REG32(base_addr, FI2C_RXFLR_OFFSET);
    u32 i = 0u;
    u32 reg_val;
    for (i = 0; i < emptyfifo; i++)
    {
        *((u8 *)(instance_p->rxframe.data_buff++)) = FI2C_READ_DATA(base_addr);
    }
    instance_p->rxframe.rx_cnt += emptyfifo;
    if (instance_p->rxframe.rx_cnt >= instance_p->rxframe.rx_total_num)
    {
        instance_p->rxframe.rx_cnt = 0;
        instance_p->status = STATUS_IDLE;
        intr_mask = FI2C_GET_INTRRUPT_MASK(base_addr);
        intr_mask &= ~(FI2C_INTR_RX_FULL);
        FI2C_SET_INTRRUPT_MASK(base_addr, intr_mask);
        FI2cFlushRxFifo(base_addr);
    }
}

/**
 * @name: FI2cMasterIntrHandler
 * @msg: 主机模式下的I2C中断响应函数
 * @return {*}
 * @param {s32} vector
 * @param {void} *param, 中断输入参数
 */
void FI2cMasterIntrHandler(s32 vector, void *param)
{
    FASSERT(param);
    FI2c *instance_p = (FI2c *)param;
    uintptr base_addr = instance_p->config.base_addr;
    u32 last_err = 0;
    u32 stat = FI2cClearIntrBits(base_addr, &last_err);
    u32 raw_stat = FI2C_READ_RAW_INTR_STAT(base_addr);
    u32 enabled = FI2C_READ_REG32(base_addr, FI2C_ENABLE_OFFSET);
    u32 val = 0;
    FASSERT(FI2C_MASTER == instance_p->config.work_mode);
    if (!(enabled & FI2C_IC_ENABLE) || !(raw_stat & ~FI2C_INTR_ACTIVITY))
    {
        return;
    }

    if (stat & FI2C_INTR_TX_ABRT) /* trans abort error */
    {
        FI2C_ERROR("last error: 0x%x", last_err);
        FI2C_ERROR("abort source: 0x%x", FI2C_READ_REG32(base_addr, FI2C_TX_ABRT_SOURCE_OFFSET));
        instance_p->status = STATUS_IDLE;
        FI2C_SET_INTRRUPT_MASK(base_addr, 0); /* disable all intr */
        FI2C_READ_REG32(base_addr, FI2C_CLR_TX_ABRT_OFFSET);
        FI2C_WRITE_REG32(base_addr, FI2C_ENABLE_OFFSET, 1);
        FI2cMasterCallEvtHandler(instance_p, FI2C_EVT_MASTER_TRANS_ABORTED, &val);
        return;
    }

    if (stat & FI2C_INTR_RX_FULL) /* rx complete */
    {
        FI2cMasterIntrRxFullHandler(instance_p);
        FI2cMasterCallEvtHandler(instance_p, FI2C_EVT_MASTER_READ_DONE, &val);
        return;
    }

    if (stat & FI2C_INTR_TX_EMPTY) /* tx complete */
    {
        FI2cMasterIntrTxEmptyHandler(instance_p);
        FI2cMasterCallEvtHandler(instance_p, FI2C_EVT_MASTER_WRITE_DONE, &val);
        return;
    }
    return;
}
/**
 * @name: FI2cMasterRegisterIntrHandler
 * @msg: 注册I2C主机中断事件函数
 * @return {*}
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} evt 中断事件，参考 FI2C_MASTER_INTR_EVT_NUM
 * @param {FI2cEvtHandler} handler 中断事件回调函数
 */
void FI2cMasterRegisterIntrHandler(FI2c *instance_p, u32 evt, FI2cEvtHandler handler)
{
    FASSERT(instance_p && evt < FI2C_MASTER_INTR_EVT_NUM);
    instance_p->master_evt_handlers[evt] = handler;
}

/**
 * @name: FI2cMasterGetIntr
 * @msg: 获取I2C主机的中断
 * @return {u32 } 返回中断寄存器值
 * @param {FI2c} *instance_p I2C驱动实例数据
 */
u32 FI2cGetIntr(FI2c *instance_p)
{
    FASSERT(instance_p);
    FI2cConfig *config_p = &instance_p->config;
    uintptr base_addr = config_p->base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FI2C_ERROR("i2c driver is not ready.");
        return FI2C_ERR_NOT_READY;
    }

    return FI2C_GET_INTRRUPT_MASK(base_addr);
}
/**
 * @name: FI2cMasterSetupIntr
 * @msg: 设置I2C主机的中断
 * @return {FError *} 返回错误码
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} mask 需要操作的中断寄存器位
 */
FError FI2cMasterSetupIntr(FI2c *instance_p, u32 mask)
{
    FASSERT(instance_p);
    FI2cConfig *config_p = &instance_p->config;
    uintptr base_addr = config_p->base_addr;
    u32 evt;

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

    /* disable all i2c irq */
    FI2C_CLEAR_INTR_STATUS(base_addr);

    for (evt = FI2C_EVT_MASTER_TRANS_ABORTED; evt < FI2C_MASTER_INTR_EVT_NUM; evt++)
    {
        if (instance_p->master_evt_handlers[evt] == NULL)
        {
            FI2cMasterRegisterIntrHandler(instance_p, evt, FI2cStubHandler);
            FI2C_INFO("evt :%d.is default.\r\n", evt);
        }
    }
    FI2C_SET_INTRRUPT_MASK(base_addr, mask);

    return FI2C_SUCCESS;
}

/**
 * @name: FI2cSlaveIntrHandler
 * @msg: I2C从机的中断响应函数
 * @return {*}
 * @param {s32} vector
 * @param {void} *param, 输入参数
 */
void FI2cSlaveIntrHandler(s32 vector, void *param)
{
    FASSERT(param);
    FI2c *instance_p = (FI2c *)param;
    uintptr base_addr = instance_p->config.base_addr;
    u32 last_err = 0;

    u32 stat = FI2C_READ_INTR_STAT(base_addr);
    u32 raw_stat = FI2C_READ_RAW_INTR_STAT(base_addr);
    u32 enabled = FI2C_READ_REG32(base_addr, FI2C_ENABLE_OFFSET);
    boolean slave_active = (FI2C_GET_STATUS(base_addr) & FI2C_STATUS_SLV_ACTIVITY) ? TRUE : FALSE;
    u8 val = 0;
    u32 reg_val;

    FASSERT(FI2C_SLAVE == instance_p->config.work_mode);

    if (!(enabled & FI2C_IC_ENABLE) || !(raw_stat & ~FI2C_INTR_ACTIVITY))
    {
        return;
    }
    stat = FI2cClearIntrBits(base_addr, &last_err);

    if (stat & FI2C_INTR_RX_FULL)
    {
        if (instance_p->status != STATUS_WRITE_IN_PROGRESS)
        {
            /* code */
            instance_p->status = STATUS_WRITE_IN_PROGRESS;
            FI2cSlaveCallEvtHandler(instance_p, FI2C_EVT_SLAVE_WRITE_REQUESTED, &val);
        }
        val = FI2C_READ_DATA(base_addr);
        FI2cSlaveCallEvtHandler(instance_p, FI2C_EVT_SLAVE_WRITE_RECEIVED, &val);
    }
    if (stat & FI2C_INTR_RD_REQ)
    {
        if (slave_active)
        {
            FI2C_READ_REG32(base_addr, FI2C_CLR_RD_REQ_OFFSET);
            instance_p->status = STATUS_WRITE_IN_PROGRESS;
            FI2cSlaveCallEvtHandler(instance_p, FI2C_EVT_SLAVE_READ_REQUESTED, &val);
            reg_val = val;
            FI2C_WRITE_DATA(base_addr, reg_val);
        }
    }

    if (stat & FI2C_INTR_RX_DONE)
    {
        FI2cSlaveCallEvtHandler(instance_p, FI2C_EVT_SLAVE_READ_PROCESSED, &val);
        FI2C_READ_REG32(base_addr, FI2C_CLR_RX_DONE_OFFSET);
        return;
    }

    if (stat & FI2C_INTR_STOP_DET)
    {
        instance_p->status = STATUS_IDLE;
        FI2cSlaveCallEvtHandler(instance_p, FI2C_EVT_SLAVE_STOP, &val);
    }

    if (stat & FI2C_INTR_TX_ABRT) /* trans abort error */
    {
        FI2C_ERROR("last error: 0x%x", last_err);
        FI2C_ERROR("abort source: 0x%x", FI2C_READ_REG32(base_addr, FI2C_TX_ABRT_SOURCE_OFFSET));
    }

    return;
}

/**
 * @name: FI2cSlaveRegisterIntrHandler
 * @msg: 注册I2C从机中断事件函数
 * @return {*}
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {u32} evt 中断事件，参考 FI2C_SLAVE_INTR_EVT_NUM
 * @param {FI2cEvtHandler} handler 中断事件回调函数
 */
void FI2cSlaveRegisterIntrHandler(FI2c *instance_p, u32 evt, FI2cEvtHandler handler)
{
    FASSERT(instance_p && evt < FI2C_SLAVE_INTR_EVT_NUM);
    instance_p->slave_evt_handlers[evt] = handler;
}

/**
 * @name: FI2cSlaveSetupIntr
 * @msg: 设置I2C从机的中断
 * @return {FError *} 返回错误码
 * @param {FI2c} *instance_p
 */
FError FI2cSlaveSetupIntr(FI2c *instance_p)
{
    FASSERT(instance_p);
    FI2cConfig *config_p = &instance_p->config;
    uintptr base_addr = config_p->base_addr;
    u32 evt;
    u32 mask;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FI2C_ERROR("i2c driver is not ready.");
        return FI2C_ERR_NOT_READY;
    }

    if (FI2C_SLAVE != instance_p->config.work_mode)
    {
        FI2C_ERROR("i2c work mode shall be slave.");
        return FI2C_ERR_INVAL_STATE;
    }

    /* disable all i2c irq */
    FI2C_CLEAR_INTR_STATUS(base_addr);

    for (evt = FI2C_EVT_SLAVE_READ_REQUESTED; evt < FI2C_SLAVE_INTR_EVT_NUM; evt++)
    {
        if (instance_p->slave_evt_handlers[evt] == NULL)
        {
            FI2cSlaveRegisterIntrHandler(instance_p, evt, FI2cStubHandler);
            FI2C_INFO("evt :%d.is default.\r\n", evt);
        }
    }
    FI2C_SET_RX_TL(instance_p->config.base_addr, 0);/* 0 表示接收缓冲区大于等于 1 时触发中断 */
    FI2C_SET_TX_TL(instance_p->config.base_addr, 0);/* 0 表示发送缓冲区大于等于 1 时触发中断 */
    mask = FI2C_GET_INTRRUPT_MASK(base_addr);
    mask |= (FI2C_INTR_SLAVE_DEF_MASK);
    FI2C_SET_INTRRUPT_MASK(base_addr, mask);

    return FI2C_SUCCESS;
}