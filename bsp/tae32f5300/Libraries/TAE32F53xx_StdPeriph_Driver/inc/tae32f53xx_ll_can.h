/**
  ******************************************************************************
  * @file    tae32f53xx_ll_can.h
  * @author  MCD Application Team
  * @brief   Header file for CAN LL module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_CAN_H_
#define _TAE32F53XX_LL_CAN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup CAN_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Types CAN LL Exported Types
  * @brief    CAN LL Exported Types
  * @{
  */

/**
  *@brief CAN RX buffer status enum type define
  */
typedef enum {
    CAN_RX_BUF_STA_EMPTY = 0,       /*!< CAN RX buffer empty        */
    CAN_RX_BUF_STA_FEW,             /*!< CAN RX buffer few          */
    CAN_RX_BUF_STA_ALMOST_FULL,     /*!< CAN RX buffer almost full  */
    CAN_RX_BUF_STA_FULL,            /*!< CAN RX buffer full         */
} CAN_RxBufStaETypeDef;

/**
  * @brief CAN acceptance filter slot definition.
  */
typedef enum {
    CAN_ACCEPT_FILT_SLOT_0 = 0,     /*!< CAN acceptance filter slot 0   */
    CAN_ACCEPT_FILT_SLOT_1,         /*!< CAN acceptance filter slot 1   */
    CAN_ACCEPT_FILT_SLOT_2,         /*!< CAN acceptance filter slot 2   */
    CAN_ACCEPT_FILT_SLOT_3,         /*!< CAN acceptance filter slot 3   */
    CAN_ACCEPT_FILT_SLOT_4,         /*!< CAN acceptance filter slot 4   */
    CAN_ACCEPT_FILT_SLOT_5,         /*!< CAN acceptance filter slot 5   */
    CAN_ACCEPT_FILT_SLOT_6,         /*!< CAN acceptance filter slot 6   */
    CAN_ACCEPT_FILT_SLOT_7,         /*!< CAN acceptance filter slot 7   */
    CAN_ACCEPT_FILT_SLOT_8,         /*!< CAN acceptance filter slot 8   */
    CAN_ACCEPT_FILT_SLOT_9,         /*!< CAN acceptance filter slot 9   */
    CAN_ACCEPT_FILT_SLOT_10,        /*!< CAN acceptance filter slot 10  */
    CAN_ACCEPT_FILT_SLOT_11,        /*!< CAN acceptance filter slot 11  */
    CAN_ACCEPT_FILT_SLOT_12,        /*!< CAN acceptance filter slot 12  */
    CAN_ACCEPT_FILT_SLOT_13,        /*!< CAN acceptance filter slot 13  */
    CAN_ACCEPT_FILT_SLOT_14,        /*!< CAN acceptance filter slot 14  */
    CAN_ACCEPT_FILT_SLOT_15,        /*!< CAN acceptance filter slot 15  */
} CAN_AcceptFilSlotETypeDef;

/**
  * @brief CAN RX buffer almost full warnning limit definition
  */
typedef enum {
    CAN_RX_ALMOST_FULL_LIMIT_0 = 0,     /*!< CAN RX buffer almost full warnning limit: 0 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_1,         /*!< CAN RX buffer almost full warnning limit: 1 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_2,         /*!< CAN RX buffer almost full warnning limit: 2 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_3,         /*!< CAN RX buffer almost full warnning limit: 3 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_4,         /*!< CAN RX buffer almost full warnning limit: 4 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_5,         /*!< CAN RX buffer almost full warnning limit: 5 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_6,         /*!< CAN RX buffer almost full warnning limit: 6 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_7,         /*!< CAN RX buffer almost full warnning limit: 7 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_8,         /*!< CAN RX buffer almost full warnning limit: 8 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_9,         /*!< CAN RX buffer almost full warnning limit: 9 Byte   */
    CAN_RX_ALMOST_FULL_LIMIT_10,        /*!< CAN RX buffer almost full warnning limit: 10 Byte  */
    CAN_RX_ALMOST_FULL_LIMIT_11,        /*!< CAN RX buffer almost full warnning limit: 11 Byte  */
    CAN_RX_ALMOST_FULL_LIMIT_12,        /*!< CAN RX buffer almost full warnning limit: 12 Byte  */
    CAN_RX_ALMOST_FULL_LIMIT_13,        /*!< CAN RX buffer almost full warnning limit: 13 Byte  */
    CAN_RX_ALMOST_FULL_LIMIT_14,        /*!< CAN RX buffer almost full warnning limit: 14 Byte  */
    CAN_RX_ALMOST_FULL_LIMIT_15,        /*!< CAN RX buffer almost full warnning limit: 15 Byte  */
} CAN_RxAlmostFullLimitETypeDef;

/**
  * @brief CAN programmable error warning limit definition
  */
typedef enum {
    CAN_ERR_WARN_LIMIT_8 = 0,           /*!< CAN programmable error warning limit: 8 bytes      */
    CAN_ERR_WARN_LIMIT_16,              /*!< CAN programmable error warning limit: 16 bytes     */
    CAN_ERR_WARN_LIMIT_24,              /*!< CAN programmable error warning limit: 24 bytes     */
    CAN_ERR_WARN_LIMIT_32,              /*!< CAN programmable error warning limit: 32 bytes     */
    CAN_ERR_WARN_LIMIT_40,              /*!< CAN programmable error warning limit: 40 bytes     */
    CAN_ERR_WARN_LIMIT_48,              /*!< CAN programmable error warning limit: 48 bytes     */
    CAN_ERR_WARN_LIMIT_56,              /*!< CAN programmable error warning limit: 56 bytes     */
    CAN_ERR_WARN_LIMIT_64,              /*!< CAN programmable error warning limit: 64 bytes     */
    CAN_ERR_WARN_LIMIT_72,              /*!< CAN programmable error warning limit: 72 bytes     */
    CAN_ERR_WARN_LIMIT_80,              /*!< CAN programmable error warning limit: 80 bytes     */
    CAN_ERR_WARN_LIMIT_88,              /*!< CAN programmable error warning limit: 88 bytes     */
    CAN_ERR_WARN_LIMIT_96,              /*!< CAN programmable error warning limit: 96 bytes     */
    CAN_ERR_WARN_LIMIT_104,             /*!< CAN programmable error warning limit: 104 bytes    */
    CAN_ERR_WARN_LIMIT_112,             /*!< CAN programmable error warning limit: 112 bytes    */
    CAN_ERR_WARN_LIMIT_120,             /*!< CAN programmable error warning limit: 120 bytes    */
    CAN_ERR_WARN_LIMIT_128,             /*!< CAN programmable error warning limit: 128 bytes    */
} CAN_ErrWarnLimitETypeDef;


/**
  * @brief CAN RX buffer format type definition
  */
typedef struct __CAN_RxBufFormatTypeDef {
    /*! Standard/Extended iDentifier value
     */
    uint32_t id                  : 29,

             /*! Reserved bit.
              */
             reserved1           : 2,

             /*! Error State Indicator. This is a read-only status bit for RBUF and is not available
              *  in TBUF. The protocol machine automatically embeds the correct value of ESI into
              *  transmitted frames. ESI is only included in CAN FD frames and does not exist in CAN
              *  2.0 frames.
              */
             err_state_indicator : 1;

    /*! The Data Length Code (DLC) in RBUF and TBUF defines the length of the payload(the
     *  number of payload bytes in a frame).
     */
    uint32_t data_len_code       : 4,

             /*! Bit Rate Switch
              *  0: nominal / slow bit rate for the complete frame.
              *  1: switch to data / fast bit rate for the data payload and the CRC
              *  Only CAN FD frames can switch the bitrate. Therefore BRS is forced to 0 if EDL=0
              */
             bit_rate_switch     : 1,

             /*! Extended Data Length
              *  0: CAN 2.0 frame (up to 8 bytes payload)
              *  1: CAN FD frame (up to 64 bytes payload)
              */
             extended_data_len   : 1,

             /*! Remote Transmission Request
              *  0: data frame
              *  1: remote frame
              *  Only CAN 2.0 frames can be remote frames. There is no remote frame for CAN FD.
              *  Therefore RTR is forced to 0 if EDL=1 in the TBUF.
              */
             remote_tx_req       : 1,

             /*! IDentifier Extension
              *  0: Standard Format: ID(10:0)
              *  1: Extended Format: ID(28:0)
              */
             id_extension        : 1,

             /*! Reserved bit.
              */
             reserved2           : 24;
} CAN_RxBufFormatTypeDef;

/**
  * @brief CAN TX buffer format type definition
  */
typedef struct __CAN_TxBufFormatTypeDef {
    /*! Standard/Extended iDentifier value
     */
    uint32_t id                  : 29,

             /*! Reserved bit.
              */
             reserved1           : 3;

    /*! The Data Length Code (DLC) in RBUF and TBUF defines the length of the payload(the
     *  number of payload bytes in a frame).
     */
    uint32_t data_len_code       : 4,

             /*! Bit Rate Switch
              *  0: nominal / slow bit rate for the complete frame.
              *  1: switch to data / fast bit rate for the data payload and the CRC
              *  Only CAN FD frames can switch the bitrate. Therefore BRS is forced to 0 if EDL=0
              */
             bit_rate_switch     : 1,

             /*! Extended Data Length
              *  0: CAN 2.0 frame (up to 8 bytes payload)
              *  1: CAN FD frame (up to 64 bytes payload)
              */
             extended_data_len   : 1,

             /*! Remote Transmission Request
              *  0: data frame
              *  1: remote frame
              *  Only CAN 2.0 frames can be remote frames. There is no remote frame for CAN FD.
              *  Therefore RTR is forced to 0 if EDL=1 in the TBUF.
              */
             remote_tx_req       : 1,

             /*! IDentifier Extension
              *  0: Standard Format: ID(10:0)
              *  1: Extended Format: ID(28:0)
              */
             id_extension        : 1,

             /*! Reserved bit.
              */
             reserved2           : 24;
} CAN_TxBufFormatTypeDef;

/**
  * @brief CAN acceptance filter config type definition
  */
typedef struct __CAN_AcceptFilCfgTypeDef {
    CAN_AcceptFilSlotETypeDef slot;     /*!< acceptance filter slot number */
    uint32_t code_val;                  /*!< acceptance filter code value */
    uint32_t mask_val;                  /*!< acceptance filter mask value */
} CAN_AcceptFilCfgTypeDef;

/**
  * @brief CAN user config type definition
  */
typedef struct __CAN_UserCfgTypeDef {
    uint32_t baudrate;                                  /*!< baudrate                               */
    uint8_t bit_timing_seg1;                            /*!< bit timing segment1                    */
    uint8_t bit_timing_seg2;                            /*!< bit timing degment2                    */
    uint8_t bit_timing_sjw;                             /*!< bit timing synchronization jump width  */
    CAN_RxAlmostFullLimitETypeDef rx_almost_full_limit; /*!< rx buffer almost full warning limit    */
    CAN_ErrWarnLimitETypeDef err_limit;                 /*!< error warning limit                    */
    CAN_AcceptFilCfgTypeDef *accept_fil_cfg_ptr;        /*!< acceptance filter config pointer       */
    uint8_t accept_fil_cfg_num;                         /*!< acceptance filter config number        */
} CAN_UserCfgTypeDef;

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Macros CAN LL Exported Macros
  * @brief    CAN LL Exported Macros
  * @{
  */

/**
  * @brief  CAN reset set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Reset_Set(__CAN__)                 SET_BIT((__CAN__)->CFG_STAT, CAN_RESET_Msk)

/**
  * @brief  CAN reset clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Reset_Clr(__CAN__)                 CLEAR_BIT((__CAN__)->CFG_STAT, CAN_RESET_Msk)

/**
  * @brief  CAN reset status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 CAN reset has set
  * @retval 1 CAN reset has clear
  */
#define __LL_CAN_ResetSta_Get(__CAN__)              (READ_BIT((__CAN__)->CFG_STAT, CAN_RESET_Msk) >> CAN_RESET_Pos)

/**
  * @brief  CAN loop back mode external enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_LoopBackModeExt_En(__CAN__)        SET_BIT((__CAN__)->CFG_STAT, CAN_LOOP_BACK_EXTERNAL_Msk)

/**
  * @brief  CAN loop back mode external disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_LoopBackModeExt_Dis(__CAN__)       CLEAR_BIT((__CAN__)->CFG_STAT, CAN_LOOP_BACK_EXTERNAL_Msk)

/**
  * @brief  CAN loop back mode internal enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_LoopBackModeInternal_En(__CAN__)   SET_BIT((__CAN__)->CFG_STAT, CAN_LOOP_BACK_INTERNAL_Msk)

/**
  * @brief  CAN loop back mode internal disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_LoopBackModeInternal_Dis(__CAN__)  CLEAR_BIT((__CAN__)->CFG_STAT, CAN_LOOP_BACK_INTERNAL_Msk)

/**
  * @brief  CAN TX primary single shot enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriSingleShot_En(__CAN__)        SET_BIT((__CAN__)->CFG_STAT, CAN_TX_PRI_SINGLE_SHOT_Msk)

/**
  * @brief  CAN TX primary single shot disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriSingleShot_Dis(__CAN__)       CLEAR_BIT((__CAN__)->CFG_STAT, CAN_TX_PRI_SINGLE_SHOT_Msk)

/**
  * @brief  CAN TX secondary single shot enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecSingleShot_En(__CAN__)        SET_BIT((__CAN__)->CFG_STAT, CAN_TX_SEC_SINGLE_SHOT_Msk)

/**
  * @brief  CAN TX secondary single shot disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecSingleShot_Dis(__CAN__)       CLEAR_BIT((__CAN__)->CFG_STAT, CAN_TX_SEC_SINGLE_SHOT_Msk)

/**
  * @brief  Judge is RX active or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't RX active
  * @retval 1 Is RX active
  */
#define __LL_CAN_IsRxActive(__CAN__)                (READ_BIT((__CAN__)->CFG_STAT, CAN_RX_ACT_Msk) >> CAN_RX_ACT_Pos)

/**
  * @brief  Judge is TX active or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't TX active
  * @retval 1 Is TX active
  */
#define __LL_CAN_IsTxActive(__CAN__)                (READ_BIT((__CAN__)->CFG_STAT, CAN_TX_ACT_Msk) >> CAN_TX_ACT_Pos)

/**
  * @brief  Judge is bus off or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Is bus on
  * @retval 1 Is bus off
  */
#define __LL_CAN_IsBusOff(__CAN__)                  (READ_BIT((__CAN__)->CFG_STAT, CAN_BUS_OFF_Msk) >> CAN_BUS_OFF_Pos)


/**
  * @brief  TX buffer select PTB
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxBufSel_PTB(__CAN__)              CLEAR_BIT((__CAN__)->TCMD, CAN_TX_BUF_SEL_Msk)

/**
  * @brief  TX buffer select STB
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxBufSel_STB(__CAN__)              SET_BIT((__CAN__)->TCMD, CAN_TX_BUF_SEL_Msk)

/**
  * @brief  Listen only mode enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ListenOnlyMode_En(__CAN__)         SET_BIT((__CAN__)->TCMD, CAN_LISTEN_ONLY_Msk)

/**
  * @brief  Listen only mode disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ListenOnlyMode_Dis(__CAN__)        CLEAR_BIT((__CAN__)->TCMD, CAN_LISTEN_ONLY_Msk)

/**
  * @brief  TX standby mode enalbe
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxStandbyMode_En(__CAN__)          SET_BIT((__CAN__)->TCMD, CAN_TX_STANDBY_Msk)

/**
  * @brief  TX standby mode disalbe
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxStandbyMode_Dis(__CAN__)         CLEAR_BIT((__CAN__)->TCMD, CAN_TX_STANDBY_Msk)

/**
  * @brief  TX primary enable set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriEn_Set(__CAN__)               SET_BIT((__CAN__)->TCMD, CAN_TX_PRI_EN_Msk)

/**
  * @brief  TX primary enable get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX primary enable status
  */
#define __LL_CAN_TxPriEn_Get(__CAN__)               (READ_BIT((__CAN__)->TCMD, CAN_TX_PRI_EN_Msk) >> CAN_TX_PRI_EN_Pos)

/**
  * @brief  TX primary abort set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriAbort_Set(__CAN__)            SET_BIT((__CAN__)->TCMD, CAN_TX_PRI_ABORT_Msk)

/**
  * @brief  TX secondary one set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecOne_Set(__CAN__)              SET_BIT((__CAN__)->TCMD, CAN_TX_SEC_ONE_Msk)

/**
  * @brief  TX secondary one get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX secondary one status
  */
#define __LL_CAN_TxSecOne_Get(__CAN__)              (READ_BIT((__CAN__)->TCMD, CAN_TX_SEC_ONE_Msk) >> CAN_TX_SEC_ONE_Pos)

/**
  * @brief  TX secondary all set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecAll_Set(__CAN__)              SET_BIT((__CAN__)->TCMD, CAN_TX_SEC_ALL_Msk)

/**
  * @brief  TX secondary all get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX secondary send all status
  */
#define __LL_CAN_TxSecAll_Get(__CAN__)              (READ_BIT((__CAN__)->TCMD, CAN_TX_SEC_ALL_Msk) >> CAN_TX_SEC_ALL_Pos)

/**
  * @brief  TX secondary abort set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecAbort_Set(__CAN__)            SET_BIT((__CAN__)->TCMD, CAN_TX_SEC_ABORT_Msk)


/**
  * @brief  FD ISO enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_FD_ISO_En(__CAN__)                 SET_BIT((__CAN__)->TCTRL, CAN_FD_ISO_Msk)

/**
  * @brief  FD ISO disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_FD_ISO_Dis(__CAN__)                CLEAR_BIT((__CAN__)->TCTRL, CAN_FD_ISO_Msk)

/**
  * @brief  TX secondary buffer next set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecNext_Set(__CAN__)             SET_BIT((__CAN__)->TCTRL, CAN_TX_SEC_NEXT_Msk)

/**
  * @brief  TX secondary status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Number of filled message secondary buffers
  */
#define __LL_CAN_TxSecSta_Get(__CAN__)              (READ_BIT((__CAN__)->TCTRL, CAN_TX_SEC_STA_Msk) >> CAN_TX_SEC_STA_Pos)


/**
  * @brief  Judge is RX buffer overflow or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't RX buffer overflow
  * @retval 1 Is RX buffer overflow
  */
#define __LL_CAN_IsRxBufOver(__CAN__)               (READ_BIT((__CAN__)->RCTRL, CAN_RX_BUF_OVER_Msk) >> CAN_RX_BUF_OVER_Pos)

/**
  * @brief  RX buffer release
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufRelease(__CAN__)              SET_BIT((__CAN__)->RCTRL, CAN_RX_BUF_REL_Msk)

/**
  * @brief  RX buffer status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 RX buffer empty
  * @retval 1 empty < RX buffer < almost full
  * @retval 2 RX buffer >= almost full
  * @retval 3 RX buffer full
  */
#define __LL_CAN_RxBufSta_Get(__CAN__)              (READ_BIT((__CAN__)->RCTRL, CAN_RX_BUF_STA_Msk) >> CAN_RX_BUF_STA_Pos)


/**
  * @brief  RX interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Rx_INT_EN(__CAN__)                 SET_BIT((__CAN__)->RTIE, CAN_RX_INT_EN_Msk)

/**
  * @brief  RX interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Rx_INT_Dis(__CAN__)                CLEAR_BIT((__CAN__)->RTIE, CAN_RX_INT_EN_Msk)

/**
  * @brief  RX buffer overrun interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufOver_INT_EN(__CAN__)          SET_BIT((__CAN__)->RTIE, CAN_RX_BUF_OVER_INT_EN_Msk)

/**
  * @brief  RX buffer overrun interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufOver_INT_Dis(__CAN__)         CLEAR_BIT((__CAN__)->RTIE, CAN_RX_BUF_OVER_INT_EN_Msk)

/**
  * @brief  RX buffer full interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufFull_INT_EN(__CAN__)          SET_BIT((__CAN__)->RTIE, CAN_RX_BUF_FULL_INT_EN_Msk)

/**
  * @brief  RX buffer full interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufFull_INT_Dis(__CAN__)         CLEAR_BIT((__CAN__)->RTIE, CAN_RX_BUF_FULL_INT_EN_Msk)

/**
  * @brief  RX buffer almost full interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufAlmostFull_INT_EN(__CAN__)    SET_BIT((__CAN__)->RTIE, CAN_RX_BUF_ALMOST_FULL_INT_EN_Msk)

/**
  * @brief  RX buffer almost full interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufAlmostFull_INT_Dis(__CAN__)   CLEAR_BIT((__CAN__)->RTIE, CAN_RX_BUF_ALMOST_FULL_INT_EN_Msk)

/**
  * @brief  TX primary interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPri_INT_En(__CAN__)              SET_BIT((__CAN__)->RTIE, CAN_TX_PRI_INT_EN_Msk)

/**
  * @brief  TX primary interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPri_INT_Dis(__CAN__)             CLEAR_BIT((__CAN__)->RTIE, CAN_TX_PRI_INT_EN_Msk)

/**
  * @brief  TX secondary interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSec_INT_En(__CAN__)              SET_BIT((__CAN__)->RTIE, CAN_TX_SEC_INT_EN_Msk)

/**
  * @brief  TX secondary interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSec_INT_Dis(__CAN__)             CLEAR_BIT((__CAN__)->RTIE, CAN_TX_SEC_INT_EN_Msk)

/**
  * @brief  Error interrupt enalbe
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Err_INT_En(__CAN__)                SET_BIT((__CAN__)->RTIE, CAN_ERR_INT_EN_Msk)

/**
  * @brief  Error interrupt disalbe
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Err_INT_Dis(__CAN__)               CLEAR_BIT((__CAN__)->RTIE, CAN_ERR_INT_EN_Msk)

/**
  * @brief  Judge is TX secondary buffer full or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't TX secondary buffer full
  * @retval 1 Is TX secondary buffer full
  */
#define __LL_CAN_IsTxSecBufFull(__CAN__)            (READ_BIT((__CAN__)->RTIE, CAN_TX_SEC_BUF_FULL_Msk) >> CAN_TX_SEC_BUF_FULL_Pos)


/**
  * @brief  Interrupt status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt status
  */
#define __LL_CAN_IntSta_Get(__CAN__)                READ_REG((__CAN__)->RTIF)


/**
  * @brief  Judge is error warning limit reached or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't error warning limit reached
  * @retval 1 Is error warning limit reached
  */
#define __LL_CAN_IsErrWarnLimitReached(__CAN__)     \
        (READ_BIT((__CAN__)ERRINT, CAN_ERR_WARN_LIMIT_REACHED_Msk) >> CAN_ERR_WARN_LIMIT_REACHED_Pos)

/**
  * @brief  Judge is error passive mode active or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Error passive mode isn't active
  * @retval 1 Error passive mode is active
  */
#define __LL_CAN_IsErrPassiveModeActive(__CAN__)    (READ_BIT((__CAN__)->ERRINT, CAN_ERR_PASS_ACT_Msk) >> CAN_ERR_PASS_ACT_Pos)

/**
  * @brief  Error passive interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrPassive_INT_En(__CAN__)         SET_BIT((__CAN__)->ERRINT, CAN_ERR_PASS_INT_EN_Msk)

/**
  * @brief  Error passive interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrPassive_INT_Dis(__CAN__)        CLEAR_BIT((__CAN__)->ERRINT, CAN_ERR_PASS_INT_EN_Msk)

/**
  * @brief  Arbitration lost interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ArbLost_INT_En(__CAN__)            SET_BIT((__CAN__)->ERRINT, CAN_ARB_LOST_INT_EN_Msk)

/**
  * @brief  Arbitration lost interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ArbLost_INT_Dis(__CAN__)           CLEAR_BIT((__CAN__)->ERRINT, CAN_ARB_LOST_INT_EN_Msk)

/**
  * @brief  Bus error interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_BusErr_INT_En(__CAN__)             SET_BIT((__CAN__)->ERRINT, CAN_BUS_ERR_INT_EN_Msk)

/**
  * @brief  Bus error interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_BusErr_INT_Dis(__CAN__)            CLEAR_BIT((__CAN__)->ERRINT, CAN_BUS_ERR_INT_EN_Msk)

/**
  * @brief  Error interrupt status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Error interrupt status
  */
#define __LL_CAN_ErrIntSta_Get(__CAN__)             \
        (READ_BIT((__CAN__)->ERRINT, (CAN_ERR_PASS_INT_STA_Msk | CAN_ARB_LOST_INT_STA_Msk | CAN_BUS_ERR_INT_STA_Msk)))


/**
  * @brief  RX buffer almost full warning limit set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_RxBufAlmostFullLimit_Set(__CAN__,val)  \
        MODIFY_REG((__CAN__)->LIMIT, CAN_RX_BUF_ALMOST_FULL_LIMIT_Msk, ((val & 0xfUL) << CAN_RX_BUF_ALMOST_FULL_LIMIT_Pos))

/**
  * @brief  Error warning limit set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_ErrWarnLimit_Set(__CAN__,val)          \
        MODIFY_REG((__CAN__)->LIMIT, CAN_ERR_WARN_LIMIT_Msk, ((val & 0xfUL) << CAN_ERR_WARN_LIMIT_Pos))


/**
  * @brief  Fast speed synchronization jump width set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_SyncJumpWidth_Set(__CAN__,val)      \
        MODIFY_REG((__CAN__)->BITTIME0, CAN_FS_SYNC_JUMP_WIDTH_Msk, ((val & 0x3UL) << CAN_FS_SYNC_JUMP_WIDTH_Pos))

/**
  * @brief  Slow speed bit timing segment1 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_BitTimingSeg1_Set(__CAN__,val)      \
        MODIFY_REG((__CAN__)->BITTIME0, CAN_SS_SEG1_Msk, ((val & 0x3fUL) << CAN_SS_SEG1_Pos))


/**
  * @brief  Fast speed bit timing segment2 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_BitTimingSeg2_Set(__CAN__,val)      \
        MODIFY_REG((__CAN__)->BITTIME1, CAN_FS_SEG2_Msk, ((val & 0x7UL) << CAN_FS_SEG2_Pos))

/**
  * @brief  Slow speed bit timing segment2 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_BitTimingSeg2_Set(__CAN__,val)      \
        MODIFY_REG((__CAN__)->BITTIME1, CAN_SS_SEG2_Msk, ((val & 0x1fUL) << CAN_SS_SEG2_Pos))


/**
  * @brief  Fast speed bit timing segment1 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_BitTimingSeg1_Set(__CAN__,val)      \
        MODIFY_REG((__CAN__)->BITTIME2, CAN_FS_SEG1_Msk, ((val & 0xfUL) << CAN_FS_SEG1_Pos))

/**
  * @brief  Slow speed synchronization jump width set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_SyncJumpWidth_Set(__CAN__,val)      \
        MODIFY_REG((__CAN__)->BITTIME2, CAN_SS_SYNC_JUMP_WIDTH_Msk, ((val & 0xfUL) << CAN_SS_SYNC_JUMP_WIDTH_Pos))


/**
  * @brief  Slow speed prescaler set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_Prescaler_Set(__CAN__,val)      WRITE_REG((__CAN__)->S_PRESC, ((val) & CAN_SS_PRESCALER_Msk))


/**
  * @brief  Fast speed prescaler set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_Prescaler_Set(__CAN__,val)      WRITE_REG((__CAN__)->F_PRESC, ((val) & CAN_FS_PRESCALER_Msk))


/**
  * @brief  TX delay compensation enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxDelayComp_En(__CAN__)            SET_BIT((__CAN__)->TDC, CAN_TX_DELAY_COMP_EN_Msk)

/**
  * @brief  TX delay compensation disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxDelayComp_Dis(__CAN__)           CLEAR_BIT((__CAN__)->TDC, CAN_TX_DELAY_COMP_EN_Msk)

/**
  * @brief  Secondary sample point offset set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SecSamplePointOffset_Set(__CAN__,val)  \
        MODIFY_REG((__CAN__)->TDC, CAN_SEC_SAMPLE_POINT_OFFSET_Msk, ((val & 0x1f) << CAN_SEC_SAMPLE_POINT_OFFSET_Pos))


/**
  * @brief  Error code get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 no error
  * @retval 1 bit error
  * @retval 2 form error
  * @retval 3 stuff error
  * @retval 4 acknowledgement error
  * @retval 5 CRC error
  * @retval 6 other error
  * @retval 7 not used
  */
#define __LL_CAN_ErrCode_Get(__CAN__)           (READ_BIT((__CAN__)->EALCAP, CAN_ERR_CODE_Msk) >> CAN_ERR_CODE_Pos)

/**
  * @brief  Arbitration lost capture get
  * @param  __CAN__ Specifies CAN peripheral
  * @return bit position in the frame where the arbitration has been lost
  */
#define __LL_CAN_ArbLostCapture_Get(__CAN__)    (READ_BIT((__CAN__)->EALCAP, CAN_ARB_LOST_CAPTURE_Msk) >> CAN_ARB_LOST_CAPTURE_Pos)


/**
  * @brief  RX error count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return RX error count
  */
#define __LL_CAN_RxErrCnt_Get(__CAN__)              READ_REG((__CAN__)->RECNT)


/**
  * @brief  TX error count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX error count
  */
#define __LL_CAN_TxErrCnt_Get(__CAN__)              READ_REG((__CAN__)->TECNT)


/**
  * @brief  Acceptance filter content select mask
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilContentSel_Mask(__CAN__)  SET_BIT((__CAN__)->ACFCTRL, CAN_ACPT_FIL_CONTENT_SEL_Msk)

/**
  * @brief  Acceptance filter content select code
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilContentSel_Code(__CAN__)  CLEAR_BIT((__CAN__)->ACFCTRL, CAN_ACPT_FIL_CONTENT_SEL_Msk)

/**
  * @brief  Acceptance filter address set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_AcceptFilAddr_Set(__CAN__, val)    \
        MODIFY_REG((__CAN__)->ACFCTRL, CAN_ACPT_FIL_ADDR_Msk, ((val & 0xfUL) << CAN_ACPT_FIL_ADDR_Pos))


/**
  * @brief  Acceptance filter enable
  * @param  __CAN__ Specifies CAN peripheral
  * @param  fil_num Acceptance filter slot number
  * @note fil_num value range [0, 15]
  * @return None
  */
#define __LL_CAN_AcceptFil_En(__CAN__, fil_num)                                                 \
        do {                                                                                    \
            if(fil_num < 8) {                                                                   \
                MODIFY_REG((__CAN__)->ACF_EN_0, (0x1UL<<fil_num), (0x1UL<<fil_num));            \
            } else if(fil_num < 16) {                                                           \
                MODIFY_REG((__CAN__)->ACF_EN_1, (0x1UL<<(fil_num-8)), (0x1UL<<(fil_num-8)));    \
            }                                                                                   \
        } while(0)


/**
  * @brief  Acceptance mask IDE bit check enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDE_En(__CAN__)       SET_BIT((__CAN__)->ACF, CAN_ACPT_MASK_IDE_CHK_EN_Msk)

/**
  * @brief  Acceptance mask IDE bit check disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDE_Dis(__CAN__)      CLEAR_BIT((__CAN__)->ACF, CAN_ACPT_MASK_IDE_CHK_EN_Msk)

/**
  * @brief  Acceptance filter accepts only extended frames
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDESel_Ext(__CAN__)   SET_BIT((__CAN__)->ACF, CAN_ACPT_MASK_IDE_BIT_VAL_Msk)

/**
  * @brief  Acceptance filter accepts only standard frames
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDESel_Std(__CAN__)   CLEAR_BIT((__CAN__)->ACF, CAN_ACPT_MASK_IDE_BIT_VAL_Msk)

/**
  * @brief  Acceptance filter code or mask set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_AcceptFilCodeOrMaskVal_Set(__CAN__, val)       \
        MODIFY_REG((__CAN__)->ACF, CAN_ACPT_CODE_OR_MASK_Msk, ((val & 0x1fffffffUL) << CAN_ACPT_CODE_OR_MASK_Pos))



/**
  * @brief CAN frame ID format to 11 bits
  */
#define __LL_CAN_FrameIDFormat_11Bits(n)            ((n) & 0x7FFUL)

/**
  * @brief CAN frame ID format to 29 bits
  */
#define __LL_CAN_FrameIDFormat_29Bits(n)            ((n) & 0x1FFFFFFFUL)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CAN_LL_Exported_Functions
  * @{
  */

/** @addtogroup CAN_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_CAN_Init(CAN_TypeDef *Instance, CAN_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_CAN_DeInit(CAN_TypeDef *Instance);
void LL_CAN_MspInit(CAN_TypeDef *Instance);
void LL_CAN_MspDeInit(CAN_TypeDef *Instance);
/**
  * @}
  */

/** @addtogroup CAN_LL_Exported_Functions_Group2
  * @{
  */
uint32_t LL_CAN_SendStandard_PTB(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf);
uint32_t LL_CAN_SendStandard_STB(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf);
uint32_t LL_CAN_SendStandard_STB_Multi(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt,
                                       uint32_t *buf, uint32_t send_cnt);
/**
  * @}
  */

/** @addtogroup CAN_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_CAN_IRQHandler(CAN_TypeDef *Instance);

void LL_CAN_RxCallback(CAN_TypeDef *Instance);
void LL_CAN_RxOverCallback(CAN_TypeDef *Instance);
void LL_CAN_RxFullCallback(CAN_TypeDef *Instance);
void LL_CAN_RxAlmostFullCallback(CAN_TypeDef *Instance);
void LL_CAN_TxPriCallback(CAN_TypeDef *Instance);
void LL_CAN_TxSecCallback(CAN_TypeDef *Instance);
void LL_CAN_ErrCallback(CAN_TypeDef *Instance);
void LL_CAN_AbortCallback(CAN_TypeDef *Instance);

void LL_CAN_ErrPassiveCallback(CAN_TypeDef *Instance);
void LL_CAN_ArbLostCallback(CAN_TypeDef *Instance);
void LL_CAN_BusErrCallback(CAN_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_CAN_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

