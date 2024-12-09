/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_tdet.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tdet"
#endif

/* all bits defined in the LOCK Register. */
#define TDET_ALL_LC_MASK 0x00FF3FF0u

/* all bits defined in the Interrupt Enable Register. */
#define TDET_ALL_IER_MASK 0x00FF03FDu

/* all bits defined in the Tamper Enable Register. */
#define TDET_ALL_TER_MASK 0x00FF0FFCu

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * Weak implementation of TDET IRQ, should be re-defined by user when using TDET IRQ
 */
__WEAK void VBAT0_DriverIRQHandler(void)
{
    /* TDET generates IRQ until corresponding bit in STATUS is cleared by calling
     * TDET_ClearStatusFlags(TDET0,kTDET_StatusAll);
     * which clear all bits or kTDET_StatusXXX to clear only one bit
     */
}

static bool tdet_IsRegisterWriteAllowed(DIGTMP_Type *base, uint32_t mask)
{
    bool retval;

    retval = false;
    mask   = mask & TDET_ALL_LC_MASK;

    /* specified LR bit(s) must be set */
    if (mask == (mask & base->LR))
    {
        retval = true;
    }
    return retval;
}

static status_t tdet_PinConfigure(DIGTMP_Type *base, const tdet_pin_config_t *pinConfig, uint32_t pin)
{
    uint32_t temp;
    uint32_t mask;
    status_t status;

    if ((tdet_IsRegisterWriteAllowed(
            base, DIGTMP_LR_PDL_MASK | DIGTMP_LR_PPL_MASK | (((uint32_t)1u << DIGTMP_LR_GFL0_SHIFT) << pin))) &&
        (pinConfig != NULL))
    {
        /* pin 0 to 7 selects bit0 to bit7 */
        mask = ((uint32_t)1u << pin);

        /* Pin Direction Register */
        temp = base->PDR;
        temp &= ~mask; /* clear the bit */
        if (kTDET_TamperPinDirectionOut == pinConfig->pinDirection)
        {
            temp |= mask; /* set the bit, if configured */
        }
        base->PDR = temp;

        /* Pin Polarity Register */
        temp = base->PPR;
        temp &= ~mask; /* clear the bit */
        if (kTDET_TamperPinPolarityExpectInverted == pinConfig->pinPolarity)
        {
            temp |= mask; /* set the bit, if configured */
        }
        base->PPR = temp;

        /* compute and set the configured value to the glitch filter register */
        temp = 0;
        temp |= DIGTMP_PGFR_GFW(pinConfig->glitchFilterWidth);
        temp |= DIGTMP_PGFR_GFP(pinConfig->glitchFilterPrescaler);
        temp |= DIGTMP_PGFR_TPSW(pinConfig->tamperPinSampleWidth);
        temp |= DIGTMP_PGFR_TPSF(pinConfig->tamperPinSampleFrequency);
        temp |= DIGTMP_PGFR_TPEX(pinConfig->tamperPinExpected);
        temp |= DIGTMP_PGFR_TPE(pinConfig->tamperPullEnable);
        temp |= DIGTMP_PGFR_TPS(pinConfig->tamperPullSelect);
        /* make sure the glitch filter is disabled when we configure glitch filter width */
        base->PGFR[pin] = temp;
        /* add glitch filter enabled */
        if (pinConfig->glitchFilterEnable)
        {
            temp |= DIGTMP_PGFR_GFE(1u);
            base->PGFR[pin] = temp;
        }
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

static status_t tdet_ActiveTamperConfigure(DIGTMP_Type *base,
                                           const tdet_active_tamper_config_t *activeTamperConfig,
                                           uint32_t activeTamperRegister)
{
    uint32_t temp;
    status_t status;

    /* check if writing to active tamper register is allowed */
    if ((tdet_IsRegisterWriteAllowed(base, ((uint32_t)1u << DIGTMP_LR_ATL0_SHIFT) << activeTamperRegister)) &&
        (activeTamperConfig != NULL))
    {
        /* compute and set the configured value to the active tamper register */
        temp = 0;
        temp |= DIGTMP_ATR_ATSR(activeTamperConfig->activeTamperShift);
        temp |= DIGTMP_ATR_ATP(activeTamperConfig->activeTamperPolynomial);
        base->ATR[activeTamperRegister] = temp;
        status                          = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Initialize TDET
 *
 * This function initializes TDET.
 *
 * param base TDET peripheral base address
 * return Status of the init operation
 */
status_t TDET_Init(DIGTMP_Type *base)
{
    return kStatus_Success;
}

/*!
 * brief Deinitialize TDET
 *
 * This function disables glitch filters and active tampers
 * This function disables the TDET clock and prescaler in TDET Control Register.
 * param base TDET peripheral base address
 */
void TDET_Deinit(DIGTMP_Type *base)
{
    uint32_t i, j, k;
    j = ARRAY_SIZE(base->PGFR);
    k = ARRAY_SIZE(base->ATR);
    /* disable all glitch filters and active tampers */
    for (i = 0; i < j; i++)
    {
        base->PGFR[i] = 0;
    }
    for (i = 0; i < k; i++)
    {
        base->ATR[i] = 0;
    }

    /* disable inner TDET clock and prescaler */
    base->CR &= ~DIGTMP_CR_DEN_MASK;
}

/*!
 * brief Gets default values for the TDET Control Register.
 *
 * This function fills the given structure with default values for the TDET Control Register.
 * The default values are:
 * code
 *     defaultConfig->innerClockAndPrescalerEnable = true
 *     defaultConfig->tamperForceSystemResetEnable = false
 *     defaultConfig->updateMode = kTDET_StatusLockWithTamper
 *     defaultConfig->clockSourceActiveTamper0 = kTDET_ClockType1Hz
 *     defaultConfig->clockSourceActiveTamper1 = kTDET_ClockType1Hz
 *     defaultConfig->disablePrescalerAfterTamper = false
 *     defaultConfig->prescaler = 0
 * endcode
 * param base TDET peripheral base address
 * param[out] defaultConfig Pointer to structure to be filled with default parameters
 */
void TDET_GetDefaultConfig(DIGTMP_Type *base, tdet_config_t *defaultConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(defaultConfig, 0, sizeof(*defaultConfig));

    struct _tdet_config myDefaultConfig = {
        true,                       /* innerClockAndPrescalerEnable */
        false,                      /* tamperForceSystemResetEnable */
        kTDET_StatusLockWithTamper, /* updateMode */
        kTDET_ClockType1Hz,         /* clockSourceActiveTamper0 */
        kTDET_ClockType1Hz,         /* clockSourceActiveTamper1 */
        false,                      /* disable prescaler on tamper event */
        0,                          /* prescaler */
    };

    *defaultConfig = myDefaultConfig;
}

/*!
 * brief Writes to the TDET Control Register.
 *
 * This function writes the given structure to the TDET Control Register.
 * param base TDET peripheral base address
 * param config Pointer to structure with TDET peripheral configuration parameters
 * return kStatus_Fail when writing to TDET Control Register is not allowed
 * return kStatus_Success when operation completes successfully
 */
status_t TDET_SetConfig(DIGTMP_Type *base, const tdet_config_t *config)
{
    uint32_t tmpCR;

    status_t retval = kStatus_Fail;

    /* check if writing to CR is allowed */
    if ((tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_CRL_MASK)) && (config != NULL))
    {
        /* compute CR value */
        tmpCR = 0;
        tmpCR |= DIGTMP_CR_TFSR(config->tamperForceSystemResetEnable);
        tmpCR |= DIGTMP_CR_UM(config->updateMode);
        tmpCR |= DIGTMP_CR_ATCS0(config->clockSourceActiveTamper0);
        tmpCR |= DIGTMP_CR_ATCS1(config->clockSourceActiveTamper1);
        tmpCR |= DIGTMP_CR_DISTAM(config->disablePrescalerAfterTamper);
        tmpCR |= DIGTMP_CR_DPR(config->prescaler);
        /* write the computed value to the CR register */
        base->CR = tmpCR;
        /* after the prescaler is written to CR register, enable the inner TDET clock and prescaler */
        if (config->innerClockAndPrescalerEnable)
        {
            base->CR = tmpCR | DIGTMP_CR_DEN_MASK;
        }
        retval = kStatus_Success;
    }
    else
    {
        retval = kStatus_Fail;
    }

    return retval;
}

/*!
 * brief Software reset.
 *
 * This function resets all TDET registers. The CR[SWR] itself is not affected;
 * it is reset by VBAT POR only.
 *
 * param base TDET peripheral base address
 * return kStatus_Fail when writing to TDET Control Register is not allowed
 * return kStatus_Success when operation completes successfully
 */
status_t TDET_SoftwareReset(DIGTMP_Type *base)
{
    status_t retval = kStatus_Fail;

    /* check if writing to CR is allowed */
    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_CRL_MASK))
    {
        /* set the CR[SWR] */
        base->CR = DIGTMP_CR_SWR_MASK;
        retval   = kStatus_Success;
    }
    else
    {
        retval = kStatus_Fail;
    }

    return retval;
}

/*!
 * brief Writes to the active tamper register(s).
 *
 * This function writes per active tamper register parameters to active tamper register(s).
 *
 * param base TDET peripheral base address
 * param activeTamperConfig Pointer to structure with active tamper register parameters
 * param activeTamperRegisterSelect Bit mask for active tamper registers to be configured. The passed value is
 *                                   combination of tdet_active_tamper_register_t values (OR'ed).
 * return kStatus_Fail when writing to TDET Active Tamper Register(s) is not allowed
 * return kStatus_Success when operation completes successfully
 */
status_t TDET_ActiveTamperSetConfig(DIGTMP_Type *base,
                                    const tdet_active_tamper_config_t *activeTamperConfig,
                                    uint32_t activeTamperRegisterSelect)
{
    uint32_t mask;
    status_t status;
    uint32_t i, j;

    mask   = 1u;
    status = kStatus_Success;
    j      = ARRAY_SIZE(base->ATR);
    /* configure active tamper register by active tamper register, by moving through all active tamper registers */
    for (i = 0; i < j; i++)
    {
        if ((activeTamperRegisterSelect & mask) != 0U)
        {
            /* configure this active tamper register */
            status = tdet_ActiveTamperConfigure(base, activeTamperConfig, i);
            if (status != kStatus_Success)
            {
                break;
            }
        }
        mask = mask << 1u;
    }

    return status;
}

/*!
 * brief Gets default values for tamper pin configuration.
 *
 * This function fills the give structure with default values for the tamper pin and glitch filter configuration.
 * The default values are:
 * code
 *     pinConfig->pinPolarity = kTDET_TamperPinPolarityExpectNormal;
 *     pinConfig->pinDirection = kTDET_TamperPinDirectionIn;
 *     pinConfig->tamperPullEnable = false;
 *     pinConfig->tamperPinSampleFrequency = kTDET_GlitchFilterSamplingEveryCycle8;
 *     pinConfig->tamperPinSampleWidth = kTDET_GlitchFilterSampleDisable;
 *     pinConfig->glitchFilterEnable = false;
 *     pinConfig->glitchFilterPrescaler = kTDET_GlitchFilterClock512Hz;
 *     pinConfig->glitchFilterWidth = 0;
 *     pinConfig->tamperPinExpected = kTDET_GlitchFilterExpectedLogicZero;
 *     pinConfig->tamperPullSelect = kTDET_GlitchFilterPullTypeAssert;
 * endcode
 *
 * param base TDET peripheral base address
 * param[out] pinConfig Pointer to structure to be filled with tamper pins default parameters
 */
void TDET_PinGetDefaultConfig(DIGTMP_Type *base, tdet_pin_config_t *pinConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(pinConfig, 0, sizeof(*pinConfig));

    struct _tdet_pin_config myPinDefaultConfig = {
        kTDET_TamperPinPolarityExpectNormal,   /* pinPolarity */
        kTDET_TamperPinDirectionIn,            /* pinDirection */
        false,                                 /* tamperPullEnable */
        kTDET_GlitchFilterSamplingEveryCycle8, /* tamperPinSampleFrequency */
        kTDET_GlitchFilterSampleDisable,       /* tamperPinSampleWidth */
        false,                                 /* glitchFilterEnable */
        kTDET_GlitchFilterClock512Hz,          /* glitchFilterPrescaler */
        0,                                     /* glitchFilterWidth */
        kTDET_GlitchFilterExpectedLogicZero,   /* tamperPinExpected */
        kTDET_GlitchFilterPullTypeAssert,      /* tamperPullSelect */
    };

    *pinConfig = myPinDefaultConfig;
}

/*!
 * brief Writes the tamper pin configuration.
 *
 * This function writes per pin parameters to tamper pin and glitch filter configuration registers.
 *
 * param base TDET peripheral base address
 * param pinConfig Pointer to structure with tamper pin and glitch filter configuration parameters
 * param pinSelect Bit mask for tamper pins to be configured. The passed value is combination of
 *                  enum _tdet_external_tamper_pin (tdet_external_tamper_pin_t) values (OR'ed).
 * return kStatus_Fail when writing to TDET Pin Direction, Pin Polarity or Glitch Filter Register(s) is not allowed
 * return kStatus_Success when operation completes successfully
 */
status_t TDET_PinSetConfig(DIGTMP_Type *base, const tdet_pin_config_t *pinConfig, uint32_t pinSelect)
{
    uint32_t mask;
    status_t status;
    uint32_t i, j;

    mask   = 1u;
    status = kStatus_Success;
    j      = ARRAY_SIZE(base->PGFR);
    /* configure pin by pin, by moving through all selected pins */
    for (i = 0; i < j; i++)
    {
        if ((pinSelect & mask) != 0U)
        {
            /* clear this pin from pinSelect */
            pinSelect &= ~mask;

            /* configure this pin */
            status = tdet_PinConfigure(base, pinConfig, i);

            /* if pinSelect is zero, we have configured all pins selected by pinSelect, so skip */
            if ((status != kStatus_Success) || (0U == pinSelect))
            {
                break;
            }
        }
        mask = mask << 1u;
    }

    return status;
}

/*!
 * brief Reads the Status Register.
 *
 * This function reads flag bits from TDET Status Register.
 *
 * param base TDET peripheral base address
 * param[out] result Pointer to uint32_t where to write Status Register read value. Use tdet_status_flag_t to decode
 *                    individual flags.
 * return kStatus_Fail when Status Register reading is not allowed
 * return kStatus_Success when result is written with the Status Register read value
 */
status_t TDET_GetStatusFlags(DIGTMP_Type *base, uint32_t *result)
{
    status_t status;

    if (result != NULL)
    {
        *result = base->SR;
        status  = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the Status Register.
 *
 * This function clears specified flag bits in TDET Status Register.
 *
 * param base TDET peripheral base address
 * param mask Bit mask for the flag bits to be cleared. Use tdet_status_flag_t to encode flags.
 * return kStatus_Fail when Status Register writing is not allowed
 * return kStatus_Success when mask is written to the Status Register
 */
status_t TDET_ClearStatusFlags(DIGTMP_Type *base, uint32_t mask)
{
    status_t status;

    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_SRL_MASK))
    {
        base->SR = mask;
        status   = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the Interrupt Enable Register.
 *
 * This function sets specified interrupt enable bits in TDET Interrupt Enable Register.
 *
 * param base TDET peripheral base address
 * param mask Bit mask for the interrupt enable bits to be set.
 * return kStatus_Fail when Interrupt Enable Register writing is not allowed
 * return kStatus_Success when mask is written to the Interrupt Enable Register
 */
status_t TDET_EnableInterrupts(DIGTMP_Type *base, uint32_t mask)
{
    status_t status;

    mask = mask & TDET_ALL_IER_MASK; /* only set the bits documented in Reference Manual. */
    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_IEL_MASK))
    {
        base->IER |= mask;
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the Interrupt Enable Register.
 *
 * This function clears specified interrupt enable bits in TDET Interrupt Enable Register.
 *
 * param base TDET peripheral base address
 * param mask Bit mask for the interrupt enable bits to be cleared.
 * return kStatus_Fail when Interrupt Enable Register writing is not allowed
 * return kStatus_Success when specified bits are cleared in the Interrupt Enable Register
 */
status_t TDET_DisableInterrupts(DIGTMP_Type *base, uint32_t mask)
{
    status_t status;

    mask = mask & TDET_ALL_IER_MASK; /* only clear the bits documented in Reference Manual.  */
    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_IEL_MASK))
    {
        base->IER &= ~mask;
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the Tamper Enable Register.
 *
 * This function sets specified tamper enable bits in TDET Tamper Enable Register.
 *
 * param base TDET peripheral base address
 * param mask Bit mask for the tamper enable bits to be set.
 * return kStatus_Fail when Tamper Enable Register writing is not allowed
 * return kStatus_Success when mask is written to the Tamper Enable Register
 */
status_t TDET_EnableTampers(DIGTMP_Type *base, uint32_t mask)
{
    status_t status;

    mask = mask & TDET_ALL_TER_MASK; /* only set the bits documented in Reference Manual */
    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_TEL_MASK))
    {
        base->TER |= mask;
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the Tamper Enable Register.
 *
 * This function clears specified tamper enable bits in TDET Tamper Enable Register.
 *
 * param base TDET peripheral base address
 * param mask Bit mask for the tamper enable bits to be cleared.
 * return kStatus_Fail when Tamper Enable Register writing is not allowed
 * return kStatus_Success when specified bits are cleared in the Tamper Enable Register
 */
status_t TDET_DisableTampers(DIGTMP_Type *base, uint32_t mask)
{
    status_t status;

    mask = mask & TDET_ALL_TER_MASK; /* only clear the bits documented in Reference Manual */
    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_TEL_MASK))
    {
        base->TER &= ~mask;
        status = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the Tamper Seconds Register.
 *
 * This function writes to TDET Tamper Seconds Register. This causes Status Register DTF flag to be set (TDET
 * tampering detected).
 *
 * param base TDET peripheral base address
 * return kStatus_Fail when Tamper Seconds Register writing is not allowed
 * return kStatus_Success when Tamper Seconds Register is written
 */
status_t TDET_ForceTamper(DIGTMP_Type *base)
{
    status_t status;

    if (tdet_IsRegisterWriteAllowed(base, DIGTMP_LR_TSL_MASK))
    {
        base->TSR = 0;
        status    = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Reads the Tamper Seconds Register.
 *
 * This function reads TDET Tamper Seconds Register. The read value returns the time in seconds at which the Status
 * Register DTF flag was set.
 *
 * param base TDET peripheral base address
 * param tamperTimeSeconds Time in seconds at which the tamper detection SR[DTF] flag was set.
 * return kStatus_Fail when Tamper Seconds Register reading is not allowed
 * return kStatus_Success when Tamper Seconds Register is read
 */
status_t TDET_GetTamperTimeSeconds(DIGTMP_Type *base, uint32_t *tamperTimeSeconds)
{
    status_t status;

    if (tamperTimeSeconds != NULL)
    {
        *tamperTimeSeconds = base->TSR;
        status             = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Writes to the TDET Lock Register.
 *
 * This function clears specified lock bits in the TDET Lock Register.
 * When a lock bit is clear, a write to corresponding TDET Register is ignored.
 * Once cleared, these bits can only be set by VBAT POR or software reset.
 *
 * param base TDET peripheral base address
 * param mask Bit mask for the lock bits to be cleared. Use tdet_register_t values to encode (OR'ed) which TDET
 * Registers shall be locked.
 */
void TDET_LockRegisters(DIGTMP_Type *base, uint32_t mask)
{
    mask &= (uint32_t)kTDET_AllRegisters; /* make sure only documented registers are selected by the mask */
    base->LR &= ~mask;                    /* clear the selected bits */
}
