/**
  ******************************************************************************
  * @file    tae32f53xx_ll_i2c.h
  * @author  MCD Application Team
  * @brief   Header file for I2C LL module.
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
#ifndef _TMF5XXX_LL_I2C_H_
#define _TMF5XXX_LL_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"
#ifdef LL_DMA_MODULE_ENABLED
#include "tae32f53xx_ll_dma.h"
#endif


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup I2C_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Constants I2C LL Exported Constants
  * @brief    I2C LL Exported Constants
  * @{
  */

/**
  * @brief I2C SS SPEED Max Macro Define
  */
#define I2C_SS_SPEED_MAX                    (100000UL)

/**
  * @brief I2C FS SPEED Max Macro Define
  */
#define I2C_FS_SPEED_MAX                    (400000UL)

/**
  * @brief I2C FS PLUS SPEED Max Macro Define
  */
#define I2C_FS_PLUS_SPEED_MAX               (1000000UL)

/**
  * @brief I2C HS SPEED Max Macro Define
  */
#define I2C_HS_SPEED_MAX                    (3400000UL)


/**
  * @brief I2C FIFO Depth Define
  */
#define I2C_FIFO_DEPTH                      (16)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Macros I2C LL Exported Macros
  * @brief    I2C LL Exported Macros
  * @{
  */

/**
  * @brief  I2C SMBUS Persistant Slave Address Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvPersistant_En(__I2C__)    SET_BIT((__I2C__)->CON, I2C_SMBUS_PST_SLV_ADDR_EN_Msk)

/**
  * @brief  I2C SMBUS Persistant Slave Address Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvPersistant_Dis(__I2C__)   CLEAR_BIT((__I2C__)->CON, I2C_SMBUS_PST_SLV_ADDR_EN_Msk)

/**
  * @brief  I2C SMBUS ARP Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARP_En(__I2C__)              SET_BIT((__I2C__)->CON, I2C_SMBUS_ARP_EN_Msk)

/**
  * @brief  I2C SMBUS ARP Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARP_Dis(__I2C__)             CLEAR_BIT((__I2C__)->CON, I2C_SMBUS_ARP_EN_Msk)

/**
  * @brief  I2C SMBUS Slave Quick Cmd Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvQuickCmd_En(__I2C__)      SET_BIT((__I2C__)->CON, I2C_SMBUS_SLV_QUICK_CMD_EN_Msk)

/**
  * @brief  I2C SMBUS Slave Quick Cmd Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvQuickCmd_Dis(__I2C__)     CLEAR_BIT((__I2C__)->CON, I2C_SMBUS_SLV_QUICK_CMD_EN_Msk)

/**
  * @brief  I2C Optional SAR Control Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_OptionalSarCtrl_Set(__I2C__)       SET_BIT((__I2C__)->CON, I2C_OPTIONAL_SAR_CTRL_Msk)

/**
  * @brief  I2C Master Bus Clear Feature Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_BusClrFeature_En(__I2C__)      SET_BIT((__I2C__)->CON, I2C_BUS_CLEAR_FEATURE_CTRL_Msk)

/**
  * @brief  I2C Master Bus Clear Feature Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_BusClrFeature_Dis(__I2C__)     CLEAR_BIT((__I2C__)->CON, I2C_BUS_CLEAR_FEATURE_CTRL_Msk)

/**
  * @brief  I2C Stop Detect If Master Active Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_StopDetIfActive_Set(__I2C__)   SET_BIT((__I2C__)->CON, I2C_STOP_DET_IF_MASTER_ACT_Msk)

/**
  * @brief  I2C Stop Detect If Master Active Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_StopDetIfActive_Clr(__I2C__)   CLEAR_BIT((__I2C__)->CON, I2C_STOP_DET_IF_MASTER_ACT_Msk)

/**
  * @brief  I2C RX FIFO Full Hold Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOFullHold_En(__I2C__)         SET_BIT((__I2C__)->CON, I2C_RX_FIFO_FULL_HLD_CTRL_Msk)

/**
  * @brief  I2C RX FIFO Full Hold Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFIFOFullHold_Dis(__I2C__)        CLEAR_BIT((__I2C__)->CON, I2C_RX_FIFO_FULL_HLD_CTRL_Msk)

/**
  * @brief  I2C TX Empty Control Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxEmptyCtrl_Set(__I2C__)           SET_BIT((__I2C__)->CON, I2C_TX_EMPTY_CTRL_Msk)

/**
  * @brief  I2C TX Empty Control Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxEmptyCtrl_Clr(__I2C__)           CLEAR_BIT((__I2C__)->CON, I2C_TX_EMPTY_CTRL_Msk)

/**
  * @brief  I2C Slave Stop Detect If Addressed Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_StopDetIfAddressed_Set(__I2C__)    SET_BIT((__I2C__)->CON, I2C_STOP_DET_IFADDRESSED_Msk)

/**
  * @brief  I2C Slave Stop Detect If Addressed Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_StopDetIfAddressed_Clr(__I2C__)    CLEAR_BIT((__I2C__)->CON, I2C_STOP_DET_IFADDRESSED_Msk)

/**
  * @brief  I2C Slave Mode Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLAVE_Mode_En(__I2C__)             CLEAR_BIT((__I2C__)->CON, I2C_SLAVE_DISABLE_Msk)

/**
  * @brief  I2C Slave Mode Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLAVE_Mode_Dis(__I2C__)            SET_BIT((__I2C__)->CON, I2C_SLAVE_DISABLE_Msk)

/**
  * @brief  I2C Master Restart Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_Restart_En(__I2C__)            SET_BIT((__I2C__)->CON, I2C_RESTART_EN_Msk)

/**
  * @brief  I2C Master Restart Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_Restart_Dis(__I2C__)           CLEAR_BIT((__I2C__)->CON, I2C_RESTART_EN_Msk)

/**
  * @brief  I2C Master 7bit Address Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_7bAddr_Set(__I2C__)            CLEAR_BIT((__I2C__)->CON, I2C_10BITADDR_MASTER_Msk)

/**
  * @brief  I2C Master 10bit Address Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_10bAddr_Set(__I2C__)           SET_BIT((__I2C__)->CON, I2C_10BITADDR_MASTER_Msk)

/**
  * @brief  I2C Slave 7bit Address Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_7bAddr_Set(__I2C__)            CLEAR_BIT((__I2C__)->CON, I2C_10BITADDR_SLAVE_Msk)

/**
  * @brief  I2C Slave 10bit Address Mode Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_10bAddr_Set(__I2C__)           SET_BIT((__I2C__)->CON, I2C_10BITADDR_SLAVE_Msk)

/**
  * @brief  I2C Speed Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  speed I2C Speed
  * @return None
  */
#define __LL_I2C_Speed_Set(__I2C__, speed)          MODIFY_REG((__I2C__)->CON, I2C_SPEED_Msk, speed)

/**
  * @brief  I2C Master Mode Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MASTER_Mode_En(__I2C__)            SET_BIT((__I2C__)->CON, I2C_MASTER_MODE_Msk)

/**
  * @brief  I2C Master Mode Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MASTER_Mode_Dis(__I2C__)           CLEAR_BIT((__I2C__)->CON, I2C_MASTER_MODE_Msk)

/**
  * @brief  I2C Master Mode is Enable or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 I2C isn't Master Mode
  * @retval 1 I2C is Master Mode
  */
#define __LL_I2C_IsMasterMode(__I2C__)              READ_BIT((__I2C__)->CON, I2C_MASTER_MODE_Msk)

/**
  * @brief  I2C TAR SMBUD Quick Cmd Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_SmbusQuickCmd_Set(__I2C__)     SET_BIT((__I2C__)->TAR, I2C_SMBUS_QUICK_CMD_Msk)

/**
  * @brief  I2C TAR SMBUD Quick Cmd Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_SmbusQuickCmd_Clr(__I2C__)     CLEAR_BIT((__I2C__)->TAR, I2C_SMBUS_QUICK_CMD_Msk)

/**
  * @brief  I2C TAR Device ID Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_DevID_Set(__I2C__)             SET_BIT((__I2C__)->TAR, I2C_TAR_DEV_ID_Msk)

/**
  * @brief  I2C TAR Device ID Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_DevID_Clr(__I2C__)             CLEAR_BIT((__I2C__)->TAR, I2C_TAR_DEV_ID_Msk)

/**
  * @brief  I2C TAR Master 7bit Address Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_MST_7bAddr_Set(__I2C__)        CLEAR_BIT((__I2C__)->TAR, I2C_TAR_10BITADDR_MASTER_Msk)

/**
  * @brief  I2C TAR Master 10bit Address Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_MST_10bAddr_Set(__I2C__)       SET_BIT((__I2C__)->TAR, I2C_TAR_10BITADDR_MASTER_Msk)

/**
  * @brief  I2C TAR Special Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_Special_Set(__I2C__)           SET_BIT((__I2C__)->TAR, I2C_SPECIAL_Msk)

/**
  * @brief  I2C TAR Special Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_Special_Clr(__I2C__)           CLEAR_BIT((__I2C__)->TAR, I2C_SPECIAL_Msk)

/**
  * @brief  I2C TAR GC OR Start Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_GcOrStart_Set(__I2C__)         SET_BIT((__I2C__)->TAR, I2C_GC_OR_START_Msk)

/**
  * @brief  I2C TAR GC OR Start Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TAR_GcOrStart_Clr(__I2C__)         CLEAR_BIT((__I2C__)->TAR, I2C_GC_OR_START_Msk)

/**
  * @brief  I2C Master TAR Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tar I2C Master TAR
  * @return None
  */
#define __LL_I2C_TAR_Set(__I2C__, tar)              MODIFY_REG((__I2C__)->TAR, I2C_TAR_Msk, ((tar & 0x3ffUL) << I2C_TAR_Pos))


/**
  * @brief  I2C Slave SAR Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tar I2C Slave SAR
  * @return None
  */
#define __LL_I2C_SAR_Set(__I2C__, sar)              MODIFY_REG((__I2C__)->SAR, I2C_SAR_Msk, ((sar & 0x3ffUL) << I2C_SAR_Pos))


/**
  * @brief  Judge Is First Data Byte or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't first data byte
  * @retval 1 Is first data byte
  */
#define __LL_I2C_IsFirstDataByte(__I2C__)   (READ_BIT((__I2C__)->DCMD, I2C_FIRST_DATA_BYTE_Msk) >> I2C_FIRST_DATA_BYTE_Pos)

/**
  * @brief  I2C Restart Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Restart_Set(__I2C__)               SET_BIT((__I2C__)->DCMD, I2C_RESTART_Msk)

/**
  * @brief  I2C Restart Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Restart_Clr(__I2C__)               CLEAR_BIT((__I2C__)->DCMD, I2C_RESTART_Msk)

/**
  * @brief  I2C Stop Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Stop_Set(__I2C__)                  SET_BIT((__I2C__)->DCMD, I2C_STOP_Msk)

/**
  * @brief  I2C Stop Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Stop_Clr(__I2C__)                  CLEAR_BIT((__I2C__)->DCMD, I2C_STOP_Msk)

/**
  * @brief  I2C Master Cmd Read Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_CmdRead_Set(__I2C__)           SET_BIT((__I2C__)->DCMD, I2C_CMD_Msk)

/**
  * @brief  I2C Master Cmd Write Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_CmdWrite_Set(__I2C__)          CLEAR_BIT((__I2C__)->DCMD, I2C_CMD_Msk)

/**
  * @brief  I2C Data Write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat data to write
  * @return None
  */
#define __LL_I2C_DAT_Write(__I2C__, dat)            MODIFY_REG((__I2C__)->DCMD, I2C_DAT_Msk, (((dat) & 0xffUL) << I2C_DAT_Pos))

/**
  * @brief  I2C Data Read
  * @param  __I2C__ Specifies I2C peripheral
  * @return read data
  */
#define __LL_I2C_DAT_Read(__I2C__)                  (READ_BIT((__I2C__)->DCMD, I2C_DAT_Msk) >> I2C_DAT_Pos)

/**
  * @brief  I2C timing start and send 8b address
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr_8b 8b address
  * @return None
  */
#define __LL_I2C_Timing_RestartAddr8b(__I2C__, addr_8b)                                             \
        do {                                                                                        \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | ((addr_8b & 0xffUL) << I2C_DAT_Pos));  \
        } while(0)

/**
  * @brief  I2C timing restart and send 16b address
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr_16b 16b address
  * @return None
  */
#define __LL_I2C_Timing_RestartAddr16b(__I2C__, addr_16b)                                                       \
        do {                                                                                                    \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | (((addr_16b >> 8) & 0xffUL) << I2C_DAT_Pos));      \
            WRITE_REG((__I2C__)->DCMD,  ((addr_16b & 0xffUL) << I2C_DAT_Pos));                              \
        } while(0)

/**
  * @brief  I2C timing restart and send 32b address
  * @param  __I2C__ Specifies I2C peripheral
  * @param  addr_32b 32b address
  * @return None
  */
#define __LL_I2C_Timing_RestartAddr32b(__I2C__, addr_32b)                                                       \
        do {                                                                                                    \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | (((addr_32b >> 24) & 0xffUL) << I2C_DAT_Pos));   \
            WRITE_REG((__I2C__)->DCMD,  (((addr_32b >> 16) & 0xffUL) << I2C_DAT_Pos));                      \
            WRITE_REG((__I2C__)->DCMD,  (((addr_32b >> 8) & 0xffUL) << I2C_DAT_Pos));                       \
            WRITE_REG((__I2C__)->DCMD,  ((addr_32b & 0xffUL) << I2C_DAT_Pos));                              \
        } while(0)

/**
  * @brief  I2C timing restart read stop
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Timing_RestartReadStop(__I2C__)                                            \
        do {                                                                                \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | I2C_CMD_READ | I2C_STOP_Msk);  \
        } while(0)

/**
  * @brief  I2C timing restart read
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Timing_RestartRead(__I2C__)                                \
        do {                                                                \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | I2C_CMD_READ); \
        } while(0)

/**
  * @brief  I2C timing read
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Timing_Read(__I2C__)                       \
        do {                                                \
            WRITE_REG((__I2C__)->DCMD, I2C_CMD_READ);   \
        } while(0)

/**
  * @brief  I2C timing read stop
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Timing_ReadStop(__I2C__)                                   \
        do {                                                                \
            WRITE_REG((__I2C__)->DCMD, I2C_CMD_READ | I2C_STOP_Msk);    \
        } while(0)

/**
  * @brief  I2C timing write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat write data
  * @return None
  */
#define __LL_I2C_Timing_Write(__I2C__, dat)                                     \
        do {                                                                    \
            WRITE_REG((__I2C__)->DCMD, (((dat) & 0xffUL) << I2C_DAT_Pos));  \
        } while(0)

/**
  * @brief  I2C timing restart write
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat write data
  * @return None
  */
#define __LL_I2C_Timing_RestartWrite(__I2C__, dat)                                                      \
        do {                                                                                            \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | (((dat) & 0xffUL) << I2C_DAT_Pos));        \
        } while(0)


/**
  * @brief  I2C timing write stop
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat write data
  * @return None
  */
#define __LL_I2C_Timing_WriteStop(__I2C__, dat)                                                 \
        do {                                                                                    \
            WRITE_REG((__I2C__)->DCMD, I2C_STOP_Msk | (((dat) & 0xffUL) << I2C_DAT_Pos));   \
        } while(0)

/**
  * @brief  I2C timing restart write stop
  * @param  __I2C__ Specifies I2C peripheral
  * @param  dat write data
  * @return None
  */
#define __LL_I2C_Timing_RestartWriteStop(__I2C__, dat)                                                                  \
        do {                                                                                                            \
            WRITE_REG((__I2C__)->DCMD, I2C_RESTART_Msk | I2C_STOP_Msk | (((dat) & 0xffUL) << I2C_DAT_Pos));         \
        } while(0)


/**
  * @brief  I2C SS SCL High Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt I2C SS SCL High Count
  * @return None
  */
#define __LL_I2C_SS_SCLHcnt_Set(__I2C__, cnt)       \
        MODIFY_REG((__I2C__)->SSHCNT, I2C_SS_SCL_HCNT_Msk, ((cnt & 0xffffUL) << I2C_SS_SCL_HCNT_Pos))


/**
  * @brief  I2C SS SCL Low Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt I2C SS SCL Low Count
  * @return None
  */
#define __LL_I2C_SS_SCLLcnt_Set(__I2C__, cnt)       \
        MODIFY_REG((__I2C__)->SSLCNT, I2C_SS_SCL_LCNT_Msk, ((cnt & 0xffffUL) << I2C_SS_SCL_LCNT_Pos))


/**
  * @brief  I2C FS SCL High Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt I2C FS SCL High Count
  * @return None
  */
#define __LL_I2C_FS_SCLHcnt_Set(__I2C__, cnt)       \
        MODIFY_REG((__I2C__)->FSHCNT, I2C_FS_SCL_HCNT_Msk, ((cnt & 0xffffUL) << I2C_FS_SCL_HCNT_Pos))


/**
  * @brief  I2C FS SCL Low Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt I2C FS SCL Low Count
  * @return None
  */
#define __LL_I2C_FS_SCLLcnt_Set(__I2C__, cnt)       \
        MODIFY_REG((__I2C__)->FSLCNT, I2C_FS_SCL_LCNT_Msk, ((cnt & 0xffffUL) << I2C_FS_SCL_LCNT_Pos))


/**
  * @brief  Judge SCL Stuck at Low or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SCL isn't Stuck at Low
  * @retval 1 SCL is Stuck at Low
  */
#define __LL_I2C_IsSCLStuckAtLow(__I2C__)           \
        (READ_BIT((__I2C__)->INTRST, I2C_SCL_STK_AT_LOW_INT_STA_Msk) >> I2C_SCL_STK_AT_LOW_INT_STA_Pos)

/**
  * @brief  Judge Master On Hold or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master isn't On Hold
  * @retval 1 Master is On Hold
  */
#define __LL_I2C_MST_IsOnHold(__I2C__)              \
        (READ_BIT((__I2C__)->INTRST, I2C_MST_ON_HOLD_INT_STA_Msk) >> I2C_MST_ON_HOLD_INT_STA_Pos)

/**
  * @brief  Judge Slave is Restart Detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave isn't Restart Detect
  * @retval 1 Slave is Restart Detect
  */
#define __LL_I2C_SLV_IsRestartDet(__I2C__)          \
        (READ_BIT((__I2C__)->INTRST, I2C_RESTART_DET_INT_STA_Msk) >> I2C_RESTART_DET_INT_STA_Pos)

/**
  * @brief  Judge Slave Genaral Call or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't Genaral Call
  * @retval 1 Is Genaral Call
  */
#define __LL_I2C_SLV_IsGenCall(__I2C__)             \
        (READ_BIT((__I2C__)->INTRST, I2C_GEN_CALL_INT_STA_Msk) >> I2C_GEN_CALL_INT_STA_Pos)

/**
  * @brief  Judge Start Detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't start detect
  * @retval 1 Is start detect
  */
#define __LL_I2C_IsStartDet(__I2C__)                \
        (READ_BIT((__I2C__)->INTRST, I2C_START_DET_INT_STA_Msk) >> I2C_START_DET_INT_STA_Pos)

/**
  * @brief  Judge Stop Detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't stop detect
  * @retval 1 Is stop detect
  */
#define __LL_I2C_IsStopDet(__I2C__)                 \
        (READ_BIT((__I2C__)->INTRST, I2C_STOP_DET_INT_STA_Msk) >> I2C_STOP_DET_INT_STA_Pos)

/**
  * @brief  Judge I2C Activity or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 I2C isn't activity
  * @retval 1 I2C is activity
  */
#define __LL_I2C_IsActivityInt(__I2C__)             \
        (READ_BIT((__I2C__)->INTRST, I2C_ACTIVITY_INT_STA_Msk) >> I2C_ACTIVITY_INT_STA_Pos)

/**
  * @brief  Judge Slave RX Done or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave isn't RX Done
  * @retval 1 Slave is RX Done
  */
#define __LL_I2C_SLV_IsRxDone(__I2C__)              \
        (READ_BIT((__I2C__)->INTRST, I2C_RX_DONE_INT_STA_Msk) >> I2C_RX_DONE_INT_STA_Pos)

/**
  * @brief  Judge TX Abort or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't TX Abort
  * @retval 1 Is TX Abort
  */
#define __LL_I2C_IsTxAbort(__I2C__)                 \
        (READ_BIT((__I2C__)->INTRST, I2C_TX_ABRT_INT_STA_Msk) >> I2C_TX_ABRT_INT_STA_Pos)

/**
  * @brief  Judge Slave Read Request or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave isn't Read Request
  * @retval 1 Slave is Read Request
  */
#define __LL_I2C_SLV_IsReadReq(__I2C__)             \
        (READ_BIT((__I2C__)->INTRST, I2C_RD_REQ_INT_STA_Msk) >> I2C_RD_REQ_INT_STA_Pos)

/**
  * @brief  Judge TX Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't TX Empty
  * @retval 1 Is TX Empty
  */
#define __LL_I2C_IsTxEmpty(__I2C__)                 \
        (READ_BIT((__I2C__)->INTRST, I2C_TX_EMPTY_INT_STA_Msk) >> I2C_TX_EMPTY_INT_STA_Pos)

/**
  * @brief  Judge TX Over or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't TX Over
  * @retval 1 Is TX Over
  */
#define __LL_I2C_IsTxOver(__I2C__)                  \
        (READ_BIT((__I2C__)->INTRST, I2C_TX_OVER_INT_STA_Msk) >> I2C_TX_OVER_INT_STA_Pos)

/**
  * @brief  Judge RX Full or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't RX Full
  * @retval 1 Is RX Full
  */
#define __LL_I2C_IsRxFull(__I2C__)                  \
        (READ_BIT((__I2C__)->INTRST, I2C_RX_FULL_INT_STA_Msk) >> I2C_RX_FULL_INT_STA_Pos)

/**
  * @brief  Judge RX Over or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't RX Over
  * @retval 1 Is RX Over
  */
#define __LL_I2C_IsRxOver(__I2C__)                  \
        (READ_BIT((__I2C__)->INTRST, I2C_RX_OVER_INT_STA_Msk) >> I2C_RX_OVER_INT_STA_Pos)

/**
  * @brief  Judge RX Under or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't RX Under
  * @retval 1 Is RX Under
  */
#define __LL_I2C_IsRxUnder(__I2C__)                 \
        (READ_BIT((__I2C__)->INTRST, I2C_RX_UNDER_INT_STA_Msk) >> I2C_RX_UNDER_INT_STA_Pos)

/**
  * @brief  I2C interrupt status get
  * @param  __I2C__ Specifies I2C peripheral
  * @return I2C interrupt status
  */
#define __LL_I2C_IntSta_Get(__I2C__)                (READ_REG((__I2C__)->INTRST))

/**
  * @brief  I2C SCL Stuck at low Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SCLStuckAtLow_INT_En(__I2C__)      SET_BIT((__I2C__)->INTRMS, I2C_SCL_STK_AT_LOW_INT_EN_Msk)

/**
  * @brief  I2C SCL Stuck at low Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SCLStuckAtLow_INT_Dis(__I2C__)     CLEAR_BIT((__I2C__)->INTRMS, I2C_SCL_STK_AT_LOW_INT_EN_Msk)

/**
  * @brief  I2C Master on hold Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_OnHold_INT_En(__I2C__)         SET_BIT((__I2C__)->INTRMS, I2C_MST_ON_HOLD_INT_EN_Msk)

/**
  * @brief  I2C Master on hold Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_OnHold_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->INTRMS, I2C_MST_ON_HOLD_INT_EN_Msk)

/**
  * @brief  I2C Slave Restart Detect Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RestartDet_INT_En(__I2C__)     SET_BIT((__I2C__)->INTRMS, I2C_RESTART_DET_INT_EN_Msk)

/**
  * @brief  I2C Slave Restart Detect Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RestartDet_INT_Dis(__I2C__)    CLEAR_BIT((__I2C__)->INTRMS, I2C_RESTART_DET_INT_EN_Msk)

/**
  * @brief  I2C Slave Genaral Call Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_GenCall_INT_En(__I2C__)        SET_BIT((__I2C__)->INTRMS, I2C_GEN_CALL_INT_EN_Msk)

/**
  * @brief  I2C Slave Genaral Call Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_GenCall_INT_Dis(__I2C__)       CLEAR_BIT((__I2C__)->INTRMS, I2C_GEN_CALL_INT_EN_Msk)

/**
  * @brief  I2C Start Detect Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_StartDet_INT_En(__I2C__)           SET_BIT((__I2C__)->INTRMS, I2C_START_DET_INT_EN_Msk)

/**
  * @brief  I2C Start Detect Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_StartDet_INT_Dis(__I2C__)          CLEAR_BIT((__I2C__)->INTRMS, I2C_START_DET_INT_EN_Msk)

/**
  * @brief  I2C Stop Detect Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_StopDet_INT_En(__I2C__)            SET_BIT((__I2C__)->INTRMS, I2C_STOP_DET_INT_EN_Msk)

/**
  * @brief  I2C Stop Detect Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_StopDet_INT_Dis(__I2C__)           CLEAR_BIT((__I2C__)->INTRMS, I2C_STOP_DET_INT_EN_Msk)

/**
  * @brief  I2C Activity Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Activity_INT_En(__I2C__)           SET_BIT((__I2C__)->INTRMS, I2C_ACTIVITY_INT_EN_Msk)

/**
  * @brief  I2C Activity Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Activity_INT_Dis(__I2C__)          CLEAR_BIT((__I2C__)->INTRMS, I2C_ACTIVITY_INT_EN_Msk)

/**
  * @brief  I2C Slave RX Done Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxDone_INT_En(__I2C__)         SET_BIT((__I2C__)->INTRMS, I2C_RX_DONE_INT_EN_Msk)

/**
  * @brief  I2C Slave RX Done Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_RxDone_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->INTRMS, I2C_RX_DONE_INT_EN_Msk)

/**
  * @brief  I2C TX Abort Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxAbort_INT_En(__I2C__)            SET_BIT((__I2C__)->INTRMS, I2C_TX_ABRT_INT_EN_Msk)

/**
  * @brief  I2C TX Abort Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxAbort_INT_Dis(__I2C__)           CLEAR_BIT((__I2C__)->INTRMS, I2C_TX_ABRT_INT_EN_Msk)

/**
  * @brief  I2C Slave Read Request Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_ReadReq_INT_En(__I2C__)        SET_BIT((__I2C__)->INTRMS, I2C_RD_REQ_INT_EN_Msk)

/**
  * @brief  I2C Slave Read Request Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_ReadReq_INT_Dis(__I2C__)       CLEAR_BIT((__I2C__)->INTRMS, I2C_RD_REQ_INT_EN_Msk)

/**
  * @brief  I2C TX Empty Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxEmpty_INT_En(__I2C__)            SET_BIT((__I2C__)->INTRMS, I2C_TX_EMPTY_INT_EN_Msk)

/**
  * @brief  I2C TX Empty Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxEmpty_INT_Dis(__I2C__)           CLEAR_BIT((__I2C__)->INTRMS, I2C_TX_EMPTY_INT_EN_Msk)

/**
  * @brief  I2C TX Over Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxOver_INT_En(__I2C__)             SET_BIT((__I2C__)->INTRMS, I2C_TX_OVER_INT_EN_Msk)

/**
  * @brief  I2C TX Over Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxOver_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTRMS, I2C_TX_OVER_INT_EN_Msk)

/**
  * @brief  I2C RX Full Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFull_INT_En(__I2C__)             SET_BIT((__I2C__)->INTRMS, I2C_RX_FULL_INT_EN_Msk)

/**
  * @brief  I2C RX Full Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxFull_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTRMS, I2C_RX_FULL_INT_EN_Msk)

/**
  * @brief  I2C RX Over Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxOver_INT_En(__I2C__)             SET_BIT((__I2C__)->INTRMS, I2C_RX_OVER_INT_EN_Msk)

/**
  * @brief  I2C RX Over Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxOver_INT_Dis(__I2C__)            CLEAR_BIT((__I2C__)->INTRMS, I2C_RX_OVER_INT_EN_Msk)

/**
  * @brief  I2C RX Under Interrupt Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxUnder_INT_En(__I2C__)            SET_BIT((__I2C__)->INTRMS, I2C_RX_UNDER_INT_EN_Msk)

/**
  * @brief  I2C RX Under Interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxUnder_INT_Dis(__I2C__)           CLEAR_BIT((__I2C__)->INTRMS, I2C_RX_UNDER_INT_EN_Msk)


/**
  * @brief  Judge SCL Stuck at Low Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SCL isn't Stuck at Low
  * @retval 1 SCL is Stuck at Low
  */
#define __LL_I2C_IsSCLStuckAtLow_Raw(__I2C__)       \
        (READ_BIT((__I2C__)->RINTRST, I2C_SCL_STK_AT_LOW_RAW_INT_STA_Msk) >> I2C_SCL_STK_AT_LOW_RAW_INT_STA_Pos)

/**
  * @brief  Judge Master On Hold Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master isn't On Hold
  * @retval 1 Master is On Hold
  */
#define __LL_I2C_MST_IsOnHold_Raw(__I2C__)          \
        (READ_BIT((__I2C__)->RINTRST, I2C_MST_ON_HOLD_RAW_INT_STA_Msk) >> I2C_MST_ON_HOLD_RAW_INT_STA_Pos)

/**
  * @brief  Judge Slave is Restart Detect Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave isn't Restart Detect
  * @retval 1 Slave is Restart Detect
  */
#define __LL_I2C_SLV_IsRestartDet_Raw(__I2C__)      \
        (READ_BIT((__I2C__)->RINTRST, I2C_RESTART_DET_RAW_INT_STA_Msk) >> I2C_RESTART_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge Slave Genaral Call Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't Genaral Call
  * @retval 1 Is Genaral Call
  */
#define __LL_I2C_SLV_IsGenCall_Raw(__I2C__)         \
        (READ_BIT((__I2C__)->RINTRST, I2C_GEN_CALL_RAW_INT_STA_Msk) >> I2C_GEN_CALL_RAW_INT_STA_Pos)

/**
  * @brief  Judge Start Detect Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't start detect
  * @retval 1 Is start detect
  */
#define __LL_I2C_IsStartDet_Raw(__I2C__)            \
        (READ_BIT((__I2C__)->RINTRST, I2C_START_DET_RAW_INT_STA_Msk) >> I2C_START_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge Stop Detect Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't stop detect
  * @retval 1 Is stop detect
  */
#define __LL_I2C_IsStopDet_Raw(__I2C__)             \
        (READ_BIT((__I2C__)->RINTRST, I2C_STOP_DET_RAW_INT_STA_Msk) >> I2C_STOP_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge I2C Activity Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 I2C isn't activity
  * @retval 1 I2C is activity
  */
#define __LL_I2C_IsActivity_Raw(__I2C__)            \
        (READ_BIT((__I2C__)->RINTRST, I2C_ACTIVITY_RAW_INT_STA_Msk) >> I2C_ACTIVITY_RAW_INT_STA_Pos)

/**
  * @brief  Judge Slave RX Done Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave isn't RX Done
  * @retval 1 Slave is RX Done
  */
#define __LL_I2C_SLV_IsRxDone_Raw(__I2C__)          \
        (READ_BIT((__I2C__)->RINTRST, I2C_RX_DONE_RAW_INT_STA_Msk) >> I2C_RX_DONE_RAW_INT_STA_Pos)

/**
  * @brief  Judge TX Abort Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't TX Abort
  * @retval 1 Is TX Abort
  */
#define __LL_I2C_IsTxAbort_Raw(__I2C__)             \
        (READ_BIT((__I2C__)->RINTRST, I2C_TX_ABRT_RAW_INT_STA_Msk) >> I2C_TX_ABRT_RAW_INT_STA_Pos)

/**
  * @brief  Judge Slave Read Request Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave isn't Read Request
  * @retval 1 Slave is Read Request
  */
#define __LL_I2C_SLV_IsReadReq_Raw(__I2C__)         \
        (READ_BIT((__I2C__)->RINTRST, I2C_RD_REQ_RAW_INT_STA_Msk) >> I2C_RD_REQ_RAW_INT_STA_Pos)

/**
  * @brief  Judge TX Empty Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't TX Empty
  * @retval 1 Is TX Empty
  */
#define __LL_I2C_IsTxEmpty_Raw(__I2C__)             \
        (READ_BIT((__I2C__)->RINTRST, I2C_TX_EMPTY_RAW_INT_STA_Msk) >> I2C_TX_EMPTY_RAW_INT_STA_Pos)

/**
  * @brief  Judge TX Over Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't TX Over
  * @retval 1 Is TX Over
  */
#define __LL_I2C_IsTxOver_Raw(__I2C__)              \
        (READ_BIT((__I2C__)->RINTRST, I2C_TX_OVER_RAW_INT_STA_Msk) >> I2C_TX_OVER_RAW_INT_STA_Pos)

/**
  * @brief  Judge RX Full Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't RX Full
  * @retval 1 Is RX Full
  */
#define __LL_I2C_IsRxFull_Raw(__I2C__)              \
        (READ_BIT((__I2C__)->RINTRST, I2C_RX_FULL_RAW_INT_STA_Msk) >> I2C_RX_FULL_RAW_INT_STA_Pos)

/**
  * @brief  Judge RX Over Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't RX Over
  * @retval 1 Is RX Over
  */
#define __LL_I2C_IsRxOver_Raw(__I2C__)              \
        (READ_BIT((__I2C__)->RINTRST, I2C_RX_OVER_RAW_INT_STA_Msk) >> I2C_RX_OVER_RAW_INT_STA_Pos)

/**
  * @brief  Judge RX Under Raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't RX Under
  * @retval 1 Is RX Under
  */
#define __LL_I2C_IsRxUnder_Raw(__I2C__)             \
        (READ_BIT((__I2C__)->RINTRST, I2C_RX_UNDER_RAW_INT_STA_Msk) >> I2C_RX_UNDER_RAW_INT_STA_Pos)


/**
  * @brief  I2C RX Trigger Level Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tl RX Trigger Level
  * @return None
  */
#define __LL_I2C_RxTL_Set(__I2C__, tl)      MODIFY_REG((__I2C__)->RXTL, I2C_RX_TL_Msk, (((tl-1) & 0xffUL) << I2C_RX_TL_Pos))

/**
  * @brief  I2C TX Trigger Level Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tl TX Trigger Level
  * @return None
  */
#define __LL_I2C_TxTL_Set(__I2C__, tl)      MODIFY_REG((__I2C__)->TXTL, I2C_TX_TL_Msk, (((tl-1) & 0xffUL) << I2C_TX_TL_Pos))


/**
  * @brief  I2C Soft Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_SoftIntSta_Clr(__I2C__)            (READ_BIT((__I2C__)->INTRCR, I2C_CLR_INT_Msk) >> I2C_CLR_INT_Pos)


/**
  * @brief  I2C RX Under Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_RxUnderRawIntSta_Clr(__I2C__)      (READ_BIT((__I2C__)->RXUNCR, I2C_CLR_RX_UNDER_Msk) >> I2C_CLR_RX_UNDER_Pos)


/**
  * @brief  I2C RX Over Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_RxOverRawIntSta_Clr(__I2C__)       (READ_BIT((__I2C__)->RXOVCR, I2C_CLR_RX_OVER_Msk) >> I2C_CLR_RX_OVER_Pos)


/**
  * @brief  I2C TX Over Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_TxOverRawIntSta_Clr(__I2C__)       (READ_BIT((__I2C__)->TXOVCR, I2C_CLR_TX_OVER_Msk) >> I2C_CLR_TX_OVER_Pos)


/**
  * @brief  I2C Slave Read Request Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_SLV_ReadReqRawIntSta_Clr(__I2C__)  (READ_BIT((__I2C__)->RDREQCR, I2C_CLR_RD_REQ_Msk) >> I2C_CLR_RD_REQ_Pos)


/**
  * @brief  I2C TX Abort Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_TxAbortRawIntSta_Clr(__I2C__)      (READ_BIT((__I2C__)->TXABCR, I2C_CLR_TX_ABRT_Msk) >> I2C_CLR_TX_ABRT_Pos)


/**
  * @brief  I2C Slave RX Done Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_SLV_RxDoneRawIntSta_Clr(__I2C__)   (READ_BIT((__I2C__)->RXDOCR, I2C_CLR_RX_DONE_Msk) >> I2C_CLR_RX_DONE_Pos)


/**
  * @brief  I2C Activity Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_ActivityRawIntSta_Clr(__I2C__)     (READ_BIT((__I2C__)->ACTICR, I2C_CLR_ACTIVITY_Msk) >> I2C_CLR_ACTIVITY_Pos)


/**
  * @brief  I2C Stop Detect Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_StopDetRawIntSta_Clr(__I2C__)      (READ_BIT((__I2C__)->SPDETCR, I2C_CLR_STOP_DET_Msk) >> I2C_CLR_STOP_DET_Pos)


/**
  * @brief  I2C Start Detect Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_StartDetRawIntSta_Clr(__I2C__)     (READ_BIT((__I2C__)->STDETCR, I2C_CLR_START_DET_Msk) >> I2C_CLR_START_DET_Pos)


/**
  * @brief  I2C Slave Genaral Call Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_SLV_GenCallRawIntSta_Clr(__I2C__)  (READ_BIT((__I2C__)->GCCR, I2C_CLR_GEN_CALL_Msk) >> I2C_CLR_GEN_CALL_Pos)


/**
  * @brief  I2C SMBUS Alert Enable Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_AlertEn_Set(__I2C__)         SET_BIT((__I2C__)->ENABLE, I2C_SMBUS_ALERT_EN_Msk)

/**
  * @brief  I2C SMBUS Alert Enable Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_AlertEn_Clr(__I2C__)         CLEAR_BIT((__I2C__)->ENABLE, I2C_SMBUS_ALERT_EN_Msk)

/**
  * @brief  I2C SMBUS Suspend Enable Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SuspendEn_Set(__I2C__)       SET_BIT((__I2C__)->ENABLE, I2C_SMBUS_SUSPEND_EN_Msk)

/**
  * @brief  I2C SMBUS Suspend Enable Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SuspendEn_Clr(__I2C__)       CLEAR_BIT((__I2C__)->ENABLE, I2C_SMBUS_SUSPEND_EN_Msk)

/**
  * @brief  I2C SMBUS CLK Reset Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ClkReset_Set(__I2C__)        SET_BIT((__I2C__)->ENABLE, I2C_SMBUS_CLK_RESET_Msk)

/**
  * @brief  I2C SMBUS CLK Reset Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ClkReset_Clr(__I2C__)        CLEAR_BIT((__I2C__)->ENABLE, I2C_SMBUS_CLK_RESET_Msk)

/**
  * @brief  I2C SDA Stuck Recovery Enable Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SDAStuckRecoveryEn_Set(__I2C__)    SET_BIT((__I2C__)->ENABLE, I2C_SDA_STK_RECOVERY_EN_Msk)

/**
  * @brief  I2C Master TX Cmd Block Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxCmdBlock_Set(__I2C__)        SET_BIT((__I2C__)->ENABLE, I2C_TX_CMD_BLOCK_Msk)

/**
  * @brief  I2C Master TX Cmd Block Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_TxCmdBlock_Clr(__I2C__)        CLEAR_BIT((__I2C__)->ENABLE, I2C_TX_CMD_BLOCK_Msk)

/**
  * @brief  I2C Master Abort Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_MST_Abort_Set(__I2C__)             SET_BIT((__I2C__)->ENABLE, I2C_ABORT_Msk)

/**
  * @brief  I2C Module Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Enable(__I2C__)                    SET_BIT((__I2C__)->ENABLE, I2C_ENABLE_Msk)

/**
  * @brief  I2C Module Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_Disable(__I2C__)                   CLEAR_BIT((__I2C__)->ENABLE, I2C_ENABLE_Msk)


/**
  * @brief  Judge SMBUS Alert Status or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't alert status
  * @retval 1 Is alert status
  */
#define __LL_I2C_SMBUS_IsAlertSta(__I2C__)      (READ_BIT((__I2C__)->STATUS, I2C_SMBUS_ALERT_STATUS_Msk) >> I2C_SMBUS_ALERT_STATUS_Pos)

/**
  * @brief  Judge SMBUS Suspend Status or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't Suspend status
  * @retval 1 Is Suspend status
  */
#define __LL_I2C_SMBUS_IsSuspendSta(__I2C__)    (READ_BIT((__I2C__)->STATUS, I2C_SMBUS_SUSPEND_STATUS_Msk) >> I2C_SMBUS_SUSPEND_STATUS_Pos)

/**
  * @brief  Judge SMBUS Slave Address Resolved or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS Slave Address Isn't Resolved
  * @retval 1 SMBUS Slave Address Is Resolved
  */
#define __LL_I2C_SMBUS_IsSlvAddrResolved(__I2C__)   \
        (READ_BIT((__I2C__)->STATUS, I2C_SMBUS_SLV_ADDR_RESOLVED_Msk) >> I2C_SMBUS_SLV_ADDR_RESOLVED_Pos)

/**
  * @brief  Judge SMBUS Slave Address Valid or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS Slave Address Isn't Valid
  * @retval 1 SMBUS Slave Address Is Valid
  */
#define __LL_I2C_SMBUS_IsSlvAddrValid(__I2C__)      \
        (READ_BIT((__I2C__)->STATUS, I2C_SMBUS_SLV_ADDR_VALID_Msk) >> I2C_SMBUS_SLV_ADDR_VALID_Pos)

/**
  * @brief  I2C SMBUS Quick Cmd Bit
  * @param  __I2C__ Specifies I2C peripheral
  * @return SMBUS Quick Cmd Bit(R/W)
  */
#define __LL_I2C_SMBUS_QuickCmdBit(__I2C__)     (READ_BIT((__I2C__)->STATUS, I2C_SMBUS_QUICK_CMD_BIT_Msk) >> I2C_SMBUS_QUICK_CMD_BIT_Pos)

/**
  * @brief  Judge SDA Stuck No Recovered or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SDA Stuck has Recovered
  * @retval 1 SDA Stuck hasn't Recovered
  */
#define __LL_I2C_IsSDAStuckNoRecovered(__I2C__)     \
        (READ_BIT((__I2C__)->STATUS, I2C_SDA_STUCK_NOT_RECOVERED_Msk) >> I2C_SDA_STUCK_NOT_RECOVERED_Pos)

/**
  * @brief  Judge Slave Hold RX FIFO Full or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave Isn't Holding RX FIFO Full
  * @retval 1 Slave Is Holding RX FIFO Full
  */
#define __LL_I2C_SLV_IsHoldRxFIFOFull(__I2C__)      \
        (READ_BIT((__I2C__)->STATUS, I2C_SLV_HOLD_RX_FIFO_FULL_Msk) >> I2C_SLV_HOLD_RX_FIFO_FULL_Pos)

/**
  * @brief  Judge Slave Hold Tx FIFO Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave Isn't Holding Tx FIFO Empty
  * @retval 1 Slave Is Holding Tx FIFO Empty
  */
#define __LL_I2C_SLV_IsHoldTxFIFOEmpty(__I2C__)     \
        (READ_BIT((__I2C__)->STATUS, I2C_SLV_HOLD_TX_FIFO_EMPTY_Msk) >> I2C_SLV_HOLD_TX_FIFO_EMPTY_Pos)

/**
  * @brief  Judge Master Hold RX FIFO Full or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master Isn't Holding RX FIFO Full
  * @retval 1 Master Is Holding RX FIFO Full
  */
#define __LL_I2C_MST_IsHoldRxFIFOFull(__I2C__)      \
        (READ_BIT((__I2C__)->STATUS, I2C_MST_HOLD_RX_FIFO_FULL_Msk) >> I2C_MST_HOLD_RX_FIFO_FULL_Pos)

/**
  * @brief  Judge Master Hold Tx FIFO Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master Isn't Holding Tx FIFO Empty
  * @retval 1 Master Is Holding Tx FIFO Empty
  */
#define __LL_I2C_MST_IsHoldTxFIFOEmpty(__I2C__)     \
        (READ_BIT((__I2C__)->STATUS, I2C_MST_HOLD_TX_FIFO_EMPTY_Msk) >> I2C_MST_HOLD_TX_FIFO_EMPTY_Pos)

/**
  * @brief  Judge Slave Activity or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave Isn't Activity
  * @retval 1 Slave Is Activity
  */
#define __LL_I2C_SLV_IsActivity(__I2C__)            (READ_BIT((__I2C__)->STATUS, I2C_SLV_ACTIVITY_Msk) >> I2C_SLV_ACTIVITY_Pos)

/**
  * @brief  Judge Master Activity or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Master Isn't Activity
  * @retval 1 Master Is Activity
  */
#define __LL_I2C_MST_IsActivity(__I2C__)            (READ_BIT((__I2C__)->STATUS, I2C_MST_ACTIVITY_Msk) >> I2C_MST_ACTIVITY_Pos)

/**
  * @brief  Judge RXFIFO Full Entirely or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 RXFIFO isn't full Entirely
  * @retval 1 RXFIFO is full Entirely
  */
#define __LL_I2C_IsRxFIFOFull(__I2C__)              (READ_BIT((__I2C__)->STATUS, I2C_RFF_Msk) >> I2C_RFF_Pos)

/**
  * @brief  Judge RXFIFO Not Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 RXFIO is empty
  * @retval 1 RXFIO isn't empty
  */
#define __LL_I2C_IsRxFIFONotEmpty(__I2C__)          (READ_BIT((__I2C__)->STATUS, I2C_RFNE_Msk) >> I2C_RFNE_Pos)

/**
  * @brief  Judge TXFIFO Empty or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 TXFIFO isn't empty
  * @retval 1 TXFIFO is empty
  */
#define __LL_I2C_IsTxFIFOEmpty(__I2C__)             (READ_BIT((__I2C__)->STATUS, I2C_TFE_Msk) >> I2C_TFE_Pos)

/**
  * @brief  Judge TXFIFO Not Full or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 TXFIFO is Full
  * @retval 1 TXFIFO isn't Full
  */
#define __LL_I2C_IsTxFIFONotFull(__I2C__)           (READ_BIT((__I2C__)->STATUS, I2C_TFNF_Msk) >> I2C_TFNF_Pos)

/**
  * @brief  Judge I2C Activity or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 I2C isn't activity
  * @retval 1 I2C is activity
  */
#define __LL_I2C_IsActivitySta(__I2C__)             (READ_BIT((__I2C__)->STATUS, I2C_ACTIVITY_Msk) >> I2C_ACTIVITY_Pos)


/**
  * @brief  I2C TXFIFO Level Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return TXFIFO Level
  */
#define __LL_I2C_TxFIFOLevel_Get(__I2C__)           (READ_BIT((__I2C__)->TXFLR, I2C_TXFLR_Msk) >> I2C_TXFLR_Pos)


/**
  * @brief  I2C RXFIFO Level Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return RXFIFO Level
  */
#define __LL_I2C_RxFIFOLevel_Get(__I2C__)           (READ_BIT((__I2C__)->RXFLR, I2C_RXFLR_Msk) >> I2C_RXFLR_Pos)


/**
  * @brief  I2C SDA RX Hold Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  hld SDA RX Hold
  * @return None
  */
#define __LL_I2C_SDARxHold_Set(__I2C__, hld)        \
        MODIFY_REG((__I2C__)->SDA_HOLD, I2C_SDA_RX_HOLD_Msk, ((hld & 0xffUL) << I2C_SDA_RX_HOLD_Pos))

/**
  * @brief  I2C SDA TX Hold Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  hld SDA TX Hold
  * @return None
  */
#define __LL_I2C_SDATxHold_Set(__I2C__, hld)        \
        MODIFY_REG((__I2C__)->SDA_HOLD, I2C_SDA_TX_HOLD_Msk, ((hld & 0xffffUL) << I2C_SDA_TX_HOLD_Pos))


/**
  * @brief  I2C TX Flush Count Get
  * @param  __I2C__ Specifies I2C peripheral
  * @return TX Flush Count
  */
#define __LL_I2C_TxFlushCnt_Get(__I2C__)        (READ_BIT((__I2C__)->TXABSR, I2C_TX_FLUSH_CNT_Msk) >> I2C_TX_FLUSH_CNT_Pos)

/**
  * @brief  Judge Master Abort Source Device Write or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Device Write
  * @retval 1 Abort Source Is Device Write
  */
#define __LL_I2C_MST_AbortSrc_IsDevWrite(__I2C__)           \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_DEV_WRITE_Msk) >> I2C_ABRT_DEV_WRITE_Pos)

/**
  * @brief  Judge Master Abort Source Device Slave Address No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Device Slave Address No ACK
  * @retval 1 Abort Source Is Device Slave Address No ACK
  */
#define __LL_I2C_MST_AbortSrc_IsDevSlvAddrNoAck(__I2C__)    \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_DEV_SLV_ADDR_NOACK_Msk) >> I2C_ABRT_DEV_SLV_ADDR_NOACK_Pos)

/**
  * @brief  Judge Master Abort Source Device No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Device No ACK
  * @retval 1 Abort Source Is Device No ACK
  */
#define __LL_I2C_MST_AbortSrc_IsDevNoAck(__I2C__)           \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_DEV_NOACK_Msk) >> I2C_ABRT_DEV_NOACK_Pos)

/**
  * @brief  Judge Master Abort Source SDA Stuck at Low or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't SDA Stuck at Low
  * @retval 1 Abort Source Is SDA Stuck at Low
  */
#define __LL_I2C_MST_AbortSrc_IsSDAStuckAtLow(__I2C__)      \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_SDA_STUCK_AT_LOW_Msk) >> I2C_ABRT_SDA_STUCK_AT_LOW_Pos)

/**
  * @brief  Judge Master Abort Source User Abort or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't User Abort
  * @retval 1 Abort Source Is User Abort
  */
#define __LL_I2C_MST_AbortSrc_IsUserAbort(__I2C__)          \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_USER_ABRT_Msk) >> I2C_ABRT_USER_ABRT_Pos)

/**
  * @brief  Judge Slave Abort Source Slave Read In TX or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Slave Read In TX
  * @retval 1 Abort Source Is Slave Read In TX
  */
#define __LL_I2C_SLV_AbortSrc_IsSlvReadInTx(__I2C__)        \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_SLVRD_INTX_Msk) >> I2C_ABRT_SLVRD_INTX_Pos)

/**
  * @brief  Judge Slave Abort Source Slave Lost Bus or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Slave Lost Bus
  * @retval 1 Abort Source Is Slave Lost Bus
  */
#define __LL_I2C_SLV_AbortSrc_IsSlvLostBus(__I2C__)         \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_SLV_ARBLOST_Msk) >> I2C_ABRT_SLV_ARBLOST_Pos)

/**
  * @brief  Judge Slave Abort Source Slave Flush TXFIFO or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Slave Flush TXFIFO
  * @retval 1 Abort Source Is Slave Flush TXFIFO
  */
#define __LL_I2C_SLV_AbortSrc_IsSlvFlushTxFIFO(__I2C__)     \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_SLVFLUSH_TXFIFO_Msk) >> I2C_ABRT_SLVFLUSH_TXFIFO_Pos)

/**
  * @brief  Judge Abort Source ARB Lost or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't ARB Lost
  * @retval 1 Abort Source Is ARB Lost
  */
#define __LL_I2C_AbortSrc_IsArbLost(__I2C__)                \
        (READ_BIT((__I2C__)->TXABSR, I2C_ARB_LOST_Msk) >> I2C_ARB_LOST_Pos)

/**
  * @brief  Judge Abort Source Master Disable or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Master Disable
  * @retval 1 Abort Source Is Master Disable
  */
#define __LL_I2C_AbortSrc_IsMasterDis(__I2C__)              \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_MASTER_DIS_Msk) >> I2C_ABRT_MASTER_DIS_Pos)

/**
  * @brief  Judge Master Abort Source 10bit Read No Restart or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't 10bit Read No Restart
  * @retval 1 Abort Source Is 10bit Read No Restart
  */
#define __LL_I2C_MST_AbortSrc_Is10bReadNoRestart(__I2C__)   \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_10B_RD_NORSTRT_Msk) >> I2C_ABRT_10B_RD_NORSTRT_Pos)

/**
  * @brief  Judge Master Abort Source Send Start No Restart or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Send Start No Restart
  * @retval 1 Abort Source Is Send Start No Restart
  */
#define __LL_I2C_MST_AbortSrc_IsSendStartNoRestart(__I2C__) \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_SBYTE_NORSTRT_Msk) >> I2C_ABRT_SBYTE_NORSTRT_Pos)

/**
  * @brief  Judge Master Abort Source HS No Restart or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't HS No Restart
  * @retval 1 Abort Source Is HS No Restart
  */
#define __LL_I2C_MST_AbortSrc_IsHsNoRestart(__I2C__)        \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_HS_NORSTRT_Msk) >> I2C_ABRT_HS_NORSTRT_Pos)

/**
  * @brief  Judge Master Abort Source Send Start ACK Detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Send Start ACK Detect
  * @retval 1 Abort Source Is Send Start ACK Detect
  */
#define __LL_I2C_MST_AbortSrc_IsSendStartAckDet(__I2C__)    \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_SBYTE_ACKDET_Msk) >> I2C_ABRT_SBYTE_ACKDET_Pos)

/**
  * @brief  Judge Master Abort Source HS ACK Detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't HS ACK Detect
  * @retval 1 Abort Source Is HS ACK Detect
  */
#define __LL_I2C_MST_AbortSrc_IsHsAckDet(__I2C__)           \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_HS_ACKDET_Msk) >> I2C_ABRT_HS_ACKDET_Pos)

/**
  * @brief  Judge Master Abort Source Genaral Call Read or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Genaral Call Read
  * @retval 1 Abort Source Is Genaral Call Read
  */
#define __LL_I2C_MST_AbortSrc_IsGenCallRead(__I2C__)        \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_GCALL_READ_Msk) >> I2C_ABRT_GCALL_READ_Pos)

/**
  * @brief  Judge Master Abort Source Genaral Call No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't Genaral Call No ACK
  * @retval 1 Abort Source Is Genaral Call No ACK
  */
#define __LL_I2C_MST_AbortSrc_IsGenCallNoAck(__I2C__)       \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_GCALL_NOACK_Msk) >> I2C_ABRT_GCALL_NOACK_Pos)

/**
  * @brief  Judge Master Abort Source TX Data No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't TX Data No ACK
  * @retval 1 Abort Source Is TX Data No ACK
  */
#define __LL_I2C_MST_AbortSrc_IsTxDataNoAck(__I2C__)        \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_TXDATA_NOACK_Msk) >> I2C_ABRT_TXDATA_NOACK_Pos)

/**
  * @brief  Judge Master Abort Source 10b Address 2 No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't 10b Address 2 No ACK
  * @retval 1 Abort Source Is 10b Address 2 No ACK
  */
#define __LL_I2C_MST_AbortSrc_Is10bAddr2NoAck(__I2C__)      \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_10ADDR2_NOACK_Msk) >> I2C_ABRT_10ADDR2_NOACK_Pos)

/**
  * @brief  Judge Master Abort Source 10b Address 1 No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't 10b Address 1 No ACK
  * @retval 1 Abort Source Is 10b Address 1 No ACK
  */
#define __LL_I2C_MST_AbortSrc_Is10bAddr1NoAck(__I2C__)      \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_10ADDR1_NOACK_Msk) >> I2C_ABRT_10ADDR1_NOACK_Pos)

/**
  * @brief  Judge Master Abort Source 7b Address No ACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Abort Source Isn't 7b Address No ACK
  * @retval 1 Abort Source Is 7b Address No ACK
  */
#define __LL_I2C_MST_AbortSrc_Is7bAddrNoAck(__I2C__)        \
        (READ_BIT((__I2C__)->TXABSR, I2C_ABRT_7B_ADDR_NOACK_Msk) >> I2C_ABRT_7B_ADDR_NOACK_Pos)


/**
  * @brief  I2C Slave Force Data No ACK Set
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_ForceDataNoAck_Set(__I2C__)    SET_BIT((__I2C__)->NACKEN, I2C_SLV_DATA_NACK_Msk)

/**
  * @brief  I2C Slave Force Data No ACK Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SLV_ForceDataNoAck_Clr(__I2C__)    CLEAR_BIT((__I2C__)->NACKEN, I2C_SLV_DATA_NACK_Msk)


/**
  * @brief  I2C TX DMA Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxDMA_En(__I2C__)                  SET_BIT((__I2C__)->DMACT, I2C_DMA_TDMAE_Msk)

/**
  * @brief  I2C TX DMA Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_TxDMA_Dis(__I2C__)                 CLEAR_BIT((__I2C__)->DMACT, I2C_DMA_TDMAE_Msk)

/**
  * @brief  I2C RX DMA Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDMA_En(__I2C__)                  SET_BIT((__I2C__)->DMACT, I2C_DMA_RDMAE_Msk)

/**
  * @brief  I2C RX DMA Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_RxDMA_Dis(__I2C__)                 CLEAR_BIT((__I2C__)->DMACT, I2C_DMA_RDMAE_Msk)


/**
  * @brief  I2C TX DMA Trigger Level Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tl TX DMA Trigger Level
  * @return None
  */
#define __LL_I2C_TxDMATriggerLevel_Set(__I2C__, tl)     \
        MODIFY_REG((__I2C__)->DMATDLR, I2C_DMA_DMATDL_Msk, ((tl & 0xfUL) << I2C_DMA_DMATDL_Pos))


/**
  * @brief  I2C RX DMA Trigger Level Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  tl RX DMA Trigger Level
  * @return None
  */
#define __LL_I2C_RxDMATriggerLevel_Set(__I2C__, tl)     \
        MODIFY_REG((__I2C__)->DMARDLR, I2C_DMA_DMARDL_Msk, (((tl-1) & 0xfUL) << I2C_DMA_DMARDL_Pos))


#define __LL_I2C_SDA_Setup_Set(__I2C__, val)            \
        MODIFY_REG((__I2C__)->SDA_SETUP, I2C_SDA_SETUP_Msk, ((val & 0xffUL) << I2C_SDA_SETUP_Pos))


/**
  * @brief  I2C ACK Genaral Call Enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_AckGenCall_En(__I2C__)             SET_BIT((__I2C__)->GCACK, I2C_ACK_GEN_CALL_Msk)

/**
  * @brief  I2C ACK Genaral Call Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_AckGenCall_Dis(__I2C__)            CLEAR_BIT((__I2C__)->GCACK, I2C_ACK_GEN_CALL_Msk)


/**
  * @brief  Judge Slave RX Data Lost or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Slave Isn't RX Data Lost
  * @retval 1 Slave Is RX Data Lost
  */
#define __LL_I2C_SLV_IsRxDataLost(__I2C__)          \
        (READ_BIT((__I2C__)->ENST, I2C_SLV_RX_DATA_LOST_Msk) >> I2C_SLV_RX_DATA_LOST_Pos)

/**
  * @brief  Judge Slave Disable While Busy or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 Isn't Slave Disable While Busy
  * @retval 1 Is Slave Disable While Busy
  */
#define __LL_I2C_SLV_IsSlvDisWhileBusy(__I2C__)     \
        (READ_BIT((__I2C__)->ENST, I2C_SLVDIS_WHILEBUSY_Msk) >> I2C_SLVDIS_WHILEBUSY_Pos)

/**
  * @brief  Judge I2C Enable or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 I2C Isn't Enable
  * @retval 1 I2C Is Enable
  */
#define __LL_I2C_IsEnable(__I2C__)                  (READ_BIT((__I2C__)->ENST, I2C_EN_Msk) >> I2C_EN_Pos)


/**
  * @brief  I2C FS Spike Lengh Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  len FS Spike Lengh
  * @return None
  */
#define __LL_I2C_FsSpkLen_Set(__I2C__, len)         \
        MODIFY_REG((__I2C__)->FS_SPKLEN, I2C_FS_SPKLEN_Msk, ((len & 0xffUL) << I2C_FS_SPKLEN_Pos))


/**
  * @brief  I2C Restart Detect RAW Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_RestartDetRawIntSta_Clr(__I2C__)   \
        (READ_BIT((__I2C__)->RSDETCR, I2C_CLR_RESTART_DET_Msk) >> I2C_CLR_RESTART_DET_Pos)


/**
  * @brief  I2C SCL Stuck at Low Timeout Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  val Timeout Value
  * @return None
  */
#define __LL_I2C_SCLStuckAtLowTimeout_Set(__I2C__, val)     MODIFY_REG((__I2C__)->SCLLTO,\
        I2C_SCL_STK_LOW_TIMEOUT_Msk, ((val & 0xffffffffUL) << I2C_SCL_STK_LOW_TIMEOUT_Pos))


/**
  * @brief  I2C SDA Stuck at Low Timeout Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  val Timeout Value
  * @return None
  */
#define __LL_I2C_SDAStuckAtLowTimeout_Set(__I2C__, val)     MODIFY_REG((__I2C__)->SDALTO,\
        I2C_SDA_STK_LOW_TIMEOUT_Msk, ((val & 0xffffffffUL) << I2C_SDA_STK_LOW_TIMEOUT_Pos))


/**
  * @brief  I2C SCL Stuck Detect RAW Interrupt Status Clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return Read Value, not use
  */
#define __LL_I2C_SCLStuckDetRawIntSta_Clr(__I2C__)          \
        (READ_BIT((__I2C__)->SSTDETCR, I2C_CLR_SCL_STK_Msk) >> I2C_CLR_SCL_STK_Pos)


/**
  * @brief  I2C Device ID Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  id Device ID
  * @return None
  */
#define __LL_I2C_DeviceID_Set(__I2C__, id)      MODIFY_REG((__I2C__)->DEVICE_ID, I2C_DEV_ID_Msk, ((id & 0xffffffUL) << I2C_DEV_ID_Pos))


/**
  * @brief  I2C SMBUS Clock Low Sext Timeout Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  val Timeout Value
  * @return None
  */
#define __LL_I2C_SMBUS_ClkLowSextTimeout_Set(__I2C__, val)      MODIFY_REG((__I2C__)->TSEXT,\
        I2C_SMBUS_CLK_LOW_SEXT_TIMEOUT_Msk, ((val & 0xffffffffUL) << I2C_SMBUS_CLK_LOW_SEXT_TIMEOUT_Pos))


/**
  * @brief  I2C SMBUS Clock Low Mext Timeout Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  val Timeout Value
  * @return None
  */
#define __LL_I2C_SMBUS_ClkLowMextTimeout_Set(__I2C__, val)      MODIFY_REG((__I2C__)->TMEXT,\
        I2C_SMBUS_CLK_LOW_MEXT_TIMEOUT_Msk, ((val & 0xffffffffUL) << I2C_SMBUS_CLK_LOW_MEXT_TIMEOUT_Pos))


/**
  * @brief  I2C SMBUS Thigh Max Bus Idle Count Set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  cnt Count
  * @return None
  */
#define __LL_I2C_SMBUS_ThighMaxBusIdleCnt_Set(__I2C__, cnt)     MODIFY_REG((__I2C__)->IDCNT,\
        I2C_SMBUS_THIGH_MAX_BUS_IDLE_CNT_Msk, ((cnt & 0xffffUL) << I2C_SMBUS_THIGH_MAX_BUS_IDLE_CNT_Pos))


/**
  * @brief  Judge SMBUS is alert detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't alert detect
  * @retval 1 SMBUS is alert detect
  */
#define __LL_I2C_SMBUS_IsAlertDet(__I2C__)              \
        (READ_BIT((__I2C__)->SMINTRST, I2C_SMBUS_ALERT_DET_INT_STA_Msk) << I2C_SMBUS_ALERT_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is suspend detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't suspend detect
  * @retval 1 SMBUS is suspend detect
  */
#define __LL_I2C_SMBUS_IsSuspendDet(__I2C__)            \
        (READ_BIT((__I2C__)->SMINTRST, I2C_SMBUS_SUSPEND_DET_INT_STA_Msk) << I2C_SMBUS_SUSPEND_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is slave RX PEC NACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't slave RX PEC NACK
  * @retval 1 SMBUS is slave RX PEC NACK
  */
#define __LL_I2C_SMBUS_IsSlvRxPecNack(__I2C__)          \
        (READ_BIT((__I2C__)->SMINTRST, I2C_SLV_RX_PEC_NACK_INT_STA_Msk) << I2C_SLV_RX_PEC_NACK_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP assgn address cmd detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP assgn address cmd detect
  * @retval 1 SMBUS is ARP assgn address cmd detect
  */
#define __LL_I2C_SMBUS_IsARPAssgnAddrCmdDet(__I2C__)    \
        (READ_BIT((__I2C__)->SMINTRST, I2C_ARP_ASSGN_ADDR_CMD_DET_INT_STA_Msk) << I2C_ARP_ASSGN_ADDR_CMD_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP get UDID cmd detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP get UDID cmd detect
  * @retval 1 SMBUS is ARP get UDID cmd detect
  */
#define __LL_I2C_SMBUS_IsARPGetUdidCmdDet(__I2C__)      \
        (READ_BIT((__I2C__)->SMINTRST, I2C_ARP_GET_UDID_CMD_DET_INT_STA_Msk) << I2C_ARP_GET_UDID_CMD_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP reset cmd detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP reset cmd detect
  * @retval 1 SMBUS is ARP reset cmd detect
  */
#define __LL_I2C_SMBUS_IsARPRstCmdDet(__I2C__)          \
        (READ_BIT((__I2C__)->SMINTRST, I2C_ARP_RST_CMD_DET_INT_STA_Msk) << I2C_ARP_RST_CMD_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP prepare cmd detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP prepare cmd detect
  * @retval 1 SMBUS is ARP prepare cmd detect
  */
#define __LL_I2C_SMBUS_IsARPPrepareCmdDet(__I2C__)      \
        (READ_BIT((__I2C__)->SMINTRST, I2C_ARP_PREPARE_CMD_DET_INT_STA_Msk) << I2C_ARP_PREPARE_CMD_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is host nofity mst detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't host nofity mst detect
  * @retval 1 SMBUS is host nofity mst detect
  */
#define __LL_I2C_SMBUS_IsHostNotifyMstDet(__I2C__)      \
        (READ_BIT((__I2C__)->SMINTRST, I2C_HOST_NOTIFY_MST_DET_INT_STA_Msk) << I2C_HOST_NOTIFY_MST_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is quick cmd detect or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't quick cmd detect
  * @retval 1 SMBUS is quick cmd detect
  */
#define __LL_I2C_SMBUS_IsQuickCmdDet(__I2C__)           \
        (READ_BIT((__I2C__)->SMINTRST, I2C_QUICK_CMD_DET_INT_STA_Msk) << I2C_QUICK_CMD_DET_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is mst clock extend timeout or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't mst clock extend timeout
  * @retval 1 SMBUS is mst clock extend timeout
  */
#define __LL_I2C_SMBUS_IsMstClkExtendTimeout(__I2C__)   \
        (READ_BIT((__I2C__)->SMINTRST, I2C_MST_CLK_EXTND_TIMEOUT_INT_STA_Msk) << I2C_MST_CLK_EXTND_TIMEOUT_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is slave clock extend timeout or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't slave clock extend timeout
  * @retval 1 SMBUS is slave clock extend timeout
  */
#define __LL_I2C_SMBUS_IsSlvClkExtendTimeout(__I2C__)   \
        (READ_BIT((__I2C__)->SMINTRST, I2C_SLV_CLK_EXTND_TIMEOUT_INT_STA_Msk) << I2C_SLV_CLK_EXTND_TIMEOUT_INT_STA_Pos)


/**
  * @brief  SMBUS alert detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_AlertDet_INT_En(__I2C__)         SET_BIT((__I2C__)->SMINTRMS, I2C_SMBUS_ALERT_DET_INT_EN_Msk)

/**
  * @brief  SMBUS alert detect interrupt Disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_AlertDet_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->SMINTRMS, I2C_SMBUS_ALERT_DET_INT_EN_Msk)

/**
  * @brief  SMBUS Suspend detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SuspendDet_INT_En(__I2C__)       SET_BIT((__I2C__)->SMINTRMS, I2C_SMBUS_SUSPEND_DET_INT_EN_Msk)

/**
  * @brief  SMBUS Suspend detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SuspendDet_INT_Dis(__I2C__)      CLEAR_BIT((__I2C__)->SMINTRMS, I2C_SMBUS_SUSPEND_DET_INT_EN_Msk)

/**
  * @brief  SMBUS slave RX PEC NACK interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvRxPecNack_INT_En(__I2C__)     SET_BIT((__I2C__)->SMINTRMS, I2C_SLV_RX_PEC_NACK_INT_EN_Msk)

/**
  * @brief  SMBUS slave RX PEC NACK interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvRxPecNack_INT_Dis(__I2C__)    CLEAR_BIT((__I2C__)->SMINTRMS, I2C_SLV_RX_PEC_NACK_INT_EN_Msk)

/**
  * @brief  SBMUS ARP assgn addr cmd detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPAssgnAddrCmdDet_INT_En(__I2C__)   SET_BIT((__I2C__)->SMINTRMS, I2C_ARP_ASSGN_ADDR_CMD_DET_INT_EN_Msk)

/**
  * @brief  SBMUS ARP assgn addr cmd detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPAssgnAddrCmdDet_INT_Dis(__I2C__)  CLEAR_BIT((__I2C__)->SMINTRMS, I2C_ARP_ASSGN_ADDR_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS ARP get UDID cmd detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPGetUdidCmdDet_INT_En(__I2C__)     SET_BIT((__I2C__)->SMINTRMS, I2C_ARP_GET_UDID_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS ARP get UDID cmd detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPGetUdidCmdDet_INT_Dis(__I2C__)    CLEAR_BIT((__I2C__)->SMINTRMS, I2C_ARP_GET_UDID_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS ARP reset cmd detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPRstCmdDet_INT_En(__I2C__)         SET_BIT((__I2C__)->SMINTRMS, I2C_ARP_RST_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS ARP reset cmd detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPRstCmdDet_INT_Dis(__I2C__)        CLEAR_BIT((__I2C__)->SMINTRMS, I2C_ARP_RST_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS ARP prepare cmd detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPPrepareCmdDet_INT_En(__I2C__)     SET_BIT((__I2C__)->SMINTRMS, I2C_ARP_PREPARE_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS ARP prepare cmd detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPPrepareCmdDet_INT_Dis(__I2C__)    CLEAR_BIT((__I2C__)->SMINTRMS, I2C_ARP_PREPARE_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS host notify master detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_HostNotifyMstDet_INT_En(__I2C__)     SET_BIT((__I2C__)->SMINTRMS, I2C_HOST_NOTIFY_MST_DET_INT_EN_Msk)

/**
  * @brief  SMBUS host notify master detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_HostNotifyMstDet_INT_Dis(__I2C__)    CLEAR_BIT((__I2C__)->SMINTRMS, I2C_HOST_NOTIFY_MST_DET_INT_EN_Msk)

/**
  * @brief  SMBUS quick cmd detect interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_QuickCmdDet_INT_En(__I2C__)          SET_BIT((__I2C__)->SMINTRMS, I2C_QUICK_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS quick cmd detect interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_QuickCmdDet_INT_Dis(__I2C__)         CLEAR_BIT((__I2C__)->SMINTRMS, I2C_QUICK_CMD_DET_INT_EN_Msk)

/**
  * @brief  SMBUS master clock extend timeout interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_MstClkExtendTimeout_INT_En(__I2C__)  SET_BIT((__I2C__)->SMINTRMS, I2C_MST_CLK_EXTND_TIMEOUT_INT_EN_Msk)

/**
  * @brief  SMBUS master clock extend timeout interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_MstClkExtendTimeout_INT_Dis(__I2C__) CLEAR_BIT((__I2C__)->SMINTRMS, I2C_MST_CLK_EXTND_TIMEOUT_INT_EN_Msk)

/**
  * @brief  SMBUS slave clock extend timeout interrupt enable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvClkExtendTimeout_INT_En(__I2C__)  SET_BIT((__I2C__)->SMINTRMS, I2C_SLV_CLK_EXTND_TIMEOUT_INT_EN_Msk)

/**
  * @brief  SMBUS slave clock extend timeout interrupt disable
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvClkExtendTimeout_INT_Dis(__I2C__) CLEAR_BIT((__I2C__)->SMINTRMS, I2C_SLV_CLK_EXTND_TIMEOUT_INT_EN_Msk)


/**
  * @brief  Judge SMBUS is alert detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't alert detect raw
  * @retval 1 SMBUS is alert detect raw
  */
#define __LL_I2C_SMBUS_IsAlertDetRaw(__I2C__)               \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_SMBUS_ALERT_DET_RAW_INT_STA_Msk) << I2C_SMBUS_ALERT_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is suspend detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't suspend detect raw
  * @retval 1 SMBUS is suspend detect raw
  */
#define __LL_I2C_SMBUS_IsSuspendDetRaw(__I2C__)             \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_SMBUS_SUSPEND_DET_RAW_INT_STA_Msk) << I2C_SMBUS_SUSPEND_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is slave RX PEC NACK or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't slave RX PEC NACK
  * @retval 1 SMBUS is slave RX PEC NACK
  */
#define __LL_I2C_SMBUS_IsSlvRxPecNackRaw(__I2C__)           \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_SLV_RX_PEC_NACK_RAW_INT_STA_Msk) << I2C_SLV_RX_PEC_NACK_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP assgn address cmd detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP assgn address cmd detect raw
  * @retval 1 SMBUS is ARP assgn address cmd detect raw
  */
#define __LL_I2C_SMBUS_IsARPAssgnAddrCmdDetRaw(__I2C__)     \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_ARP_ASSGN_ADDR_CMD_DET_RAW_INT_STA_Msk) << I2C_ARP_ASSGN_ADDR_CMD_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP get UDID cmd detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP get UDID cmd detect raw
  * @retval 1 SMBUS is ARP get UDID cmd detect raw
  */
#define __LL_I2C_SMBUS_IsARPGetUdidCmdDetRaw(__I2C__)       \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_ARP_GET_UDID_CMD_DET_RAW_INT_STA_Msk) << I2C_ARP_GET_UDID_CMD_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP reset cmd detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP reset cmd detect raw
  * @retval 1 SMBUS is ARP reset cmd detect raw
  */
#define __LL_I2C_SMBUS_IsARPRstCmdDetRaw(__I2C__)           \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_ARP_RST_CMD_DET_RAW_INT_STA_Msk) << I2C_ARP_RST_CMD_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is ARP prepare cmd detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't ARP prepare cmd detect raw
  * @retval 1 SMBUS is ARP prepare cmd detect raw
  */
#define __LL_I2C_SMBUS_IsARPPrepareCmdDetRaw(__I2C__)       \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_ARP_PREPARE_CMD_DET_RAW_INT_STA_Msk) << I2C_ARP_PREPARE_CMD_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is host nofity mst detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't host nofity mst detect raw
  * @retval 1 SMBUS is host nofity mst detect raw
  */
#define __LL_I2C_SMBUS_IsHostNotifyMstDetRaw(__I2C__)       \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_HOST_NOTIFY_MST_DET_RAW_INT_STA_Msk) << I2C_HOST_NOTIFY_MST_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is quick cmd detect raw or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't quick cmd detect raw
  * @retval 1 SMBUS is quick cmd detect raw
  */
#define __LL_I2C_SMBUS_IsQuickCmdDetRaw(__I2C__)            \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_QUICK_CMD_DET_RAW_INT_STA_Msk) << I2C_QUICK_CMD_DET_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is mst clock extend timeout or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't mst clock extend timeout
  * @retval 1 SMBUS is mst clock extend timeout
  */
#define __LL_I2C_SMBUS_IsMstClkExtendTimeoutRaw(__I2C__)    \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_MST_CLK_EXTND_TIMEOUT_RAW_INT_STA_Msk) << I2C_MST_CLK_EXTND_TIMEOUT_RAW_INT_STA_Pos)

/**
  * @brief  Judge SMBUS is slave clock extend timeout or not
  * @param  __I2C__ Specifies I2C peripheral
  * @retval 0 SMBUS isn't slave clock extend timeout
  * @retval 1 SMBUS is slave clock extend timeout
  */
#define __LL_I2C_SMBUS_IsSlvClkExtendTimeoutRaw(__I2C__)    \
        (READ_BIT((__I2C__)->SMINTRRST, I2C_SLV_CLK_EXTND_TIMEOUT_RAW_INT_STA_Msk) << I2C_SLV_CLK_EXTND_TIMEOUT_RAW_INT_STA_Pos)


/**
  * @brief  SMBUS alert detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_AlertDetRawIntSta_Clr(__I2C__)           SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_SMBUS_ALERT_DET_Msk)

/**
  * @brief  SMBUS suspend detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SuspendDetRawIntSta_Clr(__I2C__)         SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_SMBUS_SUSPEND_DET_Msk)

/**
  * @brief  SMBUS slave RX PEC NACK raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvRxPecNackRawIntSta_Clr(__I2C__)       SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_SLV_RX_PEC_NACK_Msk)

/**
  * @brief  SMBUS ARP assgn addredd cmd detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPAssgnAddrCmdDetRawIntSta_Clr(__I2C__) SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_ARP_ASSGN_ADDR_CMD_DET_Msk)

/**
  * @brief  SMBUS ARP get UDID cmd detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPUdidCmdDetRawIntSta_Clr(__I2C__)      SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_ARP_GET_UDID_CMD_DET_Msk)

/**
  * @brief  SMBUS ARP reset cmd detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPRstCmdDetRawIntSta_Clr(__I2C__)       SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_ARP_RST_CMD_DET_Msk)

/**
  * @brief  SMBUS ARP prepare cmd detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_ARPPrepareCmdDetRawIntSta_Clr(__I2C__)   SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_ARP_PREPARE_CMD_DET_Msk)

/**
  * @brief  SMBUS host notify master detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_HostNotifyMstDetRawIntSta_Clr(__I2C__)   SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_HOST_NOTIFY_MST_DET_Msk)

/**
  * @brief  SMBUS quick cmd detect raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_QuickCmdDetRawIntSta_Clr(__I2C__)        SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_QUICK_CMD_DET_Msk)

/**
  * @brief  SMBUS master clock extend timeout raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_MstClkExtendTimeoutRawIntSta_Clr(__I2C__)    SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_MST_CLOCK_EXTND_TIMEOUT_Msk)

/**
  * @brief  SMBUS Slave clock extend timeout raw interrupt status clear
  * @param  __I2C__ Specifies I2C peripheral
  * @return None
  */
#define __LL_I2C_SMBUS_SlvClkExtendTimeoutRawIntSta_Clr(__I2C__)    SET_BIT((__I2C__)->SMINTRCR, I2C_CLR_SLV_CLOCK_EXTND_TIMEOUT_Msk)


/**
  * @brief  SMBUS optional SAR set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  sar optional SAR
  * @return None
  */
#define __LL_I2C_SMBUS_OptionalSAR_Set(__I2C__, sar)                \
        MODIFY_REG((__I2C__)->SAROP, I2C_OPTIONAL_SAR_Msk, ((sar & 0x7fUL) << I2C_OPTIONAL_SAR_Pos))


/**
  * @brief  SMBUS ARP UDID LSB set
  * @param  __I2C__ Specifies I2C peripheral
  * @param  lsb SMBUS ARP UDID LSB
  * @return None
  */
#define __LL_I2C_SMBUS_ARPUdidLsb_Set(__I2C__, lsb)                 \
        MODIFY_REG((__I2C__)->UDIDLSB, I2C_SMBUS_ARP_UDID_LSB_Msk, ((lsb & 0xffffffffUL) << I2C_SMBUS_ARP_UDID_LSB_Pos))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Types I2C LL Exported Types
  * @brief    I2C LL Exported Types
  * @{
  */

/**
  * @brief I2C role definition
  */
typedef enum {
    I2C_ROLE_MASTER,    /*!< I2C role master        */
    I2C_ROLE_SLAVE,     /*!< I2C role slave         */
} I2C_RoleETypeDef;

/**
  * @brief I2C address bit definition
  */
typedef enum {
    I2C_ADDR_7BIT,      /*!< I2C address mode 7b    */
    I2C_ADDR_10BIT,     /*!< I2C address mode 10b   */
} I2C_AddrModeETypeDef;

/**
 * @brief I2C memmory address size definition
 */
typedef enum {
    I2C_MEMADDR_SIZE_INVALID    = 0,    /*!< memmory address size invalid   */
    I2C_MEMADDR_SIZE_8BIT       = 1,    /*!< memmory address size 8bit      */
    I2C_MEMADDR_SIZE_16BIT      = 2,    /*!< memmory address size 16bit     */
    I2C_MEMADDR_SIZE_32BIT      = 4,    /*!< memmory address size 32bit     */
} I2C_MemAddrSizeETypeDef;


/**
  * @brief I2C user config
  */
typedef struct __I2C_UserCfgTypeDef {
    I2C_RoleETypeDef     role;          /*!< role                       */
    I2C_AddrModeETypeDef addr_mode;     /*!< address mode               */
    uint32_t baudrate;                  /*!< baudrate                   */
    uint16_t slave_addr;                /*!< slave address              */
    LL_FuncStatusETypeDef smbus_enable; /*!< smbus enable               */
    uint32_t smbus_master_extend_clk;   /*!< smbus master extend clk    */
    uint32_t smbus_slaver_extend_clk;   /*!< smbus slaver extend clk    */
} I2C_UserCfgTypeDef;

/**
  * @brief I2C DMA Status
  */
typedef enum {
    IIC_DMA_STATE_RESET = 0,            /*!< DMA State Reset:   not yet initialized or disabled */
    IIC_DMA_STATE_READY,                /*!< DMA State Ready:   initialized and ready for use   */
    IIC_DMA_STATE_BUSY,                 /*!< DMA State Busy:    process is ongoing              */
    IIC_DMA_STATE_ERROR,                /*!< DMA State Error:   process is Error                */
    IIC_DMA_STATE_FINISH,               /*!< DMA State Finish:  process has been finished       */
} I2C_DMAStatusTypeDef;

/**
  * @brief I2C frame definition
  */
typedef struct __I2C_FrameTypeDef {
    I2C_TypeDef *Instance;                  /*!< I2C Reg base address   */
    uint16_t target_addr;                   /*!< target address         */
    uint32_t mem_addr;                      /*!< memory address         */
    I2C_MemAddrSizeETypeDef mem_addr_size;  /*!< memory address size    */
    uint8_t  *buf;                          /*!< buffer pointer         */
    uint32_t buf_len;                       /*!< buffer length          */
    uint32_t command;                       /*!< smbus_command          */
    uint16_t XferCount;                     /*!< I2C transfer counter   */
    uint32_t clk_cnt;                       /*!< I2C sent clk to read   */
#ifdef LL_DMA_MODULE_ENABLED
    DMA_ChannelETypeDef dma_tx_ch;          /*!< I2C Tx DMA Channel     */
    DMA_ChannelETypeDef dma_rx_ch;          /*!< I2C Rx DMA Channel     */
    I2C_DMAStatusTypeDef TXdma_status;      /*!< I2C DMA status         */
    I2C_DMAStatusTypeDef RXdma_status;      /*!< I2C DMA status         */
#endif
} I2C_FrameTypeDef;


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup I2C_LL_Exported_Functions
  * @{
  */

/** @addtogroup I2C_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_I2C_Init(I2C_TypeDef *Instance, I2C_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_I2C_DeInit(I2C_TypeDef *Instance);
void LL_I2C_MspInit(I2C_TypeDef *Instance);
void LL_I2C_MspDeInit(I2C_TypeDef *Instance);
/**
  * @}
  */

/** @addtogroup I2C_LL_Exported_Functions_Group2
  * @{
  */

uint32_t LL_I2C_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
uint32_t LL_I2C_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout);
uint32_t LL_SMBUS_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
uint32_t LL_SMBUS_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_SMBUS_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_I2C_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);
LL_StatusETypeDef LL_SMBUS_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame);

#ifdef LL_DMA_MODULE_ENABLED
LL_StatusETypeDef LL_I2C_MasterWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_MasterRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                        I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_SlaveRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                       I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_I2C_SlaveWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                        I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_SMBUS_MasterWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_SMBUS_MasterRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_SMBUS_SlaveWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout);
LL_StatusETypeDef LL_SMBUS_SlaveRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout);
#endif

/**
  * @}
  */

/** @addtogroup I2C_LL_Exported_Functions_Group3
  * @{
  */
void LL_I2C_IRQHandler(I2C_TypeDef *Instance, I2C_FrameTypeDef *hi2c);
void LL_I2C_SCLStuckAtLowCallback(I2C_TypeDef *Instance);
void LL_I2C_MstOnHoldCallback(I2C_TypeDef *Instance);
void LL_I2C_SlvRestartDetCallback(I2C_TypeDef *Instance);
void LL_I2C_SlvGenCallCallback(I2C_TypeDef *Instance);
void LL_I2C_StartDetCallback(I2C_TypeDef *Instance);
void LL_I2C_StopDetCallback(I2C_TypeDef *Instance);
void LL_I2C_ActivityCallback(I2C_TypeDef *Instance);
void LL_I2C_SlvRxDoneCallback(I2C_TypeDef *Instance);
void LL_I2C_TxAbortCallback(I2C_TypeDef *Instance);
void LL_I2C_SlvReadReqCallback(I2C_TypeDef *Instance);
void LL_I2C_TxEmptyCallback(I2C_TypeDef *Instance);
void LL_I2C_TxOverCallback(I2C_TypeDef *Instance);
void LL_I2C_RxFullCallback(I2C_TypeDef *Instance);
void LL_I2C_RxOverCallback(I2C_TypeDef *Instance);
void LL_I2C_RxUnderCallback(I2C_TypeDef *Instance);
void LL_SMBUS_SlvClkExtTimeoutCallback(I2C_TypeDef *Instance);
void LL_SMBUS_MstClkExtTimeoutCallback(I2C_TypeDef *Instance);


/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TMF5XXX_LL_I2C_H_ */


/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

