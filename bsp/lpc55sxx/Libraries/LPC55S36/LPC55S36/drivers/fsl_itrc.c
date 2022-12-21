/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_itrc.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.itrc"
#endif

#define b11 0x3u
#define b10 0x2u
#define b01 0x1u

/* Value used to trigger SW Events */
#define SW_EVENT_VAL 0x5AA55AA5u

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * Weak implementation of ITRC IRQ, should be re-defined by user when using ITRC IRQ
 */
__WEAK void ITRC0_DriverIRQHandler(void)
{
    /* ITRC generates IRQ until corresponding bit in STATUS is cleared by calling
     * ITRC_ClearStatus(ITRC,((uint32_t)kITRC_Irq)
     */
}

/*!
 * brief Clear ITRC status
 *
 * This function clears corresponding ITRC event or action in STATUS register.
 *
 * param base ITRC peripheral base address
 * param word 32bit word represent corresponding event/action in STATUS register to be cleared (see
 * ITRC_STATUS_INx/OUTx_STATUS)
 * return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearStatus(ITRC_Type *base, uint32_t word)
{
    /* If reserved/unused bits in STATUS register are set in 'word' parameter, return kStatus_InvalidArgument */
    if ((word & ~(IN_EVENTS_MASK | OUT_ACTIONS_MASK)) != 0u)
    {
        return kStatus_InvalidArgument;
    }

    base->STATUS |= word;

    return kStatus_Success;
}

/*!
 * brief Clear all ITRC status
 *
 * This clears all event and action status.
 *
 * param base ITRC peripheral base address
 * return Status of the ITRC
 */
status_t ITRC_ClearAllStatus(ITRC_Type *base)
{
    base->STATUS |= (IN_EVENTS_MASK | OUT_ACTIONS_MASK);

    return kStatus_Success;
}

/*!
 * brief Trigger ITRC SW Event 0
 *
 * This funciton set SW_EVENT0 register with value !=0 which triggers ITRC SW Event 0.
 *
 * param base ITRC peripheral base address
 */
void ITRC_SetSWEvent0(ITRC_Type *base)
{
    base->SW_EVENT0 = SW_EVENT_VAL;
}

/*!
 * brief Trigger ITRC SW Event 1
 *
 * This funciton set SW_EVENT1 register with value !=0 which triggers ITRC SW Event 1.
 *
 * param base ITRC peripheral base address
 */
void ITRC_SetSWEvent1(ITRC_Type *base)
{
    base->SW_EVENT1 = SW_EVENT_VAL;
}

/*!
 * brief Set ITRC Action to Event
 *
 * This function sets input Event signal to corresponding output Action response signal.
 *
 * param base ITRC peripheral base address
 * param out ITRC OUT signal action
 * param in ITRC IN signal event
 * param lock if set locks INx_SEL configuration. This can be cleared only by PMC Core reset.
 * param enable if set input Event will be selected for output Action, otherwise disable (if not already locked).
 * return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_SetActionToEvent(
    ITRC_Type *base, itrc_out_signals_t out, itrc_input_signals_t in, itrc_lock_t lock, itrc_enable_t enable)
{
    uint32_t sel0, sel1, index, select_AND_mask;

    /*   prepare values for INx_SEL0/1 bit-field according to secure techniques and register behavior
     *    +------------+------------+------------------+---------------------------+
     *    |  INx_SEL0  |  INx_SEL1  | Signal selected? |      Writable field?      |
     *    +------------+------------+------------------+---------------------------+
     *    | 10         | 10         | No               | Yes (default after reset) |
     *    | 01         | 10         | Yes              | Yes                       |
     *    | don't care | !="10"     | Yes              | No                        |
     *    | 00 or 11   | don't care | Yes              | No                        |
     *    +------------+------------+------------------+---------------------------+
     */
    if ((lock == kITRC_Unlock) && (enable == kITRC_Disable))
    {
        sel0 = b10;
        sel1 = b10;
    }
    else if ((lock == kITRC_Unlock) && (enable == kITRC_Enable))
    {
        sel0 = b01;
        sel1 = b10;
    }
    else
    {
        sel0 = b11;
        sel1 = b11;
    }

    /* Compute index for INx_SEL0/1 bit-field within OUTy_SEL0/1 registers */
    index = 2u * in;
    /* Prepare AND mask to set INx_SEL0 accordingly */
    select_AND_mask = ~(b11 << index);

    /* Last possible index in OUTx_SELy registers is 30 */
    if (index > 30u)
    {
        return kStatus_InvalidArgument;
    }

    switch (out)
    {
        case kITRC_Irq:
            base->OUT0_SEL0 = (base->OUT0_SEL0 & select_AND_mask) | (sel0 << index);
            base->OUT0_SEL1 |= sel1 << index;
            break;
        case kITRC_CssReset:
            base->OUT1_SEL0 = (base->OUT1_SEL0 & select_AND_mask) | (sel0 << index);
            base->OUT1_SEL1 |= sel1 << index;
            break;

        case kITRC_PufZeroize:
            base->OUT2_SEL0 = (base->OUT2_SEL0 & select_AND_mask) | (sel0 << index);
            base->OUT2_SEL1 |= sel1 << index;
            break;

        case kITRC_RamZeroize:
            base->OUT3_SEL0 = (base->OUT3_SEL0 & select_AND_mask) | (sel0 << index);
            base->OUT3_SEL1 |= sel1 << index;
            break;

        case kITRC_ChipReset:
            base->OUT4_SEL0 = (base->OUT4_SEL0 & select_AND_mask) | (sel0 << index);
            base->OUT4_SEL1 |= sel1 << index;
            break;

        case kITRC_TamperOut:
            base->OUT5_SEL0 = (base->OUT5_SEL0 & select_AND_mask) | (sel0 << index);
            base->OUT5_SEL1 |= sel1 << index;
            break;
        default:
            /* This case shouldn't be reached. */
            return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

/*!
 * brief Get ITRC Status
 *
 * This function returns ITRC register status.
 *
 * param base ITRC peripheral base address
 * return Value of ITRC STATUS register
 */
status_t ITRC_GetStatus(ITRC_Type *base)
{
    return base->STATUS;
}

/*!
 * brief Initialize ITRC
 *
 * This function initializes ITRC by enabling IRQ.
 *
 * param base ITRC peripheral base address
 * return Status of the init operation
 */
status_t ITRC_Init(ITRC_Type *base)
{
    NVIC_EnableIRQ(ITRC0_IRQn);

    return kStatus_Success;
}

/*!
 * brief Deinitialize ITRC
 *
 * This function just disable ITRC IRQ.
 *
 * param base ITRC peripheral base address
 */
void ITRC_Deinit(ITRC_Type *base)
{
    NVIC_DisableIRQ(ITRC0_IRQn);
}
