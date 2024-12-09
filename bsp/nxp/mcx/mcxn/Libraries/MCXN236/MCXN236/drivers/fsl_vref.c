/*
 * Copyright 2019-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_vref.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.vref_1"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Gets the instance from the base address
 *
 * @param base VREF peripheral base address
 *
 * @return The VREF instance
 */
static uint32_t VREF_GetInstance(VREF_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to VREF bases for each instance. */
static VREF_Type *const s_vrefBases[] = VREF_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to VREF clocks for each instance. */
static const clock_ip_name_t s_vrefClocks[] = VREF_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t VREF_GetInstance(VREF_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    /*
     * $Branch Coverage Justification$
     * (instance >= ARRAY_SIZE(s_vrefBases)) not covered. The peripheral base
     * address is always valid and checked by assert.
     */
    for (instance = 0; instance < ARRAY_SIZE(s_vrefBases); instance++)
    {
        /*
         * $Branch Coverage Justification$
         * (s_vrefBases[instance] != base) not covered. The peripheral base
         * address is always valid and checked by assert.
         */
        if (s_vrefBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_vrefBases));

    return instance;
}

/*!
 * brief Enables the clock gate and configures the VREF module according to the configuration structure.
 *
 * This function must be called before calling all other VREF driver functions, read/write registers, and
 * configurations with user-defined settings. The example below shows how to set up vref_config_t parameters
 * and how to call the VREF_Init function by passing in these parameters.
 * code
 *    vref_config_t vrefConfig;
 *    VREF_GetDefaultConfig(VREF, &vrefConfig);
 *    vrefConfig.bufferMode = kVREF_ModeHighPowerBuffer;
 *    VREF_Init(VREF, &vrefConfig);
 * endcode
 *
 * param base VREF peripheral address.
 * param config Pointer to the configuration structure.
 */
void VREF_Init(VREF_Type *base, const vref_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32 = 0UL;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate clock for VREF */
    CLOCK_EnableClock(s_vrefClocks[VREF_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    base->CSR |= VREF_CSR_LPBGEN_MASK;
    /* After enabling low power bandgap, delay 20 us. */
    SDK_DelayAtLeastUs(20U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* Provides bias current for other peripherals. */
    if (config->enableLowPowerBuff)
    {
        base->CSR |= VREF_CSR_LPBG_BUF_EN_MASK;
    }

    if (config->bufferMode != kVREF_ModeBandgapOnly)
    {
        if (config->enableHCBandgap)
        {
            tmp32 |= VREF_CSR_HCBGEN_MASK;
        }

        if (config->enableInternalVoltageRegulator)
        {
            tmp32 |= VREF_CSR_REGEN_MASK;
        }

        if (config->enableChopOscillator)
        {
            tmp32 |= (VREF_CSR_REGEN_MASK | VREF_CSR_CHOPEN_MASK);
        }

        if (config->enableCurvatureCompensation)
        {
            tmp32 |= VREF_CSR_ICOMPEN_MASK;
        }

        if (config->bufferMode == kVREF_ModeLowPowerBuffer)
        {
            tmp32 |= VREF_CSR_BUF21EN_MASK;
        }
        else
        {
            tmp32 |= (VREF_CSR_BUF21EN_MASK | VREF_CSR_HI_PWR_LV_MASK);
        }

        base->CSR |= tmp32;
        /* After enabling high accurancy bandgap, delay 400 us. */
        SDK_DelayAtLeastUs(400U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}

/*!
 * brief Stops and disables the clock for the VREF module.
 *
 * This function should be called to shut down the module.
 * This is an example.
 * code
 *    vref_config_t vrefUserConfig;
 *    VREF_GetDefaultConfig(VREF, &vrefUserConfig);
 *    VREF_Init(VREF, &vrefUserConfig);
 *    ...
 *    VREF_Deinit(VREF);
 * endcode
 *
 * param base VREF peripheral address.
 */
void VREF_Deinit(VREF_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate clock for VREF */
    CLOCK_DisableClock(s_vrefClocks[VREF_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initializes the VREF configuration structure.
 *
 * This function initializes the VREF configuration structure to default values.
 * This is an example.
 * code
 *    config->bufferMode = kVREF_ModeHighPowerBuffer;
 *    config->enableInternalVoltageRegulator = true;
 *    config->enableChopOscillator           = true;
 *    config->enableHCBandgap                = true;
 *    config->enableCurvatureCompensation    = true;
 *    config->enableLowPowerBuff             = true;
 * endcode
 *
 * param config Pointer to the initialization structure.
 */
void VREF_GetDefaultConfig(vref_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->bufferMode                     = kVREF_ModeHighPowerBuffer;
    config->enableInternalVoltageRegulator = true;
    config->enableChopOscillator           = true;
    config->enableHCBandgap                = true;
    config->enableCurvatureCompensation    = true;
    config->enableLowPowerBuff             = true;
}

/*!
 * brief Sets a TRIM value for the accurate 1.0V bandgap output.
 *
 * This function sets a TRIM value for the reference voltage. It will trim the accurate 1.0V bandgap by 0.5mV each step.
 *
 * param base VREF peripheral address.
 * param trimValue Value of the trim register to set the output reference voltage (maximum 0x3F (6-bit)).
 */
void VREF_SetVrefTrimVal(VREF_Type *base, uint8_t trimValue)
{
    uint32_t tmp32 = base->UTRIM;

    tmp32 &= (~VREF_UTRIM_VREFTRIM_MASK);
    tmp32 |= VREF_UTRIM_VREFTRIM(trimValue);

    base->UTRIM = tmp32;

    if (VREF_CSR_CHOPEN_MASK == (base->CSR & VREF_CSR_CHOPEN_MASK))
    {
        /* After enabling high accurancy bandgap, delay 400 us. */
        SDK_DelayAtLeastUs(400U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    else
    {
        /*Wait internal HC voltage reference stable*/
        /*
         * $Branch Coverage Justification$
         * while ((base->CSR & VREF_CSR_VREFST_MASK) != 0U) not covered. Test unfeasible,
         * the internal HC voltage stable state is too short not to catch.
         */
        while ((base->CSR & VREF_CSR_VREFST_MASK) == 0U)
        {
        }
    }
}

/*!
 * brief Sets a TRIM value for the accurate buffered VREF output.
 *
 * This function sets a TRIM value for the reference voltage. If buffer mode be set to other values (Buf21
 * enabled), it will trim the VREF_OUT by 0.1V each step from 1.0V to 2.1V.
 *
 * note When Buf21 is enabled, the value of UTRIM[TRIM2V1] should be ranged from 0b0000 to 0b1011 in order to trim the
 * output voltage from 1.0V to 2.1V, other values will make the VREF_OUT to default value, 1.0V.
 *
 * param base VREF peripheral address.
 * param trim21Value Value of the trim register to set the output reference voltage (maximum 0xF (4-bit)).
 */
void VREF_SetTrim21Val(VREF_Type *base, uint8_t trim21Value)
{
    uint32_t tmp32 = base->UTRIM;

    tmp32 &= (~VREF_UTRIM_TRIM2V1_MASK);
    tmp32 |= VREF_UTRIM_TRIM2V1(trim21Value);

    base->UTRIM = tmp32;

    if (VREF_CSR_CHOPEN_MASK == (base->CSR & VREF_CSR_CHOPEN_MASK))
    {
        /* After enabling high accurancy bandgap, delay 400 us. */
        SDK_DelayAtLeastUs(400U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    else
    {
        /*Wait internal HC voltage reference stable*/
        /*
         * $Branch Coverage Justification$
         * while ((base->CSR & VREF_CSR_VREFST_MASK) != 0U) not covered. Test unfeasible,
         * the internal HC voltage stable state is too short not to catch.
         */
        while ((base->CSR & VREF_CSR_VREFST_MASK) == 0U)
        {
        }
    }
}

/*!
 * brief Reads the VREF trim value.
 *
 * This function gets the TRIM value from the UTRIM register. It reads UTRIM[VREFTRIM] (13:8)
 *
 * param base VREF peripheral address.
 * return 6-bit value of trim setting.
 */
uint8_t VREF_GetVrefTrimVal(VREF_Type *base)
{
    uint8_t trimValue;

    trimValue = (uint8_t)((base->UTRIM & VREF_UTRIM_VREFTRIM_MASK) >> VREF_UTRIM_VREFTRIM_SHIFT);

    return trimValue;
}

/*!
 * brief Reads the VREF 2.1V trim value.
 *
 * This function gets the TRIM value from the UTRIM register. It reads UTRIM[TRIM2V1] (3:0),
 *
 * param base VREF peripheral address.
 * return 4-bit value of trim setting.
 */
uint8_t VREF_GetTrim21Val(VREF_Type *base)
{
    uint8_t trimValue;

    trimValue = (uint8_t)((base->UTRIM & VREF_UTRIM_TRIM2V1_MASK) >> VREF_UTRIM_TRIM2V1_SHIFT);

    return trimValue;
}
