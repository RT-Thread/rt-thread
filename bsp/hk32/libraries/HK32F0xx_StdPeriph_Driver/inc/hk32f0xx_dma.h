/**
  ******************************************************************************
  * @file    hk32f0xx_dma.h 
  * @version V1.0.1
  * @date    2019-08-15 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XX_DMA_H
#define __HK32F0XX_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f0xx.h"

/** @addtogroup HK32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  DMA Init structures definition
  */
typedef struct
{
  uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx.              */

  uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx.                  */

  uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction     */

  uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction     */

  uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

  uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode     */

  uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size        */

  uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size            */

  uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

  uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level              */

  uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory            */
}DMA_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants
  * @{
  */

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5) || \
                                   ((PERIPH) == DMA1_Channel6) || \
                                   ((PERIPH) == DMA1_Channel7) || \
                                   ((PERIPH) == DMA2_Channel1) || \
                                   ((PERIPH) == DMA2_Channel2) || \
                                   ((PERIPH) == DMA2_Channel3) || \
                                   ((PERIPH) == DMA2_Channel4) || \
                                   ((PERIPH) == DMA2_Channel5))

/** @defgroup DMA_data_transfer_direction 
  * @{
  */

#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)
#define DMA_DIR_PeripheralDST              DMA_CCR_DIR

#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralSRC) || \
                         ((DIR) == DMA_DIR_PeripheralDST))
/**
  * @}
  */

/** @defgroup DMA_peripheral_incremented_mode 
  * @{
  */

#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)
#define DMA_PeripheralInc_Enable           DMA_CCR_PINC

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Disable) || \
                                            ((STATE) == DMA_PeripheralInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_memory_incremented_mode 
  * @{
  */

#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)
#define DMA_MemoryInc_Enable               DMA_CCR_MINC

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Disable) || \
                                        ((STATE) == DMA_MemoryInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_peripheral_data_size 
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    DMA_CCR_PSIZE_0
#define DMA_PeripheralDataSize_Word        DMA_CCR_PSIZE_1

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_memory_data_size 
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        DMA_CCR_MSIZE_0
#define DMA_MemoryDataSize_Word            DMA_CCR_MSIZE_1

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_circular_normal_mode 
  * @{
  */

#define DMA_Mode_Normal                    ((uint32_t)0x00000000)
#define DMA_Mode_Circular                  DMA_CCR_CIRC

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal) || ((MODE) == DMA_Mode_Circular))
/**
  * @}
  */

/** @defgroup DMA_priority_level 
  * @{
  */

#define DMA_Priority_VeryHigh              DMA_CCR_PL
#define DMA_Priority_High                  DMA_CCR_PL_1
#define DMA_Priority_Medium                DMA_CCR_PL_0
#define DMA_Priority_Low                   ((uint32_t)0x00000000)

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))
/**
  * @}
  */

/** @defgroup DMA_memory_to_memory 
  * @{
  */

#define DMA_M2M_Disable                    ((uint32_t)0x00000000)
#define DMA_M2M_Enable                     DMA_CCR_MEM2MEM

#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Disable) || ((STATE) == DMA_M2M_Enable))

/**
  * @}
  */

/** @defgroup DMA_Remap_Config 
  * @{
  */ 
#define DMAx_CHANNEL1_RMP                                     0x00000000
#define DMAx_CHANNEL2_RMP                                     0x10000000
#define DMAx_CHANNEL3_RMP                                     0x20000000
#define DMAx_CHANNEL4_RMP                                     0x30000000
#define DMAx_CHANNEL5_RMP                                     0x40000000
#define DMAx_CHANNEL6_RMP                                     0x50000000
#define DMAx_CHANNEL7_RMP                                     0x60000000


#define IS_DMA_ALL_LIST(LIST) (((LIST) == DMA1) || \
                               ((LIST) == DMA2))

/****************** DMA1 remap bit field definition********************/
/* DMA1 - Channel 1 */
#define DMA1_CH1_DEFAULT      (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH1_ADC          (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_ADC)       /*!< Remap ADC on DMA1 Channel 1*/   
#define DMA1_CH1_TIM17_CH1    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 1 */
#define DMA1_CH1_TIM17_UP     (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 1 */ 
#define DMA1_CH1_USART1_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART2_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART3_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART4_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART5_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART6_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART7_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART8_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 1 */ 
/* DMA1 - Channel 2 */
#define DMA1_CH2_DEFAULT      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH2_ADC          (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_ADC)       /*!< Remap ADC on DMA1 channel 2 */  
#define DMA1_CH2_I2C1_TX      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_I2C1_TX)   /*!< Remap I2C1 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_SPI1_RX      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_SPI_1RX)   /*!< Remap SPI1 Rx on DMA1 channel 2 */ 
#define DMA1_CH2_TIM1_CH1     (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_TIM1_CH1)  /*!< Remap TIM1 channel 1 on DMA1 channel 2 */
#define DMA1_CH2_TIM17_CH1    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 2 */
#define DMA1_CH2_TIM17_UP     (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 2 */ 
#define DMA1_CH2_USART1_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART2_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART3_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART4_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART5_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART6_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART7_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART8_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 2 */ 
/* DMA1 - Channel 3 */
#define DMA1_CH3_DEFAULT      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMAx */   
#define DMA1_CH3_TIM6_UP      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM6_UP)   /*!< Remap TIM6 up on DMA1 channel 3 */ 
#define DMA1_CH3_DAC_CH1      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_DAC_CH1)   /*!< Remap DAC Channel 1on DMA1 channel 3 */ 
#define DMA1_CH3_I2C1_RX      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_I2C1_RX)   /*!< Remap I2C1 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_SPI1_TX      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_SPI1_TX)   /*!< Remap SPI1 Tx on DMA1 channel 3 */ 
#define DMA1_CH3_TIM1_CH2     (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM1_CH2)  /*!< Remap TIM1 channel 2 on DMA1 channel 3 */
#define DMA1_CH3_TIM2_CH2     (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM2_CH2)  /*!< Remap TIM2 channel 2 on DMA1 channel 3 */
#define DMA1_CH3_TIM16_CH1    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 3 */
#define DMA1_CH3_TIM16_UP     (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 3 */ 
#define DMA1_CH3_USART1_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART2_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART3_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART4_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART5_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART6_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART7_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART8_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 3 */ 
/* DMA1 - Channel 4 */
#define DMA1_CH4_DEFAULT      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH4_TIM7_UP      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM7_UP)   /*!< Remap TIM7 up on DMA1 channel 4 */ 
#define DMA1_CH4_DAC_CH2      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_DAC_CH2)   /*!< Remap DAC Channel 2 on DMA1 channel 4 */
#define DMA1_CH4_I2C2_TX      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_I2C2_TX)   /*!< Remap I2C2 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_SPI2_RX      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_SPI2_RX)   /*!< Remap SPI2 Rx on DMA1 channel 4 */ 
#define DMA1_CH4_TIM2_CH4     (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM2_CH4)  /*!< Remap TIM2 channel 4 on DMA1 channel 4 */
#define DMA1_CH4_TIM3_CH1     (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM3_CH1)  /*!< Remap TIM3 channel 1 on DMA1 channel 4 */
#define DMA1_CH4_TIM3_TRIG    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM3_TRIG) /*!< Remap TIM3 Trig on DMA1 channel 4 */ 
#define DMA1_CH4_TIM16_CH1    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 4 */
#define DMA1_CH4_TIM16_UP     (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 4 */ 
#define DMA1_CH4_USART1_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART2_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART3_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART4_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART5_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART6_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART7_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART8_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 4 */ 
/* DMA1 - Channel 5 */
#define DMA1_CH5_DEFAULT      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH5_I2C2_RX      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_I2C2_RX)   /*!< Remap I2C2 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_SPI2_TX      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_SPI2_TX)   /*!< Remap SPI1 Tx on DMA1 channel 5 */ 
#define DMA1_CH5_TIM1_CH3     (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_TIM1_CH3)  /*!< Remap TIM1 channel 3 on DMA1 channel 5 */
#define DMA1_CH5_USART1_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART2_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART3_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART4_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART5_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART6_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART7_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART8_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 5 */ 
/* DMA1 - Channel 6 */
#define DMA1_CH6_DEFAULT      (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH6_I2C1_TX      (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_I2C1_TX)   /*!< Remap I2C1 Tx on DMA1 channel 6 */ 
#define DMA1_CH6_SPI2_RX      (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_SPI2_RX)   /*!< Remap SPI2 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_TIM1_CH1     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM1_CH1)  /*!< Remap TIM1 channel 1 on DMA1 channel 6 */
#define DMA1_CH6_TIM1_CH2     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM1_CH2)  /*!< Remap TIM1 channel 2 on DMA1 channel 6 */
#define DMA1_CH6_TIM1_CH3     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM1_CH3)  /*!< Remap TIM1 channel 3 on DMA1 channel 6 */
#define DMA1_CH6_TIM3_CH1     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM3_CH1)  /*!< Remap TIM3 channel 1 on DMA1 channel 6 */
#define DMA1_CH6_TIM3_TRIG    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM3_TRIG) /*!< Remap TIM3 Trig on DMA1 channel 6 */ 
#define DMA1_CH6_TIM16_CH1    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 6 */
#define DMA1_CH6_TIM16_UP     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 6 */ 
#define DMA1_CH6_USART1_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART2_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART3_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART4_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART5_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART6_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART7_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART8_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 6 */ 
/* DMA1 - Channel 7 */
#define DMA1_CH7_DEFAULT      (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH7_I2C1_RX      (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_I2C1_RX)   /*!< Remap I2C1 Rx on DMA1 channel 7 */ 
#define DMA1_CH7_SPI2_TX      (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_SPI2_TX)   /*!< Remap SPI2 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_TIM2_CH2     (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM2_CH2)  /*!< Remap TIM2 channel 2 on DMA1 channel 7 */
#define DMA1_CH7_TIM2_CH4     (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM2_CH4)  /*!< Remap TIM2 channel 4 on DMA1 channel 7 */
#define DMA1_CH7_TIM17_CH1    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 7 */
#define DMA1_CH7_TIM17_UP     (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 7 */ 
#define DMA1_CH7_USART1_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART2_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART3_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART4_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART5_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART6_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART7_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART8_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 7 */

#define IS_DMA1_REMAP(REMAP)  ((REMAP == DMA1_CH1_DEFAULT)   ||\
                                    (REMAP == DMA1_CH1_ADC)       ||\
                                    (REMAP == DMA1_CH1_TIM17_CH1) ||\
                                    (REMAP == DMA1_CH1_TIM17_UP)  ||\
                                    (REMAP == DMA1_CH1_USART1_RX) ||\
                                    (REMAP == DMA1_CH1_USART2_RX) ||\
                                    (REMAP == DMA1_CH1_USART3_RX) ||\
                                    (REMAP == DMA1_CH1_USART4_RX) ||\
                                    (REMAP == DMA1_CH1_USART5_RX) ||\
                                    (REMAP == DMA1_CH1_USART6_RX) ||\
                                    (REMAP == DMA1_CH1_USART7_RX) ||\
                                    (REMAP == DMA1_CH1_USART8_RX) ||\
                                    (REMAP == DMA1_CH2_DEFAULT)   ||\
                                    (REMAP == DMA1_CH2_ADC)       ||\
                                    (REMAP == DMA1_CH2_I2C1_TX)   ||\
                                    (REMAP == DMA1_CH2_SPI1_RX)   ||\
                                    (REMAP == DMA1_CH2_TIM1_CH1)  ||\
                                    (REMAP == DMA1_CH2_I2C1_TX)   ||\
                                    (REMAP == DMA1_CH2_TIM17_CH1) ||\
                                    (REMAP == DMA1_CH2_TIM17_UP)  ||\
                                    (REMAP == DMA1_CH2_USART1_TX) ||\
                                    (REMAP == DMA1_CH2_USART2_TX) ||\
                                    (REMAP == DMA1_CH2_USART3_TX) ||\
                                    (REMAP == DMA1_CH2_USART4_TX) ||\
                                    (REMAP == DMA1_CH2_USART5_TX) ||\
                                    (REMAP == DMA1_CH2_USART6_TX) ||\
                                    (REMAP == DMA1_CH2_USART7_TX) ||\
                                    (REMAP == DMA1_CH2_USART8_TX) ||\
                                    (REMAP == DMA1_CH3_DEFAULT)   ||\
                                    (REMAP == DMA1_CH3_TIM6_UP)   ||\
                                    (REMAP == DMA1_CH3_DAC_CH1)   ||\
                                    (REMAP == DMA1_CH3_I2C1_RX)   ||\
                                    (REMAP == DMA1_CH3_SPI1_TX)   ||\
                                    (REMAP == DMA1_CH3_TIM1_CH2)  ||\
                                    (REMAP == DMA1_CH3_TIM2_CH2)  ||\
                                    (REMAP == DMA1_CH3_TIM16_CH1) ||\
                                    (REMAP == DMA1_CH3_TIM16_UP)  ||\
                                    (REMAP == DMA1_CH3_USART1_RX) ||\
                                    (REMAP == DMA1_CH3_USART2_RX) ||\
                                    (REMAP == DMA1_CH3_USART3_RX) ||\
                                    (REMAP == DMA1_CH3_USART4_RX) ||\
                                    (REMAP == DMA1_CH3_USART5_RX) ||\
                                    (REMAP == DMA1_CH3_USART6_RX) ||\
                                    (REMAP == DMA1_CH3_USART7_RX) ||\
                                    (REMAP == DMA1_CH3_USART8_RX) ||\
                                    (REMAP == DMA1_CH4_DEFAULT)   ||\
                                    (REMAP == DMA1_CH4_TIM7_UP)   ||\
                                    (REMAP == DMA1_CH4_DAC_CH2)   ||\
                                    (REMAP == DMA1_CH4_I2C2_TX)   ||\
                                    (REMAP == DMA1_CH4_SPI2_RX)   ||\
                                    (REMAP == DMA1_CH4_TIM2_CH4)  ||\
                                    (REMAP == DMA1_CH4_TIM3_CH1)  ||\
                                    (REMAP == DMA1_CH4_TIM3_TRIG) ||\
                                    (REMAP == DMA1_CH4_TIM16_CH1) ||\
                                    (REMAP == DMA1_CH4_TIM16_UP)  ||\
                                    (REMAP == DMA1_CH4_USART1_TX) ||\
                                    (REMAP == DMA1_CH4_USART2_TX) ||\
                                    (REMAP == DMA1_CH4_USART3_TX) ||\
                                    (REMAP == DMA1_CH4_USART4_TX) ||\
                                    (REMAP == DMA1_CH4_USART5_TX) ||\
                                    (REMAP == DMA1_CH4_USART6_TX) ||\
                                    (REMAP == DMA1_CH4_USART7_TX) ||\
                                    (REMAP == DMA1_CH4_USART8_TX) ||\
                                    (REMAP == DMA1_CH5_DEFAULT)   ||\
                                    (REMAP == DMA1_CH5_I2C2_RX)   ||\
                                    (REMAP == DMA1_CH5_SPI2_TX)   ||\
                                    (REMAP == DMA1_CH5_TIM1_CH3)  ||\
                                    (REMAP == DMA1_CH5_USART1_RX) ||\
                                    (REMAP == DMA1_CH5_USART2_RX) ||\
                                    (REMAP == DMA1_CH5_USART3_RX) ||\
                                    (REMAP == DMA1_CH5_USART4_RX) ||\
                                    (REMAP == DMA1_CH5_USART5_RX) ||\
                                    (REMAP == DMA1_CH5_USART6_RX) ||\
                                    (REMAP == DMA1_CH5_USART7_RX) ||\
                                    (REMAP == DMA1_CH5_USART8_RX) ||\
                                    (REMAP == DMA1_CH6_DEFAULT)   ||\
                                    (REMAP == DMA1_CH6_I2C1_TX)   ||\
                                    (REMAP == DMA1_CH6_SPI2_RX)   ||\
                                    (REMAP == DMA1_CH6_TIM1_CH1)  ||\
                                    (REMAP == DMA1_CH6_TIM1_CH2)  ||\
                                    (REMAP == DMA1_CH6_TIM1_CH3)  ||\
                                    (REMAP == DMA1_CH6_TIM3_CH1)  ||\
                                    (REMAP == DMA1_CH6_TIM3_TRIG) ||\
                                    (REMAP == DMA1_CH6_TIM16_CH1) ||\
                                    (REMAP == DMA1_CH6_TIM16_UP)  ||\
                                    (REMAP == DMA1_CH6_USART1_RX) ||\
                                    (REMAP == DMA1_CH6_USART2_RX) ||\
                                    (REMAP == DMA1_CH6_USART3_RX) ||\
                                    (REMAP == DMA1_CH6_USART4_RX) ||\
                                    (REMAP == DMA1_CH6_USART5_RX) ||\
                                    (REMAP == DMA1_CH6_USART6_RX) ||\
                                    (REMAP == DMA1_CH6_USART7_RX) ||\
                                    (REMAP == DMA1_CH6_USART8_RX) ||\
                                    (REMAP == DMA1_CH7_DEFAULT)   ||\
                                    (REMAP == DMA1_CH7_I2C1_RX)   ||\
                                    (REMAP == DMA1_CH7_SPI2_TX)   ||\
                                    (REMAP == DMA1_CH7_TIM2_CH2)  ||\
                                    (REMAP == DMA1_CH7_TIM2_CH4)  ||\
                                    (REMAP == DMA1_CH7_TIM17_CH1) ||\
                                    (REMAP == DMA1_CH7_TIM17_UP)  ||\
                                    (REMAP == DMA1_CH7_USART1_TX) ||\
                                    (REMAP == DMA1_CH7_USART2_TX) ||\
                                    (REMAP == DMA1_CH7_USART3_TX) ||\
                                    (REMAP == DMA1_CH7_USART4_TX) ||\
                                    (REMAP == DMA1_CH7_USART5_TX) ||\
                                    (REMAP == DMA1_CH7_USART6_TX) ||\
                                    (REMAP == DMA1_CH7_USART7_TX) ||\
                                    (REMAP == DMA1_CH7_USART8_TX))

/****************** DMA2 remap bit field definition********************/
/* DMA2 - Channel 1 */
#define DMA2_CH1_DEFAULT      (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH1_I2C2_TX      (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_I2C2_TX)   /*!< Remap I2C2 TX on DMA2 channel 1 */ 
#define DMA2_CH1_USART1_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART2_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART3_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART4_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART5_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART6_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART7_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART8_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 1 */ 
/* DMA2 - Channel 2 */
#define DMA2_CH2_DEFAULT      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH2_I2C2_RX      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_I2C2_RX)   /*!< Remap I2C2 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART1_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART1_RX) /*!< Remap USART1 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART2_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART2_RX) /*!< Remap USART2 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART3_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART3_RX) /*!< Remap USART3 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART4_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART4_RX) /*!< Remap USART4 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART5_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART5_RX) /*!< Remap USART5 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART6_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART6_RX) /*!< Remap USART6 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART7_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART7_RX) /*!< Remap USART7 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART8_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART8_RX) /*!< Remap USART8 Rx on DMA2 channel 2 */ 
/* DMA2 - Channel 3 */
#define DMA2_CH3_DEFAULT      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH3_TIM6_UP      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_TIM6_UP)   /*!< Remap TIM6 up on DMA2 channel 3 */ 
#define DMA2_CH3_DAC_CH1      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_DAC_CH1)   /*!< Remap DAC channel 1 on DMA2 channel 3 */
#define DMA2_CH3_SPI1_RX      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_SPI1_RX)   /*!< Remap SPI1 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART1_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART1_RX) /*!< Remap USART1 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART2_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART2_RX) /*!< Remap USART2 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART3_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART3_RX) /*!< Remap USART3 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART4_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART4_RX) /*!< Remap USART4 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART5_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART5_RX) /*!< Remap USART5 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART6_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART6_RX) /*!< Remap USART6 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART7_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART7_RX) /*!< Remap USART7 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART8_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART8_RX) /*!< Remap USART8 Rx on DMA2 channel 3 */ 
/* DMA2 - Channel 4 */
#define DMA2_CH4_DEFAULT      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH4_TIM7_UP      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_TIM7_UP)   /*!< Remap TIM7 up on DMA2 channel 4 */ 
#define DMA2_CH4_DAC_CH2      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_DAC_CH2)   /*!< Remap DAC channel 2 on DMA2 channel 4 */
#define DMA2_CH4_SPI1_TX      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_SPI1_TX)   /*!< Remap SPI1 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART1_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART2_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART3_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART4_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART5_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART6_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART7_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART8_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 4 */ 
/* DMA2 - Channel 5 */
#define DMA2_CH5_DEFAULT      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH5_ADC          (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_ADC)       /*!< Remap ADC on DMA2 channel 5 */  
#define DMA2_CH5_USART1_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART2_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART3_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART4_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART5_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART6_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART7_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART8_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 5 */ 

#define IS_DMA2_REMAP(REMAP)  ((REMAP == DMA2_CH1_DEFAULT)   ||\
                                    (REMAP == DMA2_CH1_I2C2_TX)   ||\
                                    (REMAP == DMA2_CH1_USART1_TX) ||\
                                    (REMAP == DMA2_CH1_USART2_TX) ||\
                                    (REMAP == DMA2_CH1_USART3_TX) ||\
                                    (REMAP == DMA2_CH1_USART4_TX) ||\
                                    (REMAP == DMA2_CH1_USART5_TX) ||\
                                    (REMAP == DMA2_CH1_USART6_TX) ||\
                                    (REMAP == DMA2_CH1_USART7_TX) ||\
                                    (REMAP == DMA2_CH1_USART8_TX) ||\
                                    (REMAP == DMA2_CH2_DEFAULT)   ||\
                                    (REMAP == DMA2_CH2_I2C2_RX)   ||\
                                    (REMAP == DMA2_CH2_USART1_RX) ||\
                                    (REMAP == DMA2_CH2_USART2_RX) ||\
                                    (REMAP == DMA2_CH2_USART3_RX) ||\
                                    (REMAP == DMA2_CH2_USART4_RX) ||\
                                    (REMAP == DMA2_CH2_USART5_RX) ||\
                                    (REMAP == DMA2_CH2_USART6_RX) ||\
                                    (REMAP == DMA2_CH2_USART7_RX) ||\
                                    (REMAP == DMA2_CH2_USART8_RX) ||\
                                    (REMAP == DMA2_CH3_DEFAULT)   ||\
                                    (REMAP == DMA2_CH3_TIM6_UP)   ||\
                                    (REMAP == DMA2_CH3_DAC_CH1)   ||\
                                    (REMAP == DMA2_CH3_SPI1_RX)   ||\
                                    (REMAP == DMA2_CH3_USART1_RX) ||\
                                    (REMAP == DMA2_CH3_USART2_RX) ||\
                                    (REMAP == DMA2_CH3_USART3_RX) ||\
                                    (REMAP == DMA2_CH3_USART4_RX) ||\
                                    (REMAP == DMA2_CH3_USART5_RX) ||\
                                    (REMAP == DMA2_CH3_USART6_RX) ||\
                                    (REMAP == DMA2_CH3_USART7_RX) ||\
                                    (REMAP == DMA2_CH3_USART8_RX) ||\
                                    (REMAP == DMA2_CH4_DEFAULT)   ||\
                                    (REMAP == DMA2_CH4_TIM7_UP)   ||\
                                    (REMAP == DMA2_CH4_DAC_CH2)   ||\
                                    (REMAP == DMA2_CH4_SPI1_TX)   ||\
                                    (REMAP == DMA2_CH4_USART1_TX) ||\
                                    (REMAP == DMA2_CH4_USART2_TX) ||\
                                    (REMAP == DMA2_CH4_USART3_TX) ||\
                                    (REMAP == DMA2_CH4_USART4_TX) ||\
                                    (REMAP == DMA2_CH4_USART5_TX) ||\
                                    (REMAP == DMA2_CH4_USART6_TX) ||\
                                    (REMAP == DMA2_CH4_USART7_TX) ||\
                                    (REMAP == DMA2_CH4_USART8_TX) ||\
                                    (REMAP == DMA2_CH5_DEFAULT)   ||\
                                    (REMAP == DMA2_CH5_ADC)       ||\
                                    (REMAP == DMA2_CH5_USART1_TX) ||\
                                    (REMAP == DMA2_CH5_USART2_TX) ||\
                                    (REMAP == DMA2_CH5_USART3_TX) ||\
                                    (REMAP == DMA2_CH5_USART4_TX) ||\
                                    (REMAP == DMA2_CH5_USART5_TX) ||\
                                    (REMAP == DMA2_CH5_USART6_TX) ||\
                                    (REMAP == DMA2_CH5_USART7_TX) ||\
                                    (REMAP == DMA2_CH5_USART8_TX ))

/**
  * @}
  */
  
/** @defgroup DMA_interrupts_definition
  * @{
  */

#define DMA_IT_TC                          DMA_CCR_TCIE
#define DMA_IT_HT                          DMA_CCR_HTIE
#define DMA_IT_TE                          DMA_CCR_TEIE

#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA1_IT_GL1                        DMA_ISR_GIF1
#define DMA1_IT_TC1                        DMA_ISR_TCIF1
#define DMA1_IT_HT1                        DMA_ISR_HTIF1
#define DMA1_IT_TE1                        DMA_ISR_TEIF1
#define DMA1_IT_GL2                        DMA_ISR_GIF2
#define DMA1_IT_TC2                        DMA_ISR_TCIF2
#define DMA1_IT_HT2                        DMA_ISR_HTIF2
#define DMA1_IT_TE2                        DMA_ISR_TEIF2
#define DMA1_IT_GL3                        DMA_ISR_GIF3
#define DMA1_IT_TC3                        DMA_ISR_TCIF3
#define DMA1_IT_HT3                        DMA_ISR_HTIF3
#define DMA1_IT_TE3                        DMA_ISR_TEIF3
#define DMA1_IT_GL4                        DMA_ISR_GIF4
#define DMA1_IT_TC4                        DMA_ISR_TCIF4
#define DMA1_IT_HT4                        DMA_ISR_HTIF4
#define DMA1_IT_TE4                        DMA_ISR_TEIF4
#define DMA1_IT_GL5                        DMA_ISR_GIF5
#define DMA1_IT_TC5                        DMA_ISR_TCIF5
#define DMA1_IT_HT5                        DMA_ISR_HTIF5
#define DMA1_IT_TE5                        DMA_ISR_TEIF5 
 

#define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00))

#define IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || \
                           ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || \
                           ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || \
                           ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || \
                           ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || \
                           ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || \
                           ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || \
                           ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || \
                           ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || \
                           ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || \
                           ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || \
                           ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || \
                           ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || \
                           ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7) || \
                           ((IT) == DMA2_IT_GL1) || ((IT) == DMA2_IT_TC1) || \
                           ((IT) == DMA2_IT_HT1) || ((IT) == DMA2_IT_TE1) || \
                           ((IT) == DMA2_IT_GL2) || ((IT) == DMA2_IT_TC2) || \
                           ((IT) == DMA2_IT_HT2) || ((IT) == DMA2_IT_TE2) || \
                           ((IT) == DMA2_IT_GL3) || ((IT) == DMA2_IT_TC3) || \
                           ((IT) == DMA2_IT_HT3) || ((IT) == DMA2_IT_TE3) || \
                           ((IT) == DMA2_IT_GL4) || ((IT) == DMA2_IT_TC4) || \
                           ((IT) == DMA2_IT_HT4) || ((IT) == DMA2_IT_TE4) || \
                           ((IT) == DMA2_IT_GL5) || ((IT) == DMA2_IT_TC5) || \
                           ((IT) == DMA2_IT_HT5) || ((IT) == DMA2_IT_TE5))

/**
  * @}
  */

/** @defgroup DMA_flags_definition 
  * @{
  */
#define DMA1_FLAG_GL1                      DMA_ISR_GIF1
#define DMA1_FLAG_TC1                      DMA_ISR_TCIF1
#define DMA1_FLAG_HT1                      DMA_ISR_HTIF1
#define DMA1_FLAG_TE1                      DMA_ISR_TEIF1
#define DMA1_FLAG_GL2                      DMA_ISR_GIF2
#define DMA1_FLAG_TC2                      DMA_ISR_TCIF2
#define DMA1_FLAG_HT2                      DMA_ISR_HTIF2
#define DMA1_FLAG_TE2                      DMA_ISR_TEIF2
#define DMA1_FLAG_GL3                      DMA_ISR_GIF3
#define DMA1_FLAG_TC3                      DMA_ISR_TCIF3
#define DMA1_FLAG_HT3                      DMA_ISR_HTIF3
#define DMA1_FLAG_TE3                      DMA_ISR_TEIF3
#define DMA1_FLAG_GL4                      DMA_ISR_GIF4
#define DMA1_FLAG_TC4                      DMA_ISR_TCIF4
#define DMA1_FLAG_HT4                      DMA_ISR_HTIF4
#define DMA1_FLAG_TE4                      DMA_ISR_TEIF4
#define DMA1_FLAG_GL5                      DMA_ISR_GIF5
#define DMA1_FLAG_TC5                      DMA_ISR_TCIF5
#define DMA1_FLAG_HT5                      DMA_ISR_HTIF5
#define DMA1_FLAG_TE5                      DMA_ISR_TEIF5 

#define DMA2_FLAG_GL1                      ((uint32_t)0x10000001)
#define DMA2_FLAG_TC1                      ((uint32_t)0x10000002)
#define DMA2_FLAG_HT1                      ((uint32_t)0x10000004)
#define DMA2_FLAG_TE1                      ((uint32_t)0x10000008)
#define DMA2_FLAG_GL2                      ((uint32_t)0x10000010)
#define DMA2_FLAG_TC2                      ((uint32_t)0x10000020)
#define DMA2_FLAG_HT2                      ((uint32_t)0x10000040)
#define DMA2_FLAG_TE2                      ((uint32_t)0x10000080)
#define DMA2_FLAG_GL3                      ((uint32_t)0x10000100)
#define DMA2_FLAG_TC3                      ((uint32_t)0x10000200)
#define DMA2_FLAG_HT3                      ((uint32_t)0x10000400)
#define DMA2_FLAG_TE3                      ((uint32_t)0x10000800)
#define DMA2_FLAG_GL4                      ((uint32_t)0x10001000)
#define DMA2_FLAG_TC4                      ((uint32_t)0x10002000)
#define DMA2_FLAG_HT4                      ((uint32_t)0x10004000)
#define DMA2_FLAG_TE4                      ((uint32_t)0x10008000)
#define DMA2_FLAG_GL5                      ((uint32_t)0x10010000)
#define DMA2_FLAG_TC5                      ((uint32_t)0x10020000)
#define DMA2_FLAG_HT5                      ((uint32_t)0x10040000)
#define DMA2_FLAG_TE5                      ((uint32_t)0x10080000)

#define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00))

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || \
                               ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || \
                               ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || \
                               ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || \
                               ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || \
                               ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || \
                               ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || \
                               ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC5) || \
                               ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE5) || \
                               ((FLAG) == DMA1_FLAG_GL6) || ((FLAG) == DMA1_FLAG_TC6) || \
                               ((FLAG) == DMA1_FLAG_HT6) || ((FLAG) == DMA1_FLAG_TE6) || \
                               ((FLAG) == DMA1_FLAG_GL7) || ((FLAG) == DMA1_FLAG_TC7) || \
                               ((FLAG) == DMA1_FLAG_HT7) || ((FLAG) == DMA1_FLAG_TE7) || \
                               ((FLAG) == DMA2_FLAG_GL1) || ((FLAG) == DMA2_FLAG_TC1) || \
                               ((FLAG) == DMA2_FLAG_HT1) || ((FLAG) == DMA2_FLAG_TE1) || \
                               ((FLAG) == DMA2_FLAG_GL2) || ((FLAG) == DMA2_FLAG_TC2) || \
                               ((FLAG) == DMA2_FLAG_HT2) || ((FLAG) == DMA2_FLAG_TE2) || \
                               ((FLAG) == DMA2_FLAG_GL3) || ((FLAG) == DMA2_FLAG_TC3) || \
                               ((FLAG) == DMA2_FLAG_HT3) || ((FLAG) == DMA2_FLAG_TE3) || \
                               ((FLAG) == DMA2_FLAG_GL4) || ((FLAG) == DMA2_FLAG_TC4) || \
                               ((FLAG) == DMA2_FLAG_HT4) || ((FLAG) == DMA2_FLAG_TE4) || \
                               ((FLAG) == DMA2_FLAG_GL5) || ((FLAG) == DMA2_FLAG_TC5) || \
                               ((FLAG) == DMA2_FLAG_HT5) || ((FLAG) == DMA2_FLAG_TE5))
/**
  * @}
  */

/** @defgroup DMA_Buffer_Size 
  * @{
  */

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the DMA configuration to the default reset state ******/
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

/* Initialization and Configuration functions *********************************/
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);

/* Data Counter functions******************************************************/ 
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);

/* Interrupts and flags management functions **********************************/
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XX_DMA_H */

/**
  * @}
  */

/**
  * @}
  */ 
