/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_VBAT_H_
#define _FSL_VBAT_H_

#include "fsl_common.h"

/*!
 * @addtogroup mcx_vbat
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief VBAT driver version 2.0.0. */
#define FSL_VBAT_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!
 * @brief The enumeration of VBAT module status.
 */
enum
{
    kStatus_VBAT_Fro16kNotEnabled = MAKE_STATUS(kStatusGroup_VBAT, 0),      /*!< Internal 16kHz free running
                                                                                 oscillator not enabled. */
    kStatus_VBAT_BandgapNotEnabled     = MAKE_STATUS(kStatusGroup_VBAT, 1), /*!< Bandgap not enabled. */
    kStatus_VBAT_WrongCapacitanceValue = MAKE_STATUS(kStatusGroup_VBAT, 2), /*!< Wrong capacitance for
                                                                                selected oscillator mode. */
};

/*!
 * @brief The enumeration of VBAT status flags.
 *
 * @anchor vbat_status_flag_t
 */
enum _vbat_status_flag
{
    kVBAT_StatusFlagPORDetect     = VBAT_STATUSA_POR_DET_MASK,     /*!< VBAT domain has been reset */
    kVBAT_StatusFlagWakeupPin     = VBAT_STATUSA_WAKEUP_FLAG_MASK, /*!< A falling edge is detected on the wakeup pin. */
    kVBAT_StatusFlagBandgapTimer0 = VBAT_STATUSA_TIMER0_FLAG_MASK, /*!< Bandgap Timer0 period reached. */
    kVBAT_StatusFlagBandgapTimer1 = VBAT_STATUSA_TIMER1_FLAG_MASK, /*!< Bandgap Timer1 period reached. */
    kVBAT_StatusFlagLdoReady      = VBAT_STATUSA_LDO_RDY_MASK,     /*!< LDO is enabled and ready. */
    kVBAT_StatusFlagOsc32kReady   = VBAT_STATUSA_OSC_RDY_MASK,     /*!< OSC32k is enabled and clock is ready. */
    kVBAT_StatusFlagConfigDetect  = VBAT_STATUSA_CONFIG_DET_MASK,  /*!< Configuration error detected. */
    kVBAT_StatusFlagInterrupt0Detect = VBAT_STATUSA_IRQ0_DET_MASK, /*!< Interrupt 0 asserted. */
    kVBAT_StatusFlagInterrupt1Detect = VBAT_STATUSA_IRQ1_DET_MASK, /*!< Interrupt 1 asserted. */
    kVBAT_StatusFlagInterrupt2Detect = VBAT_STATUSA_IRQ2_DET_MASK, /*!< Interrupt 2 asserted. */
    kVBAT_StatusFlagInterrupt3Detect = VBAT_STATUSA_IRQ3_DET_MASK, /*!< Interrupt 2 asserted. */
};

/*!
 * @brief The enumeration of VBAT interrupt enable.
 *
 * @anchor vbat_interrupt_enable_t
 */
enum _vbat_interrupt_enable
{
    kVBAT_InterruptEnablePORDetect = VBAT_IRQENA_POR_DET_MASK,         /*!< Enable POR detect interrupt. */
    kVBAT_InterruptEnableWakeupPin = VBAT_IRQENA_WAKEUP_FLAG_MASK,     /*!< Enable the interrupt when a falling edge is
                                                                           detected on the wakeup pin. */
    kVBAT_InterruptEnableBandgapTimer0 = VBAT_IRQENA_TIMER0_FLAG_MASK, /*!< Enable the interrupt if Bandgap
                                                                           Timer0 period reached. */
    kVBAT_InterruptEnableBandgapTimer1 = VBAT_IRQENA_TIMER1_FLAG_MASK, /*!< Enable the interrupt if Bandgap
                                                                           Timer1 period reached. */
    kVBAT_InterruptEnableLdoReady    = VBAT_IRQENA_LDO_RDY_MASK,       /*!< Enable LDO ready interrupt. */
    kVBAT_InterruptEnableOsc32kReady = VBAT_IRQENA_OSC_RDY_MASK,       /*!< Enable OSC32K ready interrupt. */
    kVBAT_InterruptEnableConfigDetect =
        VBAT_IRQENA_CONFIG_DET_MASK,                             /*!< Enable configuration error detected interrupt. */
    kVBAT_InterruptEnableInterrupt0 = VBAT_IRQENA_IRQ0_DET_MASK, /*!< Enable the interrupt0. */
    kVBAT_InterruptEnableInterrupt1 = VBAT_IRQENA_IRQ1_DET_MASK, /*!< Enable the interrupt1. */
    kVBAT_InterruptEnableInterrupt2 = VBAT_IRQENA_IRQ2_DET_MASK, /*!< Enable the interrupt2. */
    kVBAT_InterruptEnableInterrupt3 = VBAT_IRQENA_IRQ3_DET_MASK, /*!< Enable the interrupt3. */

    kVBAT_AllInterruptsEnable =
        (VBAT_IRQENA_POR_DET_MASK | VBAT_IRQENA_WAKEUP_FLAG_MASK | VBAT_IRQENA_TIMER0_FLAG_MASK |
         VBAT_IRQENA_TIMER1_FLAG_MASK | VBAT_IRQENA_LDO_RDY_MASK | VBAT_IRQENA_OSC_RDY_MASK |
         VBAT_IRQENA_CONFIG_DET_MASK | VBAT_IRQENA_IRQ0_DET_MASK | VBAT_IRQENA_IRQ1_DET_MASK |
         VBAT_IRQENA_IRQ2_DET_MASK | VBAT_IRQENA_IRQ3_DET_MASK), /*!< Enable all interrupts. */
};

/*!
 * @brief The enumeration of VBAT wakeup enable.
 *
 * @anchor vbat_wakeup_enable_t
 */
enum _vbat_wakeup_enable
{
    kVBAT_WakeupEnablePORDetect = VBAT_WAKENA_POR_DET_MASK,         /*!< Enable POR detect wakeup. */
    kVBAT_WakeupEnableWakeupPin = VBAT_WAKENA_WAKEUP_FLAG_MASK,     /*!< Enable wakeup feature when a falling edge is
                                                                        detected on the wakeup pin. */
    kVBAT_WakeupEnableBandgapTimer0 = VBAT_WAKENA_TIMER0_FLAG_MASK, /*!< Enable wakeup feature when bandgap
                                                                        timer0 period reached. */
    kVBAT_WakeupEnableBandgapTimer1 = VBAT_WAKENA_TIMER1_FLAG_MASK, /*!< Enable wakeup feature when bandgap
                                                                        timer1 period reached. */
    kVBAT_WakeupEnableLdoReady    = VBAT_WAKENA_LDO_RDY_MASK,       /*!< Enable wakeup when LDO ready. */
    kVBAT_WakeupEnableOsc32kReady = VBAT_WAKENA_OSC_RDY_MASK,       /*!< Enable wakeup when OSC32k ready. */
    kVBAT_WakeupEnableConfigDetect = VBAT_WAKENA_CONFIG_DET_MASK,   /*!< Enable wakeup when
                                                                        configuration error detected. */
    kVBAT_WakeupEnableInterrupt0 = VBAT_WAKENA_IRQ0_DET_MASK, /*!< Enable wakeup when interrupt0 asserted. */
    kVBAT_WakeupEnableInterrupt1 = VBAT_WAKENA_IRQ1_DET_MASK, /*!< Enable wakeup when interrupt1 asserted. */
    kVBAT_WakeupEnableInterrupt2 = VBAT_WAKENA_IRQ2_DET_MASK, /*!< Enable wakeup when interrupt2 asserted. */
    kVBAT_WakeupEnableInterrupt3 = VBAT_WAKENA_IRQ3_DET_MASK, /*!< Enable wakeup when interrupt3 asserted. */

    kVBAT_AllWakeupsEnable = (VBAT_WAKENA_POR_DET_MASK | VBAT_WAKENA_WAKEUP_FLAG_MASK | VBAT_WAKENA_TIMER0_FLAG_MASK |
                              VBAT_WAKENA_TIMER1_FLAG_MASK | VBAT_WAKENA_LDO_RDY_MASK | VBAT_WAKENA_OSC_RDY_MASK |
                              VBAT_WAKENA_CONFIG_DET_MASK | VBAT_WAKENA_IRQ0_DET_MASK | VBAT_WAKENA_IRQ1_DET_MASK |
                              VBAT_WAKENA_IRQ2_DET_MASK | VBAT_WAKENA_IRQ3_DET_MASK), /*!< Enable all wakeup. */
};

/*!
 * @brief The enumeration of bandgap timer id, VBAT support two bandgap timers.
 *
 * @anchor vbat_bandgap_timer_id_t
 */
enum _vbat_bandgap_timer_id
{
    kVBAT_BandgapTimer0 = 1U << 0U, /*!< Bandgap Timer0. */
    kVBAT_BandgapTimer1 = 1U << 1U, /*!< Bandgap Timer1. */
};

/*!
 * @brief The enumeration of connections for OSC32K/FRO32K output clock to other modules.
 *
 * @anchor vbat_clock_enable_t
 */
enum _vbat_clock_enable
{
    kVBAT_EnableClockToVddBat  = 1U << 0U, /*!< Enable OSC32K/FRO32K to VDD_BAT power domain. */
    kVBAT_EnableClockToVddSys  = 1U << 1U, /*!< Enable OSC32K/FRO32K to VDD_SYS power domain. */
    kVBAT_EnableClockToVddWake = 1U << 2U, /*!< Enable OSC32K/FRO32K to VDD_WAKE power domain. */
    kVBAT_EnableClockToVddMain = 1U << 3U, /*!< Enable OSC32K/FRO32K to VDD_MAIN power domain. */
};

/*!
 * @brief The enumeration of SRAM arrays that controlled by VBAT.
 * @anchor vbat_ram_array_t
 */
enum _vbat_ram_array
{
    kVBAT_SramArray0 = 1U << 0U, /*!< Specify SRAM array0 that controlled by VBAT. */
    kVBAT_SramArray1 = 1U << 1U, /*!< Specify SRAM array1 that controlled by VBAT. */
    kVBAT_SramArray2 = 1U << 2U, /*!< Specify SRAM array2 that controlled by VBAT. */
    kVBAT_SramArray3 = 1U << 3U, /*!< Specify SRAM array3 that controlled by VBAT. */
};

/*!
 * @brief The enumeration of bandgap refresh period.
 */
typedef enum _vbat_bandgap_refresh_period
{
    kVBAT_BandgapRefresh7P8125ms = 0U, /*!< Bandgap refresh every 7.8125ms. */
    kVBAT_BandgapRefresh15P625ms = 1U, /*!< Bandgap refresh every 15.625ms. */
    kVBAT_BandgapRefresh31P25ms  = 2U, /*!< Bandgap refresh every 31.25ms. */
    kVBAT_BandgapRefresh62P5ms   = 3U, /*!< Bandgap refresh every 62.5ms. */
} vbat_bandgap_refresh_period_t;

/*!
 * @brief The enumeration of bandgap timer0 timeout period.
 */
typedef enum _vbat_bandgap_timer0_timeout_period
{
    kVBAT_BangapTimer0Timeout1s      = 0U, /*!< Bandgap timer0 timerout every 1s. */
    kVBAT_BangapTimer0Timeout500ms   = 1U, /*!< Bandgap timer0 timerout every 500ms. */
    kVBAT_BangapTimer0Timeout250ms   = 2U, /*!< Bandgap timer0 timerout every 250ms. */
    kVBAT_BangapTimer0Timeout125ms   = 3U, /*!< Bandgap timer0 timerout every 125ms. */
    kVBAT_BangapTimer0Timeout62P5ms  = 4U, /*!< Bandgap timer0 timerout every 62.5ms. */
    kVBAT_BangapTimer0Timeout31P25ms = 5U, /*!< Bandgap timer0 timerout every 31.25ms. */
} vbat_bandgap_timer0_timeout_period_t;

/*!
 * @brief The enumeration of osc32k operate mode, including Bypass mode, low power switched mode and so on.
 */
typedef enum _vbat_osc32k_operate_mode
{
    kVBAT_Osc32kEnabledToTransconductanceMode = 0U, /*!< Set to transconductance mode. */
    kVBAT_Osc32kEnabledToLowPowerBackupMode   = 1U, /*!< Set to low power backup mode. */
    kVBAT_Osc32kEnabledToLowPowerSwitchedMode = 2U, /*!< Set to low power switched mode. */
} vbat_osc32k_operate_mode_t;

/*!
 * @brief The enumeration of OSC32K load capacitance.
 */
typedef enum _vbat_osc32k_load_capacitance_select
{
    kVBAT_Osc32kCrystalLoadCap0pF =
        0U,                         /*!< Internal capacitance bank is enabled, set the internal capacitance to 0 pF. */
    kVBAT_Osc32kCrystalLoadCap2pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 2 pF. */
    kVBAT_Osc32kCrystalLoadCap4pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 4 pF. */
    kVBAT_Osc32kCrystalLoadCap6pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 6 pF. */
    kVBAT_Osc32kCrystalLoadCap8pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 8 pF. */
    kVBAT_Osc32kCrystalLoadCap10pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 10 pF. */
    kVBAT_Osc32kCrystalLoadCap12pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 12 pF. */
    kVBAT_Osc32kCrystalLoadCap14pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 14 pF. */
    kVBAT_Osc32kCrystalLoadCap16pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 16 pF. */
    kVBAT_Osc32kCrystalLoadCap18pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 18 pF. */
    kVBAT_Osc32kCrystalLoadCap20pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 20 pF. */
    kVBAT_Osc32kCrystalLoadCap22pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 22 pF. */
    kVBAT_Osc32kCrystalLoadCap24pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 24 pF. */
    kVBAT_Osc32kCrystalLoadCap26pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 26 pF. */
    kVBAT_Osc32kCrystalLoadCap28pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 28 pF. */
    kVBAT_Osc32kCrystalLoadCap30pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 30 pF. */
    kVBAT_Osc32kCrystalLoadCapBankDisabled = 0xF0U, /*!< Internal capacitance bank is disabled. */
} vbat_osc32k_load_capacitance_select_t;

/*!
 * @brief The enumeration of start-up time of the oscillator.
 */
typedef enum _vbat_osc32k_start_up_time
{
    kVBAT_Osc32kStartUpTime8Sec = 0U, /*!< Configure the start-up time as 8 seconds. */
    kVBAT_Osc32kStartUpTime4Sec,      /*!< Configure the start-up time as 4 seconds. */
    kVBAT_Osc32kStartUpTime2Sec,      /*!< Configure the start-up time as 2 seconds. */
    kVBAT_Osc32kStartUpTime1Sec,      /*!< Configure the start-up time as 1 seconds. */
    kVBAT_Osc32kStartUpTime0P5Sec,    /*!< Configure the start-up time as 0.5 seconds. */
    kVBAT_Osc32kStartUpTime0P25Sec,   /*!< Configure the start-up time as 0.25 seconds. */
    kVBAT_Osc32kStartUpTime0P125Sec,  /*!< Configure the start-up time as 0.125 seconds. */
    kVBAT_Osc32kStartUpTime0P5MSec,   /*!< Configure the start-up time as 0.5 milliseconds. */
} vbat_osc32k_start_up_time_t;

/*!
 * @brief The enumeration of VBAT module supplies.
 */
typedef enum _vbat_internal_module_supply
{
    kVBAT_ModuleSuppliedByVddBat = 0U, /*!< VDD_BAT supplies VBAT modules. */
    kVBAT_ModuleSuppliedByVddSys = 1U, /*!< VDD_SYS supplies VBAT modules. */
} vbat_internal_module_supply_t;

/*!
 * @brief The structure of internal 16kHz free running oscillator attributes.
 */
typedef struct _vbat_fro16k_config
{
    bool enableFRO16k;              /*!< Enable/disable internal 16kHz free running oscillator. */
    uint8_t enabledConnectionsMask; /*!< The mask of connected modules to enable FRO16k clock output.  */
} vbat_fro16k_config_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FRO16K Control Interfaces
 * @{
 */

/*!
 * @brief Configure internal 16kHz free running oscillator, including enabel FRO16k, gate FRO16k output.
 *
 * @param base VBAT peripheral base address.
 * @param config Pointer to @ref vbat_fro16k_config_t structure.
 */
void VBAT_ConfigFRO16k(VBAT_Type *base, const vbat_fro16k_config_t *config);

/*!
 * @brief Enable/disable internal 16kHz free running oscillator.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable 16kHz FRO.
 *          - \b true Enable internal 16kHz free running oscillator.
 *          - \b false Disable internal 16kHz free running oscillator.
 */
static inline void VBAT_EnableFRO16k(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->FROCTLA |= VBAT_FROCTLA_FRO_EN_MASK;
        base->FROCTLB &= ~VBAT_FROCTLB_INVERSE_MASK;
    }
    else
    {
        base->FROCTLA &= ~VBAT_FROCTLA_FRO_EN_MASK;
        base->FROCTLB |= VBAT_FROCTLB_INVERSE_MASK;
    }
}

/*!
 * @brief Check if internal 16kHz free running oscillator is enabled.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval true The internal 16kHz Free running oscillator is enabled.
 * @retval false The internal 16kHz Free running oscillator is enabled.
 */
static inline bool VBAT_CheckFRO16kEnabled(VBAT_Type *base)
{
    return (bool)((base->FROCTLA & VBAT_FROCTLA_FRO_EN_MASK) == VBAT_FROCTLA_FRO_EN_MASK);
}

/*!
 * @brief Enable FRO16kHz output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The mask of modules that FRO16k is connected, should be the OR'ed
 *                        value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_UngateFRO16k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->FROCLKE |= VBAT_FROCLKE_CLKE(connectionsMask);
}

/*!
 * @brief Disable FRO16kHz output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The OR'ed value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_GateFRO16k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->FROCLKE &= ~VBAT_FROCLKE_CLKE(connectionsMask);
}

/*!
 * @brief Lock settings of internal 16kHz free running oscillator, please note that if locked 16kHz FRO's settings can
 * not be updated until the next POR.
 *
 * @note Please note that the operation to ungate/gate FRO 16kHz output clock can not be locked by this function.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockFRO16kSettings(VBAT_Type *base)
{
    base->FROLCKA |= VBAT_FROLCKA_LOCK_MASK;
    base->FROLCKB &= ~VBAT_FROLCKB_LOCK_MASK;
}

/*!
 * @brief Check if FRO16K settings are locked.
 *
 * @param base VBAT peripheral base address.
 *
 * @return @c true in case of FRO16k settings are locked, @c false in case of FRO16k settings are not locked.
 */
static inline bool VBAT_CheckFRO16kSettingsLocked(VBAT_Type *base)
{
    return ((base->FROLCKA & VBAT_FROLCKA_LOCK_MASK) != 0UL);
}

/*! @} */

/*!
 * @name OSC32K Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable 32K Crystal Oscillator.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable 32k Crystal Oscillator:
 *         - \b true Enable crystal oscillator and polling status register to check clock is ready.
 *         - \b false Disable crystal oscillator.
 */
static inline void VBAT_EnableCrystalOsc32k(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->OSCCTLA |= VBAT_OSCCTLA_OSC_EN_MASK;
        base->OSCCTLB &= ~VBAT_OSCCTLA_OSC_EN_MASK;

        /* Polling status register to check clock is ready. */
        while ((base->STATUSA & VBAT_STATUSA_OSC_RDY_MASK) == 0UL)
            ;
    }
    else
    {
        base->OSCCTLA &= ~VBAT_OSCCTLA_OSC_EN_MASK;
        base->OSCCTLB |= VBAT_OSCCTLA_OSC_EN_MASK;
    }
}

/*!
 * @brief Bypass 32k crystal oscillator, the clock is still output by oscillator but this clock is the same as clock
 * provided on EXTAL pin.
 *
 * @note In bypass mode, oscillator must be enabled; To exit bypass mode, oscillator must be disabled.
 *
 * @param base VBAT peripheral base address.
 * @param enableBypass Used to enter/exit bypass mode:
 *          - \b true Enter into bypass mode;
 *          - \b false Exit bypass mode.
 */
static inline void VBAT_BypassCrystalOsc32k(VBAT_Type *base, bool enableBypass)
{
    if (enableBypass)
    {
        base->OSCCTLA |= (VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
        base->OSCCTLB &= ~(VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
    }
    else
    {
        base->OSCCTLA &= ~(VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
        base->OSCCTLB |= (VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
    }
}

/*!
 * @brief Adjust 32k crystal oscillator amplifier gain.
 *
 * @param base VBAT peripheral base address.
 * @param coarse Specify amplifier coarse trim value.
 * @param fine Specify amplifier fine trim value.
 */
static inline void VBAT_AdjustCrystalOsc32kAmplifierGain(VBAT_Type *base, uint8_t coarse, uint8_t fine)
{
    base->OSCCTLA = ((base->OSCCTLA & ~(VBAT_OSCCTLA_COARSE_AMP_GAIN_MASK | VBAT_OSCCTLA_FINE_AMP_GAIN_MASK)) |
                     (VBAT_OSCCTLA_COARSE_AMP_GAIN(coarse) | VBAT_OSCCTLA_FINE_AMP_GAIN(fine)));
    base->OSCCTLB = ((base->OSCCTLB & ~(VBAT_OSCCTLA_COARSE_AMP_GAIN_MASK | VBAT_OSCCTLA_FINE_AMP_GAIN_MASK)) |
                     (VBAT_OSCCTLA_COARSE_AMP_GAIN(~coarse) | VBAT_OSCCTLA_FINE_AMP_GAIN(~fine)));
}

/*!
 * @brief Set 32k crystal oscillator mode and load capacitance for the XTAL/EXTAL pin.
 *
 * @param base VBAT peripheral base address.
 * @param operateMode Specify the crystal oscillator mode, please refer to @ref vbat_osc32k_operate_mode_t.
 * @param xtalCap Specify the internal capacitance for the XTAL pin from the capacitor bank.
 * @param extalCap Specify the internal capacitance for the EXTAL pin from the capacitor bank.
 *
 * @retval kStatus_VBAT_WrongCapacitanceValue The load capacitance value to set is not align with operate mode's
 * requirements.
 * @retval kStatus_Success Success to set operate mode and load capacitance.
 */
status_t VBAT_SetCrystalOsc32kModeAndLoadCapacitance(VBAT_Type *base,
                                                     vbat_osc32k_operate_mode_t operateMode,
                                                     vbat_osc32k_load_capacitance_select_t xtalCap,
                                                     vbat_osc32k_load_capacitance_select_t extalCap);

/*!
 * @brief Trim 32k crystal oscillator startup time.
 *
 * @param base VBAT peripheral base address.
 * @param startupTime Specify the startup time of the oscillator.
 */
static inline void VBAT_TrimCrystalOsc32kStartupTime(VBAT_Type *base, vbat_osc32k_start_up_time_t startupTime)
{
    base->OSCCFGA = ((base->OSCCFGA & ~(VBAT_OSCCFGA_INIT_TRIM_MASK)) | VBAT_OSCCFGA_INIT_TRIM(startupTime));
    base->OSCCFGB = ((base->OSCCFGB & ~(VBAT_OSCCFGA_INIT_TRIM_MASK)) | VBAT_OSCCFGA_INIT_TRIM(~startupTime));
}

/*!
 * @brief Set crystal oscillator comparator trim value when oscillator is set as low power switch mode.
 *
 * @param base VBAT peripheral base address.
 * @param comparatorTrimValue Comparator trim value, ranges from 0 to 7.
 */
static inline void VBAT_SetOsc32kSwitchModeComparatorTrimValue(VBAT_Type *base, uint8_t comparatorTrimValue)
{
    base->OSCCFGA = ((base->OSCCFGA & ~VBAT_OSCCFGA_CMP_TRIM_MASK) | VBAT_OSCCFGA_CMP_TRIM(comparatorTrimValue));
    base->OSCCFGB = ((base->OSCCFGB & ~VBAT_OSCCFGA_CMP_TRIM_MASK) | VBAT_OSCCFGA_CMP_TRIM(~comparatorTrimValue));
}

/*!
 * @brief Set crystal oscillator delay trim value when oscillator is set as low power switch mode.
 *
 * @param base VBAT peripheral base address.
 * @param delayTrimValue Delay trim value, ranges from 0 to 15.
 */
static inline void VBAT_SetOsc32kSwitchModeDelayTrimValue(VBAT_Type *base, uint8_t delayTrimValue)
{
    base->OSCCFGA = ((base->OSCCFGA & ~VBAT_OSCCFGA_DLY_TRIM_MASK) | VBAT_OSCCFGA_DLY_TRIM(delayTrimValue));
    base->OSCCFGB = ((base->OSCCFGB & ~VBAT_OSCCFGA_DLY_TRIM_MASK) | VBAT_OSCCFGA_DLY_TRIM(~delayTrimValue));
}

/*!
 * @brief Set crystal oscillator capacitor trim value when oscillator is set as low power switch mode.
 *
 * @param base VBAT peripheral base address.
 * @param capacitorTrimValue Capacitor value to trim, ranges from 0 to 3.
 */
static inline void VBAT_SetOsc32kSwitchModeCapacitorTrimValue(VBAT_Type *base, uint8_t capacitorTrimValue)
{
    base->OSCCFGA = ((base->OSCCFGA & ~VBAT_OSCCFGA_CAP_TRIM_MASK) | VBAT_OSCCFGA_CAP_TRIM(capacitorTrimValue));
    base->OSCCFGB = ((base->OSCCFGB & ~VBAT_OSCCFGA_CAP_TRIM_MASK) | VBAT_OSCCFGA_CAP_TRIM(~capacitorTrimValue));
}

/*!
 * @brief Lock Osc32k settings, after locked all writes to the Oscillator registers are blocked.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LookOsc32kSettings(VBAT_Type *base)
{
    base->OSCLCKA |= VBAT_OSCLCKA_LOCK_MASK;
    base->OSCLCKB &= ~VBAT_OSCLCKB_LOCK_MASK;
}

/*!
 * @brief Unlock Osc32k settings.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_UnlockOsc32kSettings(VBAT_Type *base)
{
    base->OSCLCKA &= ~VBAT_OSCLCKA_LOCK_MASK;
    base->OSCLCKB |= VBAT_OSCLCKB_LOCK_MASK;
}

/*!
 * @brief Check if osc32k settings are locked.
 *
 * @param base VBAT peripheral base address.
 * @return \c true in case of osc32k settings are locked, \c false in case of osc32k settings are not locked.
 */
static inline bool VBAT_CheckOsc32kSettingsLocked(VBAT_Type *base)
{
    return ((base->OSCLCKA & VBAT_OSCLCKA_LOCK_MASK) != 0UL);
}

/*!
 * @brief Enable OSC32k output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The OR'ed value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_UngateOsc32k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->OSCCLKE |= VBAT_OSCCLKE_CLKE(connectionsMask);
}

/*!
 * @brief Disable OSC32k output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The OR'ed value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_GateOsc32k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->OSCCLKE &= ~VBAT_OSCCLKE_CLKE(connectionsMask);
}

/*! @} */

/*!
 * @name RAM_LDO Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable Bandgap.
 *
 * @note The FRO16K must be enabled before enabling the bandgap.
 * @note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable bandgap.
 *      - \b true Enable the bandgap.
 *      - \b false Disable the bandgap.
 *
 * @retval kStatus_Success Success to enable/disable the bandgap.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable the bandgap due to FRO16k is not enabled previously.
 */
status_t VBAT_EnableBandgap(VBAT_Type *base, bool enable);

/*!
 * @brief Check if bandgap is enabled.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval true The bandgap is enabled.
 * @retval false The bandgap is disabled.
 */
static inline bool VBAT_CheckBandgapEnabled(VBAT_Type *base)
{
    return (bool)((base->LDOCTLA & VBAT_LDOCTLA_BG_EN_MASK) == VBAT_LDOCTLA_BG_EN_MASK);
}

/*!
 * @brief Enable/disable bandgap low power refresh mode.
 *
 * @note For lowest power consumption, refresh mode must be enabled.
 * @note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enableRefreshMode Used to enable/disable bandgap low power refresh mode.
 *          - \b true Enable bandgap low power refresh mode.
 *          - \b false Disable bandgap low power refresh mode.
 */
static inline void VBAT_EnableBandgapRefreshMode(VBAT_Type *base, bool enableRefreshMode)
{
    if (enableRefreshMode)
    {
        base->LDOCTLA |= VBAT_LDOCTLA_REFRESH_EN_MASK;
        base->LDOCTLB &= ~VBAT_LDOCTLA_REFRESH_EN_MASK;
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_REFRESH_EN_MASK;
        base->LDOCTLB |= VBAT_LDOCTLA_REFRESH_EN_MASK;
    }
}

/*!
 * @brief Enable/disable Backup RAM Regulator(RAM_LDO).
 *
 * @note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable RAM_LDO.
 *          - \b true Enable backup SRAM regulator.
 *          - \b false Disable backup SRAM regulator.
 *
 * @retval kStatusSuccess Success to enable/disable backup SRAM regulator.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable backup SRAM regulator due to FRO16k is not enabled previously.
 * @retval kStatus_VBAT_BandgapNotEnabled Fail to enable backup SRAM regulator due to the bandgap is not enabled
 * previously.
 */
status_t VBAT_EnableBackupSRAMRegulator(VBAT_Type *base, bool enable);

/*!
 * @brief Lock settings of RAM_LDO, please note that if locked then RAM_LDO's settings
 * can not be updated until the next POR.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockRamLdoSettings(VBAT_Type *base)
{
    base->LDOLCKA |= VBAT_LDOLCKA_LOCK_MASK;
    base->LDOLCKB &= ~VBAT_LDOLCKA_LOCK_MASK;
}

/*!
 * @brief Check if RAM_LDO settings is locked.
 *
 * @param base VBAT peripheral base address.
 * @return @c true in case of RAM_LDO settings are locked, @c false in case of RAM_LDO settings are unlocked.
 */
static inline bool VBAT_CheckRamLdoSettingsLocked(VBAT_Type *base)
{
    return ((base->LDOLCKA & VBAT_LDOLCKA_LOCK_MASK) != 0UL);
}

/*!
 * @brief Switch the SRAM to be powered by LDO_RAM.
 *
 * @note This function can be used to switch the SRAM to the VBAT retention supply at any time, but please note that the
 * SRAM must not be accessed during this time.
 * @note Invoke this function to switch power supply before switching off external power.
 * @note RAM_LDO must be enabled before invoking this function.
 * @note To access the SRAM arrays retained by the LDO_RAM, please invoke VBAT_SwitchSRAMPowerBySocSupply(), after
 * external power is switched back on.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval kStatusSuccess Success to Switch SRAM powered by VBAT.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to switch SRAM powered by VBAT due to FRO16K not enabled previously.
 */
status_t VBAT_SwitchSRAMPowerByLDOSRAM(VBAT_Type *base);

/*!
 * @brief Switch the RAM to be powered by Soc Supply in software mode.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_SwitchSRAMPowerBySocSupply(VBAT_Type *base)
{
    base->LDORAMC &= ~VBAT_LDORAMC_SWI_MASK;
    base->LDORAMC &= ~VBAT_LDORAMC_ISO_MASK;
}

/*!
 * @brief Power off selected SRAM array in low power modes.
 *
 * @param base VBAT peripheral base address.
 * @param sramMask The mask of SRAM array to power off, should be the OR'ed value of @ref vbat_ram_array_t.
 */
static inline void VBAT_PowerOffSRAMsInLowPowerModes(VBAT_Type *base, uint8_t sramMask)
{
    base->LDORAMC |= VBAT_LDORAMC_RET(sramMask);
}

/*!
 * @brief Retain selected SRAM array in low power modes.
 *
 * @param base VBAT peripheral base address.
 * @param sramMask The mask of SRAM array to retain, should be the OR'ed value of @ref vbat_ram_array_t.
 */
static inline void VBAT_RetainSRAMsInLowPowerModes(VBAT_Type *base, uint8_t sramMask)
{
    base->LDORAMC &= ~VBAT_LDORAMC_RET(sramMask);
}

/*!
 * @brief Enable/disable SRAM isolation.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable SRAM violation.
 *          - \b true SRAM will be isolated.
 *          - \b false SRAM state follows the SoC power modes.
 */
static inline void VBAT_EnableSRAMIsolation(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->LDORAMC |= VBAT_LDORAMC_ISO_MASK;
    }
    else
    {
        base->LDORAMC &= ~VBAT_LDORAMC_ISO_MASK;
    }
}

/*! @} */

/*! @name Bandgap Timer Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable Bandgap timer.
 *
 * @note The bandgap timer is available when the bandgap is enabled and are clocked by the FRO16k.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable bandgap timer.
 * @param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of @ref vbat_bandgap_timer_id_t.
 *
 * @retval kStatus_Success Success to enable/disable selected bandgap timer.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable/disable selected bandgap timer due to FRO16k not enabled
 * previously.
 * @retval kStatus_VBAT_BandgapNotEnabled Fail to enable/disable selected bandgap timer due to bandgap not enabled
 * previously.
 */
status_t VBAT_EnableBandgapTimer(VBAT_Type *base, bool enable, uint8_t timerIdMask);

/*!
 * @brief Set bandgap timer0 timeout value.
 *
 * @note The timeout value can only be changed when the timer is disabled.
 *
 * @param base VBAT peripheral base address.
 * @param timeoutPeriod Bandgap timer timeout value, please refer to @ref vbat_bandgap_timer0_timeout_period_t.
 */
void VBAT_SetBandgapTimer0TimeoutValue(VBAT_Type *base, vbat_bandgap_timer0_timeout_period_t timeoutPeriod);

/*!
 * @brief Set bandgap timer1 timeout value.
 *
 * @note The timeout value can only be changed when the timer is disabled.
 *
 * @param base VBAT peripheral base address.
 * @param timeoutPeriod The bandgap timerout 1 period, in number of seconds, ranging from 0 to 65535s.
 */
void VBAT_SetBandgapTimer1TimeoutValue(VBAT_Type *base, uint32_t timeoutPeriod);

/*! @} */

/*! @name Switch Control Interfaces
 * @{
 */

/*!
 * @brief Control the VBAT internal switch in active mode, VBAT modules can be suppiled by VDD_BAT and VDD_SYS.
 *
 * @param base VBAT peripheral base address.
 * @param supply Used to control the VBAT internal switch.
 */
static inline void VBAT_SwitchVBATModuleSupplyActiveMode(VBAT_Type *base, vbat_internal_module_supply_t supply)
{
    if (supply == kVBAT_ModuleSuppliedByVddBat)
    {
        base->SWICTLA &= ~VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLB |= VBAT_SWICTLA_SWI_EN_MASK;
    }
    else
    {
        base->SWICTLA |= VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLB &= ~VBAT_SWICTLA_SWI_EN_MASK;
    }
}

/*!
 * @brief Get VBAT module supply in active mode.
 *
 * @param base VBAT peripheral base address.
 * @return VDD_SYS supplies VBAT modules or VDD_BAT supplies VBAT modules, in type of @ref
 * vbat_internal_module_supply_t.
 */
static inline vbat_internal_module_supply_t VBAT_GetVBATModuleSupply(VBAT_Type *base)
{
    return (base->SWICTLA & VBAT_SWICTLA_SWI_EN_MASK);
}

/*!
 * @brief Control the VBAT internal switch in low power modes.
 *
 * @note If VBAT modules are supplied by VDD_SYS in low power modes, VBAT module will also supplied by VDD_SYS in active
 * mode.
 *
 * @param base VBAT peripheral base address.
 * @param supply Used to specify which voltage input supply VBAT modules in low power mode.
 */
static inline void VBAT_SwitchVBATModuleSupplyLowPowerMode(VBAT_Type *base, vbat_internal_module_supply_t supply)
{
    if (supply == kVBAT_ModuleSuppliedByVddBat)
    {
        base->SWICTLA &= ~VBAT_SWICTLA_LP_EN_MASK;
        base->SWICTLB |= VBAT_SWICTLA_LP_EN_MASK;
    }
    else
    {
        base->SWICTLA |= VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLB &= ~VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLA |= VBAT_SWICTLA_LP_EN_MASK;
        base->SWICTLB &= ~VBAT_SWICTLA_LP_EN_MASK;
    }
}

/*!
 * @brief Lock switch control, if locked all writes to the switch registers will be blocked.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockSwitchControl(VBAT_Type *base)
{
    base->SWILCKA |= VBAT_SWILCKA_LOCK_MASK;
    base->SWILCKB &= ~VBAT_SWILCKB_LOCK_MASK;
}

/*!
 * @brief Unlock switch control.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_UnlockSwitchControl(VBAT_Type *base)
{
    base->SWILCKA &= ~VBAT_SWILCKA_LOCK_MASK;
    base->SWILCKB |= VBAT_SWILCKB_LOCK_MASK;
}

/*!
 * @brief Check if switch control is locked.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval false switch control is not locked.
 * @retval true  switch control is locked, any writes to related registers are blocked.
 */
static inline bool VBAT_CheckSwitchControlLocked(VBAT_Type *base)
{
    return ((base->SWILCKA & VBAT_SWILCKA_LOCK_MASK) != 0UL);
}

/*! @} */

/*! @name Status, Interrupt, Wakeup Control Interfaces
 * @{
 */

/*!
 * @brief Get VBAT status flags
 *
 * @param base VBAT peripheral base address.
 * @return The asserted status flags, should be the OR'ed value of @ref vbat_status_flag_t.
 */
static inline uint32_t VBAT_GetStatusFlags(VBAT_Type *base)
{
    return (uint32_t)(base->STATUSA);
}

/*!
 * @brief Clear VBAT status flags.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of status flags to be cleared, should be the OR'ed value of @ref vbat_status_flag_t except
 *              @ref kVBAT_StatusFlagLdoReady, @ref kVBAT_StatusFlagOsc32kReady, @ref kVBAT_StatusFlagInterrupt0Detect,
 *              @ref kVBAT_StatusFlagInterrupt1Detect, @ref kVBAT_StatusFlagInterrupt2Detect,
 *              @ref kVBAT_StatusFlagInterrupt3Detect.
 */
static inline void VBAT_ClearStatusFlags(VBAT_Type *base, uint32_t mask)
{
    base->STATUSA = mask;
    base->STATUSB = ~mask;
}

/*!
 * @brief Enable interrupts for the VBAT module, such as POR detect interrupt, Wakeup Pin interrupt and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of interrupts to be enabled, should be the OR'ed value of @ref vbat_interrupt_enable_t.
 */
static inline void VBAT_EnableInterrupts(VBAT_Type *base, uint32_t mask)
{
    base->IRQENA |= mask;
    base->IRQENB &= (uint32_t)~mask;
}

/*!
 * @brief Disable interrupts for the VBAT module, such as POR detect interrupt, wakeup pin interrupt and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of interrupts to be disabled, should be the OR'ed value of @ref vbat_interrupt_enable_t.
 */
static inline void VBAT_DisableInterrupts(VBAT_Type *base, uint32_t mask)
{
    base->IRQENA &= ~mask;
    base->IRQENB |= mask;
}

/*!
 * @brief Enable wakeup for the VBAT module, such as POR detect wakeup, wakeup pin wakeup and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of enumerators in @ref vbat_wakeup_enable_t.
 */
static inline void VBAT_EnableWakeup(VBAT_Type *base, uint32_t mask)
{
    base->WAKENA |= mask;
    base->WAKENB &= ~mask;
}

/*!
 * @brief Disable wakeup for VBAT module, such as POR detect wakeup, wakeup pin wakeup and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of enumerators in @ref vbat_wakeup_enable_t.
 */
static inline void VBAT_DisableWakeup(VBAT_Type *base, uint32_t mask)
{
    base->WAKENA &= ~mask;
    base->WAKENB |= mask;
}

/*!
 * @brief Lock VBAT interrupt and wakeup settings, please note that if locked the interrupt and wakeup settings can not
 * be updated until the next POR.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockInterruptWakeupSettings(VBAT_Type *base)
{
    base->LOCKA |= VBAT_LOCKA_LOCK_MASK;
}

/*!
 * @brief Set the default state of the WAKEUP_b pin output when no enabled wakeup source is asserted.
 *
 * @param base VBAT peripheral base address.
 * @param assert Used to set default state of the WAKEUP_b pin output:
 *          - \b true WAKEUP_b output state is logic one;
 *          - \b false WAKEUP_b output state is logic zero.
 */
static inline void VBAT_SetWakeupPinDefaultState(VBAT_Type *base, bool assert)
{
    if (assert)
    {
        base->WAKECFG |= VBAT_WAKECFG_OUT_MASK;
    }
    else
    {
        base->WAKECFG &= ~VBAT_WAKECFG_OUT_MASK;
    }
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* __FSL_VBAT_H__ */
