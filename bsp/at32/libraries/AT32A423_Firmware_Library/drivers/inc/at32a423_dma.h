/**
  **************************************************************************
  * @file     at32a423_dma.h
  * @brief    at32a423 dma header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32A423_DMA_H
#define __AT32A423_DMA_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32a423.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/** @defgroup DMA_interrupts_definition
  * @brief dma interrupt
  * @{
  */

#define DMA_FDT_INT                      ((uint32_t)0x00000002) /*!< dma full data transfer interrupt */
#define DMA_HDT_INT                      ((uint32_t)0x00000004) /*!< dma half data transfer interrupt */
#define DMA_DTERR_INT                    ((uint32_t)0x00000008) /*!< dma errorr interrupt */

/**
  * @}
  */

/** @defgroup DMA_flags_definition
  * @brief dma flag
  * @{
  */

#define DMA1_GL1_FLAG                    ((uint32_t)0x00000001) /*!< dma1 channel1 global flag */
#define DMA1_FDT1_FLAG                   ((uint32_t)0x00000002) /*!< dma1 channel1 full data transfer flag */
#define DMA1_HDT1_FLAG                   ((uint32_t)0x00000004) /*!< dma1 channel1 half data transfer flag */
#define DMA1_DTERR1_FLAG                 ((uint32_t)0x00000008) /*!< dma1 channel1 error flag */
#define DMA1_GL2_FLAG                    ((uint32_t)0x00000010) /*!< dma1 channel2 global flag */
#define DMA1_FDT2_FLAG                   ((uint32_t)0x00000020) /*!< dma1 channel2 full data transfer flag */
#define DMA1_HDT2_FLAG                   ((uint32_t)0x00000040) /*!< dma1 channel2 half data transfer flag */
#define DMA1_DTERR2_FLAG                 ((uint32_t)0x00000080) /*!< dma1 channel2 error flag */
#define DMA1_GL3_FLAG                    ((uint32_t)0x00000100) /*!< dma1 channel3 global flag */
#define DMA1_FDT3_FLAG                   ((uint32_t)0x00000200) /*!< dma1 channel3 full data transfer flag */
#define DMA1_HDT3_FLAG                   ((uint32_t)0x00000400) /*!< dma1 channel3 half data transfer flag */
#define DMA1_DTERR3_FLAG                 ((uint32_t)0x00000800) /*!< dma1 channel3 error flag */
#define DMA1_GL4_FLAG                    ((uint32_t)0x00001000) /*!< dma1 channel4 global flag */
#define DMA1_FDT4_FLAG                   ((uint32_t)0x00002000) /*!< dma1 channel4 full data transfer flag */
#define DMA1_HDT4_FLAG                   ((uint32_t)0x00004000) /*!< dma1 channel4 half data transfer flag */
#define DMA1_DTERR4_FLAG                 ((uint32_t)0x00008000) /*!< dma1 channel4 error flag */
#define DMA1_GL5_FLAG                    ((uint32_t)0x00010000) /*!< dma1 channel5 global flag */
#define DMA1_FDT5_FLAG                   ((uint32_t)0x00020000) /*!< dma1 channel5 full data transfer flag */
#define DMA1_HDT5_FLAG                   ((uint32_t)0x00040000) /*!< dma1 channel5 half data transfer flag */
#define DMA1_DTERR5_FLAG                 ((uint32_t)0x00080000) /*!< dma1 channel5 error flag */
#define DMA1_GL6_FLAG                    ((uint32_t)0x00100000) /*!< dma1 channel6 global flag */
#define DMA1_FDT6_FLAG                   ((uint32_t)0x00200000) /*!< dma1 channel6 full data transfer flag */
#define DMA1_HDT6_FLAG                   ((uint32_t)0x00400000) /*!< dma1 channel6 half data transfer flag */
#define DMA1_DTERR6_FLAG                 ((uint32_t)0x00800000) /*!< dma1 channel6 error flag */
#define DMA1_GL7_FLAG                    ((uint32_t)0x01000000) /*!< dma1 channel7 global flag */
#define DMA1_FDT7_FLAG                   ((uint32_t)0x02000000) /*!< dma1 channel7 full data transfer flag */
#define DMA1_HDT7_FLAG                   ((uint32_t)0x04000000) /*!< dma1 channel7 half data transfer flag */
#define DMA1_DTERR7_FLAG                 ((uint32_t)0x08000000) /*!< dma1 channel7 error flag */

#define DMA2_GL1_FLAG                    ((uint32_t)0x10000001) /*!< dma2 channel1 global flag */
#define DMA2_FDT1_FLAG                   ((uint32_t)0x10000002) /*!< dma2 channel1 full data transfer flag */
#define DMA2_HDT1_FLAG                   ((uint32_t)0x10000004) /*!< dma2 channel1 half data transfer flag */
#define DMA2_DTERR1_FLAG                 ((uint32_t)0x10000008) /*!< dma2 channel1 error flag */
#define DMA2_GL2_FLAG                    ((uint32_t)0x10000010) /*!< dma2 channel2 global flag */
#define DMA2_FDT2_FLAG                   ((uint32_t)0x10000020) /*!< dma2 channel2 full data transfer flag */
#define DMA2_HDT2_FLAG                   ((uint32_t)0x10000040) /*!< dma2 channel2 half data transfer flag */
#define DMA2_DTERR2_FLAG                 ((uint32_t)0x10000080) /*!< dma2 channel2 error flag */
#define DMA2_GL3_FLAG                    ((uint32_t)0x10000100) /*!< dma2 channel3 global flag */
#define DMA2_FDT3_FLAG                   ((uint32_t)0x10000200) /*!< dma2 channel3 full data transfer flag */
#define DMA2_HDT3_FLAG                   ((uint32_t)0x10000400) /*!< dma2 channel3 half data transfer flag */
#define DMA2_DTERR3_FLAG                 ((uint32_t)0x10000800) /*!< dma2 channel3 error flag */
#define DMA2_GL4_FLAG                    ((uint32_t)0x10001000) /*!< dma2 channel4 global flag */
#define DMA2_FDT4_FLAG                   ((uint32_t)0x10002000) /*!< dma2 channel4 full data transfer flag */
#define DMA2_HDT4_FLAG                   ((uint32_t)0x10004000) /*!< dma2 channel4 half data transfer flag */
#define DMA2_DTERR4_FLAG                 ((uint32_t)0x10008000) /*!< dma2 channel4 error flag */
#define DMA2_GL5_FLAG                    ((uint32_t)0x10010000) /*!< dma2 channel5 global flag */
#define DMA2_FDT5_FLAG                   ((uint32_t)0x10020000) /*!< dma2 channel5 full data transfer flag */
#define DMA2_HDT5_FLAG                   ((uint32_t)0x10040000) /*!< dma2 channel5 half data transfer flag */
#define DMA2_DTERR5_FLAG                 ((uint32_t)0x10080000) /*!< dma2 channel5 error flag */
#define DMA2_GL6_FLAG                    ((uint32_t)0x10100000) /*!< dma2 channel6 global flag */
#define DMA2_FDT6_FLAG                   ((uint32_t)0x10200000) /*!< dma2 channel6 full data transfer flag */
#define DMA2_HDT6_FLAG                   ((uint32_t)0x10400000) /*!< dma2 channel6 half data transfer flag */
#define DMA2_DTERR6_FLAG                 ((uint32_t)0x10800000) /*!< dma2 channel6 error flag */
#define DMA2_GL7_FLAG                    ((uint32_t)0x11000000) /*!< dma2 channel7 global flag */
#define DMA2_FDT7_FLAG                   ((uint32_t)0x12000000) /*!< dma2 channel7 full data transfer flag */
#define DMA2_HDT7_FLAG                   ((uint32_t)0x14000000) /*!< dma2 channel7 half data transfer flag */
#define DMA2_DTERR7_FLAG                 ((uint32_t)0x18000000) /*!< dma2 channel7 error flag */

/**
  * @brief dmamux flag
  */
#define DMAMUX_SYNC_OV1_FLAG             ((uint32_t)0x00000001) /*!< dmamux channel1 synchronization overrun event flag */
#define DMAMUX_SYNC_OV2_FLAG             ((uint32_t)0x00000002) /*!< dmamux channel2 synchronization overrun event flag */
#define DMAMUX_SYNC_OV3_FLAG             ((uint32_t)0x00000004) /*!< dmamux channel3 synchronization overrun event flag */
#define DMAMUX_SYNC_OV4_FLAG             ((uint32_t)0x00000008) /*!< dmamux channel4 synchronization overrun event flag */
#define DMAMUX_SYNC_OV5_FLAG             ((uint32_t)0x00000010) /*!< dmamux channel5 synchronization overrun event flag */
#define DMAMUX_SYNC_OV6_FLAG             ((uint32_t)0x00000020) /*!< dmamux channel6 synchronization overrun event flag */
#define DMAMUX_SYNC_OV7_FLAG             ((uint32_t)0x00000040) /*!< dmamux channel7 synchronization overrun event flag */

#define DMAMUX_GEN_TRIG_OV1_FLAG         ((uint32_t)0x00000001) /*!< dmamux generator channel1 overrun event flag */
#define DMAMUX_GEN_TRIG_OV2_FLAG         ((uint32_t)0x00000002) /*!< dmamux generator channel2 overrun event flag */
#define DMAMUX_GEN_TRIG_OV3_FLAG         ((uint32_t)0x00000004) /*!< dmamux generator channel3 overrun event flag */
#define DMAMUX_GEN_TRIG_OV4_FLAG         ((uint32_t)0x00000008) /*!< dmamux generator channel4 overrun event flag */

/**
  * @}
  */

/** @defgroup DMA_exported_types
  * @{
  */

/**
  * @brief dma direction type
  */
typedef enum
{
  DMA_DIR_PERIPHERAL_TO_MEMORY           = 0x0000, /*!< dma data transfer direction: peripheral to memory */
  DMA_DIR_MEMORY_TO_PERIPHERAL           = 0x0010, /*!< dma data transfer direction: memory to peripheral */
  DMA_DIR_MEMORY_TO_MEMORY               = 0x4000  /*!< dma data transfer direction: memory to memory */
} dma_dir_type;

/**
  * @brief dma peripheral data size type
  */
typedef enum
{
  DMA_PERIPHERAL_DATA_WIDTH_BYTE         = 0x00, /*!< dma peripheral databus width 8bit */
  DMA_PERIPHERAL_DATA_WIDTH_HALFWORD     = 0x01, /*!< dma peripheral databus width 16bit */
  DMA_PERIPHERAL_DATA_WIDTH_WORD         = 0x02  /*!< dma peripheral databus width 32bit */
} dma_peripheral_data_size_type;

/**
  * @brief dma memory data size type
  */
typedef enum
{
  DMA_MEMORY_DATA_WIDTH_BYTE             = 0x00, /*!< dma memory databus width 8bit */
  DMA_MEMORY_DATA_WIDTH_HALFWORD         = 0x01, /*!< dma memory databus width 16bit */
  DMA_MEMORY_DATA_WIDTH_WORD             = 0x02  /*!< dma memory databus width 32bit */
} dma_memory_data_size_type;

/**
  * @brief dma priority level type
  */
typedef enum
{
  DMA_PRIORITY_LOW                       = 0x00, /*!< dma channel priority: low */
  DMA_PRIORITY_MEDIUM                    = 0x01, /*!< dma channel priority: medium */
  DMA_PRIORITY_HIGH                      = 0x02, /*!< dma channel priority: high */
  DMA_PRIORITY_VERY_HIGH                 = 0x03  /*!< dma channel priority: very high */
} dma_priority_level_type;

/**
  * @brief dmamux request type
  */
typedef enum
{
  DMAMUX_DMAREQ_ID_REQ_G1                = 0x01, /*!< dmamux channel dma request inputs resources: generator channel1 */
  DMAMUX_DMAREQ_ID_REQ_G2                = 0x02, /*!< dmamux channel dma request inputs resources: generator channel2 */
  DMAMUX_DMAREQ_ID_REQ_G3                = 0x03, /*!< dmamux channel dma request inputs resources: generator channel3 */
  DMAMUX_DMAREQ_ID_REQ_G4                = 0x04, /*!< dmamux channel dma request inputs resources: generator channel4 */
  DMAMUX_DMAREQ_ID_ADC1                  = 0x05, /*!< dmamux channel dma request inputs resources: adc1 */
  DMAMUX_DMAREQ_ID_DAC1                  = 0x06, /*!< dmamux channel dma request inputs resources: dac1 */
  DMAMUX_DMAREQ_ID_DAC2                  = 0x29, /*!< dmamux channel dma request inputs resources: dac2 */
  DMAMUX_DMAREQ_ID_TMR6_OVERFLOW         = 0x08, /*!< dmamux channel dma request inputs resources: timer6 overflow */
  DMAMUX_DMAREQ_ID_TMR7_OVERFLOW         = 0x09, /*!< dmamux channel dma request inputs resources: timer7 overflow */
  DMAMUX_DMAREQ_ID_SPI1_RX               = 0x0A, /*!< dmamux channel dma request inputs resources: spi1 rx */
  DMAMUX_DMAREQ_ID_SPI1_TX               = 0x0B, /*!< dmamux channel dma request inputs resources: spi1 tx */
  DMAMUX_DMAREQ_ID_SPI2_RX               = 0x0C, /*!< dmamux channel dma request inputs resources: spi2 rx */
  DMAMUX_DMAREQ_ID_SPI2_TX               = 0x0D, /*!< dmamux channel dma request inputs resources: spi2 tx */
  DMAMUX_DMAREQ_ID_SPI3_RX               = 0x0E, /*!< dmamux channel dma request inputs resources: spi3 rx */
  DMAMUX_DMAREQ_ID_SPI3_TX               = 0x0F, /*!< dmamux channel dma request inputs resources: spi3 tx */
  DMAMUX_DMAREQ_ID_I2C1_RX               = 0x10, /*!< dmamux channel dma request inputs resources: i2c1_rx */
  DMAMUX_DMAREQ_ID_I2C1_TX               = 0x11, /*!< dmamux channel dma request inputs resources: i2c1_tx */
  DMAMUX_DMAREQ_ID_I2C2_RX               = 0x12, /*!< dmamux channel dma request inputs resources: i2c2_rx */
  DMAMUX_DMAREQ_ID_I2C2_TX               = 0x13, /*!< dmamux channel dma request inputs resources: i2c2_tx */
  DMAMUX_DMAREQ_ID_I2C3_RX               = 0x14, /*!< dmamux channel dma request inputs resources: i2c3_rx */
  DMAMUX_DMAREQ_ID_I2C3_TX               = 0x15, /*!< dmamux channel dma request inputs resources: i2c3_tx */
  DMAMUX_DMAREQ_ID_USART1_RX             = 0x18, /*!< dmamux channel dma request inputs resources: usart1_rx */
  DMAMUX_DMAREQ_ID_USART1_TX             = 0x19, /*!< dmamux channel dma request inputs resources: usart1_tx */
  DMAMUX_DMAREQ_ID_USART2_RX             = 0x1A, /*!< dmamux channel dma request inputs resources: usart2_rx */
  DMAMUX_DMAREQ_ID_USART2_TX             = 0x1B, /*!< dmamux channel dma request inputs resources: usart2_tx */
  DMAMUX_DMAREQ_ID_USART3_RX             = 0x1C, /*!< dmamux channel dma request inputs resources: usart3_rx */
  DMAMUX_DMAREQ_ID_USART3_TX             = 0x1D, /*!< dmamux channel dma request inputs resources: usart3_tx */
  DMAMUX_DMAREQ_ID_USART4_RX             = 0x1E, /*!< dmamux channel dma request inputs resources: uart4_rx */
  DMAMUX_DMAREQ_ID_USART4_TX             = 0x1F, /*!< dmamux channel dma request inputs resources: uart4_tx */
  DMAMUX_DMAREQ_ID_USART5_RX             = 0x20, /*!< dmamux channel dma request inputs resources: uart5_rx */
  DMAMUX_DMAREQ_ID_USART5_TX             = 0x21, /*!< dmamux channel dma request inputs resources: uart5_tx */
  DMAMUX_DMAREQ_ID_USART6_RX             = 0x72, /*!< dmamux channel dma request inputs resources: usart6_rx */
  DMAMUX_DMAREQ_ID_USART6_TX             = 0x73, /*!< dmamux channel dma request inputs resources: usart6_tx */
  DMAMUX_DMAREQ_ID_USART7_RX             = 0x74, /*!< dmamux channel dma request inputs resources: uart7_rx */
  DMAMUX_DMAREQ_ID_USART7_TX             = 0x75, /*!< dmamux channel dma request inputs resources: uart7_tx */
  DMAMUX_DMAREQ_ID_USART8_RX             = 0x76, /*!< dmamux channel dma request inputs resources: uart8_rx */
  DMAMUX_DMAREQ_ID_USART8_TX             = 0x77, /*!< dmamux channel dma request inputs resources: uart8_tx */
  DMAMUX_DMAREQ_ID_TMR1_CH1              = 0x2A, /*!< dmamux channel dma request inputs resources: timer1 ch1 */
  DMAMUX_DMAREQ_ID_TMR1_CH2              = 0x2B, /*!< dmamux channel dma request inputs resources: timer1 ch2 */
  DMAMUX_DMAREQ_ID_TMR1_CH3              = 0x2C, /*!< dmamux channel dma request inputs resources: timer1 ch3 */
  DMAMUX_DMAREQ_ID_TMR1_CH4              = 0x2D, /*!< dmamux channel dma request inputs resources: timer1 ch4 */
  DMAMUX_DMAREQ_ID_TMR1_OVERFLOW         = 0x2E, /*!< dmamux channel dma request inputs resources: timer1 overflow */
  DMAMUX_DMAREQ_ID_TMR1_TRIG             = 0x2F, /*!< dmamux channel dma request inputs resources: timer1 trigger */
  DMAMUX_DMAREQ_ID_TMR1_HALL             = 0x30, /*!< dmamux channel dma request inputs resources: timer1 hall */
  DMAMUX_DMAREQ_ID_TMR2_CH1              = 0x38, /*!< dmamux channel dma request inputs resources: timer2 ch1 */
  DMAMUX_DMAREQ_ID_TMR2_CH2              = 0x39, /*!< dmamux channel dma request inputs resources: timer2 ch2 */
  DMAMUX_DMAREQ_ID_TMR2_CH3              = 0x3A, /*!< dmamux channel dma request inputs resources: timer2 ch3 */
  DMAMUX_DMAREQ_ID_TMR2_CH4              = 0x3B, /*!< dmamux channel dma request inputs resources: timer2 ch4 */
  DMAMUX_DMAREQ_ID_TMR2_OVERFLOW         = 0x3C, /*!< dmamux channel dma request inputs resources: timer2 overflow */
  DMAMUX_DMAREQ_ID_TMR2_TRIG             = 0x7E, /*!< dmamux channel dma request inputs resources: timer2 trigger */
  DMAMUX_DMAREQ_ID_TMR3_CH1              = 0x3D, /*!< dmamux channel dma request inputs resources: timer3 ch1 */
  DMAMUX_DMAREQ_ID_TMR3_CH2              = 0x3E, /*!< dmamux channel dma request inputs resources: timer3 ch2 */
  DMAMUX_DMAREQ_ID_TMR3_CH3              = 0x3F, /*!< dmamux channel dma request inputs resources: timer3 ch3 */
  DMAMUX_DMAREQ_ID_TMR3_CH4              = 0x40, /*!< dmamux channel dma request inputs resources: timer3 ch4 */
  DMAMUX_DMAREQ_ID_TMR3_OVERFLOW         = 0x41, /*!< dmamux channel dma request inputs resources: timer3 overflow */
  DMAMUX_DMAREQ_ID_TMR3_TRIG             = 0x42, /*!< dmamux channel dma request inputs resources: timer3 trigger */
  DMAMUX_DMAREQ_ID_TMR4_CH1              = 0x43, /*!< dmamux channel dma request inputs resources: timer4 ch1 */
  DMAMUX_DMAREQ_ID_TMR4_CH2              = 0x44, /*!< dmamux channel dma request inputs resources: timer4 ch2 */
  DMAMUX_DMAREQ_ID_TMR4_CH3              = 0x45, /*!< dmamux channel dma request inputs resources: timer4 ch3 */
  DMAMUX_DMAREQ_ID_TMR4_CH4              = 0x46, /*!< dmamux channel dma request inputs resources: timer4 ch4 */
  DMAMUX_DMAREQ_ID_TMR4_OVERFLOW         = 0x47, /*!< dmamux channel dma request inputs resources: timer4 overflow */
  DMAMUX_DMAREQ_ID_TMR4_TRIG             = 0x7F, /*!< dmamux channel dma request inputs resources: timer4 trigger */
  DMAMUX_DMAREQ_ID_TMR9_CH1              = 0x4E, /*!< dmamux channel dma request inputs resources: timer9 ch1 */
  DMAMUX_DMAREQ_ID_TMR9_CH2              = 0x7C, /*!< dmamux channel dma request inputs resources: timer9 ch2 */
  DMAMUX_DMAREQ_ID_TMR9_OVERFLOW         = 0x4F, /*!< dmamux channel dma request inputs resources: timer9 overflow */
  DMAMUX_DMAREQ_ID_TMR9_TRIG             = 0x50, /*!< dmamux channel dma request inputs resources: timer9 trigger */
  DMAMUX_DMAREQ_ID_TMR9_HALL             = 0x51, /*!< dmamux channel dma request inputs resources: timer9 trigger */
  DMAMUX_DMAREQ_ID_TMR10_CH1             = 0x52, /*!< dmamux channel dma request inputs resources: timer10 ch1 */
  DMAMUX_DMAREQ_ID_TMR10_OVERFLOW        = 0x53, /*!< dmamux channel dma request inputs resources: timer10 overflow */
  DMAMUX_DMAREQ_ID_TMR11_CH1             = 0x54, /*!< dmamux channel dma request inputs resources: timer11 ch1 */
  DMAMUX_DMAREQ_ID_TMR11_OVERFLOW        = 0x55, /*!< dmamux channel dma request inputs resources: timer11 overflow */
  DMAMUX_DMAREQ_ID_TMR12_CH1             = 0x5F, /*!< dmamux channel dma request inputs resources: timer12 ch1 */
  DMAMUX_DMAREQ_ID_TMR12_CH2             = 0x7D, /*!< dmamux channel dma request inputs resources: timer12 ch2 */
  DMAMUX_DMAREQ_ID_TMR12_OVERFLOW        = 0x60, /*!< dmamux channel dma request inputs resources: timer12 overflow */
  DMAMUX_DMAREQ_ID_TMR12_TRIG            = 0x61, /*!< dmamux channel dma request inputs resources: timer12 trigger */
  DMAMUX_DMAREQ_ID_TMR12_HALL            = 0x62, /*!< dmamux channel dma request inputs resources: timer12 trigger */
  DMAMUX_DMAREQ_ID_TMR13_CH1             = 0x78, /*!< dmamux channel dma request inputs resources: timer13 ch1 */
  DMAMUX_DMAREQ_ID_TMR13_OVERFLOW        = 0x79, /*!< dmamux channel dma request inputs resources: timer13 overflow */
  DMAMUX_DMAREQ_ID_TMR14_CH1             = 0x7A, /*!< dmamux channel dma request inputs resources: timer14 ch1 */
  DMAMUX_DMAREQ_ID_TMR14_OVERFLOW        = 0x7B, /*!< dmamux channel dma request inputs resources: timer14 overflow */
} dmamux_requst_id_sel_type;

/**
  * @brief dmamux sync id type
  */
typedef enum
{
  DMAMUX_SYNC_ID_EXINT0                  = 0x00, /*!< dmamux channel synchronization inputs resources: exint line0 */
  DMAMUX_SYNC_ID_EXINT1                  = 0x01, /*!< dmamux channel synchronization inputs resources: exint line1 */
  DMAMUX_SYNC_ID_EXINT2                  = 0x02, /*!< dmamux channel synchronization inputs resources: exint line2 */
  DMAMUX_SYNC_ID_EXINT3                  = 0x03, /*!< dmamux channel synchronization inputs resources: exint line3 */
  DMAMUX_SYNC_ID_EXINT4                  = 0x04, /*!< dmamux channel synchronization inputs resources: exint line4 */
  DMAMUX_SYNC_ID_EXINT5                  = 0x05, /*!< dmamux channel synchronization inputs resources: exint line5 */
  DMAMUX_SYNC_ID_EXINT6                  = 0x06, /*!< dmamux channel synchronization inputs resources: exint line6 */
  DMAMUX_SYNC_ID_EXINT7                  = 0x07, /*!< dmamux channel synchronization inputs resources: exint line7 */
  DMAMUX_SYNC_ID_EXINT8                  = 0x08, /*!< dmamux channel synchronization inputs resources: exint line8 */
  DMAMUX_SYNC_ID_EXINT9                  = 0x09, /*!< dmamux channel synchronization inputs resources: exint line9 */
  DMAMUX_SYNC_ID_EXINT10                 = 0x0A, /*!< dmamux channel synchronization inputs resources: exint line10 */
  DMAMUX_SYNC_ID_EXINT11                 = 0x0B, /*!< dmamux channel synchronization inputs resources: exint line11 */
  DMAMUX_SYNC_ID_EXINT12                 = 0x0C, /*!< dmamux channel synchronization inputs resources: exint line12 */
  DMAMUX_SYNC_ID_EXINT13                 = 0x0D, /*!< dmamux channel synchronization inputs resources: exint line13 */
  DMAMUX_SYNC_ID_EXINT14                 = 0x0E, /*!< dmamux channel synchronization inputs resources: exint line14 */
  DMAMUX_SYNC_ID_EXINT15                 = 0x0F, /*!< dmamux channel synchronization inputs resources: exint line15 */
  DMAMUX_SYNC_ID_DMAMUX_CH1_EVT          = 0x10, /*!< dmamux channel synchronization inputs resources: dmamux channel1 event */
  DMAMUX_SYNC_ID_DMAMUX_CH2_EVT          = 0x11, /*!< dmamux channel synchronization inputs resources: dmamux channel2 event */
  DMAMUX_SYNC_ID_DMAMUX_CH3_EVT          = 0x12, /*!< dmamux channel synchronization inputs resources: dmamux channel3 event */
  DMAMUX_SYNC_ID_DMAMUX_CH4_EVT          = 0x13, /*!< dmamux channel synchronization inputs resources: dmamux channel4 event */
  DMAMUX_SYNC_ID_DMAMUX_CH5_EVT          = 0x14, /*!< dmamux channel synchronization inputs resources: dmamux channel5 event */
  DMAMUX_SYNC_ID_DMAMUX_CH6_EVT          = 0x15, /*!< dmamux channel synchronization inputs resources: dmamux channel6 event */
  DMAMUX_SYNC_ID_DMAMUX_CH7_EVT          = 0x16  /*!< dmamux channel synchronization inputs resources: dmamux channel7 event */
} dmamux_sync_id_sel_type;

/**
  * @brief dmamux sync polarity type
  */
typedef enum
{
  DMAMUX_SYNC_POLARITY_DISABLE           = 0x00, /*!< dmamux channel synchronization inputs resources polarity default value */
  DMAMUX_SYNC_POLARITY_RISING            = 0x01, /*!< dmamux channel synchronization inputs resources polarity: rising */
  DMAMUX_SYNC_POLARITY_FALLING           = 0x02, /*!< dmamux channel synchronization inputs resources polarity: falling */
  DMAMUX_SYNC_POLARITY_RISING_FALLING    = 0x03  /*!< dmamux channel synchronization inputs resources polarity: rising_falling */
} dmamux_sync_pol_type;

/**
  * @brief dmamux generator id type
  */
typedef enum
{
  DMAMUX_GEN_ID_EXINT0                   = 0x00, /*!< dmamux generator channel inputs resources: exint line0 */
  DMAMUX_GEN_ID_EXINT1                   = 0x01, /*!< dmamux generator channel inputs resources: exint line1 */
  DMAMUX_GEN_ID_EXINT2                   = 0x02, /*!< dmamux generator channel inputs resources: exint line2 */
  DMAMUX_GEN_ID_EXINT3                   = 0x03, /*!< dmamux generator channel inputs resources: exint line3 */
  DMAMUX_GEN_ID_EXINT4                   = 0x04, /*!< dmamux generator channel inputs resources: exint line4 */
  DMAMUX_GEN_ID_EXINT5                   = 0x05, /*!< dmamux generator channel inputs resources: exint line5 */
  DMAMUX_GEN_ID_EXINT6                   = 0x06, /*!< dmamux generator channel inputs resources: exint line6 */
  DMAMUX_GEN_ID_EXINT7                   = 0x07, /*!< dmamux generator channel inputs resources: exint line7 */
  DMAMUX_GEN_ID_EXINT8                   = 0x08, /*!< dmamux generator channel inputs resources: exint line8 */
  DMAMUX_GEN_ID_EXINT9                   = 0x09, /*!< dmamux generator channel inputs resources: exint line9 */
  DMAMUX_GEN_ID_EXINT10                  = 0x0A, /*!< dmamux generator channel inputs resources: exint line10 */
  DMAMUX_GEN_ID_EXINT11                  = 0x0B, /*!< dmamux generator channel inputs resources: exint line11 */
  DMAMUX_GEN_ID_EXINT12                  = 0x0C, /*!< dmamux generator channel inputs resources: exint line12 */
  DMAMUX_GEN_ID_EXINT13                  = 0x0D, /*!< dmamux generator channel inputs resources: exint line13 */
  DMAMUX_GEN_ID_EXINT14                  = 0x0E, /*!< dmamux generator channel inputs resources: exint line14 */
  DMAMUX_GEN_ID_EXINT15                  = 0x0F, /*!< dmamux generator channel inputs resources: exint line15 */
  DMAMUX_GEN_ID_DMAMUX_CH1_EVT           = 0x10, /*!< dmamux generator channel inputs resources: dmamux channel1 event */
  DMAMUX_GEN_ID_DMAMUX_CH2_EVT           = 0x11, /*!< dmamux generator channel inputs resources: dmamux channel2 event */
  DMAMUX_GEN_ID_DMAMUX_CH3_EVT           = 0x12, /*!< dmamux generator channel inputs resources: dmamux channel3 event */
  DMAMUX_GEN_ID_DMAMUX_CH4_EVT           = 0x13, /*!< dmamux generator channel inputs resources: dmamux channel4 event */
  DMAMUX_GEN_ID_DMAMUX_CH5_EVT           = 0x14, /*!< dmamux generator channel inputs resources: dmamux channel5 event */
  DMAMUX_GEN_ID_DMAMUX_CH6_EVT           = 0x15, /*!< dmamux generator channel inputs resources: dmamux channel6 event */
  DMAMUX_GEN_ID_DMAMUX_CH7_EVT           = 0x16  /*!< dmamux generator channel inputs resources: dmamux channel7 event */
} dmamux_gen_id_sel_type;

/**
  * @brief dmamux generator polarity type
  */
typedef enum
{
  DMAMUX_GEN_POLARITY_DISABLE            = 0x00, /*!< dmamux generator channel inputs resources polarity default value */
  DMAMUX_GEN_POLARITY_RISING             = 0x01, /*!< dmamux generator channel inputs resources polarity: rising */
  DMAMUX_GEN_POLARITY_FALLING            = 0x02, /*!< dmamux generator channel inputs resources polarity: falling */
  DMAMUX_GEN_POLARITY_RISING_FALLING     = 0x03  /*!< dmamux generator channel inputs resources polarity: rising_falling */
} dmamux_gen_pol_type;

/**
  * @brief dma init type
  */
typedef struct
{
  uint32_t                               peripheral_base_addr;    /*!< base addrress for peripheral */
  uint32_t                               memory_base_addr;        /*!< base addrress for memory */
  dma_dir_type                           direction;               /*!< dma transmit direction, peripheral as source or as destnation  */
  uint16_t                               buffer_size;             /*!< counter to transfer (0~0xFFFF) */
  confirm_state                          peripheral_inc_enable;   /*!< periphera address increment after one transmit */
  confirm_state                          memory_inc_enable;       /*!< memory address increment after one transmit */
  dma_peripheral_data_size_type          peripheral_data_width;   /*!< peripheral data width for transmit */
  dma_memory_data_size_type              memory_data_width;       /*!< memory data width for transmit */
  confirm_state                          loop_mode_enable;        /*!< when loop mode enable, buffer size will reload if count to 0*/
  dma_priority_level_type                priority;                /*!< dma priority can choose from very high,high,dedium or low */
} dma_init_type;

/**
  * @brief dmamux sync init type
  */
typedef struct
{
  dmamux_sync_id_sel_type                sync_signal_sel;     /*!< dma dmamux synchronization input select */
  uint32_t                               sync_polarity;       /*!< dma dmamux synchronization polarity */
  uint32_t                               sync_request_number; /*!< dma dmamux number of dma requests before an output event is generated  */
  confirm_state                          sync_event_enable;   /*!< dma dmamux event generation disabled */
  confirm_state                          sync_enable;         /*!< dma dmamux synchronization enable */
} dmamux_sync_init_type;

/**
  * @brief dmamux generator init type
  */
typedef struct
{
  dmamux_gen_id_sel_type                 gen_signal_sel;     /*!< dma dmamux generator dma request trigger input select */
  dmamux_gen_pol_type                    gen_polarity;       /*!< dma dmamux generator trigger polarity */
  uint32_t                               gen_request_number; /*!< dma dmamux the number of dma requests to be generated after a trigger event  */
  confirm_state                          gen_enable;         /*!< dma dmamux generator enable */
} dmamux_gen_init_type;

/**
  * @brief type define dma1 register
  */
typedef struct
{
  /**
    * @brief dma sts register, offset:0x00
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t gf1                  : 1; /* [0] */
      __IO uint32_t fdtf1                : 1; /* [1] */
      __IO uint32_t hdtf1                : 1; /* [2] */
      __IO uint32_t dterrf1              : 1; /* [3] */
      __IO uint32_t gf2                  : 1; /* [4] */
      __IO uint32_t fdtf2                : 1; /* [5] */
      __IO uint32_t hdtf2                : 1; /* [6] */
      __IO uint32_t dterrf2              : 1; /* [7] */
      __IO uint32_t gf3                  : 1; /* [8] */
      __IO uint32_t fdtf3                : 1; /* [9] */
      __IO uint32_t hdtf3                : 1; /* [10] */
      __IO uint32_t dterrf3              : 1; /* [11] */
      __IO uint32_t gf4                  : 1; /* [12] */
      __IO uint32_t fdtf4                : 1; /* [13] */
      __IO uint32_t hdtf4                : 1; /* [14] */
      __IO uint32_t dterrf4              : 1; /* [15] */
      __IO uint32_t gf5                  : 1; /* [16] */
      __IO uint32_t fdtf5                : 1; /* [17] */
      __IO uint32_t hdtf5                : 1; /* [18] */
      __IO uint32_t dterrf5              : 1; /* [19] */
      __IO uint32_t gf6                  : 1; /* [20] */
      __IO uint32_t fdtf6                : 1; /* [21] */
      __IO uint32_t hdtf6                : 1; /* [22] */
      __IO uint32_t dterrf6              : 1; /* [23] */
      __IO uint32_t gf7                  : 1; /* [24] */
      __IO uint32_t fdtf7                : 1; /* [25] */
      __IO uint32_t hdtf7                : 1; /* [26] */
      __IO uint32_t dterrf7              : 1; /* [27] */
      __IO uint32_t reserved1            : 4; /* [31:28] */
    } sts_bit;
  };

  /**
    * @brief dma clr register, offset:0x04
    */
  union
  {
    __IO uint32_t clr;
    struct
    {
      __IO uint32_t gfc1                 : 1; /* [0] */
      __IO uint32_t fdtfc1               : 1; /* [1] */
      __IO uint32_t hdtfc1               : 1; /* [2] */
      __IO uint32_t dterrfc1             : 1; /* [3] */
      __IO uint32_t gfc2                 : 1; /* [4] */
      __IO uint32_t fdtfc2               : 1; /* [5] */
      __IO uint32_t hdtfc2               : 1; /* [6] */
      __IO uint32_t dterrfc2             : 1; /* [7] */
      __IO uint32_t gfc3                 : 1; /* [8] */
      __IO uint32_t fdtfc3               : 1; /* [9] */
      __IO uint32_t hdtfc3               : 1; /* [10] */
      __IO uint32_t dterrfc3             : 1; /* [11] */
      __IO uint32_t gfc4                 : 1; /* [12] */
      __IO uint32_t fdtfc4               : 1; /* [13] */
      __IO uint32_t hdtfc4               : 1; /* [14] */
      __IO uint32_t dterrfc4             : 1; /* [15] */
      __IO uint32_t gfc5                 : 1; /* [16] */
      __IO uint32_t fdtfc5               : 1; /* [17] */
      __IO uint32_t hdtfc5               : 1; /* [18] */
      __IO uint32_t dterrfc5             : 1; /* [19] */
      __IO uint32_t gfc6                 : 1; /* [20] */
      __IO uint32_t fdtfc6               : 1; /* [21] */
      __IO uint32_t hdtfc6               : 1; /* [22] */
      __IO uint32_t dterrfc6             : 1; /* [23] */
      __IO uint32_t gfc7                 : 1; /* [24] */
      __IO uint32_t fdtfc7               : 1; /* [25] */
      __IO uint32_t hdtfc7               : 1; /* [26] */
      __IO uint32_t dterrfc7             : 1; /* [27] */
      __IO uint32_t reserved1            : 4; /* [31:28] */
    } clr_bit;
  };

  /**
    * @brief reserved, offset:0x08~0xFC
    */
  __IO uint32_t reserved1[62];

  /**
    * @brief dmamux sel register, offset:0x100
    */
  union
  {
    __IO uint32_t muxsel;
    struct
    {
      __IO uint32_t tblsel               : 1; /* [0] */
      __IO uint32_t reserved1            : 31;/* [31:1] */
    }muxsel_bit;
  };

  /**
    * @brief reserved, offset:0x104~0x12C
    */
  __IO uint32_t reserved2[11];

  /**
    * @brief dmamux syncsts register, offset:0x130
    */
  union
  {
    __IO uint32_t muxsyncsts;
    struct
    {
      __IO uint32_t syncovf              : 7; /* [6:0] */
      __IO uint32_t reserved1            : 25;/* [31:7] */
    }muxsyncsts_bit;
  };

  /**
    * @brief dmamux syncclr register, offset:0x134
    */
  union
  {
    __IO uint32_t muxsyncclr;
    struct
    {
      __IO uint32_t syncovfc             : 7; /* [6:0] */
      __IO uint32_t reserved1            : 25;/* [31:7] */
    }muxsyncclr_bit;
  };

  /**
    * @brief dmamux request generator status register, offset:0x138
    */
  union
  {
    __IO uint32_t muxgsts;
    struct
    {
      __IO uint32_t trgovf               : 4; /* [3:0] */
      __IO uint32_t reserved1            : 28;/* [31:4] */
    }muxgsts_bit;
  };
  /**
    * @brief dmamux request generator status clear register, offset:0x13C
    */
  union
  {
    __IO uint32_t muxgclr;
    struct
    {
      __IO uint32_t trgovfc              : 4; /* [3:0] */
      __IO uint32_t reserved1            : 28;/* [31:4] */
    }muxgclr_bit;
  };
} dma_type;

/**
  * @brief type define dma channel register all
  */
typedef struct
{
  /**
    * @brief dma ch ctrl0 register, offset:0x08+20*(x-1) x=1...7
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t chen                 : 1; /* [0] */
      __IO uint32_t fdtien               : 1; /* [1] */
      __IO uint32_t hdtien               : 1; /* [2] */
      __IO uint32_t dterrien             : 1; /* [3] */
      __IO uint32_t dtd                  : 1; /* [4] */
      __IO uint32_t lm                   : 1; /* [5] */
      __IO uint32_t pincm                : 1; /* [6] */
      __IO uint32_t mincm                : 1; /* [7] */
      __IO uint32_t pwidth               : 2; /* [9:8] */
      __IO uint32_t mwidth               : 2; /* [11:10] */
      __IO uint32_t chpl                 : 2; /* [13:12] */
      __IO uint32_t m2m                  : 1; /* [14] */
      __IO uint32_t reserved1            : 17;/* [31:15] */
    } ctrl_bit;
  };

  /**
    * @brief dma tcnt register, offset:0x0C+20*(x-1) x=1...7
    */
  union
  {
    __IO uint32_t dtcnt;
    struct
    {
      __IO uint32_t cnt                  : 16;/* [15:0] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } dtcnt_bit;
  };

  /**
    * @brief dma cpba register, offset:0x10+20*(x-1) x=1...7
    */
  union
  {
    __IO uint32_t paddr;
    struct
    {
      __IO uint32_t paddr                : 32;/* [31:0] */
    } paddr_bit;
  };

  /**
    * @brief dma cmba register, offset:0x14+20*(x-1) x=1...7
    */
  union
  {
    __IO uint32_t maddr;
    struct
    {
      __IO uint32_t maddr                : 32;/* [31:0] */
    } maddr_bit;
  };
} dma_channel_type;

/**
  * @brief type define dmamux muxsctrl register
  */
typedef struct
{
  /**
    * @brief dma muxsctrl register
    */
  union
  {
    __IO uint32_t muxctrl;
    struct
    {
      __IO uint32_t reqsel               : 7; /* [6:0] */
      __IO uint32_t reserved1            : 1; /* [7] */
      __IO uint32_t syncovien            : 1; /* [8] */
      __IO uint32_t evtgen               : 1; /* [9] */
      __IO uint32_t reserved2            : 6; /* [15:10] */
      __IO uint32_t syncen               : 1; /* [16] */
      __IO uint32_t syncpol              : 2; /* [18:17] */
      __IO uint32_t reqcnt               : 5; /* [23:19] */
      __IO uint32_t syncsel              : 5; /* [28:24] */
      __IO uint32_t reserved3            : 3; /* [31:29] */
    }muxctrl_bit;
  };
} dmamux_channel_type;

/**
  * @brief type define dmamux request generator register all
  */
typedef struct
{
  /**
    * @brief dmamux request generator register, offset:0x120+4*(x-1) x=1...4
    */
  union
  {
    __IO uint32_t gctrl;
    struct
    {
      __IO uint32_t sigsel               : 5; /* [4:0] */
      __IO uint32_t reserved1            : 3; /* [7:5] */
      __IO uint32_t trgovien             : 1; /* [8] */
      __IO uint32_t reserved2            : 7; /* [15:9] */
      __IO uint32_t gen                  : 1; /* [16] */
      __IO uint32_t gpol                 : 2; /* [18:17] */
      __IO uint32_t greqcnt              : 5; /* [23:19] */
      __IO uint32_t reserved3            : 8; /* [31:24] */
    }gctrl_bit;
  };
} dmamux_generator_type;

/**
  * @}
  */

#define DMA1                             ((dma_type *) DMA1_BASE)
#define DMA1_CHANNEL1                    ((dma_channel_type *) DMA1_CHANNEL1_BASE)
#define DMA1_CHANNEL2                    ((dma_channel_type *) DMA1_CHANNEL2_BASE)
#define DMA1_CHANNEL3                    ((dma_channel_type *) DMA1_CHANNEL3_BASE)
#define DMA1_CHANNEL4                    ((dma_channel_type *) DMA1_CHANNEL4_BASE)
#define DMA1_CHANNEL5                    ((dma_channel_type *) DMA1_CHANNEL5_BASE)
#define DMA1_CHANNEL6                    ((dma_channel_type *) DMA1_CHANNEL6_BASE)
#define DMA1_CHANNEL7                    ((dma_channel_type *) DMA1_CHANNEL7_BASE)

#define DMA1MUX_CHANNEL1                 ((dmamux_channel_type *) DMA1MUX_CHANNEL1_BASE)
#define DMA1MUX_CHANNEL2                 ((dmamux_channel_type *) DMA1MUX_CHANNEL2_BASE)
#define DMA1MUX_CHANNEL3                 ((dmamux_channel_type *) DMA1MUX_CHANNEL3_BASE)
#define DMA1MUX_CHANNEL4                 ((dmamux_channel_type *) DMA1MUX_CHANNEL4_BASE)
#define DMA1MUX_CHANNEL5                 ((dmamux_channel_type *) DMA1MUX_CHANNEL5_BASE)
#define DMA1MUX_CHANNEL6                 ((dmamux_channel_type *) DMA1MUX_CHANNEL6_BASE)
#define DMA1MUX_CHANNEL7                 ((dmamux_channel_type *) DMA1MUX_CHANNEL7_BASE)

#define DMA1MUX_GENERATOR1               ((dmamux_generator_type *) DMA1MUX_GENERATOR1_BASE)
#define DMA1MUX_GENERATOR2               ((dmamux_generator_type *) DMA1MUX_GENERATOR2_BASE)
#define DMA1MUX_GENERATOR3               ((dmamux_generator_type *) DMA1MUX_GENERATOR3_BASE)
#define DMA1MUX_GENERATOR4               ((dmamux_generator_type *) DMA1MUX_GENERATOR4_BASE)

#define DMA2                             ((dma_type *) DMA2_BASE)
#define DMA2_CHANNEL1                    ((dma_channel_type *) DMA2_CHANNEL1_BASE)
#define DMA2_CHANNEL2                    ((dma_channel_type *) DMA2_CHANNEL2_BASE)
#define DMA2_CHANNEL3                    ((dma_channel_type *) DMA2_CHANNEL3_BASE)
#define DMA2_CHANNEL4                    ((dma_channel_type *) DMA2_CHANNEL4_BASE)
#define DMA2_CHANNEL5                    ((dma_channel_type *) DMA2_CHANNEL5_BASE)
#define DMA2_CHANNEL6                    ((dma_channel_type *) DMA2_CHANNEL6_BASE)
#define DMA2_CHANNEL7                    ((dma_channel_type *) DMA2_CHANNEL7_BASE)

#define DMA2MUX_CHANNEL1                 ((dmamux_channel_type *) DMA2MUX_CHANNEL1_BASE)
#define DMA2MUX_CHANNEL2                 ((dmamux_channel_type *) DMA2MUX_CHANNEL2_BASE)
#define DMA2MUX_CHANNEL3                 ((dmamux_channel_type *) DMA2MUX_CHANNEL3_BASE)
#define DMA2MUX_CHANNEL4                 ((dmamux_channel_type *) DMA2MUX_CHANNEL4_BASE)
#define DMA2MUX_CHANNEL5                 ((dmamux_channel_type *) DMA2MUX_CHANNEL5_BASE)
#define DMA2MUX_CHANNEL6                 ((dmamux_channel_type *) DMA2MUX_CHANNEL6_BASE)
#define DMA2MUX_CHANNEL7                 ((dmamux_channel_type *) DMA2MUX_CHANNEL7_BASE)

#define DMA2MUX_GENERATOR1               ((dmamux_generator_type *) DMA2MUX_GENERATOR1_BASE)
#define DMA2MUX_GENERATOR2               ((dmamux_generator_type *) DMA2MUX_GENERATOR2_BASE)
#define DMA2MUX_GENERATOR3               ((dmamux_generator_type *) DMA2MUX_GENERATOR3_BASE)
#define DMA2MUX_GENERATOR4               ((dmamux_generator_type *) DMA2MUX_GENERATOR4_BASE)

/** @defgroup DMA_exported_functions
  * @{
  */

/* dma controller function */
void dma_reset(dma_channel_type *dmax_channely);
void dma_data_number_set(dma_channel_type *dmax_channely, uint16_t data_number);
uint16_t dma_data_number_get(dma_channel_type *dmax_channely);
void dma_interrupt_enable(dma_channel_type *dmax_channely, uint32_t dma_int, confirm_state new_state);
void dma_channel_enable(dma_channel_type *dmax_channely, confirm_state new_state);
flag_status dma_flag_get(uint32_t dmax_flag);
flag_status dma_interrupt_flag_get(uint32_t dmax_flag);
void dma_flag_clear(uint32_t dmax_flag);
void dma_default_para_init(dma_init_type *dma_init_struct);
void dma_init(dma_channel_type *dmax_channely, dma_init_type *dma_init_struct);

/* dma requst multiplexer function */
void dma_flexible_config(dma_type* dma_x, dmamux_channel_type *dmamux_channelx, dmamux_requst_id_sel_type dmamux_req_sel);
void dmamux_enable(dma_type *dma_x, confirm_state new_state);
void dmamux_init(dmamux_channel_type *dmamux_channelx, dmamux_requst_id_sel_type dmamux_req_sel);
void dmamux_sync_default_para_init(dmamux_sync_init_type *dmamux_sync_init_struct);
void dmamux_sync_config(dmamux_channel_type *dmamux_channelx, dmamux_sync_init_type *dmamux_sync_init_struct);
void dmamux_generator_default_para_init(dmamux_gen_init_type *dmamux_gen_init_struct);
void dmamux_generator_config(dmamux_generator_type *dmamux_gen_x, dmamux_gen_init_type *dmamux_gen_init_struct);
void dmamux_sync_interrupt_enable(dmamux_channel_type *dmamux_channelx, confirm_state new_state);
void dmamux_generator_interrupt_enable(dmamux_generator_type *dmamux_gen_x, confirm_state new_state);
flag_status dmamux_sync_flag_get(dma_type *dma_x, uint32_t flag);
flag_status dmamux_sync_interrupt_flag_get(dma_type *dma_x, uint32_t flag);
void dmamux_sync_flag_clear(dma_type *dma_x, uint32_t flag);
flag_status dmamux_generator_flag_get(dma_type *dma_x, uint32_t flag);
flag_status dmamux_generator_interrupt_flag_get(dma_type *dma_x, uint32_t flag);
void dmamux_generator_flag_clear(dma_type *dma_x, uint32_t flag);

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
#endif

#endif
