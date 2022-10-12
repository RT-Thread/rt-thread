/**
 *******************************************************************************
 * @file  hc32_ll_can.h
 * @brief This file contains all the functions prototypes of the CAN driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_CAN_H__
#define __HC32_LL_CAN_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_CAN
 * @{
 */
#if (LL_CAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CAN_Global_Types CAN Global Types
 * @{
 */
/**
 * @brief CAN bit time configuration structure.
 * @note 1. TQ = u32Prescaler / CANClock.
 * @note 2. Bit time = (u32TimeSeg2 + u32TimeSeg2) x TQ.
 * @note 3. Baudrate = CANClock/(u32Prescaler*(u32TimeSeg1 + u32TimeSeg2))
 * @note 4. See user manual of the target MCU and ISO11898-1 for more details.
 */
typedef struct {
    uint32_t u32Prescaler;                  /*!< Specifies the prescaler of CAN clock, [1, 256]. */
    uint32_t u32TimeSeg1;                   /*!< Specifies the number of time quanta in Bit Segment 1.
                                                 u32TimeSeg1 Contains synchronization segment,
                                                 propagation time segment and phase buffer segment 1. */
    uint32_t u32TimeSeg2;                   /*!< Specifies the number of time quanta in Bit Segment 2.
                                                 Phase buffer segment 2. */
    uint32_t u32SJW;                        /*!< Synchronization Jump Width.
                                                 Specifies the maximum number of time quanta the CAN hardware
                                                 is allowed to lengthen or shorten a bit to perform resynchronization. */
} stc_can_bit_time_config_t;

/**
 * @brief CAN acceptance filter configuration structure.
 */
typedef struct {
    uint32_t u32ID;                         /*!< Specifies the identifier(ID). 11 bits standard ID or 29 bits extended ID, depending on IDE. */
    uint32_t u32IDMask;                     /*!< Specifies the identifier(ID) mask. The mask bits of ID will be ignored by the acceptance filter. */
    uint32_t u32IDType;                     /*!< Specifies the identifier(ID) type. This parameter can be a value of @ref CAN_ID_Type */
} stc_can_filter_config_t;

/* CAN-FD structure */
/**
 * @brief CAN-FD configuration structure.
 */
typedef struct {
    stc_can_bit_time_config_t stcBitCfg;    /*!< Bit time configuration of flexible data-rate bit. */
    uint8_t u8Mode;                         /*!< CAN-FD mode, Bosch CAN-FD or ISO 11898-1:2015 CAN-FD.
                                                 This parameter can be a value of @ref CAN_FD_Mode */
    uint8_t u8TDC;                          /*!< Enable or disable Transmitter Delay Compensation.
                                                 This parameter can be a value of @ref CAN_FD_TDC_En */
    uint8_t u8SSPOffset;                    /*!< Specifies Secondary Sample Point offset.
                                                 The transmitter delay plus u8SSPOffset defines the time of the secondary sample point for TDC.
                                                 u8SSPOffset is given as a number of TQ. Range is [0, 127] */
} stc_canfd_config_t;

/**
 * @brief TTCAN configuration structure.
 */
typedef struct {
    uint32_t u32RefMsgID;                   /*!< Reference message identifier. */
    uint32_t u32RefMsgIDE;                  /*!< Reference message identifier extension bit.
                                                 '1' to set the ID which is specified by parameter 'u32RefMsgID' as an extended ID while
                                                 '0' to set it as a standard ID. */
    uint8_t u8NTUPrescaler;                 /*!< Prescaler of NTU(network time unit). The source is the bit time which is defined by SBT.
                                                 This parameter can be a value of @ref TTCAN_NTU_Prescaler */
    uint8_t u8TxBufMode;                    /*!< TTCAN Transmit Buffer Mode.
                                                 This parameter can be a value of @ref TTCAN_Tx_Buf_Mode */
    uint16_t u16TriggerType;                /*!< Trigger type of TTCAN.
                                                 This parameter can be a value of @ref TTCAN_Trigger_Type */
    uint16_t u16TxEnableWindow;             /*!< Tx_Enable window. Time period within which the transmission of a message may be started. Range is [1, 16] */
    uint16_t u16TxTriggerTime;              /*!< Specifies for the referred message the time window of the matrix cycle at which it is to be transmitted. Range is [0, 65535] */
    uint16_t u16WatchTriggerTime;           /*!< Time mark used to check whether the time since the last valid reference message has been too long. Range is [0, 65535] */
} stc_can_ttc_config_t;

/**
 * @brief CAN initialization structure.
 */
typedef struct {
    stc_can_bit_time_config_t stcBitCfg;    /*!< Bit time configuration of classical CAN bit. @ref stc_can_bit_time_config_t */
    stc_can_filter_config_t *pstcFilter;    /*!< Pointer to a @ref stc_can_filter_config_t structure that
                                                 contains the configuration informations for the acceptance filters. */
    uint16_t u16FilterSelect;               /*!< Selects acceptance filters.
                                                 This parameter can be values of @ref CAN_Acceptance_Filter */
    uint8_t u8WorkMode;                     /*!< Specifies the work mode of CAN.
                                                 This parameter can be a value of @ref CAN_Work_Mode */
    uint8_t u8PTBSingleShotTx;              /*!< Enable or disable single shot transmission of PTB.
                                                 This parameter can be a value of @ref PTB_SingleShot_Tx_En */
    uint8_t u8STBSingleShotTx;              /*!< Enable or disable single shot transmission of STB.
                                                 This parameter can be a value of @ref STB_SingleShot_Tx_En */
    uint8_t u8STBPrioMode;                  /*!< Enable or disable the priority decision mode of STB.
                                                 This parameter can be a value of @ref CAN_STB_Prio_Mode_En
                                                 NOTE: A frame in the PTB has always the highest priority regardless of the ID. */
    uint8_t u8RxWarnLimit;                  /*!< Specifies receive buffer almost full warning limit. Rang is [1, 8].
                                                 Each CAN unit has 8 receive buffers. When the number of received frames reaches
                                                 the value specified by u8RxWarnLimit, register bit RTIF.RAFIF is set and the interrupt occurred
                                                 if it was enabled. */
    uint8_t u8ErrorWarnLimit;               /*!< Specifies programmable error warning limit. Range is [0, 15].
                                                 Error warning limit = (u8ErrorWarnLimit + 1) * 8. */
    uint8_t u8RxAllFrame;                   /*!< Enable or disable receive all frames(includes frames with error).
                                                 This parameter can be a value of @ref CAN_Rx_All_En */
    uint8_t u8RxOvfMode;                    /*!< Receive buffer overflow mode. In case of a full receive buffer when a new frame is received.
                                                 This parameter can be a value of @ref CAN_Rx_Ovf_Mode */
    uint8_t u8SelfAck;                      /*!< Enable or disable self-acknowledge.
                                                 This parameter can be a value of @ref CAN_Self_ACK_En */
    /* CAN-FD configuration */
    stc_canfd_config_t *pstcCanFd;          /*!< Pointer to a CAN-FD configuration structure. @ref stc_canfd_config_t
                                                 Set it to NULL if not needed CAN-FD. */

    stc_can_ttc_config_t *pstcCanTtc;       /*!< Pointer to a TTCAN configuration structure. @ref stc_can_ttc_config_t
                                                 Set it to NULL if not needed TTCAN. */
} stc_can_init_t;

/**
 * @brief CAN error information structure.
 */
typedef struct {
    uint8_t u8ArbitrLostPos;                /*!< Bit position in the frame where the arbitration has been lost.  */
    uint8_t u8ErrorType;                    /*!< CAN error type. This parameter can be a value of @ref CAN_Err_Type */
    uint8_t u8RxErrorCount;                 /*!< Receive error count. */
    uint8_t u8TxErrorCount;                 /*!< Transmit error count. */
} stc_can_error_info_t;

/**
 * @brief CAN TX frame data structure.
 */
typedef struct {
    uint32_t u32ID;                         /*!< 11 bits standard ID or 29 bits extended ID, depending on IDE. */
    union {
        uint32_t u32Ctrl;
        struct {
            uint32_t DLC: 4;                /*!< Data length code. Length of the data segment of data frame.
                                                 It should be zero while the frame is remote frame.
                                                 This parameter can be a value of @ref CAN_Data_Length_Code */
            uint32_t BRS: 1;                /*!< Bit rate switch. */
            uint32_t FDF: 1;                /*!< CAN FD frame. */
            uint32_t RTR: 1;                /*!< Remote transmission request bit.
                                                 It is used to distinguish between data frames and remote frames. */
            uint32_t IDE: 1;                /*!< Identifier extension flag.
                                                 It is used to distinguish between standard format and extended format.
                                                 This parameter can be a 1 or 0. */
            uint32_t RSVD: 24;              /*!< Reserved bits. */
        };
    };
    uint8_t au8Data[64U];                   /*!< TX data payload. */
} stc_can_tx_frame_t;

/**
 * @brief CAN RX frame data structure.
 */
typedef struct {
    uint32_t u32ID;                         /*!< 11 bits standard ID or 29 bits extended ID, depending on IDE. */
    union {
        uint32_t u32Ctrl;
        struct {
            uint32_t DLC: 4;                /*!< Data length code. Length of the data segment of data frame.
                                                 It should be zero while the frame is remote frame.
                                                 This parameter can be a value of @ref CAN_Data_Length_Code */
            uint32_t BRS: 1;                /*!< Bit rate switch. */
            uint32_t FDF: 1;                /*!< CAN FD frame. */
            uint32_t RTR: 1;                /*!< Remote transmission request bit.
                                                 It is used to distinguish between data frames and remote frames. */
            uint32_t IDE: 1;                /*!< Identifier extension flag.
                                                 It is used to distinguish between standard format and extended format.
                                                 This parameter can be 1 or 0. */
            uint32_t RSVD: 4;               /*!< Reserved bits. */
            uint32_t TX: 1;                 /*!< This bit is set to 1 when receiving self-transmitted data in loopback mode. */
            uint32_t ERRT: 3;               /*!< Error type. */
            uint32_t CYCLE_TIME: 16;        /*!< Cycle time of time-triggered communication(TTC). */
        };
    };
    uint8_t au8Data[64U];                   /*!< RX data payload. */
} stc_can_rx_frame_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CAN_Global_Macros CAN Global Macros
 * @{
 */

/**
 * @defgroup CAN_Work_Mode CAN Work Mode
 * @{
 */
#define CAN_WORK_MD_NORMAL              (0U)                    /*!< Normal work mode. */
#define CAN_WORK_MD_SILENT              (1U)                    /*!< Silent work mode. Prohibit data transmission. */
#define CAN_WORK_MD_ILB                 (2U)                    /*!< Internal loop back mode, just for self-test while developing. */
#define CAN_WORK_MD_ELB                 (3U)                    /*!< External loop back mode, just for self-test while developing. */
#define CAN_WORK_MD_ELB_SILENT          (4U)                    /*!< External loop back silent mode, just for self-test while developing.
                                                                     It is forbidden to respond to received frames and error frames,
                                                                     but data can be transmitted. */
/**
 * @}
 */

/**
 * @defgroup CAN_Tx_Buf_Type CAN Transmit Buffer Type
 * @{
 */
#define CAN_TX_BUF_PTB                  (0U)                    /*!< Primary transmit buffer. */
#define CAN_TX_BUF_STB                  (1U)                    /*!< Secondary transmit buffer. */
/**
 * @}
 */

/**
 * @defgroup CAN_Data_Length_Code CAN Data Length Code
 * @{
 */
#define CAN_DLC0                        (0x0U)                  /*!< CAN2.0 and CAN FD: the size of data field is 0 bytes. */
#define CAN_DLC1                        (0x1U)                  /*!< CAN2.0 and CAN FD: the size of data field is 1 bytes. */
#define CAN_DLC2                        (0x2U)                  /*!< CAN2.0 and CAN FD: the size of data field is 2 bytes. */
#define CAN_DLC3                        (0x3U)                  /*!< CAN2.0 and CAN FD: the size of data field is 3 bytes. */
#define CAN_DLC4                        (0x4U)                  /*!< CAN2.0 and CAN FD: the size of data field is 4 bytes. */
#define CAN_DLC5                        (0x5U)                  /*!< CAN2.0 and CAN FD: the size of data field is 5 bytes. */
#define CAN_DLC6                        (0x6U)                  /*!< CAN2.0 and CAN FD: the size of data field is 6 bytes. */
#define CAN_DLC7                        (0x7U)                  /*!< CAN2.0 and CAN FD: the size of data field is 7 bytes. */
#define CAN_DLC8                        (0x8U)                  /*!< CAN2.0 and CAN FD: the size of data field is 8 bytes. */
/* More DLC for CAN-FD. */
#define CAN_DLC12                       (0x9U)                  /*!< CAN FD: the size of data field is 12 bytes. */
#define CAN_DLC16                       (0xAU)                  /*!< CAN FD: the size of data field is 16 bytes. */
#define CAN_DLC20                       (0xBU)                  /*!< CAN FD: the size of data field is 20 bytes. */
#define CAN_DLC24                       (0xCU)                  /*!< CAN FD: the size of data field is 24 bytes. */
#define CAN_DLC32                       (0xDU)                  /*!< CAN FD: the size of data field is 32 bytes. */
#define CAN_DLC48                       (0xEU)                  /*!< CAN FD: the size of data field is 48 bytes. */
#define CAN_DLC64                       (0xFU)                  /*!< CAN FD: the size of data field is 64 bytes. */
/**
 * @}
 */

/**
 * @defgroup PTB_SingleShot_Tx_En PTB Single Shot Transmission Function Control
 * @{
 */
#define CAN_PTB_SINGLESHOT_TX_DISABLE   (0x0U)                  /*!< Primary transmit buffer auto retransmit. */
#define CAN_PTB_SINGLESHOT_TX_ENABLE    (CAN_CFG_STAT_TPSS)     /*!< Primary transmit buffer single short transmit. */
/**
 * @}
 */

/**
 * @defgroup STB_SingleShot_Tx_En STB Single Shot Transmission Function Control
 * @{
 */
#define CAN_STB_SINGLESHOT_TX_DISABLE   (0x0U)                  /*!< Secondary transmit buffer auto retransmit. */
#define CAN_STB_SINGLESHOT_TX_ENABLE    (CAN_CFG_STAT_TSSS)     /*!< Secondary transmit buffer single short transmit. */
/**
 * @}
 */

/**
 * @defgroup CAN_Tx_Request CAN Transmission Request
 * @{
 */
#define CAN_TX_REQ_STB_ONE              (CAN_TCMD_TSONE)        /*!< Transmit one STB frame. */
#define CAN_TX_REQ_STB_ALL              (CAN_TCMD_TSALL)        /*!< Transmit all STB frames. */
#define CAN_TX_REQ_PTB                  (CAN_TCMD_TPE)          /*!< Transmit PTB frame. */
/**
 * @}
 */

/**
 * @defgroup CAN_STB_Prio_Mode_En CAN STB Priority Mode Function Control
 * @note A frame in the PTB has always the highest priority regardless of the ID.
 * @{
 */
#define CAN_STB_PRIO_MD_DISABLE         (0x0U)                  /*!< The frame first in will first be transmitted. */
#define CAN_STB_PRIO_MD_ENABLE          (CAN_TCTRL_TSMODE)      /*!< The frame with lower ID will first be transmitted. */
/**
 * @}
 */

/**
 * @defgroup CAN_Tx_Buf_Status CAN Transmit Buffer Status
 * @{
 */
#define CAN_TX_BUF_EMPTY                (0x0U)                  /*!< TTCAN is disabled(TTEN == 0): STB is empty.
                                                                     TTCAN is disabled(TTEN == 1) and transmit buffer is specified by TBPTR and TTPTR(TTTBM == 1):
                                                                     PTB and STB are both empty. */
#define CAN_TX_BUF_NOT_MORE_THAN_HALF   (0x1U)                  /*!< TTEN == 0: STB is less than or equal to half full;
                                                                     TTEN == 1 && TTTBM == 1: PTB and STB are neither empty. */
#define CAN_TX_BUF_MORE_THAN_HALF       (0x2U)                  /*!< TTEN == 0: STB is more than half full;
                                                                     TTEN == 1 && TTTBM == 1: reserved value. */
#define CAN_TX_BUF_FULL                 (0x3U)                  /*!< TTEN == 0: STB is full;
                                                                     TTEN == 1 && TTTBM == 1: PTB and STB are both full. */
/**
 * @}
 */

/**
 * @defgroup CAN_Rx_Buf_Status CAN Receive Buffer Status
 * @{
 */
#define CAN_RX_BUF_EMPTY                (0x0U)                  /*!< Receive buffer is empty. */
#define CAN_RX_BUF_NOT_WARN             (0x1U)                  /*!< Receive buffer is not empty, but is less than almost full warning limit. */
#define CAN_RX_BUF_WARN                 (0x2U)                  /*!< Receive buffer is not full and not overflow, but is more than or equal to almost full warning limit. */
#define CAN_RX_BUF_FULL                 (0x3U)                  /*!< Receive buffer is full. */
/**
 * @}
 */

/**
 * @defgroup CAN_Rx_All_En CAN Receive All Frames
 * @{
 */
#define CAN_RX_ALL_FRAME_DISABLE        (0x0U)                  /*!< Only receives correct frames. */
#define CAN_RX_ALL_FRAME_ENABLE         (CAN_RCTRL_RBALL)       /*!< Receives all frames, including frames with error. */
/**
 * @}
 */

/**
 * @defgroup CAN_Rx_Ovf_Mode CAN Receive Buffer Overflow Mode
 * @{
 */
#define CAN_RX_OVF_SAVE_NEW             (0x0U)                  /*!< Saves the newly received data and the oldest frame will be overwritten. */
#define CAN_RX_OVF_DISCARD_NEW          (CAN_RCTRL_ROM)         /*!< Discard the newly received data. */
/**
 * @}
 */

/**
 * @defgroup CAN_Self_ACK_En CAN Self-ACK Function Control
 * @{
 */
#define CAN_SELF_ACK_DISABLE            (0x0U)                  /*!< Disable self-acknowledge. */
#define CAN_SELF_ACK_ENABLE             (CAN_RCTRL_SACK)        /*!< Enable self-acknowledge. */
/**
 * @}
 */

/**
 * @defgroup CAN_Interrupt_Type CAN Interrupt Type
 * @{
 */
#define CAN_INT_ERR_INT                 (1UL << 1U)             /*!< Register bit RTIE.EIE. The interrupt RTIF.EIF will be set if enabled by RTIE.EIE under the following conditions:
                                                                     The border of the error warning limit has been crossed in either direction by RECNT or TECNT or
                                                                     the BUSOFF bit has been changed in either direction. */
#define CAN_INT_STB_TX                  (1UL << 2U)             /*!< Register bit RTIE.TSIE. STB was transmitted. */
#define CAN_INT_PTB_TX                  (1UL << 3U)             /*!< Register bit RTIE.TPIE. PTB was transmitted. */
#define CAN_INT_RX_BUF_WARN             (1UL << 4U)             /*!< Register bit RTIE.RAFIE. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value. */
#define CAN_INT_RX_BUF_FULL             (1UL << 5U)             /*!< Register bit RTIE.RFIE. The FIFO of receive buffer is full. */
#define CAN_INT_RX_OVERRUN              (1UL << 6U)             /*!< Register bit RTIE.ROIE. Receive buffers are full and there is a further message to be stored. */
#define CAN_INT_RX                      (1UL << 7U)             /*!< Register bit RTIE.RIE. Received a valid data frame or remote frame. */
#define CAN_INT_BUS_ERR                 (1UL << 9U)             /*!< Register bit ERRINT.BEIE. Each of the error defined by EALCAP.KOER can cause bus-error inetrrupt. */
#define CAN_INT_ARBITR_LOST             (1UL << 11U)            /*!< Register bit ERRINT.ALIE. Arbitration lost. */
#define CAN_INT_ERR_PASSIVE             (1UL << 13U)            /*!< Register bit ERRINT.EPIE. A change from error-passive to error-active or error-active to error-passive has occurred. */

#define CAN_INT_ALL                     (CAN_INT_ERR_INT     | \
                                         CAN_INT_STB_TX      | \
                                         CAN_INT_PTB_TX      | \
                                         CAN_INT_RX_BUF_WARN | \
                                         CAN_INT_RX_BUF_FULL | \
                                         CAN_INT_RX_OVERRUN  | \
                                         CAN_INT_RX          | \
                                         CAN_INT_BUS_ERR     | \
                                         CAN_INT_ARBITR_LOST | \
                                         CAN_INT_ERR_PASSIVE)
/**
 * @}
 */

/**
 * @defgroup CAN_Status_Flag CAN Status Flag
 * @{
 */
#define CAN_FLAG_BUS_OFF                (1UL << 0U)             /*!< Register bit CFG_STAT.BUSOFF. CAN bus off. */
#define CAN_FLAG_TX_GOING               (1UL << 1U)             /*!< Register bit CFG_STAT.TACTIVE. CAN bus is transmitting. */
#define CAN_FLAG_RX_GOING               (1UL << 2U)             /*!< Register bit CFG_STAT.RACTIVE. CAN bus is receiving. */
#define CAN_FLAG_RX_BUF_OVF             (1UL << 5U)             /*!< Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one frame will be lost. */
#define CAN_FLAG_TX_BUF_FULL            (1UL << 8U)             /*!< Register bit RTIE.TSFF. Transmit buffers are all full.
                                                                     TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled.
                                                                     TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.*/
#define CAN_FLAG_TX_ABORTED             (1UL << 16U)            /*!< Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled. */
#define CAN_FLAG_ERR_INT                (1UL << 17U)            /*!< Register bit RTIF.EIF. The interrupt RTIF.EIF will be set if enabled by RTIE.EIE under the following conditions:
                                                                     The border of the error warning limit has been crossed in either direction by RECNT or TECNT or
                                                                     the BUSOFF bit has been changed in either direction. */
#define CAN_FLAG_STB_TX                 (1UL << 18U)            /*!< Register bit RTIF.TSIF. STB was transmitted. */
#define CAN_FLAG_PTB_TX                 (1UL << 19U)            /*!< Register bit RTIF.TPIF. PTB was transmitted. */
#define CAN_FLAG_RX_BUF_WARN            (1UL << 20U)            /*!< Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value. */
#define CAN_FLAG_RX_BUF_FULL            (1UL << 21U)            /*!< Register bit RTIF.RFIF. The FIFO of receive buffer is full. */
#define CAN_FLAG_RX_OVERRUN             (1UL << 22U)            /*!< Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored. */
#define CAN_FLAG_RX                     (1UL << 23U)            /*!< Register bit RTIF.RIF. Received a valid data frame or remote frame. */
#define CAN_FLAG_BUS_ERR                (1UL << 24U)            /*!< Register bit ERRINT.BEIF. Each of the error defined by EALCAP.KOER can make this flag set. */
#define CAN_FLAG_ARBITR_LOST            (1UL << 26U)            /*!< Register bit ERRINT.ALIF. Arbitration lost. */
#define CAN_FLAG_ERR_PASSIVE            (1UL << 28U)            /*!< Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred. */
#define CAN_FLAG_ERR_PASSIVE_NODE       (1UL << 30U)            /*!< Register bit ERRINT.EPASS. The node is an error-passive node. */
#define CAN_FLAG_TEC_REC_WARN           (1UL << 31U)            /*!< Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value. */

#define CAN_FLAG_ALL                    (CAN_FLAG_BUS_OFF          | \
                                         CAN_FLAG_TX_GOING         | \
                                         CAN_FLAG_RX_GOING         | \
                                         CAN_FLAG_RX_BUF_OVF       | \
                                         CAN_FLAG_TX_BUF_FULL      | \
                                         CAN_FLAG_TX_ABORTED       | \
                                         CAN_FLAG_ERR_INT          | \
                                         CAN_FLAG_STB_TX           | \
                                         CAN_FLAG_PTB_TX           | \
                                         CAN_FLAG_RX_BUF_WARN      | \
                                         CAN_FLAG_RX_BUF_FULL      | \
                                         CAN_FLAG_RX_OVERRUN       | \
                                         CAN_FLAG_RX               | \
                                         CAN_FLAG_BUS_ERR          | \
                                         CAN_FLAG_ARBITR_LOST      | \
                                         CAN_FLAG_ERR_PASSIVE      | \
                                         CAN_FLAG_ERR_PASSIVE_NODE | \
                                         CAN_FLAG_TEC_REC_WARN)

#define CAN_FLAG_CLR_ALL                (CAN_FLAG_RX_BUF_OVF       | \
                                         CAN_FLAG_TX_ABORTED       | \
                                         CAN_FLAG_ERR_INT          | \
                                         CAN_FLAG_STB_TX           | \
                                         CAN_FLAG_PTB_TX           | \
                                         CAN_FLAG_RX_BUF_WARN      | \
                                         CAN_FLAG_RX_BUF_FULL      | \
                                         CAN_FLAG_RX_OVERRUN       | \
                                         CAN_FLAG_RX               | \
                                         CAN_FLAG_BUS_ERR          | \
                                         CAN_FLAG_ARBITR_LOST      | \
                                         CAN_FLAG_ERR_PASSIVE)
/**
 * @}
 */

/**
 * @defgroup CAN_ID_Type CAN Identifier Type
 * @{
 */
#define CAN_ID_STD_EXT                  (0x0U)                  /*!< Acceptance filter accept frames with both standard ID and extended ID. */
#define CAN_ID_STD                      (CAN_ACF_AIDEE)         /*!< Acceptance filter accept frames with only standard ID. */
#define CAN_ID_EXT                      (CAN_ACF_AIDEE | \
                                         CAN_ACF_AIDE)          /*!< Acceptance filter accept frames with only extended ID. */
/**
 * @}
 */

/**
 * @defgroup CAN_Err_Type CAN Error Type
 * @{
 */
#define CAN_ERR_NONE                    (0U)                    /*!< No error. */
#define CAN_ERR_BIT                     (0x1U)                  /*!< Error is bit error. */
#define CAN_ERR_FORM                    (0x2U)                  /*!< Error is form error. */
#define CAN_ERR_STUFF                   (0x3U)                  /*!< Error is stuff error. */
#define CAN_ERR_ACK                     (0x4U)                  /*!< Error is ACK error. */
#define CAN_ERR_CRC                     (0x5U)                  /*!< Error is CRC error. */
#define CAN_ERR_OTHER                   (0x6U)                  /*!< Error is other error.
                                                                     Dominant bits after own error flag, received active Error Flag too long,
                                                                     dominant bit during Passive-Error-Flag after ACK error. */
/**
 * @}
 */

/**
 * @defgroup CAN_Acceptance_Filter CAN Acceptance Filter
 * @{
 */
#define CAN_FILTER1                     (CAN_ACFEN_AE_1)        /*!< Acceptance filter 1 select bit. */
#define CAN_FILTER2                     (CAN_ACFEN_AE_2)        /*!< Acceptance filter 2 select bit. */
#define CAN_FILTER3                     (CAN_ACFEN_AE_3)        /*!< Acceptance filter 3 select bit. */
#define CAN_FILTER4                     (CAN_ACFEN_AE_4)        /*!< Acceptance filter 4 select bit. */
#define CAN_FILTER5                     (CAN_ACFEN_AE_5)        /*!< Acceptance filter 5 select bit. */
#define CAN_FILTER6                     (CAN_ACFEN_AE_6)        /*!< Acceptance filter 6 select bit. */
#define CAN_FILTER7                     (CAN_ACFEN_AE_7)        /*!< Acceptance filter 7 select bit. */
#define CAN_FILTER8                     (CAN_ACFEN_AE_8)        /*!< Acceptance filter 8 select bit. */
#define CAN_FILTER9                     (CAN_ACFEN_AE_9)        /*!< Acceptance filter 9 select bit. */
#define CAN_FILTER10                    (CAN_ACFEN_AE_10)       /*!< Acceptance filter 10 select bit. */
#define CAN_FILTER11                    (CAN_ACFEN_AE_11)       /*!< Acceptance filter 11 select bit. */
#define CAN_FILTER12                    (CAN_ACFEN_AE_12)       /*!< Acceptance filter 12 select bit. */
#define CAN_FILTER13                    (CAN_ACFEN_AE_13)       /*!< Acceptance filter 13 select bit. */
#define CAN_FILTER14                    (CAN_ACFEN_AE_14)       /*!< Acceptance filter 14 select bit. */
#define CAN_FILTER15                    (CAN_ACFEN_AE_15)       /*!< Acceptance filter 15 select bit. */
#define CAN_FILTER16                    (CAN_ACFEN_AE_16)       /*!< Acceptance filter 16 select bit. */
#define CAN_FILTER_ALL                  (0xFFFFU)
/**
 * @}
 */

/**
 * @defgroup CAN_FD_Mode CAN-FD Mode
 * @{
 */
#define CAN_FD_MD_BOSCH                 (0x0U)                  /*!< Bosch CAN FD (non-ISO) mode. */
#define CAN_FD_MD_ISO                   (CAN_TCTRL_FD_ISO)      /*!< ISO CAN FD mode (ISO 11898-1:2015). */
/**
 * @}
 */

/**
 * @defgroup CAN_FD_TDC_En CAN-FD TDC Function Control
 * @{
 */
#define CAN_FD_TDC_DISABLE              (0x0U)                  /*!< Disable transmitter delay compensation. */
#define CAN_FD_TDC_ENABLE               (CAN_TDC_TDCEN)         /*!< Enable transmitter delay compensation. */
/**
 * @}
 */

/**
 * @defgroup TTCAN_Tx_Buf_Mode TTCAN Transmit Buffer Mode
 * @{
 */
#define CAN_TTC_TX_BUF_MD_CAN           (0x0U)                  /*!< Normal CAN mode. TTCAN transmit buffer depends on the priority mode of STB which is defined by @ref CAN_STB_Prio_Mode_En */
#define CAN_TTC_TX_BUF_MD_TTCAN         (CAN_TCTRL_TTTBM)       /*!< Full TTCAN mode. TTCAN transmit buffer is pointed by TBSLOT.TBPTR(for data filling) and
                                                                     TRG_CFG.TTPTR(for data transmission). */
/**
 * @}
 */

/**
 * @defgroup TTCAN_Tx_Buf_Sel TTCAN Transmit Buffer Selection
 * @{
 */
#define CAN_TTC_TX_BUF_PTB              (0x0U)                  /*!< Point to PTB. */
#define CAN_TTC_TX_BUF_STB1             (0x1U)                  /*!< Point to STB slot 1. */
#define CAN_TTC_TX_BUF_STB2             (0x2U)                  /*!< Point to STB slot 2. */
#define CAN_TTC_TX_BUF_STB3             (0x3U)                  /*!< Point to STB slot 3. */
/**
 * @}
 */

/**
 * @defgroup TTCAN_Tx_Buf_Mark_State TTCAN Transmit Buffer Mark State
 * @{
 */
#define CAN_TTC_TX_BUF_MARK_EMPTY       (CAN_TBSLOT_TBE)        /*!< Marks the transmit buffer selected by TBSLOT.TBPTR as "empty".
                                                                     TBE is automatically reset to 0 as soon as the slot is marked as empty and TSFF=0.
                                                                     If a transmission from this slot is active, then TBE stays set as long as either the
                                                                     transmission completes or after a transmission error or arbitration loss the transmission
                                                                     is not active any more. If both TBF and TBE are set, then TBE wins. */
#define CAN_TTC_TX_BUF_MARK_FILLED      (CAN_TBSLOT_TBF)        /*!< Marks the transmit buffer selected by TBSLOT.TBPTR as "filled".
                                                                     TBF is automatically reset to 0 as soon as the slot is marked as filled and RTIE.TSFF=1.
                                                                     If both TBF and TBE are set, then TBE wins. */
/**
 * @}
 */

/**
 * @defgroup TTCAN_Interrupt_Type TTCAN Interrupt Type
 * @{
 */
#define CAN_TTC_INT_TIME_TRIG           (CAN_TTCFG_TTIE)        /*!< Time trigger interrupt. */
#define CAN_TTC_INT_WATCH_TRIG          (CAN_TTCFG_WTIE)        /*!< Watch trigger interrupt. */
#define CAN_TTC_INT_ALL                 (CAN_TTC_INT_TIME_TRIG | \
                                         CAN_TTC_INT_WATCH_TRIG)
/**
 * @}
 */

/**
 * @defgroup TTCAN_Status_Flag TTCAN Status Flag
 * @{
 */
#define CAN_TTC_FLAG_TIME_TRIG          (CAN_TTCFG_TTIF)        /*!< Time trigger interrupt flag. */
#define CAN_TTC_FLAG_TRIG_ERR           (CAN_TTCFG_TEIF)        /*!< Trigger error interrupt flag. */
#define CAN_TTC_FLAG_WATCH_TRIG         (CAN_TTCFG_WTIF)        /*!< Watch trigger interrupt flag. */

#define CAN_TTC_FLAG_ALL                (CAN_TTC_FLAG_TIME_TRIG | \
                                         CAN_TTC_FLAG_TRIG_ERR  | \
                                         CAN_TTC_FLAG_WATCH_TRIG)
/**
 * @}
 */

/**
 * @defgroup TTCAN_NTU_Prescaler TTCAN Network Time Unit Prescaler
 * @{
 */
#define CAN_TTC_NTU_PRESCALER1          (0x0U)                  /*!< NTU is SBT bit time * 1. */
#define CAN_TTC_NTU_PRESCALER2          (CAN_TTCFG_T_PRESC_0)   /*!< NTU is SBT bit time * 2. */
#define CAN_TTC_NTU_PRESCALER4          (CAN_TTCFG_T_PRESC_1)   /*!< NTU is SBT bit time * 4. */
#define CAN_TTC_NTU_PRESCALER8          (CAN_TTCFG_T_PRESC)     /*!< NTU is SBT bit time * 8. */
/**
 * @}
 */

/**
 * @defgroup TTCAN_Trigger_Type TTCAN Trigger Type
 * @note Except for the immediate trigger, all triggers set TTIF if TTIE is enabled.
 * @{
 */
#define CAN_TTC_TRIG_IMMED_TRIG         (0x0U)                  /*!< Immediate trigger for immediate transmission. */
#define CAN_TTC_TRIG_TIME_TRIG          (CAN_TRG_CFG_TTYPE_0)   /*!< Time trigger for receive triggers. */
#define CAN_TTC_TRIG_SINGLESHOT_TX_TRIG (CAN_TRG_CFG_TTYPE_1)   /*!< Single shot transmit trigger for exclusive time windows. */
#define CAN_TTC_TRIG_TX_START_TRIG      (CAN_TRG_CFG_TTYPE_1 | \
                                         CAN_TRG_CFG_TTYPE_0)   /*!< Transmit start trigger for merged arbitrating time windows. */
#define CAN_TTC_TRIG_TX_STOP_TRIG       (CAN_TRG_CFG_TTYPE_2)   /*!< Transmit stop trigger for merged arbitrating time windows. */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup CAN_Global_Functions
 * @{
 */
/* Classical CAN */
int32_t CAN_Init(CM_CAN_TypeDef *CANx, const stc_can_init_t *pstcCanInit);
int32_t CAN_StructInit(stc_can_init_t *pstcCanInit);
void CAN_DeInit(CM_CAN_TypeDef *CANx);
void CAN_IntCmd(CM_CAN_TypeDef *CANx, uint32_t u32IntType, en_functional_state_t enNewState);
int32_t CAN_FillTxFrame(CM_CAN_TypeDef *CANx, uint8_t u8TxBufType, const stc_can_tx_frame_t *pstcTx);
void CAN_StartTx(CM_CAN_TypeDef *CANx, uint8_t u8TxRequest);
void CAN_AbortTx(CM_CAN_TypeDef *CANx, uint8_t u8TxBufType);
int32_t CAN_GetRxFrame(CM_CAN_TypeDef *CANx, stc_can_rx_frame_t *pstcRx);

en_flag_status_t CAN_GetStatus(const CM_CAN_TypeDef *CANx, uint32_t u32Flag);
void CAN_ClearStatus(CM_CAN_TypeDef *CANx, uint32_t u32Flag);
uint32_t CAN_GetStatusValue(const CM_CAN_TypeDef *CANx);
int32_t CAN_GetErrorInfo(const CM_CAN_TypeDef *CANx, stc_can_error_info_t *pstcErr);
uint8_t CAN_GetTxBufStatus(const CM_CAN_TypeDef *CANx);
uint8_t CAN_GetRxBufStatus(const CM_CAN_TypeDef *CANx);
void CAN_FilterCmd(CM_CAN_TypeDef *CANx, uint16_t u16FilterSelect, en_functional_state_t enNewState);
void CAN_SetRxWarnLimit(CM_CAN_TypeDef *CANx, uint8_t u8RxWarnLimit);
void CAN_SetErrorWarnLimit(CM_CAN_TypeDef *CANx, uint8_t u8ErrorWarnLimit);

int32_t CAN_FD_StructInit(stc_canfd_config_t *pstcCanFd);

/* TTCAN */
int32_t CAN_TTC_StructInit(stc_can_ttc_config_t *pstcCanTtc);
int32_t CAN_TTC_Config(CM_CAN_TypeDef *CANx, const stc_can_ttc_config_t *pstcCanTtc);
void CAN_TTC_IntCmd(CM_CAN_TypeDef *CANx, uint8_t u8IntType, en_functional_state_t enNewState);
void CAN_TTC_Cmd(CM_CAN_TypeDef *CANx, en_functional_state_t enNewState);

en_flag_status_t CAN_TTC_GetStatus(const CM_CAN_TypeDef *CANx, uint8_t u8Flag);
void CAN_TTC_ClearStatus(CM_CAN_TypeDef *CANx, uint8_t u8Flag);
uint8_t CAN_TTC_GetStatusValue(const CM_CAN_TypeDef *CANx);

void CAN_TTC_SetTriggerType(CM_CAN_TypeDef *CANx, uint16_t u16TriggerType);
void CAN_TTC_SetTxEnableWindow(CM_CAN_TypeDef *CANx, uint16_t u16TxEnableWindow);
void CAN_TTC_SetTxTriggerTime(CM_CAN_TypeDef *CANx, uint16_t u16TxTriggerTime);
void CAN_TTC_SetWatchTriggerTime(CM_CAN_TypeDef *CANx, uint16_t u16WatchTriggerTime);

int32_t CAN_TTC_FillTxFrame(CM_CAN_TypeDef *CANx, uint8_t u8CANTTCTxBuf, const stc_can_tx_frame_t *pstcTx);

int32_t CAN_TTC_GetConfig(const CM_CAN_TypeDef *CANx, stc_can_ttc_config_t *pstcCanTtc);

/**
 * @}
 */

#endif /* LL_CAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_CAN_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
