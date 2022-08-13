/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_gpc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.gpc_3"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief GPC submodule step registers offset */
static uint32_t const s_cmRegOffset[] = GPC_CM_STEP_REG_OFFSET;

static uint32_t const s_spRegOffset[] = GPC_SP_STEP_REG_OFFSET;

static uint32_t const s_stbyRegOffset[] = GPC_STBY_STEP_REG_OFFSET;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Enable IRQ wakeup request.
 *
 * This function enables the IRQ request which can wakeup the CPU platform.
 *
 * param base GPC CPU module base address.
 * param irqId ID of the IRQ, accessible range is 0-255.
 * param enable Enable the IRQ request or not.
 */
void GPC_CM_EnableIrqWakeup(GPC_CPU_MODE_CTRL_Type *base, uint32_t irqId, bool enable)
{
    assert(irqId < (GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_COUNT * 32UL));

    uint32_t irqGroup = irqId / 32UL;
    uint32_t irqMask  = irqId % 32UL;

    if (true == enable)
    {
        base->CM_IRQ_WAKEUP_MASK[irqGroup] &= ~(1UL << irqMask);
    }
    else
    {
        base->CM_IRQ_WAKEUP_MASK[irqGroup] |= (1UL << irqMask);
    }
}

/*!
 * brief Get the status of the IRQ wakeup request.
 *
 * param base GPC CPU module base address.
 * param irqId ID of the IRQ, accessible range is 0-255.
 * return Indicate the IRQ request is asserted or not.
 */
bool GPC_CM_GetIrqWakeupStatus(GPC_CPU_MODE_CTRL_Type *base, uint32_t irqId)
{
    assert(irqId < (GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_COUNT * 32UL));

    uint32_t irqGroup = irqId / 32UL;
    uint32_t irqMask  = irqId % 32UL;
    bool irqStatus    = false;

    irqStatus = (((base->CM_IRQ_WAKEUP_STAT[irqGroup] >> irqMask) & 0x1UL) == 0x1UL) ? true : false;
    return irqStatus;
}

/*!
 * brief Config the cpu mode transition step.
 *
 * note This function can not config the setpoint sleep/wakeup operation for those
 * operation is controlled by setpoint control. This funcion can not config the standby
 * sleep/wakeup too, because those operation is controlled by standby controlled.
 *
 * param base GPC CPU module base address.
 * param step step type, refer to "gpc_cm_tran_step_t".
 * param config transition step configuration, refer to "gpc_tran_step_config_t".
 */
void GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_Type *base,
                                        gpc_cm_tran_step_t step,
                                        const gpc_tran_step_config_t *config)
{
    if (!((step >= kGPC_CM_SleepSP) && (step <= kGPC_CM_WakeupSP)))
    {
        uint32_t tmp32 = *(uint32_t *)((uint32_t)base + s_cmRegOffset[step]);

        if (config->enableStep)
        {
            tmp32 &= ~(GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_STEP_CNT_MASK |
                       GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_CNT_MODE_MASK);
            tmp32 |= GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_CNT_MODE(config->cntMode);
            if (config->cntMode != kGPC_StepCounterDisableMode)
            {
                tmp32 |= GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_STEP_CNT(config->stepCount);
            }
            tmp32 &= ~GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_MASK;
        }
        else
        {
            tmp32 |= GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_MASK;
        }
        *(uint32_t *)((uint32_t)base + s_cmRegOffset[step]) = tmp32;
    }
}

/*!
 * brief Request a set point transition before the CPU transfers into a sleep mode.
 *
 * This function triggers the set point transition during a CPU Sleep/wakeup event and selects which one the CMC want
 * to transfer to.
 *
 * param base GPC CPU module base address.
 * param setPointSleep The set point CPU want the system to transit to on next CPU platform sleep sequence.
 * param setPointWakeup The set point CPU want the system to transit to on next CPU platform wakeup sequence.
 * param wakeupSel Select the set point transition on the next CPU platform wakeup sequence.
 */
void GPC_CM_RequestSleepModeSetPointTransition(GPC_CPU_MODE_CTRL_Type *base,
                                               uint8_t setPointSleep,
                                               uint8_t setPointWakeup,
                                               gpc_cm_wakeup_sp_sel_t wakeupSel)
{
    uint32_t tmp32 = base->CM_SP_CTRL;

    tmp32 &= ~(GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_MASK | GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_MASK |
               GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_MASK | GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL_MASK);
    /* Config set point transition in the next sleep sequence. */
    tmp32 |=
        GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_EN_MASK | GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP(setPointSleep);
    /* Config set point transition in the next wakeup sequence. */
    tmp32 |= GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_EN_MASK |
             GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP(setPointWakeup) |
             GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL(wakeupSel);

    base->CM_SP_CTRL = tmp32;
}

/*!
 * brief Request a set point transition during run mode.
 *
 * This function triggers the set point transition and selects which one the CMC want to transfer to.
 *
 * param base GPC CPU module base address.
 * param setPointRun The set point CPU want the system to transit in the run mode.
 */
void GPC_CM_RequestRunModeSetPointTransition(GPC_CPU_MODE_CTRL_Type *base, uint8_t setPointRun)
{
    uint32_t tmp32 = base->CM_SP_CTRL;

    tmp32 &= ~(GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_MASK);
    tmp32 |= GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_MASK | GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN(setPointRun);

    base->CM_SP_CTRL = tmp32;
    while ((base->CM_SP_CTRL & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_MASK) != 0UL)
    {
    }
}

/*
 * brief Set the set point mapping value for each cpu mode.
 *
 * This function configures which set point is allowed when CPU enters RUN/WAIT/STOP/SUSPEND. If there are multiple
 * setpoints, use:
 * code
 *    map = kkGPC_SetPoint0 | kGPC_SetPoint1 | ... | kGPC_SetPoint15;
 * encode
 *
 * param base GPC CPU module base address.
 * param mode CPU mode. Refer to "gpc_cpu_mode_t".
 * param map Map value of the set point. Refer to "_gpc_setpoint_map".
 */
void GPC_CM_SetCpuModeSetPointMapping(GPC_CPU_MODE_CTRL_Type *base, gpc_cpu_mode_t mode, uint32_t map)
{
    /* Ensure the allowed set point is in the accessible range (0-15). */
    map = map & 0xFFFFUL;

    switch (mode)
    {
        case kGPC_RunMode:
            base->CM_RUN_MODE_MAPPING = map;
            break;
        case kGPC_WaitMode:
            base->CM_WAIT_MODE_MAPPING = map;
            break;
        case kGPC_StopMode:
            base->CM_STOP_MODE_MAPPING = map;
            break;
        case kGPC_SuspendMode:
            base->CM_SUSPEND_MODE_MAPPING = map;
            break;
        default:
            assert(false);
            break;
    }
}

/*
 * brief Request the chip into standby mode.
 *
 * param base GPC CPU module base address.
 * param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_RequestStandbyMode(GPC_CPU_MODE_CTRL_Type *base, const gpc_cpu_mode_t mode)
{
    assert(mode != kGPC_RunMode);

    switch (mode)
    {
        case kGPC_WaitMode:
            base->CM_STBY_CTRL |= GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT_MASK;
            break;
        case kGPC_StopMode:
            base->CM_STBY_CTRL |= GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP_MASK;
            break;
        case kGPC_SuspendMode:
            base->CM_STBY_CTRL |= GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND_MASK;
            break;
        default:
            /* This branch should never be hit. */
            break;
    }
}

/*
 * brief Clear the standby mode request.
 *
 * param base GPC CPU module base address.
 * param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_ClearStandbyModeRequest(GPC_CPU_MODE_CTRL_Type *base, const gpc_cpu_mode_t mode)
{
    assert(mode != kGPC_RunMode);

    switch (mode)
    {
        case kGPC_WaitMode:
            base->CM_STBY_CTRL &= ~GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT_MASK;
            break;
        case kGPC_StopMode:
            base->CM_STBY_CTRL &= ~GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP_MASK;
            break;
        case kGPC_SuspendMode:
            base->CM_STBY_CTRL &= ~GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND_MASK;
            break;
        default:
            /* This branch should never be hit. */
            break;
    }
}

/*!
 * brief Clears CPU module interrut status flags.
 *
 * param base GPC CPU module base address.
 * param mask The interrupt status flags to be cleared. Should be the OR'ed value of _gpc_cm_interrupt_status_flag.
 */
void GPC_CM_ClearInterruptStatusFlags(GPC_CPU_MODE_CTRL_Type *base, uint32_t mask)
{
    uint32_t temp32;

    temp32 = base->CM_INT_CTRL;
    temp32 &= ~(GPC_CM_ALL_INTERRUPT_STATUS);
    base->CM_INT_CTRL = (mask | temp32);
}

/*!
 * brief Config the set point transition step.
 *
 * param base GPC Setpoint controller base address.
 * param step step type, refer to "gpc_sp_tran_step_t".
 * param config transition step configuration, refer to "gpc_tran_step_config_t".
 */
void GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL_Type *base,
                                         gpc_sp_tran_step_t step,
                                         const gpc_tran_step_config_t *config)
{
    uint32_t tmp32 = *(uint32_t *)((uint32_t)base + s_spRegOffset[step]);

    if (config->enableStep)
    {
        tmp32 &=
            ~(GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_STEP_CNT_MASK | GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_CNT_MODE_MASK);
        tmp32 |= GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_CNT_MODE(config->cntMode);
        if (config->cntMode != kGPC_StepCounterDisableMode)
        {
            tmp32 |= GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_STEP_CNT(config->stepCount);
        }
        tmp32 &= ~GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE_MASK;
    }
    else
    {
        tmp32 |= GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE_MASK;
    }
    *(uint32_t *)((uint32_t)base + s_spRegOffset[step]) = tmp32;
}

/*!
 * brief Config the standby transition step.
 *
 * param base GPC Setpoint controller base address.
 * param step step type, refer to "gpc_stby_tran_step_t".
 * param config transition step configuration, refer to "gpc_tran_step_config_t".
 */
void GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL_Type *base,
                                          gpc_stby_tran_step_t step,
                                          const gpc_tran_step_config_t *config)
{
    uint32_t tmp32 = *(uint32_t *)((uint32_t)base + s_stbyRegOffset[step]);

    if (config->enableStep)
    {
        tmp32 &= ~(GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_STEP_CNT_MASK | GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_CNT_MODE_MASK);
        tmp32 |= GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_CNT_MODE(config->cntMode);
        if (config->cntMode != kGPC_StepCounterDisableMode)
        {
            tmp32 |= GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_STEP_CNT(config->stepCount);
        }
        tmp32 &= ~GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE_MASK;
    }
    else
    {
        tmp32 |= GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE_MASK;
    }
    *(uint32_t *)((uint32_t)base + s_stbyRegOffset[step]) = tmp32;
}
