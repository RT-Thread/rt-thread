/*!
 * @file        apm32f4xx_dma.h
 *
 * @brief       This file contains all the functions prototypes for the DMA firmware library.
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
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
#ifndef __APM32F4XX_DMA_H
#define __APM32F4XX_DMA_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup DMA_Driver
  @{
*/

/** @defgroup DMA_Enumerations
  @{
*/

/**
 * @brief DMA channel
 */
typedef enum
{
    DMA_CHANNEL_0,  /*!< Select DMA channel 0 */
    DMA_CHANNEL_1,  /*!< Select DMA channel 1 */
    DMA_CHANNEL_2,  /*!< Select DMA channel 2 */
    DMA_CHANNEL_3,  /*!< Select DMA channel 3 */
    DMA_CHANNEL_4,  /*!< Select DMA channel 4 */
    DMA_CHANNEL_5,  /*!< Select DMA channel 5 */
    DMA_CHANNEL_6,  /*!< Select DMA channel 6 */
    DMA_CHANNEL_7   /*!< Select DMA channel 7 */
} DMA_CHANNEL_T;

/**
 * @brief DMA Transmission direction
 */
typedef enum
{
    DMA_DIR_PERIPHERALTOMEMORY, /*!< Peripheral to memory */
    DMA_DIR_MEMORYTOPERIPHERAL, /*!< Memory to peripheral */
    DMA_DIR_MEMORYTOMEMORY      /*!< Memory to memory */
} DMA_DIR_T;

/**
 * @brief DMA Peripheral address increment
 */
typedef enum
{
    DMA_PERIPHERAL_INC_DISABLE, /*!< Disable peripheral increment mode */
    DMA_PERIPHERAL_INC_ENABLE   /*!< Enable peripheral increment mode */
} DMA_PERIPHERAL_INC_T;

/**
 * @brief DMA Memory address increment
 */
typedef enum
{
    DMA_MEMORY_INC_DISABLE, /*!< Disable memory increment mode */
    DMA_MEMORY_INC_ENABLE   /*!< Enable memory increment mode */
} DMA_MEMORY_INC_T;

/**
 * @brief DMA Peripheral Data Size
 */
typedef enum
{
    DMA_PERIPHERAL_DATA_SIZE_BYTE,      /*!< Set peripheral data size to byte */
    DMA_PERIPHERAL_DATA_SIZE_HALFWORD,  /*!< Set peripheral data size to half-word */
    DMA_PERIPHERAL_DATA_SIZE_WORD       /*!< Set peripheral data size to word */
} DMA_PERIPHERAL_DATA_SIZE_T;

/**
 * @brief DMA Memory Data Size
 */
typedef enum
{
    DMA_MEMORY_DATA_SIZE_BYTE,          /*!< Set memory data size to byte */
    DMA_MEMORY_DATA_SIZE_HALFWORD,      /*!< Set memory data size to half-word */
    DMA_MEMORY_DATA_SIZE_WORD           /*!< Set memory data size to word */
} DMA_MEMORY_DATA_SIZE_T;

/**
 * @brief DMA Mode
 */
typedef enum
{
    DMA_MODE_NORMAL,    /*!< Disable circular mode */
    DMA_MODE_CIRCULAR   /*!< Enable circular mode */
} DMA_LOOP_MODE_T;

/**
 * @brief DMA priority level
 */
typedef enum
{
    DMA_PRIORITY_LOW,       /*!< Set priority level to low */
    DMA_PRIORITY_MEDIUM,    /*!< Set priority level to medium */
    DMA_PRIORITY_HIGH,      /*!< Set priority level to high */
    DMA_PRIORITY_VERYHIGH   /*!< Set priority level to very high */
} DMA_PRIORITY_T;

/**
 * @brief DMA fifo direct mode
 */
typedef enum
{
    DMA_FIFOMODE_DISABLE,   /*!< Enable fifo mode */
    DMA_FIFOMODE_ENABLE     /*!< Disable fifo mode */
} DMA_FIFOMODE_T;

/**
 * @brief DMA fifo threshold select
 */
typedef enum
{
    DMA_FIFOTHRESHOLD_QUARTER,      /*!< Select quarter FIFO threshold */
    DMA_FIFOTHRESHOLD_HALFFULL,     /*!< Select half-full FIFO threshold */
    DMA_FIFOTHRESHOLD_3QUARTERS,    /*!< Select three quarters FIFO threshold */
    DMA_FIFOTHRESHOLD_FULL          /*!< Select full FIFO threshold */
} DMA_FIFOTHRESHOLD_T;

/**
 * @brief DMA memory burst
 */
typedef enum
{
    DMA_MEMORYBURST_SINGLE, /*!< Single memory burst transfer */
    DMA_MEMORYBURST_INC4,   /*!< INC4 memory burst transfer */
    DMA_MEMORYBURST_INC8,   /*!< INC8 memory burst transfer */
    DMA_MEMORYBURST_INC16   /*!< INC16 memory burst transfer */
} DMA_MEMORYBURST_T;

/**
 * @brief DMA peripheral burst
 */
typedef enum
{
    DMA_PERIPHERALBURST_SINGLE, /*!< Single peripheral burst transfer */
    DMA_PERIPHERALBURST_INC4,   /*!< INC4 peripheral burst transfer */
    DMA_PERIPHERALBURST_INC8,   /*!< INC8 peripheral burst transfer */
    DMA_PERIPHERALBURST_INC16   /*!< INC16 peripheral burst transfer */
} DMA_PERIPHERALBURST_T;

/**
 * @brief DMA fifo status level
 */
typedef enum
{
    DMA_FIFOSTATUS_LESS1QUARTER,    /*!< When FIFO is less than 1 quarter-full and not empty */
    DMA_FIFOSTATUS_1QUARTER,        /*!< If more than 1 quarter-full */
    DMA_FIFOSTATUS_HalfFull,        /*!< If more than 1 half-full */
    DMA_FIFOSTATUS_3QUARTERS,       /*!< If more than 3 quarters-full */
    DMA_FIFOSTATUS_EMPTY,           /*!< When FIFO is empty */
    DMA_FIFOSTATUS_FULL             /*!< When FIFO is full */
} DMA_FIFOSTATUS_T;

/**
 * @brief DMA Flag
 */
typedef enum
{
    DMA_FLAG_FEIFLG0   =  0x10000001,   /*!< Channel0 FIFO error flag */
    DMA_FLAG_DMEIFLG0  =  0x10000004,   /*!< Channel0 direct mode error flag */
    DMA_FLAG_TEIFLG0   =  0x10000008,   /*!< Channel0 transfer error flag */
    DMA_FLAG_HTIFLG0   =  0x10000010,   /*!< Channel0 half transfer complete flag */
    DMA_FLAG_TCIFLG0   =  0x10000020,   /*!< Channel0 transfer complete flag */

    DMA_FLAG_FEIFLG1   =  0x10000040,   /*!< Channel1 FIFO error flag */
    DMA_FLAG_DMEIFLG1  =  0x10000100,   /*!< Channel1 direct mode error flag */
    DMA_FLAG_TEIFLG1   =  0x10000200,   /*!< Channel1 transfer error flag */
    DMA_FLAG_HTIFLG1   =  0x10000400,   /*!< Channel1 half transfer complete flag */
    DMA_FLAG_TCIFLG1   =  0x10000800,   /*!< Channel1 transfer complete flag */

    DMA_FLAG_FEIFLG2   =  0x10010000,   /*!< Channel2 FIFO error flag */
    DMA_FLAG_DMEIFLG2  =  0x10040000,   /*!< Channel2 direct mode error flag */
    DMA_FLAG_TEIFLG2   =  0x10080000,   /*!< Channel2 transfer error flag */
    DMA_FLAG_HTIFLG2   =  0x10100000,   /*!< Channel2 half transfer complete flag */
    DMA_FLAG_TCIFLG2   =  0x10200000,   /*!< Channel2 transfer complete flag */

    DMA_FLAG_FEIFLG3   =  0x10400000,   /*!< Channel3 FIFO error flag */
    DMA_FLAG_DMEIFLG3  =  0x11000000,   /*!< Channel3 direct mode error flag */
    DMA_FLAG_TEIFLG3   =  0x12000000,   /*!< Channel3 transfer error flag */
    DMA_FLAG_HTIFLG3   =  0x14000000,   /*!< Channel3 half transfer complete flag */
    DMA_FLAG_TCIFLG3   =  0x18000000,   /*!< Channel3 transfer complete flag */

    DMA_FLAG_FEIFLG4   =  0x20000001,   /*!< Channel4 FIFO error flag */
    DMA_FLAG_DMEIFLG4  =  0x20000004,   /*!< Channel4 direct mode error flag */
    DMA_FLAG_TEIFLG4   =  0x20000008,   /*!< Channel4 transfer error flag */
    DMA_FLAG_HTIFLG4   =  0x20000010,   /*!< Channel4 half transfer complete flag */
    DMA_FLAG_TCIFLG4   =  0x20000020,   /*!< Channel4 transfer complete flag */

    DMA_FLAG_FEIFLG5   =  0x20000040,   /*!< Channel5 FIFO error flag */
    DMA_FLAG_DMEIFLG5  =  0x20000100,   /*!< Channel5 direct mode error flag */
    DMA_FLAG_TEIFLG5   =  0x20000200,   /*!< Channel5 transfer error flag */
    DMA_FLAG_HTIFLG5   =  0x20000400,   /*!< Channel5 half transfer complete flag */
    DMA_FLAG_TCIFLG5   =  0x20000800,   /*!< Channel5 transfer complete flag */

    DMA_FLAG_FEIFLG6   =  0x20010000,   /*!< Channel6 FIFO error flag */
    DMA_FLAG_DMEIFLG6  =  0x20040000,   /*!< Channel6 direct mode error flag */
    DMA_FLAG_TEIFLG6   =  0x20080000,   /*!< Channel6 transfer error flag */
    DMA_FLAG_HTIFLG6   =  0x20100000,   /*!< Channel6 half transfer complete flag */
    DMA_FLAG_TCIFLG6   =  0x20200000,   /*!< Channel6 transfer complete flag */

    DMA_FLAG_FEIFLG7   =  0x20400000,   /*!< Channel7 FIFO error flag */
    DMA_FLAG_DMEIFLG7  =  0x21000000,   /*!< Channel7 direct mode error flag */
    DMA_FLAG_TEIFLG7   =  0x22000000,   /*!< Channel7 transfer error flag */
    DMA_FLAG_HTIFLG7   =  0x24000000,   /*!< Channel7 half transfer complete flag */
    DMA_FLAG_TCIFLG7   =  0x28000000    /*!< Channel7 transfer complete flag */
} DMA_FLAG_T;

/**
 * @brief DMA Interrupt Flag
 */
typedef enum
{
    DMA_INT_FEIFLG  = 0x01, /*!< FIFO error interrupt mask */
    DMA_INT_DMEIFLG = 0x02, /*!< Direct mode error interrupt mask */
    DMA_INT_TEIFLG  = 0x04, /*!< Transfer error interrupt mask */
    DMA_INT_HTIFLG  = 0x08, /*!< Half transfer complete interrupt mask */
    DMA_INT_TCIFLG  = 0x10  /*!< Transfer complete interrupt mask */
} DMA_INT_T;

/**
 * @brief DMA Interrupts Flag
 */
typedef enum
{
    DMA_INT_FEIFLG0   =  0x20000001,    /*!< Stream0 FIFO error flag */
    DMA_INT_DMEIFLG0  =  0x00001004,    /*!< Stream0 direct mode error flag */
    DMA_INT_TEIFLG0   =  0x00002008,    /*!< Stream0 transfer error flag */
    DMA_INT_HTIFLG0   =  0x00004010,    /*!< Stream0 half transfer complete flag */
    DMA_INT_TCIFLG0   =  0x00008020,    /*!< Stream0 transfer complete flag */

    DMA_INT_FEIFLG1   =  0x20000040,    /*!< Stream1 FIFO error flag */
    DMA_INT_DMEIFLG1  =  0x00001100,    /*!< Stream1 direct mode error flag */
    DMA_INT_TEIFLG1   =  0x00002200,    /*!< Stream1 transfer error flag */
    DMA_INT_HTIFLG1   =  0x00004400,    /*!< Stream1 half transfer complete flag */
    DMA_INT_TCIFLG1   =  0x00008800,    /*!< Stream1 transfer complete flag */

    DMA_INT_FEIFLG2   =  0x20010000,    /*!< Stream2 FIFO error flag */
    DMA_INT_DMEIFLG2  =  0x00041000,    /*!< Stream2 direct mode error flag */
    DMA_INT_TEIFLG2   =  0x00082000,    /*!< Stream2 transfer error flag */
    DMA_INT_HTIFLG2   =  0x00104000,    /*!< Stream2 half transfer complete flag */
    DMA_INT_TCIFLG2   =  0x00208000,    /*!< Stream2 transfer complete flag */

    DMA_INT_FEIFLG3   =  0x20400000,    /*!< Stream3 FIFO error flag */
    DMA_INT_DMEIFLG3  =  0x01001000,    /*!< Stream3 direct mode error flag */
    DMA_INT_TEIFLG3   =  0x02002000,    /*!< Stream3 transfer error flag */
    DMA_INT_HTIFLG3   =  0x04004000,    /*!< Stream3 half transfer complete flag */
    DMA_INT_TCIFLG3   =  0x08008000,    /*!< Stream3 transfer complete flag */

    DMA_INT_FEIFLG4   =  0x50000001,    /*!< Stream4 FIFO error flag */
    DMA_INT_DMEIFLG4  =  0x10001004,    /*!< Stream4 direct mode error flag */
    DMA_INT_TEIFLG4   =  0x10002008,    /*!< Stream4 transfer error flag */
    DMA_INT_HTIFLG4   =  0x10004010,    /*!< Stream4 half transfer complete flag */
    DMA_INT_TCIFLG4   =  0x10008020,    /*!< Stream4 transfer complete flag */

    DMA_INT_FEIFLG5   =  0x50000040,    /*!< Stream5 FIFO error flag */
    DMA_INT_DMEIFLG5  =  0x10001100,    /*!< Stream5 direct mode error flag */
    DMA_INT_TEIFLG5   =  0x10002200,    /*!< Stream5 transfer error flag */
    DMA_INT_HTIFLG5   =  0x10004400,    /*!< Stream5 half transfer complete flag */
    DMA_INT_TCIFLG5   =  0x10008800,    /*!< Stream5 transfer complete flag */

    DMA_INT_FEIFLG6   =  0x50010000,    /*!< Stream6 FIFO error flag */
    DMA_INT_DMEIFLG6  =  0x10041000,    /*!< Stream6 direct mode error flag */
    DMA_INT_TEIFLG6   =  0x10082000,    /*!< Stream6 transfer error flag */
    DMA_INT_HTIFLG6   =  0x10104000,    /*!< Stream6 half transfer complete flag */
    DMA_INT_TCIFLG6   =  0x10208000,    /*!< Stream6 transfer complete flag */

    DMA_INT_FEIFLG7   =  0x50400000,    /*!< Stream7 FIFO error flag */
    DMA_INT_DMEIFLG7  =  0x11001000,    /*!< Stream7 direct mode error flag */
    DMA_INT_TEIFLG7   =  0x12002000,    /*!< Stream7 transfer error flag */
    DMA_INT_HTIFLG7   =  0x14004000,    /*!< Stream7 half transfer complete flag */
    DMA_INT_TCIFLG7   =  0x18008000     /*!< Stream7 transfer complete flag */
} DMA_INT_FLAG_T;

/**
 * @brief DMA peripheral increment offset
 */
typedef enum
{
    DMA_PERIOSIZE_PSIZE,        /*!< Peripheral address increment is done
                                    accordingly to PSIZE parameter */
    DMA_PERIOSIZE_WORDALIGNED   /*!< Peripheral address increment offset is
                                    fixed to 4 (32-bit aligned addresses). */
} DMA_PERIOSIZE_T;

/**
 * @brief DMA flow controller
 */
typedef enum
{
    DMA_FLOWCTRL_MEMORY,        /*!< DMAy_Channelx transactions flow controller is
                                    the DMA controller */
    DMA_FLOWCTRL_PERIPHERAL     /*!< DMAy_Channelx transactions flow controller
                                    is the peripheral */
} DMA_FLOWCTRL_T;

/**
 * @brief DMA memory targets
 */
typedef enum
{
    DMA_MEMORY_0,   /*!< Memory 0 Address */
    DMA_MEMORY_1    /*!< Memory 1 Address */
} DMA_MEMORY_T;

/**@} end of group DMA_Enumerations*/

/** @addtogroup DMA_Structure Data Structure
  @{
*/

/**
 * @brief DMA Config struct definition
 */
typedef struct
{
    DMA_CHANNEL_T              channel;             /*!< Channel selection */
    uint32_t                   peripheralBaseAddr;  /*!< Peripheral base address */
    uint32_t                   memoryBaseAddr;      /*!< Memory base address */
    DMA_DIR_T                  dir;                 /*!< Direction */
    uint32_t                   bufferSize;          /*!< Buffer size */
    DMA_PERIPHERAL_INC_T       peripheralInc;       /*!< Peripheral increment mode selection */
    DMA_MEMORY_INC_T           memoryInc;           /*!< Memory increment mode selection */
    DMA_PERIPHERAL_DATA_SIZE_T peripheralDataSize;  /*!< Peripheral data size */
    DMA_MEMORY_DATA_SIZE_T     memoryDataSize;      /*!< Memory data size */
    DMA_LOOP_MODE_T            loopMode;            /*!< Loop mode */
    DMA_PRIORITY_T             priority;            /*!< DMA priority level */
    DMA_FIFOMODE_T             fifoMode;            /*!< FIFO mode selection */
    DMA_FIFOTHRESHOLD_T        fifoThreshold;       /*!< FIFO threshold configuration */
    DMA_MEMORYBURST_T          memoryBurst;         /*!< Memory burst configuration */
    DMA_PERIPHERALBURST_T      peripheralBurst;     /*!< Peripheral burst configuration */
} DMA_Config_T;

/**@} end of group DMA_Structure*/

/** @defgroup DMA_Functions
  @{
*/

/* DMA Reset and Configuration */
void DMA_Reset(DMA_Stream_T* stream);
void DMA_Config(DMA_Stream_T* stream, DMA_Config_T* dmaConfig);
void DMA_ConfigStructInit( DMA_Config_T* dmaConfig);
void DMA_Enable(DMA_Stream_T* stream);
void DMA_Disable(DMA_Stream_T* stream);

/* Stream Configuration  */
void DMA_ConfigPeriphIncOffsetSize(DMA_Stream_T* stream, DMA_PERIOSIZE_T perioSize);
void DMA_ConfigFlowController(DMA_Stream_T* stream, DMA_FLOWCTRL_T flowController);

/* DMA Data Number */
void DMA_ConfigDataNumber(DMA_Stream_T* stream, uint16_t dataNumber);
uint16_t DMA_ReadDataNumber(DMA_Stream_T* stream);

/* DMA Double Buffer mode */
void DMA_ConfigBufferMode(DMA_Stream_T* stream, uint32_t memory1BaseAddr, DMA_MEMORY_T currentMemory);
void DMA_EnableDoubleBufferMode(DMA_Stream_T* stream);
void DMA_DisableDoubleBufferMode(DMA_Stream_T* stream);
void DMA_ConfigMemoryTarget(DMA_Stream_T* stream, uint32_t memoryBaseAddr, DMA_MEMORY_T memoryTarget);
uint32_t DMA_ReadCurrentMemoryTarget(DMA_Stream_T* stream);

/* DMA Interrupts and flags */
uint8_t DMA_ReadCmdStatus(DMA_Stream_T* stream);
uint32_t DMA_ReadFIFOFlag(DMA_Stream_T* stream);

uint8_t DMA_ReadStatusFlag(DMA_Stream_T* stream, DMA_FLAG_T flag);
void DMA_ClearStatusFlag(DMA_Stream_T* stream, uint32_t flag);

void DMA_EnableInterrupt(DMA_Stream_T* stream, uint32_t interrupt);
void DMA_DisableInterrupt(DMA_Stream_T* stream, uint32_t interrupt);
uint8_t DMA_ReadIntFlag(DMA_Stream_T* stream, DMA_INT_FLAG_T flag);
void DMA_ClearIntFlag(DMA_Stream_T* stream, uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /*__APM32F4XX_DMA_H */

/**@} end of group DMA_Enumerations */
/**@} end of group DMA_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
