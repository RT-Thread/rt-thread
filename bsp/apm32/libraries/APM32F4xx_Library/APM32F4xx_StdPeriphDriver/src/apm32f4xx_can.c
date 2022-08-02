/*!
 * @file        apm32f4xx_can.c
 *
 * @brief       This file provides all the CAN firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
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

#include "apm32f4xx_can.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup CAN_Driver
  * @brief CAN driver modules
  @{
*/

/** @defgroup CAN_Functions
  @{
*/

/*!
 * @brief     Reset CAN registers
 *
 * @param     can: Select the CAN peripheral.
 *
 * @retval    None
 */
void CAN_Reset(CAN_T *can)
{
    if (can == CAN1)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_CAN1);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_CAN1);
    }
    else if (can == CAN2)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_CAN2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_CAN2);
    }
}

/*!
 * @brief     Initialization parameter configuration
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     canConfig: Point to a CAN_Config_T structure.
 *
 * @retval    ERROR or SUCCEESS
 */
uint8_t CAN_Config(CAN_T *can, CAN_Config_T *canConfig)
{
    uint8_t  initStatus = ERROR;
    uint32_t wait_ack = 0x00000000;

    /* Exit from sleep mode */
    can->MCTRL_B.SLEEPREQ = BIT_RESET;
    /* Request initialisation */
    can->MCTRL_B.INITREQ = BIT_SET;

    /* Wait the acknowledge */
    while (((can->MSTS_B.INITFLG) != BIT_SET) && (wait_ack != 0x0000FFFF))
    {
        wait_ack++;
    }
    /* Check acknowledge */
    if (((can->MSTS_B.INITFLG) != BIT_SET))
    {
        initStatus = ERROR;
    }
    else
    {
        if (canConfig->autoBusOffManage == ENABLE)
        {
            can->MCTRL_B.ALBOFFM = BIT_SET;
        }
        else
        {
            can->MCTRL_B.ALBOFFM = BIT_RESET;
        }

        if (canConfig->autoWakeUpMode == ENABLE)
        {
            can->MCTRL_B.AWUPCFG = BIT_SET;
        }
        else
        {
            can->MCTRL_B.AWUPCFG = BIT_RESET;
        }

        if (canConfig->nonAutoRetran == ENABLE)
        {
            can->MCTRL_B.ARTXMD = BIT_SET;
        }
        else
        {
            can->MCTRL_B.ARTXMD = BIT_RESET;
        }

        if (canConfig->rxFIFOLockMode == ENABLE)
        {
            can->MCTRL_B.RXFLOCK = BIT_SET;
        }
        else
        {
            can->MCTRL_B.RXFLOCK = BIT_RESET;
        }

        if (canConfig->txFIFOPriority == ENABLE)
        {
            can->MCTRL_B.TXFPCFG = BIT_SET;
        }
        else
        {
            can->MCTRL_B.TXFPCFG = BIT_RESET;
        }

        /* Set the bit timing register */
        can->BITTIM &= (uint32_t)0x3fffffff;
        can->BITTIM |= (uint32_t)canConfig->mode << 30;
        can->BITTIM_B.RSYNJW  = canConfig->syncJumpWidth;
        can->BITTIM_B.TIMSEG1 = canConfig->timeSegment1;
        can->BITTIM_B.TIMSEG2 = canConfig->timeSegment2;
        can->BITTIM_B.BRPSC   = canConfig->prescaler - 1;

        /* Request leave initialisation */
        can->MCTRL_B.INITREQ = BIT_RESET;

        wait_ack = 0;
        /* Wait the acknowledge */
        while (((can->MSTS_B.INITFLG) != BIT_RESET) && (wait_ack != 0x0000FFFF))
        {
            wait_ack++;
        }
        /* Check acknowledge */
        if (((can->MSTS_B.INITFLG) != BIT_RESET))
        {
            initStatus = ERROR;
        }
        else
        {
            initStatus = SUCCESS;
        }
    }
    return initStatus;
}

/*!
 * @brief     Congig the CAN peripheral according to the specified parameters in the filterConfig.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     filterConfig :Point to a CAN_FilterConfig_T structure.
 *
 * @retval    None
 */
void CAN_ConfigFilter(CAN_FilterConfig_T *filterConfig)
{
    CAN1->FCTRL_B.FINITEN = BIT_SET;

    CAN1->FACT &= ~(1 << filterConfig->filterNumber);

    /* Filter Scale */
    if (filterConfig->filterScale == CAN_FILTER_SCALE_16BIT)
    {
        /* 16-bit scale for the filter */
        CAN1->FSCFG &= ~(1 << filterConfig->filterNumber);

        CAN1->sFilterRegister[filterConfig->filterNumber].FBANK1 =
            ((0x0000FFFF & filterConfig->filterMaskIdLow) << 16) |
            (0x0000FFFF & filterConfig->filterIdLow);

        CAN1->sFilterRegister[filterConfig->filterNumber].FBANK2 =
            ((0x0000FFFF & filterConfig->filterMaskIdHigh) << 16) |
            (0x0000FFFF & filterConfig->filterIdHigh);
    }

    if (filterConfig->filterScale == CAN_FILTER_SCALE_32BIT)
    {
        CAN1->FSCFG |= (1 << filterConfig->filterNumber);

        CAN1->sFilterRegister[filterConfig->filterNumber].FBANK1 =
            ((0x0000FFFF & filterConfig->filterIdHigh) << 16) |
            (0x0000FFFF & filterConfig->filterIdLow);

        CAN1->sFilterRegister[filterConfig->filterNumber].FBANK2 =
            ((0x0000FFFF & filterConfig->filterMaskIdHigh) << 16) |
            (0x0000FFFF & filterConfig->filterMaskIdLow);
    }

    /* Filter Mode */
    if (filterConfig->filterMode == CAN_FILTER_MODE_IDMASK)
    {
        CAN1->FMCFG &= ~(1 << filterConfig->filterNumber);
    }
    else
    {
        CAN1->FMCFG |= (1 << filterConfig->filterNumber);
    }

    /* Filter FIFO assignment */
    if (filterConfig->filterFIFO == CAN_FILTER_FIFO_0)
    {
        CAN1->FFASS &= ~(1 << filterConfig->filterNumber);
    }
    if (filterConfig->filterFIFO == CAN_FILTER_FIFO_1)
    {
        CAN1->FFASS |= (1 << filterConfig->filterNumber);
    }

    /* Filter activation */
    if (filterConfig->filterActivation == ENABLE)
    {
        CAN1->FACT |= (1 << filterConfig->filterNumber);
    }
    CAN1->FCTRL_B.FINITEN = BIT_RESET;
}

/*!
 * @brief     Initialize a CAN_Config_T structure with the initial value.
 *
 * @param     canConfig :Point to a CAN_Config_T structure.
 *
 * @retval    None
 */
void CAN_ConfigStructInit(CAN_Config_T *canConfig)
{
    canConfig->autoBusOffManage = DISABLE;
    canConfig->autoWakeUpMode   = DISABLE;
    canConfig->nonAutoRetran    = DISABLE;
    canConfig->rxFIFOLockMode   = DISABLE;
    canConfig->txFIFOPriority   = DISABLE;
    canConfig->mode             = CAN_MODE_NORMAL;
    canConfig->syncJumpWidth    = CAN_SJW_1;
    canConfig->timeSegment1     = CAN_TIME_SEGMENT1_4;
    canConfig->timeSegment2     = CAN_TIME_SEGMENT2_3;
    canConfig->prescaler        = 1;
}

/*!
 * @brief     Select the start bank filter for slave CAN.
 *
 * @param     bankNum: the start slave bank filter from 1..27.
 *
 * @retval    None
 */
void CAN_SlaveStartBank(CAN_T *can, uint8_t bankNum)
{
    can->FCTRL_B.FINITEN = SET;
    can->FCTRL_B.CAN2BN  = bankNum;
    can->FCTRL_B.FINITEN = RESET;
}

/*!
 * @brief     Enables the DBG Freeze for CAN.
 *
 * @param     can: Select the CAN peripheral.
 *
 * @retval    None
 *
 * @note      None
 */
void CAN_EnableDBGFreeze(CAN_T *can)
{
    can->MCTRL_B.DBGFRZE = ENABLE;
}

/*!
 * @brief     Disable the DBG Freeze for CAN.
 *
 * @param     can: Select the CAN peripheral.
 *
 * @retval    None
 *
 * @note      None
 */
void CAN_DisableDBGFreeze(CAN_T *can)
{
    can->MCTRL_B.DBGFRZE = DISABLE;
}

/*!
 * @brief     Initiates the transmission of a message.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     TxMessage: pointer to a CAN_TX_MESSAGE structure.
 *
 * @retval    The number of the mailbox which is used for transmission or 3 if No mailbox is empty.
 */
uint8_t CAN_TxMessage(CAN_T *can, CAN_TxMessage_T *TxMessage)
{
    uint8_t transmit_milbox = 0;

    /* Select one empty transmit mailbox */
    if ((can->TXSTS & 0x04000000) == 0x04000000)
    {
        transmit_milbox = 0;
    }
    else if ((can->TXSTS & 0x08000000) == 0x08000000)
    {
        transmit_milbox = 1;
    }
    else if ((can->TXSTS & 0x10000000) == 0x10000000)
    {
        transmit_milbox = 2;
    }
    else
    {
        /* No mailbox is empty*/
        return 3;
    }

    /* Set up the Id */
    can->sTxMailBox[transmit_milbox].TXMID &= 0x00000001;
    if (TxMessage->typeID == CAN_TYPEID_STD)
    {
        can->sTxMailBox[transmit_milbox].TXMID |= (TxMessage->stdID << 21) | (TxMessage->remoteTxReq);
    }
    else
    {
        can->sTxMailBox[transmit_milbox].TXMID |= (TxMessage->extID << 3) | (TxMessage->typeID) | (TxMessage->remoteTxReq);
    }

    /* Set up the TXDLEN */
    TxMessage->dataLengthCode &= 0x0F;
    can->sTxMailBox[transmit_milbox].TXDLEN &= (uint32_t)0xFFFFFFF0;
    can->sTxMailBox[transmit_milbox].TXDLEN |= TxMessage->dataLengthCode;

    /* Set up the data field */
    can->sTxMailBox[transmit_milbox].TXMDL = ((uint32_t)TxMessage->data[3] << 24) | ((uint32_t)TxMessage->data[2] << 16)
            | ((uint32_t)TxMessage->data[1] << 8) | ((uint32_t)TxMessage->data[0]);
    can->sTxMailBox[transmit_milbox].TXMDH = ((uint32_t)TxMessage->data[7] << 24) | ((uint32_t)TxMessage->data[6] << 16)
            | ((uint32_t)TxMessage->data[5] << 8) | ((uint32_t)TxMessage->data[4]);
    /* Request transmission */
    can->sTxMailBox[transmit_milbox].TXMID |= 0x00000001;

    return transmit_milbox;
}

/*!
 * @brief     Checks the transmission of a message.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     TxMailbox: the number of the mailbox
 *              This parameter can be one of the following values:
 *              @arg CAN_TX_MAILBIX_0 : Tx mailbox0
 *              @arg CAN_TX_MAILBIX_1 : Tx mailbox1
 *              @arg CAN_TX_MAILBIX_2 : Tx mailbox2
 *
 * @retval    state: 0: Status of transmission is Failed
 *                   1: Status of transmission is Ok
 *                   2: transmit pending
 */
uint8_t CAN_TxMessageStatus(CAN_T *can, CAN_TX_MAILBIX_T TxMailbox)
{
    uint32_t state = 0;

    switch (TxMailbox)
    {
    case (CAN_TX_MAILBIX_0):
        state =   can->TXSTS & (0x00000001 | 0x00000002 | 0x04000000);
        break;
    case (CAN_TX_MAILBIX_1):
        state =   can->TXSTS & (0x00000100 | 0x00000200 | 0x08000000);
        break;
    case (CAN_TX_MAILBIX_2):
        state =   can->TXSTS & (0x00010000 | 0x00020000 | 0x10000000);
        break;
    default:
        state = 0;
        break;
    }
    switch (state)
    {
    /** transmit pending  */
    case (0x0):
        state = 2;
        break;
    /* transmit failed  */
    case (0x00000001 | 0x04000000):
        state = 0;
        break;
    case (0x00000100 | 0x08000000):
        state = 0;
        break;
    case (0x00010000 | 0x10000000):
        state = 0;
        break;
    /* transmit succeeded  */
    case (0x00000001 | 0x00000002 | 0x04000000):
        state = 1;
        break;
    case (0x00000100 | 0x00000200 | 0x08000000):
        state = 1;
        break;
    case (0x00010000 | 0x00020000 | 0x10000000):
        state = 1;
        break;
    default:
        state = 0;
        break;
    }
    return (uint8_t) state;
}

/*!
 * @brief     Cancels a transmit request.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     mailBox: the number of the mailbox
 *                     This parameter can be one of the following values:
 *                     @arg CAN_TX_MAILBIX_0 : Tx mailbox 0
 *                     @arg CAN_TX_MAILBIX_1 : Tx mailbox 1
 *                     @arg CAN_TX_MAILBIX_2 : Tx mailbox 2
 *
 * @retval    None
 */
void CAN_CancelTxMailbox(CAN_T *can, CAN_TX_MAILBIX_T TxMailbox)
{
    switch (TxMailbox)
    {
    case CAN_TX_MAILBIX_0:
        can->TXSTS_B.ABREQFLG0 = BIT_SET;
        break;
    case CAN_TX_MAILBIX_1:
        can->TXSTS_B.ABREQFLG1 = BIT_SET;
        break;
    case CAN_TX_MAILBIX_2:
        can->TXSTS_B.ABREQFLG2 = BIT_SET;
        break;
    default:
        break;
    }
}

/*!
 * @brief     Receives a message and save to a CAN_RxMessage_T structure.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     FIFONumber: Receive FIFO number.
 *                        This parameter can be one of the following values:
 *                        @arg CAN_RX_FIFO_0 : Receive FIFO 0
 *                        @arg CAN_RX_FIFO_1 : Receive FIFO 1
 *
 * @param     RxMessage: pointer to a structure to receive the message.
 *
 * @retval    None
 */
void CAN_RxMessage(CAN_T *can, CAN_RX_FIFO_T FIFONumber, CAN_RxMessage_T *RxMessage)
{
    /* Get the Id */
    RxMessage->typeID = ((uint8_t)0x04 & (can->sRxMailBox[FIFONumber].RXMID));
    if (RxMessage->typeID == CAN_TYPEID_STD)
    {
        RxMessage->stdID = (can->sRxMailBox[FIFONumber].RXMID >> 21) & 0x000007FF;
    }
    else
    {
        RxMessage->extID = (can->sRxMailBox[FIFONumber].RXMID >> 3) & 0x1FFFFFFF;
    }

    RxMessage->remoteTxReq = can->sRxMailBox[FIFONumber].RXMID_B.RFTXREQ;
    RxMessage->dataLengthCode = can->sRxMailBox[FIFONumber].RXDLEN_B.DLCODE;
    RxMessage->filterMatchIndex = can->sRxMailBox[FIFONumber].RXDLEN_B.FMIDX;
    /** Get the data field */
    RxMessage->data[0] = can->sRxMailBox[FIFONumber].RXMDL_B.DATABYTE0;
    RxMessage->data[1] = can->sRxMailBox[FIFONumber].RXMDL_B.DATABYTE1;
    RxMessage->data[2] = can->sRxMailBox[FIFONumber].RXMDL_B.DATABYTE2;
    RxMessage->data[3] = can->sRxMailBox[FIFONumber].RXMDL_B.DATABYTE3;
    RxMessage->data[4] = can->sRxMailBox[FIFONumber].RXMDH_B.DATABYTE4;
    RxMessage->data[5] = can->sRxMailBox[FIFONumber].RXMDH_B.DATABYTE5;
    RxMessage->data[6] = can->sRxMailBox[FIFONumber].RXMDH_B.DATABYTE6;
    RxMessage->data[7] = can->sRxMailBox[FIFONumber].RXMDH_B.DATABYTE7;

    if (FIFONumber == CAN_RX_FIFO_0)
    {
        can->RXF0_B.RFOM0 = BIT_SET;
    }
    else
    {
        can->RXF1_B.RFOM1 = BIT_SET;
    }
}

/*!
 * @brief     Releases the specified FIFO.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     FIFONumber: Receive FIFO number
 *                        This parameter can be one of the following values:
 *                        @arg CAN_RX_FIFO_0 : Receive FIFO 0
 *                        @arg CAN_RX_FIFO_1 : Receive FIFO 1
 *
 * @retval    None
 */
void CAN_ReleaseFIFO(CAN_T *can, CAN_RX_FIFO_T FIFONumber)
{
    if (FIFONumber == CAN_RX_FIFO_0)
    {
        can->RXF0_B.RFOM0 = BIT_SET;
    }
    else
    {
        can->RXF1_B.RFOM1 = BIT_SET;
    }
}

/*!
 * @brief     Returns the number of pending messages.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     FIFONumber: Receive FIFO number
 *                        This parameter can be one of the following values:
 *                        @arg CAN_RX_FIFO_0 : Receive FIFO 0
 *                        @arg CAN_RX_FIFO_1 : Receive FIFO 1
 *
 * @retval    The number of pending message.
 */
uint8_t CAN_PendingMessage(CAN_T *can, CAN_RX_FIFO_T FIFONumber)
{
    if (FIFONumber == CAN_RX_FIFO_0)
    {
        return  can->RXF0 & 0x03;
    }
    else
    {
        return  can->RXF1 & 0x03;
    }
}

/*!
 * @brief     Select the CAN Operation mode
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     operatingMode: CAN Operating Mode
 *                           This parameter can be one of the following values:
 *                           @arg CAN_OPERATING_MODE_INIT  : Initialization mode
 *                           @arg CAN_OPERATING_MODE_NORMAL: Normal mode
 *                           @arg CAN_OPERATING_MODE_SLEEP : sleep mode
 *
 * @retval    modeState:status of the requested mode
 *                      0:CAN failed entering the specific mode
 *                      1:CAN Succeed entering the specific mode
 */
uint8_t CAN_OperatingMode(CAN_T *can, CAN_OPERATING_MODE_T operatingMode)
{
    uint8_t states = 0;
    uint32_t time_out = 0x0000FFFF;

    if (operatingMode == CAN_OPERATING_MODE_INIT)
    {
        /** Request initialisation */
        can->MCTRL_B.SLEEPREQ = BIT_RESET;
        can->MCTRL_B.INITREQ = BIT_SET;

        /* Wait the acknowledge */
        while ((can->MSTS_B.INITFLG != BIT_SET && can->MSTS_B.SLEEPFLG != BIT_RESET) && (time_out != 0))
        {
            time_out --;
        }
        if ((can->MSTS_B.INITFLG == BIT_SET && can->MSTS_B.SLEEPFLG == BIT_RESET))
        {
            states = 1;
        }
    }
    else if (operatingMode == CAN_OPERATING_MODE_NORMAL)
    {
        /** Request leave initialisation and sleep mode  and enter Normal mode */
        can->MCTRL_B.SLEEPREQ = BIT_RESET;
        can->MCTRL_B.INITREQ = BIT_RESET;

        time_out = 0x0000FFFF;

        while ((can->MSTS_B.INITFLG != BIT_RESET || can->MSTS_B.SLEEPFLG != BIT_RESET) && (time_out != 0))
        {
            time_out --;
        }
        if ((can->MSTS_B.INITFLG == BIT_RESET || can->MSTS_B.SLEEPFLG == BIT_RESET))
        {
            states = 1;
        }
    }
    else if (operatingMode == CAN_OPERATING_MODE_SLEEP)
    {
        /** Request Sleep mode */
        can->MCTRL_B.SLEEPREQ = BIT_SET;
        can->MCTRL_B.INITREQ = BIT_RESET;

        time_out = 0x0000FFFF;

        while ((can->MSTS_B.INITFLG != BIT_RESET && can->MSTS_B.SLEEPFLG != BIT_SET) && (time_out != 0))
        {
            time_out --;
        }
        if ((can->MSTS_B.INITFLG == BIT_RESET && can->MSTS_B.SLEEPFLG == BIT_SET))
        {
            states = 1;
        }
    }
    return states ;
}

/*!
 * @brief     Into the low power mode.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @retval    status: Status of entering sleep mode.
 *                    0: Enter sleep fail
 *                    1: Enter sleep success
 */
uint8_t CAN_SleepMode(CAN_T *can)
{
    /** Request Sleep mode */
    can->MCTRL_B.SLEEPREQ = BIT_SET;
    can->MCTRL_B.INITREQ = BIT_RESET;

    if ((can->MSTS_B.INITFLG == BIT_RESET && can->MSTS_B.SLEEPFLG == BIT_SET))
    {
        return 1;
    }
    return 0;
}

/*!
 * @brief     Wakes the CAN up.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @retval    status: Status of waking the CAN up
 *                    0: WakeUp CAN fail,
 *                    1: WakeUp CAN success
 */
uint8_t CAN_WakeUpMode(CAN_T *can)
{
    uint32_t time_out = 0x0000FFFF;

    /** Wake up request */
    can->MCTRL_B.SLEEPREQ = BIT_RESET;
    while ((can->MSTS_B.SLEEPFLG == BIT_SET) && (time_out != 0))
    {
        time_out --;
    }
    if (can->MSTS_B.SLEEPFLG != BIT_SET)
    {
        return 1;
    }
    return 0;
}

/*!
 * @brief     Read the can's last error code (LERRC)
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @retval    The Last Error Code.
 */
uint8_t CAN_ReadLastErrorCode(CAN_T *can)
{
    return can->ERRSTS_B.LERRC;
}

/*!
 * @brief     Read the can Receive Error Counter(RXERRCNT)
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @retval    CAN Receive Error Counter.
 */
uint8_t CAN_ReadRxErrorCounter(CAN_T *can)
{
    return can->ERRSTS_B.RXERRCNT;
}

/*!
 * @brief     Read the LSB of the 9-bit can Transmit Error Counter(TXERRCNT).
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @retval    Least Significant Byte Of The 9-Bit Transmit Error Counter.
 */
uint8_t CAN_ReadLSBTxErrorCounter(CAN_T *can)
{
    return can->ERRSTS_B.TXERRCNT;
}

/*!
 * @brief     Enables the specified can interrupts.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     interrupts: specifies the CAN interrupt sources
 *                        This parameter can be any combination of the following values:
 *                        @arg CAN_INT_TXME   : Transmit mailbox empty Interrupt
 *                        @arg CAN_INT_F0MP   : FIFO 0 message pending Interrupt
 *                        @arg CAN_INT_F0FULL : FIFO 0 full Interrupt
 *                        @arg CAN_INT_F0OVR  : FIFO 0 overrun Interrupt
 *                        @arg CAN_INT_F1MP   : FIFO 1 message pending Interrupt
 *                        @arg CAN_INT_F1FULL : FIFO 1 full Interrupt
 *                        @arg CAN_INT_F1OVR  : FIFO 1 overrun Interrupt
 *                        @arg CAN_INT_ERRW   : Error warning Interrupt
 *                        @arg CAN_INT_ERRP   : Error passive Interrupt
 *                        @arg CAN_INT_BOF    : Bus-off Interrupt
 *                        @arg CAN_INT_LEC    : Last error record code Interrupt
 *                        @arg CAN_INT_ERR    : Error Interrupt
 *                        @arg CAN_INT_WUP    : Wake-up Interrupt
 *                        @arg CAN_INT_SLEEP  : Sleep acknowledge Interrupt
 *
 * @retval    None
 */
void CAN_EnableInterrupt(CAN_T *can, uint32_t interrupts)
{
    can->INTEN |= interrupts;
}

/*!
 * @brief     Disable the specified can interrupts.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     interrupts: specifies the CAN interrupt sources
 *                        This parameter can be any combination of the following values:
 *                        @arg CAN_INT_TXME   : Transmit mailbox empty Interrupt
 *                        @arg CAN_INT_F0MP   : FIFO 0 message pending Interrupt
 *                        @arg CAN_INT_F0FULL : FIFO 0 full Interrupt
 *                        @arg CAN_INT_F0OVR  : FIFO 0 overrun Interrupt
 *                        @arg CAN_INT_F1MP   : FIFO 1 message pending Interrupt
 *                        @arg CAN_INT_F1FULL : FIFO 1 full Interrupt
 *                        @arg CAN_INT_F1OVR  : FIFO 1 overrun Interrupt
 *                        @arg CAN_INT_ERRW   : Error warning Interrupt
 *                        @arg CAN_INT_ERRP   : Error passive Interrupt
 *                        @arg CAN_INT_BOF    : Bus-off Interrupt
 *                        @arg CAN_INT_LEC    : Last error record code Interrupt
 *                        @arg CAN_INT_ERR    : Error Interrupt
 *                        @arg CAN_INT_WUP    : Wake-up Interrupt
 *                        @arg CAN_INT_SLEEP  : Sleep acknowledge Interrupt
 *
 * @retval    None
 */
void CAN_DisableInterrupt(CAN_T *can, uint32_t interrupts)
{
    can->INTEN &= ~interrupts;
}

/*!
 * @brief     Read whether the specified CAN flag is set or not.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     flag: specifies the CAN flag.
 *                  This parameter can be one of the following values:
 *                  @arg CAN_FLAG_ERRW   : Error Warning Flag
 *                  @arg CAN_FLAG_ERRP   : Error Passive Flag
 *                  @arg CAN_FLAG_BOF    : Bus-Off Flag
 *                  @arg CAN_FLAG_LERRC  : Last error record code Flag
 *                  @arg CAN_FLAG_WUPI   : Wake up Flag
 *                  @arg CAN_FLAG_SLEEP  : Sleep acknowledge Flag
 *                  @arg CAN_FLAG_F0MP   : FIFO 0 Message Pending Flag
 *                  @arg CAN_FLAG_F0FULL : FIFO 0 Full Flag
 *                  @arg CAN_FLAG_F0OVR  : FIFO 0 Overrun Flag
 *                  @arg CAN_FLAG_F1MP   : FIFO 1 Message Pending Flag
 *                  @arg CAN_FLAG_F1FULL : FIFO 1 Full Flag
 *                  @arg CAN_FLAG_F1OVR  : FIFO 1 Overrun Flag
 *                  @arg CAN_FLAG_REQC0  : Request MailBox0 Flag
 *                  @arg CAN_FLAG_REQC1  : Request MailBox1 Flag
 *                  @arg CAN_FLAG_REQC2  : Request MailBox2 Flag
 *
 * @retval    flag staus:  RESET or SET
 */
uint8_t CAN_ReadStatusFlag(CAN_T *can, CAN_FLAG_T flag)
{
    uint8_t status = 0;

    if ((flag & 0x00F00000) != RESET)
    {
        if ((can->ERRSTS & (flag & 0x000FFFFF)) != RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else if ((flag & 0x01000000) != RESET)
    {
        if ((can->MSTS & (flag & 0x000FFFFF)) != RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET ;
        }
    }
    else if ((flag & 0x08000000) != RESET)
    {
        if ((can->TXSTS & (flag & 0x000FFFFF)) != RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else if ((flag & 0x02000000) != RESET)
    {
        if ((can->RXF0 & (flag & 0x000FFFFF)) != RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else
    {
        if ((can->RXF1 & (flag & 0x000FFFFF)) != RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    return status;
}

/*!
 * @brief     Clears the CAN's pending flags.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     flag: specifies the CAN flag.
 *                  This parameter can be one of the following values:
 *                  @arg CAN_FLAG_LERRC : Last error record code Flag
 *                  @arg CAN_FLAG_WUPI  : Wake up Flag
 *                  @arg CAN_FLAG_SLEEP : Sleep acknowledge Flag
 *                  @arg CAN_FLAG_F0FULL: FIFO 0 Full Flag
 *                  @arg CAN_FLAG_F0OVR : FIFO 0 Overrun Flag
 *                  @arg CAN_FLAG_F1FULL: FIFO 1 Full Flag
 *                  @arg CAN_FLAG_F1OVR : FIFO 1 Overrun Flag
 *                  @arg CAN_FLAG_REQC0 : Request MailBox0 Flag
 *                  @arg CAN_FLAG_REQC1 : Request MailBox1 Flag
 *                  @arg CAN_FLAG_REQC2 : Request MailBox2 Flag
 *
 * @retval    None
 */
void CAN_ClearStatusFlag(CAN_T *can, CAN_FLAG_T flag)
{
    uint32_t flagtmp = 0;

    /** ERRSTS register */
    if (flag == 0x30F00070)
    {
        can->ERRSTS = RESET;
    }
    else
    {
        flagtmp = flag & 0x000FFFFF;
        if ((flag & 0x02000000) != RESET)
        {
            can->RXF0 = flagtmp;
        }
        else if ((flag & 0x04000000) != RESET)
        {
            can->RXF1 = flagtmp;
        }
        else if ((flag & 0x08000000) != RESET)
        {
            can->TXSTS = flagtmp;
        }
        else
        {
            can->MSTS = flagtmp;
        }
    }
}

/*!
 * @brief     Read whether the specified can interrupt has occurred or not.
 *
 * @param     can: Select the CAN peripheral.
 *
 * @param     interrupts: specifies the CAN interrupt sources
 *                        This parameter can be one of the following values:
 *                        @arg CAN_INT_TXME   : Transmit mailbox empty Interrupt
 *                        @arg CAN_INT_F0MP   : FIFO 0 message pending Interrupt
 *                        @arg CAN_INT_F0FULL : FIFO 0 full Interrupt
 *                        @arg CAN_INT_F0OVR  : FIFO 0 overrun Interrupt
 *                        @arg CAN_INT_F1MP   : FIFO 1 message pending Interrupt
 *                        @arg CAN_INT_F1FULL : FIFO 1 full Interrupt
 *                        @arg CAN_INT_F1OVR  : FIFO 1 overrun Interrupt
 *                        @arg CAN_INT_ERRW   : Error warning Interrupt
 *                        @arg CAN_INT_ERRP   : Error passive Interrupt
 *                        @arg CAN_INT_BOF    : Bus-off Interrupt
 *                        @arg CAN_INT_LEC    : Last error record code Interrupt
 *                        @arg CAN_INT_ERR    : Error Interrupt
 *                        @arg CAN_INT_WUP    : Wake-up Interrupt
 *                        @arg CAN_INT_SLEEP  : Sleep acknowledge Interrupt
 *
 * @retval    status : SET or RESET
 */
uint8_t CAN_ReadIntFlag(CAN_T *can, CAN_INT_T flag)
{
    uint8_t status = 0;

    if ((can->INTEN & flag) != RESET)
    {
        switch (flag)
        {
        case CAN_INT_TXME:
            status = can->TXSTS_B.REQCFLG0;
            status |= can->TXSTS_B.REQCFLG1;
            status |= can->TXSTS_B.REQCFLG2;
            break;
        case CAN_INT_F0MP:
            status = can->RXF0_B.FMNUM0;
            break;
        case CAN_INT_F0FULL:
            status = can->RXF0_B.FFULLFLG0;
            break;
        case CAN_INT_F0OVR:
            status = can->RXF0_B.FOVRFLG0;
            break;
        case CAN_INT_F1MP:
            status = can->RXF1_B.FMNUM1;
            break;
        case CAN_INT_F1FULL:
            status = can->RXF1_B.FFULLFLG1;
            break;
        case CAN_INT_F1OVR:
            status = can->RXF1_B.FOVRFLG1;
            break;
        case CAN_INT_WUP:
            status = can->MSTS_B.WUPIFLG;
            break;
        case CAN_INT_SLEEP:
            status = can->MSTS_B.SLEEPIFLG;
            break;
        case CAN_INT_ERRW:
            status = can->ERRSTS_B.ERRWFLG;
            break;
        case CAN_INT_ERRP:
            status = can->ERRSTS_B.ERRPFLG;
            break;
        case CAN_INT_BOF:
            status = can->ERRSTS_B.BOFLG;
            break;
        case CAN_INT_LEC:
            status = can->ERRSTS_B.LERRC;
            break;
        case CAN_INT_ERR:
            status = can->MSTS_B.ERRIFLG;
            break;
        default:
            status = RESET;
            break;
        }
    }
    else
    {
        status = RESET;
    }
    return status;
}

/*!
 * @brief     Clears the can's interrupt flag.
 *
 * @param     can: Select the CAN peripheral which can be CAN1 or CAN2.
 *
 * @param     flag: Interrupt pending bit to clear
 *                  This parameter can be one of the following values:
 *                  @arg CAN_INT_TXME   : Transmit mailbox empty Interrupt
 *                  @arg CAN_INT_F0FULL : FIFO 0 full Interrupt
 *                  @arg CAN_INT_F0OVR  : FIFO 0 overrun Interrupt
 *                  @arg CAN_INT_F1FULL : FIFO 1 full Interrupt
 *                  @arg CAN_INT_F1OVR  : FIFO 1 overrun Interrupt
 *                  @arg CAN_INT_ERRW   : Error warning Interrupt
 *                  @arg CAN_INT_ERRP   : Error passive Interrupt
 *                  @arg CAN_INT_BOF    : Bus-off Interrupt
 *                  @arg CAN_INT_LEC    : Last error record code Interrupt
 *                  @arg CAN_INT_ERR    : Error Interrupt
 *                  @arg CAN_INT_WUP    : Wake-up Interrupt
 *                  @arg CAN_INT_SLEEP  : Sleep acknowledge Interrupt
 *
 * @retval    None
 */
void CAN_ClearIntFlag(CAN_T *can, CAN_INT_T flag)
{
    switch (flag)
    {
    case CAN_INT_TXME:
        can->TXSTS_B.REQCFLG0 = BIT_SET;
        can->TXSTS_B.REQCFLG1 = BIT_SET;
        can->TXSTS_B.REQCFLG2 = BIT_SET;
        break;
    case CAN_INT_F0FULL:
        can->RXF0_B.FFULLFLG0 = BIT_SET;
        break;
    case CAN_INT_F0OVR:
        can->RXF0_B.FOVRFLG0  = BIT_SET;
        break;
    case CAN_INT_F1FULL:
        can->RXF1_B.FFULLFLG1 = BIT_SET;
        break;
    case CAN_INT_F1OVR:
        can->RXF1_B.FOVRFLG1  = BIT_SET;
        break;
    case CAN_INT_WUP:
        can->MSTS_B.WUPIFLG   = BIT_SET;
        break;
    case CAN_INT_SLEEP:
        can->MSTS_B.SLEEPIFLG = BIT_SET;
        break;
    case CAN_INT_ERRW:
        can->MSTS_B.ERRIFLG = BIT_SET;
        break;
    case CAN_INT_ERRP:
        can->MSTS_B.ERRIFLG = BIT_SET;
        break;
    case CAN_INT_BOF:
        can->MSTS_B.ERRIFLG = BIT_SET;
        break;
    case CAN_INT_LEC:
        can->ERRSTS_B.LERRC = BIT_RESET;
        can->MSTS_B.ERRIFLG = BIT_SET;
        break;
    case CAN_INT_ERR:
        can->ERRSTS_B.LERRC = BIT_RESET;
        can->MSTS_B.ERRIFLG = BIT_SET;
        break;
    default:
        break;
    }
}

/**@} end of group CAN_Functions */
/**@} end of group CAN_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
