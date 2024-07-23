/**
  **************************************************************************
  * @file     at32f435_437_edma.h
  * @brief    at32f435_437 edma header file
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
#ifndef __AT32F435_437_EDMA_H
#define __AT32F435_437_EDMA_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @addtogroup EDMA
  * @{
  */

/** @defgroup EDMA_interrupts_definition
  * @brief edma interrupt
  * @{
  */

#define EDMA_DMERR_INT                   ((uint32_t)0x00000002) /* edma direct mode error interrupt */
#define EDMA_DTERR_INT                   ((uint32_t)0x00000004) /* edma data transfer error interrupt */
#define EDMA_HDT_INT                     ((uint32_t)0x00000008) /* edma half data transfer interrupt */
#define EDMA_FDT_INT                     ((uint32_t)0x00000010) /* edma full data transfer interrupt */
#define EDMA_FERR_INT                    ((uint32_t)0x00000080) /* edma fifo error interrupt */

/**
  * @}
  */

/** @defgroup EDMA_flags_definition
  * @brief edma flag
  * @{
  */

#define EDMA_FERR1_FLAG                  ((uint32_t)0x10000001) /* edma stream1 fifo error flag */
#define EDMA_DMERR1_FLAG                 ((uint32_t)0x10000004) /* edma stream1 direct mode error flag */
#define EDMA_DTERR1_FLAG                 ((uint32_t)0x10000008) /* edma stream1 data transfer error flag */
#define EDMA_HDT1_FLAG                   ((uint32_t)0x10000010) /* edma stream1 half data transfer flag */
#define EDMA_FDT1_FLAG                   ((uint32_t)0x10000020) /* edma stream1 full data transfer flag */
#define EDMA_FERR2_FLAG                  ((uint32_t)0x10000040) /* edma stream2 fifo error flag */
#define EDMA_DMERR2_FLAG                 ((uint32_t)0x10000100) /* edma stream2 direct mode error flag */
#define EDMA_DTERR2_FLAG                 ((uint32_t)0x10000200) /* edma stream2 data transfer error flag */
#define EDMA_HDT2_FLAG                   ((uint32_t)0x10000400) /* edma stream2 half data transfer flag */
#define EDMA_FDT2_FLAG                   ((uint32_t)0x10000800) /* edma stream2 full data transfer flag */
#define EDMA_FERR3_FLAG                  ((uint32_t)0x10010000) /* edma stream3 fifo error flag */
#define EDMA_DMERR3_FLAG                 ((uint32_t)0x10040000) /* edma stream3 direct mode error flag */
#define EDMA_DTERR3_FLAG                 ((uint32_t)0x10080000) /* edma stream3 data transfer error flag */
#define EDMA_HDT3_FLAG                   ((uint32_t)0x10100000) /* edma stream3 half data transfer flag */
#define EDMA_FDT3_FLAG                   ((uint32_t)0x10200000) /* edma stream3 full data transfer flag */
#define EDMA_FERR4_FLAG                  ((uint32_t)0x10400000) /* edma stream4 fifo error flag */
#define EDMA_DMERR4_FLAG                 ((uint32_t)0x11000000) /* edma stream4 direct mode error flag */
#define EDMA_DTERR4_FLAG                 ((uint32_t)0x12000000) /* edma stream4 data transfer error flag */
#define EDMA_HDT4_FLAG                   ((uint32_t)0x14000000) /* edma stream4 half data transfer flag */
#define EDMA_FDT4_FLAG                   ((uint32_t)0x18000000) /* edma stream4 full data transfer flag */
#define EDMA_FERR5_FLAG                  ((uint32_t)0x20000001) /* edma stream5 fifo error flag */
#define EDMA_DMERR5_FLAG                 ((uint32_t)0x20000004) /* edma stream5 direct mode error flag */
#define EDMA_DTERR5_FLAG                 ((uint32_t)0x20000008) /* edma stream5 data transfer error flag */
#define EDMA_HDT5_FLAG                   ((uint32_t)0x20000010) /* edma stream5 half data transfer flag */
#define EDMA_FDT5_FLAG                   ((uint32_t)0x20000020) /* edma stream5 full data transfer flag */
#define EDMA_FERR6_FLAG                  ((uint32_t)0x20000040) /* edma stream6 fifo error flag */
#define EDMA_DMERR6_FLAG                 ((uint32_t)0x20000100) /* edma stream6 direct mode error flag */
#define EDMA_DTERR6_FLAG                 ((uint32_t)0x20000200) /* edma stream6 data transfer error flag */
#define EDMA_HDT6_FLAG                   ((uint32_t)0x20000400) /* edma stream6 half data transfer flag */
#define EDMA_FDT6_FLAG                   ((uint32_t)0x20000800) /* edma stream6 full data transfer flag */
#define EDMA_FERR7_FLAG                  ((uint32_t)0x20010000) /* edma stream7 fifo error flag */
#define EDMA_DMERR7_FLAG                 ((uint32_t)0x20040000) /* edma stream7 direct mode error flag */
#define EDMA_DTERR7_FLAG                 ((uint32_t)0x20080000) /* edma stream7 data transfer error flag */
#define EDMA_HDT7_FLAG                   ((uint32_t)0x20100000) /* edma stream7 half data transfer flag */
#define EDMA_FDT7_FLAG                   ((uint32_t)0x20200000) /* edma stream7 full data transfer flag */
#define EDMA_FERR8_FLAG                  ((uint32_t)0x20400000) /* edma stream8 fifo error flag */
#define EDMA_DMERR8_FLAG                 ((uint32_t)0x21000000) /* edma stream8 direct mode error flag */
#define EDMA_DTERR8_FLAG                 ((uint32_t)0x22000000) /* edma stream8 data transfer error flag */
#define EDMA_HDT8_FLAG                   ((uint32_t)0x24000000) /* edma stream8 half data transfer flag */
#define EDMA_FDT8_FLAG                   ((uint32_t)0x28000000) /* edma stream8 full data transfer flag */

/**
  * @brief masks define
  */
#define EDMA_STREAM1_INT_MASK            (uint32_t)(0x0000003D)                  /*!< edma stream1 interrupt mask */
#define EDMA_STREAM2_INT_MASK            (uint32_t)(EDMA_STREAM1_INT_MASK << 6)  /*!< edma stream2 interrupt mask */
#define EDMA_STREAM3_INT_MASK            (uint32_t)(EDMA_STREAM1_INT_MASK << 16) /*!< edma stream3 interrupt mask */
#define EDMA_STREAM4_INT_MASK            (uint32_t)(EDMA_STREAM1_INT_MASK << 22) /*!< edma stream4 interrupt mask */
#define EDMA_STREAM5_INT_MASK            (uint32_t)(EDMA_STREAM1_INT_MASK)       /*!< edma stream5 interrupt mask */
#define EDMA_STREAM6_INT_MASK            (uint32_t)(EDMA_STREAM2_INT_MASK)       /*!< edma stream6 interrupt mask */
#define EDMA_STREAM7_INT_MASK            (uint32_t)(EDMA_STREAM3_INT_MASK)       /*!< edma stream7 interrupt mask */
#define EDMA_STREAM8_INT_MASK            (uint32_t)(EDMA_STREAM4_INT_MASK)       /*!< edma stream8 interrupt mask */

/**
  * @brief edmamux flag
  */
#define EDMAMUX_SYNC_OV1_FLAG            ((uint32_t)0x00000001) /*!< edmamux stream1 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV2_FLAG            ((uint32_t)0x00000002) /*!< edmamux stream2 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV3_FLAG            ((uint32_t)0x00000004) /*!< edmamux stream3 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV4_FLAG            ((uint32_t)0x00000008) /*!< edmamux stream4 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV5_FLAG            ((uint32_t)0x00000010) /*!< edmamux stream5 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV6_FLAG            ((uint32_t)0x00000020) /*!< edmamux stream6 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV7_FLAG            ((uint32_t)0x00000040) /*!< edmamux stream7 synchronization overrun event flag */
#define EDMAMUX_SYNC_OV8_FLAG            ((uint32_t)0x00000080) /*!< edmamux stream8 synchronization overrun event flag */

#define EDMAMUX_GEN_TRIG_OV1_FLAG        ((uint32_t)0x00000001) /*!< edmamux generator channel1 overrun event flag */
#define EDMAMUX_GEN_TRIG_OV2_FLAG        ((uint32_t)0x00000002) /*!< edmamux generator channel2 overrun event flag */
#define EDMAMUX_GEN_TRIG_OV3_FLAG        ((uint32_t)0x00000004) /*!< edmamux generator channel3 overrun event flag */
#define EDMAMUX_GEN_TRIG_OV4_FLAG        ((uint32_t)0x00000008) /*!< edmamux generator channel4 overrun event flag */

/**
  * @}
  */

/** @defgroup EDMA_exported_types
  * @{
  */

/**
  * @brief edma memory targets define
  */
typedef enum
{
  EDMA_MEMORY_0                          = 0x00, /*!< current target is memory 0 */
  EDMA_MEMORY_1                          = 0x01  /*!< current target is memory 1 */
} edma_memory_type;

/**
  * @brief edma direction type
  */
typedef enum
{
  EDMA_DIR_PERIPHERAL_TO_MEMORY          = 0x00, /*!< data transfer direction: peripheral to memory */
  EDMA_DIR_MEMORY_TO_PERIPHERAL          = 0x01, /*!< data transfer direction: memory to peripheral */
  EDMA_DIR_MEMORY_TO_MEMORY              = 0x02  /*!< data transfer direction: memory to memory */
} edma_dir_type;

/**
  * @brief edma peripheral data size type
  */
typedef enum
{
  EDMA_PERIPHERAL_DATA_WIDTH_BYTE        = 0x00, /*!< peripheral data bus width is 8bit */
  EDMA_PERIPHERAL_DATA_WIDTH_HALFWORD    = 0x01, /*!< peripheral data bus width is 16bit */
  EDMA_PERIPHERAL_DATA_WIDTH_WORD        = 0x02  /*!< peripheral data bus width is 32bit */
} edma_peripheral_data_size_type;

/**
  * @brief edma memory data size type
  */
typedef enum
{
  EDMA_MEMORY_DATA_WIDTH_BYTE            = 0x00, /*!< memory data bus width is 8bit */
  EDMA_MEMORY_DATA_WIDTH_HALFWORD        = 0x01, /*!< memory data bus width is 16bit */
  EDMA_MEMORY_DATA_WIDTH_WORD            = 0x02  /*!< memory data bus width is 32bit */
} edma_memory_data_size_type;

/**
  * @brief edma priority level type
  */
typedef enum
{
  EDMA_PRIORITY_LOW                      = 0x00, /*!< stream priority: low */
  EDMA_PRIORITY_MEDIUM                   = 0x01, /*!< stream priority: medium */
  EDMA_PRIORITY_HIGH                     = 0x02, /*!< stream priority: high */
  EDMA_PRIORITY_VERY_HIGH                = 0x03  /*!< stream priority: very high */
} edma_priority_level_type;

/**
  * @brief edma fifo threshold level type
  */
typedef enum
{
  EDMA_FIFO_THRESHOLD_1QUARTER           = 0x00, /*!< fifo threshold level: 1quarter full */
  EDMA_FIFO_THRESHOLD_HALF               = 0x01, /*!< fifo threshold level: half full */
  EDMA_FIFO_THRESHOLD_3QUARTER           = 0x02, /*!< fifo threshold level: 13quarter full */
  EDMA_FIFO_THRESHOLD_FULL               = 0x03  /*!< fifo threshold level: full */
} edma_fifo_threshold_type;

/**
  * @brief edma fifo stutas level type
  */
typedef enum
{
  EDMA_FIFO_STATUS_LESS_1QUARTER         = 0x00, /*!< fifo stutas level: less 1quarter full */
  EDMA_FIFO_STATUS_1QUARTER              = 0x01, /*!< fifo stutas level: 1quarter full */
  EDMA_FIFO_STATUS_HALF                  = 0x02, /*!< fifo stutas level: half full */
  EDMA_FIFO_STATUS_3QUARTER              = 0x03, /*!< fifo stutas level: 3quarter full */
  EDMA_FIFO_STATUS_EMPTY                 = 0x04, /*!< fifo stutas level: empty */
  EDMA_FIFO_STATUS_FULL                  = 0x05  /*!< fifo stutas level: full */
} edma_fifo_stutas_type;

/**
  * @brief edma memory continuous mode type
  */
typedef enum
{
  EDMA_MEMORY_SINGLE                     = 0x00, /*!< memory single transfer */
  EDMA_MEMORY_BURST_4                    = 0x01, /*!< memory burst transfer 4 beats */
  EDMA_MEMORY_BURST_8                    = 0x02, /*!< memory burst transfer 8 beats */
  EDMA_MEMORY_BURST_16                   = 0x03  /*!< memory burst transfer 16 beats */
} edma_memory_burst_type;

/**
  * @brief edma peripheral continuous mode type
  */
typedef enum
{
  EDMA_PERIPHERAL_SINGLE                 = 0x00, /*!< peripheral single transfer */
  EDMA_PERIPHERAL_BURST_4                = 0x01, /*!< peripheral burst transfer 4 beats */
  EDMA_PERIPHERAL_BURST_8                = 0x02, /*!< peripheral burst transfer 8 beats */
  EDMA_PERIPHERAL_BURST_16               = 0x03  /*!< peripheral burst transfer 16 beats */
} edma_peripheral_burst_type;

/**
  * @brief edma peripheral increment offset size type
  */
typedef enum
{
  EDMA_PERIPHERAL_INC_PSIZE              = 0x00, /*!< peripheral offset is related to psize*/
  EDMA_PERIPHERAL_INC_4_BYTE             = 0x01  /*!< peripheral offset is 4 byte*/
} edma_peripheral_inc_offset_type;

/**
  * @brief edmamux request id select type
  */
typedef enum
{
  EDMAMUX_DMAREQ_ID_REQ_G1               = 0x01, /*!< edmamux channel request inputs resources: generator channel1 */
  EDMAMUX_DMAREQ_ID_REQ_G2               = 0x02, /*!< edmamux channel request inputs resources: generator channel2 */
  EDMAMUX_DMAREQ_ID_REQ_G3               = 0x03, /*!< edmamux channel request inputs resources: generator channel3 */
  EDMAMUX_DMAREQ_ID_REQ_G4               = 0x04, /*!< edmamux channel request inputs resources: generator channel4 */
  EDMAMUX_DMAREQ_ID_ADC1                 = 0x05, /*!< edmamux channel request inputs resources: adc1 */
  EDMAMUX_DMAREQ_ID_ADC2                 = 0x24, /*!< edmamux channel request inputs resources: adc2 */
  EDMAMUX_DMAREQ_ID_ADC3                 = 0x25, /*!< edmamux channel request inputs resources: adc3 */
  EDMAMUX_DMAREQ_ID_DAC1                 = 0x06, /*!< edmamux channel request inputs resources: dac1 */
  EDMAMUX_DMAREQ_ID_DAC2                 = 0x29, /*!< edmamux channel request inputs resources: dac2 */
  EDMAMUX_DMAREQ_ID_TMR6_OVERFLOW        = 0x08, /*!< edmamux channel request inputs resources: timer6 overflow */
  EDMAMUX_DMAREQ_ID_TMR7_OVERFLOW        = 0x09, /*!< edmamux channel request inputs resources: timer7 overflow */
  EDMAMUX_DMAREQ_ID_SPI1_RX              = 0x0A, /*!< edmamux channel request inputs resources: spi1 rx */
  EDMAMUX_DMAREQ_ID_SPI1_TX              = 0x0B, /*!< edmamux channel request inputs resources: spi1 tx */
  EDMAMUX_DMAREQ_ID_SPI2_RX              = 0x0C, /*!< edmamux channel request inputs resources: spi2 rx */
  EDMAMUX_DMAREQ_ID_SPI2_TX              = 0x0D, /*!< edmamux channel request inputs resources: spi2 tx */
  EDMAMUX_DMAREQ_ID_SPI3_RX              = 0x0E, /*!< edmamux channel request inputs resources: spi3 rx */
  EDMAMUX_DMAREQ_ID_SPI3_TX              = 0x0F, /*!< edmamux channel request inputs resources: spi3 tx */
  EDMAMUX_DMAREQ_ID_SPI4_RX              = 0x6A, /*!< edmamux channel request inputs resources: spi4 rx */
  EDMAMUX_DMAREQ_ID_SPI4_TX              = 0x6B, /*!< edmamux channel request inputs resources: spi4 tx */
  EDMAMUX_DMAREQ_ID_I2S2_EXT_RX          = 0x6E, /*!< edmamux channel request inputs resources: i2s2_ext_rx */
  EDMAMUX_DMAREQ_ID_I2S2_EXT_TX          = 0x6F, /*!< edmamux channel request inputs resources: i2s2_ext_tx */
  EDMAMUX_DMAREQ_ID_I2S3_EXT_RX          = 0x70, /*!< edmamux channel request inputs resources: i2s3_ext_rx */
  EDMAMUX_DMAREQ_ID_I2S3_EXT_TX          = 0x71, /*!< edmamux channel request inputs resources: i2s3_ext_tx */
  EDMAMUX_DMAREQ_ID_I2C1_RX              = 0x10, /*!< edmamux channel request inputs resources: i2c1_rx */
  EDMAMUX_DMAREQ_ID_I2C1_TX              = 0x11, /*!< edmamux channel request inputs resources: i2c1_tx */
  EDMAMUX_DMAREQ_ID_I2C2_RX              = 0x12, /*!< edmamux channel request inputs resources: i2c2_rx */
  EDMAMUX_DMAREQ_ID_I2C2_TX              = 0x13, /*!< edmamux channel request inputs resources: i2c2_tx */
  EDMAMUX_DMAREQ_ID_I2C3_RX              = 0x14, /*!< edmamux channel request inputs resources: i2c3_rx */
  EDMAMUX_DMAREQ_ID_I2C3_TX              = 0x15, /*!< edmamux channel request inputs resources: i2c3_tx */
  EDMAMUX_DMAREQ_ID_USART1_RX            = 0x18, /*!< edmamux channel request inputs resources: usart1_rx */
  EDMAMUX_DMAREQ_ID_USART1_TX            = 0x19, /*!< edmamux channel request inputs resources: usart1_tx */
  EDMAMUX_DMAREQ_ID_USART2_RX            = 0x1A, /*!< edmamux channel request inputs resources: usart2_rx */
  EDMAMUX_DMAREQ_ID_USART2_TX            = 0x1B, /*!< edmamux channel request inputs resources: usart2_tx */
  EDMAMUX_DMAREQ_ID_USART3_RX            = 0x1C, /*!< edmamux channel request inputs resources: usart3_rx */
  EDMAMUX_DMAREQ_ID_USART3_TX            = 0x1D, /*!< edmamux channel request inputs resources: usart3_tx */
  EDMAMUX_DMAREQ_ID_UART4_RX             = 0x1E, /*!< edmamux channel request inputs resources: uart4_rx */
  EDMAMUX_DMAREQ_ID_UART4_TX             = 0x1F, /*!< edmamux channel request inputs resources: uart4_tx */
  EDMAMUX_DMAREQ_ID_UART5_RX             = 0x20, /*!< edmamux channel request inputs resources: uart5_rx */
  EDMAMUX_DMAREQ_ID_UART5_TX             = 0x21, /*!< edmamux channel request inputs resources: uart5_tx */
  EDMAMUX_DMAREQ_ID_USART6_RX            = 0x72, /*!< edmamux channel request inputs resources: usart6_rx */
  EDMAMUX_DMAREQ_ID_USART6_TX            = 0x73, /*!< edmamux channel request inputs resources: usart6_tx */
  EDMAMUX_DMAREQ_ID_UART7_RX             = 0x74, /*!< edmamux channel request inputs resources: uart7_rx */
  EDMAMUX_DMAREQ_ID_UART7_TX             = 0x75, /*!< edmamux channel request inputs resources: uart7_tx */
  EDMAMUX_DMAREQ_ID_UART8_RX             = 0x76, /*!< edmamux channel request inputs resources: uart8_rx */
  EDMAMUX_DMAREQ_ID_UART8_TX             = 0x77, /*!< edmamux channel request inputs resources: uart8_tx */
  EDMAMUX_DMAREQ_ID_SDIO1                = 0x27, /*!< edmamux channel request inputs resources: sdio1 */
  EDMAMUX_DMAREQ_ID_SDIO2                = 0x67, /*!< edmamux channel request inputs resources: sdio2 */
  EDMAMUX_DMAREQ_ID_QSPI1                = 0x28, /*!< edmamux channel request inputs resources: qspi1 */
  EDMAMUX_DMAREQ_ID_QSPI2                = 0x68, /*!< edmamux channel request inputs resources: qspi2 */
  EDMAMUX_DMAREQ_ID_TMR1_CH1             = 0x2A, /*!< edmamux channel request inputs resources: timer1 ch1 */
  EDMAMUX_DMAREQ_ID_TMR1_CH2             = 0x2B, /*!< edmamux channel request inputs resources: timer1 ch2 */
  EDMAMUX_DMAREQ_ID_TMR1_CH3             = 0x2C, /*!< edmamux channel request inputs resources: timer1 ch3 */
  EDMAMUX_DMAREQ_ID_TMR1_CH4             = 0x2D, /*!< edmamux channel request inputs resources: timer1 ch4 */
  EDMAMUX_DMAREQ_ID_TMR1_OVERFLOW        = 0x2E, /*!< edmamux channel request inputs resources: timer1 overflow */
  EDMAMUX_DMAREQ_ID_TMR1_TRIG            = 0x2F, /*!< edmamux channel request inputs resources: timer1 trigger */
  EDMAMUX_DMAREQ_ID_TMR1_HALL            = 0x30, /*!< edmamux channel request inputs resources: timer1 hall */
  EDMAMUX_DMAREQ_ID_TMR8_CH1             = 0x31, /*!< edmamux channel request inputs resources: timer8 ch1 */
  EDMAMUX_DMAREQ_ID_TMR8_CH2             = 0x32, /*!< edmamux channel request inputs resources: timer8 ch2 */
  EDMAMUX_DMAREQ_ID_TMR8_CH3             = 0x33, /*!< edmamux channel request inputs resources: timer8 ch3 */
  EDMAMUX_DMAREQ_ID_TMR8_CH4             = 0x34, /*!< edmamux channel request inputs resources: timer8 ch4 */
  EDMAMUX_DMAREQ_ID_TMR8_OVERFLOW        = 0x35, /*!< edmamux channel request inputs resources: timer8 overflow */
  EDMAMUX_DMAREQ_ID_TMR8_TRIG            = 0x36, /*!< edmamux channel request inputs resources: timer8 trigger */
  EDMAMUX_DMAREQ_ID_TMR8_HALL            = 0x37, /*!< edmamux channel request inputs resources: timer8 hall */
  EDMAMUX_DMAREQ_ID_TMR2_CH1             = 0x38, /*!< edmamux channel request inputs resources: timer2 ch1 */
  EDMAMUX_DMAREQ_ID_TMR2_CH2             = 0x39, /*!< edmamux channel request inputs resources: timer2 ch2 */
  EDMAMUX_DMAREQ_ID_TMR2_CH3             = 0x3A, /*!< edmamux channel request inputs resources: timer2 ch3 */
  EDMAMUX_DMAREQ_ID_TMR2_CH4             = 0x3B, /*!< edmamux channel request inputs resources: timer2 ch4 */
  EDMAMUX_DMAREQ_ID_TMR2_OVERFLOW        = 0x3C, /*!< edmamux channel request inputs resources: timer2 overflow */
  EDMAMUX_DMAREQ_ID_TMR2_TRIG            = 0x7E, /*!< edmamux channel request inputs resources: timer2 trigger */
  EDMAMUX_DMAREQ_ID_TMR3_CH1             = 0x3D, /*!< edmamux channel request inputs resources: timer3 ch1 */
  EDMAMUX_DMAREQ_ID_TMR3_CH2             = 0x3E, /*!< edmamux channel request inputs resources: timer3 ch2 */
  EDMAMUX_DMAREQ_ID_TMR3_CH3             = 0x3F, /*!< edmamux channel request inputs resources: timer3 ch3 */
  EDMAMUX_DMAREQ_ID_TMR3_CH4             = 0x40, /*!< edmamux channel request inputs resources: timer3 ch4 */
  EDMAMUX_DMAREQ_ID_TMR3_OVERFLOW        = 0x41, /*!< edmamux channel request inputs resources: timer3 overflow */
  EDMAMUX_DMAREQ_ID_TMR3_TRIG            = 0x42, /*!< edmamux channel request inputs resources: timer3 trigger */
  EDMAMUX_DMAREQ_ID_TMR4_CH1             = 0x43, /*!< edmamux channel request inputs resources: timer4 ch1 */
  EDMAMUX_DMAREQ_ID_TMR4_CH2             = 0x44, /*!< edmamux channel request inputs resources: timer4 ch2 */
  EDMAMUX_DMAREQ_ID_TMR4_CH3             = 0x45, /*!< edmamux channel request inputs resources: timer4 ch3 */
  EDMAMUX_DMAREQ_ID_TMR4_CH4             = 0x46, /*!< edmamux channel request inputs resources: timer4 ch4 */
  EDMAMUX_DMAREQ_ID_TMR4_OVERFLOW        = 0x47, /*!< edmamux channel request inputs resources: timer4 overflow */
  EDMAMUX_DMAREQ_ID_TMR4_TRIG            = 0x7F, /*!< edmamux channel request inputs resources: timer4 trigger */
  EDMAMUX_DMAREQ_ID_TMR5_CH1             = 0x48, /*!< edmamux channel request inputs resources: timer5 ch1 */
  EDMAMUX_DMAREQ_ID_TMR5_CH2             = 0x49, /*!< edmamux channel request inputs resources: timer5 ch2 */
  EDMAMUX_DMAREQ_ID_TMR5_CH3             = 0x4A, /*!< edmamux channel request inputs resources: timer5 ch3 */
  EDMAMUX_DMAREQ_ID_TMR5_CH4             = 0x4B, /*!< edmamux channel request inputs resources: timer5 ch4 */
  EDMAMUX_DMAREQ_ID_TMR5_OVERFLOW        = 0x4C, /*!< edmamux channel request inputs resources: timer5 overflow */
  EDMAMUX_DMAREQ_ID_TMR5_TRIG            = 0x4D, /*!< edmamux channel request inputs resources: timer5 trigger */
  EDMAMUX_DMAREQ_ID_TMR20_CH1            = 0x56, /*!< edmamux channel request inputs resources: timer20 ch1 */
  EDMAMUX_DMAREQ_ID_TMR20_CH2            = 0x57, /*!< edmamux channel request inputs resources: timer20 ch2 */
  EDMAMUX_DMAREQ_ID_TMR20_CH3            = 0x58, /*!< edmamux channel request inputs resources: timer20 ch3 */
  EDMAMUX_DMAREQ_ID_TMR20_CH4            = 0x59, /*!< edmamux channel request inputs resources: timer20 ch4 */
  EDMAMUX_DMAREQ_ID_TMR20_OVERFLOW       = 0x5A, /*!< edmamux channel request inputs resources: timer20 overflow */
  EDMAMUX_DMAREQ_ID_TMR20_TRIG           = 0x5D, /*!< edmamux channel request inputs resources: timer20 trigger */
  EDMAMUX_DMAREQ_ID_TMR20_HALL           = 0x5E, /*!< edmamux channel request inputs resources: timer20 hall */
  EDMAMUX_DMAREQ_ID_DVP                  = 0x69  /*!< edmamux channel request inputs resources: dvp */
} edmamux_requst_id_sel_type;

/**
  * @brief dmamux sync id select type
  */
typedef enum
{
  EDMAMUX_SYNC_ID_EXINT0                 = 0x00, /*!< edmamux channel synchronization inputs resources: exint line0 */
  EDMAMUX_SYNC_ID_EXINT1                 = 0x01, /*!< edmamux channel synchronization inputs resources: exint line1 */
  EDMAMUX_SYNC_ID_EXINT2                 = 0x02, /*!< edmamux channel synchronization inputs resources: exint line2 */
  EDMAMUX_SYNC_ID_EXINT3                 = 0x03, /*!< edmamux channel synchronization inputs resources: exint line3 */
  EDMAMUX_SYNC_ID_EXINT4                 = 0x04, /*!< edmamux channel synchronization inputs resources: exint line4 */
  EDMAMUX_SYNC_ID_EXINT5                 = 0x05, /*!< edmamux channel synchronization inputs resources: exint line5 */
  EDMAMUX_SYNC_ID_EXINT6                 = 0x06, /*!< edmamux channel synchronization inputs resources: exint line6 */
  EDMAMUX_SYNC_ID_EXINT7                 = 0x07, /*!< edmamux channel synchronization inputs resources: exint line7 */
  EDMAMUX_SYNC_ID_EXINT8                 = 0x08, /*!< edmamux channel synchronization inputs resources: exint line8 */
  EDMAMUX_SYNC_ID_EXINT9                 = 0x09, /*!< edmamux channel synchronization inputs resources: exint line9 */
  EDMAMUX_SYNC_ID_EXINT10                = 0x0A, /*!< edmamux channel synchronization inputs resources: exint line10 */
  EDMAMUX_SYNC_ID_EXINT11                = 0x0B, /*!< edmamux channel synchronization inputs resources: exint line11 */
  EDMAMUX_SYNC_ID_EXINT12                = 0x0C, /*!< edmamux channel synchronization inputs resources: exint line12 */
  EDMAMUX_SYNC_ID_EXINT13                = 0x0D, /*!< edmamux channel synchronization inputs resources: exint line13 */
  EDMAMUX_SYNC_ID_EXINT14                = 0x0E, /*!< edmamux channel synchronization inputs resources: exint line14 */
  EDMAMUX_SYNC_ID_EXINT15                = 0x0F, /*!< edmamux channel synchronization inputs resources: exint line15 */
  EDMAMUX_SYNC_ID_DMAMUX_CH1_EVT         = 0x10, /*!< edmamux channel synchronization inputs resources: dmamux channel1 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH2_EVT         = 0x11, /*!< edmamux channel synchronization inputs resources: dmamux channel2 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH3_EVT         = 0x12, /*!< edmamux channel synchronization inputs resources: dmamux channel3 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH4_EVT         = 0x13, /*!< edmamux channel synchronization inputs resources: dmamux channel4 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH5_EVT         = 0x14, /*!< edmamux channel synchronization inputs resources: dmamux channel5 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH6_EVT         = 0x15, /*!< edmamux channel synchronization inputs resources: dmamux channel6 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH7_EVT         = 0x16, /*!< edmamux channel synchronization inputs resources: dmamux channel7 event */
  EDMAMUX_SYNC_ID_DMAMUX_CH8_EVT         = 0x17  /*!< edmamux channel synchronization inputs resources: dmamux channel8 event */
} edmamux_sync_id_sel_type;

/**
  * @brief dmamux sync polarity type
  */
typedef enum
{
  EDMAMUX_SYNC_POLARITY_DISABLE          = 0x00, /*!< edmamux channel synchronization inputs resources polarity default value */
  EDMAMUX_SYNC_POLARITY_RISING           = 0x01, /*!< edmamux channel synchronization inputs resources polarity: rising */
  EDMAMUX_SYNC_POLARITY_FALLING          = 0x02, /*!< edmamux channel synchronization inputs resources polarity: falling */
  EDMAMUX_SYNC_POLARITY_RISING_FALLING   = 0x03  /*!< edmamux channel synchronization inputs resources polarity: rising_falling */
} edmamux_sync_pol_type;

/**
  * @brief dmamux generator id select type
  */
typedef enum
{
  EDMAMUX_GEN_ID_EXINT0                  = 0x00, /*!< edmamux generator channel inputs resources: exint line0 */
  EDMAMUX_GEN_ID_EXINT1                  = 0x01, /*!< edmamux generator channel inputs resources: exint line1 */
  EDMAMUX_GEN_ID_EXINT2                  = 0x02, /*!< edmamux generator channel inputs resources: exint line2 */
  EDMAMUX_GEN_ID_EXINT3                  = 0x03, /*!< edmamux generator channel inputs resources: exint line3 */
  EDMAMUX_GEN_ID_EXINT4                  = 0x04, /*!< edmamux generator channel inputs resources: exint line4 */
  EDMAMUX_GEN_ID_EXINT5                  = 0x05, /*!< edmamux generator channel inputs resources: exint line5 */
  EDMAMUX_GEN_ID_EXINT6                  = 0x06, /*!< edmamux generator channel inputs resources: exint line6 */
  EDMAMUX_GEN_ID_EXINT7                  = 0x07, /*!< edmamux generator channel inputs resources: exint line7 */
  EDMAMUX_GEN_ID_EXINT8                  = 0x08, /*!< edmamux generator channel inputs resources: exint line8 */
  EDMAMUX_GEN_ID_EXINT9                  = 0x09, /*!< edmamux generator channel inputs resources: exint line9 */
  EDMAMUX_GEN_ID_EXINT10                 = 0x0A, /*!< edmamux generator channel inputs resources: exint line10 */
  EDMAMUX_GEN_ID_EXINT11                 = 0x0B, /*!< edmamux generator channel inputs resources: exint line11 */
  EDMAMUX_GEN_ID_EXINT12                 = 0x0C, /*!< edmamux generator channel inputs resources: exint line12 */
  EDMAMUX_GEN_ID_EXINT13                 = 0x0D, /*!< edmamux generator channel inputs resources: exint line13 */
  EDMAMUX_GEN_ID_EXINT14                 = 0x0E, /*!< edmamux generator channel inputs resources: exint line14 */
  EDMAMUX_GEN_ID_EXINT15                 = 0x0F, /*!< edmamux generator channel inputs resources: exint line15 */
  EDMAMUX_GEN_ID_DMAMUX_CH1_EVT          = 0x10, /*!< edmamux generator channel inputs resources: dmamux channel1 event */
  EDMAMUX_GEN_ID_DMAMUX_CH2_EVT          = 0x11, /*!< edmamux generator channel inputs resources: dmamux channel2 event */
  EDMAMUX_GEN_ID_DMAMUX_CH3_EVT          = 0x12, /*!< edmamux generator channel inputs resources: dmamux channel3 event */
  EDMAMUX_GEN_ID_DMAMUX_CH4_EVT          = 0x13, /*!< edmamux generator channel inputs resources: dmamux channel4 event */
  EDMAMUX_GEN_ID_DMAMUX_CH5_EVT          = 0x14, /*!< edmamux generator channel inputs resources: dmamux channel5 event */
  EDMAMUX_GEN_ID_DMAMUX_CH6_EVT          = 0x15, /*!< edmamux generator channel inputs resources: dmamux channel6 event */
  EDMAMUX_GEN_ID_DMAMUX_CH7_EVT          = 0x16, /*!< edmamux generator channel inputs resources: dmamux channel7 event */
  EDMAMUX_GEN_ID_DMAMUX_CH8_EVT          = 0x17  /*!< edmamux generator channel inputs resources: dmamux channel8 event */
} edmamux_gen_id_sel_type;

/**
  * @brief dmamux generator polarity type
  */
typedef enum
{
  EDMAMUX_GEN_POLARITY_DISABLE           = 0x00, /*!< edmamux generator channel inputs resources polarity default value */
  EDMAMUX_GEN_POLARITY_RISING            = 0x01, /*!< edmamux generator channel inputs resources polarity: rising */
  EDMAMUX_GEN_POLARITY_FALLING           = 0x02, /*!< edmamux generator channel inputs resources polarity: falling */
  EDMAMUX_GEN_POLARITY_RISING_FALLING    = 0x03  /*!< edmamux generator channel inputs resources polarity: rising_falling */
} edmamux_gen_pol_type;

/**
  * @brief edma init type
  */
typedef struct
{
  uint32_t                               peripheral_base_addr;       /*!< base addrress for peripheral */
  uint32_t                               memory0_base_addr;          /*!< base addrress for memory 0 */
  edma_dir_type                          direction;                  /*!< edma transmit direction, peripheral as source or as destnation  */
  uint16_t                               buffer_size;                /*!< counter to transfer (0~0xFFFF)*/
  confirm_state                          peripheral_inc_enable;      /*!< periphera address increment after one transmit */
  confirm_state                          memory_inc_enable;          /*!< memory address increment after one transmit */
  edma_peripheral_data_size_type         peripheral_data_width;      /*!< peripheral data width for transmit */
  edma_memory_data_size_type             memory_data_width;          /*!< memory data width for transmit */
  confirm_state                          loop_mode_enable;           /*!< when loop mode enable, buffer size will reload if count to 0*/
  edma_priority_level_type               priority;                   /*!< edma priority can choose from very high, high, dedium or low */
  confirm_state                          fifo_mode_enable;           /*!< edma fifo mode enable */
  edma_fifo_threshold_type               fifo_threshold;             /*!< edma fifo threshold vaule */
  edma_memory_burst_type                 memory_burst_mode;          /*!< edma memory burst transfer */
  edma_peripheral_burst_type             peripheral_burst_mode;      /*!< edma peripheral burst transfer */
} edma_init_type;

/**
  * @brief edmamux sync init type
  */
typedef struct
{
  edmamux_sync_id_sel_type               sync_signal_sel;     /*!< edma dmamux synchronization input select */
  edmamux_sync_pol_type                  sync_polarity;       /*!< edma dmamux synchronization polarity */
  uint32_t                               sync_request_number; /*!< edma dmamux number of dma requests before an output event is generated */
  confirm_state                          sync_event_enable;   /*!< edma dmamux event generation disabled */
  confirm_state                          sync_enable;         /*!< edma dmamux synchronization enable */
} edmamux_sync_init_type;

/**
  * @brief edmamux generator init type
  */
typedef struct
{
  edmamux_gen_id_sel_type                gen_signal_sel;     /*!< edma dmamux generator dma request trigger input select */
  edmamux_gen_pol_type                   gen_polarity;       /*!< edma dmamux generator trigger polarity */
  uint32_t                               gen_request_number; /*!< edma dmamux the number of dma requests to be generated after a trigger event */
  confirm_state                          gen_enable;         /*!< edma dmamux generator enable */
} edmamux_gen_init_type;

/**
  * @brief type define edma register all
  */
typedef struct
{
  /**
    * @brief edma sts1 register, offset:0x00
    */
  union
  {
    __IO uint32_t sts1;
    struct
    {
      __IO uint32_t ferrf1               : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t dmerrf1              : 1; /* [2] */
      __IO uint32_t dterrf1              : 1; /* [3] */
      __IO uint32_t hdtf1                : 1; /* [4] */
      __IO uint32_t fdtf1                : 1; /* [5] */
      __IO uint32_t ferrf2               : 1; /* [6] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t dmerrf2              : 1; /* [8] */
      __IO uint32_t dterrf2              : 1; /* [9] */
      __IO uint32_t hdtf2                : 1; /* [10] */
      __IO uint32_t fdtf2                : 1; /* [11] */
      __IO uint32_t reserved3            : 4; /* [15:13] */
      __IO uint32_t ferrf3               : 1; /* [16] */
      __IO uint32_t reserved4            : 1; /* [17] */
      __IO uint32_t dmerrf3              : 1; /* [18] */
      __IO uint32_t dterrf3              : 1; /* [19] */
      __IO uint32_t hdtf3                : 1; /* [20] */
      __IO uint32_t fdtf3                : 1; /* [21] */
      __IO uint32_t ferrf4               : 1; /* [22] */
      __IO uint32_t reserved5            : 1; /* [23] */
      __IO uint32_t dmerrf4              : 1; /* [24] */
      __IO uint32_t dterrf4              : 1; /* [25] */
      __IO uint32_t hdtf4                : 1; /* [26] */
      __IO uint32_t fdtf4                : 1; /* [27] */
      __IO uint32_t reserved6            : 4; /* [31:28] */
    } sts1_bit;
  };
  /**
    * @brief edma sts2 register, offset:0x04
    */
  union
  {
    __IO uint32_t sts2;
    struct
    {
      __IO uint32_t ferrf5               : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t dmerrf5              : 1; /* [2] */
      __IO uint32_t dterrf5              : 1; /* [3] */
      __IO uint32_t hdtf5                : 1; /* [4] */
      __IO uint32_t fdtf5                : 1; /* [5] */
      __IO uint32_t ferrf6               : 1; /* [6] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t dmerrf6              : 1; /* [8] */
      __IO uint32_t dterrf6              : 1; /* [9] */
      __IO uint32_t hdtf6                : 1; /* [10] */
      __IO uint32_t fdtf6                : 1; /* [11] */
      __IO uint32_t reserved3            : 4; /* [15:13] */
      __IO uint32_t ferrf7               : 1; /* [16] */
      __IO uint32_t reserved4            : 1; /* [17] */
      __IO uint32_t dmerrf7              : 1; /* [18] */
      __IO uint32_t dterrf7              : 1; /* [19] */
      __IO uint32_t hdtf7                : 1; /* [20] */
      __IO uint32_t fdtf7                : 1; /* [21] */
      __IO uint32_t ferrf8               : 1; /* [22] */
      __IO uint32_t reserved5            : 1; /* [23] */
      __IO uint32_t dmerrf8              : 1; /* [24] */
      __IO uint32_t dterrf8              : 1; /* [25] */
      __IO uint32_t hdtf8                : 1; /* [26] */
      __IO uint32_t fdtf8                : 1; /* [27] */
      __IO uint32_t reserved6            : 4; /* [31:28] */
    } sts2_bit;
  };
  /**
    * @brief edma clr1 register, offset:0x08
    */
  union
  {
    __IO uint32_t clr1;
    struct
    {
      __IO uint32_t ferrfc1              : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t dmerrfc1             : 1; /* [2] */
      __IO uint32_t dterrfc1             : 1; /* [3] */
      __IO uint32_t hdtfc1               : 1; /* [4] */
      __IO uint32_t fdtfc1               : 1; /* [5] */
      __IO uint32_t ferrfc2              : 1; /* [6] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t dmerrfc2             : 1; /* [8] */
      __IO uint32_t dterrfc2             : 1; /* [9] */
      __IO uint32_t hdtfc2               : 1; /* [10] */
      __IO uint32_t fdtfc2               : 1; /* [11] */
      __IO uint32_t reserved3            : 4; /* [15:13] */
      __IO uint32_t ferrfc3              : 1; /* [16] */
      __IO uint32_t reserved4            : 1; /* [17] */
      __IO uint32_t dmerrfc3             : 1; /* [18] */
      __IO uint32_t dterrfc3             : 1; /* [19] */
      __IO uint32_t hdtfc3               : 1; /* [20] */
      __IO uint32_t fdtfc3               : 1; /* [21] */
      __IO uint32_t ferrfc4              : 1; /* [22] */
      __IO uint32_t reserved5            : 1; /* [23] */
      __IO uint32_t dmerrfc4             : 1; /* [24] */
      __IO uint32_t dterrfc4             : 1; /* [25] */
      __IO uint32_t hdtfc4               : 1; /* [26] */
      __IO uint32_t fdtfc4               : 1; /* [27] */
      __IO uint32_t reserved6            : 4; /* [31:28] */
    } clr1_bit;
  };
  /**
    * @brief edma clr2 register, offset:0x0C
    */
  union
  {
    __IO uint32_t clr2;
    struct
    {
      __IO uint32_t ferrfc5              : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t dmerrfc5             : 1; /* [2] */
      __IO uint32_t dterrfc5             : 1; /* [3] */
      __IO uint32_t hdtfc5               : 1; /* [4] */
      __IO uint32_t fdtfc5               : 1; /* [5] */
      __IO uint32_t ferrfc6              : 1; /* [6] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t dmerrfc6             : 1; /* [8] */
      __IO uint32_t dterrfc6             : 1; /* [9] */
      __IO uint32_t hdtfc6               : 1; /* [10] */
      __IO uint32_t fdtfc6               : 1; /* [11] */
      __IO uint32_t reserved3            : 4; /* [15:13] */
      __IO uint32_t ferrfc7              : 1; /* [16] */
      __IO uint32_t reserved4            : 1; /* [17] */
      __IO uint32_t dmerrfc7             : 1; /* [18] */
      __IO uint32_t dterrfc7             : 1; /* [19] */
      __IO uint32_t hdtfc7               : 1; /* [20] */
      __IO uint32_t fdtfc7               : 1; /* [21] */
      __IO uint32_t ferrfc8              : 1; /* [22] */
      __IO uint32_t reserved5            : 1; /* [23] */
      __IO uint32_t dmerrfc8             : 1; /* [24] */
      __IO uint32_t dterrfc8             : 1; /* [25] */
      __IO uint32_t hdtfc8               : 1; /* [26] */
      __IO uint32_t fdtfc8               : 1; /* [27] */
      __IO uint32_t reserved6            : 4; /* [31:28] */
    } clr2_bit;
  };

  /**
    * @brief reserved, offset:0x10~0xCC
    */
  __IO uint32_t reserved1[48];

  /**
    * @brief edma link list ctrl register, offset:0xD0
    */
  union
  {
    __IO uint32_t llctrl;
    struct
    {
      __IO uint32_t s1llen               : 1; /* [0] */
      __IO uint32_t s2llen               : 1; /* [1] */
      __IO uint32_t s3llen               : 1; /* [2] */
      __IO uint32_t s4llen               : 1; /* [3] */
      __IO uint32_t s5llen               : 1; /* [4] */
      __IO uint32_t s6llen               : 1; /* [5] */
      __IO uint32_t s7llen               : 1; /* [6] */
      __IO uint32_t s8llen               : 1; /* [7] */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    } llctrl_bit;
  };

  /**
    * @brief reserved, offset:0xD4~0xF0
    */
  __IO uint32_t reserved2[8];

  /**
    * @brief edma 2d ctrl register, offset:0xF4
    */
  union
  {
    __IO uint32_t s2dctrl;
    struct
    {
      __IO uint32_t s12den               : 1; /* [0] */
      __IO uint32_t s22den               : 1; /* [1] */
      __IO uint32_t s32den               : 1; /* [2] */
      __IO uint32_t s42den               : 1; /* [3] */
      __IO uint32_t s52den               : 1; /* [4] */
      __IO uint32_t s62den               : 1; /* [5] */
      __IO uint32_t s72den               : 1; /* [6] */
      __IO uint32_t s82den               : 1; /* [7] */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    } s2dctrl_bit;
  };

  /**
    * @brief reserved, offset:0xF8~0x138
    */
  __IO uint32_t reserved3[17];

  /**
    * @brief edmamux sel register, offset:0x13C
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
    * @brief reserved, offset:0x140~0x16C
    */
  __IO uint32_t reserved4[12];

  /**
    * @brief edmamux syncsts register, offset:0x170
    */
  union
  {
    __IO uint32_t muxsyncsts;
    struct
    {
      __IO uint32_t syncovf              : 8; /* [7:0] */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    }muxsyncsts_bit;
  };

  /**
    * @brief edmamux syncclr register, offset:0x174
    */
  union
  {
    __IO uint32_t muxsyncclr;
    struct
    {
      __IO uint32_t syncovfc             : 8; /* [7:0] */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    }muxsyncclr_bit;
  };

  /**
    * @brief edmamux request generator status register, offset:0x178
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
    * @brief edmamux request generator status clear register, offset:0x17C
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

} edma_type;

/**
  * @brief type define edma stream register all
  */
typedef struct
{
  /**
    * @brief edma sxctrl register, offset:0x10+0x18*n n=1...8
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t sen                  : 1; /* [0] */
      __IO uint32_t dmerrien             : 1; /* [1] */
      __IO uint32_t dterrien             : 1; /* [2] */
      __IO uint32_t hdtien               : 1; /* [3] */
      __IO uint32_t fdtien               : 1; /* [4] */
      __IO uint32_t pfctrl               : 1; /* [5] */
      __IO uint32_t dtd                  : 2; /* [7:6] */
      __IO uint32_t lm                   : 1; /* [8] */
      __IO uint32_t pincm                : 1; /* [9] */
      __IO uint32_t mincm                : 1; /* [10] */
      __IO uint32_t pwidth               : 2; /* [12:11] */
      __IO uint32_t mwidth               : 2; /* [14:13] */
      __IO uint32_t pincos               : 1; /* [15] */
      __IO uint32_t spl                  : 2; /* [17:16] */
      __IO uint32_t dmm                  : 1; /* [18] */
      __IO uint32_t cm                   : 1; /* [19] */
      __IO uint32_t reserved1            : 1; /* [20] */
      __IO uint32_t pct                  : 2; /* [22:21] */
      __IO uint32_t mct                  : 2; /* [24:23] */
      __IO uint32_t reserved2            : 3; /* [27:25] */
      __IO uint32_t reserved3            : 4; /* [31:28] */
    } ctrl_bit;
  };
  /**
    * @brief edma dtcnt register, offset:0x14+0x18*n n=1...8
    */
  union
  {
    __IO uint32_t dtcnt;
    struct
    {
      __IO uint32_t cnt                  : 16;/* [15:0] */
      __IO uint32_t reserved1            : 16; /*[31:16] */
    } dtcnt_bit;
  };
  /**
    * @brief edma paddr register, offset:0x18+0x18*n n=1...8
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
    * @brief edma m0adr register, offset:0x1C+0x18*n n=1...8
    */
  union
  {
    __IO uint32_t m0addr;
    struct
    {
      __IO uint32_t m0addr               : 32;/* [31:0] */
    } m0addr_bit;
  };
  /**
    * @brief edma m1adr register, offset:0x20+0x18*n n=1...8
    */
  union
  {
    __IO uint32_t m1addr;
    struct
    {
      __IO uint32_t m1addr               : 32;/* [31:0] */
    } m1addr_bit;
  };
  /**
    * @brief edma fctrl register, offset:0x24+0x18*n n=1...8
    */
  union
  {
    __IO uint32_t fctrl;
    struct
    {
      __IO uint32_t fthsel               : 2; /* [1:0] */
      __IO uint32_t fen                  : 1; /* [2] */
      __IO uint32_t fsts                 : 3; /* [5:3] */
      __IO uint32_t reserved1            : 1; /* [6] */
      __IO uint32_t ferrien              : 1; /* [7] */
      __IO uint32_t reserved2            : 24;/* [31:8] */
    } fctrl_bit;
  };
} edma_stream_type;

/**
  * @brief type define edma stream link list pointer register
  */
typedef struct
{
  /**
    * @brief edma stream link list pointer register
    */
  union
  {
    __IO uint32_t llp;
    struct
    {
      __IO uint32_t llp                  : 32;/* [31:0] */
    } llp_bit;
  };
} edma_stream_link_list_type;

/**
  * @brief type define edma 2d register all
  */
typedef struct
{
  /**
    * @brief edma s2dcnt register, offset:0x00
    */
  union
  {
    __IO uint32_t s2dcnt;
    struct
    {
      __IO uint32_t xcnt                 : 16;/* [15:0] */
      __IO uint32_t ycnt                 : 16;/* [31:16] */
    } s2dcnt_bit;
  };
  /**
    * @brief edma stride register, offset:0x04
    */
  union
  {
    __IO uint32_t stride;
    struct
    {
      __IO uint32_t srcstd               : 16;/* [15:0] */
      __IO uint32_t dststd               : 16;/* [31:16] */
    } stride_bit;
  };
} edma_stream_2d_type;

/**
  * @brief type define edmamux muxsctrl register
  */
typedef struct
{
  /**
    * @brief edma muxsctrl register
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
} edmamux_channel_type;

/**
  * @brief type define edmamux request generator register all
  */
typedef struct
{
  /**
    * @brief edmamux request generator register, offset:0x160+n*4 n=1...8
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
} edmamux_generator_type;

/**
  * @}
  */

#define EDMA                             ((edma_type *) EDMA_BASE)
#define EDMA_STREAM1                     ((edma_stream_type *) EDMA_STREAM1_BASE)
#define EDMA_STREAM2                     ((edma_stream_type *) EDMA_STREAM2_BASE)
#define EDMA_STREAM3                     ((edma_stream_type *) EDMA_STREAM3_BASE)
#define EDMA_STREAM4                     ((edma_stream_type *) EDMA_STREAM4_BASE)
#define EDMA_STREAM5                     ((edma_stream_type *) EDMA_STREAM5_BASE)
#define EDMA_STREAM6                     ((edma_stream_type *) EDMA_STREAM6_BASE)
#define EDMA_STREAM7                     ((edma_stream_type *) EDMA_STREAM7_BASE)
#define EDMA_STREAM8                     ((edma_stream_type *) EDMA_STREAM8_BASE)

#define EDMA_STREAM1_2D                  ((edma_stream_2d_type *) EDMA_STREAM1_2D_BASE)
#define EDMA_STREAM2_2D                  ((edma_stream_2d_type *) EDMA_STREAM2_2D_BASE)
#define EDMA_STREAM3_2D                  ((edma_stream_2d_type *) EDMA_STREAM3_2D_BASE)
#define EDMA_STREAM4_2D                  ((edma_stream_2d_type *) EDMA_STREAM4_2D_BASE)
#define EDMA_STREAM5_2D                  ((edma_stream_2d_type *) EDMA_STREAM5_2D_BASE)
#define EDMA_STREAM6_2D                  ((edma_stream_2d_type *) EDMA_STREAM6_2D_BASE)
#define EDMA_STREAM7_2D                  ((edma_stream_2d_type *) EDMA_STREAM7_2D_BASE)
#define EDMA_STREAM8_2D                  ((edma_stream_2d_type *) EDMA_STREAM8_2D_BASE)

#define EDMA_STREAM1_LL                  ((edma_stream_link_list_type *) EDMA_STREAM1_LL_BASE)
#define EDMA_STREAM2_LL                  ((edma_stream_link_list_type *) EDMA_STREAM2_LL_BASE)
#define EDMA_STREAM3_LL                  ((edma_stream_link_list_type *) EDMA_STREAM3_LL_BASE)
#define EDMA_STREAM4_LL                  ((edma_stream_link_list_type *) EDMA_STREAM4_LL_BASE)
#define EDMA_STREAM5_LL                  ((edma_stream_link_list_type *) EDMA_STREAM5_LL_BASE)
#define EDMA_STREAM6_LL                  ((edma_stream_link_list_type *) EDMA_STREAM6_LL_BASE)
#define EDMA_STREAM7_LL                  ((edma_stream_link_list_type *) EDMA_STREAM7_LL_BASE)
#define EDMA_STREAM8_LL                  ((edma_stream_link_list_type *) EDMA_STREAM8_LL_BASE)

#define EDMAMUX_CHANNEL1                 ((edmamux_channel_type *) EDMAMUX_CHANNEL1_BASE)
#define EDMAMUX_CHANNEL2                 ((edmamux_channel_type *) EDMAMUX_CHANNEL2_BASE)
#define EDMAMUX_CHANNEL3                 ((edmamux_channel_type *) EDMAMUX_CHANNEL3_BASE)
#define EDMAMUX_CHANNEL4                 ((edmamux_channel_type *) EDMAMUX_CHANNEL4_BASE)
#define EDMAMUX_CHANNEL5                 ((edmamux_channel_type *) EDMAMUX_CHANNEL5_BASE)
#define EDMAMUX_CHANNEL6                 ((edmamux_channel_type *) EDMAMUX_CHANNEL6_BASE)
#define EDMAMUX_CHANNEL7                 ((edmamux_channel_type *) EDMAMUX_CHANNEL7_BASE)
#define EDMAMUX_CHANNEL8                 ((edmamux_channel_type *) EDMAMUX_CHANNEL8_BASE)

#define EDMAMUX_GENERATOR1               ((edmamux_generator_type *) EDMAMUX_GENERATOR1_BASE)
#define EDMAMUX_GENERATOR2               ((edmamux_generator_type *) EDMAMUX_GENERATOR2_BASE)
#define EDMAMUX_GENERATOR3               ((edmamux_generator_type *) EDMAMUX_GENERATOR3_BASE)
#define EDMAMUX_GENERATOR4               ((edmamux_generator_type *) EDMAMUX_GENERATOR4_BASE)

/** @defgroup EDMA_exported_functions
  * @{
  */

/* edma controller function */
void edma_reset(edma_stream_type *edma_streamx);
void edma_init(edma_stream_type *edma_streamx, edma_init_type *edma_init_struct);
void edma_default_para_init(edma_init_type *edma_init_struct);
void edma_stream_enable(edma_stream_type *edma_streamx, confirm_state new_state);
void edma_interrupt_enable(edma_stream_type *edma_streamx, uint32_t edma_int, confirm_state new_state);
void edma_peripheral_inc_offset_set(edma_stream_type *edma_streamx, edma_peripheral_inc_offset_type offset);
void edma_flow_controller_enable(edma_stream_type *edma_streamx, confirm_state new_state);
void edma_data_number_set(edma_stream_type *edma_streamx, uint16_t data_number);
uint16_t edma_data_number_get(edma_stream_type *edma_streamx);
void edma_double_buffer_mode_init(edma_stream_type *edma_streamx, uint32_t memory1_addr, edma_memory_type current_memory);
void edma_double_buffer_mode_enable(edma_stream_type *edma_streamx, confirm_state new_state);
void edma_memory_addr_set(edma_stream_type *edma_streamx, uint32_t memory_addr, uint32_t memory_target);
edma_memory_type edma_memory_target_get(edma_stream_type *edma_streamx);
flag_status edma_stream_status_get(edma_stream_type *edma_streamx);
uint8_t edma_fifo_status_get(edma_stream_type *edma_streamx);
flag_status edma_flag_get(uint32_t edma_flag);
flag_status edma_interrupt_flag_get(uint32_t edma_flag);
void edma_flag_clear(uint32_t edma_flag);

/* edma 2d controller function */
void edma_2d_init(edma_stream_2d_type *edma_streamx_2d, int16_t src_stride, int16_t dst_stride, uint16_t xcnt, uint16_t ycnt);
void edma_2d_enable(edma_stream_2d_type *edma_streamx_2d, confirm_state new_state);

/* dma link list controller function */
void edma_link_list_init(edma_stream_link_list_type *edma_streamx_ll, uint32_t pointer);
void edma_link_list_enable(edma_stream_link_list_type *edma_streamx_ll, confirm_state new_state);

/* edma requst multiplexer function */
void edmamux_enable(confirm_state new_state);
void edmamux_init(edmamux_channel_type *edmamux_channelx, edmamux_requst_id_sel_type edmamux_req_id);
void edmamux_sync_default_para_init(edmamux_sync_init_type *edmamux_sync_init_struct);
void edmamux_sync_config(edmamux_channel_type *edmamux_channelx, edmamux_sync_init_type *edmamux_sync_init_struct);
void edmamux_generator_default_para_init(edmamux_gen_init_type *edmamux_gen_init_struct);
void edmamux_generator_config(edmamux_generator_type *edmamux_gen_x, edmamux_gen_init_type *edmamux_gen_init_struct);
void edmamux_sync_interrupt_enable(edmamux_channel_type *edmamux_channelx, confirm_state new_state);
void edmamux_generator_interrupt_enable(edmamux_generator_type *edmamux_gen_x, confirm_state new_state);
flag_status edmamux_sync_flag_get(uint32_t flag);
flag_status edmamux_sync_interrupt_flag_get(uint32_t flag);
void edmamux_sync_flag_clear(uint32_t flag);
flag_status edmamux_generator_flag_get(uint32_t flag);
flag_status edmamux_generator_interrupt_flag_get(uint32_t flag);
void edmamux_generator_flag_clear(uint32_t flag);

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
