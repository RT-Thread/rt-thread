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
 * @file n32h76x_78x_lpuart.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_lpuart.h"
#include "n32h76x_78x_rcc.h"


/**
*\*\name   LPUART_DeInit.
*\*\fun    Deinitializes the LPUART peripheral registers to their default reset values
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\return none
*/

void LPUART_DeInit(LPUART_Module* LPUARTx)
{
    if (LPUARTx == LPUART1)
    {
        RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPUART1);
    }
    else
    {
        if(LPUARTx == LPUART2)
        {
            RCC_EnableRDPeriphReset1(RCC_RD_PERIPHRST_LPUART2);
        }

    }

}

/**
*\*\name   LPUART_Init.
*\*\fun    Initializes the LPUART peripheral according to the specified parameters in the LPUART_InitStruct.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param  LPUART_InitStruct pointer to a LPUART_InitType structure
*\*\         that contains the configuration information for the specified LPUART peripheral .
*\*\return none
*/

void LPUART_Init(LPUART_Module* LPUARTx, LPUART_InitType* LPUART_InitStruct)
{
    uint32_t tmpregister = 0x00, clocksrc = 0x00, apbclock = 0x00;
    uint32_t integerdivider    = 0x00;
    uint32_t fractionaldivider = 0x00;
    uint32_t tmpdivider = 0x00, lastdivider = 0x00, i = 0x00;
    uint32_t lpuartdiv = 0x00;
    RCC_ClocksTypeDef RCC_ClocksStatus;
    const uint8_t ApbPresTable[8]    = {0, 0, 0, 0, 1, 2, 3, 4};

    /*---------------------------- LPUART BRCFG1 & 2 Configuration -----------------------*/
    /* Configure the LPUART Baud Rate -------------------------------------------*/

    if (LPUARTx == LPUART1)
    {
        clocksrc = ((uint32_t)(RCC->RDSEL1 & RCC_RDSEL1_LPUART1SEL));
    }
    else
    {
        if(LPUARTx == LPUART2)
        {
            clocksrc = ((uint32_t)(RCC->RDSEL1 & RCC_RDSEL1_LPUART2SEL)) << 4;
        }
    }

    if (clocksrc == RCC_LPUARTCLK_SRC_LSE)
    {
        apbclock = 0x8000; // 32.768kHz
    }
    else if (clocksrc == RCC_LPUARTCLK_SRC_HSI)
    {
        apbclock = HSI_VALUE;
    }
    else if (clocksrc == RCC_LPUARTCLK_SRC_MSI)
    {
        apbclock = MSI_VALUE; // 16MHz
    }
    else if (clocksrc == RCC_LPUARTCLK_SRC_SYSBUSDIV)
    {
        lpuartdiv =  ((uint32_t)((RCC->RDDIV1 & RCC_RDDIV1_LPUARTDIV) >> 24));
        RCC_GetClocksFreqValue(&RCC_ClocksStatus);
        apbclock = (RCC_ClocksStatus.SysBusDivClkFreq) >> (ApbPresTable[lpuartdiv]);
    }
    else //(clocksrc ==RCC_LPUARTCLK_SRC_HSE)
    {
        apbclock = HSE_VALUE;
    }

    /* Determine the integer part */
    integerdivider = apbclock / (LPUART_InitStruct->BaudRate);

    /* Configure sampling method */
    if(integerdivider <= 10)
    {
        LPUART_ConfigSamplingMethod(LPUARTx, LPUART_SMPCNT_1B);
    }
    else
    {
        LPUART_ConfigSamplingMethod(LPUARTx, LPUART_SMPCNT_3B);
    }

    /* Write to LPUART BRCFG1 */
    LPUARTx->BRCFG1 = (uint32_t)integerdivider;

    /* Determine the fractional part */
    fractionaldivider = ((apbclock % (LPUART_InitStruct->BaudRate)) * 10000) / (LPUART_InitStruct->BaudRate);

    tmpregister = 0x00;
    tmpdivider = fractionaldivider;

    /* Implement the fractional part in the register */
    for( i = 0; i < 8; i++)
    {
        lastdivider = tmpdivider;
        tmpdivider = lastdivider + fractionaldivider;

        if((tmpdivider / 10000) ^ (lastdivider / 10000))
        {
            tmpregister |= (0x01 << i);
        }
    }

    /* Write to LPUART BRCFG2 */
    LPUARTx->BRCFG2 = (uint32_t)tmpregister;
		
		//    /*---------------------------- LPUART CTRL Configuration -----------------------*/
    tmpregister = LPUARTx->CTRL;
    /* Clear RXEN, TXEN, RTST[1:0], PC, RTSEN,CTSEN and PEN bits */
    tmpregister &= CTRL_CLR_MASK;
    /* Configure the LPUART Parity, Mode, RtsThrehold and HardwareFlowControl ----------------------- */
    /* Set PC and PEN bits according to Parity value */
    /* Set the RXEN and TXEN bit according to Mode */
    /* Set RTST[1:0] bits according to RtsThrehold */
    /* Set RTSEN and CTSEN bits according to HardwareFlowControl */
    tmpregister |= (uint32_t)LPUART_InitStruct->Parity | LPUART_InitStruct->Mode | LPUART_InitStruct->RtsThreshold | LPUART_InitStruct->HardwareFlowControl;
    /* Write to LPUART CTRL */
    LPUARTx->CTRL = (uint32_t)tmpregister;
}

/**
*\*\name   LPUART_StructInit.
*\*\fun    Fills each LPUART_InitStruct member with its default value.
*\*\param  LPUART_InitStruct pointer to a LPUART_InitType structure
*\*\          which will be initialized.
*\*\return none
*/

void LPUART_StructInit(LPUART_InitType* LPUART_InitStruct)
{
    /* LPUART_InitStruct members default value */
    LPUART_InitStruct->BaudRate            = 9600;
    LPUART_InitStruct->Parity              = LPUART_PE_NO;
    LPUART_InitStruct->Mode                = LPUART_MODE_RX | LPUART_MODE_TX;
    LPUART_InitStruct->RtsThreshold        = LPUART_RTSTH_FIFOFU;
    LPUART_InitStruct->HardwareFlowControl = LPUART_HFCTRL_NONE;
}

/**
*\*\name   LPUART_FlushRxFifo.
*\*\fun    Flushes Receiver FIFO.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\return none
*/

void LPUART_FlushRxFifo(LPUART_Module* LPUARTx)
{
    /* Clear LPUART Flush Receiver FIFO */
    LPUARTx->CTRL |= LPUART_FLUSHRXF_ENABLE;

    while(LPUART_GetFlagStatus(LPUARTx, LPUART_FLAG_RXFIFO_NE) != RESET)
    {
    }

    LPUARTx->CTRL &= LPUART_FLUSHRXF_DISABLE;
}

/**
*\*\name   LPUART_FlushTxFifo.
*\*\fun    Flushes transmit FIFO.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\return none
*/
void LPUART_FlushTxFifo(LPUART_Module* LPUARTx)
{
    /* Clear LPUART Flush transmit FIFO */
    LPUARTx->CTRL |= LPUART_FLUSHTXF_ENABLE;

    while(LPUART_GetFlagStatus(LPUARTx, LPUART_FLAG_TXFIFO_NE) != RESET)
    {
    }

    LPUARTx->CTRL &= LPUART_FLUSHTXF_DISABLE;
}

/**
*\*\name   LPUART_ConfigInt.
*\*\fun    Enables or disables the specified LPUART interrupts.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param  LPUART_INT specifies the LPUART interrupt sources to be enabled or disabled.
*\*\	        This parameter can be one of the following values:
*\*\          - LPUART_INT_TXFIFO_NE TX FIFO Non-Empty Interrupt
*\*\          - LPUART_INT_TXFIFO_HF TX FIFO Half Full Interrupt
*\*\          - LPUART_INT_TXFIFO_QF TX FIFO 1/4 Interrupt
*\*\          - LPUART_INT_TXFIFO_FU TX FIFO Full Interrupt Enable
*\*\          - LPUART_INT_TXFIFO_OV TX FIFO Overflow Interrupt
*\*\          - LPUART_INT_WUF       Wake-Up Interrupt
*\*\          - LPUART_INT_RXFIFO_NE RX FIFO Non-Empty Interrupt
*\*\          - LPUART_INT_RXFIFO_HF RX FIFO Half Full Interrupt
*\*\          - LPUART_INT_RXFIFO_FU RX FIFO Full Interrupt Enable
*\*\          - LPUART_INT_RXFIFO_OV RX FIFO Overflow Interrupt
*\*\          - LPUART_INT_TXC       TX Complete Interrupt
*\*\          - LPUART_INT_PE        Parity Check Error Interrupt
*\*\          - LPUART_INT_IDLEF     IDLE_FRAMEIE  Interrupt
*\*\          - LPUART_INT_FE        FRAME_ERROR  Interrupt
*\*\          - LPUART_INT_TXFIFO_EM TX FIFO Empty Interrupt
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
*/

void LPUART_ConfigInt(LPUART_Module* LPUARTx, uint32_t LPUART_INT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        LPUARTx->INTEN |= LPUART_INT;
    }
    else
    {
        LPUARTx->INTEN &= (~LPUART_INT);
    }
}

/**
*\*\name   LPUART_EnableDMA.
*\*\fun    Enables or disables the LPUART's DMA interface.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param  LPUART_DMAReq specifies the DMA request.
*\*\	        This parameter can be one of the following values:
*\*\          - LPUART_DMAREQ_TX LPUART DMA transmit request
*\*\          - LPUART_DMAREQ_RX LPUART DMA receive request
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
*/

void LPUART_EnableDMA(LPUART_Module* LPUARTx, uint32_t LPUART_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transfer by setting the DMA_RXEN and/or DMA_TXEN bits in the LPUART_CTRL register */
        LPUARTx->CTRL |= LPUART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer by clearing the DMA_RXEN and/or DMA_TXEN bits in the LPUART_CTRL register */
        LPUARTx->CTRL &= (uint32_t)(~LPUART_DMAReq);
    }
}

/**
*\*\name   LPUART_ConfigWakeUpMethod.
*\*\fun    Selects the LPUART WakeUp method.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param  LPUART_WakeUpMethod specifies the LPUART wakeup method.
*\*\	        This parameter can be one of the following values:
*\*\          - LPUART_WUSTP_STARTBIT WakeUp by Start Bit Detection
*\*\          - LPUART_WUSTP_RXNE WakeUp by RXNE Detection
*\*\          - LPUART_WUSTP_BYTE WakeUp by A Configurable Received Byte
*\*\          - LPUART_WUSTP_FRAME_2 WakeUp by A Programmed 2-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_3 WakeUp by A Programmed 3-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_4 WakeUp by A Programmed 4-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_5 WakeUp by A Programmed 5-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_6 WakeUp by A Programmed 6-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_7 WakeUp by A Programmed 7-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_8 WakeUp by A Programmed 8-Byte Frame
*\*\          - LPUART_WUSTP_FRAME_MANY WakeUp by A Programmed MANY-Byte Frame
*\*\return none
*/

void LPUART_ConfigWakeUpMethod(LPUART_Module* LPUARTx, uint32_t LPUART_WakeUpMethod)
{
    LPUARTx->CTRL &= CTRL_WUSTP_MASK;
    LPUARTx->CTRL |= LPUART_WakeUpMethod;
}

/**
*\*\name   LPUART_EnableWakeUpStop.
*\*\fun    Enables or disables LPUART Wakeup in STOP2 mode.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
*/
void LPUART_EnableWakeUpStop(LPUART_Module* LPUARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable Wakeup in STOP2 mode by setting the WUSTP bit in the CTRL register */
        LPUARTx->CTRL |= LPUART_WUSTP_ON;
    }
    else
    {
        /* Disable Wakeup in STOP2 mode by clearing the WUSTP bit in the CTRL register */
        LPUARTx->CTRL &= (~LPUART_WUSTP_ON);
    }
}

/**
*\*\name   LPUART_ConfigSamplingMethod.
*\*\fun    Selects the LPUART Sampling method.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param   LPUART_SamplingMethod specifies the LPAURT sampling method.
*\*\          This parameter can be one of the following values:
*\*\          - LPUART_SMPCNT_3B 3 Sample bit
*\*\          - LPUART_SMPCNT_1B 1 Sample bit
*\*\return none
*/
void LPUART_ConfigSamplingMethod(LPUART_Module* LPUARTx, uint32_t LPUART_SamplingMethod)
{

    LPUARTx->CTRL &= CTRL_SMPCNT_MASK;
    LPUARTx->CTRL |= LPUART_SamplingMethod;
}

/**
*\*\name   LPUART_EnableLoopBack.
*\*\fun    Enables or disables LPUART Loop Back Self-Test.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
*/
void LPUART_EnableLoopBack(LPUART_Module* LPUARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable LPUART Loop Back Self-Test by setting the LOOKBACK bit in the CTRL register */
        LPUARTx->CTRL |= LPUART_LOOPBACK_ENABLE;
    }
    else
    {
        /* Disable LPUART Loop Back Self-Test by clearing the LOOKBACK bit in the CTRL register */
        LPUARTx->CTRL &= LPUART_LOOPBACK_DISABLE;
    }
}

/**
*\*\name   LPUART_SendData.
*\*\fun    Transmits single data through the LPUART peripheral.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param   Data the data to transmit.
*\*\return none
*/

void LPUART_SendData(LPUART_Module* LPUARTx, uint8_t Data)
{
    /* Transmit Data */
    LPUARTx->TXDAT = (Data & (uint8_t)0xFF);
}

/**
*\*\name   LPUART_ReceiveData.
*\*\fun    Returns the most recent received data by the LPUART peripheral.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\return The received data.
*/

uint8_t LPUART_ReceiveData(LPUART_Module* LPUARTx)
{
    /* Receive Data */
    return (uint8_t)(LPUARTx->RXDAT & (uint8_t)0xFF);
}

/**
*\*\name   LPUART_ConfigWakeUpData.
*\*\fun    SConfigures LPUART detected byte or frame match for wakeup CPU from STOPS mode.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param  LPUART_WakeUpData specifies the LPUART detected byte or frame match for wakeup CPU from STOP2 mode.
*\*\return none
*/

void LPUART_ConfigWakeUpData(LPUART_Module* LPUARTx, uint32_t LPUART_WakeUpData1, uint32_t LPUART_WakeUpData2)
{
    LPUARTx->WUDAT1 = LPUART_WakeUpData1;
    LPUARTx->WUDAT2 = LPUART_WakeUpData2;
}

/**
*\*\name   LPUART_GetFlagStatus.
*\*\fun    Checks whether the specified LPUART flag is set or not.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param  LPUART_FLAG specifies the flag to check.
*\*\	        This parameter can be one of the following values:
*\*\          -  LPUART_FLAG_PEF Parity Check Error Flag.
*\*\          -  LPUART_FLAG_TXC TX Complete Flag.
*\*\          -  LPUART_FLAG_RXFIFO_OV RX FIFO Overflow Flag.
*\*\          -  LPUART_FLAG_RXFIFO_FU RX FIFO Full Flag.
*\*\          -  LPUART_FLAG_RXFIFO_HF RX FIFO Half Full Flag.
*\*\          -  LPUART_FLAG_RXFIFO_NE RX FIFO Non-Empty Flag.
*\*\          -  LPUART_FLAG_CTS CTS Change(Hardware Flow Control) Flag.
*\*\          -  LPUART_FLAG_WUF from STOP2 mode Flag.
*\*\          -  LPUART_FLAG_NEF Noise Detection Flag.
*\*\          -  LPUART_FLAG_TXFIFO_OV TX FIFO Overflow Flag.
*\*\          -  LPUART_FLAG_TXFIFO_FU TX FIFO Full Flag.
*\*\          -  LPUART_FLAG_TXFIFO_QF TX FIFO 1/4 Full Flag.
*\*\          -  LPUART_FLAG_TXFIFO_HF TX FIFO Half Full Flag.
*\*\          -  LPUART_FLAG_TXFIFO_NE TX FIFO Non-Empty Flag.
*\*\          -  LPUART_FLAG_IDLEF     IDLE frame detected.
*\*\          -  LPUART_FLAG_FRAME_ER  frame error detected.
*\*\          -  LPUART_FLAG_TXFIFO_EM TX FIFO Empty Flag.
*\*\return  bitstatus
*\*\          - SET
*\*\          - RESET
*/

FlagStatus LPUART_GetFlagStatus(LPUART_Module* LPUARTx, uint32_t LPUART_FLAG)
{
    FlagStatus bitstatus = RESET;

    if ((LPUARTx->STS & LPUART_FLAG) != (uint32_t)RESET)
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
*\*\name   LPUART_ClrFlag.
*\*\fun    Clears the LPUART's pending flags.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param LPUART_FLAG specifies the flag to clear.
*\*\	        This parameter can be one of the following values:
*\*\          -  LPUART_FLAG_PEF Parity Check Error Flag.
*\*\          -  LPUART_FLAG_TXC TX Complete Flag.
*\*\          -  LPUART_FLAG_RXFIFO_OV RX FIFO Overflow Flag.
*\*\          -  LPUART_FLAG_RXFIFO_FU RX FIFO Full Flag.
*\*\          -  LPUART_FLAG_RXFIFO_HF RX FIFO Half Full Flag.
*\*\          -  LPUART_FLAG_RXFIFO_NE RX FIFO Non-Empty Flag.
*\*\          -  LPUART_FLAG_WUF from STOP2 mode Flag.
*\*\          -  LPUART_FLAG_NEF Noise Detection Flag.
*\*\          -  LPUART_FLAG_TXFIFO_OV TX FIFO Overflow Flag.
*\*\          -  LPUART_FLAG_TXFIFO_FU TX FIFO Full Flag.
*\*\          -  LPUART_FLAG_TXFIFO_QF TX FIFO 1/4 Full Flag.
*\*\          -  LPUART_FLAG_TXFIFO_HF TX FIFO Half Full Flag.
*\*\          -  LPUART_FLAG_TXFIFO_NE TX FIFO Non-Empty Flag.
*\*\          -  LPUART_FLAG_IDLEF     IDLE frame detected.
*\*\          -  LPUART_FLAG_FRAME_ER  frame error detected.
*\*\return none
*/
void LPUART_ClrFlag(LPUART_Module* LPUARTx, uint32_t LPUART_FLAG)
{
    LPUARTx->STS = (uint32_t)LPUART_FLAG;
}

/**
*\*\name   LPUART_GetIntStatus.
*\*\fun    Checks whether the specified LPUART interrupt has set or not.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param LPUART_INT (The input parameters must be the following values):
*\*\          - LPUART_INT_TXFIFO_NE TX FIFO Non-Empty Interrupt
*\*\          - LPUART_INT_TXFIFO_HF TX FIFO Half Full Interrupt
*\*\          - LPUART_INT_TXFIFO_QF TX FIFO 1/4 Interrupt
*\*\          - LPUART_INT_TXFIFO_FU TX FIFO Full Interrupt Enable
*\*\          - LPUART_INT_TXFIFO_OV TX FIFO Overflow Interrupt
*\*\          - LPUART_INT_WUF       Wake-Up Interrupt
*\*\          - LPUART_INT_RXFIFO_NE RX FIFO Non-Empty Interrupt
*\*\          - LPUART_INT_RXFIFO_HF RX FIFO Half Full Interrupt
*\*\          - LPUART_INT_RXFIFO_FU RX FIFO Full Interrupt Enable
*\*\          - LPUART_INT_RXFIFO_OV RX FIFO Overflow Interrupt
*\*\          - LPUART_INT_TXC       TX Complete Interrupt
*\*\          - LPUART_INT_PE        Parity Check Error Interrupt
*\*\          - LPUART_INT_IDLEF     IDLE_FRAMEIE  Interrupt
*\*\          - LPUART_INT_FE        FRAME_ERROR  Interrupt
*\*\          - LPUART_INT_TXFIFO_EM TX FIFO Empty Interrupt
*\*\return  bitstatus
*\*\          - SET
*\*\          - RESET
*/

INTStatus LPUART_GetIntStatus(LPUART_Module* LPUARTx, uint32_t LPUART_INT)
{
    uint32_t itmask = 0x00;
    INTStatus bitstatus = RESET;

    /* Get the interrupt position */
    itmask = LPUART_INT & LPUART_INT_MASK;
    itmask &= LPUARTx->INTEN;

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
*\*\name   LPUART_ClrIntPendingBit.
*\*\fun    Clears the LPUART's interrupt pending bits.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param LPUART_INT (The input parameters must be the following values):
*\*\          - LPUART_INT_TXFIFO_NE TX FIFO Non-Empty Interrupt
*\*\          - LPUART_INT_TXFIFO_HF TX FIFO Half Full Interrupt
*\*\          - LPUART_INT_TXFIFO_QF TX FIFO 1/4 Interrupt
*\*\          - LPUART_INT_TXFIFO_FU TX FIFO Full Interrupt Enable
*\*\          - LPUART_INT_TXFIFO_OV TX FIFO Overflow Interrupt
*\*\          - LPUART_INT_WUF       Wake-Up Interrupt
*\*\          - LPUART_INT_RXFIFO_NE RX FIFO Non-Empty Interrupt
*\*\          - LPUART_INT_RXFIFO_HF RX FIFO Half Full Interrupt
*\*\          - LPUART_INT_RXFIFO_FU RX FIFO Full Interrupt Enable
*\*\          - LPUART_INT_RXFIFO_OV RX FIFO Overflow Interrupt
*\*\          - LPUART_INT_TXC       TX Complete Interrupt
*\*\          - LPUART_INT_PE        Parity Check Error Interrupt
*\*\          - LPUART_INT_IDLEF     IDLE_FRAMEIE  Interrupt
*\*\          - LPUART_INT_FE        FRAME_ERROR  Interrupt
*\*\          - LPUART_INT_TXFIFO_EM TX FIFO Empty Interrupt
*\*\return none
*/

void LPUART_ClrIntPendingBit(LPUART_Module* LPUARTx, uint32_t LPUART_INT)
{
    uint32_t itmask = 0x00;

    itmask = LPUART_INT & LPUART_INT_MASK;

    if(LPUART_INT == LPUART_INT_WUF)
    {
        itmask = (itmask << 0x01);
    }
    else if (LPUART_INT > LPUART_INT_WUF)
    {
        itmask = (itmask << 0x02);
    }

    LPUARTx->STS = itmask;
}

/**
*\*\name   LPUART_IdleFrameSet.
*\*\fun    Idle frame controllable enable or disable.
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
*/
void LPUART_IdleFrameSet(LPUART_Module* LPUARTx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        LPUARTx->CTRL |= LPUART_IDLEF_ENABLE;
    }
    else
    {
        LPUARTx->CTRL &= LPUART_IDLEF_DISABLE;
    }
}

/**
*\*\name   LPUART_ConfigRXByte.
*\*\fun    A configuration byte can be configured to receive how many bytes of data to wake
*\*\param  LPUARTx (The input parameters must be the following values):
*\*\          - LPUART1
*\*\          - LPUART2
*\*\param   Cmd:LPUART_RXNUMWU
*\*\return none
*/

void LPUART_ConfigRXByte(LPUART_Module* LPUARTx, uint8_t LPUART_RXNUMWU)
{
    uint32_t tmp = 0x00;
    tmp = ((uint32_t)(LPUART_RXNUMWU & 0x1F)) << 19;
    LPUARTx->CTRL |= tmp;
}

