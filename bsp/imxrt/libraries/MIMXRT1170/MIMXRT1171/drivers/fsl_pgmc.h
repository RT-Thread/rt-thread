/*
 * Copyright 2019-2021,2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PGMC_H_
#define _FSL_PGMC_H_

#include "fsl_common.h"

/*!
 * @addtogroup PGMC
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief PGMC driver version 2.1.2. */
#define FSL_PGMC_RIVER_VERSION (MAKE_VERSION(2, 1, 2))
/*@}*/

/*! @brief The enumeration of setpoint.
 * @anchor _pgmc_setpoint_map
 */
enum
{
    kPGMC_SetPoint0  = 1UL << 0UL,  /*!< The mask of set point0. */
    kPGMC_SetPoint1  = 1UL << 1UL,  /*!< The mask of set point1. */
    kPGMC_SetPoint2  = 1UL << 2UL,  /*!< The mask of set point2. */
    kPGMC_SetPoint3  = 1UL << 3UL,  /*!< The mask of set point3. */
    kPGMC_SetPoint4  = 1UL << 4UL,  /*!< The mask of set point4. */
    kPGMC_SetPoint5  = 1UL << 5UL,  /*!< The mask of set point5. */
    kPGMC_SetPoint6  = 1UL << 6UL,  /*!< The mask of set point6. */
    kPGMC_SetPoint7  = 1UL << 7UL,  /*!< The mask of set point7. */
    kPGMC_SetPoint8  = 1UL << 8UL,  /*!< The mask of set point8. */
    kPGMC_SetPoint9  = 1UL << 9UL,  /*!< The mask of set point9. */
    kPGMC_SetPoint10 = 1UL << 10UL, /*!< The mask of set point10. */
    kPGMC_SetPoint11 = 1UL << 11UL, /*!< The mask of set point11. */
    kPGMC_SetPoint12 = 1UL << 12UL, /*!< The mask of set point12. */
    kPGMC_SetPoint13 = 1UL << 13UL, /*!< The mask of set point13. */
    kPGMC_SetPoint14 = 1UL << 14UL, /*!< The mask of set point14. */
    kPGMC_SetPoint15 = 1UL << 15UL, /*!< The mask of set point15. */
};

/*!
 * @brief The enumeration of MIF signal behaviour(Such as Sleep Signal, Standby Signal, and so on).
 */
enum _pgmc_mif_signal_behaviour
{
    kPGMC_AssertSleepSignal               = 1U << 0U,  /*!< Assert Sleep signal. */
    kPGMC_AssertInputGateSignal           = 1U << 1U,  /*!< Assert InputGate signal. */
    kPGMC_AssetLowSpeedSignal             = 1U << 2U,  /*!< Assert LowSpeed signal. */
    kPGMC_AssertHighSpeedSignal           = 1U << 3U,  /*!< Assert HighSpeed signal. */
    kPGMC_AssertStandbySignal             = 1U << 4U,  /*!< Assert Standby signal. */
    kPGMC_AssertArrayPowerDownSignal      = 1U << 5U,  /*!< Assert ArrayPowerDown signal. */
    kPGMC_AssertPeripheralPowerDownSignal = 1U << 6U,  /*!< Assert PeripheralPowerDown signal. */
    kPGMC_AssertInitnSignal               = 1U << 7U,  /*!< Assert Initn signal. */
    kPGMC_AssertSwitch1OffSignal          = 1U << 8U,  /*!< Assert Switch1Off signal. */
    kPGMC_AssertSwitch2OffSignal          = 1U << 9U,  /*!< Assert Switch2Off signal. */
    kPGMC_AssertIsoSignal                 = 1U << 10U, /*!< Assert Iso_en signal. */
};

/*!
 * @brief PGMC BPC assign domain enumeration.
 */
typedef enum _pgmc_bpc_assign_domain
{
    kPGMC_CM7Core = 0U, /*!< CM7 Core domain. */
    kPGMC_CM4Core = 1U  /*!< CM4 Core domain. */
} pgmc_bpc_assign_domain_t;

/*! @brief CPU mode. */
typedef enum _pgmc_cpu_mode
{
    kPGMC_RunMode     = 0x0UL, /*!< RUN mode. */
    kPGMC_WaitMode    = 0x1UL, /*!< WAIT mode. */
    kPGMC_StopMode    = 0x2UL, /*!< STOP mode. */
    kPGMC_SuspendMode = 0x3UL, /*!< SUSPEND mode. */
} pgmc_cpu_mode_t;

/*! @brief PGMC control modes. */
typedef enum _pgmc_control_mode
{
    kPGMC_DisableLowPowerControl   = 0UL,
    kPGMC_ControlledByCpuPowerMode = 1UL,
    kPGMC_ControlledBySetPoint     = 2UL,
} pgmc_control_mode_t;

/*!
 * @brief The enumeration of memory low power level.
 */
typedef enum _pgmc_memory_low_power_level
{
    kPGMC_MLPLHighSpeed    = 1U,  /*!< Memory low power level: High speed. */
    kPGMC_MLPLNormal       = 3U,  /*!< Memory low power level: Normal. */
    kPGMC_MLPLLowSpeed     = 4U,  /*!< Memory low power level: Low Speed. */
    kPGMC_MLPLInputGating  = 5U,  /*!< Memory low power level: Input Gating. */
    kPGMC_MLPLStandby      = 6U,  /*!< Memory low power level: Standby. */
    kPGMC_MLPLSleep        = 8U,  /*!< Memory low power level: Sleep. */
    kPGMC_MLPLArrOnPerOff  = 9U,  /*!< Memory low power level: Arr on per off. */
    kPGMC_MLPLArrOffPerOn  = 10U, /*!< Memory low power level: Arr off per on. */
    kPGMC_MLPLArrOffPerOff = 11U, /*!< Memory low power level: Arr off per off. */
    kPGMC_MLPLSw2          = 13U, /*!< Memory low power level: SW2. */
    kPGMC_MLPLSw2PerOff    = 14U, /*!< Memory low power level: SW2 Per off. */
    kPGMC_MLPLSw1PerOff    = 15U, /*!< Memory low power level: SW1 Per off. */
} pgmc_memory_low_power_level_t;

/*!
 * @brief The enumeration of MIF signal.
 */
typedef enum _pgmc_mif_signal
{
    kPGMC_SleepSignal               = 0U,  /*!< MIF Sleep signal. */
    kPGMC_InputGateSignal           = 1U,  /*!< MIF InputGate signal. */
    kPGMC_LowSpeedSignal            = 2U,  /*!< MIF LowSpeed signal. */
    kPGMC_HighSpeedSignal           = 3U,  /*!< MIF HighSpeed signal. */
    kPGMC_StandbySignal             = 4U,  /*!< MIF Standby signal. */
    kPGMC_ArrayPowerDownSignal      = 5U,  /*!< MIF ArrayPowerDown signal. */
    kPGMC_PeripheralPowerDownSignal = 6U,  /*!< MIF PeripheralPowerDown signal. */
    kPGMC_InitnSignal               = 7U,  /*!< MIF Initn signal. */
    kPGMC_Switch1OffSignal          = 8U,  /*!< MIF Switch1Off signal. */
    kPGMC_Switch2OffSignal          = 9U,  /*!< MIF Switch2Off signal. */
    kPGMC_IsoSignal                 = 10U, /*!< MIF Iso_en signal. */
} pgmc_mif_signal_t;

/*!
 * @brief The control option of the power domain controlled by CPU power mode.
 */
typedef struct _pgmc_bpc_cpu_power_mode_option
{
    pgmc_bpc_assign_domain_t assignDomain; /*!< Domain assignment of the BPC. The power mode of the selected core domain
                                              will control the selected power domain. */
    bool stateSave; /*!< Request save the state of power domain before entering target power mode.
                            - \b true Save data when domain enter the selected mode.
                            - \b false Do not save data when domain enter the selected mode. */
    bool powerOff;  /*!< Request power off the power domain.
                            - \b true Power off the power domain when enter the selected mode.
                            - \b false Do not power off the power domain when enter the selected mode. */
} pgmc_bpc_cpu_power_mode_option_t;

/*!
 * @brief The control option of the power domain controlled by setpoint mode.
 */
typedef struct _pgmc_bpc_setpoint_mode_option
{
    bool stateSave; /*!< Request save the state of power domain before entering target setpoint.
                            - \b true Save data when domain enter the selected setpoint.
                            - \b false Do not save data when domain enter the selected setpoint. */
    bool powerOff;  /*!< Request power off the power domain.
                            - \b true Power off the power domain when enter the selected setpoint.
                            - \b false Do not power off the power domain when enter the selected setpoint. */
} pgmc_bpc_setpoint_mode_option_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Basic Power Controller Related Interfaces
 * @{
 */

/*!
 * @brief Makes the BPC module controlled by the target CPU power mode, such as Wait mode.
 *
 * This function makes the module controlled by four typical CPU power modes, It also configs the resource domain and
 * set memory low power level.
 *
 * @param base PGMC basic power controller base address.
 * @param mode Target CPU power mode.
 * @param option The pointer of @ref pgmc_bpc_cpu_power_mode_option_t structure.
 */
void PGMC_BPC_ControlPowerDomainByCpuPowerMode(PGMC_BPC_Type *base,
                                               pgmc_cpu_mode_t mode,
                                               const pgmc_bpc_cpu_power_mode_option_t *option);

/*!
 * @brief Makes the BPC module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports set memory lowe power level.
 *
 * @note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * @param base PGMC basic power controller base address.
 * @param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * @param option The pointer of @ref pgmc_bpc_setpoint_mode_option_t structure.
 */
void PGMC_BPC_ControlPowerDomainBySetPointMode(PGMC_BPC_Type *base,
                                               uint32_t setPointMap,
                                               const pgmc_bpc_setpoint_mode_option_t *option);

/*!
 * @brief Controls the selected power domain by software mode.
 *
 * @note The function is used to control power domain when the CPU is in RUN mode.
 *
 * @param base PGMC basic power controller base address.
 * @param powerOff Power On/Off power domain in software mode.
 *                  - \b true Power off the power domain in software mode.
 *                  - \b false Power on the power domain in software mode.
 */
void PGMC_BPC_ControlPowerDomainBySoftwareMode(PGMC_BPC_Type *base, bool powerOff);

/*!
 * @brief Disables low power mode control.
 *
 * @param base PGMC basic power controller base address.
 */
static inline void PGMC_BPC_DisableLowPower(PGMC_BPC_Type *base)
{
    base->BPC_MODE = PGMC_BPC_BPC_MODE_CTRL_MODE(kPGMC_DisableLowPowerControl);
}

/*!
 * @brief Requests power domain state restore at run mode.
 *
 * @param base PGMC basic power controller base address.
 */
static inline void PGMC_BPC_RequestStateRestoreAtRunMode(PGMC_BPC_Type *base)
{
    base->BPC_SSAR_RESTORE_CTRL |= PGMC_BPC_BPC_SSAR_RESTORE_CTRL_RESTORE_AT_RUN_MASK;
}

/*!
 * @brief Requests power domain state restore when enters the selected set points.
 *
 * @note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 * @param base PGMC basic power controller base address.
 * @param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 */
static inline void PGMC_BPC_RequestStateRestoreAtSetPoint(PGMC_BPC_Type *base, uint32_t setPointMap)
{
    base->BPC_SSAR_RESTORE_CTRL |= PGMC_BPC_BPC_SSAR_RESTORE_CTRL_RESTORE_AT_SP(setPointMap & 0xFFFFU);
}

/*!
 * @brief Allows user mode access or not for the BPC module.
 *
 * @note If locked access related settings, the setting via this function is useless.
 *
 * @param base PGMC basic power controller base address.
 * @param enable Used to control whether allow user mode access.
 *           - \b true Allow both privilege and user mode to access CPU mode control registers.
 *           - \b false Allow only privilege mode to access CPU mode control registers.
 */
static inline void PGMC_BPC_AllowUserModeAccess(PGMC_BPC_Type *base, bool enable)
{
    if (enable)
    {
        base->BPC_AUTHEN_CTRL |= PGMC_BPC_BPC_AUTHEN_CTRL_USER_MASK;
    }
    else
    {
        base->BPC_AUTHEN_CTRL &= ~PGMC_BPC_BPC_AUTHEN_CTRL_USER_MASK;
    }
}

/*!
 * @brief Allows non-secure mode access or not for the BPC module.
 *
 * @note If locked access related settings, the setting via this function is useless.
 *
 * @param base PGMC basic power controller base address.
 * @param enable Used to control whether allow non-secure mode to access CPU mode control registers.
 *           - \b true Allow both secure and non-secure mode to access CPU mode control registers.
 *           - \b false Allow only secure mode to access CPU mode control registers.
 */
static inline void PGMC_BPC_AllowNonSecureModeAccess(PGMC_BPC_Type *base, bool enable)
{
    if (enable)
    {
        base->BPC_AUTHEN_CTRL |= PGMC_BPC_BPC_AUTHEN_CTRL_NONSECURE_MASK;
    }
    else
    {
        base->BPC_AUTHEN_CTRL &= ~PGMC_BPC_BPC_AUTHEN_CTRL_NONSECURE_MASK;
    }
}

/*!
 * @brief Locks access related settings for the BPC module, including Secure access setting and user access setting.
 *
 * @note This function used to lock access related settings. After locked the related bit field
 * can not be written unless POR.
 *
 * @param base PGMC basic power controller base address.
 */
static inline void PGMC_BPC_LockAccessSetting(PGMC_BPC_Type *base)
{
    base->BPC_AUTHEN_CTRL |= PGMC_BPC_BPC_AUTHEN_CTRL_LOCK_SETTING_MASK;
}

/*!
 * @brief Sets the corrsponding domain ID that can access CPU mode control registers for the BPC module.
 *
 * @note If locked the domain ID white list, the setting via this function is useless.
 *
 * @param base PGMC basic power controller base address.
 * @param domainId Should be the OR'ed value of @ref pgmc_bpc_assign_domain_t.
 */
static inline void PGMC_BPC_SetDomainIdWhiteList(PGMC_BPC_Type *base, uint8_t domainId)
{
    base->BPC_AUTHEN_CTRL = (base->BPC_AUTHEN_CTRL & (~PGMC_BPC_BPC_AUTHEN_CTRL_WHITE_LIST_MASK)) |
                            PGMC_BPC_BPC_AUTHEN_CTRL_WHITE_LIST(domainId);
}

/*!
 * @brief Locks the value of Domain ID white list for the BPC module.
 *
 * @note After locked the domain ID white list can not be written again unless POR.
 *
 * @param base PGMC basic power controller base address.
 */
static inline void PGMC_BPC_LockDomainIDWhiteList(PGMC_BPC_Type *base)
{
    base->BPC_AUTHEN_CTRL |= PGMC_BPC_BPC_AUTHEN_CTRL_LOCK_LIST_MASK;
}

/*!
 * @brief Locks low power configuration fields for the BPC module.
 *
 * @note After locked the low power configurations fields can not be updated unless POR.
 *
 * @param base PGMC basic power controller base address.
 */
static inline void PGMC_BPC_LockLowPowerConfigurationFields(PGMC_BPC_Type *base)
{
    base->BPC_AUTHEN_CTRL |= PGMC_BPC_BPC_AUTHEN_CTRL_LOCK_CFG_MASK;
}

/*!
 * @}
 */

/*!
 * @name CPU Power Controller Related Interfaces
 * @{
 */

/*!
 * @brief Powers off the CPC core module by the target CPU power mode, such as Wait mode.
 *
 * @param base CPC CORE module base address.
 * @param mode Target CPU power mode.
 */
void PGMC_CPC_CORE_PowerOffByCpuPowerMode(PGMC_CPC_Type *base, pgmc_cpu_mode_t mode);

/*!
 * @brief Powers off/on the CPC core module by the software.
 *
 * @param base CPC CORE module base address.
 * @param powerOff Used to power off/on the CPC core module.
 *              - \b true Power off the CPC core module.
 *              - \b false Power on the CPC core module.
 */
static inline void PGMC_CPC_CORE_PowerOffBySoftwareMode(PGMC_CPC_Type *base, bool powerOff)
{
    if (powerOff)
    {
        base->CPC_CORE_POWER_CTRL |=
            (PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_OFF_SOFT_MASK | PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_ON_SOFT_MASK);
    }
    else
    {
        base->CPC_CORE_POWER_CTRL |=
            (PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_OFF_SOFT_MASK | PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_ON_SOFT_MASK);
    }
}

/*!
 * @brief Disables low power mode control, the CPU core will not be affected by any low power modes.
 *
 * @param base CPC CORE module base address.
 */
static inline void PGMC_CPC_CORE_DisableLowPower(PGMC_CPC_Type *base)
{
    base->CPC_CORE_MODE = PGMC_CPC_CPC_CORE_MODE_CTRL_MODE(kPGMC_DisableLowPowerControl);
}

/*!
 * @brief Makes the CPC CACHE module controlled by the target CPU power mode, such as Wait mode.
 *
 * This function makes the module controlled by four typical CPU power modes, it also can set memory low power level.
 *
 * @param base CPC CACHE module base address.
 * @param mode Target CPU power mode.
 * @param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_CACHE_ControlByCpuPowerMode(PGMC_CPC_Type *base,
                                          pgmc_cpu_mode_t mode,
                                          pgmc_memory_low_power_level_t memoryLowPowerLevel);

/*!
 * @brief Makes the CPC CACHE module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports set memory lowe power level.
 *
 * @note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * @param base CPC CACHE module base address.
 * @param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * @param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_CACHE_ControlBySetPointMode(PGMC_CPC_Type *base,
                                          uint32_t setPointMap,
                                          pgmc_memory_low_power_level_t memoryLowPowerLevel);

/*!
 * @brief Disables low power mode control, so the cache will not be affected by any low power modes.
 *
 * @param base CPC CACHE module base address.
 */
static inline void PGMC_CPC_CACHE_DisableLowPower(PGMC_CPC_Type *base)
{
    base->CPC_CACHE_MODE = PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE(kPGMC_DisableLowPowerControl);
}

/*!
 * @brief Requests CPC cache module's memory low power level change by software mode.
 *
 * @note If request memory low power level change, must wait the MLPL transition complete.
 *
 * @param base CPC LMEM module base address.
 */
void PGMC_CPC_CACHE_TriggerMLPLSoftwareChange(PGMC_CPC_Type *base);

/*!
 * @brief Makes the CPC LMEM module controlled by the target CPU power mode, such as Wait mode.
 *
 * This function makes the module controlled by four typical CPU power modes, it also can set memory low power level.
 *
 * @param base CPC LMEM module base address.
 * @param mode Target CPU power mode.
 * @param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_LMEM_ControlByCpuPowerMode(PGMC_CPC_Type *base,
                                         pgmc_cpu_mode_t mode,
                                         pgmc_memory_low_power_level_t memoryLowPowerLevel);

/*!
 * @brief Makes the CPC LMEM module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports set memory lowe power level.
 *
 * @note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * @param base CPC LMEM module base address.
 * @param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * @param memoryLowPowerLevel Memory low power level.
 */
void PGMC_CPC_LMEM_ControlBySetPointMode(PGMC_CPC_Type *base,
                                         uint32_t setPointMap,
                                         pgmc_memory_low_power_level_t memoryLowPowerLevel);

/*!
 * @brief Disables low power mode control, so that the CPC LMEM will not be affected by any low power modes.
 *
 * @param base CPC LMEM module base address.
 */
static inline void PGMC_CPC_LMEM_DisableLowPower(PGMC_CPC_Type *base)
{
    base->CPC_LMEM_MODE = PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE(kPGMC_DisableLowPowerControl);
}

/*!
 * @brief Requests CPC LMEM module's memory low power level change in software mode.
 *
 * @note If request memory low power level change, must wait the MLPL transition complete.
 *
 * @param base CPC LMEM module base address.
 */
void PGMC_CPC_LMEM_TriggerMLPLSoftwareChange(PGMC_CPC_Type *base);

/*!
 * @brief Allows user mode access or not for the CPC module.
 *
 * @note If locked access related settings, the setting via this function is useless.
 *
 * @param base CPC LMEM module base address.
 * @param enable Used to control whether allow user mode access.
 *           - \b true Allow both privilege and user mode to access CPU mode control registers.
 *           - \b false Allow only privilege mode to access CPU mode control registers.
 */
static inline void PGMC_CPC_AllowUserModeAccess(PGMC_CPC_Type *base, bool enable)
{
    if (enable)
    {
        base->CPC_AUTHEN_CTRL |= PGMC_CPC_CPC_AUTHEN_CTRL_USER_MASK;
    }
    else
    {
        base->CPC_AUTHEN_CTRL &= ~PGMC_CPC_CPC_AUTHEN_CTRL_USER_MASK;
    }
}

/*!
 * @brief Allows non-secure mode access or not for the CPC module.
 *
 * @note If locked access related settings, the setting via this function is useless.
 *
 * @param base CPC LMEM module base address.
 * @param enable Used to control whether allow non-secure mode to access CPU mode control registers.
 *           - \b true Allow both secure and non-secure mode to access CPU mode control registers.
 *           - \b false Allow only secure mode to access CPU mode control registers.
 */
static inline void PGMC_CPC_AllowNonSecureModeAccess(PGMC_CPC_Type *base, bool enable)
{
    if (enable)
    {
        base->CPC_AUTHEN_CTRL |= PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE_MASK;
    }
    else
    {
        base->CPC_AUTHEN_CTRL &= ~PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE_MASK;
    }
}

/*!
 * @brief Locks access related settings, including secure access setting and user access setting, for the CPC module.
 *
 * @note This function used to lock access related settings. After locked the related bit field
 * can not be written unless POR.
 *
 * @param base CPC LMEM module base address.
 */
static inline void PGMC_CPC_LockAccessSetting(PGMC_CPC_Type *base)
{
    base->CPC_AUTHEN_CTRL |= PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_SETTING_MASK;
}

/*!
 * @brief Sets the corrsponding domain ID that can access CPU mode control registers for the CPC module.
 *
 * @note If the domain ID whitelist is locked, the setting via this function is useless.
 *
 * @param base CPC LMEM module base address.
 * @param domainId Should be the OR'ed value of @ref pgmc_bpc_assign_domain_t.
 */
static inline void PGMC_CPC_SetDomainIdWhiteList(PGMC_CPC_Type *base, uint8_t domainId)
{
    base->CPC_AUTHEN_CTRL = (base->CPC_AUTHEN_CTRL & (~PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST_MASK)) |
                            PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST(domainId);
}

/*!
 * @brief Locks the value of Domain ID white list for CPC module.
 *
 * @note After locked the domain ID white list can not be written again unless POR.
 *
 * @param base CPC LMEM module base address.
 */
static inline void PGMC_CPC_LockDomainIDWhiteList(PGMC_CPC_Type *base)
{
    base->CPC_AUTHEN_CTRL |= PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_LIST_MASK;
}

/*!
 * @brief Locks CPC realted low power configuration fields for CPC module.
 *
 * @note After locked the low power configurations fields can not be updated unless POR.
 *
 * @param base CPC LMEM module base address.
 */
static inline void PGMC_CPC_LockLowPowerConfigurationFields(PGMC_CPC_Type *base)
{
    base->CPC_AUTHEN_CTRL |= PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_CFG_MASK;
}

/*!
 * @}
 */

/*!
 * @name MIF Module Related APIs
 * @{
 */

/*!
 * @brief Sets the behaviour of each signal in MIF, such as Sleep signal.
 *
 * @note To control the memory low power operation, this function must be invoked after selecting the
 *       memory low power level.
 *       Use case:
 *        @code
 *              PGMC_BPC_ControlPowerDomainByCpuPowerMode(PGMC_BPC0_BASE, kPGMC_WaitMode, kPGMC_CM7Core,
 *                  kPGMC_MLPLSleep, false);
 *              PGMC_MIF_SetSignalBehaviour(PGMC_BPC0_MIF_BASE, kPGMC_MLPLSleep, kPGMC_AssertSleepSignal);
 *        @endcode
 *
 * @param base PGMC MIF peripheral base address.
 * @param memoryLevel The selected memory low power level. For details please refer to @ref
 * pgmc_memory_low_power_level_t.
 * @param mask The mask of MIF signal behaviour. Should be the OR'ed value of @ref _pgmc_mif_signal_behaviour
 */
void PGMC_MIF_SetSignalBehaviour(PGMC_MIF_Type *base, pgmc_memory_low_power_level_t memoryLevel, uint32_t mask);

/*!
 * @brief Locks MIF realted low power configuration fields for MIF module.
 *
 * @note After locked the low power configurations fields can not be updated unless POR.
 *
 * @param base PGMC MIF peripheral base address.
 */
static inline void PGMC_MIF_LockLowPowerConfigurationFields(PGMC_MIF_Type *base)
{
    base->MIF_AUTHEN_CTRL |= PGMC_MIF_MIF_AUTHEN_CTRL_LOCK_CFG_MASK;
}

/*! @} */

/*!
 * @name PMIC Power Related Interfaces
 * @{
 */

/*!
 * @brief Trigger PMIC standby ON/OFF.
 *
 * @param base PMIC module base address.
 * @param enable Trigger on/off PMIC standby.
 *          - \b true Trigger PMIC standby ON.
 *          - \b false Trigger PMIC standby OFF.
 */
static inline void PGMC_PPC_TriggerPMICStandbySoftMode(PGMC_PPC_Type *base, bool enable)
{
    if (enable)
    {
        base->PPC_STBY_CM_CTRL |= PGMC_PPC_PPC_STBY_CM_CTRL_STBY_ON_SOFT_MASK;
    }
    else
    {
        base->PPC_STBY_CM_CTRL |= PGMC_PPC_PPC_STBY_CM_CTRL_STBY_OFF_SOFT_MASK;
    }
}

/*!
 * @brief Makes the PMIC module controlled by the target CPU power mode, such as Wait mode.
 *
 * @param base PMIC module base address.
 * @param mode Target CPU power mode.
 */
void PGMC_PPC_ControlByCpuPowerMode(PGMC_PPC_Type *base, pgmc_cpu_mode_t mode);

/*!
 * @brief Makes the PMIC module controlled by the target set points.
 *
 * This function makes the module controlled by specific set point, It also supports PMIC standby on.
 *
 * @note When setting more than one set point, use "|" between the map values in @ref _pgmc_setpoint_map.
 *
 * @param base PMIC module base address.
 * @param setPointMap Should be the OR'ed value of @ref _pgmc_setpoint_map.
 * @param enableStandby true: PMIC standby on when system enters set point number and system is in standby mode.
 *                      false: PMIC standby on when system enters set point number
 */
void PGMC_PPC_ControlBySetPointMode(PGMC_PPC_Type *base, uint32_t setPointMap, bool enableStandby);

/*!
 * @brief Disables low power mode control.
 *
 * @param base PMIC module bsase address.
 */
static inline void PGMC_PPC_DisableLowPower(PGMC_PPC_Type *base)
{
    base->PPC_MODE = PGMC_PPC_PPC_MODE_CTRL_MODE(kPGMC_DisableLowPowerControl);
}

/*!
 * @brief Allows user mode access or not for PMIC module.
 *
 * @note If locked access related settings, the setting via this function is useless.
 *
 * @param base PMIC module base address.
 * @param enable Used to control whether allow user mode access.
 *           - \b true Allow both privilege and user mode to access CPU mode control registers.
 *           - \b false Allow only privilege mode to access CPU mode control registers.
 */
static inline void PGMC_PPC_AllowUserModeAccess(PGMC_PPC_Type *base, bool enable)
{
    if (enable)
    {
        base->PPC_AUTHEN_CTRL |= PGMC_PPC_PPC_AUTHEN_CTRL_USER_MASK;
    }
    else
    {
        base->PPC_AUTHEN_CTRL &= ~PGMC_PPC_PPC_AUTHEN_CTRL_USER_MASK;
    }
}

/*!
 * @brief Allows non-secure mode access or not for the PMIC module.
 *
 * @note If locked access related settings, the setting via this function is useless.
 *
 * @param base PMIC module base address.
 * @param enable Used to control whether allow non-secure mode to access CPU mode control registers.
 *           - \b true Allow both secure and non-secure mode to access CPU mode control registers.
 *           - \b false Allow only secure mode to access CPU mode control registers.
 */
static inline void PGMC_PPC_AllowNonSecureModeAccess(PGMC_PPC_Type *base, bool enable)
{
    if (enable)
    {
        base->PPC_AUTHEN_CTRL |= PGMC_PPC_PPC_AUTHEN_CTRL_NONSECURE_MASK;
    }
    else
    {
        base->PPC_AUTHEN_CTRL &= ~PGMC_PPC_PPC_AUTHEN_CTRL_NONSECURE_MASK;
    }
}

/*!
 * @brief Locks access related settings, including secure access setting and user access setting, for the PMIC module.
 *
 * @note This function used to lock access related settings. After locked the related bit field
 * can not be written unless POR.
 *
 * @param base PMIC module base address.
 */
static inline void PGMC_PPC_LockAccessSetting(PGMC_PPC_Type *base)
{
    base->PPC_AUTHEN_CTRL |= PGMC_PPC_PPC_AUTHEN_CTRL_LOCK_SETTING_MASK;
}

/*!
 * @brief Sets the corrsponding domain ID that can access CPU mode control registers for the PMIC module.
 *
 * @note If the domain ID whitelist is locked, the setting via this function is useless.
 *
 * @param base PMIC module base address.
 * @param domainId Should be the OR'ed value of @ref pgmc_bpc_assign_domain_t.
 */
static inline void PGMC_PPC_SetDomainIdWhiteList(PGMC_PPC_Type *base, uint8_t domainId)
{
    base->PPC_AUTHEN_CTRL = (base->PPC_AUTHEN_CTRL & (~PGMC_PPC_PPC_AUTHEN_CTRL_WHITE_LIST_MASK)) |
                            PGMC_PPC_PPC_AUTHEN_CTRL_WHITE_LIST(domainId);
}

/*!
 * @brief Locks the value of Domain ID white list for the PMIC module.
 *
 * @note After locked the domain ID white list can not be written again unless POR.
 *
 * @param base PMIC module base address.
 */
static inline void PGMC_PPC_LockDomainIDWhiteList(PGMC_PPC_Type *base)
{
    base->PPC_AUTHEN_CTRL |= PGMC_PPC_PPC_AUTHEN_CTRL_LOCK_LIST_MASK;
}

/*!
 * @brief Locks low power configuration fields for the PMIC module.
 *
 * @note After locked the low power configurations fields can not be updated unless POR.
 *
 * @param base PMIC module base address.
 */
static inline void PGMC_PPC_LockLowPowerConfigurationFields(PGMC_PPC_Type *base)
{
    base->PPC_AUTHEN_CTRL |= PGMC_PPC_PPC_AUTHEN_CTRL_LOCK_CFG_MASK;
}

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* _FSL_PGMC_H_ */
