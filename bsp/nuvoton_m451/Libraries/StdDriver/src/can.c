/**************************************************************************//**
 * @file     can.c
 * @version  V2.00
 * $Revision: 8 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series CAN driver source file
 *
 * @note
 * Copyright (C) 2014~2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M451Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CAN_Driver CAN Driver
  @{
*/

/** @addtogroup CAN_EXPORTED_FUNCTIONS CAN Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS

#if defined(CAN1)
static uint8_t gu8LockCanIf[2][2] = {0};    // The chip has two CANs.
#elif defined(CAN0) || defined(CAN)
static uint8_t gu8LockCanIf[1][2] = {0};    // The chip only has one CAN.
#endif

#define RETRY_COUNTS    (0x10000000)

//#define DEBUG_PRINTF printf
#define DEBUG_PRINTF(...)

/**
  * @brief Check if any interface is available then lock it for usage.
  * @param[in] tCAN The pointer to CAN module base address.
  * @retval 0 IF0 is free
  * @retval 1 IF1 is free
  * @retval 2 No IF is free
  * @details Search the first free message interface, starting from 0. If a interface is
  *          available, set a flag to lock the interface.
  */
static uint32_t LockIF(CAN_T *tCAN)
{
    uint32_t u32CanNo;
    uint32_t u32FreeIfNo;
    uint32_t u32IntMask;

#if defined(CAN1)
    u32CanNo = (tCAN == CAN1) ? 1 : 0;
#else // defined(CAN0) || defined(CAN)
    u32CanNo = 0;
#endif

    u32FreeIfNo = 2;

    /* Disable CAN interrupt */
    u32IntMask = tCAN->CON & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);
    tCAN->CON = tCAN->CON & ~(CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);

    /* Check interface 1 is available or not */
    if((tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
    {
        if(gu8LockCanIf[u32CanNo][0] == FALSE)
        {
            gu8LockCanIf[u32CanNo][0] = TRUE;
            u32FreeIfNo = 0;
        }
    }

    /* Or check interface 2 is available or not */
    if(u32FreeIfNo == 2 && (tCAN->IF[1].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
    {
        if(gu8LockCanIf[u32CanNo][1] == FALSE)
        {
            gu8LockCanIf[u32CanNo][1] = TRUE;
            u32FreeIfNo = 1;
        }
    }

    /* Enable CAN interrupt */
    tCAN->CON |= u32IntMask;

    return u32FreeIfNo;
}

/**
  * @brief Check if any interface is available in a time limitation then lock it for usage.
  * @param[in] tCAN The pointer to CAN module base address.
  * @retval 0 IF0 is free
  * @retval 1 IF1 is free
  * @retval 2 No IF is free
  * @details Search the first free message interface, starting from 0. If no interface is
  *          it will try again until time out. If a interface is available,  set a flag to
  *          lock the interface.
  */
static uint32_t LockIF_TL(CAN_T *tCAN)
{
    uint32_t u32Count;
    uint32_t u32FreeIfNo;

    for(u32Count = 0; u32Count < RETRY_COUNTS; u32Count++)
    {
        if((u32FreeIfNo = LockIF(tCAN)) != 2)
            return u32FreeIfNo;
    }

    return u32FreeIfNo;
}

/**
  * @brief Release locked interface.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32Info The interface number, 0 or 1.
  * @return none
  * @details Release the locked interface.
  */
static void ReleaseIF(CAN_T *tCAN, uint32_t u32IfNo)
{
    uint32_t u32IntMask;
    uint32_t u32CanNo;

    if(u32IfNo >= 2)
        return;

#if defined(CAN1)
    u32CanNo = (tCAN == CAN1) ? 1 : 0;
#else // defined(CAN0) || defined(CAN)
    u32CanNo = 0;
#endif

    /* Disable CAN interrupt */
    u32IntMask = tCAN->CON & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);
    tCAN->CON = tCAN->CON & ~(CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);

    gu8LockCanIf[u32CanNo][u32IfNo] = FALSE;

    /* Enable CAN interrupt */
    tCAN->CON |= u32IntMask;
}

/**
  * @brief Enter initialization mode
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] Following values can be used.
  *            \ref CAN_CON_DAR_Msk Disable automatic retransmission.
  *            \ref CAN_CON_EIE_Msk Enable error interrupt.
  *            \ref CAN_CON_SIE_Msk Enable status interrupt.
  *            \ref CAN_CON_IE_Msk CAN interrupt.
  * @return None
  * @details This function is used to set CAN to enter initialization mode and enable access bit timing
  *          register. After bit timing configuration ready, user must call CAN_LeaveInitMode()
  *          to leave initialization mode and lock bit timing register to let new configuration
  *          take effect.
  */
void CAN_EnterInitMode(CAN_T *tCAN, uint8_t u8Mask)
{
    tCAN->CON = u8Mask | (CAN_CON_INIT_Msk | CAN_CON_CCE_Msk);
}


/**
  * @brief Leave initialization mode
  * @param[in] tCAN The pointer to CAN module base address.
  * @return None
  * @details This function is used to set CAN to leave initialization mode to let
  *          bit timing configuration take effect after configuration ready.
  */
void CAN_LeaveInitMode(CAN_T *tCAN)
{
    tCAN->CON &= (~(CAN_CON_INIT_Msk | CAN_CON_CCE_Msk));
    while(tCAN->CON & CAN_CON_INIT_Msk); /* Check INIT bit is released */
}

/**
  * @brief Wait message into message buffer in basic mode.
  * @param[in] tCAN The pointer to CAN module base address.
  * @return None
  * @details This function is used to wait message into message buffer in basic mode. Please notice the
  *          function is polling NEWDAT bit of MCON register by while loop and it is used in basic mode.
  */
void CAN_WaitMsg(CAN_T *tCAN)
{
    tCAN->STATUS = 0x0; /* clr status */

    while(1)
    {
        if(tCAN->IF[1].MCON & CAN_IF_MCON_NEWDAT_Msk)   /* check new data */
        {
            DEBUG_PRINTF("New Data IN\n");
            break;
        }

        if(tCAN->STATUS & CAN_STATUS_RXOK_Msk)
            DEBUG_PRINTF("Rx OK\n");

        if(tCAN->STATUS & CAN_STATUS_LEC_Msk)
        {
            DEBUG_PRINTF("Error\n");
        }
    }
}

/**
  * @brief Get current bit rate
  * @param[in] tCAN The pointer to CAN module base address.
  * @return Current Bit-Rate (kilo bit per second)
  * @details Return current CAN bit rate according to the user bit-timing parameter settings
  */
uint32_t CAN_GetCANBitRate(CAN_T *tCAN)
{
    uint8_t u8Tseg1, u8Tseg2;
    uint32_t u32Bpr;

    u8Tseg1 = (tCAN->BTIME & CAN_BTIME_TSEG1_Msk) >> CAN_BTIME_TSEG1_Pos;
    u8Tseg2 = (tCAN->BTIME & CAN_BTIME_TSEG2_Msk) >> CAN_BTIME_TSEG2_Pos;
    u32Bpr  = (tCAN->BTIME & CAN_BTIME_BRP_Msk) | (tCAN->BRPE << 6);

    return (SystemCoreClock / (u32Bpr + 1) / (u8Tseg1 + u8Tseg2 + 3));
}

/**
  * @brief Switch the CAN into test mode.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u8TestMask Specifies the configuration in test modes
  *                       \ref CAN_TEST_BASIC_Msk Enable basic mode of test mode
  *                       \ref CAN_TEST_SILENT_Msk Enable silent mode of test mode
  *                       \ref CAN_TEST_LBACK_Msk Enable Loop Back Mode of test mode
  *                       \ref CAN_TEST_TX0_Msk / \ref CAN_TEST_TX1_Msk Control CAN_TX pin bit field
  * @return None
  * @details Switch the CAN into test mode. There are four test mode (BASIC/SILENT/LOOPBACK/
  *          LOOPBACK combined SILENT/CONTROL_TX_PIN)could be selected. After setting test mode,user
  *          must call CAN_LeaveInitMode() to let the setting take effect.
  */
void CAN_EnterTestMode(CAN_T *tCAN, uint8_t u8TestMask)
{
    tCAN->CON |= CAN_CON_TEST_Msk;
    tCAN->TEST = u8TestMask;
}


/**
  * @brief Leave the test mode
  * @param[in] tCAN The pointer to CAN module base address.
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
  * @brief Get the waiting status of a received message.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u8MsgObj Specifies the Message object number, from 0 to 31.
  * @retval non-zero The corresponding message object has a new data bit is set.
  * @retval 0 No message object has new data.
  * @details This function is used to get the waiting status of a received message.
  */
uint32_t CAN_IsNewDataReceived(CAN_T *tCAN, uint8_t u8MsgObj)
{
    return (u8MsgObj < 16 ? tCAN->NDAT1 & (1 << u8MsgObj) : tCAN->NDAT2 & (1 << (u8MsgObj - 16)));
}


/**
  * @brief Send CAN message in BASIC mode of test mode
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] pCanMsg Pointer to the message structure containing data to transmit.
  * @return TRUE:  Transmission OK
  *         FALSE: Check busy flag of interface 0 is timeout
  * @details The function is used to send CAN message in BASIC mode of test mode. Before call the API,
  *          the user should be call CAN_EnterTestMode(CAN_TEST_BASIC) and let CAN controller enter
  *          basic mode of test mode. Please notice IF1 Registers used as Tx Buffer in basic mode.
  */
int32_t CAN_BasicSendMsg(CAN_T *tCAN, STR_CANMSG_T* pCanMsg)
{
    uint32_t i = 0;
    while(tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk);

    tCAN->STATUS &= (~CAN_STATUS_TXOK_Msk);

    if(pCanMsg->IdType == CAN_STD_ID)
    {
        /* standard ID*/
        tCAN->IF[0].ARB1 = 0;
        tCAN->IF[0].ARB2 = (((pCanMsg->Id) & 0x7FF) << 2) ;
    }
    else
    {
        /* extended ID*/
        tCAN->IF[0].ARB1 = (pCanMsg->Id) & 0xFFFF;
        tCAN->IF[0].ARB2 = ((pCanMsg->Id) & 0x1FFF0000) >> 16  | CAN_IF_ARB2_XTD_Msk;

    }

    if(pCanMsg->FrameType)
        tCAN->IF[0].ARB2 |= CAN_IF_ARB2_DIR_Msk;
    else
        tCAN->IF[0].ARB2 &= (~CAN_IF_ARB2_DIR_Msk);

    tCAN->IF[0].MCON = (tCAN->IF[0].MCON & (~CAN_IF_MCON_DLC_Msk)) | pCanMsg->DLC;
    tCAN->IF[0].DAT_A1 = ((uint16_t)pCanMsg->Data[1] << 8) | pCanMsg->Data[0];
    tCAN->IF[0].DAT_A2 = ((uint16_t)pCanMsg->Data[3] << 8) | pCanMsg->Data[2];
    tCAN->IF[0].DAT_B1 = ((uint16_t)pCanMsg->Data[5] << 8) | pCanMsg->Data[4];
    tCAN->IF[0].DAT_B2 = ((uint16_t)pCanMsg->Data[7] << 8) | pCanMsg->Data[6];

    /* request transmission*/
    tCAN->IF[0].CREQ &= (~CAN_IF_CREQ_BUSY_Msk);
    if(tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
        DEBUG_PRINTF("Cannot clear busy for sending ...\n");
        return FALSE;
    }

    tCAN->IF[0].CREQ |= CAN_IF_CREQ_BUSY_Msk;                          // sending

    for(i = 0; i < 0xFFFFF; i++)
    {
        if((tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0)
            break;
    }

    if(i >= 0xFFFFF)
    {
        DEBUG_PRINTF("Cannot send out...\n");
        return FALSE;
    }

    return TRUE;
}

/**
  * @brief Get a message information in BASIC mode.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] pCanMsg Pointer to the message structure where received data is copied.
  *
  * @return FALSE No any message received.
  *         TRUE Receive a message success.
  *
  */
int32_t CAN_BasicReceiveMsg(CAN_T *tCAN, STR_CANMSG_T* pCanMsg)
{

    if((tCAN->IF[1].MCON & CAN_IF_MCON_NEWDAT_Msk) == 0)   /* In basic mode, receive data always save in IF2 */
    {
        return FALSE;
    }

    tCAN->STATUS &= (~CAN_STATUS_RXOK_Msk);

    tCAN->IF[1].CMASK = CAN_IF_CMASK_ARB_Msk
                        | CAN_IF_CMASK_CONTROL_Msk
                        | CAN_IF_CMASK_DATAA_Msk
                        | CAN_IF_CMASK_DATAB_Msk;

    if((tCAN->IF[1].ARB2 & CAN_IF_ARB2_XTD_Msk) == 0)
    {
        /* standard ID*/
        pCanMsg->IdType = CAN_STD_ID;
        pCanMsg->Id = (tCAN->IF[1].ARB2 >> 2) & 0x07FF;

    }
    else
    {
        /* extended ID*/
        pCanMsg->IdType = CAN_EXT_ID;
        pCanMsg->Id  = (tCAN->IF[1].ARB2 & 0x1FFF) << 16;
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
  * @brief Set Rx message object, include ID mask.
  * @param[in] u8MsgObj Specifies the Message object number, from 0 to 31.
  * @param[in] u8idType Specifies the identifier type of the frames that will be transmitted
  *                     This parameter can be one of the following values:
  *                     \ref CAN_STD_ID (standard ID, 11-bit)
  *                     \ref CAN_EXT_ID (extended ID, 29-bit)
  * @param[in] u32id Specifies the identifier used for acceptance filtering.
  * @param[in] u8singleOrFifoLast Specifies the end-of-buffer indicator.
  *                               This parameter can be one of the following values:
  *                               TRUE: for a single receive object or a FIFO receive object that is the last one of the FIFO.
  *                               FALSE: for a FIFO receive object that is not the last one.
  * @retval TRUE SUCCESS
  * @retval FALSE No useful interface
  * @details The function is used to configure a receive message object.
  */
int32_t CAN_SetRxMsgObjAndMsk(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8idType, uint32_t u32id, uint32_t u32idmask, uint8_t u8singleOrFifoLast)
{
    uint8_t u8MsgIfNum;

    /* Get and lock a free interface */
    if((u8MsgIfNum = LockIF_TL(tCAN)) == 2)
        return FALSE;

    /* Command Setting */
    tCAN->IF[u8MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                 CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

    if(u8idType == CAN_STD_ID)    /* According STD/EXT ID format,Configure Mask and Arbitration register */
    {
        tCAN->IF[u8MsgIfNum].ARB1 = 0;
        tCAN->IF[u8MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | (u32id & 0x7FF) << 2;
    }
    else
    {
        tCAN->IF[u8MsgIfNum].ARB1 = u32id & 0xFFFF;
        tCAN->IF[u8MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | CAN_IF_ARB2_XTD_Msk | (u32id & 0x1FFF0000) >> 16;
    }

    tCAN->IF[u8MsgIfNum].MASK1 = (u32idmask & 0xFFFF);
    tCAN->IF[u8MsgIfNum].MASK2 = (u32idmask >> 16) & 0xFFFF;

    //tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
    tCAN->IF[u8MsgIfNum].MCON = CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
    if(u8singleOrFifoLast)
        tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_EOB_Msk;
    else
        tCAN->IF[u8MsgIfNum].MCON &= (~CAN_IF_MCON_EOB_Msk);

    tCAN->IF[u8MsgIfNum].DAT_A1  = 0;
    tCAN->IF[u8MsgIfNum].DAT_A2  = 0;
    tCAN->IF[u8MsgIfNum].DAT_B1  = 0;
    tCAN->IF[u8MsgIfNum].DAT_B2  = 0;

    tCAN->IF[u8MsgIfNum].CREQ = 1 + u8MsgObj;
    ReleaseIF(tCAN, u8MsgIfNum);

    return TRUE;
}

/**
  * @brief Set Rx message object
  * @param[in] u8MsgObj Specifies the Message object number, from 0 to 31.
  * @param[in] u8idType Specifies the identifier type of the frames that will be transmitted
  *                     This parameter can be one of the following values:
  *                     \ref CAN_STD_ID (standard ID, 11-bit)
  *                     \ref CAN_EXT_ID (extended ID, 29-bit)
  * @param[in] u32id Specifies the identifier used for acceptance filtering.
  * @param[in] u8singleOrFifoLast Specifies the end-of-buffer indicator.
  *                               This parameter can be one of the following values:
  *                               TRUE: for a single receive object or a FIFO receive object that is the last one of the FIFO.
  *                               FALSE: for a FIFO receive object that is not the last one.
  * @retval TRUE SUCCESS
  * @retval FALSE No useful interface
  * @details The function is used to configure a receive message object.
  */
int32_t CAN_SetRxMsgObj(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8idType, uint32_t u32id, uint8_t u8singleOrFifoLast)
{
    uint8_t u8MsgIfNum;

    /* Get and lock a free interface */
    if((u8MsgIfNum = LockIF_TL(tCAN)) == 2)
        return FALSE;

    /* Command Setting */
    tCAN->IF[u8MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                 CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

    if(u8idType == CAN_STD_ID)    /* According STD/EXT ID format,Configure Mask and Arbitration register */
    {
        tCAN->IF[u8MsgIfNum].ARB1 = 0;
        tCAN->IF[u8MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | (u32id & 0x7FF) << 2;
    }
    else
    {
        tCAN->IF[u8MsgIfNum].ARB1 = u32id & 0xFFFF;
        tCAN->IF[u8MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | CAN_IF_ARB2_XTD_Msk | (u32id & 0x1FFF0000) >> 16;
    }

    //tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
    tCAN->IF[u8MsgIfNum].MCON = CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
    if(u8singleOrFifoLast)
        tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_EOB_Msk;
    else
        tCAN->IF[u8MsgIfNum].MCON &= (~CAN_IF_MCON_EOB_Msk);

    tCAN->IF[u8MsgIfNum].DAT_A1  = 0;
    tCAN->IF[u8MsgIfNum].DAT_A2  = 0;
    tCAN->IF[u8MsgIfNum].DAT_B1  = 0;
    tCAN->IF[u8MsgIfNum].DAT_B2  = 0;

    tCAN->IF[u8MsgIfNum].CREQ = 1 + u8MsgObj;
    ReleaseIF(tCAN, u8MsgIfNum);

    return TRUE;
}

/**
  * @brief Gets the message
  * @param[in] u8MsgObj Specifies the Message object number, from 0 to 31.
  * @param[in] u8Release Specifies the message release indicator.
  *                      This parameter can be one of the following values:
  *                      TRUE: the message object is released when getting the data.
  *                      FALSE:the message object is not released.
  * @param[in] pCanMsg Pointer to the message structure where received data is copied.
  * @retval TRUE Success
  * @retval FALSE No any message received
  * @details Gets the message, if received.
  */
int32_t CAN_ReadMsgObj(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8Release, STR_CANMSG_T* pCanMsg)
{
    uint8_t u8MsgIfNum;

    if(!CAN_IsNewDataReceived(tCAN, u8MsgObj))
        return FALSE;

    /* Get and lock a free interface */
    if((u8MsgIfNum = LockIF_TL(tCAN)) == 2)
        return FALSE;

    tCAN->STATUS &= (~CAN_STATUS_RXOK_Msk);

    /* read the message contents*/
    tCAN->IF[u8MsgIfNum].CMASK = CAN_IF_CMASK_MASK_Msk
                                 | CAN_IF_CMASK_ARB_Msk
                                 | CAN_IF_CMASK_CONTROL_Msk
                                 | CAN_IF_CMASK_CLRINTPND_Msk
                                 | (u8Release ? CAN_IF_CMASK_TXRQSTNEWDAT_Msk : 0)
                                 | CAN_IF_CMASK_DATAA_Msk
                                 | CAN_IF_CMASK_DATAB_Msk;

    tCAN->IF[u8MsgIfNum].CREQ = 1 + u8MsgObj;

    while(tCAN->IF[u8MsgIfNum].CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
        /*Wait*/
    }

    if((tCAN->IF[u8MsgIfNum].ARB2 & CAN_IF_ARB2_XTD_Msk) == 0)
    {
        /* standard ID*/
        pCanMsg->IdType = CAN_STD_ID;
        pCanMsg->Id     = (tCAN->IF[u8MsgIfNum].ARB2 & CAN_IF_ARB2_ID_Msk) >> 2;
    }
    else
    {
        /* extended ID*/
        pCanMsg->IdType = CAN_EXT_ID;
        pCanMsg->Id  = (((tCAN->IF[u8MsgIfNum].ARB2) & 0x1FFF) << 16) | tCAN->IF[u8MsgIfNum].ARB1;
    }

    pCanMsg->DLC     = tCAN->IF[u8MsgIfNum].MCON & CAN_IF_MCON_DLC_Msk;
    pCanMsg->Data[0] = tCAN->IF[u8MsgIfNum].DAT_A1 & CAN_IF_DAT_A1_DATA0_Msk;
    pCanMsg->Data[1] = (tCAN->IF[u8MsgIfNum].DAT_A1 & CAN_IF_DAT_A1_DATA1_Msk) >> CAN_IF_DAT_A1_DATA1_Pos;
    pCanMsg->Data[2] = tCAN->IF[u8MsgIfNum].DAT_A2 & CAN_IF_DAT_A2_DATA2_Msk;
    pCanMsg->Data[3] = (tCAN->IF[u8MsgIfNum].DAT_A2 & CAN_IF_DAT_A2_DATA3_Msk) >> CAN_IF_DAT_A2_DATA3_Pos;
    pCanMsg->Data[4] = tCAN->IF[u8MsgIfNum].DAT_B1 & CAN_IF_DAT_B1_DATA4_Msk;
    pCanMsg->Data[5] = (tCAN->IF[u8MsgIfNum].DAT_B1 & CAN_IF_DAT_B1_DATA5_Msk) >> CAN_IF_DAT_B1_DATA5_Pos;
    pCanMsg->Data[6] = tCAN->IF[u8MsgIfNum].DAT_B2 & CAN_IF_DAT_B2_DATA6_Msk;
    pCanMsg->Data[7] = (tCAN->IF[u8MsgIfNum].DAT_B2 & CAN_IF_DAT_B2_DATA7_Msk) >> CAN_IF_DAT_B2_DATA7_Pos;

    ReleaseIF(tCAN, u8MsgIfNum);
    return TRUE;
}

/// @endcond HIDDEN_SYMBOLS


/**
  * @brief Set bus baud-rate.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32BaudRate The target CAN baud-rate. The range of u32BaudRate is 1~1000KHz.
  *
  * @return u32CurrentBitRate  Real baud-rate value.
  *
  * @details The function is used to set bus timing parameter according current clock and target baud-rate.
  */
uint32_t CAN_SetBaudRate(CAN_T *tCAN, uint32_t u32BaudRate)
{
    uint8_t u8Tseg1, u8Tseg2;
    uint32_t u32Brp;
    uint32_t u32Value;

    CAN_EnterInitMode(tCAN, 0);
    SystemCoreClockUpdate();
    u32Value = SystemCoreClock / u32BaudRate;

#if 0
    u8Tseg1 = 2;
    u8Tseg2 = 1;
    while(1)
    {
        if(((u32Value % (u8Tseg1 + u8Tseg2 + 3)) == 0))
            break;
        if(u8Tseg1 < 7)
            u8Tseg2++;

        if((u32Value % (u8Tseg1 + u8Tseg2 + 3)) == 0)
            break;
        if(u8Tseg1 < 15)
            u8Tseg1++;
        else
        {
            u8Tseg1 = 2;
            u8Tseg2 = 1;
            break;
        }
    }
#else

    /* Fix for most standard baud rates, include 125K */

    u8Tseg1 = 3;
    u8Tseg2 = 2;
    while(1)
    {
        if(((u32Value % (u8Tseg1 + u8Tseg2 + 3)) == 0) | (u8Tseg1 >= 15))
            break;

        u8Tseg1++;

        if((u32Value % (u8Tseg1 + u8Tseg2 + 3)) == 0)
            break;

        if(u8Tseg2 < 7)
            u8Tseg2++;
    }
#endif
    u32Brp  = SystemCoreClock / (u32BaudRate) / (u8Tseg1 + u8Tseg2 + 3) - 1;

    u32Value = ((uint32_t)u8Tseg2 << CAN_BTIME_TSEG2_Pos) | ((uint32_t)u8Tseg1 << CAN_BTIME_TSEG1_Pos) |
               (u32Brp & CAN_BTIME_BRP_Msk) | (tCAN->BTIME & CAN_BTIME_SJW_Msk);
    tCAN->BTIME = u32Value;
    tCAN->BRPE     = (u32Brp >> 6) & 0x0F;

    CAN_LeaveInitMode(tCAN);

    return (CAN_GetCANBitRate(tCAN));
}

/**
  * @brief The function is used to disable all CAN interrupt.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  *
  * @return None
  *
  * @details No Status Change Interrupt and Error Status Interrupt will be generated.
  */
void CAN_Close(CAN_T *tCAN)
{
    CAN_DisableInt(tCAN, (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk));
}

/**
  * @brief Set CAN operation mode and target baud-rate.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32BaudRate The target CAN baud-rate. The range of u32BaudRate is 1~1000KHz.
  * @param[in] u32Mode The CAN operation mode. Valid values are:
  *                    - \ref CAN_NORMAL_MODE Normal operation.
  *                    - \ref CAN_BASIC_MODE Basic mode.
  * @return u32CurrentBitRate  Real baud-rate value.
  *
  * @details Set bus timing parameter according current clock and target baud-rate.
  *          In Basic mode, IF1 Registers used as Tx Buffer, IF2 Registers used as Rx Buffer.
  */
uint32_t CAN_Open(CAN_T *tCAN, uint32_t u32BaudRate, uint32_t u32Mode)
{
    uint32_t u32CurrentBitRate;

    u32CurrentBitRate = CAN_SetBaudRate(tCAN, u32BaudRate);

    if(u32Mode == CAN_BASIC_MODE)
        CAN_EnterTestMode(tCAN, CAN_TEST_BASIC_Msk);

    return u32CurrentBitRate;
}

/**
  * @brief The function is used to configure a transmit object.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  * @param[in] pCanMsg Pointer to the message structure where received data is copied.
  *
  * @retval FALSE No useful interface.
  * @retval TRUE Config message object success.
  *
  * @details The two sets of interface registers (IF1 and IF2) control the software access to the Message RAM.
  *          They buffer the data to be transferred to and from the RAM, avoiding conflicts between software accesses and message reception/transmission.
  */
int32_t CAN_SetTxMsg(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg)
{
    uint8_t u8MsgIfNum;

    if((u8MsgIfNum = LockIF_TL(tCAN)) == 2)
        return FALSE;

    /* update the contents needed for transmission*/
    tCAN->IF[u8MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                 CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk  | CAN_IF_CMASK_DATAB_Msk;

    if(pCanMsg->IdType == CAN_STD_ID)
    {
        /* standard ID*/
        tCAN->IF[u8MsgIfNum].ARB1 = 0;
        tCAN->IF[u8MsgIfNum].ARB2 = (((pCanMsg->Id) & 0x7FF) << 2) | CAN_IF_ARB2_DIR_Msk | CAN_IF_ARB2_MSGVAL_Msk;
    }
    else
    {
        /* extended ID*/
        tCAN->IF[u8MsgIfNum].ARB1 = (pCanMsg->Id) & 0xFFFF;
        tCAN->IF[u8MsgIfNum].ARB2 = ((pCanMsg->Id) & 0x1FFF0000) >> 16 |
                                    CAN_IF_ARB2_DIR_Msk | CAN_IF_ARB2_XTD_Msk | CAN_IF_ARB2_MSGVAL_Msk;
    }

    if(pCanMsg->FrameType)
        tCAN->IF[u8MsgIfNum].ARB2 |=   CAN_IF_ARB2_DIR_Msk;
    else
        tCAN->IF[u8MsgIfNum].ARB2 &= (~CAN_IF_ARB2_DIR_Msk);

    tCAN->IF[u8MsgIfNum].DAT_A1 = ((uint16_t)pCanMsg->Data[1] << 8) | pCanMsg->Data[0];
    tCAN->IF[u8MsgIfNum].DAT_A2 = ((uint16_t)pCanMsg->Data[3] << 8) | pCanMsg->Data[2];
    tCAN->IF[u8MsgIfNum].DAT_B1 = ((uint16_t)pCanMsg->Data[5] << 8) | pCanMsg->Data[4];
    tCAN->IF[u8MsgIfNum].DAT_B2 = ((uint16_t)pCanMsg->Data[7] << 8) | pCanMsg->Data[6];

    tCAN->IF[u8MsgIfNum].MCON   =  CAN_IF_MCON_NEWDAT_Msk | pCanMsg->DLC | CAN_IF_MCON_TXIE_Msk | CAN_IF_MCON_EOB_Msk;
    tCAN->IF[u8MsgIfNum].CREQ   = 1 + u32MsgNum;

    ReleaseIF(tCAN, u8MsgIfNum);
    return TRUE;
}

/**
  * @brief Set transmit request bit.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  *
  * @return TRUE: Start transmit message.
  *
  * @details If a transmission is requested by programming bit TxRqst/NewDat (IFn_CMASK[2]), the TxRqst (IFn_MCON[8]) will be ignored.
  */
int32_t CAN_TriggerTxMsg(CAN_T  *tCAN, uint32_t u32MsgNum)
{
    uint8_t u8MsgIfNum;

    if((u8MsgIfNum = LockIF_TL(tCAN)) == 2)
        return FALSE;

    tCAN->STATUS &= (~CAN_STATUS_TXOK_Msk);

    /* read the message contents*/
    tCAN->IF[u8MsgIfNum].CMASK = CAN_IF_CMASK_CLRINTPND_Msk
                                 | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;

    tCAN->IF[u8MsgIfNum].CREQ = 1 + u32MsgNum;

    while(tCAN->IF[u8MsgIfNum].CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
        /*Wait*/
    }
    tCAN->IF[u8MsgIfNum].CMASK  = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    tCAN->IF[u8MsgIfNum].CREQ  = 1 + u32MsgNum;

    ReleaseIF(tCAN, u8MsgIfNum);
    return TRUE;
}

/**
  * @brief Enable CAN interrupt.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32Mask Interrupt Mask. Valid values are:
  *                    - \ref CAN_CON_IE_Msk Module interrupt enable.
  *                    - \ref CAN_CON_SIE_Msk Status change interrupt enable.
  *                    - \ref CAN_CON_EIE_Msk Error interrupt enable.
  *
  * @return None
  *
  * @details The application software has two possibilities to follow the source of a message interrupt.
  *          First, it can follow the IntId in the Interrupt Register and second it can poll the Interrupt Pending Register.
  */
void CAN_EnableInt(CAN_T *tCAN, uint32_t u32Mask)
{
    tCAN->CON = (tCAN->CON & ~(CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk)) |
                (u32Mask & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk));
}

/**
  * @brief Disable CAN interrupt.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32Mask Interrupt Mask. (CAN_CON_IE_Msk / CAN_CON_SIE_Msk / CAN_CON_EIE_Msk).
  *
  * @return None
  *
  * @details The interrupt remains active until the Interrupt Register is back to value zero (the cause of the interrupt is reset) or until IE is reset.
  */
void CAN_DisableInt(CAN_T *tCAN, uint32_t u32Mask)
{
    tCAN->CON = tCAN->CON & ~((u32Mask & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk)));
}


/**
  * @brief The function is used to configure a receive message object.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  * @param[in] u32IDType Specifies the identifier type of the frames that will be transmitted. Valid values are:
  *                      - \ref CAN_STD_ID The 11-bit identifier.
  *                      - \ref CAN_EXT_ID The 29-bit identifier.
  * @param[in] u32ID Specifies the identifier used for acceptance filtering.
  *
  * @retval FALSE No useful interface.
  * @retval TRUE Configure a receive message object success.
  *
  * @details If the RxIE bit (CAN_IFn_MCON[10]) is set, the IntPnd bit (CAN_IFn_MCON[13])
  *          will be set when a received Data Frame is accepted and stored in the Message Object.
  */
int32_t CAN_SetRxMsg(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32IDType, uint32_t u32ID)
{
    uint32_t u32TimeOutCount = 0;

    while(CAN_SetRxMsgObj(tCAN, u32MsgNum, u32IDType, u32ID, TRUE) == FALSE)
    {
        if(++u32TimeOutCount >= RETRY_COUNTS) return FALSE;
    }

    return TRUE;
}

/**
  * @brief The function is used to configure a receive message object.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  * @param[in] u32IDType Specifies the identifier type of the frames that will be transmitted. Valid values are:
  *                      - \ref CAN_STD_ID The 11-bit identifier.
  *                      - \ref CAN_EXT_ID The 29-bit identifier.
  * @param[in] u32ID Specifies the identifier used for acceptance filtering.
  * @param[in] u32IDMask Specifies the identifier mask used for acceptance filtering.
  *
  * @retval FALSE No useful interface.
  * @retval TRUE Configure a receive message object success.
  *
  * @details If the RxIE bit (CAN_IFn_MCON[10]) is set, the IntPnd bit (CAN_IFn_MCON[13])
  *          will be set when a received Data Frame is accepted and stored in the Message Object.
  */
int32_t CAN_SetRxMsgAndMsk(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32IDType, uint32_t u32ID, uint32_t u32IDMask)
{
    uint32_t u32TimeOutCount = 0;

    while(CAN_SetRxMsgObjAndMsk(tCAN, u32MsgNum, u32IDType, u32ID, u32IDMask, TRUE) == FALSE)
    {
        if(++u32TimeOutCount >= RETRY_COUNTS) return FALSE;
    }

    return TRUE;
}

/**
  * @brief The function is used to configure several receive message objects.
  *
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum The starting MSG RAM number(0 ~ 31).
  * @param[in] u32MsgCount the number of MSG RAM of the FIFO.
  * @param[in] u32IDType Specifies the identifier type of the frames that will be transmitted. Valid values are:
  *                      - \ref CAN_STD_ID The 11-bit identifier.
  *                      - \ref CAN_EXT_ID The 29-bit identifier.
  * @param[in] u32ID Specifies the identifier used for acceptance filtering.
  *
  * @retval FALSE No useful interface.
  * @retval TRUE Configure receive message objects success.
  *
  * @details The Interface Registers avoid conflict between the CPU accesses to the Message RAM and CAN message reception
  *          and transmission by buffering the data to be transferred.
  */
int32_t CAN_SetMultiRxMsg(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32MsgCount, uint32_t u32IDType, uint32_t u32ID)
{
    uint32_t i = 0;
    uint32_t u32TimeOutCount;
    uint32_t u32EOB_Flag = 0;

    for(i = 1; i < u32MsgCount; i++)
    {
        u32TimeOutCount = 0;

        u32MsgNum += (i - 1);

        if(i == u32MsgCount) u32EOB_Flag = 1;

        while(CAN_SetRxMsgObj(tCAN, u32MsgNum, u32IDType, u32ID, u32EOB_Flag) == FALSE)
        {
            if(++u32TimeOutCount >= RETRY_COUNTS) return FALSE;
        }
    }

    return TRUE;
}


/**
  * @brief Send CAN message.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  * @param[in] pCanMsg Pointer to the message structure where received data is copied.
  *
  * @retval FALSE 1. When operation in basic mode: Transmit message time out. \n
  *               2. When operation in normal mode: No useful interface. \n
  * @retval TRUE Transmit Message success.
  *
  * @details The receive/transmit priority for the Message Objects is attached to the message number.
  *          Message Object 1 has the highest priority, while Message Object 32 has the lowest priority.
  */
int32_t CAN_Transmit(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg)
{
    if((tCAN->CON & CAN_CON_TEST_Msk) && (tCAN->TEST & CAN_TEST_BASIC_Msk))
    {
        return (CAN_BasicSendMsg(tCAN, pCanMsg));
    }
    else
    {
        if(CAN_SetTxMsg(tCAN, u32MsgNum, pCanMsg) == FALSE)
            return FALSE;
        CAN_TriggerTxMsg(tCAN, u32MsgNum);
    }

    return TRUE;
}


/**
  * @brief Gets the message, if received.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  * @param[in] pCanMsg Pointer to the message structure where received data is copied.
  *
  * @retval FALSE No any message received.
  * @retval TRUE Receive Message success.
  *
  * @details The Interface Registers avoid conflict between the CPU accesses to the Message RAM and CAN message reception
  *          and transmission by buffering the data to be transferred.
  */
int32_t CAN_Receive(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg)
{
    if((tCAN->CON & CAN_CON_TEST_Msk) && (tCAN->TEST & CAN_TEST_BASIC_Msk))
    {
        return (CAN_BasicReceiveMsg(tCAN, pCanMsg));
    }
    else
    {
        return CAN_ReadMsgObj(tCAN, u32MsgNum, TRUE, pCanMsg);
    }
}

/**
  * @brief Clear interrupt pending bit.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u32MsgNum Specifies the Message object number, from 0 to 31.
  *
  * @return None
  *
  * @details An interrupt remains pending until the application software has cleared it.
  */
void CAN_CLR_INT_PENDING_BIT(CAN_T *tCAN, uint8_t u32MsgNum)
{
    uint32_t u32MsgIfNum;

    if((u32MsgIfNum = LockIF_TL(tCAN)) == 2)
        u32MsgIfNum = 0;

    tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_CLRINTPND_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    tCAN->IF[u32MsgIfNum].CREQ = 1 + u32MsgNum;

    ReleaseIF(tCAN, u32MsgIfNum);
}


/*@}*/ /* end of group CAN_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CAN_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/

