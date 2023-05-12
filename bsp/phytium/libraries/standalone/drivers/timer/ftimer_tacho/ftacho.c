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
 * FilePath: ftacho.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-05-20 09:08:52
 * Description:  This file is for user tacho API implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/05/20    first commit
 */

/***************************** Include Files *********************************/

#include <string.h>
#include "fassert.h"
#include "fkernel.h"
#include "fsleep.h"
#include "ftimer_tacho_hw.h"
#include "ftimer_tacho.h"
#include "fparameters.h"

/************************** Function Prototypes ******************************/
/**
 * @name: FTachoInit
 * @msg: 初始化Tacho，并且使能计数器和tachometer
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {FTimerTachoConfig} *config_p 驱动配置数据结构
 */
FError FTachoInit(FTimerTachoCtrl *instance_p, const FTimerTachoConfig *config_p)
{
    FASSERT(instance_p && config_p);

    u32 reg_val = 0;

    if (instance_p->isready == FT_COMPONENT_IS_READY)
    {
        FTIMER_INFO("Device is already initialized !!!\r\n");
        return FTIMER_TACHO_ERR_IS_READ;
    }

    /* set work mode */
    if (FTIMER_WORK_MODE_TACHO == config_p->work_mode)
    {
        reg_val |= FTIMER_REG_TACHO_MODE_TACHO;
        reg_val |= FTACHO_REG_CAP_IN_ENABLE;
        /* plus num of rpm calculate period */
        FTIMER_CMPL_WRITE(instance_p, config_p->plus_num);
    }
    else if (FTIMER_WORK_MODE_CAPTURE == config_p->work_mode)
    {
        reg_val |= FTIMER_REG_TACHO_MODE_CAPTURE;
        reg_val |= FTIMER_REG_TACHO_CAPTURE_ENABLE;
        /* set capture cnt to assert capture intr */
        reg_val |= FTIMER_REG_TACHO_CAPTURE_CNT_MASK & (config_p->captue_cnt << FTIMER_REG_TACHO_CAPTURE_CNT_SHIFT);
        reg_val |= FTIMER_REG_ENABLE;
    }
    else
    {
        FTACHO_ERROR("Not support work_mode.");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    /* set timer bits */
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
        FTACHO_ERROR("Invalid input 32/64bits.");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    /* set edge mode */
    if (FTACHO_FALLING_EDGE == config_p->edge_mode)
    {
        reg_val &= ~FTACHO_REG_MODE_MASK;
        reg_val |= FTACHO_REG_MODE_FALLING_EDGE;
    }
    else if (FTACHO_RISING_EDGE == config_p->edge_mode)
    {
        reg_val &= ~FTACHO_REG_MODE_MASK;
        reg_val |= FTACHO_REG_MODE_RISING_EDGE;
    }
    else if (FTACHO_DOUBLE_EDGE == config_p->edge_mode)
    {
        reg_val &= ~FTACHO_REG_MODE_MASK;
        reg_val |= FTACHO_REG_MODE_DOUBLE_EDGE;
    }
    else
    {
        FTACHO_ERROR("Invalid input edge.");
        return FTIMER_TACHO_ERR_INVAL_PARM;
    }

    /* set jitter level */
    reg_val |= FTACHO_REG_ANTI_JITTER_MASK &
               (config_p->jitter_level << FTACHO_REG_ANTI_JITTER_SHIFT);

    //use input config
    if (config_p != &instance_p->config)
    {
        instance_p->config = *config_p;
    }

    FTIMER_CTRL_WRITE(instance_p, reg_val);
    instance_p->isready = FT_COMPONENT_IS_READY;

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: FTachoGetFanRPM
 * @msg: 获取风扇的转速值
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u32} *rpm 将获取到的数值写入到此地址
 */
FError FTachoGetFanRPM(FTimerTachoCtrl *instance_p, u32 *rpm)
{
    u32 loop_cnt;
    u32 raw_dat;

    FASSERT(instance_p);

    if (instance_p->isready != FT_COMPONENT_IS_READY || instance_p->config.work_mode != FTIMER_WORK_MODE_TACHO)
    {
        FTIMER_ERROR("Device is not ready or not work on TACHO_MODE!!!");
        return FTIMER_TACHO_ERR_NOT_READY;
    }

    u32 cnt_num = FTIMER_CMPL_READ(instance_p);

    for (loop_cnt = 0;; loop_cnt++)
    {
        raw_dat = FTACHO_RESU_READ(instance_p);
        /* wait for tacho result */
        if (raw_dat & FTACHO_REG_RESU_ISVALID)
        {
            break;
        }

        if (loop_cnt < 300)
        {
            fsleep_millisec(20); //20ms
        }
        else
        {
            return FTIMER_TACHO_ERR_ABORT;
        }
    }

    raw_dat &= FTACHO_REG_RESU_MASK;
    if (0 == raw_dat)
    {
        *rpm = 0;
    }
    else
    {
        /* calculate rpm */
        /* (60(second) * freq * tacho) / (2 * (cmp_l + 1)) cmp_l */
        *rpm = (FTIMER_CLK_FREQ_HZ * 60 * raw_dat) / (2 * (cnt_num + 1));
    }

    return FTIMER_TACHO_SUCCESS;
}

/**
 * @name: FTachoGetCaptureCnt
 * @msg: 获取capture模式下，tacho输入脉冲的个数
 * @return {u32}返回获取到的数值
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
u32 FTachoGetCaptureCnt(FTimerTachoCtrl *instance_p)
{
    u32 cap_cnt = FTIMER_TACHO_SUCCESS;

    FASSERT(instance_p);

    if (instance_p->isready != FT_COMPONENT_IS_READY || instance_p->config.work_mode != FTIMER_WORK_MODE_CAPTURE)
    {
        FTIMER_ERROR("Device is not ready or not work on CAPTURE_MODE!!!");
        return FTIMER_TACHO_ERR_NOT_READY;
    }

    /* read cap cnt */
    cap_cnt = FTIMER_CNTL_READ(instance_p);

    return cap_cnt;
}

/**
 * @name: FTimerSwithMode
 * @msg: 切换定时器模式和tachometer-capture模式
 * @return {FError} 驱动初始化的错误码信息，FTIMER_TACHO_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {FTimerTachoConfig} *pNewConfig 新的驱动配置数据结构
 */
FError FTimerSwithMode(FTimerTachoCtrl *instance_p, FTimerTachoConfig *pNewConfig)
{
    FASSERT(instance_p && pNewConfig);

    u32 ret = FTIMER_TACHO_SUCCESS;

    if (instance_p->config.work_mode == pNewConfig->work_mode)
    {
        return FTIMER_TACHO_SUCCESS;
    }

    /* disable and clear timer */
    u32 reg_val = FTIMER_CTRL_READ(instance_p);
    reg_val &= (~FTIMER_REG_ENABLE);
    reg_val |= FTIMER_REG_CNT_CLR;
    FTIMER_CTRL_WRITE(instance_p, reg_val);

    if (FTIMER_WORK_MODE_TIMER == pNewConfig->work_mode)
    {
        ret = FTimerInit(instance_p, pNewConfig);
    }
    else
    {
        ret = FTachoInit(instance_p, pNewConfig);
    }

    return ret;
}

/**
 * @name: FTachoSetCntPeriod
 * @msg: 配置 tach计数周期 = pulse_num
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u32}计数ticks
 */
void FTachoSetCntPeriod(FTimerTachoCtrl *instance_p, u32 ticks)
{
    FTIMER_CMPL_WRITE(instance_p, ticks);
}

/**
 * @name: FTachoSetOverLimit
 * @msg: 预设tacho的最大值
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u32}上限值
 */
void FTachoSetOverLimit(FTimerTachoCtrl *instance_p, u32 overLim)
{
    FTACHO_OVER_WRITE(instance_p, overLim);
}

/**
 * @name: FTachoSetUnderLimit
 * @msg: 预设tacho的最小值
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 * @param {u32}下限值
 */
void FTachoSetUnderLimit(FTimerTachoCtrl *instance_p, u32 underLim)
{
    FTACHO_UNDER_WRITE(instance_p, underLim);
}

/**
 * @name: FTachoDeInit
 * @msg: 去初始化，寄存器复位，结构体参数置0
 * @return {void}
 * @param {FTimerTachoCtrl} *instance_p 驱动控制数据结构
 */
void FTachoDeInit(FTimerTachoCtrl *instance_p)
{
    FASSERT(instance_p);

    /* reset reg*/
    FTimerSoftwareReset(instance_p);

    instance_p->isready = 0;
    memset(instance_p, 0, sizeof(*instance_p));

    return;
}