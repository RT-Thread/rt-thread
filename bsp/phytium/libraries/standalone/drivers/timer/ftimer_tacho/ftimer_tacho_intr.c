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
 * FilePath: ftimer_tacho_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:09:36
 * Description:  This file is for timer_tacho interrupt operation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/02/18    first commit
 */

/***************************** Include Files *********************************/
#include "fassert.h"
#include "ftimer_tacho.h"
#include "ftimer_tacho_hw.h"

/************************** Constant Definitions *****************************/

static const u32 g_intrBits[FMAX_TIMER_TACHO_EVENT] =
{
    FTACHO_OVER_INTR_EN, FTACHO_UNDER_INTR_EN,
    FTIMER_ROLLOVER_INTR_EN, FTIMER_ONCECMP_INTR_EN, FTIMER_CYCCMP_INTR_EN,
    FTACHO_CAPTURE_INTR_EN
};

static const u32 g_intrStats[FMAX_TIMER_TACHO_EVENT] =
{
    FTACHO_OVER_INTR_STATUS, FTACHO_UNDER_INTR_STATUS,
    FTIMER_ROLLOVER_INTR_STATUS, FTIMER_ONCECMP_INTR_STATUS, FTIMER_CYCCMP_INTR_STATUS,
    FTACHO_CAPTURE_INTR_STATUS
};

/************************** Function Prototypes ******************************/
/**
 * @name: FTimerGetInterruptMask
 * @msg: 获取中断设置
 * @return {u32} 返回中断寄存器的值
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
u32 FTimerGetInterruptMask(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);
    return FTIMER_INTR_M_READ(instance_p);
}

/**
 * @name: FTimerSetInterruptMask
 * @msg: 设置中断
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {enum} intrType 中断枚举类型
 * @param {boolean} enable 使能或者失能
 */
void FTimerSetInterruptMask(FTimerTachoCtrl *instance_p,
                            FTimerTachoEventType intrType,
                            boolean enable)
{
    FASSERT(instance_p && intrType < FMAX_TIMER_TACHO_EVENT);
    u32 mask = FTIMER_INTR_M_READ(instance_p);

    if (enable)
    {
        mask |= g_intrBits[intrType];
    }
    else
    {
        mask &= ~g_intrBits[intrType];
    }

    FTIMER_INTR_M_WRITE(instance_p, mask);
}

/**
 * @name: FTimerTachoIntrHandler
 * @msg: 中断服务函数，跳转到自己注册的回调函数(如果注册，没有注册则跳转到FTimerDefaultEvtCallback)
 * @return {void}
 * @param {s32} vector，中断向量号，此处不关心此参数
 * @param {void} *param, 中断输入参数, 指向FTimerTachoCtrl的驱动控制实例
 */
void FTimerTachoIntrHandler(s32 vector, void *param)
{
    FASSERT(param);

    FTimerTachoCtrl *instance_p = (FTimerTachoCtrl *)param;
    const u32 intr_status = FTIMER_INTR_S_READ(instance_p);
    u32 loop;
    FTimerEventHandler evtHandler;

    FTIMER_INFO("Intr entered cause: 0x%x.\r\n", intr_status);

    /* check intr status bit by bit */
    for (loop = 0; loop < FMAX_TIMER_TACHO_EVENT; loop++)
    {
        evtHandler = instance_p->evt_handlers[loop];

        if ((g_intrStats[loop] & intr_status) && (NULL != evtHandler))
        {
            evtHandler((void *)instance_p);
        }
    }

    FTIMER_INTR_S_CLEAR(instance_p, intr_status);
}

/**
 * @name: FTimerDefaultEvtCallback
 * @msg: 默认中断回调函数
 * @return {void}
 * @param {void} *param,函数输入参数指向FTimerTachoCtrl的驱动控制实例
 */
static void FTimerDefaultEvtCallback(void *param)
{
    FASSERT(param);
    FTimerTachoCtrl *instance_p = (FTimerTachoCtrl *)param;
    const u32 intr_status = FTIMER_INTR_S_READ(instance_p);

    FTIMER_INFO("timer id: 0x%x, intr cause: 0x%x.\r\n", intr_status);
}

/**
 * @name: FTimerRegisterEvtCallback
 * @msg: 回调函数的注册函数
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {enum} intrType 中断枚举类型
 * @param {FTimerEventHandler}
 */
void FTimerRegisterEvtCallback(FTimerTachoCtrl *instance_p,
                               FTimerTachoEventType evt,
                               FTimerEventHandler callback)
{
    FASSERT(instance_p && evt < FMAX_TIMER_TACHO_EVENT);
    instance_p->evt_handlers[evt] = callback;
}

/**
 * @name: FTimerTachoSetIntr
 * @msg: 根据工作模式和状态设置相应的中断
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
void FTimerTachoSetIntr(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);

    if (FTIMER_WORK_MODE_TIMER == instance_p->config.work_mode)
    {
        if (FTIMER_ONCE_CMP == instance_p->config.cmp_type)
        {
            FTimerSetInterruptMask(instance_p, FTIMER_EVENT_ONCE_CMP, TRUE);
            if (instance_p->evt_handlers[FTIMER_EVENT_ONCE_CMP] == NULL)
            {
                FTimerRegisterEvtCallback(instance_p, FTIMER_EVENT_ONCE_CMP, FTimerDefaultEvtCallback);
            }
        }
        else
        {
            FTimerSetInterruptMask(instance_p, FTIMER_EVENT_CYC_CMP, TRUE);
            if (instance_p->evt_handlers[FTIMER_EVENT_CYC_CMP] == NULL)
            {
                FTimerRegisterEvtCallback(instance_p, FTIMER_EVENT_CYC_CMP, FTimerDefaultEvtCallback);
            }
        }
        /*暂时屏蔽不开启翻转中断，因为cmp设置触发就是最大值，等同于翻转中断*/
        /*FTimerSetInterruptMask(instance_p, FTIMER_EVENT_ROLL_OVER, TRUE);*/
        if (instance_p->evt_handlers[FTIMER_EVENT_ROLL_OVER] == NULL)
        {
            FTimerRegisterEvtCallback(instance_p, FTIMER_EVENT_ROLL_OVER, FTimerDefaultEvtCallback);
        }
    }
    else if (FTIMER_WORK_MODE_TACHO == instance_p->config.work_mode)
    {
        FTimerSetInterruptMask(instance_p, FTACHO_EVENT_OVER, TRUE);
        FTimerSetInterruptMask(instance_p, FTACHO_EVENT_UNDER, TRUE);
        if (instance_p->evt_handlers[FTACHO_EVENT_OVER] == NULL)
        {
            FTimerRegisterEvtCallback(instance_p, FTACHO_EVENT_OVER, FTimerDefaultEvtCallback);
        }
        if (instance_p->evt_handlers[FTACHO_EVENT_UNDER] == NULL)
        {
            FTimerRegisterEvtCallback(instance_p, FTACHO_EVENT_UNDER, FTimerDefaultEvtCallback);
        }
    }
    else if (FTIMER_WORK_MODE_CAPTURE == instance_p->config.work_mode)
    {
        FTimerSetInterruptMask(instance_p, FTACHO_EVENT_CAPTURE, TRUE);
        if (instance_p->evt_handlers[FTACHO_EVENT_CAPTURE] == NULL)
        {
            FTimerRegisterEvtCallback(instance_p, FTACHO_EVENT_CAPTURE, FTimerDefaultEvtCallback);
        }
    }
    else
    {
        FASSERT(0);
    }
    FTIMER_INFO("Mask:0x%x.\r\n", FTIMER_INTR_M_READ(instance_p));
    return;
}