/*!
 * @file        apm32f10x_sci2c.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for the SCI2C(I2C3, I2C4) peripheral
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F10X_SCI2C_H
#define __APM32F10X_SCI2C_H

/* Includes */
#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup SCI2C_Driver SCI2C Driver
  @{
*/

/** @defgroup SCI2C_Enumerations Enumerations
  @{
*/

/**
 * @brief SCI2C speed enumeration
 */
typedef enum
{
    SCI2C_SPEED_STANDARD = 1,
    SCI2C_SPEED_FAST,
    SCI2C_SPEED_HIGH
} SCI2C_SPEED_T;

/**
 * @brief   Address mode
 */
typedef enum
{
    SCI2C_ADDR_MODE_7BIT,
    SCI2C_ADDR_MODE_10BIT
} SCI2C_ADDR_MODE_T;

/**
 * @brief   SCI2C mode enumeration
 */
typedef enum
{
    SCI2C_MODE_MASTER,
    SCI2C_MODE_SLAVE
} SCI2C_MODE_T;

/**
 * @brief   Restart enable or disable
 */
typedef enum
{
    SCI2C_RESTART_DISABLE,
    SCI2C_RESTART_ENABLE
} SCI2C_RESTART_T;

/**
 * @brief   Enable or disable generate stop condition
 */
typedef enum
{
    SCI2C_STOP_DISABLE,
    SCI2C_STOP_ENABLE
} SCI2C_STOP_T;
/**
 * @brief   Data direction
 */
typedef enum
{
    SCI2C_DATA_DIR_WRITE,
    SCI2C_DATA_DIR_READ,
} SCI2C_DATA_DIR_T;

/**
 * @brief   SCI2C interrupt
 */
typedef enum
{
    SCI2C_INT_RFU       = BIT0,         /*!< Rx FIFO underflow interrupt */
    SCI2C_INT_RFO       = BIT1,         /*!< Rx FIFO onverflow interrupt */
    SCI2C_INT_RFF       = BIT2,         /*!< Rx FIFO full interrupt */
    SCI2C_INT_TFO       = BIT3,         /*!< Tx FIFO onverflow interrupt */
    SCI2C_INT_TFE       = BIT4,         /*!< Tx FIFO empty interrupt */
    SCI2C_INT_RR        = BIT5,         /*!< Read request interrupt */
    SCI2C_INT_TA        = BIT6,         /*!< Tx abort interrupt */
    SCI2C_INT_RD        = BIT7,         /*!< Read done interrupt */
    SCI2C_INT_ACT       = BIT8,         /*!< Activity interrupt */
    SCI2C_INT_STPD      = BIT9,         /*!< Stop detect interrupt */
    SCI2C_INT_STAD      = BIT10,        /*!< Start detect interrupt */
    SCI2C_INT_GC        = BIT11,        /*!< Gernal call interrupt */
    SCI2C_INT_RSTAD     = BIT12,        /*!< Restart detect interrupt */
    SCI2C_INT_MOH       = BIT13,        /*!< Master on hold interrupt */
    SCI2C_INT_ALL       = BIT15         /*!< All interrupt */
} SCI2C_INT_T;

/**
 * @brief   Flag enumeration
 */
typedef enum
{
    SCI2C_FLAG_ACT      = BIT0,         /*!< Activity flag */
    SCI2C_FLAG_TFNF     = BIT1,         /*!< Tx FIFO not full flag */
    SCI2C_FLAG_TFE      = BIT2,         /*!< Tx FIFO empty flag */
    SCI2C_FLAG_RFNE     = BIT3,         /*!< Rx FIFO not empty flag */
    SCI2C_FLAG_RFF      = BIT4,         /*!< Rx FIFO full flag */
    SCI2C_FLAG_MA       = BIT5,         /*!< Master activity flag */
    SCI2C_FLAG_SA       = BIT6,         /*!< Slave activity flag */
    SCI2C_FLAG_I2CEN    = BIT8 | BIT0,  /*!< I2C enable flag */
    SCI2C_FLAG_SDWB     = BIT8 | BIT1,  /*!< Slave disable while busy flag */
    SCI2C_FLAG_SRDL     = BIT8 | BIT2   /*!< Slave receive data lost flag */
} SCI2C_FLAG_T;

/**
 * @brief   Tx abort source
 */
typedef enum
{
    SCI2C_TAS_AD7NA     = BIT0,         /*!< 7 bit address mode NACK */
    SCI2C_TAS_AD10FBNA  = BIT1,         /*!< 10 bit address mode first byte NACK */
    SCI2C_TAS_AD10SBNA  = BIT2,         /*!< 10 bit address mode second byte NACK */
    SCI2C_TAS_TDNA      = BIT3,         /*!< Tx data NACK */
    SCI2C_TAS_GCNA      = BIT4,         /*!< Gernal call NACK */
    SCI2C_TAS_GCR       = BIT5,         /*!< Gernal call read */
    SCI2C_TAS_HSAD      = BIT6,         /*!< High speed ack detected */
    SCI2C_TAS_SNR       = BIT7,         /*!< Start byte no restart */
    SCI2C_TAS_RNR10B    = BIT8,         /*!< Read 10bit address mode when restart disable */
    SCI2C_TAS_MSTDIS    = BIT9,         /*!< Master disable */
    SCI2C_TAS_ARBLOST   = BIT10,        /*!< Arbitration lost */
    SCI2C_TAS_LFTF      = BIT11,        /*!< Slave flush tx FIFO */
    SCI2C_TAS_SAL       = BIT12,        /*!< Slave arbitration lost */
    SCI2C_TAS_SRI       = BIT13,        /*!< Slave read done */
    SCI2C_TAS_USRARB    = BIT14,        /*!< User abort */
    SCI2C_TAS_FLUCNT    = BIT15         /*!< Tx flush counter */
} SCI2C_TAS_T;

/**
 * @brief   DMA Enable
 */
typedef enum
{
    SCI2C_DMA_RX = BIT0,
    SCI2C_DMA_TX = BIT1,
} SCI2C_DMA_T;

/**@} end of group SCI2C_Enumerations */

/** @defgroup SCI2C_Macros Macros
  @{
*/

/* Macros description */
#define SCI2C_CTRL1_RESET_VALUE     ((uint32_t)0x3E)
#define SCI2C_TARADDR_RESET_VALUE   ((uint32_t)0x1055)
#define SCI2C_SLAADDR_RESET_VALUE   ((uint32_t)0x55)
#define SCI2C_HSMC_RESET_VALUE      ((uint32_t)0x07)
#define SCI2C_DATA_RESET_VALUE      ((uint32_t)0x00)
#define SCI2C_SSCHC_RESET_VALUE     ((uint32_t)0x190)
#define SCI2C_SSCLC_RESET_VALUE     ((uint32_t)0x1D6)
#define SCI2C_FSCHC_RESET_VALUE     ((uint32_t)0x3C)
#define SCI2C_FSCLC_RESET_VALUE     ((uint32_t)0x82)
#define SCI2C_HSCHC_RESET_VALUE     ((uint32_t)0x06)
#define SCI2C_HSCLC_RESET_VALUE     ((uint32_t)0x10)
#define SCI2C_INTEN_RESET_VALUE     ((uint32_t)0x00)
#define SCI2C_RFT_RESET_VALUE       ((uint32_t)0x00)
#define SCI2C_TFT_RESET_VALUE       ((uint32_t)0x00)
#define SCI2C_CTRL2_RESET_VALUE     ((uint32_t)0x00)
#define SCI2C_TFL_RESET_VALUE       ((uint32_t)0x00)
#define SCI2C_RFL_RESET_VALUE       ((uint32_t)0x00)
#define SCI2C_SDAHOLD_RESET_VALUE   ((uint32_t)0x01)
#define SCI2C_SDNO_RESET_VALUE      ((uint32_t)0x00)
#define SCI2C_DMACTRL_RESET_VALUE   ((uint32_t)0x00)
#define SCI2C_DTDL_RESET_VALUE      ((uint32_t)0x00)
#define SCI2C_DRDL_RESET_VALUE      ((uint32_t)0x00)
#define SCI2C_SDADLY_RESET_VALUE    ((uint32_t)0x64)
#define SCI2C_GCA_RESET_VALUE       ((uint32_t)0x01)
#define SCI2C_LSSSL_RESET_VALUE     ((uint32_t)0x05)
#define SCI2C_HSSSL_RESET_VALUE     ((uint32_t)0x01)

#define SCI2C_FIFO_DEPTH            (0X08)

/**@} end of group SCI2C_Macros */

/** @defgroup SCI2C_Structures Structures
  @{
*/

/**
 * @brief Structure description
 */
typedef struct
{
    uint16_t            slaveAddr;        /*!< Slave address. */
    SCI2C_MODE_T        mode;             /*!< Specifies mode, master mode or slave mode */
    SCI2C_SPEED_T       speed;            /*!< Specifies speed. Standard speed, fast speed or high speed. */
    uint16_t            clkLowPeriod;     /*!< SCL high period */
    uint16_t            clkHighPeriod;    /*!< SCL low period */
    uint8_t             rxFifoThreshold;  /*!< Rx FIFO threshold */
    uint8_t             txFifoThreshold;  /*!< Tx FIFO threshold */
    SCI2C_RESTART_T     restart;          /*!< Enable or disable restart */
    SCI2C_ADDR_MODE_T   addrMode;         /*!< Address mode. 7-bit or 10-bit mode. */
} SCI2C_Config_T;

/**@} end of group SCI2C_Structure */

/** @defgroup SCI2C_Functions Functions
  @{
*/

/* Reset */
void SCI2C_Reset(SCI2C_T* i2c);

/* Configuration */
void SCI2C_Config(SCI2C_T* i2c, SCI2C_Config_T* sci2cConfig);
void SCI2C_ConfigStructInit(SCI2C_Config_T* sci2cConfig);

/* Stop detect */
void SCI2C_EnableStopDetectAddressed(SCI2C_T* i2c);
void SCI2C_DisableStopDetectAddressed(SCI2C_T* i2c);
void SCI2C_EnableStopDetectMasterActivity(SCI2C_T* i2c);
void SCI2C_DisableStopDetectMasterActivity(SCI2C_T* i2c);

/* Restart */
void SCI2C_EnableRestart(SCI2C_T* i2c);
void SCI2C_DisableRestart(SCI2C_T* i2c);

/* Speed */
void SCI2C_ConfigSpeed(SCI2C_T* i2c, SCI2C_SPEED_T speed);

/* Address */
void SCI2C_ConfigMasterAddr(SCI2C_T* i2c, SCI2C_ADDR_MODE_T mode, uint16_t addr);
void SCI2C_ConfigSlaveAddr(SCI2C_T* i2c, SCI2C_ADDR_MODE_T mode, uint16_t addr);

/* Master mode and slave mode */
void SCI2C_EnableMasterMode(SCI2C_T* i2c);
void SCI2C_DisableMasterMode(SCI2C_T* i2c);
void SCI2C_EnableSlaveMode(SCI2C_T* i2c);
void SCI2C_DisableSlaveMode(SCI2C_T* i2c);
void SCI2C_ConfigMasterCode(SCI2C_T* i2c, uint8_t code);

/* Data */
void SCI2C_ConfigDataDir(SCI2C_T* i2c, SCI2C_DATA_DIR_T dir);
void SCI2C_TxData(SCI2C_T* i2c, uint8_t data);
uint8_t SCI2C_RxData(SCI2C_T* i2c);
void SCI2C_ConfigDataRegister(SCI2C_T* i2c, SCI2C_STOP_T stop, SCI2C_DATA_DIR_T dataDir, uint8_t data);

/* Rx and Tx FIFO */
uint8_t SCI2C_ReadRxFifoDataCnt(SCI2C_T* i2c);
uint8_t SCI2C_ReadTxFifoDataCnt(SCI2C_T* i2c);
void SCI2C_ConfigRxFifoThreshold(SCI2C_T* i2c, uint8_t threshold);
void SCI2C_ConfigTxFifoThreshold(SCI2C_T* i2c, uint8_t threshold);

/* I2C Enable, disable, abort, block */
void SCI2C_Enable(SCI2C_T* i2c);
void SCI2C_Disable(SCI2C_T* i2c);
void SCI2C_Abort(SCI2C_T* i2c);
void SCI2C_BlockTxCmd(SCI2C_T* i2c, uint8_t enable);

/* SCL and SDA */
void SCI2C_ConfigClkPeriod(SCI2C_T* i2c, SCI2C_SPEED_T speed, uint16_t highPeriod, uint16_t lowPeriod);
void SCI2C_ConfigSDAHoldTime(SCI2C_T* i2c, uint16_t txHold, uint8_t rxHold);
void SCI2C_ConfigSDADelayTime(SCI2C_T* i2c, uint8_t delay);

/* ACK and NACK */
void SCI2C_GernalCallAck(SCI2C_T* i2c, uint8_t enable);
void SCI2C_SlaveDataNackOnly(SCI2C_T* i2c, uint8_t enable);

/* Abort */
uint32_t SCI2C_ReadTxAbortSource(SCI2C_T* i2c);

/* DMA */
void SCI2C_EnableDMA(SCI2C_T* i2c, SCI2C_DMA_T dma);
void SCI2C_DisableDMA(SCI2C_T* i2c, SCI2C_DMA_T dma);
void SCI2C_ConfigDMATxDataLevel(SCI2C_T* i2c, uint8_t cnt);
void SCI2C_ConfigDMARxDataLevel(SCI2C_T* i2c, uint8_t cnt);

/* Spike suppression limit */
void SCI2C_ConfigSpikeSuppressionLimit(SCI2C_T* i2c, SCI2C_SPEED_T speed, uint8_t limit);

/* Ingerrupt and flag */
uint8_t SCI2C_ReadStatusFlag(SCI2C_T* i2c, SCI2C_FLAG_T flag);
void SCI2C_ClearIntFlag(SCI2C_T* i2c, SCI2C_INT_T flag);
uint8_t SCI2C_ReadIntFlag(SCI2C_T* i2c, SCI2C_INT_T flag);
uint8_t SCI2C_ReadRawIntFlag(SCI2C_T* i2c, SCI2C_INT_T flag);
void SCI2C_EnableInterrupt(SCI2C_T* i2c, uint16_t interrupt);
void SCI2C_DisableInterrupt(SCI2C_T* i2c, uint16_t interrupt);

/**@} end of group SCI2C_Functions */
/**@} end of group SCI2C_Driver */
/**@} end of group APM32F10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_SCI2C_H */
