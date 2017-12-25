/**
  ******************************************************************************
  * @file    stm32h7xx_hal_dma_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    21-April-2017
  * @brief   Header file of DMA HAL extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_HAL_DMA_EX_H
#define __STM32H7xx_HAL_DMA_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup DMAEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/** @defgroup DMAEx_Exported_Types DMAEx Exported Types
  * @brief DMAEx Exported types
  * @{
  */
   
/** 
  * @brief  HAL DMA Memory definition  
  */ 
typedef enum
{
  MEMORY0      = 0x00U,    /*!< Memory 0     */
  MEMORY1      = 0x01U,    /*!< Memory 1     */

}HAL_DMA_MemoryTypeDef;

/**
  * @brief  HAL DMAMUX Synchronization configuration structure definition
  */
typedef struct
{
  uint32_t SyncSignalID;  /*!< Specifies the synchronization signal gating the DMA request in periodic mode.
                              This parameter can be a value of @ref DMAEx_MUX_SyncSignalID_selection */
  
  uint32_t SyncPolarity;  /*!< Specifies the polarity of the signal on which the DMA request is synchronized.
                              This parameter can be a value of @ref DMAEx_MUX_SyncPolarity_selection */

  FunctionalState SyncEnable;  /*!< Specifies if the synchronization shall be enabled or disabled
                                    This parameter can take the value ENABLE or DISABLE*/
  
  
  FunctionalState EventEnable;    /*!< Specifies if an event shall be generated once the RequestNumber is reached.
                                       This parameter can take the value ENABLE or DISABLE */

  uint32_t RequestNumber; /*!< Specifies the number of DMA request that will be authorized after a sync event*/

}HAL_DMA_MuxSyncConfigTypeDef;


/**
  * @brief  HAL DMAMUX request generator parameters structure definition
  */
typedef struct
{
 uint32_t SignalID;      /*!< Specifies the ID of the signal used for DMAMUX request generator
                              This parameter can be a value of @ref DMAEx_MUX_SignalGeneratorID_selection */

  uint32_t Polarity;       /*!< Specifies the polarity of the signal on which the request is generated.
                             This parameter can be a value of @ref DMAEx_MUX_RequestGeneneratorPolarity_selection */
  
  uint32_t RequestNumber;  /*!< Specifies the number of DMA request that will be generated after a signal event*/

}HAL_DMA_MuxRequestGeneratorConfigTypeDef;

/**
  * @}
  */
  
/* Exported constants --------------------------------------------------------*/

/** @defgroup DMAEx_Exported_Constants DMA Exported Constants
  * @brief    DMAEx Exported constants 
  * @{
  */

/** @defgroup DMAEx_MUX_SyncSignalID_selection DMAEx MUX SyncSignalID selection
  * @brief    DMAEx MUX SyncSignalID selection 
  * @{
  */ 
#define HAL_DMAMUX1_SYNC_DMAMUX1_CH0_EVT  ((uint32_t)0x00000000)       /*!< D2 Domain synchronization Signal is DMAMUX1 Channel0 Event */
#define HAL_DMAMUX1_SYNC_DMAMUX1_CH1_EVT  ((uint32_t)0x01000000)       /*!< D2 Domain synchronization Signal is DMAMUX1 Channel1 Event */
#define HAL_DMAMUX1_SYNC_DMAMUX1_CH2_EVT  ((uint32_t)0x02000000)       /*!< D2 Domain synchronization Signal is DMAMUX1 Channel2 Event */
#define HAL_DMAMUX1_SYNC_LPTIM1_OUT       ((uint32_t)0x03000000)       /*!< D2 Domain synchronization Signal is LPTIM1 OUT */
#define HAL_DMAMUX1_SYNC_LPTIM2_OUT       ((uint32_t)0x04000000)       /*!< D2 Domain synchronization Signal is LPTIM2 OUT */
#define HAL_DMAMUX1_SYNC_LPTIM3_OUT       ((uint32_t)0x05000000)       /*!< D2 Domain synchronization Signal is LPTIM3 OUT */
#define HAL_DMAMUX1_SYNC_EXTI0            ((uint32_t)0x06000000)       /*!< D2 Domain synchronization Signal is EXTI0 IT   */
#define HAL_DMAMUX1_SYNC_TIM12_TRGO       ((uint32_t)0x07000000)       /*!< D2 Domain synchronization Signal is TIM12 TRGO */

#define HAL_DMAMUX2_SYNC_DMAMUX2_CH0_EVT  ((uint32_t)0x00000000)       /*!< D3 Domain synchronization Signal is DMAMUX2 Channel0 Event */
#define HAL_DMAMUX2_SYNC_DMAMUX2_CH1_EVT  ((uint32_t)0x01000000)       /*!< D3 Domain synchronization Signal is DMAMUX2 Channel1 Event */
#define HAL_DMAMUX2_SYNC_DMAMUX2_CH2_EVT  ((uint32_t)0x02000000)       /*!< D3 Domain synchronization Signal is DMAMUX2 Channel2 Event */
#define HAL_DMAMUX2_SYNC_DMAMUX2_CH3_EVT  ((uint32_t)0x03000000)       /*!< D3 Domain synchronization Signal is DMAMUX2 Channel3 Event */
#define HAL_DMAMUX2_SYNC_DMAMUX2_CH4_EVT  ((uint32_t)0x04000000)       /*!< D3 Domain synchronization Signal is DMAMUX2 Channel4 Event */
#define HAL_DMAMUX2_SYNC_DMAMUX2_CH5_EVT  ((uint32_t)0x05000000)       /*!< D3 Domain synchronization Signal is DMAMUX2 Channel5 Event */
#define HAL_DMAMUX2_SYNC_LPUART1_RX_WKUP  ((uint32_t)0x06000000)       /*!< D3 Domain synchronization Signal is LPUART1 RX Wakeup */
#define HAL_DMAMUX2_SYNC_LPUART1_TX_WKUP  ((uint32_t)0x07000000)       /*!< D3 Domain synchronization Signal is LPUART1 TX Wakeup */
#define HAL_DMAMUX2_SYNC_LPTIM2_OUT       ((uint32_t)0x08000000)       /*!< D3 Domain synchronization Signal is LPTIM2 output */
#define HAL_DMAMUX2_SYNC_LPTIM3_OUT       ((uint32_t)0x09000000)       /*!< D3 Domain synchronization Signal is LPTIM3 output */
#define HAL_DMAMUX2_SYNC_I2C4_WKUP        ((uint32_t)0x0A000000)       /*!< D3 Domain synchronization Signal is I2C4 Wakeup   */
#define HAL_DMAMUX2_SYNC_SPI6_WKUP        ((uint32_t)0x0B000000)       /*!< D3 Domain synchronization Signal is SPI6 Wakeup   */
#define HAL_DMAMUX2_SYNC_COMP1_OUT        ((uint32_t)0x0C000000)       /*!< D3 Domain synchronization Signal is Comparator 1 output */
#define HAL_DMAMUX2_SYNC_RTC_WKUP         ((uint32_t)0x0D000000)       /*!< D3 Domain synchronization Signal is RTC Wakeup */
#define HAL_DMAMUX2_SYNC_EXTI0            ((uint32_t)0x0E000000)       /*!< D3 Domain synchronization Signal is EXTI0 IT   */
#define HAL_DMAMUX2_SYNC_EXTI2            ((uint32_t)0x0F000000)       /*!< D3 Domain synchronization Signal is EXTI2 IT   */

/**
  * @}
  */

/** @defgroup DMAEx_MUX_SyncPolarity_selection DMAEx MUX SyncPolarity selection
  * @brief    DMAEx MUX SyncPolarity selection 
  * @{
  */
#define HAL_DMAMUX_SYNC_NO_EVENT   ((uint32_t)0x00000000)            /*!< block synchronization events        */
#define HAL_DMAMUX_SYNC_RISING     ((uint32_t)DMAMUX_CxCR_SPOL_0)    /*!< synchronize with rising edge events */
#define HAL_DMAMUX_SYNC_FALLING    ((uint32_t)DMAMUX_CxCR_SPOL_1)    /*!< synchronize with falling edge events */
#define HAL_DMAMUX_SYNC_RISING_FALLING ((uint32_t)DMAMUX_CxCR_SPOL)  /*!< synchronize with rising and falling edge events */

/**
  * @}
  */

  
/** @defgroup DMAEx_MUX_SignalGeneratorID_selection DMAEx MUX SignalGeneratorID selection
  * @brief    DMAEx MUX SignalGeneratorID selection
  * @{
  */
#define HAL_DMAMUX1_REQUEST_GEN_DMAMUX1_CH0_EVT  ((uint32_t)0x00000000)   /*!< D2 domain Request generator Signal is DMAMUX1 Channel0 Event */
#define HAL_DMAMUX1_REQUEST_GEN_DMAMUX1_CH1_EVT  ((uint32_t)0x00000001)   /*!< D2 domain Request generator Signal is DMAMUX1 Channel1 Event */
#define HAL_DMAMUX1_REQUEST_GEN_DMAMUX1_CH2_EVT  ((uint32_t)0x00000002)   /*!< D2 domain Request generator Signal is DMAMUX1 Channel2 Event */
#define HAL_DMAMUX1_REQUEST_GEN_LPTIM1_OUT       ((uint32_t)0x00000003)   /*!< D2 domain Request generator Signal is LPTIM1 OUT */
#define HAL_DMAMUX1_REQUEST_GEN_LPTIM2_OUT       ((uint32_t)0x00000004)   /*!< D2 domain Request generator Signal is LPTIM2 OUT */
#define HAL_DMAMUX1_REQUEST_GEN_LPTIM3_OUT       ((uint32_t)0x00000005)   /*!< D2 domain Request generator Signal is LPTIM3 OUT */
#define HAL_DMAMUX1_REQUEST_GEN_EXTI0            ((uint32_t)0x00000006)   /*!< D2 domain Request generator Signal is EXTI0 IT   */
#define HAL_DMAMUX1_REQUEST_GEN_TIM12_TRGO       ((uint32_t)0x00000007)   /*!< D2 domain Request generator Signal is TIM12 TRGO */

#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH0_EVT  ((uint32_t)0x00000000)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel0 Event */
#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH1_EVT  ((uint32_t)0x00000001)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel1 Event */
#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH2_EVT  ((uint32_t)0x00000002)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel2 Event */
#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH3_EVT  ((uint32_t)0x00000003)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel3 Event */
#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH4_EVT  ((uint32_t)0x00000004)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel4 Event */
#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH5_EVT  ((uint32_t)0x00000005)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel5 Event */
#define HAL_DMAMUX2_REQUEST_GEN_DMAMUX2_CH6_EVT  ((uint32_t)0x00000006)   /*!< D3 domain Request generator Signal is DMAMUX2 Channel6 Event */
#define HAL_DMAMUX2_REQUEST_GEN_LPUART1_RX_WKUP  ((uint32_t)0x00000007)   /*!< D3 domain Request generator Signal is LPUART1 RX Wakeup   */
#define HAL_DMAMUX2_REQUEST_GEN_LPUART1_TX_WKUP  ((uint32_t)0x00000008)   /*!< D3 domain Request generator Signal is LPUART1 TX Wakeup   */
#define HAL_DMAMUX2_REQUEST_GEN_LPTIM2_WKUP      ((uint32_t)0x00000009)   /*!< D3 domain Request generator Signal is LPTIM2 Wakeup       */
#define HAL_DMAMUX2_REQUEST_GEN_LPTIM2_OUT       ((uint32_t)0x0000000A)   /*!< D3 domain Request generator Signal is LPTIM2 OUT          */
#define HAL_DMAMUX2_REQUEST_GEN_LPTIM3_WKUP      ((uint32_t)0x0000000B)   /*!< D3 domain Request generator Signal is LPTIM3 Wakeup       */
#define HAL_DMAMUX2_REQUEST_GEN_LPTIM3_OUT       ((uint32_t)0x0000000C)   /*!< D3 domain Request generator Signal is LPTIM3 OUT          */
#define HAL_DMAMUX2_REQUEST_GEN_LPTIM4_WKUP      ((uint32_t)0x0000000D)   /*!< D3 domain Request generator Signal is LPTIM4 Wakeup       */
#define HAL_DMAMUX2_REQUEST_GEN_LPTIM5_WKUP      ((uint32_t)0x0000000E)   /*!< D3 domain Request generator Signal is LPTIM5 Wakeup       */
#define HAL_DMAMUX2_REQUEST_GEN_I2C4_WKUP        ((uint32_t)0x0000000F)   /*!< D3 domain Request generator Signal is I2C4 Wakeup         */
#define HAL_DMAMUX2_REQUEST_GEN_SPI6_WKUP        ((uint32_t)0x00000010)   /*!< D3 domain Request generator Signal is SPI6 Wakeup         */
#define HAL_DMAMUX2_REQUEST_GEN_COMP1_OUT        ((uint32_t)0x00000011)   /*!< D3 domain Request generator Signal is Comparator 1 output */
#define HAL_DMAMUX2_REQUEST_GEN_COMP2_OUT        ((uint32_t)0x00000012)   /*!< D3 domain Request generator Signal is Comparator 2 output */
#define HAL_DMAMUX2_REQUEST_GEN_RTC_WKUP         ((uint32_t)0x00000013)   /*!< D3 domain Request generator Signal is RTC Wakeup          */
#define HAL_DMAMUX2_REQUEST_GEN_EXTI0            ((uint32_t)0x00000014)   /*!< D3 domain Request generator Signal is EXTI0               */
#define HAL_DMAMUX2_REQUEST_GEN_EXTI2            ((uint32_t)0x00000015)   /*!< D3 domain Request generator Signal is EXTI2               */
#define HAL_DMAMUX2_REQUEST_GEN_I2C4_IT_EVT      ((uint32_t)0x00000016)   /*!< D3 domain Request generator Signal is I2C4 IT Event       */
#define HAL_DMAMUX2_REQUEST_GEN_SPI6_IT          ((uint32_t)0x00000017)   /*!< D3 domain Request generator Signal is SPI6 IT             */
#define HAL_DMAMUX2_REQUEST_GEN_LPUART1_TX_IT    ((uint32_t)0x00000018)   /*!< D3 domain Request generator Signal is LPUART1 Tx IT       */
#define HAL_DMAMUX2_REQUEST_GEN_LPUART1_RX_IT    ((uint32_t)0x00000019)   /*!< D3 domain Request generator Signal is LPUART1 Rx IT       */
#define HAL_DMAMUX2_REQUEST_GEN_ADC3_IT          ((uint32_t)0x0000001A)   /*!< D3 domain Request generator Signal is ADC3 IT             */
#define HAL_DMAMUX2_REQUEST_GEN_ADC3_AWD1_OUT    ((uint32_t)0x0000001B)   /*!< D3 domain Request generator Signal is ADC3 Analog Watchdog 1 output */
#define HAL_DMAMUX2_REQUEST_GEN_BDMA_CH0_IT      ((uint32_t)0x0000001C)   /*!< D3 domain Request generator Signal is BDMA Channel 0 IT    */
#define HAL_DMAMUX2_REQUEST_GEN_BDMA_CH1_IT      ((uint32_t)0x0000001D)   /*!< D3 domain Request generator Signal is BDMA Channel 1 IT    */


/**
  * @}
  */  

/** @defgroup DMAEx_MUX_RequestGeneneratorPolarity_selection DMAEx MUX RequestGeneneratorPolarity selection
  * @brief    DMAEx MUX RequestGeneneratorPolarity selection 
  * @{
  */
#define HAL_DMAMUX_REQUEST_GEN_NO_EVENT       ((uint32_t)0x00000000)           /*!< block request generator events                     */
#define HAL_DMAMUX_REQUEST_GEN_RISING         ((uint32_t)DMAMUX_RGxCR_GPOL_0)  /*!< generate request on rising edge events             */
#define HAL_DMAMUX_REQUEST_GEN_FALLING        ((uint32_t)DMAMUX_RGxCR_GPOL_1)  /*!< generate request on falling edge events            */
#define HAL_DMAMUX_REQUEST_GEN_RISING_FALLING ((uint32_t)DMAMUX_RGxCR_GPOL)    /*!< generate request on rising and falling edge events */
                                          
/**
  * @}
  */

/**
  * @}
  */  

/* Exported functions --------------------------------------------------------*/
/** @defgroup DMAEx_Exported_Functions DMAEx Exported Functions
  * @brief   DMAEx Exported functions
  * @{
  */

/** @defgroup DMAEx_Exported_Functions_Group1 Extended features functions
  * @brief   Extended features functions
  * @{
  */

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMAEx_ChangeMemory(DMA_HandleTypeDef *hdma, uint32_t Address, HAL_DMA_MemoryTypeDef memory);
HAL_StatusTypeDef HAL_DMAEx_ConfigMuxSync(DMA_HandleTypeDef *hdma, HAL_DMA_MuxSyncConfigTypeDef *pSyncConfig);
HAL_StatusTypeDef HAL_DMAEx_ConfigMuxRequestGenerator (DMA_HandleTypeDef *hdma, HAL_DMA_MuxRequestGeneratorConfigTypeDef *pRequestGeneratorConfig);
HAL_StatusTypeDef HAL_DMAEx_EnableMuxRequestGenerator (DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMAEx_DisableMuxRequestGenerator (DMA_HandleTypeDef *hdma);

void HAL_DMAEx_MUX_IRQHandler(DMA_HandleTypeDef *hdma);
/**
  * @}
  */
/**
  * @}
  */
  
/* Private macros ------------------------------------------------------------*/
/** @defgroup DMAEx_Private_Macros DMA Private Macros
  * @brief    DMAEx private macros 
  * @{
  */

#define IS_D2_DMAMUX_SYNC_SIGNAL_ID(SIGNAL_ID) ((SIGNAL_ID) <= HAL_DMAMUX1_SYNC_TIM12_TRGO)
#define IS_D3_DMAMUX_SYNC_SIGNAL_ID(SIGNAL_ID) ((SIGNAL_ID) <= HAL_DMAMUX2_SYNC_EXTI2)

#define IS_DMAMUX_SYNC_REQUEST_NUMBER(REQUEST_NUMBER) (((REQUEST_NUMBER) > 0) && ((REQUEST_NUMBER) <= 32))

#define IS_DMAMUX_SYNC_POLARITY(POLARITY) (((POLARITY) == HAL_DMAMUX_SYNC_NO_EVENT)    || \
                                           ((POLARITY) == HAL_DMAMUX_SYNC_RISING)   || \
                                           ((POLARITY) == HAL_DMAMUX_SYNC_FALLING)  || \
                                           ((POLARITY) == HAL_DMAMUX_SYNC_RISING_FALLING))

#define IS_DMAMUX_SYNC_STATE(SYNC) (((SYNC) == DISABLE)   || ((SYNC) == ENABLE))

#define IS_DMAMUX_SYNC_EVENT(EVENT) (((EVENT) == DISABLE)   || \
                                     ((EVENT) == ENABLE))

#define IS_D2_DMAMUX_REQUEST_GEN_SIGNAL_ID(SIGNAL_ID) ((SIGNAL_ID) <= HAL_DMAMUX1_REQUEST_GEN_TIM12_TRGO)
#define IS_D3_DMAMUX_REQUEST_GEN_SIGNAL_ID(SIGNAL_ID) ((SIGNAL_ID) <= HAL_DMAMUX2_REQUEST_GEN_BDMA_CH1_IT)

#define IS_DMAMUX_REQUEST_GEN_REQUEST_NUMBER(REQUEST_NUMBER) (((REQUEST_NUMBER) > 0) && ((REQUEST_NUMBER) <= 32))

#define IS_DMAMUX_REQUEST_GEN_POLARITY(POLARITY) (((POLARITY) == HAL_DMAMUX_REQUEST_GEN_NO_EVENT) || \
                                                  ((POLARITY) == HAL_DMAMUX_REQUEST_GEN_RISING)   || \
                                                  ((POLARITY) == HAL_DMAMUX_REQUEST_GEN_FALLING)   || \
                                                  ((POLARITY) == HAL_DMAMUX_REQUEST_GEN_RISING_FALLING))

/**
  * @}
  */  
         
/* Private functions ---------------------------------------------------------*/
/** @defgroup DMAEx_Private_Functions DMAEx Private Functions
  * @brief DMAEx Private functions
  * @{
  */
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

#endif /* __STM32H7xx_HAL_DMA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
