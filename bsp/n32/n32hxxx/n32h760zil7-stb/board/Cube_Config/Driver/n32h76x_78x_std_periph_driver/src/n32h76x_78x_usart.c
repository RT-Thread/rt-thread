/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_usart.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_usart.h"
#include "n32h76x_78x_rcc.h"


/**
*\*\name    USART_DeInit
*\*\fun     Deinitializes the USARTx peripheral registers to their default reset values.
*\*\param   U(S)ARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  none
**/
void USART_DeInit(USART_Module* USARTx)
{
    if (USARTx == USART1)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_USART1);
    }
    else if (USARTx == USART2)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_USART2);
    }
    else if (USARTx == USART3)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_USART3);
    }
    else if (USARTx == USART4)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_USART4);
    }
    else if (USARTx == USART5)
    {
        RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_USART5);
    }
    else if (USARTx == USART6)
    {
        RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_USART6);
    }
    else if (USARTx == USART7)
    {
        RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_USART7);
    }
    else if (USARTx == USART8)
    {
        RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_USART8);
    }
    else if (USARTx == UART9)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_UART9);
    }
    else if (USARTx == UART10)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_UART10);
    }
    else if (USARTx == UART11)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_UART11);
    }
    else if (USARTx == UART12)
    {
        RCC_EnableAPB1PeriphReset3(RCC_APB1_PERIPHRST_UART12);
    }
    else if (USARTx == UART13)
    {
        RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_UART13);
    }
    else if (USARTx == UART14)
    {
        RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_UART14);
    }
    else
    {
        if (USARTx == UART15)
        {
            RCC_EnableAPB2PeriphReset3(RCC_APB2_PERIPHRST_UART15);
        }
    }
}


/**
*\*\name    USART_Init
*\*\fun     Initializes the USARTx peripheral according to USART_InitStruct.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15

*\*\param   USART_InitStruct (The input parameters must be the following values):
*\*\          - buad_rate :
*\*\            - (((buad_rate) > 0) && ((buad_rate) < 0x00E4E1C0))
*\*\          - WordLength
*\*\            - USART_WL_8B
*\*\            - USART_WL_9B
*\*\          - StopBits
*\*\            - USART_STPB_1
*\*\            - USART_STPB_0_5
*\*\            - USART_STPB_2
*\*\            - USART_STPB_1_5
*\*\          - Parity
*\*\            - USART_PE_NO
*\*\            - USART_PE_EVEN
*\*\            - USART_PE_ODD
*\*\          - Mode
*\*\            - USART_MODE_RX
*\*\            - USART_MODE_TX
*\*\          - HardwareFlowControl
*\*\            - USART_HFCTRL_NONE
*\*\            - USART_HFCTRL_RTS
*\*\            - USART_HFCTRL_CTS
*\*\            - USART_HFCTRL_RTS_CTS
*\*\          - OverSampling
*\*\            - USART_8OVER
*\*\            - USART_16OVER
*\*\return  none
**/
void USART_Init(USART_Module* USARTx, USART_InitType* USART_InitStruct)
{
    uint32_t tmpregister;
    uint32_t apbclock;
    uint32_t integerdivider;
    uint32_t fractionaldivider;
    uint32_t usartxbase;
    RCC_ClocksTypeDef RCC_ClocksStatus;
    const uint8_t ApbPresTable[8]    = {0, 0, 0, 0, 1, 2, 3, 4};

    usartxbase = (uint32_t)USARTx;

    /* USART CTRL2 Configuration */
    tmpregister = USARTx->CTRL2;
    /* Clear STOP[1:0] bits */
    tmpregister &= CTRL2_STPB_CLR_MASK;
    /* Configure the USART Stop Bits */
    /* Set STOP[1:0] bits according to StopBits value */
    tmpregister |= (uint32_t)USART_InitStruct->StopBits;
    /* Write to USART CTRL2 */
    USARTx->CTRL2 = (uint32_t)tmpregister;


    /* USART CTRL1 Configuration */
    tmpregister = USARTx->CTRL1;
    /* Clear RXEN, TXEN, PSEL, PCEN, WL and OSPM bits */
    tmpregister &= USART_CTRL1_CLR_MASK;
    /* Configure the USART Word Length, Parity, OverSampling and mode */
    /* Set the WL bits according to WordLength value */
    /* Set PSEL and PCEN bits according to Parity value */
    /* Set RXEN and TXEN bits according to Mode value */
    /* Set OSPM bits according to OverSampling value */
    tmpregister |= (uint32_t)USART_InitStruct->WordLength | USART_InitStruct->Parity \
                   | USART_InitStruct->OverSampling | USART_InitStruct->Mode;
    /* Write to USART CTRL1 */
    USARTx->CTRL1 = (uint32_t)tmpregister;

    /* USART CTRL3 Configuration */
    tmpregister = USARTx->CTRL3;
    /* Clear CTSE and RTSE bits */
    tmpregister &= CTRL3_CLR_MASK;
    /* Configure the USART HFC */
    /* Set CTSE and RTSE bits according to HardwareFlowControl value */
    tmpregister |= USART_InitStruct->HardwareFlowControl;
    /* Write to USART CTRL3 */
    USARTx->CTRL3 = (uint32_t)tmpregister;

    /* USART PBC Configuration */
    /* Configure the USART Baud Rate */
    RCC_GetClocksFreqValue(&RCC_ClocksStatus);

    if ((usartxbase == USART5_BASE) || (usartxbase == USART6_BASE) \
            || (usartxbase == USART7_BASE) || (usartxbase == USART8_BASE) \
            || (usartxbase == UART13_BASE) || (usartxbase == UART14_BASE) \
            || (usartxbase == UART15_BASE))
    {
        apbclock = RCC_ClocksStatus.APB2ClkFreq;
    }
    else if ((usartxbase == USART1_BASE) || (usartxbase == USART2_BASE))
    {
        apbclock = RCC_ClocksStatus.AHB1ClkFreq >> (ApbPresTable[(RCC->APB1DIV1 & RCC_APB1DIV1_APB1USARTDIV) >> 28]);
    }
    else
    {
        apbclock = RCC_ClocksStatus.APB1ClkFreq;
    }

    /* Determine the integer part */
    if((USARTx->CTRL1 & USART_8OVER) == 0)
    {
        /* Integer part computing in case Oversampling mode is 16 Samples */
        integerdivider = ((25 * (apbclock / 4)) / (USART_InitStruct->BaudRate));
    }
    else
    {
        /* Integer part computing in case Oversampling mode is 8 Samples */
        integerdivider = ((25 * (apbclock / 2)) / (USART_InitStruct->BaudRate));
    }

    tmpregister = (integerdivider / 100) << 4;

    /* Determine the fractional part */
    fractionaldivider = integerdivider - (100 * (tmpregister >> 4));

    /*Determine whether the fractional part needs to carried*/
    if((USARTx->CTRL1 & USART_8OVER) != 0)
    {
        /* Oversampling mode is 8 Samples */
        fractionaldivider = ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x0F);

        if(fractionaldivider == 0x08)
        {
            tmpregister = tmpregister + 0x10;
        }
        else
        {
            tmpregister |= fractionaldivider;
        }
    }
    else
    {
        /* Oversampling mode is 16 Samples */
        tmpregister += ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x1F);
    }

    /* Write to USART PBC */
    USARTx->BRCF = (uint32_t)tmpregister;
}

/**
*\*\name    USART_StructInit.
*\*\fun     Fills each USART_InitStruct member with its default value.
*\*\param   USART_InitStruct (The input parameters must be the following values):
*\*\          - BaudRate
*\*\          - WordLength
*\*\          - StopBits
*\*\          - Parity
*\*\          - Mode
*\*\          - OverSampling
*\*\return  none
**/
void USART_StructInit(USART_InitType* USART_InitStruct)
{
    /* USART_InitStruct members default value */
    USART_InitStruct->BaudRate            = 9600;
    USART_InitStruct->WordLength          = USART_WL_8B;
    USART_InitStruct->StopBits            = USART_STPB_1;
    USART_InitStruct->Parity              = USART_PE_NO;
    USART_InitStruct->Mode                = USART_MODE_RX | USART_MODE_TX;
    USART_InitStruct->HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStruct->OverSampling        = USART_16OVER;
}


/**
*\*\name    USART_ClockInit
*\*\fun     Initializes the USARTx peripheral Clock according to the specified parameters in the USART_ClockInitStruct.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\param   USART_ClockInitStruct (The input parameters must be the following values):
*\*\          - Clock :
*\*\            - USART_CLK_DISABLE
*\*\            - USART_CLK_ENABLE
*\*\          - USART_Clock_Polarity
*\*\            - USART_CLKPOL_LOW
*\*\            - USART_CLKPOL_HIGH
*\*\          - USART_Clock_Phase
*\*\            - USART_CLKPHA_1EDGE
*\*\            - USART_CLKPHA_2EDGE
*\*\          - USART_Last_Bit
*\*\            - USART_CLKLB_DISABLE
*\*\            - USART_CLKLB_ENABLE
*\*\return  none
*\*\note    The Smart Card and Synchronous modes are not available for UART5/UART6/UART7/UART8.
**/
void USART_ClockInit(USART_Module* USARTx, USART_ClockInitType* USART_ClockInitStruct)
{
    uint32_t tmpregister;

    /* USART CTRL2 Configuration */
    tmpregister = USARTx->CTRL2;
    /* Clear CLKEN, CPOL, CPHA and LBCLK bits */
    tmpregister &= CTRL2_CLOCK_CLR_MASK;
    /* Configure the USART Clock, CPOL, CPHA and LastBit */
    /* Set CLKEN bit according to Clock value */
    /* Set CLKPOL bit according to Polarity value */
    /* Set CLKPHA bit according to Phase value */
    /* Set LBCLK bit according to LastBit value */
    tmpregister |= (uint32_t)USART_ClockInitStruct->Clock | USART_ClockInitStruct->Polarity
                   | USART_ClockInitStruct->Phase | USART_ClockInitStruct->LastBit;
    /* Write to USART CTRL2 */
    USARTx->CTRL2 = (uint32_t)tmpregister;
}

/**
*\*\name    USART_ClockStructInit
*\*\fun     Fills each USART_ClockInitStruct member with its default value.
*\*\param   USART_ClockInitStruct (The input parameters must be the following values):
*\*\          - Clock
*\*\          - USART_Clock_Polarity
*\*\          - USART_Clock_Phase
*\*\          - USART_Last_Bit
*\*\return  none
**/
void USART_ClockStructInit(USART_ClockInitType* USART_ClockInitStruct)
{
    /* USART_ClockInitStruct members default value */
    USART_ClockInitStruct->Clock    = USART_CLK_DISABLE;
    USART_ClockInitStruct->Polarity = USART_CLKPOL_LOW;
    USART_ClockInitStruct->Phase    = USART_CLKPHA_1EDGE;
    USART_ClockInitStruct->LastBit  = USART_CLKLB_DISABLE;
}


/**
*\*\name    USART_Enable
*\*\fun     Enables or disables the specified USART peripheral.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_Enable(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected USART by setting the UE bit in the CTRL1 register */
        USARTx->CTRL1 |= CTRL1_UEN_SET;
    }
    else
    {
        /* Disable the selected USART by clearing the UE bit in the CTRL1 register */
        USARTx->CTRL1 &= CTRL1_UEN_RESET;
    }
}


/**
*\*\name    USART_ConfigInt
*\*\fun     Enables or disables the specified USART interrupts.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_INT (The input parameters must be the following values):
*\*\          - USART_INT_PEF   Parity Error interrupt
*\*\          - USART_INT_TXC   Transmission complete interrupt
*\*\          - USART_INT_TXDE  Transmit Data Register empty interrupt
*\*\          - USART_INT_RXDNE Receive Data register not empty interrupt
*\*\          - USART_INT_IDLEF Idle line detection interrupt
*\*\          - USART_INT_RTOE  Receiver timeout interrupt
*\*\          - USART_INT_LINBD LIN Break detection interrupt
*\*\          - USART_INT_ERRF  Error interrupt(Frame error, noise error, overrun error)
*\*\          - USART_INT_CTSF  CTS change interrupt
*\*\          - USART_INT_TXFTE  TXFIFO threshold interrupt enable
*\*\          - USART_INT_RXFTE  RXFIFO threshold interrupt enable
*\*\          - USART_INT_RXFEE  RXFIFO empty interrupt enable
*\*\          - USART_INT_TXFEE  TXFIFO empty interrupt enable
*\*\          - USART_INT_RXFFE  RXFIFO full interrupt enable
*\*\          - USART_INT_TXFFE  TXFIFO full interrupt enable
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_ConfigInt(USART_Module* USARTx, uint32_t USART_INT, FunctionalState Cmd)
{
    uint32_t itmask;
    uint32_t usartxbase;

    usartxbase = (uint32_t)USARTx;

    /* Get the interrupt position */
    itmask = USART_INT & USART_INT_MASK;

    if((USART_INT & USART_CTRL1_INTMASK) != (uint32_t)0x00) /* The IT is in CTRL1 register */
    {
        usartxbase += 0x00;
    }
    else if((USART_INT & USART_CTRL2_INTMASK) != (uint32_t)0x00) /* The IT is in CTRL2 register */
    {
        usartxbase += 0x04;
    }
    else if((USART_INT & USART_CTRL3_INTMASK) != (uint32_t)0x00) /* The IT is in CTRL3 register */
    {
        usartxbase += 0x08;
    }
    else /* The IT is in FIFO register */
    {
        usartxbase += 0x1C;
    }

    if (Cmd != DISABLE)
    {
        *(__IO uint32_t*)usartxbase |= itmask;
    }
    else
    {
        *(__IO uint32_t*)usartxbase &= ~itmask;
    }
}


/**
*\*\name    USART_EnableDMA
*\*\fun     Enables or disables the USART's DMA interface.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_DMAReq (The input parameters must be the following values):
*\*\          - USART_DMAREQ_TX USART DMA transmit request
*\*\          - USART_DMAREQ_RX USART DMA receive request
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_EnableDMA(USART_Module* USARTx, uint32_t USART_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transfer for selected requests by setting the DMAT and/or
           DADDR bits in the USART CTRL3 register */
        USARTx->CTRL3 |= USART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
           DADDR bits in the USART CTRL3 register */
        USARTx->CTRL3 &= (uint32_t)~USART_DMAReq;
    }
}

/**
*\*\name    USART_SetAddr
*\*\fun     Sets the address of the USART node.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_Addr (The input parameters must be the following values):
*\*\          - (((USART_Addr)>=0x00)&&((USART_Addr)<0x10))
*\*\return  none
**/
void USART_SetAddr(USART_Module* USARTx, uint8_t USART_Addr)
{
    /* Clear the USART address */
    USARTx->CTRL2 &= CTRL2_ADDR_MASK;
    /* Set the USART address node */
    USARTx->CTRL2 |= USART_Addr;
}


/**
*\*\name    USART_ConfigWakeUpMode
*\*\fun     Selects the USART WakeUp method.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_WakeUpMode (The input parameters must be the following values):
*\*\          - USART_WUM_IDLELINE WakeUp by an idle line detection
*\*\          - USART_WUM_ADDRMASK WakeUp by an address mark
*\*\return  none
**/
void USART_ConfigWakeUpMode(USART_Module* USARTx, uint32_t USART_WakeUpMode)
{
    USARTx->CTRL1 &= CTRL1_WUM_MASK;
    USARTx->CTRL1 |= USART_WakeUpMode;
}


/**
*\*\name    USART_EnableRcvWakeUp
*\*\fun     Determines if the USART is in mute mode or not.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_EnableRcvWakeUp(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the USART mute mode  by setting the RWU bit in the CTRL1 register */
        USARTx->CTRL1 |= CTRL1_RCVWU_SET;
    }
    else
    {
        /* Disable the USART mute mode by clearing the RWU bit in the CTRL1 register */
        USARTx->CTRL1 &= CTRL1_RCVWU_RESET;
    }
}


/**
*\*\name    USART_ConfigLINBreakDetectLength
*\*\fun     Sets the USART LIN Break detection length.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_LINBreakDetectLength (The input parameters must be the following values):
*\*\          - USART_LINBDL_10B 10-bit break detection
*\*\          - USART_LINBDL_11B 11-bit break detection
*\*\return  none
**/
void USART_ConfigLINBreakDetectLength(USART_Module* USARTx, uint32_t USART_LINBreakDetectLength)
{
    USARTx->CTRL2 &= CTRL2_LINBDL_MASK;
    USARTx->CTRL2 |= USART_LINBreakDetectLength;
}


/**
*\*\name    USART_EnableLIN
*\*\fun     Enables or disables the USART's LIN mode.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_EnableLIN(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the LIN mode by setting the LINEN bit in the CTRL2 register */
        USARTx->CTRL2 |= CTRL2_LINMEN_SET;
    }
    else
    {
        /* Disable the LIN mode by clearing the LINEN bit in the CTRL2 register */
        USARTx->CTRL2 &= CTRL2_LINMEN_RESET;
    }
}

/**
*\*\name    USART_SendData
*\*\fun     Transmits single data through the USARTx peripheral.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   Data :
*\*\          - the data to transmit
*\*\return  none
**/
void USART_SendData(USART_Module* USARTx, uint32_t Data)
{
    /* Transmit Data */
    USARTx->DAT = (Data & (uint32_t)0x01FF);
}

/**
*\*\name    USART_ReceiveData
*\*\fun     Returns the most recent received data by the USARTx peripheral.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  none
**/
uint32_t USART_ReceiveData(USART_Module* USARTx)
{
    /* Receive Data */
    return (uint32_t)(USARTx->DAT & (uint32_t)0x01FF);
}

/**
*\*\name    USART_SendBreak
*\*\fun     Transmits break characters.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  none
**/
void USART_SendBreak(USART_Module* USARTx)
{
    /* Send break characters */
    USARTx->CTRL1 |= CTRL1_SDBRK_SET;
}


/**
*\*\name    USART_SetGuardTime
*\*\fun     Sets the specifies USART guard time.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\param   USART_GuardTime:
*\*\          - specifies the guard time
*\*\return  none
**/
void USART_SetGuardTime(USART_Module* USARTx, uint8_t USART_GuardTime)
{
    /* Clear the USART Guard time */
    USARTx->GTP &= GTP_LSB_MASK;
    /* Set the USART guard time */
    USARTx->GTP |= (uint32_t)((uint32_t)USART_GuardTime << 0x08);
}

/**
*\*\name    USART_SetPrescaler
*\*\fun     Sets the system clock prescaler.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_Prescaler:
*\*\          - specifies the prescaler clock
*\*\return  none
**/
void USART_SetPrescaler(USART_Module* USARTx, uint8_t USART_Prescaler)
{
    /* Clear the USART prescaler */
    USARTx->GTP &= GTP_MSB_MASK;
    /* Set the USART prescaler */
    USARTx->GTP |= USART_Prescaler;
}

/**
*\*\name    USART_EnableSmartCard
*\*\fun     Enables or disables the USART's Smart Card mode.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_EnableSmartCard(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the SC mode by setting the SCEN bit in the CTRL3 register */
        USARTx->CTRL3 |= CTRL3_SCMEN_SET;
    }
    else
    {
        /* Disable the SC mode by clearing the SCEN bit in the CTRL3 register */
        USARTx->CTRL3 &= CTRL3_SCMEN_RESET;
    }
}

/**
*\*\name    USART_SetSmartCardNACK
*\*\fun     Enables or disables NACK transmission.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_SetSmartCardNACK(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the NACK transmission by setting the NACK bit in the CTRL3 register */
        USARTx->CTRL3 |= CTRL3_SCNACK_SET;
    }
    else
    {
        /* Disable the NACK transmission by clearing the NACK bit in the CTRL3 register */
        USARTx->CTRL3 &= CTRL3_SCNACK_RESET;
    }
}


/**
*\*\name    USART_EnableHalfDuplex
*\*\fun     Enables or disables the USART's Half Duplex communication.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_EnableHalfDuplex(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Half-Duplex mode by setting the HDSEL bit in the CTRL3 register */
        USARTx->CTRL3 |= CTRL3_HDMEN_SET;
    }
    else
    {
        /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CTRL3 register */
        USARTx->CTRL3 &= CTRL3_HDMEN_RESET;
    }
}


/**
*\*\name    USART_ConfigIrDAMode
*\*\fun     Configures the USART's IrDA interface.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_IrDAMode (The input parameters must be the following values):
*\*\          - USART_IRDAMODE_LOWPPWER
*\*\          - USART_IRDAMODE_NORMAL
*\*\return  none
**/
void USART_ConfigIrDAMode(USART_Module* USARTx, uint32_t USART_IrDAMode)
{
    USARTx->CTRL3 &= CTRL3_IRDALP_MASK;
    USARTx->CTRL3 |= USART_IrDAMode;
}


/**
*\*\name    USART_EnableIrDA
*\*\fun     Enables or disables the USART's IrDA interface.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_EnableIrDA(USART_Module* USARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the IrDA mode by setting the IREN bit in the CTRL3 register */
        USARTx->CTRL3 |= CTRL3_IRDAMEN_SET;
    }
    else
    {
        /* Disable the IrDA mode by clearing the IREN bit in the CTRL3 register */
        USARTx->CTRL3 &= CTRL3_IRDAMEN_RESET;
    }
}


/**
*\*\name    USART_GetFlagStatus
*\*\fun     Checks whether the specified USART flag is set or not.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_FLAG (The input   parameters must be the following values):
*\*\          - USART_FLAG_FELOSE   Received Data FE Error Discard Flag
*\*\          - USART_FLAG_NELOSE   Received Data NE Error Discard Flag
*\*\          - USART_FLAG_PELOSE   Received Data PE Error Discard Flag
*\*\          - USART_FLAG_RTO      recevier timeout Flag
*\*\          - USART_FLAG_FEF      Framing error Flag
*\*\          - USART_FLAG_NEF      Noise error flag Flag
*\*\          - USART_FLAG_OREF     Overrun error
*\*\          - USART_FLAG_PEF      Parity error
*\*\          - USART_FLAG_LINBD    LIN break detection flag
*\*\          - USART_FLAG_CTSF     CTS Change flag
*\*\          - USART_FLAG_RXDNE    Receive data register not empty flag
*\*\          - USART_FLAG_TXC      Transmission Complete flag
*\*\          - USART_FLAG_TXDE     Transmit data register empty flag
*\*\          - USART_FLAG_IDLEF    Idle Line detection flag
*\*\          - USART_FLAG_TXFT     TX FIFO threshold flag
*\*\          - USART_FLAG_RXFT     RX FIFO threshold flag
*\*\          - USART_FLAG_RXFE     RX FIFO empty flag
*\*\          - USART_FLAG_TXFE     TX FIFO empty flag
*\*\          - USART_FLAG_RXFF     RX FIFO full flag
*\*\          - USART_FLAG_TXFF     TX FIFO full flag
*\*\return  USART_FLAG
*\*\          - SET
*\*\          - RESET
**/
FlagStatus USART_GetFlagStatus(USART_Module* USARTx, uint32_t USART_FLAG)
{
    FlagStatus bitstatus;

    if ((USARTx->STS & USART_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    USART_ClrFlag
*\*\fun     Clears the USARTx's pending flags.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_FLAG (The input   parameters must be the following values):
*\*\          - USART_FLAG_FELOSE   Received Data FE Error Discard Flag
*\*\          - USART_FLAG_NELOSE   Received Data NE Error Discard Flag
*\*\          - USART_FLAG_PELOSE   Received Data PE Error Discard Flag
*\*\          - USART_FLAG_LINBD    LIN break detection flag
*\*\          - USART_FLAG_CTSF     CTS Change flag
*\*\          - USART_FLAG_RXDNE    Receive data register not empty flag
*\*\          - USART_FLAG_TXC      Transmission Complete flag
*\*\return  none
*\*\note
*\*\          - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
*\*\            error) and IDLE (Idle line detected) flags are cleared by software
*\*\            sequence: a read operation to USART_STS register (USART_GetFlagStatus())
*\*\            followed by a read operation to USART_DAT register (USART_ReceiveData()).
*\*\          - RXNE flag can be also cleared by a read to the USART_DAT register
*\*\            (USART_ReceiveData()).
*\*\          - TC flag can be also cleared by software sequence: a read operation to
*\*\            USART_SR register (USART_GetFlagStatus()) followed by a write operation
*\*\            to USART_DAT register (USART_SendData()).
*\*\          - TXE flag is cleared only by a write to the USART_DAT register
*\*\            (USART_SendData()).
*\*\          - RTO flag is cleared only by a write 1 to the USART_CTRL2.RTOCF bit.
*\*\            (USART_ClrRTOFlag()).
**/
void USART_ClrFlag(USART_Module* USARTx, uint32_t USART_FLAG)
{
    if((USART_FLAG & USART_FLAG_LOSEMASK) != (uint32_t)RESET)
    {
        USARTx->STS = USART_FLAG;
    }
    else
    {
        USARTx->STS = (~(USART_FLAG | USART_FLAG_LOSEMASK));
    }
}


/**
*\*\name    USART_ClrRTOFlag
*\*\fun     Clears the USARTx's RTO pending flag.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  none
**/
void USART_ClrRTOFlag(USART_Module* USARTx)
{
    uint32_t time_out;
    USARTx->CTRL2 |= USART_FLAG_RTO;
    time_out = 0xFFFF;

    while((USART_GetFlagStatus(USARTx, USART_FLAG_RTO) == SET) && (time_out--));

    USARTx->CTRL2 &= (~USART_FLAG_RTO);
}

/**
*\*\name    USART_GetIntStatus
*\*\fun     Checks whether the specified USART interrupt has set or not.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   USART_INT (The input parameters must be the following values):
*\*\          - USART_INT_PEF   Parity Error interrupt
*\*\          - USART_INT_TXC   Transmission complete interrupt
*\*\          - USART_INT_TXDE  Transmit Data Register empty interrupt
*\*\          - USART_INT_RXDNE Receive Data register not empty interrupt
*\*\          - USART_INT_IDLEF Idle line detection interrupt
*\*\          - USART_INT_RTOE  Receiver timeout interrupt
*\*\          - USART_INT_LINBD LIN Break detection interrupt
*\*\          - USART_INT_ERRF  Error interrupt(Frame error, noise error, overrun error)
*\*\          - USART_INT_CTSF  CTS change interrupt
*\*\          - USART_INT_TXFTE  TXFIFO threshold interrupt enable
*\*\          - USART_INT_RXFTE  RXFIFO threshold interrupt enable
*\*\          - USART_INT_RXFEE  RXFIFO empty interrupt enable
*\*\          - USART_INT_TXFEE  TXFIFO empty interrupt enable
*\*\          - USART_INT_RXFFE  RXFIFO full interrupt enable
*\*\          - USART_INT_TXFFE  TXFIFO full interrupt enable
*\*\return  bitstatus
*\*\          - SET
*\*\          - RESET
**/
INTStatus USART_GetIntStatus(USART_Module* USARTx, uint32_t USART_INT)
{
    uint32_t itmask;
    INTStatus bitstatus;

    /* Get the interrupt position */
    itmask = USART_INT & USART_INT_MASK;

    if ((USART_INT & USART_CTRL1_INTMASK) != 0x00) /* The IT  is in CTRL1 register */
    {
        itmask &= USARTx->CTRL1;
    }
    else if ((USART_INT & USART_CTRL2_INTMASK) != 0x00) /* The IT  is in CTRL2 register */
    {
        itmask &= USARTx->CTRL2;
    }
    else if ((USART_INT & USART_CTRL3_INTMASK) != 0x00) /* The IT  is in CTRL3 register */
    {
        itmask &= USARTx->CTRL3;
    }
    else
    {
        itmask &= USARTx->FIFO;
    }

    if (itmask != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name    USART_IdleFrameSet
*\*\fun     Idle frame controllable enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_IdleFrameSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL1 |= CTRL1_IFCEN_ENABLE;
    }
    else
    {
        USARTx->CTRL1 &= CTRL1_IFCEN_DISABLE;
    }
}


/**
*\*\name    USART_PinSwapSet
*\*\fun     Swap TX/RX pins enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_PinSwapSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL1 |= CTRL1_SWAP_ENABLE;
    }
    else
    {
        USARTx->CTRL1 &= CTRL1_SWAP_DISABLE;
    }
}


/**
*\*\name    USART_CfgDriverAssertTime
*\*\fun     Set Driver Enable assertion time.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Time:(The input parameters must be the following values)
*\*\          - 0x01 ~ 0x1F
*\*\return  none
**/
void USART_CfgDriverAssertTime(USART_Module* USARTx, uint32_t Time)
{
    USARTx->CTRL1 &= (~USART_CTRL1_DEAT_MASK);
    USARTx->CTRL1 |= (Time << 21);
}




/**
*\*\name    USART_CfgDriverdeassertTime
*\*\fun     Set Driver Enable deassertion time.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Time:(The input parameters must be the following values)
*\*\          - 0x01 ~ 0x1F
*\*\return  none
**/
void USART_CfgDriverdeassertTime(USART_Module* USARTx, uint32_t Time)
{
    USARTx->CTRL1 &= (~USART_CTRL1_DEDT_MASK);
    USARTx->CTRL1 |= (Time << 16);
}


/**
*\*\name    USART_DriverPolaritySet
*\*\fun     Driver enable polarity selection.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_DriverPolaritySet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL1 |= CTRL1_DEP_ENABLE;
    }
    else
    {
        USARTx->CTRL1 &= CTRL1_DEP_DISABLE;
    }
}


/**
*\*\name    USART_DriverModeSet
*\*\fun     Driver enable mode selection.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_DriverModeSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL1 |= CTRL1_DEM_ENABLE;
    }
    else
    {
        USARTx->CTRL1 &= CTRL1_DEM_DISABLE;
    }
}


/**
*\*\name    USART_FEFDiscardSet
*\*\fun     FEF Data Discard enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_FEFDiscardSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL2 |= CTRL2_FEFLOSE_ENABLE;
    }
    else
    {
        USARTx->CTRL2 &= CTRL2_FEFLOSE_DISABLE;
    }
}


/**
*\*\name    USART_NEFDiscardSet
*\*\fun     NEF Data Discard enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_NEFDiscardSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL2 |= CTRL2_NEFLOSE_ENABLE;
    }
    else
    {
        USARTx->CTRL2 &= CTRL2_NEFLOSE_DISABLE;
    }
}


/**
*\*\name    USART_PEFDiscardSet
*\*\fun     PEF Data Discard enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_PEFDiscardSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL2 |= CTRL2_PEFLOSE_ENABLE;
    }
    else
    {
        USARTx->CTRL2 &= CTRL2_PEFLOSE_DISABLE;
    }
}


/**
*\*\name    USART_RTOSet
*\*\fun     Receiver timeout enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_RTOSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->CTRL2 |= CTRL2_RTO_ENABLE;
    }
    else
    {
        USARTx->CTRL2 &= CTRL2_RTO_DISABLE;
    }
}


/**
*\*\name    USART_GetTxFIFO_Num
*\*\fun     number of  TXFIFO valid data.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  0x00~0x08
**/
uint32_t USART_GetTxFIFO_Num(USART_Module* USARTx)
{
    return ((USARTx->FIFO & USART_FIFO_TXCNT_MASK) >> 18);
}


/**
*\*\name    USART_GetRxFIFO_Num
*\*\fun     number of  RXFIFO valid data.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  0x00~0x08
**/
uint32_t USART_GetRxFIFO_Num(USART_Module* USARTx)
{
    return ((USARTx->FIFO & USART_FIFO_RXCNT_MASK) >> 14);
}


/**
*\*\name    USART_CfgRxFIFOThreshold
*\*\fun     RXFIFO threshold configuration.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   threshold (The input parameters must be the following values):
*\*\          - USART_FIFO_DEEP1
*\*\          - USART_FIFO_DEEP2
*\*\          - USART_FIFO_DEEP4
*\*\          - USART_FIFO_DEEP6
*\*\          - USART_FIFO_DEEP7
*\*\          - USART_FIFO_DEEP8
*\*\return  none
**/
void USART_CfgRxFIFOThreshold(USART_Module* USARTx, uint32_t threshold)
{
    USARTx->FIFO &= (~USART_FIFO_RXFTCFG_MASK);
    USARTx->FIFO |= (threshold << 5);
}


/**
*\*\name    USART_CfgTxFIFOThreshold
*\*\fun     TXFIFO threshold configuration.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param   threshold (The input parameters must be the following values):
*\*\          - USART_FIFO_DEEP1
*\*\          - USART_FIFO_DEEP2
*\*\          - USART_FIFO_DEEP4
*\*\          - USART_FIFO_DEEP6
*\*\          - USART_FIFO_DEEP7
*\*\          - USART_FIFO_DEEP8
*\*\return  none
**/
void USART_CfgTxFIFOThreshold(USART_Module* USARTx, uint32_t threshold)
{
    USARTx->FIFO &= (~USART_FIFO_TXFTCFG_MASK);
    USARTx->FIFO |= (threshold << 2);
}


/**
*\*\name    USART_ClrFIFO
*\*\fun     FIFO clear.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\return  none
**/
void USART_ClrFIFO(USART_Module* USARTx)
{
    USARTx->FIFO |= USART_CLEAR_FIFO;
}


/**
*\*\name    USART_FIFOModeSet
*\*\fun     FIFO mode enable or disable.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Cmd:(The input parameters must be the following values)
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void USART_FIFOModeSet(USART_Module* USARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        USARTx->FIFO |= USART_FIFO_ENABLE;
    }
    else
    {
        USARTx->FIFO &= USART_FIFO_DISABLE;
    }
}


/**
*\*\name    USART_CfgIdleFrameWidth
*\*\fun     configure Idle frame width.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Width:(The input parameters must be the following values)
*\*\          - 0x0000 ~ 0xFFFF
*\*\return  none
**/
void USART_IdleFrameWidthSet(USART_Module* USARTx, uint32_t Width)
{
    USARTx->IFW = Width;
}


/**
*\*\name    USART_CfgRTOWidth
*\*\fun     configure receive timeout width.
*\*\param   USARTx (The input parameters must be the following values):
*\*\          - USART1
*\*\          - USART2
*\*\          - USART3
*\*\          - USART4
*\*\          - USART5
*\*\          - USART6
*\*\          - USART7
*\*\          - USART8
*\*\          - UART9
*\*\          - UART10
*\*\          - UART11
*\*\          - UART12
*\*\          - UART13
*\*\          - UART14
*\*\          - UART15
*\*\param  Width:(The input parameters must be the following values)
*\*\          - 0x00000000 ~ 0x0FFFFFFF
*\*\return  none
**/
void USART_CfgRTOWidth(USART_Module* USARTx, uint32_t Width)
{
    USARTx->RTO = Width;
}

