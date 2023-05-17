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
 * FilePath: fddma_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:47
 * Description:  This files is for ddma register rw operations
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

/***************************** Include Files *********************************/
#include <string.h>

#include "fkernel.h"
#include "fparameters.h"
#include "fassert.h"
#include "fdebug.h"

#include "fddma_hw.h"
#include "fddma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FDDMA_DEBUG_TAG "DDMA-HW"
#define FDDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_WARN(format, ...)   FT_DEBUG_PRINT_W(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/****************************************************************************/
/**
 * @name: FDdmaDisable
 * @msg: 去使能DDMA控制器
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 */
void FDdmaDisable(uintptr base_addr)
{
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET);
    reg_val &= ~FDDMA_CTL_ENABLE;
    FDdmaWriteReg(base_addr, FDDMA_CTL_OFFSET, reg_val);
    FDDMA_DEBUG("ddma @%p disabled : 0x%x", base_addr, FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET));
    return;
}

/**
 * @name: FDdmaEnable
 * @msg: 使能DDMA控制器
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 */
void FDdmaEnable(uintptr base_addr)
{
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET);
    reg_val |= FDDMA_CTL_ENABLE;
    FDdmaWriteReg(base_addr, FDDMA_CTL_OFFSET, reg_val);
    FDDMA_DEBUG("ddma @%p enabled : 0x%x", base_addr, FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET));
    return;
}

/**
 * @name: FDdmaSoftwareReset
 * @msg: 复位DDMA控制器
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 */
void FDdmaSoftwareReset(uintptr base_addr)
{
    int delay = 10000;
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET);
    reg_val |= FDDMA_CTL_SRST;
    FDdmaWriteReg(base_addr, FDDMA_CTL_OFFSET, reg_val);
    FDDMA_DEBUG("ddma @%p soft reset start : 0x%x", base_addr, FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET));

    while (--delay > 0) /* wait a while to do reset */
        ;

    reg_val &= ~FDDMA_CTL_SRST;
    FDdmaWriteReg(base_addr, FDDMA_CTL_OFFSET, reg_val); /* exit from software reset */
    FDDMA_DEBUG("ddma @%p soft reset end : 0x%x", base_addr, FDdmaReadReg(base_addr, FDDMA_CTL_OFFSET));
    return;
}

/**
 * @name: FDdmaDisableGlobalIrq
 * @msg: 关闭DDMA全局中断
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 */
void FDdmaDisableGlobalIrq(uintptr base_addr)
{
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_MASK_INTR_OFFSET);
    reg_val |= FDDMA_MASK_EN_GLOBAL_INTR; /* write 1 and disable interrupt */
    FDdmaWriteReg(base_addr, FDDMA_MASK_INTR_OFFSET, reg_val);
    return;
}

/**
 * @name: FDdmaEnableGlobalIrq
 * @msg: 打开DDMA全局中断
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 */
void FDdmaEnableGlobalIrq(uintptr base_addr)
{
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_MASK_INTR_OFFSET);
    reg_val &= ~FDDMA_MASK_EN_GLOBAL_INTR; /* write 0 and enable interrupt */
    FDdmaWriteReg(base_addr, FDDMA_MASK_INTR_OFFSET, reg_val);
    return;
}

/**
 * @name: FDdmaDisableChanIrq
 * @msg: 关闭DDMA通道中断
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
void FDdmaDisableChanIrq(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_MASK_INTR_OFFSET);
    reg_val |= FDDMA_MASK_EN_CHAN_INTR(chan);
    FDdmaWriteReg(base_addr, FDDMA_MASK_INTR_OFFSET, reg_val);
    return;
}

/**
 * @name: FDdmaEnableChanIrq
 * @msg: 打开DDMA通道中断
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
void FDdmaEnableChanIrq(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val  = FDdmaReadReg(base_addr, FDDMA_MASK_INTR_OFFSET);
    reg_val &= ~FDDMA_MASK_EN_CHAN_INTR(chan); /* write 0 and enable  */
    FDdmaWriteReg(base_addr, FDDMA_MASK_INTR_OFFSET, reg_val);
    return;
}

/**
 * @name: FDdmaDisableChan
 * @msg: 去使能DDMA通道
 * @return {FError} FDDMA_SUCCESS 表示去使能成功
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
FError FDdmaDisableChan(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    int delay = 1000;
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan));
    reg_val &= ~FDDMA_CHAN_CTL_EN;
    FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan), reg_val);

    /* 先写该位 1’b0，随后读取到该位是 1’b0 的时候，才能复位该通道 */
    do
    {
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan));
        if (delay-- <= 0)
        {
            break;
        }
    }
    while (reg_val & FDDMA_CHAN_CTL_EN);

    FDDMA_DEBUG("ddma@ %p channel %d is disabled : 0x%x", base_addr, chan, FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan)));
    return (delay > 0) ? FDDMA_SUCCESS : FDDMA_ERR_WAIT_TIMEOUT;
}

/**
 * @name: FDdmaEnableChan
 * @msg: 使能DDMA通道
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
void FDdmaEnableChan(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan));
    reg_val |= FDDMA_CHAN_CTL_EN;
    FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan), reg_val);
    FDDMA_DEBUG("ddma @%p chan %d enabled : 0x%x", base_addr, chan, FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan)));
    return;
}

/**
 * @name: FDdmaClearChanIrq
 * @msg: 清除DDMA通道中断状态
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
void FDdmaClearChanIrq(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    /* write 1 to clear irq status of channel */
    FDdmaWriteReg(base_addr, FDDMA_STA_OFFSET, FDDMA_STA_CHAN_REQ_DONE(chan));
}

/**
 * @name: FDdmaResetChan
 * @msg: 重置DDMA通道
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
void FDdmaResetChan(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    int delay = 1000;
    u32 reg_val;

    if (FDdmaIsChanRunning(base_addr, chan)) /* disable channel if running */
    {
        (void)FDdmaDisableChan(base_addr, chan);
    }

    reg_val  = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan));
    reg_val |= FDDMA_CHAN_CTL_SRST;
    FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan), reg_val);

    while (--delay > 0) /* wait a while to do reset */
        ;

    reg_val &= ~FDDMA_CHAN_CTL_SRST;
    FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan), reg_val);
    FDDMA_DEBUG("Channel reset done, ctrl: 0x%x", FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan)));
    return;
}

/**
 * @name: FDdmaIsChanRunning
 * @msg: 检查通道是否在工作中
 * @return {boolean} TRUE: 在工作中
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 */
boolean FDdmaIsChanRunning(uintptr base_addr, u32 chan)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan));
    return (FDDMA_CHAN_CTL_EN & reg_val) ? TRUE : FALSE;
}

/**
 * @name: FDdmaSetChanSelection
 * @msg: 将DDMA通道与外设绑定
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 * @param {u32} slave_id, 外设对应的slave id
 */
void FDdmaSetChanSelection(uintptr base_addr, u32 chan, u32 slave_id)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    FASSERT_MSG((FDDMA_MAX_SLAVE_ID >= slave_id), "Invalid slave id %d", slave_id);
    u32 reg_val;

    if (FDDMA_CHAN_4 > chan)
    {
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET);
        reg_val &= ~FDDMA_CHAN_0_3_SEL_MASK(chan);
        reg_val |= FDDMA_CHAN_0_3_SEL(chan, slave_id);
        reg_val |= FDDMA_CHAN_0_3_SEL_EN(chan);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET, reg_val);
        FDDMA_DEBUG("ddma%p sets the slaveid of chan-%d to %d, 0x%x", base_addr, chan, slave_id, FDdmaReadReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET));
    }
    else
    {
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_4_7_CFG_OFFSET);
        reg_val &= ~FDDMA_CHAN_4_7_SEL_MASK(chan);
        reg_val |= FDDMA_CHAN_4_7_SEL(chan, slave_id);
        reg_val |= FDDMA_CHAN_4_7_SEL_EN(chan);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_4_7_CFG_OFFSET, reg_val);
        FDDMA_DEBUG("ddma%p sets the slaveid of chan-%d to %d, 0x%x", base_addr, chan, slave_id, FDdmaReadReg(base_addr, FDDMA_CHAN_4_7_CFG_OFFSET));
    }

    return;
}

/**
 * @name: FDdmaSetChanBind
 * @msg: 修改通道的绑定状态
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 * @param {boolean} bind, TRUE: 绑定，FALSE: 解除绑定
 */
void FDdmaSetChanBind(uintptr base_addr, u32 chan, boolean bind)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_BIND_OFFSET);

    if (bind)
    {
        reg_val |= BIT(chan);
    }
    else
    {
        reg_val &= ~BIT(chan);
    }

    FDDMA_DEBUG("ddma@%p %s chan-%d, 0x%x", base_addr, bind ? "bind" : "unbind", chan, FDdmaReadReg(base_addr, FDDMA_CHAN_BIND_OFFSET));
    FDdmaWriteReg(base_addr, FDDMA_CHAN_BIND_OFFSET, reg_val);
    return;
}

/**
 * @name: FDdmaSetChanDirection
 * @msg: 设置通道的方向
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 * @param {boolean} is_rx, TRUE: 接收, FALSE: 发送
 */
void FDdmaSetChanDirection(uintptr base_addr, u32 chan, boolean is_rx)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan));
    if (is_rx)
    {
        reg_val |= FDDMA_CHAN_CTL_RX_MODE;    /* device to memory */
    }
    else
    {
        reg_val &= ~FDDMA_CHAN_CTL_RX_MODE;    /* memory to device */
    }
    FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan), reg_val);
    return;
}

/**
 * @name: FDdmaSetChanTimeout
 * @msg: 设置通道超时
 * @return {*}
 * @param {uintptr} base_addr, DDMA控制器基地址
 * @param {u32} chan, DDMA通道号
 * @param {u32} timeout, 超时设置，0表示不启用超时
 */
void FDdmaSetChanTimeout(uintptr base_addr, u32 chan, u32 timeout)
{
    FASSERT_MSG((FDDMA_NUM_OF_CHAN > chan), "Channel %d is not supported", chan);
    u32 reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_TIMEOUT_CNT_OFFSET(chan));

    if (0 < timeout)
    {
        reg_val &= ~FDDMA_CHAN_TIMEOUT_CNT_MASK;
        reg_val |= FDDMA_CHAN_TIMEOUT_CNT_SET(timeout);
        reg_val |= FDDMA_CHAN_TIMEOUT_EN;
    }
    else
    {
        reg_val &= ~FDDMA_CHAN_TIMEOUT_EN;
    }

    FDdmaWriteReg(base_addr, FDDMA_CHAN_TIMEOUT_CNT_OFFSET(chan), reg_val);
    return;
}