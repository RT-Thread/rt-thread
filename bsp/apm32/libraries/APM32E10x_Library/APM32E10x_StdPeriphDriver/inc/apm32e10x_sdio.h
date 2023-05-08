/*!
 * @file        apm32e10x_sdio.h
 *
 * @brief       This file contains all the functions prototypes for the SDIO firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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
#ifndef __APM32E10X_SDIO_H
#define __APM32E10X_SDIO_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup SDIO_Driver
  @{
*/

/** @defgroup SDIO_Macros Macros
  @{
*/

/* ------------ SDIO registers bit address in the alias region ----------- */
#define SDIO_OFFSET                (SDIO_BASE - PERIPH_BASE)

/* --- CLKCTRL Register ---*/

/* Alias word address of CLKEN bit */
#define CLKCTRL_OFFSET            (SDIO_OFFSET + 0x04)
#define CLKEN_BitNumber            0x08
#define CLKCTRL_CLKEN_BB          (PERIPH_BB_BASE + (CLKCTRL_OFFSET * 32) + (CLKEN_BitNumber * 4))

/* --- CMD Register --- */

/* Alias word address of SDIOSC bit */
#define CMD_OFFSET                (SDIO_OFFSET + 0x0C)
#define SDIOSC_BitNumber           0x0B
#define CMD_SDIOSC_BB             (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (SDIOSC_BitNumber * 4))

/* Alias word address of CMDCPEN bit */
#define CMDCPEN_BitNumber          0x0C
#define CMD_CMDCPEN_BB            (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (CMDCPEN_BitNumber * 4))

/* Alias word address of INTEN bit */
#define INTEN_BitNumber            0x0D
#define CMD_INTEN_BB              (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (INTEN_BitNumber * 4))

/* Alias word address of ATACMD bit */
#define ATACMD_BitNumber           0x0E
#define CMD_ATACMD_BB             (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (ATACMD_BitNumber * 4))

/* --- DCTRL Register --- */

/* Alias word address of DMAEN bit */
#define DCTRL_OFFSET              (SDIO_OFFSET + 0x2C)
#define DMAEN_BitNumber            0x03
#define DCTRL_DMAEN_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (DMAEN_BitNumber * 4))

/* Alias word address of RWSTR bit */
#define RWSTR_BitNumber            0x08
#define DCTRL_RWSTR_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTR_BitNumber * 4))

/* Alias word address of RWSTOP bit */
#define RWSTOP_BitNumber           0x09
#define DCTRL_RWSTOP_BB           (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTOP_BitNumber * 4))

/* Alias word address of RDWAIT bit */
#define RDWAIT_BitNumber           0x0A
#define DCTRL_RDWAIT_BB           (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RDWAIT_BitNumber * 4))

/* Alias word address of SDIOF bit */
#define SDIOF_BitNumber            0x0B
#define DCTRL_SDIOF_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (SDIOF_BitNumber * 4))

/**@} end of group SDIO_Macros */

/** @defgroup SDIO_Enumerations Enumerations
  @{
*/

/**
 * @brief    SDIO clock edge
 */
typedef enum
{
    SDIO_CLOCK_EDGE_RISING        = 0x00000000,
    SDIO_CLOCK_EDGE_FALLING       = 0x00002000
}SDIO_CLOCK_EDGE_T;

/**
 * @brief    SDIO clock bypass
 */
typedef enum
{
    SDIO_CLOCK_BYPASS_DISABLE     = 0x00000000,
    SDIO_CLOCK_BYPASS_ENABLE      = 0x00000400
}SDIO_CLOCK_BYPASS_T;

/**
 * @brief    SDIO clock power save
 */
typedef enum
{
    SDIO_CLOCK_POWER_SAVE_DISABLE = 0x00000000,
    SDIO_CLOCK_POWER_SAVE_ENABLE  = 0x00000200
}SDIO_CLOCK_POWER_SAVE_T;

/**
 * @brief    SDIO bus wide
 */
typedef enum
{
    SDIO_BUSWIDE_1B = 0x00000000,
    SDIO_BUSWIDE_4B = 0x00000800,
    SDIO_BUSWIDE_8B = 0x00001000
}SDIO_BUSWIDE_T;

/**
 * @brief    SDIO hardware flow control
 */
typedef enum
{
    SDIO_HARDWARE_FLOW_CONTROL_DISABLE = 0x00000000,
    SDIO_HARDWARE_FLOW_CONTROL_ENABLE  = 0x00004000
}SDIO_HARDWARE_FLOW_CONTROL_T;

/**
 * @brief    SDIO power state
 */
typedef enum
{
    SDIO_POWER_STATE_OFF = 0x00000000,
    SDIO_POWER_STATE_ON  = 0x00000003
}SDIO_POWER_STATE_T;

/**
 * @brief    SDIO interrupt sources
 */
typedef enum
{
    SDIO_INT_COMRESP    = 0x00000001,
    SDIO_INT_DBDR       = 0x00000002,
    SDIO_INT_CMDRESTO   = 0x00000004,
    SDIO_INT_DATATO     = 0x00000008,
    SDIO_INT_TXUDRER    = 0x00000010,
    SDIO_INT_RXOVRER    = 0x00000020,
    SDIO_INT_CMDRES     = 0x00000040,
    SDIO_INT_CMDSENT    = 0x00000080,
    SDIO_INT_DATAEND    = 0x00000100,
    SDIO_INT_SBE        = 0x00000200,
    SDIO_INT_DBCP       = 0x00000400,
    SDIO_INT_CMDACT     = 0x00000800,
    SDIO_INT_TXACT      = 0x00001000,
    SDIO_INT_RXACT      = 0x00002000,
    SDIO_INT_TXFHF      = 0x00004000,
    SDIO_INT_RXFHF      = 0x00008000,
    SDIO_INT_TXFF       = 0x00010000,
    SDIO_INT_RXFF       = 0x00020000,
    SDIO_INT_TXFE       = 0x00040000,
    SDIO_INT_RXFE       = 0x00080000,
    SDIO_INT_TXDA       = 0x00100000,
    SDIO_INT_RXDA       = 0x00200000,
    SDIO_INT_SDIOINT    = 0x00400000,
    SDIO_INT_ATAEND     = 0x00800000
}SDIO_INT_T;

/**
 * @brief    SDIO response
 */
typedef enum
{
    SDIO_RESPONSE_NO    = 0x00000000,
    SDIO_RESPONSE_SHORT = 0x00000040,
    SDIO_RESPONSE_LONG  = 0x000000C0
}SDIO_RESPONSE_T;

/**
 * @brief    SDIO wait interrupt state
 */
typedef enum
{
    SDIO_WAIT_NO        = 0x00000000,
    SDIO_WAIT_INT       = 0x00000100,
    SDIO_WAIT_PEND      = 0x00000200
}SDIO_WAIT_T;

/**
 * @brief    SDIO CPSM state
 */
typedef enum
{
    SDIO_CPSM_DISABLE   = 0x00000000,
    SDIO_CPSM_ENABLE    = 0x00000400
}SDIO_CPSM_T;

/**
 * @brief    SDIO response registers
 */
typedef enum
{
    SDIO_RES1 = 0x00000000,
    SDIO_RES2 = 0x00000004,
    SDIO_RES3 = 0x00000008,
    SDIO_RES4 = 0x0000000C
}SDIO_RES_T;

/**
 * @brief    SDIO data block size
 */
typedef enum
{
    SDIO_DATA_BLOCKSIZE_1B     = 0x00000000,
    SDIO_DATA_BLOCKSIZE_2B     = 0x00000010,
    SDIO_DATA_BLOCKSIZE_4B     = 0x00000020,
    SDIO_DATA_BLOCKSIZE_8B     = 0x00000030,
    SDIO_DATA_BLOCKSIZE_16B    = 0x00000040,
    SDIO_DATA_BLOCKSIZE_32B    = 0x00000050,
    SDIO_DATA_BLOCKSIZE_64B    = 0x00000060,
    SDIO_DATA_BLOCKSIZE_128B   = 0x00000070,
    SDIO_DATA_BLOCKSIZE_256B   = 0x00000080,
    SDIO_DATA_BLOCKSIZE_512B   = 0x00000090,
    SDIO_DATA_BLOCKSIZE_1024B  = 0x000000A0,
    SDIO_DATA_BLOCKSIZE_2048B  = 0x000000B0,
    SDIO_DATA_BLOCKSIZE_496B   = 0x000000C0,
    SDIO_DATA_BLOCKSIZE_8192B  = 0x000000D0,
    SDIO_DATA_BLOCKSIZE_16384B = 0x000000E0
}SDIO_DATA_BLOCKSIZE_T;

/**
 * @brief    SDIO transfer direction
 */
typedef enum
{
    SDIO_TRANSFER_DIR_TOCARD   = 0x00000000,
    SDIO_TRANSFER_DIR_TOSDIO   = 0x00000002
}SDIO_TRANSFER_DIR_T;

/**
 * @brief    SDIO transfer type
 */
typedef enum
{
    SDIO_TRANSFER_MODE_BLOCK   = 0x00000000,
    SDIO_TRANSFER_MODE_STREAM  = 0x00000004
}SDIO_TRANSFER_MODE_T;

/**
 * @brief    SDIO DPSM state
 */
typedef enum
{
    SDIO_DPSM_DISABLE          = 0x00000000,
    SDIO_DPSM_ENABLE           = 0x00000001
}SDIO_DPSM_T;

/**
 * @brief    SDIO flag
 */
typedef enum
{
    SDIO_FLAG_COMRESP   = 0x00000001,
    SDIO_FLAG_DBDR      = 0x00000002,
    SDIO_FLAG_CMDRESTO  = 0x00000004,
    SDIO_FLAG_DATATO    = 0x00000008,
    SDIO_FLAG_TXUDRER   = 0x00000010,
    SDIO_FLAG_RXOVRER   = 0x00000020,
    SDIO_FLAG_CMDRES    = 0x00000040,
    SDIO_FLAG_CMDSENT   = 0x00000080,
    SDIO_FLAG_DATAEND   = 0x00000100,
    SDIO_FLAG_SBE       = 0x00000200,
    SDIO_FLAG_DBCP      = 0x00000400,
    SDIO_FLAG_CMDACT    = 0x00000800,
    SDIO_FLAG_TXACT     = 0x00001000,
    SDIO_FLAG_RXACT     = 0x00002000,
    SDIO_FLAG_TXFHF     = 0x00004000,
    SDIO_FLAG_RXFHF     = 0x00008000,
    SDIO_FLAG_TXFF      = 0x00010000,
    SDIO_FLAG_RXFF      = 0x00020000,
    SDIO_FLAG_TXFE      = 0x00040000,
    SDIO_FLAG_RXFE      = 0x00080000,
    SDIO_FLAG_TXDA      = 0x00100000,
    SDIO_FLAG_RXDA      = 0x00200000,
    SDIO_FLAG_SDIOINT   = 0x00400000,
    SDIO_FLAG_ATAEND    = 0x00800000
}SDIO_FLAG_T;

/**
 * @brief    SDIO read wait mode
 */
typedef enum
{
    SDIO_READ_WAIT_MODE_CLK   = 0x00000001,
    SDIO_READ_WAIT_MODE_DATA2 = 0x00000000
}SDIO_READ_WAIT_MODE_T;

/**@} end of group SDIO_Enumerations */


/** @defgroup SDIO_Structures Structures
  @{
*/

/**
 * @brief    SDIO Config structure definition
 */
typedef struct
{
    SDIO_CLOCK_EDGE_T            clockEdge;
    SDIO_CLOCK_BYPASS_T          clockBypass;
    SDIO_CLOCK_POWER_SAVE_T      clockPowerSave;
    SDIO_BUSWIDE_T               busWide;
    SDIO_HARDWARE_FLOW_CONTROL_T hardwareFlowControl;
    uint8_t                      clockDiv;
}SDIO_Config_T;

/**
 * @brief    SDIO CMD Config structure definition
 */
typedef struct
{
    uint32_t                     argument;
    uint32_t                     cmdIndex;
    SDIO_RESPONSE_T              response;
    SDIO_WAIT_T                  wait;
    SDIO_CPSM_T                  CPSM;
}SDIO_CMDConfig_T;

/**
 * @brief    SDIO Data Config structure definition
 */
typedef struct
{
    uint32_t                     dataTimeOut;
    uint32_t                     dataLength;
    SDIO_DATA_BLOCKSIZE_T        dataBlockSize;
    SDIO_TRANSFER_DIR_T          transferDir;
    SDIO_TRANSFER_MODE_T         transferMode;
    SDIO_DPSM_T                  DPSM;
}SDIO_DataConfig_T;

/**@} end of group SDIO_Structures */


/** @defgroup SDIO_Functions Functions
  @{
*/

/* SDIO reset and configuration */
void SDIO_Reset(void);
void SDIO_Config(SDIO_Config_T* sdioConfig);
void SDIO_ConfigStructInit(SDIO_Config_T* sdioConfig);
void SDIO_EnableClock(void);
void SDIO_DisableClock(void);
void SDIO_ConfigPowerState(SDIO_POWER_STATE_T powerState);
uint32_t SDIO_ReadPowerState(void);

/* DMA */
void SDIO_EnableDMA(void);
void SDIO_DisableDMA(void);

/* Command */
void SDIO_TxCommand(SDIO_CMDConfig_T *cmdConfig);
void SDIO_TxCommandStructInit(SDIO_CMDConfig_T* cmdconfig);
uint8_t SDIO_ReadCommandResponse(void);
uint32_t SDIO_ReadResponse(SDIO_RES_T res);

/* SDIO data configuration */
void SDIO_ConfigData(SDIO_DataConfig_T* dataConfig);
void SDIO_ConfigDataStructInit(SDIO_DataConfig_T* dataConfig);
uint32_t SDIO_ReadDataCounter(void);
void SDIO_WriteData(uint32_t data);
uint32_t SDIO_ReadData(void);
uint32_t SDIO_ReadFIFOCount(void);

/* SDIO mode */
void SDIO_EnableStartReadWait(void);
void SDIO_DisableStartReadWait(void);
void SDIO_EnableStopReadWait(void);
void SDIO_DisableStopReadWait(void);
void SDIO_ConfigSDIOReadWaitMode(SDIO_READ_WAIT_MODE_T readWaitMode);
void SDIO_EnableSDIO(void);
void SDIO_DisableSDIO(void);
void SDIO_EnableTxSDIOSuspend(void);
void SDIO_DisableTxSDIOSuspend(void);
void SDIO_EnableCommandCompletion(void);
void SDIO_DisableCommandCompletion(void);
void SDIO_EnableCEATAInterrupt(void);
void SDIO_DisableCEATAInterrupt(void);
void SDIO_EnableTxCEATA(void);
void SDIO_DisableTxCEATA(void);

/* Interrupt and flags */
void SDIO_EnableInterrupt(uint32_t interrupt);
void SDIO_DisableInterrupt(uint32_t interrupt);
uint8_t SDIO_ReadStatusFlag(SDIO_FLAG_T flag);
void SDIO_ClearStatusFlag(uint32_t flag);
uint8_t SDIO_ReadIntFlag(SDIO_INT_T flag);
void SDIO_ClearIntFlag(uint32_t flag);

/**@} end of group SDIO_Functions*/
/**@} end of group SDIO_Driver*/
/**@} end of group APM32E10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_SDIO_H */
