/**
 *******************************************************************************
 * @file  hc32f4a0_can.h
 * @brief This file contains all the functions prototypes of the CAN driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
   2020-12-14       Wuze            Modified comment of structure stc_can_bt_cfg_t
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_CAN_H__
#define __HC32F4A0_CAN_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_CAN
 * @{
 */

#if (DDL_CAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CAN_Global_Types CAN Global Types
 * @{
 */

/**
 * @brief CAN bit timing configuration structure. See 11898-1 for details.
 * @note 1. Restrictions: u32SEG1 >= u32SEG2 + 1, u32SEG2 >= u32SJW.
 * @note 2. TQ = u32Prescaler / CANClock.
 * @note 3. Bit time = (u32SEG2 + u32SEG2) x TQ.
 * @note 4. Baudrate = CANClock/(u32Prescaler*(u32SEG1 + u32SEG2))
 */
typedef struct
{
    uint32_t u32SEG1;                       /*!< TQs of segment 1. Contains synchronization segment, \
                                                 propagation time segment and phase buffer segment 1. */
    uint32_t u32SEG2;                       /*!< TQs of segment 2. Phase buffer segment 2. */
    uint32_t u32SJW;                        /*!< TQs of synchronization jump width. */
    uint32_t u32Prescaler;                  /*!< Range [1, 256]. */
} stc_can_bt_cfg_t;

/**
 * @brief CAN acceptance filter structure.
 */
typedef struct
{
    uint32_t u32ID;                         /*!< 11 bits standard ID or 29 bits extended ID, depending on IDE. */
    uint32_t u32IDMsk;                      /*!< ID mask. The mask bits of ID will be ignored by the acceptance filter. */
    uint32_t u32MskType;                    /*!< Acceptance filter mask type. This parameter can be a value of @ref CAN_AF_Mask_Type */
} stc_can_af_cfg_t;

/**
 * @brief CAN FD configuration structure.
 */
typedef struct
{
    uint8_t u8CANFDMode;                    /*!< CAN-FD mode, Bosch CAN-FD or 11898-1:2015 CAN-FD.
                                                 This parameter can be a value of @ref CAN_FD_Mode */
    stc_can_bt_cfg_t stcFBT;                /*!< Bit timing configuration of fast bit timing. */
    uint8_t u8TDCCmd;                       /*!< Transmiter delay compensation function control.
                                                 This parameter can be a value of @ref CAN_FD_TDC_Command */
    uint8_t u8TDCSSP;                       /*!< Specify secondary sample point(SSP) of transmitter delay compensatin(TDC). Number of TQ. */
} stc_can_fd_cfg_t;

/**
 * @brief CAN time-triggered communication configuration structure.
 */
typedef struct
{
    uint8_t u8TransBufMode;                 /*!< TTCAN Transmit Buffer Mode.
                                                 This parameter can be a value of @ref CAN_TTC_Transmit_Buffer_Mode */
    uint8_t u8NTUPrescaler;                 /*!< Prescaler of NTU(network time unit). The source is the bit time which is defined by SBT.
                                                 This parameter can be a value of @ref CAN_TTC_NTU_Prescaler */
    uint32_t u32RefMsgIDE;                  /*!< Reference message identifier extension bit.
                                                 '1' to set the ID which is specified by parameter 'u32RefMsgID' as an extended ID while \
                                                 '0' to set it as a standard ID. */
    uint32_t u32RefMsgID;                   /*!< Reference message identifier. */
    uint16_t u16TrigType;                   /*!< Trigger type of TTC.
                                                 This parameter can be a value of @ref CAN_TTC_Trigger_Type */
    uint16_t u16TxEnWindow;                 /*!< Tx_Enable window. Time period within which the transmission of a message may be started. Range is [1, 16U] */
    uint16_t u16TxTrigTime;                 /*!< Specifies for the referred message the time window of the matrix cycle at which it is to be transmitted. */
    uint16_t u16WatchTrigTime;              /*!< Time mark used to check whether the time since the last valid reference message has been too long. */
} stc_can_ttc_cfg_t;

/**
 * @brief CAN initialization structure.
 */
typedef struct
{
    uint8_t u8WorkMode;                     /*!< Specify the work mode of CAN.
                                                 This parameter can be a value of @ref CAN_Work_Mode */
    stc_can_bt_cfg_t stcSBT;                /*!< Bit timing configuration of slow bit timing. */

    en_functional_state_t enCANFDCmd;       /*!< Enable or Disable CAN-FD. If Disable, the following configuration valuse will not \
                                                 be written to the registers. */

    stc_can_fd_cfg_t stcFDCfg;              /*!< CAN-FD configuration structure. */

    uint8_t u8TransMode;                    /*!< Transmission mode of PTB and STB.
                                                 This parameter can be a value of @ref CAN_Trans_Mode */
    uint8_t u8STBPrioMode;                  /*!< Priority mode of STB. First in first transmit. OR the priority is determined by ID. Smaller ID higher priority.
                                                 Whatever the priority mode of STB is, PTB always has the highest priority.
                                                 This parameter can be a value of @ref CAN_STB_Priority_Mode */
    uint8_t u8RBSWarnLimit;                 /*!< Specify receive buffer almost full warning limit. Rang is [1, 8]. \
                                                 Each CAN unit has 8 receive buffer slots. When the number of received frames reaches \
                                                 the set value of u8RBSWarnLimit, register bit RTIF.RAFIF is set and the interrupt occurred \
                                                 if it was enabled. */
    uint8_t u8ErrWarnLimit;                 /*!< Specify programmable error warning limit. Range is [0, 15]. \
                                                 Error warning limit = (u8ErrWarnLimit + 1) * 8. */
    stc_can_af_cfg_t *pstcAFCfg;            /*!< Points to a stc_can_af_cfg_t structure type pointer value that
                                                 contains the configuration informations for the acceptance filters. */
    uint16_t u16AFSel;                      /*!< Specify acceptance filter for receive buffer.
                                                 This parameter can be values of @ref CAN_AF */
    uint8_t u8RBStoreSel;                   /*!< Receive buffer stores all data frames, includes error data.
                                                 This parameter can be a value of @ref CAN_RB_Store_Selection */
    uint8_t u8RBOvfOp;                      /*!< Operation when receive buffer overflow.
                                                 This parameter can be a value of @ref CAN_RB_Overflow_Operation */
    uint8_t u8SelfACKCmd;                   /*!< Self ACK. Only for external loopback mode.
                                                 This parameter can be a value of @ref CAN_Self_ACK_Command */
} stc_can_init_t;

/**
 * @brief CAN transmit data structure.
 */
typedef struct
{
    uint32_t u32ID;                         /*!< 11 bits standard ID or 29 bits extended ID, depending on IDE. */
    union
    {
        uint32_t u32Ctrl;
        struct
        {
            uint32_t DLC: 4;                /*!< Data length code. Length of the data segment of data frame. \
                                                 It should be zero while the frame is remote frame. \
                                                 This parameter can be a value of @ref CAN_DLC */
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
    uint8_t *pu8Data;                      /*!< Pointer to data filed of data frame. */
} stc_can_tx_t;

/**
 * @brief CAN receive data structure.
 */
typedef struct
{
    uint32_t u32ID;                         /*!< 11 bits standard ID or 29 bits extended ID, depending on IDE. */
    union
    {
        uint32_t u32Ctrl;
        struct
        {
            uint32_t DLC: 4;                /*!< Data length code. Length of the data segment of data frame. \
                                                 It should be zero while the frame is remote frame. \
                                                 This parameter can be a value of @ref CAN_DLC */
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
    uint8_t *pu8Data;                       /*!< Pointer to data filed of data frame. */
} stc_can_rx_t;

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
#define CAN_MODE_NORMAL                 (0U)                    /*!< Normal work mode. */
#define CAN_MODE_SILENT                 (1U)                    /*!< Silent work mode. Prohibit data transmission. */
#define CAN_MODE_ILB                    (2U)                    /*!< Internal loopback mode, just for self-test while developing. */
#define CAN_MODE_ELB                    (3U)                    /*!< External loopback mode, just for self-test while developing. */
#define CAN_MODE_ELB_SILENT             (4U)                    /*!< External loppback silent mode, just for self-test while developing. \
                                                                     It is forbidden to respond to received frames and error frames, but data can be transmitted. */
/**
 * @}
 */

/**
 * @defgroup CAN_Transmit_Buffer_Type CAN Transmit Buffer Type
 * @{
 */
#define CAN_BUF_PTB                     (0U)                    /*!< Primary transmit buffer. */
#define CAN_BUF_STB                     (1U)                    /*!< Secondary transmit buffer. */
/**
 * @}
 */

/**
 * @defgroup CAN_DLC CAN Data_Length_Code
 * @{
 */
#define CAN_DLC_0                       (0x0U)                    /*!< CAN2.0 and CAN FD: payload is 0 in bytes. */
#define CAN_DLC_1                       (0x1U)                    /*!< CAN2.0 and CAN FD: payload is 1 in bytes. */
#define CAN_DLC_2                       (0x2U)                    /*!< CAN2.0 and CAN FD: payload is 2 in bytes. */
#define CAN_DLC_3                       (0x3U)                    /*!< CAN2.0 and CAN FD: payload is 3 in bytes. */
#define CAN_DLC_4                       (0x4U)                    /*!< CAN2.0 and CAN FD: payload is 4 in bytes. */
#define CAN_DLC_5                       (0x5U)                    /*!< CAN2.0 and CAN FD: payload is 5 in bytes. */
#define CAN_DLC_6                       (0x6U)                    /*!< CAN2.0 and CAN FD: payload is 6 in bytes. */
#define CAN_DLC_7                       (0x7U)                    /*!< CAN2.0 and CAN FD: payload is 7 in bytes. */
#define CAN_DLC_8                       (0x8U)                    /*!< CAN2.0 and CAN FD: payload is 8 in bytes. */
#define CAN_DLC_12                      (0x9U)                    /*!< CAN FD: payload is 12 in bytes. CAN2.0: payload is 8 in bytes. */
#define CAN_DLC_16                      (0xAU)                    /*!< CAN FD: payload is 16 in bytes. CAN2.0: payload is 8 in bytes. */
#define CAN_DLC_20                      (0xBU)                    /*!< CAN FD: payload is 20 in bytes. CAN2.0: payload is 8 in bytes. */
#define CAN_DLC_24                      (0xCU)                    /*!< CAN FD: payload is 24 in bytes. CAN2.0: payload is 8 in bytes. */
#define CAN_DLC_32                      (0xDU)                    /*!< CAN FD: payload is 32 in bytes. CAN2.0: payload is 8 in bytes. */
#define CAN_DLC_48                      (0xEU)                    /*!< CAN FD: payload is 48 in bytes. CAN2.0: payload is 8 in bytes. */
#define CAN_DLC_64                      (0xFU)                    /*!< CAN FD: payload is 64 in bytes. CAN2.0: payload is 8 in bytes. */
/**
 * @}
 */

/**
 * @defgroup CAN_Trans_Mode CAN Transmission Mode
 * @{
 */
#define CAN_TRANS_PTB_STB_AUTO_RETX     (0x0U)                  /*!< Both PTB and STB automatically retransmit. */
#define CAN_TRANS_PTB_SSHOT             (CAN_CFG_STAT_TPSS)     /*!< PTB single shot transmission mode. */
#define CAN_TRANS_STB_SSHOT             (CAN_CFG_STAT_TSSS)     /*!< STB single shot transmission mode. */
#define CAN_TRANS_PTB_STB_SSHOT         (CAN_CFG_STAT_TPSS | \
                                         CAN_CFG_STAT_TSSS)     /*!< STB single shot, PTB single shot. */
/**
 * @}
 */

/**
 * @defgroup CAN_STB_Trans_Control CAN STB Transmission Control
 * @{
 */
#define CAN_STB_TRANS_ALL               (0U)                    /*!< Transmit all of STB slots. */
#define CAN_STB_TRANS_ONE               (1U)                    /*!< Transmit one STB slot. */
/**
 * @}
 */

/**
 * @defgroup CAN_STB_Priority_Mode CAN STB Priority Mode
 * @{
 */
#define CAN_STB_PRIO_FIFO               (0x0U)                  /*!< Data first in and first be transmitted. */
#define CAN_STB_PRIO_ID                 (CAN_TCTRL_TSMODE)      /*!< Data with smallest ID first be transmitted. */
/**
 * @}
 */

/**
 * @defgroup CAN_TB_Status CAN Transmit Buffer Status
 * @{
 */
#define CAN_TB_STAT_EMPTY               (0x0U)                  /*!< TTCAN is disabled(TTEN == 0): STB is empty. \
                                                                     TTCAN is disabled(TTEN == 1) and transmit buffer is specified by TBPTR and TTPTR(TTTBM == 1): \
                                                                     PTB and STB are both empty. */
#define CAN_TB_STAT_LESS_HALF           (0x1U)                  /*!< TTEN == 0: STB is not less than half full; \
                                                                     TTEN == 1 && TTTBM == 1: PTB and STB are neither empty. */
#define CAN_TB_STAT_MORE_HALF           (0x2U)                  /*!< TTEN == 0: STB is more than half full; \
                                                                     TTEN == 1 && TTTBM == 1: reserved value. */
#define CAN_TB_STAT_FULL                (0x3U)                  /*!< TTEN == 0: STB is full; \
                                                                     TTEN == 1 && TTTBM == 1: PTB and STB are both full. */
/**
 * @}
 */

/**
 * @defgroup CAN_RB_Status CAN Receive Buffer Status
 * @{
 */
#define CAN_RB_STAT_EMPTY               (0x0U)                  /*!< Receive buffer(RB) is empty. */
#define CAN_RB_STAT_LESS_WARN_LIMIT     (0x1U)                  /*!< RB is not empty, but is less than almost full warning limit. */
#define CAN_RB_STAT_MORE_WARN_LIMIT     (0x2U)                  /*!< RB is not full, but is more than or equal to almost full warning limit. */
#define CAN_RB_STAT_FULL                (0x3U)                  /*!< RB is full. */
/**
 * @}
 */

/**
 * @defgroup CAN_FD_Mode CAN FD Mode
 * @{
 */
#define CAN_FD_MODE_BOSCH               (0x0U)
#define CAN_FD_MODE_ISO_11898           (CAN_TCTRL_FD_ISO)
/**
 * @}
 */

/**
 * @defgroup CAN_RB_Store_Selection CAN Receive Buffer Store Selection
 * @{
 */
#define CAN_RB_STORE_CORRECT_DATA       (0x0U)                  /*!< Receive buffer stores correct data frames only. */
#define CAN_RB_STORE_ALL_DATA           (CAN_RCTRL_RBALL)       /*!< Receive buffer stores all data frames, includes error data. */
/**
 * @}
 */

/**
 * @defgroup CAN_RB_Overflow_Operation CAN Receive Buffer Overflow Operation
 * @{
 */
#define CAN_RB_OVF_SAVE_NEW             (0x0U)                  /*!< Saves the newly received data and the first received data will be overwritten. */
#define CAN_RB_OVF_DISCARD_NEW          (CAN_RCTRL_ROM)         /*!< Discard the newly received data. */
/**
 * @}
 */

/**
 * @defgroup CAN_Self_ACK_Command CAN Self ACK Command
 * @{
 */
#define CAN_SELF_ACK_DISABLE            (0x0U)
#define CAN_SELF_ACK_ENABLE             (CAN_RCTRL_SACK)
/**
 * @}
 */

/**
 * @defgroup CAN_FD_TDC_Command CAN-FD Transmiter Delay Compensation Command
 * @{
 */
#define CAN_FD_TDC_DISABLE              (0x0U)
#define CAN_FD_TDC_ENABLE               (CAN_TDC_TDCEN)
/**
 * @}
 */

/**
 * @defgroup CAN_Interrupt_Type CAN Interrupt Type
 * @{
 */
#define CAN_INT_ERR_INT                 (1UL << 1U)             /*!< Register bit RTIE.EIE. Error interrupt. */
#define CAN_INT_STB_TRANS_OK            (1UL << 2U)             /*!< Register bit RTIE.TSIE. Secondary transmit buffer was transmitted successfully. */
#define CAN_INT_PTB_TRANS_OK            (1UL << 3U)             /*!< Register bit RTIE.TPIE. Primary transmit buffer was transmitted successfully. */
#define CAN_INT_RB_ALMOST_FULL          (1UL << 4U)             /*!< Register bit RTIE.RAFIE. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value. */
#define CAN_INT_RB_FIFO_FULL            (1UL << 5U)             /*!< Register bit RTIE.RFIE. The FIFO of receive buffer is full. */
#define CAN_INT_RX_OVERRUN              (1UL << 6U)             /*!< Register bit RTIE.ROIE. Receive buffers are full and there is a further message to be stored. */
#define CAN_INT_RX                      (1UL << 7U)             /*!< Register bit RTIE.RIE. Received a valid data frame or remote frame. */
#define CAN_INT_BUS_ERR                 (1UL << 9U)             /*!< Register bit ERRINT.BEIE. Arbitration lost caused bus error */
#define CAN_INT_ARB_LOST                (1UL << 11U)            /*!< Register bit ERRINT.ALIE. Arbitration lost. */
#define CAN_INT_ERR_PASSIVE             (1UL << 13U)            /*!< Register bit ERRINT.EPIE. A change from error-passive to error-active or error-active to error-passive has occurred. */

#define CAN_INT_ALL                     (CAN_INT_ERR_INT        | \
                                         CAN_INT_STB_TRANS_OK   | \
                                         CAN_INT_PTB_TRANS_OK   | \
                                         CAN_INT_RB_ALMOST_FULL | \
                                         CAN_INT_RB_FIFO_FULL   | \
                                         CAN_INT_RX_OVERRUN     | \
                                         CAN_INT_RX             | \
                                         CAN_INT_BUS_ERR        | \
                                         CAN_INT_ARB_LOST       | \
                                         CAN_INT_ERR_PASSIVE)
/**
 * @}
 */

/**
 * @defgroup CAN_Common_Status_Flag CAN Common Status Flag
 * @{
 */
#define CAN_FLAG_BUS_OFF                (1UL << 0U)             /*!< Register bit CFG_STAT.BUSOFF. CAN bus off. */
#define CAN_FLAG_BUS_TX                 (1UL << 1U)             /*!< Register bit CFG_STAT.TACTIVE. CAN bus is transmitting. */
#define CAN_FLAG_BUS_RX                 (1UL << 2U)             /*!< Register bit CFG_STAT.RACTIVE. CAN bus is receiving. */
#define CAN_FLAG_RB_OVF                 (1UL << 5U)             /*!< Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost. */
#define CAN_FLAG_TB_FULL                (1UL << 8U)             /*!< Register bit RTIE.TSFF. Transmit buffers are all full. \
                                                                     TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled. \
                                                                     TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.*/
#define CAN_FLAG_TRANS_ABORTED          (1UL << 16U)            /*!< Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled. */
#define CAN_FLAG_ERR_INT                (1UL << 17U)            /*!< Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter and the \
                                                                     set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than \
                                                                     the set value to greater than the set value, or from greater than the set value to less than the set value. */
#define CAN_FLAG_STB_TRANS_OK           (1UL << 18U)            /*!< Register bit RTIF.TSIF. STB was transmitted successfully. */
#define CAN_FLAG_PTB_TRANS_OK           (1UL << 19U)            /*!< Register bit RTIF.TPIF. PTB was transmitted successfully. */
#define CAN_FLAG_RB_ALMOST_FULL         (1UL << 20U)            /*!< Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value. */
#define CAN_FLAG_RB_FIFO_FULL           (1UL << 21U)            /*!< Register bit RTIF.RFIF. The FIFO of receive buffer is full. */
#define CAN_FLAG_RX_OVERRUN             (1UL << 22U)            /*!< Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored. */
#define CAN_FLAG_RX_OK                  (1UL << 23U)            /*!< Register bit RTIF.RIF. Received a valid data frame or remote frame. */
#define CAN_FLAG_BUS_ERR                (1UL << 24U)            /*!< Register bit ERRINT.BEIF. Arbitration lost caused bus error. */
#define CAN_FLAG_ARB_LOST               (1UL << 26U)            /*!< Register bit ERRINT.ALIF. Arbitration lost. */
#define CAN_FLAG_ERR_PASSIVE            (1UL << 28U)            /*!< Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred. */
#define CAN_FLAG_ERR_PASSIVE_NODE       (1UL << 30U)            /*!< Register bit ERRINT.EPASS. The node is an error-passive node. */
#define CAN_FLAG_REACH_WARN_LIMIT       (1UL << 31U)            /*!< Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value. */

#define CAN_FLAG_ALL                    (CAN_FLAG_BUS_OFF          | \
                                         CAN_FLAG_BUS_TX           | \
                                         CAN_FLAG_BUS_RX           | \
                                         CAN_FLAG_RB_OVF           | \
                                         CAN_FLAG_TB_FULL          | \
                                         CAN_FLAG_TRANS_ABORTED    | \
                                         CAN_FLAG_ERR_INT          | \
                                         CAN_FLAG_STB_TRANS_OK     | \
                                         CAN_FLAG_PTB_TRANS_OK     | \
                                         CAN_FLAG_RB_ALMOST_FULL   | \
                                         CAN_FLAG_RB_FIFO_FULL     | \
                                         CAN_FLAG_RX_OVERRUN       | \
                                         CAN_FLAG_RX_OK            | \
                                         CAN_FLAG_BUS_ERR          | \
                                         CAN_FLAG_ARB_LOST         | \
                                         CAN_FLAG_ERR_PASSIVE      | \
                                         CAN_FLAG_ERR_PASSIVE_NODE | \
                                         CAN_FLAG_REACH_WARN_LIMIT)

#define CAN_FLAG_CLR_MSK                (CAN_FLAG_RB_OVF           | \
                                         CAN_FLAG_TRANS_ABORTED    | \
                                         CAN_FLAG_ERR_INT          | \
                                         CAN_FLAG_STB_TRANS_OK     | \
                                         CAN_FLAG_PTB_TRANS_OK     | \
                                         CAN_FLAG_RB_ALMOST_FULL   | \
                                         CAN_FLAG_RB_FIFO_FULL     | \
                                         CAN_FLAG_RX_OVERRUN       | \
                                         CAN_FLAG_RX_OK            | \
                                         CAN_FLAG_BUS_ERR          | \
                                         CAN_FLAG_ARB_LOST         | \
                                         CAN_FLAG_ERR_PASSIVE      | \
                                         CAN_FLAG_ERR_PASSIVE_NODE | \
                                         CAN_FLAG_REACH_WARN_LIMIT)

#define CAN_FLAG_TX_ERR_MSK             (CAN_FLAG_BUS_OFF          | \
                                         CAN_FLAG_TB_FULL          | \
                                         CAN_FLAG_ERR_INT          | \
                                         CAN_FLAG_BUS_ERR          | \
                                         CAN_FLAG_ARB_LOST         | \
                                         CAN_FLAG_ERR_PASSIVE      | \
                                         CAN_FLAG_ERR_PASSIVE_NODE | \
                                         CAN_FLAG_REACH_WARN_LIMIT)

/**
 * @}
 */

/**
 * @defgroup CAN_AF_Mask_Type CAN AF Mask Type
 * @{
 */
#define CAN_AF_MSK_STD_EXT              (0x0U)                  /*!< Acceptance filter accept standard ID mask and extended ID mask. */
#define CAN_AF_MSK_STD                  (CAN_ACF_AIDEE)         /*!< Acceptance filter accept standard ID mask. */
#define CAN_AF_MSK_EXT                  (CAN_ACF_AIDEE | \
                                         CAN_ACF_AIDE)          /*!< Acceptance filter accept extended ID mask. */
/**
 * @}
 */

/**
 * @defgroup CAN_Error_Type CAN Error Type
 * @{
 */
#define CAN_ERR_NO                      (0U)                    /*!< No error. */
#define CAN_ERR_BIT                     (CAN_EALCAP_KOER_0)     /*!< Error is bit error. */
#define CAN_ERR_FORM                    (CAN_EALCAP_KOER_1)     /*!< Error is form error. */
#define CAN_ERR_STUFF                   (CAN_EALCAP_KOER_1 | \
                                         CAN_EALCAP_KOER_0)     /*!< Error is stuff error. */
#define CAN_ERR_ACK                     (CAN_EALCAP_KOER_2)     /*!< Error is ACK error. */
#define CAN_ERR_CRC                     (CAN_EALCAP_KOER_2 | \
                                         CAN_EALCAP_KOER_0)     /*!< Error is CRC error. */
#define CAN_ERR_OTHER                   (CAN_EALCAP_KOER_2 | \
                                         CAN_EALCAP_KOER_1)     /*!< Error is other error. */
/**
 * @}
 */

/**
 * @defgroup CAN_AF CAN Acceptance Filter
 * @{
 */
#define CAN_AF1                         (CAN_ACFEN_AE_1)        /*!< Acceptance filter 1 select bit. */
#define CAN_AF2                         (CAN_ACFEN_AE_2)        /*!< Acceptance filter 2 select bit. */
#define CAN_AF3                         (CAN_ACFEN_AE_3)        /*!< Acceptance filter 3 select bit. */
#define CAN_AF4                         (CAN_ACFEN_AE_4)        /*!< Acceptance filter 4 select bit. */
#define CAN_AF5                         (CAN_ACFEN_AE_5)        /*!< Acceptance filter 5 select bit. */
#define CAN_AF6                         (CAN_ACFEN_AE_6)        /*!< Acceptance filter 6 select bit. */
#define CAN_AF7                         (CAN_ACFEN_AE_7)        /*!< Acceptance filter 7 select bit. */
#define CAN_AF8                         (CAN_ACFEN_AE_8)        /*!< Acceptance filter 8 select bit. */
#define CAN_AF9                         (CAN_ACFEN_AE_9)        /*!< Acceptance filter 9 select bit. */
#define CAN_AF10                        (CAN_ACFEN_AE_10)       /*!< Acceptance filter 10 select bit. */
#define CAN_AF11                        (CAN_ACFEN_AE_11)       /*!< Acceptance filter 11 select bit. */
#define CAN_AF12                        (CAN_ACFEN_AE_12)       /*!< Acceptance filter 12 select bit. */
#define CAN_AF13                        (CAN_ACFEN_AE_13)       /*!< Acceptance filter 13 select bit. */
#define CAN_AF14                        (CAN_ACFEN_AE_14)       /*!< Acceptance filter 14 select bit. */
#define CAN_AF15                        (CAN_ACFEN_AE_15)       /*!< Acceptance filter 15 select bit. */
#define CAN_AF16                        (CAN_ACFEN_AE_16)       /*!< Acceptance filter 16 select bit. */
#define CAN_AF_ALL                      (0xFFFFU)
/**
 * @}
 */

/**
 * @defgroup CAN_TTC_Transmit_Buffer_Mode CAN Time-triggered Communication Transmit Buffer Mode
 * @{
 */
#define CAN_TTC_TB_MODE_NORMAL          (0x0U)                      /*!< TTC transmit buffer depends on the priority of STB which is defined by @ref CAN_STB_Priority_Mode */
#define CAN_TTC_TB_MODE_PTR             (CAN_TCTRL_TTTBM)           /*!< TTC transmit buffer is pointed by TBSLOT.TBPTR(for data filling) and \
                                                                         TRG_CFG.TTPTR(for data transmission). */
/**
 * @}
 */

/**
 * @defgroup CAN_TTC_TBS_Pointer CAN Time-triggered Communication Transmit Buffer Slot Pointer
 * @{
 */
#define CAN_TTC_TBS_PTB                 (0x0U)                      /*!< Point to PTB. */
#define CAN_TTC_TBS_STB1                (0x1U)                      /*!< Point to STB slot 1. */
#define CAN_TTC_TBS_STB2                (0x2U)                      /*!< Point to STB slot 2. */
#define CAN_TTC_TBS_STB3                (0x3U)                      /*!< Point to STB slot 3. */
/**
 * @}
 */

/**
 * @defgroup CAN_TTC_Status_Flag CAN Time-triggered Communication Status Flag
 * @{
 */
#define CAN_TTC_FLAG_TTI                (CAN_TTCFG_TTIF)            /*!< Time trigger interrupt flag. */
#define CAN_TTC_FLAG_TEI                (CAN_TTCFG_TEIF)            /*!< Trigger error interrupt flag. */
#define CAN_TTC_FLAG_WTI                (CAN_TTCFG_WTIF)            /*!< Watch trigger interrupt flag. */

#define CAN_TTC_FLAG_ALL                (CAN_TTC_FLAG_TTI | \
                                         CAN_TTC_FLAG_TEI | \
                                         CAN_TTC_FLAG_WTI)
/**
 * @}
 */

/**
 * @defgroup CAN_TTC_Interrupt_Type CAN Time-triggered Communication Interrupt Type
 * @{
 */
#define CAN_TTC_INT_TTI                 (CAN_TTCFG_TTIE)            /*!< Time trigger interrupt. */
#define CAN_TTC_INT_WTI                 (CAN_TTCFG_WTIE)            /*!< Watch trigger interrupt. */
#define CAN_TTC_INT_ALL                 (CAN_TTC_INT_TTI | CAN_TTC_INT_WTI)
/**
 * @}
 */

/**
 * @defgroup CAN_TTC_NTU_Prescaler CAN Time-triggered Communication Network Time Unit Prescaler
 * @{
 */
#define CAN_TTC_NTU_PRESC_1             (0x0U)                      /*!< NTU is SBT bit time * 1. */
#define CAN_TTC_NTU_PRESC_2             (CAN_TTCFG_T_PRESC_0)       /*!< NTU is SBT bit time * 2. */
#define CAN_TTC_NTU_PRESC_4             (CAN_TTCFG_T_PRESC_1)       /*!< NTU is SBT bit time * 4. */
#define CAN_TTC_NTU_PRESC_8             (CAN_TTCFG_T_PRESC_1 | \
                                         CAN_TTCFG_T_PRESC_0)       /*!< NTU is SBT bit time * 8. */
/**
 * @}
 */

/**
 * @defgroup CAN_TTC_Trigger_Type CAN Time-triggered Communication Trigger Type
 * @{
 */
#define CAN_TTC_TRIG_IMMED_TRIG         (0x0U)                      /*!< Immediate trigger for immediate transmission. */
#define CAN_TTC_TRIG_TIME_TRIG          (CAN_TRG_CFG_TTYPE_0)       /*!< Time trigger for receive triggers. */
#define CAN_TTC_TRIG_SSHOT_TRANS_TRIG   (CAN_TRG_CFG_TTYPE_1)       /*!< Single shot transmit trigger for exclusive time windows. */
#define CAN_TTC_TRIG_TRANS_START_TRIG   (CAN_TRG_CFG_TTYPE_1 | \
                                         CAN_TRG_CFG_TTYPE_0)       /*!< Transmit start trigger for merged arbitrating time windows. */
#define CAN_TTC_TRIG_TRANS_STOP_TRIG    (CAN_TRG_CFG_TTYPE_2)       /*!< Transmit stop trigger for merged arbitrating time windows. */
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
     en_result_t CAN_Init(M4_CAN_TypeDef *CANx, const stc_can_init_t *pstcInit);
     en_result_t CAN_StructInit(stc_can_init_t *pstcInit);
            void CAN_DeInit(M4_CAN_TypeDef *CANx);

            void CAN_SWReset(M4_CAN_TypeDef *CANx);
            void CAN_EnterNormalComm(M4_CAN_TypeDef *CANx);

            void CAN_SetWorkMode(M4_CAN_TypeDef *CANx, uint8_t u8WorkMode);
            void CAN_SetTransMode(M4_CAN_TypeDef *CANx, uint8_t u8TransMode);
            void CAN_SetSTBPrioMode(M4_CAN_TypeDef *CANx, uint8_t u8STBPrioMode);
            void CAN_SetRBStoreSel(M4_CAN_TypeDef *CANx, uint8_t u8RBStoreSel);
            void CAN_SetRBOvfOp(M4_CAN_TypeDef *CANx, uint8_t u8RBOvfOperation);

            void CAN_IntCmd(M4_CAN_TypeDef *CANx, uint32_t u32IntType, en_functional_state_t enNewState);
     en_result_t CAN_SBTConfig(M4_CAN_TypeDef *CANx, const stc_can_bt_cfg_t *pstcCfg);
         uint8_t CAN_GetArbLostPos(const M4_CAN_TypeDef *CANx);
         uint8_t CAN_GetErrType(const M4_CAN_TypeDef *CANx);
            void CAN_SetRBSWarnLimit(M4_CAN_TypeDef *CANx, uint8_t u8RBSWarnLimit);
            void CAN_SetErrWarnLimit(M4_CAN_TypeDef *CANx, uint8_t u8ErrWarnLimit);
         uint8_t CAN_GetREC(const M4_CAN_TypeDef *CANx);
         uint8_t CAN_GetTEC(const M4_CAN_TypeDef *CANx);
            void CAN_ClrErrCount(M4_CAN_TypeDef *CANx);
     en_result_t CAN_AFConfig(M4_CAN_TypeDef *CANx, uint16_t u16AFSel, const stc_can_af_cfg_t pstcAFCfg[]);
            void CAN_AFCmd(M4_CAN_TypeDef *CANx, uint16_t u16AFSel, en_functional_state_t enNewState);

         uint8_t CAN_GetTBType(const M4_CAN_TypeDef *CANx);
            void CAN_AbortTrans(M4_CAN_TypeDef *CANx, uint8_t u8TBType);

en_flag_status_t CAN_GetStatus(const M4_CAN_TypeDef *CANx, uint32_t u32Flag);
            void CAN_ClrStatus(M4_CAN_TypeDef *CANx, uint32_t u32Flag);
        uint32_t CAN_GetStatusVal(const M4_CAN_TypeDef *CANx);
         uint8_t CAN_GetTBFullStatus(const M4_CAN_TypeDef *CANx);
         uint8_t CAN_GetRBFullStatus(const M4_CAN_TypeDef *CANx);

     en_result_t CAN_FD_Config(M4_CAN_TypeDef *CANx, const stc_can_fd_cfg_t *pstcCfg);
     en_result_t CAN_FD_StructInit(stc_can_fd_cfg_t *pstcCfg);
            void CAN_FD_Cmd(const M4_CAN_TypeDef *CANx, en_functional_state_t enNewState);

     en_result_t CAN_TTC_StructInit(stc_can_ttc_cfg_t *pstcCfg);
     en_result_t CAN_TTC_Config(M4_CAN_TypeDef *CANx, const stc_can_ttc_cfg_t *pstcCfg);
            void CAN_TTC_Cmd(M4_CAN_TypeDef *CANx, en_functional_state_t enNewState);

            void CAN_TTC_SetTBSToBeFilled(M4_CAN_TypeDef *CANx, uint8_t u8SlotPtr);
            void CAN_TTC_SetTBSFilled(M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetNTUPrescaler(M4_CAN_TypeDef *CANx, uint8_t u8NTUPrescaler);
            void CAN_TTC_IntCmd(M4_CAN_TypeDef *CANx, uint8_t u8IntType, en_functional_state_t enNewState);
en_flag_status_t CAN_TTC_GetStatus(const M4_CAN_TypeDef *CANx, uint8_t u8Flag);
            void CAN_TTC_ClrStatus(M4_CAN_TypeDef *CANx, uint8_t u8Flag);
         uint8_t CAN_TTC_GetStatusVal(const M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetRefMsgID(M4_CAN_TypeDef *CANx, uint32_t u32ID);
            void CAN_TTC_SetRefMsgIDE(M4_CAN_TypeDef *CANx, uint32_t u32IDE);
        uint32_t CAN_TTC_GetRefMsgID(const M4_CAN_TypeDef *CANx);
        uint32_t CAN_TTC_GetRefMsgIDE(const M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetTxTrigTBS(M4_CAN_TypeDef *CANx, uint8_t u8TBSlotPtr);
         uint8_t CAN_TTC_GetTxTrigTBS(const M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetTrigType(M4_CAN_TypeDef *CANx, uint16_t u16TrigType);
        uint16_t CAN_TTC_GetTrigType(const M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetTxEnableWindow(M4_CAN_TypeDef *CANx, uint16_t u16TxEnableWindow);
        uint16_t CAN_TTC_GetTxEnableWindow(const M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetTxTrigTime(M4_CAN_TypeDef *CANx, uint16_t u16TxTrigTime);
        uint16_t CAN_TTC_GetTxTrigTime(const M4_CAN_TypeDef *CANx);
            void CAN_TTC_SetWatchTrigTime(M4_CAN_TypeDef *CANx, uint16_t u16WatchTrigTime);
        uint16_t CAN_TTC_GetWatchTrigTime(const M4_CAN_TypeDef *CANx);

     en_result_t CAN_TransData(M4_CAN_TypeDef *CANx, const stc_can_tx_t *pstcTx,
                               uint8_t u8TxBufType, uint8_t u8STBTxCtrl, uint32_t u32Timeout);
     en_result_t CAN_TTC_TransData(M4_CAN_TypeDef *CANx, const stc_can_tx_t *pstcTx, uint8_t u8TBSlot);

     en_result_t CAN_ReceiveData(M4_CAN_TypeDef *CANx, stc_can_rx_t *pstcRx, uint8_t *pu8RxFrameCnt, uint8_t u8RxFrameBufLength);

/**
 * @}
 */

#endif /* DDL_CAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_CAN_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
