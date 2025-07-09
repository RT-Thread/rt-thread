/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_smartcard_uart.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.smartcard_uart"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of UART peripheral base address. */
static UART_Type *const s_uartBases[] = UART_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of UART clock name. */
static const clock_ip_name_t s_uartClock[] = UART_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void smartcard_uart_CompleteSendData(UART_Type *base, smartcard_context_t *context);
static void smartcard_uart_StartSendData(UART_Type *base, smartcard_context_t *context);
static void smartcard_uart_CompleteReceiveData(UART_Type *base, smartcard_context_t *context);
static void smartcard_uart_StartReceiveData(UART_Type *base, smartcard_context_t *context);
static void smartcard_uart_SetTransferType(UART_Type *base, smartcard_context_t *context, smartcard_control_t control);
static void smartcard_uart_TimerInit(uint8_t channel);
static void smartcard_uart_TimerStop(uint8_t channel);
static uint32_t smartcard_uart_GetInstance(UART_Type *base);
static status_t smartcard_uart_ConfigureBaudrate(UART_Type *base, smartcard_context_t *context);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Get the UART instance from peripheral base address.
 *
 * @param base UART peripheral base address.
 * @return UART instance.
 */
static uint32_t smartcard_uart_GetInstance(UART_Type *base)
{
    uint32_t instance;
    uint32_t uartArrayCount = (sizeof(s_uartBases) / sizeof(s_uartBases[0]));
    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < uartArrayCount; instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_uartBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < uartArrayCount);

    return instance;
}

/*!
 * @brief Finish up a transmit by completing the process of sending data and disabling the interrupt.
 *
 * @param base The UART peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_uart_CompleteSendData(UART_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Disable TCIE and TI interrupt */
    base->C2 &= ~(UART_C2_TCIE_MASK | UART_C2_TIE_MASK);

    /* Switch to receive mode after transmission is complete */
    base->C3 &= ~UART_C3_TXDIR_MASK;
    /* disable transmitter after transmit */
    base->C2 &= ~UART_C2_TE_MASK;
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
 * @param base The UART peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_uart_CompleteReceiveData(UART_Type *base, smartcard_context_t *context)
{
    assert(NULL != context);

    /* Disable receive data full interrupt */
    base->C2 &= ~UART_C2_RIE_MASK;

    /* Read data from fifo */
    while ((base->RCFIFO) && (context->xSize))
    {
        /* Get data and put into receive buffer */
        *context->xBuff = (uint8_t)(base->D);
        ++context->xBuff;
        --context->xSize;
    }

    if (context->tType == kSMARTCARD_T1Transport)
    {
        base->C2 &= ~UART_C2_RE_MASK;
    }
    /* Update the information of the module driver context */
    context->xIsBusy       = false;
    context->transferState = kSMARTCARD_IdleState;
    /* Invoke user call-back */
    if (NULL != context->transferCallback)
    {
        context->transferCallback(context, context->transferCallbackParam);
    }
}

/*!
 * @brief Initiate (start) a transmit by beginning the process of sending data and enabling the interrupt.
 *
 * @param base The UART peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_uart_StartSendData(UART_Type *base, smartcard_context_t *context)
{
    assert(NULL != context);

    context->transferState = kSMARTCARD_TransmittingState;
    /* Disable transmitter */
    base->C2 &= ~(UART_C2_TE_MASK);
    /* Check if current transport protocol is T=1 */
    if (context->tType == kSMARTCARD_T1Transport)
    { /* Reset CWT timer at the beginning of transmission only */
        context->timersState.cwtExpired = false;
        /* clear any pending Character WT interrupt flag */
        base->IS7816 |= UART_IS7816_CWT_MASK;
        /* The TLEN does not count the NAD, PCB, LEN, LRC */
        base->TL7816 = context->xSize - 4u;
    }
    context->xIsBusy = true;
    /* Set the TX pin as output */
    base->C3 |= UART_C3_TXDIR_MASK;
    /* Flush tx fifo */
    base->CFIFO |= 0x80;
    /* Enable transmitter */
    base->C2 |= (UART_C2_TE_MASK);

    /* Enable TIE interrupt */
    base->C2 |= UART_C2_TIE_MASK;
}

/*!
 * @brief Initiate (start) a receive by beginning the process of receiving data and enabling the interrupt.
 *
 * @param base The UART peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_uart_StartReceiveData(UART_Type *base, smartcard_context_t *context)
{
    assert((NULL != context));

    /* Initialize the module driver context structure to indicate transfer in progress */
    context->xIsBusy = true;
    /* Disable transmitter */
    base->C2 &= ~UART_C2_TE_MASK;

    /* Set the rx threshold - RWFIFO[RXWATER] */
    if ((context->tType == kSMARTCARD_T1Transport) && (base->IE7816 & UART_IE7816_BWTE_MASK))
    {
        /* After receiving one byte is necessary to disable BWT interrupt and enable CWT interrupt */
        base->RWFIFO = 1;
    }
    else
    {
        if (context->xSize < context->rxFifoThreshold)
        {
            base->RWFIFO = context->xSize;
        }
        else
        {
            base->RWFIFO = context->rxFifoThreshold;
        }
    }
    /* Flush rx fifo */
    base->CFIFO |= 0x40;

    /* Enable receiver and switch to receive direction */
    base->C2 |= UART_C2_RE_MASK;
    base->C3 &= ~UART_C3_TXDIR_MASK;
    /* Disable GTV flag for data receiving */
    base->IE7816 &= ~UART_IE7816_GTVE_MASK;
    /* Enable RIE interrupt */
    base->C2 |= UART_C2_RIE_MASK;
}

/*!
 * @brief Sets up the UART hardware for T=0 or T=1 protocol data exchange and initialize timer values.
 *
 * @param base The UART peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 */
static void smartcard_uart_SetTransferType(UART_Type *base, smartcard_context_t *context, smartcard_control_t control)
{
    assert((NULL != context));
    assert((control == kSMARTCARD_SetupATRMode) || (control == kSMARTCARD_SetupT0Mode) ||
           (control == kSMARTCARD_SetupT1Mode));

#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
    uint16_t temp16;
    uint16_t bwiVal = 0u;
#endif
    uint8_t temp8;

    if (control == kSMARTCARD_SetupATRMode)
    { /* Set default values as per EMV specification */
        context->cardParams.Fi       = 372u;
        context->cardParams.currentD = 1u;
        context->cardParams.WI       = 0x0Au;
        /* Configure UART baud rate */
        smartcard_uart_ConfigureBaudrate(base, context);
        base->C2 &= ~UART_C2_RE_MASK;
        base->IS7816 = 0xFF;
        base->CFIFO |= 0xC0;
        (void)base->C3;
        (void)base->D;

        /* Disable ISO7816 mode 1st and Set transport protocol type to T=0 */
        base->C7816 = 0u;
/* Calculate and set Work Wait Timer (WWT) */
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480) = 480xD x (2xWI + 1)
         * UART formula: WI x 480 */
        temp16                 = context->cardParams.currentD * ((2u * context->cardParams.WI) + 1u);
        base->TYPE0.WP7816A_T0 = (uint8_t)(temp16 >> 8u);
        base->TYPE0.WP7816B_T0 = (uint8_t)(temp16);
#else
        base->WP7816T0 = context->cardParams.WI;
#endif
        /* Set Extended Guard Timer value
         * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN = GTN equal to 255 -> 12
         * UART formula: same as above */
        if ((context->cardParams.GTN <= SMARTCARD_EMV_RX_TO_TX_GUARD_TIME_T0))
        {
            temp8 = SMARTCARD_EMV_RX_TO_TX_GUARD_TIME_T0;
        }
        else
        { /* All other values include default 0xFF */
            temp8 = context->cardParams.GTN;
        }
        temp8++;
        base->WN7816 = temp8;
        /* Set FD multiplier */
        base->WF7816 = context->cardParams.currentD;
        /* Setup for single wire ISO7816 mode */
        base->C1 |= (UART_C1_LOOPS_MASK | UART_C1_RSRC_MASK | UART_C1_M_MASK);
        /* Normally, parity mode should be set to kUartParityEven,
         * but in case can be set to kUartParityOdd to help in initial character
         * (TS) detection by SW(by switching off hardware feature) */
        if (context->parity == kSMARTCARD_OddParity)
        {
            base->C1 |= (UART_C1_PT_MASK | UART_C1_PE_MASK);
        }
        else
        {
            base->C1 = (base->C1 & ~UART_C1_PT_MASK) | UART_C1_PE_MASK;
        }
        /* Setting RX threshold to 0 so that an interrupt is generated when a NACK is
         * sent either due to parity error or wrong INIT char.
         * Setting up TX NACK threshold */
        base->ET7816 = (SMARTCARD_EMV_TX_NACK_THRESHOLD << UART_ET7816_TXTHRESHOLD_SHIFT);
        /* Enable Interrupt for RXT crossing */
        base->IE7816 |= UART_IE7816_RXTE_MASK;
        /* Enable parity error indication */
        base->C3 |= UART_C3_PEIE_MASK;
        /* Disable ANACK generation and Enable ISO7816 mode */
        base->C7816 = (base->C7816 & ~UART_C7816_ANACK_MASK) | UART_C7816_ISO_7816E_MASK;
        /* Set transport type to T=0 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T0Transport;
    }
    else if (control == kSMARTCARD_SetupT0Mode)
    {
        base->IS7816 = 0xFF;
        base->C2 &= ~UART_C2_RE_MASK;
        /* Disable ISO7816 mode 1st and Set transport protocol type to T=0 */
        base->C7816 &= ~(UART_C7816_ISO_7816E_MASK | UART_C7816_TTYPE_MASK);
/* Calculate and set Work Wait Timer (WWT) */
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480) = 480xD x (2xWI + 1)
         * UART formula: WI x 480 */
        temp16                 = context->cardParams.currentD * ((2u * context->cardParams.WI) + 1u);
        base->TYPE0.WP7816A_T0 = (uint8_t)(temp16 >> 8u);
        base->TYPE0.WP7816B_T0 = (uint8_t)(temp16);
#else
        base->WP7816T0 = (uint8_t)context->cardParams.WI;
#endif
        /* Set Extended Guard Timer value
         * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN = GTN equal to 255 -> 12
         * UART formula: same as above */
        if (context->cardParams.GTN < 0xFB)
        {
            temp8 = context->cardParams.GTN + 4u;
        }
        else
        {
            temp8 = context->cardParams.GTN;
        }
        if (temp8 == 255)
        {
            temp8--;
        }
        base->WN7816 = temp8;
        /* Set FD multiplier */
        base->WF7816 = (uint8_t)context->cardParams.currentD;
        /* Setup for single wire ISO7816 mode, 9 bits per char */
        base->C1 |= UART_C1_LOOPS_MASK | UART_C1_RSRC_MASK | UART_C1_M_MASK;
        /* Normally, parity mode should be set to kUartParityEven,
         * but in case can be set to kUartParityOdd to help in initial character
         * (TS) detection by SW(by switching off hardware feature) */
        if (context->parity == kSMARTCARD_OddParity)
        {
            base->C1 |= UART_C1_PT_MASK | UART_C1_PE_MASK;
        }
        else
        {
            base->C1 = (base->C1 & ~UART_C1_PT_MASK) | UART_C1_PE_MASK;
        }
        /* Setting RX threshold so that an interrupt is generated when a NACK is
         * sent either due to parity error or wrong INIT char
         * Setting up TX NACK threshold */
        base->ET7816 = ((SMARTCARD_EMV_RX_NACK_THRESHOLD << UART_ET7816_RXTHRESHOLD_SHIFT) |
                        (SMARTCARD_EMV_TX_NACK_THRESHOLD << UART_ET7816_TXTHRESHOLD_SHIFT));
        /* Enable Interrupt for RXT crossing */
        base->IE7816 |= UART_IE7816_RXTE_MASK;
        base->IE7816 |= UART_IE7816_TXTE_MASK;
        /* Disable parity error interrupt */
        base->C3 &= ~UART_C3_PEIE_MASK;
        /* Enable ISO7816 mode and Enable NACK on error interrupt */
        base->C7816 |= (UART_C7816_ISO_7816E_MASK | UART_C7816_ANACK_MASK);
        /* re-enable Receiver */
        base->C2 |= UART_C2_RE_MASK;
        /* Set transport type to T=0 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T0Transport;
    }
    else
    { /* Disable ISO7816 mode 1st */
        base->C7816 = 0u;
/* Calculate and set Block Wait Timer (BWT) value */
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
        /* EMV expectation: BWT = 11 + (2^BWI x 960 x D) + (D x 960) = 11 + (2^BWI + 1) x 960 x D
         * UART formula: BWT = (11 + (BWI x 960 x GTFD)) * (WTX + 1) */
        bwiVal                 = (1 << context->cardParams.BWI) + 1u;
        base->TYPE1.WP7816A_T1 = (uint8_t)(bwiVal >> 8u);
        base->TYPE1.WP7816B_T1 = (uint8_t)(bwiVal);
#else
        base->WP7816T1 = context->cardParams.BWI;
#endif
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
        /* Set Wait Timer Multiplier default value */
        base->WP7816 = 0u;
#endif
/* Calculate and set Character Wait Timer (BWT) value */
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
        /* EMV expectation: CWT = ((2^CWI + 11) + 4)
         * UART formula: CWT = 2^CWI1 + CWI2
         * EMV expectation: BGT = 22
         * UART formula: BWT = 16 + BGI */
        /* Set CW2 */
        if (context->cardParams.currentD == 1)
        {
            base->WP7816C_T1 = 15;
        }
        else
        {
            base->WP7816C_T1 = 15 + 1;
        }
        /* Set CW1 and Block Guard Time Integer */
        base->WGP7816_T1 = (uint8_t)((context->cardParams.CWI) << UART_WGP7816_T1_CWI1_SHIFT) |
                           (uint8_t)(context->cardParams.BGI & 0x0Fu);
#else
        base->WP7816T1 = (uint8_t)(base->WP7816T1 & ~UART_WP7816T1_CWI_MASK) |
                         (uint8_t)(context->cardParams.CWI << UART_WP7816T1_CWI_SHIFT);
#endif
        /* Set Extended Guard Timer value
         * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN = GTN equal to 255 -> 11
         * UART formula: same as above */
        if (context->cardParams.GTN < 0xFE)
        {
            temp8 = context->cardParams.GTN + 1u;
        }
        else
        {
            temp8 = context->cardParams.GTN;
        }
        base->WN7816 = temp8;

        /* Set FD multiplier */
        base->WF7816 = context->cardParams.currentD;
        /* Setup for single wire ISO7816 mode, 9 bits per char */
        base->C1 |= UART_C1_LOOPS_MASK | UART_C1_RSRC_MASK | UART_C1_M_MASK;
        /* Set parity mode */
        if (context->parity == kSMARTCARD_OddParity)
        {
            base->C1 |= UART_C1_PT_MASK | UART_C1_PE_MASK;
        }
        else
        { /* Even parity */
            base->C1 = (base->C1 & ~UART_C1_PT_MASK) | UART_C1_PE_MASK;
        }
        /* Clear all ISO interrupt modes, and enable only GTV interrupt by default */
        base->IE7816 = UART_IE7816_GTVE_MASK;
        /* Enable ISO7816 mode and set transport protocol type to T=1*/
        base->C7816 |= (UART_C7816_ISO_7816E_MASK | UART_C7816_TTYPE_MASK);
        /* Set transport type to T=1 in SMARTCARD context structure */
        context->tType = kSMARTCARD_T1Transport;
    }
}

#if defined(FSL_FEATURE_SOC_PIT_COUNT) && (FSL_FEATURE_SOC_PIT_COUNT)
/*!
 * @brief Function un-gates peripheral clock of PIT0.
 */
static void smartcard_uart_TimerInit(uint8_t channel)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate the PIT timer clock*/
    CLOCK_EnableClock(kCLOCK_Pit0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* enable timers clock */
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    /* Set timer period to zero */
    PIT->CHANNEL[channel].LDVAL = 0u;
    /* Stop timer and disable interrupt if it's not */
    PIT->CHANNEL[channel].TCTRL = 0u;
    /* Enable timer interrupt to occur */
    NVIC_EnableIRQ(PIT0_IRQn);
}

/*!
 * @brief Function gates peripheral clock of PIT0.
 */
static void smartcard_uart_TimerDeinit(void)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the PIT timer clock*/
    CLOCK_DisableClock(kCLOCK_Pit0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Disable pit IRQ interrupt to occur */
    NVIC_DisableIRQ(PIT0_IRQn);
}

/*!
 * brief Initializes timer specific channel with input period, enable channel interrupt and start counter.
 *
 * param channel The timer channel.
 * param time The time period.
 */
void smartcard_uart_TimerStart(uint8_t channel, uint32_t time)
{
    /* Set timer period */
    PIT->CHANNEL[channel].LDVAL = time;
    /* Clear timer interrupt flag */
    PIT->CHANNEL[channel].TFLG = 1u;
    /* Enable timer channel interrupt and timer */
    PIT->CHANNEL[channel].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
}

/*!
 * @brief Stop timer specific channel, disable channel interrupts and stops counter.
 */
static void smartcard_uart_TimerStop(uint8_t channel)
{
    /* Stop timer if it's not and disable timer channel interrupt*/
    PIT->CHANNEL[channel].TCTRL &= ~(PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK);
}
#endif /* FSL_FEATURE_SOC_PIT_COUNT */

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
void SMARTCARD_UART_GetDefaultConfig(smartcard_card_params_t *cardParams)
{
    /* Initializes the configure structure to zero. */
    memset(cardParams, 0, sizeof(*cardParams));

    /* EMV default values */
    cardParams->Fi       = 372u;
    cardParams->Di       = 1u;
    cardParams->currentD = 1u;
    cardParams->WI       = 0x0Au;
    cardParams->GTN      = 0x00u;
}

/*!
 * brief Initializes a UART peripheral for the Smart card/ISO-7816 operation.
 *
 * This function un-gates the UART clock, initializes the module to EMV default settings,
 * configures the IRQ, enables the module-level interrupt to the core, and initializes the driver context.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a smart card driver context structure.
 * param srcClock_Hz Smart card clock generation module source clock.
 *
 * return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_UART_Init(UART_Type *base, smartcard_context_t *context, uint32_t srcClock_Hz)
{
    assert((NULL != base));

    if ((NULL == context) || (srcClock_Hz == 0u))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    IRQn_Type uart_irqs[]      = UART_RX_TX_IRQS;
    IRQn_Type uartError_irqs[] = UART_ERR_IRQS;
    uint32_t instance          = 0u;

    context->base = base;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable peripheral clock */
    CLOCK_EnableClock(s_uartClock[smartcard_uart_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Initialize UART to a known context. */
    base->BDH = 0u;
    base->BDL = 0u;
    base->C1  = 0u;
    base->C2  = 0u;
    base->S2  = 0u;
    base->C3  = 0u;
#if defined(FSL_FEATURE_UART_HAS_ADDRESS_MATCHING) && (FSL_FEATURE_UART_HAS_ADDRESS_MATCHING)
    base->MA1 = 0u;
    base->MA2 = 0u;
#endif
    base->C4 = 0u;
#if defined(FSL_FEATURE_UART_HAS_DMA_ENABLE) && (FSL_FEATURE_UART_HAS_DMA_ENABLE)
    base->C5 = 0u;
#endif
#if defined(FSL_FEATURE_UART_HAS_MODEM_SUPPORT) && (FSL_FEATURE_UART_HAS_MODEM_SUPPORT)
    base->MODEM = 0u;
#endif
#if defined(FSL_FEATURE_UART_HAS_IR_SUPPORT) && (FSL_FEATURE_UART_HAS_IR_SUPPORT)
    base->IR = 0u;
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && (FSL_FEATURE_UART_HAS_FIFO)
    base->PFIFO  = 0u;
    base->CFIFO  = 0u;
    base->SFIFO  = 0xC0u;
    base->TWFIFO = 0u;
    base->RWFIFO = 1u;
#endif
    /* Initialize UART module for SMARTCARD mode of default operation */
    smartcard_uart_SetTransferType(base, context, kSMARTCARD_SetupATRMode);
#if defined(FSL_FEATURE_UART_HAS_FIFO) && (FSL_FEATURE_UART_HAS_FIFO)
    /* Flush fifo contents */
    base->CFIFO |= ((1u << UART_CFIFO_TXFLUSH_SHIFT) | (1u << UART_CFIFO_RXFLUSH_SHIFT));
#endif
    /* Compute size of tx fifo */
    context->txFifoEntryCount = 1u;
    if (base->PFIFO & UART_PFIFO_TXFIFOSIZE_MASK)
    {
        context->txFifoEntryCount =
            (1 << (((base->PFIFO & UART_PFIFO_TXFIFOSIZE_MASK) >> UART_PFIFO_TXFIFOSIZE_SHIFT) + 1));
        /* Enable tx fifo */
        base->PFIFO |= UART_PFIFO_TXFE_MASK;
    }

    /* Compute max value of rx fifo threshold (RXWATER) */
    context->rxFifoThreshold = 1u;
    if (base->PFIFO & UART_PFIFO_RXFIFOSIZE_MASK)
    {
        /* Size of rx fifo */
        context->rxFifoThreshold =
            (1 << (((base->PFIFO & UART_PFIFO_RXFIFOSIZE_MASK) >> UART_PFIFO_RXFIFOSIZE_SHIFT) + 1));
        /* The value of RXWATER must be set to less than the rx fifo buffer size */
        context->rxFifoThreshold--;
        /* Enable rx fifo */
        base->PFIFO |= UART_PFIFO_RXFE_MASK;
    }
#if defined(FSL_FEATURE_PIT_TIMER_COUNT) && (FSL_FEATURE_PIT_TIMER_COUNT)
    /* Initialize HW timer for the initial character (TS) delay measurement */
    smartcard_uart_TimerInit(context->interfaceConfig.tsTimerId);
#endif
    /* Enable UART interrupt on NVIC level. */
    instance = smartcard_uart_GetInstance(base);
    NVIC_EnableIRQ(uart_irqs[instance]);
    NVIC_EnableIRQ(uartError_irqs[instance]);
    /* Finally, disable the UART receiver and transmitter */
    base->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief This function disables the UART interrupts, disables the transmitter and receiver, and
 * flushes the FIFOs (for modules that support FIFOs) and gates UART clock in SIM.
 *
 * param base The UART peripheral base address.
 */
void SMARTCARD_UART_Deinit(UART_Type *base)
{
    assert(NULL != base);

    uint32_t instance          = 0u;
    IRQn_Type uart_irqs[]      = UART_RX_TX_IRQS;
    IRQn_Type uartError_irqs[] = UART_ERR_IRQS;
    /* In case there is still data in the TX FIFO or shift register that is
     * being transmitted wait till transmit is complete.
     * Wait until the data is completely shifted out of shift register */
    while (0u == ((base->S1 & UART_S1_TC_MASK) >> UART_S1_TC_SHIFT))
    {
    }

    base->C2 &= ~UART_C2_TIE_MASK;
#if defined(FSL_FEATURE_UART_IS_SCI) && (FSL_FEATURE_UART_IS_SCI)
    base->C4 &= ~UART_C4_TDMAS_MASK;
#else
    base->C5 &= ~UART_C5_TDMAS_MASK;
#endif
    base->C2 &= ~UART_C2_RIE_MASK;
#if defined(FSL_FEATURE_UART_IS_SCI) && (FSL_FEATURE_UART_IS_SCI)
    base->C4 &= ~UART_C4_RDMAS_MASK;
#else
    base->C5 &= ~UART_C5_RDMAS_MASK;
#endif
    /* Disable TX and RX */
    base->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK);
#if defined(FSL_FEATURE_UART_HAS_FIFO) && (FSL_FEATURE_UART_HAS_FIFO)
    /* Flush FIFO contents */
    base->CFIFO |= ((1u << UART_CFIFO_TXFLUSH_SHIFT) | (1u << UART_CFIFO_RXFLUSH_SHIFT));
#endif
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable UART module clock */
    CLOCK_DisableClock(s_uartClock[smartcard_uart_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Disable the interrupt */
    instance = smartcard_uart_GetInstance(base);
    NVIC_DisableIRQ(uart_irqs[instance]);
    NVIC_DisableIRQ(uartError_irqs[instance]);
/* De-initialize also external PIT timer */
#if defined(FSL_FEATURE_PIT_TIMER_COUNT) && (FSL_FEATURE_PIT_TIMER_COUNT)
    smartcard_uart_TimerDeinit();
#endif
}

/*!
 * brief Returns whether the previous UART transfer has finished.
 *
 * When performing an async transfer, call this function to ascertain the context of the
 * current transfer: in progress (or busy) or complete (success). If the
 * transfer is still in progress, the user can obtain the number of words that have not been transferred
 * by reading xSize of smart card context structure.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 *
 * return The number of bytes not transferred.
 */
int32_t SMARTCARD_UART_GetTransferRemainingBytes(UART_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return -1;
    }

    if (context->xIsBusy)
    {
        if (context->direction == kSMARTCARD_Transmit)
        {
            /* Count of bytes in buffer + data in fifo + one now transmitted byte */
            return (context->xSize + base->TCFIFO + 1);
        }
        return context->xSize;
    }

    return 0;
}

/*!
 * brief Terminates an asynchronous UART transfer early.
 *
 * During an async UART transfer, the user can terminate the transfer early
 * if the transfer is still in progress.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 *
 * retval kStatus_SMARTCARD_Success The transfer abort was successful.
 * retval kStatus_SMARTCARD_NoTransmitInProgress No transmission is currently in progress.
 */
status_t SMARTCARD_UART_AbortTransfer(UART_Type *base, smartcard_context_t *context)
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
        smartcard_uart_CompleteReceiveData(base, context);
    }
    else if (kSMARTCARD_Transmit == context->direction)
    { /* Stop the running transfer. */
        smartcard_uart_CompleteSendData(base, context);
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Transfers data using interrupts.
 *
 * A non-blocking (also known as asynchronous) function means that the function returns
 * immediately after initiating the transfer function. The application has to get the
 * transfer status to see when the transfer is complete. In other words, after calling non-blocking
 * (asynchronous) transfer function, the application must get the transfer status to check if transmit
 * is completed or not.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 * param xfer A pointer to Smart card transfer structure where the linked buffers and sizes are stored.
 *
 * return An error code or kStatus_SMARTCARD_Success.
 */
status_t SMARTCARD_UART_TransferNonBlocking(UART_Type *base, smartcard_context_t *context, smartcard_xfer_t *xfer)
{
    if ((NULL == context) || (NULL == xfer) || (NULL == xfer->buff))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    /* Check input parameters */
    if ((0u == xfer->size))
    {
        return kStatus_SMARTCARD_Success;
    }
    /* Check if some transfer is in progress */
    if (0u != SMARTCARD_UART_GetTransferRemainingBytes(base, context))
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
        smartcard_uart_StartReceiveData(base, context);
    }
    else if (kSMARTCARD_Transmit == xfer->direction)
    {
        context->direction     = xfer->direction;
        context->transferState = kSMARTCARD_TransmittingState;
        /* Start transfer */
        smartcard_uart_StartSendData(base, context);
    }
    else
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Error interrupt handler for UART.
 *
 * This function handles error conditions during a transfer.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 */
void SMARTCARD_UART_ErrIRQHandler(UART_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return;
    }

    /* Check if a parity error occurred */
    if (base->S1 & UART_S1_PF_MASK)
    {
        if (kSMARTCARD_WaitingForTSState == context->transferState)
        {
            /* A parity error detected during initial character (TS) detection phase */
            context->transferState = kSMARTCARD_InvalidTSDetecetedState;
            /* Un-block any caller waiting for initial character detection */
            if ((context->xIsBusy) && (context->direction == kSMARTCARD_Receive))
            {
                smartcard_uart_CompleteReceiveData(base, context);
            }
        }
        else
        { /* Parity error detected after initial character detection phase */
            context->parityError = true;
            if (context->tType == kSMARTCARD_T0Transport)
            {
                smartcard_uart_CompleteReceiveData(base, context);
            }
        }
    }
    /* Check if Transmission threshold value was exceeded */
    if (base->IS7816 & UART_IS7816_TXT_MASK)
    { /* Disable transmitter */
        base->C2 &= ~UART_C2_TE_MASK;
        /* Clear Transmission threshold interrupt flag */
        base->IS7816 = UART_IS7816_TXT_MASK;
        /* Enable transmitter */
        base->C2 |= UART_C2_TE_MASK;
        context->txtCrossed = true;
        /* Disable the transmitter interrupt */
        base->C2 &= ~UART_C2_TIE_MASK;
        /* Flush tx fifo */
        base->CFIFO |= 0x80;
        /* Un-block the caller */
        smartcard_uart_CompleteSendData(base, context);
    }
    /* Check if Receiver threshold value was exceeded */
    if (base->IS7816 & UART_IS7816_RXT_MASK)
    {
        /* Clear Receiver threshold interrupt flag */
        base->IS7816 = UART_IS7816_RXT_MASK;
        /* Check if Receiver threshold was exceeded during initial character detection */
        if (kSMARTCARD_WaitingForTSState == context->transferState)
        {
            context->transferState = kSMARTCARD_InvalidTSDetecetedState;
            if ((context->xIsBusy) && (context->direction == kSMARTCARD_Receive))
            {
                smartcard_uart_CompleteReceiveData(base, context);
            }
        }
        else
        { /* Receiver threshold exceeded during normal transfer, set flags */
            context->rxtCrossed = true;
            smartcard_uart_CompleteReceiveData(base, context);
        }
    }
    /* Check if a Guard Timer rule was violated */
    if (base->IS7816 & UART_IS7816_GTV_MASK)
    { /* Clear respective interrupt status flag */
        base->IS7816 = UART_IS7816_GTV_MASK;
    }
    /* Check if a Work Wait Timer expired */
    if (base->IS7816 & UART_IS7816_WT_MASK)
    { /* Reset WWT timer */
        SMARTCARD_UART_Control(base, context, kSMARTCARD_ResetWWT, 0);
        /* Indicate WWT expired */
        context->timersState.wwtExpired = true;

        if (context->xIsBusy)
        {
            if (kSMARTCARD_Receive == context->direction)
            { /* Terminate and un-block any caller */
                smartcard_uart_CompleteReceiveData(base, context);
            }
            else
            { /* Terminate and un-block any caller */
                smartcard_uart_CompleteSendData(base, context);
            }
        }
    }
    /* Check if a Character Wait Timer expired */
    if (base->IS7816 & UART_IS7816_CWT_MASK)
    { /* Disable Character Wait Timer interrupt */
        base->IE7816 &= ~UART_IE7816_CWTE_MASK;
        /* Reset CWT timer otherwise this interrupt keeps coming */
        SMARTCARD_UART_Control(base, context, kSMARTCARD_ResetCWT, 0);
        /* Change transfer context to Idle */
        context->transferState = kSMARTCARD_IdleState;
        /* Indicate CWT expired */
        context->timersState.cwtExpired = true;

        if (context->xIsBusy)
        {
            if (kSMARTCARD_Receive == context->direction)
            { /* Terminate and un-block any caller */
                smartcard_uart_CompleteReceiveData(base, context);
            }
            else
            { /* Terminate and un-block any caller */
                smartcard_uart_CompleteSendData(base, context);
            }
        }
    }
    /* Check if a Block Wait Timer expired */
    if (base->IS7816 & UART_IS7816_BWT_MASK)
    { /* Disable Block Wait Timer interrupt */
        base->IE7816 &= ~UART_IE7816_BWTE_MASK;
        /* Reset BWT timer */
        SMARTCARD_UART_Control(base, context, kSMARTCARD_ResetBWT, 0);
        /* Indicate BWT expired */
        context->timersState.bwtExpired = true;
        /* Check if Wait Time Extension was requested */
        if (context->wtxRequested)
        {
            SMARTCARD_UART_Control(base, context, kSMARTCARD_ResetWaitTimeMultiplier, 0);
        }
        if (context->xIsBusy)
        {
            if (kSMARTCARD_Receive == context->direction)
            { /* Terminate and un-block any caller */
                smartcard_uart_CompleteReceiveData(base, context);
            }
            else
            { /* Terminate and un-block any caller */
                smartcard_uart_CompleteSendData(base, context);
            }
        }
    }
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
    /* Check if a ATR duration timer Wait Timer expired */
    if (base->IS7816 & UART_IS7816_ADT_MASK)
    { /* Clear ATR Duration Timer interrupt flag */
        base->IS7816 = UART_IS7816_ADT_MASK;
        /* Indicate ADT expired */
        context->timersState.adtExpired = true;
        /* If transfer is in progress, terminate session */
        if ((context->xIsBusy))
        {
            smartcard_uart_CompleteReceiveData(base, context);
        }
    }
#endif
    /* Clear pending interrupts */
    (void)base->S1;
    (void)base->D;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * brief Interrupt handler for UART.
 *
 * This handler uses the buffers stored in the smartcard_context_t structures to transfer
 * data. The Smart card driver requires this function to call when the UART interrupt occurs.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 */
void SMARTCARD_UART_IRQHandler(UART_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return;
    }

    /* Check if Initial Character (TS) was detected */
    if (base->IS7816 & UART_IS7816_INITD_MASK)
    {
#if defined(FSL_FEATURE_PIT_TIMER_COUNT) && (FSL_FEATURE_PIT_TIMER_COUNT)
        /* Stop TS timer */
        smartcard_uart_TimerStop(context->interfaceConfig.tsTimerId);
#endif
        /* Get Data Convention format from RXINV bit in UART_S2 register */
        context->cardParams.convention = (smartcard_card_convention_t)(base->S2 & UART_S2_RXINV_MASK);
        /* Clear interrupt flag for initial character detected */
        base->IS7816 = UART_IS7816_INITD_MASK;
        /* Disable initial character detection */
        base->IE7816 &= ~UART_IE7816_INITDE_MASK;
        /* Set transfer mode to receiving(ATR bytes) mode */
        context->transferState = kSMARTCARD_ReceivingState;
        /* Complete receive process */
        smartcard_uart_CompleteReceiveData(base, context);
        return;
    }
    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!context->xIsBusy))
    {
        return;
    }

    /* RIE IRQ - count of bytes in rx fifo reached the rx threshold value RX_THD[RDT] */
    if ((base->C2 & UART_C2_RIE_MASK) && (base->S1 & UART_S1_RDRF_MASK))
    {
        if ((context->tType == kSMARTCARD_T1Transport) && (context->xSize > 1u) &&
            (base->IE7816 & UART_IE7816_BWTE_MASK))
        {
            /* Only the 1st byte has been received, now time to disable BWT interrupt and enable CWT interrupt */
            base->IE7816                    = (base->IE7816 & ~UART_IE7816_BWTE_MASK) | UART_IE7816_CWTE_MASK;
            context->timersState.cwtExpired = false;
            base->RWFIFO                    = context->rxFifoThreshold;
        }

        while ((base->RCFIFO) && (context->xSize))
        {
            /* Get data and put into receive buffer */
            *(context->xBuff) = base->D;
            ++context->xBuff;
            --context->xSize;
        }

        /* Check if the last byte was received */
        if (context->xSize == 0)
        {
            smartcard_uart_CompleteReceiveData(base, context);
        }
        else
        {
            /* If the count of remaining bytes to receive is less than fifo size, update the value of receiver data
             * threshold */
            if (context->xSize < context->rxFifoThreshold)
            {
                base->RWFIFO = context->xSize;
            }
        }
    }

    /* TCIE IRQ - all data from fifo is transmitted */
    if ((base->C2 & UART_C2_TCIE_MASK) && (base->S1 & UART_S1_TC_MASK))
    {
        smartcard_uart_CompleteSendData(base, context);
    }

    /* TIE IRQ - tx fifo is empty */
    if ((base->C2 & UART_C2_TIE_MASK) && (base->S1 & UART_S1_TDRE_MASK))
    {
        while ((context->txFifoEntryCount - base->TCFIFO) && (context->xSize))
        {
            base->D = *(context->xBuff);
            ++context->xBuff;
            --context->xSize;
        }

        if (context->xSize == 0)
        {
            base->C2 &= ~UART_C2_TIE_MASK;
            base->C2 |= UART_C2_TCIE_MASK;
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Configure baudrate
 *
 * @param base The UART peripheral base address.
 * @param context A pointer to a SMARTCARD driver context structure.
 *
 * @return An error code or kStatus_SMARTCARD_Success.
 */
static status_t smartcard_uart_ConfigureBaudrate(UART_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    uint32_t uartModuleClock;
    uint32_t instance;
    uint8_t temp;
    uint32_t brfa, sbr;
    uint32_t sourceClockInKHz = 0u;
    uint32_t sCClockInKHz     = 0u;

    instance = smartcard_uart_GetInstance(base);
    /* Get UART module clock from system clock module */
    switch (instance)
    {
        case 0u:
#if defined(UART0_CLK_SRC)
            uartModuleClock = CLOCK_GetFreq(UART0_CLK_SRC);
#else
            uartModuleClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif
            break;
        case 1u:
#if defined(UART1_CLK_SRC)
            uartModuleClock = CLOCK_GetFreq(UART1_CLK_SRC);
#else
            uartModuleClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif
            break;
#if (FSL_FEATURE_SOC_UART_COUNT >= 3)
        case 2u:
#if defined(UART2_CLK_SRC)
            uartModuleClock = CLOCK_GetFreq(UART2_CLK_SRC);
#else
            uartModuleClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif
            break;
#endif
#if (FSL_FEATURE_SOC_UART_COUNT >= 4)
        case 3u:
#if defined(UART3_CLK_SRC)
            uartModuleClock = CLOCK_GetFreq(UART3_CLK_SRC);
#else
            uartModuleClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif
            break;
#endif
#if (FSL_FEATURE_SOC_UART_COUNT >= 5)
        case 4u:
#if defined(UART4_CLK_SRC)
            uartModuleClock = CLOCK_GetFreq(UART4_CLK_SRC);
#else
            uartModuleClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif
            break;
#endif
#if (FSL_FEATURE_SOC_UART_COUNT >= 6)
        case 5u:
#if defined(UART5_CLK_SRC)
            uartModuleClock = CLOCK_GetFreq(UART5_CLK_SRC);
#else
            uartModuleClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif
            break;
#endif
        default:
            uartModuleClock = 0u;
            break;
    }
    sourceClockInKHz = uartModuleClock / 1000u;
    sCClockInKHz     = context->interfaceConfig.smartCardClock / 1000u;
    /* BaudRate = (SourceClkInHz)/[16 * (SBR +  BRFA)] */
    sbr = (uint16_t)(sourceClockInKHz * context->cardParams.Fi / (context->cardParams.currentD * sCClockInKHz * 16u));
    /* check to see if sbr is out of range of register bits */
    if ((sbr > 0x1FFFu) || (sbr < 1u))
    { /* unsupported baud rate for given source clock input*/
        return kStatus_SMARTCARD_OtherError;
    }
    switch (context->cardParams.currentD)
    {
        case 1:
        {
            if (context->cardParams.t0Indicated == 1)
            {
                sbr = sbr + SBR_CAL_ADJUST_D1_T0;
            }
            else
            {
                sbr = sbr + SBR_CAL_ADJUST_D1_T1;
            }

            break;
        }
        case 2:
        {
            if (context->cardParams.t0Indicated == 1)
            {
                sbr = sbr + SBR_CAL_ADJUST_D2_T0;
            }
            else
            {
                sbr = sbr + SBR_CAL_ADJUST_D2_T1;
            }

            break;
        }
        case 4:
        {
            if (context->cardParams.t0Indicated == 1)
            {
                sbr = sbr + SBR_CAL_ADJUST_D4_T0;
            }
            else
            {
                sbr = sbr + SBR_CAL_ADJUST_D4_T1;
            }

            break;
        }

        default:
            break;
    }
    base->C2 &= ~UART_C2_RE_MASK;
    temp      = base->BDH & ~UART_BDH_SBR_MASK;
    base->BDH = temp | (uint8_t)(sbr >> 8u);
    base->BDL = (uint8_t)sbr;
#if defined(FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT) && (FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT)
    /* determine if a fractional divider is needed to fine tune closer to the
     * desired baud, each value of brfa is in 1/32 increments,
     * hence the multiply-by-32. */
    brfa = (32u * sourceClockInKHz * context->cardParams.Fi) / (context->cardParams.currentD * sCClockInKHz * 16u);
    brfa -= (uint16_t)(32u * sbr);
    switch (context->cardParams.currentD)
    {
        case 1:
        {
            if (context->cardParams.t0Indicated == 1)
            {
                brfa = brfa + BRFA_CAL_ADJUST_D1_T0;
            }
            else
            {
                brfa = brfa + BRFA_CAL_ADJUST_D1_T1;
            }

            break;
        }
        case 2:
        {
            if (context->cardParams.t0Indicated == 1)
            {
                brfa = brfa + BRFA_CAL_ADJUST_D2_T0;
            }
            else
            {
                brfa = brfa + BRFA_CAL_ADJUST_D2_T1;
            }

            break;
        }
        case 4:
        {
            if (context->cardParams.t0Indicated == 1)
            {
                brfa = brfa + BRFA_CAL_ADJUST_D4_T0;
            }
            else
            {
                brfa = (uint32_t)((int32_t)brfa + BRFA_CAL_ADJUST_D4_T1);
            }

            break;
        }

        default:
            break;
    }
    /* write the brfa value to the register*/
    temp     = base->C4 & ~UART_C4_BRFA_MASK;
    base->C4 = temp | brfa;
#endif
    base->C2 |= UART_C2_RE_MASK;

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Controls the UART module per different user requests.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a smart card driver context structure.
 * param control Smart card command type.
 * param param Integer value specific to a control command.
 *
 * return An kStatus_SMARTCARD_OtherError in case of error
 * return kStatus_SMARTCARD_Success in success
 */
status_t SMARTCARD_UART_Control(UART_Type *base,
                                smartcard_context_t *context,
                                smartcard_control_t control,
                                uint32_t param)
{
    if ((NULL == context))
    {
        return kStatus_SMARTCARD_InvalidInput;
    }

    uint8_t temp;

    switch (control)
    {
        case kSMARTCARD_EnableADT:
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
            /* Disable ISO-7816 mode first */
            base->C7816 &= ~UART_C7816_ISO_7816E_MASK;
            /* Set ATR timer value */
            base->AP7816A_T0 = (uint8_t)((SMARTCARD_EMV_ATR_DURATION_ETU) >> 8);
            base->AP7816B_T0 = (uint8_t)(SMARTCARD_EMV_ATR_DURATION_ETU);
            /* Enable ATR specific interrupt */
            base->IE7816 |= UART_IE7816_ADTE_MASK;
            /* Enable ISO-7816 mode */
            base->C7816 |= UART_C7816_ISO_7816E_MASK;
#endif
            break;
        case kSMARTCARD_DisableADT:
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
            /* Disable ATR specific interrupt */
            base->IE7816 &= ~UART_IE7816_ADTE_MASK;
            /* Clear ATR timer value */
            base->AP7816A_T0 = 0u;
            base->AP7816B_T0 = 0u;
#endif
            break;
        case kSMARTCARD_EnableGTV:
            /* Enable GTV specific interrupt */
            base->IE7816 |= UART_IE7816_GTVE_MASK;
            break;
        case kSMARTCARD_DisableGTV:
            /* Disable GTV specific interrupt */
            base->IE7816 &= ~UART_IE7816_GTVE_MASK;
            break;
        case kSMARTCARD_ResetWWT:
            /* save the current value of IE7816 register */
            temp = base->IE7816;
            /* disable 7816 function */
            base->C7816 &= ~UART_C7816_ISO_7816E_MASK;
            /* clear any pending WT interrupt flag */
            base->IS7816 = UART_IS7816_WT_MASK;
            /* enable 7816 function */
            base->C7816 |= UART_C7816_ISO_7816E_MASK;
            /* re-enable all interrupts */
            base->IE7816 = temp;
            break;
        case kSMARTCARD_EnableWWT:
            /* Enable WWT Timer interrupt to occur */
            base->IE7816 |= UART_IE7816_WTE_MASK;
            break;
        case kSMARTCARD_DisableWWT:
            /* Disable WWT Timer interrupt to occur */
            base->IE7816 &= ~UART_IE7816_WTE_MASK;
            break;
        case kSMARTCARD_ResetCWT:
            /* Reset CWT Timer */
            /* Save interrupts configuration */
            temp = base->IE7816;
            /* disable 7816 function */
            base->C7816 &= ~UART_C7816_ISO_7816E_MASK;
            /* Clear Character Wait Timer interrupt flag */
            base->IS7816 = UART_IS7816_CWT_MASK;
            /* enable 7816 function */
            base->C7816 |= UART_C7816_ISO_7816E_MASK;
            /* re-enable all interrupts */
            base->IE7816 = temp;
            break;
        case kSMARTCARD_EnableCWT:
            /* Enable CWT Timer interrupt to occur */
            base->IE7816 |= UART_IE7816_CWTE_MASK;
            break;
        case kSMARTCARD_DisableCWT:
            /* Disable WWT Timer interrupt to occur */
            base->IE7816 &= ~UART_IE7816_CWTE_MASK;
            break;
        case kSMARTCARD_ResetBWT:
            /* Reset BWT timer */
            /* Save interrupts configuration */
            temp = base->IE7816;
            /* disable 7816 function */
            base->C7816 &= ~UART_C7816_ISO_7816E_MASK;
            /* Clear Block Wait Timer interrupt flag */
            base->IS7816 = UART_IS7816_BWT_MASK;
            /* enable 7816 function */
            base->C7816 |= UART_C7816_ISO_7816E_MASK;
            /* re-enable all interrupts */
            base->IE7816 = temp;
            break;
        case kSMARTCARD_EnableBWT:
            /* Enable BWT Timer interrupt to occur */
            base->IE7816 |= UART_IE7816_BWTE_MASK;
            break;
        case kSMARTCARD_DisableBWT:
            /* Disable BWT Timer interrupt to occur */
            base->IE7816 &= ~UART_IE7816_BWTE_MASK;
            break;
        case kSMARTCARD_EnableInitDetect:
            /* Disable receiver */
            base->C2 &= ~UART_C2_RE_MASK;
            base->S2 &= ~(UART_S2_RXINV_MASK | UART_S2_MSBF_MASK);
            /* Clear all ISO7816 interrupt flags */
            base->IS7816 = 0xFFu;
            /* Enable initial character detection */
            base->C7816 |= UART_C7816_INIT_MASK;
            /* Check and clear any pending initial character detected flag */
            base->IS7816 = UART_IS7816_INITD_MASK;
            /* Enable TS detect interrupt*/
            base->IE7816 |= UART_IE7816_INITDE_MASK;
            break;
        case kSMARTCARD_EnableAnack:
            /* Enable NACK-on-error interrupt to occur */
            base->C7816 |= UART_C7816_ANACK_MASK;
            break;
        case kSMARTCARD_DisableAnack:
            /* Disable NACK-on-error interrupt to occur */
            base->C7816 &= ~UART_C7816_ANACK_MASK;
            break;
        case kSMARTCARD_ConfigureBaudrate:
            return smartcard_uart_ConfigureBaudrate(base, context);
        case kSMARTCARD_SetupATRMode:
            /* Set in default ATR mode */
            smartcard_uart_SetTransferType(base, context, kSMARTCARD_SetupATRMode);
            break;
        case kSMARTCARD_SetupT0Mode:
            /* Set transport protocol type to T=0 */
            smartcard_uart_SetTransferType(base, context, kSMARTCARD_SetupT0Mode);
            break;
        case kSMARTCARD_SetupT1Mode:
            /* Set transport protocol type to T=1 */
            smartcard_uart_SetTransferType(base, context, kSMARTCARD_SetupT1Mode);
            break;
        case kSMARTCARD_EnableReceiverMode:
            /* Enable receiver mode and switch to receive direction */
            base->C2 |= UART_C2_RE_MASK;
            base->C3 &= ~UART_C3_TXDIR_MASK;
            break;
        case kSMARTCARD_DisableReceiverMode:
            /* Disable receiver */
            base->C2 &= ~UART_C2_RE_MASK;
            break;
        case kSMARTCARD_EnableTransmitterMode:
            /* Enable transmitter mode and switch to transmit direction */
            base->C2 |= UART_C2_TE_MASK;
            base->C3 |= UART_C3_TXDIR_MASK;
            break;
        case kSMARTCARD_DisableTransmitterMode:
            /* Disable transmitter */
            base->C2 &= ~UART_C2_TE_MASK;
            break;
        case kSMARTCARD_ResetWaitTimeMultiplier:
#if defined(FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT) && (FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT)
            /* Reset Wait Timer Multiplier */
            /* Save interrupts configuration */
            temp = base->IE7816;
            /* Disable ISO7816 functionality */
            base->C7816 &= ~UART_C7816_ISO_7816E_MASK;
            /* Setting of the Wait Parameter Register */
            if (param > 1)
            {
                base->WP7816 = (uint8_t)(param - 1);
            }
            else
            {
                base->WP7816 = (uint8_t)(param);
            }
            /* enable 7816 functionality */
            base->C7816 |= UART_C7816_ISO_7816E_MASK;
            /* Restore interrupts configuration */
            base->IE7816 = temp;
            /* Set flag to SMARTCARD context accordingly */
            if ((uint8_t)param == 0u)
            {
                context->wtxRequested = false;
            }
            else
            {
                context->wtxRequested = true;
            }
#endif
            break;
        default:
            return kStatus_SMARTCARD_InvalidInput;
    }

    return kStatus_SMARTCARD_Success;
}

/*!
 * brief Handles initial TS character timer time-out event.
 *
 * param base The UART peripheral base address.
 * param context A pointer to a Smart card driver context structure.
 */
void SMARTCARD_UART_TSExpiryCallback(UART_Type *base, smartcard_context_t *context)
{
    if ((NULL == context))
    {
        return;
    }
#if defined(FSL_FEATURE_SOC_PIT_COUNT) && FSL_FEATURE_SOC_PIT_COUNT
    /* Clear PIT timer interrupt status flag */
    PIT->CHANNEL[context->interfaceConfig.tsTimerId].TFLG = PIT_TFLG_TIF_MASK;
#endif /* FSL_FEATURE_SOC_PIT_COUNT */
    /* Set timer has expired */
    context->timersState.initCharTimerExpired = true;
    /* Stop TS timer */
    smartcard_uart_TimerStop(context->interfaceConfig.tsTimerId);
    context->transferState = kSMARTCARD_IdleState;
    /* Un-block the caller */
    smartcard_uart_CompleteReceiveData(base, context);

    return;
}
