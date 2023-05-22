/*!
 * @file        apm32s10x_usart.c
 *
 * @brief       This file provides all the USART firmware functions
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32s10x_usart.h"
#include "apm32s10x_rcm.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup USART_Driver USART Driver
  @{
*/

/** @defgroup USART_Functions Functions
  @{
*/

/*!
 * @brief     Reset usart peripheral registers to their default reset values
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_Reset(USART_T* usart)
{
    if (USART1 == usart)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_USART1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_USART1);
    }
    else if (USART2 == usart)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_USART2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_USART2);
    }
    else if (USART3 == usart)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_USART3);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_USART3);
    }
}

/*!
 * @brief     Configure the USART peripheral according to the specified parameters in the usartConfig
 *
 * @param     uart: Select the USART or the UART peripheral
 *
 * @param     usartConfig: pointer to a USART_Config_T structure
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_Config(USART_T* uart, USART_Config_T* usartConfig)
{
    uint32_t temp, fCLK, intDiv, fractionalDiv;

    temp = uart->CTRL1;
    temp &= 0xE9F3;
    temp |= (uint32_t)usartConfig->mode | \
            (uint32_t)usartConfig->parity | \
            (uint32_t)usartConfig->wordLength;
    uart->CTRL1 = temp;

    temp = uart->CTRL2;
    temp &= 0xCFFF;
    temp |= usartConfig->stopBits;
    uart->CTRL2 = temp;

    temp = uart->CTRL3;
    temp &= 0xFCFF;
    temp |= (uint32_t)usartConfig->hardwareFlow;
    uart->CTRL3 = temp;

    if (uart == USART1)
    {
        RCM_ReadPCLKFreq(NULL, &fCLK);
    }
    else
    {
        RCM_ReadPCLKFreq(&fCLK, NULL);
    }

    intDiv = ((25 * fCLK) / (4 * (usartConfig->baudRate)));
    temp = (intDiv / 100) << 4;
    fractionalDiv = intDiv - (100 * (temp >> 4));
    temp |= ((((fractionalDiv * 16) + 50) / 100)) & ((uint8_t)0x0F);

    uart->BR = temp;
}

/*!
 * @brief     Fill each USART_InitStruct member with its default value
 *
 * @param     usartConfig: pointer to a USART_Config_T structure which will be initialized
 *
 * @retval    None
 */
void USART_ConfigStructInit(USART_Config_T* usartConfig)
{
    usartConfig->baudRate = 9600;
    usartConfig->wordLength = USART_WORD_LEN_8B;
    usartConfig->stopBits = USART_STOP_BIT_1;
    usartConfig->parity = USART_PARITY_NONE ;
    usartConfig->mode = USART_MODE_TX_RX;
    usartConfig->hardwareFlow = USART_HARDWARE_FLOW_NONE;
}

/*!
 * @brief     Configure communication clock
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     clockConfig: Pointer to a USART_clockConfig_T structure
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ConfigClock(USART_T* usart, USART_ClockConfig_T* clockConfig)
{
    usart->CTRL2_B.CLKEN   = clockConfig->clock;
    usart->CTRL2_B.CPHA    = clockConfig->phase;
    usart->CTRL2_B.CPOL    = clockConfig->polarity;
    usart->CTRL2_B.LBCPOEN = clockConfig->lastBit;
}

/*!
 * @brief     Fill each clockConfig member with its default value
 *
 * @param     clockConfig: Pointer to a USART_clockConfig_T structure
 *
 * @retval    None
 *
 */
void USART_ConfigClockStructInit(USART_ClockConfig_T* clockConfig)
{
    clockConfig->clock     = USART_CLKEN_DISABLE;
    clockConfig->phase     = USART_CLKPHA_1EDGE;
    clockConfig->polarity  = USART_CLKPOL_LOW;
    clockConfig->lastBit   = USART_LBCP_DISABLE;
}

/*!
 * @brief     Enable the specified USART peripheral
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_Enable(USART_T* usart)
{
    usart->CTRL1_B.UEN = BIT_SET;
}

/*!
 * @brief     Disable the specified USART peripheral
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_Disable(USART_T* usart)
{
    usart->CTRL1_B.UEN = BIT_RESET;
}

/*!
 * @brief     Enable the USART DMA interface
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     dmaReq: Specifies the DMA request
 *              This parameter can be one of the following values:
 *              @arg USART_DMA_TX:    USART DMA receive request
 *              @arg USART_DMA_RX:    USART DMA transmit request
 *              @arg USART_DMA_TX_RX: USART DMA transmit/receive request
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableDMA(USART_T* usart, USART_DMA_T dmaReq)
{
    usart->CTRL3 |= dmaReq;
}

/*!
 * @brief     Disable the USART DMA interface
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     dmaReq: Specifies the DMA request
 *              This parameter can be one of the following values:
 *              @arg USART_DMA_TX:    USART DMA receive request
 *              @arg USART_DMA_RX:    USART DMA transmit request
 *              @arg USART_DMA_TX_RX: USART DMA transmit/receive request
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableDMA(USART_T* usart, USART_DMA_T dmaReq)
{
    usart->CTRL3 &= (uint32_t)~dmaReq;
}

/*!
 * @brief     Configure the address of the USART node
 *
 * @param     usart:   Select the USART or the UART peripheral
 *
 * @param     address: Indicates the address of the USART node
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_Address(USART_T* usart, uint8_t address)
{
    usart->CTRL2_B.ADDR = address;
}

/*!
 * @brief     Select the USART WakeUp method.
 *
 * @param     usart:  Select the USART or the UART peripheral
 *
 * @param     wakeup: Specifies the selected USART auto baud rate method
 *              This parameter can be one of the following values:
 *              @arg USART_WAKEUP_IDLE_LINE:    WakeUp by an idle line detection
 *              @arg USART_WAKEUP_ADDRESS_MARK: WakeUp by an address mark
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ConfigWakeUp(USART_T* usart, USART_WAKEUP_T wakeup)
{
    usart->CTRL1_B.WUPMCFG = wakeup;
}

/*!
 * @brief     Enable USART Receiver in mute mode
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableMuteMode(USART_T* usart)
{
    usart->CTRL1_B.RXMUTEEN = BIT_SET;
}

/*!
 * @brief     Disable USART Receiver in active mode
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableMuteMode(USART_T* usart)
{
    usart->CTRL1_B.RXMUTEEN = BIT_RESET;
}

/*!
 * @brief     Set the USART LIN Break detection length
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     length: Specifies the LIN break detection length
 *              This parameter can be one of the following values:
 *              @arg USART_LBDL_10B: 10-bit break detection
 *              @arg USART_LBDL_10B: 11-bit break detection
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ConfigLINBreakDetectLength(USART_T* usart, USART_LBDL_T length)
{
    usart->CTRL2_B.LBDLCFG = length;
}

/*!
 * @brief     Enable the USART LIN MODE
 *
 * @param     usart:   Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableLIN(USART_T* usart)
{
    usart->CTRL2_B.LINMEN = BIT_SET;
}

/*!
 * @brief     Disable the USART LIN MODE
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableLIN(USART_T* usart)
{
    usart->CTRL2_B.LINMEN = BIT_RESET;
}

/*!
 * @brief     Enable USART transmitter
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableTx(USART_T* usart)
{
    usart->CTRL1_B.TXEN = BIT_SET;
}

/*!
 * @brief     Disable USART transmitter
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableTx(USART_T* usart)
{
    usart->CTRL1_B.TXEN = BIT_RESET;
}

/*!
 * @brief     Enable USART receiver
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableRx(USART_T* usart)
{
    usart->CTRL1_B.RXEN = BIT_SET;
}

/*!
 * @brief     Disable USART receiver
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableRx(USART_T* usart)
{
    usart->CTRL1_B.RXEN = BIT_RESET;
}

/*!
 * @brief     Transmit single data
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     data:  the data to transmit
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_TxData(USART_T* usart, uint16_t data)
{
    usart->DATA_B.DATA = data;
}

/*!
 * @brief     Return the most recent received data
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
uint16_t USART_RxData(USART_T* usart)
{
    return (uint16_t)usart->DATA_B.DATA;
}

/*!
 * @brief     Transmit break characters
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_TxBreak(USART_T* usart)
{
    usart->CTRL1_B.TXBF = BIT_SET;
}

/*!
 * @brief     Set the specified USART guard time
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     guardTime: Specifies the guard time
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ConfigGuardTime(USART_T* usart, uint8_t guardTime)
{
    usart->GTPSC_B.GRDT = guardTime;
}

/*!
 * @brief     Set the system clock divider number
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     div:   specifies the divider number
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ConfigPrescaler(USART_T* usart, uint8_t div)
{
    usart->GTPSC_B.PSC = div;
}

/*!
 * @brief     Enable the USART Smart Card mode
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note
 */
void USART_EnableSmartCard(USART_T* usart)
{
    usart->CTRL3_B.SCEN = BIT_SET;
}

/*!
 * @brief     Disable the USART Smart Card mode
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note
 */
void USART_DisableSmartCard(USART_T* usart)
{
    usart->CTRL3_B.SCEN = BIT_RESET;
}

/*!
 * @brief     Enable NACK transmission
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note
 */
void USART_EnableSmartCardNACK(USART_T* usart)
{
    usart->CTRL3_B.SCNACKEN = BIT_SET;
}

/*!
 * @brief     Disable NACK transmission
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note
 */
void USART_DisableSmartCardNACK(USART_T* usart)
{
    usart->CTRL3_B.SCNACKEN = BIT_RESET;
}

/*!
 * @brief     Enable USART Half Duplex communication
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableHalfDuplex(USART_T* usart)
{
    usart->CTRL3_B.HDEN = BIT_SET;
}

/*!
 * @brief     Disable USART Half Duplex communication
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableHalfDuplex(USART_T* usart)
{
    usart->CTRL3_B.HDEN = BIT_RESET;
}

/*!
 * @brief     Configure the USART's IrDA interface
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     IrDAMode: Specifies the IrDA mode
 *              This parameter can be one of the following values:
 *              @arg USART_IRDALP_NORMAL:   Normal
 *              @arg USART_IRDALP_LOWPOWER: Low-Power
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ConfigIrDA(USART_T* usart, USART_IRDALP_T IrDAMode)
{
    usart->CTRL3_B.IRLPEN = IrDAMode;
}

/*!
 * @brief     Enable the USART's IrDA interface
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableIrDA(USART_T* usart)
{
    usart->CTRL3_B.IREN = BIT_SET;
}

/*!
 * @brief     Disable the USART's IrDA interface
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableIrDA(USART_T* usart)
{
    usart->CTRL3_B.IREN = BIT_RESET;
}

/*!
 * @brief     Enable the specified USART interrupts
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     interrupt: Specifies the USART interrupts sources
 *              The parameter can be one of following values:
 *              @arg USART_INT_PE:    Parity error interrupt
 *              @arg USART_INT_TXBE:  Tansmit data buffer empty interrupt
 *              @arg USART_INT_TXC:   Transmission complete interrupt
 *              @arg USART_INT_RXBNE: Receive data buffer not empty interrupt
 *              @arg USART_INT_IDLE:  Idle line detection interrupt
 *              @arg USART_INT_LBD:   LIN break detection interrupt
 *              @arg USART_INT_CTS:   CTS change interrupt
 *              @arg USART_INT_ERR:   Error interrupt(Frame error, noise error, overrun error)
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_EnableInterrupt(USART_T* usart, USART_INT_T interrupt)
{
    uint32_t temp;

    temp = (uint32_t)(interrupt & 0xffff);

    if (interrupt & 0x10000)
    {
        usart->CTRL1 |= temp;
    }

    if (interrupt & 0x20000)
    {
        usart->CTRL2 |= temp;
    }

    if (interrupt & 0x40000)
    {
        usart->CTRL3 |= temp;
    }
}

/*!
 * @brief     Disable the specified USART interrupts
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     interrupt: Specifies the USART interrupts sources
 *              The parameter can be one of following values:
 *              @arg USART_INT_PE:    Parity error interrupt
 *              @arg USART_INT_TXBE:  Tansmit data buffer empty interrupt
 *              @arg USART_INT_TXC:   Transmission complete interrupt
 *              @arg USART_INT_RXBNE: Receive data buffer not empty interrupt
 *              @arg USART_INT_IDLE:  Idle line detection interrupt
 *              @arg USART_INT_LBD:   LIN break detection interrupt
 *              @arg USART_INT_CTS:   CTS change interrupt
 *              @arg USART_INT_ERR:   Error interrupt(Frame error, noise error, overrun error)
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_DisableInterrupt(USART_T* usart, USART_INT_T interrupt)
{
    uint32_t temp;

    temp = (uint32_t)~(interrupt & 0xffff);

    if (interrupt & 0x10000)
    {
        usart->CTRL1 &= temp;
    }

    if (interrupt & 0x20000)
    {
        usart->CTRL2 &= temp;
    }

    if (interrupt & 0x40000)
    {
        usart->CTRL3 &= temp;
    }
}

/*!
 * @brief     Read the specified USART flag
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     flag: Specifies the flag to check
 *              The parameter can be one of following values:
 *              @arg USART_FLAG_CTS:   CTS Change flag
 *              @arg USART_FLAG_LBD:   LIN Break detection flag
 *              @arg USART_FLAG_TXBE:  Transmit data buffer empty flag
 *              @arg USART_FLAG_TXC:   Transmission Complete flag
 *              @arg USART_FLAG_RXBNE: Receive data buffer not empty flag
 *              @arg USART_FLAG_IDLE:  Idle Line detection flag
 *              @arg USART_FLAG_OVRE:  OverRun Error flag
 *              @arg USART_FLAG_NE:    Noise Error flag
 *              @arg USART_FLAG_FE:    Framing Error flag
 *              @arg USART_FLAG_PE:    Parity Error flag
 *
 * @retval    The new state of flag (SET or RESET)
 *
 * @note      The usart can be USART1, USART2, USART3
 */
uint8_t USART_ReadStatusFlag(USART_T* usart, USART_FLAG_T flag)
{
    return (usart->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the USARTx's pending flags
 *
 * @param     usart:   Select the USART or the UART peripheral
 *
 * @param     flag:  Specifies the flag to clear
 *              The parameter can be one of following values:
 *              @arg USART_FLAG_CTS:   CTS Change flag
 *              @arg USART_FLAG_LBD:   LIN Break detection flag
 *              @arg USART_FLAG_TXC:   Transmission Complete flag
 *              @arg USART_FLAG_RXBNE: Receive data buffer not empty flag
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ClearStatusFlag(USART_T* usart, USART_FLAG_T flag)
{
    usart->STS &= (uint32_t)~flag;
}

/*!
 * @brief     Read the specified USART interrupt flag
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     flag:  Specifies the USART interrupt source to check
 *              The parameter can be one of following values:
 *              @arg USART_INT_TXBE:  Tansmit data buffer empty interrupt
 *              @arg USART_INT_TXC:   Transmission complete interrupt
 *              @arg USART_INT_RXBNE: Receive data buffer not empty interrupt
 *              @arg USART_INT_IDLE:  Idle line detection interrupt
 *              @arg USART_INT_LBD:   LIN break detection interrupt
 *              @arg USART_INT_CTS:   CTS change interrupt
 *              @arg USART_INT_OVRE:  OverRun Error interruptpt
 *              @arg USART_INT_NE:    Noise Error interrupt
 *              @arg USART_INT_FE:    Framing Error interrupt
 *              @arg USART_INT_PE:    Parity error interrupt
 *
 * @retval    The new state of flag (SET or RESET)
 *
 * @note      The usart can be USART1, USART2, USART3
 */
uint8_t USART_ReadIntFlag(USART_T* usart, USART_INT_T flag)
{
    uint32_t itFlag, srFlag;

    if (flag & 0x10000)
    {
        itFlag = usart->CTRL1 & flag & 0xffff;
    }
    else if (flag & 0x20000)
    {
        itFlag = usart->CTRL2 & flag & 0xffff;
    }
    else
    {
        itFlag = usart->CTRL3 & flag & 0xffff;
    }

    srFlag = flag >> 24;
    srFlag = (uint32_t)(1 << srFlag);
    srFlag = usart->STS & srFlag;

    if (srFlag && itFlag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief     Clears the USART interrupt pending bits
 *
 * @param     usart: Select the USART or the UART peripheral
 *
 * @param     flag:  Specifies the interrupt pending bit to clear
 *              The parameter can be one of following values:
 *              @arg USART_INT_RXBNE: Receive data buffer not empty interrupt
 *              @arg USART_INT_TXC:   Transmission complete interrupt
 *              @arg USART_INT_LBD:   LIN break detection interrupt
 *              @arg USART_INT_CTS:   CTS change interrupt
 *
 * @retval    None
 *
 * @note      The usart can be USART1, USART2, USART3
 */
void USART_ClearIntFlag(USART_T* usart, USART_INT_T flag)
{
    uint32_t srFlag;

    srFlag = flag >> 24;
    srFlag = (uint32_t)(1 << srFlag);

    usart->STS &= (uint32_t)~srFlag;
}

/**@} end of group USART_Functions */
/**@} end of group USART_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */
