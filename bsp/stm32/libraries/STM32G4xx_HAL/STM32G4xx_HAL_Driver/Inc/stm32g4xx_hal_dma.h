/**
  ******************************************************************************
  * @file    stm32g4xx_hal_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32G4xx_HAL_DMA_H
#define __STM32G4xx_HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DMA_Exported_Types DMA Exported Types
  * @{
  */

/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct
{
  uint32_t Request;                   /*!< Specifies the request selected for the specified channel.
                                           This parameter can be a value of @ref DMA_request */

  uint32_t Direction;                 /*!< Specifies if the data will be transferred from memory to peripheral,
                                           from memory to memory or from peripheral to memory.
                                           This parameter can be a value of @ref DMA_Data_transfer_direction */

  uint32_t PeriphInc;                 /*!< Specifies whether the Peripheral address register should be incremented or not.
                                           This parameter can be a value of @ref DMA_Peripheral_incremented_mode */

  uint32_t MemInc;                    /*!< Specifies whether the memory address register should be incremented or not.
                                           This parameter can be a value of @ref DMA_Memory_incremented_mode */

  uint32_t PeriphDataAlignment;       /*!< Specifies the Peripheral data width.
                                           This parameter can be a value of @ref DMA_Peripheral_data_size */

  uint32_t MemDataAlignment;          /*!< Specifies the Memory data width.
                                           This parameter can be a value of @ref DMA_Memory_data_size */

  uint32_t Mode;                      /*!< Specifies the operation mode of the DMAy Channelx.
                                           This parameter can be a value of @ref DMA_mode
                                           @note The circular buffer mode cannot be used if the memory-to-memory
                                                 data transfer is configured on the selected Channel */

  uint32_t Priority;                  /*!< Specifies the software priority for the DMAy Channelx.
                                           This parameter can be a value of @ref DMA_Priority_level */
} DMA_InitTypeDef;

/**
  * @brief  HAL DMA State structures definition
  */
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,  /*!< DMA not yet initialized or disabled    */
  HAL_DMA_STATE_READY             = 0x01U,  /*!< DMA initialized and ready for use      */
  HAL_DMA_STATE_BUSY              = 0x02U,  /*!< DMA process is ongoing                 */
  HAL_DMA_STATE_TIMEOUT           = 0x03U,  /*!< DMA timeout state                     */
} HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Error Code structure definition
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER      = 0x00U,    /*!< Full transfer     */
  HAL_DMA_HALF_TRANSFER      = 0x01U     /*!< Half Transfer     */
} HAL_DMA_LevelCompleteTypeDef;


/**
  * @brief  HAL DMA Callback ID structure definition
  */
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID          = 0x00U,    /*!< Full transfer     */
  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,    /*!< Half transfer     */
  HAL_DMA_XFER_ERROR_CB_ID         = 0x02U,    /*!< Error             */
  HAL_DMA_XFER_ABORT_CB_ID         = 0x03U,    /*!< Abort             */
  HAL_DMA_XFER_ALL_CB_ID           = 0x04U     /*!< All               */

} HAL_DMA_CallbackIDTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef    *Instance;                                                  /*!< Register base address                */

  DMA_InitTypeDef       Init;                                                        /*!< DMA communication parameters         */

  HAL_LockTypeDef       Lock;                                                        /*!< DMA locking object                   */

  __IO HAL_DMA_StateTypeDef  State;                                                  /*!< DMA transfer state                   */

  void                  *Parent;                                                     /*!< Parent object state                  */

  void (* XferCpltCallback)(struct __DMA_HandleTypeDef *hdma);                       /*!< DMA transfer complete callback       */

  void (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma);                   /*!< DMA Half transfer complete callback  */

  void (* XferErrorCallback)(struct __DMA_HandleTypeDef *hdma);                      /*!< DMA transfer error callback          */

  void (* XferAbortCallback)(struct __DMA_HandleTypeDef *hdma);                      /*!< DMA transfer abort callback          */

  __IO uint32_t          ErrorCode;                                                  /*!< DMA Error code                       */

  DMA_TypeDef            *DmaBaseAddress;                                            /*!< DMA Channel Base Address             */

  uint32_t               ChannelIndex;                                               /*!< DMA Channel Index                    */

  DMAMUX_Channel_TypeDef           *DMAmuxChannel;                                   /*!< Register base address                */

  DMAMUX_ChannelStatus_TypeDef     *DMAmuxChannelStatus;                             /*!< DMAMUX Channels Status Base Address  */

  uint32_t                         DMAmuxChannelStatusMask;                          /*!< DMAMUX Channel Status Mask           */

  DMAMUX_RequestGen_TypeDef        *DMAmuxRequestGen;                                /*!< DMAMUX request generator Base Address */

  DMAMUX_RequestGenStatus_TypeDef  *DMAmuxRequestGenStatus;                          /*!< DMAMUX request generator Address     */

  uint32_t                         DMAmuxRequestGenStatusMask;                       /*!< DMAMUX request generator Status mask */

} DMA_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_Error_Code DMA Error Code
  * @{
  */
#define HAL_DMA_ERROR_NONE             0x00000000U    /*!< No error                              */
#define HAL_DMA_ERROR_TE               0x00000001U    /*!< Transfer error                        */
#define HAL_DMA_ERROR_NO_XFER          0x00000004U    /*!< Abort requested with no Xfer ongoing  */
#define HAL_DMA_ERROR_TIMEOUT          0x00000020U    /*!< Timeout error                         */
#define HAL_DMA_ERROR_NOT_SUPPORTED    0x00000100U    /*!< Not supported mode                    */
#define HAL_DMA_ERROR_SYNC             0x00000200U    /*!< DMAMUX sync overrun  error              */
#define HAL_DMA_ERROR_REQGEN           0x00000400U    /*!< DMAMUX request generator overrun  error */
/**
  * @}
  */

/** @defgroup DMA_request DMA request
  * @{
  */
#define DMA_REQUEST_MEM2MEM            0U  /*!< memory to memory transfer   */

#define DMA_REQUEST_GENERATOR0         1U
#define DMA_REQUEST_GENERATOR1         2U
#define DMA_REQUEST_GENERATOR2         3U
#define DMA_REQUEST_GENERATOR3         4U

#define DMA_REQUEST_ADC1               5U

#define DMA_REQUEST_DAC1_CHANNEL1      6U
#define DMA_REQUEST_DAC1_CHANNEL2      7U

#define DMA_REQUEST_TIM6_UP            8U
#define DMA_REQUEST_TIM7_UP            9U

#define DMA_REQUEST_SPI1_RX           10U
#define DMA_REQUEST_SPI1_TX           11U
#define DMA_REQUEST_SPI2_RX           12U
#define DMA_REQUEST_SPI2_TX           13U
#define DMA_REQUEST_SPI3_RX           14U
#define DMA_REQUEST_SPI3_TX           15U

#define DMA_REQUEST_I2C1_RX           16U
#define DMA_REQUEST_I2C1_TX           17U
#define DMA_REQUEST_I2C2_RX           18U
#define DMA_REQUEST_I2C2_TX           19U
#define DMA_REQUEST_I2C3_RX           20U
#define DMA_REQUEST_I2C3_TX           21U
#if defined (I2C4)
#define DMA_REQUEST_I2C4_RX           22U
#define DMA_REQUEST_I2C4_TX           23U
#endif /* I2C4 */

#define DMA_REQUEST_USART1_RX         24U
#define DMA_REQUEST_USART1_TX         25U
#define DMA_REQUEST_USART2_RX         26U
#define DMA_REQUEST_USART2_TX         27U
#define DMA_REQUEST_USART3_RX         28U
#define DMA_REQUEST_USART3_TX         29U

#define DMA_REQUEST_UART4_RX          30U
#define DMA_REQUEST_UART4_TX          31U
#if defined (UART5)
#define DMA_REQUEST_UART5_RX          32U
#define DMA_REQUEST_UART5_TX          33U
#endif /* UART5 */

#define DMA_REQUEST_LPUART1_RX        34U
#define DMA_REQUEST_LPUART1_TX        35U

#define DMA_REQUEST_ADC2              36U
#if defined (ADC3)
#define DMA_REQUEST_ADC3              37U
#endif /* ADC3 */
#if defined (ADC4)
#define DMA_REQUEST_ADC4              38U
#endif /* ADC4 */
#if defined (ADC5)
#define DMA_REQUEST_ADC5              39U
#endif /* ADC5 */

#if defined (QUADSPI)
#define DMA_REQUEST_QUADSPI           40U
#endif /* QUADSPI */

#if defined (DAC2)
#define DMA_REQUEST_DAC2_CHANNEL1     41U
#endif /* DAC2 */

#define DMA_REQUEST_TIM1_CH1          42U
#define DMA_REQUEST_TIM1_CH2          43U
#define DMA_REQUEST_TIM1_CH3          44U
#define DMA_REQUEST_TIM1_CH4          45U
#define DMA_REQUEST_TIM1_UP           46U
#define DMA_REQUEST_TIM1_TRIG         47U
#define DMA_REQUEST_TIM1_COM          48U

#define DMA_REQUEST_TIM8_CH1          49U
#define DMA_REQUEST_TIM8_CH2          50U
#define DMA_REQUEST_TIM8_CH3          51U
#define DMA_REQUEST_TIM8_CH4          52U
#define DMA_REQUEST_TIM8_UP           53U
#define DMA_REQUEST_TIM8_TRIG         54U
#define DMA_REQUEST_TIM8_COM          55U

#define DMA_REQUEST_TIM2_CH1          56U
#define DMA_REQUEST_TIM2_CH2          57U
#define DMA_REQUEST_TIM2_CH3          58U
#define DMA_REQUEST_TIM2_CH4          59U
#define DMA_REQUEST_TIM2_UP           60U

#define DMA_REQUEST_TIM3_CH1          61U
#define DMA_REQUEST_TIM3_CH2          62U
#define DMA_REQUEST_TIM3_CH3          63U
#define DMA_REQUEST_TIM3_CH4          64U
#define DMA_REQUEST_TIM3_UP           65U
#define DMA_REQUEST_TIM3_TRIG         66U

#define DMA_REQUEST_TIM4_CH1          67U
#define DMA_REQUEST_TIM4_CH2          68U
#define DMA_REQUEST_TIM4_CH3          69U
#define DMA_REQUEST_TIM4_CH4          70U
#define DMA_REQUEST_TIM4_UP           71U

#if defined (TIM5)
#define DMA_REQUEST_TIM5_CH1          72U
#define DMA_REQUEST_TIM5_CH2          73U
#define DMA_REQUEST_TIM5_CH3          74U
#define DMA_REQUEST_TIM5_CH4          75U
#define DMA_REQUEST_TIM5_UP           76U
#define DMA_REQUEST_TIM5_TRIG         77U
#endif /* TIM5 */

#define DMA_REQUEST_TIM15_CH1         78U
#define DMA_REQUEST_TIM15_UP          79U
#define DMA_REQUEST_TIM15_TRIG        80U
#define DMA_REQUEST_TIM15_COM         81U

#define DMA_REQUEST_TIM16_CH1         82U
#define DMA_REQUEST_TIM16_UP          83U
#define DMA_REQUEST_TIM17_CH1         84U
#define DMA_REQUEST_TIM17_UP          85U

#if defined (TIM20)
#define DMA_REQUEST_TIM20_CH1         86U
#define DMA_REQUEST_TIM20_CH2         87U
#define DMA_REQUEST_TIM20_CH3         88U
#define DMA_REQUEST_TIM20_CH4         89U
#define DMA_REQUEST_TIM20_UP          90U
#endif /* TIM20 */

#define DMA_REQUEST_AES_IN            91U
#define DMA_REQUEST_AES_OUT           92U

#if defined (TIM20)
#define DMA_REQUEST_TIM20_TRIG        93U
#define DMA_REQUEST_TIM20_COM         94U
#endif /* TIM20 */

#if defined (HRTIM1)
#define DMA_REQUEST_HRTIM1_M          95U
#define DMA_REQUEST_HRTIM1_A          96U
#define DMA_REQUEST_HRTIM1_B          97U
#define DMA_REQUEST_HRTIM1_C          98U
#define DMA_REQUEST_HRTIM1_D          99U
#define DMA_REQUEST_HRTIM1_E          100U
#define DMA_REQUEST_HRTIM1_F          101U
#endif /* HRTIM1 */

#define DMA_REQUEST_DAC3_CHANNEL1     102U
#define DMA_REQUEST_DAC3_CHANNEL2     103U
#if defined (DAC4)
#define DMA_REQUEST_DAC4_CHANNEL1     104U
#define DMA_REQUEST_DAC4_CHANNEL2     105U
#endif /* DAC4 */

#if defined (SPI4)
#define DMA_REQUEST_SPI4_RX           106U
#define DMA_REQUEST_SPI4_TX           107U
#endif /* SPI4 */

#define DMA_REQUEST_SAI1_A            108U
#define DMA_REQUEST_SAI1_B            109U

#define DMA_REQUEST_FMAC_READ         110U
#define DMA_REQUEST_FMAC_WRITE        111U

#define DMA_REQUEST_CORDIC_READ       112U
#define DMA_REQUEST_CORDIC_WRITE      113U

#define DMA_REQUEST_UCPD1_RX         114U
#define DMA_REQUEST_UCPD1_TX         115U

/**
  * @}
  */

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY         0x00000000U                   /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH         DMA_CCR_DIR                   /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY         DMA_CCR_MEM2MEM               /*!< Memory to memory direction     */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @{
  */
#define DMA_PINC_ENABLE        DMA_CCR_PINC              /*!< Peripheral increment mode Enable */
#define DMA_PINC_DISABLE       0x00000000U               /*!< Peripheral increment mode Disable */
/**
  * @}
  */

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @{
  */
#define DMA_MINC_ENABLE         DMA_CCR_MINC              /*!< Memory increment mode Enable  */
#define DMA_MINC_DISABLE        0x00000000U               /*!< Memory increment mode Disable */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @{
  */
#define DMA_PDATAALIGN_BYTE          0x00000000U                  /*!< Peripheral data alignment : Byte     */
#define DMA_PDATAALIGN_HALFWORD      DMA_CCR_PSIZE_0              /*!< Peripheral data alignment : HalfWord */
#define DMA_PDATAALIGN_WORD          DMA_CCR_PSIZE_1              /*!< Peripheral data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @{
  */
#define DMA_MDATAALIGN_BYTE          0x00000000U                  /*!< Memory data alignment : Byte     */
#define DMA_MDATAALIGN_HALFWORD      DMA_CCR_MSIZE_0              /*!< Memory data alignment : HalfWord */
#define DMA_MDATAALIGN_WORD          DMA_CCR_MSIZE_1              /*!< Memory data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_mode DMA mode
  * @{
  */
#define DMA_NORMAL         0x00000000U       /*!< Normal mode                  */
#define DMA_CIRCULAR       DMA_CCR_CIRC      /*!< Circular mode                */
/**
  * @}
  */

/** @defgroup DMA_Priority_level DMA Priority level
  * @{
  */
#define DMA_PRIORITY_LOW              0x00000000U              /*!< Priority level : Low       */
#define DMA_PRIORITY_MEDIUM           DMA_CCR_PL_0             /*!< Priority level : Medium    */
#define DMA_PRIORITY_HIGH             DMA_CCR_PL_1             /*!< Priority level : High      */
#define DMA_PRIORITY_VERY_HIGH        DMA_CCR_PL               /*!< Priority level : Very_High */
/**
  * @}
  */


/** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @{
  */
#define DMA_IT_TC                     DMA_CCR_TCIE
#define DMA_IT_HT                     DMA_CCR_HTIE
#define DMA_IT_TE                     DMA_CCR_TEIE
/**
  * @}
  */

/** @defgroup DMA_flag_definitions DMA flag definitions
  * @{
  */
#define DMA_FLAG_GL1                      0x00000001U
#define DMA_FLAG_TC1                      0x00000002U
#define DMA_FLAG_HT1                      0x00000004U
#define DMA_FLAG_TE1                      0x00000008U
#define DMA_FLAG_GL2                      0x00000010U
#define DMA_FLAG_TC2                      0x00000020U
#define DMA_FLAG_HT2                      0x00000040U
#define DMA_FLAG_TE2                      0x00000080U
#define DMA_FLAG_GL3                      0x00000100U
#define DMA_FLAG_TC3                      0x00000200U
#define DMA_FLAG_HT3                      0x00000400U
#define DMA_FLAG_TE3                      0x00000800U
#define DMA_FLAG_GL4                      0x00001000U
#define DMA_FLAG_TC4                      0x00002000U
#define DMA_FLAG_HT4                      0x00004000U
#define DMA_FLAG_TE4                      0x00008000U
#define DMA_FLAG_GL5                      0x00010000U
#define DMA_FLAG_TC5                      0x00020000U
#define DMA_FLAG_HT5                      0x00040000U
#define DMA_FLAG_TE5                      0x00080000U
#define DMA_FLAG_GL6                      0x00100000U
#define DMA_FLAG_TC6                      0x00200000U
#define DMA_FLAG_HT6                      0x00400000U
#define DMA_FLAG_TE6                      0x00800000U
#if defined (DMA1_Channel7)
#define DMA_FLAG_GL7                      0x01000000U
#define DMA_FLAG_TC7                      0x02000000U
#define DMA_FLAG_HT7                      0x04000000U
#define DMA_FLAG_TE7                      0x08000000U
#endif /* DMA1_Channel7 */
#if defined (DMA1_Channel8)
#define DMA_FLAG_GL8                      0x10000000U
#define DMA_FLAG_TC8                      0x20000000U
#define DMA_FLAG_HT8                      0x40000000U
#define DMA_FLAG_TE8                      0x80000000U
#endif /* DMA1_Channel8 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup DMA_Exported_Macros DMA Exported Macros
  * @{
  */

/** @brief  Reset DMA handle state.
  * @param  __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CCR |=  DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param  __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__)       ((__HANDLE__)->Instance->CCR &=  ~DMA_CCR_EN)


/* Interrupt & Flag management */

/**
  * @brief  Return the current DMA Channel transfer complete flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer complete flag index.
  */

#if defined (DMA1_Channel8)
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_TC1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_TC2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_TC3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_TC4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_TC5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TC6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel6))? DMA_FLAG_TC6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_FLAG_TC7 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel7))? DMA_FLAG_TC7 :\
   DMA_FLAG_TC8)
#elif defined (DMA1_Channel6)
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_TC1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_TC2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_TC3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_TC4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_TC5 :\
   DMA_FLAG_TC6)
#endif /* DMA1_Channel8 */

/**
  * @brief  Return the current DMA Channel half transfer complete flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified half transfer complete flag index.
  */
#if defined (DMA1_Channel8)
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_HT1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_HT2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_HT3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_HT4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_HT5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_HT6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel6))? DMA_FLAG_HT6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_FLAG_HT7 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel7))? DMA_FLAG_HT7 :\
   DMA_FLAG_HT8)
#elif defined (DMA1_Channel6)
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_HT1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_HT2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_HT3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_HT4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_HT5 :\
   DMA_FLAG_HT6)
#endif /* DMA1_Channel8 */

/**
  * @brief  Return the current DMA Channel transfer error flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined (DMA1_Channel8)
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_TE1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_TE2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_TE3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_TE4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_TE5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TE6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel6))? DMA_FLAG_TE6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_FLAG_TE7 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel7))? DMA_FLAG_TE7 :\
   DMA_FLAG_TE8)
#elif defined (DMA1_Channel6)
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_TE1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_TE2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_TE3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_TE4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_TE5 :\
   DMA_FLAG_TE6)
#endif /* DMA1_Channel8 */

/**
  * @brief  Return the current DMA Channel Global interrupt flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined (DMA1_Channel8)
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__)\
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_ISR_GIF1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_ISR_GIF1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_ISR_GIF2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_ISR_GIF2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_ISR_GIF3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_ISR_GIF3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_ISR_GIF4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_ISR_GIF4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_ISR_GIF5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_ISR_GIF5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_ISR_GIF6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel6))? DMA_ISR_GIF6 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_ISR_GIF7 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel7))? DMA_ISR_GIF7 :\
   DMA_ISR_GIF8)
#elif defined (DMA1_Channel6)
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__)\
  (((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_ISR_GIF1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_ISR_GIF1 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_ISR_GIF2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_ISR_GIF2 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_ISR_GIF3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_ISR_GIF3 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_ISR_GIF4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_ISR_GIF4 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_ISR_GIF5 :\
   ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_ISR_GIF5 :\
   DMA_ISR_GIF6)
#endif /* DMA1_Channel8 */

/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__ DMA handle
  * @param  __FLAG__ Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx  Transfer complete flag
  *            @arg DMA_FLAG_HTx  Half transfer complete flag
  *            @arg DMA_FLAG_TEx  Transfer error flag
  *            @arg DMA_FLAG_GLx  Global interrupt flag
  *         Where x can be from 1 to 8 to select the DMA Channel x flag.
  * @retval The state of FLAG (SET or RESET).
  */
#if defined (DMA1_Channel8)
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) (((uint32_t)((__HANDLE__)->Instance) > ((uint32_t)DMA1_Channel8))? \
                                                  (DMA2->ISR & (__FLAG__)) : (DMA1->ISR & (__FLAG__)))
#elif defined (DMA1_Channel6)
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) (((uint32_t)((__HANDLE__)->Instance) > ((uint32_t)DMA1_Channel6))? \
                                                  (DMA2->ISR & (__FLAG__)) : (DMA1->ISR & (__FLAG__)))
#endif /* DMA1_Channel8 */

/**
  * @brief  Clear the DMA Channel pending flags.
  * @param  __HANDLE__ DMA handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx  Transfer complete flag
  *            @arg DMA_FLAG_HTx  Half transfer complete flag
  *            @arg DMA_FLAG_TEx  Transfer error flag
  *            @arg DMA_FLAG_GLx  Global interrupt flag
  *         Where x can be from 1 to 8 to select the DMA Channel x flag.
  * @retval None
  */
#if defined (DMA1_Channel8)
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (((uint32_t)((__HANDLE__)->Instance) > ((uint32_t)DMA1_Channel8))? \
                                                    (DMA2->IFCR = (__FLAG__)) : (DMA1->IFCR = (__FLAG__)))
#else
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (((uint32_t)((__HANDLE__)->Instance) > ((uint32_t)DMA1_Channel6))? \
                                                    (DMA2->IFCR = (__FLAG__)) : (DMA1->IFCR = (__FLAG__)))
#endif /* DMA1_Channel8 */

/**
  * @brief  Enable the specified DMA Channel interrupts.
  * @param  __HANDLE__ DMA handle
  * @param __INTERRUPT__ specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC  Transfer complete interrupt mask
  *            @arg DMA_IT_HT  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA Channel interrupts.
  * @param  __HANDLE__ DMA handle
  * @param __INTERRUPT__ specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC  Transfer complete interrupt mask
  *            @arg DMA_IT_HT  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified DMA Channel interrupt is enabled or not.
  * @param  __HANDLE__ DMA handle
  * @param  __INTERRUPT__ specifies the DMA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA_IT_TC  Transfer complete interrupt mask
  *            @arg DMA_IT_HT  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE  Transfer error interrupt mask
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @brief  Return the number of remaining data units in the current DMA Channel transfer.
  * @param  __HANDLE__ DMA handle
  * @retval The number of remaining data units in the current DMA Channel transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNDTR)

/**
  * @}
  */

/* Include DMA HAL Extension module */
#include "stm32g4xx_hal_dma_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @addtogroup DMA_Exported_Functions
  * @{
  */

/** @addtogroup DMA_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress,
                                   uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel,
                                          uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);

/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1U) && ((SIZE) < 0x40000U))

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PINC_ENABLE) || \
                                            ((STATE) == DMA_PINC_DISABLE))

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MINC_ENABLE)  || \
                                        ((STATE) == DMA_MINC_DISABLE))

#define IS_DMA_ALL_REQUEST(REQUEST)    ((REQUEST) <= DMA_REQUEST_UCPD1_TX)

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PDATAALIGN_BYTE)     || \
                                           ((SIZE) == DMA_PDATAALIGN_HALFWORD) || \
                                           ((SIZE) == DMA_PDATAALIGN_WORD))

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MDATAALIGN_BYTE)     || \
                                       ((SIZE) == DMA_MDATAALIGN_HALFWORD) || \
                                       ((SIZE) == DMA_MDATAALIGN_WORD ))

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_CIRCULAR))

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_LOW )   || \
                                   ((PRIORITY) == DMA_PRIORITY_MEDIUM) || \
                                   ((PRIORITY) == DMA_PRIORITY_HIGH)   || \
                                   ((PRIORITY) == DMA_PRIORITY_VERY_HIGH))

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32G4xx_HAL_DMA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
