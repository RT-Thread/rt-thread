/**
  ******************************************************************************
  * @file    stm32h7xx_hal_dma.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    21-April-2017
  * @brief   Header file of DMA HAL module.
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
#ifndef __STM32H7xx_HAL_DMA_H
#define __STM32H7xx_HAL_DMA_H

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
#define HAL_DMA_ERROR_NONE            ((uint32_t)0x00000000U)    /*!< No error                                */
#define HAL_DMA_ERROR_TE              ((uint32_t)0x00000001U)    /*!< Transfer error                          */
#define HAL_DMA_ERROR_FE              ((uint32_t)0x00000002U)    /*!< FIFO error                              */
#define HAL_DMA_ERROR_DME             ((uint32_t)0x00000004U)    /*!< Direct Mode error                       */
#define HAL_DMA_ERROR_TIMEOUT         ((uint32_t)0x00000020U)    /*!< Timeout error                           */
#define HAL_DMA_ERROR_PARAM           ((uint32_t)0x00000040U)    /*!< Parameter error                         */
#define HAL_DMA_ERROR_NO_XFER         ((uint32_t)0x00000080U)    /*!< Abort requested with no Xfer ongoing    */ 
#define HAL_DMA_ERROR_NOT_SUPPORTED   ((uint32_t)0x00000100U)    /*!< Not supported mode                      */ 
#define HAL_DMA_ERROR_SYNC            ((uint32_t)0x00000200U)    /*!< DMAMUX sync overrun  error              */
#define HAL_DMA_ERROR_REQGEN          ((uint32_t)0x00000400U)    /*!< DMAMUX request generator overrun  error */

/**
  * @}
  */

/** @defgroup DMA_Request_selection DMA Request selection
  * @brief    DMA Request selection
  * @{
  */ 
/* D2 Domain : DMAMUX1 requests */
#define DMA_REQUEST_MEM2MEM          ((uint32_t)0x00000000)  /*!< memory to memory transfer   */

#define DMA_REQUEST_GENERATOR0       ((uint32_t)0x00000001)  /*!< DMAMUX1 request generator 0 */
#define DMA_REQUEST_GENERATOR1       ((uint32_t)0x00000002)  /*!< DMAMUX1 request generator 1 */
#define DMA_REQUEST_GENERATOR2       ((uint32_t)0x00000003)  /*!< DMAMUX1 request generator 2 */
#define DMA_REQUEST_GENERATOR3       ((uint32_t)0x00000004)  /*!< DMAMUX1 request generator 3 */
#define DMA_REQUEST_GENERATOR4       ((uint32_t)0x00000005)  /*!< DMAMUX1 request generator 4 */
#define DMA_REQUEST_GENERATOR5       ((uint32_t)0x00000006)  /*!< DMAMUX1 request generator 5 */
#define DMA_REQUEST_GENERATOR6       ((uint32_t)0x00000007)  /*!< DMAMUX1 request generator 6 */
#define DMA_REQUEST_GENERATOR7       ((uint32_t)0x00000008)  /*!< DMAMUX1 request generator 7 */

#define DMA_REQUEST_ADC1             ((uint32_t)0x00000009)  /*!< DMAMUX1 ADC1 request */
#define DMA_REQUEST_ADC2             ((uint32_t)0x0000000A)  /*!< DMAMUX1 ADC2 request */
                                     
#define DMA_REQUEST_TIM1_CH1         ((uint32_t)0x0000000B)  /*!< DMAMUX1 TIM1 CH1 request  */
#define DMA_REQUEST_TIM1_CH2         ((uint32_t)0x0000000C)  /*!< DMAMUX1 TIM1 CH2 request  */
#define DMA_REQUEST_TIM1_CH3         ((uint32_t)0x0000000D)  /*!< DMAMUX1 TIM1 CH3 request  */
#define DMA_REQUEST_TIM1_CH4         ((uint32_t)0x0000000E)  /*!< DMAMUX1 TIM1 CH4 request  */
#define DMA_REQUEST_TIM1_UP          ((uint32_t)0x0000000F)  /*!< DMAMUX1 TIM1 UP request   */
#define DMA_REQUEST_TIM1_TRIG        ((uint32_t)0x00000010)  /*!< DMAMUX1 TIM1 TRIG request */
#define DMA_REQUEST_TIM1_COM         ((uint32_t)0x00000011)  /*!< DMAMUX1 TIM1 COM request  */
                                     
#define DMA_REQUEST_TIM2_CH1         ((uint32_t)0x00000012)  /*!< DMAMUX1 TIM2 CH1 request  */
#define DMA_REQUEST_TIM2_CH2         ((uint32_t)0x00000013)  /*!< DMAMUX1 TIM2 CH2 request  */
#define DMA_REQUEST_TIM2_CH3         ((uint32_t)0x00000014)  /*!< DMAMUX1 TIM2 CH3 request  */
#define DMA_REQUEST_TIM2_CH4         ((uint32_t)0x00000015)  /*!< DMAMUX1 TIM2 CH4 request  */
#define DMA_REQUEST_TIM2_UP          ((uint32_t)0x00000016)  /*!< DMAMUX1 TIM2 UP request   */
                                     
#define DMA_REQUEST_TIM3_CH1         ((uint32_t)0x00000017)  /*!< DMAMUX1 TIM3 CH1 request  */
#define DMA_REQUEST_TIM3_CH2         ((uint32_t)0x00000018)  /*!< DMAMUX1 TIM3 CH2 request  */
#define DMA_REQUEST_TIM3_CH3         ((uint32_t)0x00000019)  /*!< DMAMUX1 TIM3 CH3 request  */
#define DMA_REQUEST_TIM3_CH4         ((uint32_t)0x0000001A)  /*!< DMAMUX1 TIM3 CH4 request  */
#define DMA_REQUEST_TIM3_UP          ((uint32_t)0x0000001B)  /*!< DMAMUX1 TIM3 UP request   */
#define DMA_REQUEST_TIM3_TRIG        ((uint32_t)0x0000001C)  /*!< DMAMUX1 TIM3 TRIG request */
                                     
#define DMA_REQUEST_TIM4_CH1         ((uint32_t)0x0000001D)  /*!< DMAMUX1 TIM4 CH1 request  */
#define DMA_REQUEST_TIM4_CH2         ((uint32_t)0x0000001E)  /*!< DMAMUX1 TIM4 CH2 request  */
#define DMA_REQUEST_TIM4_CH3         ((uint32_t)0x0000001F)  /*!< DMAMUX1 TIM4 CH3 request  */
#define DMA_REQUEST_TIM4_UP          ((uint32_t)0x00000020)  /*!< DMAMUX1 TIM4 UP request   */
                                     
#define DMA_REQUEST_I2C1_RX          ((uint32_t)0x00000021)  /*!< DMAMUX1 I2C1 RX request   */
#define DMA_REQUEST_I2C1_TX          ((uint32_t)0x00000022)  /*!< DMAMUX1 I2C1 TX request   */
#define DMA_REQUEST_I2C2_RX          ((uint32_t)0x00000023)  /*!< DMAMUX1 I2C2 RX request   */
#define DMA_REQUEST_I2C2_TX          ((uint32_t)0x00000024)  /*!< DMAMUX1 I2C2 TX request   */
                                     
#define DMA_REQUEST_SPI1_RX          ((uint32_t)0x00000025)  /*!< DMAMUX1 SPI1 RX request   */
#define DMA_REQUEST_SPI1_TX          ((uint32_t)0x00000026)  /*!< DMAMUX1 SPI1 TX request   */
#define DMA_REQUEST_SPI2_RX          ((uint32_t)0x00000027)  /*!< DMAMUX1 SPI2 RX request   */
#define DMA_REQUEST_SPI2_TX          ((uint32_t)0x00000028)  /*!< DMAMUX1 SPI2 TX request   */
                                     
#define DMA_REQUEST_USART1_RX        ((uint32_t)0x00000029)  /*!< DMAMUX1 USART1 RX request */
#define DMA_REQUEST_USART1_TX        ((uint32_t)0x0000002A)  /*!< DMAMUX1 USART1 TX request */
#define DMA_REQUEST_USART2_RX        ((uint32_t)0x0000002B)  /*!< DMAMUX1 USART2 RX request */
#define DMA_REQUEST_USART2_TX        ((uint32_t)0x0000002C)  /*!< DMAMUX1 USART2 TX request */
#define DMA_REQUEST_USART3_RX        ((uint32_t)0x0000002D)  /*!< DMAMUX1 USART3 RX request */
#define DMA_REQUEST_USART3_TX        ((uint32_t)0x0000002E)  /*!< DMAMUX1 USART3 TX request */
                                     
#define DMA_REQUEST_TIM8_CH1         ((uint32_t)0x0000002F)  /*!< DMAMUX1 TIM8 CH1 request  */
#define DMA_REQUEST_TIM8_CH2         ((uint32_t)0x00000030)  /*!< DMAMUX1 TIM8 CH2 request  */
#define DMA_REQUEST_TIM8_CH3         ((uint32_t)0x00000031)  /*!< DMAMUX1 TIM8 CH3 request  */
#define DMA_REQUEST_TIM8_CH4         ((uint32_t)0x00000032)  /*!< DMAMUX1 TIM8 CH4 request  */
#define DMA_REQUEST_TIM8_UP          ((uint32_t)0x00000033)  /*!< DMAMUX1 TIM8 UP request   */
#define DMA_REQUEST_TIM8_TRIG        ((uint32_t)0x00000034)  /*!< DMAMUX1 TIM8 TRIG request */
#define DMA_REQUEST_TIM8_COM         ((uint32_t)0x00000035)  /*!< DMAMUX1 TIM8 COM request  */

#define DMA_REQUEST_TIM5_CH1         ((uint32_t)0x00000037)  /*!< DMAMUX1 TIM5 CH1 request  */
#define DMA_REQUEST_TIM5_CH2         ((uint32_t)0x00000038)  /*!< DMAMUX1 TIM5 CH2 request  */
#define DMA_REQUEST_TIM5_CH3         ((uint32_t)0x00000039)  /*!< DMAMUX1 TIM5 CH3 request  */
#define DMA_REQUEST_TIM5_CH4         ((uint32_t)0x0000003A)  /*!< DMAMUX1 TIM5 CH4 request  */
#define DMA_REQUEST_TIM5_UP          ((uint32_t)0x0000003B)  /*!< DMAMUX1 TIM5 UP request   */
#define DMA_REQUEST_TIM5_TRIG        ((uint32_t)0x0000003C)  /*!< DMAMUX1 TIM5 TRIG request */
                                     
#define DMA_REQUEST_SPI3_RX          ((uint32_t)0x0000003D)  /*!< DMAMUX1 SPI3 RX request   */
#define DMA_REQUEST_SPI3_TX          ((uint32_t)0x0000003E)  /*!< DMAMUX1 SPI3 TX request   */
                                     
#define DMA_REQUEST_UART4_RX         ((uint32_t)0x0000003F)  /*!< DMAMUX1 UART4 RX request */
#define DMA_REQUEST_UART4_TX         ((uint32_t)0x00000040)  /*!< DMAMUX1 UART4 TX request */
#define DMA_REQUEST_UART5_RX         ((uint32_t)0x00000041)  /*!< DMAMUX1 UART5 RX request */
#define DMA_REQUEST_UART5_TX         ((uint32_t)0x00000042)  /*!< DMAMUX1 UART5 TX request */
                                     
#define DMA_REQUEST_DAC1             ((uint32_t)0x00000043)  /*!< DMAMUX1 DAC1 request      */
#define DMA_REQUEST_DAC2             ((uint32_t)0x00000044)  /*!< DMAMUX1 DAC2 request      */
                                     
#define DMA_REQUEST_TIM6_UP          ((uint32_t)0x00000045)  /*!< DMAMUX1 TIM6 UP request   */
#define DMA_REQUEST_TIM7_UP          ((uint32_t)0x00000046)  /*!< DMAMUX1 TIM7 UP request   */
                                     
#define DMA_REQUEST_USART6_RX        ((uint32_t)0x00000047)  /*!< DMAMUX1 USART6 RX request */
#define DMA_REQUEST_USART6_TX        ((uint32_t)0x00000048)  /*!< DMAMUX1 USART6 TX request */
                                     
#define DMA_REQUEST_I2C3_RX          ((uint32_t)0x00000049)  /*!< DMAMUX1 I2C3 RX request   */
#define DMA_REQUEST_I2C3_TX          ((uint32_t)0x0000004A)  /*!< DMAMUX1 I2C3 TX request   */
                                     
#define DMA_REQUEST_DCMI             ((uint32_t)0x0000004B)  /*!< DMAMUX1 DCMI request      */
                                     
#define DMA_REQUEST_CRYP_IN          ((uint32_t)0x0000004C)  /*!< DMAMUX1 CRYP IN request   */
#define DMA_REQUEST_CRYP_OUT         ((uint32_t)0x0000004D)  /*!< DMAMUX1 CRYP OUT request  */
                                     
#define DMA_REQUEST_HASH_IN          ((uint32_t)0x0000004E)  /*!< DMAMUX1 HASH IN request   */
                                     
#define DMA_REQUEST_UART7_RX         ((uint32_t)0x0000004F)  /*!< DMAMUX1 UART7 RX request  */
#define DMA_REQUEST_UART7_TX         ((uint32_t)0x00000050)  /*!< DMAMUX1 UART7 TX request  */
#define DMA_REQUEST_UART8_RX         ((uint32_t)0x00000051)  /*!< DMAMUX1 UART8 RX request  */
#define DMA_REQUEST_UART8_TX         ((uint32_t)0x00000052)  /*!< DMAMUX1 UART8 TX request  */
                                     
#define DMA_REQUEST_SPI4_RX          ((uint32_t)0x00000053)  /*!< DMAMUX1 SPI4 RX request   */
#define DMA_REQUEST_SPI4_TX          ((uint32_t)0x00000054)  /*!< DMAMUX1 SPI4 TX request   */
#define DMA_REQUEST_SPI5_RX          ((uint32_t)0x00000055)  /*!< DMAMUX1 SPI5 RX request   */
#define DMA_REQUEST_SPI5_TX          ((uint32_t)0x00000056)  /*!< DMAMUX1 SPI5 TX request   */
                                     
#define DMA_REQUEST_SAI1_A           ((uint32_t)0x00000057)  /*!< DMAMUX1 SAI1 A request    */
#define DMA_REQUEST_SAI1_B           ((uint32_t)0x00000058)  /*!< DMAMUX1 SAI1 B request    */
#define DMA_REQUEST_SAI2_A           ((uint32_t)0x00000059)  /*!< DMAMUX1 SAI2 A request    */
#define DMA_REQUEST_SAI2_B           ((uint32_t)0x0000005A)  /*!< DMAMUX1 SAI2 B request    */
                                     
#define DMA_REQUEST_SWPMI_RX         ((uint32_t)0x0000005B)  /*!< DMAMUX1 SWPMI RX request  */
#define DMA_REQUEST_SWPMI_TX         ((uint32_t)0x0000005C)  /*!< DMAMUX1 SWPMI TX request  */
                                     
#define DMA_REQUEST_SPDIF_RX_DT      ((uint32_t)0x0000005D)  /*!< DMAMUX1 SPDIF RXDT request*/
#define DMA_REQUEST_SPDIF_RX_CS      ((uint32_t)0x0000005E)  /*!< DMAMUX1 SPDIF RXCS request*/
                                     
#define DMA_REQUEST_HRTIM_MASTER     ((uint32_t)0x0000005F)  /*!< DMAMUX1 HRTIM1 Master request 1 */
#define DMA_REQUEST_HRTIM_TIMER_A    ((uint32_t)0x00000060)  /*!< DMAMUX1 HRTIM1 TimerA request 2 */
#define DMA_REQUEST_HRTIM_TIMER_B    ((uint32_t)0x00000061)  /*!< DMAMUX1 HRTIM1 TimerB request 3 */
#define DMA_REQUEST_HRTIM_TIMER_C    ((uint32_t)0x00000062)  /*!< DMAMUX1 HRTIM1 TimerC request 4 */
#define DMA_REQUEST_HRTIM_TIMER_D    ((uint32_t)0x00000063)  /*!< DMAMUX1 HRTIM1 TimerD request 5 */
#define DMA_REQUEST_HRTIM_TIMER_E    ((uint32_t)0x00000064)  /*!< DMAMUX1 HRTIM1 TimerE request 6 */

#define DMA_REQUEST_DFSDM1_FLT0      ((uint32_t)0x00000065)  /*!< DMAMUX1 DFSDM Filter0 request */
#define DMA_REQUEST_DFSDM1_FLT1      ((uint32_t)0x00000066)  /*!< DMAMUX1 DFSDM Filter1 request */
#define DMA_REQUEST_DFSDM1_FLT2      ((uint32_t)0x00000067)  /*!< DMAMUX1 DFSDM Filter2 request */
#define DMA_REQUEST_DFSDM1_FLT3      ((uint32_t)0x00000068)  /*!< DMAMUX1 DFSDM Filter3 request */
                                     
#define DMA_REQUEST_TIM15_CH1        ((uint32_t)0x00000069)  /*!< DMAMUX1 TIM15 CH1 request  */
#define DMA_REQUEST_TIM15_UP         ((uint32_t)0x0000006A)  /*!< DMAMUX1 TIM15 UP request   */
#define DMA_REQUEST_TIM15_TRIG       ((uint32_t)0x0000006B)  /*!< DMAMUX1 TIM15 TRIG request */
#define DMA_REQUEST_TIM15_COM        ((uint32_t)0x0000006C)  /*!< DMAMUX1 TIM15 COM request  */
                                     
#define DMA_REQUEST_TIM16_CH1        ((uint32_t)0x0000006D)  /*!< DMAMUX1 TIM16 CH1 request  */
#define DMA_REQUEST_TIM16_UP         ((uint32_t)0x0000006E)  /*!< DMAMUX1 TIM16 UP request   */
                                     
#define DMA_REQUEST_TIM17_CH1        ((uint32_t)0x0000006F)  /*!< DMAMUX1 TIM17 CH1 request  */
#define DMA_REQUEST_TIM17_UP         ((uint32_t)0x00000070)  /*!< DMAMUX1 TIM17 UP request   */
                                     
#define DMA_REQUEST_SAI3_A           ((uint32_t)0x00000071)  /*!< DMAMUX1 SAI3 A request  */
#define DMA_REQUEST_SAI3_B           ((uint32_t)0x00000072)  /*!< DMAMUX1 SAI3 B request  */
                                     
#define DMA_REQUEST_ADC3             ((uint32_t)0x00000073)  /*!< DMAMUX1 ADC3  request  */


/* D3 Domain : DMAMUX2 requests */
#define BDMA_REQUEST_MEM2MEM          ((uint32_t)0x00000000)  /*!< memory to memory transfer   */
#define BDMA_REQUEST_GENERATOR0       ((uint32_t)0x10000001)  /*!< DMAMUX2 request generator 0 */
#define BDMA_REQUEST_GENERATOR1       ((uint32_t)0x10000002)  /*!< DMAMUX2 request generator 1 */
#define BDMA_REQUEST_GENERATOR2       ((uint32_t)0x10000003)  /*!< DMAMUX2 request generator 2 */
#define BDMA_REQUEST_GENERATOR3       ((uint32_t)0x10000004)  /*!< DMAMUX2 request generator 3 */
#define BDMA_REQUEST_GENERATOR4       ((uint32_t)0x10000005)  /*!< DMAMUX2 request generator 4 */
#define BDMA_REQUEST_GENERATOR5       ((uint32_t)0x10000006)  /*!< DMAMUX2 request generator 5 */
#define BDMA_REQUEST_GENERATOR6       ((uint32_t)0x10000007)  /*!< DMAMUX2 request generator 6 */
#define BDMA_REQUEST_GENERATOR7       ((uint32_t)0x10000008)  /*!< DMAMUX2 request generator 7 */
#define BDMA_REQUEST_LP_UART1_RX      ((uint32_t)0x10000009)  /*!< DMAMUX2 LP_UART1_RX request */
#define BDMA_REQUEST_LP_UART1_TX      ((uint32_t)0x1000000A)  /*!< DMAMUX2 LP_UART1_TX request */
#define BDMA_REQUEST_SPI6_RX          ((uint32_t)0x1000000B)  /*!< DMAMUX2 SPI6 RX request     */
#define BDMA_REQUEST_SPI6_TX          ((uint32_t)0x1000000C)  /*!< DMAMUX2 SPI6 TX request     */
#define BDMA_REQUEST_I2C4_RX          ((uint32_t)0x1000000D)  /*!< DMAMUX2 I2C4 RX request     */
#define BDMA_REQUEST_I2C4_TX          ((uint32_t)0x1000000E)  /*!< DMAMUX2 I2C4 TX request     */
#define BDMA_REQUEST_SAI4_A           ((uint32_t)0x1000000F)  /*!< DMAMUX2 SAI4 A request      */
#define BDMA_REQUEST_SAI4_B           ((uint32_t)0x10000010)  /*!< DMAMUX2 SAI4 B request      */
#define BDMA_REQUEST_ADC3             ((uint32_t)0x10000011)  /*!< DMAMUX2 ADC3 request        */

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
#define DMA_PDATAALIGN_BYTE          ((uint32_t)0x00000000U)        /*!< Peripheral data alignment: Byte     */
#define DMA_PDATAALIGN_HALFWORD      ((uint32_t)DMA_SxCR_PSIZE_0)  /*!< Peripheral data alignment: HalfWord */
#define DMA_PDATAALIGN_WORD          ((uint32_t)DMA_SxCR_PSIZE_1)  /*!< Peripheral data alignment: Word     */
/**
  * @}
  */ 

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @brief    DMA memory data size 
  * @{ 
  */
#define DMA_MDATAALIGN_BYTE          ((uint32_t)0x00000000U)        /*!< Memory data alignment: Byte     */
#define DMA_MDATAALIGN_HALFWORD      ((uint32_t)DMA_SxCR_MSIZE_0)  /*!< Memory data alignment: HalfWord */
#define DMA_MDATAALIGN_WORD          ((uint32_t)DMA_SxCR_MSIZE_1)  /*!< Memory data alignment: Word     */
/**
  * @}
  */

/** @defgroup DMA_mode DMA mode
  * @brief    DMA mode 
  * @{
  */ 
#define DMA_NORMAL         ((uint32_t)0x00000000U)       /*!< Normal mode                  */
#define DMA_CIRCULAR       ((uint32_t)DMA_SxCR_CIRC)    /*!< Circular mode                */
#define DMA_PFCTRL         ((uint32_t)DMA_SxCR_PFCTRL)  /*!< Peripheral flow control mode */
/**
  * @}
  */

/** @defgroup DMA_Priority_level DMA Priority level
  * @brief    DMA priority levels 
  * @{
  */
#define DMA_PRIORITY_LOW             ((uint32_t)0x00000000U)     /*!< Priority level: Low       */
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
#define DMA_FLAG_FEIF0_4                    ((uint32_t)0x00800001U)
#define DMA_FLAG_DMEIF0_4                   ((uint32_t)0x00800004U)
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
#define __HAL_DMA_GET_FS(__HANDLE__) ((IS_D2_DMA_INSTANCE(__HANDLE__))? (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->FCR & (DMA_SxFCR_FS)) : 0)

/**
  * @brief  Enable the specified DMA Stream.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__) \
((IS_D2_DMA_INSTANCE(__HANDLE__))? (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR |=  DMA_SxCR_EN) : \
(((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR |=  BDMA_CCR_EN))

/**
  * @brief  Disable the specified DMA Stream.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__) \
((IS_D2_DMA_INSTANCE(__HANDLE__))? (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->CR &=  ~DMA_SxCR_EN) : \
(((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR &=  ~BDMA_CCR_EN))

/* Interrupt & Flag management */

/**
  * @brief  Return the current DMA Stream transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */
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
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_FLAG_TC0    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_FLAG_TC1    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_FLAG_TC2    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_FLAG_TC3    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_FLAG_TC4    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_FLAG_TC5    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_FLAG_TC6    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_FLAG_TC7    :\
 (uint32_t)0x00000000)

/**
  * @brief  Return the current DMA Stream half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */      
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
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_FLAG_HT0    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_FLAG_HT1    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_FLAG_HT2    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_FLAG_HT3    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_FLAG_HT4    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_FLAG_HT5    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_FLAG_HT6    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_FLAG_HT7    :\
 (uint32_t)0x00000000)

/**
  * @brief  Return the current DMA Stream transfer error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
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
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel0))? BDMA_FLAG_TE0    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel1))? BDMA_FLAG_TE1    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel2))? BDMA_FLAG_TE2    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel3))? BDMA_FLAG_TE3    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel4))? BDMA_FLAG_TE4    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel5))? BDMA_FLAG_TE5    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel6))? BDMA_FLAG_TE6    :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)BDMA_Channel7))? BDMA_FLAG_TE7    :\
 (uint32_t)0x00000000)

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
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)\
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream7)? (BDMA->ISR & (__FLAG__))  :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)? (DMA2->HISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)? (DMA2->LISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)? (DMA1->HISR & (__FLAG__)) : (DMA1->LISR & (__FLAG__)))

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
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream7)? (BDMA->IFCR = (__FLAG__))  :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)? (DMA2->HIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)? (DMA2->LIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)? (DMA1->HIFCR = (__FLAG__)) : (DMA1->LIFCR = (__FLAG__)))


#define D2_TO_D3_DMA_IT(__DMA_IT__) \
((((__DMA_IT__) & (DMA_IT_TC | DMA_IT_HT | DMA_IT_TE)) == (DMA_IT_TC | DMA_IT_HT | DMA_IT_TE)) ? (BDMA_CCR_TCIE | BDMA_CCR_HTIE |BDMA_CCR_TEIE) :\
(((__DMA_IT__) & (DMA_IT_TC | DMA_IT_HT)) == (DMA_IT_TC | DMA_IT_HT)) ? (BDMA_CCR_TCIE | BDMA_CCR_HTIE) :\
(((__DMA_IT__) & (DMA_IT_HT | DMA_IT_TE)) == (DMA_IT_HT | DMA_IT_TE)) ? (BDMA_CCR_HTIE |BDMA_CCR_TEIE)  :\
(((__DMA_IT__) & (DMA_IT_TC | DMA_IT_TE)) == (DMA_IT_TC | DMA_IT_TE)) ? (BDMA_CCR_TCIE |BDMA_CCR_TEIE)  :\
((__DMA_IT__) == DMA_IT_TC) ? BDMA_CCR_TCIE :\
((__DMA_IT__) == DMA_IT_HT) ? BDMA_CCR_HTIE :\
((__DMA_IT__) == DMA_IT_TE) ? BDMA_CCR_TEIE :\
(uint32_t)0x00000000)
                                     
                                     
#define __HAL_DMA_D3_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
(((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR |= (D2_TO_D3_DMA_IT(__INTERRUPT__)))

#define __HAL_DMA_D2_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((__INTERRUPT__) != DMA_IT_FE)? \
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
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((IS_D2_DMA_INSTANCE(__HANDLE__))?\
                                                        (__HAL_DMA_D2_ENABLE_IT((__HANDLE__), (__INTERRUPT__))) :\
                                                        (__HAL_DMA_D3_ENABLE_IT((__HANDLE__), (__INTERRUPT__))))


#define __HAL_DMA_D3_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR &= ~(D2_TO_D3_DMA_IT(__INTERRUPT__)))

#define __HAL_DMA_D2_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
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
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((IS_D2_DMA_INSTANCE(__HANDLE__))?\
                                                         (__HAL_DMA_D2_DISABLE_IT((__HANDLE__), (__INTERRUPT__))) :\
                                                         (__HAL_DMA_D3_DISABLE_IT((__HANDLE__), (__INTERRUPT__))))


#define __HAL_DMA_D3_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CCR & (D2_TO_D3_DMA_IT(__INTERRUPT__))))

#define __HAL_DMA_D2_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
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
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((IS_D2_DMA_INSTANCE(__HANDLE__))? \
                                                            (__HAL_DMA_D2_GET_IT_SOURCE((__HANDLE__), (__INTERRUPT__))) :\
                                                            (__HAL_DMA_D3_GET_IT_SOURCE((__HANDLE__), (__INTERRUPT__))))

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
#define __HAL_DMA_SET_COUNTER(__HANDLE__, __COUNTER__) ((IS_D2_DMA_INSTANCE(__HANDLE__))? \
                                                        (((DMA_Stream_TypeDef *)(__HANDLE__)->Instance)->NDTR = (uint16_t)(__COUNTER__)) :\
                                                        (((BDMA_Channel_TypeDef *)(__HANDLE__)->Instance)->CNDTR = (uint16_t)(__COUNTER__)))

/**
  * @brief  Returns the number of remaining data units in the current DMAy Streamx transfer.
  * @param  __HANDLE__: DMA handle
  *   
  * @retval The number of remaining data units in the current DMA Stream transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((IS_D2_DMA_INSTANCE(__HANDLE__))?\
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

/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @brief    DMA private macros 
  * @{
  */

#define IS_DMA_D2_REQUEST(REQUEST) (((REQUEST) <= DMA_REQUEST_ADC3))

#define IS_BDMA_D3_REQUEST(REQUEST) (((REQUEST) == BDMA_REQUEST_MEM2MEM) || \
                                    (((REQUEST) >= BDMA_REQUEST_GENERATOR0) &&  ((REQUEST) <= BDMA_REQUEST_ADC3)))

#define IS_D2_DMA_INSTANCE(__HANDLE__) (((uint32_t)((__HANDLE__)->Instance) >= ((uint32_t)DMA1_Stream0)) && ((uint32_t)((__HANDLE__)->Instance) <= ((uint32_t)DMA2_Stream7)))  
#define IS_D3_DMA_INSTANCE(__HANDLE__) (((uint32_t)((__HANDLE__)->Instance) >= ((uint32_t)BDMA_Channel0)) && ((uint32_t)((__HANDLE__)->Instance) <= ((uint32_t)BDMA_Channel7)))  


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

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_CIRCULAR) || \
                           ((MODE) == DMA_PFCTRL)) 

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

#endif /* __STM32H7xx_HAL_DMA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
