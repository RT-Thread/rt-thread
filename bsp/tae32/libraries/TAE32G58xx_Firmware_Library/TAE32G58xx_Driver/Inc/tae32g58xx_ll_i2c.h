/**
  ******************************************************************************
  * @file    tae32g58xx_ll_i2c.h
  * @author  MCD Application Team
  * @brief   Header file for I2C LL module
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
#ifndef _TAE32G58XX_LL_I2C_H_
#define _TAE32G58XX_LL_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"
#ifdef LL_DMA_MODULE_ENABLED
#include "tae32g58xx_ll_dma.h"
#endif


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup I2C_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Constants I2C LL Exported Constants
  * @brief    I2C LL Exported Constants
  * @{
  */

#define I2C_DIRECT_TX               (0x0UL << I2C0_CTRL_DIRECT_Pos)
#define I2C_DIRECT_RX               (0x1UL << I2C0_CTRL_DIRECT_Pos)

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Macros I2C LL Exported Macros
  * @brief    I2C LL Exported Macros
  * @{
  */

/**
  * @brief  I2C Bus Status Get
  * @note   This bit is mainly used for single-byte reception control of the 
  *         slave device. After the RXFIFO full threshold interrupt is set, 
  *         wait for this bit to become 0x2 before performing subsequent actions.
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Bus Status
  */
#define __LL_I2C_BusSta_Get(__I2C__)                    READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_HDRX_Msk, I2C0_ENABLE_HDRX_Pos)

/**
  * @brief  Slave SCL Stretching Disable Assert
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_SCLStrchDis_Assert(__I2C__)        SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_NSTCH_Msk)

/**
  * @brief  Slave SCL Stretching Disable Release
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_SCLStrchDis_Release(__I2C__)       CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_NSTCH_Msk)

/**
  * @brief  Judge is Slave SCL Stretching Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 is Slave SCL Stretching Disable
  * @retval 1 is Slave SCL Stretching Enable
  */
#define __LL_I2C_SLV_IsSCLStrchEn(__I2C__)              (!READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_NSTCH_Msk, I2C0_ENABLE_NSTCH_Pos))

/**
  * @brief  I2C Receive Data SCL Stretching Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDatSCLStrch_En(__I2C__)              SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_MSTCH_Msk)

/**
  * @brief  I2C Receive Data SCL Stretching Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDatSCLStrch_Dis(__I2C__)             CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_MSTCH_Msk)

/**
  * @brief  Judge is I2C Receive Data SCL Stretching Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 is Receive Data SCL Stretching Disable
  * @retval 1 is Receive Data SCL Stretching Enable
  */
#define __LL_I2C_IsRxDatSCLStrchEn(__I2C__)             READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_MSTCH_Msk, I2C0_ENABLE_MSTCH_Pos)

/**
  * @brief  SMBUS Timeout Counter Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_TimeoutCnt_En(__I2C__)           SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMTOEN_Msk)

/**
  * @brief  SMBUS Timeout Counter Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_TimeoutCnt_Dis(__I2C__)          CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMTOEN_Msk)

/**
  * @brief  SMBUS Host Address Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_HostAddr_En(__I2C__)             SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMHEN_Msk)

/**
  * @brief  SMBUS Host Address Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_HostAddr_Dis(__I2C__)            CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMHEN_Msk)

/**
  * @brief  SMBUS ARP Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARP_En(__I2C__)                  SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMARPEN_Msk)

/**
  * @brief  SMBUS ARP Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARP_Dis(__I2C__)                 CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMARPEN_Msk)

/**
  * @brief  SMBUS Alert Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_Alert_En(__I2C__)                SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMALEN_Msk)

/**
  * @brief  SMBUS Alert Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_Alert_Dis(__I2C__)               CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_SMALEN_Msk)

/**
  * @brief  I2C Optional Slave Address Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_OptSlvAddr_En(__I2C__)             SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_OSAEN_Msk)

/**
  * @brief  I2C Optional Slave Address Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_OptSlvAddr_Dis(__I2C__)            CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_OSAEN_Msk)

/**
  * @brief  Judge is I2C Optional Slave Address Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 is I2C Optional Slave Address Disable
  * @retval 1 is I2C Optional Slave Address Enable
  */
#define __LL_I2C_SLV_IsOptSlvAddrEn(__I2C__)            READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_OSAEN_Msk, I2C0_ENABLE_OSAEN_Pos)

/**
  * @brief  General Call Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_GenCall_En(__I2C__)                    SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_GCEN_Msk)

/**
  * @brief  General Call Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_GenCall_Dis(__I2C__)                   CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_GCEN_Msk)

/**
  * @brief  I2C 7bit Address Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_7bAddr_Set(__I2C__)                    CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_A10BEN_Msk)

/**
  * @brief  I2C 10bit Address Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_10bAddr_Set(__I2C__)                   SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_A10BEN_Msk)

/**
  * @brief  I2C Slave Role Set
  * @param  __I2C__ Specifies I2C peripheral
  * @deprecated This interface is no longer accessible to users
  * @return None
  */
#define __LL_I2C_SlaveRole_Set(__I2C__)                 CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_MSTEN_Msk)

/**
  * @brief  I2C Master Role Set
  * @param  __I2C__ Specifies I2C peripheral
  * @deprecated This interface is no longer accessible to users
  * @return None
  */
#define __LL_I2C_MasterRole_Set(__I2C__)                SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_MSTEN_Msk)

/**
  * @brief  I2C Current Role Get
  * @note   
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Role
  */
#define __LL_I2C_CurrRole_Get(__I2C__)                  READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_MSTEN_Msk, I2C0_ENABLE_MSTEN_Pos)

/**
  * @brief  I2C Receive Data SCL Stretching Mode Non-empty Set
  * @param  __I2C__ Specifies I2C peripheral
  * @note   When RXFIFO is not empty, the SCL is low, and when RXFIFO is empty, the SCL is released
  * @return None
  */
#define __LL_I2C_RxDatSCLStrchModeNonEmpty_Set(__I2C__) CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_RFHSEN_Msk)

/**
  * @brief  I2C Receive Data SCL Stretching Mode Full Set
  * @param  __I2C__ Specifies I2C peripheral
  * @note   When RXFIFO is full, SCL is held down, and when RXFIFO is not full, SCL is released
  * @return None
  */
#define __LL_I2C_RxDatSCLStrchModeFull_Set(__I2C__)     SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_RFHSEN_Msk)

/**
  * @brief  I2C Receive Data SCL Stretching Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  mode I2C Receive Data SCL Stretching Mode @ref I2C_RcvClkStrchModeETypeDef
  * @return None
  */
#define __LL_I2C_RxDatSCLStrchMode_Set(__I2C__, mode)         \
        MODIFY_REG((__I2C__)->ENABLE, I2C0_ENABLE_RFHSEN_Msk, (((mode) & 0x1UL) << I2C0_ENABLE_RFHSEN_Pos))

/**
  * @brief  I2C Receive Data SCL Stretching Mode Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDatSCLStrchMode_Get(__I2C__)         \
        READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_RFHSEN_Msk, I2C0_ENABLE_RFHSEN_Pos)

/**
  * @brief  Tx DMA Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxDMA_En(__I2C__)                      SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_DMATXEN_Msk)

/**
  * @brief  Tx DMA Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxDMA_Dis(__I2C__)                     CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_DMATXEN_Msk)

/**
  * @brief  Rx DMA Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDMA_En(__I2C__)                      SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_DMARXEN_Msk)

/**
  * @brief  Rx DMA Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDMA_Dis(__I2C__)                     CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_DMARXEN_Msk)

/**
  * @brief  Release Command (Release Command to start I2C transmit after config CTRL register)
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Cmd_Release(__I2C__)                   SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_RLSCMD_Msk)

/**
  * @brief  Judge I2C is Start Transmission or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Not action
  * @retval 1 Start Transmission
  */
#define __LL_I2C_IsStartTrans(__I2C__)                  READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_RLSCMD_Msk, I2C0_ENABLE_RLSCMD_Pos)

/**
  * @brief  TxFIFO Reset (Auto Clear)
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxFIFO_Reset(__I2C__)                  SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_TFRST_Msk)

/**
  * @brief  RxFIFO Reset (Auto Clear)
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFO_Reset(__I2C__)                  SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_RFRST_Msk)

/**
  * @brief  I2C Send Fixed Data At Slave Underrun Condition Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_UnderrunSndFixDat_Set(__I2C__)     CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_UDRCFG_Msk)

/**
  * @brief  I2C Send Repetitive Data At Slave Underrun Condition Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_UnderrunSndReptDat_Set(__I2C__)    SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_UDRCFG_Msk)

/**
  * @brief  II2C Behavior At Slave Underrun Condition Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_UnderrunBehavior_Get(__I2C__)      \
        READ_BIT_SHIFT((__I2C__)->ENABLE, I2C0_ENABLE_UDRCFG_Msk, I2C0_ENABLE_UDRCFG_Pos)

/**
  * @brief  I2C Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Enable(__I2C__)                        SET_BIT((__I2C__)->ENABLE, I2C0_ENABLE_I2CEN_Msk)

/**
  * @brief  I2C Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Disable(__I2C__)                       CLEAR_BIT((__I2C__)->ENABLE, I2C0_ENABLE_I2CEN_Msk)


/**
  * @brief  Auto End Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_AutoEnd_En(__I2C__)                    SET_BIT((__I2C__)->CTRL, I2C0_CTRL_AUTOEND_Msk)

/**
  * @brief  Auto End Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_AutoEnd_Dis(__I2C__)                   CLEAR_BIT((__I2C__)->CTRL, I2C0_CTRL_AUTOEND_Msk)

/**
  * @brief  I2C 10BIT Master-Read Mode Write Command Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_10bReadModeWriteCmd_Set(__I2C__)   CLEAR_BIT((__I2C__)->CTRL, I2C0_CTRL_MODE10B_Msk)

/**
  * @brief  I2C 10BIT Master-Read Mode Read Command Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_10bReadModeReadCmd_Set(__I2C__)    SET_BIT((__I2C__)->CTRL, I2C0_CTRL_MODE10B_Msk)

/**
  * @brief  I2C 10BIT Master-Read Mode Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_10bReadMode_Get(__I2C__)           \
        READ_BIT_SHIFT((__I2C__)->CTRL, I2C0_CTRL_MODE10B_Msk, I2C0_CTRL_MODE10B_Pos)

/**
  * @brief  SMBUS PEC Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_PEC_En(__I2C__)                  SET_BIT((__I2C__)->CTRL, I2C0_CTRL_PECBYTE_Msk)

/**
  * @brief  SMBUS PEC Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_PEC_Dis(__I2C__)                 CLEAR_BIT((__I2C__)->CTRL, I2C0_CTRL_PECBYTE_Msk)

/**
  * @brief  Slave Reply NACK after receive data
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_Reply_NACK(__I2C__)                SET_BIT((__I2C__)->CTRL, I2C0_CTRL_NACK_Msk)

/**
  * @brief  Master Start Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_Start_En(__I2C__)                  SET_BIT((__I2C__)->CTRL, I2C0_CTRL_START_Msk)

/**
  * @brief  Master Stop Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_Stop_En(__I2C__)                   SET_BIT((__I2C__)->CTRL, I2C0_CTRL_STOP_Msk)

/**
  * @brief  Master Direction TX Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_DirTX_Set(__I2C__)                 CLEAR_BIT((__I2C__)->CTRL, I2C0_CTRL_DIRECT_Msk)

/**
  * @brief  Master Direction RX Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_DirRX_Set(__I2C__)                 SET_BIT((__I2C__)->CTRL, I2C0_CTRL_DIRECT_Msk)

/**
  * @brief  Data Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Data Count
  * @return None
  */
#define __LL_I2C_DatCnt_SET(__I2C__, cnt)               \
        MODIFY_REG((__I2C__)->CTRL, I2C0_CTRL_I2CCNT_Msk, (((cnt) & 0xffUL) << I2C0_CTRL_I2CCNT_Pos))

/**
  * @brief  CTRL Register Write Operation and Command Release
  * @param  __I2C__ Specifies I2C peripheral
  * @param  val CTRL Register Write Value
  * @return None
  */
#define __LL_I2C_CTRLRegWrite_OPT(__I2C__, val)         \
        do {                                            \
            WRITE_REG((__I2C__)->CTRL, val);            \
            __LL_I2C_Cmd_Release(__I2C__);              \
        } while (0)


/**
  * @brief  SCL High Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  hcnt SCL High Count
  * @return None
  */
#define __LL_I2C_SCLHighCnt_Set(__I2C__, hcnt)          \
        MODIFY_REG((__I2C__)->BAUD, I2C0_BAUD_SCLHCNT_Msk, (((hcnt-1) & 0x3ffUL) << I2C0_BAUD_SCLHCNT_Pos))

/**
  * @brief  SCL Low Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  lcnt SCL Low Count
  * @return None
  */
#define __LL_I2C_SCLLowCnt_Set(__I2C__, lcnt)           \
        MODIFY_REG((__I2C__)->BAUD, I2C0_BAUD_SCLLCNT_Msk, (((lcnt-1) & 0x3ffUL) << I2C0_BAUD_SCLLCNT_Pos))

/**
  * @brief  SCL High and Low Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  hcnt SCL High Count
  * @param  lcnt SCL Low Count
  * @return None
  */
#define __LL_I2C_SCLHighLowCnt_Set(__I2C__, hcnt, lcnt)                              \
        MODIFY_REG((__I2C__)->BAUD, I2C0_BAUD_SCLHCNT_Msk | I2C0_BAUD_SCLLCNT_Msk,   \
        (((hcnt-1) & 0x3ffUL) << I2C0_BAUD_SCLHCNT_Pos) | (((lcnt-1) & 0x3ffUL) << I2C0_BAUD_SCLLCNT_Pos))


/**
  * @brief  I2C Data At Slave Underrun Condition Write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat I2C Data At Slave Underrun Condition
  * @return None
  */
#define __LL_I2C_SLV_TxFIFOUnderrunFixDat_Write(__I2C__, dat)                        \
        MODIFY_REG((__I2C__)->UDRDR, I2C0_UDRDR_UDRDR_Msk, ((dat & 0xffUL) << I2C0_UDRDR_UDRDR_Pos))

/**
  * @brief  I2C Data At Slave Underrun Condition Read
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Data At Slave Underrun Condition
  */
#define __LL_I2C_SLV_TxFIFOUnderrunFixDat_Read(__I2C__)                              \
        READ_BIT_SHIFT((__I2C__)->UDRDR, I2C0_UDRDR_UDRDR_Msk, I2C0_UDRDR_UDRDR_Pos)


/**
  * @brief  RxFIFO Full Threshold Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  thres RxFIFO Full Threshold
  * @return None
  */
#define __LL_I2C_RxFIFOFullThres_Set(__I2C__, thres)    \
        MODIFY_REG((__I2C__)->FIFOCTRL, I2C0_FIFOCTRL_RXFTLR_Msk, (((thres-1) & 0xfUL) << I2C0_FIFOCTRL_RXFTLR_Pos))

/**
  * @brief  RxFIFO Full Threshold Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return RxFIFO Full Threshold
  */
#define __LL_I2C_RxFIFOFullThres_Get(__I2C__)           \
        (READ_BIT_SHIFT((__I2C__)->FIFOCTRL, I2C0_FIFOCTRL_RXFTLR_Msk, I2C0_FIFOCTRL_RXFTLR_Pos) + 1)

/**
  * @brief  TxFIFO Empty Threshold Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  thres TxFIFO Empty Threshold
  * @return None
  */
#define __LL_I2C_TxFIFOEmptyThres_Set(__I2C__, thres)   \
        MODIFY_REG((__I2C__)->FIFOCTRL, I2C0_FIFOCTRL_TXFTLR_Msk, (((thres) & 0xfUL) << I2C0_FIFOCTRL_TXFTLR_Pos))

/**
  * @brief  TxFIFO Empty Threshold Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return TxFIFO Empty Threshold
  */
#define __LL_I2C_TxFIFOEmptyThres_Get(__I2C__)          \
        READ_BIT_SHIFT((__I2C__)->FIFOCTRL, I2C0_FIFOCTRL_TXFTLR_Msk, I2C0_FIFOCTRL_TXFTLR_Pos)


/**
  * @brief  Master Target Address Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tar I2C Master Target Address
  * @return None
  */
#define __LL_I2C_MST_TAR_Set(__I2C__, tar)              WRITE_REG((__I2C__)->TAR, tar & 0x3ffUL)


/**
  * @brief  Slave Receive Address Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  sar I2C Slave Receive Address
  * @return None
  */
#define __LL_I2C_SLV_SAR_Set(__I2C__, sar)              WRITE_REG((__I2C__)->SAR, sar & 0x3ffUL)

/**
  * @brief  Slave Receive Address Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Slave Receive Address
  */
#define __LL_I2C_SLV_SAR_Get(__I2C__)                   READ_BIT((__I2C__)->SAR, 0x3ffUL)


/**
  * @brief  I2C Optional Slave Address Mask Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  mask I2C Optional Slave Address Mask
  * @return None
  */
#define __LL_I2C_SLV_OptSlvAddrMask_Set(__I2C__, mask)  \
        MODIFY_REG((__I2C__)->OSAR, I2C0_OSAR_OSAM_Msk, (((mask) & 0x3ffUL) << I2C0_OSAR_OSAM_Pos))

/**
  * @brief  I2C Optional Slave Address Mask Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Optional Slave Address Mask
  */
#define __LL_I2C_SLV_OptSlvAddrMask_Get(__I2C__)        \
        READ_BIT_SHIFT((__I2C__)->OSAR, I2C0_OSAR_OSAM_Msk, I2C0_OSAR_OSAM_Pos)

/**
  * @brief  I2C Optional Slave Address Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr I2C Optional Slave Address
  * @return None
  */
#define __LL_I2C_SLV_OptSlvAddr_Set(__I2C__, addr)      \
        MODIFY_REG((__I2C__)->OSAR, I2C0_OSAR_OSAR_Msk, (((addr) & 0x3ffUL) << I2C0_OSAR_OSAR_Pos))

/**
  * @brief  I2C Optional Slave Address Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Optional Slave Address
  */
#define __LL_I2C_SLV_OptSlvAddr_Get(__I2C__)            \
        READ_BIT_SHIFT((__I2C__)->OSAR, I2C0_OSAR_OSAR_Msk, I2C0_OSAR_OSAR_Pos)


/**
  * @brief  SMBUS Calculate PEC Data Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return Calculate PEC Data
  */
#define __LL_I2C_SMBUS_CalcPECData_Get(__I2C__)         READ_BIT_SHIFT((__I2C__)->PEC, I2C0_PEC_IDPEC_Msk, I2C0_PEC_IDPEC_Pos)

/**
  * @brief  SMBUS Rx PEC Data Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return Rx PEC Data
  */
#define __LL_I2C_SMBUS_RxPECData_Get(__I2C__)           READ_BIT_SHIFT((__I2C__)->PEC, I2C0_PEC_RXPEC_Msk, I2C0_PEC_RXPEC_Pos)


/**
  * @brief  Spike Suppression Limit Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  limit Spike Suppression Limit
  * @return None
  */
#define __LL_I2C_SpikeSupprLimit_Set(__I2C__, limit)        \
        MODIFY_REG((__I2C__)->TIMING, I2C0_TIMING_SPKLEN_Msk, (((limit) & 0xffUL) << I2C0_TIMING_SPKLEN_Pos))

/**
  * @brief  Slave Tx Transmit Delay Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  delay Slave Tx Transmit Delay Count in SYSCLK Unit
  * @return None
  */
#define __LL_I2C_SLV_TxTransmitDelay_Set(__I2C__, delay)    \
        MODIFY_REG((__I2C__)->TIMING, I2C0_TIMING_SLVSUDAT_Msk, (((delay) & 0xffUL) << I2C0_TIMING_SLVSUDAT_Pos))

/**
  * @brief  Rx Capture Delay Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  delay Rx Capture Delay Count in SYSCLK Unit
  * @return None
  */
#define __LL_I2C_RxCaptureDelay_Set(__I2C__, delay)         \
        MODIFY_REG((__I2C__)->TIMING, I2C0_TIMING_SUDAT_Msk, (((delay) & 0xffUL) << I2C0_TIMING_SUDAT_Pos))

/**
  * @brief  Tx Transmit Delay Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  delay Tx Transmit Delay Count in SYSCLK Unit
  * @return None
  */
#define __LL_I2C_TxTransmitDelay_Set(__I2C__, delay)        \
        MODIFY_REG((__I2C__)->TIMING, I2C0_TIMING_HDDAT_Msk, (((delay) & 0xffUL) << I2C0_TIMING_HDDAT_Pos))


/**
  * @brief  Slave Tsext Timing Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  timing Slave Tsext Timing Value
  * @return None
  */
#define __LL_I2C_SLV_TsextTiming_Set(__I2C__, timing)       \
        MODIFY_REG((__I2C__)->TIMEOUT, I2C0_TIMEOUT_SEXTTO_Msk, (((timing) & 0xffffUL) << I2C0_TIMEOUT_SEXTTO_Pos))

/**
  * @brief  Master Tmext Timing Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  timing Master Tmext Timing Value
  * @return None
  */
#define __LL_I2C_MST_TmextTiming_Set(__I2C__, timing)       \
        MODIFY_REG((__I2C__)->TIMEOUT, I2C0_TIMEOUT_MEXTTO_Msk, (((timing) & 0xffffUL) << I2C0_TIMEOUT_MEXTTO_Pos))


/**
  * @brief  I2C Clock Timeout BTO Check SCL Low Level
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_ClkTimeoutCkSCLLowLvl_Set(__I2C__)         CLEAR_BIT((__I2C__)->BUSTOUT, I2C0_BUSTOUT_TOSEL_Msk)

/**
  * @brief  I2C Clock Timeout BTO Check SCL and SDA High Level
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_ClkTimeoutCkSCLnSDAHighLvl_Set(__I2C__)    SET_BIT((__I2C__)->BUSTOUT, I2C0_BUSTOUT_TOSEL_Msk)

/**
  * @brief  I2C Clock Timeout Check Select Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Clock Timeout Check Select
  */
#define __LL_I2C_ClkTimeoutCkSel_Get(__I2C__)               \
        READ_BIT_SHIFT((__I2C__)->BUSTOUT, I2C0_BUSTOUT_TOSEL_Msk, I2C0_BUSTOUT_TOSEL_Pos)

/**
  * @brief  I2C Bus Timeout Timing Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  timing I2C Bus Timeout Timing
  * @return None
  */
#define __LL_I2C_BusTimeoutTiming_Set(__I2C__, timing)      \
        MODIFY_REG((__I2C__)->TIMEOUT, I2C0_BUSTOUT_BTO_Msk, (((timing) & 0xffffUL) << I2C0_BUSTOUT_BTO_Pos))

/**
  * @brief  I2C Bus Timeout Timing Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C Bus Timeout Timing
  */
#define __LL_I2C_BusTimeoutTiming_Get(__I2C__, timing)      \
        READ_BIT_SHIFT((__I2C__)->TIMEOUT, I2C0_BUSTOUT_BTO_Msk, I2C0_BUSTOUT_BTO_Pos)


/**
  * @brief  I2C Bus Timeout Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_BusTimeout_INT_En(__I2C__)             SET_BIT((__I2C__)->INTREN, I2C0_INTREN_BTOIE_Msk)

/**
  * @brief  I2C Bus Timeout Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_BusTimeout_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_BTOIE_Msk)

/**
  * @brief  Judge is I2C Bus Timeout Interrupt Enable or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 is I2C Bus Timeout Interrupt Disable
  * @retval 1 is I2C Bus Timeout Interrupt Enable
  */
#define __LL_I2C_IsBusTimeoutIntEn(__I2C__)             READ_BIT_SHIFT((__I2C__)->INTREN, I2C0_INTREN_BTOIE_Msk, I2C0_INTREN_BTOIE_Pos)

/**
  * @brief  Master On Hold Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_OnHold_INT_En(__I2C__)             SET_BIT((__I2C__)->INTREN, I2C0_INTREN_MOHIE_Msk)

/**
  * @brief  Master On Hold Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_OnHold_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_MOHIE_Msk)

/**
  * @brief  Slave Wait TX Data Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_WaitTxDat_INT_En(__I2C__)          SET_BIT((__I2C__)->INTREN, I2C0_INTREN_SWTXIE_Msk)

/**
  * @brief  Slave Wait TX Data Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_WaitTxDat_INT_Dis(__I2C__)         CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_SWTXIE_Msk)

/**
  * @brief  Master TX Address Done Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxAddrDone_INT_En(__I2C__)         SET_BIT((__I2C__)->INTREN, I2C0_INTREN_MTXAIE_Msk)

/**
  * @brief  Master TX Address Done Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxAddrDone_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_MTXAIE_Msk)

/**
  * @brief  Slave Rx General Call Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxGenCall_INT_En(__I2C__)          SET_BIT((__I2C__)->INTREN, I2C0_INTREN_RXGCIE_Msk)

/**
  * @brief  Slave Rx General Call Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxGenCall_INT_Dis(__I2C__)         CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_RXGCIE_Msk)

/**
  * @brief  Rx PEC Error Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxPECErr_INT_En(__I2C__)               SET_BIT((__I2C__)->INTREN, I2C0_INTREN_PECRXIE_Msk)

/**
  * @brief  Rx PEC Error Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxPECErr_INT_Dis(__I2C__)              CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_PECRXIE_Msk)

/**
  * @brief  Slave Tsext Timeout Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_TsextTimeout_INT_En(__I2C__)       SET_BIT((__I2C__)->INTREN, I2C0_INTREN_SEXTOIE_Msk)

/**
  * @brief  Slave Tsext Timeout Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_TsextTimeout_INT_Dis(__I2C__)      CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_SEXTOIE_Msk)

/**
  * @brief  Master Tmext Timeout Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TmextTimeout_INT_En(__I2C__)       SET_BIT((__I2C__)->INTREN, I2C0_INTREN_MEXTOIE_Msk)

/**
  * @brief  Master Tmext Timeout Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TmextTimeout_INT_Dis(__I2C__)      CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_MEXTOIE_Msk)

/**
  * @brief  Master Detect Alert Signal Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_DetAlertSig_INT_En(__I2C__)        SET_BIT((__I2C__)->INTREN, I2C0_INTREN_ALDETIE_Msk)

/**
  * @brief  Master Detect Alert Signal Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_DetAlertSig_INT_Dis(__I2C__)       CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_ALDETIE_Msk)

/**
  * @brief  Rx NACK Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxNACK_INT_En(__I2C__)                 SET_BIT((__I2C__)->INTREN, I2C0_INTREN_NACKIE_Msk)

/**
  * @brief  Rx NACK Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxNACK_INT_Dis(__I2C__)                CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_NACKIE_Msk)

/**
  * @brief  Detect Restart Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetRestart_INT_En(__I2C__)             SET_BIT((__I2C__)->INTREN, I2C0_INTREN_RSDETIE_Msk)

/**
  * @brief  Detect Restart Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetRestart_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_RSDETIE_Msk)

/**
  * @brief  Detect Stop Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetStop_INT_En(__I2C__)                SET_BIT((__I2C__)->INTREN, I2C0_INTREN_SPDETIE_Msk)

/**
  * @brief  Detect Stop Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetStop_INT_Dis(__I2C__)               CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_SPDETIE_Msk)

/**
  * @brief  Detect Start Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetStart_INT_En(__I2C__)               SET_BIT((__I2C__)->INTREN, I2C0_INTREN_STDETIE_Msk)

/**
  * @brief  Detect Start Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetStart_INT_Dis(__I2C__)              CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_STDETIE_Msk)

/**
  * @brief  Slave RX Address and Command is Slave RX Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_INT_En(__I2C__)    SET_BIT((__I2C__)->INTREN, I2C0_INTREN_RXADIE_Msk)

/**
  * @brief  Slave RX Address and Command is Slave RX Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_INT_Dis(__I2C__)   CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_RXADIE_Msk)

/**
  * @brief  Slave RX Address and Command is Slave TX Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_INT_En(__I2C__)    SET_BIT((__I2C__)->INTREN, I2C0_INTREN_TXADIE_Msk)

/**
  * @brief  Slave RX Address and Command is Slave TX Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_INT_Dis(__I2C__)   CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_TXADIE_Msk)

/**
  * @brief  Master Tx/Rx Done Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxRxDone_INT_En(__I2C__)           SET_BIT((__I2C__)->INTREN, I2C0_INTREN_MDEIE_Msk)

/**
  * @brief  Master Tx/Rx Done Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxRxDone_INT_Dis(__I2C__)          CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_MDEIE_Msk)

/**
  * @brief  Bus Error Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_BusErr_INT_En(__I2C__)                 SET_BIT((__I2C__)->INTREN, I2C0_INTREN_BUSEIE_Msk)

/**
  * @brief  Bus Error Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_BusErr_INT_Dis(__I2C__)                CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_BUSEIE_Msk)

/**
  * @brief  Arbitration Fail Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_ArbFail_INT_En(__I2C__)                SET_BIT((__I2C__)->INTREN, I2C0_INTREN_ARBFIE_Msk)

/**
  * @brief  Arbitration Fail Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_ArbFail_INT_Dis(__I2C__)               CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_ARBFIE_Msk)

/**
  * @brief  TxFIFO Overflow Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxFIFOOverflow_INT_En(__I2C__)         SET_BIT((__I2C__)->INTREN, I2C0_INTREN_TXOFIE_Msk)

/**
  * @brief  TxFIFO Overflow Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxFIFOOverflow_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_TXOFIE_Msk)

/**
  * @brief  RxFIFO Underflow Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOUnderflow_INT_En(__I2C__)        SET_BIT((__I2C__)->INTREN, I2C0_INTREN_RXUFIE_Msk)

/**
  * @brief  RxFIFO Underflow Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOUnderflow_INT_Dis(__I2C__)       CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_RXUFIE_Msk)

/**
  * @brief  RxFIFO Overflow Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOOverflow_INT_En(__I2C__)         SET_BIT((__I2C__)->INTREN, I2C0_INTREN_RXOFIE_Msk)

/**
  * @brief  RxFIFO Overflow Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOOverflow_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_RXOFIE_Msk)

/**
  * @brief  TxFIFO Empty Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxFIFOEmpty_INT_En(__I2C__)            SET_BIT((__I2C__)->INTREN, I2C0_INTREN_TXEIE_Msk)

/**
  * @brief  TxFIFO Empty Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxFIFOEmpty_INT_Dis(__I2C__)           CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_TXEIE_Msk)

/**
  * @brief  RxFIFO Full Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOFull_INT_En(__I2C__)             SET_BIT((__I2C__)->INTREN, I2C0_INTREN_RXFIE_Msk)

/**
  * @brief  RxFIFO Full Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOFull_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTREN, I2C0_INTREN_RXFIE_Msk)

/**
  * @brief  All Interrupt Enable Status Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return All Interrupt Enable Status
  */
#define __LL_I2C_AllIntEn_Get(__I2C__)                  READ_REG((__I2C__)->INTREN)


/**
  * @brief  Remain Counter Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return Remain Counter
  */
#define __LL_I2C_RemainCnter_Get(__I2C__)               READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RCNT_Msk, I2C0_INTR_RCNT_Pos)

/**
  * @brief  Judge is I2C Bus Timeout Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't I2C Bus Timeout Interrupt Pending
  * @retval 1 is I2C Bus Timeout Interrupt Pending
  */
#define __LL_I2C_IsBusTimeoutPnd(__I2C__)               READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_BTOI_Msk, I2C0_INTR_BTOI_Pos)

/**
  * @brief  I2C Bus Timeout Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_BusTimeoutPnd_Clr(__I2C__)             WRITE_REG((__I2C__)->INTR, I2C0_INTR_BTOI_Msk)

/**
  * @brief  Judge is Master On Hold Interrupt Pending or not (Auto Clear)
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master hasn't On Hold
  * @retval 1 Master has On Hold
  */
#define __LL_I2C_MST_IsOnHold(__I2C__)                  READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_MOHI_Msk, I2C0_INTR_MOHI_Pos)

/**
  * @brief  Judge is Slave Wait TX Data Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't Slave Wait TX Data Interrupt Pending
  * @retval 1 is Slave Wait TX Data Interrupt Pending
  */
#define __LL_I2C_SLV_IsWaitTxDat(__I2C__)               READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_SWTXI_Msk, I2C0_INTR_SWTXI_Pos)

/**
  * @brief  Slave Wait TX Data Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_WaitTxDat_Clr(__I2C__)             WRITE_REG((__I2C__)->INTR, I2C0_INTR_SWTXI_Msk)

/**
  * @brief  Judge is Master Tx Address Done Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master Tx Address hasn't Done
  * @retval 1 Master Tx Address has Done
  */
#define __LL_I2C_MST_IsTxAddrDone(__I2C__)              READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_MTXAI_Msk, I2C0_INTR_MTXAI_Pos)

/**
  * @brief  Master Tx Address Done Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxAddrDone_Clr(__I2C__)            WRITE_REG((__I2C__)->INTR, I2C0_INTR_MTXAI_Msk)

/**
  * @brief  Judge is Slave Rx General Call Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave hasn't Rx General Call
  * @retval 1 Slave has Rx General Call
  */
#define __LL_I2C_SLV_IsRxGenCall(__I2C__)               READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RXGCI_Msk, I2C0_INTR_RXGCI_Pos)

/**
  * @brief  Slave Rx General Call Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxGenCall_Clr(__I2C__)             WRITE_REG((__I2C__)->INTR, I2C0_INTR_RXGCI_Msk)

/**
  * @brief  Judge is Rx PEC Error Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 hasn't Rx PEC or PEC Correct
  * @retval 1 PEC Error
  */
#define __LL_I2C_IsRxPECErr(__I2C__)                    READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_PECRXI_Msk, I2C0_INTR_PECRXI_Pos)

/**
  * @brief  Rx PEC Error Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxPECErr_Clr(__I2C__)                  WRITE_REG((__I2C__)->INTR, I2C0_INTR_PECRXI_Msk)

/**
  * @brief  Judge is Slave Tsext Timeout Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave hasn't Tsext Timeout
  * @retval 1 Slave has Tsext Timeout
  */
#define __LL_I2C_SLV_IsTsextTimeout(__I2C__)            READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_SEXTOI_Msk, I2C0_INTR_SEXTOI_Pos)

/**
  * @brief  Slave Tsext Timeout Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_TsextTimeout_Clr(__I2C__)          WRITE_REG((__I2C__)->INTR, I2C0_INTR_SEXTOI_Msk)

/**
  * @brief  Judge is Master Tmext Timeout Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master hasn't Tmext Timeout
  * @retval 1 Master has Tmext Timeout
  */
#define __LL_I2C_MST_IsTmextTimeout(__I2C__)            READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_MEXTOI_Msk, I2C0_INTR_MEXTOI_Pos)

/**
  * @brief  Master Tmext Timeout Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TmextTimeout_Clr(__I2C__)          WRITE_REG((__I2C__)->INTR, I2C0_INTR_MEXTOI_Msk)

/**
  * @brief  Judge is Master Detect Alert Signal Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master hasn't Detected Alert Signal
  * @retval 1 Master has Detected Alert Signal
  */
#define __LL_I2C_MST_IsDetAlertSig(__I2C__)             READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_ALDETI_Msk, I2C0_INTR_ALDETI_Pos)

/**
  * @brief  Master Detect Alert Signal Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_DetAlertSig_Clr(__I2C__)           WRITE_REG((__I2C__)->INTR, I2C0_INTR_ALDETI_Msk)

/**
  * @brief  Judge is Rx NACK Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 hasn't Rx NACK
  * @retval 1 has Rx NACK
  */
#define __LL_I2C_IsRxNACK(__I2C__)                      READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_NACKI_Msk, I2C0_INTR_NACKI_Pos)

/**
  * @brief  Rx NACK Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxNACK_Clr(__I2C__)                    WRITE_REG((__I2C__)->INTR, I2C0_INTR_NACKI_Msk)

/**
  * @brief  Judge is Detect Restart Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 hasn't Detect Restart
  * @retval 1 has Detect Restart
  */
#define __LL_I2C_IsDetRestart(__I2C__)                  READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RSDETI_Msk, I2C0_INTR_RSDETI_Pos)

/**
  * @brief  Detect Restart Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetRestart_Clr(__I2C__)                WRITE_REG((__I2C__)->INTR, I2C0_INTR_RSDETI_Msk)

/**
  * @brief  Judge is Detect Stop Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 hasn't Detected Stop
  * @retval 1 has Detected Stop
  */
#define __LL_I2C_IsDetStop(__I2C__)                     READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_SPETI_Msk, I2C0_INTR_SPETI_Pos)

/**
  * @brief  Detect Stop Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetStop_Clr(__I2C__)                   WRITE_REG((__I2C__)->INTR, I2C0_INTR_SPETI_Msk)

/**
  * @brief  Judge is Detect Start Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 hasn't Detected Start
  * @retval 1 has Detected Start
  */
#define __LL_I2C_IsDetStart(__I2C__)                    READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_STDETI_Msk, I2C0_INTR_STDETI_Pos)

/**
  * @brief  Detect Start Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_DetStart_Clr(__I2C__)                  WRITE_REG((__I2C__)->INTR, I2C0_INTR_STDETI_Msk)

/**
  * @brief  Judge is Slave Rx Address and Command is Slave RX Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave hasn't Rx Address and Command is Slave RX
  * @retval 1 Slave has Rx Address and Command is Slave RX
  */
#define __LL_I2C_SLV_IsRxAddrAndCmdIsSlvRX(__I2C__)     READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RXADI_Msk, I2C0_INTR_RXADI_Pos)

/**
  * @brief  Slave Rx Address and Command is Slave RX Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_Clr(__I2C__)   WRITE_REG((__I2C__)->INTR, I2C0_INTR_RXADI_Msk)

/**
  * @brief  Judge is Slave Rx Address and Command is Slave TX Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave hasn't Rx Address and Command is Slave TX
  * @retval 1 Slave has Rx Address and Command is Slave TX
  */
#define __LL_I2C_SLV_IsRxAddrAndCmdIsSlvTX(__I2C__)     READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_TXADI_Msk, I2C0_INTR_TXADI_Pos)

/**
  * @brief  Slave Rx Address and Command is Slave TX Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_Clr(__I2C__)   WRITE_REG((__I2C__)->INTR, I2C0_INTR_TXADI_Msk)

/**
  * @brief  Judge is Master Tx/Rx Done Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master Tx/Rx hasn't Done
  * @retval 1 Master Tx/Rx has Done
  */
#define __LL_I2C_MST_IsTxRxDone(__I2C__)                READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_MDEI_Msk, I2C0_INTR_MDEI_Pos)

/**
  * @brief  Master Tx/Rx Done Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxRxDone_Clr(__I2C__)              WRITE_REG((__I2C__)->INTR, I2C0_INTR_MDEI_Msk)

/**
  * @brief  Judge is Bus Error Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't Bus Error
  * @retval 1 is Bus Error
  */
#define __LL_I2C_IsBusErr(__I2C__)                      READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_BUSEI_Msk, I2C0_INTR_BUSEI_Pos)

/**
  * @brief  Bus Error Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_BusErr_Clr(__I2C__)                    WRITE_REG((__I2C__)->INTR, I2C0_INTR_BUSEI_Msk)

/**
  * @brief  Judge is Arbitration Fail Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't Arbitration Fail
  * @retval 1 is Arbitration Fail
  */
#define __LL_I2C_IsArbFail(__I2C__)                     READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_ARBFI_Msk, I2C0_INTR_ARBFI_Pos)

/**
  * @brief  Arbitration Fail Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_ArbFail_Clr(__I2C__)                   WRITE_REG((__I2C__)->INTR, I2C0_INTR_ARBFI_Msk)

/**
  * @brief  Judge is TxFIFO Overflow Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't TxFIFO Overflow
  * @retval 1 is TxFIFO Overflow
  */
#define __LL_I2C_IsTxFIFOOverflow(__I2C__)              READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_TXOFI_Msk, I2C0_INTR_TXOFI_Pos)

/**
  * @brief  TxFIFO Overflow Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxFIFOOverflow_Clr(__I2C__)            WRITE_REG((__I2C__)->INTR, I2C0_INTR_TXOFI_Msk)

/**
  * @brief  Judge is RxFIFO Underflow Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't RxFIFO Underflow
  * @retval 1 is RxFIFO Underflow
  */
#define __LL_I2C_IsRxFIFOUnderflow(__I2C__)             READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RXUFI_Msk, I2C0_INTR_RXUFI_Pos)

/**
  * @brief  RxFIFO Underflow Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOUnderflow_Clr(__I2C__)           WRITE_REG((__I2C__)->INTR, I2C0_INTR_RXUFI_Msk)

/**
  * @brief  Judge is RxFIFO Overflow Interrupt Pending or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't RxFIFO Overflow
  * @retval 1 is RxFIFO Overflow
  */
#define __LL_I2C_IsRxFIFOOverflow(__I2C__)              READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RXOFI_Msk, I2C0_INTR_RXOFI_Pos)

/**
  * @brief  RxFIFO Overflow Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOOverflow_Clr(__I2C__)            WRITE_REG((__I2C__)->INTR, I2C0_INTR_RXOFI_Msk)

/**
  * @brief  Judge is TxFIFO Empty Interrupt Pending or not (Auto Clear)
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't TxFIFO Empty
  * @retval 1 is TxFIFO Empty
  */
#define __LL_I2C_IsTxFIFOEmpty_IntPnd(__I2C__)          READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_TXEI_Msk, I2C0_INTR_TXEI_Pos)

/**
  * @brief  Judge is RxFIFO Full Interrupt Pending or not (Auto Clear)
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't RxFIFO Full
  * @retval 1 is RxFIFO Full
  */
#define __LL_I2C_IsRxFIFOFull_IntPnd(__I2C__)           READ_BIT_SHIFT((__I2C__)->INTR, I2C0_INTR_RXFI_Msk, I2C0_INTR_RXFI_Pos)

/**
  * @brief  All Interrupt Pending Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return All Interrupt Pending
  */
#define __LL_I2C_AllIntPnd_Get(__I2C__)                 READ_REG((__I2C__)->INTR)

/**
  * @brief  All Interrupt Pending Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_AllIntPnd_Clr(__I2C__)                 WRITE_REG((__I2C__)->INTR, 0xffffffffUL)


/**
  * @brief  Judge is RxFIFO Full or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 RxFIFO isn't Full
  * @retval 1 RxFIFO is Full
  */
#define __LL_I2C_IsRxFIFOFull(__I2C__)                  READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_RFF_Msk, I2C0_STATUS_RFF_Pos)

/**
  * @brief  Judge is RxFIFO Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 RxFIFO isn't Empty
  * @retval 1 RxFIFO is Empty
  */
#define __LL_I2C_IsRxFIFOEmpty(__I2C__)                 READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_RFE_Msk, I2C0_STATUS_RFE_Pos)

/**
  * @brief  RxFIFO Level Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return RxFIFO Level
  */
#define __LL_I2C_RxFIFOLevel_Get(__I2C__)               READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_RXFLR_Msk, I2C0_STATUS_RXFLR_Pos)

/**
  * @brief  Judge is TxFIFO Full or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 TxFIFO isn't Full
  * @retval 1 TxFIFO is Full
  */
#define __LL_I2C_IsTxFIFOFull(__I2C__)                  READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_TFF_Msk, I2C0_STATUS_TFF_Pos)

/**
  * @brief  Judge is TxFIFO Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 TxFIFO isn't Empty
  * @retval 1 TxFIFO is Empty
  */
#define __LL_I2C_IsTxFIFOEmpty(__I2C__)                 READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_TFE_Msk, I2C0_STATUS_TFE_Pos)

/**
  * @brief  TxFIFO Level Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return TxFIFO Level
  */
#define __LL_I2C_TxFIFOLevel_Get(__I2C__)               READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_TXFLR_Msk, I2C0_STATUS_TXFLR_Pos)

/**
  * @brief  Bus Arbitration Status Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return Bus Arbitration Status
  */
#define __LL_I2C_BusArbSta_Get(__I2C__)                 \
        READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_ARBSTA_Msk, I2C0_STATUS_ARBSTA_Pos)

/**
  * @brief  Judge is Bus Busy Status or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't Bus Busy Status
  * @retval 1 is Bus Busy Status
  */
#define __LL_I2C_IsBusBusy(__I2C__)                     \
        READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_BUSBSY_Msk, I2C0_STATUS_BUSBSY_Pos)

/**
  * @brief  Judge is FSM Busy or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 isn't FSM Busy
  * @retval 1 is FSM Busy
  */
#define __LL_I2C_IsFSMBusy(__I2C__)                     \
        READ_BIT_SHIFT((__I2C__)->STATUS, I2C0_STATUS_FSMBSY_Msk, I2C0_STATUS_FSMBSY_Pos)


/**
  * @brief  I2C Data Write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat data to write
  * @return None
  */
#define __LL_I2C_Dat_Write(__I2C__, dat)                WRITE_REG((__I2C__)->TXDATA, (dat & 0xffUL))

/**
  * @brief  I2C Data Read
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read data
  */
#define __LL_I2C_Dat_Read(__I2C__)                      \
        READ_BIT_SHIFT((__I2C__)->RXDATA, I2C0_RXDATA_RXDATA_Msk, I2C0_RXDATA_RXDATA_Pos)


/**
  * @brief  Slave Address Match Code Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return Slave Address Match Code
  */
#define __LL_I2C_SLV_AddrMatchCode_Get(__I2C__)         \
        READ_BIT_SHIFT((__I2C__)->RXADDR, I2C0_RXADDR_ADDR_Msk, I2C0_RXADDR_ADDR_Pos)

/**
  * @brief  Slave Transfer Direction Get
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave Transfer Direction Write
  * @retval 1 Slave Transfer Direction Read
  */
#define __LL_I2C_SLV_TransDir_Get(__I2C__)              \
        READ_BIT_SHIFT((__I2C__)->RXADDR, I2C0_RXADDR_DIR_Msk, I2C0_RXADDR_DIR_Pos)



/**
  * @brief  I2C timing start and send 8b address
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr_8b 8b address
  * @return None
  */
#define __LL_I2C_Timing_StartAddr8b(__I2C__, addr_8b)                                                   \
        do {                                                                                            \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | (0x1 & I2C0_CTRL_I2CCNT_Msk) );    \
            __LL_I2C_Dat_Write(__I2C__, addr_8b);                                                       \
        } while(0)

/**
  * @brief  I2C timing start and send 16b address
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr_16b 16b address
  * @return None
  */
#define __LL_I2C_Timing_StartAddr16b(__I2C__, addr_16b)                                                 \
        do {                                                                                            \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | (0x2 & I2C0_CTRL_I2CCNT_Msk) );    \
            __LL_I2C_Dat_Write(__I2C__, ((addr_16b >> 8) & 0xffUL));                                    \
            __LL_I2C_Dat_Write(__I2C__, ((addr_16b) & 0xffUL));                                         \
        } while(0)

/**
  * @brief  I2C timing start and send 32b address
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr_32b 32b address
  * @return None
  */
#define __LL_I2C_Timing_StartAddr32b(__I2C__, addr_32b)                                                 \
        do {                                                                                            \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | (0x4 & I2C0_CTRL_I2CCNT_Msk) );    \
            __LL_I2C_Dat_Write(__I2C__, ((addr_32b >> 24) & 0xffUL));                                   \
            __LL_I2C_Dat_Write(__I2C__, ((addr_32b >> 16) & 0xffUL));                                   \
            __LL_I2C_Dat_Write(__I2C__, ((addr_32b >> 8) & 0xffUL));                                    \
            __LL_I2C_Dat_Write(__I2C__, ((addr_32b) & 0xffUL));                                         \
        } while(0)


/**
  * @brief  I2C timing start read stop
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Read Count
  * @return None
  */
#define __LL_I2C_Timing_StartReadStop(__I2C__, cnt)                                                             \
        do {                                                                                                    \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | I2C0_CTRL_AUTOEND_Msk | I2C_DIRECT_RX |    \
            (cnt & I2C0_CTRL_I2CCNT_Msk));                                                                      \
        } while(0)

/**
  * @brief  I2C timing start read
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Read Count
  * @return None
  */
#define __LL_I2C_Timing_StartRead(__I2C__, cnt)                                                                     \
        do {                                                                                                        \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | I2C_DIRECT_RX | (cnt & I2C0_CTRL_I2CCNT_Msk)); \
        } while(0)

/**
  * @brief  I2C timing read
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Read Count
  * @return None
  */
#define __LL_I2C_Timing_Read(__I2C__, cnt)                                                      \
        do {                                                                                    \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C_DIRECT_RX | (cnt & I2C0_CTRL_I2CCNT_Msk));   \
        } while(0)

/**
  * @brief  I2C timing read stop
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Read Count
  * @return None
  */
#define __LL_I2C_Timing_ReadStop(__I2C__,cnt)                                                                           \
        do {                                                                                                            \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_AUTOEND_Msk | I2C_DIRECT_RX | (cnt & I2C0_CTRL_I2CCNT_Msk));   \
        } while(0)


/**
  * @brief  I2C timing Write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Write Count
  * @return None
  */
#define __LL_I2C_Timing_Write(__I2C__, cnt)                                                     \
        do {                                                                                    \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C_DIRECT_TX | (cnt & I2C0_CTRL_I2CCNT_Msk));   \
        } while(0)

/**
  * @brief  I2C timing start write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Write Count
  * @return None
  */
#define __LL_I2C_Timing_StartWrite(__I2C__, cnt)                                                                    \
        do {                                                                                                        \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | I2C_DIRECT_TX | (cnt & I2C0_CTRL_I2CCNT_Msk)); \
        } while(0)

/**
  * @brief  I2C timing write stop
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Write Count
  * @return None
  */
#define __LL_I2C_Timing_WriteStop(__I2C__, cnt)                                                                         \
        do {                                                                                                            \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_AUTOEND_Msk | I2C_DIRECT_TX | (cnt & I2C0_CTRL_I2CCNT_Msk));   \
        } while(0)

/**
  * @brief  I2C timing start write stop
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Write Count
  * @return None
  */
#define __LL_I2C_Timing_StartWriteStop(__I2C__, cnt)                                                            \
        do {                                                                                                    \
            __LL_I2C_CTRLRegWrite_OPT(__I2C__, I2C0_CTRL_START_Msk | I2C0_CTRL_AUTOEND_Msk | I2C_DIRECT_TX |    \
            (cnt & I2C0_CTRL_I2CCNT_Msk));                                                                      \
        } while(0)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Types I2C LL Exported Types
  * @brief    I2C LL Exported Types
  * @{
  */

/**
  * @brief I2C Uer callback function type definition
  */
typedef void (*I2C_UserCallback)(void);

/**
  * @brief I2C Instance Definition
  */
typedef enum {
    I2C_INSTANCE_0 = 0,     /*!< I2C Instance 0         */
    I2C_INSTANCE_1,         /*!< I2C Instance 1         */
    I2C_INSTANCE_2,         /*!< I2C Instance 2         */
    I2C_INSTANCE_NUMS,      /*!< I2C Instance Numbers   */
} I2C_InstanceETypeDef;

/**
  * @brief I2C State definition
  */
typedef enum {
    I2C_STATE_RESET,        /*!< Peripheral not Initialized                 */
    I2C_STATE_READY,        /*!< Peripheral Initialized and ready for use   */
    I2C_STATE_BUSY,         /*!< an internal process is ongoing             */
    I2C_STATE_BUSY_TX,      /*!< Data Transmit process is ongoing           */
    I2C_STATE_BUSY_RX,      /*!< Data Receive process is ongoing            */
    I2C_STATE_ERROR,        /*!< I2C error state                            */
} I2C_StateETypeDef;


/**
  * @brief I2C role definition
  */
typedef enum {
    I2C_ROLE_MASTER,        /*!< I2C role master        */
    I2C_ROLE_SLAVE,         /*!< I2C role slave         */
} I2C_RoleETypeDef;

/**
  * @brief I2C address bit definition
  */
typedef enum {
    I2C_ADDR_7BIT,          /*!< I2C address mode 7b    */
    I2C_ADDR_10BIT,         /*!< I2C address mode 10b   */
} I2C_AddrModeETypeDef;

/**
 * @brief I2C memmory address size definition
 */
typedef enum {
    I2C_MEMADDR_SIZE_INVALID = 0,           /*!< memmory address size invalid   */
    I2C_MEMADDR_SIZE_8BIT    = 1,           /*!< memmory address size 8bit      */
    I2C_MEMADDR_SIZE_16BIT   = 2,           /*!< memmory address size 16bit     */
    I2C_MEMADDR_SIZE_32BIT   = 4,           /*!< memmory address size 32bit     */
} I2C_MemAddrSizeETypeDef;

/**
 * @brief I2C IRQ Callback ID definition
 */
typedef enum {
    I2C_TX_CPLT_CB_ID,                      /*!< I2C Tx Completed callback ID       */
    I2C_RX_CPLT_CB_ID,                      /*!< I2C Rx Completed callback ID       */
    I2C_TX_HALF_CPLT_CB_ID,                 /*!< I2C Tx Half Completed callback ID  */
    I2C_RX_HALF_CPLT_CB_ID,                 /*!< I2C Rx Half Completed callback ID  */
    I2C_ERROR_CB_ID,                        /*!< I2C Error callback ID              */
} I2C_UserCallbackIdETypeDef;

/**
  * @brief I2C Receive Date SCL Stretching Mode definition
  */
typedef enum {
    I2C_RCV_CLK_STRCH_MODE_NON_EMPTY = 0,   /*!< When RXFIFO is not empty, the SCL  
                                                is low, and when RXFIFO is empty, 
                                                the SCL is released                 */
    I2C_RCV_CLK_STRCH_MODE_FULL,            /*!< When RXFIFO is full, SCL is held 
                                                down, and when RXFIFO is not full, 
                                                SCL is released                     */
} I2C_RcvClkStrchModeETypeDef;


/**
  * @brief I2C IRQ Callback structure definition
  */
typedef struct __I2C_UserCallbackTypeDef {
    I2C_UserCallback TxCpltCallback;        /*!< I2C Tx Completed callback          */
    I2C_UserCallback RxCpltCallback;        /*!< I2C Rx Completed callback          */
    I2C_UserCallback TxHalfCpltCallback;    /*!< I2C Tx Half Completed callback     */
    I2C_UserCallback RxHalfCpltCallback;    /*!< I2C Rx Half Completed callback     */
    I2C_UserCallback ErrorCallback;         /*!< I2C Error callback                 */
} I2C_UserCallbackTypeDef;

/**
  * @brief I2C LL Config Type Definition
  */
typedef struct __I2C_LLCfgTypeDef {
    uint8_t tx_fifo_empty_thres;                        /*!< TxFIFO Empty Threshold                 */
    uint8_t rx_fifo_full_thres;                         /*!< RxFIFO Full Threshold                  */
    uint16_t mst_tmext_timing;                          /*!< Master Tmext Timing                    */
    uint16_t slv_tsext_timing;                          /*!< Slave Tsext Timing                     */
    bool rcv_clk_strch_en;                              /*!< Receive Data SCL Stretching Enable     */
    I2C_RcvClkStrchModeETypeDef rcv_clk_strch_mode;     /*!< Receive Data SCL Stretching Mode       */
    bool slv_opt_addr_en;                               /*!< Optional Slave Address Enable          */
    uint32_t slv_opt_addr;                              /*!< Optional Slave Address                 */
    uint32_t slv_opt_addr_mask;                         /*!< Optional Slave Address Mask            */
    bool timing_cfg_en;                                 /*!< Timing Config Enable                   */
    bool timing_cfg_auto_set;                           /*!< Timing Config Auto Set                 */
    uint8_t spike_suppr_limit;                          /*!< Spike Suppression Limit                */
    uint8_t slv_data_setup_time;                        /*!< Data Setup Time                        */
    uint8_t data_setup_time;                            /*!< Slave Data Setup Time                  */
    uint8_t data_hold_time;                             /*!< Data Hold Time                         */
} I2C_LLCfgTypeDef;

/**
  * @brief I2C user config
  */
typedef struct __I2C_UserCfgTypeDef {
    I2C_RoleETypeDef        role;           /*!< role                       */
    I2C_AddrModeETypeDef    addr_mode;      /*!< address mode               */
    I2C_LLCfgTypeDef       *ll_cfg;         /*!< Optional LL Config Pointer */
    I2C_UserCallbackTypeDef user_callback;  /*!< User Callback              */
    uint32_t baudrate;                      /*!< baudrate                   */
    uint16_t slave_addr;                    /*!< slave address              */
} I2C_UserCfgTypeDef;

/**
  * @brief I2C frame definition
  */
typedef struct __I2C_FrameTypeDef {
    uint16_t target_addr;                   /*!< target address         */
    uint32_t mem_addr;                      /*!< memory address         */
    I2C_MemAddrSizeETypeDef mem_addr_size;  /*!< memory address size    */
    uint8_t  *buf;                          /*!< buffer pointer         */
    uint16_t buf_len;                       /*!< buffer length          */

    //Smbus
    uint8_t smbus_cmd;                      /*!< smbus_command          */
} I2C_FrameTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup I2C_LL_Exported_Functions
  * @{
  */

/** @addtogroup I2C_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_I2C_Init(I2C_TypeDef *Instance, I2C_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_I2C_DeInit(I2C_TypeDef *Instance);
LL_StatusETypeDef LL_I2C_Reset(I2C_TypeDef *Instance);
void LL_I2C_MspInit(I2C_TypeDef *Instance);
void LL_I2C_MspDeInit(I2C_TypeDef *Instance);
LL_StatusETypeDef LL_I2C_RegisterCallback(I2C_TypeDef *Instance, I2C_UserCallbackIdETypeDef CallbackID, I2C_UserCallback pCallback);
LL_StatusETypeDef LL_I2C_UnRegisterCallback(I2C_TypeDef *Instance, I2C_UserCallbackIdETypeDef CallbackID);
/**
  * @}
  */


/** @addtogroup I2C_LL_Exported_Functions_Group2
  * @{
  */
/******* Blocking mode: Polling */
LL_StatusETypeDef LL_I2C_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_I2C_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_I2C_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_I2C_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_SMBUS_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_SMBUS_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_SMBUS_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);
LL_StatusETypeDef LL_SMBUS_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout);

/******* Non-Blocking mode: Interrupt */
LL_StatusETypeDef LL_I2C_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);

#ifdef LL_DMA_MODULE_ENABLED
/******* Non-Blocking mode: DMA */
LL_StatusETypeDef LL_I2C_MasterRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_MasterWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_MasterRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_MasterWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
#endif
/**
  * @}
  */


/** @addtogroup I2C_LL_Exported_Functions_Group3
  * @{
  */
/******* Blocking mode: Polling */
LL_StatusETypeDef LL_I2C_Master_Transmit(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_Master_Receive(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_Slave_Transmit(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_Slave_Receive(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_Mem_Write(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                   I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_Mem_Read(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                  I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/******* Non-Blocking mode: Interrupt */
LL_StatusETypeDef LL_I2C_Master_Transmit_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Master_Receive_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Slave_Transmit_IT(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Slave_Receive_IT(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Mem_Write_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                      I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Mem_Read_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                     I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size);

#ifdef LL_DMA_MODULE_ENABLED
/******* Non-Blocking mode: DMA */
LL_StatusETypeDef LL_I2C_Master_Transmit_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Master_Receive_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Slave_Transmit_DMA(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Slave_Receive_DMA(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Mem_Write_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                       I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size);
LL_StatusETypeDef LL_I2C_Mem_Read_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                      I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size);
#endif
/**
  * @}
  */


/** @addtogroup I2C_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_I2C_IRQHandler(I2C_TypeDef *Instance);

void LL_I2C_RxFullCallback(I2C_TypeDef *Instance);
void LL_I2C_TxEmptyCallback(I2C_TypeDef *Instance);
void LL_I2C_RxOverflowCallback(I2C_TypeDef *Instance);
void LL_I2C_RxUnderflowCallback(I2C_TypeDef *Instance);
void LL_I2C_TxOverflowCallback(I2C_TypeDef *Instance);
void LL_I2C_ArbFailCallback(I2C_TypeDef *Instance);
void LL_I2C_BusErrCallback(I2C_TypeDef *Instance);
void LL_I2C_MST_TxRxDoneCallback(I2C_TypeDef *Instance);
void LL_I2C_SLV_RxAddrAndCmdIsSlvTXCallback(I2C_TypeDef *Instance);
void LL_I2C_SLV_RxAddrAndCmdIsSlvRXCallback(I2C_TypeDef *Instance);
void LL_I2C_DetStartCallback(I2C_TypeDef *Instance);
void LL_I2C_DetStopCallback(I2C_TypeDef *Instance);
void LL_I2C_DetRestartCallback(I2C_TypeDef *Instance);
void LL_I2C_RxNACKCallback(I2C_TypeDef *Instance);
void LL_I2C_MST_DetAlertSigCallback(I2C_TypeDef *Instance);
void LL_I2C_MST_TmextTimeoutCallback(I2C_TypeDef *Instance);
void LL_I2C_SLV_TsextTimeoutCallback(I2C_TypeDef *Instance);
void LL_I2C_RxPECErrCallback(I2C_TypeDef *Instance);
void LL_I2C_SLV_RxGenCallCallback(I2C_TypeDef *Instance);
void LL_I2C_MST_TxAddrDoneCallback(I2C_TypeDef *Instance);
void LL_I2C_SLV_WaitTxDatCallback(I2C_TypeDef *Instance);
void LL_I2C_MST_OnHoldCallback(I2C_TypeDef *Instance);
void LL_I2C_BusTimeoutCallback(I2C_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_I2C_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

