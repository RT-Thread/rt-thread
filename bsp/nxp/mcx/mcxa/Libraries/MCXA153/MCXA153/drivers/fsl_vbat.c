/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_vbat.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mcx_vbat"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Configure internal 16kHz free running oscillator, including enabel FRO16k, gate FRO16k output.
 *
 * param base VBAT peripheral base address.
 * param config Pointer to vbat_fro16k_config_t structure.
 */
void VBAT_ConfigFRO16k(VBAT_Type *base, const vbat_fro16k_config_t *config)
{
    assert(config != NULL);

    VBAT_EnableFRO16k(base, config->enableFRO16k);
    VBAT_UngateFRO16k(base, config->enabledConnectionsMask);
}

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG)
/*!
 * brief Set 32k crystal oscillator mode and load capacitance for the XTAL/EXTAL pin.
 *
 * param base VBAT peripheral base address.
 * param operateMode Specify the crystal oscillator mode, please refer to vbat_osc32k_operate_mode_t.
 * param xtalCap Specify the internal capacitance for the XTAL pin from the capacitor bank.
 * param extalCap Specify the internal capacitance for the EXTAL pin from the capacitor bank.
 *
 * retval kStatus_VBAT_WrongCapacitanceValue The load capacitance value to set is not align with operate mode's
 * requirements.
 * retval kStatus_Success Success to set operate mode and load capacitance.
 */
status_t VBAT_SetCrystalOsc32kModeAndLoadCapacitance(VBAT_Type *base,
                                                     vbat_osc32k_operate_mode_t operateMode,
                                                     vbat_osc32k_load_capacitance_select_t xtalCap,
                                                     vbat_osc32k_load_capacitance_select_t extalCap)
{
    if (operateMode == kVBAT_Osc32kEnabledToTransconductanceMode)
    {
        if (((uint8_t)extalCap & 0x1U) == 0U)
        {
            return kStatus_VBAT_WrongCapacitanceValue;
        }
    }

    if (operateMode == kVBAT_Osc32kEnabledToLowPowerSwitchedMode)
    {
        if ((extalCap != kVBAT_Osc32kCrystalLoadCap0pF) && (xtalCap != kVBAT_Osc32kCrystalLoadCap0pF))
        {
            return kStatus_VBAT_WrongCapacitanceValue;
        }
    }

    if (operateMode == kVBAT_Osc32kEnabledToLowPowerBackupMode)
    {
        if ((extalCap & 0x1U) != 0U)
        {
            return kStatus_VBAT_WrongCapacitanceValue;
        }
    }

    if ((xtalCap != kVBAT_Osc32kCrystalLoadCapBankDisabled) && (extalCap != kVBAT_Osc32kCrystalLoadCapBankDisabled))
    {
        base->OSCCTLA |= VBAT_OSCCTLA_CAP_SEL_EN_MASK;
        base->OSCCTLB &= ~VBAT_OSCCTLA_CAP_SEL_EN_MASK;
        base->OSCCTLA = ((base->OSCCTLA & ~(VBAT_OSCCTLA_EXTAL_CAP_SEL_MASK | VBAT_OSCCTLA_XTAL_CAP_SEL_MASK)) |
                         (VBAT_OSCCTLA_XTAL_CAP_SEL(xtalCap) | VBAT_OSCCTLA_EXTAL_CAP_SEL(extalCap)));
        base->OSCCTLB = ((base->OSCCTLB & ~(VBAT_OSCCTLA_EXTAL_CAP_SEL_MASK | VBAT_OSCCTLA_XTAL_CAP_SEL_MASK)) |
                         VBAT_OSCCTLA_XTAL_CAP_SEL(~xtalCap) | VBAT_OSCCTLA_EXTAL_CAP_SEL(~extalCap));
    }

    base->OSCCTLA = (((base->OSCCTLA & ~VBAT_OSCCTLA_MODE_EN_MASK)) | VBAT_OSCCTLA_MODE_EN(operateMode));
    base->OSCCTLB = ((base->OSCCTLB & ~VBAT_OSCCTLA_MODE_EN_MASK) | VBAT_OSCCTLA_MODE_EN((uint8_t)~operateMode));

    return kStatus_Success;
}
#endif /* FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG)
/*!
 * brief Enable/disable Bandgap.
 *
 * note The FRO16K must be enabled before enableing the bandgap.
 * note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * param base VBAT peripheral base address.
 * param enable Used to enable/disable bandgap.
 *      - \b true Enable the bandgap.
 *      - \b false Disable the bandgap.
 *
 * retval kStatus_Success Success to enable/disable the bandgap.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to enable the bandgap due to FRO16k is not enabled previously.
 */
status_t VBAT_EnableBandgap(VBAT_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        if (VBAT_CheckFRO16kEnabled(base))
        {
            base->LDOCTLA |= VBAT_LDOCTLA_BG_EN_MASK;
            base->LDOCTLB &= ~VBAT_LDOCTLA_BG_EN_MASK;
        }
        else
        {
            /* FRO16K must be enabled before enabling the Bandgap. */
            status = kStatus_VBAT_Fro16kNotEnabled;
        }
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_BG_EN_MASK;
        base->LDOCTLB |= VBAT_LDOCTLA_BG_EN_MASK;
    }

    return status;
}

/*!
 * brief Enable/disable Backup RAM Regulator(RAM_LDO).
 *
 * note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * param base VBAT peripheral base address.
 * param enable Used to enable/disable RAM_LDO.
 *          - \b true Enable backup SRAM regulator.
 *          - \b false Disable backup SRAM regulator.
 *
 * retval kStatusSuccess Success to enable/disable backup SRAM regulator.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to enable backup SRAM regulator due to FRO16k is not enabled previously.
 * retval kStatus_VBAT_BandgapNotEnabled Fail to enable backup SRAM regulator due to the bandgap is not enabled
 * previously.
 */
status_t VBAT_EnableBackupSRAMRegulator(VBAT_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        if (VBAT_CheckFRO16kEnabled(base))
        {
            if (VBAT_CheckBandgapEnabled(base))
            {
                base->LDOCTLA |= VBAT_LDOCTLA_LDO_EN_MASK;
                base->LDOCTLB &= ~VBAT_LDOCTLA_LDO_EN_MASK;
                /* Polling until LDO is enabled. */
                while ((base->STATUSA & VBAT_STATUSA_LDO_RDY_MASK) == 0UL)
                {
                }
            }
            else
            {
                /* The bandgap must be enabled previously. */
                status = kStatus_VBAT_BandgapNotEnabled;
            }
        }
        else
        {
            /* FRO16k must be enabled previously. */
            status = kStatus_VBAT_Fro16kNotEnabled;
        }
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_LDO_EN_MASK;
        base->LDOCTLB |= VBAT_LDOCTLA_LDO_EN_MASK;
    }

    return status;
}

/*!
 * brief Switch the SRAM to be powered by VBAT.
 *
 * param base VBAT peripheral base address.
 *
 * retval kStatusSuccess Success to Switch SRAM powered by VBAT.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to switch SRAM powered by VBAT due to FRO16K not enabled previously.
 */
status_t VBAT_SwitchSRAMPowerByLDOSRAM(VBAT_Type *base)
{
    status_t status = kStatus_Success;

    status = VBAT_EnableBandgap(base, true);

    if (status == kStatus_Success)
    {
        VBAT_EnableBandgapRefreshMode(base, true);
        (void)VBAT_EnableBackupSRAMRegulator(base, true);

        /* Isolate the SRAM array */
        base->LDORAMC |= VBAT_LDORAMC_ISO_MASK;
        /* Switch the supply to VBAT LDO. */
        base->LDORAMC |= VBAT_LDORAMC_SWI_MASK;
    }

    return status;
}
#endif /* FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER) && FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER)
/*!
 * brief Enable/disable Bandgap timer.
 *
 * note The bandgap timer is available when the bandgap is enabled and are clocked by the FRO16k.
 *
 * param base VBAT peripheral base address.
 * param enable Used to enable/disable bandgap timer.
 * param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of vbat_bandgap_timer_id_t.
 *
 * retval kStatus_Success Success to enable/disable selected bandgap timer.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to enable/disable selected bandgap timer due to FRO16k not enabled
 * previously. retval kStatus_VBAT_BandgapNotEnabled Fail to enable/disable selected bandgap timer due to bandgap not
 * enabled previously.
 */
status_t VBAT_EnableBandgapTimer(VBAT_Type *base, bool enable, uint8_t timerIdMask)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        if (VBAT_CheckFRO16kEnabled(base))
        {
            if (VBAT_CheckBandgapEnabled(base))
            {
                if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer0) != 0U)
                {
                    base->LDOTIMER0 |= VBAT_LDOTIMER0_TIMEN_MASK;
                }

                if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer1) != 0U)
                {
                    base->LDOTIMER1 |= VBAT_LDOTIMER1_TIMEN_MASK;
                }
            }
            else
            {
                /* Bandgap must be enabled previously. */
                status = kStatus_VBAT_BandgapNotEnabled;
            }
        }
        else
        {
            /* FRO16K must be enabled previously. */
            status = kStatus_VBAT_Fro16kNotEnabled;
        }
    }
    else
    {
        if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer0) != 0U)
        {
            base->LDOTIMER0 &= ~VBAT_LDOTIMER0_TIMEN_MASK;
        }

        if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer1) != 0U)
        {
            base->LDOTIMER1 &= ~VBAT_LDOTIMER1_TIMEN_MASK;
        }
    }

    return status;
}

/*!
 * brief Set bandgap timer0 timeout value.
 *
 * param base VBAT peripheral base address.
 * param timeoutPeriod Bandgap timer timeout value, please refer to vbat_bandgap_timer0_timeout_period_t.
 */
void VBAT_SetBandgapTimer0TimeoutValue(VBAT_Type *base, vbat_bandgap_timer0_timeout_period_t timeoutPeriod)
{
    bool timerEnabled = false;

    timerEnabled = ((base->LDOTIMER0 & VBAT_LDOTIMER0_TIMEN_MASK) != 0UL) ? true : false;

    if (timerEnabled)
    {
        base->LDOTIMER0 &= ~VBAT_LDOTIMER0_TIMEN_MASK;
    }

    base->LDOTIMER0 = ((base->LDOTIMER0 & (~VBAT_LDOTIMER0_TIMCFG_MASK)) | VBAT_LDOTIMER0_TIMCFG(timeoutPeriod));

    if (timerEnabled)
    {
        base->LDOTIMER0 |= VBAT_LDOTIMER0_TIMEN_MASK;
    }
}

/*!
 * brief Set bandgap timer1 timeout value.
 *
 * note The timeout value can only be changed when the timer is disabled.
 *
 * param base VBAT peripheral base address.
 * param timeoutPeriod The bandgap timerout 1 period, in number of seconds, ranging from 0 to 65535s.
 */
void VBAT_SetBandgapTimer1TimeoutValue(VBAT_Type *base, uint32_t timeoutPeriod)
{
    bool timerEnabled = false;

    timerEnabled = ((base->LDOTIMER1 & VBAT_LDOTIMER1_TIMEN_MASK) != 0UL) ? true : false;

    if (timerEnabled)
    {
        base->LDOTIMER1 &= ~VBAT_LDOTIMER1_TIMEN_MASK;
    }

    base->LDOTIMER1 = ((base->LDOTIMER1 & (~VBAT_LDOTIMER1_TIMCFG_MASK)) | VBAT_LDOTIMER1_TIMCFG(timeoutPeriod));

    if (timerEnabled)
    {
        base->LDOTIMER1 |= VBAT_LDOTIMER1_TIMEN_MASK;
    }
}
#endif /* FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG) && FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG)
/*!
 * brief Initializes the VBAT clock monitor, enable clock monitor and set the clock monitor configuration.
 *
 * note Both FRO16K and OSC32K should be enabled and stable before invoking this function.
 *
 * param base VBAT peripheral base address.
 * param config Pointer to vbat_clock_monitor_config_t structure.
 *
 * retval kStatus_Success Clock monitor is initialized successfully.
 * retval kStatus_VBAT_Fro16kNotEnabled FRO16K is not enabled.
 * retval kStatus_VBAT_Osc32kNotReady OSC32K is not ready.
 * retval kStatus_VBAT_ClockMonitorLocked Clock monitor is locked.
 */
status_t VBAT_InitClockMonitor(VBAT_Type *base, const vbat_clock_monitor_config_t *config)
{
    assert(config != NULL);

    status_t status = kStatus_Success;

    if (VBAT_CheckFRO16kEnabled(base))
    {
        if ((VBAT_GetStatusFlags(base) & kVBAT_StatusFlagOsc32kReady) != 0UL)
        {
            if (VBAT_CheckClockMonitorControlLocked(base))
            {
                status = kStatus_VBAT_ClockMonitorLocked;
            }
            else
            {
                /* Disable clock monitor before configuring clock monitor. */
                VBAT_EnableClockMonitor(base, false);
                /* Set clock monitor divide trim value. */
                VBAT_SetClockMonitorDivideTrim(base, config->divideTrim);
                /* Set clock monitor frequency trim value. */
                VBAT_SetClockMonitorFrequencyTrim(base, config->freqTrim);
                /* Enable clock monitor. */
                VBAT_EnableClockMonitor(base, true);

                if (config->lock)
                {
                    VBAT_LockClockMonitorControl(base);
                }
            }
        }
        else
        {
            status = kStatus_VBAT_OSC32KNotReady;
        }
    }
    else
    {
        status = kStatus_VBAT_Fro16kNotEnabled;
    }

    return status;
}

/*!
 * brief Deinitialize the VBAT clock monitor.
 *
 * param base VBAT peripheral base address.
 *
 * retval kStatus_Success Clock monitor is de-initialized successfully.
 * retval kStatus_VBAT_ClockMonitorLocked Control of Clock monitor is locked.
 */
status_t VBAT_DeinitMonitor(VBAT_Type *base)
{
    if (VBAT_CheckClockMonitorControlLocked(base))
    {
        return kStatus_VBAT_ClockMonitorLocked;
    }

    VBAT_EnableClockMonitor(base, false);

    return kStatus_Success;
}
#endif /* FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG) && FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG)
/*!
 * brief Initialize tamper control.
 *
 * note Both FRO16K and bandgap should be enabled before calling this function.
 *
 * param base VBAT peripheral base address.
 * param config Pointer to vbat_tamper_config_t structure.
 *
 * retval kStatus_Success Tamper is initialized successfully.
 * retval kStatus_VBAT_TamperLocked Tamper control is locked.
 * retval kStatus_VBAT_BandgapNotEnabled Bandgap is not enabled.
 * retval kStatus_VBAT_Fro16kNotEnabled FRO 16K is not enabled.
 */
status_t VBAT_InitTamper(VBAT_Type *base, const vbat_tamper_config_t *config)
{
    assert(config != NULL);

    status_t status = kStatus_Success;

    if (VBAT_CheckFRO16kEnabled(base))
    {
        if (VBAT_CheckBandgapEnabled(base))
        {
            if (VBAT_CheckTamperControlLocked(base))
            {
                return kStatus_VBAT_TamperLocked;
            }
            else
            {
                base->TAMCTLA = ((base->TAMCTLA & (~VBAT_TAMCTLA_VOLT_EN_MASK | VBAT_TAMCTLA_TEMP_EN_MASK)) |
                                 VBAT_TAMCTLA_VOLT_EN(config->enableVoltageDetect) |
                                 VBAT_TAMCTLA_TEMP_EN(config->enableTemperatureDetect));
                base->TAMCTLB = ((base->TAMCTLB & (~VBAT_TAMCTLA_VOLT_EN_MASK | VBAT_TAMCTLA_TEMP_EN_MASK)) |
                                 VBAT_TAMCTLA_VOLT_EN((config->enableVoltageDetect) ? 0U : 1U) |
                                 VBAT_TAMCTLA_TEMP_EN((config->enableTemperatureDetect) ? 0U : 1U));

                if (config->lock)
                {
                    VBAT_LockTamperControl(base);
                }
            }
        }
        else
        {
            status = kStatus_VBAT_BandgapNotEnabled;
        }
    }
    else
    {
        status = kStatus_VBAT_Fro16kNotEnabled;
    }

    return status;
}

/*!
 * brief De-initialize tamper control.
 *
 * param base VBAT peripheral base address.
 *
 * retval kStatus_Success Tamper is de-initialized successfully.
 * retval kStatus_VBAT_TamperLocked Tamper control is locked.
 */
status_t VBAT_DeinitTamper(VBAT_Type *base)
{
    if (VBAT_CheckTamperControlLocked(base))
    {
        return kStatus_VBAT_TamperLocked;
    }

    base->TAMCTLA &= ~(VBAT_TAMCTLA_VOLT_EN_MASK | VBAT_TAMCTLA_TEMP_EN_MASK);
    base->TAMCTLB |= (VBAT_TAMCTLA_VOLT_EN_MASK | VBAT_TAMCTLA_TEMP_EN_MASK);

    return kStatus_Success;
}
#endif /* FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG */
