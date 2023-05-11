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
 * FilePath: fpwm.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-15 11:45:05
 * Description:  This file is for the minimum required function implementations for this driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/15   init commit
 */

#include <string.h>
#include "fkernel.h"
#include "ftypes.h"
#include "ferror_code.h"
#include "fdebug.h"
#include "fpwm.h"
#include "fpwm_hw.h"
#include "fparameters.h"
#include "fsleep.h"

#define FPWM_DEBUG_TAG "PWM"
#define FPWM_ERROR(format, ...)     FT_DEBUG_PRINT_E(FPWM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPWM_WARN(format, ...)     FT_DEBUG_PRINT_W(FPWM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPWM_INFO(format, ...)      FT_DEBUG_PRINT_I(FPWM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPWM_DEBUG(format, ...)     FT_DEBUG_PRINT_D(FPWM_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FPwmReset
 * @msg:  reset pwm
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmReset(FPwmCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);

    u32 reg_val = 0;
    int timeout = FPWM_RESET_TIMEOUT;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    reg_val |= FPWM_TIM_CTRL_RESET;
    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);

    /* Check for the reset complete*/
    do
    {
        reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    }
    while ((FPWM_TIM_CTRL_RESET & reg_val) && (0 <= --timeout));

    if (0 >= timeout)
    {
        FPWM_ERROR("Time out while waiting for pwm reset to complete");
        return FPWM_ERR_TIMEOUT;
    }
    return FPWM_SUCCESS;
}

/**
 * @name: FPwmEnable
 * @msg:  enable pwm
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @return
 */
void FPwmEnable(FPwmCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    reg_val |= FPWM_TIM_CTRL_ENABLE;
    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);

    pctrl->channel_ctrl_enable[channel] = TRUE;
}

/**
 * @name: FPwmDisable
 * @msg:  disable pwm
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @return
 */
void FPwmDisable(FPwmCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    reg_val &= (~FPWM_TIM_CTRL_ENABLE);
    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);

    pctrl->channel_ctrl_enable[channel] = FALSE;

}

/**
 * @name: FPwmTimCtrlModeSet
 * @msg:  config pwm timer counter mode.
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmTimCtrlMode} mode, counter mode parameters of FPWM
 * @return
 */
static void FPwmTimCtrlModeSet(FPwmCtrl *pctrl, u32 channel, FPwmTimCtrlMode mode)
{
    FASSERT(pctrl != NULL);
    FASSERT(mode < FPWM_TIM_CTRL_MODE_NUM);
    /* check whether the state is disabled */
    FASSERT(pctrl->channel_ctrl_enable[channel] == FALSE);

    u32 reg_val = 0;

    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);
    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);

    switch (mode)
    {
        /* modulo */
        case FPWM_MODULO:
            reg_val &= (~FPWM_TIM_CTRL_MODE_UD);
            break;
        /* up-and-down */
        case FPWM_UP_DOWN:
            reg_val |= FPWM_TIM_CTRL_MODE_UD;
            break;
        default:
            break;
    }

    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmTimInterruptEnable
 * @msg:  enable pwm timer global and counter-overflow interrupt
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @return
 */
static void FPwmTimInterruptEnable(FPwmCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl != NULL);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    reg_val &= (~(FPWM_TIM_CTRL_OVFIF_ENABLE | FPWM_TIM_CTRL_GIE));
    reg_val |= (FPWM_TIM_CTRL_OVFIF_ENABLE | FPWM_TIM_CTRL_GIE);

    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmTimInterruptDisable
 * @msg:  disable pwm timer global and counter-overflow interrupt
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @return
 */
static void FPwmTimInterruptDisable(FPwmCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl != NULL);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    reg_val &= (~(FPWM_TIM_CTRL_OVFIF_ENABLE | FPWM_TIM_CTRL_GIE));

    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmDivSet
 * @msg:  config pwm div, div range：0~4095, corresponding to 1~4096
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {u16} div, div parameters
 * @return
 */
static void FPwmDivSet(FPwmCtrl *pctrl, u32 channel, u16 div)
{
    u32 reg_val = 0;
    FASSERT(pctrl != NULL);
    FASSERT(div < FPWM_TIM_CTRL_DIV_MAX);
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_TIM_CTRL_OFFSET);
    reg_val |= (FPWM_TIM_CTRL_DIV_MASK & FPWM_TIM_CTRL_DIV(div));

    FPWM_WRITE_REG32(base_addr, FPWM_TIM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmPeriodSet
 * @msg:  config pwm period, range：1~0xffff
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {u16} pwm_period, period parameters
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
static void FPwmPeriodSet(FPwmCtrl *pctrl, u32 channel, u16 pwm_period)
{
    FASSERT(pctrl != NULL);
    u32 reg_val = 0;
    u64 cycles = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_PERIOD_OFFSET);
    reg_val &= (~FPWM_PERIOD_CCR_MASK);
    reg_val |= (pwm_period & FPWM_PERIOD_CCR_MASK);

    FPWM_WRITE_REG32(base_addr, FPWM_PERIOD_OFFSET, reg_val);
}

/**
 * @name: FPwmDutySourceSet
 * @msg:  config pwm duty source, from pwm_ccr register or fifo
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmDutySourceMode} duty_source, duty source parameters
 * @return
 */
static void FPwmDutySourceSet(FPwmCtrl *pctrl, u32 channel, FPwmDutySourceMode duty_source)
{
    FASSERT(pctrl != NULL);
    FASSERT(duty_source < FPWM_DUTY_SEL_MODE_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CTRL_OFFSET);
    switch (duty_source)
    {
        /* duty from PWM_CCR */
        case FPWM_DUTY_CCR:
            reg_val &= (~FPWM_CTRL_DUTY_SOURCE_FIFO);
            break;
        /* from FIFO */
        case FPWM_DUTY_FIFO:
            reg_val |= FPWM_CTRL_DUTY_SOURCE_FIFO;
            break;
        default:
            break;
    }

    FPWM_WRITE_REG32(base_addr, FPWM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmPulseSet
 * @msg:  config pwm duty, pwm_ccr is less than pwm_period
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {u16} pwm_ccr, pwm_ccr parameters
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmPulseSet(FPwmCtrl *pctrl, u32 channel, u16 pwm_ccr)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    u32 reg_val = 0;
    u64 cycles = 0;
    u32 state = 0;
    u16 pwm_period_ccr = 0;

    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    /* Check the pwm_ccr < pwm_period_ccr */
    pwm_period_ccr = (u16)FPWM_READ_REG32(base_addr, FPWM_PERIOD_OFFSET);
    if (pwm_ccr > pwm_period_ccr)
    {
        FPWM_ERROR("The pwm ccr is larger than the period");
        return FPWM_ERR_INVAL_PARM;
    }

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CTRL_OFFSET);

    /* Check the duty source */
    if (reg_val & FPWM_CTRL_DUTY_SOURCE_FIFO)
    {
        /* Check the duty fifo is not full */
        state = FPWM_READ_REG32(base_addr, FPWM_STATE_OFFSET);
        if (state & FPWM_STATE_FIFO_FULL)
        {
            FPWM_ERROR("The fifo of the pwm is full");
            return FPWM_ERR_CMD_FAILED;
        }
    }

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CCR_OFFSET);
    reg_val &= (~FPWM_CCR_MASK);
    reg_val |= (pwm_ccr & FPWM_CCR_MASK);

    FPWM_WRITE_REG32(base_addr, FPWM_CCR_OFFSET, reg_val);

    return FPWM_SUCCESS;
}

/**
 * @name: FPwmCtrlModeSet
 * @msg:  config pwm mode, currently only support compare output
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @return
 */
static void FPwmCtrlModeSet(FPwmCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl != NULL);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CTRL_OFFSET);

    reg_val |= FPWM_CTRL_MODE_OUTPUT;

    FPWM_WRITE_REG32(base_addr, FPWM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmPolaritySet
 * @msg:  config pwm compare output polarity
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmPolarity} polarity, compare output polarity parameters
 * @return
 */
static void FPwmPolaritySet(FPwmCtrl *pctrl, u32 channel, FPwmPolarity polarity)
{
    FASSERT(pctrl != NULL);
    FASSERT(polarity < FPWM_POLARITY_NUM);
    /* check whether the state is disabled */
    FASSERT(pctrl->channel_ctrl_enable[channel] == FALSE);
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    u32 reg_val = 0;
    reg_val = FPWM_READ_REG32(base_addr, FPWM_CTRL_OFFSET);
    reg_val &= (~FPWM_CTRL_CMP_MASK);
    reg_val |= FPWM_CTRL_CMP(polarity);
    FPWM_WRITE_REG32(base_addr, FPWM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmDbReset
 * @msg:  reset pwm db
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
static FError FPwmDbReset(FPwmCtrl *pctrl)
{
    FASSERT(pctrl != NULL);

    u32 reg_val = 0;
    int timeout = FPWM_RESET_TIMEOUT;
    uintptr base_addr = pctrl->config.db_base_addr;

    reg_val = FPWM_READ_REG32(base_addr, FPWM_DB_CTRL_OFFSET);
    reg_val |= FPWM_DB_CTRL_RESET;
    FPWM_WRITE_REG32(base_addr, FPWM_DB_CTRL_OFFSET, reg_val);

    /* Check for the db reset complete*/
    do
    {
        reg_val = FPWM_READ_REG32(base_addr, FPWM_DB_CTRL_OFFSET);
    }
    while ((FPWM_DB_CTRL_RESET & reg_val) && (0 <= --timeout));

    if (0 >= timeout)
    {
        FPWM_ERROR("Time out while waiting for pwm db reset to complete");
        return FPWM_ERR_TIMEOUT;
    }
    return FPWM_SUCCESS;
}

/**
 * @name: FPwmDbPolaritySet
 * @msg:  config pwm db polarity
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {FPwmDbPolarity} db_polarity, db polarity parameters
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmDbPolaritySet(FPwmCtrl *pctrl, FPwmDbPolarity db_polarity)
{
    FASSERT(pctrl != NULL);
    FASSERT(db_polarity < FPWM_DB_POLARITY_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.db_base_addr;

    reg_val = FPWM_READ_REG32(base_addr, FPWM_DB_CTRL_OFFSET);
    reg_val &= (~FPWM_DB_CTRL_POLSEL_MASK);
    reg_val |= FPWM_DB_CTRL_POLSEL(db_polarity);
    FPWM_WRITE_REG32(base_addr, FPWM_DB_CTRL_OFFSET, reg_val);

    return FPWM_SUCCESS;
}

/**
 * @name: FPwmDbFallCycleSet
 * @msg:  config pwm db fall cycle
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u16} fall_edge_delay, db fall cycle parameters
 * @return
 */
static void FPwmDbFallCycleSet(FPwmCtrl *pctrl, u16 fall_edge_delay)
{
    FASSERT(pctrl != NULL);
    FASSERT(fall_edge_delay < FPWM_DB_DLY_MAX);
    u32 reg_val = 0;
    uintptr pwm_base_addr = pctrl->config.pwm_base_addr;
    uintptr db_base_addr = pctrl->config.db_base_addr;

    u32 pwm_period = FPWM_READ_REG32(pwm_base_addr, FPWM_PERIOD_OFFSET);

    reg_val = FPWM_READ_REG32(db_base_addr, FPWM_DB_DLY_OFFSET);
    reg_val &= (~FPWM_DB_DLY_FALL_MASK);
    reg_val |= FPWM_DB_DLY_FALL(fall_edge_delay);
    FPWM_WRITE_REG32(db_base_addr, FPWM_DB_DLY_OFFSET, reg_val);
}

/**
 * @name: FPwmDbRiseCycleSet
 * @msg:  config pwm db rise cycle
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u16} rise_edge_delay, db rise cycle parameters
 * @return
 */
static void FPwmDbRiseCycleSet(FPwmCtrl *pctrl, u16 rise_edge_delay)
{
    FASSERT(pctrl != NULL);
    FASSERT(rise_edge_delay < FPWM_DB_DLY_MAX);
    u32 reg_val = 0;
    uintptr pwm_base_addr = pctrl->config.pwm_base_addr;
    uintptr db_base_addr = pctrl->config.db_base_addr;

    u32 pwm_period = FPWM_READ_REG32(pwm_base_addr, FPWM_PERIOD_OFFSET);

    reg_val = FPWM_READ_REG32(db_base_addr, FPWM_DB_DLY_OFFSET);
    reg_val &= (~FPWM_DB_DLY_RISE_MASK);
    reg_val |= (u32)(rise_edge_delay & FPWM_DB_DLY_RISE_MASK);
    FPWM_WRITE_REG32(db_base_addr, FPWM_DB_DLY_OFFSET, reg_val);
}

/**
 * @name: FPwmDbInModeSet
 * @msg:  config pwm db in source mode, pwm0 or pwm1
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {FPwmDbInMode} db_in_mode, db in mode parameters
 * @return void
 */
static void FPwmDbInModeSet(FPwmCtrl *pctrl, FPwmDbInMode db_in_mode)
{
    FASSERT(db_in_mode < FPWM_DB_IN_MODE_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.db_base_addr;

    reg_val = FPWM_READ_REG32(base_addr, FPWM_DB_CTRL_OFFSET);
    switch (db_in_mode)
    {
        case FPWM_DB_IN_MODE_PWM0:
            reg_val &= (~FPWM_DB_CTRL_IN_MODE);
            break;
        case FPWM_DB_IN_MODE_PWM1:
            reg_val |= FPWM_DB_CTRL_IN_MODE;
            break;
        default:
            break;
    }

    FPWM_WRITE_REG32(base_addr, FPWM_DB_CTRL_OFFSET, reg_val);
}

static void FPwmDbOutModeSet(FPwmCtrl *pctrl, FPwmDbOutMode db_out_mode)
{
    FASSERT(db_out_mode < FPWM_DB_OUT_MODE_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.db_base_addr;

    reg_val = FPWM_READ_REG32(base_addr, FPWM_DB_CTRL_OFFSET);
    reg_val &= (~FPWM_DB_CTRL_OUT_MODE_MASK);
    reg_val |= FPWM_DB_CTRL_OUT_MODE(db_out_mode);
    FPWM_WRITE_REG32(base_addr, FPWM_DB_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmInterruptEnable
 * @msg:  enable pwm compare output interrupt
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmIntrEventType} intr_type, pwm interrupt event type
 * @return
 */
void FPwmInterruptEnable(FPwmCtrl *pctrl, u32 channel, FPwmIntrEventType intr_type)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CTRL_OFFSET);

    if (intr_type == FPWM_INTR_EVENT_COUNTER)
    {
        reg_val &= (~FPWM_CTRL_INTR_COUNTER_ENABLE);
        reg_val |= FPWM_CTRL_INTR_COUNTER_ENABLE;
    }

    if (intr_type == FPWM_INTR_EVENT_FIFO_EMPTY)
    {
        reg_val &= (~FPWM_CTRL_INTR_FIFO_EMPTY_ENABLE);
        reg_val |= FPWM_CTRL_INTR_FIFO_EMPTY_ENABLE;
    }

    FPWM_WRITE_REG32(base_addr, FPWM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmInterruptDisable
 * @msg:  disable pwm compare output interrupt
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmIntrEventType} intr_type, pwm interrupt event type
 * @return
 */
void FPwmInterruptDisable(FPwmCtrl *pctrl, u32 channel, FPwmIntrEventType intr_type)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CTRL_OFFSET);

    if (intr_type == FPWM_INTR_EVENT_COUNTER)
    {
        reg_val &= (~FPWM_CTRL_INTR_COUNTER_ENABLE);
    }

    if (intr_type == FPWM_INTR_EVENT_FIFO_EMPTY)
    {
        reg_val &= (~FPWM_CTRL_INTR_FIFO_EMPTY_ENABLE);
    }

    FPWM_WRITE_REG32(base_addr, FPWM_CTRL_OFFSET, reg_val);
}

/**
 * @name: FPwmDbVariableSet
 * @msg:  set pwm db Variable config, users need call this function before
 *             FPwmVariableSet if you want to use deadband function.
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {FPwmDbVariableConfig} db_cfg_p, db config parameters, include mode and cycles
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmDbVariableSet(FPwmCtrl *pctrl, FPwmDbVariableConfig *db_cfg_p)
{
    FASSERT(pctrl != NULL);
    FASSERT(db_cfg_p != NULL);

    FError ret = FPWM_SUCCESS;

    ret = FPwmDbReset(pctrl);
    if (ret != FPWM_SUCCESS)
    {
        FPWM_ERROR("%s ,The FPwmDbReset call failed",__func__);
        return FPWM_ERR_CMD_FAILED;
    }

    FPwmDbRiseCycleSet(pctrl, db_cfg_p->db_rise_cycle);

    FPwmDbFallCycleSet(pctrl, db_cfg_p->db_fall_cycle);

    ret = FPwmDbPolaritySet(pctrl, db_cfg_p->db_polarity_sel);
    if (ret != FPWM_SUCCESS)
    {
        FPWM_ERROR("%s ,The FPwmDbPolaritySet call failed",__func__);
        return FPWM_ERR_CMD_FAILED;
    }

    FPwmDbInModeSet(pctrl, db_cfg_p->db_in_mode);

    FPwmDbOutModeSet(pctrl, db_cfg_p->db_out_mode);

    return ret;
}

/**
 * @name: FPwmDbVariableGet
 * @msg:  get pwm deadband variable configuration.
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {FPwmDbVariableConfig} *db_cfg_p, pwm deadband config parameters
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmDbVariableGet(FPwmCtrl *pctrl, FPwmDbVariableConfig *db_cfg_p)
{
    FASSERT(pctrl != NULL);
    FASSERT(db_cfg_p != NULL);
    FError ret = FPWM_SUCCESS;

    uintptr db_base_addr = pctrl->config.db_base_addr;

    u32 db_ctrl = FPWM_READ_REG32(db_base_addr, FPWM_DB_CTRL_OFFSET);
    /* db input source*/
    db_cfg_p->db_in_mode =
        (db_ctrl & FPWM_DB_CTRL_IN_MODE) ? FPWM_DB_IN_MODE_PWM1 : FPWM_DB_IN_MODE_PWM0;

    /* db polarity select*/
    db_cfg_p->db_polarity_sel = FPWM_DB_CTRL_POLSEL_GET(db_ctrl & FPWM_DB_CTRL_POLSEL_MASK);
    /* db output mode*/
    db_cfg_p->db_out_mode = FPWM_DB_CTRL_OUT_MODE_GET(db_ctrl & FPWM_DB_CTRL_OUT_MODE_MASK);

    u32 db_dly = FPWM_READ_REG32(db_base_addr, FPWM_DB_DLY_OFFSET);
    /* db falling edge delay cycle */
    db_cfg_p->db_fall_cycle = FPWM_DB_DLY_FALL_GET(db_dly & FPWM_DB_DLY_FALL_MASK);
    /* db rising edge delay cycle */
    db_cfg_p->db_rise_cycle = (db_dly & FPWM_DB_DLY_RISE_MASK);

    return ret;

}

/**
 * @name: FPwmVariableSet
 * @msg:  set pwm channel variable configuration, users need call this function after
 *             FPwmDbVariableSet if you want to use deadband function.
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmVariableConfig} pwm_cfg_p, pwm config parameters, include mode and duty
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmVariableSet(FPwmCtrl *pctrl, u32 channel, FPwmVariableConfig *pwm_cfg_p)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    FASSERT(pwm_cfg_p != NULL);
    FError ret = FPWM_SUCCESS;

#if defined(FLSD_CONFIG_BASE)
    /* enable lsd pwm syn */
    FPwmLsdEnable(FLSD_CONFIG_BASE, pctrl->config.instance_id);
#endif
    /* bit[0]:set pwm_tim_ctrl SW_RST */
    ret = FPwmReset(pctrl, channel);
    if (ret != FPWM_SUCCESS)
    {
        FPWM_ERROR("%s ,FPwmReset  call failed",__func__);
        return FPWM_ERR_CMD_FAILED;
    }

    /* pwm timer ctrl disable, before can config */
    FPwmDisable(pctrl, channel);

    /* bit[2]:set tim_ctrl Mode */
    FPwmTimCtrlModeSet(pctrl, channel, pwm_cfg_p->tim_ctrl_mode);

    /* bit[4,5]:set tim_ctrl interrput */
    FPwmTimInterruptEnable(pctrl, channel);

    /*bit[16~27]: set tim_ctrl DIV 0~4095 */
    FPwmDivSet(pctrl, channel, pwm_cfg_p->tim_ctrl_div);

    /*bit[0~15]: set pwm_period */
    FPwmPeriodSet(pctrl, channel, pwm_cfg_p->pwm_period);

    /*bit[2]:pwm control mode, input capture or output compare  */
    FPwmCtrlModeSet(pctrl, channel);

    /*bit[3]:pwm control mode irq */
    FPwmInterruptEnable(pctrl, channel, FPWM_INTR_EVENT_COUNTER);
    FPwmInterruptEnable(pctrl, channel, FPWM_INTR_EVENT_FIFO_EMPTY);

    /*bit[4~6]:pwm ctrl polarity config CMP:0b100*/
    FPwmPolaritySet(pctrl, channel, pwm_cfg_p->pwm_polarity);

    /*bit[8]:pwm duty source , duty from ccr or fifo */
    FPwmDutySourceSet(pctrl, channel, pwm_cfg_p->pwm_duty_source_mode);

    /*pwm pulse set, duty */
    ret = FPwmPulseSet(pctrl, channel, pwm_cfg_p->pwm_pulse);
    if (ret != FPWM_SUCCESS)
    {
        FPWM_ERROR("%s , FPwmPulseSet failed",__func__);
        return FPWM_ERR_CMD_FAILED;
    }

    return ret;
}

/**
 * @name: FPwmVariableGet
 * @msg:  get pwm channel variable configuration.
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {FPwmVariableConfig} *pwm_cfg_p, pwm config parameters, include mode and duty
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmVariableGet(FPwmCtrl *pctrl, u32 channel, FPwmVariableConfig *pwm_cfg_p)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FPWM_CHANNEL_NUM);
    FASSERT(pwm_cfg_p != NULL);
    FError ret = FPWM_SUCCESS;

    uintptr pwm_base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    u32 tim_ctrl = FPWM_READ_REG32(pwm_base_addr, FPWM_TIM_CTRL_OFFSET);
    /* tim_ctrl mode, counter mode */
    pwm_cfg_p->tim_ctrl_mode =
        (tim_ctrl & FPWM_TIM_CTRL_MODE_UD) ? FPWM_UP_DOWN : FPWM_MODULO;
    /* pwm divider */
    pwm_cfg_p->tim_ctrl_div = FPWM_TIM_CTRL_DIV_GET(tim_ctrl & FPWM_TIM_CTRL_DIV_MASK);

    /* pwm period value */
    u32 pwm_period = FPWM_READ_REG32(pwm_base_addr, FPWM_PERIOD_OFFSET) ;
    pwm_cfg_p->pwm_period = (u16)(pwm_period & FPWM_PERIOD_CCR_MASK);

    u32 pwm_ctrl = FPWM_READ_REG32(pwm_base_addr, FPWM_CTRL_OFFSET);
    /* pwm mode, compare output */
    pwm_cfg_p->pwm_mode =
        (pwm_ctrl & FPWM_CTRL_MODE_OUTPUT) ? FPWM_OUTPUT_COMPARE : FPWM_NONE_MODE;

    /* pwm compare output polarity */
    pwm_cfg_p->pwm_polarity = FPWM_CTRL_CMP_GET(pwm_ctrl & FPWM_CTRL_CMP_MASK);

    /* pwm duty value source */
    pwm_cfg_p->pwm_duty_source_mode =
        (pwm_ctrl & FPWM_CTRL_DUTY_SOURCE_FIFO) ? FPWM_DUTY_FIFO : FPWM_DUTY_CCR;

    /* pwm pulse value */
    u32 pwm_ccr = FPWM_READ_REG32(pwm_base_addr, FPWM_CCR_OFFSET);
    pwm_cfg_p->pwm_pulse = (u16)(pwm_ccr & FPWM_CCR_MASK);

    return ret;
}

/**
 * @name: FPwmDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @return {*}
 */
void FPwmDeInitialize(FPwmCtrl *pctrl)
{
    FASSERT(pctrl);

    pctrl->is_ready = 0;
    memset(pctrl, 0, sizeof(*pctrl));

    return;
}

/**
 * @name: FPwmCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {FPwmConfig} *input_config_p, Configuration parameters of FPWM
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FPwmCfgInitialize(FPwmCtrl *pctrl, const FPwmConfig *input_config_p)
{
    FASSERT(pctrl && input_config_p);

    FError ret = FPWM_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == pctrl->is_ready)
    {
        FPWM_WARN("The device has been initialized!!!");
    }

    /*Set default values and configuration data */
    FPwmDeInitialize(pctrl);

    pctrl->config = *input_config_p;
#if defined(CONFIG_TARGET_E2000) 
    ret = FPwmDbReset(pctrl);
    if (ret != FPWM_SUCCESS)
    {
        FPWM_ERROR("%s ,The FPwmDbReset call failed");
        return FPWM_ERR_CMD_FAILED;
    }
#endif
    pctrl->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}

/**
 * @name: FPwmGpioSet
 * @msg:  Control gpio output
 * @param {FPwmCtrl} *pctrl, instance of FPWM controller
 * @param {u32} channel, pwm module's channel, 0/1
 * @param {u32} output, set high or low level, 0-low, 1-high
 * @return void
 */
void FPwmGpioSet(FPwmCtrl *pctrl, u32 channel, u32 output)
{
    FASSERT(pctrl != NULL);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

    reg_val = FPWM_READ_REG32(base_addr, FPWM_CCR_OFFSET);
    if(output)
	    reg_val |= FPWM_CCR_GPIO;
    else
        reg_val &= (~FPWM_CCR_GPIO);        
	FPWM_WRITE_REG32(base_addr, FPWM_CCR_OFFSET, reg_val);
    
}