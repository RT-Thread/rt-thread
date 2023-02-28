/*!
 * @file        apm32f0xx_can.c
 *
 * @brief       This file contains all the functions for the CAN peripheral
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

/* include */
#include "apm32f0xx_can.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CAN_Driver
  @{
*/

/** @defgroup CAN_Macros Macros
  @{
*/

/**@} end of group CAN_Macros */

/** @defgroup CAN_Enumerations Enumerations
  @{
*/

/**@} end of group CAN_Enumerations */

/** @defgroup CAN_Structures Structures
  @{
*/

/**@} end of group CAN_Structures */

/** @defgroup CAN_Variables Variables
  @{
*/

/**@} end of group CAN_Variables */

/** @defgroup CAN_Functions Functions
  @{
*/

/*!
 * @brief       Reset CAN peripheral registers to their default values.
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CAN_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_CAN);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_CAN);
}

/*!
 * @brief       Congfig the CAN peripheral using the specified parameters in the canConfig.
 *
 * @param       canConfig : pointer to a CAN_Config_T structure that contains
 *                          the configuration information for the CAN peripheral.
 *
 * @retval      Configuration status (SET or RESET)
 */
uint8_t CAN_Config(CAN_Config_T* canConfig)
{
    uint8_t InitStatus = RESET;
    uint32_t ackWait = 0x00000000;

    CAN->MCTRL_B.SLEEPREQ = BIT_RESET;

    CAN->MCTRL_B.INITREQ = BIT_SET;

    while ((CAN->MSTS_B.INITFLG != BIT_SET) && (ackWait != (uint32_t)0x00FFFFFF))
    {
        ackWait++;
    }

    if (CAN->MSTS_B.INITFLG != BIT_SET)
    {
        InitStatus = RESET;
    }
    else
    {
        if (canConfig->timeTrigComMode == ENABLE)
        {
            CAN->MCTRL_B.TTCM = BIT_SET;
        }
        else
        {
            CAN->MCTRL_B.TTCM = BIT_RESET;
        }

        if (canConfig->autoBusOffManage == ENABLE)
        {
            CAN->MCTRL_B.ALBOFFM = BIT_SET;
        }
        else
        {
            CAN->MCTRL_B.ALBOFFM = BIT_RESET;
        }

        if (canConfig->autoWakeUpMode == ENABLE)
        {
            CAN->MCTRL_B.AWUPCFG = BIT_SET;
        }
        else
        {
            CAN->MCTRL_B.AWUPCFG = BIT_RESET;
        }

        if (canConfig->nonAutoRetran == ENABLE)
        {
            CAN->MCTRL_B.ARTXMD = BIT_SET;
        }
        else
        {
            CAN->MCTRL_B.ARTXMD = BIT_RESET;
        }

        if (canConfig->rxFIFOLockMode == ENABLE)
        {
            CAN->MCTRL_B.RXFLOCK = BIT_SET;
        }
        else
        {
            CAN->MCTRL_B.RXFLOCK = BIT_RESET;
        }

        if (canConfig->txFIFOPriority == ENABLE)
        {
            CAN->MCTRL_B.TXFPCFG = BIT_SET;
        }
        else
        {
            CAN->MCTRL_B.TXFPCFG = BIT_RESET;
        }

        CAN->BITTIM = (uint32_t)canConfig->mode << 30;
        CAN->BITTIM_B.RSYNJW     = canConfig->syncJumpWidth;
        CAN->BITTIM_B.TIMSEG1 = canConfig->timeSegment1;
        CAN->BITTIM_B.TIMSEG2 = canConfig->timeSegment2;
        CAN->BITTIM_B.BRPSC     = canConfig->prescaler - 1;

        CAN->MCTRL_B.INITREQ = BIT_RESET;

        ackWait = 0x00000000;

        while ((CAN->MSTS_B.INITFLG == BIT_SET) && (ackWait != (uint32_t)0x00FFFFFF))
        {
            ackWait++;
        }

        if (CAN->MSTS_B.INITFLG == BIT_RESET)
        {
            InitStatus = SET;
        }
        else
        {
            InitStatus = RESET;
        }
    }
    return InitStatus;
}

/*!
 * @brief       Congfig the CAN filter according to the specified parameters in the filterConfig.
 *
 * @param       filterConfig: pointer to a CAN_Filter_Config_T structure that
 *                            contains the configuration information.
 *
 * @retval      None
 */
void CAN_ConfigFilter(CAN_FilterConfig_T* filterConfig)
{
    uint16_t filterNumber = 0;

    filterNumber = BIT0 << filterConfig->filterNumber;

    CAN->FCTRL_B.FIM = BIT_SET;

    CAN->FACT &= ~filterNumber;

    if (filterConfig->filterScale == CAN_FILTER_SCALE_16BIT)
    {
        CAN->FSCFG &= ~filterNumber;

        CAN->sFilterRegister[filterConfig->filterNumber].R1 =
            ((0x0000FFFF & filterConfig->filterMaskIdLow) << 16) |
            (0x0000FFFF & filterConfig->filterIdLow);

        CAN->sFilterRegister[filterConfig->filterNumber].R2 =
            ((0x0000FFFF & filterConfig->filterMaskIdHigh) << 16) |
            (0x0000FFFF & filterConfig->filterIdHigh);
    }

    if (filterConfig->filterScale == CAN_FILTER_SCALE_32BIT)
    {
        CAN->FSCFG |= filterNumber;

        CAN->sFilterRegister[filterConfig->filterNumber].R1 =
            ((0x0000FFFF & filterConfig->filterIdHigh) << 16) |
            (0x0000FFFF & filterConfig->filterIdLow);

        CAN->sFilterRegister[filterConfig->filterNumber].R2 =
            ((0x0000FFFF & filterConfig->filterMaskIdHigh) << 16) |
            (0x0000FFFF & filterConfig->filterMaskIdLow);
    }

    if (filterConfig->filterMode == CAN_FILTER_MODE_IDMASK)
    {
        CAN->FMCFG &= ~filterNumber;
    }
    else
    {
        CAN->FMCFG |= filterNumber;
    }

    if (filterConfig->filterFIFO == CAN_FIFO_0)
    {
        CAN->FFASS &= ~filterNumber;
    }
    else
    {
        CAN->FFASS |= filterNumber;
    }

    if (filterConfig->filterActivation == ENABLE)
    {
        CAN->FACT |= filterNumber;
    }

    CAN->FCTRL_B.FIM = BIT_RESET;
}

/*!
 * @brief   Fills each canConfig member with its default value.
 *
 * @param   canConfig : Pointer to a CAN_Config_T structure which is used for configuration.
 *
 * @retval  None
 */
void CAN_ConfigStructInit(CAN_Config_T* canConfig)
{
    canConfig->timeTrigComMode  = DISABLE;

    canConfig->autoBusOffManage  = DISABLE;

    canConfig->autoWakeUpMode   = DISABLE;

    canConfig->nonAutoRetran   = DISABLE;

    canConfig->rxFIFOLockMode = DISABLE;

    canConfig->txFIFOPriority  = DISABLE;

    canConfig->mode = CAN_MODE_NORMAL;

    canConfig->syncJumpWidth = CAN_SJW_1;

    canConfig->timeSegment1 = CAN_TIME_SEGMENT1_4;

    canConfig->timeSegment2 = CAN_TIME_SEGMENT2_3;

    canConfig->prescaler = 1;
}

/*!
 * @brief     Select the start bank filter for slave CAN.
 *
 * @param     bankNumber:Select the start slave bank filter from 1 to 27.
 *
 * @retval    None
 *
 * @note      This function applies only to APM32 Connectivity line devices.
 */
void CAN_StartBankSlave(uint8_t bankNumber)
{
    CAN->FCTRL_B.FIM = BIT_SET;

    CAN->FCTRL &= 0xFFFFC0F1;
    CAN->FCTRL |= (uint32_t)(bankNumber) << 8;

    CAN->FCTRL_B.FIM = BIT_RESET;
}

/*!
 * @brief      Enable the Debug Freeze mdoe for CAN.
 *
 * @param      None
 *
 * @retval     None
 */
void CAN_EnableDebugFreeze(void)
{
    CAN->MCTRL_B.DBGFRZE = BIT_SET;
}

/*!
 * @brief      Disable the Debug Freeze mode for CAN.
 *
 * @param      None
 *
 * @retval     None
 */
void CAN_DisableDebugFreeze(void)
{
    CAN->MCTRL_B.DBGFRZE = BIT_RESET;
}

/*!
 * @brief      Enables the Time Triggered Communication mode for CAN.
 *
 * @param      None
 *
 * @retval     None
 */
void CAN_EnableTTComMode(void)
{
    CAN->MCTRL_B.TTCM = BIT_SET;

    CAN->sTxMailBox[0].TXDLEN_B.TXGT = BIT_SET;
    CAN->sTxMailBox[1].TXDLEN_B.TXGT = BIT_SET;
    CAN->sTxMailBox[2].TXDLEN_B.TXGT = BIT_SET;
}

/*!
 * @brief      Disables the Time Triggered Communication mode for CAN.
 *
 * @param      None
 *
 * @retval     None
 */
void CAN_DisableTTComMode(void)
{
    CAN->MCTRL_B.TTCM = BIT_RESET;

    CAN->sTxMailBox[0].TXDLEN_B.TXGT = BIT_RESET;
    CAN->sTxMailBox[1].TXDLEN_B.TXGT = BIT_RESET;
    CAN->sTxMailBox[2].TXDLEN_B.TXGT = BIT_RESET;
}

/*!
 * @brief     Transmit a message from TxMessage of CAN_Tx_Message structure.
 *
 * @param     TxMessage : Pointer to a structure which contains CAN Id, CAN DLCODE and CAN data.
 *
 * @retval    Returns the number of the transmit mailbox state.It can be one of value:
 *                 @arg 0: Transmit mailbox 0
 *                 @arg 1: Transmit mailbox 1
 *                 @arg 2: Transmit mailbox 2
 *                 @arg 4: There is no empty mailbox
 */
uint8_t CAN_TxMessage(CAN_Tx_Message* TxMessage)
{
    uint8_t TxMailbox = 0;

    if ((CAN->TXSTS_B.TXMEFLG0 == BIT_SET))
    {
        TxMailbox = 0;
    }
    else if ((CAN->TXSTS_B.TXMEFLG1 == BIT_SET))
    {
        TxMailbox = 1;
    }
    else if ((CAN->TXSTS_B.TXMEFLG2 == BIT_SET))
    {
        TxMailbox = 2;
    }
    else
    {
        TxMailbox = CAN_TX_MAILBOX_FULL;
    }

    if (TxMailbox != CAN_TX_MAILBOX_FULL)
    {
        /* Set up the Id */
        CAN->sTxMailBox[TxMailbox].TXMID &= BIT0;
        if (TxMessage->typeID == CAN_TYPEID_STD)
        {
            CAN->sTxMailBox[TxMailbox].TXMID |= (((uint32_t)TxMessage->stanID << 21) | \
                                                 TxMessage->typeID        | \
                                                 TxMessage->remoteTxReq);
        }
        else
        {
            CAN->sTxMailBox[TxMailbox].TXMID |= (((uint32_t)TxMessage->extenID << 3) | \
                                                 TxMessage->typeID       | \
                                                 TxMessage->remoteTxReq);
        }

        /* Set up the DLCODE */
        CAN->sTxMailBox[TxMailbox].TXDLEN_B.DLCODE = (TxMessage->dataLengthCode & 0x0F);

        /* Set up the data field */
        CAN->sTxMailBox[TxMailbox].TXMDH_B.DATABYTE7 = TxMessage->data[7];
        CAN->sTxMailBox[TxMailbox].TXMDH_B.DATABYTE6 = TxMessage->data[6];
        CAN->sTxMailBox[TxMailbox].TXMDH_B.DATABYTE5 = TxMessage->data[5];
        CAN->sTxMailBox[TxMailbox].TXMDH_B.DATABYTE4 = TxMessage->data[4];

        CAN->sTxMailBox[TxMailbox].TXMDL_B.DATABYTE3 = TxMessage->data[3];
        CAN->sTxMailBox[TxMailbox].TXMDL_B.DATABYTE2 = TxMessage->data[2];
        CAN->sTxMailBox[TxMailbox].TXMDL_B.DATABYTE1 = TxMessage->data[1];
        CAN->sTxMailBox[TxMailbox].TXMDL_B.DATABYTE0 = TxMessage->data[0];

        /* Request transmission */
        CAN->sTxMailBox[TxMailbox].TXMID |= BIT0;
    }

    return TxMailbox;
}

/*!
 * @brief     Reads the status of a transmission.
 *
 * @param     TxMailbox: the number of the mailbox
 *              This parameter can be one of the following values:
 *              @arg CAN_MAILBOX_0 : Transmit mailbox 0
 *              @arg CAN_MAILBOX_1 : Transmit mailbox 1
 *              @arg CAN_MAILBOX_2 : Transmit mailbox 2
 *
 * @retval    Returns the transmission state.
 *              It can be one of the following values:
 *              @arg CAN_TX_FAILED
 *              @arg CAN_TX_OK
 *              @arg CAN_TX_WAITING
 */
uint8_t CAN_TxMessageStatus(CAN_MAILBOX_T TxMailbox)
{
    uint8_t state = CAN_TX_FAILED;

    switch (TxMailbox)
    {
        case (CAN_MAILBOX_0):
            if (CAN->TXSTS_B.REQCFLG0 && CAN->TXSTS_B.TXSUSFLG0 && CAN->TXSTS_B.TXMEFLG0)
            {
                state = CAN_TX_OK;
            }
            else if (!(CAN->TXSTS_B.REQCFLG0 || CAN->TXSTS_B.TXSUSFLG0 || CAN->TXSTS_B.TXMEFLG0))
            {
                state = CAN_TX_WAITING;
            }
            break;

        case (CAN_MAILBOX_1):
            if (CAN->TXSTS_B.REQCFLG1 && CAN->TXSTS_B.TXSUSFLG1 && CAN->TXSTS_B.TXMEFLG1)
            {
                state = CAN_TX_OK;
            }
            else if (!(CAN->TXSTS_B.REQCFLG1 || CAN->TXSTS_B.TXSUSFLG1 || CAN->TXSTS_B.TXMEFLG1))
            {
                state = CAN_TX_WAITING;
            }
            break;

        case (CAN_MAILBOX_2):
            if (CAN->TXSTS_B.REQCFLG2 && CAN->TXSTS_B.TXSUSFLG2 && CAN->TXSTS_B.TXMEFLG2)
            {
                state = CAN_TX_OK;
            }
            else if (!(CAN->TXSTS_B.REQCFLG2 || CAN->TXSTS_B.TXSUSFLG2 || CAN->TXSTS_B.TXMEFLG2))
            {
                state = CAN_TX_WAITING;
            }
            break;

        default:
            break;
    }

    return state;
}

/*!
 * @brief     Cancels a transmit request.
 *
 * @param     TxMailbox: the number of the mailbox
 *              This parameter can be one of the following values:
 *                @arg CAN_MAILBOX_0 : Abort transmission request for mailbox 0
 *                @arg CAN_MAILBOX_1 : Abort transmission request for mailbox 1
 *                @arg CAN_MAILBOX_2 : Abort transmission request for mailbox 2
 *
 * @retval    None
 */
void CAN_CancelTx(CAN_MAILBOX_T TxMailbox)
{
    switch (TxMailbox)
    {
        case 0:
            CAN->TXSTS_B.ABREQFLG0 = BIT_SET;
            break;

        case 1:
            CAN->TXSTS_B.ABREQFLG1 = BIT_SET;
            break;

        case 2:
            CAN->TXSTS_B.ABREQFLG2 = BIT_SET;
            break;

        default:
            break;
    }
}

/*!
 * @brief     Receive a valid message through the filter.
 *
 * @param     FIFONumber: The number of Receive FIFO
 *              This parameter can be one of the following values:
 *                @arg CAN_FIFO_0 : CAN FIFO 0 used to receive
 *                @arg CAN_FIFO_1 : CAN FIFO 1 used to receive
 *
 * @param     RxMessage : pointer to a structure that is used to receive message
 *
 * @retval    None
 */
void CAN_RxMessage(uint8_t FIFONumber, CAN_Rx_Message* RxMessage)
{
    RxMessage->typeID = (CAN_TYPEID_T)(BIT2 & CAN->sRxFIFO[FIFONumber].RXMID);

    if (RxMessage->typeID == CAN_TYPEID_STD)
    {
        RxMessage->stanID = CAN->sRxFIFO[FIFONumber].RXMID_B.STDID;
    }
    else
    {
        RxMessage->extenID = (CAN->sRxFIFO[FIFONumber].RXMID_B.STDID << 18);
        RxMessage->extenID |= CAN->sRxFIFO[FIFONumber].RXMID_B.EXTID;
    }

    RxMessage->remoteTxReq = (CAN_RTXR_T)(BIT1 & CAN->sRxFIFO[FIFONumber].RXMID);
    RxMessage->dataLengthCode = CAN->sRxFIFO[FIFONumber].RXDLEN_B.DLCODE;
    RxMessage->filterMatchIndex = CAN->sRxFIFO[FIFONumber].RXDLEN_B.FMIDX;

    RxMessage->data[7] = CAN->sRxFIFO[FIFONumber].RXMDH_B.DATABYTE7;
    RxMessage->data[6] = CAN->sRxFIFO[FIFONumber].RXMDH_B.DATABYTE6;
    RxMessage->data[5] = CAN->sRxFIFO[FIFONumber].RXMDH_B.DATABYTE5;
    RxMessage->data[4] = CAN->sRxFIFO[FIFONumber].RXMDH_B.DATABYTE4;

    RxMessage->data[3] = CAN->sRxFIFO[FIFONumber].RXMDL_B.DATABYTE3;
    RxMessage->data[2] = CAN->sRxFIFO[FIFONumber].RXMDL_B.DATABYTE2;
    RxMessage->data[1] = CAN->sRxFIFO[FIFONumber].RXMDL_B.DATABYTE1;
    RxMessage->data[0] = CAN->sRxFIFO[FIFONumber].RXMDL_B.DATABYTE0;

    if (FIFONumber == CAN_FIFO_0)
    {
        CAN->RXF0_B.RFOM0 = BIT_SET;
    }
    else
    {
        CAN->RXF1_B.RFOM1 = BIT_SET;
    }
}

/*!
 * @brief     Releases the specified receive FIFO.
 *
 * @param     FIFONumber : the number of receive FIFO
 *              This parameter can be one of the following values:
 *                @arg CAN_FIFO_0 : CAN FIFO 0 used to receive
 *                @arg CAN_FIFO_1 : CAN FIFO 1 used to receive
 *
 * @retval    None
 */
void CAN_ReleaseFIFO(uint8_t FIFONumber)
{
    if (FIFONumber == CAN_FIFO_0)
    {
        CAN->RXF0_B.RFOM0 = BIT_SET;
    }
    else
    {
        CAN->RXF1_B.RFOM1 = BIT_SET;
    }
}

/*!
 * @brief    Reads the number of pending messages.
 *
 * @param    FIFONumber : the number of receive FIFO
 *              This parameter can be one of the following values:
 *                @arg CAN_FIFO_0 : CAN FIFO 0 used to receive
 *                @arg CAN_FIFO_1 : CAN FIFO 1 used to receive
 *
 * @retval   which is the number of pending message.
 */
uint8_t CAN_PendingMessage(uint8_t FIFONumber)
{
    if (FIFONumber == CAN_FIFO_0)
    {
        return  CAN->RXF0_B.FMNUM0;
    }
    else
    {
        return  CAN->RXF1_B.FMNUM1;
    }
}

/*!
 * @brief     Select the CAN Operation mode.
 *
 * @param     operatingMode: CAN Operating Mode
 *              This parameter can be one of the following values:
 *              @arg CAN_OPERATING_MODE_INIT  : Initialization mode
 *              @arg CAN_OPERATING_MODE_NORMAL: Normal mode
 *              @arg CAN_OPERATING_MODE_SLEEP : sleep mode
 *
 * @retval    status: 0 : CAN failed entering the specific mode
 *                    1 : CAN Succeed entering the specific mode
 */
uint8_t CAN_OperatingMode(CAN_OPERATING_MODE_T operatingMode)
{
    uint8_t status = RESET;
    uint32_t timeout = 0x00FFFFFF;
    uint8_t sleepflg, initfig;

    sleepflg = CAN->MSTS_B.SLEEPFLG;
    initfig = CAN->MSTS_B.INITFLG;

    switch ((uint8_t)operatingMode)
    {
        case CAN_OPERATING_MODE_INIT:
            CAN->MCTRL_B.SLEEPREQ  = BIT_RESET;
            CAN->MCTRL_B.INITREQ = BIT_SET;

            while ((sleepflg | !initfig) && (timeout != 0))
            {
                sleepflg = CAN->MSTS_B.SLEEPFLG;
                initfig = CAN->MSTS_B.INITFLG;
                timeout--;
            }

            if (sleepflg | !initfig)
            {
                status = RESET;
            }
            else
            {
                status = SET;
            }
            break;

        case CAN_OPERATING_MODE_NORMAL:

            CAN->MCTRL_B.INITREQ = BIT_RESET;
            CAN->MCTRL_B.SLEEPREQ     = BIT_RESET;

            while ((sleepflg | initfig) && (timeout != 0))
            {
                sleepflg = CAN->MSTS_B.SLEEPFLG;
                initfig = CAN->MSTS_B.INITFLG;
                timeout--;
            }

            if (sleepflg | initfig)
            {
                status = RESET;
            }
            else
            {
                status = SET;
            }
            break;

        case CAN_OPERATING_MODE_SLEEP:
            CAN->MCTRL_B.INITREQ = BIT_RESET;
            CAN->MCTRL_B.SLEEPREQ     = BIT_SET;

            while ((!sleepflg | initfig) && (timeout != 0))
            {
                sleepflg = CAN->MSTS_B.SLEEPFLG;
                initfig = CAN->MSTS_B.INITFLG;
                timeout--;
            }

            if (!sleepflg | initfig)
            {
                status = RESET;
            }
            else
            {
                status = SET;
            }
            break;

        default:
            status = RESET;
            break;
    }

    return status;
}

/*!
 * @brief     Enters the sleep mode.
 *
 * @param     None
 *
 * @retval    status: 0 : Into sleep fail
 *                    1 : Into sleep success
 */
uint8_t CAN_SleepMode(void)
{
    CAN_SLEEP_T sleepstatus = CAN_SLEEP_FAILED;

    CAN->MCTRL_B.INITREQ = BIT_RESET;
    CAN->MCTRL_B.SLEEPREQ     = BIT_SET;

    if ((CAN->MSTS_B.SLEEPFLG == BIT_SET) && (CAN->MSTS_B.INITFLG == BIT_RESET))
    {
        sleepstatus =  CAN_SLEEP_OK;
    }

    return (uint8_t)sleepstatus;
}

/*!
 * @brief     Wakes up the CAN from sleep mode.
 *
 * @param     None
 *
 * @retval    status: 0 : WakeUp CAN fail
 *                    1 : WakeUp CAN success
 */
uint8_t CAN_WakeUpMode(void)
{
    uint32_t slakWait = 0x00FFFFFF;
    CAN_WUP_T wakeupstatus = CAN_WAKEUP_FAILED;

    CAN->MCTRL_B.SLEEPREQ = BIT_RESET;

    while ((CAN->MSTS_B.SLEEPFLG == BIT_SET) && (slakWait != 0x00))
    {
        slakWait--;
    }
    if (CAN->MSTS_B.SLEEPFLG != BIT_SET)
    {
        wakeupstatus = CAN_WAKEUP_OK;
    }
    return (uint8_t)wakeupstatus;
}

/*!
 * @brief     Read the last error code of CAN.
 *
 * @param     None
 *
 * @retval    CAN_ErrorCode
 */
uint8_t CAN_ReadLastErrorCode(void)
{
    uint8_t errorcode = 0;
    errorcode = CAN->ERRSTS_B.LERRC;
    return errorcode;
}

/*!
 * @brief    Read the Receive Error Counter of CAN.
 *
 * @param    None
 *
 * @retval   CAN Receive Error Counter.
 */
uint8_t CAN_ReadRxErrorCounter(void)
{
    uint8_t counter = 0;
    counter = CAN->ERRSTS_B.RXERRCNT;
    return counter;
}

/*!
 * @brief   Reads the Least significant byte of the 9-bit CAN Transmit Error Counter.
 *
 * @param   None
 *
 * @retval  Least significant byte of the 9-bit CAN Transmit Error Counter.
 */
uint8_t CAN_ReadLSBTxErrorCounter(void)
{
    uint8_t counter = 0;
    counter = CAN->ERRSTS_B.TXERRCNT;
    return counter;
}

/*!
 * @brief  Enables the specified CAN interrupts.
 *
 * @param  interrupt: Selects the CAN interrupt sources to be enabled.
 *          The parameter can be any combination of the following values:
 *            @arg CAN_INT_TXME : Transmit mailbox empty Interrupt
 *            @arg CAN_INT_F0MP : FIFO 0 message pending Interrupt
 *            @arg CAN_INT_F0FUL: FIFO 0 full Interrupt
 *            @arg CAN_INT_F0OVR: FIFO 0 overrun Interrupt
 *            @arg CAN_INT_F1MP : FIFO 1 message pending Interrupt
 *            @arg CAN_INT_F1FUL: FIFO 1 full Interrupt
 *            @arg CAN_INT_F1OVR: FIFO 1 overrun Interrupt
 *            @arg CAN_INT_EWIE : Error warning Interrupt
 *            @arg CAN_INT_EPIE : Error passive Interrupt
 *            @arg CAN_INT_BOIE : Bus-off Interrupt
 *            @arg CAN_INT_LEC  : Last error code Interrupt
 *            @arg CAN_INT_ERR  : Error Interrupt
 *            @arg CAN_INT_WUP  : Wake-up Interrupt
 *            @arg CAN_INT_SLE  : Sleep acknowledge Interrupt
 *
 * @retval  None
 */
void CAN_EnableInterrupt(uint32_t interrupt)
{
    CAN->INTEN |= interrupt;
}

/*!
 * @brief  Disables the specified CAN interrupts.
 *
 * @param  interrupt: Selects the CAN interrupt sources to be disabled.
 *          The parameter can be any combination of the following values:
 *            @arg CAN_INT_TXME : Transmit mailbox empty Interrupt
 *            @arg CAN_INT_F0MP : FIFO 0 message pending Interrupt
 *            @arg CAN_INT_F0FUL: FIFO 0 full Interrupt
 *            @arg CAN_INT_F0OVR: FIFO 0 overrun Interrupt
 *            @arg CAN_INT_F1MP : FIFO 1 message pending Interrupt
 *            @arg CAN_INT_F1FUL: FIFO 1 full Interrupt
 *            @arg CAN_INT_F1OVR: FIFO 1 overrun Interrupt
 *            @arg CAN_INT_WUP  : Wake-up Interrupt
 *            @arg CAN_INT_SLE  : Sleep acknowledge Interrupt
 *            @arg CAN_INT_EWIE : Error warning Interrupt
 *            @arg CAN_INT_EPIE : Error passive Interrupt
 *            @arg CAN_INT_BOIE : Bus-off Interrupt
 *            @arg CAN_INT_LEC  : Last error code Interrupt
 *            @arg CAN_INT_ERR  : Error Interrupt
 *
 * @retval None
 */
void CAN_DisableInterrupt(uint32_t interrupt)
{
    CAN->INTEN &= ~interrupt;
}

/*!
 * @brief  Reads the specified CAN flag status.
 *
 * @param  flag: specifies the flag of CAN.
 *          The parameter can be one of following values:
 *            @arg CAN_FLAG_EWF  : Error Warning Flag
 *            @arg CAN_FLAG_EPF  : Error Passive Flag
 *            @arg CAN_FLAG_BOF  : Bus-Off Flag
 *            @arg CAN_FLAG_LEC  : Last error code Flag
 *            @arg CAN_FLAG_WUP  : Wake up Flag
 *            @arg CAN_FLAG_SLAK : Sleep acknowledge Flag
 *            @arg CAN_FLAG_RQCP0: Request MailBox0 Flag
 *            @arg CAN_FLAG_RQCP1: Request MailBox1 Flag
 *            @arg CAN_FLAG_RQCP2: Request MailBox2 Flag
 *            @arg CAN_FLAG_FMP0 : FIFO 0 Message Pending Flag
 *            @arg CAN_FLAG_FF0  : FIFO 0 Full Flag
 *            @arg CAN_FLAG_FOV0 : FIFO 0 Overrun Flag
 *            @arg CAN_FLAG_FMP1 : FIFO 1 Message Pending Flag
 *            @arg CAN_FLAG_FF1  : FIFO 1 Full Flag
 *            @arg CAN_FLAG_FOV1 : FIFO 1 Overrun Flag
 *
 * @retval  staus : RESET or SET
 */
uint8_t CAN_ReadStatusFlag(CAN_FLAG_T flag)
{
    uint8_t status = RESET;

    if ((flag & 0x00F00000) != (uint32_t)RESET)
    {
        if ((CAN->ERRSTS & (flag & 0x000FFFFF)) != (uint32_t)RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else if ((flag & 0x01000000) != (uint32_t)RESET)
    {
        if ((CAN->MSTS & (flag & 0x000FFFFF)) != (uint32_t)RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else if ((flag & 0x02000000) != (uint32_t)RESET)
    {
        if ((CAN->TXSTS & (flag & 0x000FFFFF)) != (uint32_t)RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    else if ((flag & 0x04000000) != (uint32_t)RESET)
    {
        if ((CAN->RXF0 & (flag & 0x000FFFFF)) != (uint32_t)RESET)
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
        if ((CAN->RXF1 & (flag & 0x000FFFFF)) != (uint32_t)RESET)
        {
            status = SET;
        }
        else
        {
            status = RESET;
        }
    }
    return  status;
}

/*!
 * @brief  Clears the status flags of CAN.
 *
 * @param  flag : specifies the flag to clear.
 *           The parameter can be one of following values:
 *            @arg CAN_FLAG_LEC  : Last error code Flag
 *            @arg CAN_FLAG_WUP  : Wake up Flag
 *            @arg CAN_FLAG_SLAK : Sleep acknowledge Flag
 *            @arg CAN_FLAG_RQCP0: Request MailBox0 Flag
 *            @arg CAN_FLAG_RQCP1: Request MailBox1 Flag
 *            @arg CAN_FLAG_RQCP2: Request MailBox2 Flag
 *            @arg CAN_FLAG_FF0  : FIFO 0 Full Flag
 *            @arg CAN_FLAG_FOV0 : FIFO 0 Overrun Flag
 *            @arg CAN_FLAG_FF1  : FIFO 1 Full Flag
 *            @arg CAN_FLAG_FOV1 : FIFO 1 Overrun Flag
 *
 * @retval  None
 */
void CAN_ClearStatusFlag(CAN_FLAG_T flag)
{
    uint32_t flagtmp = 0;

    if (flag == CAN_FLAG_LEC)
    {
        CAN->ERRSTS_B.LERRC = 0;
    }
    else
    {
        flagtmp = flag & 0x000FFFFF;

        if ((flag & 0x01000000) != RESET)
        {
            CAN->MSTS = flagtmp;
        }
        else if ((flag & 0x02000000) != RESET)
        {
            CAN->TXSTS = flagtmp;
        }
        else if ((flag & 0x04000000) != RESET)
        {
            CAN->RXF0 = flagtmp;
        }
        else
        {
            CAN->RXF1 = flagtmp;
        }
    }
}

/*!
 * @brief  Reads the specified CAN interrupt flag status.
 *
 * @param  interrupt: specifies the CAN interrupt source.
 *          The parameter can be one of following values:
 *            @arg CAN_INT_TXME : Transmit mailbox empty Interrupt
 *            @arg CAN_INT_F0MP : FIFO 0 message pending Interrupt
 *            @arg CAN_INT_F0FUL: FIFO 0 full Interrupt
 *            @arg CAN_INT_F0OVR: FIFO 0 overrun Interrupt
 *            @arg CAN_INT_F1MP : FIFO 1 message pending Interrupt
 *            @arg CAN_INT_F1FUL: FIFO 1 full Interrupt
 *            @arg CAN_INT_F1OVR: FIFO 1 overrun Interrupt
 *            @arg CAN_INT_EWIE : Error warning Interrupt
 *            @arg CAN_INT_EPIE : Error passive Interrupt
 *            @arg CAN_INT_BOIE : Bus-off Interrupt
 *            @arg CAN_INT_LEC  : Last error code Interrupt
 *            @arg CAN_INT_ERR  : Error Interrupt
 *            @arg CAN_INT_WUP  : Wake-up Interrupt
 *            @arg CAN_INT_SLE  : Sleep acknowledge Interrupt
 *
 * @retval  status : SET or RESET
 */
uint8_t CAN_ReadIntFlag(CAN_INT_T interrupt)
{
    uint8_t status = 0;

    if ((CAN->INTEN & interrupt) != RESET)
    {
        switch (interrupt)
        {
            case CAN_INT_TXME:
                status = CAN->TXSTS_B.REQCFLG0;
                status |= CAN->TXSTS_B.REQCFLG1;
                status |= CAN->TXSTS_B.REQCFLG2;
                break;
            case CAN_INT_F0MP:
                status = !(!CAN->RXF0_B.FMNUM0);
                break;
            case CAN_INT_F0FUL:
                status = CAN->RXF0_B.FFULLFLG0;
                break;
            case CAN_INT_F0OVR:
                status = CAN->RXF0_B.FOVRFLG0;
                break;
            case CAN_INT_F1MP:
                status = !(!CAN->RXF1_B.FMNUM1);
                break;
            case CAN_INT_F1FUL:
                status = CAN->RXF1_B.FFULLFLG1;
                break;
            case CAN_INT_F1OVR:
                status = CAN->RXF1_B.FOVRFLG1;
                break;
            case CAN_INT_EWIE:
                status = CAN->ERRSTS_B.ERRWFLG;
                break;
            case CAN_INT_EPIE:
                status = CAN->ERRSTS_B.ERRPFLG;
                break;
            case CAN_INT_BOIE:
                status = CAN->ERRSTS_B.BOFLG;
                break;
            case CAN_INT_LEC:
                status = !(!CAN->ERRSTS_B.LERRC);
                break;
            case CAN_INT_ERR:
                status = CAN->MSTS_B.ERRIFLG;
                break;
            case CAN_INT_WUP:
                status = CAN->MSTS_B.WUPIFLG;
                break;
            case CAN_INT_SLE:
                status = CAN->MSTS_B.SLEEPIFLG;
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
 * @brief  Clears the CAN's interrupt flag.
 *
 * @param  interrupt: specifies the interrupt flag to clear.
 *          The parameter can be any combination of the following values:
 *            @arg CAN_INT_TXME : Transmit mailbox empty Interrupt
 *            @arg CAN_INT_F0FUL: FIFO 0 full Interrupt
 *            @arg CAN_INT_F0OVR: FIFO 0 overrun Interrupt
 *            @arg CAN_INT_F1FUL: FIFO 1 full Interrupt
 *            @arg CAN_INT_F1OVR: FIFO 1 overrun Interrupt
 *            @arg CAN_INT_EWIE : Error warning Interrupt
 *            @arg CAN_INT_EPIE : Error passive Interrupt
 *            @arg CAN_INT_BOIE : Bus-off Interrupt
 *            @arg CAN_INT_LEC  : Last error code Interrupt
 *            @arg CAN_INT_ERR  : Error Interrupt
 *            @arg CAN_INT_WUP  : Wake-up Interrupt
 *            @arg CAN_INT_SLE  : Sleep acknowledge Interrupt
 *
 * @retval  None
 */
void CAN_ClearIntFlag(uint32_t interrupt)
{
    if (interrupt & CAN_INT_TXME)
    {
        CAN->TXSTS_B.REQCFLG0 = BIT_SET;
        CAN->TXSTS_B.REQCFLG1 = BIT_SET;
        CAN->TXSTS_B.REQCFLG2 = BIT_SET;
    }
    if (interrupt & CAN_INT_F0FUL)
    {
        CAN->RXF0_B.FFULLFLG0 = BIT_SET;
    }
    if (interrupt & CAN_INT_F0OVR)
    {
        CAN->RXF0_B.FOVRFLG0 = BIT_SET;
    }
    if (interrupt & CAN_INT_F1FUL)
    {
        CAN->RXF1_B.FFULLFLG1 = BIT_SET;
    }
    if (interrupt & CAN_INT_F1OVR)
    {
        CAN->RXF1_B.FOVRFLG1 = BIT_SET;
    }
    if (interrupt & CAN_INT_EWIE)
    {
        /**  Note : the corresponding Flag is cleared by hardware
         *          depending of the CAN Bus status
         */
        CAN->MSTS_B.ERRIFLG = BIT_SET;
    }
    if (interrupt & CAN_INT_EPIE)
    {
        /**  Note : the corresponding Flag is cleared by hardware
         *          depending of the CAN Bus status
         */
        CAN->MSTS_B.ERRIFLG = BIT_SET;
    }
    if (interrupt & CAN_INT_BOIE)
    {
        /**  Note : the corresponding Flag is cleared by hardware
         *          depending of the CAN Bus status
         */
        CAN->MSTS_B.ERRIFLG = BIT_SET;
    }
    if (interrupt & CAN_INT_LEC)
    {
        CAN->ERRSTS_B.LERRC = 0;
        CAN->MSTS_B.ERRIFLG = BIT_SET;
    }
    if (interrupt & CAN_INT_ERR)
    {
        CAN->ERRSTS_B.LERRC = 0;
        CAN->MSTS_B.ERRIFLG = BIT_SET;
    }
    if (interrupt & CAN_INT_WUP)
    {
        CAN->MSTS_B.WUPIFLG = BIT_SET;
    }
    if (interrupt & CAN_INT_SLE)
    {
        CAN->MSTS_B.SLEEPIFLG = BIT_SET;
    }
}

/**@} end of group CAN_Functions */
/**@} end of group CAN_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
