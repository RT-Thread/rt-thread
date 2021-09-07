/**
  ******************************************************************************
  * @file    stm32g0xx_hal_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
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
#ifndef STM32G0xx_HAL_DMA_H
#define STM32G0xx_HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"
#include "stm32g0xx_ll_dma.h"

/** @addtogroup STM32G0xx_HAL_Driver
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
  uint32_t Request;               /*!< Specifies the request selected for the specified channel.
                                       This parameter can be a value of @ref DMA_request */

  uint32_t Direction;             /*!< Specifies if the data will be transferred from memory to peripheral,
                                       from memory to memory or from peripheral to memory.
                                       This parameter can be a value of @ref DMA_Data_transfer_direction */

  uint32_t PeriphInc;             /*!< Specifies whether the Peripheral address register should be incremented or not.
                                       This parameter can be a value of @ref DMA_Peripheral_incremented_mode */

  uint32_t MemInc;                /*!< Specifies whether the memory address register should be incremented or not.
                                       This parameter can be a value of @ref DMA_Memory_incremented_mode */

  uint32_t PeriphDataAlignment;   /*!< Specifies the Peripheral data width.
                                       This parameter can be a value of @ref DMA_Peripheral_data_size */

  uint32_t MemDataAlignment;      /*!< Specifies the Memory data width.
                                       This parameter can be a value of @ref DMA_Memory_data_size */

  uint32_t Mode;                  /*!< Specifies the operation mode of the DMAy Channelx.
                                       This parameter can be a value of @ref DMA_mode
                                       @note The circular buffer mode cannot be used if the memory-to-memory
                                             data transfer is configured on the selected Channel */

  uint32_t Priority;              /*!< Specifies the software priority for the DMAy Channelx.
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
} HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Error Code structure definition
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER           = 0x00U,  /*!< Full transfer     */
  HAL_DMA_HALF_TRANSFER           = 0x01U   /*!< Half Transfer     */
} HAL_DMA_LevelCompleteTypeDef;

/**
  * @brief  HAL DMA Callback ID structure definition
  */
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID          = 0x00U,  /*!< Full transfer    */
  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,  /*!< Half transfer    */
  HAL_DMA_XFER_ERROR_CB_ID         = 0x02U,  /*!< Error            */
  HAL_DMA_XFER_ABORT_CB_ID         = 0x03U,  /*!< Abort            */
  HAL_DMA_XFER_ALL_CB_ID           = 0x04U   /*!< All              */

} HAL_DMA_CallbackIDTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef             *Instance;                          /*!< Register base address                 */

  DMA_InitTypeDef                 Init;                               /*!< DMA communication parameters          */

  HAL_LockTypeDef                 Lock;                               /*!< DMA locking object                    */

  __IO HAL_DMA_StateTypeDef       State;                              /*!< DMA transfer state                    */

  void   *Parent;                                                     /*!< Parent object state                   */

  void (* XferCpltCallback)(struct __DMA_HandleTypeDef *hdma);        /*!< DMA transfer complete callback        */

  void (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA Half transfer complete callback   */

  void (* XferErrorCallback)(struct __DMA_HandleTypeDef *hdma);       /*!< DMA transfer error callback           */

  void (* XferAbortCallback)(struct __DMA_HandleTypeDef *hdma);       /*!< DMA transfer abort callback           */

  __IO uint32_t                   ErrorCode;                          /*!< DMA Error code                        */

#if defined(DMA2)
  DMA_TypeDef            *DmaBaseAddress;                             /*!< DMA Channel Base Address              */

#endif
  uint32_t                        ChannelIndex;                       /*!< DMA Channel Index                     */

  DMAMUX_Channel_TypeDef           *DMAmuxChannel;                    /*!< Register base address                 */

  DMAMUX_ChannelStatus_TypeDef     *DMAmuxChannelStatus;              /*!< DMAMUX Channels Status Base Address   */

  uint32_t                         DMAmuxChannelStatusMask;           /*!< DMAMUX Channel Status Mask            */

  DMAMUX_RequestGen_TypeDef        *DMAmuxRequestGen;                 /*!< DMAMUX request generator Base Address */

  DMAMUX_RequestGenStatus_TypeDef  *DMAmuxRequestGenStatus;           /*!< DMAMUX request generator Address      */

  uint32_t                         DMAmuxRequestGenStatusMask;        /*!< DMAMUX request generator Status mask  */
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
#define HAL_DMA_ERROR_NONE           0x00000000U       /*!< No error                                */
#define HAL_DMA_ERROR_TE             0x00000001U       /*!< Transfer error                          */
#define HAL_DMA_ERROR_NO_XFER        0x00000004U       /*!< Abort requested with no Xfer ongoing    */
#define HAL_DMA_ERROR_TIMEOUT        0x00000020U       /*!< Timeout error                           */
#define HAL_DMA_ERROR_PARAM          0x00000040U       /*!< Parameter error                         */
#define HAL_DMA_ERROR_BUSY           0x00000080U       /*!< DMA Busy error                          */
#define HAL_DMA_ERROR_NOT_SUPPORTED  0x00000100U       /*!< Not supported mode                      */
#define HAL_DMA_ERROR_SYNC           0x00000200U       /*!< DMAMUX sync overrun error               */
#define HAL_DMA_ERROR_REQGEN         0x00000400U       /*!< DMAMUX request generator overrun error  */

/**
  * @}
  */

/** @defgroup DMA_request DMA request
  * @{
  */
#define DMA_REQUEST_MEM2MEM          LL_DMAMUX_REQ_MEM2MEM        /*!< memory to memory transfer  */
#define DMA_REQUEST_GENERATOR0       LL_DMAMUX_REQ_GENERATOR0     /*!< DMAMUX request generator 0 */
#define DMA_REQUEST_GENERATOR1       LL_DMAMUX_REQ_GENERATOR1     /*!< DMAMUX request generator 1 */
#define DMA_REQUEST_GENERATOR2       LL_DMAMUX_REQ_GENERATOR2     /*!< DMAMUX request generator 2 */
#define DMA_REQUEST_GENERATOR3       LL_DMAMUX_REQ_GENERATOR3     /*!< DMAMUX request generator 3 */
#define DMA_REQUEST_ADC1             LL_DMAMUX_REQ_ADC1           /*!< DMAMUX ADC1 request        */
#if defined(AES)
#define DMA_REQUEST_AES_IN           LL_DMAMUX_REQ_AES_IN         /*!< DMAMUX AES_IN request      */
#define DMA_REQUEST_AES_OUT          LL_DMAMUX_REQ_AES_OUT        /*!< DMAMUX AES_OUT request     */
#endif
#if defined(DAC1)
#define DMA_REQUEST_DAC1_CH1         LL_DMAMUX_REQ_DAC1_CH1       /*!< DMAMUX DAC_CH1 request     */
#define DMA_REQUEST_DAC1_CH2         LL_DMAMUX_REQ_DAC1_CH2       /*!< DMAMUX DAC_CH2 request     */
#endif
#define DMA_REQUEST_I2C1_RX          LL_DMAMUX_REQ_I2C1_RX        /*!< DMAMUX I2C1 RX request     */
#define DMA_REQUEST_I2C1_TX          LL_DMAMUX_REQ_I2C1_TX        /*!< DMAMUX I2C1 TX request     */
#define DMA_REQUEST_I2C2_RX          LL_DMAMUX_REQ_I2C2_RX        /*!< DMAMUX I2C2 RX request     */
#define DMA_REQUEST_I2C2_TX          LL_DMAMUX_REQ_I2C2_TX        /*!< DMAMUX I2C2 TX request     */
#if defined(LPUART1)
#define DMA_REQUEST_LPUART1_RX       LL_DMAMUX_REQ_LPUART1_RX     /*!< DMAMUX LPUART1 RX request  */
#define DMA_REQUEST_LPUART1_TX       LL_DMAMUX_REQ_LPUART1_TX     /*!< DMAMUX LPUART1 TX request  */
#endif
#define DMA_REQUEST_SPI1_RX          LL_DMAMUX_REQ_SPI1_RX        /*!< DMAMUX SPI1 RX request     */
#define DMA_REQUEST_SPI1_TX          LL_DMAMUX_REQ_SPI1_TX        /*!< DMAMUX SPI1 TX request     */
#define DMA_REQUEST_SPI2_RX          LL_DMAMUX_REQ_SPI2_RX        /*!< DMAMUX SPI2 RX request     */
#define DMA_REQUEST_SPI2_TX          LL_DMAMUX_REQ_SPI2_TX        /*!< DMAMUX SPI2 TX request     */
#define DMA_REQUEST_TIM1_CH1         LL_DMAMUX_REQ_TIM1_CH1       /*!< DMAMUX TIM1 CH1 request    */
#define DMA_REQUEST_TIM1_CH2         LL_DMAMUX_REQ_TIM1_CH2       /*!< DMAMUX TIM1 CH2 request    */
#define DMA_REQUEST_TIM1_CH3         LL_DMAMUX_REQ_TIM1_CH3       /*!< DMAMUX TIM1 CH3 request    */
#define DMA_REQUEST_TIM1_CH4         LL_DMAMUX_REQ_TIM1_CH4       /*!< DMAMUX TIM1 CH4 request    */
#define DMA_REQUEST_TIM1_TRIG_COM    LL_DMAMUX_REQ_TIM1_TRIG_COM  /*!< DMAMUX TIM1 TRIG COM request */
#define DMA_REQUEST_TIM1_UP          LL_DMAMUX_REQ_TIM1_UP        /*!< DMAMUX TIM1 UP request     */
#if defined(TIM2)
#define DMA_REQUEST_TIM2_CH1         LL_DMAMUX_REQ_TIM2_CH1       /*!< DMAMUX TIM2 CH1 request    */
#define DMA_REQUEST_TIM2_CH2         LL_DMAMUX_REQ_TIM2_CH2       /*!< DMAMUX TIM2 CH2 request    */
#define DMA_REQUEST_TIM2_CH3         LL_DMAMUX_REQ_TIM2_CH3       /*!< DMAMUX TIM2 CH3 request    */
#define DMA_REQUEST_TIM2_CH4         LL_DMAMUX_REQ_TIM2_CH4       /*!< DMAMUX TIM2 CH4 request    */
#define DMA_REQUEST_TIM2_TRIG        LL_DMAMUX_REQ_TIM2_TRIG      /*!< DMAMUX TIM2 TRIG request   */
#define DMA_REQUEST_TIM2_UP          LL_DMAMUX_REQ_TIM2_UP        /*!< DMAMUX TIM2 UP request     */
#endif
#define DMA_REQUEST_TIM3_CH1         LL_DMAMUX_REQ_TIM3_CH1       /*!< DMAMUX TIM3 CH1 request    */
#define DMA_REQUEST_TIM3_CH2         LL_DMAMUX_REQ_TIM3_CH2       /*!< DMAMUX TIM3 CH2 request    */
#define DMA_REQUEST_TIM3_CH3         LL_DMAMUX_REQ_TIM3_CH3       /*!< DMAMUX TIM3 CH3 request    */
#define DMA_REQUEST_TIM3_CH4         LL_DMAMUX_REQ_TIM3_CH4       /*!< DMAMUX TIM3 CH4 request    */
#define DMA_REQUEST_TIM3_TRIG        LL_DMAMUX_REQ_TIM3_TRIG      /*!< DMAMUX TIM3 TRIG request   */
#define DMA_REQUEST_TIM3_UP          LL_DMAMUX_REQ_TIM3_UP        /*!< DMAMUX TIM3 UP request     */
#if defined(TIM6)
#define DMA_REQUEST_TIM6_UP          LL_DMAMUX_REQ_TIM6_UP        /*!< DMAMUX TIM6 UP request     */
#endif
#if defined(TIM7)
#define DMA_REQUEST_TIM7_UP          LL_DMAMUX_REQ_TIM7_UP        /*!< DMAMUX TIM7 UP request     */
#endif
#if defined(TIM15)
#define DMA_REQUEST_TIM15_CH1        LL_DMAMUX_REQ_TIM15_CH1      /*!< DMAMUX TIM15 CH1 request   */
#define DMA_REQUEST_TIM15_CH2        LL_DMAMUX_REQ_TIM15_CH2      /*!< DMAMUX TIM15 CH2 request   */
#define DMA_REQUEST_TIM15_TRIG_COM   LL_DMAMUX_REQ_TIM15_TRIG_COM /*!< DMAMUX TIM15 TRIG COM request */
#define DMA_REQUEST_TIM15_UP         LL_DMAMUX_REQ_TIM15_UP       /*!< DMAMUX TIM15 UP request    */
#endif
#define DMA_REQUEST_TIM16_CH1        LL_DMAMUX_REQ_TIM16_CH1      /*!< DMAMUX TIM16 CH1 request   */
#define DMA_REQUEST_TIM16_COM        LL_DMAMUX_REQ_TIM16_COM      /*!< DMAMUX TIM16 COM request   */
#define DMA_REQUEST_TIM16_UP         LL_DMAMUX_REQ_TIM16_UP       /*!< DMAMUX TIM16 UP request    */
#define DMA_REQUEST_TIM17_CH1        LL_DMAMUX_REQ_TIM17_CH1      /*!< DMAMUX TIM17 CH1 request   */
#define DMA_REQUEST_TIM17_COM        LL_DMAMUX_REQ_TIM17_COM      /*!< DMAMUX TIM17 COM request   */
#define DMA_REQUEST_TIM17_UP         LL_DMAMUX_REQ_TIM17_UP       /*!< DMAMUX TIM17 UP request    */
#define DMA_REQUEST_USART1_RX        LL_DMAMUX_REQ_USART1_RX      /*!< DMAMUX USART1 RX request  */
#define DMA_REQUEST_USART1_TX        LL_DMAMUX_REQ_USART1_TX      /*!< DMAMUX USART1 TX request  */
#define DMA_REQUEST_USART2_RX        LL_DMAMUX_REQ_USART2_RX      /*!< DMAMUX USART2 RX request  */
#define DMA_REQUEST_USART2_TX        LL_DMAMUX_REQ_USART2_TX      /*!< DMAMUX USART2 TX request  */
#if defined(USART3)
#define DMA_REQUEST_USART3_RX        LL_DMAMUX_REQ_USART3_RX      /*!< DMAMUX USART3 RX request  */
#define DMA_REQUEST_USART3_TX        LL_DMAMUX_REQ_USART3_TX      /*!< DMAMUX USART3 TX request  */
#endif
#if defined(USART4)
#define DMA_REQUEST_USART4_RX        LL_DMAMUX_REQ_USART4_RX      /*!< DMAMUX USART4 RX request  */
#define DMA_REQUEST_USART4_TX        LL_DMAMUX_REQ_USART4_TX      /*!< DMAMUX USART4 TX request  */
#endif
#if defined(UCPD1)
#define DMA_REQUEST_UCPD1_RX         LL_DMAMUX_REQ_UCPD1_RX       /*!< DMAMUX UCPD1 RX request  */
#define DMA_REQUEST_UCPD1_TX         LL_DMAMUX_REQ_UCPD1_TX       /*!< DMAMUX UCPD1 TX request  */
#endif
#if defined(UCPD2)
#define DMA_REQUEST_UCPD2_RX         LL_DMAMUX_REQ_UCPD2_RX       /*!< DMAMUX UCPD2 RX request  */
#define DMA_REQUEST_UCPD2_TX         LL_DMAMUX_REQ_UCPD2_TX       /*!< DMAMUX UCPD2 TX request  */
#endif
                                          
#if defined(I2C3)
#define DMA_REQUEST_I2C3_RX          LL_DMAMUX_REQ_I2C3_RX        /*!< DMAMUX I2C3 RX request  */
#define DMA_REQUEST_I2C3_TX          LL_DMAMUX_REQ_I2C3_TX        /*!< DMAMUX I2C3 TX request  */
#endif

#if defined(LPUART2)
#define DMA_REQUEST_LPUART2_RX       LL_DMAMUX_REQ_LPUART2_RX     /*!< DMAMUX LPUART2 RX request  */
#define DMA_REQUEST_LPUART2_TX       LL_DMAMUX_REQ_LPUART2_TX     /*!< DMAMUX LPUART2 TX request  */
#endif

#if defined(SPI3)
#define DMA_REQUEST_SPI3_RX          LL_DMAMUX_REQ_SPI3_RX        /*!< DMAMUX SPI3 RX request     */
#define DMA_REQUEST_SPI3_TX          LL_DMAMUX_REQ_SPI3_TX        /*!< DMAMUX SPI3 TX request     */
#endif

#if defined(TIM4)
#define DMA_REQUEST_TIM4_CH1         LL_DMAMUX_REQ_TIM4_CH1       /*!< DMAMUX TIM4 CH1 request    */
#define DMA_REQUEST_TIM4_CH2         LL_DMAMUX_REQ_TIM4_CH2       /*!< DMAMUX TIM4 CH2 request    */
#define DMA_REQUEST_TIM4_CH3         LL_DMAMUX_REQ_TIM4_CH3       /*!< DMAMUX TIM4 CH3 request    */
#define DMA_REQUEST_TIM4_CH4         LL_DMAMUX_REQ_TIM4_CH4       /*!< DMAMUX TIM4 CH4 request    */
#define DMA_REQUEST_TIM4_TRIG        LL_DMAMUX_REQ_TIM4_TRIG      /*!< DMAMUX TIM4 TRIG request   */
#define DMA_REQUEST_TIM4_UP          LL_DMAMUX_REQ_TIM4_UP        /*!< DMAMUX TIM4 UP request     */
#endif

#if defined(USART5)
#define DMA_REQUEST_USART5_RX        LL_DMAMUX_REQ_USART5_RX      /*!< DMAMUX USART5 RX request  */
#define DMA_REQUEST_USART5_TX        LL_DMAMUX_REQ_USART5_TX      /*!< DMAMUX USART5 TX request  */
#endif

#if defined(USART6)
#define DMA_REQUEST_USART6_RX        LL_DMAMUX_REQ_USART6_RX      /*!< DMAMUX USART6 RX request  */
#define DMA_REQUEST_USART6_TX        LL_DMAMUX_REQ_USART6_TX      /*!< DMAMUX USART6 TX request  */
#endif


#define DMA_MAX_REQUEST              LL_DMAMUX_MAX_REQ
/**
  * @}
  */

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY         LL_DMA_DIRECTION_PERIPH_TO_MEMORY  /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH         LL_DMA_DIRECTION_MEMORY_TO_PERIPH  /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY         LL_DMA_DIRECTION_MEMORY_TO_MEMORY  /*!< Memory to memory direction     */

/**
  * @}
  */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @{
  */
#define DMA_PINC_ENABLE              LL_DMA_PERIPH_INCREMENT            /*!< Peripheral increment mode Enable  */
#define DMA_PINC_DISABLE             LL_DMA_PERIPH_NOINCREMENT          /*!< Peripheral increment mode Disable */
/**
  * @}
  */

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @{
  */
#define DMA_MINC_ENABLE              LL_DMA_MEMORY_INCREMENT            /*!< Memory increment mode Enable  */
#define DMA_MINC_DISABLE             LL_DMA_MEMORY_NOINCREMENT          /*!< Memory increment mode Disable */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @{
  */
#define DMA_PDATAALIGN_BYTE          LL_DMA_PDATAALIGN_BYTE             /*!< Peripheral data alignment : Byte     */
#define DMA_PDATAALIGN_HALFWORD      LL_DMA_PDATAALIGN_HALFWORD         /*!< Peripheral data alignment : HalfWord */
#define DMA_PDATAALIGN_WORD          LL_DMA_PDATAALIGN_WORD             /*!< Peripheral data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @{
  */
#define DMA_MDATAALIGN_BYTE          LL_DMA_MDATAALIGN_BYTE             /*!< Memory data alignment : Byte     */
#define DMA_MDATAALIGN_HALFWORD      LL_DMA_MDATAALIGN_HALFWORD         /*!< Memory data alignment : HalfWord */
#define DMA_MDATAALIGN_WORD          LL_DMA_MDATAALIGN_WORD             /*!< Memory data alignment : Word     */
/**
  * @}
  */

/** @defgroup DMA_mode DMA mode
  * @{
  */
#define DMA_NORMAL                   LL_DMA_MODE_NORMAL                 /*!< Normal mode    */
#define DMA_CIRCULAR                 LL_DMA_MODE_CIRCULAR               /*!< Circular mode  */
/**
  * @}
  */

/** @defgroup DMA_Priority_level DMA Priority level
  * @{
  */
#define DMA_PRIORITY_LOW             LL_DMA_PRIORITY_LOW                /*!< Priority level : Low       */
#define DMA_PRIORITY_MEDIUM          LL_DMA_PRIORITY_MEDIUM             /*!< Priority level : Medium    */
#define DMA_PRIORITY_HIGH            LL_DMA_PRIORITY_HIGH               /*!< Priority level : High      */
#define DMA_PRIORITY_VERY_HIGH       LL_DMA_PRIORITY_VERYHIGH           /*!< Priority level : Very_High */
/**
  * @}
  */

/** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @{
  */
#define DMA_IT_TC                    DMA_CCR_TCIE                       /*!< Transfer Complete interrupt      */
#define DMA_IT_HT                    DMA_CCR_HTIE                       /*!< Half Transfer Complete interrupt */
#define DMA_IT_TE                    DMA_CCR_TEIE                       /*!< Transfer Error interrupt         */
/**
  * @}
  */

/** @defgroup DMA_flag_definitions DMA flag definitions
  * @{
  */

#define DMA_FLAG_GI1                 DMA_ISR_GIF1                       /*!< Global Interrupt flag for Channel 1  */
#define DMA_FLAG_TC1                 DMA_ISR_TCIF1                      /*!< Transfer Complete flag for Channel 1 */
#define DMA_FLAG_HT1                 DMA_ISR_HTIF1                      /*!< Half Transfer flag for Channel 1      */
#define DMA_FLAG_TE1                 DMA_ISR_TEIF1                      /*!< Transfer Error flag for Channel 1     */
#define DMA_FLAG_GI2                 DMA_ISR_GIF2                       /*!< Global Interrupt flag for Channel 2  */
#define DMA_FLAG_TC2                 DMA_ISR_TCIF2                      /*!< Transfer Complete flag for Channel 2 */
#define DMA_FLAG_HT2                 DMA_ISR_HTIF2                      /*!< Half Transfer flag for Channel 2      */
#define DMA_FLAG_TE2                 DMA_ISR_TEIF2                      /*!< Transfer Error flag for Channel 2     */
#define DMA_FLAG_GI3                 DMA_ISR_GIF3                       /*!< Global Interrupt flag for Channel 3  */
#define DMA_FLAG_TC3                 DMA_ISR_TCIF3                      /*!< Transfer Complete flag for Channel 3 */
#define DMA_FLAG_HT3                 DMA_ISR_HTIF3                      /*!< Half Transfer flag for Channel 3      */
#define DMA_FLAG_TE3                 DMA_ISR_TEIF3                      /*!< Transfer Error flag for Channel 3     */
#define DMA_FLAG_GI4                 DMA_ISR_GIF4                       /*!< Global Interrupt flag for Channel 4  */
#define DMA_FLAG_TC4                 DMA_ISR_TCIF4                      /*!< Transfer Complete flag for Channel 4 */
#define DMA_FLAG_HT4                 DMA_ISR_HTIF4                      /*!< Half Transfer flag for Channel 4      */
#define DMA_FLAG_TE4                 DMA_ISR_TEIF4                      /*!< Transfer Error flag for Channel 4     */
#define DMA_FLAG_GI5                 DMA_ISR_GIF5                       /*!< Global Interrupt flag for Channel 5  */
#define DMA_FLAG_TC5                 DMA_ISR_TCIF5                      /*!< Transfer Complete flag for Channel 5 */
#define DMA_FLAG_HT5                 DMA_ISR_HTIF5                      /*!< Half Transfer flag for Channel 5      */
#define DMA_FLAG_TE5                 DMA_ISR_TEIF5                      /*!< Transfer Error for Channel 5          */
#if defined(DMA1_Channel6)
#define DMA_FLAG_GI6                 DMA_ISR_GIF6                       /*!< Global Interrupt flag for Channel 6  */
#define DMA_FLAG_TC6                 DMA_ISR_TCIF6                      /*!< Transfer Complete flag for Channel 6 */
#define DMA_FLAG_HT6                 DMA_ISR_HTIF6                      /*!< Half Transfer flag for Channel 6      */
#define DMA_FLAG_TE6                 DMA_ISR_TEIF6                      /*!< Transfer Error flag for Channel 6     */
#endif
#if defined(DMA1_Channel7)
#define DMA_FLAG_GI7                 DMA_ISR_GIF7                       /*!< Global Interrupt flag for Channel 7  */
#define DMA_FLAG_TC7                 DMA_ISR_TCIF7                      /*!< Transfer Complete flag for Channel 7 */
#define DMA_FLAG_HT7                 DMA_ISR_HTIF7                      /*!< Half Transfer flag for Channel 7      */
#define DMA_FLAG_TE7                 DMA_ISR_TEIF7                      /*!< Transfer Error flag for Channel 7     */
#endif
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

/** @brief  Reset DMA handle state
  * @param __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CCR |=  DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param __HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__)       ((__HANDLE__)->Instance->CCR &=  ~DMA_CCR_EN)

/**
  * @brief  Return the current DMA Channel transfer complete flag.
  * @param __HANDLE__ DMA handle
  * @retval The specified transfer complete flag index.
  */
#if defined(DMA2)
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
   DMA_FLAG_TC7)
#else /* DMA1 */
#if   defined(DMA1_Channel7)
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TC6 :\
   DMA_FLAG_TC7)
#else
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
   DMA_FLAG_TC5)
#endif
#endif /* DMA2 */

/**
  * @brief  Return the current DMA Channel half transfer complete flag.
  * @param __HANDLE__ DMA handle
  * @retval The specified half transfer complete flag index.
  */
#if defined(DMA2)
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__) \
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
   DMA_FLAG_HT7)
#else /* DMA1 */
#if   defined(DMA1_Channel7)
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_HT6 :\
   DMA_FLAG_HT7)
#else
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
   DMA_FLAG_HT5)
#endif
#endif /* DMA2 */

/**
  * @brief  Return the current DMA Channel transfer error flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined(DMA2)
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__) \
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
   DMA_FLAG_TE7)
#else /* DMA1 */
#if   defined(DMA1_Channel7)
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TE6 :\
   DMA_FLAG_TE7)
#else
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
   DMA_FLAG_TE5)
#endif
#endif /* DMA2 */

/**
  * @brief  Return the current DMA Channel Global interrupt flag.
  * @param  __HANDLE__ DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined(DMA2)
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_GI1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_GI1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_GI2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_GI2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_GI3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_GI3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_GI4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_GI4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_GI5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel5))? DMA_FLAG_GI5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_GI6 :\
   DMA_FLAG_GI7)
#else /* DMA1 */
#if   defined(DMA1_Channel7)
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_GI1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_GI2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_GI3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_GI4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_GI5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_GI6 :\
   DMA_FLAG_GI7)
#else
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_GI1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_GI2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_GI3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_GI4 :\
   DMA_FLAG_GI5)
#endif
#endif /* DMA2 */

/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__ DMA handle
  * @param  __FLAG__ Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *            @arg DMA_FLAG_GIx:  Global interrupt flag
  *         Where x can be 1 to max Channel supported by the product to select the DMA Channel flag.
  * @retval The state of FLAG (SET or RESET).
  */
#if defined(DMA2)
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) (((uint32_t)((__HANDLE__)->Instance) > ((uint32_t)DMA1_Channel7))? \
 (DMA2->ISR & (__FLAG__)) : (DMA1->ISR & (__FLAG__)))
#else /* DMA1 */
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)  (DMA1->ISR & (__FLAG__))
#endif /* DMA2 */

/**
  * @brief  Clear the DMA Channel pending flags.
  * @param  __HANDLE__ DMA handle
  * @param  __FLAG__ specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *            @arg DMA_FLAG_GIx:  Global interrupt flag
  *         Where x can be 1 to max Channel supported by the product to select the DMA Channel flag.
  * @retval None
  */
#if defined(DMA2)
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (((uint32_t)((__HANDLE__)->Instance) > ((uint32_t)DMA1_Channel7))? \
 (DMA2->IFCR = (__FLAG__)) : (DMA1->IFCR = (__FLAG__)))
#else /* DMA1 */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (DMA1->IFCR |= (__FLAG__))
#endif /* DMA2 */

/**
  * @brief  Enable the specified DMA Channel interrupts.
  * @param  __HANDLE__ DMA handle
  * @param __INTERRUPT__ specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA Channel interrupts.
  * @param  __HANDLE__ DMA handle
  * @param __INTERRUPT__ specifies the DMA interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified DMA Channel interrupt is enabled or disabled.
  * @param  __HANDLE__ DMA handle
  * @param  __INTERRUPT__ specifies the DMA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @brief  Returns the number of remaining data units in the current DMA Channel transfer.
  * @param  __HANDLE__ DMA handle
  * @retval The number of remaining data units in the current DMA Channel transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNDTR)

/**
  * @}
  */

/* Include DMA HAL Extension module */
#include "stm32g0xx_hal_dma_ex.h"

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
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
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

#define IS_DMA_DIRECTION(DIRECTION)             (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                                 ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                                 ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_BUFFER_SIZE(SIZE)                (((SIZE) >= 0x1U) && ((SIZE) < DMA_CNDTR_NDT))

#define IS_DMA_PERIPHERAL_INC_STATE(STATE)      (((STATE) == DMA_PINC_ENABLE) || \
                                                 ((STATE) == DMA_PINC_DISABLE))

#define IS_DMA_MEMORY_INC_STATE(STATE)          (((STATE) == DMA_MINC_ENABLE)  || \
                                                 ((STATE) == DMA_MINC_DISABLE))

#define IS_DMA_ALL_REQUEST(REQUEST)             ((REQUEST) <= DMA_MAX_REQUEST)

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE)       (((SIZE) == DMA_PDATAALIGN_BYTE)     || \
                                                 ((SIZE) == DMA_PDATAALIGN_HALFWORD) || \
                                                 ((SIZE) == DMA_PDATAALIGN_WORD))

#define IS_DMA_MEMORY_DATA_SIZE(SIZE)           (((SIZE) == DMA_MDATAALIGN_BYTE)     || \
                                                 ((SIZE) == DMA_MDATAALIGN_HALFWORD) || \
                                                 ((SIZE) == DMA_MDATAALIGN_WORD ))

#define IS_DMA_MODE(MODE)                       (((MODE) == DMA_NORMAL )  || \
                                                 ((MODE) == DMA_CIRCULAR))

#define IS_DMA_PRIORITY(PRIORITY)               (((PRIORITY) == DMA_PRIORITY_LOW )   || \
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

#endif /* STM32G0xx_HAL_DMA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
