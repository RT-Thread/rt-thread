/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_GPC_H_
#define _FSL_GPC_H_

#include "fsl_common.h"

/*!
 * @addtogroup gpc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief GPC driver version 2.2.0. */
#define FSL_GPC_RIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @}*/

#define GPC_RESERVED_USE_MACRO 0xFFFFFFFFU

/* GPC CPU module step control register offset. */
#define GPC_CM_SLEEP_SSAR_CTRL_OFFSET   (0x200)
#define GPC_CM_SLEEP_LPCG_CTRL_OFFSET   (0x208)
#define GPC_CM_SLEEP_PLL_CTRL_OFFSET    (0x210)
#define GPC_CM_SLEEP_ISO_CTRL_OFFSET    (0x218)
#define GPC_CM_SLEEP_RESET_CTRL_OFFSET  (0x220)
#define GPC_CM_SLEEP_POWER_CTRL_OFFSET  (0x228)
#define GPC_CM_WAKEUP_POWER_CTRL_OFFSET (0x290)
#define GPC_CM_WAKEUP_RESET_CTRL_OFFSET (0x298)
#define GPC_CM_WAKEUP_ISO_CTRL_OFFSET   (0x2A0)
#define GPC_CM_WAKEUP_PLL_CTRL_OFFSET   (0x2A8)
#define GPC_CM_WAKEUP_LPCG_CTRL_OFFSET  (0x2B0)
#define GPC_CM_WAKEUP_SSAR_CTRL_OFFSET  (0x2B8)

/* GPC set point module step control register offset. */
#define GPC_SP_SSAR_SAVE_CTRL_OFFSET    (0x100)
#define GPC_SP_LPCG_OFF_CTRL_OFFSET     (0x110)
#define GPC_SP_GROUP_DOWN_CTRL_OFFSET   (0x120)
#define GPC_SP_ROOT_DOWN_CTRL_OFFSET    (0x130)
#define GPC_SP_PLL_OFF_CTRL_OFFSET      (0x140)
#define GPC_SP_ISO_ON_CTRL_OFFSET       (0x150)
#define GPC_SP_RESET_EARLY_CTRL_OFFSET  (0x160)
#define GPC_SP_POWER_OFF_CTRL_OFFSET    (0x170)
#define GPC_SP_BIAS_OFF_CTRL_OFFSET     (0x180)
#define GPC_SP_BG_PLDO_OFF_CTRL_OFFSET  (0x190)
#define GPC_SP_LDO_PRE_CTRL_OFFSET      (0x1A0)
#define GPC_SP_DCDC_DOWN_CTRL_OFFSET    (0x1B0)
#define GPC_SP_DCDC_UP_CTRL_OFFSET      (0x2B0)
#define GPC_SP_LDO_POST_CTRL_OFFSET     (0x210)
#define GPC_SP_BG_PLDO_ON_CTRL_OFFSET   (0x220)
#define GPC_SP_BIAS_ON_CTRL_OFFSET      (0x230)
#define GPC_SP_POWER_ON_CTRL_OFFSET     (0x240)
#define GPC_SP_RESET_LATE_CTRL_OFFSET   (0x250)
#define GPC_SP_ISO_OFF_CTRL_OFFSET      (0x260)
#define GPC_SP_PLL_ON_CTRL_OFFSET       (0x270)
#define GPC_SP_ROOT_UP_CTRL_OFFSET      (0x280)
#define GPC_SP_GROUP_UP_CTRL_OFFSET     (0x290)
#define GPC_SP_LPCG_ON_CTRL_OFFSET      (0x2A0)
#define GPC_SP_SSAR_RESTORE_CTRL_OFFSET (0x2B0)

/* GPC standby module step control register offset. */
#define GPC_STBY_LPCG_IN_CTRL_OFFSET     (0xF0)
#define GPC_STBY_PLL_IN_CTRL_OFFSET      (0x100)
#define GPC_STBY_BIAS_IN_CTRL_OFFSET     (0x110)
#define GPC_STBY_PLDO_IN_CTRL_OFFSET     (0x120)
#define GPC_STBY_BANDGAP_IN_CTRL_OFFSET  (0x128)
#define GPC_STBY_LDO_IN_CTRL_OFFSET      (0x130)
#define GPC_STBY_DCDC_IN_CTRL_OFFSET     (0x140)
#define GPC_STBY_PMIC_IN_CTRL_OFFSET     (0x150)
#define GPC_STBY_PMIC_OUT_CTRL_OFFSET    (0x200)
#define GPC_STBY_DCDC_OUT_CTRL_OFFSET    (0x210)
#define GPC_STBY_LDO_OUT_CTRL_OFFSET     (0x220)
#define GPC_STBY_BANDGAP_OUT_CTRL_OFFSET (0x238)
#define GPC_STBY_PLDO_OUT_CTRL_OFFSET    (0x238)
#define GPC_STBY_BIAS_OUT_CTRL_OFFSET    (0x240)
#define GPC_STBY_PLL_OUT_CTRL_OFFSET     (0x250)
#define GPC_STBY_LPCG_OUT_CTRL_OFFSET    (0x260)

/* GPC CPU module step register offset. */
#define GPC_CM_STEP_REG_OFFSET                                                                               \
    {                                                                                                        \
        GPC_CM_SLEEP_SSAR_CTRL_OFFSET, GPC_CM_SLEEP_LPCG_CTRL_OFFSET, GPC_CM_SLEEP_PLL_CTRL_OFFSET,          \
            GPC_CM_SLEEP_ISO_CTRL_OFFSET, GPC_CM_SLEEP_RESET_CTRL_OFFSET, GPC_CM_SLEEP_POWER_CTRL_OFFSET,    \
            GPC_RESERVED_USE_MACRO, GPC_RESERVED_USE_MACRO, GPC_RESERVED_USE_MACRO, GPC_RESERVED_USE_MACRO,  \
            GPC_CM_WAKEUP_POWER_CTRL_OFFSET, GPC_CM_WAKEUP_RESET_CTRL_OFFSET, GPC_CM_WAKEUP_ISO_CTRL_OFFSET, \
            GPC_CM_WAKEUP_PLL_CTRL_OFFSET, GPC_CM_WAKEUP_LPCG_CTRL_OFFSET, GPC_CM_WAKEUP_SSAR_CTRL_OFFSET,   \
    }

/* GPC set point module step control register offset. */
#define GPC_SP_STEP_REG_OFFSET                                                                         \
    {                                                                                                  \
        GPC_SP_SSAR_SAVE_CTRL_OFFSET, GPC_SP_LPCG_OFF_CTRL_OFFSET, GPC_SP_GROUP_DOWN_CTRL_OFFSET,      \
            GPC_SP_ROOT_DOWN_CTRL_OFFSET, GPC_SP_PLL_OFF_CTRL_OFFSET, GPC_SP_ISO_ON_CTRL_OFFSET,       \
            GPC_SP_RESET_EARLY_CTRL_OFFSET, GPC_SP_POWER_OFF_CTRL_OFFSET, GPC_SP_BIAS_OFF_CTRL_OFFSET, \
            GPC_SP_BG_PLDO_OFF_CTRL_OFFSET, GPC_SP_LDO_PRE_CTRL_OFFSET, GPC_SP_DCDC_DOWN_CTRL_OFFSET,  \
            GPC_SP_DCDC_UP_CTRL_OFFSET, GPC_SP_LDO_POST_CTRL_OFFSET, GPC_SP_BG_PLDO_ON_CTRL_OFFSET,    \
            GPC_SP_BIAS_ON_CTRL_OFFSET, GPC_SP_POWER_ON_CTRL_OFFSET, GPC_SP_RESET_LATE_CTRL_OFFSET,    \
            GPC_SP_ISO_OFF_CTRL_OFFSET, GPC_SP_PLL_ON_CTRL_OFFSET, GPC_SP_ROOT_UP_CTRL_OFFSET,         \
            GPC_SP_GROUP_UP_CTRL_OFFSET, GPC_SP_LPCG_ON_CTRL_OFFSET, GPC_SP_SSAR_RESTORE_CTRL_OFFSET,  \
    }

/* GPC standby module step register offset. */
#define GPC_STBY_STEP_REG_OFFSET                                                                           \
    {                                                                                                      \
        GPC_STBY_LPCG_IN_CTRL_OFFSET, GPC_STBY_PLL_IN_CTRL_OFFSET, GPC_STBY_BIAS_IN_CTRL_OFFSET,           \
            GPC_STBY_PLDO_IN_CTRL_OFFSET, GPC_STBY_BANDGAP_IN_CTRL_OFFSET, GPC_STBY_LDO_IN_CTRL_OFFSET,    \
            GPC_STBY_DCDC_IN_CTRL_OFFSET, GPC_STBY_PMIC_IN_CTRL_OFFSET, GPC_STBY_PMIC_OUT_CTRL_OFFSET,     \
            GPC_STBY_DCDC_OUT_CTRL_OFFSET, GPC_STBY_LDO_OUT_CTRL_OFFSET, GPC_STBY_BANDGAP_OUT_CTRL_OFFSET, \
            GPC_STBY_PLDO_OUT_CTRL_OFFSET, GPC_STBY_BIAS_OUT_CTRL_OFFSET, GPC_STBY_PLL_OUT_CTRL_OFFSET,    \
            GPC_STBY_LPCG_OUT_CTRL_OFFSET,                                                                 \
    }

/* Make/Get status. */
/* Make the mask/shift value of GPC status register in a variable. */
#define GPC_STAT(mask, shift) (uint32_t)(((uint32_t)(shift) << 16UL) + ((uint32_t)(mask) >> (uint32_t)(shift)))

#define GPC_CM_ALL_INTERRUPT_STATUS                                     \
    (GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_MASK |  \
     GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_MASK | \
     GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_MASK)

/*! @brief _gpc_cm_non_irq_wakeup_request GPC Non-IRQ wakeup request. */
enum
{
    kGPC_CM_EventWakeupRequest =
        GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_EVENT_WAKEUP_MASK_MASK, /*!< Event wakeup request. */
    kGPC_CM_DebugWakeupRequest =
        GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK_MASK, /*!< Debug wakeup request. */
};

/* @brief _gpc_setpoint_map GPC setpoint map. */
enum
{
    kGPC_SetPoint0  = 1UL << 0UL,  /*!< GPC set point 0. */
    kGPC_SetPoint1  = 1UL << 1UL,  /*!< GPC set point 1. */
    kGPC_SetPoint2  = 1UL << 2UL,  /*!< GPC set point 2. */
    kGPC_SetPoint3  = 1UL << 3UL,  /*!< GPC set point 3. */
    kGPC_SetPoint4  = 1UL << 4UL,  /*!< GPC set point 4. */
    kGPC_SetPoint5  = 1UL << 5UL,  /*!< GPC set point 5. */
    kGPC_SetPoint6  = 1UL << 6UL,  /*!< GPC set point 6. */
    kGPC_SetPoint7  = 1UL << 7UL,  /*!< GPC set point 7. */
    kGPC_SetPoint8  = 1UL << 8UL,  /*!< GPC set point 8. */
    kGPC_SetPoint9  = 1UL << 9UL,  /*!< GPC set point 9. */
    kGPC_SetPoint10 = 1UL << 10UL, /*!< GPC set point 10. */
    kGPC_SetPoint11 = 1UL << 11UL, /*!< GPC set point 11. */
    kGPC_SetPoint12 = 1UL << 12UL, /*!< GPC set point 12. */
    kGPC_SetPoint13 = 1UL << 13UL, /*!< GPC set point 13. */
    kGPC_SetPoint14 = 1UL << 14UL, /*!< GPC set point 14. */
    kGPC_SetPoint15 = 1UL << 15UL, /*!< GPC set point 15. */
};

/*!
 * @brief _gpc_cm_interrupt_status_flag
 */
enum
{
    kGPC_CM_SoftSPNotAllowedStatusFlag  = GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_MASK,
    kGPC_CM_WaitSPNotAllowedStatusFlag  = GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_MASK,
    kGPC_CM_SleepSPNotAllowedStatusFlag = GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_MASK,
};

/*! @brief CPU standby mode status. */
typedef enum _gpc_cm_standby_mode_status
{
    kGPC_CM_SleepBusy = GPC_STAT(
        GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY_MASK,
        GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY_SHIFT), /*!< Indicate the CPU is busy entering standby mode. */
    kGPC_CM_WakeupBusy = GPC_STAT(
        GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY_MASK,
        GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY_SHIFT), /*!< Indicate the CPU is busy exiting standby mode. */
} gpc_cm_standby_mode_status_t;

/*! @brief CPU mode transition step in sleep/wakeup sequence. */
typedef enum _gpc_cm_tran_step
{
    kGPC_CM_SleepSsar   = 0UL,  /*!< SSAR (State Save And Restore) sleep step. */
    kGPC_CM_SleepLpcg   = 1UL,  /*!< LPCG (Low Power Clock Gating) sleep step. */
    kGPC_CM_SleepPll    = 2UL,  /*!< PLL sleep step. */
    kGPC_CM_SleepIso    = 3UL,  /*!< ISO (Isolation) sleep step. */
    kGPC_CM_SleepReset  = 4UL,  /*!< Reset sleep step. */
    kGPC_CM_SleepPower  = 5UL,  /*!< Power sleep step. */
    kGPC_CM_SleepSP     = 6UL,  /*!< Setpoint sleep step. Note that this step is controlled by setpoint controller. */
    kGPC_CM_SleepSTBY   = 7UL,  /*!< Standby sleep step. Note that this step is controlled by standby controller. */
    kGPC_CM_WakeupSTBY  = 8UL,  /*!< Standby wakeup step. Note that this step is controlled by standby controller. */
    kGPC_CM_WakeupSP    = 9UL,  /*!< Setpoint wakeup step. Note that this step is controlled by setpoint countroller. */
    kGPC_CM_WakeupPower = 10UL, /*!< Power wakeup step. */
    kGPC_CM_WakeupReset = 11UL, /*!< Reset wakeup step. */
    kGPC_CM_WakeupIso   = 12UL, /*!< ISO wakeup step. */
    kGPC_CM_WakeupPll   = 13UL, /*!< PLL wakeup step. */
    kGPC_CM_WakeupLpcg  = 14UL, /*!< LPCG wakeup step. */
    kGPC_CM_WakeupSsar  = 15UL, /*!< SSAR wakeup step. */
} gpc_cm_tran_step_t;

/*! @brief Step counter work mode. */
typedef enum _gpc_tran_step_counter_mode
{
    kGPC_StepCounterDisableMode =
        0UL, /*!< Counter disable mode: not use step counter, step completes once receiving step_done. */
    kGPC_StepCounterDelayMode =
        1UL, /*!< Counter delay mode: delay after receiving step_done, delay cycle number is STEP_CNT */
    kGPC_StepCounterIgnoreResponseMode = 2UL, /*!< Ignore step_done response, the counter starts to count once step
                                                    begins, when counter reaches STEP_CNT value, the step completes. */
    kGPC_StepCounterTimeOutMode = 3UL,        /*!< Time out mode, the counter starts to count once step begins, the step
                                                    completes when either step_done received or counting to STEP_CNT value. */
} gpc_tran_step_counter_mode_t;

/*! @brief GPC set point transition steps. */
typedef enum _gpc_sp_tran_step
{
    kGPC_SP_SsarSave         = 0UL,  /*!< SSAR save step. */
    kGPC_SP_LpcgOff          = 1UL,  /*!< LPCG off step. */
    kGPC_SP_GroupDown        = 2UL,  /*!< Group down step. */
    kGPC_SP_RootDown         = 3UL,  /*!< Root down step. */
    kGPC_SP_PllOff           = 4UL,  /*!< PLL off step. */
    kGPC_SP_IsoOn            = 5UL,  /*!< ISO on. */
    kGPC_SP_ResetEarly       = 6UL,  /*!< Reset early step. */
    kGPC_SP_PowerOff         = 7UL,  /*!< Power off step. */
    kGPC_SP_BiasOff          = 8UL,  /*!< Bias off step. */
    kGPC_SP_BandgapPllLdoOff = 9UL,  /*!< Bandgap and PLL_LDO off step. */
    kGPC_SP_LdoPre           = 10UL, /*!< LDO (Low-Dropout) pre step. */
    kGPC_SP_DcdcDown         = 11UL, /*!< DCDC down step. */
    kGPC_SP_DcdcUp           = 12UL, /*!< DCDC up step. */
    kGPC_SP_LdoPost          = 13UL, /*!< LDO post step. */
    kGPC_SP_BandgapPllLdoOn  = 14UL, /*!< Bandgap and PLL_LDO on step. */
    kGPC_SP_BiasOn           = 15UL, /*!< Bias on step. */
    kGPC_SP_PowerOn          = 16UL, /*!< Power on step. */
    kGPC_SP_ResetLate        = 17UL, /*!< Reset late step. */
    kGPC_SP_IsoOff           = 18UL, /*!< ISO off step. */
    kGPC_SP_PllOn            = 19UL, /*!< PLL on step */
    kGPC_SP_RootUp           = 20UL, /*!< Root up step. */
    kGPC_SP_GroupUp          = 21UL, /*!< Group up step. */
    kGPC_SP_LpcgOn           = 22UL, /*!< LPCG on step. */
    kGPC_SP_SsarRestore      = 23UL, /*!< SSAR restore step. */
} gpc_sp_tran_step_t;

/*! @brief CPU mode. */
typedef enum _gpc_cpu_mode
{
    kGPC_RunMode     = 0x0UL, /*!< Stay in RUN mode. */
    kGPC_WaitMode    = 0x1UL, /*!< Transit to WAIT mode. */
    kGPC_StopMode    = 0x2UL, /*!< Transit to STOP mode. */
    kGPC_SuspendMode = 0x3UL, /*!< Transit to SUSPEND mode. */
} gpc_cpu_mode_t;

/*! @brief Configuration for GPC transition step. */
typedef struct _gpc_tran_step_config
{
    uint32_t stepCount;                   /*!< Step count, which is depended on the value of cntMode. */
    gpc_tran_step_counter_mode_t cntMode; /*!< Step counter working mode. */
    bool enableStep;                      /*!< Enable the step. */
} gpc_tran_step_config_t;

/*! @brief CPU wakeup sequence setpoint options. */
typedef enum _gpc_cm_wakeup_sp_sel
{
    kGPC_CM_WakeupSetpoint =
        0UL, /*!< Request SP transition to CPU_SP_WAKEUP (param "setPointWakeup" in gpc_cm_sleep_sp_tran_config_t). */
    kGPC_CM_RequestPreviousSetpoint = 1UL, /*!< Request SP transition to the set point when the sleep event happens. */
} gpc_cm_wakeup_sp_sel_t;

/*! @brief GPC standby mode transition steps. */
typedef enum _gpc_stby_tran_step
{
    kGPC_STBY_LpcgIn     = 0UL,  /*!< LPCG in step. */
    kGPC_STBY_PllIn      = 1UL,  /*!< PLL in step. */
    kGPC_STBY_BiasIn     = 2UL,  /*!< Bias in step. */
    kGPC_STBY_PldoIn     = 3UL,  /*!< PLDO in step. */
    kGPC_STBY_BandgapIn  = 4UL,  /*!< Bandgap in step. */
    kGPC_STBY_LdoIn      = 5UL,  /*!< LDO in step. */
    kGPC_STBY_DcdcIn     = 6UL,  /*!< DCDC in step. */
    kGPC_STBY_PmicIn     = 7UL,  /*!< PMIC in step. */
    kGPC_STBY_PmicOut    = 8UL,  /*!< PMIC out step. */
    kGPC_STBY_DcdcOut    = 9UL,  /*!< DCDC out step. */
    kGPC_STBY_LdoOut     = 10UL, /*!< LDO out step. */
    kGPC_STBY_BandgapOut = 11UL, /*!< Bandgap out step. */
    kGPC_STBY_PldoOut    = 12UL, /*!< PLDO out step. */
    kGPC_STBY_BiasOut    = 13UL, /*!< Bias out step. */
    kGPC_STBY_PllOut     = 14UL, /*!< PLL out step. */
    kGPC_STBY_LpcgOut    = 15UL, /*!< LPCG out step. */
} gpc_stby_tran_step_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name CPU mode control
 * @{
 */

/*
 * @brief Hold core in sleep state.
 *
 * This function is used to hold the core in sleep state once it enters WFI, and until finishing wakeup sequence. If a
 * wakeup IRQ happens during the delay between core sleeps and core clock stops, the core will be woken up but GPC is on
 * sleep sequence and shut off the clock when core is processing the IRQ, this may leads to an unpredictable status.
 *
 * @param base GPC CPU module base address.
 */
static inline void GPC_CM_EnableCpuSleepHold(GPC_CPU_MODE_CTRL_Type *base, bool enable)
{
    if (enable)
    {
        base->CM_MISC |= GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN_MASK;
    }
    else
    {
        base->CM_MISC &= ~GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN_MASK;
    }
}

/*!
 * @brief Set the CPU mode on the next sleep event.
 *
 * This function configures the CPU mode that the CPU core will transmit to on next sleep event.
 *
 * @note This API must be called each time before entering sleep.
 *
 * @param base GPC CPU module base address.
 * @param mode The CPU mode that the core will transmit to, refer to "gpc_cpu_mode_t".
 */
static inline void GPC_CM_SetNextCpuMode(GPC_CPU_MODE_CTRL_Type *base, gpc_cpu_mode_t mode)
{
    base->CM_MODE_CTRL = (base->CM_MODE_CTRL & ~GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_MASK) |
                         GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET(mode);
}

/*!
 * @brief Get current CPU mode.
 *
 * @param base GPC CPU module base address.
 * @return The current CPU mode, in type of @ref gpc_cpu_mode_t.
 */
static inline gpc_cpu_mode_t GPC_CM_GetCurrentCpuMode(GPC_CPU_MODE_CTRL_Type *base)
{
    return (gpc_cpu_mode_t)(uint32_t)((base->CM_MODE_STAT & GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_MASK) >>
                                      GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_SHIFT);
}

/*!
 * @brief Get previous CPU mode.
 *
 * @param base GPC CPU module base address.
 * @return The previous CPU mode, in type of @ref gpc_cpu_mode_t.
 */
static inline gpc_cpu_mode_t GPC_CM_GetPreviousCpuMode(GPC_CPU_MODE_CTRL_Type *base)
{
    return (gpc_cpu_mode_t)(uint32_t)((base->CM_MODE_STAT & GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_MASK) >>
                                      GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_SHIFT);
}

/*!
 * @brief Enable IRQ wakeup request.
 *
 * This function enables the IRQ request which can wakeup the CPU platform.
 *
 * @param base GPC CPU module base address.
 * @param irqId ID of the IRQ, accessible range is 0-255.
 * @param enable Enable the IRQ request or not.
 */
void GPC_CM_EnableIrqWakeup(GPC_CPU_MODE_CTRL_Type *base, uint32_t irqId, bool enable);

/*!
 * @brief Enable Non-IRQ wakeup request.
 *
 * This function enables the non-IRQ request which can wakeup the CPU platform.
 *
 * @param base GPC CPU module base address.
 * @param mask Non-IRQ type, refer to "_gpc_cm_non_irq_wakeup_request".
 * @param enable Enable the Non-IRQ request or not.
 */
static inline void GPC_CM_EnableNonIrqWakeup(GPC_CPU_MODE_CTRL_Type *base, uint32_t mask, bool enable)
{
    assert(mask < 2UL);

    if (true == enable)
    {
        base->CM_NON_IRQ_WAKEUP_MASK &= ~mask;
    }
    else
    {
        base->CM_NON_IRQ_WAKEUP_MASK |= mask;
    }
}

/*!
 * @brief Get the status of the IRQ wakeup request.
 *
 * @param base GPC CPU module base address.
 * @param irqId ID of the IRQ, accessible range is 0-255.
 * @return Indicate the IRQ request is asserted or not.
 */
bool GPC_CM_GetIrqWakeupStatus(GPC_CPU_MODE_CTRL_Type *base, uint32_t irqId);

/*!
 * @brief Get the status of the Non-IRQ wakeup request.
 *
 * @param base GPC CPU module base address.
 * @param mask Non-IRQ type, refer to "_gpc_cm_non_irq_wakeup_request".
 * @return Indicate the Non-IRQ request is asserted or not.
 */
static inline bool GPC_CM_GetNonIrqWakeupStatus(GPC_CPU_MODE_CTRL_Type *base, uint32_t mask)
{
    return (mask == (base->CM_NON_IRQ_WAKEUP_STAT & mask));
}

/*!
 * @brief Config the cpu mode transition step.
 *
 * @note This function can not config the setpoint sleep/wakeup operation for those
 * operation is controlled by setpoint control. This funcion can not config the standby
 * sleep/wakeup too, because those operation is controlled by standby controlled.
 *
 * @param base GPC CPU module base address.
 * @param step step type, refer to "gpc_cm_tran_step_t".
 * @param config transition step configuration, refer to "gpc_tran_step_config_t".
 */
void GPC_CM_ConfigCpuModeTransitionStep(GPC_CPU_MODE_CTRL_Type *base,
                                        gpc_cm_tran_step_t step,
                                        const gpc_tran_step_config_t *config);

/*!
 * @brief Request a set point transition before the CPU transfers into a sleep mode.
 *
 * This function triggers the set point transition during a CPU Sleep/wakeup event and selects which one the CMC want
 * to transfer to.
 *
 * @param base GPC CPU module base address.
 * @param setPointSleep The set point CPU want the system to transit to on next CPU platform sleep sequence.
 * @param setPointWakeup The set point CPU want the system to transit to on next CPU platform wakeup sequence.
 * @param wakeupSel Select the set point transition on the next CPU platform wakeup sequence.
 */
void GPC_CM_RequestSleepModeSetPointTransition(GPC_CPU_MODE_CTRL_Type *base,
                                               uint8_t setPointSleep,
                                               uint8_t setPointWakeup,
                                               gpc_cm_wakeup_sp_sel_t wakeupSel);

/*!
 * @brief Request a set point transition during run mode.
 *
 * This function triggers the set point transition and selects which one the CMC want to transfer to.
 *
 * @param base GPC CPU module base address.
 * @param setPointRun The set point CPU want the system to transit in the run mode.
 */
void GPC_CM_RequestRunModeSetPointTransition(GPC_CPU_MODE_CTRL_Type *base, uint8_t setPointRun);

/*!
 * @brief Set the set point mapping value for each set point.
 *
 * This function configures which set point is allowed after current set point. If there are multiple setpoints, use:
 * @code
 *    map = kkGPC_SetPoint0 | kGPC_SetPoint1 | ... | kGPC_SetPoint15;
 * @endcode
 *
 * @param base GPC CPU module base address.
 * @param setPoint Set point index, available range is 0-15.
 * @param map Map value of the set point. Refer to "_gpc_setpoint_map".
 */
static inline void GPC_CM_SetSetPointMapping(GPC_CPU_MODE_CTRL_Type *base, uint32_t setPoint, uint32_t map)
{
    assert(setPoint < 16UL);

    base->CM_SP_MAPPING[setPoint] = (map & 0xFFFFUL);
}

/*!
 * @brief Set the set point mapping value for each cpu mode.
 *
 * This function configures which set point is allowed when CPU enters RUN/WAIT/STOP/SUSPEND. If there are multiple
 * setpoints, use:
 * @code
 *    map = kkGPC_SetPoint0 | kGPC_SetPoint1 | ... | kGPC_SetPoint15;
 * @endcode
 *
 * @param base GPC CPU module base address.
 * @param mode CPU mode. Refer to "gpc_cpu_mode_t".
 * @param map Map value of the set point. Refer to "_gpc_setpoint_map".
 */
void GPC_CM_SetCpuModeSetPointMapping(GPC_CPU_MODE_CTRL_Type *base, gpc_cpu_mode_t mode, uint32_t map);

/*!
 * @brief Request the chip into standby mode.
 *
 * @param base GPC CPU module base address.
 * @param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_RequestStandbyMode(GPC_CPU_MODE_CTRL_Type *base, const gpc_cpu_mode_t mode);

/*!
 * @brief Clear the standby mode request.
 *
 * @param base GPC CPU module base address.
 * @param mode CPU mode. Refer to "gpc_cpu_mode_t".
 */
void GPC_CM_ClearStandbyModeRequest(GPC_CPU_MODE_CTRL_Type *base, const gpc_cpu_mode_t mode);

/*!
 * @brief Get the status of the CPU standby mode transition.
 *
 * @param base GPC CPU module base address.
 * @param mask Standby mode transition status mask, refer to "gpc_cm_standby_mode_status_t".
 * @return Indicate the CPU's standby transition status.
 */
static inline bool GPC_CM_GetStandbyModeStatus(GPC_CPU_MODE_CTRL_Type *base, uint32_t mask)
{
    return (mask == (base->CM_STBY_CTRL & mask));
}

/*!
 * @brief Get the status flags of the GPC CPU module.
 *
 * @param base GPC CPU module base address.
 * @return The OR'ed value of status flags.
 */
static inline uint32_t GPC_CM_GetInterruptStatusFlags(GPC_CPU_MODE_CTRL_Type *base)
{
    return ((base->CM_INT_CTRL) & GPC_CM_ALL_INTERRUPT_STATUS);
}

/*!
 * @brief Clears CPU module interrut status flags.
 *
 * @param base GPC CPU module base address.
 * @param mask The interrupt status flags to be cleared. Should be the OR'ed value of _gpc_cm_interrupt_status_flag.
 */
void GPC_CM_ClearInterruptStatusFlags(GPC_CPU_MODE_CTRL_Type *base, uint32_t mask);

/*!
 * @}
 */

/*!
 * @name Set point request control
 * @{
 */

/*!
 * @brief Set the priority of set point.
 *
 * This function will configure the priority of the set point. If the result of API GPC_SP_GetAllowedSetPointMap() has
 * more than one valid bit, high priority set point will be taken.
 *
 * @param base GPC Setpoint controller base address.
 * @param setPoint Set point index, available range is 0-15.
 * @param priority Priority level, available range is 0-15.
 */
static inline void GPC_SP_SetSetpointPriority(GPC_SET_POINT_CTRL_Type *base, uint32_t setPoint, uint32_t priority)
{
    assert(priority < 16UL);
    assert(setPoint < 16UL);

    if (setPoint < 8UL)
    {
        base->SP_PRIORITY_0_7 |= (priority << (setPoint * 4UL));
    }
    else
    {
        base->SP_PRIORITY_8_15 |= (priority << ((setPoint - 8UL) * 4UL));
    }
}

/*!
 * @brief Config the set point transition step.
 *
 * @param base GPC Setpoint controller base address.
 * @param step step type, refer to "gpc_sp_tran_step_t".
 * @param config transition step configuration, refer to "gpc_tran_step_config_t".
 */
void GPC_SP_ConfigSetPointTransitionStep(GPC_SET_POINT_CTRL_Type *base,
                                         gpc_sp_tran_step_t step,
                                         const gpc_tran_step_config_t *config);

/*!
 * @brief Get system current setpoint, only valid when setpoint trans not busy.
 *
 * @param base GPC Setpoint controller base address.
 * @return The current setpoint number, range from 0 to 15.
 */
static inline uint8_t GPC_SP_GetCurrentSetPoint(GPC_SET_POINT_CTRL_Type *base)
{
    return (uint8_t)((base->SP_SYS_STAT & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT_MASK) >>
                     GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT_SHIFT);
}

/*!
 * @brief Get system previous setpoint, only valid when setpoint trans not busy.
 *
 * @param base GPC Setpoint controller base address.
 * @return The previous setpoint number, range from 0 to 15.
 */
static inline uint8_t GPC_SP_GetPreviousSetPoint(GPC_SET_POINT_CTRL_Type *base)
{
    return (uint8_t)((base->SP_SYS_STAT & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS_MASK) >>
                     GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS_SHIFT);
}

/*!
 * @brief Get target setpoint.
 *
 * @param base GPC Setpoint controller base address.
 * @return The target setpoint number, range from 0 to 15.
 */
static inline uint8_t GPC_SP_GetTargetSetPoint(GPC_SET_POINT_CTRL_Type *base)
{
    return (uint8_t)((base->SP_SYS_STAT & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET_MASK) >>
                     GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET_SHIFT);
}
/*!
 * @}
 */

/*!
 * @name Standby mode control
 * @{
 */

/*!
 * @brief Config the standby transition step.
 *
 * @param base GPC Setpoint controller base address.
 * @param step step type, refer to "gpc_stby_tran_step_t".
 * @param config transition step configuration, refer to "gpc_tran_step_config_t".
 */
void GPC_STBY_ConfigStandbyTransitionStep(GPC_STBY_CTRL_Type *base,
                                          gpc_stby_tran_step_t step,
                                          const gpc_tran_step_config_t *config);

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* _FSL_GPC_H_ */
