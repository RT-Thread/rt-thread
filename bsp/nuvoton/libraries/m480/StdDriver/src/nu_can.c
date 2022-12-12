/**************************************************************************//**
 * @file     can.c
 * @version  V2.00
 * @brief    M480 series CAN driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CAN_Driver CAN Driver
  @{
*/

/** @addtogroup CAN_EXPORTED_FUNCTIONS CAN Exported Functions
  @{
*/

/** @cond HIDDEN_SYMBOLS */

#if defined(CAN2)
static uint8_t gu8LockCanIf[3ul][2ul] = {0ul};    /* The chip has three CANs. */
#elif defined(CAN1)
static uint8_t gu8LockCanIf[2ul][2ul] = {0ul};    /* The chip has two CANs. */
#elif defined(CAN0) || defined(CAN)
static uint8_t gu8LockCanIf[1ul][2ul] = {0ul};    /* The chip only has one CAN. */
#endif

#define RETRY_COUNTS    (0x10000000ul)

#define TSEG1_MIN 2ul
#define TSEG1_MAX 16ul
#define TSEG2_MIN 1ul
#define TSEG2_MAX 8ul
#define BRP_MIN   1ul
#define BRP_MAX   1024ul  /* 6-bit BRP field + 4-bit BRPE field*/
#define SJW_MAX   4ul
#define BRP_INC   1ul

/* #define DEBUG_PRINTF printf */
#define DEBUG_PRINTF(...)

static uint32_t LockIF(CAN_T *tCAN);
static uint32_t LockIF_TL(CAN_T *tCAN);
static void ReleaseIF(CAN_T *tCAN, uint32_t u32IfNo);
static int can_update_spt(int sampl_pt, int tseg, int *tseg1, int *tseg2);

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
    uint32_t u32CanNo = 0ul;
    uint32_t u32FreeIfNo;
    uint32_t u32IntMask;

#if defined(CAN1)
    if (tCAN == CAN0)
        u32CanNo = 0ul;
    else if (tCAN == CAN1)
        u32CanNo = 1ul;
#if defined(CAN2)
    else if (tCAN == CAN2)
        u32CanNo = 2ul;
#endif
#else /* defined(CAN0) || defined(CAN) */
    u32CanNo = 0ul;
#endif

    u32FreeIfNo = 2ul;

    /* Disable CAN interrupt */
    u32IntMask = tCAN->CON & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);
    tCAN->CON = tCAN->CON & ~(CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);

    /* Check interface 1 is available or not */
    if ((tCAN->IF[0ul].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0ul)
    {
        if (gu8LockCanIf[u32CanNo][0ul] == 0ul)
        {
            gu8LockCanIf[u32CanNo][0ul] = 1u;
            u32FreeIfNo = 0ul;
        }
        else
        {
        }
    }
    else
    {
    }

    /* Or check interface 2 is available or not */
    if (u32FreeIfNo == 2ul)
    {
        if ((tCAN->IF[1ul].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0ul)
        {
            if (gu8LockCanIf[u32CanNo][1ul] == 0ul)
            {
                gu8LockCanIf[u32CanNo][1ul] = 1u;
                u32FreeIfNo = 1ul;
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
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

    for (u32Count = 0ul; u32Count < RETRY_COUNTS; u32Count++)
    {
        if ((u32FreeIfNo = LockIF(tCAN)) != 2ul)
        {
            break;
        }
        else
        {
        }
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
    uint32_t u32CanNo = 0ul;

    if (u32IfNo >= 2ul)
    {
    }
    else
    {
#if defined(CAN1)
        if (tCAN == CAN0)
            u32CanNo = 0ul;
        else if (tCAN == CAN1)
            u32CanNo = 1ul;
#if defined(CAN2)
        else if (tCAN == CAN2)
            u32CanNo = 2ul;
#endif
#else /* defined(CAN0) || defined(CAN) */
        u32CanNo = 0ul;
#endif

        /* Disable CAN interrupt */
        u32IntMask = tCAN->CON & (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);
        tCAN->CON = tCAN->CON & ~(CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);

        gu8LockCanIf[u32CanNo][u32IfNo] = 0u;

        /* Enable CAN interrupt */
        tCAN->CON |= u32IntMask;
    }
}

static int can_update_spt(int sampl_pt, int tseg, int *tseg1, int *tseg2)
{
    *tseg2 = tseg + 1 - (sampl_pt * (tseg + 1)) / 1000;
    if (*tseg2 < TSEG2_MIN)
    {
        *tseg2 = TSEG2_MIN;
    }
    else
    {
    }

    if (*tseg2 > TSEG2_MAX)
    {
        *tseg2 = TSEG2_MAX;
    }
    else
    {
    }

    *tseg1 = tseg - *tseg2;
    if (*tseg1 > TSEG1_MAX)
    {
        *tseg1 = TSEG1_MAX;
        *tseg2 = tseg - *tseg1;
    }
    else
    {
    }

    return 1000 * (tseg + 1 - *tseg2) / (tseg + 1);
}

/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief Enter initialization mode
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u8Mask Following values can be used.
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
    while (tCAN->CON & CAN_CON_INIT_Msk)
    {
        /* Check INIT bit is released */
    }
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
    tCAN->STATUS = 0x0ul; /* clr status */

    while (1)
    {
        if (tCAN->IF[1].MCON & CAN_IF_MCON_NEWDAT_Msk)  /* check new data */
        {
            /* New Data IN */
            break;
        }
        else
        {
        }

        if (tCAN->STATUS & CAN_STATUS_RXOK_Msk)
        {
            /* Rx OK */
        }
        else
        {
        }

        if (tCAN->STATUS & CAN_STATUS_LEC_Msk)
        {
            /* Error */
        }
        else
        {
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
    uint32_t u32Tseg1, u32Tseg2;
    uint32_t u32Bpr;

    u32Tseg1 = (tCAN->BTIME & CAN_BTIME_TSEG1_Msk) >> CAN_BTIME_TSEG1_Pos;
    u32Tseg2 = (tCAN->BTIME & CAN_BTIME_TSEG2_Msk) >> CAN_BTIME_TSEG2_Pos;
    u32Bpr   = (tCAN->BTIME & CAN_BTIME_BRP_Msk) | (tCAN->BRPE << 6ul);

    return (SystemCoreClock / (u32Bpr + 1ul) / (u32Tseg1 + u32Tseg2 + 3ul));
}

/**
  * @brief Switch the CAN into test mode.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u8TestMask Specifies the configuration in test modes
  *                       \ref CAN_TEST_BASIC_Msk Enable basic mode of test mode
  *                       \ref CAN_TEST_SILENT_Msk Enable silent mode of test mode
  *                       \ref CAN_TEST_LBACK_Msk Enable Loop Back Mode of test mode
  *                       \ref CAN_TEST_Tx_Msk Control CAN_TX pin bit field
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
    return (u8MsgObj < 16ul ? tCAN->NDAT1 & (1ul << u8MsgObj) : tCAN->NDAT2 & (1ul << (u8MsgObj - 16ul)));
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
int32_t CAN_BasicSendMsg(CAN_T *tCAN, STR_CANMSG_T *pCanMsg)
{
    uint32_t i = 0ul;
    int32_t rev = 1l;

    while (tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
    }

    tCAN->STATUS &= (~CAN_STATUS_TXOK_Msk);

    if (pCanMsg->IdType == CAN_STD_ID)
    {
        /* standard ID*/
        tCAN->IF[0].ARB1 = 0ul;
        tCAN->IF[0].ARB2 = (((pCanMsg->Id) & 0x7FFul) << 2ul) ;
    }
    else
    {
        /* extended ID*/
        tCAN->IF[0].ARB1 = (pCanMsg->Id) & 0xFFFFul;
        tCAN->IF[0].ARB2 = ((pCanMsg->Id) & 0x1FFF0000ul) >> 16ul  | CAN_IF_ARB2_XTD_Msk;

    }

    if (pCanMsg->FrameType)
    {
        tCAN->IF[0].ARB2 |= CAN_IF_ARB2_DIR_Msk;
    }
    else
    {
        tCAN->IF[0].ARB2 &= (~CAN_IF_ARB2_DIR_Msk);
    }

    tCAN->IF[0].MCON = (tCAN->IF[0].MCON & (~CAN_IF_MCON_DLC_Msk)) | pCanMsg->DLC;
    tCAN->IF[0].DAT_A1 = (uint16_t)((uint16_t)((uint16_t)pCanMsg->Data[1] << 8) | pCanMsg->Data[0]);
    tCAN->IF[0].DAT_A2 = (uint16_t)((uint16_t)((uint16_t)pCanMsg->Data[3] << 8) | pCanMsg->Data[2]);
    tCAN->IF[0].DAT_B1 = (uint16_t)((uint16_t)((uint16_t)pCanMsg->Data[5] << 8) | pCanMsg->Data[4]);
    tCAN->IF[0].DAT_B2 = (uint16_t)((uint16_t)((uint16_t)pCanMsg->Data[7] << 8) | pCanMsg->Data[6]);

    /* request transmission*/
    tCAN->IF[0].CREQ &= (~CAN_IF_CREQ_BUSY_Msk);
    if (tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk)
    {
        /* Cannot clear busy for sending ...*/
        rev = 0l; /* return FALSE */
    }
    else
    {
        tCAN->IF[0].CREQ |= CAN_IF_CREQ_BUSY_Msk;  /* sending */

        for (i = 0ul; i < 0xFFFFFul; i++)
        {
            if ((tCAN->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) == 0ul)
            {
                break;
            }
            else
            {
            }
        }

        if (i >= 0xFFFFFul)
        {
            /* Cannot send out... */
            rev = 0l; /* return FALSE */
        }
        else
        {
        }
    }

    return rev;
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
int32_t CAN_BasicReceiveMsg(CAN_T *tCAN, STR_CANMSG_T *pCanMsg)
{
    int32_t rev = 1l;

    if ((tCAN->IF[1].MCON & CAN_IF_MCON_NEWDAT_Msk) == 0ul)
    {
        /* In basic mode, receive data always save in IF2 */
        rev = 0; /* return FALSE */
    }
    else
    {

        tCAN->STATUS &= (~CAN_STATUS_RXOK_Msk);

        tCAN->IF[1].CMASK = CAN_IF_CMASK_ARB_Msk
                            | CAN_IF_CMASK_CONTROL_Msk
                            | CAN_IF_CMASK_DATAA_Msk
                            | CAN_IF_CMASK_DATAB_Msk;

        if ((tCAN->IF[1].ARB2 & CAN_IF_ARB2_XTD_Msk) == 0ul)
        {
            /* standard ID*/
            pCanMsg->IdType = CAN_STD_ID;
            pCanMsg->Id = (tCAN->IF[1].ARB2 >> 2) & 0x07FFul;

        }
        else
        {
            /* extended ID*/
            pCanMsg->IdType = CAN_EXT_ID;
            pCanMsg->Id  = (tCAN->IF[1].ARB2 & 0x1FFFul) << 16;
            pCanMsg->Id |= (uint32_t)tCAN->IF[1].ARB1;
        }

        pCanMsg->FrameType = (((tCAN->IF[1].ARB2 & CAN_IF_ARB2_DIR_Msk) >> CAN_IF_ARB2_DIR_Pos)) ? 0ul : 1ul;

        pCanMsg->DLC     = (uint8_t)(tCAN->IF[1].MCON & CAN_IF_MCON_DLC_Msk);
        pCanMsg->Data[0] = (uint8_t)(tCAN->IF[1].DAT_A1 & CAN_IF_DAT_A1_DATA0_Msk);
        pCanMsg->Data[1] = (uint8_t)((tCAN->IF[1].DAT_A1 & CAN_IF_DAT_A1_DATA1_Msk) >> CAN_IF_DAT_A1_DATA1_Pos);
        pCanMsg->Data[2] = (uint8_t)(tCAN->IF[1].DAT_A2 & CAN_IF_DAT_A2_DATA2_Msk);
        pCanMsg->Data[3] = (uint8_t)((tCAN->IF[1].DAT_A2 & CAN_IF_DAT_A2_DATA3_Msk) >> CAN_IF_DAT_A2_DATA3_Pos);
        pCanMsg->Data[4] = (uint8_t)(tCAN->IF[1].DAT_B1 & CAN_IF_DAT_B1_DATA4_Msk);
        pCanMsg->Data[5] = (uint8_t)((tCAN->IF[1].DAT_B1 & CAN_IF_DAT_B1_DATA5_Msk) >> CAN_IF_DAT_B1_DATA5_Pos);
        pCanMsg->Data[6] = (uint8_t)(tCAN->IF[1].DAT_B2 & CAN_IF_DAT_B2_DATA6_Msk);
        pCanMsg->Data[7] = (uint8_t)((tCAN->IF[1].DAT_B2 & CAN_IF_DAT_B2_DATA7_Msk) >> CAN_IF_DAT_B2_DATA7_Pos);
    }

    return rev;
}

/**
  * @brief Set Rx message object, include ID mask.
  * @param[in] tCAN The pointer to CAN module base address.
  * @param[in] u8MsgObj Specifies the Message object number, from 0 to 31.
  * @param[in] u8idType Specifies the identifier type of the frames that will be transmitted
  *                     This parameter can be one of the following values:
  *                     \ref CAN_STD_ID (standard ID, 11-bit)
  *                     \ref CAN_EXT_ID (extended ID, 29-bit)
  * @param[in] u32id Specifies the identifier used for acceptance filtering.
  * @param[in] u32idmask Specifies the identifier mask used for acceptance filtering.
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
    int32_t rev = 1l;
    uint32_t u32MsgIfNum;

    /* Get and lock a free interface */
    if ((u32MsgIfNum = LockIF_TL(tCAN)) == 2ul)
    {
        rev = 0; /* return FALSE */
    }
    else
    {
        /* Command Setting */
        tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                      CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

        if (u8idType == CAN_STD_ID)   /* According STD/EXT ID format,Configure Mask and Arbitration register */
        {
            tCAN->IF[u32MsgIfNum].ARB1 = 0ul;
            tCAN->IF[u32MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | (u32id & 0x7FFul) << 2;
        }
        else
        {
            tCAN->IF[u32MsgIfNum].ARB1 = u32id & 0xFFFFul;
            tCAN->IF[u32MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | CAN_IF_ARB2_XTD_Msk | (u32id & 0x1FFF0000ul) >> 16;
        }

        tCAN->IF[u32MsgIfNum].MASK1 = (u32idmask & 0xFFFFul);
        tCAN->IF[u32MsgIfNum].MASK2 = (u32idmask >> 16) & 0xFFFFul;

        /* tCAN->IF[u32MsgIfNum].MCON |= CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk; */
        tCAN->IF[u32MsgIfNum].MCON = CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
        if (u8singleOrFifoLast)
        {
            tCAN->IF[u32MsgIfNum].MCON |= CAN_IF_MCON_EOB_Msk;
        }
        else
        {
            tCAN->IF[u32MsgIfNum].MCON &= (~CAN_IF_MCON_EOB_Msk);
        }

        tCAN->IF[u32MsgIfNum].DAT_A1  = 0ul;
        tCAN->IF[u32MsgIfNum].DAT_A2  = 0ul;
        tCAN->IF[u32MsgIfNum].DAT_B1  = 0ul;
        tCAN->IF[u32MsgIfNum].DAT_B2  = 0ul;

        tCAN->IF[u32MsgIfNum].CREQ = 1ul + u8MsgObj;
        ReleaseIF(tCAN, u32MsgIfNum);
    }

    return rev;
}

/**
  * @brief Set Rx message object
  * @param[in] tCAN The pointer to CAN module base address.
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
    int32_t rev = 1l;
    uint32_t u32MsgIfNum;

    /* Get and lock a free interface */
    if ((u32MsgIfNum = LockIF_TL(tCAN)) == 2ul)
    {
        rev = 0; /* return FALSE */
    }
    else
    {
        /* Command Setting */
        tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                      CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk;

        if (u8idType == CAN_STD_ID)   /* According STD/EXT ID format,Configure Mask and Arbitration register */
        {
            tCAN->IF[u32MsgIfNum].ARB1 = 0ul;
            tCAN->IF[u32MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | (u32id & 0x7FFul) << 2;
        }
        else
        {
            tCAN->IF[u32MsgIfNum].ARB1 = u32id & 0xFFFFul;
            tCAN->IF[u32MsgIfNum].ARB2 = CAN_IF_ARB2_MSGVAL_Msk | CAN_IF_ARB2_XTD_Msk | (u32id & 0x1FFF0000ul) >> 16;
        }

        /* tCAN->IF[u8MsgIfNum].MCON |= CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk; */
        tCAN->IF[u32MsgIfNum].MCON = CAN_IF_MCON_UMASK_Msk | CAN_IF_MCON_RXIE_Msk;
        if (u8singleOrFifoLast)
        {
            tCAN->IF[u32MsgIfNum].MCON |= CAN_IF_MCON_EOB_Msk;
        }
        else
        {
            tCAN->IF[u32MsgIfNum].MCON &= (~CAN_IF_MCON_EOB_Msk);
        }

        tCAN->IF[u32MsgIfNum].DAT_A1  = 0ul;
        tCAN->IF[u32MsgIfNum].DAT_A2  = 0ul;
        tCAN->IF[u32MsgIfNum].DAT_B1  = 0ul;
        tCAN->IF[u32MsgIfNum].DAT_B2  = 0ul;

        tCAN->IF[u32MsgIfNum].CREQ = 1ul + u8MsgObj;
        ReleaseIF(tCAN, u32MsgIfNum);
    }

    return rev;
}

/**
  * @brief Gets the message
  * @param[in] tCAN The pointer to CAN module base address.
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
int32_t CAN_ReadMsgObj(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8Release, STR_CANMSG_T *pCanMsg)
{
    int32_t rev = 1l;
    uint32_t u32MsgIfNum;

    if (!CAN_IsNewDataReceived(tCAN, u8MsgObj))
    {
        rev = 0; /* return FALSE */
    }
    else
    {
        /* Get and lock a free interface */
        if ((u32MsgIfNum = LockIF_TL(tCAN)) == 2ul)
        {
            rev = 0; /* return FALSE */
        }
        else
        {
            tCAN->STATUS &= (~CAN_STATUS_RXOK_Msk);

            /* read the message contents*/
            tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_MASK_Msk
                                          | CAN_IF_CMASK_ARB_Msk
                                          | CAN_IF_CMASK_CONTROL_Msk
                                          | CAN_IF_CMASK_CLRINTPND_Msk
                                          | (u8Release ? CAN_IF_CMASK_TXRQSTNEWDAT_Msk : 0ul)
                                          | CAN_IF_CMASK_DATAA_Msk
                                          | CAN_IF_CMASK_DATAB_Msk;

            tCAN->IF[u32MsgIfNum].CREQ = 1ul + u8MsgObj;

            while (tCAN->IF[u32MsgIfNum].CREQ & CAN_IF_CREQ_BUSY_Msk)
            {
                /*Wait*/
            }

            if ((tCAN->IF[u32MsgIfNum].ARB2 & CAN_IF_ARB2_XTD_Msk) == 0ul)
            {
                /* standard ID*/
                pCanMsg->IdType = CAN_STD_ID;
                pCanMsg->Id     = (tCAN->IF[u32MsgIfNum].ARB2 & CAN_IF_ARB2_ID_Msk) >> 2ul;
            }
            else
            {
                /* extended ID*/
                pCanMsg->IdType = CAN_EXT_ID;
                pCanMsg->Id  = (((tCAN->IF[u32MsgIfNum].ARB2) & 0x1FFFul) << 16) | tCAN->IF[u32MsgIfNum].ARB1;
            }

            pCanMsg->DLC     = (uint8_t)(tCAN->IF[u32MsgIfNum].MCON & CAN_IF_MCON_DLC_Msk);
            pCanMsg->Data[0] = (uint8_t)(tCAN->IF[u32MsgIfNum].DAT_A1 & CAN_IF_DAT_A1_DATA0_Msk);
            pCanMsg->Data[1] = (uint8_t)((tCAN->IF[u32MsgIfNum].DAT_A1 & CAN_IF_DAT_A1_DATA1_Msk) >> CAN_IF_DAT_A1_DATA1_Pos);
            pCanMsg->Data[2] = (uint8_t)(tCAN->IF[u32MsgIfNum].DAT_A2 & CAN_IF_DAT_A2_DATA2_Msk);
            pCanMsg->Data[3] = (uint8_t)((tCAN->IF[u32MsgIfNum].DAT_A2 & CAN_IF_DAT_A2_DATA3_Msk) >> CAN_IF_DAT_A2_DATA3_Pos);
            pCanMsg->Data[4] = (uint8_t)(tCAN->IF[u32MsgIfNum].DAT_B1 & CAN_IF_DAT_B1_DATA4_Msk);
            pCanMsg->Data[5] = (uint8_t)((tCAN->IF[u32MsgIfNum].DAT_B1 & CAN_IF_DAT_B1_DATA5_Msk) >> CAN_IF_DAT_B1_DATA5_Pos);
            pCanMsg->Data[6] = (uint8_t)(tCAN->IF[u32MsgIfNum].DAT_B2 & CAN_IF_DAT_B2_DATA6_Msk);
            pCanMsg->Data[7] = (uint8_t)((tCAN->IF[u32MsgIfNum].DAT_B2 & CAN_IF_DAT_B2_DATA7_Msk) >> CAN_IF_DAT_B2_DATA7_Pos);

            ReleaseIF(tCAN, u32MsgIfNum);
        }
    }

    return rev;
}


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
    long rate;
    long best_error = 1000000000, error = 0;
    int best_tseg = 0, best_brp = 0, brp = 0;
    int tsegall, tseg = 0, tseg1 = 0, tseg2 = 0;
    int spt_error = 1000, spt = 0, sampl_pt;
    uint64_t clock_freq = (uint64_t)0, u64PCLK_DIV = (uint64_t)1;
    uint32_t sjw = (uint32_t)1;

    CAN_EnterInitMode(tCAN, (uint8_t)0);

    SystemCoreClockUpdate();
    if ((tCAN == CAN0) || (tCAN == CAN2))
    {
        u64PCLK_DIV = (uint64_t)(CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk);
        u64PCLK_DIV = (uint64_t)(1 << u64PCLK_DIV);
    }
    else if (tCAN == CAN1)
    {
        u64PCLK_DIV = (uint64_t)((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) >> CLK_PCLKDIV_APB1DIV_Pos);
        u64PCLK_DIV = (uint64_t)(1 << u64PCLK_DIV);
    }

    clock_freq = SystemCoreClock / u64PCLK_DIV;

    if (u32BaudRate >= (uint32_t)1000000)
    {
        u32BaudRate = (uint32_t)1000000;
    }

    /* Use CIA recommended sample points */
    if (u32BaudRate > (uint32_t)800000)
    {
        sampl_pt = (int)750;
    }
    else if (u32BaudRate > (uint32_t)500000)
    {
        sampl_pt = (int)800;
    }
    else
    {
        sampl_pt = (int)875;
    }

    /* tseg even = round down, odd = round up */
    for (tseg = (TSEG1_MAX + TSEG2_MAX) * 2ul + 1ul; tseg >= (TSEG1_MIN + TSEG2_MIN) * 2ul; tseg--)
    {
        tsegall = 1ul + tseg / 2ul;
        /* Compute all possible tseg choices (tseg=tseg1+tseg2) */
        brp = clock_freq / (tsegall * u32BaudRate) + tseg % 2;
        /* chose brp step which is possible in system */
        brp = (brp / BRP_INC) * BRP_INC;

        if ((brp < BRP_MIN) || (brp > BRP_MAX))
        {
            continue;
        }
        rate = clock_freq / (brp * tsegall);

        error = u32BaudRate - rate;

        /* tseg brp biterror */
        if (error < 0)
        {
            error = -error;
        }
        if (error > best_error)
        {
            continue;
        }
        best_error = error;
        if (error == 0)
        {
            spt = can_update_spt(sampl_pt, tseg / 2, &tseg1, &tseg2);
            error = sampl_pt - spt;
            if (error < 0)
            {
                error = -error;
            }
            if (error > spt_error)
            {
                continue;
            }
            spt_error = error;
        }
        best_tseg = tseg / 2;
        best_brp = brp;

        if (error == 0)
        {
            break;
        }
    }

    spt = can_update_spt(sampl_pt, best_tseg, &tseg1, &tseg2);

    /* check for sjw user settings */
    /* bt->sjw is at least 1 -> sanitize upper bound to sjw_max */
    if (sjw > SJW_MAX)
    {
        sjw = SJW_MAX;
    }
    /* bt->sjw must not be higher than tseg2 */
    if (tseg2 < sjw)
    {
        sjw = tseg2;
    }

    /* real bit-rate */
    u32BaudRate = clock_freq / (best_brp * (tseg1 + tseg2 + 1));

    tCAN->BTIME = ((uint32_t)(tseg2 - 1ul) << CAN_BTIME_TSEG2_Pos) | ((uint32_t)(tseg1 - 1ul) << CAN_BTIME_TSEG1_Pos) |
                  ((uint32_t)(best_brp - 1ul) & CAN_BTIME_BRP_Msk) | (sjw << CAN_BTIME_SJW_Pos);
    tCAN->BRPE  = ((uint32_t)(best_brp - 1ul) >> 6) & 0x0Ful;

    /* printf("\n bitrate = %d \n", CAN_GetCANBitRate(tCAN)); */

    CAN_LeaveInitMode(tCAN);

    return u32BaudRate;
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

    if (u32Mode == CAN_BASIC_MODE)
    {
        CAN_EnterTestMode(tCAN, (uint8_t)CAN_TEST_BASIC_Msk);
    }
    else
    {
    }

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
int32_t CAN_SetTxMsg(CAN_T *tCAN, uint32_t u32MsgNum, STR_CANMSG_T *pCanMsg)
{
    int32_t rev = 1l;
    uint32_t u32MsgIfNum;

    if ((u32MsgIfNum = LockIF_TL(tCAN)) == 2ul)
    {
        rev = 0; /* return FALSE */
    }
    else
    {
        /* update the contents needed for transmission*/
        tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk | CAN_IF_CMASK_ARB_Msk |
                                      CAN_IF_CMASK_CONTROL_Msk | CAN_IF_CMASK_DATAA_Msk  | CAN_IF_CMASK_DATAB_Msk;

        if (pCanMsg->IdType == CAN_STD_ID)
        {
            /* standard ID*/
            tCAN->IF[u32MsgIfNum].ARB1 = 0ul;
            tCAN->IF[u32MsgIfNum].ARB2 = (((pCanMsg->Id) & 0x7FFul) << 2) | CAN_IF_ARB2_DIR_Msk | CAN_IF_ARB2_MSGVAL_Msk;
        }
        else
        {
            /* extended ID*/
            tCAN->IF[u32MsgIfNum].ARB1 = (pCanMsg->Id) & 0xFFFFul;
            tCAN->IF[u32MsgIfNum].ARB2 = ((pCanMsg->Id) & 0x1FFF0000ul) >> 16 |
                                         CAN_IF_ARB2_DIR_Msk | CAN_IF_ARB2_XTD_Msk | CAN_IF_ARB2_MSGVAL_Msk;
        }

        if (pCanMsg->FrameType)
        {
            tCAN->IF[u32MsgIfNum].ARB2 |=   CAN_IF_ARB2_DIR_Msk;
        }
        else
        {
            tCAN->IF[u32MsgIfNum].ARB2 &= (~CAN_IF_ARB2_DIR_Msk);
        }

        tCAN->IF[u32MsgIfNum].DAT_A1 = (uint16_t)((uint16_t)(((uint16_t)pCanMsg->Data[1] << 8)) | pCanMsg->Data[0]);
        tCAN->IF[u32MsgIfNum].DAT_A2 = (uint16_t)((uint16_t)(((uint16_t)pCanMsg->Data[3] << 8)) | pCanMsg->Data[2]);
        tCAN->IF[u32MsgIfNum].DAT_B1 = (uint16_t)((uint16_t)(((uint16_t)pCanMsg->Data[5] << 8)) | pCanMsg->Data[4]);
        tCAN->IF[u32MsgIfNum].DAT_B2 = (uint16_t)((uint16_t)(((uint16_t)pCanMsg->Data[7] << 8)) | pCanMsg->Data[6]);

        tCAN->IF[u32MsgIfNum].MCON   =  CAN_IF_MCON_NEWDAT_Msk | pCanMsg->DLC | CAN_IF_MCON_TXIE_Msk | CAN_IF_MCON_EOB_Msk;
        tCAN->IF[u32MsgIfNum].CREQ   = 1ul + u32MsgNum;

        ReleaseIF(tCAN, u32MsgIfNum);
    }

    return rev;
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
    int32_t rev = 1l;
    uint32_t u32MsgIfNum;

    if ((u32MsgIfNum = LockIF_TL(tCAN)) == 2ul)
    {
        rev = 0; /* return FALSE */
    }
    else
    {
        tCAN->STATUS &= (~CAN_STATUS_TXOK_Msk);

        /* read the message contents*/
        tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_CLRINTPND_Msk
                                      | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;

        tCAN->IF[u32MsgIfNum].CREQ = 1ul + u32MsgNum;

        while (tCAN->IF[u32MsgIfNum].CREQ & CAN_IF_CREQ_BUSY_Msk)
        {
            /*Wait*/
        }
        tCAN->IF[u32MsgIfNum].CMASK  = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
        tCAN->IF[u32MsgIfNum].CREQ  = 1ul + u32MsgNum;

        ReleaseIF(tCAN, u32MsgIfNum);
    }

    return rev;
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
int32_t CAN_SetRxMsg(CAN_T *tCAN, uint32_t u32MsgNum, uint32_t u32IDType, uint32_t u32ID)
{
    int32_t rev = (int32_t)TRUE;
    uint32_t u32TimeOutCount = 0ul;

    while (CAN_SetRxMsgObj(tCAN, (uint8_t)u32MsgNum, (uint8_t)u32IDType, u32ID, (uint8_t)TRUE) == (int32_t)FALSE)
    {
        if (++u32TimeOutCount >= RETRY_COUNTS)
        {
            rev = (int32_t)(FALSE); /* return FALSE */
            break;
        }
        else
        {
        }
    }

    return rev;
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
int32_t CAN_SetRxMsgAndMsk(CAN_T *tCAN, uint32_t u32MsgNum, uint32_t u32IDType, uint32_t u32ID, uint32_t u32IDMask)
{
    int32_t  rev = (int32_t)TRUE;
    uint32_t u32TimeOutCount = 0ul;

    while (CAN_SetRxMsgObjAndMsk(tCAN, (uint8_t)u32MsgNum, (uint8_t)u32IDType, u32ID, u32IDMask, (uint8_t)TRUE) == (int32_t)FALSE)
    {
        if (++u32TimeOutCount >= RETRY_COUNTS)
        {
            rev = (int32_t)FALSE;
            break;
        }
        else
        {
        }
    }

    return rev;
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
int32_t CAN_SetMultiRxMsg(CAN_T *tCAN, uint32_t u32MsgNum, uint32_t u32MsgCount, uint32_t u32IDType, uint32_t u32ID)
{
    int32_t  rev = (int32_t)TRUE;
    uint32_t i;
    uint32_t u32TimeOutCount;
    uint32_t u32EOB_Flag = 0ul;

    for (i = 1ul; i <= u32MsgCount; i++)
    {
        u32TimeOutCount = 0ul;

        u32MsgNum += (i - 1ul);

        if (i == u32MsgCount)
        {
            u32EOB_Flag = 1ul;
        }
        else
        {
        }

        while (CAN_SetRxMsgObj(tCAN, (uint8_t)u32MsgNum, (uint8_t)u32IDType, u32ID, (uint8_t)u32EOB_Flag) == (int32_t)FALSE)
        {
            if (++u32TimeOutCount >= RETRY_COUNTS)
            {
                rev = (int32_t)FALSE;
                break;
            }
            else
            {
            }
        }
    }

    return rev;
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
int32_t CAN_Transmit(CAN_T *tCAN, uint32_t u32MsgNum, STR_CANMSG_T *pCanMsg)
{
    int32_t rev = (int32_t)TRUE;
    uint32_t u32Tmp;

    u32Tmp = (tCAN->TEST & CAN_TEST_BASIC_Msk);

    if ((tCAN->CON & CAN_CON_TEST_Msk) && u32Tmp)
    {
        rev = CAN_BasicSendMsg(tCAN, pCanMsg);
    }
    else
    {
        if (CAN_SetTxMsg(tCAN, u32MsgNum, pCanMsg) == FALSE)
        {
            rev = (int32_t)FALSE;
        }
        else
        {
            CAN_TriggerTxMsg(tCAN, u32MsgNum);
        }
    }

    return rev;
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
int32_t CAN_Receive(CAN_T *tCAN, uint32_t u32MsgNum, STR_CANMSG_T *pCanMsg)
{
    int32_t rev = (int32_t)TRUE;
    uint32_t u32Tmp;

    u32Tmp = (tCAN->TEST & CAN_TEST_BASIC_Msk);

    if ((tCAN->CON & CAN_CON_TEST_Msk) && u32Tmp)
    {
        rev = CAN_BasicReceiveMsg(tCAN, pCanMsg);
    }
    else
    {
        rev = CAN_ReadMsgObj(tCAN, (uint8_t)u32MsgNum, (uint8_t)TRUE, pCanMsg);
    }

    return rev;
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

    if ((u32MsgIfNum = LockIF_TL(tCAN)) == 2ul)
    {
        u32MsgIfNum = 0ul;
    }
    else
    {
    }

    tCAN->IF[u32MsgIfNum].CMASK = CAN_IF_CMASK_CLRINTPND_Msk | CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    tCAN->IF[u32MsgIfNum].CREQ = 1ul + u32MsgNum;

    ReleaseIF(tCAN, u32MsgIfNum);
}


/*@}*/ /* end of group CAN_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CAN_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

