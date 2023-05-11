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
 * FilePath: fgmac_intr.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  Functions in this file implement general purpose interrupt processing related
 * functionality.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/07/13    first release
 */

/***************************** Include Files *********************************/

#include "fgmac.h"
#include "fgmac_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGMAC_CALL_EVT_HANDLER(instance_p, evt)    \
    {\
        if (NULL != (instance_p)->evt_handler[(evt)]) \
        {                                        \
            (instance_p)->evt_handler[evt]((void *)(instance_p));  \
        }\
    }

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

/**
 * @name: FGmacInterruptHandler
 * @msg: FGMAC中断处理函数
 * @return {*}
 * @param {s32} vector, 中断向量号，此处没有用到
          {void} *param, 中断输入参数，此处传入的是FGMAC的驱动控制数据
 * @note 此函数运行在中断上下文
 */
void FGmacInterruptHandler(s32 vector, void *param)
{
    FASSERT(param);
    FGmac *instance_p = (FGmac *)param;
    uintptr base_addr = instance_p->config.base_addr;
    u32 status = 0;

    /* dma interrupt */
    status = FGMAC_READ_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET);

    if (FGMAC_DMA_STATUS_GLI & status)
    {
        FGMAC_CALL_EVT_HANDLER(instance_p, FGMAC_PHY_STATUS_EVT);
    }

    if (FGMAC_DMA_STATUS_RI & status)
    {
        FGMAC_CALL_EVT_HANDLER(instance_p, FGMAC_RX_COMPLETE_EVT);
        FGMAC_SET_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, FGMAC_DMA_STATUS_RI); /* write to clear */
    }

    if (FGMAC_DMA_STATUS_TI & status)
    {
        FGMAC_CALL_EVT_HANDLER(instance_p, FGMAC_TX_COMPLETE_EVT);
        FGMAC_SET_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, FGMAC_DMA_STATUS_TI); /* write to clear */
    }

    if (FGMAC_DMA_STATUS_AIS & status)
    {
        FGMAC_CALL_EVT_HANDLER(instance_p, FGMAC_DMA_ERR_EVT);
        FGMAC_SET_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, FGMAC_DMA_STATUS_CLR_ABLE);
    }

    FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, status); /* write to clear */

    /* RGMII/SGMII Interrupt */
    status = FGMAC_READ_REG32(base_addr, FGMAC_INTR_STATUS_OFFSET);
    if (status & FGMAC_ISR_STATUS_RSIS)
    {
        /* status changed, read SGMII register to clear */
        FGMAC_READ_REG32(base_addr, FGMAC_MAC_PHY_STATUS);
    }

    return;
}

/**
 * @name: FGmacRegisterEvtHandler
 * @msg: 注册FGMAC中断事件响应函数
 * @return {*}
 * @param {FGmac} *instance_p 驱动控制数据
 * @param {u32} evt 中断事件类型
 * @param {FGmacEvtHandler} handler 中断事件响应函数
 * @note 注册的函数handler会在中断上下文执行
 */
void FGmacRegisterEvtHandler(FGmac *instance_p, u32 evt, FGmacEvtHandler handler)
{
    FASSERT((NULL != instance_p) && (FGMAC_INTR_EVT_NUM > evt));
    instance_p->evt_handler[evt] = handler;
}

/**
 * @name: FGmacSetInterruptMask
 * @msg: 屏蔽FGMAC中断
 * @return {*}
 * @param {FGmac} *instance_p 驱动控制数据
 * @param {u32} intr_type 中断类型 GMAC中断/DMA中断
 * @param {u32} mask 中断屏蔽位
 * @note 在FGMAC驱动初始化成功后调用此函数
 */
void FGmacSetInterruptMask(FGmac *instance_p, u32 intr_type, u32 mask)
{
    FASSERT(instance_p);
    FASSERT(FGMAC_MAX_INTR_TYPE > intr_type);
    u32 cur_mask = 0;
    uintptr base_addr = instance_p->config.base_addr;

    if (FGMAC_CTRL_INTR == intr_type)
    {
        cur_mask = FGMAC_READ_REG32(base_addr, FGMAC_INTR_MASK_OFFSET);
        cur_mask |= mask;
        FGMAC_WRITE_REG32(base_addr, FGMAC_INTR_MASK_OFFSET, cur_mask);
    }
    else
    {
        cur_mask = FGMAC_READ_REG32(base_addr, FGMAC_DMA_INTR_OFFSET);
        cur_mask &= (~mask);
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_INTR_OFFSET, cur_mask);
    }

    return;
}

/**
 * @name: FGmacSetInterruptUmask
 * @msg: 使能FGMAC中断
 * @return {*}
 * @param {FGmac} *instance_p 驱动控制数据
 * @param {u32} intr_type 中断类型 GMAC中断/DMA中断
 * @param {u32} mask 中断使能标志位
 * @note 在FGMAC驱动初始化成功后调用此函数
 */
void FGmacSetInterruptUmask(FGmac *instance_p, u32 intr_type, u32 mask)
{
    FASSERT(instance_p);
    FASSERT(FGMAC_MAX_INTR_TYPE > intr_type);
    u32 cur_mask = 0;
    uintptr base_addr = instance_p->config.base_addr;

    if (FGMAC_CTRL_INTR == intr_type)
    {
        cur_mask = FGMAC_READ_REG32(base_addr, FGMAC_INTR_MASK_OFFSET);
        cur_mask &= (~mask);
        FGMAC_WRITE_REG32(base_addr, FGMAC_INTR_MASK_OFFSET, cur_mask);
    }
    else
    {
        cur_mask = FGMAC_READ_REG32(base_addr, FGMAC_DMA_INTR_OFFSET);
        cur_mask |= mask;
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_INTR_OFFSET, cur_mask);
    }

    return;
}
