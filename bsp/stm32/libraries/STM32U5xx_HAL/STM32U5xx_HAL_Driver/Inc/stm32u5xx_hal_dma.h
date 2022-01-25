/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5xx_HAL_DMA_H
#define STM32U5xx_HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */


/* Exported types ----------------------------------------------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA Exported Types
  * @brief    DMA Exported Types
  * @{
  */

/**
  * @brief DMA Transfer Configuration Structure definition.
  */
typedef struct
{
  uint32_t Request;               /*!< Specifies the DMA channel request.
                                       This parameter can be a value of @ref DMA_Request_Selection                    */

  uint32_t BlkHWRequest;          /*!< Specifies the Block hardware request mode for DMA channel.
                                       Block Hardware request feature can be used only with dedicated peripherals.
                                       This parameter can be a value of @ref DMA_Block_Request                        */

  uint32_t Direction;             /*!< Specifies the transfer direction for DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Direction                   */

  uint32_t SrcInc;                /*!< Specifies the source increment mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Source_Increment_Mode                */

  uint32_t DestInc;               /*!< Specifies the destination increment mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Destination_Increment_Mode           */

  uint32_t SrcDataWidth;          /*!< Specifies the source data width for the DMA channel.
                                       This parameter can be a value of @ref DMA_Source_Data_Width                    */

  uint32_t DestDataWidth;         /*!< Specifies the destination data width for the DMA channel.
                                       This parameter can be a value of @ref DMA_Destination_Data_Width               */

  uint32_t Priority;              /*!< Specifies the priority level for the DMA channel.
                                       This parameter can be a value of @ref DMA_Priority_Level                       */

  uint32_t SrcBurstLength;        /*!< Specifies the source burst length (number of beats within a burst) for the DMA
                                       channel.
                                       This parameter can be a value between 1 and 64                                 */

  uint32_t DestBurstLength;       /*!< Specifies the destination burst length (number of beats within a burst) for the
                                       DMA channel.
                                       This parameter can be a value between 1 and 64                                 */

  uint32_t TransferAllocatedPort; /*!< Specifies the transfer allocated ports.
                                       This parameter can be a combination of @ref DMA_Transfer_Allocated_Port        */

  uint32_t TransferEventMode;     /*!< Specifies the transfer event mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Event_Mode                  */

  uint32_t Mode;                  /*!< Specifies the transfer mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Mode                        */

} DMA_InitTypeDef;

/**
  * @brief DMA Linked-List Configuration Structure Definition.
  */
typedef struct
{
  uint32_t Priority;          /*!< Specifies the priority level for the DMA channel.
                                   This parameter can be a value of @ref DMA_Priority_Level        */

  uint32_t LinkStepMode;      /*!< Specifies the link step mode for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_Link_Step_Mode      */

  uint32_t LinkAllocatedPort; /*!< Specifies the linked-list allocated port for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_Link_Allocated_Port */

  uint32_t TransferEventMode; /*!< Specifies the transfer event mode for the DMA channel.
                                   This parameter can be a value of @ref DMA_Transfer_Event_Mode   */

  uint32_t LinkedListMode;    /*!< Specifies linked-list transfer mode for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_LinkedList_Mode     */

} DMA_InitLinkedListTypeDef;

/**
  * @brief  HAL DMA State Enumeration Definition.
  */
typedef enum
{
  HAL_DMA_STATE_RESET   = 0x00U, /*!< DMA not yet initialized or disabled */
  HAL_DMA_STATE_READY   = 0x01U, /*!< DMA initialized and ready for use   */
  HAL_DMA_STATE_BUSY    = 0x02U, /*!< DMA process is ongoing              */
  HAL_DMA_STATE_ERROR   = 0x03U, /*!< DMA error state                     */
  HAL_DMA_STATE_ABORT   = 0x04U, /*!< DMA Abort state                     */
  HAL_DMA_STATE_SUSPEND = 0x05U, /*!< DMA Suspend state                   */

} HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Level Complete Enumeration Definition.
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER = 0x00U, /*!< Full channel transfer */
  HAL_DMA_HALF_TRANSFER = 0x01U, /*!< Half channel transfer */

} HAL_DMA_LevelCompleteTypeDef;

/**
  * @brief  HAL DMA Callbacks IDs Enumeration Definition.
  */
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID     = 0x00U, /*!< Complete transfer callback ID      */
  HAL_DMA_XFER_HALFCPLT_CB_ID = 0x01U, /*!< Half complete transfer callback ID */
  HAL_DMA_XFER_ERROR_CB_ID    = 0x02U, /*!< Error transfer callback ID         */
  HAL_DMA_XFER_ABORT_CB_ID    = 0x03U, /*!< Abort transfer callback ID         */
  HAL_DMA_XFER_SUSPEND_CB_ID  = 0x04U, /*!< Suspend transfer callback ID       */
  HAL_DMA_XFER_ALL_CB_ID      = 0x05U  /*!< All callback ID                    */

} HAL_DMA_CallbackIDTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef       *Instance;                             /*!< Register the DMA channel base address   */

  DMA_InitTypeDef           Init;                                  /*!< DMA channel init parameters             */

  DMA_InitLinkedListTypeDef InitLinkedList;                        /*!< DMA channel linked-list init parameters */

  HAL_LockTypeDef           Lock;                                  /*!< DMA locking object                      */

  uint32_t                  Mode;                                  /*!< DMA transfer mode                       */

  __IO HAL_DMA_StateTypeDef State;                                 /*!< DMA transfer state                      */

  __IO uint32_t             ErrorCode;                             /*!< DMA error code                          */

  void                      *Parent;                               /*!< Parent object state                     */

  void (* XferCpltCallback)(struct __DMA_HandleTypeDef *hdma);     /*!< DMA transfer complete callback          */

  void (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA half transfer complete callback     */

  void (* XferErrorCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA transfer error callback             */

  void (* XferAbortCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA transfer Abort callback             */

  void (* XferSuspendCallback)(struct __DMA_HandleTypeDef *hdma);  /*!< DMA transfer Suspend callback           */

  struct __DMA_QListTypeDef  *LinkedListQueue;                     /*!< DMA linked-list queue                   */

} DMA_HandleTypeDef;
/**
  * @}
  */


/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @brief    DMA Exported constants
  * @{
  */

/** @defgroup DMA_Error_Codes DMA Error Codes
  * @brief    DMA Error Codes
  * @{
  */
#define HAL_DMA_ERROR_NONE             (0x0000U) /*!< No error                      */
#define HAL_DMA_ERROR_DTE              (0x0001U) /*!< Data transfer error           */
#define HAL_DMA_ERROR_ULE              (0x0002U) /*!< Update linked-list item error */
#define HAL_DMA_ERROR_USE              (0x0004U) /*!< User setting error            */
#define HAL_DMA_ERROR_TO               (0x0008U) /*!< Trigger overrun error         */
#define HAL_DMA_ERROR_TIMEOUT          (0x0010U) /*!< Timeout error                 */
#define HAL_DMA_ERROR_NO_XFER          (0x0020U) /*!< No transfer ongoing error     */
#define HAL_DMA_ERROR_BUSY             (0x0040U) /*!< Busy error                    */
#define HAL_DMA_ERROR_INVALID_CALLBACK (0x0080U) /*!< Invalid callback error        */
#define HAL_DMA_ERROR_NOT_SUPPORTED    (0x0100U) /*!< Not supported mode            */
/**
  * @}
  */

/** @defgroup DMA_Interrupt_Enable_Definition DMA Interrupt Enable Definition
  * @brief    DMA Interrupt Enable Definition
  * @{
  */
#define DMA_IT_TC   DMA_CCR_TCIE   /*!< Transfer complete interrupt             */
#define DMA_IT_HT   DMA_CCR_HTIE   /*!< Half transfer complete interrupt        */
#define DMA_IT_DTE  DMA_CCR_DTEIE  /*!< Data transfer error interrupt           */
#define DMA_IT_ULE  DMA_CCR_ULEIE  /*!< Update linked-list item error interrupt */
#define DMA_IT_USE  DMA_CCR_USEIE  /*!< User eetting error interrupt            */
#define DMA_IT_SUSP DMA_CCR_SUSPIE /*!< Completed suspension interrupt          */
#define DMA_IT_TO   DMA_CCR_TOIE   /*!< Trigger overrun interrupt               */
/**
  * @}
  */

/** @defgroup DMA_Flag_Definition DMA Flag Definition
  * @brief    DMA Flag Definition
  * @{
  */
#define DMA_FLAG_IDLE DMA_CSR_IDLEF /*!< Idle flag                          */
#define DMA_FLAG_TC   DMA_CSR_TCF   /*!< Transfer complete flag             */
#define DMA_FLAG_HT   DMA_CSR_HTF   /*!< Half transfer complete flag        */
#define DMA_FLAG_DTE  DMA_CSR_DTEF  /*!< Data transfer error flag           */
#define DMA_FLAG_ULE  DMA_CSR_ULEF  /*!< Update linked-list item error flag */
#define DMA_FLAG_USE  DMA_CSR_USEF  /*!< User setting error flag            */
#define DMA_FLAG_SUSP DMA_CSR_SUSPF /*!< Completed suspension flag          */
#define DMA_FLAG_TO   DMA_CSR_TOF   /*!< Trigger overrun flag               */
/**
  * @}
  */

/** @defgroup DMA_Request_Selection DMA Request Selection
  * @brief    DMA Request Selection
  * @{
  */
/* GPDMA1 requests */
#define GPDMA1_REQUEST_ADC1         (0U)   /*!< GPDMA1 HW request is ADC1         */
#define GPDMA1_REQUEST_ADC4         (1U)   /*!< GPDMA1 HW request is ADC4         */
#define GPDMA1_REQUEST_DAC1_CH1     (2U)   /*!< GPDMA1 HW request is DAC1_CH1     */
#define GPDMA1_REQUEST_DAC1_CH2     (3U)   /*!< GPDMA1 HW request is DAC1_CH2     */
#define GPDMA1_REQUEST_TIM6_UP      (4U)   /*!< GPDMA1 HW request is TIM6_UP      */
#define GPDMA1_REQUEST_TIM7_UP      (5U)   /*!< GPDMA1 HW request is TIM7_UP      */
#define GPDMA1_REQUEST_SPI1_RX      (6U)   /*!< GPDMA1 HW request is SPI1_RX      */
#define GPDMA1_REQUEST_SPI1_TX      (7U)   /*!< GPDMA1 HW request is SPI1_TX      */
#define GPDMA1_REQUEST_SPI2_RX      (8U)   /*!< GPDMA1 HW request is SPI2_RX      */
#define GPDMA1_REQUEST_SPI2_TX      (9U)   /*!< GPDMA1 HW request is SPI2_TX      */
#define GPDMA1_REQUEST_SPI3_RX      (10U)  /*!< GPDMA1 HW request is SPI3_RX      */
#define GPDMA1_REQUEST_SPI3_TX      (11U)  /*!< GPDMA1 HW request is SPI3_TX      */
#define GPDMA1_REQUEST_I2C1_RX      (12U)  /*!< GPDMA1 HW request is I2C1_RX      */
#define GPDMA1_REQUEST_I2C1_TX      (13U)  /*!< GPDMA1 HW request is I2C1_TX      */
#define GPDMA1_REQUEST_I2C1_EVC     (14U)  /*!< GPDMA1 HW request is I2C1_EVC     */
#define GPDMA1_REQUEST_I2C2_RX      (15U)  /*!< GPDMA1 HW request is I2C2_RX      */
#define GPDMA1_REQUEST_I2C2_TX      (16U)  /*!< GPDMA1 HW request is I2C2_TX      */
#define GPDMA1_REQUEST_I2C2_EVC     (17U)  /*!< GPDMA1 HW request is I2C2_EVC     */
#define GPDMA1_REQUEST_I2C3_RX      (18U)  /*!< GPDMA1 HW request is I2C3_RX      */
#define GPDMA1_REQUEST_I2C3_TX      (19U)  /*!< GPDMA1 HW request is I2C3_TX      */
#define GPDMA1_REQUEST_I2C3_EVC     (20U)  /*!< GPDMA1 HW request is I2C3_EVC     */
#define GPDMA1_REQUEST_I2C4_RX      (21U)  /*!< GPDMA1 HW request is I2C4_RX      */
#define GPDMA1_REQUEST_I2C4_TX      (22U)  /*!< GPDMA1 HW request is I2C4_TX      */
#define GPDMA1_REQUEST_I2C4_EVC     (23U)  /*!< GPDMA1 HW request is I2C4_EVC     */
#define GPDMA1_REQUEST_USART1_RX    (24U)  /*!< GPDMA1 HW request is USART1_RX    */
#define GPDMA1_REQUEST_USART1_TX    (25U)  /*!< GPDMA1 HW request is USART1_TX    */
#define GPDMA1_REQUEST_USART2_RX    (26U)  /*!< GPDMA1 HW request is USART2_RX    */
#define GPDMA1_REQUEST_USART2_TX    (27U)  /*!< GPDMA1 HW request is USART2_TX    */
#define GPDMA1_REQUEST_USART3_RX    (28U)  /*!< GPDMA1 HW request is USART3_RX    */
#define GPDMA1_REQUEST_USART3_TX    (29U)  /*!< GPDMA1 HW request is USART3_TX    */
#define GPDMA1_REQUEST_UART4_RX     (30U)  /*!< GPDMA1 HW request is UART4_RX     */
#define GPDMA1_REQUEST_UART4_TX     (31U)  /*!< GPDMA1 HW request is UART4_TX     */
#define GPDMA1_REQUEST_UART5_RX     (32U)  /*!< GPDMA1 HW request is UART5_RX     */
#define GPDMA1_REQUEST_UART5_TX     (33U)  /*!< GPDMA1 HW request is UART5_TX     */
#define GPDMA1_REQUEST_LPUART1_RX   (34U)  /*!< GPDMA1 HW request is LPUART1_RX   */
#define GPDMA1_REQUEST_LPUART1_TX   (35U)  /*!< GPDMA1 HW request is LPUART1_TX   */
#define GPDMA1_REQUEST_SAI1_A       (36U)  /*!< GPDMA1 HW request is SAI1_A       */
#define GPDMA1_REQUEST_SAI1_B       (37U)  /*!< GPDMA1 HW request is SAI1_B       */
#define GPDMA1_REQUEST_SAI2_A       (38U)  /*!< GPDMA1 HW request is SAI2_A       */
#define GPDMA1_REQUEST_SAI2_B       (39U)  /*!< GPDMA1 HW request is SAI2_B       */
#define GPDMA1_REQUEST_OCTOSPI1     (40U)  /*!< GPDMA1 HW request is OCTOSPI1     */
#define GPDMA1_REQUEST_OCTOSPI2     (41U)  /*!< GPDMA1 HW request is OCTOSPI2     */
#define GPDMA1_REQUEST_TIM1_CH1     (42U)  /*!< GPDMA1 HW request is TIM1_CH1     */
#define GPDMA1_REQUEST_TIM1_CH2     (43U)  /*!< GPDMA1 HW request is TIM1_CH2     */
#define GPDMA1_REQUEST_TIM1_CH3     (44U)  /*!< GPDMA1 HW request is TIM1_CH3     */
#define GPDMA1_REQUEST_TIM1_CH4     (45U)  /*!< GPDMA1 HW request is TIM1_CH4     */
#define GPDMA1_REQUEST_TIM1_UP      (46U)  /*!< GPDMA1 HW request is TIM1_UP      */
#define GPDMA1_REQUEST_TIM1_TRIG    (47U)  /*!< GPDMA1 HW request is TIM1_TRIG    */
#define GPDMA1_REQUEST_TIM1_COM     (48U)  /*!< GPDMA1 HW request is TIM1_COM     */
#define GPDMA1_REQUEST_TIM8_CH1     (49U)  /*!< GPDMA1 HW request is TIM8_CH1     */
#define GPDMA1_REQUEST_TIM8_CH2     (50U)  /*!< GPDMA1 HW request is TIM8_CH2     */
#define GPDMA1_REQUEST_TIM8_CH3     (51U)  /*!< GPDMA1 HW request is TIM8_CH3     */
#define GPDMA1_REQUEST_TIM8_CH4     (52U)  /*!< GPDMA1 HW request is TIM8_CH4     */
#define GPDMA1_REQUEST_TIM8_UP      (53U)  /*!< GPDMA1 HW request is TIM8_UP      */
#define GPDMA1_REQUEST_TIM8_TRIG    (54U)  /*!< GPDMA1 HW request is TIM8_TRIG    */
#define GPDMA1_REQUEST_TIM8_COM     (55U)  /*!< GPDMA1 HW request is TIM8_COM     */
#define GPDMA1_REQUEST_TIM2_CH1     (56U)  /*!< GPDMA1 HW request is TIM2_CH1     */
#define GPDMA1_REQUEST_TIM2_CH2     (57U)  /*!< GPDMA1 HW request is TIM2_CH2     */
#define GPDMA1_REQUEST_TIM2_CH3     (58U)  /*!< GPDMA1 HW request is TIM2_CH3     */
#define GPDMA1_REQUEST_TIM2_CH4     (59U)  /*!< GPDMA1 HW request is TIM2_CH4     */
#define GPDMA1_REQUEST_TIM2_UP      (60U)  /*!< GPDMA1 HW request is TIM2_UP      */
#define GPDMA1_REQUEST_TIM3_CH1     (61U)  /*!< GPDMA1 HW request is TIM3_CH1     */
#define GPDMA1_REQUEST_TIM3_CH2     (62U)  /*!< GPDMA1 HW request is TIM3_CH2     */
#define GPDMA1_REQUEST_TIM3_CH3     (63U)  /*!< GPDMA1 HW request is TIM3_CH3     */
#define GPDMA1_REQUEST_TIM3_CH4     (64U)  /*!< GPDMA1 HW request is TIM3_CH4     */
#define GPDMA1_REQUEST_TIM3_UP      (65U)  /*!< GPDMA1 HW request is TIM3_UP      */
#define GPDMA1_REQUEST_TIM3_TRIG    (66U)  /*!< GPDMA1 HW request is TIM3_TRIG    */
#define GPDMA1_REQUEST_TIM4_CH1     (67U)  /*!< GPDMA1 HW request is TIM4_CH1     */
#define GPDMA1_REQUEST_TIM4_CH2     (68U)  /*!< GPDMA1 HW request is TIM4_CH2     */
#define GPDMA1_REQUEST_TIM4_CH3     (69U)  /*!< GPDMA1 HW request is TIM4_CH3     */
#define GPDMA1_REQUEST_TIM4_CH4     (70U)  /*!< GPDMA1 HW request is TIM4_CH4     */
#define GPDMA1_REQUEST_TIM4_UP      (71U)  /*!< GPDMA1 HW request is TIM4_UP      */
#define GPDMA1_REQUEST_TIM5_CH1     (72U)  /*!< GPDMA1 HW request is TIM5_CH1     */
#define GPDMA1_REQUEST_TIM5_CH2     (73U)  /*!< GPDMA1 HW request is TIM5_CH2     */
#define GPDMA1_REQUEST_TIM5_CH3     (74U)  /*!< GPDMA1 HW request is TIM5_CH3     */
#define GPDMA1_REQUEST_TIM5_CH4     (75U)  /*!< GPDMA1 HW request is TIM5_CH4     */
#define GPDMA1_REQUEST_TIM5_UP      (76U)  /*!< GPDMA1 HW request is TIM5_UP      */
#define GPDMA1_REQUEST_TIM5_TRIG    (77U)  /*!< GPDMA1 HW request is TIM5_TRIG    */
#define GPDMA1_REQUEST_TIM15_CH1    (78U)  /*!< GPDMA1 HW request is TIM15_CH1    */
#define GPDMA1_REQUEST_TIM15_UP     (79U)  /*!< GPDMA1 HW request is TIM15_UP     */
#define GPDMA1_REQUEST_TIM15_TRIG   (80U)  /*!< GPDMA1 HW request is TIM15_TRIG   */
#define GPDMA1_REQUEST_TIM15_COM    (81U)  /*!< GPDMA1 HW request is TIM15_COM    */
#define GPDMA1_REQUEST_TIM16_CH1    (82U)  /*!< GPDMA1 HW request is TIM16_CH1    */
#define GPDMA1_REQUEST_TIM16_UP     (83U)  /*!< GPDMA1 HW request is TIM16_UP     */
#define GPDMA1_REQUEST_TIM17_CH1    (84U)  /*!< GPDMA1 HW request is TIM17_CH1    */
#define GPDMA1_REQUEST_TIM17_UP     (85U)  /*!< GPDMA1 HW request is TIM17_UP     */
#define GPDMA1_REQUEST_DCMI         (86U)  /*!< GPDMA1 HW request is DCMI         */
#define GPDMA1_REQUEST_AES_IN       (87U)  /*!< GPDMA1 HW request is AES_IN       */
#define GPDMA1_REQUEST_AES_OUT      (88U)  /*!< GPDMA1 HW request is AES_OUT      */
#define GPDMA1_REQUEST_HASH_IN      (89U)  /*!< GPDMA1 HW request is HASH_IN      */
#define GPDMA1_REQUEST_UCPD1_TX     (90U)  /*!< GPDMA1 HW request is UCPD1_TX     */
#define GPDMA1_REQUEST_UCPD1_RX     (91U)  /*!< GPDMA1 HW request is UCPD1_RX     */
#define GPDMA1_REQUEST_MDF1_FLT0    (92U)  /*!< GPDMA1 HW request is MDF1_FLT0    */
#define GPDMA1_REQUEST_MDF1_FLT1    (93U)  /*!< GPDMA1 HW request is MDF1_FLT1    */
#define GPDMA1_REQUEST_MDF1_FLT2    (94U)  /*!< GPDMA1 HW request is MDF1_FLT2    */
#define GPDMA1_REQUEST_MDF1_FLT3    (95U)  /*!< GPDMA1 HW request is MDF1_FLT3    */
#define GPDMA1_REQUEST_MDF1_FLT4    (96U)  /*!< GPDMA1 HW request is MDF1_FLT4    */
#define GPDMA1_REQUEST_MDF1_FLT5    (97U)  /*!< GPDMA1 HW request is MDF1_FLT5    */
#define GPDMA1_REQUEST_ADF1_FLT0    (98U)  /*!< GPDMA1 HW request is ADF1_FLT0    */
#define GPDMA1_REQUEST_FMAC_READ    (99U)  /*!< GPDMA1 HW request is FMAC_READ    */
#define GPDMA1_REQUEST_FMAC_WRITE   (100U) /*!< GPDMA1 HW request is FMAC_WRITE   */
#define GPDMA1_REQUEST_CORDIC_READ  (101U) /*!< GPDMA1 HW request is CORDIC_READ  */
#define GPDMA1_REQUEST_CORDIC_WRITE (102U) /*!< GPDMA1 HW request is CORDIC_WRITE */
#define GPDMA1_REQUEST_SAES_IN      (103U) /*!< GPDMA1 HW request is SAES_IN      */
#define GPDMA1_REQUEST_SAES_OUT     (104U) /*!< GPDMA1 HW request is SAES_OUT     */
#define GPDMA1_REQUEST_LPTIM1_IC1   (105U) /*!< GPDMA1 HW request is LPTIM1_IC1   */
#define GPDMA1_REQUEST_LPTIM1_IC2   (106U) /*!< GPDMA1 HW request is LPTIM1_IC2   */
#define GPDMA1_REQUEST_LPTIM1_UE    (107U) /*!< GPDMA1 HW request is LPTIM1_UE    */
#define GPDMA1_REQUEST_LPTIM2_IC1   (108U) /*!< GPDMA1 HW request is LPTIM2_IC1   */
#define GPDMA1_REQUEST_LPTIM2_IC2   (109U) /*!< GPDMA1 HW request is LPTIM2_IC2   */
#define GPDMA1_REQUEST_LPTIM2_UE    (110U) /*!< GPDMA1 HW request is LPTIM2_UE    */
#define GPDMA1_REQUEST_LPTIM3_IC1   (111U) /*!< GPDMA1 HW request is LPTIM3_IC1   */
#define GPDMA1_REQUEST_LPTIM3_IC2   (112U) /*!< GPDMA1 HW request is LPTIM3_IC2   */
#define GPDMA1_REQUEST_LPTIM3_UE    (113U) /*!< GPDMA1 HW request is LPTIM3_UE    */

/* LPDMA1 requests */
#define LPDMA1_REQUEST_LPUART1_RX (0U)  /*!< LPDMA1 HW request is LPUART1_RX */
#define LPDMA1_REQUEST_LPUART1_TX (1U)  /*!< LPDMA1 HW request is LPUART1_TX */
#define LPDMA1_REQUEST_SPI3_RX    (2U)  /*!< LPDMA1 HW request is SPI3_RX    */
#define LPDMA1_REQUEST_SPI3_TX    (3U)  /*!< LPDMA1 HW request is SPI3_TX    */
#define LPDMA1_REQUEST_I2C3_RX    (4U)  /*!< LPDMA1 HW request is I2C3_RX    */
#define LPDMA1_REQUEST_I2C3_TX    (5U)  /*!< LPDMA1 HW request is I2C3_TX    */
#define LPDMA1_REQUEST_I2C3_EVC   (6U)  /*!< LPDMA1 HW request is I2C3_EVC   */
#define LPDMA1_REQUEST_ADC4       (7U)  /*!< LPDMA1 HW request is ADC4       */
#define LPDMA1_REQUEST_DAC1_CH1   (8U)  /*!< LPDMA1 HW request is DAC1_CH1   */
#define LPDMA1_REQUEST_DAC1_CH2   (9U)  /*!< LPDMA1 HW request is DAC1_CH2   */
#define LPDMA1_REQUEST_ADF1_FLT0  (10U) /*!< LPDMA1 HW request is ADF1_FLT0  */
#define LPDMA1_REQUEST_LPTIM1_IC1 (11U) /*!< LPDMA1 HW request is LPTIM1_IC1 */
#define LPDMA1_REQUEST_LPTIM1_IC2 (12U) /*!< LPDMA1 HW request is LPTIM1_IC2 */
#define LPDMA1_REQUEST_LPTIM1_UE  (13U) /*!< LPDMA1 HW request is LPTIM1_UE  */
#define LPDMA1_REQUEST_LPTIM3_IC1 (14U) /*!< LPDMA1 HW request is LPTIM3_IC1 */
#define LPDMA1_REQUEST_LPTIM3_IC2 (15U) /*!< LPDMA1 HW request is LPTIM3_IC2 */
#define LPDMA1_REQUEST_LPTIM3_UE  (16U) /*!< LPDMA1 HW request is LPTIM3_UE  */

/* Software request */
#define DMA_REQUEST_SW DMA_CTR2_SWREQ /*!< DMA SW request */
/**
  * @}
  */

/** @defgroup DMA_Block_Request DMA Block Request
  * @brief    DMA Block Request
  * @{
  */
#define DMA_BREQ_SINGLE_BURST 0x00000000U   /*!< Hardware request protocol at a single / burst level */
#define DMA_BREQ_BLOCK        DMA_CTR2_BREQ /*!< Hardware request protocol at a block level          */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Direction DMA Transfer Direction
  * @brief    DMA transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY 0x00000000U    /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH DMA_CTR2_DREQ  /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY DMA_CTR2_SWREQ /*!< Memory to memory direction     */
/**
  * @}
  */

/** @defgroup DMA_Source_Increment_Mode DMA Source Increment Mode
  * @brief    DMA Source Increment Mode
  * @{
  */
#define DMA_SINC_FIXED       0x00000000U   /*!< Source fixed       single / burst */
#define DMA_SINC_INCREMENTED DMA_CTR1_SINC /*!< Source incremented single / burst */
/**
  * @}
  */

/** @defgroup DMA_Destination_Increment_Mode DMA Destination Increment Mode
  * @brief    DMA Destination Increment Mode
  * @{
  */
#define DMA_DINC_FIXED       0x00000000U   /*!< Destination fixed       single / burst */
#define DMA_DINC_INCREMENTED DMA_CTR1_DINC /*!< Destination incremented single / burst */
/**
  * @}
  */

/** @defgroup DMA_Source_Data_Width DMA Source Data Width
  * @brief    DMA Source Data Width
  * @{
  */
#define DMA_SRC_DATAWIDTH_BYTE     0x00000000U         /*!< Source data width : Byte     */
#define DMA_SRC_DATAWIDTH_HALFWORD DMA_CTR1_SDW_LOG2_0 /*!< Source data width : HalfWord */
#define DMA_SRC_DATAWIDTH_WORD     DMA_CTR1_SDW_LOG2_1 /*!< Source data width : Word     */
/**
  * @}
  */

/** @defgroup DMA_Destination_Data_Width DMA destination Data Width
  * @brief    DMA destination Data Width
  * @{
  */
#define DMA_DEST_DATAWIDTH_BYTE     0x00000000U         /*!< Destination data width : Byte     */
#define DMA_DEST_DATAWIDTH_HALFWORD DMA_CTR1_DDW_LOG2_0 /*!< Destination data width : HalfWord */
#define DMA_DEST_DATAWIDTH_WORD     DMA_CTR1_DDW_LOG2_1 /*!< Destination data width : Word     */
/**
  * @}
  */

/** @defgroup DMA_Priority_Level DMA Priority Level
  * @brief    DMA Priority Level
  * @{
  */
#define DMA_LOW_PRIORITY_LOW_WEIGHT  0x00000000U    /*!< Priority level : Low Priority, Low weight  */
#define DMA_LOW_PRIORITY_MID_WEIGHT  DMA_CCR_PRIO_0 /*!< Priority level : Low Priority, Mid weight  */
#define DMA_LOW_PRIORITY_HIGH_WEIGHT DMA_CCR_PRIO_1 /*!< Priority level : Low Priority, High weight */
#define DMA_HIGH_PRIORITY            DMA_CCR_PRIO   /*!< Priority level : HIGH Priority             */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Allocated_Port DMA Transfer Allocated Port
  * @brief    DMA Transfer Allocated Port
  * @{
  */
#define DMA_SRC_ALLOCATED_PORT0  0x00000000U  /*!< Source allocated Port 0      */
#define DMA_SRC_ALLOCATED_PORT1  DMA_CTR1_SAP /*!< Source allocated Port 1      */
#define DMA_DEST_ALLOCATED_PORT0 0x00000000U  /*!< Destination allocated Port 0 */
#define DMA_DEST_ALLOCATED_PORT1 DMA_CTR1_DAP /*!< Destination allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Event_Mode DMA Transfer Event Mode
  * @brief    DMA Transfer Event Mode
  * @{
  */
#define DMA_TCEM_BLOCK_TRANSFER          0x00000000U     /*!< The TC event is generated at the end of each block and the
                                                              HT event is generated at the half of each block         */
#define DMA_TCEM_REPEATED_BLOCK_TRANSFER DMA_CTR2_TCEM_0 /*!< The TC event is generated at the end of the repeated block
                                                              and the HT event is generated at the half of the repeated
                                                              block                                                   */
#define DMA_TCEM_EACH_LL_ITEM_TRANSFER   DMA_CTR2_TCEM_1 /*!< The TC event is generated at the end of each linked-list
                                                              item and the HT event is generated at the half of each
                                                              linked-list item                                        */
#define DMA_TCEM_LAST_LL_ITEM_TRANSFER   DMA_CTR2_TCEM   /*!< The TC event is generated at the end of the last
                                                              linked-list item and the HT event is generated at the half
                                                              of the last linked-list item                            */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Mode DMA Transfer Mode
  * @brief    DMA Transfer Mode
  * @{
  */
#define DMA_NORMAL (0x00U) /*!< Normal DMA transfer */
/**
  * @}
  */

/** @defgroup DMA_Channel_Attributes DMA Channel Attributes
  * @brief    DMA Channel Security and Privilege Attributes
  * @note     Secure and non-secure attributes are only available from the secure world when TZEN = 1
  * @{
  */
#define DMA_CHANNEL_PRIV      (DMA_CHANNEL_ATTR_PRIV_MASK | 0x01U)     /*!< Channel is privileged             */
#define DMA_CHANNEL_NPRIV     (DMA_CHANNEL_ATTR_PRIV_MASK)             /*!< Channel is unprivileged           */

#define DMA_CHANNEL_SEC       (DMA_CHANNEL_ATTR_SEC_MASK | 0x02U)      /*!< Channel is secure                 */
#define DMA_CHANNEL_NSEC      (DMA_CHANNEL_ATTR_SEC_MASK)              /*!< Channel is non-secure             */
#define DMA_CHANNEL_SRC_SEC   (DMA_CHANNEL_ATTR_SEC_SRC_MASK | 0x04U)  /*!< Channel source is secure          */
#define DMA_CHANNEL_SRC_NSEC  (DMA_CHANNEL_ATTR_SEC_SRC_MASK)          /*!< Channel source is non-secure      */
#define DMA_CHANNEL_DEST_SEC  (DMA_CHANNEL_ATTR_SEC_DEST_MASK | 0x08U) /*!< Channel destination is secure     */
#define DMA_CHANNEL_DEST_NSEC (DMA_CHANNEL_ATTR_SEC_DEST_MASK)         /*!< Channel destination is non-secure */

#define DMA_CHANNEL_ATTRIBUTE_UNLOCKED (0x00U)                         /*!< Channel attribute is unlocked     */
#define DMA_CHANNEL_ATTRIBUTE_LOCKED   (0x01U)                         /*!< Channel attribute is locked       */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Macros DMA Exported Macros
  * @brief    DMA Exported Macros
  * @{
  */

/** @brief  Reset DMA handle state.
  * @param  __HANDLE__ : DMA handle.
  * @retval None.
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) \
  ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__ : DMA handle.
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__) \
  ((__HANDLE__)->Instance->CCR |=  DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param  __HANDLE__ : DMA handle.
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__) \
  ((__HANDLE__)->Instance->CCR |= (DMA_CCR_SUSP | DMA_CCR_RESET))

/**
  * @brief  Get the DMA channel pending flags.
  * @param  __HANDLE__ : DMA handle.
  * @param  __FLAG__   : Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TC    : Transfer Complete flag.
  *            @arg DMA_FLAG_HT    : Half Transfer Complete flag.
  *            @arg DMA_FLAG_DTE   : Data Transfer Error flag.
  *            @arg DMA_FLAG_ULE   : Update linked-list Error flag.
  *            @arg DMA_FLAG_USE   : User Setting Error flag.
  *            @arg DMA_FLAG_TO    : Trigger Overrun flag.
  *            @arg DMA_FLAG_SUSP  : Completed Suspension flag.
  *            @arg DMA_FLAG_IDLEF : Idle flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) \
  ((__HANDLE__)->Instance->CSR & (__FLAG__))

/**
  * @brief  Clear the DMA Channel pending flags.
  * @param  __HANDLE__ : DMA handle.
  * @param  __FLAG__   : Specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TC   : Transfer Complete flag.
  *            @arg DMA_FLAG_HT   : Half Transfer Complete flag.
  *            @arg DMA_FLAG_DTE  : Data Transfer Error flag.
  *            @arg DMA_FLAG_ULE  : Update Linked-List Error flag.
  *            @arg DMA_FLAG_USE  : User Setting Error flag.
  *            @arg DMA_FLAG_TO   : Trigger Overrun flag.
  *            @arg DMA_FLAG_SUSP : Completed Suspension flag.
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
  ((__HANDLE__)->Instance->CFCR = (__FLAG__))

/**
  * @brief  Enable the specified DMA Channel interrupts.
  * @param  __HANDLE__    : DMA handle.
  * @param  __INTERRUPT__ : Specifies the DMA interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC   : Transfer Complete interrupt.
  *            @arg DMA_IT_HT   : Half Transfer Complete interrupt.
  *            @arg DMA_IT_DTE  : Data Transfer Error interrupt.
  *            @arg DMA_IT_ULE  : Update Linked-List Error interrupt.
  *            @arg DMA_IT_USE  : User Setting Error interrupt.
  *            @arg DMA_IT_TO   : Trigger Overrun interrupt.
  *            @arg DMA_IT_SUSP : Completed Suspension interrupt.
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
  ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA Channel interrupts.
  * @param  __HANDLE__   : DMA handle.
  * @param __INTERRUPT__ : specifies the DMA interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC   : Transfer Complete interrupt.
  *            @arg DMA_IT_HT   : Half Transfer Complete interrupt.
  *            @arg DMA_IT_DTE  : Data Transfer Error interrupt.
  *            @arg DMA_IT_ULE  : Update Linked-List Error interrupt.
  *            @arg DMA_IT_USE  : User Setting Error interrupt.
  *            @arg DMA_IT_TO   : Trigger Overrun interrupt.
  *            @arg DMA_IT_SUSP : Completed Suspension interrupt.
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Checks whether the specified DMA Channel interrupt is enabled or not.
  * @param  __HANDLE__    : DMA handle.
  * @param  __INTERRUPT__ : specifies the DMA interrupt source to check.
  *            @arg DMA_IT_TC   : Transfer Complete interrupt.
  *            @arg DMA_IT_HT   : Half Transfer Complete interrupt.
  *            @arg DMA_IT_DTE  : Data Transfer Error interrupt.
  *            @arg DMA_IT_ULE  : Update Linked-List Error interrupt.
  *            @arg DMA_IT_USE  : User Setting Error interrupt.
  *            @arg DMA_IT_TO   : Trigger Overrun interrupt.
  *            @arg DMA_IT_SUSP : Completed Suspension interrupt.
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @brief  Writes the block number of bytes to be transferred from the source on the DMA Channel.
  * @param  __HANDLE__  : DMA handle.
  * @param  __COUNTER__ : Number of data bytes to be transferred from the source (from 0 to 65535).
  */
#define __HAL_DMA_SET_COUNTER(__HANDLE__, __COUNTER__) \
  MODIFY_REG((__HANDLE__)->Instance->CBR1, DMA_CBR1_BNDT, (__COUNTER__))

/**
  * @brief  Returns the number of remaining data bytes in the current DMA Channel transfer.
  * @param  __HANDLE__ : DMA handle.
  * @retval The number of remaining data units in the current DMA Stream transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) \
  (((__HANDLE__)->Instance->CBR1) & DMA_CBR1_BNDT)
/**
  * @}
  */


/* Include DMA HAL Extension module */
#include "stm32u5xx_hal_dma_ex.h"


/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Functions DMA Exported Functions
  * @brief    DMA Exported Functions
  * @{
  */

/** @defgroup DMA_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @brief    Initialization and De-Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *const hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group2 I/O Operation Functions
  * @brief    I/O Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *const hdma,
                                uint32_t SrcAddress,
                                uint32_t DstAddress,
                                uint32_t SrcDataSize);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *const hdma,
                                   uint32_t SrcAddress,
                                   uint32_t DstAddress,
                                   uint32_t SrcDataSize);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *const hdma,
                                          HAL_DMA_LevelCompleteTypeDef CompleteLevel,
                                          uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *const hdma,
                                           HAL_DMA_CallbackIDTypeDef CallbackID,
                                           void (*const  pCallback)(DMA_HandleTypeDef *const _hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *const hdma,
                                             HAL_DMA_CallbackIDTypeDef CallbackID);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group3 State and Error Functions
  * @brief    State and Error Functions
  * @{
  */
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef const *const hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef const *const hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group4 DMA Attributes Functions
  * @brief    DMA Attributes Functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_ConfigChannelAttributes(DMA_HandleTypeDef *const hdma,
                                                  uint32_t ChannelAttributes);
HAL_StatusTypeDef HAL_DMA_GetConfigChannelAttributes(DMA_HandleTypeDef const *const hdma,
                                                     uint32_t *const pChannelAttributes);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_DMA_LockChannelAttributes(DMA_HandleTypeDef const *const hdma);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
HAL_StatusTypeDef HAL_DMA_GetLockChannelAttributes(DMA_HandleTypeDef const *const hdma,
                                                   uint32_t *const pLockState);

/**
  * @}
  */

/**
  * @}
  */


/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Constants DMA Private Constants
  * @brief    DMA Private Constants
  * @{
  */
#define HAL_TIMEOUT_DMA_ABORT          (0x00000005U) /* DMA channel abort timeout 5 milli-second */
#define HAL_DMA_CHANNEL_START          (0x00000050U) /* DMA channel offset                       */
#define HAL_DMA_CHANNEL_SIZE           (0x00000080U) /* DMA channel size                         */
#define HAL_DMA_OFFSET_MASK            (0x00000FFFU) /* DMA channel offset mask                  */
#define DMA_CHANNEL_ATTR_PRIV_MASK     (0x00000010U) /* DMA channel privilege mask               */
#define DMA_CHANNEL_ATTR_SEC_MASK      (0x00000020U) /* DMA channel secure mask                  */
#define DMA_CHANNEL_ATTR_SEC_SRC_MASK  (0x00000040U) /* DMA channel source secure mask           */
#define DMA_CHANNEL_ATTR_SEC_DEST_MASK (0x00000080U) /* DMA channel destination secure mask      */
#define DMA_CHANNEL_ATTR_VALUE_MASK    (0x0000000FU) /* DMA channel attributes value mask        */
#define DMA_CHANNEL_ATTR_ITEM_MASK     (0x000000F0U) /* DMA channel attributes item mask         */
#define DMA_CHANNEL_BURST_MIN          (0x00000001U) /* DMA channel minimum burst size           */
#define DMA_CHANNEL_BURST_MAX          (0x00000040U) /* DMA channel maximum burst size           */
/**
  * @}
  */


/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @brief    DMA Private Macros
  * @{
  */
#define GET_DMA_INSTANCE(__HANDLE__) \
  ((DMA_TypeDef *)((uint32_t)((__HANDLE__)->Instance) & (~HAL_DMA_OFFSET_MASK)))

#define GET_DMA_CHANNEL(__HANDLE__) \
  ((((uint32_t)((__HANDLE__)->Instance) & HAL_DMA_OFFSET_MASK) - HAL_DMA_CHANNEL_START) / HAL_DMA_CHANNEL_SIZE)

#define IS_DMA_MODE(MODE) \
  ((MODE) == DMA_NORMAL)

#define IS_DMA_DIRECTION(DIRECTION)         \
  (((DIRECTION) == DMA_PERIPH_TO_MEMORY) || \
   ((DIRECTION) == DMA_MEMORY_TO_PERIPH) || \
   ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_LEVEL_COMPLETE(LEVEL)     \
  (((LEVEL) == HAL_DMA_FULL_TRANSFER) || \
   ((LEVEL) == HAL_DMA_HALF_TRANSFER))

#define IS_DMA_SOURCE_INC(INC)  \
  (((INC) == DMA_SINC_FIXED) || \
   ((INC) == DMA_SINC_INCREMENTED))

#define IS_DMA_DESTINATION_INC(INC) \
  (((INC) == DMA_DINC_FIXED)     || \
   ((INC) == DMA_DINC_INCREMENTED))

#define IS_DMA_SOURCE_DATA_WIDTH(WIDTH)       \
  (((WIDTH) == DMA_SRC_DATAWIDTH_BYTE)     || \
   ((WIDTH) == DMA_SRC_DATAWIDTH_HALFWORD) || \
   ((WIDTH) == DMA_SRC_DATAWIDTH_WORD))

#define IS_DMA_DESTINATION_DATA_WIDTH(WIDTH)   \
  (((WIDTH) == DMA_DEST_DATAWIDTH_BYTE)     || \
   ((WIDTH) == DMA_DEST_DATAWIDTH_HALFWORD) || \
   ((WIDTH) == DMA_DEST_DATAWIDTH_WORD))

#define IS_DMA_BURST_LENGTH(LENGTH)       \
  (((LENGTH) >= DMA_CHANNEL_BURST_MIN) && \
   ((LENGTH) <= DMA_CHANNEL_BURST_MAX))

#define IS_DMA_PRIORITY(PRIORITY)                  \
  (((PRIORITY) == DMA_LOW_PRIORITY_LOW_WEIGHT)  || \
   ((PRIORITY) == DMA_LOW_PRIORITY_MID_WEIGHT)  || \
   ((PRIORITY) == DMA_LOW_PRIORITY_HIGH_WEIGHT) || \
   ((PRIORITY) == DMA_HIGH_PRIORITY))

#define  IS_DMA_TRANSFER_ALLOCATED_PORT(ALLOCATED_PORT) \
  (((ALLOCATED_PORT) & (~(DMA_CTR1_SAP | DMA_CTR1_DAP))) == 0U)

#define IS_DMA_REQUEST(REQUEST)     \
  (((REQUEST) == DMA_REQUEST_SW) || \
   ((REQUEST) <= GPDMA1_REQUEST_LPTIM3_UE))

#define IS_DMA_BLOCK_HW_REQUEST(MODE)   \
  (((MODE) == DMA_BREQ_SINGLE_BURST) || \
   ((MODE) == DMA_BREQ_BLOCK))

#define IS_DMA_TCEM_EVENT_MODE(MODE)               \
  (((MODE) == DMA_TCEM_BLOCK_TRANSFER)          || \
   ((MODE) == DMA_TCEM_REPEATED_BLOCK_TRANSFER) || \
   ((MODE) == DMA_TCEM_EACH_LL_ITEM_TRANSFER)   || \
   ((MODE) == DMA_TCEM_LAST_LL_ITEM_TRANSFER))

#define IS_DMA_BLOCK_SIZE(SIZE) \
  (((SIZE) > 0U) && ((SIZE) <= DMA_CBR1_BNDT))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_DMA_ATTRIBUTES(ATTRIBUTE)                                                                               \
  (((ATTRIBUTE) != 0U) && (((ATTRIBUTE) & (~(DMA_CHANNEL_ATTR_VALUE_MASK | DMA_CHANNEL_ATTR_ITEM_MASK))) == 0U) && \
   (((((ATTRIBUTE) & DMA_CHANNEL_ATTR_ITEM_MASK) >> 4U) | ((ATTRIBUTE) & DMA_CHANNEL_ATTR_VALUE_MASK)) ==          \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_ITEM_MASK) >> 4U)))
#else
#define IS_DMA_ATTRIBUTES(ATTRIBUTE)    \
  (((ATTRIBUTE) == DMA_CHANNEL_PRIV) || \
   ((ATTRIBUTE) == DMA_CHANNEL_NPRIV))
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_DMA_GLOBAL_ACTIVE_FLAG(INSTANCE, GLOBAL_FLAG) \
  (((INSTANCE)->SMISR & (GLOBAL_FLAG)))
#else
#define IS_DMA_GLOBAL_ACTIVE_FLAG(INSTANCE, GLOBAL_FLAG) \
  (((INSTANCE)->MISR & (GLOBAL_FLAG)))
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */


/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Functions DMA Private Functions
  * @brief    DMA Private Functions
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_HAL_DMA_H */
