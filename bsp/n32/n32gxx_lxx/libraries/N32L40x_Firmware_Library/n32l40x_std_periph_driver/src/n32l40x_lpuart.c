/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l40x_lpuart.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x_lpuart.h"
#include "n32l40x_rcc.h"

/** @addtogroup n32l40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup LPUART
 * @brief LPUART driver modules
 * @{
 */

/** @addtogroup LPUART_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup LPUART_Private_Defines
 * @{
 */

#define STS_CLR_MASK        ((uint16_t)0x01BF) /*!< LPUART STS Mask */

#define INTEN_CLR_MASK      ((uint16_t)0x0000) /*!< LPUART INTEN Mask */
#define INT_MASK            ((uint16_t)0x007F) /*!< LPUART Interrupt Mask */

#define CTRL_CLR_MASK       ((uint16_t)0x70F4) /*!< LPUART CTRL Mask */
#define CTRL_SMPCNT_MASK        ((uint16_t)0x3FFF) /*!< LPUART Sampling Method Mask */
#define CTRL_WUSTP_MASK         ((uint16_t)0x4FFF) /*!< LPUART WakeUp Method Mask */
#define CTRL_WUSTP_SET          ((uint16_t)0x0080) /*!< LPUART stop mode Enable Mask */
#define CTRL_WUSTP_RESET        ((uint16_t)0x7F7F) /*!< LPUART stop mode Disable Mask */
#define CTRL_LOOPBACK_SET   ((uint16_t)0x0010) /*!< LPUART Loopback Test Enable Mask */
#define CTRL_LOOPBACK_RESET ((uint16_t)0xFFEF) /*!< LPUART Loopback Test Disable Mask */
#define CTRL_FLUSH_SET          ((uint16_t)0x0004) /*!< LPUART Flush Receiver FIFO Enable Mask */
#define CTRL_FLUSH_RESET        ((uint16_t)0x7FFB) /*!< LPUART Flush Receiver FIFO Disable Mask */

/**
 * @}
 */

/** @addtogroup LPUART_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup LPUART_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup LPUART_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup LPUART_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the LPUART peripheral registers to their default reset values.
 */
void LPUART_DeInit(void)
{
    RCC_EnableRETPeriphReset(RCC_RET_PERIPH_LPUART, ENABLE);
    RCC_EnableRETPeriphReset(RCC_RET_PERIPH_LPUART, DISABLE);
}

/**
 * @brief  Initializes the LPUART peripheral according to the specified
 *         parameters in the LPUART_InitStruct.
 * @param LPUART_InitStruct pointer to a LPUART_InitType structure
 *         that contains the configuration information for the specified LPUART
 *         peripheral.
 */
void LPUART_Init(LPUART_InitType* LPUART_InitStruct)
{
    uint32_t tmpregister = 0x00, clocksrc = 0x00, apbclock = 0x00;
    uint32_t integerdivider    = 0x00;
    uint32_t fractionaldivider = 0x00;
    uint32_t tmpdivider = 0x00, lastdivider = 0x00, i = 0x00;
    RCC_ClocksType RCC_ClocksStatus;

    /* Check the parameters */
    // assert_param(IS_LPUART_BAUDRATE(LPUART_InitStruct->BaudRate));
    assert_param(IS_LPUART_PARITY(LPUART_InitStruct->Parity));
    assert_param(IS_LPUART_MODE(LPUART_InitStruct->Mode));
    assert_param(IS_LPUART_RTSTHRESHOLD(LPUART_InitStruct->RtsThreshold));
    assert_param(IS_LPUART_HARDWARE_FLOW_CONTROL(LPUART_InitStruct->HardwareFlowControl));

    // 时钟源判断，波特率范围

    /*---------------------------- LPUART CTRL Configuration -----------------------*/
    tmpregister = LPUART->CTRL;
    /* Clear FC_RXEN, FC_TXEN, RTS_THSEL[1:0], PCDIS, TRS and PSEL bits */
    tmpregister &= CTRL_CLR_MASK;
    /* Configure the LPUART Parity, Mode, RtsThrehold and HardwareFlowControl ----------------------- */
    /* Set PCDIS and PSEL bits according to Parity value */
    /* Set the TRS bit according to Mode */
    /* Set RTS_THSEL[1:0] bits according to RtsThrehold */
    /* Set FC_RXEN and FC_TXEN bits according to HardwareFlowControl */
    tmpregister |= (uint32_t)LPUART_InitStruct->Parity | LPUART_InitStruct->Mode | LPUART_InitStruct->RtsThreshold | LPUART_InitStruct->HardwareFlowControl;
    /* Write to LPUART CTRL */
    LPUART->CTRL = (uint16_t)tmpregister;

    /*---------------------------- LPUART BRCFG1 & 2 Configuration -----------------------*/
    /* Configure the LPUART Baud Rate -------------------------------------------*/
    clocksrc = RCC_GetLPUARTClkSrc();
    if (clocksrc == RCC_LPUARTCLK_SRC_LSE)
    {
        apbclock = 0x8000; // 32.768kHz
    }
    else if (clocksrc == RCC_LPUARTCLK_SRC_HSI)
    {
        apbclock = 0xF42400; // 16MHz
    }
    else if (clocksrc == RCC_LPUARTCLK_SRC_SYSCLK)
    {
        RCC_GetClocksFreqValue(&RCC_ClocksStatus);
        apbclock = RCC_ClocksStatus.SysclkFreq;
    }
    else //(clocksrc ==RCC_LPUARTCLK_SRC_APB1)
    {
        RCC_GetClocksFreqValue(&RCC_ClocksStatus);
        apbclock = RCC_ClocksStatus.Pclk1Freq;
    }

    /* Determine the integer part */
    integerdivider = apbclock / (LPUART_InitStruct->BaudRate);

    /* Configure sampling method */
    if (integerdivider <= 10)
    {
        LPUART_ConfigSamplingMethod(LPUART_SMPCNT_1B);
    }
    else
    {
        LPUART_ConfigSamplingMethod(LPUART_SMPCNT_3B);
    }

    /* Check baudrate */
    assert_param(IS_LPUART_BAUDRATE(integerdivider));
    /* Write to LPUART BRCFG1 */
    LPUART->BRCFG1 = (uint16_t)integerdivider;

    /* Determine the fractional part */
    fractionaldivider = ((apbclock % (LPUART_InitStruct->BaudRate)) * 10000) / (LPUART_InitStruct->BaudRate);

    tmpregister = 0x00;
    tmpdivider = fractionaldivider;
    /* Implement the fractional part in the register */
    for( i = 0; i < 8; i++)
    {
        lastdivider = tmpdivider;
        tmpdivider = lastdivider + fractionaldivider;
        if ((tmpdivider / 10000) ^ (lastdivider / 10000))
        {
            tmpregister |= (0x01 << i);
        }
    }
    /* Write to LPUART BRCFG2 */
    LPUART->BRCFG2 = (uint8_t)tmpregister;
}

/**
 * @brief  Fills each LPUART_InitStruct member with its default value.
 * @param LPUART_InitStruct pointer to a LPUART_InitType structure
 *         which will be initialized.
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
 * @brief  Flushes Receiver FIFO.
 */
void LPUART_FlushRxFifo(void)
{
    /* Clear LPUART Flush Receiver FIFO */
    LPUART->CTRL |= CTRL_FLUSH_SET;
    while (LPUART_GetFlagStatus(LPUART_FLAG_FIFO_NE) != RESET)
    {
    }
    LPUART->CTRL &= CTRL_FLUSH_RESET;
}

/**
 * @brief  Enables or disables the specified LPUART interrupts.
 * @param LPUART_INT specifies the LPUART interrupt sources to be enabled or disabled.
 *   This parameter can be one of the following values:
 *     @arg LPUART_INT_WUF Wake-Up Interrupt
 *     @arg LPUART_INT_FIFO_NE FIFO Non-Empty Interrupt
 *     @arg LPUART_INT_FIFO_HF FIFO Half Full Interrupt
 *     @arg LPUART_INT_FIFO_FU FIFO Full Interrupt Enable
 *     @arg LPUART_INT_FIFO_OV FIFO Overflow Interrupt
 *     @arg LPUART_INT_TXC TX Complete Interrupt
 *     @arg LPUART_INT_PE Parity Check Error Interrupt
 * @param Cmd new state of the specified LPUART interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void LPUART_ConfigInt(uint16_t LPUART_INT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_LPUART_CFG_INT(LPUART_INT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
       LPUART->INTEN |= (uint8_t)LPUART_INT;
    }
    else
    {
        LPUART->INTEN &= (uint8_t)(~LPUART_INT);
    }
}

/**
 * @brief  Enables or disables the LPUART's DMA interface.
 * @param LPUART_DMAReq specifies the DMA request.
 *   This parameter can be any combination of the following values:
 *     @arg LPUART_DMAREQ_TX LPUART DMA transmit request
 *     @arg LPUART_DMAREQ_RX LPUART DMA receive request
 * @param Cmd new state of the DMA Request sources.
 *   This parameter can be: ENABLE or DISABLE.
 */
void LPUART_EnableDMA(uint16_t LPUART_DMAReq, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_LPUART_DMAREQ(LPUART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transfer by setting the DMA_RXEN and/or DMA_TXEN bits in the LPUART_CTRL register */
        LPUART->CTRL |= LPUART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer by clearing the DMA_RXEN and/or DMA_TXEN bits in the LPUART_CTRL register */
        LPUART->CTRL &= (uint16_t)(~LPUART_DMAReq);
    }
}

/**
 * @brief  Selects the LPUART WakeUp method.
 * @param LPUART_WakeUpMethod specifies the LPUART wakeup method.
 *   This parameter can be one of the following values:
 *     @arg LPUART_WUSTP_STARTBIT WakeUp by Start Bit Detection
 *     @arg LPUART_WUSTP_RXNE WakeUp by RXNE Detection
 *     @arg LPUART_WUSTP_BYTE WakeUp by A Configurable Received Byte
 *     @arg LPUART_WUSTP_FRAME WakeUp by A Programmed 4-Byte Frame
 */
void LPUART_ConfigWakeUpMethod(uint16_t LPUART_WakeUpMethod)
{
    /* Check the parameters */
    assert_param(IS_LPUART_WAKEUP(LPUART_WakeUpMethod));

    LPUART->CTRL &= CTRL_WUSTP_MASK;
    LPUART->CTRL |= LPUART_WakeUpMethod;
}

/**
 * @brief  Enables or disables LPUART Wakeup in STOP2 mode.
 * @param Cmd new state of the LPUART Wakeup in STOP2 mode.
 *   This parameter can be: ENABLE or DISABLE.
 */
void LPUART_EnableWakeUpStop(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable Wakeup in STOP2 mode by setting the WUSTP bit in the CTRL register */
        LPUART->CTRL |= CTRL_WUSTP_SET;
    }
    else
    {
        /* Disable Wakeup in STOP2 mode by clearing the WUSTP bit in the CTRL register */
        LPUART->CTRL &= CTRL_WUSTP_RESET;
    }
}

/**
 * @brief  Selects the LPUART Sampling method.
 * @param LPUART_SamplingMethod specifies the LPAURT sampling method.
 *   This parameter can be one of the following values:
 *     @arg LPUART_SMPCNT_3B 3 Sample bit
 *     @arg LPUART_SMPCNT_1B 1 Sample bit
 */
void LPUART_ConfigSamplingMethod(uint16_t LPUART_SamplingMethod)
{
    /* Check the parameters */
    assert_param(IS_LPUART_SAMPLING(LPUART_SamplingMethod));

    LPUART->CTRL &= CTRL_SMPCNT_MASK;
    LPUART->CTRL |= LPUART_SamplingMethod;
}

/**
 * @brief  Enables or disables LPUART Loop Back Self-Test.
 * @param Cmd new state of the LPUART Loop Back Self-Test.
 *   This parameter can be: ENABLE or DISABLE.
 */
void LPUART_EnableLoopBack(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable LPUART Loop Back Self-Test by setting the LOOKBACK bit in the CTRL register */
        LPUART->CTRL |= CTRL_LOOPBACK_SET;
    }
    else
    {
        /* Disable LPUART Loop Back Self-Test by clearing the LOOKBACK bit in the CTRL register */
        LPUART->CTRL &= CTRL_LOOPBACK_RESET;
    }
}

/**
 * @brief  Transmits single data through the LPUART peripheral.
 * @param Data the data to transmit.
 */
void LPUART_SendData(uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_LPUART_DATA(Data));

    /* Transmit Data */
    LPUART->DAT = (Data & (uint8_t)0xFF);
}

/**
 * @brief  Returns the most recent received data by the LPUART peripheral.
 * @return The received data.
 */
uint8_t LPUART_ReceiveData(void)
{
    /* Receive Data */
    return (uint8_t)(LPUART->DAT & (uint8_t)0xFF);
}

/**
 * @brief  SConfigures LPUART detected byte or frame match for wakeup CPU from STOPS mode.
 * @param LPUART_WakeUpData specifies the LPUART detected byte or frame match for wakeup CPU from STOP2 mode.
 */
void LPUART_ConfigWakeUpData(uint32_t LPUART_WakeUpData)
{
    LPUART->WUDAT = LPUART_WakeUpData;
}

/**
 * @brief  Checks whether the specified LPUART flag is set or not.
 * @param LPUART_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg LPUART_FLAG_PEF Parity Check Error Flag.
 *     @arg LPUART_FLAG_TXC TX Complete Flag.
 *     @arg LPUART_FLAG_FIFO_OV FIFO Overflow Flag.
 *     @arg LPUART_FLAG_FIFO_FU FIFO Full Flag.
 *     @arg LPUART_FLAG_FIFO_HF FIFO Half Full Flag.
 *     @arg LPUART_FLAG_FIFO_NE FIFO Non-Empty Flag.
 *     @arg LPUART_FLAG_CTS CTS Change(Hardware Flow Control) Flag.
 *     @arg LPUART_FLAG_WUFWakeup from STOP2 mode Flag.
 *     @arg LPUART_FLAG_NF Noise Detection Flag.
 * @return The new state of LPUART_FLAG (SET or RESET).
 */
FlagStatus LPUART_GetFlagStatus(uint16_t LPUART_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_LPUART_FLAG(LPUART_FLAG));

    if ((LPUART->STS & LPUART_FLAG) != (uint16_t)RESET)
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
 * @brief  Clears the LPUART's pending flags.
 * @param LPUART_FLAG specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg LPUART_FLAG_PEF Parity Check Error Flag.
 *     @arg LPUART_FLAG_TXC TX Complete Flag.
 *     @arg LPUART_FLAG_FIFO_OV FIFO Overflow Flag.
 *     @arg LPUART_FLAG_FIFO_FU FIFO Full Flag.
 *     @arg LPUART_FLAG_FIFO_HF FIFO Half Full Flag.
 *     @arg LPUART_FLAG_FIFO_NE FIFO Non-Empty Flag.
 *     @arg LPUART_FLAG_CTS CTS Change(Hardware Flow Control) Flag.
 *     @arg LPUART_FLAG_WUFWakeup from STOP2 mode Flag.
 *     @arg LPUART_FLAG_NF Noise Detection Flag.
 */
void LPUART_ClrFlag(uint16_t LPUART_FLAG)
{
    /* Check the parameters */
    assert_param(IS_LPUART_CLEAR_FLAG(LPUART_FLAG));

    LPUART->STS = (uint16_t)LPUART_FLAG;
}

/**
 * @brief  Checks whether the specified LPUART interrupt has occurred or not.
 * @param LPUART_INT specifies the LPUART interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg LPUART_INT_WUF Wake-Up Interrupt
 *     @arg LPUART_INT_FIFO_NE FIFO Non-Empty Interrupt
 *     @arg LPUART_INT_FIFO_HF FIFO Half Full Interrupt
 *     @arg LPUART_INT_FIFO_FU FIFO Full Interrupt Enable
 *     @arg LPUART_INT_FIFO_OV FIFO Overflow Interrupt
 *     @arg LPUART_INT_TXC TX Complete Interrupt
 *     @arg LPUART_INT_PE Parity Check Error Interrupt
 * @return The new state of LPUART_INT (SET or RESET).
 */
INTStatus LPUART_GetIntStatus(uint16_t LPUART_INT)
{
    uint32_t bitpos = 0x00, itmask = 0x00;
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_LPUART_GET_INT(LPUART_INT));

    /* Get the interrupt position */
    itmask = (uint8_t)(LPUART_INT >> 0x08) & INT_MASK;
    itmask = (uint32_t)0x01 << itmask;
    itmask &= LPUART->INTEN;

    bitpos = ((uint8_t)LPUART_INT) & 0xFF;
    if (LPUART_INT_WUF == LPUART_INT){
        bitpos = (bitpos << 0x01);
    }
    bitpos &= LPUART->STS;
    if ((itmask != (uint16_t)RESET) && (bitpos != (uint16_t)RESET))
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
 * @brief  Clears the LPUART's interrupt pending bits.
 * @param LPUART_INT specifies the interrupt pending bit to clear.
 *   This parameter can be one of the following values:
 *     @arg LPUART_INT_WUF Wake-Up Interrupt
 *     @arg LPUART_INT_FIFO_NE FIFO Non-Empty Interrupt
 *     @arg LPUART_INT_FIFO_HF FIFO Half Full Interrupt
 *     @arg LPUART_INT_FIFO_FU FIFO Full Interrupt Enable
 *     @arg LPUART_INT_FIFO_OV FIFO Overflow Interrupt
 *     @arg LPUART_INT_TXC TX Complete Interrupt
 *     @arg LPUART_INT_PE Parity Check Error Interrupt
 */
void LPUART_ClrIntPendingBit(uint16_t LPUART_INT)
{
    uint16_t itmask = 0x00;
    /* Check the parameters */
    assert_param(IS_LPUART_CLR_INT(LPUART_INT));

    itmask      = ((uint8_t)LPUART_INT) & 0xFF;
    LPUART->STS = (uint16_t)itmask;
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
