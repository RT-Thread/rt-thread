/*
 * Copyright 2019-2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pgmc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pgmc"
#endif

/*!
 * @brief The structure of MIF signal.
 */
typedef struct
{
    __IO uint32_t SIGNAL; /*!< MIF MLPL control of each signal. */
    __IO uint32_t DELAY;  /*!< MIF Delay of each signal */
    uint32_t RESERVED[2];
} PGMC_MIF_SIGNAL_Type;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Makes the BPC module controlled by the target CPU power mode(Such as Wait mode).
 *
 * This function makes the module controlled by four typical CPU power modes, It also configs the resource domain and
 * set memory low power level.
 *
 * param base PGMC basic power controller base address.
 * param mode Target CPU power mode.
 * param option The pointer of @ref pgmc_bpc_cpu_power_mode_option_t structure.
 */
void PGMC_BPC_ControlPowerDomainByCpuPowerMode(PGMC_BPC_Type *base,
                                               pgmc_cpu_mode_t mode,
                                               const pgmc_bpc_cpu_power_mode_option_t *option)
{
    assert(option != NULL);

    uint32_t tmp32 = base->BPC_SSAR_SAVE_CTRL;

    base->BPC_MODE = PGMC_BPC_BPC_MODE_DOMAIN_ASSIGN(option->assignDomain) |
                     PGMC_BPC_BPC_MODE_CTRL_MODE(kPGMC_ControlledByCpuPowerMode);
    switch (mode)
    {
        case kPGMC_RunMode:
            tmp32 |= PGMC_BPC_BPC_SSAR_SAVE_CTRL_SAVE_AT_RUN_MASK;
            break;
        case kPGMC_WaitMode:
            if (option->powerOff)
            {
                base->BPC_POWER_CTRL |= PGMC_BPC_BPC_POWER_CTRL_PWR_OFF_AT_WAIT_MASK;
            }
            tmp32 |= PGMC_BPC_BPC_SSAR_SAVE_CTRL_SAVE_AT_WAIT_MASK;
            break;
        case kPGMC_StopMode:
            if (option->powerOff)
            {
                base->BPC_POWER_CTRL |= PGMC_BPC_BPC_POWER_CTRL_PWR_OFF_AT_STOP_MASK;
            }
            tmp32 |= PGMC_BPC_BPC_SSAR_SAVE_CTRL_SAVE_AT_SUSPEND_MASK;
            break;
        case kPGMC_SuspendMode:
            if (option->powerOff)
            {
                base->BPC_POWER_CTRL |= PGMC_BPC_BPC_POWER_CTRL_PWR_OFF_AT_SUSPEND_MASK;
            }
            tmp32 |= PGMC_BPC_BPC_SSAR_SAVE_CTRL_SAVE_AT_SUSPEND_MASK;
            break;
        default:
            assert(false);
            break;
    }

    if (option->stateSave)
    {
        base->BPC_SSAR_SAVE_CTRL = tmp32;
    }
}

/*!
 * brief Makes the BPC module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports set memory lowe power level.
 *
 * note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * param base PGMC basic power controller base address.
 * param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * param option The pointer of @ref pgmc_bpc_setpoint_mode_option_t structure.
 */
void PGMC_BPC_ControlPowerDomainBySetPointMode(PGMC_BPC_Type *base,
                                               uint32_t setPointMap,
                                               const pgmc_bpc_setpoint_mode_option_t *option)
{
    assert(option != NULL);

    setPointMap &= 0xFFFFU;

    base->BPC_MODE = PGMC_BPC_BPC_MODE_CTRL_MODE(kPGMC_ControlledBySetPoint);
    if (option->powerOff)
    {
        base->BPC_POWER_CTRL |= PGMC_BPC_BPC_POWER_CTRL_PWR_OFF_AT_SP(setPointMap);
    }

    if (option->stateSave)
    {
        base->BPC_SSAR_SAVE_CTRL = PGMC_BPC_BPC_SSAR_SAVE_CTRL_SAVE_AT_SP(setPointMap);
    }
}

/*!
 * brief Controls the selected power domain by software mode.
 *
 * note The function is used to control power domain when the CPU is in RUN mode.
 *
 * param base PGMC basic power controller base address.
 * param powerOff Power On/Off power domain in software mode.
 *                  - \b true Power off the power domain in software mode.
 *                  - \b false Power on the power domain in software mode.
 */
void PGMC_BPC_ControlPowerDomainBySoftwareMode(PGMC_BPC_Type *base, bool powerOff)
{
    if (powerOff)
    {
        base->BPC_POWER_CTRL |= (PGMC_BPC_BPC_POWER_CTRL_PSW_OFF_SOFT_MASK | PGMC_BPC_BPC_POWER_CTRL_ISO_ON_SOFT_MASK);
    }
    else
    {
        base->BPC_POWER_CTRL |= (PGMC_BPC_BPC_POWER_CTRL_PSW_ON_SOFT_MASK | PGMC_BPC_BPC_POWER_CTRL_ISO_OFF_SOFT_MASK);
    }
}

/*!
 * brief Powers off the CPC core module by the target CPU power mode(Such as Wait mode).
 *
 * param base CPC CORE module base address.
 * param mode Target CPU power mode.
 */
void PGMC_CPC_CORE_PowerOffByCpuPowerMode(PGMC_CPC_Type *base, pgmc_cpu_mode_t mode)
{
    base->CPC_CORE_MODE = PGMC_CPC_CPC_CORE_MODE_CTRL_MODE(kPGMC_ControlledByCpuPowerMode);
    switch (mode)
    {
        case kPGMC_RunMode:
            break;
        case kPGMC_WaitMode:
            base->CPC_CORE_POWER_CTRL |= PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_WAIT_MASK;
            break;
        case kPGMC_StopMode:
            base->CPC_CORE_POWER_CTRL |= PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_STOP_MASK;
            break;
        case kPGMC_SuspendMode:
            base->CPC_CORE_POWER_CTRL |= PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_SUSPEND_MASK;
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Makes the CPC CACHE module controlled by the target CPU power mode(Such as Wait mode).
 *
 * This function makes the module controlled by four typical CPU power modes, it also can set memory low power level.
 *
 * param base CPC CACHE module base address.
 * param mode Target CPU power mode.
 * param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_CACHE_ControlByCpuPowerMode(PGMC_CPC_Type *base,
                                          pgmc_cpu_mode_t mode,
                                          pgmc_memory_low_power_level_t memoryLowPowerLevel)
{
    uint32_t temp32;

    base->CPC_CACHE_MODE = PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE(kPGMC_ControlledByCpuPowerMode);
    temp32               = base->CPC_CACHE_CM_CTRL;
    switch (mode)
    {
        case kPGMC_RunMode:
            temp32 &= ~PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN_MASK;
            base->CPC_CACHE_CM_CTRL = temp32 | PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN(memoryLowPowerLevel);
            break;
        case kPGMC_WaitMode:
            temp32 &= ~PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT_MASK;
            base->CPC_CACHE_CM_CTRL = temp32 | PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT(memoryLowPowerLevel);
            break;
        case kPGMC_StopMode:
            temp32 &= ~PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP_MASK;
            base->CPC_CACHE_CM_CTRL = temp32 | PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP(memoryLowPowerLevel);
            break;
        case kPGMC_SuspendMode:
            temp32 &= ~PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND_MASK;
            base->CPC_CACHE_CM_CTRL = temp32 | PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND(memoryLowPowerLevel);
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Makes the CPC CACHE module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports set memory lowe power level.
 *
 * note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * param base CPC CACHE module base address.
 * param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_CACHE_ControlBySetPointMode(PGMC_CPC_Type *base,
                                          uint32_t setPointMap,
                                          pgmc_memory_low_power_level_t memoryLowPowerLevel)
{
    uint32_t setPointIndex             = 0UL;
    uint32_t tmp32                     = 0UL;
    uint32_t regIndex                  = 0UL;
    volatile uint32_t *ptrMemSpCtrlReg = NULL;

    setPointMap &= 0xFFFFU;

    base->CPC_CACHE_MODE = PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE(kPGMC_ControlledBySetPoint);

    ptrMemSpCtrlReg = &(base->CPC_CACHE_SP_CTRL_0);
    for (regIndex = 0UL; regIndex < 2UL; regIndex++)
    {
        ptrMemSpCtrlReg += regIndex;
        tmp32 = *ptrMemSpCtrlReg;
        for (setPointIndex = 0UL; setPointIndex < 8UL; setPointIndex++)
        {
            if (0UL != (setPointMap & (1UL << ((regIndex * 8UL) + setPointIndex))))
            {
                tmp32 &= ~((uint32_t)PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP0_MASK << (setPointIndex * 4U));
                tmp32 |= ((uint32_t)memoryLowPowerLevel << (setPointIndex * 4U));
            }
        }
        *ptrMemSpCtrlReg = tmp32;
    }
}

/*!
 * brief Requests CPC cache module's memory low power level change by software mode.
 *
 * note If request memory low power level change, must wait the MLPL transition complete.
 *
 * param base CPC LMEM module base address.
 */
void PGMC_CPC_CACHE_TriggerMLPLSoftwareChange(PGMC_CPC_Type *base)
{
    base->CPC_CACHE_CM_CTRL |= PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT_MASK;

    /* If request software change, check the MLPL transition status. */
    while (0UL != ((base->CPC_CACHE_CM_CTRL) & PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT_MASK))
    {
    }
}

/*!
 * brief Makes the CPC LMEM module controlled by the target CPU power mode(Such as Wait mode).
 *
 * This function makes the module controlled by four typical CPU power modes, it also can set memory low power level.
 *
 * param base CPC LMEM module base address.
 * param mode Target CPU power mode.
 * param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_LMEM_ControlByCpuPowerMode(PGMC_CPC_Type *base,
                                         pgmc_cpu_mode_t mode,
                                         pgmc_memory_low_power_level_t memoryLowPowerLevel)
{
    uint32_t temp32;

    base->CPC_LMEM_MODE = PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE(kPGMC_ControlledByCpuPowerMode);

    temp32 = base->CPC_LMEM_CM_CTRL;
    switch (mode)
    {
        case kPGMC_RunMode:
            temp32 &= ~PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN_MASK;
            base->CPC_LMEM_CM_CTRL = temp32 | PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN(memoryLowPowerLevel);
            break;
        case kPGMC_WaitMode:
            temp32 &= ~PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT_MASK;
            base->CPC_LMEM_CM_CTRL = temp32 | PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT(memoryLowPowerLevel);
            break;
        case kPGMC_StopMode:
            temp32 &= ~PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP_MASK;
            base->CPC_LMEM_CM_CTRL = temp32 | PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP(memoryLowPowerLevel);
            break;
        case kPGMC_SuspendMode:
            temp32 &= ~PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND_MASK;
            base->CPC_LMEM_CM_CTRL = temp32 | PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND(memoryLowPowerLevel);
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Makes the CPC LMEM module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports set memory lowe power level.
 *
 * note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * param base CPC LMEM module base address.
 * param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_LMEM_ControlBySetPointMode(PGMC_CPC_Type *base,
                                         uint32_t setPointMap,
                                         pgmc_memory_low_power_level_t memoryLowPowerLevel)
{
    uint32_t setPointIndex             = 0UL;
    uint32_t tmp32                     = 0UL;
    uint32_t regIndex                  = 0UL;
    volatile uint32_t *ptrMemSpCtrlReg = NULL;

    setPointMap &= 0xFFFFU;

    base->CPC_LMEM_MODE = PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE(kPGMC_ControlledBySetPoint);

    ptrMemSpCtrlReg = &(base->CPC_LMEM_SP_CTRL_0);
    for (regIndex = 0UL; regIndex < 2UL; regIndex++)
    {
        ptrMemSpCtrlReg += regIndex;
        tmp32 = *ptrMemSpCtrlReg;
        for (setPointIndex = 0UL; setPointIndex < 8UL; setPointIndex++)
        {
            if (0UL != (setPointMap & (1UL << ((regIndex * 8UL) + setPointIndex))))
            {
                tmp32 &= ~((uint32_t)PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP0_MASK << (setPointIndex * 4U));
                tmp32 |= ((uint32_t)memoryLowPowerLevel << (setPointIndex * 4U));
            }
        }
        *ptrMemSpCtrlReg = tmp32;
    }
}

/*!
 * brief Requests CPC LMEM module's memory low power level change in software mode.
 *
 * note If request memory low power level change, must wait the MLPL transition complete.
 *
 * param base CPC LMEM module base address.
 */
void PGMC_CPC_LMEM_TriggerMLPLSoftwareChange(PGMC_CPC_Type *base)
{
    base->CPC_LMEM_CM_CTRL |= PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT_MASK;

    /* If request software change, check the MLPL transition status. */
    while (0UL != ((base->CPC_LMEM_CM_CTRL) & PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT_MASK))
    {
    }
}

/*!
 * brief Sets the behaviour of each signal(Such as Sleep signal) in MIF.
 *
 * note To control the memory low power operation, this function must be invoked after selecting the
 *       memory low power level.
 *       Use case:
 *        code
 *              PGMC_BPC_ControlPowerDomainByCpuPowerMode(PGMC_BPC0_BASE, kPGMC_WaitMode, kPGMC_CM7Core,
 *                  kPGMC_MLPLSleep, false);
 *              PGMC_MIF_SetSignalBehaviour(PGMC_BPC0_MIF_BASE, kPGMC_MLPLSleep, kPGMC_AssertSleepSignal);
 *        endcode
 *
 * param base PGMC MIF peripheral base address.
 * param memoryLevel The selected memory low power level. For details please refer to @ref
 * pgmc_memory_low_power_level_t.
 * param mask The mask of MIF signal behaviour. Should be the OR'ed value of @ref _pgmc_mif_signal_behaviour
 */
void PGMC_MIF_SetSignalBehaviour(PGMC_MIF_Type *base, pgmc_memory_low_power_level_t memoryLevel, uint32_t mask)
{
    uint8_t signalIndex           = 0U;
    uint32_t temp32               = 0U;
    PGMC_MIF_SIGNAL_Type *MIF_SIG = (PGMC_MIF_SIGNAL_Type *)(uint32_t)(&(base->MIF_MLPL_SLEEP));

    for (signalIndex = 0U; signalIndex < 11U; signalIndex++)
    {
        temp32 = MIF_SIG[signalIndex].SIGNAL;
        temp32 &= ~(1UL << (uint32_t)memoryLevel);
        temp32 |= ((uint32_t)(mask & (1UL << signalIndex)) << (uint32_t)memoryLevel);
        MIF_SIG[signalIndex].SIGNAL = temp32;
    }
}

/*!
 * brief Makes the PMIC module controlled by the target CPU power mode(Such as Wait mode).
 *
 * param base PMIC module base address.
 * param mode Target CPU power mode.
 */
void PGMC_PPC_ControlByCpuPowerMode(PGMC_PPC_Type *base, pgmc_cpu_mode_t mode)
{
    base->PPC_MODE = PGMC_PPC_PPC_MODE_CTRL_MODE(kPGMC_ControlledByCpuPowerMode);
    switch (mode)
    {
        case kPGMC_RunMode:
            break;
        case kPGMC_WaitMode:
            base->PPC_STBY_CM_CTRL |= PGMC_PPC_PPC_STBY_CM_CTRL_STBY_ON_AT_WAIT_MASK;
            break;
        case kPGMC_StopMode:
            base->PPC_STBY_CM_CTRL |= PGMC_PPC_PPC_STBY_CM_CTRL_STBY_ON_AT_STOP_MASK;
            break;
        case kPGMC_SuspendMode:
            base->PPC_STBY_CM_CTRL |= PGMC_PPC_PPC_STBY_CM_CTRL_STBY_ON_AT_SUSPEND_MASK;
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Makes the PMIC module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports PMIC standby on.
 *
 * note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * param base PMIC module base address.
 * param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * param enableStandby true: PMIC standby on when system enters set point number and system is in standby mode.
 *                      false: PMIC standby on when system enters set point number
 */
void PGMC_PPC_ControlBySetPointMode(PGMC_PPC_Type *base, uint32_t setPointMap, bool enableStandby)
{
    setPointMap &= 0xFFFFU;

    base->PPC_MODE = PGMC_PPC_PPC_MODE_CTRL_MODE(kPGMC_ControlledBySetPoint);

    if (enableStandby)
    {
        base->PPC_STBY_SP_CTRL = (setPointMap << PGMC_PPC_PPC_STBY_SP_CTRL_STBY_ON_AT_SP_SLEEP_SHIFT);
    }
    else
    {
        base->PPC_STBY_SP_CTRL = setPointMap;
    }
}
