/**
  ******************************************************************************
  * @file    tae32g58xx_ll_can.h
  * @author  MCD Application Team
  * @brief   Header file for CAN LL module
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
#ifndef _TAE32G58XX_LL_CAN_H_
#define _TAE32G58XX_LL_CAN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup CAN_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Constants CAN LL Exported Constants
  * @brief    CAN LL Exported Constants
  * @{
  */

/**
  * @brief CAN 2.0 Max Data Length Definition
  */
#define CAN_20_DAT_LEN_MAX      (8)

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Macros CAN LL Exported Macros
  * @brief    CAN LL Exported Macros
  * @{
  */

/**
  * @brief  RX buffer almost full warning limit set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_RxBufAlmostFullLimit_Set(__CAN__, val) \
        MODIFY_REG((__CAN__)->CTRL, CAN0_CTRL_AFWL_Msk, (((val) & 0xfUL) << CAN0_CTRL_AFWL_Pos))

/**
  * @brief  Error warning limit set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_ErrWarnLimit_Set(__CAN__, val)         \
        MODIFY_REG((__CAN__)->CTRL, CAN0_CTRL_EWL_Msk, (((val) & 0xfUL) << CAN0_CTRL_EWL_Pos))

/**
  * @brief  ETB buffer release
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBBufRelease(__CAN__)                 SET_BIT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk)

/**
  * @brief  Judge is ETB buffer release complete or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 ETB buffer release doing
  * @retval 1 ETB buffer release done
  */
#define __LL_CAN_IsETBBufReleaseDone(__CAN__)           (!READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk, CAN0_CTRL_EREL_Pos))

/**
  * @brief  ETB all buffer release
  * @note   Do not define local variables inside this macro.
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBAllBufRelease(__CAN__)              \
        do {                                            \
            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk);                                     \
            while (READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk, CAN0_CTRL_EREL_Pos)); \
            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk);                                     \
            while (READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk, CAN0_CTRL_EREL_Pos)); \
            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk);                                     \
            while (READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_EREL_Msk, CAN0_CTRL_EREL_Pos)); \
        }while(0)

/**
  * @brief  SRB buffer release
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBBufRelease(__CAN__)                 SET_BIT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk)

/**
  * @brief  Judge is SRB buffer release complete or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 SRB buffer release doing
  * @retval 1 SRB buffer release done
  */
#define __LL_CAN_IsSRBBufReleaseDone(__CAN__)           (!READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk, CAN0_CTRL_SREL_Pos))

/**
  * @brief  SRB all buffer release
  * @note   Do not define local variables inside this macro.
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBAllBufRelease(__CAN__)              \
        do {                                            \
            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk);                                     \
            while (READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk, CAN0_CTRL_SREL_Pos)); \
            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk);                                     \
            while (READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk, CAN0_CTRL_SREL_Pos)); \
            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk);                                     \
            while (READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_SREL_Msk, CAN0_CTRL_SREL_Pos)); \
        }while(0)

/**
  * @brief  RX buffer release
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufRelease(__CAN__)                  SET_BIT((__CAN__)->CTRL, CAN0_CTRL_RREL_Msk)

/**
  * @brief  CAN FD Enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_FD_En(__CAN__)                         SET_BIT((__CAN__)->CTRL, CAN0_CTRL_FD_EN_Msk)

/**
  * @brief  CAN FD Disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_FD_Dis(__CAN__)                        CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_FD_EN_Msk)

/**
  * @brief  Judge is CAN FD Enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 CAN FD is Disable
  * @retval 1 CAN FD is Enable
  */
#define __LL_CAN_IsFDEn(__CAN__)                        READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_FD_EN_Msk, CAN0_CTRL_FD_EN_Pos)

/**
  * @brief  CAN FD ISO Enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_FD_ISO_En(__CAN__)                     SET_BIT((__CAN__)->CTRL, CAN0_CTRL_FD_ISO_Msk)

/**
  * @brief  CAN FD ISO Disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_FD_ISO_Dis(__CAN__)                    CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_FD_ISO_Msk)

/**
  * @brief  TX secondary buffer next set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecNext_Set(__CAN__)                 SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSNEXT_Msk)

/**
  * @brief  TX secondary buffer next get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Not action
  * @retval 1 TX secondary buffer next
  */
#define __LL_CAN_TxSecNext_Get(__CAN__)                 READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_TSNEXT_Msk, CAN0_CTRL_TSNEXT_Pos)

/**
  * @brief  Protocol Exception Detect Disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ProtExcDetectDis_Assert(__CAN__)       SET_BIT((__CAN__)->CTRL, CAN0_CTRL_PEDT_Msk)

/**
  * @brief  Protocol Exception Detect Enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ProtExcDetectDis_Release(__CAN__)      CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_PEDT_Msk)

/**
  * @brief  Judge is Protocol Exception Detect Disable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Protocol Exception Detect Enable
  * @retval 1 Protocol Exception Detect Disable
  */
#define __LL_CAN_IsProtExcDetectDis(__CAN__)            READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_PEDT_Msk, CAN0_CTRL_PEDT_Pos)

/**
  * @brief  RX Receive Multiplexer Set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  muxsel Rx Receive Multiplexer select
  * @return None
  */
#define __LL_CAN_RxMuxSel_Set(__CAN__, muxsel)      \
        MODIFY_REG((__CAN__)->CTRL, CAN0_CTRL_MUXSEL_Msk, (((muxsel) & 0x1UL) << CAN0_CTRL_MUXSEL_Pos))

/**
  * @brief  TX buffer select PTB
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxBufSel_PTB(__CAN__)                  CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_TBSEL_Msk)

/**
  * @brief  TX buffer select STB
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxBufSel_STB(__CAN__)                  SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TBSEL_Msk)

/**
  * @brief  TX buffer select PTB or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 1 Select PTB Buffer
  * @retval 0 Select STB Buffer
  */
#define __LL_CAN_IsTxBufSelPTB(__CAN__)                 (!READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_TBSEL_Msk, CAN0_CTRL_TBSEL_Pos))

/**
  * @brief  Listen only mode Enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ListenOnlyMode_En(__CAN__)             SET_BIT((__CAN__)->CTRL, CAN0_CTRL_LOM_Msk)

/**
  * @brief  Listen only mode Disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ListenOnlyMode_Dis(__CAN__)            CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_LOM_Msk)

/**
  * @brief  TX primary enable set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriEn_Set(__CAN__)                   SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TPE_Msk)

/**
  * @brief  TX primary enable get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX primary enable status
  */
#define __LL_CAN_TxPriEn_Get(__CAN__)                   READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_TPE_Msk, CAN0_CTRL_TPE_Pos)

/**
  * @brief  TX primary abort set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriAbort_Set(__CAN__)                SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TPA_Msk)

/**
  * @brief  TX secondary one set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecOne_Set(__CAN__)                  SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSONE_Msk)

/**
  * @brief  TX secondary one get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX secondary one status
  */
#define __LL_CAN_TxSecOne_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_TSONE_Msk, CAN0_CTRL_TSONE_Pos)

/**
  * @brief  TX secondary all set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecAll_Set(__CAN__)                  SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSALL_Msk)

/**
  * @brief  TX secondary all get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX secondary send all status
  */
#define __LL_CAN_TxSecAll_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_TSALL_Msk, CAN0_CTRL_TSALL_Pos)

/**
  * @brief  TX secondary abort set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecAbort_Set(__CAN__)                SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSA_Msk)

/**
  * @brief  CAN reset set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Reset_Set(__CAN__)                     SET_BIT((__CAN__)->CTRL, CAN0_CTRL_RESET_Msk)

/**
  * @brief  CAN reset clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Reset_Clr(__CAN__)                     CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_RESET_Msk)

/**
  * @brief  CAN reset status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 CAN reset has set
  * @retval 1 CAN reset has clear
  */
#define __LL_CAN_ResetSta_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->CTRL, CAN0_CTRL_RESET_Msk, CAN0_CTRL_RESET_Pos)

/**
  * @brief  CAN loop back mode external enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_CAN_LoopBackModeExt_En(__CAN__)            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_LBME_Msk)

/**
  * @brief  CAN loop back mode external disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_CAN_LoopBackModeExt_Dis(__CAN__)           CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_LBME_Msk)

/**
  * @brief  CAN loop back mode internal enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_CAN_LoopBackModeInternal_En(__CAN__)       SET_BIT((__CAN__)->CTRL, CAN0_CTRL_LBMI_Msk)

/**
  * @brief  CAN loop back mode internal disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_CAN_LoopBackModeInternal_Dis(__CAN__)      CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_LBMI_Msk)

/**
  * @brief  CAN TX primary single shot enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriSingleShot_En(__CAN__)            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TPSS_Msk)

/**
  * @brief  CAN TX primary single shot disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriSingleShot_Dis(__CAN__)           CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_TPSS_Msk)

/**
  * @brief  CAN TX secondary single shot enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecSingleShot_En(__CAN__)            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSSS_Msk)

/**
  * @brief  CAN TX secondary single shot disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecSingleShot_Dis(__CAN__)           CLEAR_BIT((__CAN__)->CTRL, CAN0_CTRL_TSSS_Msk)


/**
  * @brief  SRB Almost Full Warning Limit set
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the SFIF flag is also set.
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SRBAlmostFullWarnLimit_Set(__CAN__, val)         \
        MODIFY_REG((__CAN__)->STATUS, CAN0_STATUS_SAFWL_Msk, (((val) & 0xfUL) << CAN0_STATUS_SAFWL_Pos))

/**
  * @brief  SRB Almost Full Warning Limit get
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the SFIF flag is also set.
  * @param  __CAN__ Specifies CAN peripheral
  * @return SRB Message Max Quantity
  */
#define __LL_CAN_SRBAlmostFullWarnLimit_Get(__CAN__)    READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_SAFWL_Msk, CAN0_STATUS_SAFWL_Pos)

/**
  * @brief  ETB Almost Full Warning Limit set
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the EFIF flag is also set.
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_ETBAlmostFullWarnLimit_Set(__CAN__, val)         \
        MODIFY_REG((__CAN__)->STATUS, CAN0_STATUS_EAFWL_Msk, (((val) & 0xfUL) << CAN0_STATUS_EAFWL_Pos))

/**
  * @brief  ETB Almost Full Warning Limit get
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the EFIF flag is also set.
  * @param  __CAN__ Specifies CAN peripheral
  * @return ETB Message Max Quantity
  */
#define __LL_CAN_ETBAlmostFullWarnLimit_Get(__CAN__)    READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_EAFWL_Msk, CAN0_STATUS_EAFWL_Pos)

/**
  * @brief  STB Almost Empty Warning Limit set
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the TAEIF flag is also set.
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_STBAlmostEmptyWarnLimit_Set(__CAN__, val)        \
        MODIFY_REG((__CAN__)->STATUS, CAN0_STATUS_AEWL_Msk, (((val) & 0xfUL) << CAN0_STATUS_AEWL_Pos))

/**
  * @brief  STB Almost Empty Warning Limit get
  * @note   (1)If its value is greater than 3, it is automatically treated as 3.
  * @note   (2)If the value equals 3, the TAEIF flag is also set.
  * @param  __CAN__ Specifies CAN peripheral
  * @return STB Message Max Quantity
  */
#define __LL_CAN_STBAlmostEmptyWarnLimit_Get(__CAN__)   READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_AEWL_Msk, CAN0_STATUS_AEWL_Pos)

/**
  * @brief  Judge is RX buffer overflow or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't RX buffer overflow
  * @retval 1 Is RX buffer overflow
  */
#define __LL_CAN_IsRxBufOver(__CAN__)                   READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_ROV_Msk, CAN0_STATUS_ROV_Pos)

/**
  * @brief  RX buffer status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 RX buffer empty
  * @retval 1 empty < RX buffer < almost full
  * @retval 2 RX buffer >= almost full
  * @retval 3 RX buffer full
  */
#define __LL_CAN_RxBufSta_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_RSTAT_Msk, CAN0_STATUS_RSTAT_Pos)

/**
  * @brief  Judge is SRB Receive Buffer Overflow or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Receive Buffer Overflow
  * @retval 1 Is SRB Receive Buffer Overflow
  */
#define __LL_CAN_IsSRBRxBufOver(__CAN__)                READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_SOV_Msk, CAN0_STATUS_SOV_Pos)

/**
  * @brief  SRB Receive Buffer Overflow status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 RX buffer empty
  * @retval 1 empty < RX buffer < almost full
  * @retval 2 RX buffer >= almost full
  * @retval 3 RX buffer full
  */
#define __LL_CAN_SRBRxBufSta_Get(__CAN__)               READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_SSTAT_Msk, CAN0_STATUS_SSTAT_Pos)

/**
  * @brief  TX secondary status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Number of secondary buffer filled messages
  */
#define __LL_CAN_TxSecSta_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_TSSTAT_Msk, CAN0_STATUS_TSSTAT_Pos)

/**
  * @brief  Judge is ETB Receive Buffer Overflow or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Receive Buffer Overflow
  * @retval 1 Is ETB Receive Buffer Overflow
  */
#define __LL_CAN_IsETBRxBufOver(__CAN__)                READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_EOV_Msk, CAN0_STATUS_EOV_Pos)

/**
  * @brief  ETB Receive Buffer Overflow status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 RX buffer empty
  * @retval 1 empty < RX buffer < almost full
  * @retval 2 RX buffer >= almost full
  * @retval 3 RX buffer full
  */
#define __LL_CAN_ETBRxBufSta_Get(__CAN__)               READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_ESTAT_Msk, CAN0_STATUS_ESTAT_Pos)

/**
  * @brief  Judge is RX active or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't RX active
  * @retval 1 Is RX active
  */
#define __LL_CAN_IsRxActive(__CAN__)                    READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_RACTIVE_Msk, CAN0_STATUS_RACTIVE_Pos)

/**
  * @brief  Judge is TX active or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't TX active
  * @retval 1 Is TX active
  */
#define __LL_CAN_IsTxActive(__CAN__)                    READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_TACTIVE_Msk, CAN0_STATUS_TACTIVE_Pos)

/**
  * @brief  Judge is bus off or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Is bus on
  * @retval 1 Is bus off
  */
#define __LL_CAN_IsBusOff(__CAN__)                      READ_BIT_SHIFT((__CAN__)->STATUS, CAN0_STATUS_BUSOFF_Msk, CAN0_STATUS_BUSOFF_Pos)


/**
  * @brief  STB Empty Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_STBEmpty_INT_En(__CAN__)               SET_BIT((__CAN__)->INTREN, CAN0_INTREN_TEIE_Msk)

/**
  * @brief  STB Empty Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_STBEmpty_INT_Dis(__CAN__)              CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_TEIE_Msk)

/**
  * @brief  Judge is STB Empty Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't STB Empty Interrupt enable
  * @retval 1 Is STB Empty Interrupt enable
  */
#define __LL_CAN_IsSTBEmptyIntEn(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_TEIE_Msk, CAN0_INTREN_TEIE_Pos)

/**
  * @brief  STB Almost Empty Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_STBAlmostEmpty_INT_En(__CAN__)         SET_BIT((__CAN__)->INTREN, CAN0_INTREN_TAEIE_Msk)

/**
  * @brief  STB Almost Empty Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_STBAlmostEmpty_INT_Dis(__CAN__)        CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_TAEIE_Msk)

/**
  * @brief  Judge is STB Almost Empty Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't STB Almost Empty Interrupt enable
  * @retval 1 Is STB Almost Empty Interrupt enable
  */
#define __LL_CAN_IsSTBAlmostEmptyIntEn(__CAN__)         READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_TAEIE_Msk, CAN0_INTREN_TAEIE_Pos)

/**
  * @brief  Priority Message Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PrioMesg_INT_En(__CAN__)               SET_BIT((__CAN__)->INTREN, CAN0_INTREN_PMIE_Msk)

/**
  * @brief  Priority Message Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PrioMesg_INT_Dis(__CAN__)              CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_PMIE_Msk)

/**
  * @brief  Judge is Priority Message Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Priority Message Interrupt enable
  * @retval 1 Is Priority Message Interrupt enable
  */
#define __LL_CAN_IsPrioMesgIntEn(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_PMIE_Msk, CAN0_INTREN_PMIE_Pos)

/**
  * @brief  Timestamp Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Timestamp_INT_En(__CAN__)              SET_BIT((__CAN__)->INTREN, CAN0_INTREN_TSCIE_Msk)

/**
  * @brief  Timestamp Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Timestamp_INT_Dis(__CAN__)             CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_TSCIE_Msk)

/**
  * @brief  Judge is Timestamp Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Timestamp Interrupt enable
  * @retval 1 Is Timestamp Interrupt enable
  */
#define __LL_CAN_IsTimestampIntEn(__CAN__)              READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_TSCIE_Msk, CAN0_INTREN_TSCIE_Pos)

/**
  * @brief  PRB Timeout Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBTimeout_INT_En(__CAN__)             SET_BIT((__CAN__)->INTREN, CAN0_INTREN_RTOIE_Msk)

/**
  * @brief  PRB Timeout Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBTimeout_INT_Dis(__CAN__)            CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_RTOIE_Msk)

/**
  * @brief  Judge is PRB Timeout Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't PRB Timeout Interrupt enable
  * @retval 1 Is PRB Timeout Interrupt enable
  */
#define __LL_CAN_IsPRBTimeoutIntEn(__CAN__)             READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_RTOIE_Msk, CAN0_INTREN_RTOIE_Pos)

/**
  * @brief  SRB Timeout Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBTimeout_INT_En(__CAN__)             SET_BIT((__CAN__)->INTREN, CAN0_INTREN_STOIE_Msk)

/**
  * @brief  SRB Timeout Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBTimeout_INT_Dis(__CAN__)            CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_STOIE_Msk)

/**
  * @brief  Judge is SRB Timeout Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Timeout Interrupt enable
  * @retval 1 Is SRB Timeout Interrupt enable
  */
#define __LL_CAN_IsSRBTimeoutIntEn(__CAN__)             READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_STOIE_Msk, CAN0_INTREN_STOIE_Pos)

/**
  * @brief  ETB Timeout Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBTimeout_INT_En(__CAN__)             SET_BIT((__CAN__)->INTREN, CAN0_INTREN_ETOIE_Msk)

/**
  * @brief  ETB Timeout Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBTimeout_INT_Dis(__CAN__)            CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_ETOIE_Msk)

/**
  * @brief  Judge is ETB Timeout Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Timeout Interrupt enable
  * @retval 1 Is ETB Timeout Interrupt enable
  */
#define __LL_CAN_IsETBTimeoutIntEn(__CAN__)             READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_ETOIE_Msk, CAN0_INTREN_ETOIE_Pos)

/**
  * @brief  Continuous Count Timeout Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ContCntTimeout_INT_En(__CAN__)         SET_BIT((__CAN__)->INTREN, CAN0_INTREN_CTOIE_Msk)

/**
  * @brief  Continuous Count Timeout Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ContCntTimeout_INT_Dis(__CAN__)        CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_CTOIE_Msk)

/**
  * @brief  Judge is Continuous Count Timeout Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Continuous Count Timeout Interrupt enable
  * @retval 1 Is Continuous Count Timeout Interrupt enable
  */
#define __LL_CAN_IsContCntTimeoutIntEn(__CAN__)         READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_CTOIE_Msk, CAN0_INTREN_CTOIE_Pos)

/**
  * @brief  SRB Overrun Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBOver_INT_En(__CAN__)                SET_BIT((__CAN__)->INTREN, CAN0_INTREN_SOIE_Msk)

/**
  * @brief  SRB Overrun Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBOver_INT_Dis(__CAN__)               CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_SOIE_Msk)

/**
  * @brief  Judge is SRB Overrun Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Overrun Interrupt enable
  * @retval 1 Is SRB Overrun Interrupt enable
  */
#define __LL_CAN_IsSRBOverIntEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_SOIE_Msk, CAN0_INTREN_SOIE_Pos)

/**
  * @brief  SRB Full Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBFull_INT_En(__CAN__)                SET_BIT((__CAN__)->INTREN, CAN0_INTREN_SFIE_Msk)

/**
  * @brief  SRB Full Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBFull_INT_Dis(__CAN__)               CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_SFIE_Msk)

/**
  * @brief  Judge is SRB Full Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Full Interrupt enable
  * @retval 1 Is SRB Full Interrupt enable
  */
#define __LL_CAN_IsSRBFullIntEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_SFIE_Msk, CAN0_INTREN_SFIE_Pos)

/**
  * @brief  SRB Almost Full Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBAlmostFull_INT_En(__CAN__)          SET_BIT((__CAN__)->INTREN, CAN0_INTREN_SAFIE_Msk)

/**
  * @brief  SRB Almost Full Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBAlmostFull_INT_Dis(__CAN__)         CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_SAFIE_Msk)

/**
  * @brief  Judge is SRB Almost Full Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Almost Full Interrupt enable
  * @retval 1 Is SRB Almost Full Interrupt enable
  */
#define __LL_CAN_IsSRBAlmostFullIntEn(__CAN__)          READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_SAFIE_Msk, CAN0_INTREN_SAFIE_Pos)

/**
  * @brief  ETB Overrun Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBOver_INT_En(__CAN__)                SET_BIT((__CAN__)->INTREN, CAN0_INTREN_EOIE_Msk)

/**
  * @brief  ETB Overrun Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBOver_INT_Dis(__CAN__)               CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_EOIE_Msk)

/**
  * @brief  Judge is ETB Overrun Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Overrun Interrupt enable
  * @retval 1 Is ETB Overrun Interrupt enable
  */
#define __LL_CAN_IsETBOverIntEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_EOIE_Msk, CAN0_INTREN_EOIE_Pos)

/**
  * @brief  ETB Full Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBFull_INT_En(__CAN__)                SET_BIT((__CAN__)->INTREN, CAN0_INTREN_EFIE_Msk)

/**
  * @brief  ETB Full Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBFull_INT_Dis(__CAN__)               CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_EFIE_Msk)

/**
  * @brief  Judge is ETB Full Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Full Interrupt enable
  * @retval 1 Is ETB Full Interrupt enable
  */
#define __LL_CAN_IsETBFullIntEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_EFIE_Msk, CAN0_INTREN_EFIE_Pos)

/**
  * @brief  ETB Almost Full Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBAlmostFull_INT_En(__CAN__)          SET_BIT((__CAN__)->INTREN, CAN0_INTREN_EAFIE_Msk)

/**
  * @brief  ETB Almost Full Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBAlmostFull_INT_Dis(__CAN__)         CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_EAFIE_Msk)

/**
  * @brief  Judge is ETB Almost Full Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Almost Full Interrupt enable
  * @retval 1 Is ETB Almost Full Interrupt enable
  */
#define __LL_CAN_IsETBAlmostFullIntEn(__CAN__)          READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_EAFIE_Msk, CAN0_INTREN_EAFIE_Pos)

/**
  * @brief  Abort Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Abort_INT_En(__CAN__)                  SET_BIT((__CAN__)->INTREN, CAN0_INTREN_AIE_Msk)

/**
  * @brief  Abort Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Abort_INT_Dis(__CAN__)                 CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_AIE_Msk)

/**
  * @brief  Judge is Abort Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Abort Interrupt enable
  * @retval 1 Is Abort Interrupt enable
  */
#define __LL_CAN_IsAbortIntEn(__CAN__)                  READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_AIE_Msk, CAN0_INTREN_AIE_Pos)

/**
  * @brief  SRB Receive Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBRcv_INT_En(__CAN__)                 SET_BIT((__CAN__)->INTREN, CAN0_INTREN_SRIE_Msk)

/**
  * @brief  SRB Receive Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBRcv_INT_Dis(__CAN__)                CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_SRIE_Msk)

/**
  * @brief  Judge is SRB Receive Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Receive Interrupt enable
  * @retval 1 Is SRB Receive Interrupt enable
  */
#define __LL_CAN_IsSRBRcvIntEn(__CAN__)                 READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_SRIE_Msk, CAN0_INTREN_SRIE_Pos)

/**
  * @brief  ETB Receive Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBRcv_INT_En(__CAN__)                 SET_BIT((__CAN__)->INTREN, CAN0_INTREN_ERIE_Msk)

/**
  * @brief  ETB Receive Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBRcv_INT_Dis(__CAN__)                CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_ERIE_Msk)

/**
  * @brief  Judge is ETB Receive Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Receive Interrupt enable
  * @retval 1 Is ETB Receive Interrupt enable
  */
#define __LL_CAN_IsETBRcvIntEn(__CAN__)                 READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_ERIE_Msk, CAN0_INTREN_ERIE_Pos)

/**
  * @brief  Error Counter Interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrCnt_INT_En(__CAN__)                 SET_BIT((__CAN__)->INTREN, CAN0_INTREN_ECIE_Msk)

/**
  * @brief  Error Counter Interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrCnt_INT_Dis(__CAN__)                CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_ECIE_Msk)

/**
  * @brief  Judge is Error Counter Interrupt enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Error Counter Interrupt enable
  * @retval 1 Is Error Counter Interrupt enable
  */
#define __LL_CAN_IsErrCntIntEn(__CAN__)                 READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_ECIE_Msk, CAN0_INTREN_ECIE_Pos)

/**
  * @brief  Error passive interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrPassive_INT_En(__CAN__)             SET_BIT((__CAN__)->INTREN, CAN0_INTREN_EPIE_Msk)

/**
  * @brief  Error passive interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrPassive_INT_Dis(__CAN__)            CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_EPIE_Msk)

/**
  * @brief  Arbitration lost interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ArbLost_INT_En(__CAN__)                SET_BIT((__CAN__)->INTREN, CAN0_INTREN_ALIE_Msk)

/**
  * @brief  Arbitration lost interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ArbLost_INT_Dis(__CAN__)               CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_ALIE_Msk)

/**
  * @brief  Bus error interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_BusErr_INT_En(__CAN__)                 SET_BIT((__CAN__)->INTREN, CAN0_INTREN_BEIE_Msk)

/**
  * @brief  Bus error interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_BusErr_INT_Dis(__CAN__)                CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_BEIE_Msk)

/**
  * @brief  RX interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Rx_INT_En(__CAN__)                     SET_BIT((__CAN__)->INTREN, CAN0_INTREN_RIE_Msk)

/**
  * @brief  RX interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Rx_INT_Dis(__CAN__)                    CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_RIE_Msk)

/**
  * @brief  RX buffer overrun interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufOver_INT_En(__CAN__)              SET_BIT((__CAN__)->INTREN, CAN0_INTREN_ROIE_Msk)

/**
  * @brief  RX buffer overrun interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufOver_INT_Dis(__CAN__)             CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_ROIE_Msk)

/**
  * @brief  RX buffer full interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufFull_INT_En(__CAN__)              SET_BIT((__CAN__)->INTREN, CAN0_INTREN_RFIE_Msk)

/**
  * @brief  RX buffer full interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufFull_INT_Dis(__CAN__)             CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_RFIE_Msk)

/**
  * @brief  RX buffer almost full interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufAlmostFull_INT_En(__CAN__)        SET_BIT((__CAN__)->INTREN, CAN0_INTREN_RAFIE_Msk)

/**
  * @brief  RX buffer almost full interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxBufAlmostFull_INT_Dis(__CAN__)       CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_RAFIE_Msk)

/**
  * @brief  TX primary interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPri_INT_En(__CAN__)                  SET_BIT((__CAN__)->INTREN, CAN0_INTREN_TPIE_Msk)

/**
  * @brief  TX primary interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPri_INT_Dis(__CAN__)                 CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_TPIE_Msk)

/**
  * @brief  TX secondary interrupt enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSec_INT_En(__CAN__)                  SET_BIT((__CAN__)->INTREN, CAN0_INTREN_TSIE_Msk)

/**
  * @brief  TX secondary interrupt disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSec_INT_Dis(__CAN__)                 CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_TSIE_Msk)

/**
  * @brief  Error interrupt enalbe
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Err_INT_En(__CAN__)                    SET_BIT((__CAN__)->INTREN, CAN0_INTREN_EIE_Msk)

/**
  * @brief  Error interrupt disalbe
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_Err_INT_Dis(__CAN__)                   CLEAR_BIT((__CAN__)->INTREN, CAN0_INTREN_EIE_Msk)

/**
  * @brief  Judge is TX secondary buffer full or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't TX secondary buffer full
  * @retval 1 Is TX secondary buffer full
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_CAN_IsTxSecBufFull(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTREN, CAN0_INTREN_TSFF_Msk, CAN0_INTREN_TSFF_Pos)

/**
  * @brief  All Interrupt Enable Status Get
  * @param  __CAN__ Specifies CAN peripheral
  * @return All Interrupt Enable Status
  */
#define __LL_CAN_AllIntEn_Get(__CAN__)                  READ_REG((__CAN__)->INTREN)


/**
  * @brief  Judge is STB Empty Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't STB Empty Interrupt Pending
  * @retval 1 Is STB Empty Interrupt Pending
  */
#define __LL_CAN_IsSTBEmptyIntPnd(__CAN__)              READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_TEIF_Msk, CAN0_INTRST_TEIF_Pos)

/**
  * @brief  STB Empty Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_STBEmptyIntPnd_Clr(__CAN__)            SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSNEXT_Msk)


/**
  * @brief  Judge is STB Almost Empty Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't STB Almost Empty Interrupt Pending
  * @retval 1 Is STB Almost Empty Interrupt Pending
  */
#define __LL_CAN_IsSTBAlmostEmptyIntPnd(__CAN__)        READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_TAEIF_Msk, CAN0_INTRST_TAEIF_Pos)

/**
  * @brief  STB Almost Empty Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_STBAlmostEmptyIntPnd_Clr(__CAN__)      SET_BIT((__CAN__)->CTRL, CAN0_CTRL_TSNEXT_Msk)

/**
  * @brief  Judge is Priority Message Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Priority Message Interrupt Pending
  * @retval 1 Is Priority Message Interrupt Pending
  */
#define __LL_CAN_IsPrioMesgIntPnd(__CAN__)              READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_PMIF_Msk, CAN0_INTRST_PMIF_Pos)

/**
  * @brief  Priority Message Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PrioMesgIntPnd_Clr(__CAN__)            WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_PMIF_Msk)

/**
  * @brief  Judge is Timestamp Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Timestamp Interrupt Pending
  * @retval 1 Is Timestamp Interrupt Pending
  */
#define __LL_CAN_IsTimestampIntPnd(__CAN__)             READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_TSCIF_Msk, CAN0_INTRST_TSCIF_Pos)

/**
  * @brief  Timestamp Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TimestampIntPnd_Clr(__CAN__)           WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_TSCIF_Msk)

/**
  * @brief  Judge is PRB Timeout Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't PRB Timeout Interrupt Pending
  * @retval 1 Is PRB Timeout Interrupt Pending
  */
#define __LL_CAN_IsPRBTimeoutIntPnd(__CAN__)            READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_RTOIF_Msk, CAN0_INTRST_RTOIF_Pos)

/**
  * @brief  PRB Timeout Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBTimeoutIntPnd_Clr(__CAN__)          WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_RTOIF_Msk)

/**
  * @brief  Judge is SRB Timeout Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Timeout Interrupt Pending
  * @retval 1 Is SRB Timeout Interrupt Pending
  */
#define __LL_CAN_IsSRBTimeoutIntPnd(__CAN__)            READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_STOIF_Msk, CAN0_INTRST_STOIF_Pos)

/**
  * @brief  SRB Timeout Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBTimeoutIntPnd_Clr(__CAN__)          WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_STOIF_Msk)

/**
  * @brief  Judge is ETB Timeout Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Timeout Interrupt Pending
  * @retval 1 Is ETB Timeout Interrupt Pending
  */
#define __LL_CAN_IsETBTimeoutIntPnd(__CAN__)            READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_ETOIF_Msk, CAN0_INTRST_ETOIF_Pos)

/**
  * @brief  ETB Timeout Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBTimeoutIntPnd_Clr(__CAN__)          WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_ETOIF_Msk)

/**
  * @brief  Judge is Continuous Count Timeout Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Continuous Count Timeout Interrupt Pending
  * @retval 1 Is Continuous Count Timeout Interrupt Pending
  */
#define __LL_CAN_IsContCntTimeoutIntPnd(__CAN__)        READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_CTOIF_Msk, CAN0_INTRST_CTOIF_Pos)

/**
  * @brief  Continuous Count Timeout Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ContCntTimeoutIntPnd_Clr(__CAN__)      WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_CTOIF_Msk)

/**
  * @brief  Judge is SRB Overflow Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Overflow Interrupt Pending
  * @retval 1 Is SRB Overflow Interrupt Pending
  */
#define __LL_CAN_IsSRBOverIntPnd(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_SOIF_Msk, CAN0_INTRST_SOIF_Pos)

/**
  * @brief  SRB Overflow Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBOverIntPnd_Clr(__CAN__)             WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_SOIF_Msk)

/**
  * @brief  Judge is SRB Full Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Full Interrupt Pending
  * @retval 1 Is SRB Full Interrupt Pending
  */
#define __LL_CAN_IsSRBFullIntPnd(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_SFIF_Msk, CAN0_INTRST_SFIF_Pos)

/**
  * @brief  SRB Full Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBFullIntPnd_Clr(__CAN__)             WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_SFIF_Msk)

/**
  * @brief  Judge is SRB Almost Full Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Almost Full Interrupt Pending
  * @retval 1 Is SRB Almost Full Interrupt Pending
  */
#define __LL_CAN_IsSRBAlmostFullIntPnd(__CAN__)         READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_SAFIF_Msk, CAN0_INTRST_SAFIF_Pos)

/**
  * @brief  SRB Almost Full Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBAlmostFullIntPnd_Clr(__CAN__)       WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_SAFIF_Msk)

/**
  * @brief  Judge is ETB Overflow Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Overflow Interrupt Pending
  * @retval 1 Is ETB Overflow Interrupt Pending
  */
#define __LL_CAN_IsETBOverIntPnd(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EOIF_Msk, CAN0_INTRST_EOIF_Pos)

/**
  * @brief  ETB Overflow Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBOverIntPnd_Clr(__CAN__)             WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_EOIF_Msk)

/**
  * @brief  Judge is ETB Full Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Full Interrupt Pending
  * @retval 1 Is ETB Full Interrupt Pending
  */
#define __LL_CAN_IsETBFullIntPnd(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EFIF_Msk, CAN0_INTRST_EFIF_Pos)

/**
  * @brief  ETB Full Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBFullIntPnd_Clr(__CAN__)             WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_EFIF_Msk)

/**
  * @brief  Judge is ETB Almost Full Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Almost Full Interrupt Pending
  * @retval 1 Is ETB Almost Full Interrupt Pending
  */
#define __LL_CAN_IsETBAlmostFullIntPnd(__CAN__)         READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EAFIF_Msk, CAN0_INTRST_EAFIF_Pos)

/**
  * @brief  ETB Almost Full Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBAlmostFullIntPnd_Clr(__CAN__)       WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_EAFIF_Msk)

/**
  * @brief  Judge is error warning limit reached or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't error warning limit reached
  * @retval 1 Is error warning limit reached
  */
#define __LL_CAN_IsErrWarnLimitReached(__CAN__)         READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EWARN_Msk, CAN0_INTRST_EWARN_Pos)

/**
  * @brief  Judge is error passive mode active or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Error passive mode isn't active
  * @retval 1 Error passive mode is active
  */
#define __LL_CAN_IsErrPassiveModeActive(__CAN__)        READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EPASS_Msk, CAN0_INTRST_EPASS_Pos)

/**
  * @brief  Judge is SRB Receive Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't SRB Receive Interrupt Pending
  * @retval 1 Is SRB Receive Interrupt Pending
  */
#define __LL_CAN_IsSRBRcvIntPnd(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_SRIF_Msk, CAN0_INTRST_SRIF_Pos)

/**
  * @brief  SRB Receive Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBRcvIntPnd_Clr(__CAN__)              WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_SRIF_Msk)

/**
  * @brief  Judge is ETB Receive Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't ETB Receive Interrupt Pending
  * @retval 1 Is ETB Receive Interrupt Pending
  */
#define __LL_CAN_IsETBRcvIntPnd(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_ERIF_Msk, CAN0_INTRST_ERIF_Pos)

/**
  * @brief  ETB Receive Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBRcvIntPnd_Clr(__CAN__)              WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_ERIF_Msk)

/**
  * @brief  Judge is Error Counter Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Error Counter Interrupt Pending
  * @retval 1 Is Error Counter Interrupt Pending
  */
#define __LL_CAN_IsErrCntIntPnd(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_ECIF_Msk, CAN0_INTRST_ECIF_Pos)

/**
  * @brief  Error Counter Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrCntIntPnd_Clr(__CAN__)              WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_ECIF_Msk)

/**
  * @brief  Judge is Error Passive Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Error Passive Interrupt Pending
  * @retval 1 Is Error Passive Interrupt Pending
  */
#define __LL_CAN_IsErrPassiveIntPnd(__CAN__)            READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EPIF_Msk, CAN0_INTRST_EPIF_Pos)

/**
  * @brief  Error Passive Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrPassiveIntPnd_Clr(__CAN__)          WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_EPIF_Msk)

/**
  * @brief  Judge is Arbitration Lost Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Arbitration Lost Interrupt Pending
  * @retval 1 Is Arbitration Lost Interrupt Pending
  */
#define __LL_CAN_IsArbLostIntPnd(__CAN__)               READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_ALIF_Msk, CAN0_INTRST_ALIF_Pos)

/**
  * @brief  Arbitration Lost Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ArbLostIntPnd_Clr(__CAN__)             WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_ALIF_Msk)

/**
  * @brief  Judge is Bus Error Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Bus Error Interrupt Pending
  * @retval 1 Is Bus Error Interrupt Pending
  */
#define __LL_CAN_IsBusErrIntPnd(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_BEIF_Msk, CAN0_INTRST_BEIF_Pos)

/**
  * @brief  Bus Error Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_BusErrIntPnd_Clr(__CAN__)              WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_BEIF_Msk)

/**
  * @brief  Judge is Receive Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Receive Interrupt Pending
  * @retval 1 Is Receive Interrupt Pending
  */
#define __LL_CAN_IsRxIntPnd(__CAN__)                    READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_RIF_Msk, CAN0_INTRST_RIF_Pos)

/**
  * @brief  Receive Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxIntPnd_Clr(__CAN__)                  WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_RIF_Msk)

/**
  * @brief  Judge is Rx Buffer Overflow Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Rx Buffer Overflow Interrupt Pending
  * @retval 1 Is Rx Buffer Overflow Interrupt Pending
  */
#define __LL_CAN_IsRxOverIntPnd(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_ROIF_Msk, CAN0_INTRST_ROIF_Pos)

/**
  * @brief  Rx Buffer Overflow Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxOverIntPnd_Clr(__CAN__)              WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_ROIF_Msk)

/**
  * @brief  Judge is Rx Buffer Full Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Rx Buffer Full Interrupt Pending
  * @retval 1 Is Rx Buffer Full Interrupt Pending
  */
#define __LL_CAN_IsRxFullIntPnd(__CAN__)                READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_RFIF_Msk, CAN0_INTRST_RFIF_Pos)

/**
  * @brief  Rx Buffer Full Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxFullIntPnd_Clr(__CAN__)              WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_RFIF_Msk)

/**
  * @brief  Judge is Rx Buffer Almost Full Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Rx Buffer Almost Full Interrupt Pending
  * @retval 1 Is Rx Buffer Almost Full Interrupt Pending
  */
#define __LL_CAN_IsRxAlmostFullIntPnd(__CAN__)          READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_RAFIF_Msk, CAN0_INTRST_RAFIF_Pos)

/**
  * @brief  Rx Buffer Almost Full Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_RxAlmostFullIntPnd_Clr(__CAN__)        WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_RAFIF_Msk)

/**
  * @brief  Judge is Transmission Primary Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Transmission Primary Interrupt Pending
  * @retval 1 Is Transmission Primary Interrupt Pending
  */
#define __LL_CAN_IsTxPriIntPnd(__CAN__)                 READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_TPIF_Msk, CAN0_INTRST_TPIF_Pos)

/**
  * @brief  Transmission Primary Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxPriIntPnd_Clr(__CAN__)               WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_TPIF_Msk)

/**
  * @brief  Judge is Transmission Secondary Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Transmission Secondary Interrupt Pending
  * @retval 1 Is Transmission Secondary Interrupt Pending
  */
#define __LL_CAN_IsTxSecIntPnd(__CAN__)                 READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_TSIF_Msk, CAN0_INTRST_TSIF_Pos)

/**
  * @brief  Transmission Secondary Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TxSecIntPnd_Clr(__CAN__)               WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_TSIF_Msk)

/**
  * @brief  Judge is Error Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Error Interrupt Pending
  * @retval 1 Is Error Interrupt Pending
  */
#define __LL_CAN_IsErrIntPnd(__CAN__)                   READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_EIF_Msk, CAN0_INTRST_EIF_Pos)

/**
  * @brief  Error Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ErrIntPnd_Clr(__CAN__)                 WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_EIF_Msk)

/**
  * @brief  Judge is Abort Interrupt Pending or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Isn't Abort Interrupt Pending
  * @retval 1 Is Abort Interrupt Pending
  */
#define __LL_CAN_IsAbortIntPnd(__CAN__)                 READ_BIT_SHIFT((__CAN__)->INTRST, CAN0_INTRST_AIF_Msk, CAN0_INTRST_AIF_Pos)

/**
  * @brief  Abort Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AbortIntPnd_Clr(__CAN__)               WRITE_REG((__CAN__)->INTRST, CAN0_INTRST_AIF_Msk)

/**
  * @brief  Interrupt status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt status
  */
#define __LL_CAN_AllIntPnd_Get(__CAN__)                 READ_REG((__CAN__)->INTRST)

/**
  * @brief  All Interrupt Pending Clear
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AllIntPnd_Clr(__CAN__)                 WRITE_REG((__CAN__)->INTRST, 0xffffffffUL)


/**
  * @brief  Fast speed bit timing segment1 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_BitTimingSeg1_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->BITTIME, CAN0_BITTIME_F_SEG1_Msk, (((val) & 0xfUL) << CAN0_BITTIME_F_SEG1_Pos))

/**
  * @brief  Slow speed synchronization jump width set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_SyncJumpWidth_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->BITTIME, CAN0_BITTIME_S_SJW_Msk, (((val) & 0xfUL) << CAN0_BITTIME_S_SJW_Pos))

/**
  * @brief  Fast speed bit timing segment2 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_BitTimingSeg2_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->BITTIME, CAN0_BITTIME_F_SEG2_Msk, (((val) & 0x7UL) << CAN0_BITTIME_F_SEG2_Pos))

/**
  * @brief  Slow speed bit timing segment2 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_BitTimingSeg2_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->BITTIME, CAN0_BITTIME_S_SEG2_Msk, (((val) & 0x1fUL) << CAN0_BITTIME_S_SEG2_Pos))

/**
  * @brief  Fast speed synchronization jump width set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_SyncJumpWidth_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->BITTIME, CAN0_BITTIME_F_SJW_Msk, (((val) & 0x3UL) << CAN0_BITTIME_F_SJW_Pos))

/**
  * @brief  Slow speed bit timing segment1 set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_BitTimingSeg1_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->BITTIME, CAN0_BITTIME_S_SEG1_Msk, (((val) & 0x3fUL) << CAN0_BITTIME_S_SEG1_Pos))


/**
  * @brief  Transmitter Delay Compensation Enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TransDlyComp_En(__CAN__)               SET_BIT((__CAN__)->PRESC, CAN0_PRESC_TDCEN_Msk)

/**
  * @brief  Transmitter Delay Compensation Disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_TransDlyComp_Dis(__CAN__)              CLEAR_BIT((__CAN__)->PRESC, CAN0_PRESC_TDCEN_Msk)

/**
  * @brief  Secondary Sample Point Offset Set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SecSamplePointOffset_Set(__CAN__, val) \
        MODIFY_REG((__CAN__)->PRESC, CAN0_PRESC_SSPOFF_Msk, (((val) & 0x1fUL) << CAN0_PRESC_SSPOFF_Pos))

/**
  * @brief  Fast speed prescaler set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_FS_Prescaler_Set(__CAN__, val)         \
        MODIFY_REG((__CAN__)->PRESC, CAN0_PRESC_F_PRESC_Msk, (((val) & 0xffUL) << CAN0_PRESC_F_PRESC_Pos))

/**
  * @brief  Slow speed prescaler set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_SS_Prescaler_Set(__CAN__, val)         \
        MODIFY_REG((__CAN__)->PRESC, CAN0_PRESC_S_PRESC_Msk, (((val) & 0xffUL) << CAN0_PRESC_S_PRESC_Pos))


/**
  * @brief  RX error count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return RX error count
  */
#define __LL_CAN_RxErrCnt_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->ERRST, CAN0_ERRST_RECNT_Msk, CAN0_ERRST_RECNT_Pos)

/**
  * @brief  TX error count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX error count
  */
#define __LL_CAN_TxErrCnt_Get(__CAN__)                  READ_BIT_SHIFT((__CAN__)->ERRST, CAN0_ERRST_TECNT_Msk, CAN0_ERRST_TECNT_Pos)

/**
  * @brief  RX and TX error count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return TX error count
  */
#define __LL_CAN_RxTxErrCnt_Get(__CAN__)                READ_BIT_SHIFT((__CAN__)->ERRST, CAN0_ERRST_ECNT_Msk, CAN0_ERRST_ECNT_Pos)

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
#define __LL_CAN_ErrCode_Get(__CAN__)                   READ_BIT_SHIFT((__CAN__)->ERRST, CAN0_ERRST_KOER_Msk, CAN0_ERRST_KOER_Pos)

/**
  * @brief  Arbitration lost capture get
  * @param  __CAN__ Specifies CAN peripheral
  * @return bit position in the frame where the arbitration has been lost
  */
#define __LL_CAN_ArbLostCapture_Get(__CAN__)            READ_BIT_SHIFT((__CAN__)->ERRST, CAN0_ERRST_ALC_Msk, CAN0_ERRST_ALC_Pos)


/**
  * @brief  Data Kind Of Error get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Data Kind Of Error @ref CAN_DatFieldErrETypeDef
  */
#define __LL_CAN_DataErrType_Get(__CAN__)               READ_BIT_SHIFT((__CAN__)->PRTST, CAN0_PRTST_DKOER_Msk, CAN0_PRTST_DKOER_Pos)

/**
  * @brief  Data Kind Of Error Extract
  * @param  __CAN__ Specifies CAN peripheral
  * @param  sta CAN Protocol Status @ref __LL_CAN_ProtStaReg_Read
  * @return Data Kind Of Error @ref CAN_DatFieldErrETypeDef
  */
#define __LL_CAN_DataErrType_Extract(sta)               READ_BIT_SHIFT((uint32_t)sta, CAN0_PRTST_DKOER_Msk, CAN0_PRTST_DKOER_Pos)

/**
  * @brief  CAN RX FD Status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0010b CAN FD Data Frame
  * @retval 0011b CAN FD Accelerated Data Frame
  * @retval 1010b CAN FD Extend Data Frame
  * @retval 1011b CAN FD Extend Accelerated Data Frame
  * @retval x1xxb CAN FD Data Frame Protocol Error
  */
#define __LL_CAN_RxFDDatFrmType_Get(__CAN__)            READ_BIT_SHIFT((__CAN__)->PRTST, CAN0_PRTST_FDSTS_Msk, CAN0_PRTST_FDSTS_Pos)

/**
  * @brief  CAN RX FD Status Extract
  * @param  sta CAN Protocol Status @ref __LL_CAN_ProtStaReg_Read
  * @retval 0010b CAN FD Data Frame
  * @retval 0011b CAN FD Accelerated Data Frame
  * @retval 1010b CAN FD Extend Data Frame
  * @retval 1011b CAN FD Extend Accelerated Data Frame
  * @retval x1xxb CAN FD Data Frame Protocol Error
  */
#define __LL_CAN_RxFDDatFrmType_Extract(sta)            READ_BIT_SHIFT((uint32_t)sta, CAN0_PRTST_FDSTS_Msk, CAN0_PRTST_FDSTS_Pos)

/**
  * @brief  CAN Node Status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN Node Status @ref CAN_NodeStaETypeDef
  */
#define __LL_CAN_NodeSta_Get(__CAN__)                   READ_BIT_SHIFT((__CAN__)->PRTST, CAN0_PRTST_NDSTS_Msk, CAN0_PRTST_NDSTS_Pos)

/**
  * @brief  CAN Node Status Extract
  * @param  __CAN__ Specifies CAN peripheral
  * @param  sta CAN Protocol Status @ref __LL_CAN_ProtStaReg_Read
  * @return CAN Node Status @ref CAN_NodeStaETypeDef
  */
#define __LL_CAN_NodeSta_Extract(sta)                   READ_BIT_SHIFT((uint32_t)sta, CAN0_PRTST_NDSTS_Msk, CAN0_PRTST_NDSTS_Pos)

/**
  * @brief  CAN RX Frame Store Mode get
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN RX Frame Store Mode @ref CAN_FrmStoreModeETypeDef
  */
#define __LL_CAN_RxFrmStoreMode_Get(__CAN__)            READ_BIT_SHIFT((__CAN__)->PRTST, CAN0_PRTST_RBSTS_Msk, CAN0_PRTST_RBSTS_Pos)

/**
  * @brief  CAN RX Frame Store Mode Extract
  * @param  __CAN__ Specifies CAN peripheral
  * @param  sta CAN Protocol Status @ref __LL_CAN_ProtStaReg_Read
  * @return CAN RX Frame Store Mode @ref CAN_FrmStoreModeETypeDef
  */
#define __LL_CAN_RxFrmStoreMode_Extract(sta)            READ_BIT_SHIFT((uint32_t)sta, CAN0_PRTST_RBSTS_Msk, CAN0_PRTST_RBSTS_Pos)

/**
  * @brief  CAN Protocol Status Register read
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN Protocol Status
  */
#define __LL_CAN_ProtStaReg_Read(__CAN__)               READ_REG((__CAN__)->PRTST)


/**
  * @brief  STB Empty Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_STBEmptyIntLine_Set(__CAN__, line)               \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_TEILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_TEILS_Pos))

/**
  * @brief  STB Empty Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_STBEmptyIntLine_Get(__CAN__)                     \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_TEILS_Msk, CAN0_INTRLS_TEILS_Pos)

/**
  * @brief  STB Almost Empty Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_STBAlmostEmptyIntLine_Set(__CAN__, line)         \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_TAEILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_TAEILS_Pos))

/**
  * @brief  STB Almost Empty Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_STBAlmostEmptyIntLine_Get(__CAN__)               \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_TAEILS_Msk, CAN0_INTRLS_TAEILS_Pos)

/**
  * @brief  Priority Message Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PrioMesgIntLine_Set(__CAN__, line)               \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_PMILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_PMILS_Pos))

/**
  * @brief  Priority Message Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PrioMesgIntLine_Get(__CAN__)               \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_PMILS_Msk, CAN0_INTRLS_PMILS_Pos)

/**
  * @brief  Timestamp Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_TimestampIntLine_Set(__CAN__, line)              \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_TSCILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_TSCILS_Pos))

/**
  * @brief  Timestamp Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref 
  */
#define __LL_CAN_TimestampIntLine_Get(__CAN__)                    \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_TSCILS_Msk, CAN0_INTRLS_TSCILS_Pos)

/**
  * @brief  PRB Timeout Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PRBTimeoutIntLine_Set(__CAN__, line)             \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_RTOILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_RTOILS_Pos))

/**
  * @brief  PRB Timeout Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PRBTimeoutIntLine_Get(__CAN__)                   \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_RTOILS_Msk, CAN0_INTRLS_RTOILS_Pos)

/**
  * @brief  SRB Timeout Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_SRBTimeoutIntLine_Set(__CAN__, line)             \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_STOILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_STOILS_Pos))

/**
  * @brief  SRB Timeout Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_SRBTimeoutIntLine_Get(__CAN__)                   \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_STOILS_Msk, CAN0_INTRLS_STOILS_Pos)

/**
  * @brief  ETB Timeout Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ETBTimeoutIntLine_Set(__CAN__, line)             \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_ETOILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_ETOILS_Pos))

/**
  * @brief  ETB Timeout Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ETBTimeoutIntLine_Get(__CAN__)                   \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_ETOILS_Msk, CAN0_INTRLS_ETOILS_Pos)

/**
  * @brief  Continuous Count Timeout Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ContCntTimeoutIntLine_Set(__CAN__, line)         \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_CTOILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_CTOILS_Pos))

/**
  * @brief  Continuous Count Timeout Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ContCntTimeoutIntLine_Get(__CAN__)               \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_CTOILS_Msk, CAN0_INTRLS_CTOILS_Pos)

/**
  * @brief  SRB Overrun Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_SRBOverIntLine_Set(__CAN__, line)                \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_SOILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_SOILS_Pos))

/**
  * @brief  SRB Overrun Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_SRBOverIntLine_Get(__CAN__)                      \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_SOILS_Msk, CAN0_INTRLS_SOILS_Pos)

/**
  * @brief  SRB Full Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_SRBFullIntLine_Set(__CAN__, line)                \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_SFILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_SFILS_Pos))

/**
  * @brief  SRB Full Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_SRBFullIntLine_Get(__CAN__)                      \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_SFILS_Msk, CAN0_INTRLS_SFILS_Pos)

/**
  * @brief  SRB Almost Full Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_SRBAlmostFullIntLine_Set(__CAN__, line)          \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_SAFILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_SAFILS_Pos))

/**
  * @brief  SRB Almost Full Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_SRBAlmostFullIntLine_Get(__CAN__)                \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_SAFILS_Msk, CAN0_INTRLS_SAFILS_Pos)

/**
  * @brief  ETB Overrun Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ETBOverIntLine_Set(__CAN__, line)                \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_EOILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_EOILS_Pos))

/**
  * @brief  ETB Overrun Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ETBOverIntLine_Get(__CAN__)                      \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_EOILS_Msk, CAN0_INTRLS_EOILS_Pos)

/**
  * @brief  ETB Full Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ETBFullIntLine_Set(__CAN__, line)                \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_EFILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_EFILS_Pos))

/**
  * @brief  ETB Full Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ETBFullIntLine_Get(__CAN__)                      \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_EFILS_Msk, CAN0_INTRLS_EFILS_Pos)

/**
  * @brief  ETB Almost Full Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ETBAlmostFullIntLine_Set(__CAN__, line)          \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_EAFILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_EAFILS_Pos))

/**
  * @brief  ETB Almost Full Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ETBAlmostFullIntLine_Get(__CAN__)                \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_EAFILS_Msk, CAN0_INTRLS_EAFILS_Pos)

/**
  * @brief  SRB Receive Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_SRBRxIntLine_Set(__CAN__, line)                  \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_SRILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_SRILS_Pos))

/**
  * @brief  SRB Receive Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef 
  */
#define __LL_CAN_SRBRxIntLine_Get(__CAN__)                        \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_SRILS_Msk, CAN0_INTRLS_SRILS_Pos)

/**
  * @brief  ETB Receive Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ETBRxIntLine_Set(__CAN__, line)                  \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_ERILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_ERILS_Pos))

/**
  * @brief  ETB Receive Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ETBRxIntLine_Get(__CAN__)                        \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_ERILS_Msk, CAN0_INTRLS_ERILS_Pos)

/**
  * @brief  Error Counter Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ErrCntIntLine_Set(__CAN__, line)                 \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_ECILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_ECILS_Pos))

/**
  * @brief  Error Counter Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ErrCntIntLine_Get(__CAN__)                       \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_ECILS_Msk, CAN0_INTRLS_ECILS_Pos)

/**
  * @brief  Error Passive Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ErrPassiveIntLine_Set(__CAN__, line)             \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_EPILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_EPILS_Pos))

/**
  * @brief  Error Passive Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ErrPassiveIntLine_Get(__CAN__)                   \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_EPILS_Msk, CAN0_INTRLS_EPILS_Pos)

/**
  * @brief  Arbitration Lost Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ArbiLostIntLine_Set(__CAN__, line)               \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_ALILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_ALILS_Pos))

/**
  * @brief  Arbitration Lost Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ArbiLostIntLine_Get(__CAN__)                     \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_ALILS_Msk, CAN0_INTRLS_ALILS_Pos)

/**
  * @brief  Bus Error Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_BusErrIntLine_Set(__CAN__, line)                 \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_BEILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_BEILS_Pos))

/**
  * @brief  Bus Error Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_BusErrIntLine_Get(__CAN__)                       \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_BEILS_Msk, CAN0_INTRLS_BEILS_Pos)

/**
  * @brief  PRB Receive Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PRBRxIntLine_Set(__CAN__, line)                  \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_RILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_RILS_Pos))

/**
  * @brief  PRB Receive Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PRBRxIntLine_Get(__CAN__)                        \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_RILS_Msk, CAN0_INTRLS_RILS_Pos)

/**
  * @brief  PRB Overrun Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PRBOverIntLine_Set(__CAN__, line)                \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_ROILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_ROILS_Pos))

/**
  * @brief  PRB Overrun Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PRBOverIntLine_Get(__CAN__)                      \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_ROILS_Msk, CAN0_INTRLS_ROILS_Pos)

/**
  * @brief  PRB Full Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PRBFullIntLine_Set(__CAN__, line)                \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_RFILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_RFILS_Pos))

/**
  * @brief  PRB Full Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PRBFullIntLine_Get(__CAN__)                      \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_RFILS_Msk, CAN0_INTRLS_RFILS_Pos)

/**
  * @brief  PRB Almost Full Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PRBAlmostIntLine_Set(__CAN__, line)              \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_RAFILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_RAFILS_Pos))

/**
  * @brief  PRB Almost Full Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PRBAlmostIntLine_Get(__CAN__)                    \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_RAFILS_Msk, CAN0_INTRLS_RAFILS_Pos)

/**
  * @brief  PTB Transmission Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_PTBTxIntLine_Set(__CAN__, line)                  \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_TPILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_TPILS_Pos))

/**
  * @brief  PTB Transmission Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_PTBTxIntLine_Get(__CAN__)                        \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_TPILS_Msk, CAN0_INTRLS_TPILS_Pos)

/**
  * @brief  STB Transmission Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_STBTxIntLine_Set(__CAN__, line)                  \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_TSILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_TSILS_Pos))

/**
  * @brief  STB Transmission Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_STBTxIntLine_Get(__CAN__)                        \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_TSILS_Msk, CAN0_INTRLS_TSILS_Pos)

/**
  * @brief  Error Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_ErrIntLine_Set(__CAN__, line)                    \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_EILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_EILS_Pos))

/**
  * @brief  Error Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_ErrIntLine_Get(__CAN__)                          \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_EILS_Msk, CAN0_INTRLS_EILS_Pos)

/**
  * @brief  Abort Interrupt Line Select set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  line Interrupt Line @ref CAN_IntLineETypeDef
  * @return None
  */
#define __LL_CAN_AbortIntLine_Set(__CAN__, line)                  \
        MODIFY_REG((__CAN__)->INTRLS, CAN0_INTRLS_AILS_Msk, (((line) & 0x1UL) << CAN0_INTRLS_AILS_Pos))

/**
  * @brief  Abort Interrupt Line Select get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Interrupt Line @ref CAN_IntLineETypeDef
  */
#define __LL_CAN_AbortIntLine_Get(__CAN__)                        \
        READ_BIT_SHIFT((__CAN__)->INTRLS, CAN0_INTRLS_AILS_Msk, CAN0_INTRLS_AILS_Pos)

/**
  * @brief  All Interrupt Line Select
  * @param  __CAN__ Specifies CAN peripheral
  * @param  mask Interrupt Line Select Bit
  * @return None
  */
#define __LL_CAN_AllIntLine_Select(__CAN__, mask)       MODIFY_REG((__CAN__)->INTRLS, 0xfffc3fffUL, (mask & 0xfffc3fffUL)) 

/**
  * @brief  All Interrupt Line Set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AllIntLine_Set(__CAN__)                MODIFY_REG((__CAN__)->INTRLS, 0xfffc3fffUL, 0xfffc3fffUL)

/**
  * @brief  All Interrupt Line Reset
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AllIntLine_Clr(__CAN__)                MODIFY_REG((__CAN__)->INTRLS, 0xfffc3fffUL, 0x00000000UL)

/**
  * @brief  All Interrupt Line Get
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AllIntLine_Get(__CAN__)                (READ_REG((__CAN__)->INTRLS) & 0xfffc3fffUL)


/**
  * @brief  Standard Remote Frames Reject enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_StdRmtFrmRjct_En(__CAN__)              SET_BIT((__CAN__)->GFCR, CAN0_GFCR_SRFR_Msk)

/**
  * @brief  Standard Remote Frames Reject disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_StdRmtFrmRjct_Dis(__CAN__)             CLEAR_BIT((__CAN__)->GFCR, CAN0_GFCR_SRFR_Msk)

/**
  * @brief  Judge is Standard Remote Frames Reject enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Standard Remote Frames Reject disable
  * @retval 1 Standard Remote Frames Reject enable
  */
#define __LL_CAN_IsStdRmtFrmRjctEn(__CAN__)             READ_BIT_SHIFT((__CAN__)->GFCR, CAN0_GFCR_SRFR_Msk, CAN0_GFCR_SRFR_Pos)

/**
  * @brief  Extended Remote Frames Reject enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ExtRmtFrmRjct_En(__CAN__)              SET_BIT((__CAN__)->GFCR, CAN0_GFCR_ERFR_Msk)

/**
  * @brief  Extended Remote Frames Reject disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ExtRmtFrmRjct_Dis(__CAN__)             CLEAR_BIT((__CAN__)->GFCR, CAN0_GFCR_ERFR_Msk)

/**
  * @brief  Judge is Extended Remote Frames Reject enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Extended Remote Frames Reject disable
  * @retval 1 Extended Remote Frames Reject enable
  */
#define __LL_CAN_IsExtRmtFrmRjctEn(__CAN__)             READ_BIT_SHIFT((__CAN__)->GFCR, CAN0_GFCR_ERFR_Msk, CAN0_GFCR_ERFR_Pos)

/**
  * @brief  PRB Working Mode set
  * @param  __CAN__ Specifies CAN peripheral
  * @param mode Working Mode @ref CAN_RxBufWorkModeETypeDef
  * @return None
  */
#define __LL_CAN_PRBWorkMode_Set(__CAN__, mode)         \
        MODIFY_REG((__CAN__)->GFCR, CAN0_GFCR_PRBM_Msk, (((mode) & 0x1UL) << CAN0_GFCR_PRBM_Pos))

/**
  * @brief  PRB Working Mode Cover set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBWorkModeCover_Set(__CAN__)          CLEAR_BIT((__CAN__)->GFCR, CAN0_GFCR_PRBM_Msk)

/**
  * @brief  PRB Working Mode Block set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBWorkModeBlock_Set(__CAN__)          SET_BIT((__CAN__)->GFCR, CAN0_GFCR_PRBM_Msk)

/**
  * @brief  PRB Working Mode get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Working Mode @ref CAN_RxBufWorkModeETypeDef
  */
#define __LL_CAN_PRBWorkMode_Get(__CAN__)               \
        READ_BIT_SHIFT((__CAN__)->GFCR, CAN0_GFCR_PRBM_Msk, CAN0_GFCR_PRBM_Pos)

/**
  * @brief  SRB Working Mode set
  * @param  __CAN__ Specifies CAN peripheral
  * @param mode Working Mode @ref CAN_RxBufWorkModeETypeDef
  * @return None
  */
#define __LL_CAN_SRBWorkMode_Set(__CAN__, mode)         \
        MODIFY_REG((__CAN__)->GFCR, CAN0_GFCR_SRBM_Msk, (((mode) & 0x1UL) << CAN0_GFCR_SRBM_Pos))

/**
  * @brief  SRB Working Mode Cover set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBWorkModeCover_Set(__CAN__)          CLEAR_BIT((__CAN__)->GFCR, CAN0_GFCR_SRBM_Msk)

/**
  * @brief  SRB Working Mode Block set
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBWorkModeBlock_Set(__CAN__)          SET_BIT((__CAN__)->GFCR, CAN0_GFCR_SRBM_Msk)

/**
  * @brief  SRB Working Mode get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Working Mode @ref CAN_RxBufWorkModeETypeDef
  */
#define __LL_CAN_SRBWorkMode_Get(__CAN__)               \
        READ_BIT_SHIFT((__CAN__)->GFCR, CAN0_GFCR_SRBM_Msk, CAN0_GFCR_SRBM_Pos)

/**
  * @brief  Extended ID Mask set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  mask Extended ID Mask
  * @return None
  */
#define __LL_CAN_ExtIdMask_Set(__CAN__, mask)           \
        MODIFY_REG((__CAN__)->EMCR, CAN0_EMCR_EIDM_Msk, (((mask) & 0x1fffffffUL) << CAN0_EMCR_EIDM_Pos))

/**
  * @brief  Extended ID Mask get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Extended ID Mask
  */
#define __LL_CAN_ExtIdMask_Get(__CAN__)           \
        READ_BIT_SHIFT((__CAN__)->EMCR, CAN0_EMCR_EIDM_Msk, CAN0_EMCR_EIDM_Pos)


/**
  * @brief  Priority Message Acceptance Status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Acceptance filter sequence number
  */
#define __LL_CAN_PrioMesgAcceptSta_Get(__CAN__)         READ_BIT_SHIFT((__CAN__)->PMST, CAN0_PMST_PMAS_Msk, CAN0_PMST_PMAS_Pos)

/**
  * @brief  Priority Message Buffer Status get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Priority Message Buffer Status @ref CAN_FrmStoreModeETypeDef
  */
#define __LL_CAN_PrioMesgBufSta_Get(__CAN__)            READ_BIT_SHIFT((__CAN__)->PMST, CAN0_PMST_PMBS_Msk, CAN0_PMST_PMBS_Pos)

/**
  * @brief  Priority Message IDE Status get
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Priority Message is Standard Frame
  * @retval 1 Priority Message is Extended Frame
  */
#define __LL_CAN_PrioMesgIDESta_Get(__CAN__)            READ_BIT_SHIFT((__CAN__)->PMST, CAN0_PMST_PMIS_Msk, CAN0_PMST_PMIS_Pos)


/**
  * @brief  Acceptance filter enable
  * @param  __CAN__ Specifies CAN peripheral
  * @param  fil_num Acceptance filter slot number
  * @note   fil_num value range [0, 15]
  * @return None
  */
#define __LL_CAN_AcceptFil_En(__CAN__, fil_num)         SET_BIT((__CAN__)->ACFEN, BIT(fil_num))

/**
  * @brief  Acceptance filter disable
  * @param  __CAN__ Specifies CAN peripheral
  * @param  fil_num Acceptance filter slot number
  * @note   fil_num value range [0, 15]
  * @return None
  */
#define __LL_CAN_AcceptFil_Dis(__CAN__, fil_num)        CLEAR_BIT((__CAN__)->ACFEN, BIT(fil_num))


/**
  * @brief  Acceptance filter content select mask
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilContentSel_Mask(__CAN__)      SET_BIT((__CAN__)->ACFCTRL, CAN0_ACFCTRL_SELMASK_Msk)

/**
  * @brief  Acceptance filter content select code
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilContentSel_Code(__CAN__)      CLEAR_BIT((__CAN__)->ACFCTRL, CAN0_ACFCTRL_SELMASK_Msk)

/**
  * @brief  Acceptance filter address set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_AcceptFilAddr_Set(__CAN__, val)        \
        MODIFY_REG((__CAN__)->ACFCTRL, CAN0_ACFCTRL_ACFADR_Msk, (((val) & 0xfUL) << CAN0_ACFCTRL_ACFADR_Pos))

/**
  * @brief  Acceptance filter address read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Acceptance filter address
  */
#define __LL_CAN_AcceptFilAddr_Read(__CAN__)         	READ_BIT_SHIFT((__CAN__)->ACFCTRL, CAN0_ACFCTRL_ACFADR_Msk, CAN0_ACFCTRL_ACFADR_Pos)


/**
  * @brief  Acceptance mask IDE bit check enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDE_En(__CAN__)           SET_BIT((__CAN__)->ACF, CAN0_ACF_AIDEE_Msk)

/**
  * @brief  Acceptance mask IDE bit check disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDE_Dis(__CAN__)          CLEAR_BIT((__CAN__)->ACF, CAN0_ACF_AIDEE_Msk)

/**
  * @brief  Acceptance filter accepts only extended frames
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDESel_Ext(__CAN__)       SET_BIT((__CAN__)->ACF, CAN0_ACF_AIDE_Msk)

/**
  * @brief  Acceptance filter accepts only standard frames
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_AcceptFilMaskIDESel_Std(__CAN__)       CLEAR_BIT((__CAN__)->ACF, CAN0_ACF_AIDE_Msk)

/**
  * @brief  Acceptance filter Rx frame type set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  frm_type Rx frame type
  * @return None
  */
#define __LL_CAN_AcceptFilRxFrm_Set(__CAN__, frm_type)  \
        MODIFY_REG((__CAN__)->ACF, CAN0_ACF_AIDEE_Msk | CAN0_ACF_AIDE_Msk, ((frm_type) & 0x3) << CAN0_ACF_AIDE_Pos)

/**
  * @brief  Acceptance filter code or mask set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val set value
  * @return None
  */
#define __LL_CAN_AcceptFilCodeOrMaskVal_Set(__CAN__, val)   \
        MODIFY_REG((__CAN__)->ACF, CAN0_ACF_ACF_X_Msk, (((val) & 0x1fffffffUL) << CAN0_ACF_ACF_X_Pos))


/**
  * @brief  CAN Acceptance Mode set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  mode CAN Acceptance Mode @ref CAN_AcceptModeETypeDef
  * @return None
  */
#define __LL_CAN_AcceptMode_Set(__CAN__, mode)          \
        MODIFY_REG((__CAN__)->ACFE, CAN0_ACFE_ACF_M_Msk, (((mode) & 0x0fUL) << CAN0_ACFE_ACF_M_Pos))

/**
  * @brief  CAN Acceptance Mode get
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN Acceptance Mode @ref CAN_AcceptModeETypeDef
  */
#define __LL_CAN_AcceptMode_Get(__CAN__)                \
        READ_BIT_SHIFT((__CAN__)->ACFE, CAN0_ACFE_ACF_M_Msk, CAN0_ACFE_ACF_M_Pos)

/**
  * @brief  CAN Acceptance Control set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  ctrl CAN Acceptance Control @ref CAN_AcceptCtrlETypeDef
  * @return None
  */
#define __LL_CAN_AcceptCtrl_Set(__CAN__, ctrl)          \
        MODIFY_REG((__CAN__)->ACFE, CAN0_ACFE_ACF_C_Msk, (((ctrl) & 0x0fUL) << CAN0_ACFE_ACF_C_Pos))

/**
  * @brief  CAN Acceptance Control get
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN Acceptance Control @ref CAN_AcceptCtrlETypeDef
  */
#define __LL_CAN_AcceptCtrl_Get(__CAN__)                \
        READ_BIT_SHIFT((__CAN__)->ACFE, CAN0_ACFE_ACF_C_Msk, CAN0_ACFE_ACF_C_Pos)


/**
  * @brief  Rx Buffer ID Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Read Value
  */
#define __LL_CAN_RxBufReg_ID_Read(__CAN__)              READ_REG((__CAN__)->RBUFID)


/**
  * @brief  Rx Buffer Control Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Read Value
  */
#define __LL_CAN_RxBufReg_Ctrl_Read(__CAN__)            READ_REG((__CAN__)->RBUFCR)


/**
  * @brief  Rx Buffer Data Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @param  num Data Register Number range [0, 15]
  * @return Read Value
  */
#define __LL_CAN_RxBufReg_Data_Read(__CAN__, num)       READ_REG((__CAN__)->RBUFDT[((uint32_t)(num) % 16)])


/**
  * @brief  Tx Buffer ID Register Write
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val Write Value
  * @return None
  */
#define __LL_CAN_TxBufReg_ID_Write(__CAN__, val)        WRITE_REG((__CAN__)->TBUFID, val)


/**
  * @brief  Tx Buffer Control Register Write
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val Write Value
  * @return None
  */
#define __LL_CAN_TxBufReg_Ctrl_Write(__CAN__, val)      WRITE_REG((__CAN__)->TBUFCR, val)


/**
  * @brief  Tx Buffer Data Register Write
  * @param  __CAN__ Specifies CAN peripheral
  * @param  num Data Register Number range [0, 15]
  * @param  val Write Value
  * @return None
  */
#define __LL_CAN_TxBufReg_Data_Write(__CAN__, num, val) WRITE_REG((__CAN__)->TBUFDT[((uint32_t)(num) % 16)], val)


/**
  * @brief  ETB Buffer ID Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Read Value
  */
#define __LL_CAN_ETBBufReg_ID_Read(__CAN__)             READ_REG((__CAN__)->EBUFID)


/**
  * @brief  ETB Buffer Data Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Read Value
  */
#define __LL_CAN_ETBBufReg_Data_Read(__CAN__)           READ_REG((__CAN__)->EBUFDT)


/**
  * @brief  SRB Buffer ID Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Read Value
  */
#define __LL_CAN_SRBBufReg_ID_Read(__CAN__)             READ_REG((__CAN__)->SBUFID)


/**
  * @brief  SRB Buffer Control Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @return Read Value
  */
#define __LL_CAN_SRBBufReg_Ctrl_Read(__CAN__)           READ_REG((__CAN__)->SBUFCR)


/**
  * @brief  SRB Buffer Data Register Read
  * @param  __CAN__ Specifies CAN peripheral
  * @param  num Data Register Number range [0, 15]
  * @return Read Value
  */
#define __LL_CAN_SRBBufReg_Data_Read(__CAN__, num)      READ_REG((__CAN__)->SBUFDT[((uint32_t)(num) % 16)])


/**
  * @brief  Timestamp Prescaler set
  * @note   The actual value is equal to the configured value +1
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val Timestamp Prescaler
  * @return None
  */
#define __LL_CAN_TimestampPrescaler_Set(__CAN__, val)   \
        MODIFY_REG((__CAN__)->TSCR, CAN0_TSCR_TSP_Msk, (((val) & 0x0fUL) << CAN0_TSCR_TSP_Pos))

/**
  * @brief  Timestamp Prescaler get
  * @note   The actual value is equal to the configured value +1
  * @param  __CAN__ Specifies CAN peripheral
  * @return Timestamp Prescaler
  */
#define __LL_CAN_TimestampPrescaler_Get(__CAN__)       \
        READ_BIT_SHIFT((__CAN__)->TSCR, CAN0_TSCR_TSP_Msk, CAN0_TSCR_TSP_Pos)

/**
  * @brief  Timestamp Timebase set
  * @param  __CAN__ Specifies CAN peripheral
  * @param  tb Timestamp Timebase @ref CAN_TimestampTimebaseETypeDef
  * @return None
  */
#define __LL_CAN_TimestampTimebase_Set(__CAN__, tb)     \
        MODIFY_REG((__CAN__)->TSCR, CAN0_TSCR_TSS_Msk, (((tb) & 0x0fUL) << CAN0_TSCR_TSS_Pos))

/**
  * @brief  Timestamp Timebase get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Timestamp Timebase @ref CAN_TimestampTimebaseETypeDef
  */
#define __LL_CAN_TimestampTimebase_Get(__CAN__)        \
        READ_BIT_SHIFT((__CAN__)->TSCR, CAN0_TSCR_TSS_Msk, CAN0_TSCR_TSS_Pos)


/**
  * @brief  Timestamp Count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Timestamp Count
  */
#define __LL_CAN_TimestampCnt_Get(__CAN__)             \
        READ_BIT_SHIFT((__CAN__)->TSC, CAN0_TSC_TSC_Msk, CAN0_TSC_TSC_Pos)


/**
  * @brief  PRB Timeout enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBTimeout_En(__CAN__)                 SET_BIT((__CAN__)->RTOP, CAN0_RTOP_RTOE_Msk)

/**
  * @brief  PRB Timeout disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_PRBTimeout_Dis(__CAN__)                CLEAR_BIT((__CAN__)->RTOP, CAN0_RTOP_RTOE_Msk)

/**
  * @brief  Judge is PRB Timeout enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 PRB Timeout disable
  * @retval 1 PRB Timeout enable
  */
#define __LL_CAN_IsPRBTimeoutEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->RTOP, CAN0_RTOP_RTOE_Msk, CAN0_RTOP_RTOE_Pos)

/**
  * @brief  PRB Timeout Period set
  * @note   
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val PRB Timeout Period
  * @return None
  */
#define __LL_CAN_PRBTimeoutPeriod_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->RTOP, CAN0_RTOP_RTOP_Msk, (((val) & 0xffffUL) << CAN0_RTOP_RTOP_Pos))

/**
  * @brief  PRB Timeout Period get
  * @param  __CAN__ Specifies CAN peripheral
  * @return PRB Timeout Period
  */
#define __LL_CAN_PRBTimeoutPeriod_Get(__CAN__)          \
        READ_BIT_SHIFT((__CAN__)->RTOP, CAN0_RTOP_RTOP_Msk, CAN0_RTOP_RTOP_Pos)


/**
  * @brief  PRB Timeout Count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return PRB Timeout Count
  */
#define __LL_CAN_PRBTimeoutCnt_Get(__CAN__)             \
        READ_BIT_SHIFT((__CAN__)->RTOC, CAN0_RTOC_RTOC_Msk, CAN0_RTOC_RTOC_Pos)


/**
  * @brief  SRB Timeout enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBTimeout_En(__CAN__)                 SET_BIT((__CAN__)->STOP, CAN0_STOP_STOE_Msk)

/**
  * @brief  SRB Timeout disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_SRBTimeout_Dis(__CAN__)                CLEAR_BIT((__CAN__)->STOP, CAN0_STOP_STOE_Msk)

/**
  * @brief  Judge is SRB Timeout enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 SRB Timeout disable
  * @retval 1 SRB Timeout enable
  */
#define __LL_CAN_IsSRBTimeoutEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->STOP, CAN0_STOP_STOE_Msk, CAN0_STOP_STOE_Pos)

/**
  * @brief  SRB Timeout Period set
  * @note   
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val SRB Timeout Period
  * @return None
  */
#define __LL_CAN_SRBTimeoutPeriod_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->STOP, CAN0_STOP_STOP_Msk, (((val) & 0xffffUL) << CAN0_STOP_STOP_Pos))

/**
  * @brief  SRB Timeout Period get
  * @param  __CAN__ Specifies CAN peripheral
  * @return SRB Timeout Period
  */
#define __LL_CAN_SRBTimeoutPeriod_Get(__CAN__)          \
        READ_BIT_SHIFT((__CAN__)->STOP, CAN0_STOP_STOP_Msk, CAN0_STOP_STOP_Pos)


/**
  * @brief  SRB Timeout Count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return SRB Timeout Count
  */
#define __LL_CAN_SRBTimeoutCnt_Get(__CAN__)             \
        READ_BIT_SHIFT((__CAN__)->STOC, CAN0_STOC_STOC_Msk, CAN0_STOC_STOC_Pos)


/**
  * @brief  ETB Timeout enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBTimeout_En(__CAN__)                 SET_BIT((__CAN__)->ETOP, CAN0_ETOP_ETOE_Msk)

/**
  * @brief  ETB Timeout disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ETBTimeout_Dis(__CAN__)                CLEAR_BIT((__CAN__)->ETOP, CAN0_ETOP_ETOE_Msk)

/**
  * @brief  Judge is ETB Timeout enable or not
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 ETB Timeout disable
  * @retval 1 ETB Timeout enable
  */
#define __LL_CAN_IsETBTimeoutEn(__CAN__)                READ_BIT_SHIFT((__CAN__)->ETOP, CAN0_ETOP_ETOE_Msk, CAN0_ETOP_ETOE_Pos)

/**
  * @brief  ETB Timeout Period set
  * @note   
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val ETB Timeout Period
  * @return None
  */
#define __LL_CAN_ETBTimeoutPeriod_Set(__CAN__, val)     \
        MODIFY_REG((__CAN__)->ETOP, CAN0_ETOP_ETOP_Msk, (((val) & 0xffffUL) << CAN0_ETOP_ETOP_Pos))

/**
  * @brief  ETB Timeout Period get
  * @param  __CAN__ Specifies CAN peripheral
  * @return ETB Timeout Period
  */
#define __LL_CAN_ETBTimeoutPeriod_Get(__CAN__)          \
        READ_BIT_SHIFT((__CAN__)->ETOP, CAN0_ETOP_ETOP_Msk, CAN0_ETOP_ETOP_Pos)


/**
  * @brief  ETB Timeout Count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return ETB Timeout Count
  */
#define __LL_CAN_ETBTimeoutCnt_Get(__CAN__)             \
        READ_BIT_SHIFT((__CAN__)->ETOC, CAN0_ETOC_ETOC_Msk, CAN0_ETOC_ETOC_Pos)


/**
  * @brief  Continuous Count Timeout enable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ContCntTimeout_En(__CAN__)             SET_BIT((__CAN__)->CTOP, CAN0_CTOP_CTOE_Msk)

/**
  * @brief  Continuous Count Timeout disable
  * @param  __CAN__ Specifies CAN peripheral
  * @return None
  */
#define __LL_CAN_ContCntTimeout_Dis(__CAN__)            CLEAR_BIT((__CAN__)->CTOP, CAN0_CTOP_CTOE_Msk)

/**
  * @brief  Continuous Count Timeout enable
  * @param  __CAN__ Specifies CAN peripheral
  * @retval 0 Continuous Count Timeout disable
  * @retval 1 Continuous Count Timeout enable
  */
#define __LL_CAN_IsContCntTimeoutEn(__CAN__)            READ_BIT_SHIFT((__CAN__)->CTOP, CAN0_CTOP_CTOE_Msk, CAN0_CTOP_CTOE_Pos)

/**
  * @brief  Continuous Timeout Period set
  * @note   
  * @param  __CAN__ Specifies CAN peripheral
  * @param  val Continuous Timeout Period
  * @return None
  */
#define __LL_CAN_ContTimeoutPeriod_Set(__CAN__, val)    \
        MODIFY_REG((__CAN__)->CTOP, CAN0_CTOP_CTOP_Msk, (((val) & 0xffffUL) << CAN0_CTOP_CTOP_Pos))

/**
  * @brief  Continuous Timeout Period get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Continuous Timeout Period
  */
#define __LL_CAN_ContTimeoutPeriod_Get(__CAN__)         \
        READ_BIT_SHIFT((__CAN__)->CTOP, CAN0_CTOP_CTOP_Msk, CAN0_CTOP_CTOP_Pos)


/**
  * @brief  Continuous Timeout Count get
  * @param  __CAN__ Specifies CAN peripheral
  * @return Continuous Timeout Count
  */
#define __LL_CAN_ContTimeoutCnt_Get(__CAN__)            \
        READ_BIT_SHIFT((__CAN__)->CTOP, CAN0_CTOC_CTOC_Msk, CAN0_CTOC_CTOC_Pos)


/**
  * @brief CAN frame ID format to 11 bits
  */
#define __LL_CAN_FrameIDFormat_11Bits(n)                ((n) & 0x7FFUL)

/**
  * @brief CAN frame ID format to 29 bits
  */
#define __LL_CAN_FrameIDFormat_29Bits(n)                ((n) & 0x1FFFFFFFUL)


/**
  * @brief CAN TxFIFO Size Get
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN TxFIFO Size in Byte Unit
  */
#define __LL_CAN_TxFIFOSize_Get(__CAN__)                (sizeof((__CAN__)->TBUFDT))

/**
  * @brief CAN RxFIFO Size Get
  * @param  __CAN__ Specifies CAN peripheral
  * @return CAN RxFIFO Size in Byte Unit
  */
#define __LL_CAN_RxFIFOSize_Get(__CAN__)                (sizeof((__CAN__)->RBUFDT))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Types CAN LL Exported Types
  * @brief    CAN LL Exported Types
  * @{
  */

/**
  * @brief CAN Uer callback function type definition
  */
typedef void (*CAN_UserCallback)(void);

/**
  * @brief CAN Instance Definition
  */
typedef enum {
    CAN_INSTANCE_0 = 0,         /*!< CAN Instance 0         */
    CAN_INSTANCE_1,             /*!< CAN Instance 1         */
    CAN_INSTANCE_NUMS,          /*!< CAN Instance Numbers   */
} CAN_InstanceETypeDef;

/**
  * @brief CAN State definition
  */
typedef enum {
    CAN_STATE_RESET = 0,        /*!< Peripheral not Initialized                         */
    CAN_STATE_READY,            /*!< Peripheral Initialized and ready for use           */
    CAN_STATE_BUSY,             /*!< An internal process is ongoing                     */
    CAN_STATE_BUSY_TX,          /*!< Data Transmission process is ongoing               */
    CAN_STATE_BUSY_RX,          /*!< Data Reception process is ongoing                  */
    CAN_STATE_ABORT,            /*!< CAN Abort state                                    */
    CAN_STATE_ERROR,            /*!< CAN Error state                                    */
} CAN_StateETypeDef;

/**
  * @brief CAN Rx Receive Multiplexer definition
  */
typedef enum {
    CAN_RX_MUXSEL_DISABLE = 0,      /*!< CAN RX Receive Multiplexer Disabled:
                                            For CAN0 : CAN0_RX used as the receive signal source.
                                            For CAN1 : CAN1_RX used as the receive signal source.   */
    CAN_RX_MUXSEL_ENABLE,           /*!< CAN RX Receive Multiplexer Enabled:
                                            For CAN0 : CAN1_RX used as the receive signal source.
                                            For CAN1 : CAN0_RX used as the receive signal source.
                                         Note: When CAN is configured in listen-only mode(LOM=1), the CAN RX Receive Multiplexer can be enabled.*/
} CAN_RxMuxSelETypeDef;

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
    CAN_ACCEPT_FILT_SLOT_0 = 0,     /*!< CAN acceptance filter slot 0       */
    CAN_ACCEPT_FILT_SLOT_1,         /*!< CAN acceptance filter slot 1       */
    CAN_ACCEPT_FILT_SLOT_2,         /*!< CAN acceptance filter slot 2       */
    CAN_ACCEPT_FILT_SLOT_3,         /*!< CAN acceptance filter slot 3       */
    CAN_ACCEPT_FILT_SLOT_4,         /*!< CAN acceptance filter slot 4       */
    CAN_ACCEPT_FILT_SLOT_5,         /*!< CAN acceptance filter slot 5       */
    CAN_ACCEPT_FILT_SLOT_6,         /*!< CAN acceptance filter slot 6       */
    CAN_ACCEPT_FILT_SLOT_7,         /*!< CAN acceptance filter slot 7       */
    CAN_ACCEPT_FILT_SLOT_8,         /*!< CAN acceptance filter slot 8       */
    CAN_ACCEPT_FILT_SLOT_9,         /*!< CAN acceptance filter slot 9       */
    CAN_ACCEPT_FILT_SLOT_10,        /*!< CAN acceptance filter slot 10      */
    CAN_ACCEPT_FILT_SLOT_11,        /*!< CAN acceptance filter slot 11      */
    CAN_ACCEPT_FILT_SLOT_12,        /*!< CAN acceptance filter slot 12      */
    CAN_ACCEPT_FILT_SLOT_13,        /*!< CAN acceptance filter slot 13      */
    CAN_ACCEPT_FILT_SLOT_14,        /*!< CAN acceptance filter slot 14      */
    CAN_ACCEPT_FILT_SLOT_15,        /*!< CAN acceptance filter slot 15      */
    CAN_ACCEPT_FILT_SLOT_NUMS,      /*!< CAN acceptance filter slot Numbers */
} CAN_AcceptFilSlotETypeDef;

/**
  * @brief CAN acceptance filter Rx frame type definition.
  */
typedef enum {
    CAN_ACCEPT_FILT_FRM_STD_EXT = 0,/*!< CAN acceptance filter Rx frame type Standard and Extend    */
    CAN_ACCEPT_FILT_FRM_STD     = 2,/*!< CAN acceptance filter Rx frame type Standard               */
    CAN_ACCEPT_FILT_FRM_EXT,        /*!< CAN acceptance filter Rx frame type Extend                 */
} CAN_AcceptFilRxFrmETypeDef;

/**
  * @brief CAN RX buffer almost full warnning limit definition
  */
typedef enum {
    CAN_RX_ALMOST_FULL_LIMIT_0 = 0, /*!< CAN RX buffer almost full warnning limit: 0 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_1,     /*!< CAN RX buffer almost full warnning limit: 1 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_2,     /*!< CAN RX buffer almost full warnning limit: 2 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_3,     /*!< CAN RX buffer almost full warnning limit: 3 Frame   */

    //Reserved, the following enumerated values do not take effect
    CAN_RX_ALMOST_FULL_LIMIT_4,     /*!< CAN RX buffer almost full warnning limit: 4 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_5,     /*!< CAN RX buffer almost full warnning limit: 5 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_6,     /*!< CAN RX buffer almost full warnning limit: 6 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_7,     /*!< CAN RX buffer almost full warnning limit: 7 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_8,     /*!< CAN RX buffer almost full warnning limit: 8 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_9,     /*!< CAN RX buffer almost full warnning limit: 9 Frame   */
    CAN_RX_ALMOST_FULL_LIMIT_10,    /*!< CAN RX buffer almost full warnning limit: 10 Frame  */
    CAN_RX_ALMOST_FULL_LIMIT_11,    /*!< CAN RX buffer almost full warnning limit: 11 Frame  */
    CAN_RX_ALMOST_FULL_LIMIT_12,    /*!< CAN RX buffer almost full warnning limit: 12 Frame  */
    CAN_RX_ALMOST_FULL_LIMIT_13,    /*!< CAN RX buffer almost full warnning limit: 13 Frame  */
    CAN_RX_ALMOST_FULL_LIMIT_14,    /*!< CAN RX buffer almost full warnning limit: 14 Frame  */
    CAN_RX_ALMOST_FULL_LIMIT_15,    /*!< CAN RX buffer almost full warnning limit: 15 Frame  */
} CAN_RxAlmostFullLimitETypeDef;

/**
  * @brief CAN buffer almost full warnning limit definition
  */
typedef enum {
    CAN_BUF_ALMOST_FULL_LIMIT_0 = 0,    /*!< CAN buffer almost full warnning limit: 0 Frame */
    CAN_BUF_ALMOST_FULL_LIMIT_1,        /*!< CAN buffer almost full warnning limit: 1 Frame */
    CAN_BUF_ALMOST_FULL_LIMIT_2,        /*!< CAN buffer almost full warnning limit: 2 Frame */
    CAN_BUF_ALMOST_FULL_LIMIT_3,        /*!< CAN buffer almost full warnning limit: 3 Frame */
    CAN_BUF_ALMOST_FULL_LIMIT_ENUM_END, /*!< CAN buffer almost full warnning limit enum end */
} CAN_BufAlmostFullLimitETypeDef;

/**
  * @brief CAN buffer almost empty warnning limit definition
  */
typedef enum {
    CAN_BUF_ALMOST_EMPTY_LIMIT_0 = 0,    /*!< CAN buffer almost empty warnning limit: 0 Frame */
    CAN_BUF_ALMOST_EMPTY_LIMIT_1,        /*!< CAN buffer almost empty warnning limit: 1 Frame */
    CAN_BUF_ALMOST_EMPTY_LIMIT_2,        /*!< CAN buffer almost empty warnning limit: 2 Frame */
    CAN_BUF_ALMOST_EMPTY_LIMIT_3,        /*!< CAN buffer almost empty warnning limit: 3 Frame */
    CAN_BUF_ALMOST_EMPTY_LIMIT_ENUM_END, /*!< CAN buffer almost empty warnning limit enum end */
} CAN_BufAlmostEmptyLimitETypeDef;

/**
  * @brief CAN programmable error warning limit definition
  */
typedef enum {
    CAN_ERR_WARN_LIMIT_8 = 0,       /*!< CAN programmable error warning limit: 8 bytes      */
    CAN_ERR_WARN_LIMIT_16,          /*!< CAN programmable error warning limit: 16 bytes     */
    CAN_ERR_WARN_LIMIT_24,          /*!< CAN programmable error warning limit: 24 bytes     */
    CAN_ERR_WARN_LIMIT_32,          /*!< CAN programmable error warning limit: 32 bytes     */
    CAN_ERR_WARN_LIMIT_40,          /*!< CAN programmable error warning limit: 40 bytes     */
    CAN_ERR_WARN_LIMIT_48,          /*!< CAN programmable error warning limit: 48 bytes     */
    CAN_ERR_WARN_LIMIT_56,          /*!< CAN programmable error warning limit: 56 bytes     */
    CAN_ERR_WARN_LIMIT_64,          /*!< CAN programmable error warning limit: 64 bytes     */
    CAN_ERR_WARN_LIMIT_72,          /*!< CAN programmable error warning limit: 72 bytes     */
    CAN_ERR_WARN_LIMIT_80,          /*!< CAN programmable error warning limit: 80 bytes     */
    CAN_ERR_WARN_LIMIT_88,          /*!< CAN programmable error warning limit: 88 bytes     */
    CAN_ERR_WARN_LIMIT_96,          /*!< CAN programmable error warning limit: 96 bytes     */
    CAN_ERR_WARN_LIMIT_104,         /*!< CAN programmable error warning limit: 104 bytes    */
    CAN_ERR_WARN_LIMIT_112,         /*!< CAN programmable error warning limit: 112 bytes    */
    CAN_ERR_WARN_LIMIT_120,         /*!< CAN programmable error warning limit: 120 bytes    */
    CAN_ERR_WARN_LIMIT_128,         /*!< CAN programmable error warning limit: 128 bytes    */
} CAN_ErrWarnLimitETypeDef;

/**
  * @brief CAN Data Length Code definition
  * @note  data_len_code > 8 is only valid with FD Enable
  */
typedef enum {
    CAN_DAT_LEN_CODE_BYTE_0 = 0,    /*!< CAN Data Length 0 Byte     */
    CAN_DAT_LEN_CODE_BYTE_1,        /*!< CAN Data Length 1 Byte     */
    CAN_DAT_LEN_CODE_BYTES_2,       /*!< CAN Data Length 2 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_3,       /*!< CAN Data Length 3 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_4,       /*!< CAN Data Length 4 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_5,       /*!< CAN Data Length 5 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_6,       /*!< CAN Data Length 6 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_7,       /*!< CAN Data Length 7 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_8,       /*!< CAN Data Length 8 Bytes    */
    CAN_DAT_LEN_CODE_BYTES_12,      /*!< CAN Data Length 12 Bytes   */
    CAN_DAT_LEN_CODE_BYTES_16,      /*!< CAN Data Length 16 Bytes   */
    CAN_DAT_LEN_CODE_BYTES_20,      /*!< CAN Data Length 20 Bytes   */
    CAN_DAT_LEN_CODE_BYTES_24,      /*!< CAN Data Length 24 Bytes   */
    CAN_DAT_LEN_CODE_BYTES_32,      /*!< CAN Data Length 32 Bytes   */
    CAN_DAT_LEN_CODE_BYTES_48,      /*!< CAN Data Length 48 Bytes   */
    CAN_DAT_LEN_CODE_BYTES_64,      /*!< CAN Data Length 64 Bytes   */
} CAN_DatLenCodeETypeDef;


/**
  * @brief CAN frame store mode definition.
  */
typedef enum {
    CAN_FRAME_STORE_MODE_NONE = 0,   /*!< CAN frame store none      */
    CAN_FRAME_STORE_MODE_PRB,        /*!< CAN frame store with PRB  */
    CAN_FRAME_STORE_MODE_SRB,        /*!< CAN frame store with SRB  */
} CAN_FrmStoreModeETypeDef;

/**
  * @brief CAN node status definition.
  */
typedef enum {
    CAN_NODE_STA_SYNC = 0,    /*!< CAN node Synchronization status  */
    CAN_NODE_STA_IDLE,        /*!< CAN node Idle status             */
    CAN_NODE_STA_RECV,        /*!< CAN node Receive status          */
    CAN_NODE_STA_SEND,        /*!< CAN node Transmission status     */
} CAN_NodeStaETypeDef;

/**
  * @brief CAN Data Field Error definition.
  */
typedef enum {
    CAN_DATA_FIELD_ERR_NONE = 0,                    /*!< CAN data field no error */
    CAN_DATA_FIELD_ERR_BIT,                         /*!< CAN data field Bit error */
    CAN_DATA_FIELD_ERR_BIT_STUFFING,                /*!< CAN data field Bit Stuffing error */
    CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT,            /*!< CAN data field Acc Accelerated Frame Bit error */
    CAN_DATA_FIELD_ERR_FD_ACC_FRAME_BIT_STUFFING,   /*!< CAN data field Acc Accelerated Frame Bit Stuffing error */
} CAN_DatFieldErrETypeDef;


/**
  * @brief CAN Interrupt Line definition.
  */
typedef enum {
    CAN_INT_LINE_0 = 0,   /*!< CAN Interrupt Line CANx_INT0     */
    CAN_INT_LINE_1,       /*!< CAN Interrupt Line CANx_INT1     */
} CAN_IntLineETypeDef;


/**
  * @brief CAN Acceptance Mode definition.
  */
typedef enum {
    CAN_ACCEPT_MODE_AND         = 1 , /*!< Range of CAN filter matching is ID=ACODE_X & ~AMASK_X */
    CAN_ACCEPT_MODE_OR          = 2 , /*!< Range of CAN filter matching is ID=ACODE_X or ID=AMASK_X */
    CAN_ACCEPT_MODE_RANGE       = 4 , /*!< Range of CAN filter matching is ACODE_X <= ID <= AMASK_X */
    CAN_ACCEPT_MODE_AND_EIDM    = 9 , /*!< Range of CAN filter matching is ID=(ACODE_X & ~AMASK_X) and support EIDM */
    CAN_ACCEPT_MODE_OR_EIDM     = 10, /*!< Range of CAN filter matching is ID=ACODE_X or ID=AMASK_X and support EIDM */
    CAN_ACCEPT_MODE_RANGE_EIDM  = 12, /*!< Range of CAN filter matching is ACODE_X <= ID <= AMASK_X and support EIDM */
} CAN_AcceptModeETypeDef;

/**
  * @brief CAN Acceptance Control definition.
  */
typedef enum {
    CAN_ACCEPT_CTRL_NONE                          = 0, /*!< CAN filter match, no action */
    CAN_ACCEPT_CTRL_STORE_PRB                     = 1, /*!< CAN filter match, data store in PRB  */
    CAN_ACCEPT_CTRL_STORE_SRB                     = 2, /*!< CAN filter match, data store in SRB  */
    CAN_ACCEPT_CTRL_UPD_PRIO_STA_REG              = 4, /*!< CAN filter match, update priority status register */
    CAN_ACCEPT_CTRL_STORE_PRB_UPD_PRIO_STA_REG    = 5, /*!< CAN filter match, data store in PRB and update priority status register */
    CAN_ACCEPT_CTRL_STORE_SRB_UPD_PRIO_STA_REG    = 6, /*!< CAN filter match, data store in SRB and update priority status register */
} CAN_AcceptCtrlETypeDef;


/**
  * @brief CAN Timestamp Timebase definition.
  */
typedef enum {
    CAN_TIMESTAMP_TIMEBASE_CLOSE    = 0,    /*!< CAN Timestamp Timebase close             */  
    CAN_TIMESTAMP_TIMEBASE_INT_TSC  = 1,    /*!< CAN Timestamp Timebase interior TSC      */
    CAN_TIMESTAMP_TIMEBASE_EXT_TMR0 = 2,    /*!< CAN Timestamp Timebase external timer 0  */
    CAN_TIMESTAMP_TIMEBASE_EXT_TMR1 = 4,    /*!< CAN Timestamp Timebase external timer 1  */
    CAN_TIMESTAMP_TIMEBASE_EXT_TMR2 = 8,    /*!< CAN Timestamp Timebase external timer 2  */
} CAN_TimestampTimebaseETypeDef;

/**
  * @brief CAN Rx Buffer Work Mode definition.
  */
typedef enum {
    CAN_RX_BUF_WORK_MODE_COVER  = 0,        /*!< Rx buffer work mode Cover    */  
    CAN_RX_BUF_WORK_MODE_BLOCK  = 1,        /*!< Rx buffer work mode Block    */  
} CAN_RxBufWorkModeETypeDef;


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
     *  number of payload bytes in a frame). @ref CAN_DatLenCodeETypeDef
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

             /*! Data Timestamp
              */
             data_timestamp      : 16,

             /*! Acceptance Data
              */
             acceptance_data     : 4,

             /*! Reserved bit.
              */
             reserved2           : 4;
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
     *  number of payload bytes in a frame). @ref CAN_DatLenCodeETypeDef
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

             /*! Data Message Marker
              */
             mesg_marker         : 8,

             /*! Reserved bit.
              */
             reserved2           : 15,

             /*! Event Buffer
              *  0: Message not write to ETB
              *  1: Message write to ETB
              */
             evt_buffer          : 1;
} CAN_TxBufFormatTypeDef;

/**
  * @brief CAN ETB buffer format type definition
  */
typedef struct __CAN_TxEvtBufFormatTypeDef {
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
     *  number of payload bytes in a frame). @ref CAN_DatLenCodeETypeDef
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

             /*! Tx Data Timestamp
              */
             data_timestamp      : 16,

             /*! Tx Buffer Frame Message Marker
              */
             mesg_marker         : 8;
} CAN_TxEvtBufFormatTypeDef;

/**
 * @brief CAN IRQ Callback ID definition
 */
typedef enum {
    CAN_PTB_TX_CPLT_CB_ID,                  /*!< CAN PTB Tx Completed callback ID   */
    CAN_STB_TX_CPLT_CB_ID,                  /*!< CAN STB Tx Completed callback ID   */
    CAN_RX_CPLT_CB_ID,                      /*!< CAN Rx Completed callback ID       */
    CAN_SRB_RX_CPLT_CB_ID,                  /*!< CAN SRB Completed callback ID      */
    CAN_ETB_CPLT_CB_ID,                     /*!< CAN ETB Completed callback ID      */
    //CAN_ERROR_CB_ID,                      /*!< CAN Error callback ID              */
    CAN_CB_ID_ENUM_END,                     /*!< CAN callback ID enum end           */
} CAN_UserCallbackIdETypeDef;


/**
  * @brief CAN IRQ Callback structure definition
  */
typedef struct __CAN_UserCallbackTypeDef {
    CAN_UserCallback TxCpltCallback_ptb;    /*!< CAN PTB Tx Completed callback        */
    CAN_UserCallback TxCpltCallback_stb;    /*!< CAN STB Tx Completed callback        */
    CAN_UserCallback RxCpltCallback;        /*!< CAN PRB Completed callback            */
    CAN_UserCallback RxCpltCallback_srb;    /*!< CAN SRB Completed callback            */
    CAN_UserCallback TxEvtCpltCallback_etb; /*!< CAN ETB Tx Event Completed callback  */
    //CAN_UserCallback ErrorCallback;       /*!< CAN Error callback                   */
} CAN_UserCallbackTypeDef;

/**
  * @brief CAN acceptance filter config type definition
  */
typedef struct __CAN_AcceptFilCfgTypeDef {
    CAN_AcceptFilSlotETypeDef slot;                     /*!< Acceptance filter slot number                  */
    uint32_t code_val;                                  /*!< Acceptance filter code value                   */
    uint32_t mask_val;                                  /*!< Acceptance filter mask value                   */
    CAN_AcceptFilRxFrmETypeDef rx_frm;                  /*!< Acceptance filter Rx frame type                */
    bool ex_cfg_no_default;                             /*!< Acceptance filter extended config not default  */
    CAN_AcceptModeETypeDef ex_cfg_mode;                 /*!< Acceptance Mode                                */
    CAN_AcceptCtrlETypeDef ex_cfg_ctrl;                 /*!< Acceptance Control                             */
} CAN_AcceptFilCfgTypeDef;

/**
  * @brief CAN Protocol Status type definition
  */
typedef struct __CAN_ProtStaTypeDef {
    bool fd_dat_frm;                                    /*!< CAN FD Standard data frame flag    */
    bool fd_acc_dat;                                    /*!< CAN FD Accelerated data frame flag */
    bool fd_ext_dat;                                    /*!< CAN FD Extended data frame flag    */
    bool fd_prot_mistake;                               /*!< CAN FD protocol mistake flag       */
    CAN_FrmStoreModeETypeDef rx_store_mode;             /*!< CAN Rx buffer frame store type     */
    CAN_NodeStaETypeDef node_sta;                       /*!< CAN Node Status                    */
    CAN_DatFieldErrETypeDef err_code;                   /*!< Data Kind Of Error                 */
} CAN_ProtStaTypeDef;

/**
  * @brief CAN Priority Message Status type definition
  */
typedef struct __CAN_PrioMsgStaTypeDef {
    bool ext_frm_flag;                                  /*!< Is Extended frame, or standard     */
    CAN_FrmStoreModeETypeDef msg_store_mode;            /*!< Priority message frame store type  */
    CAN_AcceptFilSlotETypeDef accept_fil_num;           /*!< Acceptance filter slot number      */
} CAN_PrioMsgStaTypeDef;

/**
  * @brief CAN global filter config type definition
  */
typedef struct __CAN_GlobalFilCfgTypeDef {
    bool rej_std_remote_frm;                            /*!< Reject Standard remote frames      */
    bool rej_ext_remote_frm;                            /*!< Reject Extended remote frames      */
    CAN_RxBufWorkModeETypeDef prb_work_mode;            /*!< PRB Working Mode                   */
    CAN_RxBufWorkModeETypeDef srb_work_mode;            /*!< SRB Working Mode                   */
    uint32_t ext_id_mask;                               /*!< Extended ID Global Mask            */
} CAN_GlobalFilCfgTypeDef;

/**
  * @brief CAN timestamp counter base config type definition
  */
typedef struct __CAN_TimestampBaseCfgTypeDef {
    CAN_TimestampTimebaseETypeDef timebase_type;        /*!< Timestamp timebase select or close */
    uint32_t timestamp_prescaler;                       /*!< Timestamp prescaler                */
} CAN_TimestampBaseCfgTypeDef;

/**
  * @brief CAN timeout counter control config type definition
  */
typedef struct __CAN_TimeoutCntrCtlCfgTypeDef {
    bool cnt_enable;                                    /*!< Timeout Count function enbale      */
    bool int_enable;                                    /*!< Timeout Count interrupt enable     */
    uint32_t period;                                    /*!< Timeout Counter (down)count period */
} CAN_TimeoutCntrCtlCfgTypeDef;

/**
  * @brief CAN timestamp counter config type definition
  */
typedef struct __CAN_TimeCntrCfgTypeDef {
    CAN_TimestampBaseCfgTypeDef base_ctl;               /*!< timeout counter timebase config    */
    CAN_TimeoutCntrCtlCfgTypeDef prb_timeout_cntr;      /*!< PRB timeout counter config         */
    CAN_TimeoutCntrCtlCfgTypeDef srb_timeout_cntr;      /*!< SRB Timeout counter config         */
    CAN_TimeoutCntrCtlCfgTypeDef etb_timeout_cntr;      /*!< ETB Timeout counter config         */
    CAN_TimeoutCntrCtlCfgTypeDef cont_timeout_cntr;     /*!< Continuous Timeout counter config  */
} CAN_TimeCntrCfgTypeDef;



/**
  * @brief CAN LL Config Type Definition
  */
typedef struct __CAN_LLCfgTypeDef {
    bool prot_exc_detect_dis;                                 /*!< Protocol exception detect disable      */    
    CAN_BufAlmostFullLimitETypeDef srb_almost_full_limit;     /*!< SRB almost full warning limit          */    
    CAN_BufAlmostFullLimitETypeDef etb_almost_full_limit;     /*!< ETB almost full warning limit          */
    CAN_BufAlmostEmptyLimitETypeDef stb_almost_empty_limit;   /*!< STB almost empty warning limit          */
    CAN_GlobalFilCfgTypeDef global_fil;                       /*!< Global Filter config                   */
} CAN_LLCfgTypeDef;

/**
  * @brief CAN user config type definition
  */
typedef struct __CAN_UserCfgTypeDef {
    bool fd_en;                                         /*!< CAN FD Enable                              */
    bool fd_iso_en;                                     /*!< CAN FD ISO Enable                          */
    uint32_t func_clk_freq;                             /*!< CAN function clock freq                    */

    uint32_t baudrate_ss;                               /*!< SS baudrate                                */
    uint8_t bit_timing_seg1_ss;                         /*!< SS bit timing segment1                     */
    uint8_t bit_timing_seg2_ss;                         /*!< SS bit timing degment2                     */
    uint8_t bit_timing_sjw_ss;                          /*!< SS bit timing synchronization jump width   */

    uint32_t baudrate_fs;                               /*!< FS baudrate                                */
    uint8_t bit_timing_seg1_fs;                         /*!< FS bit timing segment1                     */
    uint8_t bit_timing_seg2_fs;                         /*!< FS bit timing degment2                     */
    uint8_t bit_timing_sjw_fs;                          /*!< FS bit timing synchronization jump width   */

    CAN_RxAlmostFullLimitETypeDef rx_almost_full_limit; /*!< rx buffer almost full warning limit        */
    CAN_RxMuxSelETypeDef rx_muxsel;                     /*!< rx receive multiplexer select              */
    CAN_ErrWarnLimitETypeDef err_limit;                 /*!< error warning limit                        */
    CAN_AcceptFilCfgTypeDef *accept_fil_cfg_ptr;        /*!< acceptance filter config pointer           */
    uint8_t accept_fil_cfg_num;                         /*!< acceptance filter config number            */

    CAN_UserCallbackTypeDef  user_callback;             /*!< User Callback                              */

    CAN_LLCfgTypeDef *ll_cfg;                           /*!< Optional LL Config Pointer                 */
} CAN_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup CAN_LL_Exported_Functions
  * @{
  */

/** @addtogroup CAN_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_CAN_Init(CAN_TypeDef *Instance, CAN_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_CAN_DeInit(CAN_TypeDef *Instance);
LL_StatusETypeDef LL_CAN_Reset(CAN_TypeDef *Instance);
void LL_CAN_MspInit(CAN_TypeDef *Instance);
void LL_CAN_MspDeInit(CAN_TypeDef *Instance);
LL_StatusETypeDef LL_CAN_RegisterCallback(CAN_TypeDef *Instance, CAN_UserCallbackIdETypeDef CallbackID, CAN_UserCallback pCallback);
LL_StatusETypeDef LL_CAN_UnRegisterCallback(CAN_TypeDef *Instance, CAN_UserCallbackIdETypeDef CallbackID);
/**
  * @}
  */


/** @addtogroup CAN_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_CAN_ResetEnter(CAN_TypeDef *Instance);
LL_StatusETypeDef LL_CAN_ResetExit(CAN_TypeDef *Instance);
LL_StatusETypeDef LL_CAN_AcceptFilCfg(CAN_TypeDef *Instance, CAN_AcceptFilCfgTypeDef *fil_cfg);
uint8_t LL_CAN_DatLen_Get(CAN_TypeDef *Instance, uint8_t dat_len_code);
CAN_DatLenCodeETypeDef LL_CAN_DatLenCode_Get(CAN_TypeDef *Instance, uint8_t dat_len);
LL_StatusETypeDef LL_CAN_GlobalFilCfg(CAN_TypeDef *Instance, CAN_GlobalFilCfgTypeDef *fil_cfg);
LL_StatusETypeDef LL_CAN_TimeCounterCfg(CAN_TypeDef *Instance, CAN_TimeCntrCfgTypeDef *cntr_cfg);
LL_StatusETypeDef LL_CAN_RxFrmSta_Get(CAN_TypeDef *Instance, CAN_ProtStaTypeDef *sta);
LL_StatusETypeDef LL_CAN_PrioMsgSta_Get(CAN_TypeDef *Instance, CAN_PrioMsgStaTypeDef *sta);
/**
  * @}
  */


/** @addtogroup CAN_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_CAN_TransmitPTB_CPU(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_TransmitSTB_CPU(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_Receive_CPU(CAN_TypeDef *Instance, CAN_RxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_ReceiveSRB_CPU(CAN_TypeDef *Instance, CAN_RxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_GetTxEvent_CPU(CAN_TypeDef *Instance, CAN_TxEvtBufFormatTypeDef *buf_fmt);

LL_StatusETypeDef LL_CAN_TransmitPTB_IT(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_TransmitSTB_IT(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_Receive_IT(CAN_TypeDef *Instance, CAN_RxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_ReceiveSRB_IT(CAN_TypeDef *Instance, CAN_RxBufFormatTypeDef *buf_fmt, uint32_t *buf);
LL_StatusETypeDef LL_CAN_GetTxEvent_IT(CAN_TypeDef *Instance, CAN_TxEvtBufFormatTypeDef *buf_fmt);
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

void LL_CAN_ErrCntCallback(CAN_TypeDef *Instance);
void LL_CAN_ETBRcvCallback(CAN_TypeDef *Instance);
void LL_CAN_SRBRcvCallback(CAN_TypeDef *Instance);
void LL_CAN_ETBAlmostFullCallback(CAN_TypeDef *Instance);
void LL_CAN_ETBFullCallback(CAN_TypeDef *Instance);
void LL_CAN_ETBOverCallback(CAN_TypeDef *Instance);
void LL_CAN_SRBAlmostFullCallback(CAN_TypeDef *Instance);
void LL_CAN_SRBFullCallback(CAN_TypeDef *Instance);
void LL_CAN_SRBOverCallback(CAN_TypeDef *Instance);
void LL_CAN_ContCntTimeoutCallback(CAN_TypeDef *Instance);
void LL_CAN_ETBTimeoutCallback(CAN_TypeDef *Instance);
void LL_CAN_SRBTimeoutCallback(CAN_TypeDef *Instance);
void LL_CAN_PRBTimeoutCallback(CAN_TypeDef *Instance);
void LL_CAN_TimestampCallback(CAN_TypeDef *Instance);
void LL_CAN_PrioMesgCallback(CAN_TypeDef *Instance);
void LL_CAN_STBAlmostEmptyCallback(CAN_TypeDef *Instance);
void LL_CAN_STBEmptyCallback(CAN_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_CAN_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

