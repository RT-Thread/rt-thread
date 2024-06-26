/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_inputmux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.inputmux"
#endif

#if defined(INPUTMUX_RSTS)
#define INPUTMUX_RESETS_ARRAY INPUTMUX_RSTS
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(INPUTMUX_RESETS_ARRAY)
/*!
 * @brief Get instance number for INPUTMUX module.
 *
 * @param base INPUTMUX peripheral base address
 */
static uint32_t INPUTMUX_GetInstance(INPUTMUX_Type *base);
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(INPUTMUX_RESETS_ARRAY)
/*! @brief Pointers to INPUTMUX bases for each instance. */
static INPUTMUX_Type *const s_inputmuxBases[] = INPUTMUX_BASE_PTRS;

/* Reset array */
static const reset_ip_name_t s_inputmuxResets[] = INPUTMUX_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(INPUTMUX_RESETS_ARRAY)
static uint32_t INPUTMUX_GetInstance(INPUTMUX_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_inputmuxBases); instance++)
    {
        if (s_inputmuxBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_inputmuxBases));

    return instance;
}
#endif

/*!
 * brief    Initialize INPUTMUX peripheral.

 * This function enables the INPUTMUX clock.
 *
 * param base Base address of the INPUTMUX peripheral.
 *
 * retval None.
 */
void INPUTMUX_Init(INPUTMUX_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE) && FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE
#if (defined(FSL_FEATURE_SOC_SCT_COUNT) && (FSL_FEATURE_SOC_SCT_COUNT > 0))
    CLOCK_EnableClock(kCLOCK_Sct);
#endif /* FSL_FEATURE_SOC_SCT_COUNT */
    CLOCK_EnableClock(kCLOCK_Dma);
#else
    CLOCK_EnableClock(kCLOCK_InputMux);
#endif /* FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(INPUTMUX_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_inputmuxResets[INPUTMUX_GetInstance(base)]);
#endif
}

/*!
 * brief Attaches a signal
 *
 * This function attaches multiplexed signals from INPUTMUX to target signals.
 * For example, to attach GPIO PORT0 Pin 5 to PINT peripheral, do the following:
 * code
 *      INPUTMUX_AttachSignal(INPUTMUX, 2, kINPUTMUX_GpioPort0Pin5ToPintsel);
 * endcode
 * In this example, INTMUX has 8 registers for PINT, PINT_SEL0~PINT_SEL7.
 * With parameter p index specified as 2, this function configures register PINT_SEL2.
 *
 * param base Base address of the INPUTMUX peripheral.
 * param index The serial number of destination register in the group of INPUTMUX registers with same name.
 * param connection Applies signal from source signals collection to target signal.
 *
 * retval None.
 */
void INPUTMUX_AttachSignal(INPUTMUX_Type *base, uint32_t index, inputmux_connection_t connection)
{
    uint32_t pmux_id;
    uint32_t output_id;

    /* extract pmux to be used */
    pmux_id = ((uint32_t)(connection)) >> PMUX_SHIFT;
    /*  extract function number */
    output_id = ((uint32_t)(connection)) & ((1UL << PMUX_SHIFT) - 1U);
    /* programm signal */
    *(volatile uint32_t *)(((uint32_t)base) + pmux_id + (index * 4U)) = output_id;
}

#if defined(FSL_FEATURE_INPUTMUX_HAS_SIGNAL_ENA)
/*!
 * brief Enable/disable a signal
 *
 * This function gates the INPUTPMUX clock.
 *
 * param base Base address of the INPUTMUX peripheral.
 * param signal Enable signal register id and bit offset.
 * param enable Selects enable or disable.
 *
 * retval None.
 */
void INPUTMUX_EnableSignal(INPUTMUX_Type *base, inputmux_signal_t signal, bool enable)
{
    uint32_t ena_id;
    uint32_t ena_id_mask = (1UL << (32U - ENA_SHIFT)) - 1U;
    uint32_t bit_offset;

#if defined(FSL_FEATURE_INPUTMUX_HAS_CHANNEL_MUX) && FSL_FEATURE_INPUTMUX_HAS_CHANNEL_MUX
    uint32_t chmux_offset;
    uint32_t chmux_value;

    /* Only enable need to update channel mux */
    if (enable && ((((uint32_t)signal) & (1UL << CHMUX_AVL_SHIFT)) != 0U))
    {
        chmux_offset = (((uint32_t)signal) >> CHMUX_OFF_SHIFT) & ((1UL << (CHMUX_AVL_SHIFT - CHMUX_OFF_SHIFT)) - 1UL);
        chmux_value  = (((uint32_t)signal) >> CHMUX_VAL_SHIFT) & ((1UL << (CHMUX_OFF_SHIFT - CHMUX_VAL_SHIFT)) - 1UL);
        *(volatile uint32_t *)(((uint32_t)base) + chmux_offset) = chmux_value;
    }
    ena_id_mask = (1UL << (CHMUX_VAL_SHIFT - ENA_SHIFT)) - 1U;
#endif
    /* extract enable register to be used */
    ena_id = (((uint32_t)signal) >> ENA_SHIFT) & ena_id_mask;
    /* extract enable bit offset */
    bit_offset = ((uint32_t)signal) & ((1UL << ENA_SHIFT) - 1U);
    /* set signal */
    if (enable)
    {
        *(volatile uint32_t *)(((uint32_t)base) + ena_id) |= (1UL << bit_offset);
    }
    else
    {
        *(volatile uint32_t *)(((uint32_t)base) + ena_id) &= ~(1UL << bit_offset);
    }
}
#endif

/*!
 * brief    Deinitialize INPUTMUX peripheral.

 * This function disables the INPUTMUX clock.
 *
 * param base Base address of the INPUTMUX peripheral.
 *
 * retval None.
 */
void INPUTMUX_Deinit(INPUTMUX_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE) && FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE
#if (defined(FSL_FEATURE_SOC_SCT_COUNT) && (FSL_FEATURE_SOC_SCT_COUNT > 0))
    CLOCK_DisableClock(kCLOCK_Sct);
#endif /* FSL_FEATURE_SOC_SCT_COUNT */
    CLOCK_DisableClock(kCLOCK_Dma);
#else
    CLOCK_DisableClock(kCLOCK_InputMux);
#endif /* FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
