/*!
 * @file        apm32s10x_qspi.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for the QSPI peripheral
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32S10X_QSPI_H
#define __APM32S10X_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32s10x.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup QSPI_Driver QSPI Driver
  @{
*/

/** @defgroup QSPI_Macros Macros
  @{
*/

/* CTRL1 register reset value */
#define QSPI_CTRL1_RESET_VALUE      ((uint32_t)0x4007)
/* CTRL2 register reset value */
#define QSPI_CTRL2_RESET_VALUE      ((uint32_t)0x00)
/* SSIEN register reset value */
#define QSPI_SSIEN_RESET_VALUE      ((uint32_t)0x00)
/* SLAEN register reset value */
#define QSPI_SLAEN_RESET_VALUE      ((uint32_t)0x00)
/* BR register reset value */
#define QSPI_BR_RESET_VALUE         ((uint32_t)0x00)
/* TFTL register reset value */
#define QSPI_TFTL_RESET_VALUE       ((uint32_t)0x00)
/* RFTL register reset value */
#define QSPI_RFTL_RESET_VALUE       ((uint32_t)0x00)
/* TFL register reset value */
#define QSPI_TFL_RESET_VALUE        ((uint32_t)0x00)
/* RFL register reset value */
#define QSPI_RFL_RESET_VALUE        ((uint32_t)0x00)
/* STS register reset value */
#define QSPI_STS_RESET_VALUE        ((uint32_t)0x06)
/* INTEN register reset value */
#define QSPI_INTEN_RESET_VALUE      ((uint32_t)0x7F)
/* RSD register reset value */
#define QSPI_RSD_RESET_VALUE        ((uint32_t)0x00)
/* CTRL3 register reset value */
#define QSPI_CTRL3_RESET_VALUE      ((uint32_t)0x200)
/* IOSW register reset value */
#define QSPI_IOSW_RESET_VALUE       ((uint32_t)0x00)

/**@} end of group QSPI_Macros */

/** @defgroup QSPI_Enumerations Enumerations
  @{
*/

/**
 * @brief   Frame format
 */
typedef enum
{
    QSPI_FRF_STANDARD,              /*!< Standard mode */
    QSPI_FRF_DUAL,                  /*!< Dual SPI */
    QSPI_FRF_QUAD                   /*!< QUAD SPI */
} QSPI_FRF_T;

/**
 * @brief   Transmission mode
 */
typedef enum
{
    QSPI_TRANS_MODE_TX_RX,          /*!< TX and RX mode */
    QSPI_TRANS_MODE_TX,             /*!< TX mode only */
    QSPI_TRANS_MODE_RX,             /*!< RX mode only */
    QSPI_TRANS_MODE_EEPROM_READ     /*!< EEPROM read mode */
} QSPI_TRANS_MODE_T;

/**
 * @brief   Clock polarity
 */
typedef enum
{
    QSPI_CLKPOL_LOW,
    QSPI_CLKPOL_HIGH
} QSPI_CLKPOL_T;

/**
 * @brief   Clock phase
 */
typedef enum
{
    QSPI_CLKPHA_1EDGE,
    QSPI_CLKPHA_2EDGE
} QSPI_CLKPHA_T;

/**
 * @brief   Data format size
 */
typedef enum
{
    QSPI_DFS_4BIT   = 3,
    QSPI_DFS_5BIT,
    QSPI_DFS_6BIT,
    QSPI_DFS_7BIT,
    QSPI_DFS_8BIT,
    QSPI_DFS_9BIT,
    QSPI_DFS_10BIT,
    QSPI_DFS_11BIT,
    QSPI_DFS_12BIT,
    QSPI_DFS_13BIT,
    QSPI_DFS_14BIT,
    QSPI_DFS_15BIT,
    QSPI_DFS_16BIT,
    QSPI_DFS_17BIT,
    QSPI_DFS_18BIT,
    QSPI_DFS_19BIT,
    QSPI_DFS_20BIT,
    QSPI_DFS_21BIT,
    QSPI_DFS_22BIT,
    QSPI_DFS_23BIT,
    QSPI_DFS_24BIT,
    QSPI_DFS_25BIT,
    QSPI_DFS_26BIT,
    QSPI_DFS_27BIT,
    QSPI_DFS_28BIT,
    QSPI_DFS_29BIT,
    QSPI_DFS_30BIT,
    QSPI_DFS_31BIT,
    QSPI_DFS_32BIT
} QSPI_DFS_T;

/**
 * @brief   QSPI flag
 */
typedef enum
{
    QSPI_FLAG_BUSY      = BIT0,     /*!< Busy flag */
    QSPI_FLAG_TFNF      = BIT1,     /*!< TX FIFO not full flag */
    QSPI_FLAG_TFE       = BIT2,     /*!< TX FIFO empty flag */
    QSPI_FLAG_RFNE      = BIT3,     /*!< RX FIFO not empty flag */
    QSPI_FLAG_RFF       = BIT4,     /*!< RX FIFO full flag */
    QSPI_FLAG_DCE       = BIT6      /*!< Data collision error */
} QSPI_FLAG_T;

/**
 * @brief   QSPI interrupt source
 */
typedef enum
{
    QSPI_INT_TFE        = BIT0,     /*!< TX FIFO empty interrupt */
    QSPI_INT_TFO        = BIT1,     /*!< TX FIFO overflow interrupt */
    QSPI_INT_RFU        = BIT2,     /*!< RX FIFO underflow interrupt */
    QSPI_INT_RFO        = BIT3,     /*!< RX FIFO overflow interrupt */
    QSPI_INT_RFF        = BIT4,     /*!< RX FIFO full interrupt */
    QSPI_INT_MST        = BIT5      /*!< Master interrupt */
} QSPI_INT_T;

/**
 * @brief   QSPI interrupt flag
 */
typedef enum
{
    QSPI_INT_FLAG_TFE   = BIT0,     /*!< TX FIFO empty interrupt flag */
    QSPI_INT_FLAG_TFO   = BIT1,     /*!< TX FIFO overflow interrupt flag */
    QSPI_INT_FLAG_RFU   = BIT2,     /*!< RX FIFO underflow interrupt flag */
    QSPI_INT_FLAG_RFO   = BIT3,     /*!< RX FIFO overflow interrupt flag */
    QSPI_INT_FLAG_RFF   = BIT4,     /*!< RX FIFO full interrupt flag */
    QSPI_INT_FLAG_MST   = BIT5      /*!< Master interrupt flag */
} QSPI_INT_FLAG_T;

/**
 * @brief   Reception sample edge
 */
typedef enum
{
    QSPI_RSE_RISING,
    QSPI_RSE_FALLING
} QSPI_RSE_T;

/**
 * @brief   Instruction length
 */
typedef enum
{
    QSPI_INST_LEN_0,
    QSPI_INST_LEN_4BIT,
    QSPI_INST_LEN_8BIT,
    QSPI_INST_LEN_16BIT
} QSPI_INST_LEN_T;

/**
 * @brief   QSPI address length
 */
typedef enum
{
    QSPI_ADDR_LEN_0,
    QSPI_ADDR_LEN_4BIT,
    QSPI_ADDR_LEN_8BIT,
    QSPI_ADDR_LEN_12BIT,
    QSPI_ADDR_LEN_16BIT,
    QSPI_ADDR_LEN_20BIT,
    QSPI_ADDR_LEN_24BIT,
    QSPI_ADDR_LEN_28BIT,
    QSPI_ADDR_LEN_32BIT,
    QSPI_ADDR_LEN_36BIT,
    QSPI_ADDR_LEN_40BIT,
    QSPI_ADDR_LEN_44BIT,
    QSPI_ADDR_LEN_48BIT,
    QSPI_ADDR_LEN_52BIT,
    QSPI_ADDR_LEN_56BIT,
    QSPI_ADDR_LEN_60BIT
} QSPI_ADDR_LEN_T;

/**
 * @brief   Instruction and address transmission mode
 */
typedef enum
{
    QSPI_INST_ADDR_TYPE_STANDARD,
    QSPI_INST_TYPE_STANDARD,
    QSPI_INST_ADDR_TYPE_FRF
} QSPI_INST_ADDR_TYPE_T;

/**
 * @brief   Slave Select Toggle
 */
typedef enum
{
    QSPI_SST_DISABLE,
    QSPI_SST_ENABLE
} QSPI_SST_T;

/**@} end of group QSPI_Enumerations */

/** @defgroup QSPI_Structures Structures
  @{
*/
typedef struct
{
    QSPI_SST_T       selectSlaveToggle; /*!< Slave Select Toggle */
    QSPI_FRF_T       frameFormat;       /*!< Frame format */
    uint16_t         clockDiv;          /*!< Clock divider */
    QSPI_CLKPOL_T    clockPolarity;     /*!< Clock polarity */
    QSPI_CLKPHA_T    clockPhase;        /*!< Clock phase */
    QSPI_DFS_T       dataFrameSize;     /*!< Data frame size */
} QSPI_Config_T;

/**@} end of group QSPI_Structures */

/** @defgroup QSPI_Functions Functions
  @{
*/

/* Reset */
void QSPI_Reset(void);

/* Configuration */
void QSPI_Config(QSPI_Config_T* qspiConfig);
void QSPI_ConfigStructInit(QSPI_Config_T* qspiConfig);

/* Data frame size, frame number, frame format */
void QSPI_ConfigFrameNum(uint16_t num);
void QSPI_ConfigDataFrameSize(QSPI_DFS_T dfs);
void QSPI_ConfigFrameFormat(QSPI_FRF_T frameFormat);

/* Disable or Enable */
void QSPI_Enable(void);
void QSPI_Disable(void);

/* TX and RX FIFO */
uint8_t QSPI_ReadTxFifoDataNum(void);
uint8_t QSPI_ReadRxFifoDataNum(void);
void QSPI_ConfigRxFifoThreshold(uint8_t threshold);
void QSPI_ConfigTxFifoThreshold(uint8_t threshold);
void QSPI_ConfigTxFifoEmptyThreshold(uint8_t threshold);

/* RX Sample */
void QSPI_ConfigRxSampleEdge(QSPI_RSE_T rse);
void QSPI_ConfigRxSampleDelay(uint8_t delay);

/* Clock stretch */
void QSPI_EnableClockStretch(void);
void QSPI_DisableClockStretch(void);

/* Instruction, address, Wait cycle */
void QSPI_ConfigInstLen(QSPI_INST_LEN_T len);
void QSPI_ConfigAddrLen(QSPI_ADDR_LEN_T len);
void QSPI_ConfigInstAddrType(QSPI_INST_ADDR_TYPE_T type);
void QSPI_ConfigWaitCycle(uint8_t cycle);

/* IO */
void QSPI_OpenIO(void);
void QSPI_CloseIO(void);

/* Transmission mode */
void QSPI_ConfigTansMode(QSPI_TRANS_MODE_T mode);

/* Rx and Tx data */
uint32_t QSPI_RxData(void);
void QSPI_TxData(uint32_t data);

/* Slave */
void QSPI_EnableSlave(void);
void QSPI_DisableSlave(void);

/* Interrupt */
void QSPI_EnableInterrupt(uint32_t interrupt);
void QSPI_DisableInterrupt(uint32_t interrupt);

/* Flag */
uint8_t QSPI_ReadStatusFlag(QSPI_FLAG_T flag);
void QSPI_ClearStatusFlag(void);
uint8_t QSPI_ReadIntFlag(QSPI_INT_FLAG_T flag);
void QSPI_ClearIntFlag(uint32_t flag);

/**@} end of group QSPI_Functions */
/**@} end of group QSPI_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif  /* __APM32S10X_QSPI_H_ */
