/**************************************************************************//**
 * @file     CAN.c
 * @version  V1.00
 * $Revision: 15 $
 * $Date: 15/11/26 10:40a $
 * @brief    NUC472/NUC442 CAN driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "NUC472_442.h"
/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CAN_Driver CAN Driver
  @{
*/


/** @addtogroup NUC472_442_CAN_EXPORTED_FUNCTIONS CAN Exported Functions
  @{
*/

#include <stdio.h>


/// @cond HIDDEN_SYMBOLS

#define TSEG1_MIN 2
#define TSEG1_MAX 16
#define TSEG2_MIN 1
#define TSEG2_MAX 8
#define BRP_MIN   1
#define BRP_MAX   1024  /* 6-bit BRP field + 4-bit BRPE field*/
#define SJW_MAX   4
#define BRP_INC   1

static uint32_t GetFreeIF(CAN_T  *tCAN);


//#define DEBUG_PRINTF printf
#define DEBUG_PRINTF(...)

/**
  * @brief    Check if SmartCard slot is presented.
  * @param[in]  tCAN    The base address of can module.
  * @retval   0   IF0 is free
  * @retval   1   IF1 is free
  * @retval   2   No IF is free
  * @details  Search the first free message interface, starting from 0.
  */
static uint32_t GetFreeIF(CAN_T  *tCAN)
{
    if((tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
        return 0;
    else if((tCAN->IF[1].CREQ  & CAN_IF_CREQ_BUSY_Msk) == 0)
        return 1;
    else
        return 2;
}

/**
  * @brief    Enter initialization mode
  * @param[in]    tCAN    The base address of can module.
  * @return   None
  * @details  This function is used to set CAN to enter initialization mode and enable access bit timing
  *           register. After bit timing configuration ready, user must call CAN_LeaveInitMode()
  *           to leave initialization mode and lock bit timing register to let new configuration
  *           take effect.
  */
void CAN_EnterInitMode(CAN_T *tCAN)
{
    tCAN->CON |= CAN_CON_INIT_Msk;
    tCAN->CON |= CAN_CON_CCE_Msk;
}


/**
  * @brief    Leave initialization mode
  * @param[in]    tCAN    The base address of can module.
  * @return   None
  * @details  This function is used to set CAN to leave initialization mode to let
  *           bit timing configuration take effect after configuration ready.
  */
void CAN_LeaveInitMode(CAN_T *tCAN)
{
    tCAN->CON &= (~(CAN_CON_INIT_Msk | CAN_CON_CCE_Msk));

    while(tCAN->CON & CAN_CON_INIT_Msk);       /* Check INIT bit is released */
}

/**
  * @brief    Wait message into message buffer in basic mode.
  * @param[in]    tCAN    The base address of can module.
  * @return   None
  * @details  This function is used to wait message into message buffer in basic mode. Please notice the
  *           function is polling NEWDAT bit of MCON register by while loop and it is used in basic mode.
  */
void CAN_WaitMsg(CAN_T *tCAN)
{
    tCAN->STATUS = 0x0;         /* clr status */

    while (1) {
        if(tCAN->IF[1].MCON & CAN_IF_MCON_NEWDAT_Msk) { /* check new data */
            DEBUG_PRINTF("New Data IN\n");
            break;
        }
        if(tCAN->STATUS & CAN_STATUS_RXOK_Msk)
            DEBUG_PRINTF("Rx OK\n");

        if(tCAN->STATUS & CAN_STATUS_LEC_Msk) {
            DEBUG_PRINTF("Error\n");
        }
    }
}

/**
  * @brief    Get current bit rate
  * @param[in]    tCAN        The base address of can module.
  * @return   Current Bit-Rate (kilo bit per second)
  * @details  Return current CAN bit rate according to the user bit-timing parameter settings
  */
uint32_t CAN_GetCANBitRate(CAN_T  *tCAN)
{
    uint8_t u8Tseg1,u8Tseg2;
    uint32_t u32Bpr;

    u8Tseg1 = (tCAN->BTIME & CAN_BTIME_TSEG1_Msk) >> CAN_BTIME_TSEG1_Pos;
    u8Tseg2 = (tCAN->BTIME & CAN_BTIME_TSEG2_Msk) >> CAN_BTIME_TSEG2_Pos;
    u32Bpr  = (tCAN->BTIME & CAN_BTIME_BRP_Msk) | (tCAN->BRPE << 6);

    return (SystemCoreClock/(u32Bpr+1)/(u8Tseg1 + u8Tseg2 + 3));
}

/**
  * @brief    Switch the CAN into test mode.
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u8TestMask  Specifies the configuration in test modes
  *                             CAN_TEST_BASIC_Msk   : Enable basic mode of test mode
  *                             CAN_TESTR_SILENT_Msk  : Enable silent mode of test mode
  *                             CAN_TESTR_LBACK_Msk   : Enable Loop Back Mode of test mode
  *                             CAN_TESTR_TX0_Msk/CAN_TESTR_TX1_Msk: Control CAN_TX pin bit field
  * @return   None
  * @details  Switch the CAN into test mode. There are four test mode (BASIC/SILENT/LOOPBACK/
  *           LOOPBACK combined SILENT/CONTROL_TX_PIN)could be selected. After setting test mode,user
  *           must call CAN_LeaveInitMode() to let the setting take effect.
  */
void CAN_EnterTestMode(CAN_T *tCAN, uint8_t u8TestMask)
{
    tCAN->CON |= CAN_CON_TEST_Msk;
    tCAN->TEST = u8TestMask;
}


/**
  * @brief    Leave the test mode
  * @param[in]    tCAN    The base address of can module.
  * @return   None
  * @details  This function is used to Leave the test mode (switch into normal mode).
  */
void CAN_LeaveTestMode(CAN_T *tCAN)
{
    tCAN->CON |= CAN_CON_TEST_Msk;
    tCAN->TEST &= ~(CAN_TEST_LBACK_Msk | CAN_TEST_SILENT_Msk | CAN_TEST_BASIC_Msk);
    tCAN->CON &= (~CAN_CON_TEST_Msk);
}

/**
  * @brief    Get the waiting status of a received message.
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u8MsgObj    Specifies the Message object number, from 0 to 31.
  * @retval   non-zero    The corresponding message object has a new data bit is set.
  * @retval   0           No message object has new data.
  * @details  This function is used to get the waiting status of a received message.
  */
uint32_t CAN_IsNewDataReceived(CAN_T *tCAN, uint8_t u8MsgObj)
{
    return (u8MsgObj < 16 ? tCAN->NDAT1 & (1 << u8MsgObj) : tCAN->NDAT2 & (1 << (u8MsgObj-16)));
}


/**
  * @brief    Send CAN message in BASIC mode of test mode
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    pCanMsg     Pointer to the message structure containing data to transmit.
  * @return   TRUE:  Transmission OK
  *           FALSE: Check busy flag of interface 0 is timeout
  * @details  The function is used to send CAN message in BASIC mode of test mode. Before call the API,
  *           the user should be call CAN_EnterTestMode(CAN_TESTR_BASIC) and let CAN controller enter
  *           basic mode of test mode. Please notice IF1 Registers used as Tx Buffer in basic mode.
  */
int32_t CAN_BasicSendMsg(CAN_T *tCAN, STR_CANMSG_T* pCanMsg)
{
    uint32_t i=0;
    while(tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk);

    tCAN->STATUS &= (~CAN_STATUS_TXOK_Msk);

    tCAN->IF[0].CMASK = CAN_IF_CMASK_WRRD_Msk;

    if (pCanMsg->IdType == CAN_STD_ID) {
        /* standard ID*/
        tCAN->IF[0].ARB1 = 0;
        tCAN->IF[0].ARB2 =  (((pCanMsg->Id)&0x7FF)<<2) ;
    } else {
        /* extended ID*/
        tCAN->IF[0].ARB1 = (pCanMsg->Id)&0xFFFF;
        tCAN->IF[0].ARB2 = ((pCanMsg->Id)&0x1FFF0000)>>16  | CAN_IF_ARB2_XTD_Msk;

    }

    if(pCanMsg->FrameType)
        tCAN->IF[0].ARB2 |= CAN_IF_ARB2_DIR_Msk;
    else
        tCAN->IF[0].ARB2 &= (~CAN_IF_ARB2_DIR_Msk);

    tCAN->IF[0].MCON = (tCAN->IF[0].MCON & (~CAN_IF_MCON_DLC_Msk)) | pCanMsg->DLC;
    tCAN->IF[0].DAT_A1 = ((uint16_t)pCanMsg->Data[1]<<8) | pCanMsg->Data[0];
    tCAN->IF[0].DAT_A2 = ((uint16_t)pCanMsg->Data[3]<<8) | pCanMsg->Data[2];
    tCAN->IF[0].DAT_B1 = ((uint16_t)pCanMsg->Data[5]<<8) | pCanMsg->Data[4];
    tCAN->IF[0].DAT_B2 = ((uint16_t)pCanMsg->Data[7]<<8) | pCanMsg->Data[6];

    /* request transmission*/
    tCAN->IF[0].CREQ &= (~CAN_IF_CREQ_BUSY_Msk);
    if(tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) {
        DEBUG_PRINTF("Cannot clear busy for sending ...\n");
        return FALSE;
    }

    tCAN->IF[0].CREQ |= CAN_IF_CREQ_BUSY_Msk;                          // sending

    for ( i=0; i<0xFFFFF; i++) {
        if((tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0) break;
    }

    if ( i >= 0xFFFFF ) {
        DEBUG_PRINTF("Cannot send out...\n");
        return FALSE;
    }

    return TRUE;
}


/**
  * @brief    Get a message information in BASIC mode.
  *
  * @param[in]    tCAN        The base address of can module.
  * @param[out]    pCanMsg     Pointer to the message structure where received data is copied.
  *
  * @return   FALSE  No any message received. \n
  *           TRUE   Receive a message success.
  *
  */
int32_t CAN_BasicReceiveMsg(CAN_T *tCAN, STR_CANMSG_T* pCanMsg)
{
    if((tCAN->IF[1].MCON & CAN_IF_MCON_NEWDAT_Msk) == 0) { /* In basic mode, receive data always save in IF2 */
        return FALSE;
    }

    tCAN->STATUS &= (~CAN_STATUS_RXOK_Msk);

    tCAN->IF[1].CMASK = CAN_IF_CMASK_ARB_Msk
                        | CAN_IF_CMASK_CONTROL_Msk
                        | CAN_IF_CMASK_DATAA_Msk
                        | CAN_IF_CMASK_DATAB_Msk;

    if((tCAN->IF[1].ARB2 & CAN_IF_ARB2_XTD_Msk) == 0) {
        /* standard ID*/
        pCanMsg->IdType = CAN_STD_ID;
        pCanMsg->Id = (tCAN->IF[1].ARB2 >> 2) & 0x07FF;

    } else {
        /* extended ID*/
        pCanMsg->IdType = CAN_EXT_ID;
        pCanMsg->Id  = (tCAN->IF[1].ARB2 & 0x1FFF)<<16;
        pCanMsg->Id |= (uint32_t)tCAN->IF[1].ARB1;
    }

    pCanMsg->FrameType = !((tCAN->IF[1].ARB2 & CAN_IF_ARB2_DIR_Msk) >> CAN_IF_ARB2_DIR_Pos);

    pCanMsg->DLC     = tCAN->IF[1].MCON & CAN_IF_MCON_DLC_Msk;
    pCanMsg->Data[0] = tCAN->IF[1].DAT_A1 & CAN_IF_DAT_A1_DATA0_Msk;
    pCanMsg->Data[1] = (tCAN->IF[1].DAT_A1 & CAN_IF_DAT_A1_DATA1_Msk) >> CAN_IF_DAT_A1_DATA1_Pos;
    pCanMsg->Data[2] = tCAN->IF[1].DAT_A2 & CAN_IF_DAT_A2_DATA2_Msk;
    pCanMsg->Data[3] = (tCAN->IF[1].DAT_A2 & CAN_IF_DAT_A2_DATA3_Msk) >> CAN_IF_DAT_A2_DATA3_Pos;
    pCanMsg->Data[4] = tCAN->IF[1].DAT_B1 & CAN_IF_DAT_B1_DATA4_Msk;
    pCanMsg->Data[5] = (tCAN->IF[1].DAT_B1 & CAN_IF_DAT_B1_DATA5_Msk) >> CAN_IF_DAT_B1_DATA5_Pos;
    pCanMsg->Data[6] = tCAN->IF[1].DAT_B2 & CAN_IF_DAT_B2_DATA6_Msk;
    pCanMsg->Data[7] = (tCAN->IF[1].DAT_B2 & CAN_IF_DAT_B2_DATA7_Msk) >> CAN_IF_DAT_B2_DATA7_Pos;

    return TRUE;
}

/**
  * @brief    Set Rx message object
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u8MsgObj    Specifies the Message object number, from 0 to 31.
  * @param[in]    u8idType    Specifies the identifier type of the frames that will be transmitted
  *                       This parameter can be one of the following values:
  *                       CAN_STD_ID (standard ID, 11-bit)
  *                       CAN_EXT_ID (extended ID, 29-bit)
  * @param[in]    u32id       Specifies the identifier used for acceptance filtering.
  * @param[in]    u8singleOrFifoLast  Specifies the end-of-buffer indicator.
  *                                 This parameter can be one of the following values:
  *                                 TRUE: for a single receive object or a FIFO receive object that is the last one of the FIFO.
  *                                 FALSE: for a FIFO receive object that is not the last one.
  * @retval   TRUE           SUCCESS
  * @retval   FALSE   No useful interface
  * @details  The function is used to configure a receive message object.
  */
int32_t CAN_SetRxMsgObj(CAN_T  *tCAN, uint8_t u8MsgObj, uint8_t u8idType, uint32_t u32id, uint8_t u8singleOrFifoLast)
{
    uint8_t u8MsgIfNum=0;

    if ((u8MsgIfNum = GetFreeIF(tCAN)) == 2) {                      /* Check Free Interface for configure */
        return FALSE;
    }
    /* Command Setting */
    tCAN->IF[u8MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                 CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

    if (u8idType == CAN_STD_ID) { /* According STD/EXT ID format,Configure Mask and Arbitration register */
        tCAN->IF[u8MsgIfNum].ARB1 = 0;
        tCAN->IF[u8MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | (u32id & 0x7FF)<< 2;
    } else {
        tCAN->IF[u8MsgIfNum].ARB1 = u32id & 0xFFFF;
        tCAN->IF[u8MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | CAN_IF_ARB2_XTD_Msk | (u32id & 0x1FFF0000)>>16;
    }

    tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
    if(u8singleOrFifoLast)
        tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_EOB_Msk;
    else
        tCAN->IF[u8MsgIfNum].MCON &= (~CAN_IF_MCON_EOB_Msk);

    tCAN->IF[u8MsgIfNum].DAT_A1  = 0;
    tCAN->IF[u8MsgIfNum].DAT_A2  = 0;
    tCAN->IF[u8MsgIfNum].DAT_B1  = 0;
    tCAN->IF[u8MsgIfNum].DAT_B2  = 0;

    tCAN->IF[u8MsgIfNum].CREQ = 1 + u8MsgObj;

    return TRUE;
}


/**
  * @brief    Gets the message
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u8MsgObj    Specifies the Message object number, from 0 to 31.
  * @param[in]    u8Release   Specifies the message release indicator.
  *                       This parameter can be one of the following values:
  *                        TRUE: the message object is released when getting the data.
  *                        FALSE:the message object is not released.
  * @param[out]    pCanMsg     Pointer to the message structure where received data is copied.
  * @retval   TRUE   Success
  * @retval   FALSE    No any message received
  * @details  Gets the message, if received.
  */
int32_t CAN_ReadMsgObj(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8Release, STR_CANMSG_T* pCanMsg)
{
    if (!CAN_IsNewDataReceived(tCAN, u8MsgObj)) {
        return FALSE;
    }

    tCAN->STATUS &= (~CAN_STATUS_RXOK_Msk);

    /* read the message contents*/
    tCAN->IF[1].CMASK = CAN_IF_CMASK_MASK_Msk
                        | CAN_IF_CMASK_ARB_Msk
                        | CAN_IF_CMASK_CONTROL_Msk
                        | CAN_IF_CMASK_CLRINTPND_Msk
                        | (u8Release ? CAN_IF_CMASK_TXRQSTNEWDAT_Msk : 0)
                        | CAN_IF_CMASK_DATAA_Msk
                        | CAN_IF_CMASK_DATAB_Msk;

    tCAN->IF[1].CREQ = 1 + u8MsgObj;

    while (tCAN->IF[1].CREQ & CAN_IF_CREQ_BUSY_Msk) {
        /*Wait*/
    }

    if ((tCAN->IF[1].ARB2 & CAN_IF_ARB2_XTD_Msk) == 0) {
        /* standard ID*/
        pCanMsg->IdType = CAN_STD_ID;
        pCanMsg->Id     = (tCAN->IF[1].ARB2 & CAN_IF_ARB2_ID_Msk) >> 2;
    } else {
        /* extended ID*/
        pCanMsg->IdType = CAN_EXT_ID;
        pCanMsg->Id  = (((tCAN->IF[1].ARB2) & 0x1FFF)<<16) | tCAN->IF[1].ARB1;
    }

    pCanMsg->DLC     = tCAN->IF[1].MCON & CAN_IF_MCON_DLC_Msk;
    pCanMsg->Data[0] = tCAN->IF[1].DAT_A1 & CAN_IF_DAT_A1_DATA0_Msk;
    pCanMsg->Data[1] = (tCAN->IF[1].DAT_A1 & CAN_IF_DAT_A1_DATA1_Msk) >> CAN_IF_DAT_A1_DATA1_Pos;
    pCanMsg->Data[2] = tCAN->IF[1].DAT_A2 & CAN_IF_DAT_A2_DATA2_Msk;
    pCanMsg->Data[3] = (tCAN->IF[1].DAT_A2 & CAN_IF_DAT_A2_DATA3_Msk) >> CAN_IF_DAT_A2_DATA3_Pos;
    pCanMsg->Data[4] = tCAN->IF[1].DAT_B1 & CAN_IF_DAT_B1_DATA4_Msk;
    pCanMsg->Data[5] = (tCAN->IF[1].DAT_B1 & CAN_IF_DAT_B1_DATA5_Msk) >> CAN_IF_DAT_B1_DATA5_Pos;
    pCanMsg->Data[6] = tCAN->IF[1].DAT_B2 & CAN_IF_DAT_B2_DATA6_Msk;
    pCanMsg->Data[7] = (tCAN->IF[1].DAT_B2 & CAN_IF_DAT_B2_DATA7_Msk) >> CAN_IF_DAT_B2_DATA7_Pos;

    return TRUE;
}

static int can_update_spt(int sampl_pt, int tseg, int *tseg1, int *tseg2)
{
    *tseg2 = tseg + 1 - (sampl_pt * (tseg + 1)) / 1000;
    if (*tseg2 < TSEG2_MIN)
        *tseg2 = TSEG2_MIN;
    if (*tseg2 > TSEG2_MAX)
        *tseg2 = TSEG2_MAX;
    *tseg1 = tseg - *tseg2;
    if (*tseg1 > TSEG1_MAX) {
        *tseg1 = TSEG1_MAX;
        *tseg2 = tseg - *tseg1;
    }
    return 1000 * (tseg + 1 - *tseg2) / (tseg + 1);
}

/// @endcond HIDDEN_SYMBOLS


/**
  * @brief    The function is used to set bus timing parameter according current clock and target baud-rate.
  *
  * @param[in]    tCAN        The base address of can module
  * @param[in]    u32BaudRate The target CAN baud-rate. The range of u32BaudRate is 1~1000KHz
  *
  * @return   u32CurrentBitRate  Real baud-rate value
  */
uint32_t CAN_SetBaudRate(CAN_T *tCAN, uint32_t u32BaudRate)
{
    long rate;
    long best_error = 1000000000, error = 0;
    int best_tseg = 0, best_brp = 0, brp = 0;
    int tsegall, tseg = 0, tseg1 = 0, tseg2 = 0;
    int spt_error = 1000, spt = 0, sampl_pt;
    uint64_t clock_freq = 0;
    uint32_t sjw = 1;

    CAN_EnterInitMode(tCAN);

    SystemCoreClockUpdate();

    clock_freq = SystemCoreClock;

    if(u32BaudRate >= 1000000)
        u32BaudRate = 1000000;

    /* Use CIA recommended sample points */
    if (u32BaudRate > 800000)
        sampl_pt = 750;
    else if (u32BaudRate > 500000)
        sampl_pt = 800;
    else
        sampl_pt = 875;

    /* tseg even = round down, odd = round up */
    for (tseg = (TSEG1_MAX + TSEG2_MAX) * 2 + 1; tseg >= (TSEG1_MIN + TSEG2_MIN) * 2; tseg--) {
        tsegall = 1 + tseg / 2;
        /* Compute all possible tseg choices (tseg=tseg1+tseg2) */
        brp = clock_freq / (tsegall * u32BaudRate) + tseg % 2;
        /* chose brp step which is possible in system */
        brp = (brp / BRP_INC) * BRP_INC;

        if ((brp < BRP_MIN) || (brp > BRP_MAX))
            continue;
        rate = clock_freq / (brp * tsegall);

        error = u32BaudRate - rate;

        /* tseg brp biterror */
        if (error < 0)
            error = -error;
        if (error > best_error)
            continue;
        best_error = error;
        if (error == 0) {
            spt = can_update_spt(sampl_pt, tseg / 2, &tseg1, &tseg2);
            error = sampl_pt - spt;
            if (error < 0)
                error = -error;
            if (error > spt_error)
                continue;
            spt_error = error;
        }
        best_tseg = tseg / 2;
        best_brp = brp;

        if (error == 0)
            break;
    }

    spt = can_update_spt(sampl_pt, best_tseg, &tseg1, &tseg2);

    /* check for sjw user settings */
    /* bt->sjw is at least 1 -> sanitize upper bound to sjw_max */
    if (sjw > SJW_MAX)
        sjw = SJW_MAX;
    /* bt->sjw must not be higher than tseg2 */
    if (tseg2 < sjw)
        sjw = tseg2;

    /* real bit-rate */
    u32BaudRate = clock_freq / (best_brp * (tseg1 + tseg2 + 1));

    tCAN->BTIME = ((uint32_t)(tseg2 - 1) << CAN_BTIME_TSEG2_Pos) | ((uint32_t)(tseg1 - 1) << CAN_BTIME_TSEG1_Pos) |
                  ((best_brp - 1) & CAN_BTIME_BRP_Msk) | (sjw << CAN_BTIME_SJW_Pos);
    tCAN->BRPE  = ((best_brp - 1) >> 6) & 0x0F;

    //printf("\n bitrate = %d \n", CAN_GetCANBitRate(tCAN));

    CAN_LeaveInitMode(tCAN);

    return u32BaudRate;
}

/**
  * @brief    The function is used to disable all CAN interrupt.
  *
  * @param[in]    tCAN  The base address of can module
  *
  * @return   None
  */
void CAN_Close(CAN_T *tCAN)
{
    CAN_DisableInt(tCAN, (CAN_CON_IE_Msk|CAN_CON_SIE_Msk|CAN_CON_EIE_Msk));
}

/**
  * @brief    The function is sets bus timing parameter according current clock and target baud-rate. And set CAN operation mode.
  *
  * @param[in]    tCAN        The base address of can module
  * @param[in]    u32BaudRate The target CAN baud-rate. The range of u32BaudRate is 1~1000KHz
  * @param[in]    u32Mode     The CAN operation mode. ( \ref CAN_NORMAL_MODE / \ref CAN_BASIC_MODE)
  *
  * @return   u32CurrentBitRate  Real baud-rate value
  */
uint32_t CAN_Open(CAN_T *tCAN, uint32_t u32BaudRate, uint32_t u32Mode)
{
    uint32_t u32CurrentBitRate;

    u32CurrentBitRate = CAN_SetBaudRate(tCAN, u32BaudRate);

    if(u32Mode == CAN_BASIC_MODE)
        CAN_EnterTestMode(tCAN, CAN_TEST_BASIC_Msk);
    else
        tCAN->CON &= ~CAN_CON_TEST_Msk;

    return u32CurrentBitRate;
}

/**
  * @brief    The function is used to configure a transmit object.
  *
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u32MsgNum   Specifies the Message object number, from 0 to 31
  * @param[in]    pCanMsg     Pointer to the message structure where received data is copied.
  *
  * @return   FALSE: No useful interface. \n
  *           TRUE : Config message object success.
  *
  */
int32_t CAN_SetTxMsg(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg)
{
    uint8_t u8MsgIfNum=0;
    uint32_t i=0;

    while((u8MsgIfNum = GetFreeIF(tCAN)) == 2) {
        i++;
        if(i > 0x10000000)
            return FALSE;
    }

    /* update the contents needed for transmission*/
    tCAN->IF[u8MsgIfNum].CMASK = 0xF3;  /*CAN_CMASK_WRRD_Msk | CAN_CMASK_MASK_Msk | CAN_CMASK_ARB_Msk
                                           | CAN_CMASK_CONTROL_Msk | CAN_CMASK_DATAA_Msk  | CAN_CMASK_DATAB_Msk ; */

    if (pCanMsg->IdType == CAN_STD_ID) {
        /* standard ID*/
        tCAN->IF[u8MsgIfNum].ARB1 = 0;
        tCAN->IF[u8MsgIfNum].ARB2 =  (((pCanMsg->Id)&0x7FF)<<2) | CAN_IF_ARB2_DIR_Msk | CAN_IF_ARB2_MSGVAL_Msk;
    } else {
        /* extended ID*/
        tCAN->IF[u8MsgIfNum].ARB1 = (pCanMsg->Id)&0xFFFF;
        tCAN->IF[u8MsgIfNum].ARB2 = ((pCanMsg->Id)&0x1FFF0000)>>16 | CAN_IF_ARB2_DIR_Msk
                                    | CAN_IF_ARB2_XTD_Msk | CAN_IF_ARB2_MSGVAL_Msk;
    }

    if(pCanMsg->FrameType)
        tCAN->IF[u8MsgIfNum].ARB2 |=   CAN_IF_ARB2_DIR_Msk;
    else
        tCAN->IF[u8MsgIfNum].ARB2 &= (~CAN_IF_ARB2_DIR_Msk);

    tCAN->IF[u8MsgIfNum].DAT_A1 = ((uint16_t)pCanMsg->Data[1]<<8) | pCanMsg->Data[0];
    tCAN->IF[u8MsgIfNum].DAT_A2 = ((uint16_t)pCanMsg->Data[3]<<8) | pCanMsg->Data[2];
    tCAN->IF[u8MsgIfNum].DAT_B1 = ((uint16_t)pCanMsg->Data[5]<<8) | pCanMsg->Data[4];
    tCAN->IF[u8MsgIfNum].DAT_B2 = ((uint16_t)pCanMsg->Data[7]<<8) | pCanMsg->Data[6];

    tCAN->IF[u8MsgIfNum].MCON   =  CAN_IF_MCON_NEWDAT_Msk | pCanMsg->DLC |CAN_IF_MCON_TXIE_Msk | CAN_IF_MCON_EOB_Msk;
    tCAN->IF[u8MsgIfNum].CREQ   = 1 + u32MsgNum;

    return TRUE;
}

/**
  * @brief    Set transmit request bit
  *
  * @param[in]    tCAN         The base address of can module.
  * @param[in]    u32MsgNum    Specifies the Message object number, from 0 to 31.
  *
  * @return   TRUE: Start transmit message.
  */
int32_t CAN_TriggerTxMsg(CAN_T  *tCAN, uint32_t u32MsgNum)
{
    STR_CANMSG_T rMsg;
    CAN_ReadMsgObj(tCAN, u32MsgNum,TRUE, &rMsg);
    tCAN->IF[0].CMASK  = CAN_IF_CMASK_WRRD_Msk |CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    tCAN->IF[0].CREQ  = 1 + u32MsgNum;

    return TRUE;
}

/**
  * @brief    Enable CAN interrupt
  *
  * @param[in]    tCAN       The base address of can module.
  * @param[in]    u32Mask    Interrupt Mask. ( \ref CAN_CON_IE_Msk / \ref CAN_CON_SIE_Msk / \ref CAN_CON_EIE_Msk)
  *
  * @return   None
  */
void CAN_EnableInt(CAN_T *tCAN, uint32_t u32Mask)
{
    CAN_EnterInitMode(tCAN);

    tCAN->CON = (tCAN->CON & ~(CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk)) |
                (u32Mask & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk));


    CAN_LeaveInitMode(tCAN);
}

/**
  * @brief    Disable CAN interrupt
  *
  * @param[in]    tCAN       The base address of can module.
  * @param[in]    u32Mask    Interrupt Mask. ( \ref CAN_CON_IE_Msk / \ref CAN_CON_SIE_Msk / \ref CAN_CON_EIE_Msk)
  *
  * @return   None
  */
void CAN_DisableInt(CAN_T *tCAN, uint32_t u32Mask)
{
    CAN_EnterInitMode(tCAN);

    tCAN->CON = tCAN->CON & ~((u32Mask & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk)));

    CAN_LeaveInitMode(tCAN);
}


/**
  * @brief    The function is used to configure a receive message object
  *
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u32MsgNum   Specifies the Message object number, from 0 to 31
  * @param[in]    u32IDType   Specifies the identifier type of the frames that will be transmitted. ( \ref CAN_STD_ID / \ref CAN_EXT_ID)
  * @param[in]    u32ID       Specifies the identifier used for acceptance filtering.
  *
  * @return   FALSE: No useful interface \n
  *           TRUE : Configure a receive message object success.
  *
  */
int32_t CAN_SetRxMsg(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32IDType, uint32_t u32ID)
{
    uint32_t u32TimeOutCount = 0;

    while(CAN_SetRxMsgObj(tCAN, u32MsgNum, u32IDType, u32ID, TRUE) == FALSE) {
        u32TimeOutCount++;

        if(u32TimeOutCount >= 0x10000000) return FALSE;
    }

    return TRUE;
}

/**
  * @brief    The function is used to configure several receive message objects
  *
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u32MsgNum   The starting MSG RAM number. (0 ~ 31)
  * @param[in]    u32MsgCount the number of MSG RAM of the FIFO.
  * @param[in]    u32IDType   Specifies the identifier type of the frames that will be transmitted. ( \ref CAN_STD_ID / \ref CAN_EXT_ID)
  * @param[in]    u32ID       Specifies the identifier used for acceptance filtering.
  *
  * @return   FALSE: No useful interface \n
  *           TRUE : Configure receive message objects success.
  *
  */
int32_t CAN_SetMultiRxMsg(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32MsgCount, uint32_t u32IDType, uint32_t u32ID)
{
    uint32_t i = 0;
    uint32_t u32TimeOutCount;
    uint32_t u32EOB_Flag = 0;

    for(i= 1; i < u32MsgCount; i++) {
        u32TimeOutCount = 0;

        u32MsgNum += (i - 1);

        if(i == u32MsgCount) u32EOB_Flag = 1;

        while(CAN_SetRxMsgObj(tCAN, u32MsgNum, u32IDType, u32ID, u32EOB_Flag) == FALSE) {
            u32TimeOutCount++;

            if(u32TimeOutCount >= 0x10000000) return FALSE;
        }
    }

    return TRUE;
}


/**
  * @brief    Send CAN message.
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u32MsgNum   Specifies the Message object number, from 0 to 31
  * @param[in]    pCanMsg     Pointer to the message structure where received data is copied.
  *
  * @return   FALSE: When operation in basic mode: Transmit message time out, or when operation in normal mode: No useful interface. \n
  *           TRUE : Transmit Message success.
  */
int32_t CAN_Transmit(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg)
{
    if((tCAN->CON & CAN_CON_TEST_Msk) && (tCAN->TEST & CAN_TEST_BASIC_Msk)) {
        return (CAN_BasicSendMsg(tCAN, pCanMsg));
    } else {
        if(CAN_SetTxMsg(tCAN, u32MsgNum, pCanMsg) == FALSE)
            return FALSE;
        CAN_TriggerTxMsg(tCAN, u32MsgNum);
    }

    return TRUE;
}


/**
  * @brief    Gets the message, if received.
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u32MsgNum   Specifies the Message object number, from 0 to 31
  * @param[out]    pCanMsg     Pointer to the message structure where received data is copied.
  *
  * @return   FALSE: No any message received. \n
  *           TRUE : Receive Message success.
  */
int32_t CAN_Receive(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg)
{
    if((tCAN->CON & CAN_CON_TEST_Msk) && (tCAN->TEST & CAN_TEST_BASIC_Msk)) {
        return (CAN_BasicReceiveMsg(tCAN, pCanMsg));
    } else {
        return CAN_ReadMsgObj(tCAN, u32MsgNum, TRUE, pCanMsg);
    }
}

/**
  * @brief    Clear interrupt pending bit.
  * @param[in]    tCAN        The base address of can module.
  * @param[in]    u32MsgNum   Specifies the Message object number, from 0 to 31
  *
  * @return   None
  *
  */
void CAN_CLR_INT_PENDING_BIT(CAN_T *tCAN, uint8_t u32MsgNum)
{
    uint32_t u32MsgIfNum = 0;
    uint32_t u32IFBusyCount = 0;

    while(u32IFBusyCount < 0x10000000) {
        if((tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0) {
            u32MsgIfNum = 0;
            break;
        } else if((tCAN->IF[1].CREQ  & CAN_IF_CREQ_BUSY_Msk) == 0) {
            u32MsgIfNum = 1;
            break;
        }

        u32IFBusyCount++;
    }

    tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_CLRINTPND_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    tCAN->IF[u32MsgIfNum].CREQ = 1 + u32MsgNum;

}


/*@}*/ /* end of group NUC472_442_CAN_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_CAN_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


