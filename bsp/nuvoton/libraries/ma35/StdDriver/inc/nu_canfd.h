/****************************************************************************
 * @file     nu_canfd.h
 * @version  V1.00
 * @brief    CAN FD driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef __NU_CANFD_H__
#define __NU_CANFD_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CANFD_Driver CAN_FD Driver
  @{
*/

/** @addtogroup CANFD_EXPORTED_CONSTANTS CAN_FD Exported Constants
  @{
*/

#define CANFD_OP_CAN_MODE     0
#define CANFD_OP_CAN_FD_MODE  1

/* Reserved number of elements in Message RAM - used for calculation of start addresses within RAM Configuration
   some element_numbers set to less than max, to stay altogether below 256 words of Message RAM requirement*/
#define CANFD_MAX_11_BIT_FTR_ELEMS    128ul  /*!<  maximum is 128 11-bit Filter */
#define CANFD_MAX_29_BIT_FTR_ELEMS    64ul   /*!<  maximum is  64 29-bit Filter */
#define CANFD_MAX_RX_FIFO0_ELEMS      64ul   /*!<  maximum is  64 Rx FIFO 0 elements */
#define CANFD_MAX_RX_FIFO1_ELEMS      64ul   /*!<  maximum is  64 Rx FIFO 1 elements */
#define CANFD_MAX_RX_BUF_ELEMS        64ul   /*!<  maximum is  64 Rx Buffers */
#define CANFD_MAX_TX_BUF_ELEMS        32ul   /*!<  maximum is  32 Tx Buffers */
#define CANFD_MAX_TX_EVNT_FIFO_ELEMS  32ul   /*!<  maximum is  32 Tx Event FIFO elements */

/* CAN FD sram size  */
#define CANFD_SRAM_SIZE          0x2000ul
#define CANFD_SRAM_OFFSET        0x200ul

/* CAN FD sram address  */
#define CANFD_SRAM_BASE_ADDR(psCanfd)  ((uint32_t)psCanfd + CANFD_SRAM_OFFSET)

/* CAN FD  Mask all interrupt */
#define CANFD_INT_ALL_SIGNALS         0x3FFFFFFFul

/* Maximum size of a CAN FD frame. Must be a valid CAN FD value */
#define CANFD_MAX_MESSAGE_BYTES     64

/* Maximum size of a CAN FD frame. Must be a valid CAN FD value */
#define CANFD_MAX_MESSAGE_WORDS     (CANFD_MAX_MESSAGE_BYTES/4)

/* Receive message buffer helper macro */
#define CANFD_RX_BUFFER_STD(id, mbIdx)               ((7UL << 27) | ((id & 0x7FF) << 16) | (mbIdx & 0x3F))

/* Receive message buffer extended helper macro - low */
#define CANFD_RX_BUFFER_EXT_LOW(id, mbIdx)           ((7UL << 29) | (id & 0x1FFFFFFFUL))

/*  Receive message buffer extended helper macro - high */
#define CANFD_RX_BUFFER_EXT_HIGH(id, mbIdx)          (mbIdx & 0x3FUL)

/*  CAN FD Rx FIFO 0 Mask helper macro. */
#define CANFD_RX_FIFO0_STD_MASK(match, mask)         ((2UL << 30) | (1UL << 27) | ((match & 0x7FF) << 16) | (mask & 0x7FF))

/* CAN FD Rx FIFO 0 extended Mask helper macro - low. */
#define CANFD_RX_FIFO0_EXT_MASK_LOW(match)           ((1UL << 29) | (match & 0x1FFFFFFF))

/* CAN FD Rx FIFO 0 extended Mask helper macro - high. */
#define CANFD_RX_FIFO0_EXT_MASK_HIGH(mask)           ((2UL << 30) | (mask & 0x1FFFFFFF))

/* CAN FD Rx FIFO 1 Mask helper macro. */
#define CANFD_RX_FIFO1_STD_MASK(match, mask)         ((2UL << 30) | (2UL << 27) | ((match & 0x7FF) << 16) | (mask & 0x7FF))

/* CANFD Rx FIFO 1 extended Mask helper macro - low. */
#define CANFD_RX_FIFO1_EXT_MASK_LOW(match)           ((2UL << 29) | (match & 0x1FFFFFFF))

/* CANFD Rx FIFO 1 extended Mask helper macro - high. */
#define CANFD_RX_FIFO1_EXT_MASK_HIGH(mask)           ((2UL << 30) | (mask & 0x1FFFFFFF))

/**
 *    @brief        Get the CAN Communication State Flag
 *
 *    @param[in]    canfd    The pointer of the specified CANFD module
 *
 *    @retval       0 Synchronizing - node is synchronizing on CANFD communication.
 *    @retval       1 Idle - node is neither receiver nor transmitter.
 *    @retval       2 Receiver - node is operating as receiver.
 *    @retval       3 Transmitter - node is operating as transmitter.
 *
 *    @details      This macro gets the CANFD communication state.
 *    \hideinitializer
 */
#define CANFD_GET_COMMUNICATION_STATE(canfd)    (((canfd)->PSR  & CANFD_PSR_ACT_Msk) >> CANFD_PSR_ACT_Pos)


/* CAN FD frame data field size. */
typedef enum
{
    eCANFD_BYTE8  = 0, /*!< 8 byte data field. */
    eCANFD_BYTE12 = 1, /*!< 12 byte data field. */
    eCANFD_BYTE16 = 2, /*!< 16 byte data field. */
    eCANFD_BYTE20 = 3, /*!< 20 byte data field. */
    eCANFD_BYTE24 = 4, /*!< 24 byte data field. */
    eCANFD_BYTE32 = 5, /*!< 32 byte data field. */
    eCANFD_BYTE48 = 6, /*!< 48 byte data field. */
    eCANFD_BYTE64 = 7  /*!< 64 byte data field. */
} E_CANFD_DATA_FIELD_SIZE;

/* CAN FD Tx FIFO/Queue Mode. */
typedef enum
{
    eCANFD_QUEUE_MODE = 0, /*!< Tx FIFO operation. */
    eCANFD_FIFO_MODE = 1   /*!< Tx Queue operation. */
} E_CANFD_MODE;

/* CAN FD Test & Bus monitor Mode. */
typedef enum
{
    eCANFD_NORMAL = 0,              /*!< None, Normal mode. */

    /*
    Support:
    (1) to receive data frames
    (2) to receive remote frames
    (3) to give acknowledge to valid frames
    Not support:
    (1) data frames sending
    (2) remote frames sending
    (3) active error frames or overload frames sending
    */
    eCANFD_RESTRICTED_OPERATION,    /*!< Receive external RX frame and always keep recessive state or send dominate bit on ACK bit on TX pin. */

    /*
    Support:
    (1) to receive valid data frames
    (2) to receive valid remote frames
    Not support:
    (1) transmission start
    (2) acknowledge to valid frames
    */
    eCANFD_BUS_MONITOR,             /*!< Receive external RX frame and always keep recessive state on TX pin. */

    /*
    Support:
    (1) Loopback
    (2) Also send out frames
    Not support:
    (1) to receive external frame
    */
    eCANFD_LOOPBACK_EXTERNAL,       /*!< Won't receive external RX frame. */
    /*
    Support:
    (1) Loopback
    Not support:
    (1) to receive external frame
    (2) transmission start
    */
    eCANFD_LOOPBACK_INTERNAL        /*!< Won't receive external RX frame and always keep recessive state on TX pin */
} E_CANFD_TEST_MODE;

/* TX Buffer Configuration Parameters  */
typedef struct
{
    E_CANFD_DATA_FIELD_SIZE eDataFieldSize;     /*!< TX Buffer Data Field Size (8byte .. 64byte) */
    E_CANFD_MODE            eModeSel;           /*!< select: CANFD_QUEUE_MODE/CANFD_FIFO_MODE */
    uint32_t                u32ElemCnt;         /*!< Elements in FIFO/Queue */
    uint32_t                u32DBufNumber;      /*!< Number of dedicated TX buffers */
} CANFD_TX_BUF_CONFIG_T;


/* Nominal Bit Timing Parameters */
typedef struct
{
    uint32_t u32BitRate;          /*!< Transceiver baud rate in bps */
    uint16_t u16TDCOffset;        /*!< Transceiver Delay Compensation Offset */
    uint16_t u16TDCFltrWin;       /*!< Transceiver Delay Compensation Filter Window Length */
    uint8_t  u8TDC;               /*!< Transceiver Delay Compensation (1:Yes, 0:No) */
} CANFD_NBT_CONFIG_T;


/* Data Bit Timing Parameters */
typedef struct
{
    uint32_t u32BitRate;          /*!< Transceiver baud rate in bps */
    uint16_t u16TDCOffset;        /*!< Transceiver Delay Compensation Offset */
    uint16_t u16TDCFltrWin;       /*!< Transceiver Delay Compensation Filter Window Length */
    uint8_t  u8TDC;               /*!< Transceiver Delay Compensation (1:Yes, 0:No) */
} CANFD_DBT_CONFIG_T;

/*! CAN FD protocol timing characteristic configuration structure. */
typedef struct
{
    uint8_t  u8PreDivider;        /*!< Global Clock Division Factor. */
    uint16_t u16NominalPrescaler; /*!< Nominal clock prescaler. */
    uint8_t  u8NominalRJumpwidth; /*!< Nominal Re-sync Jump Width. */
    uint8_t  u8NominalPhaseSeg1;  /*!< Nominal Phase Segment 1. */
    uint8_t  u8NominalPhaseSeg2;  /*!< Nominal Phase Segment 2. */
    uint8_t  u8NominalPropSeg;    /*!< Nominal Propagation Segment. */
    uint8_t  u8DataPrescaler;     /*!< Data clock prescaler. */
    uint8_t  u8DataRJumpwidth;    /*!< Data Re-sync Jump Width. */
    uint8_t  u8DataPhaseSeg1;     /*!< Data Phase Segment 1. */
    uint8_t  u8DataPhaseSeg2;     /*!< Data Phase Segment 2. */
    uint8_t  u8DataPropSeg;       /*!< Data Propagation Segment. */

} CANFD_TIMEING_CONFIG_T;

/* CAN FD module configuration structure. */
typedef struct
{
    CANFD_NBT_CONFIG_T sNormBitRate;       /*!< Normal bit rate. */
    CANFD_DBT_CONFIG_T sDataBitRate;       /*!< Data bit rate.   */
    CANFD_TIMEING_CONFIG_T sConfigBitTing; /*!< Bit timing config*/
    uint8_t bFDEn;                         /*!< 1 == FD Operation enabled. */
    uint8_t bBitRateSwitch;                /*!< 1 == Bit Rate Switch enabled (only evaluated in HW, if FD operation enabled). */
    E_CANFD_TEST_MODE evTestMode;          /*!< See E_CANFD_TEST_MODE declaration. */
} CANFD_FD_BT_CONFIG_T;

/* CAN FD Message RAM Partitioning - i.e. Start Addresses (BYTE) */
typedef struct
{
    uint32_t u32SIDFC_FLSSA; /*!<Standard ID Filter Configuration */
    uint32_t u32XIDFC_FLESA; /*!<Extended ID Filter Configuration */
    uint32_t u32RXF0C_F0SA;  /*!< RX FIFO 0 Start Address */
    uint32_t u32RXF1C_F1SA;  /*!< RX FIFO 1 Start Address */
    uint32_t u32RXBC_RBSA;   /*!< Rx Buffer Configuration */
    uint32_t u32TXEFC_EFSA;  /*!< Tx Event FIFO Configuration */
    uint32_t u32TXBC_TBSA;   /*!< Tx Buffer Configuration */
} CANFD_RAM_PART_T;

/*CAN FD element size structure */
typedef struct
{
    uint32_t  u32SIDFC;          /*!< Standard Message ID Filter element size in words  */
    uint32_t  u32XIDFC;          /*!< Extended Message ID Filter element size in words  */
    uint32_t  u32RxFifo0;        /*!< Rx FIFO0 element size in words  */
    uint32_t  u32RxFifo1;        /*!< Rx FIFO1 element size in words  */
    uint32_t  u32RxBuf;          /*!< Rx Buffer element size in words */
    uint32_t  u32TxBuf;          /*!< Tx Buffer element size in words */
    uint32_t  u32TxEventFifo;    /*!< Tx Event FIFO element size in words */
} CANFD_ELEM_SIZE_T;

/* CAN FD Message frame structure */
typedef struct
{
    CANFD_FD_BT_CONFIG_T    sBtConfig;        /*!< Bit Timing Configuration */
    CANFD_RAM_PART_T        sMRamStartAddr;   /*!< Absolute Byte Start Addresses for Element Types in Message RAM */
    CANFD_ELEM_SIZE_T       sElemSize;        /*!< Size of Elements in Message RAM (RX Elem. in FIFO0, in FIFO1, TX Buffer) given in words */
    CANFD_TX_BUF_CONFIG_T   sTxConfig;        /*!< TX Buffer Configuration  */
    uint32_t                u32MRamSize;      /*!< Size of the Message RAM: number of words */
} CANFD_FD_T;

/* CAN FD Message ID Type */
typedef enum
{
    eCANFD_SID = 0,  /*!< Standard frame format attribute. */
    eCANFD_XID = 1   /*!< Extend frame format attribute. */
} E_CANFD_ID_TYPE;

/* CAN FD Rx Message Type */
typedef enum
{
    eCANFD_RX_FIFO_0 = 0,
    eCANFD_RX_FIFO_1 = 1,
    eCANFD_RX_DBUF = 2
} E_CANFD_RX_BUF_TYPE;

/* CAN FD communication state.*/
typedef enum
{
    eCANFD_SYNC         = 0,
    eCANFD_IDLE         = 1,
    eCANFD_RECEIVER     = 2,
    eCANFD_TRANSMITTER  = 3
} E_CANFD_COMMUNICATION_STATE;

/* CAN FD Message receive Information: via which RX Buffers, etc. */
typedef struct
{
    E_CANFD_RX_BUF_TYPE  eRxBuf;         /*!< Type of RX Buffer */
    uint32_t            u32BufIdx;       /*!< RX Buffer: buffer index, if RX FIFO: GetIndex */
} CANFD_RX_INFO_T;

/* CAN FD frame type. */
typedef enum
{
    eCANFD_DATA_FRM = 0,      /*!< Data frame type attribute. */
    eCANFD_REMOTE_FRM = 1     /*!< Remote frame type attribute. */
} E_CANFD_FRM_TYPE;

/* CAN FD Message Struct */
typedef struct
{
    E_CANFD_ID_TYPE   eIdType;                         /*! Standard ID or Extended ID */
    CANFD_RX_INFO_T   sRxInfo;                         /*! Information regarding the reception of the frame */
    E_CANFD_FRM_TYPE  eFrmType;                        /*! eCANFD_DATA_FRM/eCANFD_REMOTE_FRM */
    uint32_t          u32Id;                           /*! Standard ID (11bits) or Extended ID (29bits) */
    uint32_t          u32DLC;                          /*! Data Length */
    union
    {
        uint32_t au32Data[CANFD_MAX_MESSAGE_WORDS];    /*!< Word access to buffer data. */
        uint8_t  au8Data[CANFD_MAX_MESSAGE_BYTES];     /*!< Byte access to buffer data. */
    };
    uint8_t           u8MsgMarker;                     /*! Message marker (will be copied to TX Event FIFO element) */
    uint8_t           bFDFormat;                       /*! FD Format (1 = FD Format) */
    uint8_t           bBitRateSwitch;                  /*! Bit Rate Switch (1 = with Bit Rate Switch) */
    uint8_t           bErrStaInd;                      /*! Error State Indicator */
    uint8_t           bEvntFifoCon;                    /*! Event FIFO Control (1 = Store TX Event FIFO element after transmission)*/
} CANFD_FD_MSG_T;


/*   Transmit and Receive message element structure. */
typedef struct
{
    uint32_t u32Id;     /*!< Message identifier and associated flags. */
    uint32_t u32Config; /*!< Buffer configuration. */
    union
    {
        uint32_t au32Data[CANFD_MAX_MESSAGE_WORDS];  /*!< Word access to buffer data. */
        uint8_t  au8Data[CANFD_MAX_MESSAGE_BYTES];   /*!< Byte access to buffer data. */
    };
} CANFD_BUF_T;

/* Standard ID message filter element structure.*/
typedef struct
{
    union
    {
        struct
        {
            uint32_t SFID2     : 11; /*!<Standard Filter ID 2. */
            uint32_t reserved1 : 5;
            uint32_t SFID1     : 11; /*!<Standard Filter ID 1. */
            uint32_t SFEC      : 3;  /*!<Standard Filter Element Configuration */
            uint32_t SFT       : 2;  /*!<Standard Filter Type */
        };
        struct
        {
            uint32_t VALUE; /*!< Access to filter as a word. */
        };
    };
} CANFD_STD_FILTER_T;

/* Extended ID message filter element structure.*/
typedef struct
{
    union
    {
        struct
        {
            uint32_t EFID1     : 29; /*!< Extended Filter ID 1. */
            uint32_t EFEC      : 3;  /*!< Extended Filter Element Configuration. */
            uint32_t EFID2     : 29; /*!< Extended Filter ID 2. */
            uint32_t reserved1 : 1;
            uint32_t EFT       : 2;  /*!< Extended Filter Type. */
        };
        struct
        {
            uint32_t LOWVALUE;  /*!< Access to filter low word. */
            uint32_t HIGHVALUE; /*!< Access to filter high word. */
        };
    };
} CANFD_EXT_FILTER_T;

/* Accept Non-matching Frames (GFC Register) */
typedef enum
{
    eCANFD_ACC_NON_MATCH_FRM_RX_FIFO0 = 0x0,  /*!< Accept Non-Masking Frames in Rx FIFO 0. */
    eCANFD_ACC_NON_MATCH_FRM_RX_FIFO1 = 0x1,  /*!< Accept Non-Masking Frames in Rx FIFO 1. */
    eCANFD_REJ_NON_MATCH_FRM   = 0x3          /*!< Reject Non-Matching Frames. */
} E_CANFD_ACC_NON_MATCH_FRM;


/* Standard ID Filter Element Type */
typedef enum
{
    eCANFD_SID_FLTR_TYPE_RANGE     = 0x0, /*!< Range filter from SFID1 to SFID2. */
    eCANFD_SID_FLTR_TYPE_DUAL      = 0x1, /*!< Dual ID filter for SFID1 or SFID2. */
    eCANFD_SID_FLTR_TYPE_CLASSIC   = 0x2, /*!< Classic filter: SFID1 = filter, SFID2 = mask. */
    eCANFD_SID_FLTR_TYPE_DIS       = 0x3  /*!< Filter element disabled */
} E_CANFD_SID_FLTR_ELEM_TYPE;

/* Extended ID Filter Element Type */
typedef enum
{
    eCANFD_XID_FLTR_TYPE_RANGE      = 0x0,  /*!< Range filter from EFID1 to EFID2. */
    eCANFD_XID_FLTR_TYPE_DUAL       = 0x1,  /*!< Dual ID filter for EFID1 or EFID2. */
    eCANFD_XID_FLTR_TYPE_CLASSIC    = 0x2,  /*!< Classic filter: EFID1=filter, EFID2=mask */
    eCANFD_XID_FLTR_TYPE_RANGE_XIDAM_NOT_APP     = 0x3   /*!< XID range filter from EFID1 to EFID2(EFID2 > EFID1), XIDAM not applied */
}  E_CANFD_XID_FLTR_ELEM_TYPE;

/* Filter Element Configuration - Can be used for SFEC(Standard Id filter configuration) and EFEC(Extended Id filter configuration) */
typedef enum
{
    eCANFD_FLTR_ELEM_DIS         = 0x0,            /*!< Filter Element Disable  */
    eCANFD_FLTR_ELEM_STO_FIFO0   = 0x1,            /*!< Filter Element Store In Fifo0  */
    eCANFD_FLTR_ELEM_STO_FIFO1   = 0x2,            /*!< Filter Element Store In Fifo1  */
    eCANFD_FLTR_ELEM_REJ_ID      = 0x3,            /*!< Filter Element RejectId  */
    eCANFD_FLTR_ELEM_SET_PRI     = 0x4,            /*!< Filter Element Set Priority */
    eCANFD_FLTR_ELEM_SET_PRI_STO_FIFO0 = 0x5,      /*!< Filter Element Set Priority And Store In Fifo0  */
    eCANFD_FLTR_ELEM_SET_PRI_STO_FIFO1 = 0x6,      /*!< Filter Element Set Priority And Store In Fifo1  */
    eCANFD_FLTR_ELEM_STO_RX_BUF_OR_DBG_MSG = 0x7   /*!< Filter Element Store In Rx Buf Or Debug Msg  */
} E_CANFD_FLTR_CONFIG;

/* TX Event FIFO Element Struct */
typedef struct
{
    E_CANFD_ID_TYPE     eIdType;         /*!< Standard ID or Extended ID */
    uint32_t            u32Id;           /*!< Standard ID (11bits) or Extended ID (29bits) */
    uint32_t            u32DLC;          /*!< Data Length Code used in the frame on the bus */
    uint32_t            u32TxTs;         /*!< Tx Timestamp */
    uint32_t            u32MsgMarker;    /*!< Message marker */
    uint8_t             bErrStaInd;      /*!< Error State Indicator */
    uint8_t             bRemote;         /*!< Remote transmission request */
    uint8_t             bFDFormat;       /*!< FD Format */
    uint8_t             bBitRateSwitch;  /*!< Bit Rate Switch */
} CANFD_TX_EVNT_ELEM_T;

#define CANFD_TIMEOUT             1000000           /* 1 second time-out */
#define CANFD_OK                 ( 0L)              /*!< CANFD operation OK */
#define CANFD_ERR_FAIL           (-1L)              /*!< CANFD operation failed */
#define CANFD_ERR_TIMEOUT        (-2L)              /*!< CANFD operation abort due to timeout error */
#define CANFD_READ_REG_TIMEOUT   (48UL)             /*!< CANFD read register time-out count */

void CANFD_Open(CANFD_T *canfd, CANFD_FD_T *psCanfdStr);
void CANFD_Close(CANFD_T *canfd);
void CANFD_EnableInt(CANFD_T *canfd, uint32_t u32IntLine0, uint32_t u32IntLine1, uint32_t u32TXBTIE, uint32_t u32TXBCIE);
void CANFD_DisableInt(CANFD_T *canfd, uint32_t u32IntLine0, uint32_t u32IntLine1, uint32_t u32TXBTIE, uint32_t u32TXBCIE);
uint32_t CANFD_TransmitTxMsg(CANFD_T *canfd, uint32_t u32TxBufIdx, CANFD_FD_MSG_T *psTxMsg);
uint32_t CANFD_TransmitDMsg(CANFD_T *canfd, uint32_t u32TxBufIdx, CANFD_FD_MSG_T *psTxMsg);
void CANFD_SetGFC(CANFD_T *canfd, E_CANFD_ACC_NON_MATCH_FRM eNMStdFrm, E_CANFD_ACC_NON_MATCH_FRM eEMExtFrm, uint32_t u32RejRmtStdFrm, uint32_t u32RejRmtExtFrm);
void CANFD_SetSIDFltr(CANFD_T *canfd, uint32_t u32FltrIdx, uint32_t u32Filter);
void CANFD_SetXIDFltr(CANFD_T *canfd, uint32_t u32FltrIdx, uint32_t u32FilterLow, uint32_t u32FilterHigh);
uint32_t CANFD_ReadRxBufMsg(CANFD_T *canfd, uint8_t u8MbIdx, CANFD_FD_MSG_T *psMsgBuf);
uint32_t CANFD_ReadRxFifoMsg(CANFD_T *canfd, uint8_t u8FifoIdx, CANFD_FD_MSG_T *psMsgBuf);
void CANFD_CopyDBufToMsgBuf(CANFD_BUF_T *psRxBuffer, CANFD_FD_MSG_T *psMsgBuf);
void CANFD_CopyRxFifoToMsgBuf(CANFD_BUF_T *psRxBuf, CANFD_FD_MSG_T *psMsgBuf);
uint32_t CANFD_GetRxFifoWaterLvl(CANFD_T *canfd, uint32_t u32RxFifoNum);
void CANFD_TxBufCancelReq(CANFD_T *canfd, uint32_t u32TxBufIdx);
uint32_t CANFD_IsTxBufCancelFin(CANFD_T *canfd, uint32_t u32TxBufIdx);
uint32_t CANFD_IsTxBufTransmitOccur(CANFD_T *canfd, uint32_t u32TxBufIdx);
uint32_t CANFD_GetTxEvntFifoWaterLvl(CANFD_T *canfd);
void CANFD_CopyTxEvntFifoToUsrBuf(CANFD_T *canfd, uint32_t u32TxEvntNum, CANFD_TX_EVNT_ELEM_T *psTxEvntElem);
void CANFD_GetBusErrCount(CANFD_T *canfd, uint8_t *pu8TxErrBuf, uint8_t *pu8RxErrBuf);
int32_t CANFD_RunToNormal(CANFD_T *canfd, uint8_t u8Enable);
void CANFD_GetDefaultConfig(CANFD_FD_T *psConfig, uint8_t u8OpMode);
void CANFD_ClearStatusFlag(CANFD_T *canfd, uint32_t u32InterruptFlag);
uint32_t CANFD_GetStatusFlag(CANFD_T *canfd, uint32_t u32IntTypeFlag);
uint32_t CANFD_ReadReg(__I uint32_t *pu32RegAddr);

/*@}*/ /* end of group CANFD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CANFD_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __NU_CANFD_H__ */
