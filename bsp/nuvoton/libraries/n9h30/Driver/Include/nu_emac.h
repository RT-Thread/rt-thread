/**************************************************************************//**
 * @file     nu_emac.h
 * @version  V1.00
 * @brief    EMAC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_EMAC_H__
#define __NU_EMAC_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "emac_reg.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EMAC_Driver EMAC Driver
  @{
*/

/** @addtogroup EMAC_EXPORTED_CONSTANTS EMAC Exported Constants
  @{
*/

#define EMAC_PHY_ADDR      1UL    /*!<  PHY address, this address is board dependent \hideinitializer */
#define EMAC_RX_DESC_SIZE  64UL    /*!<  Number of Rx Descriptors, should be 2 at least \hideinitializer */
#define EMAC_TX_DESC_SIZE  32UL    /*!<  Number of Tx Descriptors, should be 2 at least \hideinitializer */
#define EMAC_CAMENTRY_NB   16UL   /*!<  Number of CAM \hideinitializer */
#define EMAC_MAX_PKT_SIZE  1536UL /*!<  Number of HDR + EXTRA + VLAN_TAG + PAYLOAD + CRC \hideinitializer */

#define EMAC_LINK_DOWN    0UL    /*!<  Ethernet link is down \hideinitializer */
#define EMAC_LINK_100F    1UL    /*!<  Ethernet link is 100Mbps full duplex \hideinitializer */
#define EMAC_LINK_100H    2UL    /*!<  Ethernet link is 100Mbps half duplex \hideinitializer */
#define EMAC_LINK_10F     3UL    /*!<  Ethernet link is 10Mbps full duplex \hideinitializer */
#define EMAC_LINK_10H     4UL    /*!<  Ethernet link is 10Mbps half duplex \hideinitializer */

/*@}*/ /* end of group EMAC_EXPORTED_CONSTANTS */


/** Tx/Rx buffer descriptor structure */
typedef struct
{
    uint32_t u32Status1;   /*!<  Status word 1 */
    uint32_t u32Data;      /*!<  Pointer to data buffer */
    uint32_t u32Status2;   /*!<  Status word 2 */
    uint32_t u32Next;      /*!<  Pointer to next descriptor */
    uint32_t u32Backup1;   /*!<  For backup descriptor fields over written by time stamp */
    uint32_t u32Backup2;   /*!<  For backup descriptor fields over written by time stamp */
} EMAC_DESCRIPTOR_T;

/** Tx/Rx buffer structure */
typedef struct
{
    uint8_t au8Buf[EMAC_MAX_PKT_SIZE];
} EMAC_FRAME_T;

typedef struct
{
    EMAC_T  *psEmac;

    uint32_t u32TxDescSize;
    uint32_t u32RxDescSize;

    EMAC_DESCRIPTOR_T *psRXDescs;
    EMAC_FRAME_T *psRXFrames;
    EMAC_DESCRIPTOR_T *psTXDescs;
    EMAC_FRAME_T *psTXFrames;

    EMAC_DESCRIPTOR_T *psCurrentTxDesc;
    EMAC_DESCRIPTOR_T *psNextTxDesc;
    EMAC_DESCRIPTOR_T *psCurrentRxDesc;

} EMAC_MEMMGR_T;

/** @addtogroup EMAC_EXPORTED_FUNCTIONS EMAC Exported Functions
  @{
*/


/**
  * @brief  Enable EMAC Tx function
  * @param  None
  * @return None
  * \hideinitializer
  */
#define EMAC_ENABLE_TX(EMAC) (EMAC->CTL |= EMAC_CTL_TXON_Msk)


/**
  * @brief  Enable EMAC Rx function
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_ENABLE_RX(EMAC) do{EMAC->CTL |= EMAC_CTL_RXON_Msk; EMAC->RXST = 0;}while(0)

/**
  * @brief  Disable EMAC Tx function
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_DISABLE_TX(EMAC) (EMAC->CTL &= ~EMAC_CTL_TXON_Msk)


/**
  * @brief  Disable EMAC Rx function
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_DISABLE_RX(EMAC) (EMAC->CTL &= ~EMAC_CTL_RXON_Msk)

/**
  * @brief  Enable EMAC Magic Packet Wakeup function
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_ENABLE_MAGIC_PKT_WAKEUP(EMAC) (EMAC->CTL |= EMAC_CTL_WOLEN_Msk)

/**
  * @brief  Disable EMAC Magic Packet Wakeup function
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_DISABLE_MAGIC_PKT_WAKEUP(EMAC) (EMAC->CTL &= ~EMAC_CTL_WOLEN_Msk)

/**
  * @brief  Enable EMAC to receive broadcast packets
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_ENABLE_RECV_BCASTPKT(EMAC) (EMAC->CAMCTL |= EMAC_CAMCTL_ABP_Msk)

/**
  * @brief  Disable EMAC to receive broadcast packets
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_DISABLE_RECV_BCASTPKT(EMAC) (EMAC->CAMCTL &= ~EMAC_CAMCTL_ABP_Msk)

/**
  * @brief  Enable EMAC to receive multicast packets
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_ENABLE_RECV_MCASTPKT(EMAC) (EMAC->CAMCTL |= EMAC_CAMCTL_AMP_Msk)

/**
  * @brief  Disable EMAC Magic Packet Wakeup function
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_DISABLE_RECV_MCASTPKT(EMAC) (EMAC->CAMCTL &= ~EMAC_CAMCTL_AMP_Msk)

/**
  * @brief  Check if EMAC time stamp alarm interrupt occurred or not
  * @param  The pointer of the specified EMAC module
  * @return If time stamp alarm interrupt occurred or not
  * @retval 0 Alarm interrupt does not occur
  * @retval 1 Alarm interrupt occurred
  * \hideinitializer
  */
#define EMAC_GET_ALARM_FLAG(EMAC) (EMAC->INTSTS & EMAC_INTSTS_TSALMIF_Msk ? 1 : 0)

/**
  * @brief  Clear EMAC time stamp alarm interrupt flag
  * @param  The pointer of the specified EMAC module
  * @return None
  * \hideinitializer
  */
#define EMAC_CLR_ALARM_FLAG(EMAC) (EMAC->INTSTS = EMAC_INTSTS_TSALMIF_Msk)

/**
  * @brief  Trigger EMAC Rx function
  * @param  The pointer of the specified EMAC module
  * @return None
  */
#define EMAC_TRIGGER_RX(EMAC) do{EMAC->RXST = 0UL;}while(0)

/**
  * @brief  Trigger EMAC Tx function
  * @param  The pointer of the specified EMAC module
  * @return None
  */
#define EMAC_TRIGGER_TX(EMAC) do{EMAC->TXST = 0UL;}while(0)

/**
 *    @brief        Enable specified EMAC interrupt
 *
 *    @param[in]    EMAC        The pointer of the specified EMAC module
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - \ref EMAC_INTEN_RXIEN_Msk    : Receive
 *                              - \ref EMAC_INTEN_CRCEIEN_Msk  : CRC Error
 *                              - \ref EMAC_INTEN_RXOVIEN_Msk  : Receive FIFO Overflow
 *                              - \ref EMAC_INTEN_LPIEN_Msk    : Long Packet
 *                              - \ref EMAC_INTEN_RXGDIEN_Msk  : Receive Good
 *                              - \ref EMAC_INTEN_ALIEIEN_Msk  : Alignment Error
 *                              - \ref EMAC_INTEN_RPIEN_Msk    : Runt Packet
 *                              - \ref EMAC_INTEN_MPCOVIEN_Msk : Miss Packet Counter Overrun
 *                              - \ref EMAC_INTEN_MFLEIEN_Msk  : Maximum Frame Length Exceed
 *                              - \ref EMAC_INTEN_DENIEN_Msk   : DMA Early Notification
 *                              - \ref EMAC_INTEN_RDUIEN_Msk   : Receive Descriptor Unavailable
 *                              - \ref EMAC_INTEN_RXBEIEN_Msk  : Receive Bus Error
 *                              - \ref EMAC_INTEN_CFRIEN_Msk   : Control Frame Receive
 *                              - \ref EMAC_INTEN_WOLIEN_Msk   : Wake on LAN Interrupt
 *                              - \ref EMAC_INTEN_TXIEN_Msk    : Transmit
 *                              - \ref EMAC_INTEN_TXUDIEN_Msk  : Transmit FIFO Underflow
 *                              - \ref EMAC_INTEN_TXCPIEN_Msk  : Transmit Completion
 *                              - \ref EMAC_INTEN_EXDEFIEN_Msk : Defer Exceed
 *                              - \ref EMAC_INTEN_NCSIEN_Msk   : No Carrier Sense
 *                              - \ref EMAC_INTEN_TXABTIEN_Msk : Transmit Abort
 *                              - \ref EMAC_INTEN_LCIEN_Msk    : Late Collision
 *                              - \ref EMAC_INTEN_TDUIEN_Msk   : Transmit Descriptor Unavailable
 *                              - \ref EMAC_INTEN_TXBEIEN_Msk  : Transmit Bus Error
 *                              - \ref EMAC_INTEN_TSALMIEN_Msk : Time Stamp Alarm
 *
 *    @return       None
 *
 *    @details      This macro enable specified EMAC interrupt.
 *    \hideinitializer
 */
#define EMAC_ENABLE_INT(EMAC, u32eIntSel)    ((EMAC)->INTEN |= (u32eIntSel))

/**
 *    @brief        Disable specified EMAC interrupt
 *
 *    @param[in]    emac        The pointer of the specified EMAC module
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - \ref EMAC_INTEN_RXIEN_Msk    : Receive
 *                              - \ref EMAC_INTEN_CRCEIEN_Msk  : CRC Error
 *                              - \ref EMAC_INTEN_RXOVIEN_Msk  : Receive FIFO Overflow
 *                              - \ref EMAC_INTEN_LPIEN_Msk    : Long Packet
 *                              - \ref EMAC_INTEN_RXGDIEN_Msk  : Receive Good
 *                              - \ref EMAC_INTEN_ALIEIEN_Msk  : Alignment Error
 *                              - \ref EMAC_INTEN_RPIEN_Msk    : Runt Packet
 *                              - \ref EMAC_INTEN_MPCOVIEN_Msk : Miss Packet Counter Overrun
 *                              - \ref EMAC_INTEN_MFLEIEN_Msk  : Maximum Frame Length Exceed
 *                              - \ref EMAC_INTEN_DENIEN_Msk   : DMA Early Notification
 *                              - \ref EMAC_INTEN_RDUIEN_Msk   : Receive Descriptor Unavailable
 *                              - \ref EMAC_INTEN_RXBEIEN_Msk  : Receive Bus Error
 *                              - \ref EMAC_INTEN_CFRIEN_Msk   : Control Frame Receive
 *                              - \ref EMAC_INTEN_WOLIEN_Msk   : Wake on LAN Interrupt
 *                              - \ref EMAC_INTEN_TXIEN_Msk    : Transmit
 *                              - \ref EMAC_INTEN_TXUDIEN_Msk  : Transmit FIFO Underflow
 *                              - \ref EMAC_INTEN_TXCPIEN_Msk  : Transmit Completion
 *                              - \ref EMAC_INTEN_EXDEFIEN_Msk : Defer Exceed
 *                              - \ref EMAC_INTEN_NCSIEN_Msk   : No Carrier Sense
 *                              - \ref EMAC_INTEN_TXABTIEN_Msk : Transmit Abort
 *                              - \ref EMAC_INTEN_LCIEN_Msk    : Late Collision
 *                              - \ref EMAC_INTEN_TDUIEN_Msk   : Transmit Descriptor Unavailable
 *                              - \ref EMAC_INTEN_TXBEIEN_Msk  : Transmit Bus Error
 *                              - \ref EMAC_INTEN_TSALMIEN_Msk : Time Stamp Alarm
 *
 *    @return       None
 *
 *    @details      This macro disable specified EMAC interrupt.
 *    \hideinitializer
 */
#define EMAC_DISABLE_INT(EMAC, u32eIntSel)    ((EMAC)->INTEN &= ~ (u32eIntSel))

/**
 *    @brief        Get specified interrupt flag/status
 *
 *    @param[in]    emac            The pointer of the specified EMAC module
 *    @param[in]    u32eIntTypeFlag Interrupt Type Flag, should be
 *                                  - \ref EMAC_INTSTS_RXIF_Msk : Receive
 *                                  - \ref EMAC_INTSTS_CRCEIF_Msk : CRC Error
 *                                  - \ref EMAC_INTSTS_RXOVIF_Msk : Receive FIFO Overflow
 *                                  - \ref EMAC_INTSTS_LPIF_Msk : Long Packet
 *                                  - \ref EMAC_INTSTS_RXGDIF_Msk : Receive Good
 *                                  - \ref EMAC_INTSTS_ALIEIF_Msk : Alignment Error
 *                                  - \ref EMAC_INTSTS_RPIF_Msk : Runt Packet
 *                                  - \ref EMAC_INTSTS_MPCOVIF_Msk : Missed Packet Counter
 *                                  - \ref EMAC_INTSTS_MFLEIF_Msk : Maximum Frame Length Exceed
 *                                  - \ref EMAC_INTSTS_DENIF_Msk : DMA Early Notification
 *                                  - \ref EMAC_INTSTS_RDUIF_Msk : Receive Descriptor Unavailable
 *                                  - \ref EMAC_INTSTS_RXBEIF_Msk : Receive Bus Error
 *                                  - \ref EMAC_INTSTS_CFRIF_Msk : Control Frame Receive
 *                                  - \ref EMAC_INTSTS_WOLIF_Msk : Wake on LAN
 *                                  - \ref EMAC_INTSTS_TXIF_Msk : Transmit
 *                                  - \ref EMAC_INTSTS_TXUDIF_Msk : Transmit FIFO Underflow
 *                                  - \ref EMAC_INTSTS_TXCPIF_Msk : Transmit Completion
 *                                  - \ref EMAC_INTSTS_EXDEFIF_Msk : Defer Exceed
 *                                  - \ref EMAC_INTSTS_NCSIF_Msk : No Carrier Sense
 *                                  - \ref EMAC_INTSTS_TXABTIF_Msk : Transmit Abort
 *                                  - \ref EMAC_INTSTS_LCIF_Msk : Late Collision
 *                                  - \ref EMAC_INTSTS_TDUIF_Msk : Transmit Descriptor Unavailable
 *                                  - \ref EMAC_INTSTS_TXBEIF_Msk : Transmit Bus Error
 *                                  - \ref EMAC_INTSTS_TSALMIF_Msk : Time Stamp Alarm
 *
 *    @return       None
 *
 *    @details      This macro get specified interrupt flag or interrupt indicator status.
 *    \hideinitializer
 */
#define EMAC_GET_INT_FLAG(EMAC, u32eIntTypeFlag)    (((EMAC)->INTSTS & (u32eIntTypeFlag))?1:0)

/**
 *    @brief        Clear specified interrupt flag/status
 *
 *    @param[in]    emac            The pointer of the specified EMAC module
 *    @param[in]    u32eIntTypeFlag Interrupt Type Flag, should be
 *                                  - \ref EMAC_INTSTS_RXIF_Msk : Receive
 *                                  - \ref EMAC_INTSTS_CRCEIF_Msk : CRC Error
 *                                  - \ref EMAC_INTSTS_RXOVIF_Msk : Receive FIFO Overflow
 *                                  - \ref EMAC_INTSTS_LPIF_Msk : Long Packet
 *                                  - \ref EMAC_INTSTS_RXGDIF_Msk : Receive Good
 *                                  - \ref EMAC_INTSTS_ALIEIF_Msk : Alignment Error
 *                                  - \ref EMAC_INTSTS_RPIF_Msk : Runt Packet
 *                                  - \ref EMAC_INTSTS_MPCOVIF_Msk : Missed Packet Counter
 *                                  - \ref EMAC_INTSTS_MFLEIF_Msk : Maximum Frame Length Exceed
 *                                  - \ref EMAC_INTSTS_DENIF_Msk : DMA Early Notification
 *                                  - \ref EMAC_INTSTS_RDUIF_Msk : Receive Descriptor Unavailable
 *                                  - \ref EMAC_INTSTS_RXBEIF_Msk : Receive Bus Error
 *                                  - \ref EMAC_INTSTS_CFRIF_Msk : Control Frame Receive
 *                                  - \ref EMAC_INTSTS_WOLIF_Msk : Wake on LAN
 *                                  - \ref EMAC_INTSTS_TXIF_Msk : Transmit
 *                                  - \ref EMAC_INTSTS_TXUDIF_Msk : Transmit FIFO Underflow
 *                                  - \ref EMAC_INTSTS_TXCPIF_Msk : Transmit Completion
 *                                  - \ref EMAC_INTSTS_EXDEFIF_Msk : Defer Exceed
 *                                  - \ref EMAC_INTSTS_NCSIF_Msk : No Carrier Sense
 *                                  - \ref EMAC_INTSTS_TXABTIF_Msk : Transmit Abort
 *                                  - \ref EMAC_INTSTS_LCIF_Msk : Late Collision
 *                                  - \ref EMAC_INTSTS_TDUIF_Msk : Transmit Descriptor Unavailable
 *                                  - \ref EMAC_INTSTS_TXBEIF_Msk : Transmit Bus Error
 *                                  - \ref EMAC_INTSTS_TSALMIF_Msk : Time Stamp Alarm
 *
 *    @retval       0 The specified interrupt is not happened.
 *                  1 The specified interrupt is happened.
 *
 *    @details      This macro clear specified interrupt flag or interrupt indicator status.
 *    \hideinitializer
 */
#define EMAC_CLEAR_INT_FLAG(EMAC, u32eIntTypeFlag)    ((EMAC)->INTSTS |= (u32eIntTypeFlag))
#define EMAC_CLEAR_ALL_INT_FLAG(EMAC)                 ((EMAC)->INTSTS |= (EMAC)->INTSTS)


void EMAC_Open(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8MacAddr);
void EMAC_Close(EMAC_T *EMAC);
void EMAC_SetMacAddr(EMAC_T *EMAC, uint8_t *pu8MacAddr);
void EMAC_EnableCamEntry(EMAC_T *EMAC, uint32_t u32Entry, uint8_t pu8MacAddr[]);
void EMAC_DisableCamEntry(EMAC_T *EMAC, uint32_t u32Entry);

uint32_t EMAC_RecvPkt(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8Data, uint32_t *pu32Size);
uint32_t EMAC_RecvPktTS(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8Data, uint32_t *pu32Size, uint32_t *pu32Sec, uint32_t *pu32Nsec);
void EMAC_RecvPktDone(EMAC_MEMMGR_T *psMemMgr);

uint32_t EMAC_SendPkt(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8Data, uint32_t u32Size);
uint32_t EMAC_SendPktDone(EMAC_MEMMGR_T *psMemMgr);
uint32_t EMAC_SendPktDoneTS(EMAC_MEMMGR_T *psMemMgr, uint32_t *pu32Sec, uint32_t *pu32Nsec);

void EMAC_EnableTS(EMAC_T *EMAC, uint32_t u32Sec, uint32_t u32Nsec);
void EMAC_DisableTS(EMAC_T *EMAC);
void EMAC_GetTime(EMAC_T *EMAC, uint32_t *pu32Sec, uint32_t *pu32Nsec);
void EMAC_SetTime(EMAC_T *EMAC, uint32_t u32Sec, uint32_t u32Nsec);
void EMAC_UpdateTime(EMAC_T *EMAC, uint32_t u32Neg, uint32_t u32Sec, uint32_t u32Nsec);
void EMAC_EnableAlarm(EMAC_T *EMAC, uint32_t u32Sec, uint32_t u32Nsec);
void EMAC_DisableAlarm(EMAC_T *EMAC);

uint32_t EMAC_CheckLinkStatus(EMAC_T *EMAC);

void EMAC_Reset(EMAC_T *EMAC);
void EMAC_PhyInit(EMAC_T *EMAC);
int32_t EMAC_FillCamEntry(EMAC_T *EMAC, uint8_t pu8MacAddr[]);
uint8_t *EMAC_ClaimFreeTXBuf(EMAC_MEMMGR_T *psMemMgr);
uint32_t EMAC_GetAvailRXBufSize(EMAC_MEMMGR_T *psMemMgr, uint8_t **ppuDataBuf);
uint32_t EMAC_SendPktWoCopy(EMAC_MEMMGR_T *psMemMgr, uint32_t u32Size);
void EMAC_RecvPktDoneWoRxTrigger(EMAC_MEMMGR_T *psMemMgr);

/*@}*/ /* end of group EMAC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EMAC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_EMAC_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
