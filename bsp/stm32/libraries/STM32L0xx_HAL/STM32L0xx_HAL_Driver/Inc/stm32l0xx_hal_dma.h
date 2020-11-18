/**
  ******************************************************************************
  * @file    stm32l0xx_hal_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics.
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
#ifndef STM32L0xx_HAL_DMA_H
#define STM32L0xx_HAL_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
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
  HAL_DMA_STATE_TIMEOUT           = 0x03U,  /*!< DMA timeout state                      */
}HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Error Code structure definition
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER      = 0x00U,    /*!< Full transfer     */
  HAL_DMA_HALF_TRANSFER      = 0x01U     /*!< Half Transfer     */
}HAL_DMA_LevelCompleteTypeDef;


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
}HAL_DMA_CallbackIDTypeDef;

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

  void                  (* XferCpltCallback)(struct __DMA_HandleTypeDef * hdma);     /*!< DMA transfer complete callback       */

  void                  (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef * hdma); /*!< DMA Half transfer complete callback  */

  void                  (* XferErrorCallback)(struct __DMA_HandleTypeDef * hdma);    /*!< DMA transfer error callback          */

  void                  (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);   /*!< DMA transfer abort callback          */

  __IO uint32_t          ErrorCode;                                                  /*!< DMA Error code                       */

  DMA_TypeDef            *DmaBaseAddress;                                            /*!< DMA Channel Base Address             */

  uint32_t               ChannelIndex;                                               /*!< DMA Channel Index                    */

}DMA_HandleTypeDef;

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
#define HAL_DMA_ERROR_NONE                 0x00000000U    /*!< No error                                */
#define HAL_DMA_ERROR_TE                   0x00000001U    /*!< Transfer error                          */
#define HAL_DMA_ERROR_NO_XFER              0x00000004U    /*!< Abort requested with no Xfer ongoing    */
#define HAL_DMA_ERROR_TIMEOUT              0x00000020U    /*!< Timeout error                           */
#define HAL_DMA_ERROR_NOT_SUPPORTED        0x00000100U    /*!< Not supported mode                      */

/**
  * @}
  */

/** @defgroup DMA_request DMA request
  * @{
  */

#if defined (STM32L010x4) || defined (STM32L010x6) || defined (STM32L010x8) || defined (STM32L010xC)

#define DMA_REQUEST_0                     0U
#define DMA_REQUEST_1                     1U
#define DMA_REQUEST_4                     4U
#define DMA_REQUEST_5                     5U
#define DMA_REQUEST_6                     6U
#define DMA_REQUEST_8                     8U

#define IS_DMA_ALL_REQUEST(REQUEST) (((REQUEST) == DMA_REQUEST_0) || \
                                     ((REQUEST) == DMA_REQUEST_1) || \
                                     ((REQUEST) == DMA_REQUEST_4) || \
                                     ((REQUEST) == DMA_REQUEST_5) || \
                                     ((REQUEST) == DMA_REQUEST_6) || \
                                     ((REQUEST) == DMA_REQUEST_8))

/* STM32L010x4 || STM32L010x6 || STM32L010x8 || STM32L010xC */

#elif defined (STM32L021xx) || defined (STM32L041xx) || defined (STM32L061xx) || defined (STM32L062xx) || defined (STM32L063xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)

#define DMA_REQUEST_0                     0U
#define DMA_REQUEST_1                     1U
#define DMA_REQUEST_2                     2U
#define DMA_REQUEST_3                     3U
#define DMA_REQUEST_4                     4U
#define DMA_REQUEST_5                     5U
#define DMA_REQUEST_6                     6U
#define DMA_REQUEST_7                     7U
#define DMA_REQUEST_8                     8U
#define DMA_REQUEST_9                     9U
#define DMA_REQUEST_10                   10U
#define DMA_REQUEST_11                   11U  /* AES product only */
#define DMA_REQUEST_12                   12U
#define DMA_REQUEST_13                   13U
#define DMA_REQUEST_14                   14U
#define DMA_REQUEST_15                   15U

#define IS_DMA_ALL_REQUEST(REQUEST) (((REQUEST) == DMA_REQUEST_0) || \
                                     ((REQUEST) == DMA_REQUEST_1) || \
                                     ((REQUEST) == DMA_REQUEST_2) || \
                                     ((REQUEST) == DMA_REQUEST_3) || \
                                     ((REQUEST) == DMA_REQUEST_4) || \
                                     ((REQUEST) == DMA_REQUEST_5) || \
                                     ((REQUEST) == DMA_REQUEST_6) || \
                                     ((REQUEST) == DMA_REQUEST_7) || \
                                     ((REQUEST) == DMA_REQUEST_8) || \
                                     ((REQUEST) == DMA_REQUEST_9) || \
                                     ((REQUEST) == DMA_REQUEST_10) || \
                                     ((REQUEST) == DMA_REQUEST_11) || \
                                     ((REQUEST) == DMA_REQUEST_12) || \
                                     ((REQUEST) == DMA_REQUEST_13) || \
                                     ((REQUEST) == DMA_REQUEST_14) || \
                                     ((REQUEST) == DMA_REQUEST_15))

/* (STM32L021xx) || (STM32L041xx) || (STM32L061xx) || (STM32L062xx) || (STM32L063xx) || (STM32L081xx) || (STM32L082xx) || (STM32L083xx) */

#else

#define DMA_REQUEST_0                     0U
#define DMA_REQUEST_1                     1U
#define DMA_REQUEST_2                     2U
#define DMA_REQUEST_3                     3U
#define DMA_REQUEST_4                     4U
#define DMA_REQUEST_5                     5U
#define DMA_REQUEST_6                     6U
#define DMA_REQUEST_7                     7U
#define DMA_REQUEST_8                     8U
#define DMA_REQUEST_9                     9U
#define DMA_REQUEST_10                   10U
#define DMA_REQUEST_12                   12U
#define DMA_REQUEST_13                   13U
#define DMA_REQUEST_14                   14U
#define DMA_REQUEST_15                   15U

#define IS_DMA_ALL_REQUEST(REQUEST) (((REQUEST) == DMA_REQUEST_0) || \
                                     ((REQUEST) == DMA_REQUEST_1) || \
                                     ((REQUEST) == DMA_REQUEST_2) || \
                                     ((REQUEST) == DMA_REQUEST_3) || \
                                     ((REQUEST) == DMA_REQUEST_4) || \
                                     ((REQUEST) == DMA_REQUEST_5) || \
                                     ((REQUEST) == DMA_REQUEST_6) || \
                                     ((REQUEST) == DMA_REQUEST_7) || \
                                     ((REQUEST) == DMA_REQUEST_8) || \
                                     ((REQUEST) == DMA_REQUEST_9) || \
                                     ((REQUEST) == DMA_REQUEST_10) || \
                                     ((REQUEST) == DMA_REQUEST_12) || \
                                     ((REQUEST) == DMA_REQUEST_13) || \
                                     ((REQUEST) == DMA_REQUEST_14) || \
                                     ((REQUEST) == DMA_REQUEST_15))

#endif /* (STM32L031xx) || (STM32L051xx) || (STM32L052xx) || (STM32L053xx) || (STM32L071xx) || (STM32L072xx) || (STM32L073xx) */



/**
  * @}
  */

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY         0x00000000U        /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH         DMA_CCR_DIR        /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY         DMA_CCR_MEM2MEM    /*!< Memory to memory direction     */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @{
  */
#define DMA_PINC_ENABLE              DMA_CCR_PINC  /*!< Peripheral increment mode Enable */
#define DMA_PINC_DISABLE             0x00000000U   /*!< Peripheral increment mode Disable */
/**
  * @}
  */

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @{
  */
#define DMA_MINC_ENABLE              DMA_CCR_MINC   /*!< Memory increment mode Enable  */
#define DMA_MINC_DISABLE             0x00000000U    /*!< Memory increment mode Disable */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @{
  */
#define DMA_PDATAALIGN_BYTE          0x00000000U     /*!< Peripheral data alignment : Byte     */
#define DMA_PDATAALIGN_HALFWORD      DMA_CCR_PSIZE_0 /*!< Peripheral data alignment : HalfWord */
#define DMA_PDATAALIGN_WORD          DMA_CCR_PSIZE_1 /*!< Peripheral data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @{
  */
#define DMA_MDATAALIGN_BYTE          0x00000000U     /*!< Memory data alignment : Byte     */
#define DMA_MDATAALIGN_HALFWORD      DMA_CCR_MSIZE_0 /*!< Memory data alignment : HalfWord */
#define DMA_MDATAALIGN_WORD          DMA_CCR_MSIZE_1 /*!< Memory data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_mode DMA mode
  * @{
  */
#define DMA_NORMAL                   0x00000000U     /*!< Normal mode                  */
#define DMA_CIRCULAR                 DMA_CCR_CIRC    /*!< Circular mode                */
/**
  * @}
  */

/** @defgroup DMA_Priority_level DMA Priority level
  * @{
  */
#define DMA_PRIORITY_LOW             0x00000000U      /*!< Priority level : Low       */
#define DMA_PRIORITY_MEDIUM          DMA_CCR_PL_0     /*!< Priority level : Medium    */
#define DMA_PRIORITY_HIGH            DMA_CCR_PL_1     /*!< Priority level : High      */
#define DMA_PRIORITY_VERY_HIGH       DMA_CCR_PL       /*!< Priority level : Very_High */
/**
  * @}
  */


/** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @{
  */
#define DMA_IT_TC                         DMA_CCR_TCIE
#define DMA_IT_HT                         DMA_CCR_HTIE
#define DMA_IT_TE                         DMA_CCR_TEIE
/**
  * @}
  */

/** @defgroup DMA_flag_definitions DMA flag definitions
  * @{
  */
#define DMA_FLAG_GL1                      DMA_ISR_GIF1
#define DMA_FLAG_TC1                      DMA_ISR_TCIF1
#define DMA_FLAG_HT1                      DMA_ISR_HTIF1
#define DMA_FLAG_TE1                      DMA_ISR_TEIF1
#define DMA_FLAG_GL2                      DMA_ISR_GIF2
#define DMA_FLAG_TC2                      DMA_ISR_TCIF2
#define DMA_FLAG_HT2                      DMA_ISR_HTIF2
#define DMA_FLAG_TE2                      DMA_ISR_TEIF2
#define DMA_FLAG_GL3                      DMA_ISR_GIF3
#define DMA_FLAG_TC3                      DMA_ISR_TCIF3
#define DMA_FLAG_HT3                      DMA_ISR_HTIF3
#define DMA_FLAG_TE3                      DMA_ISR_TEIF3
#define DMA_FLAG_GL4                      DMA_ISR_GIF4
#define DMA_FLAG_TC4                      DMA_ISR_TCIF4
#define DMA_FLAG_HT4                      DMA_ISR_HTIF4
#define DMA_FLAG_TE4                      DMA_ISR_TEIF4
#define DMA_FLAG_GL5                      DMA_ISR_GIF5
#define DMA_FLAG_TC5                      DMA_ISR_TCIF5
#define DMA_FLAG_HT5                      DMA_ISR_HTIF5
#define DMA_FLAG_TE5                      DMA_ISR_TEIF5
#define DMA_FLAG_GL6                      DMA_ISR_GIF6
#define DMA_FLAG_TC6                      DMA_ISR_TCIF6
#define DMA_FLAG_HT6                      DMA_ISR_HTIF6
#define DMA_FLAG_TE6                      DMA_ISR_TEIF6
#define DMA_FLAG_GL7                      DMA_ISR_GIF7
#define DMA_FLAG_TC7                      DMA_ISR_TCIF7
#define DMA_FLAG_HT7                      DMA_ISR_HTIF7
#define DMA_FLAG_TE7                      DMA_ISR_TEIF7
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
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CCR |=  DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__)       ((__HANDLE__)->Instance->CCR &=  ~DMA_CCR_EN)


/* Interrupt & Flag management */

/**
  * @brief  Return the current DMA Channel transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */

#if defined (STM32L010x4) || defined (STM32L011xx) || defined (STM32L021xx)
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
 DMA_FLAG_TC5)
#else
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TC6 :\
   DMA_FLAG_TC7)
#endif
/**
  * @brief  Return the current DMA Channel half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */
#if defined (STM32L010x4) || defined (STM32L011xx) || defined (STM32L021xx)
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
 DMA_FLAG_HT5)
#else
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_HT6 :\
   DMA_FLAG_HT7)
#endif
/**
  * @brief  Returns the current DMA Channel transfer error flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined (STM32L010x4) || defined (STM32L011xx) || defined (STM32L021xx)
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
 DMA_FLAG_TE5)
#else
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TE6 :\
   DMA_FLAG_TE7)
#endif
/**
  * @brief  Returns the current DMA Channel Global interrupt flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined (STM32L010x4) || defined (STM32L011xx) || defined (STM32L021xx)
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_ISR_GIF1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_ISR_GIF2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_ISR_GIF3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_ISR_GIF4 :\
   DMA_ISR_GIF5)
#else
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_ISR_GIF1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_ISR_GIF2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_ISR_GIF3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_ISR_GIF4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_ISR_GIF5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_ISR_GIF6 :\
   DMA_ISR_GIF7)
#endif
/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__ DMA handle
  * @param  __FLAG__ Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCIFx:  Transfer complete flag
  *            @arg DMA_FLAG_HTIFx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEIFx:  Transfer error flag
  *            @arg DMA_ISR_GIFx: Global interrupt flag
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Channel flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) (DMA1->ISR & (__FLAG__))

/**
  * @brief  Clears the DMA Channel pending flags.
  * @param  __HANDLE__ DMA handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *            @arg DMA_FLAG_GLx:  Global interrupt flag
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Channel flag.
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (DMA1->IFCR = (__FLAG__))

/**
  * @brief  Enable the specified DMA Channel interrupts.
  * @param  __HANDLE__: DMA handle
  * @param __INTERRUPT__: specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA Channel interrupts.
  * @param  __HANDLE__: DMA handle
  * @param __INTERRUPT__: specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified DMA Channel interrupt is enabled or not.
  * @param  __HANDLE__: DMA handle
  * @param  __INTERRUPT__: specifies the DMA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @brief  Return the number of remaining data units in the current DMA Channel transfer.
  * @param  __HANDLE__: DMA handle
  * @retval The number of remaining data units in the current DMA Channel transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNDTR)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup DMA_Exported_Functions
  * @{
  */

/** @addtogroup DMA_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit (DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)( DMA_HandleTypeDef * _hdma));
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
/* Define the private group ***********************************/
/**************************************************************/
/** @defgroup DMA_Private DMA Private
  * @{
  */

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1U) && ((SIZE) < 0x10000U))

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PINC_ENABLE) || \
                                            ((STATE) == DMA_PINC_DISABLE))

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MINC_ENABLE)  || \
                                        ((STATE) == DMA_MINC_DISABLE))

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
/**************************************************************/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32L0xx_HAL_DMA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
