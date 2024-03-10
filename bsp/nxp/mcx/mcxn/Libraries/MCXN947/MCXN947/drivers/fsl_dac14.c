/*!
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dac14.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dac14"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for DAC14 module.
 *
 * @param base DAC14 peripheral base address
 */
static uint32_t DAC14_GetInstance(HPDAC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to DAC14 bases for each instance. */
static HPDAC_Type *const s_dac14Bases[] = HPDAC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to DAC14 clocks for each instance. */
static const clock_ip_name_t s_dac14Clocks[] = HPDAC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t DAC14_GetInstance(HPDAC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dac14Bases); instance++)
    {
        if (s_dac14Bases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dac14Bases));

    return instance;
}

/*!
 * brief Initialize the DAC14 module with common configuartion.
 *
 * The clock will be enabled in this function.
 *
 * param base DAC14 peripheral base address.
 * param config Pointer to configuration structure.
 */
void DAC14_Init(HPDAC_Type *base, const dac14_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32 = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_dac14Clocks[DAC14_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Software reset and FIFO reset. */
    DAC14_DoSoftwareReset(base);
    DAC14_DoFIFOReset(base);

    /* Opamp is used as buffer. */
    if (config->enableOpampBuffer)
    {
        tmp32 |= HPDAC_GCR_BUF_EN_MASK;
    }
    /*Enable the DAC system.*/
    if (config->enableDAC)
    {
        tmp32 |= HPDAC_GCR_DACEN_MASK;
    }

    if (config->WorkMode != kDAC14_BufferWorkMode)
    {
        /*Use software trigger source.*/
        if (kDAC14_SoftwareTriggerSource == config->TriggerSource)
        {
            tmp32 |= HPDAC_GCR_TRGSEL_MASK;
        }

        if (config->WorkMode != kDAC14_SwingBackWorkMode)
        {
            if (config->WorkMode != kDAC14_PeriodTriggerAndSwingBackWorkMode)
            {
                /*Configurtion FIFO watermarklevel.*/
                base->FCR = HPDAC_FCR_WML(config->fifoWatermarkLevel);

                if (config->WorkMode == kDAC14_PeriodTriggerWorkMode)
                {
                    tmp32 |= HPDAC_GCR_FIFOEN_MASK | HPDAC_GCR_PTGEN_MASK; /* Enable period trigger mode. */
                    /* Set trigger number and width. */
                    base->PCR = HPDAC_PCR_PTG_NUM(config->periodicTriggerNumber) |
                                HPDAC_PCR_PTG_PERIOD(config->periodicTriggerWidth);
                }
                else
                {
                    tmp32 |= HPDAC_GCR_FIFOEN_MASK; /* Enable FIFO mode.*/
                }
            }
            else
            {
                /* Enable period trigger mode and swing back mode. */
                tmp32 |= HPDAC_GCR_FIFOEN_MASK | HPDAC_GCR_PTGEN_MASK | HPDAC_GCR_SWMD_MASK;
                /* Set trigger number and width. */
                base->PCR = HPDAC_PCR_PTG_NUM(config->periodicTriggerNumber) |
                            HPDAC_PCR_PTG_PERIOD(config->periodicTriggerWidth);
            }
        }
        else
        {
            tmp32 |= HPDAC_GCR_FIFOEN_MASK | HPDAC_GCR_SWMD_MASK; /* Enable swing mode. */
        }
    }
    base->GCR = tmp32;
}

/*!
 * brief Get the default settings for initialization's configuration.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * code
    config->fifoWatermarkLevel = 0U;
    config->TriggerSource    = kDAC14_HardwareTriggerSource;
    config->WorkMode       = kDAC14_BufferWorkMode;
    config->enableOpampBuffer  = false;
    config->enableADC  = false;
    config->periodicTriggerNumber = 0U;
    config->periodicTriggerWidth  = 0U;
 * endcode
 *
 * param config Pointer to configuration structure.
 */
void DAC14_GetDefaultConfig(dac14_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->fifoWatermarkLevel    = 0U;
    config->TriggerSource         = kDAC14_HardwareTriggerSource;
    config->WorkMode              = kDAC14_BufferWorkMode;
    config->enableOpampBuffer     = false;
    config->enableDAC             = false;
    config->periodicTriggerNumber = 0U;
    config->periodicTriggerWidth  = 0U;
}
/*!
 * brief De-initialize the DAC14 module.
 *
 * The clock will be disabled in this function.
 *
 * param base DAC14 peripheral base address.
 */
void DAC14_Deinit(HPDAC_Type *base)
{
    /* Disable the module. */
    DAC14_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_dac14Clocks[DAC14_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
