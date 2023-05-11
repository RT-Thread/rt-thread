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
 * FilePath: fspim_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:08:10
 * Description:  This file is for providing spim interrupt func.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/3   init commit
 * 1.1   zhugengyu  2022/4/15   support test mode
 */

/***************************** Include Files *********************************/
#include <string.h>
#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fassert.h"
#include "fdebug.h"
#include "fspim_hw.h"
#include "fspim.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
/* be very careful to use print log in intrrupt handler */
#define FSPIM_DEBUG_TAG "SPIM-INTR"
#define FSPIM_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_WARN(format, ...)    FT_DEBUG_PRINT_W(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_INFO(format, ...)    FT_DEBUG_PRINT_I(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)

#define FSPIM_CALL_INTR_EVT_HANDLDER(instance_p, evt) \
    if (instance_p->evt_handler[evt])                 \
        instance_p->evt_handler[evt](instance_p, instance_p->evt_param[evt])

/************************** Function Prototypes ******************************/
extern void FSpimFifoTx(FSpim *instance_p);
extern void FSpimFifoRx(FSpim *instance_p);
extern FError FSpimReset(FSpim *instance_p);

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FSpimInterruptHandler
 * @msg: SPIM中断处理函数
 * @return {无}
 * @param {s32} vector，中断向量号，此处不关心此参数
 * @param {void} *param, 中断输入参数, 指向FSPIM的驱动控制实例
 */
void FSpimInterruptHandler(s32 vector, void *param)
{
    FASSERT(param);
    FSpim *instance_p = (FSpim *)param;
    uintptr base_addr = instance_p->config.base_addr;
    u32 intr_status = FSPIM_RIS_R_ALL_BITS & FSPIM_READ_REG32(base_addr, FSPIM_RIS_R_OFFSET);

    if (0 == intr_status)
    {
        return;
    }

    if ((FSPIM_RIS_R_TXOIR | FSPIM_RIS_R_RXOIR | FSPIM_RIS_R_RXUIR) & intr_status) /* 发送FIFO溢出 */
    {
        FSPIM_WARN("Fifo overflow or underflow");
        if (FSPIM_RIS_R_TXOIR & intr_status)
        {
            FSPIM_CALL_INTR_EVT_HANDLDER(instance_p, FSPIM_INTR_EVT_TX_OVERFLOW);
        }

        if (FSPIM_RIS_R_RXUIR & intr_status)
        {
            FSPIM_CALL_INTR_EVT_HANDLDER(instance_p, FSPIM_INTR_EVT_RX_UNDERFLOW);
        }

        if (FSPIM_RIS_R_RXOIR & intr_status)
        {
            FSPIM_CALL_INTR_EVT_HANDLDER(instance_p, FSPIM_INTR_EVT_RX_OVERFLOW);
        }

        FSpimReset(instance_p);
        return;
    }

    FSpimFifoRx(instance_p); /* 检查 RX Fifo是否为空，如果不为空则接收数据 */

    if (instance_p->rx_buff_end == instance_p->rx_buff) /* RX 缓冲区已满，停止填入发送数据 */
    {
        FSpimMaskIrq(base_addr, FSPIM_IMR_TXEIS);
        FSPIM_CALL_INTR_EVT_HANDLDER(instance_p, FSPIM_INTR_EVT_RX_DONE);
        return;
    }

    if (FSPIM_RIS_R_TXEIR & intr_status) /* TX Fifo为空，填入待发送数据 */
    {
        FSpimMaskIrq(base_addr, FSPIM_IMR_TXEIS);
        FSpimFifoTx(instance_p);
        FSpimUmaskIrq(base_addr, FSPIM_IMR_TXEIS);
    }

    return;
}

/**
 * @name: FSpimRegisterIntrruptHandler
 * @msg: 注册FSPIM中断事件处理函数
 * @return {*}
 * @param {FI2c} *instance_p
 * @param {u32} evt
 * @param {FI2cEvtHandler} handler
 */
void FSpimRegisterIntrruptHandler(FSpim *instance_p, FSpimIntrEvtType evt, FSpimEvtHandler handler, void *param)
{
    FASSERT(instance_p && evt < FSPIM_INTR_EVT_NUM);
    instance_p->evt_handler[evt] = handler;
    instance_p->evt_param[evt] = param;
}