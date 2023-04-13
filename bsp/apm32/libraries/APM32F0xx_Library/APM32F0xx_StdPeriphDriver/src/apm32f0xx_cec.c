/*!
 * @file        apm32f0xx_cec.c
 *
 * @brief       This file contains all the functions for the CEC peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f0xx_cec.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CEC_Driver
  @{
*/

/** @defgroup CEC_Macros Macros
  @{
*/

/**@} end of group CEC_Macros */

/** @defgroup CEC_Enumerations Enumerations
  @{
*/

/**@} end of group CEC_Enumerations */

/** @defgroup CEC_Structures Structures
  @{
*/

/**@} end of group CEC_Structures */

/** @defgroup CEC_Variables Variables
  @{
*/

/**@} end of group CEC_Variables */

/** @defgroup CEC_Functions Functions
  @{
*/

/*!
 * @brief    Reset CEC peripheral registers to their default values.
 *
 * @param    None
 *
 * @retval   None
 */
void CEC_Reset(void)
{
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CEC);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_CEC);
}

/*!
 * @brief    Configs the CEC peripheral according to the specified parameters
 *           in the cecConfig.
 *
 * @param    cecConfig: pointer to an CEC_Config_T structure that is used to
 *           the configuration information for the specified CEC peripheral.
 *
 * @retval   None
 *
 * @note     The CEC parameters must be configured before enabling the CEC peripheral.
 */
void CEC_Config(CEC_Config_T* cecConfig)
{
    CEC->CFG_B.SFTCFG    = cecConfig->signalFreeTime;
    CEC->CFG_B.RXTCFG   = cecConfig->RxTolerance;
    CEC->CFG_B.RXSBRERR = cecConfig->stopReception;
    CEC->CFG_B.GEBRERR  = cecConfig->bitRisingError;
    CEC->CFG_B.GELBPERR = cecConfig->longPeriodError;
    CEC->CFG_B.AEBGIB = cecConfig->broadcastrNoGen;
    CEC->CFG_B.SFTOB  = cecConfig->signalFreeTimeOption;
}

/*!
 * @brief    Fills each CEC_InitStruct member with its default value.
 *
 * @param    cecConfig: pointer to a CEC_InitTypeDef structure which will
 *           be initialized.
 *
 * @retval   None
 */
void CEC_ConfigStructInit(CEC_Config_T* cecConfig)
{
    cecConfig->signalFreeTime     = CEC_SINGANL_FREETIME_STANDARD;
    cecConfig->RxTolerance        = CEC_RX_TOLERANCE_STANDARD;
    cecConfig->stopReception      = CEC_STOP_RECEPTION_OFF;
    cecConfig->bitRisingError     = CEC_BIT_RISING_ERR_OFF;
    cecConfig->longPeriodError    = CEC_LONG_PERIOD_ERR_OFF;
    cecConfig->broadcastrNoGen    = CEC_BROADCAST_NO_ERR_OFF;
    cecConfig->signalFreeTimeOption  = CEC_SIGNAL_FREETIME_OPTION_OFF;
}

/*!
 * @brief    Enables the CEC peripheral.
 *
 * @param    None
 *
 * @retval   None
 */
void CEC_Enable(void)
{
    CEC->CTRL_B.CECEN = SET;
}

/*!
 * @brief    Disables the CEC peripheral.
 *
 * @param    None
 *
 * @retval   None
 */
void CEC_Disable(void)
{
    CEC->CTRL_B.CECEN = RESET;
}

/*!
 * @brief    Enables the CEC Listen Mode.
 *
 * @param    None
 *
 * @retval   None
 */
void CEC_EnableListenMode(void)
{
    CEC->CFG_B.LMODSEL = SET;
}

/*!
 * @brief    Disables the CEC Listen Mode.
 *
 * @param    None
 *
 * @retval   None
 */
void CEC_DisableListenMode(void)
{
    CEC->CFG_B.LMODSEL = RESET;
}

/*!
 * @brief    Defines the Own Address of the CEC device.
 *
 * @param    ownAddress: The CEC own address.
 *
 * @retval   None
 */
void CEC_ConfigOwnAddress(uint8_t ownAddress)
{
    CEC->CFG_B.OACFG |= (1 << ownAddress);
}

/*!
 * @brief    Clears the Own Address of the CEC device.
 *
 * @param    CEC_OwnAddress: The CEC own address.
 *
 * @retval   None
 */
void CEC_ClearQwnAddress(void)
{
    CEC->CFG = 0x00;
}

/*!
 * @brief    Transmits single data through the CEC peripheral.
 *
 * @param    Data: the data to transmit.
 *
 * @retval   None
 */
void CEC_TxData(uint8_t Data)
{
    CEC->TXDATA = Data;
}

/*!
 * @brief    Returns the most recent received data by the CEC peripheral.
 *
 * @param    None
 *
 * @retval   The received data.
 */
uint8_t CEC_RxData(void)
{
    return (uint8_t)(CEC->RXDATA);
}

/*!
 * @brief    Starts a new message.
 *
 * @param    None
 *
 * @retval   None
 */
void CEC_StartNewMessage(void)
{
    CEC->CTRL_B.TXSM = SET;
}

/*!
 * @brief  Transmits message with an EOM bit.
 *
 * @param  None
 *
 * @retval None
 */
void CEC_CompleteMessage(void)
{
    CEC->CTRL_B.TXEM = SET;
}

/*!
 * @brief    Enables the selected CEC interrupts.
 *
 * @param    flag: specifies the CEC interrupt source to be enabled.
 *            This parameter can be any combination of the following values:
 *              @arg CEC_INT_RXBR     Rx-Byte Received
 *              @arg CEC_INT_RXEND    End Of Reception
 *              @arg CEC_INT_RXOVR    Rx Overrun.
 *              @arg CEC_INT_BRE      Rx Bit Rising Error
 *              @arg CEC_INT_SBPE     Rx Short period Error
 *              @arg CEC_INT_LBPE     Rx Long period Error
 *              @arg CEC_INT_RXACKE   Rx-Missing Acknowledge
 *              @arg CEC_INT_ARBLST   Arbitration Lost
 *              @arg CEC_INT_TXBR     Tx-Byte Request.
 *              @arg CEC_INT_TXEND    End of Transmission
 *              @arg CEC_INT_TXUDR    Tx-Buffer Underrun.
 *              @arg CEC_INT_TXERR    Tx Error.
 *              @arg CEC_INT_TXACKE   Tx Missing acknowledge Error
 *
 * @retval   None
 */
void CEC_EnableInterrupt(uint32_t interrupt)
{
    CEC->INTEN |= (uint32_t)interrupt;
}

/*!
 * @brief    Disables the selected CEC interrupts.
 *
 * @param    flag: specifies the CEC interrupt source to be enabled.
 *            This parameter can be any combination of the following values:
 *              @arg CEC_INT_RXBR     Rx-Byte Received
 *              @arg CEC_INT_RXEND    End Of Reception
 *              @arg CEC_INT_RXOVR    Rx Overrun.
 *              @arg CEC_INT_BRE      Rx Bit Rising Error
 *              @arg CEC_INT_SBPE     Rx Short period Error
 *              @arg CEC_INT_LBPE     Rx Long period Error
 *              @arg CEC_INT_RXACKE   Rx-Missing Acknowledge
 *              @arg CEC_INT_ARBLST   Arbitration Lost
 *              @arg CEC_INT_TXBR     Tx-Byte Request.
 *              @arg CEC_INT_TXEND    End of Transmission
 *              @arg CEC_INT_TXUDR    Tx-Buffer Underrun.
 *              @arg CEC_INT_TXERR    Tx Error.
 *              @arg CEC_INT_TXACKE   Tx Missing acknowledge Error
 *
 * @retval   None
 */
void CEC_DisableInterrupt(uint32_t interrupt)
{
    CEC->INTEN &= ~(uint32_t)interrupt;
}

/*!
 * @brief    Read the CEC flag status.
 *
 * @param    flag: specifies the CEC interrupt source to be enabled.
 *            This parameter can be any combination of the following values:
 *              @arg CEC_FLAG_RXBR      Rx-Byte Received
 *              @arg CEC_FLAG_RXEND     End Of Reception
 *              @arg CEC_FLAG_RXOVR     Rx Overrun.
 *              @arg CEC_FLAG_BRE       Rx Bit Rising Error
 *              @arg CEC_FLAG_SBPE      Rx Short period Error
 *              @arg CEC_FLAG_LBPE      Rx Long period Error
 *              @arg CEC_FLAG_RXACKE    Rx-Missing Acknowledge
 *              @arg CEC_FLAG_ARBLST    Arbitration Lost
 *              @arg CEC_FLAG_TXBR      Tx-Byte Request.
 *              @arg CEC_FLAG_TXEND     End of Transmission
 *              @arg CEC_FLAG_TXUDR     Tx-Buffer Underrun.
 *              @arg CEC_FLAG_TXERR     Tx Error.
 *              @arg CEC_FLAG_TXACKE    Tx Missing acknowledge Error
 *
 * @retval   The new state of CEC_FLAG (SET or RESET)
 */
uint8_t CEC_ReadStatusFlag(uint32_t flag)
{
    uint32_t status;

    status = (uint32_t)(CEC->STS & flag);

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief    Clears the CEC's pending flags.
 *
 * @param    flag: specifies the flag to clear.
 *            This parameter can be any combination of the following values:
 *              @arg CEC_FLAG_RXBR      Rx-Byte Received
 *              @arg CEC_FLAG_RXEND     End Of Reception
 *              @arg CEC_FLAG_RXOVR     Rx Overrun.
 *              @arg CEC_FLAG_BRE       Rx Bit Rising Error
 *              @arg CEC_FLAG_SBPE      Rx Short period Error
 *              @arg CEC_FLAG_LBPE      Rx Long period Error
 *              @arg CEC_FLAG_RXACKE    Rx-Missing Acknowledge
 *              @arg CEC_FLAG_ARBLST    Arbitration Lost
 *              @arg CEC_FLAG_TXBR      Tx-Byte Request.
 *              @arg CEC_FLAG_TXEND     End of Transmission
 *              @arg CEC_FLAG_TXUDR     Tx-Buffer Underrun.
 *              @arg CEC_FLAG_TXERR     Tx Error.
 *              @arg CEC_FLAG_TXACKE    Tx Missing acknowledge Error
 *
 * @retval   None
 */
void CEC_ClearStatusFlag(uint32_t flag)
{
    CEC->STS = flag;
}

/*!
 * @brief    Checks whether the specified CEC interrupt has occurred or not.
 *
 * @param    flag: specifies the CEC interrupt source to check.
 *            This parameter can be one of the following values:
 *              @arg CEC_INT_RXBR     Rx-Byte Received
 *              @arg CEC_INT_RXEND    End Of Reception
 *              @arg CEC_INT_RXOVR    Rx Overrun.
 *              @arg CEC_INT_BRE      Rx Bit Rising Error
 *              @arg CEC_INT_SBPE     Rx Short period Error
 *              @arg CEC_INT_LBPE     Rx Long period Error
 *              @arg CEC_INT_RXACKE   Rx-Missing Acknowledge
 *              @arg CEC_INT_ARBLST   Arbitration Lost
 *              @arg CEC_INT_TXBR     Tx-Byte Request.
 *              @arg CEC_INT_TXEND    End of Transmission
 *              @arg CEC_INT_TXUDR    Tx-Buffer Underrun.
 *              @arg CEC_INT_TXERR    Tx Error.
 *              @arg CEC_INT_TXACKE   Tx Missing acknowledge Error
 *
 * @retval   The new state of Flag (SET or RESET).
 */
uint8_t CEC_ReadIntFlag(uint16_t flag)
{
    uint32_t intEnable;
    uint32_t intStatus;
    intEnable = (CEC->INTEN & flag);
    intStatus = (CEC->STS & flag);
    if ((intStatus != (uint32_t)RESET) && intEnable)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief    Clears the CEC's interrupt flag.
 *
 * @param    flag: specifies the CEC interrupt flag to clear.
 *            This parameter can be any combination of the following values:
 *              @arg CEC_INT_RXBR     Rx-Byte Received
 *              @arg CEC_INT_RXEND    End Of Reception
 *              @arg CEC_INT_RXOVR    Rx Overrun.
 *              @arg CEC_INT_BRE      Rx Bit Rising Error
 *              @arg CEC_INT_SBPE     Rx Short period Error
 *              @arg CEC_INT_LBPE     Rx Long period Error
 *              @arg CEC_INT_RXACKE   Rx-Missing Acknowledge
 *              @arg CEC_INT_ARBLST   Arbitration Lost
 *              @arg CEC_INT_TXBR     Tx-Byte Request.
 *              @arg CEC_INT_TXEND    End of Transmission
 *              @arg CEC_INT_TXUDR    Tx-Buffer Underrun.
 *              @arg CEC_INT_TXERR    Tx Error.
 *              @arg CEC_INT_TXACKE   Tx Missing acknowledge Error
 *
 * @retval   None
 */
void CEC_ClearIntFlag(uint16_t flag)
{
    CEC->STS = flag;
}

/**@} end of group CEC_Functions */
/**@} end of group CEC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
