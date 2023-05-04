/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smartcard_emvsim.h"
#include "fsl_smartcard_phy.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.smartcard_phy_emvsim"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static uint32_t smartcard_phy_emvsim_InterfaceClockInit(EMVSIM_Type *base,
                                                        const smartcard_interface_config_t *config,
                                                        uint32_t srcClock_Hz);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief This function initializes clock module used for card clock generation
 */
static uint32_t smartcard_phy_emvsim_InterfaceClockInit(EMVSIM_Type *base,
                                                        const smartcard_interface_config_t *config,
                                                        uint32_t srcClock_Hz)
{
    assert((NULL != config) && (0u != srcClock_Hz));

    uint32_t emvsimClkMhz = 0u;
    uint8_t emvsimPRSCValue;

    /* Retrieve EMV SIM clock */
    emvsimClkMhz = srcClock_Hz / 1000000u;
    /* Calculate MOD value */
    emvsimPRSCValue = (uint8_t)((emvsimClkMhz * 1000u) / (config->smartCardClock / 1000u));
    /* Set clock prescaler */
    base->CLKCFG = (base->CLKCFG & ~EMVSIM_CLKCFG_CLK_PRSC_MASK) | EMVSIM_CLKCFG_CLK_PRSC(emvsimPRSCValue);

    return config->smartCardClock;
}

void SMARTCARD_PHY_GetDefaultConfig(smartcard_interface_config_t *config)
{
    assert((NULL != config));

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->clockToResetDelay = SMARTCARD_INIT_DELAY_CLOCK_CYCLES;
    config->vcc               = kSMARTCARD_VoltageClassB3_3V;
}

status_t SMARTCARD_PHY_Init(void *base, smartcard_interface_config_t const *config, uint32_t srcClock_Hz)
{
    if ((NULL == config) || (0u == srcClock_Hz))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    EMVSIM_Type *emvsimBase = (EMVSIM_Type *)base;

    /* SMARTCARD clock initialization. Clock is still not active after this call */
    (void)smartcard_phy_emvsim_InterfaceClockInit(emvsimBase, config, srcClock_Hz);

    /* Configure EMVSIM direct interface driver interrupt occur according card presence */
    if ((emvsimBase->PCSR & EMVSIM_PCSR_SPDP_MASK) != 0u)
    {
        emvsimBase->PCSR &= ~EMVSIM_PCSR_SPDES_MASK;
    }
    else
    {
        emvsimBase->PCSR |= EMVSIM_PCSR_SPDES_MASK;
    }
    /* Un-mask presence detect interrupt flag */
    emvsimBase->PCSR &= ~EMVSIM_PCSR_SPDIM_MASK;

    return kStatus_SMARTCARD_Success;
}

void SMARTCARD_PHY_Deinit(void *base, smartcard_interface_config_t const *config)
{
    assert((NULL != config));
    /* Deactivate VCC, CLOCK */
    ((EMVSIM_Type *)base)->PCSR &= ~(EMVSIM_PCSR_SCEN_MASK | EMVSIM_PCSR_SVCC_EN_MASK);
}

status_t SMARTCARD_PHY_Activate(void *base, smartcard_context_t *context, smartcard_reset_type_t resetType)
{
    if ((NULL == context) || (NULL == context->timeDelay))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    assert(context->interfaceConfig.vcc == kSMARTCARD_VoltageClassB3_3V);

    EMVSIM_Type *emvsimBase = (EMVSIM_Type *)base;

    context->timersState.initCharTimerExpired = false;
    context->resetType                        = resetType;

    /* Disable receiver to deactivate GPC timers trigger */
    emvsimBase->CTRL &= ~EMVSIM_CTRL_RCV_EN_MASK;
    if (resetType == kSMARTCARD_ColdReset)
    { /* Set polarity of VCC to active high, Enable VCC for SMARTCARD, Enable smart card clock */
        emvsimBase->PCSR =
            (emvsimBase->PCSR & ~EMVSIM_PCSR_VCCENP_MASK) | (EMVSIM_PCSR_SVCC_EN_MASK | EMVSIM_PCSR_SCEN_MASK);
        /* Set transfer inversion to default(direct) value */
        emvsimBase->CTRL &= ~EMVSIM_CTRL_IC_MASK;
    }
    else if (resetType == kSMARTCARD_WarmReset)
    { /* Ensure that card is already active */
        if (!context->cardParams.active)
        { /* Card is not active;hence return */
            return kStatus_SMARTCARD_CardNotActivated;
        }
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }
    /* Set Reset low */
    emvsimBase->PCSR &= ~EMVSIM_PCSR_SRST_MASK;
    /* Calculate time delay needed for reset */
    uint32_t temp =
        ((((uint32_t)10000u * context->interfaceConfig.clockToResetDelay) / context->interfaceConfig.smartCardClock) *
         100u) +
        1u;
    context->timeDelay(temp);
    /* Pull reset HIGH Now to mark the end of Activation sequence */
    emvsimBase->PCSR |= EMVSIM_PCSR_SRST_MASK;
    /* Disable GPC timers input clock */
    emvsimBase->CLKCFG &= ~(EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK | EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK);
    /* Down counter trigger, and clear any pending counter status flag */
    emvsimBase->TX_STATUS = EMVSIM_TX_STATUS_GPCNT1_TO_MASK | EMVSIM_TX_STATUS_GPCNT0_TO_MASK;
    /* Set counter value for TS detection delay */
    emvsimBase->GPCNT0_VAL = (SMARTCARD_INIT_DELAY_CLOCK_CYCLES + SMARTCARD_INIT_DELAY_CLOCK_CYCLES_ADJUSTMENT);
    /* Pre-load counter value for ATR duration delay */
    emvsimBase->GPCNT1_VAL = (SMARTCARD_EMV_ATR_DURATION_ETU + SMARTCARD_ATR_DURATION_ADJUSTMENT);
    /* Select the clock for GPCNT for both TS detection and early start of ATR duration counter */
    emvsimBase->CLKCFG |=
        (EMVSIM_CLKCFG_GPCNT0_CLK_SEL(kEMVSIM_GPCCardClock) | EMVSIM_CLKCFG_GPCNT1_CLK_SEL(kEMVSIM_GPCTxClock));
    /* Set receiver to ICM mode, Flush RX FIFO */
    emvsimBase->CTRL |= (EMVSIM_CTRL_ICM_MASK | EMVSIM_CTRL_FLSH_RX_MASK);
    /* Enable counter interrupt for TS detection */
    emvsimBase->INT_MASK &= ~EMVSIM_INT_MASK_GPCNT0_IM_MASK;
    /* Clear any pending status flags */
    emvsimBase->RX_STATUS = 0xFFFFFFFFu;
    /* Enable receiver */
    emvsimBase->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;
    /* Here the card was activated */
    context->cardParams.active = true;

    return kStatus_SMARTCARD_Success;
}

status_t SMARTCARD_PHY_Deactivate(void *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    EMVSIM_Type *emvsimBase = (EMVSIM_Type *)base;

    /* Assert Reset */
    emvsimBase->PCSR &= ~EMVSIM_PCSR_SRST_MASK;
    /* Stop SMARTCARD clock generation */
    emvsimBase->PCSR &= ~EMVSIM_PCSR_SCEN_MASK;
    /* Deactivate card by disabling VCC */
    emvsimBase->PCSR &= ~EMVSIM_PCSR_SVCC_EN_MASK;
    /* According EMV 4.3 specification deactivation sequence should be done within 100ms.
     * The period is measured from the time that RST is set to state L to the time that Vcc
     * reaches 0.4 V or less.
     */
    context->timeDelay(100 * 1000);
    /* Here the card was deactivated */
    context->cardParams.active = false;

    return kStatus_SMARTCARD_Success;
}

status_t SMARTCARD_PHY_Control(void *base,
                               smartcard_context_t *context,
                               smartcard_interface_control_t control,
                               uint32_t param)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    status_t status = kStatus_SMARTCARD_Success;

    switch (control)
    {
        case kSMARTCARD_InterfaceSetVcc:
            /* Only 3.3V interface supported by the direct interface */
            assert((smartcard_card_voltage_class_t)param == kSMARTCARD_VoltageClassB3_3V);
            context->interfaceConfig.vcc = (smartcard_card_voltage_class_t)param;
            break;
        case kSMARTCARD_InterfaceSetClockToResetDelay:
            /* Set interface clock to Reset delay set by caller */
            context->interfaceConfig.clockToResetDelay = param;
            break;
        case kSMARTCARD_InterfaceReadStatus:
            /* Expecting active low present detect */
            context->cardParams.present = (bool)((emvsim_presence_detect_status_t)(uint32_t)(
                                                     (((EMVSIM_Type *)base)->PCSR & EMVSIM_PCSR_SPDP_MASK) >>
                                                     EMVSIM_PCSR_SPDP_SHIFT) == kEMVSIM_DetectPinIsLow);
            break;
        default:
            status = kStatus_SMARTCARD_InvalidInput;
            break;
    }

    return status;
}
