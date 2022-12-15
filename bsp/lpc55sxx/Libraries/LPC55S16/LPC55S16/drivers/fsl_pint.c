/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pint.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pint"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
/*! @brief Irq number array */
static const IRQn_Type s_pintIRQ[FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS +
                                 FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS] = PINT_IRQS;

/*! @brief Callback function array for SECPINT(s). */
static pint_cb_t s_secpintCallback[FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS];
#else
/*! @brief Irq number array */
static const IRQn_Type s_pintIRQ[FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS] = PINT_IRQS;
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */

/*! @brief Callback function array for PINT(s). */
static pint_cb_t s_pintCallback[FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief    Initialize PINT peripheral.

 * This function initializes the PINT peripheral and enables the clock.
 *
 * param base Base address of the PINT peripheral.
 *
 * retval None.
 */
void PINT_Init(PINT_Type *base)
{
    uint32_t i;
    uint32_t pmcfg    = 0;
    uint8_t pintcount = 0;
    assert(base != NULL);

    if (base == PINT)
    {
        pintcount = FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS;
        /* clear PINT callback array*/
        for (i = 0; i < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            s_pintCallback[i] = NULL;
        }
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        pintcount = FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS;
        /* clear SECPINT callback array*/
        for (i = 0; i < (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            s_secpintCallback[i] = NULL;
        }
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }

    /* Disable all bit slices for pint*/
    for (i = 0; i < pintcount; i++)
    {
        pmcfg = pmcfg | ((uint32_t)kPINT_PatternMatchNever << (PININT_BITSLICE_CFG_START + (i * 3U)));
    }

#if defined(FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE) && (FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE == 1)

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(kCLOCK_GpioInt);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(kGPIOINT_RST_N_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

#elif defined(FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE) && (FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE == 0)

    if (base == PINT)
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_EnableClock(kCLOCK_Gpio0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kGPIO0_RST_N_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_EnableClock(kCLOCK_Gpio_Sec);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kGPIOSEC_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }

#else

    if (base == PINT)
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_EnableClock(kCLOCK_Pint);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kPINT_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
    }
    else
    {
        /* if need config SECURE PINT device,then enable secure pint interrupt clock */
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_EnableClock(kCLOCK_Gpio_Sec_Int);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kGPIOSECINT_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }
#endif /* FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE */

    /* Disable all pattern match bit slices */
    base->PMCFG = pmcfg;
}

/*!
 * brief    Configure PINT peripheral pin interrupt.

 * This function configures a given pin interrupt.
 *
 * param base Base address of the PINT peripheral.
 * param intr Pin interrupt.
 * param enable Selects detection logic.
 * param callback Callback.
 *
 * retval None.
 */
void PINT_PinInterruptConfig(PINT_Type *base, pint_pin_int_t intr, pint_pin_enable_t enable, pint_cb_t callback)
{
    assert(base != NULL);

    /* Clear Rise and Fall flags first */
    PINT_PinInterruptClrRiseFlag(base, intr);
    PINT_PinInterruptClrFallFlag(base, intr);

    /* Security PINT uses additional callback array */
    if (base == PINT)
    {
        s_pintCallback[intr] = callback;
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        s_secpintCallback[intr] = callback;
#endif
    }

    /* select level or edge sensitive */
    base->ISEL = (base->ISEL & ~(1UL << (uint32_t)intr)) |
                 ((((uint32_t)enable & PINT_PIN_INT_LEVEL) != 0U) ? (1UL << (uint32_t)intr) : 0U);

    /* enable rising or level interrupt */
    if (((unsigned)enable & (PINT_PIN_INT_LEVEL | PINT_PIN_INT_RISE)) != 0U)
    {
        base->SIENR = 1UL << (uint32_t)intr;
    }
    else
    {
        base->CIENR = 1UL << (uint32_t)intr;
    }

    /* Enable falling or select high level */
    if (((unsigned)enable & PINT_PIN_INT_FALL_OR_HIGH_LEVEL) != 0U)
    {
        base->SIENF = 1UL << (uint32_t)intr;
    }
    else
    {
        base->CIENF = 1UL << (uint32_t)intr;
    }
}

/*!
 * brief    Get PINT peripheral pin interrupt configuration.

 * This function returns the configuration of a given pin interrupt.
 *
 * param base Base address of the PINT peripheral.
 * param pintr Pin interrupt.
 * param enable Pointer to store the detection logic.
 * param callback Callback.
 *
 * retval None.
 */
void PINT_PinInterruptGetConfig(PINT_Type *base, pint_pin_int_t pintr, pint_pin_enable_t *enable, pint_cb_t *callback)
{
    uint32_t mask;
    bool level;

    assert(base != NULL);

    *enable = kPINT_PinIntEnableNone;
    level   = false;

    mask = 1UL << (uint32_t)pintr;
    if ((base->ISEL & mask) != 0U)
    {
        /* Pin interrupt is level sensitive */
        level = true;
    }

    if ((base->IENR & mask) != 0U)
    {
        if (level)
        {
            /* Level interrupt is enabled */
            *enable = kPINT_PinIntEnableLowLevel;
        }
        else
        {
            /* Rising edge interrupt */
            *enable = kPINT_PinIntEnableRiseEdge;
        }
    }

    if ((base->IENF & mask) != 0U)
    {
        if (level)
        {
            /* Level interrupt is active high */
            *enable = kPINT_PinIntEnableHighLevel;
        }
        else
        {
            /* Either falling or both edge */
            if (*enable == kPINT_PinIntEnableRiseEdge)
            {
                /* Rising and faling edge */
                *enable = kPINT_PinIntEnableBothEdges;
            }
            else
            {
                /* Falling edge */
                *enable = kPINT_PinIntEnableFallEdge;
            }
        }
    }

    /* Security PINT uses additional callback array */
    if (base == PINT)
    {
        *callback = s_pintCallback[pintr];
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        *callback = s_secpintCallback[pintr];
#endif
    }
}

/*!
 * brief    Configure PINT pattern match.

 * This function configures a given pattern match bit slice.
 *
 * param base Base address of the PINT peripheral.
 * param bslice Pattern match bit slice number.
 * param cfg Pointer to bit slice configuration.
 *
 * retval None.
 */
void PINT_PatternMatchConfig(PINT_Type *base, pint_pmatch_bslice_t bslice, pint_pmatch_cfg_t *cfg)
{
    uint32_t src_shift;
    uint32_t cfg_shift;
    uint32_t pmcfg;
    uint32_t tmp_src_shift = PININT_BITSLICE_SRC_MASK;
    uint32_t tmp_cfg_shift = PININT_BITSLICE_CFG_MASK;

    assert(base != NULL);

    src_shift = PININT_BITSLICE_SRC_START + ((uint32_t)bslice * 3UL);
    cfg_shift = PININT_BITSLICE_CFG_START + ((uint32_t)bslice * 3UL);

    /* Input source selection for selected bit slice */
    base->PMSRC = (base->PMSRC & ~(tmp_src_shift << src_shift)) | ((uint32_t)(cfg->bs_src) << src_shift);

    /* Bit slice configuration */
    pmcfg = base->PMCFG;
    pmcfg = (pmcfg & ~(tmp_cfg_shift << cfg_shift)) | ((uint32_t)(cfg->bs_cfg) << cfg_shift);

    /* If end point is true, enable the bits */
    if ((uint32_t)bslice != 7UL)
    {
        if (cfg->end_point)
        {
            pmcfg |= (1UL << (uint32_t)bslice);
        }
        else
        {
            pmcfg &= ~(1UL << (uint32_t)bslice);
        }
    }

    base->PMCFG = pmcfg;

    /* Save callback pointer */
    if (base == PINT)
    {
        if ((uint32_t)bslice < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS)
        {
            s_pintCallback[bslice] = cfg->callback;
        }
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        if ((uint32_t)bslice < (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        {
            s_secpintCallback[bslice] = cfg->callback;
        }
#endif
    }
}

/*!
 * brief    Get PINT pattern match configuration.

 * This function returns the configuration of a given pattern match bit slice.
 *
 * param base Base address of the PINT peripheral.
 * param bslice Pattern match bit slice number.
 * param cfg Pointer to bit slice configuration.
 *
 * retval None.
 */
void PINT_PatternMatchGetConfig(PINT_Type *base, pint_pmatch_bslice_t bslice, pint_pmatch_cfg_t *cfg)
{
    uint32_t src_shift;
    uint32_t cfg_shift;
    uint32_t tmp_src_shift = PININT_BITSLICE_SRC_MASK;
    uint32_t tmp_cfg_shift = PININT_BITSLICE_CFG_MASK;

    assert(base != NULL);

    src_shift = PININT_BITSLICE_SRC_START + ((uint32_t)bslice * 3UL);
    cfg_shift = PININT_BITSLICE_CFG_START + ((uint32_t)bslice * 3UL);

    cfg->bs_src = (pint_pmatch_input_src_t)(uint32_t)((base->PMSRC & (tmp_src_shift << src_shift)) >> src_shift);
    cfg->bs_cfg = (pint_pmatch_bslice_cfg_t)(uint32_t)((base->PMCFG & (tmp_cfg_shift << cfg_shift)) >> cfg_shift);

    if ((uint32_t)bslice == 7U)
    {
        cfg->end_point = true;
    }
    else
    {
        cfg->end_point = (((base->PMCFG & (1UL << (uint32_t)bslice)) >> (uint32_t)bslice) != 0U) ? true : false;
    }

    if (base == PINT)
    {
        if ((uint32_t)bslice < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS)
        {
            cfg->callback = s_pintCallback[bslice];
        }
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        if ((uint32_t)bslice < (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        {
            cfg->callback = s_secpintCallback[bslice];
        }
#endif
    }
}

/*!
 * brief    Reset pattern match detection logic.

 * This function resets the pattern match detection logic if any of the product term is matching.
 *
 * param base Base address of the PINT peripheral.
 *
 * retval pmstatus Each bit position indicates the match status of corresponding bit slice.
 * = 0 Match was detected.  = 1 Match was not detected.
 */
uint32_t PINT_PatternMatchResetDetectLogic(PINT_Type *base)
{
    uint32_t pmctrl;
    uint32_t pmstatus;
    uint32_t pmsrc;

    pmctrl   = base->PMCTRL;
    pmstatus = pmctrl >> PINT_PMCTRL_PMAT_SHIFT;
    if (pmstatus != 0UL)
    {
        /* Reset Pattern match engine detection logic */
        pmsrc       = base->PMSRC;
        base->PMSRC = pmsrc;
    }
    return (pmstatus);
}

/*!
 * @brief   Clear Selected pin interrupt status only when the pin was triggered by edge-sensitive.

 * This function clears the selected pin interrupt status.
 *
 * @param base Base address of the PINT peripheral.
 * @param pintr Pin interrupt.
 *
 * @retval None.
 */
void PINT_PinInterruptClrStatus(PINT_Type *base, pint_pin_int_t pintr)
{
    uint32_t pinIntMode   = base->ISEL & (1UL << (uint32_t)pintr);
    uint32_t pinIntStatus = base->IST & (1UL << (uint32_t)pintr);

    /* Edge sensitive and pin interrupt that is currently requesting an interrupt. */
    if ((pinIntMode == 0x0UL) && (pinIntStatus != 0x0UL))
    {
        base->IST = (1UL << (uint32_t)pintr);
    }
}

/*!
 * @brief   Clear all pin interrupts status only when pins were triggered by edge-sensitive.

 * This function clears the status of all pin interrupts.
 *
 * @param base Base address of the PINT peripheral.
 *
 * @retval None.
 */
void PINT_PinInterruptClrStatusAll(PINT_Type *base)
{
    uint32_t pinIntMode   = 0;
    uint32_t pinIntStatus = 0;
    uint32_t pinIntCount  = 0;
    uint32_t mask         = 0;
    uint32_t i;

    if (base == PINT)
    {
        pinIntCount = (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS;
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        pinIntCount = (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS;
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }

    for (i = 0; i < pinIntCount; i++)
    {
        pinIntMode   = base->ISEL & (1UL << i);
        pinIntStatus = base->IST & (1UL << i);

        /* Edge sensitive and pin interrupt that is currently requesting an interrupt. */
        if ((pinIntMode == 0x0UL) && (pinIntStatus != 0x0UL))
        {
            mask |= 1UL << i;
        }
    }

    base->IST = mask;
}

/*!
 * brief    Enable callback.

 * This function enables the interrupt for the selected PINT peripheral. Although the pin(s) are monitored
 * as soon as they are enabled, the callback function is not enabled until this function is called.
 *
 * param base Base address of the PINT peripheral.
 *
 * retval None.
 */
void PINT_EnableCallback(PINT_Type *base)
{
    uint32_t i;

    assert(base != NULL);

    if (base == PINT)
    {
        for (i = 0; i < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            PINT_PinInterruptClrStatus(base, (pint_pin_int_t)i);
            NVIC_ClearPendingIRQ(s_pintIRQ[i]);
            (void)EnableIRQ(s_pintIRQ[i]);
        }
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        for (i = 0; i < (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            PINT_PinInterruptClrStatus(base, (pint_pin_int_t)i);
            NVIC_ClearPendingIRQ(s_pintIRQ[i + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS]);
            (void)EnableIRQ(s_pintIRQ[i + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS]);
        }
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }
}

/*!
 * brief    enable callback by pin index.

 * This function  enables callback by pin index instead of enabling all pins.
 *
 * param base Base address of the peripheral.
 * param pinIdx pin index.
 *
 * retval None.
 */
void PINT_EnableCallbackByIndex(PINT_Type *base, pint_pin_int_t pintIdx)
{
    assert(base != NULL);

    PINT_PinInterruptClrStatus(base, (pint_pin_int_t)pintIdx);

#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
    /* Get the right security pint irq index in array */
    if (base == SECPINT)
    {
        pintIdx =
            (pint_pin_int_t)(uint32_t)((uint32_t)pintIdx + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS);
    }
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */

    NVIC_ClearPendingIRQ(s_pintIRQ[pintIdx]);
    (void)EnableIRQ(s_pintIRQ[pintIdx]);
}

/*!
 * brief    Disable callback.

 * This function disables the interrupt for the selected PINT peripheral. Although the pins are still
 * being monitored but the callback function is not called.
 *
 * param base Base address of the peripheral.
 *
 * retval None.
 */
void PINT_DisableCallback(PINT_Type *base)
{
    uint32_t i;

    assert(base != NULL);

    if (base == PINT)
    {
        for (i = 0; i < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            (void)DisableIRQ(s_pintIRQ[i]);
            PINT_PinInterruptClrStatus(base, (pint_pin_int_t)i);
            NVIC_ClearPendingIRQ(s_pintIRQ[i]);
        }
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        for (i = 0; i < (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            (void)DisableIRQ(s_pintIRQ[i + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS]);
            PINT_PinInterruptClrStatus(base, (pint_pin_int_t)i);
            NVIC_ClearPendingIRQ(s_pintIRQ[i + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS]);
        }
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }
}

/*!
 * brief disable callback by pin index.

 * This function disables callback by pin index instead of disabling all pins.
 *
 * param base Base address of the peripheral.
 * param pinIdx pin index.
 *
 * retval None.
 */
void PINT_DisableCallbackByIndex(PINT_Type *base, pint_pin_int_t pintIdx)
{
    assert(base != NULL);

    if (base == PINT)
    {
        (void)DisableIRQ(s_pintIRQ[pintIdx]);
        PINT_PinInterruptClrStatus(base, (pint_pin_int_t)pintIdx);
        NVIC_ClearPendingIRQ(s_pintIRQ[pintIdx]);
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        (void)DisableIRQ(s_pintIRQ[(uint32_t)pintIdx + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS]);
        PINT_PinInterruptClrStatus(base, (pint_pin_int_t)pintIdx);
        NVIC_ClearPendingIRQ(s_pintIRQ[(uint32_t)pintIdx + (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS]);
#endif
    }
}

/*!
 * brief    Deinitialize PINT peripheral.

 * This function disables the PINT clock.
 *
 * param base Base address of the PINT peripheral.
 *
 * retval None.
 */
void PINT_Deinit(PINT_Type *base)
{
    uint32_t i;

    assert(base != NULL);

    /* Cleanup */
    PINT_DisableCallback(base);
    if (base == PINT)
    {
        /* clear PINT callback array*/
        for (i = 0; i < (uint32_t)FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            s_pintCallback[i] = NULL;
        }
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
        /* clear SECPINT callback array */
        for (i = 0; i < (uint32_t)FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS; i++)
        {
            s_secpintCallback[i] = NULL;
        }
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }

#if defined(FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE) && (FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE == 1)

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_DisableClock(kCLOCK_GpioInt);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(kGPIOINT_RST_N_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

#elif defined(FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE) && (FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE == 0)

    if (base == PINT)
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_DisableClock(kCLOCK_Gpio0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kGPIO0_RST_N_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
    }
    else
    {
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_DisableClock(kCLOCK_Gpio_Sec);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kGPIOSEC_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }

#else

    if (base == PINT)
    {
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_DisableClock(kCLOCK_Pint);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kPINT_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
    }
    else
    {
        /* if need config SECURE PINT device,then enable secure pint interrupt clock */
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
        /* Enable the clock. */
        CLOCK_DisableClock(kCLOCK_Gpio_Sec_Int);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
        /* Reset the module. */
        RESET_PeripheralReset(kGPIOSECINT_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
    }
#endif /* FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE */
}
#if (defined(FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS) && FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS)
/* IRQ handler functions overloading weak symbols in the startup */
void SEC_GPIO_INT0_IRQ0_DriverIRQHandler(void);
void SEC_GPIO_INT0_IRQ0_DriverIRQHandler(void)
{
    uint32_t pmstatus = 0;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(SECPINT);
    /* Call user function */
    if (s_secpintCallback[kPINT_SecPinInt0] != NULL)
    {
        s_secpintCallback[kPINT_SecPinInt0](kPINT_SecPinInt0, pmstatus);
    }
    if ((SECPINT->ISEL & 0x1U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(SECPINT, kPINT_PinInt0);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if (FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS > 1U)
/* IRQ handler functions overloading weak symbols in the startup */
void SEC_GPIO_INT0_IRQ1_DriverIRQHandler(void);
void SEC_GPIO_INT0_IRQ1_DriverIRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(SECPINT);
    /* Call user function */
    if (s_secpintCallback[kPINT_SecPinInt1] != NULL)
    {
        s_secpintCallback[kPINT_SecPinInt1](kPINT_SecPinInt1, pmstatus);
    }
    if ((SECPINT->ISEL & 0x1U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(SECPINT, kPINT_PinInt1);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */
#endif /* FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS */

/* IRQ handler functions overloading weak symbols in the startup */
void PIN_INT0_DriverIRQHandler(void);
void PIN_INT0_DriverIRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt0] != NULL)
    {
        s_pintCallback[kPINT_PinInt0](kPINT_PinInt0, pmstatus);
    }
    if ((PINT->ISEL & 0x1U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt0);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 1U)
void PIN_INT1_DriverIRQHandler(void);
void PIN_INT1_DriverIRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt1] != NULL)
    {
        s_pintCallback[kPINT_PinInt1](kPINT_PinInt1, pmstatus);
    }
    if ((PINT->ISEL & 0x2U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt1);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 2U)
void PIN_INT2_DriverIRQHandler(void);
void PIN_INT2_DriverIRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt2] != NULL)
    {
        s_pintCallback[kPINT_PinInt2](kPINT_PinInt2, pmstatus);
    }
    if ((PINT->ISEL & 0x4U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt2);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 3U)
void PIN_INT3_DriverIRQHandler(void);
void PIN_INT3_DriverIRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt3] != NULL)
    {
        s_pintCallback[kPINT_PinInt3](kPINT_PinInt3, pmstatus);
    }
    if ((PINT->ISEL & 0x8U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt3);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 4U)
void PIN_INT4_DriverIRQHandler(void);
void PIN_INT4_DriverIRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt4] != NULL)
    {
        s_pintCallback[kPINT_PinInt4](kPINT_PinInt4, pmstatus);
    }
    if ((PINT->ISEL & 0x10U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt4);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 5U)
#if defined(FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER) && FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER
void PIN_INT5_DAC1_IRQHandler(void);
void PIN_INT5_DAC1_IRQHandler(void)
#else
void PIN_INT5_DriverIRQHandler(void);
void PIN_INT5_DriverIRQHandler(void)
#endif /* FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER */
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt5] != NULL)
    {
        s_pintCallback[kPINT_PinInt5](kPINT_PinInt5, pmstatus);
    }
    if ((PINT->ISEL & 0x20U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt5);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 6U)
#if defined(FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER) && FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER
void PIN_INT6_USART3_IRQHandler(void);
void PIN_INT6_USART3_IRQHandler(void)
#else
void PIN_INT6_DriverIRQHandler(void);
void PIN_INT6_DriverIRQHandler(void)
#endif /* FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER */
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt6] != NULL)
    {
        s_pintCallback[kPINT_PinInt6](kPINT_PinInt6, pmstatus);
    }
    if ((PINT->ISEL & 0x40U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt6);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if (FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS > 7U)
#if defined(FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER) && FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER
void PIN_INT7_USART4_IRQHandler(void);
void PIN_INT7_USART4_IRQHandler(void)
#else
void PIN_INT7_DriverIRQHandler(void);
void PIN_INT7_DriverIRQHandler(void)
#endif /* FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER */
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);
    /* Call user function */
    if (s_pintCallback[kPINT_PinInt7] != NULL)
    {
        s_pintCallback[kPINT_PinInt7](kPINT_PinInt7, pmstatus);
    }
    if ((PINT->ISEL & 0x80U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt7);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif
