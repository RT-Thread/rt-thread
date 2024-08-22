/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mcx_spc"
#endif

/*
 * $Coverage Justification Reference$
 *
 * $Justification spc_c_ref_1$
 * The SPC busy status flag is too short to get coverage data.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
 * brief Gets selected power domain's requested low power mode.
 *
 * param base SPC peripheral base address.
 * param powerDomainId Power Domain Id, please refer to spc_power_domain_id_t.
 *
 * return The selected power domain's requested low power mode, please refer to spc_power_domain_low_power_mode_t.
 */
spc_power_domain_low_power_mode_t SPC_GetPowerDomainLowPowerMode(SPC_Type *base, spc_power_domain_id_t powerDomainId)
{
    assert((uint8_t)powerDomainId < SPC_PD_STATUS_COUNT);

    uint32_t val;

    val = ((base->PD_STATUS[(uint8_t)powerDomainId] & SPC_PD_STATUS_LP_MODE_MASK) >> SPC_PD_STATUS_LP_MODE_SHIFT);
    return (spc_power_domain_low_power_mode_t)val;
}

/*!
 * brief Gets Isolation status for each power domains.
 *
 * This function gets the status which indicates whether certain
 * peripheral and the IO pads are in a latched state as a result
 * of having been in POWERDOWN mode.
 *
 * param base SPC peripheral base address.
 * return Current isolation status for each power domains.
 */
uint8_t SPC_GetPeriphIOIsolationStatus(SPC_Type *base)
{
    uint32_t reg;

    reg = base->SC;
    return (uint8_t)((reg & SPC_SC_ISO_CLR_MASK) >> SPC_SC_ISO_CLR_SHIFT);
}

/*!
 * brief Configs Low power request output pin.
 *
 * This function configs the low power request output pin
 *
 * param base SPC peripheral base address.
 * param config Pointer the spc_LowPower_Request_config_t structure.
 */
void SPC_SetLowPowerRequestConfig(SPC_Type *base, const spc_lowpower_request_config_t *config)
{
    assert(config != NULL);

    uint32_t reg;

    reg = base->LPREQ_CFG;
    reg &= ~(SPC_LPREQ_CFG_LPREQOE_MASK | SPC_LPREQ_CFG_LPREQPOL_MASK | SPC_LPREQ_CFG_LPREQOV_MASK);

    if (config->enable)
    {
        reg |= SPC_LPREQ_CFG_LPREQOE_MASK | SPC_LPREQ_CFG_LPREQPOL((uint8_t)(config->polarity)) |
               SPC_LPREQ_CFG_LPREQOV((uint8_t)(config->override));
    }
    else
    {
        reg &= ~SPC_LPREQ_CFG_LPREQOE_MASK;
    }

    base->LPREQ_CFG = reg;
}

#if !(defined(FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT) && FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT)
/*!
 * brief Configures VDD Core Glitch detector, including ripple counter selection, timeout value and so on.
 *
 * param base SPC peripheral base address.
 * param config Pointer to the structure in type of spc_vdd_core_glitch_detector_config_t.
 */
void SPC_ConfigVddCoreGlitchDetector(SPC_Type *base, const spc_vdd_core_glitch_detector_config_t *config)
{
    assert(config != NULL);

    uint32_t reg;

    reg = (base->VDD_CORE_GLITCH_DETECT_SC) &
          ~(SPC_VDD_CORE_GLITCH_DETECT_SC_CNT_SELECT_MASK | SPC_VDD_CORE_GLITCH_DETECT_SC_TIMEOUT_MASK |
            SPC_VDD_CORE_GLITCH_DETECT_SC_RE_MASK | SPC_VDD_CORE_GLITCH_DETECT_SC_IE_MASK);

    reg |= SPC_VDD_CORE_GLITCH_DETECT_SC_CNT_SELECT(config->rippleCounterSelect) |
           SPC_VDD_CORE_GLITCH_DETECT_SC_TIMEOUT(config->resetTimeoutValue) |
           SPC_VDD_CORE_GLITCH_DETECT_SC_RE(config->enableReset) |
           SPC_VDD_CORE_GLITCH_DETECT_SC_IE(config->enableInterrupt);

    base->VDD_CORE_GLITCH_DETECT_SC = reg;
}
#endif

/*!
 * brief Set SRAM operate voltage.
 *
 * param base SPC peripheral base address.
 * param config The pointer to spc_sram_voltage_config_t, specifies the configuration of sram voltage.
 */
void SPC_SetSRAMOperateVoltage(SPC_Type *base, const spc_sram_voltage_config_t *config)
{
    assert(config != NULL);

    uint32_t reg = 0UL;

    reg |= SPC_SRAMCTL_VSM(config->operateVoltage);

    base->SRAMCTL = reg;

    if (config->requestVoltageUpdate)
    {
        base->SRAMCTL |= SPC_SRAMCTL_REQ_MASK;
        while ((base->SRAMCTL & SPC_SRAMCTL_ACK_MASK) == 0UL)
        {
            /* Wait until acknowledged */
            ;
        }
        base->SRAMCTL &= ~SPC_SRAMCTL_REQ_MASK;
    }
}

/*!
 * brief Configs Bandgap mode in Active mode.
 *
 * @note To disable bandgap in Active mode:
 *          1. Disable all LVD's and HVD's in active mode;
 *          2. Disable Glitch detect;
 *          3. Configrue LDO's and DCDC to low drive strength in active mode;
 *          4. Invoke this function to disable bandgap in active mode;
 *      otherwise the error status will be reported.
 *
 * @note Some other system resources(such as PLL, CMP) require bandgap to be enabled, to disable bandgap please
 * take care of other system resources.
 *
 * param base SPC peripheral base address.
 * param mode The Bandgap mode be selected.
 *
 * retval kStatus_SPC_BandgapModeWrong The Bandgap can not be disabled in active mode.
 * retval kStatus_Success Config Bandgap mode in Active power mode successful.
 */
status_t SPC_SetActiveModeBandgapModeConfig(SPC_Type *base, spc_bandgap_mode_t mode)
{
    uint32_t reg;
    uint32_t state;

    reg = base->ACTIVE_CFG;

    if (mode == kSPC_BandgapDisabled)
    {
        state = SPC_GetActiveModeVoltageDetectStatus(base);

        /* If any of the LVD/HVDs are kept enabled, bandgap mode must be enabled with buffer disabled. */
        if (state != 0UL)
        {
            return kStatus_SPC_BandgapModeWrong;
        }

        /* The bandgap mode must be enabled if any regulators' drive strength set as Normal. */
#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
        if ((base->ACTIVE_CFG & SPC_ACTIVE_CFG_SYSLDO_VDD_DS_MASK) ==
            SPC_ACTIVE_CFG_SYSLDO_VDD_DS(kSPC_SysLDO_NormalDriveStrength))
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
        if ((base->ACTIVE_CFG & SPC_ACTIVE_CFG_DCDC_VDD_DS_MASK) == SPC_ACTIVE_CFG_DCDC_VDD_DS(kSPC_DCDC_NormalVoltage))
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */

#if !(defined(FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT) && FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT)
        /* state of GLITCH_DETECT_DISABLE will be ignored if bandgap is disabled. */
        if ((base->ACTIVE_CFG & SPC_ACTIVE_CFG_GLITCH_DETECT_DISABLE_MASK) == 0UL)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif
#if defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS
        if ((base->ACTIVE_CFG & SPC_ACTIVE_CFG_CORELDO_VDD_DS_MASK) ==
            SPC_ACTIVE_CFG_CORELDO_VDD_DS(kSPC_CoreLDO_NormalDriveStrength))
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */
    }

    reg &= ~SPC_ACTIVE_CFG_BGMODE_MASK;
    reg |= SPC_ACTIVE_CFG_BGMODE(mode);

    base->ACTIVE_CFG = reg;

    return kStatus_Success;
}

/*!
 * brief Configs Bandgap mode in Low Power mode.
 *
 * @note To disable Bandgap in Low-power mode:
 *          1. Disable all LVD's ad HVD's in low power mode;
 *          2. Disable Glitch detect in low power mode;
 *          3. Configure LDO's and DCDC to low drive strength in low power mode;
 *          4. Disable bandgap in low power mode;
 *      Otherwise, the error status will be reported.
 *
 * @note Some other system resources(such as PLL, CMP) require bandgap to be enabled, to disable bandgap please
 * take care of other system resources.
 *
 * param base SPC peripheral base address.
 * param mode The Bandgap mode be selected.
 *
 * retval kStatus_SPC_BandgapModeWrong The bandgap mode setting in Low Power mode is wrong.
 * retval kStatus_Success Config Bandgap mode in Low Power power mode successful.
 */
status_t SPC_SetLowPowerModeBandgapmodeConfig(SPC_Type *base, spc_bandgap_mode_t mode)
{
    uint32_t reg;
    uint32_t state;

    reg = base->LP_CFG;

    if (mode == kSPC_BandgapDisabled)
    {
        state = (uint32_t)SPC_GetLowPowerModeVoltageDetectStatus(base);

        /* If any of the LVD/HVDs are kept enabled, bandgap mode must be enabled with buffer disabled. */
        if (state != 0UL)
        {
            return kStatus_SPC_BandgapModeWrong;
        }

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
        if ((base->LP_CFG & SPC_LP_CFG_DCDC_VDD_DS_MASK) == SPC_LP_CFG_DCDC_VDD_DS(kSPC_DCDC_NormalDriveStrength))
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
        if ((base->LP_CFG & SPC_LP_CFG_SYSLDO_VDD_DS_MASK) == SPC_LP_CFG_SYSLDO_VDD_DS(kSPC_SysLDO_NormalDriveStrength))
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

        if ((base->LP_CFG & SPC_LP_CFG_CORELDO_VDD_DS_MASK) ==
            SPC_LP_CFG_CORELDO_VDD_DS(kSPC_CoreLDO_NormalDriveStrength))
        {
            return kStatus_SPC_BandgapModeWrong;
        }

#if !(defined(FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT) && FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT)
        /* state of GLITCH_DETECT_DISABLE will be ignored if bandgap is disabled. */
        if ((base->LP_CFG & SPC_LP_CFG_GLITCH_DETECT_DISABLE_MASK) == 0UL)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
#endif
    }

    reg &= ~SPC_LP_CFG_BGMODE_MASK;
    reg |= SPC_LP_CFG_BGMODE(mode);
    base->LP_CFG = reg;

    return kStatus_Success;
}

/*!
 * brief Configs CORE voltage detect options.
 *
 * This function configs CORE voltage detect options.
 * Note: Setting both the voltage detect interrupt and reset
 *       enable will cause interrupt to be generated on exit from reset.
 *       If those conditioned is not desired, interrupt/reset only one is enabled.
 *
 * param base       SPC peripheral base address.
 * param config     Pointer to spc_core_voltage_detect_config_t structure.
 */
void SPC_SetCoreVoltageDetectConfig(SPC_Type *base, const spc_core_voltage_detect_config_t *config)
{
    assert(config != NULL);

    uint32_t reg = 0UL;

#if (defined(FSL_FEATURE_MCX_SPC_HAS_COREVDD_HVD) && FSL_FEATURE_MCX_SPC_HAS_COREVDD_HVD)
    reg |= (config->option.HVDInterruptEnable) ? SPC_VD_CORE_CFG_HVDIE(1U) : SPC_VD_CORE_CFG_HVDIE(0U);
    reg |= (config->option.HVDResetEnable) ? SPC_VD_CORE_CFG_HVDRE(1U) : SPC_VD_CORE_CFG_HVDRE(0U);
#endif /* FSL_FEATURE_MCX_SPC_HAS_COREVDD_HVD */
    reg |= (config->option.LVDInterruptEnable) ? SPC_VD_CORE_CFG_LVDIE(1U) : SPC_VD_CORE_CFG_LVDIE(0U);
    reg |= (config->option.LVDResetEnable) ? SPC_VD_CORE_CFG_LVDRE(1U) : SPC_VD_CORE_CFG_LVDRE(0U);

    base->VD_CORE_CFG = reg;
}

#if (defined(FSL_FEATURE_MCX_SPC_HAS_COREVDD_HVD) && FSL_FEATURE_MCX_SPC_HAS_COREVDD_HVD)
/*!
 * brief Enables the Core High Voltage Detector in Active mode.
 *
 * note If the CORE_LDO high voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable Core HVD.
 *          true    -   Enable Core High voltage detector in active mode.
 *          false   -   Disable Core High voltage detector in active mode.
 *
 * retval kStatus_Success Enable Core High Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeCoreHighVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_CORE_HVDE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_CORE_HVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the Core High Voltage Detector in Low Power mode.
 *
 * note If the CORE_LDO high voltage detect is enabled in Low Power mode,
 * please note that the bandgap must be enabled and the drive strength of each regulator
 * must not set to low in low power mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable Core HVD.
 *          true    -   Enable Core High voltage detector in low power mode.
 *          false   -   Disable Core High voltage detector in low power mode.
 *
 * retval kStatus_Success Enable Core High Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeCoreHighVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_CORE_HVDE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_CORE_HVDE_MASK;
    }

    return status;
}
#endif /* FSL_FEATURE_MCX_SPC_HAS_COREVDD_HVD */

/*!
 * brief Enables the Core VDD Low Voltage Detector in Active mode.
 *
 * note If the Core VDD high voltage detect is enabled in Active mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable Core LVD.
 *          true    -   Enable Core Low voltage detector in active mode.
 *          false   -   Disable Core Low voltage detector in active mode.
 *
 * retval kStatus_Success Enable Core Low Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeCoreLowVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_CORE_LVDE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_CORE_LVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the Core Low Voltage Detector in Low Power mode.
 *
 * note If the Core VDD low voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Low Power mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable Core HVD.
 *          true    -   Enable Core Low voltage detector in low power mode.
 *          false   -   Disable Core Low voltage detector in low power mode.
 *
 * retval kStatus_Success Enable Core Low Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeCoreLowVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_CORE_LVDE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_CORE_LVDE_MASK;
    }

    return status;
}

/*!
 * brief Set system VDD Low-voltage level selection.
 *
 * This function selects the system VDD low-voltage level. Changing system VDD low-voltage level
 * must be done after disabling the System VDD low voltage reset and interrupt.
 * 
 * @deprecated In latest RM, reserved for all devices, will removed in next release.
 * 
 * param base SPC peripheral base address.
 * param level System VDD Low-Voltage level selection. See @ref spc_low_voltage_level_select_t for details.
 */
void SPC_SetSystemVDDLowVoltageLevel(SPC_Type *base, spc_low_voltage_level_select_t level)
{
    (void)level;
    (void)base;

    /*
    uint32_t reg;

    reg = base->VD_SYS_CFG;

    base->VD_SYS_CFG &= ~(SPC_VD_SYS_CFG_LVDRE_MASK | SPC_VD_SYS_CFG_LVDIE_MASK);
    reg |= SPC_VD_SYS_CFG_LVSEL(level);

    base->VD_SYS_CFG = reg; */
}

/*!
 * brief Configs SYS VDD voltage detect options.
 *
 * This function config SYS voltage detect options.
 * Note: Setting both the voltage detect interrupt and reset
 *       enable will cause interrupt to be generated on exit from reset.
 *       If those conditioned is not desired, interrupt/reset only one is enabled.
 *
 * param base       SPC peripheral base address.
 * param config     Pointer to spc_system_voltage_detect_config_t structure.
 */
void SPC_SetSystemVoltageDetectConfig(SPC_Type *base, const spc_system_voltage_detect_config_t *config)
{
    assert(config != NULL);

    uint32_t reg = 0UL;

    reg |= (config->option.HVDInterruptEnable) ? SPC_VD_SYS_CFG_HVDIE(1U) : SPC_VD_SYS_CFG_HVDIE(0U);
    reg |= (config->option.LVDInterruptEnable) ? SPC_VD_SYS_CFG_LVDIE(1U) : SPC_VD_SYS_CFG_LVDIE(0U);
    reg |= (config->option.HVDResetEnable) ? SPC_VD_SYS_CFG_HVDRE(1U) : SPC_VD_SYS_CFG_HVDRE(0U);
    reg |= (config->option.LVDResetEnable) ? SPC_VD_SYS_CFG_LVDRE(1U) : SPC_VD_SYS_CFG_LVDRE(0U);

    base->VD_SYS_CFG = reg;

    (void)(config->level);
    /* SPC_SetSystemVDDLowVoltageLevel(base, config->level); */
}

/*!
 * brief Enables the System VDD High Voltage Detector in Active mode.
 *
 * note If the System_LDO high voltage detect is enabled in Active mode,
 * please note that the bandgap must be enabled and the drive strength of
 * each regulator must not set to low in Active mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable System HVD.
 *          true    -   Enable System High voltage detector in active mode.
 *          false   -   Disable System High voltage detector in active mode.
 *
 * retval kStatus_Success Enable System High Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeSystemHighVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_SYS_HVDE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_SYS_HVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the System VDD Low Voltage Detector in Active mode.
 *
 * note If the System_LDO low voltage detect is enabled in Active mode,
 * please note that the bandgap must be enabled and the drive strength of each
 * regulator must not set to low in Active mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable System LVD.
 *          true    -   Enable System Low voltage detector in active mode.
 *          false   -   Disable System Low voltage detector in active mode.
 *
 * retval kStatus_Success Enable the System Low Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeSystemLowVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_SYS_LVDE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_SYS_LVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the System VDD High Voltage Detector in Low Power mode.
 *
 * note If the System_LDO high voltage detect is enabled in low power mode,
 * please note that the bandgap must be enabled and the drive strength of each
 * regulator must not set to low in low power mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable System HVD.
 *          true    -   Enable System High voltage detector in low power mode.
 *          false   -   Disable System High voltage detector in low power mode.
 *
 * retval kStatus_Success Enable System High Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeSystemHighVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_SYS_HVDE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_SYS_HVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the System VDD Low Voltage Detector in Low Power mode.
 *
 * note If the System_LDO low voltage detect is enabled in Low Power mode,
 * please note that the bandgap must be enabled and the drive strength of each
 * regulator must not set to low in Low Power mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable System HVD.
 *          true    -   Enable System Low voltage detector in low power mode.
 *          false   -   Disable System Low voltage detector in low power mode.
 *
 * retval kStatus_Success Enable System Low Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeSystemLowVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_SYS_LVDE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_SYS_LVDE_MASK;
    }

    return status;
}

#if (defined(FSL_FEATURE_MCX_SPC_HAS_IOVDD_VD) && FSL_FEATURE_MCX_SPC_HAS_IOVDD_VD)
/*!
 * brief Set IO VDD Low-Voltage level selection.
 *
 * This function selects the IO VDD Low-voltage level. Changing IO VDD low-voltage level
 * must be done after disabling the IO VDD low voltage reset and interrupt.
 *
 * param base SPC peripheral base address.
 * param level IO VDD Low-voltage level selection.
 */
void SPC_SetIOVDDLowVoltageLevel(SPC_Type *base, spc_low_voltage_level_select_t level)
{
    uint32_t reg;

    reg = base->VD_IO_CFG;

    base->VD_IO_CFG &= ~(SPC_VD_IO_CFG_LVDRE_MASK | SPC_VD_IO_CFG_LVDIE_MASK | SPC_VD_IO_CFG_LVSEL_MASK);
    reg |= SPC_VD_IO_CFG_LVSEL(level);

    base->VD_IO_CFG = reg;
}

/*!
 * brief Configs IO VDD voltage detect options.
 *
 * This function config IO voltage detect options.
 * Note: Setting both the voltage detect interrupt and reset
 *       enable will cause interrupt to be generated on exit from reset.
 *       If those conditioned is not desired, interrupt/reset so only one is enabled.
 *
 * param base       SPC peripheral base address.
 * param config     Pointer to spc_IO_voltage_detect_config_t structure.
 */
void SPC_SetIOVoltageDetectConfig(SPC_Type *base, const spc_io_voltage_detect_config_t *config)
{
    assert(config != NULL);

    uint32_t reg = 0UL;

    /* Set trip voltage level. */
    SPC_SetIOVDDLowVoltageLevel(base, config->level);

    reg = base->VD_IO_CFG;
    reg &= ~(SPC_VD_IO_CFG_LVDRE_MASK | SPC_VD_IO_CFG_LVDIE_MASK | SPC_VD_IO_CFG_HVDRE_MASK | SPC_VD_IO_CFG_HVDIE_MASK);

    reg |= (config->option.HVDInterruptEnable) ? SPC_VD_IO_CFG_HVDIE(1U) : SPC_VD_IO_CFG_HVDIE(0U);
    reg |= (config->option.LVDInterruptEnable) ? SPC_VD_IO_CFG_LVDIE(1U) : SPC_VD_IO_CFG_LVDIE(0U);
    reg |= (config->option.HVDResetEnable) ? SPC_VD_IO_CFG_HVDRE(1U) : SPC_VD_IO_CFG_HVDRE(0U);
    reg |= (config->option.LVDResetEnable) ? SPC_VD_IO_CFG_LVDRE(1U) : SPC_VD_IO_CFG_LVDRE(0U);

    base->VD_IO_CFG = reg;
}

/*!
 * brief Enables the IO VDD High Voltage Detector in Active mode.
 *
 * note If the IO high voltage detect is enabled in Active mode,
 * please note that the bandgap must be enabled and the drive strength
 * of each regulator must not set to low in Active mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable IO HVD.
 *          true    -   Enable IO High voltage detector in active mode.
 *          false   -   Disable IO High voltage detector in active mode.
 *
 * retval kStatus_Success Enable IO High Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeIOHighVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_IO_HVDE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_IO_HVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the IO VDD Low Voltage Detector in Active mode.
 *
 * note If the IO low voltage detect is enabled in Active mode,
 * please note that the bandgap must be enabled and the drive strength
 * of each regulator must not set to low in Active mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable IO LVD.
 *          true    -   Enable IO Low voltage detector in active mode.
 *          false   -   Disable IO Low voltage detector in active mode.
 *
 * retval kStatus_Success Enable IO Low Voltage Detect successfully.
 */
status_t SPC_EnableActiveModeIOLowVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->ACTIVE_CFG |= SPC_ACTIVE_CFG_IO_LVDE_MASK;
    }
    else
    {
        base->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_IO_LVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the IO VDD High Voltage Detector in Low Power mode.
 *
 * note If the IO high voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Low Power mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable IO HVD.
 *          true    -   Enable IO High voltage detector in low power mode.
 *          false   -   Disable IO High voltage detector in low power mode.
 *
 * retval kStatus_Success Enable IO High Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeIOHighVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_IO_HVDE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_IO_HVDE_MASK;
    }

    return status;
}

/*!
 * brief Enables the IO VDD Low Voltage Detector in Low Power mode.
 *
 * note If the IO low voltage detect is enabled in Low Power mode, please note that the bandgap must be enabled
 * and the drive strength of each regulator must not set to low in Low Power mode.
 *
 * param base SPC peripheral base address.
 * param enable Enable/Disable IO HVD.
 *          true    -   Enable IO Low voltage detector in low power mode.
 *          false   -   Disable IO Low voltage detector in low power mode.
 *
 * retval kStatus_Success Enable IO Low Voltage Detect in low power mode successfully.
 */
status_t SPC_EnableLowPowerModeIOLowVoltageDetect(SPC_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        base->LP_CFG |= SPC_LP_CFG_IO_LVDE_MASK;
    }
    else
    {
        base->LP_CFG &= ~SPC_LP_CFG_IO_LVDE_MASK;
    }

    return status;
}
#endif /* FSL_FEATURE_MCX_SPC_HAS_IOVDD_VD */

/*!
 * brief Configs external voltage domains
 *
 * This function configs external voltage domains isolation.
 *
 * param base SPC peripheral base address.
 * param lowPowerIsoMask The mask of external domains isolate enable during low power mode.
 * param IsoMask The mask of external domains isolate.
 */
void SPC_SetExternalVoltageDomainsConfig(SPC_Type *base, uint8_t lowPowerIsoMask, uint8_t IsoMask)
{
    uint32_t reg = 0UL;

    reg |= SPC_EVD_CFG_REG_EVDISO(IsoMask) | SPC_EVD_CFG_REG_EVDLPISO(lowPowerIsoMask);
    base->EVD_CFG = reg;
}

/*!
 * brief Configs Core LDO Regulator in Active mode.
 *
 * @note The bandgap must be enabled before invoking this function.
 * @note To set Core LDO as low drive strength, all HVDs/LVDs must be disabled previously.
 *
 * param base SPC peripheral base address.
 * param option Pointer to the spc_active_mode_Core_LDO_option_t structure.
 *
 * retval kStatus_Success Config Core LDO regulator in Active power mode successful.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_BandgapModeWrong Bandgap should be enabled before invoking this function.
 * retval kStatus_SPC_CORELDOLowDriveStrengthIgnore To set Core LDO as low drive strength,
 *                                                  all LVDs/HVDs must be disabled before invoking this function.
 */
status_t SPC_SetActiveModeCoreLDORegulatorConfig(SPC_Type *base, const spc_active_mode_core_ldo_option_t *option)
{
    assert(option != NULL);

    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        return kStatus_SPC_Busy;
    }

    /* Check input parameters. */
    /*  1. Bandgap must not be disabled. */
    if (SPC_GetActiveModeBandgapMode(base) == kSPC_BandgapDisabled)
    {
        return kStatus_SPC_BandgapModeWrong;
    }

    /*  2. To set to low drive strength, all LVDs/HVDs must be disabled previously. */
    if ((SPC_GetActiveModeVoltageDetectStatus(base) != 0UL) &&
        (option->CoreLDODriveStrength == kSPC_CoreLDO_LowDriveStrength))
    {
        return kStatus_SPC_CORELDOLowDriveStrengthIgnore;
    }

    if ((uint8_t)SPC_GetActiveModeCoreLDOVDDVoltageLevel(base) != (uint8_t)(option->CoreLDOVoltage))
    {
#if defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS
        (void)SPC_SetActiveModeCoreLDORegulatorDriveStrength(base, kSPC_CoreLDO_NormalDriveStrength);
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */
        (void)SPC_SetActiveModeCoreLDORegulatorVoltageLevel(base, option->CoreLDOVoltage);
    }

#if defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS
    (void)SPC_SetActiveModeCoreLDORegulatorDriveStrength(base, option->CoreLDODriveStrength);
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */

    return kStatus_Success;
}

/*!
 * brief Set Core LDO VDD Regulator Voltage level in Active mode.
 *
 * @note In active mode, the Core LDO voltage level should only be changed when the
 *  Core LDO is in normal drive strength.
 *
 * @note Update Core LDO voltage level will set Busy flag,
 *      this function return only when busy flag is cleared by hardware
 *
 * param base SPC peripheral base address.
 * param voltageLevel Specify the voltage level of CORE LDO Regulator in Active mode, please
        refer to @ref spc_core_ldo_voltage_level_t.
 *
 * retval kStatus_SPC_CORELDOVoltageSetFail  Core LDO voltage level should only be
 *                                          changed when the CORE_LDO is in normal drive strength.
 * retval kStatus_Success Set Core LDO regulator voltage level in Active power mode successful.
 */
status_t SPC_SetActiveModeCoreLDORegulatorVoltageLevel(SPC_Type *base, spc_core_ldo_voltage_level_t voltageLevel)
{
    if ((uint8_t)voltageLevel != (uint8_t)SPC_GetActiveModeCoreLDOVDDVoltageLevel(base))
    {
#if (defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS)
        if (SPC_GetActiveModeCoreLDODriveStrength(base) != kSPC_CoreLDO_NormalDriveStrength)
        {
            return kStatus_SPC_CORELDOVoltageSetFail;
        }
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */

        base->ACTIVE_CFG =
            ((base->ACTIVE_CFG & ~SPC_ACTIVE_CFG_CORELDO_VDD_LVL_MASK) | SPC_ACTIVE_CFG_CORELDO_VDD_LVL(voltageLevel));

        /*
         * $Branch Coverage Justification$
         * $ref spc_c_ref_1$.
         */
        while ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
        {
        }
    }
    return kStatus_Success;
}

#if defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS
/*!
 * brief Set Core LDO VDD Regulator Drive Strength in Active mode.
 *
 * param base SPC peripheral base address.
 * param driveStrength Specify the drive strength of CORE LDO Regulator in Active mode, please
        refer to @ref spc_core_ldo_drive_strength_t.
 *
 * retval #kStatus_Success Set Core LDO regulator drive strength in Active power mode successful.
 * retval #kStatus_SPC_CORELDOLowDriveStrengthIgnore If any voltage detect enabled,
            core_ldo's drive strength can not set to low.
 * retval #kStatus_SPC_BandgapModeWrong The selected bandgap mode is not allowed.
 */
status_t SPC_SetActiveModeCoreLDORegulatorDriveStrength(SPC_Type *base, spc_core_ldo_drive_strength_t driveStrength)
{
    if (driveStrength == kSPC_CoreLDO_LowDriveStrength)
    {
        /* If any voltage detect feature is enabled in Active mode, then CORE_LDO's drive strength must not set to low.
         */
        if (SPC_GetActiveModeVoltageDetectStatus(base) != 0UL)
        {
            return kStatus_SPC_CORELDOLowDriveStrengthIgnore;
        }
    }

    if (driveStrength == kSPC_CoreLDO_NormalDriveStrength)
    {
        /* If specify normal drive strength, bandgap must not be disabled. */
        if (SPC_GetActiveModeBandgapMode(base) == kSPC_BandgapDisabled)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
    }

    base->ACTIVE_CFG =
        ((base->ACTIVE_CFG & ~SPC_ACTIVE_CFG_CORELDO_VDD_DS_MASK) | SPC_ACTIVE_CFG_CORELDO_VDD_DS(driveStrength));

    return kStatus_Success;
}
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */

/*!
 * brief Configs CORE LDO Regulator in low power mode
 *
 * This function configs CORE LDO Regulator in Low Power mode.
 * If CORE LDO VDD Drive Strength is set to Normal, the CORE LDO VDD regulator voltage
 * level in Active mode must be equal to the voltage level in Low power mode. And the Bandgap
 * must be programmed to select bandgap enabled.
 * Core VDD voltage levels for the Core LDO low power regulator can only be changed when the CORE
 * LDO Drive Strength is set as Normal.
 *
 * param base SPC peripheral base address.
 * param option Pointer to the spc_lowpower_mode_Core_LDO_option_t structure.
 * retval kStatus_Success Config Core LDO regulator in power mode successfully.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_CORELDOLowDriveStrengthIgnore HVDs/LVDs are not disabled before invoking this function.
 * retval kStatus_SPC_BandgapModeWrong The bandgap is not enabled before invoking this function.
 */
status_t SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC_Type *base, const spc_lowpower_mode_core_ldo_option_t *option)
{
    status_t status = kStatus_Success;

    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        /*
         * $Line Coverage Justification$
         * $ref spc_c_ref_1$.
         */
        return kStatus_SPC_Busy;
    }

    status = SPC_SetLowPowerModeCoreLDORegulatorDriveStrength(base, option->CoreLDODriveStrength);
    if (status == kStatus_Success)
    {
        (void)SPC_SetLowPowerModeCoreLDORegulatorVoltageLevel(base, option->CoreLDOVoltage);
    }

    return status;
}

/*!
 * brief Set Core LDO VDD Regulator Voltage level in Low power mode.
 *
 * @note If Core LDO's drive strengths are same in active and low power mode, the Core LDO's voltage must be set to the
 * same value in active and low power mode. Application should take care of this limitation.
 *
 * @note Some devices require Core LDO and DCDC have the same voltage level even if Core LDO is off. Application should
 * take care of this limitation.
 *
 * param base SPC peripheral base address.
 * param voltageLevel Voltage level of CORE LDO Regulator in Low power mode, please
        refer to @ref spc_core_ldo_voltage_level_t.
 *
 * retval #kStatus_SPC_Busy The SPC instance is busy to execute other operation.
 * retval #kStatus_Success Set Core LDO regulator voltage level in Low power mode successful.
 */
status_t SPC_SetLowPowerModeCoreLDORegulatorVoltageLevel(SPC_Type *base, spc_core_ldo_voltage_level_t voltageLevel)
{
    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        /*
            * $Line Coverage Justification$
            * $ref spc_c_ref_1$.
            */
        return kStatus_SPC_Busy;
    }

    base->LP_CFG = ((base->LP_CFG & ~SPC_LP_CFG_CORELDO_VDD_LVL_MASK) | SPC_LP_CFG_CORELDO_VDD_LVL(voltageLevel));

    /*
        * $Branch Coverage Justification$
        * $ref spc_c_ref_1$.
        */
    while ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Set Core LDO VDD Regulator Drive Strength in Low power mode.
 *
 * param base SPC peripheral base address.
 * param driveStrength Specify drive strength of CORE LDO in low power mode.
 *
 * retval #kStatus_SPC_CORELDOLowDriveStrengthIgnore Some voltage detect enabled, CORE LDO's drive strength can not set
 *           as low.
 * retval #kStatus_Success Set Core LDO regulator drive strength in Low power mode successful.
 * retval #kStatus_SPC_BandgapModeWrong Bandgap is disabled when attempt to set CORE LDO work as normal drive strength.
 */
status_t SPC_SetLowPowerModeCoreLDORegulatorDriveStrength(SPC_Type *base, spc_core_ldo_drive_strength_t driveStrength)
{
    if (driveStrength == kSPC_CoreLDO_LowDriveStrength)
    {
        /* If any voltage detect feature is enabled in Low Power mode, then CORE_LDO's drive strength must not set to
         * low.
         */
        if (SPC_GetLowPowerModeVoltageDetectStatus(base) != 0UL)
        {
            return kStatus_SPC_CORELDOLowDriveStrengthIgnore;
        }
    }
    else
    {
        /* To specify normal drive strength, the bandgap must be enabled in low power mode. */
        if (SPC_GetLowPowerModeBandgapMode(base) == kSPC_BandgapDisabled)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
    }

    base->LP_CFG = ((base->LP_CFG & ~SPC_LP_CFG_CORELDO_VDD_DS_MASK) | SPC_LP_CFG_CORELDO_VDD_DS(driveStrength));

    return kStatus_Success;
}

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
/*!
 * brief Configs System LDO VDD Regulator in Active mode.
 *
 * This function configs System LDO VDD Regulator in Active mode.
 * If System LDO VDD Drive Strength is set to Normal, the Bandgap mode in Active mode must be programmed
 * to a value that enable the bandgap.
 * If any voltage detects are kept enabled, configuration to set System LDO VDD drive strength to low will
 * be ignored.
 * If select System LDO VDD Regulator voltage level to Over Drive Voltage, the Drive Strength of System LDO VDD
 * Regulator must be set to Normal otherwise the regulator Drive Strength will be forced to Normal.
 * If select System LDO VDD Regulator voltage level to Over Drive Voltage, the High voltage detect must be disabled.
 * Otherwise it will be fail to regulator to Over Drive Voltage.
 *
 * param base SPC peripheral base address.
 * param option Pointer to the spc_active_mode_Sys_LDO_option_t structure.
 * retval kStatus_Success Config System LDO regulator in Active power mode successful.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_BandgapModeWrong The bandgap is not enabled before invoking this function.
 * retval kStatus_SPC_SYSLDOOverDriveVoltageFail HVD of System VDD is not disable before setting to Over Drive voltage.
 * retval kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set System LDO VDD regulator's driver strength to Low will be
 * ignored.
 */
status_t SPC_SetActiveModeSystemLDORegulatorConfig(SPC_Type *base, const spc_active_mode_sys_ldo_option_t *option)
{
    assert(option != NULL);

    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        /*
         * $Line Coverage Justification$
         * $ref spc_c_ref_1$.
         */
        return kStatus_SPC_Busy;
    }

    /* Check input parameters before setting registers. */
    /*  1. To set to low DS, all LVDs/HVDs must be disabled previously. */
    if ((SPC_GetActiveModeVoltageDetectStatus(base) != 0UL) &&
        (option->SysLDODriveStrength == kSPC_SysLDO_LowDriveStrength))
    {
        return kStatus_SPC_SYSLDOLowDriveStrengthIgnore;
    }
    /* 2. If specify normal drive strength, bandgap must not be disabled. */
    if ((SPC_GetActiveModeBandgapMode(base) == kSPC_BandgapDisabled) &&
        (option->SysLDODriveStrength == kSPC_SysLDO_NormalDriveStrength))
    {
        return kStatus_SPC_BandgapModeWrong;
    }

    /* 3. Must disable system LDO high voltage detector before specifing overdrive voltage. */
    if ((option->SysLDOVoltage == kSPC_SysLDO_OverDriveVoltage) &&
        ((SPC_GetActiveModeVoltageDetectStatus(base) & SPC_ACTIVE_CFG_SYS_HVDE_MASK) != 0UL))
    {
        return kStatus_SPC_SYSLDOOverDriveVoltageFail;
    }

    (void)SPC_SetActiveModeSystemLDORegulatorDriveStrength(base, option->SysLDODriveStrength);
    (void)SPC_SetActiveModeSystemLDORegulatorVoltageLevel(base, option->SysLDOVoltage);

    return kStatus_Success;
}

/*!
 * brief Set System LDO Regulator voltage level in Active mode.
 *
 * @note The system LDO regulator can only operate at the overdrive voltage level for a limited amount of time for the
 * life of chip.
 *
 * param base SPC peripheral base address.
 * param voltageLevel Specify the voltage level of System LDO Regulator in Active mode.
 *
 * retval #kStatus_Success Set System LDO Regulator voltage level in Active mode successfully.
 * retval #kStatus_SPC_SYSLDOOverDriveVoltageFail Must disable system LDO high voltage detector before specifing
 * overdrive voltage.
 */
status_t SPC_SetActiveModeSystemLDORegulatorVoltageLevel(SPC_Type *base, spc_sys_ldo_voltage_level_t voltageLevel)
{
    if (voltageLevel == kSPC_SysLDO_OverDriveVoltage)
    {
        /* Must disable system LDO high voltage detector before specifing overdrive voltage. */
        if ((SPC_GetActiveModeVoltageDetectStatus(base) & SPC_ACTIVE_CFG_SYS_HVDE_MASK) != 0UL)
        {
            return kStatus_SPC_SYSLDOOverDriveVoltageFail;
        }
    }

    base->ACTIVE_CFG =
        (base->ACTIVE_CFG & ~SPC_ACTIVE_CFG_SYSLDO_VDD_LVL_MASK) | SPC_ACTIVE_CFG_SYSLDO_VDD_LVL(voltageLevel);

    return kStatus_Success;
}

/*!
 * brief Set System LDO Regulator Drive Strength in Active mode.
 *
 * param base SPC peripheral base address.
 * param driveStrength Specify the drive strength  of System LDO Regulator in Active mode.
 *
 * retval #kStatus_Success Set System LDO Regulator drive strength in Active mode successfully.
 * retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Attempt to specify low drive strength is ignored due to any
            voltage detect feature is enabled in active mode.
 * retval #kStatus_SPC_BandgapModeWrong Bandgap mode in Active mode must be programmed to a value that enables
            the bandgap if attempt to specify normal drive strength.
 */
status_t SPC_SetActiveModeSystemLDORegulatorDriveStrength(SPC_Type *base, spc_sys_ldo_drive_strength_t driveStrength)
{
    if (driveStrength == kSPC_SysLDO_LowDriveStrength)
    {
        /* If enabled any LVDs or HVDs, SPC will ignore the attempt to specify low drive strength. */
        if (SPC_GetActiveModeVoltageDetectStatus(base) != 0UL)
        {
            return kStatus_SPC_SYSLDOLowDriveStrengthIgnore;
        }
    }

    if (driveStrength == kSPC_SysLDO_NormalDriveStrength)
    {
        /* If specify normal drive strength, bandgap must not be disabled. */
        if (SPC_GetActiveModeBandgapMode(base) == kSPC_BandgapDisabled)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
    }

    base->ACTIVE_CFG =
        (base->ACTIVE_CFG & ~SPC_ACTIVE_CFG_SYSLDO_VDD_DS_MASK) | SPC_ACTIVE_CFG_SYSLDO_VDD_DS(driveStrength);

    return kStatus_Success;
}

/*!
 * brief Configs System LDO regulator in low power modes.
 *
 * This function configs System LDO regulator in low power modes.
 * If System LDO VDD Regulator Drive strength is set to normal, bandgap mode in low power
 * mode must be programmed to a value that enables the Bandgap.
 * If any High voltage detectors or Low Voltage detectors are kept enabled, configuration
 * to set System LDO Regulator drive strength as Low will be ignored.
 *
 * param base SPC peripheral base address.
 * param option Pointer to spc_lowpower_mode_Sys_LDO_option_t structure.
 *
 * retval kStatus_Success Config System LDO regulator in Low Power Mode successfully.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_BandgapModeWrong The bandgap mode setting in Low Power Mode is wrong.
 * retval kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 */
status_t SPC_SetLowPowerModeSystemLDORegulatorConfig(SPC_Type *base, const spc_lowpower_mode_sys_ldo_option_t *option)
{
    status_t status;

    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        /*
         * $Line Coverage Justification$
         * $ref spc_c_ref_1$.
         */
        return kStatus_SPC_Busy;
    }

    status = SPC_SetLowPowerModeSystemLDORegulatorDriveStrength(base, option->SysLDODriveStrength);

    return status;
}

/*!
 * brief Set System LDO Regulator drive strength in Low Power Mode.
 *
 * param base SPC peripheral base address.
 * param driveStrength Specify the drive strength of System LDO Regulator in Low Power Mode.
 *
 * retval #kStatus_Success Set System LDO Regulator drive strength in Low Power Mode successfully.
 * retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Attempt to specify low drive strength is ignored due to any
            voltage detect feature is enabled in low power mode.
 * retval #kStatus_SPC_BandgapModeWrong Bandgap mode in low power mode must be programmed to a value that enables
            the bandgap if attempt to specify normal drive strength.
 */
status_t SPC_SetLowPowerModeSystemLDORegulatorDriveStrength(SPC_Type *base, spc_sys_ldo_drive_strength_t driveStrength)
{
    if (driveStrength == kSPC_SysLDO_LowDriveStrength)
    {
        /* If enabled any LVDs or HVDs, SPC will ignore the attempt to specify low drive strength. */
        if (SPC_GetLowPowerModeVoltageDetectStatus(base) != 0UL)
        {
            return kStatus_SPC_SYSLDOLowDriveStrengthIgnore;
        }
    }
    else
    {
        /* If specify normal drive strength, bandgap must not be disabled. */
        if (SPC_GetLowPowerModeBandgapMode(base) == kSPC_BandgapDisabled)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
    }

    base->LP_CFG = (base->LP_CFG & ~SPC_LP_CFG_SYSLDO_VDD_DS_MASK) | SPC_LP_CFG_SYSLDO_VDD_DS(driveStrength);

    return kStatus_Success;
}
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
/*!
 * brief Configs DCDC VDD Regulator in Active mode.
 *
 * note When changing the DCDC output voltage level, take care to change the CORE LDO voltage level.
 *
 * param base SPC peripheral base address.
 * param option Pointer to the spc_active_mode_DCDC_option_t structure.
 *
 * retval kStatus_Success Config DCDC regulator in Active power mode successful.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_BandgapModeWrong The bandgap mode setting in Active mode is wrong.
 */
status_t SPC_SetActiveModeDCDCRegulatorConfig(SPC_Type *base, const spc_active_mode_dcdc_option_t *option)
{
    assert(option != NULL);
    status_t status = kStatus_Success;

    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        /*
         * $Line Coverage Justification$
         * $ref spc_c_ref_1$.
         */
        return kStatus_SPC_Busy;
    }

    status = SPC_SetActiveModeDCDCRegulatorDriveStrength(base, option->DCDCDriveStrength);

    if (status == kStatus_Success)
    {
        SPC_SetActiveModeDCDCRegulatorVoltageLevel(base, option->DCDCVoltage);
    }

    /*
     * $Branch Coverage Justification$
     * $ref spc_c_ref_1$.
     */
    while ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
    }

    return status;
}

/*!
 * brief Set DCDC VDD Regulator drive strength in Active mode.
 *
 * note To set DCDC drive strength as Normal, the bandgap must be enabled.
 *
 * param base SPC peripheral base address.
 * param driveStrength Specify the DCDC VDD regulator drive strength, please refer to @ref spc_dcdc_drive_strength_t.
 *
 * retval #kStatus_Success Set DCDC VDD Regulator drive strength in Active mode successfully.
 * retval #kStatus_SPC_BandgapModeWrong Set DCDC VDD Regulator drive strength to Normal, the Bandgap must be enabled.
 */
status_t SPC_SetActiveModeDCDCRegulatorDriveStrength(SPC_Type *base, spc_dcdc_drive_strength_t driveStrength)
{
    if (driveStrength == kSPC_DCDC_NormalDriveStrength)
    {
        /* If specify normal drive strength, bandgap must not be disabled. */
        if (SPC_GetActiveModeBandgapMode(base) == kSPC_BandgapDisabled)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
    }

    base->ACTIVE_CFG =
        ((base->ACTIVE_CFG) & (~SPC_ACTIVE_CFG_DCDC_VDD_DS_MASK)) | SPC_ACTIVE_CFG_DCDC_VDD_DS(driveStrength);

    return kStatus_Success;
}

/*!
 * brief Configs DCDC VDD Regulator in Low power modes.
 *
 * If DCDC VDD Drive Strength is set to Normal, the Bandgap mode in Low Power mode must be programmed
 * to a value that enables the Bandgap.
 * In Deep Power Down mode, DCDC regulator is always turned off.
 *
 * param base SPC peripheral base address.
 * param option Pointer to the spc_lowpower_mode_DCDC_option_t structure.
 *
 * retval kStatus_Success Config DCDC regulator in low power mode successfully.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_BandgapModeWrong The bandgap should be enabled before invoking this function.
 */
status_t SPC_SetLowPowerModeDCDCRegulatorConfig(SPC_Type *base, const spc_lowpower_mode_dcdc_option_t *option)
{
    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        /*
         * $Line Coverage Justification$
         * $ref spc_c_ref_1$.
         */
        return kStatus_SPC_Busy;
    }

    /* Check input parameter before setting registers. */
    if ((option->DCDCDriveStrength == kSPC_DCDC_NormalDriveStrength) &&
        (SPC_GetLowPowerModeBandgapMode(base) == kSPC_BandgapDisabled))
    {
        return kStatus_SPC_BandgapModeWrong;
    }

    /*
        1. Configure to desired voltage level.
        2. Change to low drive strength.
        3. Configure same voltage level in active mode.
    */
    SPC_SetLowPowerModeDCDCRegulatorVoltageLevel(base, option->DCDCVoltage);

    /* Change to desired drive strength. */
    if (option->DCDCDriveStrength != kSPC_DCDC_LowDriveStrength)
    {
        (void)SPC_SetLowPowerModeDCDCRegulatorDriveStrength(base, option->DCDCDriveStrength);
    }

    /*
     * $Branch Coverage Justification$
     * $ref spc_c_ref_1$.
     */
    while ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
    }

    return kStatus_Success;
}

/*!
 * brief Set DCDC VDD Regulator drive strength in Low power mode.
 *
 * param base SPC peripheral base address.
 * param driveStrength Specify the DCDC VDD Regulator drive strength, please refer to @ref spc_dcdc_drive_strength_t.
 *
 * retval #kStatus_Success Set DCDC VDD Regulator drive strength in Low power mode successfully.
 * retval #kStatus_SPC_BandgapModeWrong Set DCDC VDD Regulator drive strength to Normal, the Bandgap must be enabled.
 */
status_t SPC_SetLowPowerModeDCDCRegulatorDriveStrength(SPC_Type *base, spc_dcdc_drive_strength_t driveStrength)
{
    if (driveStrength == kSPC_DCDC_NormalDriveStrength)
    {
        /* If specify normal drive strength, bandgap must not be disabled. */
        if (SPC_GetLowPowerModeBandgapMode(base) == kSPC_BandgapDisabled)
        {
            return kStatus_SPC_BandgapModeWrong;
        }
    }

    base->LP_CFG = ((base->LP_CFG) & (~SPC_LP_CFG_DCDC_VDD_DS_MASK)) | SPC_LP_CFG_DCDC_VDD_DS(driveStrength);

    return kStatus_Success;
}

/*!
 * brief Config DCDC Burst options
 *
 * param base SPC peripheral base address.
 * param config Pointer to spc_DCDC_burst_config_t structure.
 */
void SPC_SetDCDCBurstConfig(SPC_Type *base, spc_dcdc_burst_config_t *config)
{
    assert(config != NULL);
    uint32_t reg;
    reg = base->DCDC_CFG;
    reg &= ~(SPC_DCDC_CFG_FREQ_CNTRL_MASK | SPC_DCDC_CFG_FREQ_CNTRL_ON_MASK);
    reg |= SPC_DCDC_CFG_FREQ_CNTRL(config->freq);
    reg |= config->stabilizeBurstFreq ? SPC_DCDC_CFG_FREQ_CNTRL_ON(1U) : SPC_DCDC_CFG_FREQ_CNTRL_ON(0U);
    base->DCDC_CFG = reg;

    /* Blocking until previous DCDC burst completed. */
    while ((base->DCDC_BURST_CFG & SPC_DCDC_BURST_CFG_BURST_ACK_MASK) == 0UL)
    {
    }

    if ((config->sofwareBurstRequest) || (config->externalBurstRequest))
    {
        /* Clear DCDC burst acknowledge flag. */
        base->DCDC_BURST_CFG |= SPC_DCDC_BURST_CFG_BURST_ACK_MASK;
    }
    base->DCDC_BURST_CFG |= SPC_DCDC_BURST_CFG_EXT_BURST_EN(config->externalBurstRequest);

    if (config->sofwareBurstRequest)
    {
        base->DCDC_BURST_CFG |= SPC_DCDC_BURST_CFG_BURST_REQ_MASK;
    }
}

/*!
 * brief Set the count value of the reference clock.
 *
 * This function set the count value of the reference clock to control the frequency
 * of dcdc refresh when dcdc is configured in Pulse Refresh mode.
 *
 * param base SPC peripheral base address.
 * param count The count value, 16 bit width.
 */
void SPC_SetDCDCRefreshCount(SPC_Type *base, uint16_t count)
{
    uint32_t reg;

    reg = base->DCDC_BURST_CFG;
    reg &= ~SPC_DCDC_BURST_CFG_PULSE_REFRESH_CNT_MASK;
    reg |= SPC_DCDC_BURST_CFG_PULSE_REFRESH_CNT(count);

    base->DCDC_BURST_CFG = reg;
}
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */

/*!
 * brief Configs all settings of regulators in Active mode at a time.
 *
 * @note This function is used to overwrite all settings of regulators(including bandgap mode, regulators'
 * drive strength and voltage level) in active mode at a time.
 *
 * @note Enable/disable LVDs/HVDs before invoking this function.
 *
 * @note This function will check input parameters based on hardware restrictions before setting registers, if input
 * parameters do not satisfy hardware restrictions the specific error will be reported.
 *
 *
 * @note Some hardware restrictions not covered, application should be aware of this and follow this hardware
 * restrictions otherwise some unkown issue may occur:
 *        1. If Core LDO's drive strength are set to same value in both Active mode and low power mode,
 *          the voltage level should also set to same value.
 *        2. When switching Core LDO's drive strength from low to normal, ensure the LDO_CORE high voltage level is set
 *          to same level that was set prior to switching to the LDO_CORE drive strength. Otherwise, if the LVDs are
 *          enabled, an unexpected LVD can occur.
 *
 * @note If this function can not satisfy some tricky settings, please invoke other low-level functions.
 *
 * param base SPC peripheral base address.
 * param config Pointer to spc_active_mode_regulators_config_t structure.
 * retval kStatus_Success Config regulators in Active power mode successful.
 * retval kStatus_SPC_BandgapModeWrong The bandgap mode setting in Active mode is wrong.
 * retval kStatus_SPC_Busy The SPC instance is busy to execute any type of power mode transition.
 * retval kStatus_SPC_CORELDOVoltageWrong The selected voltage level in active mode is not allowed.
 * retval kStatus_SPC_SYSLDOOverDriveVoltageFail Fail to regulator to Over Drive Voltage.
 * retval kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to Low will be ignored.
 * retval kStatus_SPC_DCDCLowDriveStrengthIgnore Set driver strength to Low will be ignored.
 */
status_t SPC_SetActiveModeRegulatorsConfig(SPC_Type *base, const spc_active_mode_regulators_config_t *config)
{
    assert(config != NULL);

    uint32_t activeModeVDValue = SPC_GetActiveModeVoltageDetectStatus(base);

    /* Check input parameters */
    /*  1. Bandgap should not be disabled if any of regulator in normal drive strength or
            if any of LVDs/HVDs are enabled or if VDD CORE glitch detect are enabled. */
    if ((config->bandgapMode == kSPC_BandgapDisabled) &&
        ((activeModeVDValue != 0UL)
#if !(defined(FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT) && FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT)
         || (SPC_CheckActiveModeVddCoreGlitchDetectEnabled(base) == true)
#endif /* FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT */
#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
         || (config->DCDCOption.DCDCDriveStrength == kSPC_DCDC_NormalDriveStrength)
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */
#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
         || (config->SysLDOOption.SysLDODriveStrength == kSPC_SysLDO_NormalDriveStrength)
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */
#if (defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS)
         || (config->CoreLDOOption.CoreLDODriveStrength == kSPC_CoreLDO_NormalDriveStrength)
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */
             ))
    {
        return kStatus_SPC_BandgapModeWrong;
    }

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
    /*  2. Must disable system LDO high voltage detector before specifing SysLDO to overdrive voltage  */
    if (((activeModeVDValue & SPC_ACTIVE_CFG_SYS_HVDE_MASK) != 0UL) &&
        (config->SysLDOOption.SysLDOVoltage == kSPC_SysLDO_OverDriveVoltage))
    {
        return kStatus_SPC_SYSLDOOverDriveVoltageFail;
    }
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
    /* 3. To set System LDO's drive strength to low, all LVDs and HVDs must be disabled. */
    if ((activeModeVDValue != 0UL) && (config->SysLDOOption.SysLDODriveStrength == kSPC_SysLDO_LowDriveStrength))
    {
        return kStatus_SPC_SYSLDOLowDriveStrengthIgnore;
    }
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS)
    /* 4. To set Core LDO's drive strength to low, all LVDs and HVDs must be disabled. */
    if ((activeModeVDValue != 0UL) && (config->CoreLDOOption.CoreLDODriveStrength == kSPC_CoreLDO_LowDriveStrength))
    {
        return kStatus_SPC_CORELDOLowDriveStrengthIgnore;
    }
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
    /* 5. Core LDO and DCDC should have same voltage level. */
    if ((uint8_t)config->DCDCOption.DCDCVoltage != (uint8_t)config->CoreLDOOption.CoreLDOVoltage)
    {
        return kStatus_SPC_CORELDOVoltageWrong;
    }
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */

    if ((base->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
        return kStatus_SPC_Busy;
    }

    base->ACTIVE_CFG =
        ((base->ACTIVE_CFG) & ~(SPC_ACTIVE_CFG_BGMODE_MASK)) | SPC_ACTIVE_CFG_BGMODE(config->bandgapMode);
#if (defined(FSL_FEATURE_MCX_SPC_HAS_LPBUFF_EN_BIT) && FSL_FEATURE_MCX_SPC_HAS_LPBUFF_EN_BIT)
    SPC_EnableActiveModeCMPBandgapBuffer(base, config->lpBuff);
#endif /* FSL_FEATURE_MCX_SPC_HAS_LPBUFF_EN_BIT */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
    (void)SPC_SetActiveModeSystemLDORegulatorConfig(base, &config->SysLDOOption);
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
    (void)SPC_SetActiveModeDCDCRegulatorConfig(base, &config->DCDCOption);
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */

    (void)SPC_SetActiveModeCoreLDORegulatorConfig(base, &config->CoreLDOOption);

    return kStatus_Success;
}

/*!
 * brief Configs regulators in Low Power mode.
 *
 * This function provides the method to config all on-chip regulators in Low Power mode.
 *
 * param base SPC peripheral base address.
 * param config Pointer to spc_lowpower_mode_regulators_config_t structure.
 * retval #kStatus_Success Config regulators in Low power mode successful.
 * retval #kStatus_SPC_BandgapModeWrong The bandgap should not be disabled based on input settings.
 * retval #kStatus_SPC_CORELDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 * retval #kStatus_SPC_SYSLDOLowDriveStrengthIgnore Set driver strength to low will be ignored.
 * retval #kStatus_SPC_CORELDOVoltageWrong Core LDO and System LDO do not have same voltage level.
 */
status_t SPC_SetLowPowerModeRegulatorsConfig(SPC_Type *base, const spc_lowpower_mode_regulators_config_t *config)
{
    assert(config != NULL);
    uint32_t lpModeVDValue = SPC_GetLowPowerModeVoltageDetectStatus(base);

    /* Check input parameters */
    /*  1. Bandgap should not be disabled if any of regulator in normal drive strength or
            if any of LVDs/HVDs are enabled or if VDD CORE glitch detect are enabled. */
    if ((config->bandgapMode == kSPC_BandgapDisabled) &&
        ((lpModeVDValue != 0UL)
#if !(defined(FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT) && FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT)
         || (SPC_CheckLowPowerModeVddCoreGlitchDetectEnabled(base) == true)
#endif /* FSL_FEATURE_MCX_SPC_HAS_NO_GLITCH_DETECT */
#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
         || (config->DCDCOption.DCDCDriveStrength == kSPC_DCDC_NormalDriveStrength)
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */
#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
         || (config->SysLDOOption.SysLDODriveStrength == kSPC_SysLDO_NormalDriveStrength)
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */
#if (defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS)
         || (config->CoreLDOOption.CoreLDODriveStrength == kSPC_CoreLDO_NormalDriveStrength)
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */
             ))
    {
        return kStatus_SPC_BandgapModeWrong;
    }

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
    /* 2. To set System LDO's drive strength to low, all LVDs and HVDs must be disabled. */
    if ((lpModeVDValue != 0UL) && (config->SysLDOOption.SysLDODriveStrength == kSPC_SysLDO_LowDriveStrength))
    {
        return kStatus_SPC_SYSLDOLowDriveStrengthIgnore;
    }
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS) && FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS)
    /* 3. To set Core LDO's drive strength to low, all LVDs and HVDs must be disabled. */
    if ((lpModeVDValue != 0UL) && (config->CoreLDOOption.CoreLDODriveStrength == kSPC_CoreLDO_LowDriveStrength))
    {
        return kStatus_SPC_CORELDOLowDriveStrengthIgnore;
    }
#endif /* FSL_FEATURE_SPC_HAS_CORELDO_VDD_DS */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
    /* 5. Core LDO and DCDC should have same voltage level. */
    if ((uint8_t)config->DCDCOption.DCDCVoltage != (uint8_t)config->CoreLDOOption.CoreLDOVoltage)
    {
        return kStatus_SPC_CORELDOVoltageWrong;
    }
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */
    base->LP_CFG = ((base->LP_CFG) & ~(SPC_LP_CFG_BGMODE_MASK)) | SPC_LP_CFG_BGMODE(config->bandgapMode);
#if (defined(FSL_FEATURE_MCX_SPC_HAS_LPBUFF_EN_BIT) && FSL_FEATURE_MCX_SPC_HAS_LPBUFF_EN_BIT)
    SPC_EnableLowPowerModeCMPBandgapBuffer(base, config->lpBuff);
#endif /* FSL_FEATURE_MCX_SPC_HAS_LPBUFF_EN_BIT */
#if (defined(FSL_FEATURE_MCX_SPC_HAS_COREVDD_IVS_EN_BIT) && FSL_FEATURE_MCX_SPC_HAS_COREVDD_IVS_EN_BIT)
    SPC_EnableLowPowerModeCoreVDDInternalVoltageScaling(base, config->CoreIVS);
#endif /* FSL_FEATURE_MCX_SPC_HAS_COREVDD_IVS_EN_BIT */
    SPC_EnableLowPowerModeLowPowerIREF(base, config->lpIREF);

#if (defined(FSL_FEATURE_MCX_SPC_HAS_SYS_LDO) && FSL_FEATURE_MCX_SPC_HAS_SYS_LDO)
    (void)SPC_SetLowPowerModeSystemLDORegulatorConfig(base, &config->SysLDOOption);
#endif /* FSL_FEATURE_MCX_SPC_HAS_SYS_LDO */

#if (defined(FSL_FEATURE_MCX_SPC_HAS_DCDC) && FSL_FEATURE_MCX_SPC_HAS_DCDC)
    (void)SPC_SetLowPowerModeDCDCRegulatorConfig(base, &config->DCDCOption);
#endif /* FSL_FEATURE_MCX_SPC_HAS_DCDC */

    (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(base, &config->CoreLDOOption);

    return kStatus_Success;
}
