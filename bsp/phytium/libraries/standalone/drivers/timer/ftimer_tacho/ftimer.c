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
 * FilePath: ftimer.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:09:49
 * Description:  This file is for user timer API implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/02/18    first commit
 */

/***************************** Include Files *********************************/
#include <string.h>
#include "fassert.h"
#include "ftimer_tacho_hw.h"
#include "ftimer_tacho.h"


/************************** Function Prototypes ******************************/
/**
 * @name: FTimerSoftwareReset
 * @msg: 将控制器复位
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
FError FTimerSoftwareReset(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);

    if (instance_p->isready != FT_COMPONENT_IS_READY)
    {
        FTIMER_ERROR("Device is not ready!!!");
        return FTIMER_TACHO_ERR_NOT_READY;
    }

    u32 reg_val = FTIMER_CTRL_READ(instance_p);
    u32 Timeout = 0;
    reg_val |= FTIMER_REG_TACHO_RESET;
    FTIMER_CTRL_WRITE(instance_p, reg_val);

    do
    {
        reg_val = FTIMER_CTRL_READ(instance_p);
        Timeout++;
    }
    while ((reg_val & FTIMER_REG_TACHO_RESET) && (Timeout < FTIMER_TIMEOUT));

    if (Timeout >= FTIMER_TIMEOUT)
    {
        FTIMER_ERROR("Software Reset Failed!!!");
        return FTIMER_TACHO_ERR_FAILED;
    }

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: FTimerStart
 * @msg: 启动timer_tacho外设,根据不同的功能，开启使能位
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
FError FTimerStart(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);
    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    u32 reg_val;
    reg_val = FTIMER_CTRL_READ(instance_p);
    if (FTIMER_WORK_MODE_TIMER == instance_p->config.work_mode)
    {
        reg_val |= FTIMER_REG_ENABLE;
    }
    else
    {
        /* for tacho mode and capture mode */
        reg_val |= FTIMER_REG_ENABLE | FTACHO_REG_CAP_IN_ENABLE;
    }

    FTIMER_CTRL_WRITE(instance_p, reg_val);

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: FTimerStop
 * @msg: 停止timer外设，根据不同的功能，关闭使能位，计数值停止并冻结
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
FError FTimerStop(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    u32 reg_val = FTIMER_CTRL_READ(instance_p);

    if (FTIMER_WORK_MODE_TIMER == instance_p->config.work_mode)
    {
        reg_val &= (~FTIMER_REG_ENABLE);
    }
    else
    {
        /* for tacho mode and capture mode */
        reg_val &= (~FTIMER_REG_ENABLE) & (~FTACHO_REG_CAP_IN_ENABLE);
    }

    FTIMER_CTRL_WRITE(instance_p, reg_val);

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: TimerSwithBits
 * @msg: 计数器32/64切换
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
static FError TimerSwithBits(FTimerTachoCtrl *instance_p)
{
    u32 reg_val;

    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    reg_val = FTIMER_CTRL_READ(instance_p);

    if (FTIMER_32_BITS == instance_p->config.timer_bits)
    {
        reg_val &= (~FTIMER_REG_CNT_SERIES_64BIT);
    }
    else if (FTIMER_64_BITS == instance_p->config.timer_bits)
    {
        reg_val |= FTIMER_REG_CNT_SERIES_64BIT;
    }
    else
    {
        FTIMER_ERROR("Invalid input");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    FTIMER_CTRL_WRITE(instance_p, reg_val);

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: TimerForceLoad
 * @msg: 强制更新位置位
 * @return {void} 无
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
static void TimerForceLoad(FTimerTachoCtrl *instance_p)
{
    u32 reg_val;

    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    reg_val = FTIMER_CTRL_READ(instance_p);
    reg_val |= FTIMER_REG_TACHO_FORCE_LOAD;
    FTIMER_CTRL_WRITE(instance_p, reg_val);

    return;
}

/**
 * @name: FTimerSetPeriod32
 * @msg: 设置32位计数模式下，计数器的compare的值，达到此值，如果开启中断，则开启中断
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u32}NewCmpL
 */
FError FTimerSetPeriod32(FTimerTachoCtrl *instance_p, u32 new_cmp_l)
{
    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    if (FTIMER_64_BITS == instance_p->config.timer_bits)
    {
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    /* update cmp val */
    FTIMER_CMPL_WRITE(instance_p, new_cmp_l);

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: FTimerSetPeriod64
 * @msg: 设置64位计数模式下，计数器的compare的值，达到此值，如果开启中断，则开启中断
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u64}ticks
 */
FError FTimerSetPeriod64(FTimerTachoCtrl *instance_p, u64 ticks)
{
    u32 low_cmp;
    u32 up_cmp;
    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    if (FTIMER_32_BITS == instance_p->config.timer_bits)
    {
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    low_cmp = (u32)(GENMASK_ULL(31, 0) & ticks);
    up_cmp = (u32)((GENMASK_ULL(63, 32) & ticks) >> 32);

    /* MUST write low 32 bit first !!! */
    FTIMER_CMPL_WRITE(instance_p, low_cmp);
    FTIMER_CMPU_WRITE(instance_p, up_cmp);

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: FTimerSetStartVal
 * @msg: 设置计数器初始值
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u32} cnt
 */
inline FError FTimerSetStartVal(FTimerTachoCtrl *instance_p, u32 cnt)
{
    u32 ret = FTIMER_TACHO_SUCCESS;
    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    ret = TimerSwithBits(instance_p);
    if (FTIMER_TACHO_SUCCESS != ret)
    {
        return ret;
    }

    FTIMER_STAR_WRITE(instance_p, cnt);
    /* set force_load=1，invalid previous cmp val,
       otherwise the previous cmp val still work */
    TimerForceLoad(instance_p);

    FTIMER_INFO("Set start val 0x%x", FTIMER_STAR_READ(instance_p));

    return ret;
}


/**
 * @name: FTimerGetCurCnt32
 * @msg: 32位模式下，获取计数器当前计数值
 * @return {u32}返回当前计数器的值
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
u32 FTimerGetCurCnt32(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    return FTIMER_CNTL_READ(instance_p);
}

/**
 * @name: FTimerGetCurCnt64
 * @msg: 64位模式下，获取计数器当前计数值
 * @return {u64}返回当前计数器的值
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
inline u64 FTimerGetCurCnt64(FTimerTachoCtrl *instance_p)
{
    u64 cnt = 0;
    FASSERT(instance_p);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    /* must read lower 32 bits first */
    cnt |= (u64)FTIMER_CNTL_READ(instance_p);
    cnt |= (u64)(((u64)FTIMER_CNTU_READ(instance_p)) << 32);
    return cnt;
}

/**
 * @name: FTimerInit
 * @msg: 完成TimerTacho驱动实例的初始化，使之在就绪状态
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {FTimerTachoConfig} *config_p 驱动配置数据结构
 */
FError FTimerInit(FTimerTachoCtrl *instance_p, const FTimerTachoConfig *config_p)
{
    FASSERT(instance_p && config_p);

    u32 reg_val = 0;
    u32 Ret = FTIMER_TACHO_SUCCESS;

    if ((FTIMER_ONCE_CMP == config_p->cmp_type) &&
        (FTIMER_FREE_RUN != config_p->timer_mode))
    {
        FTIMER_ERROR("Time mode shall be free-run when use once timer!!");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    if (instance_p->isready == FT_COMPONENT_IS_READY)
    {
        FTIMER_INFO("Device is already initialized.!!!\r\n");
        return FTIMER_TACHO_ERR_IS_READ;
    }

    if (FTIMER_WORK_MODE_TIMER == config_p->work_mode)
    {
        reg_val |= FTIMER_REG_TACHO_MODE_TIMER;
    }
    else
    {
        FTIMER_ERROR("Not support");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    if (FTIMER_FREE_RUN == config_p->timer_mode)
    {
        reg_val &= (~FTIMER_REG_CNT_RESTART);
    }
    else if (FTIMER_RESTART == config_p->timer_mode)
    {
        reg_val |= FTIMER_REG_CNT_RESTART;
    }
    else
    {
        FTIMER_ERROR("Invalid input");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    if (FTIMER_32_BITS == config_p->timer_bits)
    {
        reg_val &= (~FTIMER_REG_CNT_SERIES_64BIT);
    }
    else if (FTIMER_64_BITS == config_p->timer_bits)
    {
        reg_val |= FTIMER_REG_CNT_SERIES_64BIT;
    }
    else
    {
        FTIMER_ERROR("Invalid input");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    if (FTIMER_ONCE_CMP == config_p->cmp_type)
    {
        reg_val |= FTIMER_REG_MODE_ONCE;
    }
    else if (FTIMER_CYC_CMP == config_p->cmp_type)
    {
        reg_val &= (~FTIMER_REG_MODE_ONCE);
    }
    else
    {
        FTIMER_ERROR("Invalid input");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    if (TRUE == config_p->force_load)
    {
        reg_val |= FTIMER_REG_TACHO_FORCE_LOAD;
    }

    if (TRUE == config_p->clear_cnt)
    {
        reg_val |= FTIMER_REG_CNT_CLR;
    }

    /*use input config*/
    if (config_p != &instance_p->config)
    {
        instance_p->config = *config_p;
    }

    FTIMER_CTRL_WRITE(instance_p, reg_val);
    instance_p->isready = FT_COMPONENT_IS_READY;

    return FTIMER_TACHO_SUCCESS;
}

void FTimerDeInit(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);

    /* stop timer first */
    FTimerStop(instance_p);
    /* reset reg*/
    FTimerSoftwareReset(instance_p);

    instance_p->isready = 0;
    memset(instance_p, 0, sizeof(*instance_p));

    return;
}

/**
 * @name: FTimeSettingDump
 * @msg: 打印寄存器信息
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
FError FTimeSettingDump(const FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);
    u32 CtrlReg = FTIMER_CTRL_READ(instance_p);
    boolean is64Bit = ((CtrlReg & FTIMER_REG_CNT_SERIES_64BIT) != 0);

    FASSERT(FT_COMPONENT_IS_READY == instance_p->isready);

    FTIMER_DEBUG("ctrl: ");
    FTIMER_DEBUG("===%d-bit timer", is64Bit ? 64 : 32);
    FTIMER_DEBUG("===timer enabled: %d", (CtrlReg & FTIMER_REG_ENABLE) ? 1 : 0);
    FTIMER_DEBUG("===timer mode: %d", (CtrlReg & FTIMER_REG_TACHO_MODE_TIMER) ? 1 : 0);
    FTIMER_DEBUG("===once timer: %d", (CtrlReg & FTIMER_REG_MODE_ONCE) ? 1 : 0);
    FTIMER_DEBUG("===restart mode: %d", (CtrlReg & FTIMER_REG_CNT_RESTART) ? 1 : 0);
    FTIMER_DEBUG("===in reset: %d", (CtrlReg & FTIMER_REG_TACHO_RESET) ? 1 : 0);
    FTIMER_DEBUG("===force load: %d", (CtrlReg & FTIMER_REG_TACHO_FORCE_LOAD) ? 1 : 0);
    FTIMER_DEBUG("===clear cnt: %d", (CtrlReg & FTIMER_REG_CNT_CLR) ? 1 : 0);

    FTIMER_DEBUG("start cnt: 0x%08x", FTIMER_STAR_READ(instance_p));
    if (is64Bit)
    {
        FTIMER_DEBUG("cmp low: 0x%08x", FTIMER_CMPL_READ(instance_p));
        FTIMER_DEBUG("high: 0x%08x", FTIMER_CMPU_READ(instance_p));
        FTIMER_DEBUG("cur cnt: low: 0x%08x", FTIMER_CNTL_READ(instance_p));
        FTIMER_DEBUG("high: 0x%08x", FTIMER_CNTU_READ(instance_p));
    }
    else
    {
        FTIMER_DEBUG("cmp low: 0x%08x", FTIMER_CMPL_READ(instance_p));
        FTIMER_DEBUG("cur cnt: low: 0x%08x", FTIMER_CNTL_READ(instance_p));
    }

    FTIMER_DEBUG("intr mask: 0x%08x", FTIMER_INTR_M_READ(instance_p));
    FTIMER_DEBUG("intr status: 0x%08x", FTIMER_INTR_S_READ(instance_p));

    return FTIMER_TACHO_SUCCESS;
}