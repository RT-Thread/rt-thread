/*
 * Copyright 2019-2024 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wuu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.wuu"
#endif

#define WUU_PE_REG_BIT_FIELD_MASK  0x03UL
#define WUU_PDC_REG_BIT_FIELD_MASK 0x03UL
#define WUU_PMC_REG_BIT_FIELD_MASK 0x01UL

#define WUU_ME_REG_WUME_FIELD_MASK 0x01UL
#define WUU_DE_REG_WUME_FIELD_MASK 0x01UL

#define WUU_FILT_REG_FILTE_FIELD_MASK   0x60U
#define WUU_FILT_REG_FILTSET_FIELD_MASK 0x1FU
#define WUU_FDC_REG_FILTC_FIELD_MASK    0x3U
#define WUU_FMC_REG_FILTM_FIELD_MASK    0x1U

#define WUU_FILT_REG_FILTSET_FIELD(x)            (((uint32_t)(x) << 5UL) & WUU_FILT_REG_FILTE_FIELD_MASK)
#define WUU_CLEAR_BIT_FIELD_IN_REG(mask, offset) (~((uint32_t)(mask) << (offset)))
#define WUU_SET_BIT_FIELD_IN_REG(val, offset)    ((uint32_t)(val) << (offset))
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
 * brief Enables and Configs External WakeUp Pins.
 *
 * This function enables/disables the external pin as wakeup input. What's more this
 * function configs pins options, including edge detection wakeup event and operate mode.
 *
 * param base     MUU peripheral base address.
 * param pinIndex The index of the external input pin. See Reference Manual for the details.
 * param config   Pointer to wuu_external_wakeup_pin_config_t structure.
 */
void WUU_SetExternalWakeUpPinsConfig(WUU_Type *base, uint8_t pinIndex, const wuu_external_wakeup_pin_config_t *config)
{
    assert(config != NULL);

    volatile uint32_t *edgeRegBase  = NULL;
    volatile uint32_t *eventRegBase = NULL;
    uint32_t edgeReg;
    uint32_t eventReg;
    uint32_t modeReg;
    uint8_t offset;

    /* Calculate offset. */
    offset = 2U * (pinIndex & 0xFU);

    if (config->edge != kWUU_ExternalPinDisable)
    {
        /* Based on pin index, get register base address. */
        if ((pinIndex >> 4U) != 0U)
        {
            edgeRegBase  = &base->PE2;
            eventRegBase = &base->PDC2;
        }
        else
        {
            edgeRegBase  = &base->PE1;
            eventRegBase = &base->PDC1;
        }

        /* Enable and config the edge detection. */
        edgeReg = *edgeRegBase;
        edgeReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_PE_REG_BIT_FIELD_MASK, offset);
        edgeReg |= WUU_SET_BIT_FIELD_IN_REG(config->edge, offset);
        *edgeRegBase = edgeReg;

        /* Config the wakeup event. */
        eventReg = *eventRegBase;
        eventReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_PDC_REG_BIT_FIELD_MASK, offset);
        eventReg |= WUU_SET_BIT_FIELD_IN_REG(config->event, offset);
        *eventRegBase = eventReg;

        /* Config operate mode. */
        modeReg = base->PMC;
        modeReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_PMC_REG_BIT_FIELD_MASK, pinIndex);
        modeReg |= WUU_SET_BIT_FIELD_IN_REG(config->mode, pinIndex);

        base->PMC = modeReg;
    }
    else
    {
        /* Based on pin index, get register base address. */
        if ((pinIndex >> 4U) != 0U)
        {
            edgeRegBase = &base->PE2;
        }
        else
        {
            edgeRegBase = &base->PE1;
        }

        edgeReg = *edgeRegBase;
        edgeReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_PE_REG_BIT_FIELD_MASK, offset);
        *edgeRegBase = edgeReg;
    }
}

/*!
 * brief Disable and clear external wakeup pin settings.
 * 
 * param base MUU peripheral base address.
 * param pinIndex The index of the external input pin.
 */
void WUU_ClearExternalWakeupPinsConfig(WUU_Type *base, uint8_t pinIndex)
{
    if (pinIndex <= 15U)
    {
        base->PE1 &= ~(WUU_PE_REG_BIT_FIELD_MASK << (2UL * (uint32_t)pinIndex));
        base->PDC1 &= ~(WUU_PDC_REG_BIT_FIELD_MASK << (2UL * (uint32_t)pinIndex));
    }
    else
    {
        base->PE1 &= ~(WUU_PE_REG_BIT_FIELD_MASK << (2UL * (uint32_t)((uint32_t)pinIndex % 16UL)));
        base->PDC1 &= ~(WUU_PDC_REG_BIT_FIELD_MASK << (2UL * (uint32_t)((uint32_t)pinIndex % 16UL)));
    }
}

/*!
 * brief Config Internal modules' event as the wake up soures.
 *
 * This function configs the internal modules event as the wake up sources.
 *
 * param base WUU peripheral base address.
 * param moduleIndex The selected internal module. See the Reference Manual for the details.
 * param event Select interrupt or DMA/Trigger of the internal module as the wake up source.
 */
void WUU_SetInternalWakeUpModulesConfig(WUU_Type *base, uint8_t moduleIndex, wuu_internal_wakeup_module_event_t event)
{
    switch (event)
    {
        case kWUU_InternalModuleInterrupt:
            base->ME |= WUU_SET_BIT_FIELD_IN_REG(WUU_ME_REG_WUME_FIELD_MASK, moduleIndex);
            break;
        case kWUU_InternalModuleDMATrigger:
            base->DE |= WUU_SET_BIT_FIELD_IN_REG(WUU_DE_REG_WUME_FIELD_MASK, moduleIndex);
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Disable an on-chip internal modules' event as the wakeup sources.
 * 
 * param base WUU peripheral base address.
 * param moduleIndex The selected internal module. See the Reference Manual for the details.
 * param event The event(interrupt or DMA/trigger) of the internal module to disable.
 */
void WUU_ClearInternalWakeUpModulesConfig(WUU_Type *base, uint8_t moduleIndex, wuu_internal_wakeup_module_event_t event)
{
    switch(event)
    {
        case kWUU_InternalModuleInterrupt:
            base->ME &= ~WUU_SET_BIT_FIELD_IN_REG(WUU_ME_REG_WUME_FIELD_MASK, moduleIndex);
            break;
        case kWUU_InternalModuleDMATrigger:
            base->DE &= ~WUU_SET_BIT_FIELD_IN_REG(WUU_DE_REG_WUME_FIELD_MASK, moduleIndex);
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Configs and Enables Pin filters.
 *
 * This function configs Pin filter, including pin select, filer operate mode
 * filer wakeup event and filter edge detection.
 *
 * param base WUU peripheral base address.
 * param filterIndex The index of the pin filer.
 * param config Pointer to wuu_pin_filter_config_t structure.
 */
void WUU_SetPinFilterConfig(WUU_Type *base, uint8_t filterIndex, const wuu_pin_filter_config_t *config)
{
    assert(config != NULL);

    uint8_t shift;
    uint32_t filterReg;
    uint32_t eventReg;
    uint32_t modeReg;

    shift     = (filterIndex - 1U) * 8U;
    filterReg = base->FILT;
    filterReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_FILT_REG_FILTE_FIELD_MASK, shift);
    filterReg |= WUU_SET_BIT_FIELD_IN_REG(WUU_FILT_REG_FILTSET_FIELD(config->edge), shift);

    if (config->edge != kWUU_FilterDisabled)
    {
        filterReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_FILT_REG_FILTSET_FIELD_MASK, shift);
        filterReg |= WUU_SET_BIT_FIELD_IN_REG(config->pinIndex, shift);

        /* Config wake up event. */
        shift    = (filterIndex - 1U) * 2U;
        eventReg = base->FDC;
        eventReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_FDC_REG_FILTC_FIELD_MASK, shift);
        eventReg |= WUU_SET_BIT_FIELD_IN_REG(config->event, shift);
        base->FDC = eventReg;

        /* Config operate mode. */
        shift   = (filterIndex - 1U) * 1U;
        modeReg = base->FMC;
        modeReg &= WUU_CLEAR_BIT_FIELD_IN_REG(WUU_FMC_REG_FILTM_FIELD_MASK, shift);
        modeReg |= WUU_SET_BIT_FIELD_IN_REG(config->mode, shift);
        base->FMC = modeReg;
    }

    base->FILT = filterReg;
}

/*!
 * brief Gets the pin filter configuration.
 *
 * This function gets the pin filter flag.
 *
 * param base WUU peripheral base address.
 * param filterIndex A pin filter index, which starts from 1.
 * return True if the flag is a source of the existing low-leakage power mode.
 */
bool WUU_GetPinFilterFlag(WUU_Type *base, uint8_t filterIndex)
{
    bool ret = false;

    switch (filterIndex)
    {
        case 1:
            ret = ((base->FILT & WUU_FILT_FILTF1_MASK) != 0U);
            break;
        case 2:
            ret = ((base->FILT & WUU_FILT_FILTF2_MASK) != 0U);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

/*!
 * brief Clears the pin filter configuration.
 *
 * This function clears the pin filter flag.
 *
 * param base WUU peripheral base address.
 * param filterIndex A pin filter index to clear the flag, starting from 1.
 */
void WUU_ClearPinFilterFlag(WUU_Type *base, uint8_t filterIndex)
{
    uint32_t reg;

    reg = base->FILT;
    /* Clean the W1C bits, in case the flags are cleared by mistake. */
    reg &= ~(WUU_FILT_FILTF1_MASK | WUU_FILT_FILTF2_MASK);

    reg |= WUU_SET_BIT_FIELD_IN_REG(WUU_FILT_FILTF1_MASK, ((filterIndex - 1U) * 8U));

    base->FILT = reg;
}

/*!
 * brief Gets the external wakeup source flag.
 *
 * This function checks the external pin flag to detect whether the MCU is
 * woken up by the specific pin.
 *
 * param base WUU peripheral base address.
 * param pinIndex     A pin index, which starts from 0.
 * return True if the specific pin is a wakeup source.
 */
bool WUU_GetExternalWakeupPinFlag(WUU_Type *base, uint32_t pinIndex)
{
    return (0U != (base->PF & (1UL << pinIndex)));
}

/*!
 * brief Clears the external wakeup source flag.
 *
 * This function clears the external wakeup source flag for a specific pin.
 *
 * param base WUU peripheral base address.
 * param pinIndex A pin index, which starts from 0.
 */
void WUU_ClearExternalWakeupPinFlag(WUU_Type *base, uint32_t pinIndex)
{
    base->PF = (1UL << pinIndex);
}
