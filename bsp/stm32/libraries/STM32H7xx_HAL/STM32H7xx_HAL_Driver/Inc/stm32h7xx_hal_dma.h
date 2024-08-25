/**
  ******************************************************************************
  * @file    stm32h7xx_hal_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_DMA_H
#define STM32H7xx_HAL_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA Exported Types
  * @brief    DMA Exported Types
  * @{
  */

/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct
{
  uint32_t Request;               /*!< Specifies the request selected for the specified stream.
                                           This parameter can be a value of @ref DMA_Request_selection              */

  uint32_t Direction;            /*!< Specifies if the data will be transferred from memory to peripheral,
                                      from memory to memory or from peripheral to memory.
                                      This parameter can be a value of @ref DMA_Data_transfer_direction              */

  uint32_t PeriphInc;            /*!< Specifies whether the Peripheral address register should be incremented or not.
                                      This parameter can be a value of @ref DMA_Peripheral_incremented_mode          */

  uint32_t MemInc;               /*!< Specifies whether the memory address register should be incremented or not.
                                      This parameter can be a value of @ref DMA_Memory_incremented_mode              */

  uint32_t PeriphDataAlignment;  /*!< Specifies the Peripheral data width.
                                      This parameter can be a value of @ref DMA_Peripheral_data_size                 */

  uint32_t MemDataAlignment;     /*!< Specifies the Memory data width.
                                      This parameter can be a value of @ref DMA_Memory_data_size                     */

  uint32_t Mode;                 /*!< Specifies the operation mode of the DMAy Streamx.
                                      This parameter can be a value of @ref DMA_mode
                                      @note The circular buffer mode cannot be used if the memory-to-memory
                                            data transfer is configured on the selected Stream                        */

  uint32_t Priority;             /*!< Specifies the software priority for the DMAy Streamx.
                                      This parameter can be a value of @ref DMA_Priority_level                        */

  uint32_t FIFOMode;             /*!< Specifies if the FIFO mode or Direct mode will be used for the specified stream.
                                      This parameter can be a value of @ref DMA_FIFO_direct_mode
                                      @note The Direct mode (FIFO mode disabled) cannot be used if the
                                            memory-to-memory data transfer is configured on the selected stream       */

  uint32_t FIFOThreshold;        /*!< Specifies the FIFO threshold level.
                                      This parameter can be a value of @ref DMA_FIFO_threshold_level                  */

  uint32_t MemBurst;             /*!< Specifies the Burst transfer configuration for the memory transfers.
                                      It specifies the amount of data to be transferred in a single non interruptible
                                      transaction.
                                      This parameter can be a value of @ref DMA_Memory_burst
                                      @note The burst mode is possible only if the address Increment mode is enabled. */

  uint32_t PeriphBurst;          /*!< Specifies the Burst transfer configuration for the peripheral transfers.
                                      It specifies the amount of data to be transferred in a single non interruptible
                                      transaction.
                                      This parameter can be a value of @ref DMA_Peripheral_burst
                                      @note The burst mode is possible only if the address Increment mode is enabled. */
}DMA_InitTypeDef;

/**
  * @brief  HAL DMA State structures definition
  */
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,  /*!< DMA not yet initialized or disabled */
  HAL_DMA_STATE_READY             = 0x01U,  /*!< DMA initialized and ready for use   */
  HAL_DMA_STATE_BUSY              = 0x02U,  /*!< DMA process is ongoing              */
  HAL_DMA_STATE_ERROR             = 0x03U,  /*!< DMA error state                     */
  HAL_DMA_STATE_ABORT             = 0x04U,  /*!< DMA Abort state                     */
}HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Transfer complete level structure definition
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER      = 0x00U,    /*!< Full transfer     */
  HAL_DMA_HALF_TRANSFER      = 0x01U,    /*!< Half Transfer     */
}HAL_DMA_LevelCompleteTypeDef;

/**
  * @brief  HAL DMA Callbacks IDs structure definition
  */
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID          = 0x00U,    /*!< Full transfer     */
  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,    /*!< Half Transfer     */
  HAL_DMA_XFER_M1CPLT_CB_ID        = 0x02U,    /*!< M1 Full Transfer  */
  HAL_DMA_XFER_M1HALFCPLT_CB_ID    = 0x03U,    /*!< M1 Half Transfer  */
  HAL_DMA_XFER_ERROR_CB_ID         = 0x04U,    /*!< Error             */
  HAL_DMA_XFER_ABORT_CB_ID         = 0x05U,    /*!< Abort             */
  HAL_DMA_XFER_ALL_CB_ID           = 0x06U     /*!< All               */
}HAL_DMA_CallbackIDTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  void                            *Instance;                                                        /*!< Register base address                         */

  DMA_InitTypeDef                 Init;                                                             /*!< DMA communication parameters                  */

  HAL_LockTypeDef                 Lock;                                                             /*!< DMA locking object                            */

  __IO HAL_DMA_StateTypeDef       State;                                                            /*!< DMA transfer state                            */

  void                            *Parent;                                                          /*!< Parent object state                           */

  void                            (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);         /*!< DMA transfer complete callback                */

  void                            (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);     /*!< DMA Half transfer complete callback           */

  void                            (* XferM1CpltCallback)( struct __DMA_HandleTypeDef * hdma);       /*!< DMA transfer complete Memory1 callback        */

  void                            (* XferM1HalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);   /*!< DMA transfer Half complete Memory1 callback   */

  void                            (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);        /*!< DMA transfer error callback                   */

  void                            (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);        /*!< DMA transfer Abort callback                   */

 __IO uint32_t                    ErrorCode;                                                        /*!< DMA Error code                                */

 uint32_t                         StreamBaseAddress;                                                /*!< DMA Stream Base Address                       */

 uint32_t                         StreamIndex;                                                      /*!< DMA Stream Index                              */

 DMAMUX_Channel_TypeDef           *DMAmuxChannel;                                                   /*!< DMAMUX Channel Base Address                   */

 DMAMUX_ChannelStatus_TypeDef     *DMAmuxChannelStatus;                                             /*!< DMAMUX Channels Status Base Address           */

 uint32_t                         DMAmuxChannelStatusMask;                                          /*!< DMAMUX Channel Status Mask                    */


 DMAMUX_RequestGen_TypeDef        *DMAmuxRequestGen;                                                /*!< DMAMUX request generator Base Address         */

 DMAMUX_RequestGenStatus_TypeDef  *DMAmuxRequestGenStatus;                                          /*!< DMAMUX request generator Status Address       */

 uint32_t                         DMAmuxRequestGenStatusMask;                                       /*!< DMAMUX request generator Status mask          */

}DMA_HandleTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @brief    DMA Exported constants
  * @{
  */

/** @defgroup DMA_Error_Code DMA Error Code
  * @brief    DMA Error Code
  * @{
  */
#define HAL_DMA_ERROR_NONE            (0x00000000U)    /*!< No error                                */
#define HAL_DMA_ERROR_TE              (0x00000001U)    /*!< Transfer error                          */
#define HAL_DMA_ERROR_FE              (0x00000002U)    /*!< FIFO error                              */
#define HAL_DMA_ERROR_DME             (0x00000004U)    /*!< Direct Mode error                       */
#define HAL_DMA_ERROR_TIMEOUT         (0x00000020U)    /*!< Timeout error                           */
#define HAL_DMA_ERROR_PARAM           (0x00000040U)    /*!< Parameter error                         */
#define HAL_DMA_ERROR_NO_XFER         (0x00000080U)    /*!< Abort requested with no Xfer ongoing    */
#define HAL_DMA_ERROR_NOT_SUPPORTED   (0x00000100U)    /*!< Not supported mode                      */
#define HAL_DMA_ERROR_SYNC            (0x00000200U)    /*!< DMAMUX sync overrun  error              */
#define HAL_DMA_ERROR_REQGEN          (0x00000400U)    /*!< DMAMUX request generator overrun  error */
#define HAL_DMA_ERROR_BUSY            (0x00000800U)    /*!< DMA Busy                          error */

/**
  * @}
  */

/** @defgroup DMA_Request_selection DMA Request selection
  * @brief    DMA Request selection
  * @{
  */
/* DMAMUX1 requests */
#define DMA_REQUEST_MEM2MEM          0U  /*!< memory to memory transfer   */

#define DMA_REQUEST_GENERATOR0       1U  /*!< DMAMUX1 request generator 0 */
#define DMA_REQUEST_GENERATOR1       2U  /*!< DMAMUX1 request generator 1 */
#define DMA_REQUEST_GENERATOR2       3U  /*!< DMAMUX1 request generator 2 */
#define DMA_REQUEST_GENERATOR3       4U  /*!< DMAMUX1 request generator 3 */
#define DMA_REQUEST_GENERATOR4       5U  /*!< DMAMUX1 request generator 4 */
#define DMA_REQUEST_GENERATOR5       6U  /*!< DMAMUX1 request generator 5 */
#define DMA_REQUEST_GENERATOR6       7U  /*!< DMAMUX1 request generator 6 */
#define DMA_REQUEST_GENERATOR7       8U  /*!< DMAMUX1 request generator 7 */

#define DMA_REQUEST_ADC1             9U  /*!< DMAMUX1 ADC1 request */
#define DMA_REQUEST_ADC2             10U /*!< DMAMUX1 ADC2 request */

#define DMA_REQUEST_TIM1_CH1         11U  /*!< DMAMUX1 TIM1 CH1 request  */
#define DMA_REQUEST_TIM1_CH2         12U  /*!< DMAMUX1 TIM1 CH2 request  */
#define DMA_REQUEST_TIM1_CH3         13U  /*!< DMAMUX1 TIM1 CH3 request  */
#define DMA_REQUEST_TIM1_CH4         14U  /*!< DMAMUX1 TIM1 CH4 request  */
#define DMA_REQUEST_TIM1_UP          15U  /*!< DMAMUX1 TIM1 UP request   */
#define DMA_REQUEST_TIM1_TRIG        16U  /*!< DMAMUX1 TIM1 TRIG request */
#define DMA_REQUEST_TIM1_COM         17U  /*!< DMAMUX1 TIM1 COM request  */

#define DMA_REQUEST_TIM2_CH1         18U  /*!< DMAMUX1 TIM2 CH1 request  */
#define DMA_REQUEST_TIM2_CH2         19U  /*!< DMAMUX1 TIM2 CH2 request  */
#define DMA_REQUEST_TIM2_CH3         20U  /*!< DMAMUX1 TIM2 CH3 request  */
#define DMA_REQUEST_TIM2_CH4         21U  /*!< DMAMUX1 TIM2 CH4 request  */
#define DMA_REQUEST_TIM2_UP          22U  /*!< DMAMUX1 TIM2 UP request   */

#define DMA_REQUEST_TIM3_CH1         23U  /*!< DMAMUX1 TIM3 CH1 request  */
#define DMA_REQUEST_TIM3_CH2         24U  /*!< DMAMUX1 TIM3 CH2 request  */
#define DMA_REQUEST_TIM3_CH3         25U  /*!< DMAMUX1 TIM3 CH3 request  */
#define DMA_REQUEST_TIM3_CH4         26U  /*!< DMAMUX1 TIM3 CH4 request  */
#define DMA_REQUEST_TIM3_UP          27U  /*!< DMAMUX1 TIM3 UP request   */
#define DMA_REQUEST_TIM3_TRIG        28U  /*!< DMAMUX1 TIM3 TRIG request */

#define DMA_REQUEST_TIM4_CH1         29U  /*!< DMAMUX1 TIM4 CH1 request  */
#define DMA_REQUEST_TIM4_CH2         30U  /*!< DMAMUX1 TIM4 CH2 request  */
#define DMA_REQUEST_TIM4_CH3         31U  /*!< DMAMUX1 TIM4 CH3 request  */
#define DMA_REQUEST_TIM4_UP          32U  /*!< DMAMUX1 TIM4 UP request   */

#define DMA_REQUEST_I2C1_RX          33U  /*!< DMAMUX1 I2C1 RX request   */
#define DMA_REQUEST_I2C1_TX          34U  /*!< DMAMUX1 I2C1 TX request   */
#define DMA_REQUEST_I2C2_RX          35U  /*!< DMAMUX1 I2C2 RX request   */
#define DMA_REQUEST_I2C2_TX          36U  /*!< DMAMUX1 I2C2 TX request   */

#define DMA_REQUEST_SPI1_RX          37U  /*!< DMAMUX1 SPI1 RX request   */
#define DMA_REQUEST_SPI1_TX          38U  /*!< DMAMUX1 SPI1 TX request   */
#define DMA_REQUEST_SPI2_RX          39U  /*!< DMAMUX1 SPI2 RX request   */
#define DMA_REQUEST_SPI2_TX          40U  /*!< DMAMUX1 SPI2 TX request   */

#define DMA_REQUEST_USART1_RX        41U  /*!< DMAMUX1 USART1 RX request */
#define DMA_REQUEST_USART1_TX        42U  /*!< DMAMUX1 USART1 TX request */
#define DMA_REQUEST_USART2_RX        43U  /*!< DMAMUX1 USART2 RX request */
#define DMA_REQUEST_USART2_TX        44U  /*!< DMAMUX1 USART2 TX request */
#define DMA_REQUEST_USART3_RX        45U  /*!< DMAMUX1 USART3 RX request */
#define DMA_REQUEST_USART3_TX        46U  /*!< DMAMUX1 USART3 TX request */

#define DMA_REQUEST_TIM8_CH1         47U  /*!< DMAMUX1 TIM8 CH1 request  */
#define DMA_REQUEST_TIM8_CH2         48U  /*!< DMAMUX1 TIM8 CH2 request  */
#define DMA_REQUEST_TIM8_CH3         49U  /*!< DMAMUX1 TIM8 CH3 request  */
#define DMA_REQUEST_TIM8_CH4         50U  /*!< DMAMUX1 TIM8 CH4 request  */
#define DMA_REQUEST_TIM8_UP          51U  /*!< DMAMUX1 TIM8 UP request   */
#define DMA_REQUEST_TIM8_TRIG        52U  /*!< DMAMUX1 TIM8 TRIG request */
#define DMA_REQUEST_TIM8_COM         53U  /*!< DMAMUX1 TIM8 COM request  */

#define DMA_REQUEST_TIM5_CH1         55U  /*!< DMAMUX1 TIM5 CH1 request  */
#define DMA_REQUEST_TIM5_CH2         56U  /*!< DMAMUX1 TIM5 CH2 request  */
#define DMA_REQUEST_TIM5_CH3         57U  /*!< DMAMUX1 TIM5 CH3 request  */
#define DMA_REQUEST_TIM5_CH4         58U  /*!< DMAMUX1 TIM5 CH4 request  */
#define DMA_REQUEST_TIM5_UP          59U  /*!< DMAMUX1 TIM5 UP request   */
#define DMA_REQUEST_TIM5_TRIG        60U  /*!< DMAMUX1 TIM5 TRIG request */

#define DMA_REQUEST_SPI3_RX          61U  /*!< DMAMUX1 SPI3 RX request   */
#define DMA_REQUEST_SPI3_TX          62U  /*!< DMAMUX1 SPI3 TX request   */

#define DMA_REQUEST_UART4_RX         63U  /*!< DMAMUX1 UART4 RX request */
#define DMA_REQUEST_UART4_TX         64U  /*!< DMAMUX1 UART4 TX request */
#define DMA_REQUEST_UART5_RX         65U  /*!< DMAMUX1 UART5 RX request */
#define DMA_REQUEST_UART5_TX         66U  /*!< DMAMUX1 UART5 TX request */

#define DMA_REQUEST_DAC1_CH1         67U  /*!< DMAMUX1 DAC1 Channel 1 request */
#define DMA_REQUEST_DAC1_CH2         68U  /*!< DMAMUX1 DAC1 Channel 2 request */

#define DMA_REQUEST_TIM6_UP          69U  /*!< DMAMUX1 TIM6 UP request   */
#define DMA_REQUEST_TIM7_UP          70U  /*!< DMAMUX1 TIM7 UP request   */

#define DMA_REQUEST_USART6_RX        71U  /*!< DMAMUX1 USART6 RX request */
#define DMA_REQUEST_USART6_TX        72U  /*!< DMAMUX1 USART6 TX request */

#define DMA_REQUEST_I2C3_RX          73U  /*!< DMAMUX1 I2C3 RX request   */
#define DMA_REQUEST_I2C3_TX          74U  /*!< DMAMUX1 I2C3 TX request   */

#if defined (PSSI)
#define DMA_REQUEST_DCMI_PSSI        75U  /*!< DMAMUX1 DCMI/PSSI request    */
#define DMA_REQUEST_DCMI             DMA_REQUEST_DCMI_PSSI /* Legacy define */
#else
#define DMA_REQUEST_DCMI             75U  /*!< DMAMUX1 DCMI request         */
#endif /* PSSI */

#define DMA_REQUEST_CRYP_IN          76U  /*!< DMAMUX1 CRYP IN request   */
#define DMA_REQUEST_CRYP_OUT         77U  /*!< DMAMUX1 CRYP OUT request  */

#define DMA_REQUEST_HASH_IN          78U  /*!< DMAMUX1 HASH IN request   */

#define DMA_REQUEST_UART7_RX         79U  /*!< DMAMUX1 UART7 RX request  */
#define DMA_REQUEST_UART7_TX         80U  /*!< DMAMUX1 UART7 TX request  */
#define DMA_REQUEST_UART8_RX         81U  /*!< DMAMUX1 UART8 RX request  */
#define DMA_REQUEST_UART8_TX         82U  /*!< DMAMUX1 UART8 TX request  */

#define DMA_REQUEST_SPI4_RX          83U  /*!< DMAMUX1 SPI4 RX request   */
#define DMA_REQUEST_SPI4_TX          84U  /*!< DMAMUX1 SPI4 TX request   */
#define DMA_REQUEST_SPI5_RX          85U  /*!< DMAMUX1 SPI5 RX request   */
#define DMA_REQUEST_SPI5_TX          86U  /*!< DMAMUX1 SPI5 TX request   */

#define DMA_REQUEST_SAI1_A           87U  /*!< DMAMUX1 SAI1 A request    */
#define DMA_REQUEST_SAI1_B           88U  /*!< DMAMUX1 SAI1 B request    */

#if defined(SAI2)
#define DMA_REQUEST_SAI2_A           89U  /*!< DMAMUX1 SAI2 A request    */
#define DMA_REQUEST_SAI2_B           90U  /*!< DMAMUX1 SAI2 B request    */
#endif /* SAI2 */

#define DMA_REQUEST_SWPMI_RX         91U  /*!< DMAMUX1 SWPMI RX request  */
#define DMA_REQUEST_SWPMI_TX         92U  /*!< DMAMUX1 SWPMI TX request  */

#define DMA_REQUEST_SPDIF_RX_DT      93U  /*!< DMAMUX1 SPDIF RXDT request*/
#define DMA_REQUEST_SPDIF_RX_CS      94U  /*!< DMAMUX1 SPDIF RXCS request*/

#if defined(HRTIM1)
#define DMA_REQUEST_HRTIM_MASTER     95U  /*!< DMAMUX1 HRTIM1 Master request 1 */
#define DMA_REQUEST_HRTIM_TIMER_A    96U  /*!< DMAMUX1 HRTIM1 Timer A request 2 */
#define DMA_REQUEST_HRTIM_TIMER_B    97U  /*!< DMAMUX1 HRTIM1 Timer B request 3 */
#define DMA_REQUEST_HRTIM_TIMER_C    98U  /*!< DMAMUX1 HRTIM1 Timer C request 4 */
#define DMA_REQUEST_HRTIM_TIMER_D    99U  /*!< DMAMUX1 HRTIM1 Timer D request 5 */
#define DMA_REQUEST_HRTIM_TIMER_E   100U  /*!< DMAMUX1 HRTIM1 Timer E request 6*/
#endif /* HRTIM1 */

#define DMA_REQUEST_DFSDM1_FLT0     101U  /*!< DMAMUX1 DFSDM Filter0 request */
#define DMA_REQUEST_DFSDM1_FLT1     102U  /*!< DMAMUX1 DFSDM Filter1 request */
#define DMA_REQUEST_DFSDM1_FLT2     103U  /*!< DMAMUX1 DFSDM Filter2 request */
#define DMA_REQUEST_DFSDM1_FLT3     104U  /*!< DMAMUX1 DFSDM Filter3 request */

#define DMA_REQUEST_TIM15_CH1       105U  /*!< DMAMUX1 TIM15 CH1 request  */
#define DMA_REQUEST_TIM15_UP        106U  /*!< DMAMUX1 TIM15 UP request   */
#define DMA_REQUEST_TIM15_TRIG      107U  /*!< DMAMUX1 TIM15 TRIG request */
#define DMA_REQUEST_TIM15_COM       108U  /*!< DMAMUX1 TIM15 COM request  */

#define DMA_REQUEST_TIM16_CH1       109U  /*!< DMAMUX1 TIM16 CH1 request  */
#define DMA_REQUEST_TIM16_UP        110U  /*!< DMAMUX1 TIM16 UP request   */

#define DMA_REQUEST_TIM17_CH1       111U  /*!< DMAMUX1 TIM17 CH1 request  */
#define DMA_REQUEST_TIM17_UP        112U  /*!< DMAMUX1 TIM17 UP request   */

#if defined(SAI3)
#define DMA_REQUEST_SAI3_A          113U  /*!< DMAMUX1 SAI3 A request  */
#define DMA_REQUEST_SAI3_B          114U  /*!< DMAMUX1 SAI3 B request  */
#endif /* SAI3 */

#if defined(ADC3)
#define DMA_REQUEST_ADC3            115U  /*!< DMAMUX1 ADC3 request  */
#endif /* ADC3 */

#if defined(UART9)
#define DMA_REQUEST_UART9_RX        116U  /*!< DMAMUX1 UART9 request  */
#define DMA_REQUEST_UART9_TX        117U  /*!< DMAMUX1 UART9 request  */
#endif /* UART9 */

#if defined(USART10)
#define DMA_REQUEST_USART10_RX      118U  /*!< DMAMUX1 USART10 request  */
#define DMA_REQUEST_USART10_TX      119U  /*!< DMAMUX1 USART10 request  */
#endif /* USART10 */

#if defined(FMAC)
#define DMA_REQUEST_FMAC_READ       120U  /*!< DMAMUX1 FMAC Read request  */
#define DMA_REQUEST_FMAC_WRITE      121U  /*!< DMAMUX1 FMAC Write request */
#endif /* FMAC */

#if defined(CORDIC)
#define DMA_REQUEST_CORDIC_READ     122U  /*!< DMAMUX1 CORDIC Read request  */
#define DMA_REQUEST_CORDIC_WRITE    123U  /*!< DMAMUX1 CORDIC Write request */
#endif /* CORDIC */

#if defined(I2C5)
#define DMA_REQUEST_I2C5_RX         124U  /*!< DMAMUX1 I2C5 RX request   */
#define DMA_REQUEST_I2C5_TX         125U  /*!< DMAMUX1 I2C5 TX request   */
#endif /* I2C5 */

#if defined(TIM23)
#define DMA_REQUEST_TIM23_CH1        126U  /*!< DMAMUX1 TIM23 CH1 request  */
#define DMA_REQUEST_TIM23_CH2        127U  /*!< DMAMUX1 TIM23 CH2 request  */
#define DMA_REQUEST_TIM23_CH3        128U  /*!< DMAMUX1 TIM23 CH3 request  */
#define DMA_REQUEST_TIM23_CH4        129U  /*!< DMAMUX1 TIM23 CH4 request  */
#define DMA_REQUEST_TIM23_UP         130U  /*!< DMAMUX1 TIM23 UP request   */
#define DMA_REQUEST_TIM23_TRIG       131U  /*!< DMAMUX1 TIM23 TRIG request */
#endif /* TIM23 */

#if defined(TIM24)
#define DMA_REQUEST_TIM24_CH1        132U  /*!< DMAMUX1 TIM24 CH1 request  */
#define DMA_REQUEST_TIM24_CH2        133U  /*!< DMAMUX1 TIM24 CH2 request  */
#define DMA_REQUEST_TIM24_CH3        134U  /*!< DMAMUX1 TIM24 CH3 request  */
#define DMA_REQUEST_TIM24_CH4        135U  /*!< DMAMUX1 TIM24 CH4 request  */
#define DMA_REQUEST_TIM24_UP         136U  /*!< DMAMUX1 TIM24 UP request   */
#define DMA_REQUEST_TIM24_TRIG       137U  /*!< DMAMUX1 TIM24 TRIG request */
#endif /* TIM24 */

/* DMAMUX2 requests */
#define BDMA_REQUEST_MEM2MEM          0U  /*!< memory to memory transfer   */
#define BDMA_REQUEST_GENERATOR0       1U  /*!< DMAMUX2 request generator 0 */
#define BDMA_REQUEST_GENERATOR1       2U  /*!< DMAMUX2 request generator 1 */
#define BDMA_REQUEST_GENERATOR2       3U  /*!< DMAMUX2 request generator 2 */
#define BDMA_REQUEST_GENERATOR3       4U  /*!< DMAMUX2 request generator 3 */
#define BDMA_REQUEST_GENERATOR4       5U  /*!< DMAMUX2 request generator 4 */
#define BDMA_REQUEST_GENERATOR5       6U  /*!< DMAMUX2 request generator 5 */
#define BDMA_REQUEST_GENERATOR6       7U  /*!< DMAMUX2 request generator 6 */
#define BDMA_REQUEST_GENERATOR7       8U  /*!< DMAMUX2 request generator 7 */
#define BDMA_REQUEST_LPUART1_RX       9U  /*!< DMAMUX2 LP_UART1_RX request */
#define BDMA_REQUEST_LPUART1_TX      10U  /*!< DMAMUX2 LP_UART1_TX request */
#define BDMA_REQUEST_SPI6_RX         11U  /*!< DMAMUX2 SPI6 RX request     */
#define BDMA_REQUEST_SPI6_TX         12U  /*!< DMAMUX2 SPI6 TX request     */
#define BDMA_REQUEST_I2C4_RX         13U  /*!< DMAMUX2 I2C4 RX request     */
#define BDMA_REQUEST_I2C4_TX         14U  /*!< DMAMUX2 I2C4 TX request     */
#if defined(SAI4)
#define BDMA_REQUEST_SAI4_A          15U  /*!< DMAMUX2 SAI4 A request      */
#define BDMA_REQUEST_SAI4_B          16U  /*!< DMAMUX2 SAI4 B request      */
#endif /* SAI4 */
#if defined(ADC3)
#define BDMA_REQUEST_ADC3            17U  /*!< DMAMUX2 ADC3 request        */
#endif /* ADC3 */
#if defined(DAC2)
#define BDMA_REQUEST_DAC2_CH1        17U  /*!< DMAMUX2 DAC2 CH1 request    */
#endif /* DAC2 */
#if defined(DFSDM2_Channel0)
#define BDMA_REQUEST_DFSDM2_FLT0     18U  /*!< DMAMUX2 DFSDM2 request      */
#endif /* DFSDM1_Channel0 */

/**
  * @}
  */

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
  * @brief    DMA data transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY         ((uint32_t)0x00000000U)      /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH         ((uint32_t)DMA_SxCR_DIR_0)  /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY         ((uint32_t)DMA_SxCR_DIR_1)  /*!< Memory to memory direction     */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
  * @brief    DMA peripheral incremented mode
  * @{
  */
#define DMA_PINC_ENABLE        ((uint32_t)DMA_SxCR_PINC)  /*!< Peripheral increment mode enable  */
#define DMA_PINC_DISABLE       ((uint32_t)0x00000000U)     /*!< Peripheral increment mode disable */
/**
  * @}
  */

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
  * @brief    DMA memory incremented mode
  * @{
  */
#define DMA_MINC_ENABLE         ((uint32_t)DMA_SxCR_MINC)  /*!< Memory increment mode enable  */
#define DMA_MINC_DISABLE        ((uint32_t)0x00000000U)     /*!< Memory increment mode disable */
/**
  * @}
  */

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @brief    DMA peripheral data size
  * @{
  */
#define DMA_PDATAALIGN_BYTE          ((uint32_t)0x00000000U)       /*!< Peripheral data alignment: Byte      */
#define DMA_PDATAALIGN_HALFWORD      ((uint32_t)DMA_SxCR_PSIZE_0)  /*!< Peripheral data alignment: HalfWord  */
#define DMA_PDATAALIGN_WORD          ((uint32_t)DMA_SxCR_PSIZE_1)  /*!< Peripheral data alignment: Word      */
/**
  * @}
  */

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @brief    DMA memory data size
  * @{
  */
#define DMA_MDATAALIGN_BYTE          ((uint32_t)0x00000000U)       /*!< Memory data alignment: Byte     */
#define DMA_MDATAALIGN_HALFWORD      ((uint32_t)DMA_SxCR_MSIZE_0)  /*!< Memory data alignment: HalfWord */
#define DMA_MDATAALIGN_WORD          ((uint32_t)DMA_SxCR_MSIZE_1)  /*!< Memory data alignment: Word     */
/**
  * @}
  */

/** @defgroup DMA_mode DMA mode
  * @brief    DMA mode
  * @{
  */
#define DMA_NORMAL              ((uint32_t)0x00000000U)                  /*!< Normal mode                                    */
#define DMA_CIRCULAR            ((uint32_t)DMA_SxCR_CIRC)                /*!< Circular mode                                  */
#define DMA_PFCTRL              ((uint32_t)DMA_SxCR_PFCTRL)              /*!< Peripheral flow control mode                   */
#define DMA_DOUBLE_BUFFER_M0    ((uint32_t)DMA_SxCR_DBM)                 /*!< Double buffer mode with first target memory M0 */
#define DMA_DOUBLE_BUFFER_M1    ((uint32_t)(DMA_SxCR_DBM | DMA_SxCR_CT)) /*!< Double buffer mode with first target memory M1 */
/**
  * @}
  */

/** @defgroup DMA_Priority_level DMA Priority level
  * @brief    DMA priority levels
  * @{
  */
#define DMA_PRIORITY_LOW             ((uint32_t)0x00000000U)    /*!< Priority level: Low       */
#define DMA_PRIORITY_MEDIUM          ((uint32_t)DMA_SxCR_PL_0)  /*!< Priority level: Medium    */
#define DMA_PRIORITY_HIGH            ((uint32_t)DMA_SxCR_PL_1)  /*!< Priority level: High      */
#define DMA_PRIORITY_VERY_HIGH       ((uint32_t)DMA_SxCR_PL)    /*!< Priority level: Very High */
/**
  * @}
  */

/** @defgroup DMA_FIFO_direct_mode DMA FIFO direct mode
  * @brief    DMA FIFO direct mode
  * @{
  */
#define DMA_FIFOMODE_DISABLE        ((uint32_t)0x00000000U)       /*!< FIFO mode disable */
#define DMA_FIFOMODE_ENABLE         ((uint32_t)DMA_SxFCR_DMDIS)  /*!< FIFO mode enable  */
/**
  * @}
  */

/** @defgroup DMA_FIFO_threshold_level DMA FIFO threshold level
  * @brief    DMA FIFO level
  * @{
  */
#define DMA_FIFO_THRESHOLD_1QUARTERFULL       ((uint32_t)0x00000000U)       /*!< FIFO threshold 1 quart full configuration  */
#define DMA_FIFO_THRESHOLD_HALFFULL           ((uint32_t)DMA_SxFCR_FTH_0)  /*!< FIFO threshold half full configuration     */
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL      ((uint32_t)DMA_SxFCR_FTH_1)  /*!< FIFO threshold 3 quarts full configuration */
#define DMA_FIFO_THRESHOLD_FULL               ((uint32_t)DMA_SxFCR_FTH)    /*!< FIFO threshold full configuration          */
/**
  * @}
  */

/** @defgroup DMA_Memory_burst DMA Memory burst
  * @brief    DMA memory burst
  * @{
  */
#define DMA_MBURST_SINGLE       ((uint32_t)0x00000000U)
#define DMA_MBURST_INC4         ((uint32_t)DMA_SxCR_MBURST_0)
#define DMA_MBURST_INC8         ((uint32_t)DMA_SxCR_MBURST_1)
#define DMA_MBURST_INC16        ((uint32_t)DMA_SxCR_MBURST)
/**
  * @}
  */

/** @defgroup DMA_Peripheral_burst DMA Peripheral burst
  * @brief    DMA peripheral burst
  * @{
  */
#define DMA_PBURST_SINGLE       ((uint32_t)0x00000000U)
#define DMA_PBURST_INC4         ((uint32_t)DMA_SxCR_PBURST_0)
#define DMA_PBURST_INC8         ((uint32_t)DMA_SxCR_PBURST_1)
#define DMA_PBURST_INC16        ((uint32_t)DMA_SxCR_PBURST)
/**
  * @}
  */

/** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @brief    DMA interrupts definition
  * @{
  */
#define DMA_IT_TC                         ((uint32_t)DMA_SxCR_TCIE)
#define DMA_IT_HT                         ((uint32_t)DMA_SxCR_HTIE)
#define DMA_IT_TE                         ((uint32_t)DMA_SxCR_TEIE)
#define DMA_IT_DME                        ((uint32_t)DMA_SxCR_DMEIE)
#define DMA_IT_FE                         ((uint32_t)0x00000080U)
/**
  * @}
  */

/** @defgroup DMA_flag_definitions DMA flag definitions
  * @brief    DMA flag definitions
  * @{
  */
#define DMA_FLAG_FEIF0_4                    ((uint32_t)0x00000001U)
#define DMA_FLAG_DMEIF0_4                   ((uint32_t)0x00000004U)
#define DMA_FLAG_TEIF0_4                    ((uint32_t)0x00000008U)
#define DMA_FLAG_HTIF0_4                    ((uint32_t)0x00000010U)
#define DMA_FLAG_TCIF0_4                    ((uint32_t)0x00000020U)
#define DMA_FLAG_FEIF1_5                    ((uint32_t)0x00000040U)
#define DMA_FLAG_DMEIF1_5                   ((uint32_t)0x00000100U)
#define DMA_FLAG_TEIF1_5                    ((uint32_t)0x00000200U)
#define DMA_FLAG_HTIF1_5                    ((uint32_t)0x00000400U)
#define DMA_FLAG_TCIF1_5                    ((uint32_t)0x00000800U)
#define DMA_FLAG_FEIF2_6                    ((uint32_t)0x00010000U)
#define DMA_FLAG_DMEIF2_6                   ((uint32_t)0x00040000U)
#define DMA_FLAG_TEIF2_6                    ((uint32_t)0x00080000U)
#define DMA_FLAG_HTIF2_6                    ((uint32_t)0x00100000U)
#define DMA_FLAG_TCIF2_6                    ((uint32_t)0x00200000U)
#define DMA_FLAG_FEIF3_7                    ((uint32_t)0x00400000U)
#define DMA_FLAG_DMEIF3_7                   ((uint32_t)0x01000000U)
#define DMA_FLAG_TEIF3_7                    ((uint32_t)0x02000000U)
#define DMA_FLAG_HTIF3_7                    ((uint32_t)0x04000000U)
#define DMA_FLAG_TCIF3_7                    ((uint32_t)0x08000000U)
/**
  * @}
  */

/** @defgroup BDMA_flag_definitions BDMA flag definitions
  * @brief    BDMA flag definitions
  * @{
  */
#define BDMA_FLAG_GL0                      ((uint32_t)0x00000001)
#define BDMA_FLAG_TC0                      ((uint32_t)0x00000002)
#define BDMA_FLAG_HT0                      ((uint32_t)0x00000004)
#define BDMA_FLAG_TE0                      ((uint32_t)0x00000008)
#define BDMA_FLAG_GL1                      ((uint32_t)0x00000010)
#define BDMA_FLAG_TC1                      ((uint32_t)0x00000020)
#define BDMA_FLAG_HT1                      ((uint32_t)0x00000040)
#define BDMA_FLAG_TE1                      ((uint32_t)0x00000080)
#define BDMA_FLAG_GL2                      ((uint32_t)0x00000100)
#define BDMA_FLAG_TC2                      ((uint32_t)0x00000200)
#define BDMA_FLAG_HT2                      ((uint32_t)0x00000400)
#define BDMA_FLAG_TE2                      ((uint32_t)0x00000800)
#define BDMA_FLAG_GL3                      ((uint32_t)0x00001000)
#define BDMA_FLAG_TC3                      ((uint32_t)0x00002000)
#define BDMA_FLAG_HT3                      ((uint32_t)0x00004000)
#define BDMA_FLAG_TE3                      ((uint32_t)0x00008000)
#define BDMA_FLAG_GL4                      ((uint32_t)0x00010000)
#define BDMA_FLAG_TC4                      ((uint32_t)0x00020000)
#define BDMA_FLAG_HT4                      ((uint32_t)0x00040000)
#define BDMA_FLAG_TE4                      ((uint32_t)0x00080000)
#define BDMA_FLAG_GL5                      ((uint32_t)0x00100000)
#define BDMA_FLAG_TC5                      ((uint32_t)0x00200000)
#define BDMA_FLAG_HT5                      ((uint32_t)0x00400000)
#define BDMA_FLAG_TE5                      ((uint32_t)0x00800000)
#define BDMA_FLAG_GL6                      ((uint32_t)0x01000000)
#define BDMA_FLAG_TC6                      ((uint32_t)0x02000000)
#define BDMA_FLAG_HT6                      ((uint32_t)0x04000000)
#define BDMA_FLAG_TE6                      ((uint32_t)0x08000000)
#define BDMA_FLAG_GL7                      ((uint32_t)0x10000000)
#define BDMA_FLAG_TC7                      ((uint32_t)0x20000000)
#define BDMA_FLAG_HT7                      ((uint32_t)0x40000000)
#define BDMA_FLAG_TE7                      ((uint32_t)0x80000000)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMA_Exported_Macros DMA Exported Macros
  * @{
  */

/** @brief Reset DMA handle state
  * @param  __HANDLE__: specifies the DMA handle.
  * @retval None
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Return the current DMA Stream FIFO filled level.
  * @param  __HANDLE__: DMA handle
  * @retval The FIFO filling state.
  *           - DMA_FIFOStatus_Less1QuarterFull: when FIFO is less than 1 quarter-full
  *                                              and not empty.
  *           - DMA_FIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *           - DMA_FIFOStatus_HalfFull: if more than 1 half-full.
  *           - DMA_FIFOStatus_3QuartersFull: if more than 3 quarters-full.
  *           - DMA_FIFOStatus_Empty: when FIFO is empty
  *           - DMA_FIFOStatus_Full: when FIFO is full
  */
#define __HAL_DMA_GET_FS(__HANDLE__) ((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))? (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->FCR & (DMA_SxFCR_FS)) : 0)

/**
  * @brief  Enable the specified DMA Stream.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__) \
((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))? (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR |=  DMA_SxCR_EN) : \
(((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR |=  BDMA_CCR_EN))

/**
  * @brief  Disable the specified DMA Stream.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__) \
((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))? (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR &=  ~DMA_SxCR_EN) : \
(((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR &=  ~BDMA_CCR_EN))

/* Interrupt & Flag management */

/**
  * @brief  Return the current DMA Stream transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */
#if defined(BDMA1)
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel0))? BDMA_FLAG_TC0  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel0))? BDMA_FLAG_TC0  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel1))? BDMA_FLAG_TC1  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel1))? BDMA_FLAG_TC1  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel2))? BDMA_FLAG_TC2  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel2))? BDMA_FLAG_TC2  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel3))? BDMA_FLAG_TC3  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel3))? BDMA_FLAG_TC3  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel4))? BDMA_FLAG_TC4  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel4))? BDMA_FLAG_TC4  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel5))? BDMA_FLAG_TC5  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel5))? BDMA_FLAG_TC5  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel6))? BDMA_FLAG_TC6  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel6))? BDMA_FLAG_TC6  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel7))? BDMA_FLAG_TC7  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel7))? BDMA_FLAG_TC7  :\
 (uint32_t)0x00000000)
#else
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_TCIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_FLAG_TC0   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_FLAG_TC1   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_FLAG_TC2   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_FLAG_TC3   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_FLAG_TC4   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_FLAG_TC5   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_FLAG_TC6   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_FLAG_TC7   :\
 (uint32_t)0x00000000)
#endif /* BDMA1 */

/**
  * @brief  Return the current DMA Stream half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */
#if defined(BDMA1)
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel0))? BDMA_FLAG_HT0  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel0))? BDMA_FLAG_HT0  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel1))? BDMA_FLAG_HT1  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel1))? BDMA_FLAG_HT1  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel2))? BDMA_FLAG_HT2  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel2))? BDMA_FLAG_HT2  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel3))? BDMA_FLAG_HT3  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel3))? BDMA_FLAG_HT3  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel4))? BDMA_FLAG_HT4  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel4))? BDMA_FLAG_HT4  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel5))? BDMA_FLAG_HT5  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel5))? BDMA_FLAG_HT5  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel6))? BDMA_FLAG_HT6  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel6))? BDMA_FLAG_HT6  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel7))? BDMA_FLAG_HT7  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel7))? BDMA_FLAG_HT7  :\
 (uint32_t)0x00000000)
#else
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_HTIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_FLAG_HT0   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_FLAG_HT1   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_FLAG_HT2   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_FLAG_HT3   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_FLAG_HT4   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_FLAG_HT5   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_FLAG_HT6   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_FLAG_HT7   :\
 (uint32_t)0x00000000)
#endif /* BDMA1 */

/**
  * @brief  Return the current DMA Stream transfer error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined(BDMA1)
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel0))? BDMA_FLAG_TE0  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel0))? BDMA_FLAG_TE0  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel1))? BDMA_FLAG_TE1  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel1))? BDMA_FLAG_TE1  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel2))? BDMA_FLAG_TE2  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel2))? BDMA_FLAG_TE2  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel3))? BDMA_FLAG_TE3  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel3))? BDMA_FLAG_TE3  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel4))? BDMA_FLAG_TE4  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel4))? BDMA_FLAG_TE4  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel5))? BDMA_FLAG_TE5  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel5))? BDMA_FLAG_TE5  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel6))? BDMA_FLAG_TE6  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel6))? BDMA_FLAG_TE6  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel7))? BDMA_FLAG_TE7  :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel7))? BDMA_FLAG_TE7  :\
 (uint32_t)0x00000000)
#else
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_TEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_FLAG_TE0   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_FLAG_TE1   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_FLAG_TE2   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_FLAG_TE3   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_FLAG_TE4   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_FLAG_TE5   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_FLAG_TE6   :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_FLAG_TE7   :\
 (uint32_t)0x00000000)
#endif /* BDMA1 */

/**
  * @brief  Return the current DMA Stream FIFO error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified FIFO error flag index.
  */
#define __HAL_DMA_GET_FE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_FEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_FEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_FEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_FEIF3_7 :\
  (uint32_t)0x00000000)

/**
  * @brief  Return the current DMA Stream direct mode error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified direct mode error flag index.
  */
#define __HAL_DMA_GET_DME_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream3))? DMA_FLAG_DMEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream3))? DMA_FLAG_DMEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream7))? DMA_FLAG_DMEIF3_7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream7))? DMA_FLAG_DMEIF3_7 :\
  (uint32_t)0x00000000)

/**
  * @brief  Returns the current BDMA Channel Global interrupt flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#if defined(BDMA1)
#define __HAL_BDMA_GET_GI_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel0))? BDMA_ISR_GIF0 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel0))? BDMA_ISR_GIF0 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel1))? BDMA_ISR_GIF1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel1))? BDMA_ISR_GIF1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel2))? BDMA_ISR_GIF2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel2))? BDMA_ISR_GIF2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel3))? BDMA_ISR_GIF3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel3))? BDMA_ISR_GIF3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel4))? BDMA_ISR_GIF4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel4))? BDMA_ISR_GIF4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel5))? BDMA_ISR_GIF5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel5))? BDMA_ISR_GIF5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel6))? BDMA_ISR_GIF6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel6))? BDMA_ISR_GIF6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA1_Channel7))? BDMA_ISR_GIF7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA2_Channel7))? BDMA_ISR_GIF7 :\
 (uint32_t)0x00000000)
#else
#define __HAL_BDMA_GET_GI_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_ISR_GIF0 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_ISR_GIF1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_ISR_GIF2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_ISR_GIF3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_ISR_GIF4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_ISR_GIF5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_ISR_GIF6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_ISR_GIF7 :\
  (uint32_t)0x00000000)
#endif /* BDMA1 */

/**
  * @brief  Get the DMA Stream pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCIFx: Transfer complete flag.
  *            @arg DMA_FLAG_HTIFx: Half transfer complete flag.
  *            @arg DMA_FLAG_TEIFx: Transfer error flag.
  *            @arg DMA_FLAG_DMEIFx: Direct mode error flag.
  *            @arg DMA_FLAG_FEIFx: FIFO error flag.
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Stream flag.
  * @retval The state of FLAG (SET or RESET).
  */
#if defined(BDMA1)
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)\
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)BDMA1_Channel7)?  (BDMA2->ISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream7  )?  (BDMA1->ISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3  )?  (DMA2->HISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7  )?  (DMA2->LISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3  )?  (DMA1->HISR & (__FLAG__)) : (DMA1->LISR & (__FLAG__)))
#else
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)\
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream7)? (BDMA->ISR & (__FLAG__))  :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)? (DMA2->HISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)? (DMA2->LISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)? (DMA1->HISR & (__FLAG__)) : (DMA1->LISR & (__FLAG__)))
#endif /* BDMA1 */

/**
  * @brief  Clear the DMA Stream pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCIFx: Transfer complete flag.
  *            @arg DMA_FLAG_HTIFx: Half transfer complete flag.
  *            @arg DMA_FLAG_TEIFx: Transfer error flag.
  *            @arg DMA_FLAG_DMEIFx: Direct mode error flag.
  *            @arg DMA_FLAG_FEIFx: FIFO error flag.
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Stream flag.
  * @retval None
  */
#if defined(BDMA1)
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)BDMA1_Channel7)? (BDMA2->IFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream7)?  (BDMA1->IFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)?  (DMA2->HIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)?  (DMA2->LIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)?  (DMA1->HIFCR = (__FLAG__)) : (DMA1->LIFCR = (__FLAG__)))
#else
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream7)? (BDMA->IFCR = (__FLAG__))  :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)? (DMA2->HIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)? (DMA2->LIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)? (DMA1->HIFCR = (__FLAG__)) : (DMA1->LIFCR = (__FLAG__)))
#endif /* BDMA1 */

#define DMA_TO_BDMA_IT(__DMA_IT__) \
((((__DMA_IT__) & (DMA_IT_TC | DMA_IT_HT | DMA_IT_TE)) == (DMA_IT_TC | DMA_IT_HT | DMA_IT_TE)) ? (BDMA_CCR_TCIE | BDMA_CCR_HTIE |BDMA_CCR_TEIE) :\
 (((__DMA_IT__) & (DMA_IT_TC | DMA_IT_HT)) == (DMA_IT_TC | DMA_IT_HT)) ? (BDMA_CCR_TCIE | BDMA_CCR_HTIE) :\
 (((__DMA_IT__) & (DMA_IT_HT | DMA_IT_TE)) == (DMA_IT_HT | DMA_IT_TE)) ? (BDMA_CCR_HTIE |BDMA_CCR_TEIE)  :\
 (((__DMA_IT__) & (DMA_IT_TC | DMA_IT_TE)) == (DMA_IT_TC | DMA_IT_TE)) ? (BDMA_CCR_TCIE |BDMA_CCR_TEIE)  :\
 ((__DMA_IT__) == DMA_IT_TC) ? BDMA_CCR_TCIE :\
 ((__DMA_IT__) == DMA_IT_HT) ? BDMA_CCR_HTIE :\
 ((__DMA_IT__) == DMA_IT_TE) ? BDMA_CCR_TEIE :\
 (uint32_t)0x00000000)


#define __HAL_BDMA_CHANNEL_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
(((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR |= (DMA_TO_BDMA_IT(__INTERRUPT__)))

#define __HAL_DMA_STREAM_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((__INTERRUPT__) != DMA_IT_FE)? \
(((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR |= (__INTERRUPT__)) : (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->FCR |= (__INTERRUPT__)))

/**
  * @brief  Enable the specified DMA Stream interrupts.
  * @param  __HANDLE__: DMA handle
  * @param  __INTERRUPT__: specifies the DMA interrupt sources to be enabled or disabled.
  *        This parameter can be one of the following values:
  *           @arg DMA_IT_TC: Transfer complete interrupt mask.
  *           @arg DMA_IT_HT: Half transfer complete interrupt mask.
  *           @arg DMA_IT_TE: Transfer error interrupt mask.
  *           @arg DMA_IT_FE: FIFO error interrupt mask.
  *           @arg DMA_IT_DME: Direct mode error interrupt.
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))?\
                                                        (__HAL_DMA_STREAM_ENABLE_IT((__HANDLE__), (__INTERRUPT__))) :\
                                                        (__HAL_BDMA_CHANNEL_ENABLE_IT((__HANDLE__), (__INTERRUPT__))))


#define __HAL_BDMA_CHANNEL_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR &= ~(DMA_TO_BDMA_IT(__INTERRUPT__)))

#define __HAL_DMA_STREAM_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
(((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR &= ~(__INTERRUPT__)) : (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->FCR &= ~(__INTERRUPT__)))

/**
  * @brief  Disable the specified DMA Stream interrupts.
  * @param  __HANDLE__: DMA handle
  * @param  __INTERRUPT__: specifies the DMA interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg DMA_IT_TC: Transfer complete interrupt mask.
  *            @arg DMA_IT_HT: Half transfer complete interrupt mask.
  *            @arg DMA_IT_TE: Transfer error interrupt mask.
  *            @arg DMA_IT_FE: FIFO error interrupt mask.
  *            @arg DMA_IT_DME: Direct mode error interrupt.
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))?\
                                                         (__HAL_DMA_STREAM_DISABLE_IT((__HANDLE__), (__INTERRUPT__))) :\
                                                         (__HAL_BDMA_CHANNEL_DISABLE_IT((__HANDLE__), (__INTERRUPT__))))


#define __HAL_BDMA_CHANNEL_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR & (DMA_TO_BDMA_IT(__INTERRUPT__))))

#define __HAL_DMA_STREAM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
                                                        (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR & (__INTERRUPT__)) : \
                                                        (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->FCR & (__INTERRUPT__)))

/**
  * @brief  Check whether the specified DMA Stream interrupt is enabled or not.
  * @param  __HANDLE__: DMA handle
  * @param  __INTERRUPT__: specifies the DMA interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg DMA_IT_TC: Transfer complete interrupt mask.
  *            @arg DMA_IT_HT: Half transfer complete interrupt mask.
  *            @arg DMA_IT_TE: Transfer error interrupt mask.
  *            @arg DMA_IT_FE: FIFO error interrupt mask.
  *            @arg DMA_IT_DME: Direct mode error interrupt.
  * @retval The state of DMA_IT.
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))? \
                                                            (__HAL_DMA_STREAM_GET_IT_SOURCE((__HANDLE__), (__INTERRUPT__))) :\
                                                            (__HAL_BDMA_CHANNEL_GET_IT_SOURCE((__HANDLE__), (__INTERRUPT__))))

/**
  * @brief  Writes the number of data units to be transferred on the DMA Stream.
  * @param  __HANDLE__: DMA handle
  * @param  __COUNTER__: Number of data units to be transferred (from 0 to 65535)
  *          Number of data items depends only on the Peripheral data format.
  *
  * @note   If Peripheral data format is Bytes: number of data units is equal
  *         to total number of bytes to be transferred.
  *
  * @note   If Peripheral data format is Half-Word: number of data units is
  *         equal to total number of bytes to be transferred / 2.
  *
  * @note   If Peripheral data format is Word: number of data units is equal
  *         to total  number of bytes to be transferred / 4.
  *
  * @retval The number of remaining data units in the current DMAy Streamx transfer.
  */
#define __HAL_DMA_SET_COUNTER(__HANDLE__, __COUNTER__) ((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))? \
                                                        (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->NDTR = (uint16_t)(__COUNTER__)) :\
                                                        (((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CNDTR = (uint16_t)(__COUNTER__)))

/**
  * @brief  Returns the number of remaining data units in the current DMAy Streamx transfer.
  * @param  __HANDLE__: DMA handle
  *
  * @retval The number of remaining data units in the current DMA Stream transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((IS_DMA_STREAM_INSTANCE((__HANDLE__)->Instance))? \
                                           (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->NDTR) :\
                                           (((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CNDTR))

/**
  * @}
  */

/* Include DMA HAL Extension module */
#include "stm32h7xx_hal_dma_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @defgroup DMA_Exported_Functions DMA Exported Functions
  * @brief    DMA Exported functions
  * @{
  */

/** @defgroup DMA_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief   Initialization and de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group2 I/O operation functions
  * @brief   I/O operation functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
void              HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group3 Peripheral State functions
  * @brief    Peripheral State functions
  * @{
  */
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);
/**
  * @}
  */
/**
  * @}
  */
/* Private Constants -------------------------------------------------------------*/
/** @defgroup DMA_Private_Constants DMA Private Constants
  * @brief    DMA private defines and constants
  * @{
  */
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup DMA_Private_Types DMA Private Types
  * @{
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @brief    DMA private macros
  * @{
  */

#if defined(TIM24)
#define IS_DMA_REQUEST(REQUEST) (((REQUEST) <= DMA_REQUEST_TIM24_TRIG))
#elif defined(ADC3)
#define IS_DMA_REQUEST(REQUEST) (((REQUEST) <= DMA_REQUEST_ADC3))
#else
#define IS_DMA_REQUEST(REQUEST) (((REQUEST) <= DMA_REQUEST_USART10_TX))
#endif /* TIM24 */

#if defined(ADC3)
#define IS_BDMA_REQUEST(REQUEST) (((REQUEST) <= BDMA_REQUEST_ADC3))
#else
#define IS_BDMA_REQUEST(REQUEST) (((REQUEST) <= BDMA_REQUEST_DFSDM2_FLT0))
#endif /* ADC3 */

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x01U) && ((SIZE) < 0x10000U))

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

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )           || \
                           ((MODE) == DMA_CIRCULAR)          || \
                           ((MODE) == DMA_PFCTRL)            || \
                           ((MODE) == DMA_DOUBLE_BUFFER_M0)  || \
                           ((MODE) == DMA_DOUBLE_BUFFER_M1))

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_LOW )   || \
                                   ((PRIORITY) == DMA_PRIORITY_MEDIUM) || \
                                   ((PRIORITY) == DMA_PRIORITY_HIGH)   || \
                                   ((PRIORITY) == DMA_PRIORITY_VERY_HIGH))

#define IS_DMA_FIFO_MODE_STATE(STATE) (((STATE) == DMA_FIFOMODE_DISABLE ) || \
                                       ((STATE) == DMA_FIFOMODE_ENABLE))

#define IS_DMA_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == DMA_FIFO_THRESHOLD_1QUARTERFULL ) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_HALFFULL)      || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_3QUARTERSFULL) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_FULL))

#define IS_DMA_MEMORY_BURST(BURST) (((BURST) == DMA_MBURST_SINGLE) || \
                                    ((BURST) == DMA_MBURST_INC4)   || \
                                    ((BURST) == DMA_MBURST_INC8)   || \
                                    ((BURST) == DMA_MBURST_INC16))

#define IS_DMA_PERIPHERAL_BURST(BURST) (((BURST) == DMA_PBURST_SINGLE) || \
                                        ((BURST) == DMA_PBURST_INC4)   || \
                                        ((BURST) == DMA_PBURST_INC8)   || \
                                        ((BURST) == DMA_PBURST_INC16))
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup DMA_Private_Functions DMA Private Functions
  * @brief    DMA private  functions
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

#endif /* STM32H7xx_HAL_DMA_H */

