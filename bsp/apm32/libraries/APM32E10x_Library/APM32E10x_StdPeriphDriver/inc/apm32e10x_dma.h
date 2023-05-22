/*!
 * @file       apm32e10x_dma.h
 *
 * @brief      This file contains all the functions prototypes for the DMA firmware library
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
#ifndef __APM32E10X_DMA_H
#define __APM32E10X_DMA_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup DMA_Driver
  @{
*/

/** @defgroup DMA_Enumerations Enumerations
  @{
*/

/**
 * @brief   DMA Transmission direction
 */
typedef enum
{
    DMA_DIR_PERIPHERAL_SRC,
    DMA_DIR_PERIPHERAL_DST
} DMA_DIR_T;

/**
 * @brief   DMA Peripheral address increment
 */
typedef enum
{
    DMA_PERIPHERAL_INC_DISABLE,
    DMA_PERIPHERAL_INC_ENABLE
} DMA_PERIPHERAL_INC_T;

/**
 * @brief   DMA Memory address increment
 */
typedef enum
{
    DMA_MEMORY_INC_DISABLE,
    DMA_MEMORY_INC_ENABLE
} DMA_MEMORY_INC_T;

/**
 * @brief   DMA Peripheral Data Size
 */
typedef enum
{
    DMA_PERIPHERAL_DATA_SIZE_BYTE,
    DMA_PERIPHERAL_DATA_SIZE_HALFWORD,
    DMA_PERIPHERAL_DATA_SIZE_WOED
} DMA_PERIPHERAL_DATA_SIZE_T;

/**
 * @brief   DMA Memory Data Size
 */
typedef enum
{
    DMA_MEMORY_DATA_SIZE_BYTE,
    DMA_MEMORY_DATA_SIZE_HALFWORD,
    DMA_MEMORY_DATA_SIZE_WOED
} DMA_MEMORY_DATA_SIZE_T;

/**
 * @brief   DMA Mode
 */
typedef enum
{
    DMA_MODE_NORMAL,
    DMA_MODE_CIRCULAR
} DMA_LOOP_MODE_T;

/**
 * @brief   DMA priority level
 */
typedef enum
{
    DMA_PRIORITY_LOW,
    DMA_PRIORITY_MEDIUM,
    DMA_PRIORITY_HIGH,
    DMA_PRIORITY_VERYHIGH
} DMA_PRIORITY_T;

/**
 * @brief   DMA Memory to Memory
 */
typedef enum
{
    DMA_M2MEN_DISABLE,
    DMA_M2MEN_ENABLE
} DMA_M2MEN_T;

/**
 * @brief   DMA interrupt
 */
typedef enum
{
    DMA_INT_TC   = 0x00000002,
    DMA_INT_HT   = 0x00000004,
    DMA_INT_TERR = 0x00000008
} DMA_INT_T;

/**
 * @brief   DMA Flag
 */
typedef enum
{
    DMA1_FLAG_GINT1 = 0x00000001,
    DMA1_FLAG_TC1   = 0x00000002,
    DMA1_FLAG_HT1   = 0x00000004,
    DMA1_FLAG_TERR1 = 0x00000008,
    DMA1_FLAG_GINT2 = 0x00000010,
    DMA1_FLAG_TC2   = 0x00000020,
    DMA1_FLAG_HT2   = 0x00000040,
    DMA1_FLAG_TERR2 = 0x00000080,
    DMA1_FLAG_GINT3 = 0x00000100,
    DMA1_FLAG_TC3   = 0x00000200,
    DMA1_FLAG_HT3   = 0x00000400,
    DMA1_FLAG_TERR3 = 0x00000800,
    DMA1_FLAG_GINT4 = 0x00001000,
    DMA1_FLAG_TC4   = 0x00002000,
    DMA1_FLAG_HT4   = 0x00004000,
    DMA1_FLAG_TERR4 = 0x00008000,
    DMA1_FLAG_GINT5 = 0x00010000,
    DMA1_FLAG_TC5   = 0x00020000,
    DMA1_FLAG_HT5   = 0x00040000,
    DMA1_FLAG_TERR5 = 0x00080000,
    DMA1_FLAG_GINT6 = 0x00100000,
    DMA1_FLAG_TC6   = 0x00200000,
    DMA1_FLAG_HT6   = 0x00400000,
    DMA1_FLAG_TERR6 = 0x00800000,
    DMA1_FLAG_GINT7 = 0x01000000,
    DMA1_FLAG_TC7   = 0x02000000,
    DMA1_FLAG_HT7   = 0x04000000,
    DMA1_FLAG_TERR7 = 0x08000000,

    DMA2_FLAG_GINT1 = 0x10000001,
    DMA2_FLAG_TC1   = 0x10000002,
    DMA2_FLAG_HT1   = 0x10000004,
    DMA2_FLAG_TERR1 = 0x10000008,
    DMA2_FLAG_GINT2 = 0x10000010,
    DMA2_FLAG_TC2   = 0x10000020,
    DMA2_FLAG_HT2   = 0x10000040,
    DMA2_FLAG_TERR2 = 0x10000080,
    DMA2_FLAG_GINT3 = 0x10000100,
    DMA2_FLAG_TC3   = 0x10000200,
    DMA2_FLAG_HT3   = 0x10000400,
    DMA2_FLAG_TERR3 = 0x10000800,
    DMA2_FLAG_GINT4 = 0x10001000,
    DMA2_FLAG_TC4   = 0x10002000,
    DMA2_FLAG_HT4   = 0x10004000,
    DMA2_FLAG_TERR4 = 0x10008000,
    DMA2_FLAG_GINT5 = 0x10010000,
    DMA2_FLAG_TC5   = 0x10020000,
    DMA2_FLAG_HT5   = 0x10040000,
    DMA2_FLAG_TERR5 = 0x10080000
} DMA_FLAG_T;

/**
 * @brief DMA Interrupt Flag
 */
typedef enum
{
    DMA1_INT_FLAG_GINT1   = 0x00000001,
    DMA1_INT_FLAG_TC1     = 0x00000002,
    DMA1_INT_FLAG_HT1     = 0x00000004,
    DMA1_INT_FLAG_TERR1   = 0x00000008,
    DMA1_INT_FLAG_GINT2   = 0x00000010,
    DMA1_INT_FLAG_TC2     = 0x00000020,
    DMA1_INT_FLAG_HT2     = 0x00000040,
    DMA1_INT_FLAG_TERR2   = 0x00000080,
    DMA1_INT_FLAG_GINT3   = 0x00000100,
    DMA1_INT_FLAG_TC3     = 0x00000200,
    DMA1_INT_FLAG_HT3     = 0x00000400,
    DMA1_INT_FLAG_TERR3   = 0x00000800,
    DMA1_INT_FLAG_GINT4   = 0x00001000,
    DMA1_INT_FLAG_TC4     = 0x00002000,
    DMA1_INT_FLAG_HT4     = 0x00004000,
    DMA1_INT_FLAG_TERR4   = 0x00008000,
    DMA1_INT_FLAG_GINT5   = 0x00010000,
    DMA1_INT_FLAG_TC5     = 0x00020000,
    DMA1_INT_FLAG_HT5     = 0x00040000,
    DMA1_INT_FLAG_TERR5   = 0x00080000,
    DMA1_INT_FLAG_GINT6   = 0x00100000,
    DMA1_INT_FLAG_TC6     = 0x00200000,
    DMA1_INT_FLAG_HT6     = 0x00400000,
    DMA1_INT_FLAG_TERR6   = 0x00800000,
    DMA1_INT_FLAG_GINT7   = 0x01000000,
    DMA1_INT_FLAG_TC7     = 0x02000000,
    DMA1_INT_FLAG_HT7     = 0x04000000,
    DMA1_INT_FLAG_TERR7   = 0x08000000,

    DMA2_INT_FLAG_GINT1   = 0x10000001,
    DMA2_INT_FLAG_TC1     = 0x10000002,
    DMA2_INT_FLAG_HT1     = 0x10000004,
    DMA2_INT_FLAG_TERR1   = 0x10000008,
    DMA2_INT_FLAG_GINT2   = 0x10000010,
    DMA2_INT_FLAG_TC2     = 0x10000020,
    DMA2_INT_FLAG_HT2     = 0x10000040,
    DMA2_INT_FLAG_TERR2   = 0x10000080,
    DMA2_INT_FLAG_GINT3   = 0x10000100,
    DMA2_INT_FLAG_TC3     = 0x10000200,
    DMA2_INT_FLAG_HT3     = 0x10000400,
    DMA2_INT_FLAG_TERR3   = 0x10000800,
    DMA2_INT_FLAG_GINT4   = 0x10001000,
    DMA2_INT_FLAG_TC4     = 0x10002000,
    DMA2_INT_FLAG_HT4     = 0x10004000,
    DMA2_INT_FLAG_TERR4   = 0x10008000,
    DMA2_INT_FLAG_GINT5   = 0x10010000,
    DMA2_INT_FLAG_TC5     = 0x10020000,
    DMA2_INT_FLAG_HT5     = 0x10040000,
    DMA2_INT_FLAG_TERR5   = 0x10080000
} DMA_INT_FLAG_T;

/**@} end of group DMA_Enumerations */


/** @defgroup DMA_Structures Structures
  @{
*/

/**
 * @brief    DMA Config struct definition
 */
typedef struct
{
    uint32_t                   peripheralBaseAddr;
    uint32_t                   memoryBaseAddr;
    DMA_DIR_T                  dir;
    uint32_t                   bufferSize;
    DMA_PERIPHERAL_INC_T       peripheralInc;
    DMA_MEMORY_INC_T           memoryInc;
    DMA_PERIPHERAL_DATA_SIZE_T peripheralDataSize;
    DMA_MEMORY_DATA_SIZE_T     memoryDataSize;
    DMA_LOOP_MODE_T            loopMode;
    DMA_PRIORITY_T             priority;
    DMA_M2MEN_T                M2M;
} DMA_Config_T;

/**@} end of group DMA_Structures */


/** @defgroup DMA_Functions Functions
  @{
*/

/** Reset and configuration */
void DMA_Reset(DMA_Channel_T *channel);
void DMA_Config(DMA_Channel_T* channel, DMA_Config_T* dmaConfig);
void DMA_ConfigStructInit( DMA_Config_T* dmaConfig);
void DMA_Enable(DMA_Channel_T *channel);
void DMA_Disable(DMA_Channel_T *channel);

/** Data number */
void DMA_ConfigDataNumber(DMA_Channel_T *channel, uint16_t dataNumber);
uint16_t DMA_ReadDataNumber(DMA_Channel_T *channel);

/** Interrupt and flag */
void DMA_EnableInterrupt(DMA_Channel_T *channel, uint32_t interrupt);
void DMA_DisableInterrupt(DMA_Channel_T *channel, uint32_t interrupt);
uint8_t DMA_ReadStatusFlag(DMA_FLAG_T flag);
void DMA_ClearStatusFlag(uint32_t flag);
uint8_t DMA_ReadIntFlag(DMA_INT_FLAG_T flag);
void DMA_ClearIntFlag(uint32_t flag);

/**@} end of group DMA_Functions */
/**@} end of group DMA_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_DMA_H */
