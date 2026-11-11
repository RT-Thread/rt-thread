/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l43x_dma.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32L43X_DMA_H__
#define __N32L43X_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l43x.h"

/** @addtogroup n32l43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup DMA
 * @{
 */

/** @addtogroup DMA_Exported_Types
 * @{
 */

/**
 * @brief  DMA Init structure definition
 */

typedef struct
{
    uint32_t PeriphAddr; /*!< Specifies the peripheral base address for DMAy Channelx. */

    uint32_t MemAddr; /*!< Specifies the memory base address for DMAy Channelx. */

    uint32_t Direction; /*!< Specifies if the peripheral is the source or destination.
                           This parameter can be a value of @ref DMA_data_transfer_direction */

    uint32_t BufSize; /*!< Specifies the buffer size, in data unit, of the specified Channel.
                                  The data unit is equal to the configuration set in PeriphDataSize
                                  or MemDataSize members depending in the transfer direction. */

    uint32_t PeriphInc; /*!< Specifies whether the Peripheral address register is incremented or not.
                                     This parameter can be a value of @ref DMA_peripheral_incremented_mode */

    uint32_t DMA_MemoryInc; /*!< Specifies whether the memory address register is incremented or not.
                                 This parameter can be a value of @ref DMA_memory_incremented_mode */

    uint32_t PeriphDataSize; /*!< Specifies the Peripheral data width.
                                          This parameter can be a value of @ref DMA_peripheral_data_size */

    uint32_t MemDataSize; /*!< Specifies the Memory data width.
                                      This parameter can be a value of @ref DMA_memory_data_size */

    uint32_t CircularMode; /*!< Specifies the operation mode of the DMAy Channelx.
                            This parameter can be a value of @ref DMA_circular_normal_mode.
                            @note: The circular buffer mode cannot be used if the memory-to-memory
                                   data transfer is configured on the selected Channel */

    uint32_t Priority; /*!< Specifies the software priority for the DMAy Channelx.
                                This parameter can be a value of @ref DMA_priority_level */

    uint32_t Mem2Mem; /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                           This parameter can be a value of @ref DMA_memory_to_memory */
} DMA_InitType;

/**
 * @}
 */

/** @addtogroup DMA_Exported_Constants
 * @{
 */

#define IS_DMA_ALL_PERIPH(PERIPH)                                                                                      \
    (((PERIPH) == DMA_CH1) || ((PERIPH) == DMA_CH2) || ((PERIPH) == DMA_CH3) || ((PERIPH) == DMA_CH4)              \
     || ((PERIPH) == DMA_CH5) || ((PERIPH) == DMA_CH6) || ((PERIPH) == DMA_CH7) || ((PERIPH) == DMA_CH8))

/** @addtogroup DMA_data_transfer_direction
 * @{
 */

#define DMA_DIR_PERIPH_DST ((uint32_t)0x00000010)
#define DMA_DIR_PERIPH_SRC ((uint32_t)0x00000000)
#define IS_DMA_DIR(DIR)    (((DIR) == DMA_DIR_PERIPH_DST) || ((DIR) == DMA_DIR_PERIPH_SRC))
/**
 * @}
 */

/** @addtogroup DMA_peripheral_incremented_mode
 * @{
 */

#define DMA_PERIPH_INC_ENABLE          ((uint32_t)0x00000040)
#define DMA_PERIPH_INC_DISABLE         ((uint32_t)0x00000000)
#define IS_DMA_PERIPH_INC_STATE(STATE) (((STATE) == DMA_PERIPH_INC_ENABLE) || ((STATE) == DMA_PERIPH_INC_DISABLE))
/**
 * @}
 */

/** @addtogroup DMA_memory_incremented_mode
 * @{
 */

#define DMA_MEM_INC_ENABLE          ((uint32_t)0x00000080)
#define DMA_MEM_INC_DISABLE         ((uint32_t)0x00000000)
#define IS_DMA_MEM_INC_STATE(STATE) (((STATE) == DMA_MEM_INC_ENABLE) || ((STATE) == DMA_MEM_INC_DISABLE))
/**
 * @}
 */

/** @addtogroup DMA_peripheral_data_size
 * @{
 */

#define DMA_PERIPH_DATA_SIZE_BYTE     ((uint32_t)0x00000000)
#define DMA_PERIPH_DATA_SIZE_HALFWORD ((uint32_t)0x00000100)
#define DMA_PERIPH_DATA_SIZE_WORD     ((uint32_t)0x00000200)
#define IS_DMA_PERIPH_DATA_SIZE(SIZE)                                                                                  \
    (((SIZE) == DMA_PERIPH_DATA_SIZE_BYTE) || ((SIZE) == DMA_PERIPH_DATA_SIZE_HALFWORD)                                \
     || ((SIZE) == DMA_PERIPH_DATA_SIZE_WORD))
/**
 * @}
 */

/** @addtogroup DMA_memory_data_size
 * @{
 */

#define DMA_MemoryDataSize_Byte     ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord ((uint32_t)0x00000400)
#define DMA_MemoryDataSize_Word     ((uint32_t)0x00000800)
#define IS_DMA_MEMORY_DATA_SIZE(SIZE)                                                                                  \
    (((SIZE) == DMA_MemoryDataSize_Byte) || ((SIZE) == DMA_MemoryDataSize_HalfWord)                                    \
     || ((SIZE) == DMA_MemoryDataSize_Word))
/**
 * @}
 */

/** @addtogroup DMA_circular_normal_mode
 * @{
 */

#define DMA_MODE_CIRCULAR ((uint32_t)0x00000020)
#define DMA_MODE_NORMAL   ((uint32_t)0x00000000)
#define IS_DMA_MODE(MODE) (((MODE) == DMA_MODE_CIRCULAR) || ((MODE) == DMA_MODE_NORMAL))
/**
 * @}
 */

/** @addtogroup DMA_priority_level
 * @{
 */

#define DMA_PRIORITY_VERY_HIGH ((uint32_t)0x00003000)
#define DMA_PRIORITY_HIGH      ((uint32_t)0x00002000)
#define DMA_PRIORITY_MEDIUM    ((uint32_t)0x00001000)
#define DMA_PRIORITY_LOW       ((uint32_t)0x00000000)
#define IS_DMA_PRIORITY(PRIORITY)                                                                                      \
    (((PRIORITY) == DMA_PRIORITY_VERY_HIGH) || ((PRIORITY) == DMA_PRIORITY_HIGH)                                       \
     || ((PRIORITY) == DMA_PRIORITY_MEDIUM) || ((PRIORITY) == DMA_PRIORITY_LOW))
/**
 * @}
 */

/** @addtogroup DMA_memory_to_memory
 * @{
 */

#define DMA_M2M_ENABLE          ((uint32_t)0x00004000)
#define DMA_M2M_DISABLE         ((uint32_t)0x00000000)
#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_ENABLE) || ((STATE) == DMA_M2M_DISABLE))

/**
 * @}
 */

/** @addtogroup DMA_interrupts_definition
 * @{
 */

#define DMA_INT_TXC           ((uint32_t)0x00000002)
#define DMA_INT_HTX           ((uint32_t)0x00000004)
#define DMA_INT_ERR           ((uint32_t)0x00000008)
#define IS_DMA_CONFIG_INT(IT) ((((IT)&0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA_INT_GLB1 ((uint32_t)0x00000001)
#define DMA_INT_TXC1 ((uint32_t)0x00000002)
#define DMA_INT_HTX1 ((uint32_t)0x00000004)
#define DMA_INT_ERR1 ((uint32_t)0x00000008)
#define DMA_INT_GLB2 ((uint32_t)0x00000010)
#define DMA_INT_TXC2 ((uint32_t)0x00000020)
#define DMA_INT_HTX2 ((uint32_t)0x00000040)
#define DMA_INT_ERR2 ((uint32_t)0x00000080)
#define DMA_INT_GLB3 ((uint32_t)0x00000100)
#define DMA_INT_TXC3 ((uint32_t)0x00000200)
#define DMA_INT_HTX3 ((uint32_t)0x00000400)
#define DMA_INT_ERR3 ((uint32_t)0x00000800)
#define DMA_INT_GLB4 ((uint32_t)0x00001000)
#define DMA_INT_TXC4 ((uint32_t)0x00002000)
#define DMA_INT_HTX4 ((uint32_t)0x00004000)
#define DMA_INT_ERR4 ((uint32_t)0x00008000)
#define DMA_INT_GLB5 ((uint32_t)0x00010000)
#define DMA_INT_TXC5 ((uint32_t)0x00020000)
#define DMA_INT_HTX5 ((uint32_t)0x00040000)
#define DMA_INT_ERR5 ((uint32_t)0x00080000)
#define DMA_INT_GLB6 ((uint32_t)0x00100000)
#define DMA_INT_TXC6 ((uint32_t)0x00200000)
#define DMA_INT_HTX6 ((uint32_t)0x00400000)
#define DMA_INT_ERR6 ((uint32_t)0x00800000)
#define DMA_INT_GLB7 ((uint32_t)0x01000000)
#define DMA_INT_TXC7 ((uint32_t)0x02000000)
#define DMA_INT_HTX7 ((uint32_t)0x04000000)
#define DMA_INT_ERR7 ((uint32_t)0x08000000)
#define DMA_INT_GLB8 ((uint32_t)0x10000000)
#define DMA_INT_TXC8 ((uint32_t)0x20000000)
#define DMA_INT_HTX8 ((uint32_t)0x40000000)
#define DMA_INT_ERR8 ((uint32_t)0x80000000)


#define IS_DMA_CLR_INT(IT) ((IT) != 0x00)

#define IS_DMA_GET_IT(IT)                                                                                              \
    (((IT) == DMA_INT_GLB1) || ((IT) == DMA_INT_TXC1) || ((IT) == DMA_INT_HTX1) || ((IT) == DMA_INT_ERR1)          \
     || ((IT) == DMA_INT_GLB2) || ((IT) == DMA_INT_TXC2) || ((IT) == DMA_INT_HTX2) || ((IT) == DMA_INT_ERR2)       \
     || ((IT) == DMA_INT_GLB3) || ((IT) == DMA_INT_TXC3) || ((IT) == DMA_INT_HTX3) || ((IT) == DMA_INT_ERR3)       \
     || ((IT) == DMA_INT_GLB4) || ((IT) == DMA_INT_TXC4) || ((IT) == DMA_INT_HTX4) || ((IT) == DMA_INT_ERR4)       \
     || ((IT) == DMA_INT_GLB5) || ((IT) == DMA_INT_TXC5) || ((IT) == DMA_INT_HTX5) || ((IT) == DMA_INT_ERR5)       \
     || ((IT) == DMA_INT_GLB6) || ((IT) == DMA_INT_TXC6) || ((IT) == DMA_INT_HTX6) || ((IT) == DMA_INT_ERR6)       \
     || ((IT) == DMA_INT_GLB7) || ((IT) == DMA_INT_TXC7) || ((IT) == DMA_INT_HTX7) || ((IT) == DMA_INT_ERR7)       \
     || ((IT) == DMA_INT_GLB8) || ((IT) == DMA_INT_TXC8) || ((IT) == DMA_INT_HTX8) || ((IT) == DMA_INT_ERR8))

/**
 * @}
 */

/** @addtogroup DMA_flags_definition
 * @{
 */
#define DMA_FLAG_GL1 ((uint32_t)0x00000001)
#define DMA_FLAG_TC1 ((uint32_t)0x00000002)
#define DMA_FLAG_HT1 ((uint32_t)0x00000004)
#define DMA_FLAG_TE1 ((uint32_t)0x00000008)
#define DMA_FLAG_GL2 ((uint32_t)0x00000010)
#define DMA_FLAG_TC2 ((uint32_t)0x00000020)
#define DMA_FLAG_HT2 ((uint32_t)0x00000040)
#define DMA_FLAG_TE2 ((uint32_t)0x00000080)
#define DMA_FLAG_GL3 ((uint32_t)0x00000100)
#define DMA_FLAG_TC3 ((uint32_t)0x00000200)
#define DMA_FLAG_HT3 ((uint32_t)0x00000400)
#define DMA_FLAG_TE3 ((uint32_t)0x00000800)
#define DMA_FLAG_GL4 ((uint32_t)0x00001000)
#define DMA_FLAG_TC4 ((uint32_t)0x00002000)
#define DMA_FLAG_HT4 ((uint32_t)0x00004000)
#define DMA_FLAG_TE4 ((uint32_t)0x00008000)
#define DMA_FLAG_GL5 ((uint32_t)0x00010000)
#define DMA_FLAG_TC5 ((uint32_t)0x00020000)
#define DMA_FLAG_HT5 ((uint32_t)0x00040000)
#define DMA_FLAG_TE5 ((uint32_t)0x00080000)
#define DMA_FLAG_GL6 ((uint32_t)0x00100000)
#define DMA_FLAG_TC6 ((uint32_t)0x00200000)
#define DMA_FLAG_HT6 ((uint32_t)0x00400000)
#define DMA_FLAG_TE6 ((uint32_t)0x00800000)
#define DMA_FLAG_GL7 ((uint32_t)0x01000000)
#define DMA_FLAG_TC7 ((uint32_t)0x02000000)
#define DMA_FLAG_HT7 ((uint32_t)0x04000000)
#define DMA_FLAG_TE7 ((uint32_t)0x08000000)
#define DMA_FLAG_GL8 ((uint32_t)0x10000000)
#define DMA_FLAG_TC8 ((uint32_t)0x20000000)
#define DMA_FLAG_HT8 ((uint32_t)0x40000000)
#define DMA_FLAG_TE8 ((uint32_t)0x80000000)

#define IS_DMA_CLEAR_FLAG(FLAG) ((FLAG) != 0x00)

#define IS_DMA_GET_FLAG(FLAG)                                                                                          \
    (((FLAG) == DMA_FLAG_GL1) || ((FLAG) == DMA_FLAG_TC1) || ((FLAG) == DMA_FLAG_HT1) || ((FLAG) == DMA_FLAG_TE1)  \
     || ((FLAG) == DMA_FLAG_GL2) || ((FLAG) == DMA_FLAG_TC2) || ((FLAG) == DMA_FLAG_HT2)                            \
     || ((FLAG) == DMA_FLAG_TE2) || ((FLAG) == DMA_FLAG_GL3) || ((FLAG) == DMA_FLAG_TC3)                            \
     || ((FLAG) == DMA_FLAG_HT3) || ((FLAG) == DMA_FLAG_TE3) || ((FLAG) == DMA_FLAG_GL4)                            \
     || ((FLAG) == DMA_FLAG_TC4) || ((FLAG) == DMA_FLAG_HT4) || ((FLAG) == DMA_FLAG_TE4)                            \
     || ((FLAG) == DMA_FLAG_GL5) || ((FLAG) == DMA_FLAG_TC5) || ((FLAG) == DMA_FLAG_HT5)                            \
     || ((FLAG) == DMA_FLAG_TE5) || ((FLAG) == DMA_FLAG_GL6) || ((FLAG) == DMA_FLAG_TC6)                            \
     || ((FLAG) == DMA_FLAG_HT6) || ((FLAG) == DMA_FLAG_TE6) || ((FLAG) == DMA_FLAG_GL7)                            \
     || ((FLAG) == DMA_FLAG_TC7) || ((FLAG) == DMA_FLAG_HT7) || ((FLAG) == DMA_FLAG_TE7)                            \
     || ((FLAG) == DMA_FLAG_GL8) || ((FLAG) == DMA_FLAG_TC8) || ((FLAG) == DMA_FLAG_HT8)                            \
     || ((FLAG) == DMA_FLAG_TE8))
/**
 * @}
 */

/** @addtogroup DMA_Buffer_Size
 * @{
 */

#define IS_DMA_BUF_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/**
 * @}
 */

/** @addtogroup DMA_remap_request_definition
 * @{
 */
#define DMA_REMAP_ADC1                    ((uint32_t)0x00000000)
#define DMA_REMAP_USART1_TX               ((uint32_t)0x00000001)
#define DMA_REMAP_USART1_RX               ((uint32_t)0x00000002)
#define DMA_REMAP_USART2_TX               ((uint32_t)0x00000003)
#define DMA_REMAP_USART2_RX               ((uint32_t)0x00000004)
#define DMA_REMAP_USART3_TX               ((uint32_t)0x00000005)
#define DMA_REMAP_USART3_RX               ((uint32_t)0x00000006)
#define DMA_REMAP_UART4_TX                ((uint32_t)0x00000007)
#define DMA_REMAP_UART4_RX                ((uint32_t)0x00000008)
#define DMA_REMAP_UART5_TX                ((uint32_t)0x00000009)
#define DMA_REMAP_UART5_RX                ((uint32_t)0x0000000A)
#define DMA_REMAP_LPUART_TX               ((uint32_t)0x0000000B)
#define DMA_REMAP_LPUART_RX               ((uint32_t)0x0000000C)
#define DMA_REMAP_SPI1_TX                 ((uint32_t)0x0000000D)
#define DMA_REMAP_SPI1_RX                 ((uint32_t)0x0000000E)
#define DMA_REMAP_SPI2_TX                 ((uint32_t)0x0000000F)
#define DMA_REMAP_SPI2_RX                 ((uint32_t)0x00000010)
#define DMA_REMAP_I2C1_TX                 ((uint32_t)0x00000011)
#define DMA_REMAP_I2C1_RX                 ((uint32_t)0x00000012)
#define DMA_REMAP_I2C2_TX                 ((uint32_t)0x00000013)
#define DMA_REMAP_I2C2_RX                 ((uint32_t)0x00000014)
#define DMA_REMAP_DAC1                    ((uint32_t)0x00000015)
#define DMA_REMAP_TIM1_CH1                ((uint32_t)0x00000016)
#define DMA_REMAP_TIM1_CH2                ((uint32_t)0x00000017)
#define DMA_REMAP_TIM1_CH3                ((uint32_t)0x00000018)
#define DMA_REMAP_TIM1_CH4                ((uint32_t)0x00000019)
#define DMA_REMAP_TIM1_COM                ((uint32_t)0x0000001A)
#define DMA_REMAP_TIM1_UP                 ((uint32_t)0x0000001B)
#define DMA_REMAP_TIM1_TRIG               ((uint32_t)0x0000001C)
#define DMA_REMAP_TIM2_CH1                ((uint32_t)0x0000001D)
#define DMA_REMAP_TIM2_CH2                ((uint32_t)0x0000001E)
#define DMA_REMAP_TIM2_CH3                ((uint32_t)0x0000001F)
#define DMA_REMAP_TIM2_CH4                ((uint32_t)0x00000020)
#define DMA_REMAP_TIM2_UP                 ((uint32_t)0x00000021)
#define DMA_REMAP_TIM3_CH1                ((uint32_t)0x00000022)
#define DMA_REMAP_TIM3_CH3                ((uint32_t)0x00000023)
#define DMA_REMAP_TIM3_CH4                ((uint32_t)0x00000024)
#define DMA_REMAP_TIM3_UP                 ((uint32_t)0x00000025)
#define DMA_REMAP_TIM3_TRIG               ((uint32_t)0x00000026)
#define DMA_REMAP_TIM4_CH1                ((uint32_t)0x00000027)
#define DMA_REMAP_TIM4_CH2                ((uint32_t)0x00000028)
#define DMA_REMAP_TIM4_CH3                ((uint32_t)0x00000029)
#define DMA_REMAP_TIM4_UP                 ((uint32_t)0x0000002A)
#define DMA_REMAP_TIM5_CH1                ((uint32_t)0x0000002B)
#define DMA_REMAP_TIM5_CH2                ((uint32_t)0x0000002C)
#define DMA_REMAP_TIM5_CH3                ((uint32_t)0x0000002D)
#define DMA_REMAP_TIM5_CH4                ((uint32_t)0x0000002E)
#define DMA_REMAP_TIM5_UP                 ((uint32_t)0x0000002F)
#define DMA_REMAP_TIM5_TRIG               ((uint32_t)0x00000030)
#define DMA_REMAP_TIM6_UP                 ((uint32_t)0x00000031)
#define DMA_REMAP_TIM7_UP                 ((uint32_t)0x00000032)
#define DMA_REMAP_TIM8_CH1                ((uint32_t)0x00000033)
#define DMA_REMAP_TIM8_CH2                ((uint32_t)0x00000034)
#define DMA_REMAP_TIM8_CH3                ((uint32_t)0x00000035)
#define DMA_REMAP_TIM8_CH4                ((uint32_t)0x00000036)
#define DMA_REMAP_TIM8_COM                ((uint32_t)0x00000037)
#define DMA_REMAP_TIM8_UP                 ((uint32_t)0x00000038)
#define DMA_REMAP_TIM8_TRIG               ((uint32_t)0x00000039)
#define DMA_REMAP_TIM9_CH1                ((uint32_t)0x0000003A)
#define DMA_REMAP_TIM9_TRIG               ((uint32_t)0x0000003B)
#define DMA_REMAP_TIM9_CH3                ((uint32_t)0x0000003C)
#define DMA_REMAP_TIM9_CH4                ((uint32_t)0x0000003D)
#define DMA_REMAP_TIM9_UP                 ((uint32_t)0x0000003E)


#define IS_DMA_REMAP(FLAG)                                                                                             \
    (((FLAG) == DMA_REMAP_ADC1) || ((FLAG) == DMA_REMAP_USART1_TX) || ((FLAG) == DMA_REMAP_USART1_RX)               \
        || ((FLAG) == DMA_REMAP_USART2_TX) || ((FLAG) == DMA_REMAP_USART2_RX) || ((FLAG) == DMA_REMAP_USART3_TX)        \
        || ((FLAG) == DMA_REMAP_USART3_RX) || ((FLAG) == DMA_REMAP_UART4_TX)  || ((FLAG) == DMA_REMAP_UART4_RX)         \
        || ((FLAG) == DMA_REMAP_UART5_TX)  || ((FLAG) == DMA_REMAP_UART5_RX)  || ((FLAG) == DMA_REMAP_LPUART_TX)        \
        || ((FLAG) == DMA_REMAP_LPUART_RX) || ((FLAG) == DMA_REMAP_SPI1_TX)   || ((FLAG) == DMA_REMAP_SPI1_RX)          \
        || ((FLAG) == DMA_REMAP_SPI2_TX)  || ((FLAG) == DMA_REMAP_SPI2_RX) || ((FLAG) == DMA_REMAP_I2C1_TX)      \
        || ((FLAG) == DMA_REMAP_I2C1_RX)  || ((FLAG) == DMA_REMAP_I2C2_TX)  || ((FLAG) == DMA_REMAP_I2C2_RX)              \
        || ((FLAG) == DMA_REMAP_DAC1)     || ((FLAG) == DMA_REMAP_TIM1_CH1) || ((FLAG) == DMA_REMAP_TIM1_CH2)               \
        || ((FLAG) == DMA_REMAP_TIM1_CH3) || ((FLAG) == DMA_REMAP_TIM1_CH4) || ((FLAG) == DMA_REMAP_TIM1_COM)           \
        || ((FLAG) == DMA_REMAP_TIM1_UP)  || ((FLAG) == DMA_REMAP_TIM1_TRIG)|| ((FLAG) == DMA_REMAP_TIM2_CH1)           \
        || ((FLAG) == DMA_REMAP_TIM2_CH2) || ((FLAG) == DMA_REMAP_TIM2_CH3) || ((FLAG) == DMA_REMAP_TIM2_CH4)           \
        || ((FLAG) == DMA_REMAP_TIM2_UP)  || ((FLAG) == DMA_REMAP_TIM3_CH1) || ((FLAG) == DMA_REMAP_TIM3_CH3)           \
        || ((FLAG) == DMA_REMAP_TIM3_CH4) || ((FLAG) == DMA_REMAP_TIM3_UP)  || ((FLAG) == DMA_REMAP_TIM3_TRIG)          \
        || ((FLAG) == DMA_REMAP_TIM4_CH1) || ((FLAG) == DMA_REMAP_TIM4_CH2) || ((FLAG) == DMA_REMAP_TIM4_CH3)           \
        || ((FLAG) == DMA_REMAP_TIM4_UP)  || ((FLAG) == DMA_REMAP_TIM5_CH1) || ((FLAG) == DMA_REMAP_TIM5_CH2)           \
        || ((FLAG) == DMA_REMAP_TIM5_CH3) || ((FLAG) == DMA_REMAP_TIM5_CH4) || ((FLAG) == DMA_REMAP_TIM5_UP)            \
        || ((FLAG) == DMA_REMAP_TIM5_TRIG)|| ((FLAG) == DMA_REMAP_TIM6_UP)  || ((FLAG) == DMA_REMAP_TIM7_UP)            \
        || ((FLAG) == DMA_REMAP_TIM8_CH1) || ((FLAG) == DMA_REMAP_TIM8_CH2) || ((FLAG) == DMA_REMAP_TIM8_CH3)           \
        || ((FLAG) == DMA_REMAP_TIM8_CH4) || ((FLAG) == DMA_REMAP_TIM8_COM) || ((FLAG) == DMA_REMAP_TIM8_UP)            \
        || ((FLAG) == DMA_REMAP_TIM8_TRIG)|| ((FLAG) == DMA_REMAP_TIM9_CH1) || ((FLAG) == DMA_REMAP_TIM9_TRIG)          \
        || ((FLAG) == DMA_REMAP_TIM9_CH3) || ((FLAG) == DMA_REMAP_TIM9_CH4) || ((FLAG) == DMA_REMAP_TIM9_UP))
/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup DMA_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup DMA_Exported_Functions
 * @{
 */

void DMA_DeInit(DMA_ChannelType* DMAChx);
void DMA_Init(DMA_ChannelType* DMAChx, DMA_InitType* DMA_InitParam);
void DMA_StructInit(DMA_InitType* DMA_InitParam);
void DMA_EnableChannel(DMA_ChannelType* DMAChx, FunctionalState Cmd);
void DMA_ConfigInt(DMA_ChannelType* DMAChx, uint32_t DMAInt, FunctionalState Cmd);
void DMA_SetCurrDataCounter(DMA_ChannelType* DMAChx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_ChannelType* DMAChx);
FlagStatus DMA_GetFlagStatus(uint32_t DMAFlag, DMA_Module* DMAy);
void DMA_ClearFlag(uint32_t DMAFlag, DMA_Module* DMAy);
INTStatus DMA_GetIntStatus(uint32_t DMA_IT, DMA_Module* DMAy);
void DMA_ClrIntPendingBit(uint32_t DMA_IT, DMA_Module* DMAy);
void DMA_RequestRemap(uint32_t DMA_REMAP, DMA_Module* DMAy, DMA_ChannelType* DMAChx, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /*__N32L43X_DMA_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
