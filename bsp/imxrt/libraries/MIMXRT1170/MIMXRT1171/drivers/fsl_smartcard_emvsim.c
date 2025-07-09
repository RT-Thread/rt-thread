/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smartcard_emvsim.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.smartcard_emvsim"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to emvsim bases for each instance. */
static EMVSIM_Type *const s_emvsimBases[] = EMVSIM_BASE_PTRS;

/*! @brief Pointers to emvsim IRQ number for each instance. */
static const IRQn_Type s_emvsimIRQ[] = EMVSIM_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to emvsim clocks for each instance. */
static const clock_ip_name_t s_emvsimClock[] = EMVSIM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* #define CARDSIM_EXTRADELAY_USED */

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void smartcard_emvsim_CompleteSendData(EMVSIM_Type *base, smartcard_context_t *context);
static void smartcard_emvsim_StartSendData(EMVSIM_Type *base, smartcard_context_t *context);
static void smartcard_emvsim_CompleteReceiveData(EMVSIM_Type *base, smartcard_context_t *context);
static void smartcard_emvsim_StartReceiveData(EMVSIM_Type *base, smartcard_context_t *context);
static void smartcard_emvsim_SetTransferType(EMVSIM_Type *base,
                                             smartcard_context_t *context,
                                             smartcard_control_t control);
static uint32_t smartcard_emvsim_GetInstance(EMVSIM_Type *base);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Get the UART instance from peripheral base address.
 *
 * @param base UART peripheral base address.
 * @return UART instance.
 */
static uint32_t smartcard_emvsim_GetInstance(EMVSIM_Type *base)
{
    uint8_t instance          = 0;
    uint32_t emvsimArrayCount = (sizeof(s_emvsimBases) / sizeof(s_emvsimBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < emvsimArrayCount; instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_emvsimBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < emvsimArrayCount);

    return instance;
}
/*!
 * @brief Finish up a transmit by completing the process of sending data and disabling the interrupt.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_emvsim_CompleteSendData(EMVSIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Disable ETC and TDT interrupt */
    base->INT_MASK |= (EMVSIM_INT_MASK_ETC_IM_MASK | EMVSIM_INT_MASK_TDT_IM_MASK);

    /* Disable transmitter */
    base->CTRL &= ~EMVSIM_CTRL_XMT_EN_MASK;
    /* Clear receive status flag */
    base->RX_STATUS = EMVSIM_RX_STATUS_RX_DATA_MASK;
    /* Enable Receiver */
    base->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;
    /* Update the information of the module driver context */
    context->xIsBusy       = false;
    context->transferState = kSMARTCARD_IdleState;
    /* Clear txSize to avoid any spurious transmit from ISR */
    context->xSize = 0u;
    /* Invoke user call-back */
    if (NULL != context->transferCallback)
    {
        context->transferCallback(context, context->transferCallbackParam);
    }
}

/*!
 * @brief Finish up a receive by completing the process of receiving data and disabling the interrupt.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_emvsim_CompleteReceiveData(EMVSIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Disable RDT and RX_DATA interrupt */
    base->INT_MASK |= (EMVSIM_INT_MASK_RDT_IM_MASK | EMVSIM_INT_MASK_RX_DATA_IM_MASK);

    /* Read data from fifo */
    while (((base->RX_STATUS & EMVSIM_RX_STATUS_RX_CNT_MASK) != 0u) && ((context->xSize) > 0u))
    {
        /* Get data and put into receive buffer */
        *context->xBuff = (uint8_t)(base->RX_BUF);
        ++context->xBuff;
        --context->xSize;
    }

    /* Update the information of the module driver context */
    context->xIsBusy = false;
    /* Invoke user call-back */
    if (NULL != context->transferCallback)
    {
        context->transferCallback(context, context->transferCallbackParam);
    }
}

/*!
 * @brief Initiate (start) a transmit by beginning the process of sending data and enabling the interrupt.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_emvsim_StartSendData(EMVSIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    uint32_t delay   = 0u;
    uint32_t control = 0u;

    /* Block guard time */
    /* 22 etus (16 Receiver Clocks == 1 etu) */
    delay = 22u * 16u;
    /* Disable all functionality like protocol timers, NACK generation */
    control       = base->CTRL;
    base->CTRL    = 0u;
    base->TX_GETU = context->cardParams.GTN;
    /* Clear Global counter time-out flag */
    base->TX_STATUS = EMVSIM_TX_STATUS_GPCNT1_TO_MASK;
    /* Disable counter interrupt */
    base->INT_MASK |= EMVSIM_INT_MASK_GPCNT1_IM_MASK;
    /* Set counter value */
    base->GPCNT1_VAL = delay;
    /* Select the clock for GPCNT */
    base->CLKCFG =
        (base->CLKCFG & ~EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK) | EMVSIM_CLKCFG_GPCNT1_CLK_SEL(kEMVSIM_GPCRxClock);
    /* Trigger the counter */
    base->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;
    /* Wait until counter overflow event occur */
    while ((base->TX_STATUS & EMVSIM_TX_STATUS_GPCNT1_TO_MASK) == 0u)
    {
    }
    /* Clear status flag and disable GPCNT1 clock */
    base->TX_STATUS = EMVSIM_TX_STATUS_GPCNT1_TO_MASK;
    base->CLKCFG &= ~EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK;
    /* Restore Control register */
    base->CTRL = control & ~(EMVSIM_CTRL_XMT_EN_MASK | EMVSIM_CTRL_RCV_EN_MASK);
    /* Update transferState */
    context->transferState = kSMARTCARD_TransmittingState;
    context->xIsBusy       = true;

    /* Flush transmitter */
    base->CTRL |= EMVSIM_CTRL_FLSH_TX_MASK;

    /* Enable transmitter */
    base->CTRL |= EMVSIM_CTRL_XMT_EN_MASK;

    /* Set transmitter data threshold value to 0 - TDTF is set when the fifo is empty */
    base->TX_THD &= ~EMVSIM_TX_THD_TDT_MASK;

    /* Enable TDT interrupt */
    base->INT_MASK &= ~EMVSIM_INT_MASK_TDT_IM_MASK;
}

/*!
 * @brief Initiate (start) a receive by beginning the process of receiving data and enabling the interrupt.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_emvsim_StartReceiveData(EMVSIM_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Initialize the module driver context structure to indicate transfer in progress */
    context->xIsBusy = true;
    /* Enable BWT Timer interrupt to occur */
    base->INT_MASK &= ~EMVSIM_INT_MASK_BWT_ERR_IM_MASK;
    /* Disable transmitter */
    base->CTRL &= ~EMVSIM_CTRL_XMT_EN_MASK;
    /* Enable receiver and switch to receive direction */
    base->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;

    /* Set rx threshold value - number of bytes that must exist in the Receive FIFO to trigger the receive data
     * threshold interrupt flag (RDTF).*/
    if (context->xSize < context->rxFifoThreshold)
    {
        uint32_t rx_thd;
        rx_thd = (base->RX_THD & ~EMVSIM_RX_THD_RDT_MASK);
        rx_thd |= context->xSize;
        base->RX_THD = rx_thd;
    }
    else
    {
        base->RX_THD = ((base->RX_THD & ~EMVSIM_RX_THD_RDT_MASK) | context->rxFifoThreshold);
    }

    /* Enable RDT interrupt - count of bytes in rx fifo is equal or greater than threshold RX_THD[RDT] */
    base->INT_MASK &= ~EMVSIM_INT_MASK_RDT_IM_MASK;

    if (context->tType == kSMARTCARD_T1Transport)
    {
        /* Enable interrupt when new byte is received - in T=1 is necessary to disable BWT interrupt and enable CWT
         * interrupt after receiving the first byte */
        base->INT_MASK &= ~EMVSIM_INT_MASK_RX_DATA_IM_MASK;
    }
}

/*!
 * @brief Sets up the EMVSIM hardware for T=0 or T=1 protocol data exchange and initialize timer values.
 *
 * @param base The EMVSIM peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_emvsim_SetTransferType(EMVSIM_Type *base,
                                             smartcard_context_t *context,
                                             smartcard_control_t control)
{
    assert((NULL != context));
    assert((control == kSMARTCARD_SetupATRMode) || (control == kSMARTCARD_SetupT0Mode) ||
           (control == kSMARTCARD_SetupT1Mode));

    uint16_t temp16 = 0u;
    uint32_t bwiVal = 0u;
    uint8_t tdt     = 0u;

    if (control == kSMARTCARD_SetupATRMode)
    {
        /* Disable all functionality at first */
        base->CTRL &= ~(EMVSIM_CTRL_RCVR_11_MASK | EMVSIM_CTRL_XMT_CRC_LRC_MASK | EMVSIM_CTRL_LRC_EN_MASK |
                        EMVSIM_CTRL_ANACK_MASK | EMVSIM_CTRL_ONACK_MASK | EMVSIM_CTRL_RCV_EN_MASK);
        /* Set default values as per EMV specification */
        context->cardParams.Fi       = 372u;
        context->cardParams.Di       = 1u;
        context->cardParams.currentD = 1u;
        context->cardParams.WI       = 0x0Au;
        context->cardParams.GTN      = 0x00u;
        /* Set default baudrate/ETU time based on EMV parameters and card clock */
        base->DIVISOR = (((uint32_t)context->cardParams.Fi / context->cardParams.currentD) & 0x1FFu);
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480)
         * EMVSIM formula: BWT_VAL[15:0] = CWT_VAL[15:0] */
        temp16 = (960u * context->cardParams.currentD * context->cardParams.WI) +
                 (context->cardParams.currentD * 480u) + SMARTCARD_WWT_ADJUSTMENT;
        base->CWT_VAL = temp16;
        base->BWT_VAL = temp16;
        /* Set Extended Guard Timer value
         * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN = GTN equal to 255 -> 12
         * EMVSIM formula: same as above */
        base->TX_GETU = context->cardParams.GTN;
        /* Setting Rx threshold so that an interrupt is generated when a NACK is
           sent either due to parity error or wrong INIT char*/
        base->RX_THD = EMVSIM_RX_THD_RDT(1);
        /* Setting up Tx NACK threshold */
        tdt = (uint8_t)(((base->PARAM & EMVSIM_PARAM_TX_FIFO_DEPTH_MASK) >> EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT) - 1u);
        base->TX_THD = (EMVSIM_TX_THD_TNCK_THD(SMARTCARD_EMV_TX_NACK_THRESHOLD) | EMVSIM_TX_THD_TDT(tdt));
        /* Clear all pending interrupts */
        base->RX_STATUS = 0xFFFFFFFFu;
        /* Enable Tx NACK threshold interrupt to occur */
        base->INT_MASK &= ~EMVSIM_INT_MASK_TNACK_IM_MASK;
        /* Set transport type to T=0 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T0Transport;
    }
    else if (control == kSMARTCARD_SetupT0Mode)
    {
        /* Disable receiver at first if it's not, Disable T=0 mode counters 1st,
         * Setup for single wire ISO7816 mode (setup 12 etu mode).
         * Set transport protocol type to T=0, Disable initial character detection.*/
        base->CTRL &=
            ~(EMVSIM_CTRL_RCV_EN_MASK | EMVSIM_CTRL_CWT_EN_MASK | EMVSIM_CTRL_BWT_EN_MASK | EMVSIM_CTRL_RCVR_11_MASK |
              EMVSIM_CTRL_XMT_CRC_LRC_MASK | EMVSIM_CTRL_LRC_EN_MASK | EMVSIM_CTRL_ICM_MASK);
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480)
         * EMVSIM formula: BWT_VAL[15:0] = CWT_VAL[15:0]  */
        temp16 = (960u * context->cardParams.currentD * context->cardParams.WI) +
                 (context->cardParams.currentD * 480u) + SMARTCARD_WWT_ADJUSTMENT;
        base->CWT_VAL = temp16;
        base->BWT_VAL = temp16;
        /* Set Extended Guard Timer value
         * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN = GTN equal to 255 -> 12
         * EMVSIM formula: same as above for range [0:254]
         * Fix for EMV. If TX_GETU == 0 in T0 mode, 3 stop bits are inserted. */
        context->cardParams.GTN = (context->cardParams.GTN == 0xFFu) ? 0x00u : context->cardParams.GTN;
        base->TX_GETU           = context->cardParams.GTN;
        /* Setting Rx threshold so that an interrupt is generated when a NACK is
        sent either due to parity error or wrong INIT char */
        base->RX_THD = (EMVSIM_RX_THD_RNCK_THD(SMARTCARD_EMV_RX_NACK_THRESHOLD) | EMVSIM_RX_THD_RDT(1));
        /* Setting up Tx NACK threshold */
        tdt = (uint8_t)(((base->PARAM & EMVSIM_PARAM_TX_FIFO_DEPTH_MASK) >> EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT) - 1u);
        base->TX_THD = (EMVSIM_TX_THD_TNCK_THD(SMARTCARD_EMV_TX_NACK_THRESHOLD) | EMVSIM_TX_THD_TDT(tdt));
        /* Enable Tx NACK threshold interrupt to occur */
        base->INT_MASK &= ~EMVSIM_INT_MASK_TNACK_IM_MASK;
        /* Enable T=0 mode counters, Enable NACK on error interrupt and NACK on overflow interrupt */
        base->CTRL |=
            (EMVSIM_CTRL_CWT_EN_MASK | EMVSIM_CTRL_BWT_EN_MASK | EMVSIM_CTRL_ANACK_MASK | EMVSIM_CTRL_ONACK_MASK);
        /* Set transport type to T=0 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T0Transport;
    }
    else
    { /* Disable T=1 mode counters 1st, Disable NACK on error interrupt, Disable NACK on overflow interrupt */
        base->CTRL &= ~(EMVSIM_CTRL_CWT_EN_MASK | EMVSIM_CTRL_BWT_EN_MASK | EMVSIM_CTRL_ANACK_MASK |
                        EMVSIM_CTRL_ONACK_MASK | EMVSIM_CTRL_XMT_CRC_LRC_MASK | EMVSIM_CTRL_LRC_EN_MASK);
        /* Calculate and set Block Wait Timer (BWT) value
         * EMV expectation: BWT = 11 + (2^BWI x 960 x D) + (D x 960) = 11 + (2^BWI + 1) x 960 x D
         * EMVSIM formula: BWT = Same */
        bwiVal = 11u + ((((uint32_t)1u << context->cardParams.BWI) + 1u) * 960u * context->cardParams.currentD);
#ifdef CARDSIM_EXTRADELAY_USED
        base->BWT_VAL = bwiVal + 100u;
#else
        base->BWT_VAL = bwiVal;
#endif
        /* Calculate and set Character Wait Timer (CWT) value
         * EMV expectation: CWT = ((2^CWI + 11) + 4)
         * EMVSIM formula: CWT = Same */
        if (context->cardParams.currentD == 1u)
        {
#ifdef CARDSIM_EXTRADELAY_USED
            temp16 = ((uint16_t)1u << context->cardParams.CWI) + 16u;
#else
            temp16 = ((uint16_t)1u << context->cardParams.CWI) + 15u;
#endif
        }
        else
        {
#ifdef CARDSIM_EXTRADELAY_USED
            temp16 = ((uint16_t)1u << context->cardParams.CWI) + 20u + SMARTCARD_CWT_ADJUSTMENT;
#else
            temp16 = ((uint16_t)1u << context->cardParams.CWI) + 15u + SMARTCARD_CWT_ADJUSTMENT;
#endif
        }
        /* EMV = 15, ISO = 11,
         * EMV expectation: BGT = 22
         * EMVSIM formula: BGT = Same */
        base->CWT_VAL           = temp16;
        context->cardParams.BGI = 22u;
        base->BGT_VAL           = context->cardParams.BGI;
        /* Set Extended Guard Timer value
         * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN = GTN equal to 255 -> 11
         * EMVSIM formula: same as above */
        base->TX_GETU = context->cardParams.GTN;
        /* Setup for single wire ISO7816 mode,
         * Set transport protocol type to T=1, Enable T=0 mode counters */
        base->CTRL |= (EMVSIM_CTRL_RCVR_11_MASK | EMVSIM_CTRL_CWT_EN_MASK | EMVSIM_CTRL_BWT_EN_MASK);
        /* Setting Rx threshold */
        base->RX_THD = (EMVSIM_RX_THD_RNCK_THD(SMARTCARD_EMV_RX_NACK_THRESHOLD) | EMVSIM_RX_THD_RDT(1));
        /* Setting up Tx threshold */
        tdt = (uint8_t)(((base->PARAM & EMVSIM_PARAM_TX_FIFO_DEPTH_MASK) >> EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT) - 1u);
        base->TX_THD = (EMVSIM_TX_THD_TDT(tdt) | EMVSIM_TX_THD_TNCK_THD(SMARTCARD_EMV_TX_NACK_THRESHOLD));
        /* Set transport type to T=1 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T1Transport;
    }
}

/*!
 * brief Fills in the smartcard_card_params structure with default values according to the EMV 4.3 specification.
 *
 * param cardParams The configuration structure of type smartcard_interface_config_t.
 * Function fill in members:
 *        Fi = 372;
 *        Di = 1;
 *        currentD = 1;
 *        WI = 0x0A;
 *        GTN = 0x00;
 * with default values.
 */
void SMARTCARD_EMVSIM_GetDefaultConfig(smartcard_card_params_t *cardParams)
{
    /* Initializes the configure structure to zero. */
    (void)memset(cardParams, 0, sizeof(*cardParams));

    /* EMV default values */
    cardParams->Fi       = 372u;
    cardParams->Di       = 1u;
    cardParams->currentD = 1u;
    cardParams->WI       = 0x0Au;
    cardParams->GTN      = 0x00u;
}

/*!
 * brief Initializes an EMVSIM peripheral for the Smart card/ISO-7816 operation.
 *
 * This function un-gates the EMVSIM clock, initializes the module to EMV default settings,
 * configures the IRQ, enables the module-level interrupt to the core and, initializes the driver context.
 *
 * param base The EMVSIM peripheral base address.
 * param context A pointer to the smart card driver context structure.
 * param srcClock_Hz Smart card clock generation module source clock.
 *
 * return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_EMVSIM_Init(EMVSIM_Type *base, smartcard_context_t *context, uint32_t srcClock_Hz)
{
    assert((NULL != base));

    if ((NULL == context) || (srcClock_Hz == 0u))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    uint32_t instance = smartcard_emvsim_GetInstance(base);
/* Set source clock for EMVSIM MCGPLLCLK */
#if (defined(FSL_FEATURE_SOC_MCG_COUNT) && FSL_FEATURE_SOC_MCG_COUNT)
    CLOCK_SetEmvsimClock(1u);
#endif
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable emvsim clock */
    CLOCK_EnableClock(s_emvsimClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    context->base = base;
    /* Initialize EMVSIM to a known context. */
    base->CLKCFG     = 0u;
    base->DIVISOR    = 372u;
    base->CTRL       = 0x300u;
    base->INT_MASK   = 0x7FFFu;
    base->RX_THD     = 1u;
    base->TX_THD     = 0u;
    base->PCSR       = 0x1000000u;
    base->TX_GETU    = 0u;
    base->CWT_VAL    = 0xFFFFu;
    base->BWT_VAL    = 0xFFFFFFFFu;
    base->BGT_VAL    = 0u;
    base->GPCNT0_VAL = 0xFFFFu;
    base->GPCNT1_VAL = 0xFFFFu;
    /* Initialize EMVSIM module for SMARTCARD mode of default operation */
    smartcard_emvsim_SetTransferType(base, context, kSMARTCARD_SetupATRMode);
    /* Store information about tx fifo depth */
    context->txFifoEntryCount =
        (uint8_t)((base->PARAM & EMVSIM_PARAM_TX_FIFO_DEPTH_MASK) >> EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT);
    /* Compute max value of rx fifo threshold */
    context->rxFifoThreshold =
        (uint8_t)((base->PARAM & EMVSIM_PARAM_RX_FIFO_DEPTH_MASK) >> EMVSIM_PARAM_RX_FIFO_DEPTH_SHIFT);
    if ((EMVSIM_RX_THD_RDT_MASK >> EMVSIM_RX_THD_RDT_SHIFT) < context->rxFifoThreshold)
    {
        context->rxFifoThreshold = (EMVSIM_RX_THD_RDT_MASK >> EMVSIM_RX_THD_RDT_SHIFT);
    }
/* Enable EMVSIM interrupt on NVIC level. */
#if defined(FSL_FEATURE_SOC_INTMUX_COUNT) && FSL_FEATURE_SOC_INTMUX_COUNT
    if ((uint32_t)s_emvsimIRQ[instance] < (uint32_t)FSL_FEATURE_INTMUX_IRQ_START_INDEX)
    {
        NVIC_EnableIRQ(s_emvsimIRQ[instance]);
    }
#else
    NVIC_EnableIRQ(s_emvsimIRQ[instance]);
#endif
    /* Finally, disable the EMVSIM receiver and transmitter */
    base->CTRL &= ~EMVSIM_CTRL_XMT_EN_MASK & ~EMVSIM_CTRL_RCV_EN_MASK;

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief This function disables the EMVSIM interrupts, disables the transmitter and receiver,
 * flushes the FIFOs, and gates EMVSIM clock in SIM.
 *
 * param base The EMVSIM module base address.
 */
void SMARTCARD_EMVSIM_Deinit(EMVSIM_Type *base)
{
    uint32_t instance = 0u;
    /* In case there is still data in the TX FIFO or shift register that is
     * being transmitted wait till transmit is complete.
     * Wait until the data is completely shifted out of shift register */
    if ((base->TX_STATUS & EMVSIM_TX_STATUS_TX_CNT_MASK) != 0u)
    {
        while ((base->TX_STATUS & EMVSIM_TX_STATUS_ETCF_MASK) == 0u)
        {
        }
    }
    instance = smartcard_emvsim_GetInstance(base);
    /* Disable TX and RX */
    base->CTRL &= ~EMVSIM_CTRL_XMT_EN_MASK & ~EMVSIM_CTRL_RCV_EN_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate EMVSIM module clock */
    CLOCK_DisableClock(s_emvsimClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/* Disable emvsim interrupt in NVIC */
#if defined(FSL_FEATURE_SOC_INTMUX_COUNT) && FSL_FEATURE_SOC_INTMUX_COUNT
    if ((uint32_t)s_emvsimIRQ[instance] < (uint32_t)FSL_FEATURE_INTMUX_IRQ_START_INDEX)
    {
        NVIC_DisableIRQ(s_emvsimIRQ[instance]);
    }
#else
    NVIC_DisableIRQ(s_emvsimIRQ[instance]);
#endif
}

/*!
 * brief Transfer data using interrupts.
 *
 * A non-blocking (also known as asynchronous) function means that the function returns
 * immediately after initiating the transfer function. The application has to get the
 * transfer status to see when the transfer is complete. In other words, after calling the non-blocking
 * (asynchronous) transfer function, the application must get the transfer status to check if the transmit
 * is completed or not.
 *
 * param base The EMVSIM peripheral base address.
 * param context A pointer to a smart card driver context structure.
 * param xfer A pointer to the smart card transfer structure where the linked buffers and sizes are stored.
 *
 * return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_EMVSIM_TransferNonBlocking(EMVSIM_Type *base, smartcard_context_t *context, smartcard_xfer_t *xfer)
{
    if ((NULL == context) || (NULL == xfer) || (xfer->buff == NULL))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    /* Check input parameters */
    if ((0u == xfer->size))
    {
        return kStatus_SMARTCARD_Success;
    }
    /* Check if some transfer is in progress */
    if (0 != SMARTCARD_EMVSIM_GetTransferRemainingBytes(base, context))
    {
        if (kSMARTCARD_Receive == context->direction)
        {
            return kStatus_SMARTCARD_RxBusy;
        }
        else
        {
            return kStatus_SMARTCARD_TxBusy;
        }
    }
    /* Initialize error check flags */
    context->rxtCrossed  = false;
    context->txtCrossed  = false;
    context->parityError = false;
    /* Initialize SMARTCARD context structure to start transfer */
    context->xBuff = xfer->buff;
    context->xSize = xfer->size;

    if (kSMARTCARD_Receive == xfer->direction)
    {
        context->direction     = xfer->direction;
        context->transferState = kSMARTCARD_ReceivingState;
        /* Start transfer */
        smartcard_emvsim_StartReceiveData(base, context);
    }
    else if (kSMARTCARD_Transmit == xfer->direction)
    {
        context->direction     = xfer->direction;
        context->transferState = kSMARTCARD_TransmittingState;
        /* Start transfer */
        smartcard_emvsim_StartSendData(base, context);
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Returns whether the previous EMVSIM transfer has finished.
 *
 * When performing an async transfer, call this function to ascertain the context of the
 * current transfer: in progress (or busy) or complete (success). If the
 * transfer is still in progress, the user can obtain the number of words that have not been
 * transferred.
 *
 * param base The EMVSIM module base address.
 * param context A pointer to a smart card driver context structure.
 *
 * return The number of bytes not transferred.
 */
int32_t SMARTCARD_EMVSIM_GetTransferRemainingBytes(EMVSIM_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return -1;
    }
    if (context->xIsBusy)
    {
        if (context->direction == kSMARTCARD_Transmit)
        {
            /* Count of bytes in buffer + data in fifo */
            uint32_t count;
            count = context->xSize;
            count += ((base->TX_STATUS & EMVSIM_TX_STATUS_TX_CNT_MASK) >> EMVSIM_TX_STATUS_TX_CNT_SHIFT);
            return (int32_t)count;
        }
        return (int32_t)context->xSize;
    }

    return 0;
}

/*!
 * brief Terminates an asynchronous EMVSIM transfer early.
 *
 * During an async EMVSIM transfer, the user can terminate the transfer early
 * if the transfer is still in progress.
 *
 * param base The EMVSIM peripheral address.
 * param context A pointer to a smart card driver context structure.
 * retval kStatus_SMARTCARD_Success The transmit abort was successful.
 * retval kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
status_t SMARTCARD_EMVSIM_AbortTransfer(EMVSIM_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    context->abortTransfer = true;

    /* Check if a transfer is running. */
    if ((!context->xIsBusy))
    {
        return kStatus_SMARTCARD_NoTransferInProgress;
    }
    /* Call transfer complete to abort transfer */
    if (kSMARTCARD_Receive == context->direction)
    { /* Stop the running transfer. */
        smartcard_emvsim_CompleteReceiveData(base, context);
    }
    else if (kSMARTCARD_Transmit == context->direction)
    { /* Stop the running transfer. */
        smartcard_emvsim_CompleteSendData(base, context);
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Handles EMVSIM module interrupts.
 *
 * param base The EMVSIM peripheral base address.
 * param context A pointer to a smart card driver context structure.
 */
void SMARTCARD_EMVSIM_IRQHandler(EMVSIM_Type *base, smartcard_context_t *context)
{
    if (NULL == context)
    {
        return;
    }

    /* Check card insertion/removal interrupt occurs, only EMVSIM DIRECT interface driver using enables this interrupt
     * to occur */
    if (((base->PCSR & EMVSIM_PCSR_SPDIM_MASK) == 0u) && ((base->PCSR & EMVSIM_PCSR_SPDIF_MASK) != 0u))
    {
        /* Clear card presence interrupt status */
        base->PCSR |= EMVSIM_PCSR_SPDIF_MASK;
        /* Set PD signal edge behaviour */
        if (((emvsim_presence_detect_edge_t)(uint32_t)((base->PCSR & EMVSIM_PCSR_SPDES_MASK) >>
                                                       EMVSIM_PCSR_SPDES_SHIFT) == kEMVSIM_DetectOnFallingEdge) &&
            ((emvsim_presence_detect_status_t)(uint32_t)((base->PCSR & EMVSIM_PCSR_SPDP_MASK) >>
                                                         EMVSIM_PCSR_SPDP_SHIFT) == kEMVSIM_DetectPinIsLow))
        { /* Set rising edge interrupt */
            base->PCSR |= EMVSIM_PCSR_SPDES_MASK;
        }
        if (((emvsim_presence_detect_edge_t)(uint32_t)((base->PCSR & EMVSIM_PCSR_SPDES_MASK) >>
                                                       EMVSIM_PCSR_SPDES_SHIFT) == kEMVSIM_DetectOnRisingEdge) &&
            ((emvsim_presence_detect_status_t)(uint32_t)((base->PCSR & EMVSIM_PCSR_SPDP_MASK) >>
                                                         EMVSIM_PCSR_SPDP_SHIFT) == kEMVSIM_DetectPinIsHigh))
        { /* Set falling edge interrupt */
            base->PCSR &= ~EMVSIM_PCSR_SPDES_MASK;
        }
        /* Card presence(insertion)/removal detected */
        /* Invoke callback if there is one */
        if (NULL != context->interfaceCallback)
        {
            context->interfaceCallback(context, context->interfaceCallbackParam);
        }
        return;
    }
    /* Check if timer for initial character (TS) detection has expired */
    if (((base->INT_MASK & EMVSIM_INT_MASK_GPCNT0_IM_MASK) >> EMVSIM_INT_MASK_GPCNT0_IM_SHIFT == 0u) &&
        ((base->TX_STATUS & EMVSIM_TX_STATUS_GPCNT0_TO_MASK) != 0u))
    {
        /* Disable TS and ADT timers by clearing source clock to 0 */
        base->CLKCFG &= ~(EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK | EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK);
        context->timersState.initCharTimerExpired = true;
        /* Disable and clear GPCNT interrupt */
        base->INT_MASK |= EMVSIM_INT_MASK_GPCNT0_IM_MASK;
        base->TX_STATUS = EMVSIM_TX_STATUS_GPCNT0_TO_MASK;
        /* Down counter trigger, and clear any pending counter status flag */
        base->CTRL &= ~EMVSIM_CTRL_RCV_EN_MASK;
        base->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;
        context->transferState = kSMARTCARD_IdleState;
        /* Unblock the caller */
        smartcard_emvsim_CompleteReceiveData(base, context);
        return;
    }
    /* Check if timer for ATR duration timer has expired */
    if (((base->INT_MASK & EMVSIM_INT_MASK_GPCNT1_IM_MASK) == 0u) &&
        ((base->TX_STATUS & EMVSIM_TX_STATUS_GPCNT1_TO_MASK) != 0u))
    { /* Disable clock counter by clearing source clock to 0 */
        base->CLKCFG &= ~EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK;
        /* Disable and clear GPCNT interrupt */
        base->INT_MASK |= EMVSIM_INT_MASK_GPCNT1_IM_MASK;
        base->TX_STATUS                 = EMVSIM_TX_STATUS_GPCNT1_TO_MASK;
        context->timersState.adtExpired = true;
        /* Unblock the caller */
        smartcard_emvsim_CompleteReceiveData(base, context);
        return;
    }
    /*
     * Check if a parity error was indicated.
     * A parity error will cause transmission of NACK if ANACK bit is set in
     * CTRL register and PEF bit will not be asserted. When ANACK is not set,
     * PEF will be asserted.
     */
    if ((base->RX_STATUS & EMVSIM_RX_STATUS_PEF_MASK) != 0u)
    {
        context->parityError = true;
        /* Clear parity error indication */
        base->RX_STATUS = EMVSIM_RX_STATUS_PEF_MASK;
    }
    /* Check if transmit NACK generation threshold was reached */
    if ((base->TX_STATUS & EMVSIM_TX_STATUS_TNTE_MASK) != 0u)
    {
        context->txtCrossed = true;
        /* Disable transmit NACK threshold interrupt */
        base->INT_MASK |= EMVSIM_INT_MASK_TNACK_IM_MASK;
        /* Clear transmit NACK threshold error flag */
        base->TX_STATUS = EMVSIM_TX_STATUS_TNTE_MASK;
        /* Unblock the caller */
        smartcard_emvsim_CompleteSendData(base, context);
        return;
    }
    /* Check if receive NACK generation threshold was reached */
    if ((base->RX_STATUS & EMVSIM_RX_STATUS_RTE_MASK) != 0u)
    {
        context->rxtCrossed = true;
        /* Clear receiver NACK threshold interrupt status */
        base->RX_STATUS = EMVSIM_RX_STATUS_RTE_MASK;
        if (context->xIsBusy)
        { /* Unblock the caller */
            smartcard_emvsim_CompleteReceiveData(base, context);
        }
    }
    /* Check if a Character Wait Timer expired */
    if (((base->INT_MASK & EMVSIM_INT_MASK_CWT_ERR_IM_MASK) == 0u) &&
        ((base->RX_STATUS & EMVSIM_RX_STATUS_CWT_ERR_MASK) != 0u))
    { /* Disable Character Wait Timer interrupt */
        base->INT_MASK |= EMVSIM_INT_MASK_CWT_ERR_IM_MASK;
        /* Reset the counter */
        base->CTRL &= ~EMVSIM_CTRL_CWT_EN_MASK;
        /* Clear interrupt status */
        base->RX_STATUS = EMVSIM_RX_STATUS_CWT_ERR_MASK;
        /* Enable CWT timer */
        base->CTRL |= EMVSIM_CTRL_CWT_EN_MASK;
        context->transferState = kSMARTCARD_IdleState;

        if (kSMARTCARD_T0Transport == context->tType)
        { /* Indicate WWT expired */
            context->timersState.wwtExpired = true;
        }
        else
        { /* Indicate CWT expired */
            context->timersState.cwtExpired = true;
        }
        if (context->xIsBusy)
        { /* Terminate and unblock any caller */
            smartcard_emvsim_CompleteReceiveData(base, context);
        }
    }
    /* Check if a Block Wait Timer expired */
    if (((base->INT_MASK & EMVSIM_INT_MASK_BWT_ERR_IM_MASK) == 0u) &&
        ((base->RX_STATUS & EMVSIM_RX_STATUS_BWT_ERR_MASK) != 0u))
    { /* Disable Block Wait Timer interrupt */
        base->INT_MASK |= EMVSIM_INT_MASK_BWT_ERR_IM_MASK;
        /* Clear interrupt status flag */
        base->CTRL &= ~EMVSIM_CTRL_BWT_EN_MASK;
        /* Clear error */
        base->RX_STATUS = EMVSIM_RX_STATUS_BWT_ERR_MASK;
        /* Enable BWT timer */
        base->CTRL |= EMVSIM_CTRL_BWT_EN_MASK;

        if (kSMARTCARD_T0Transport == context->tType)
        { /* Indicate WWT expired */
            context->timersState.wwtExpired = true;
        }
        else
        { /* Indicate BWT expired */
            context->timersState.bwtExpired = true;
        }
        /* Check if Wait Time Extension(WTX) was requested */
        if (context->wtxRequested)
        { /* Reset WTX to default */
            (void)SMARTCARD_EMVSIM_Control(base, context, kSMARTCARD_ResetWaitTimeMultiplier, 1u);
        }
        if (context->xIsBusy)
        { /* Terminate and unblock any caller */
            smartcard_emvsim_CompleteReceiveData(base, context);
        }
    }

    /* RX_DATA IRQ */
    /* Used in T=1 after receive 1st byte - disable BWT and enable CWT interrupt */
    if (((base->INT_MASK & EMVSIM_INT_MASK_RX_DATA_IM_MASK) == 0u) &&
        ((base->RX_STATUS & EMVSIM_RX_STATUS_RX_DATA_MASK) != 0u))
    {
        if ((context->tType == kSMARTCARD_T1Transport) && (context->xSize > 0u) &&
            ((base->INT_MASK & EMVSIM_INT_MASK_BWT_ERR_IM_MASK) == 0u))
        {
            context->timersState.cwtExpired = false;
            /* Clear CWT error flag */
            base->RX_STATUS = EMVSIM_RX_STATUS_CWT_ERR_MASK;
            /* Enable CWT */
            base->CTRL |= EMVSIM_CTRL_CWT_EN_MASK;
            /* Only the 1st byte has been received, now time to disable BWT interrupt and enable CWT interrupt */
            base->INT_MASK = (base->INT_MASK & ~EMVSIM_INT_MASK_CWT_ERR_IM_MASK) | EMVSIM_INT_MASK_BWT_ERR_IM_MASK;
        }
        /* Disable interrupt when is received new byte */
        base->INT_MASK |= EMVSIM_INT_MASK_RX_DATA_IM_MASK;
    }

    /* RDT IRQ - count of bytes in rx fifo reached the rx threshold value RX_THD[RDT] */
    if (((base->INT_MASK & EMVSIM_INT_MASK_RDT_IM_MASK) == 0u) &&
        ((base->RX_STATUS & EMVSIM_RX_STATUS_RDTF_MASK) != 0u))
    {
        if (kSMARTCARD_WaitingForTSState == context->transferState)
        {
            /* Read byte */
            (void)(base->RX_BUF);

            if ((base->CTRL & EMVSIM_CTRL_ICM_MASK) != 0u)
            { /* ICM mode still enabled, this is due to parity error */
                context->transferState = kSMARTCARD_InvalidTSDetecetedState;
            }
            else
            { /* Received valid TS */
                context->transferState = kSMARTCARD_ReceivingState;
                /* Get Data Convention form by reading IC bit of EMVSIM_CTRL register */
                context->cardParams.convention =
                    (smartcard_card_convention_t)(uint32_t)((base->CTRL & EMVSIM_CTRL_IC_MASK) >> EMVSIM_CTRL_IC_SHIFT);
            }
            if (kSMARTCARD_InvalidTSDetecetedState == context->transferState)
            { /* Stop initial character (TS) detection timer, ADT timer and it's interrupt to occur */
                base->CLKCFG &= ~(EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK | EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK);
                base->INT_MASK |= EMVSIM_INT_MASK_GPCNT0_IM_MASK;
                smartcard_emvsim_CompleteReceiveData(base, context);
            }
            if (kSMARTCARD_ReceivingState == context->transferState)
            { /* Stop initial character (TS) detection timer and disable ATR duration timer to reset it */
                base->CLKCFG &= ~(EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK | EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK);
                /* Start ATR duration counter (restart GPCNT) */
                base->CLKCFG |= EMVSIM_CLKCFG_GPCNT1_CLK_SEL(kEMVSIM_GPCTxClock);
                /* Start ATR duration counter, Disable counter 0 interrupt and Enable counter 1 interrupt */
                base->INT_MASK = (base->INT_MASK & ~EMVSIM_INT_MASK_GPCNT1_IM_MASK) | EMVSIM_INT_MASK_GPCNT0_IM_MASK;
                /* Complete receive transfer */
                smartcard_emvsim_CompleteReceiveData(base, context);
            }
            /* Return anyway */
            return;
        }

        while (((base->RX_STATUS & EMVSIM_RX_STATUS_RX_CNT_MASK) != 0u) && ((context->xSize) > 0u))
        {
            /* Get data and put into receive buffer */
            *context->xBuff = (uint8_t)(base->RX_BUF);
            ++context->xBuff;
            --context->xSize;
        }

        /* Check if the last byte was received */
        if (context->xSize == 0u)
        {
            smartcard_emvsim_CompleteReceiveData(base, context);
        }
        else
        {
            /* If the count of remaining bytes to receive is less than depth of fifo, update the value of the receiver
             * data threshold */
            if (context->xSize < context->rxFifoThreshold)
            {
                /* Set receiver data threshold value to count of remaining bytes */
                uint32_t rx_thd;
                rx_thd = (base->RX_THD & ~EMVSIM_RX_THD_RDT_MASK);
                rx_thd |= context->xSize;
                base->RX_THD = rx_thd;
            }
        }
    }

    /* ETC IRQ - all data from fifo is transmitted */
    if (((base->INT_MASK & EMVSIM_INT_MASK_ETC_IM_MASK) == 0u) &&
        ((base->TX_STATUS & EMVSIM_TX_STATUS_ETCF_MASK) != 0u))
    {
        smartcard_emvsim_CompleteSendData(base, context);
    }

    /* TDT IRQ - tx fifo is empty */
    if (((base->INT_MASK & EMVSIM_INT_MASK_TDT_IM_MASK) == 0u) &&
        ((base->TX_STATUS & EMVSIM_TX_STATUS_TDTF_MASK) != 0u))
    {
        if (context->xSize == 0u)
        {
            smartcard_emvsim_CompleteSendData(base, context);
        }

        if (context->xSize == 1u)
        {
            /* Disable TDT interrupt */
            base->INT_MASK |= EMVSIM_INT_MASK_TDT_IM_MASK;
            /* When the TX_GETU is not zero while sending last byte, the transmitter sends one byte more */
            base->TX_GETU = 0;

            /* Write data to fifo */
            base->TX_BUF = *(context->xBuff);
            ++context->xBuff;
            --context->xSize;

            /* Last byte was written to fifo - wait for ETC interrupt */
            /* Clear ETC flag and enable ETC interrupt */
            base->TX_STATUS |= EMVSIM_TX_STATUS_ETCF_MASK;
            base->INT_MASK &= ~EMVSIM_INT_MASK_ETC_IM_MASK;
        }
        else
        {
            /* To fifo will be written 2 or more bytes */
            size_t getu_tail = (size_t)(base->TX_GETU > 0u);
            while (((context->txFifoEntryCount - (uint8_t)((base->TX_STATUS & EMVSIM_TX_STATUS_TX_CNT_MASK) >>
                                                           EMVSIM_TX_STATUS_TX_CNT_SHIFT)) > 0u) &&
                   (context->xSize > getu_tail))
            {
                /* Write data to fifo */
                base->TX_BUF = *(context->xBuff);
                ++context->xBuff;
                --context->xSize;
            }

            if (context->xSize == 0u)
            {
                /* Disable TDT interrupt */
                base->INT_MASK |= EMVSIM_INT_MASK_TDT_IM_MASK;

                /* Clear ETC flag and enable ETC interrupt */
                base->TX_STATUS |= EMVSIM_TX_STATUS_ETCF_MASK;
                base->INT_MASK &= ~EMVSIM_INT_MASK_ETC_IM_MASK;
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * brief Controls the EMVSIM module per different user request.
 *
 * param base The EMVSIM peripheral base address.
 * param context A pointer to a smart card driver context structure.
 * param control Control type.
 * param param Integer value of specific to control command.
 *
 * return kStatus_SMARTCARD_Success in success.
 * return kStatus_SMARTCARD_OtherError in case of error.
 */
status_t SMARTCARD_EMVSIM_Control(EMVSIM_Type *base,
                                  smartcard_context_t *context,
                                  smartcard_control_t control,
                                  uint32_t param)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    status_t status = kStatus_SMARTCARD_Success;
    uint32_t temp32 = 0u;

    switch (control)
    {
        case kSMARTCARD_EnableADT:
            /* Do nothing, ADT counter has been loaded and started after reset
             * and during starting TS delay counter only. This is because, once
             * TS counter has been triggered with RCV_EN down-up, we should not
             * trigger again after TS is received(to avoid missing next character to
             * TS. Rather, after TS is received, the ATR duration counter should just
             * be restarted w/o re-triggering the counter. */
            break;
        case kSMARTCARD_DisableADT:
            base->CTRL &= ~EMVSIM_CTRL_RCV_EN_MASK;
            /* Stop ADT specific counter and it's interrupt to occur */
            base->CLKCFG &= ~EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK;
            base->TX_STATUS = EMVSIM_TX_STATUS_GPCNT1_TO_MASK;
            base->INT_MASK |= EMVSIM_INT_MASK_GPCNT1_IM_MASK;
            break;
        case kSMARTCARD_EnableGTV:
            /* Enable GTV specific interrupt */
            base->INT_MASK &= ~EMVSIM_INT_MASK_BGT_ERR_IM_MASK;
            break;
        case kSMARTCARD_DisableGTV:
            /* Disable GTV specific interrupt */
            base->INT_MASK |= EMVSIM_INT_MASK_BGT_ERR_IM_MASK;
            break;
        case kSMARTCARD_ResetWWT:
            /* Reset WWT Timer */
            base->CTRL &= ~(EMVSIM_CTRL_CWT_EN_MASK | EMVSIM_CTRL_BWT_EN_MASK);
            base->CTRL |= (EMVSIM_CTRL_CWT_EN_MASK | EMVSIM_CTRL_BWT_EN_MASK);
            break;
        case kSMARTCARD_EnableWWT:
            /* BGT must be masked */
            base->INT_MASK |= EMVSIM_INT_MASK_BGT_ERR_IM_MASK;
            /* Enable WWT Timer interrupt to occur */
            base->INT_MASK &= (~EMVSIM_INT_MASK_CWT_ERR_IM_MASK & ~EMVSIM_INT_MASK_BWT_ERR_IM_MASK);
            break;
        case kSMARTCARD_DisableWWT:
            /* Disable WWT Timer interrupt to occur */
            base->INT_MASK |= (EMVSIM_INT_MASK_CWT_ERR_IM_MASK | EMVSIM_INT_MASK_BWT_ERR_IM_MASK);
            break;
        case kSMARTCARD_ResetCWT:
            /* Reset CWT Timer */
            base->CTRL &= ~EMVSIM_CTRL_CWT_EN_MASK;
            base->CTRL |= EMVSIM_CTRL_CWT_EN_MASK;
            break;
        case kSMARTCARD_EnableCWT:
            base->CTRL |= EMVSIM_CTRL_CWT_EN_MASK;
            /* Enable CWT Timer interrupt to occur */
            base->INT_MASK &= ~EMVSIM_INT_MASK_CWT_ERR_IM_MASK;
            break;
        case kSMARTCARD_DisableCWT:
            /* CWT counter is for receive mode only */
            base->CTRL &= ~EMVSIM_CTRL_CWT_EN_MASK;
            /* Disable CWT Timer interrupt to occur */
            base->INT_MASK |= EMVSIM_INT_MASK_CWT_ERR_IM_MASK;
            break;
        case kSMARTCARD_ResetBWT:
            /* Reset BWT Timer */
            base->CTRL &= ~EMVSIM_CTRL_BWT_EN_MASK;
            base->CTRL |= EMVSIM_CTRL_BWT_EN_MASK;
            break;
        case kSMARTCARD_EnableBWT:
            base->CTRL |= EMVSIM_CTRL_BWT_EN_MASK;
            /* Enable BWT Timer interrupt to occur */
            base->INT_MASK &= ~EMVSIM_INT_MASK_BWT_ERR_IM_MASK;
            break;
        case kSMARTCARD_DisableBWT:
            /* Disable BWT Timer interrupt to occur */
            base->INT_MASK |= EMVSIM_INT_MASK_BWT_ERR_IM_MASK;
            break;
        case kSMARTCARD_EnableInitDetect:
            /* Clear all ISO7816 interrupt flags */
            base->RX_STATUS = 0xFFFFFFFFu;
            /* Enable initial character detection : hardware method */
            context->transferState = kSMARTCARD_WaitingForTSState;
            /* Enable initial character detection */
            base->CTRL |= EMVSIM_CTRL_ICM_MASK;
            base->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;
            break;
        case kSMARTCARD_EnableAnack:
            /* Enable NACK-on-error interrupt to occur */
            base->CTRL |= EMVSIM_CTRL_ANACK_MASK;
            break;
        case kSMARTCARD_DisableAnack:
            /* Disable NACK-on-error interrupt to occur */
            base->CTRL &= ~EMVSIM_CTRL_ANACK_MASK;
            break;
        case kSMARTCARD_ConfigureBaudrate:
            /* Set default baudrate/ETU time based on EMV parameters and card clock */
            base->DIVISOR = (((uint32_t)context->cardParams.Fi / context->cardParams.currentD) & 0x1FFu);
            break;
        case kSMARTCARD_SetupATRMode:
            /* Set in default ATR mode */
            smartcard_emvsim_SetTransferType(base, context, kSMARTCARD_SetupATRMode);
            break;
        case kSMARTCARD_SetupT0Mode:
            /* Set transport protocol type to T=0 */
            smartcard_emvsim_SetTransferType(base, context, kSMARTCARD_SetupT0Mode);
            break;
        case kSMARTCARD_SetupT1Mode:
            /* Set transport protocol type to T=1 */
            smartcard_emvsim_SetTransferType(base, context, kSMARTCARD_SetupT1Mode);
            break;
        case kSMARTCARD_EnableReceiverMode:
            /* Enable receiver mode and switch to receive direction */
            base->CTRL |= EMVSIM_CTRL_RCV_EN_MASK;
            /* Set receiver threshold value to 1 */
            base->RX_THD = ((base->RX_THD & ~EMVSIM_RX_THD_RDT_MASK) | 1u);
            /* Enable RDT interrupt */
            base->INT_MASK &= ~EMVSIM_INT_MASK_RDT_IM_MASK;
            break;
        case kSMARTCARD_DisableReceiverMode:
            /* Disable receiver */
            base->CTRL &= ~EMVSIM_CTRL_RCV_EN_MASK;
            break;
        case kSMARTCARD_EnableTransmitterMode:
            /* Enable transmitter mode and switch to transmit direction */
            base->CTRL |= EMVSIM_CTRL_XMT_EN_MASK;
            break;
        case kSMARTCARD_DisableTransmitterMode:
            /* Disable transmitter */
            base->CTRL &= ~EMVSIM_CTRL_XMT_EN_MASK;
            break;
        case kSMARTCARD_ResetWaitTimeMultiplier:
            base->CTRL &= ~EMVSIM_CTRL_BWT_EN_MASK;
            /* Reset Wait Timer Multiplier
             * EMV Formula : WTX x (11 + ((2^BWI + 1) x 960 x D)) */
            temp32 = ((uint8_t)param) *
                     (11u + ((((uint32_t)1u << context->cardParams.BWI) + 1u) * 960u * context->cardParams.currentD));
#ifdef CARDSIM_EXTRADELAY_USED
            temp32 += context->cardParams.currentD * 50;
#endif
            base->BWT_VAL = temp32;
            /* Set flag to SMARTCARD context accordingly */
            if (param > 1u)
            {
                context->wtxRequested = true;
            }
            else
            {
                context->wtxRequested = false;
            }
            base->CTRL |= EMVSIM_CTRL_BWT_EN_MASK;
            break;
        default:
            status = kStatus_SMARTCARD_InvalidInput;
            break;
    }
    return status;
}
