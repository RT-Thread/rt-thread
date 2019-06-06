/**
  ******************************************************************************
  * @file    stm32h7xx_hal_usart.h
  * @author  MCD Application Team
  * @brief   Header file of USART HAL module.
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
#ifndef __STM32H7xx_HAL_USART_H
#define __STM3H7xx_HAL_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup USART_Exported_Types USART Exported Types
  * @{
  */

/**
  * @brief USART Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the Usart communication baud rate.
                                           The baud rate is computed using the following formula:
                                              Baud Rate Register = ((PCLKx) / ((husart->Init.BaudRate))) */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USARTEx_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint32_t Parity;                   /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint32_t CLKPolarity;               /*!< Specifies the steady state of the serial clock.
                                           This parameter can be a value of @ref USART_Clock_Polarity */

  uint32_t CLKPhase;                  /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref USART_Clock_Phase */

  uint32_t CLKLastBit;                /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                           data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                           This parameter can be a value of @ref USART_Last_Bit */

  uint32_t Prescaler;                 /*!< Specifies the prescaler value used to divide the USART clock source.
                                           This parameter can be a value of @ref USART_Prescaler */

  uint32_t NSS;                       /*!< Specifies whether the NSS signal is managed by hardware (DIS_NSS pin)
                                           or by software . This parameter can be a value
                                           of @ref USART_Slave_Select_management */

  uint32_t SlaveMode;                 /*!< Enable/Disable UART SPI Slave Mode. This parameter can be a value
                                           of @ref USART_Slave_Mode */

  uint32_t FIFOMode;                  /*!< Specifies if the FIFO mode will be used. This parameter can be a value
                                           of @ref USART_FIFO_mode */

  uint32_t TXFIFOThreshold;           /*!< Specifies the TXFIFO threshold level.
                                           This parameter can be a value of @ref USART_TXFIFO_threshold_level */

  uint32_t RXFIFOThreshold;           /*!< Specifies the RXFIFO threshold level.
                                           This parameter can be a value of @ref USART_RXFIFO_threshold_level */

}USART_InitTypeDef;

/**
  * @brief HAL USART State structures definition
  */
typedef enum
{
  HAL_USART_STATE_RESET             = 0x00U,    /*!< Peripheral is not initialized                  */
  HAL_USART_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use       */
  HAL_USART_STATE_BUSY              = 0x02U,    /*!< an internal process is ongoing                 */
  HAL_USART_STATE_BUSY_TX           = 0x12U,    /*!< Data Transmission process is ongoing           */
  HAL_USART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing              */
  HAL_USART_STATE_BUSY_TX_RX        = 0x32U,    /*!< Data Transmission Reception process is ongoing */
  HAL_USART_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                                  */
  HAL_USART_STATE_ERROR             = 0x04U     /*!< Error                                          */
}HAL_USART_StateTypeDef;

/**
  * @brief  HAL USART Error Code structure definition
  */
typedef enum
{
  HAL_USART_ERROR_NONE      = 0x00U,    /*!< No error            */
  HAL_USART_ERROR_PE        = 0x01U,    /*!< Parity error        */
  HAL_USART_ERROR_NE        = 0x02U,    /*!< Noise error         */
  HAL_USART_ERROR_FE        = 0x04U,    /*!< frame error         */
  HAL_USART_ERROR_ORE       = 0x08U,    /*!< Overrun error       */
  HAL_USART_ERROR_DMA       = 0x10U,    /*!< DMA transfer error  */
  HAL_USART_ERROR_UDR       = 0x11U     /*!< SPI UnderRun error  */
}HAL_USART_ErrorTypeDef;

/**
  * @brief  USART clock sources definitions
  */
typedef enum
{
  USART_CLOCKSOURCE_D2PCLK1    = 0x00U,    /*!< Domain2 PCLK1 clock source */
  USART_CLOCKSOURCE_D2PCLK2    = 0x01U,    /*!< Domain2 PCLK2 clock source */
  USART_CLOCKSOURCE_D3PCLK1    = 0x02U,    /*!< Domain3 PCLK1 clock source */
  USART_CLOCKSOURCE_PLL2       = 0x04U,    /*!< PLL2Q clock source         */
  USART_CLOCKSOURCE_HSI        = 0x08U,    /*!< HSI clock source           */
  USART_CLOCKSOURCE_CSI        = 0x10U,    /*!< CSI clock source           */
  USART_CLOCKSOURCE_LSE        = 0x20U,    /*!< LSE clock source           */
  USART_CLOCKSOURCE_PLL3       = 0x40U,    /*!< PLL3Q clock source         */
  USART_CLOCKSOURCE_UNDEFINED  = 0x80U     /*!< Undefined clock source     */
}USART_ClockSourceTypeDef;


/**
  * @brief  USART handle Structure definition
  */
typedef struct
{
  USART_TypeDef                 *Instance;        /*!<  USART registers base address        */

  USART_InitTypeDef             Init;             /*!< USART communication parameters      */

  uint8_t                       *pTxBuffPtr;      /*!< Pointer to USART Tx transfer Buffer */

  uint16_t                      TxXferSize;       /*!< USART Tx Transfer size              */

  __IO uint16_t                 TxXferCount;      /*!< USART Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      /*!< Pointer to USART Rx transfer Buffer */

  uint16_t                      RxXferSize;       /*!< USART Rx Transfer size              */

  __IO uint16_t                 RxXferCount;      /*!< USART Rx Transfer Counter           */

  uint16_t                      Mask;             /*!< USART Rx RDR register mask          */

  DMA_HandleTypeDef             *hdmatx;          /*!< USART Tx DMA Handle parameters      */

  DMA_HandleTypeDef             *hdmarx;          /*!< USART Rx DMA Handle parameters      */

  HAL_LockTypeDef               Lock;            /*!<  Locking object                      */

  __IO HAL_USART_StateTypeDef   State;           /*!< USART communication state           */

  __IO uint32_t                 ErrorCode;       /*!< USART Error code                    */

}USART_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup USART_Exported_Constants USART Exported Constants
  * @{
  */

/** @defgroup USART_Stop_Bits  USART Number of Stop Bits
  * @{
  */
#define USART_STOPBITS_0_5                  ((uint32_t)USART_CR2_STOP_0)                      /*!< USART frame with 0.5 stop bit  */
#define USART_STOPBITS_1                    ((uint32_t)0x00000000U)                           /*!< USART frame with 1 stop bit    */
#define USART_STOPBITS_1_5                  ((uint32_t)(USART_CR2_STOP_0 | USART_CR2_STOP_1)) /*!< USART frame with 1.5 stop bits */
#define USART_STOPBITS_2                    ((uint32_t)USART_CR2_STOP_1)                      /*!< USART frame with 2 stop bits   */
/**
  * @}
  */

/** @defgroup USART_Parity    USART Parity
  * @{
  */
#define USART_PARITY_NONE                   ((uint32_t)0x00000000U)                     /*!< No parity   */
#define USART_PARITY_EVEN                   ((uint32_t)USART_CR1_PCE)                   /*!< Even parity */
#define USART_PARITY_ODD                    ((uint32_t)(USART_CR1_PCE | USART_CR1_PS))  /*!< Odd parity  */
/**
  * @}
  */

/** @defgroup USART_Mode   USART Mode
  * @{
  */
#define USART_MODE_RX                       ((uint32_t)USART_CR1_RE)                   /*!< RX mode        */
#define USART_MODE_TX                       ((uint32_t)USART_CR1_TE)                   /*!< TX mode        */
#define USART_MODE_TX_RX                    ((uint32_t)(USART_CR1_TE |USART_CR1_RE))   /*!< RX and TX mode */
/**
  * @}
  */

/** @defgroup USART_Over_Sampling USART Over Sampling
  * @{
  */
#define USART_OVERSAMPLING_16               ((uint32_t)0x00000000U)         /*!< Oversampling by 16 */
#define USART_OVERSAMPLING_8                ((uint32_t)USART_CR1_OVER8)     /*!< Oversampling by 8  */
/**
  * @}
  */

/** @defgroup USART_Clock  USART Clock
  * @{
  */
#define USART_CLOCK_DISABLE                 ((uint32_t)0x00000000U)       /*!< USART clock disable */
#define USART_CLOCK_ENABLE                  ((uint32_t)USART_CR2_CLKEN)   /*!< USART clock enable  */
/**
  * @}
  */

/** @defgroup USART_Clock_Polarity  USART Clock Polarity
  * @{
  */
#define USART_POLARITY_LOW                  ((uint32_t)0x00000000U)      /*!< USART Clock signal is steady Low  */
#define USART_POLARITY_HIGH                 ((uint32_t)USART_CR2_CPOL)   /*!< USART Clock signal is steady High */
/**
  * @}
  */

/** @defgroup USART_Clock_Phase   USART Clock Phase
  * @{
  */
#define USART_PHASE_1EDGE                   ((uint32_t)0x00000000U)      /*!< USART frame phase on first clock transition  */
#define USART_PHASE_2EDGE                   ((uint32_t)USART_CR2_CPHA)   /*!< USART frame phase on second clock transition */
/**
  * @}
  */

/** @defgroup USART_Last_Bit  USART Last Bit
  * @{
  */
#define USART_LASTBIT_DISABLE               ((uint32_t)0x00000000U)      /*!< USART frame last data bit clock pulse not output to SCLK pin */
#define USART_LASTBIT_ENABLE                ((uint32_t)USART_CR2_LBCL)   /*!< USART frame last data bit clock pulse output to SCLK pin     */
/**
  * @}
  */

/** @defgroup USART_Prescaler  USART Prescaler
  * @{
  */
#define USART_PRESCALER_DIV1    ((uint32_t)0x00000000U)  /*!< USART clock /1   */
#define USART_PRESCALER_DIV2    ((uint32_t)0x00000001U)  /*!< USART clock /2   */
#define USART_PRESCALER_DIV4    ((uint32_t)0x00000002U)  /*!< USART clock /4   */
#define USART_PRESCALER_DIV6    ((uint32_t)0x00000003U)  /*!< USART clock /6   */
#define USART_PRESCALER_DIV8    ((uint32_t)0x00000004U)  /*!< USART clock /8   */
#define USART_PRESCALER_DIV10   ((uint32_t)0x00000005U)  /*!< USART clock /10  */
#define USART_PRESCALER_DIV12   ((uint32_t)0x00000006U)  /*!< USART clock /12  */
#define USART_PRESCALER_DIV16   ((uint32_t)0x00000007U)  /*!< USART clock /16  */
#define USART_PRESCALER_DIV32   ((uint32_t)0x00000008U)  /*!< USART clock /32  */
#define USART_PRESCALER_DIV64   ((uint32_t)0x00000009U)  /*!< USART clock /64  */
#define USART_PRESCALER_DIV128  ((uint32_t)0x0000000AU)  /*!< USART clock /128 */
#define USART_PRESCALER_DIV256  ((uint32_t)0x0000000BU)  /*!< USART clock /256 */

/**
  * @}
  */

/** @defgroup USART_Slave_Select_management USART Slave Select Management
  * @{
  */
#define USART_NSS_HW    ((uint32_t)0x00000000U)       /*!< USART Hardware NSS management */
#define USART_NSS_SW    ((uint32_t)USART_CR2_DIS_NSS) /*!< USART Software NSS management */
/**
  * @}
  */

/** @defgroup USART_Slave_Mode USART Synchronous Slave mode enable
  * @{
  */
#define USART_SLAVEMODE_DISABLE   ((uint32_t)0x00000000U)     /*!< USART SPI Slave Mode Enable  */
#define USART_SLAVEMODE_ENABLE    ((uint32_t)USART_CR2_SLVEN) /*!< USART SPI Slave Mode Disable */
/**
  * @}
  */


 /** @defgroup USART_FIFO_mode USART FIFO mode
   * @brief    USART FIFO  mode
   * @{
   */
#define USART_FIFOMODE_DISABLE        ((uint32_t)0x00000000U)       /*!< FIFO mode disable */
#define USART_FIFOMODE_ENABLE         ((uint32_t)USART_CR1_FIFOEN)  /*!< FIFO mode enable  */
/**
  * @}
  */

/** @defgroup USART_TXFIFO_threshold_level USART TXFIFO threshold level
  * @brief    USART TXFIFO level
  * @{
  */
#define USART_TXFIFO_THRESHOLD_1_8    ((uint32_t)0x00000000U)                               /*!< TXFIFO reaches 1/8 of its depth */
#define USART_TXFIFO_THRESHOLD_1_4    ((uint32_t)USART_CR3_TXFTCFG_0)                       /*!< TXFIFO reaches 1/4 of its depth */
#define USART_TXFIFO_THRESHOLD_1_2    ((uint32_t)USART_CR3_TXFTCFG_1)                       /*!< TXFIFO reaches 1/2 of its depth */
#define USART_TXFIFO_THRESHOLD_3_4    ((uint32_t)(USART_CR3_TXFTCFG_0|USART_CR3_TXFTCFG_1)) /*!< TXFIFO reaches 3/4 of its depth */
#define USART_TXFIFO_THRESHOLD_7_8    ((uint32_t)USART_CR3_TXFTCFG_2)                       /*!< TXFIFO reaches 7/8 of its depth */
#define USART_TXFIFO_THRESHOLD_8_8    ((uint32_t)(USART_CR3_TXFTCFG_2|USART_CR3_TXFTCFG_0)) /*!< TXFIFO becomes empty            */
/**
  * @}
  */

/** @defgroup USART_RXFIFO_threshold_level USART RXFIFO threshold level
  * @brief    USART RXFIFO level
  * @{
  */
#define USART_RXFIFO_THRESHOLD_1_8    ((uint32_t)0x00000000U)                               /*!< RXFIFO reaches 1/8 of its depth */
#define USART_RXFIFO_THRESHOLD_1_4    ((uint32_t)USART_CR3_RXFTCFG_0)                       /*!< RXFIFO reaches 1/4 of its depth */
#define USART_RXFIFO_THRESHOLD_1_2    ((uint32_t)USART_CR3_RXFTCFG_1)                       /*!< RXFIFO reaches 1/2 of its depth */
#define USART_RXFIFO_THRESHOLD_3_4    ((uint32_t)(USART_CR3_RXFTCFG_0|USART_CR3_RXFTCFG_1)) /*!< RXFIFO reaches 3/4 of its depth */
#define USART_RXFIFO_THRESHOLD_7_8    ((uint32_t)USART_CR3_RXFTCFG_2)                       /*!< RXFIFO reaches 7/8 of its depth */
#define USART_RXFIFO_THRESHOLD_8_8    ((uint32_t)(USART_CR3_RXFTCFG_2|USART_CR3_RXFTCFG_0)) /*!< RXFIFO becomes full             */
/**
  * @}
  */

/** @defgroup USART_Request_Parameters  USART Request Parameters
  * @{
  */
#define USART_RXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_RXFRQ)        /*!< Receive Data flush Request  */
#define USART_TXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_TXFRQ)        /*!< Transmit data flush Request */
/**
  * @}
  */

/** @defgroup USART_Flags      USART Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define USART_FLAG_TXFT                      USART_ISR_TXFT    /*!< USART TXFIFO threshold flag            */
#define USART_FLAG_RXFT                      USART_ISR_RXFT    /*!< USART RXFIFO threshold flag            */
#define USART_FLAG_RXFF                      USART_ISR_RXFF    /*!< USART RXFIFO Fullflag                  */
#define USART_FLAG_TXFE                      USART_ISR_TXFE    /*!< USART TXFIFO Empty flag                */
#define USART_FLAG_REACK                     USART_ISR_REACK   /*!< USART receive enable acknowledge flag  */
#define USART_FLAG_TEACK                     USART_ISR_TEACK   /*!< USART transmit enable acknowledge flag */
#define USART_FLAG_BUSY                      USART_ISR_BUSY    /*!< USART busy flag                        */
#define USART_FLAG_UDR                       USART_ISR_UDR     /*!< USART SPI slave underrun error         */
#define USART_FLAG_LBDF                      USART_ISR_LBDF    /*!< USART LIN break detection flag         */
#define USART_FLAG_TXE                       USART_ISR_TXE     /*!< USART transmit data register empty     */
#define USART_FLAG_TXFNF                     USART_ISR_TXE     /*!< USART TXFIFO not full                  */
#define USART_FLAG_TC                        USART_ISR_TC      /*!< USART transmission complete            */
#define USART_FLAG_RXNE                      USART_ISR_RXNE    /*!< USART read data register not empty     */
#define USART_FLAG_RXFNE                     USART_ISR_RXNE    /*!< USART RXFIFO not empty                 */
#define USART_FLAG_IDLE                      USART_ISR_IDLE    /*!< USART idle flag                        */
#define USART_FLAG_ORE                       USART_ISR_ORE     /*!< USART overrun error                    */
#define USART_FLAG_NE                        USART_ISR_NE      /*!< USART noise error                      */
#define USART_FLAG_FE                        USART_ISR_FE      /*!< USART frame error                      */
#define USART_FLAG_PE                        USART_ISR_PE      /*!< USART parity error                     */
/**
  * @}
  */

/** @defgroup USART_Interrupt_definition USART Interrupts Definition
  *        Elements values convention: 0000ZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZ  : Flag position in the ISR register(5bits instead of 4bits)
  * @{
  */

#define USART_IT_PE                          ((uint16_t)0x0028U)
#define USART_IT_TXE                         ((uint16_t)0x0727U)
#define USART_IT_TC                          ((uint16_t)0x0626U)
#define USART_IT_RXNE                        ((uint16_t)0x0525U)
#define USART_IT_IDLE                        ((uint16_t)0x0424U)
#define USART_IT_ERR                         ((uint16_t)0x0060U)
#define USART_IT_RXFF                        ((uint16_t)0x183FU)
#define USART_IT_TXFE                        ((uint16_t)0x173EU)
#define USART_IT_RXFT                        ((uint16_t)0x1A7CU)
#define USART_IT_TXFT                        ((uint16_t)0x1B77U)

#define USART_IT_UDR                         ((uint16_t)0x0D00U)
#define USART_IT_ORE                         ((uint16_t)0x0300U)
#define USART_IT_NE                          ((uint16_t)0x0200U)
#define USART_IT_FE                          ((uint16_t)0x0100U)
/**
  * @}
  */

/** @defgroup USART_IT_CLEAR_Flags    USART Interruption Clear Flags
  * @{
  */
#define USART_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag          */
#define USART_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag         */
#define USART_CLEAR_NEF                       USART_ICR_NCF             /*!< Noise detected Clear Flag        */
#define USART_CLEAR_OREF                      USART_ICR_ORECF           /*!< OverRun Error Clear Flag         */
#define USART_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag    */
#define USART_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag */
#define USART_CLEAR_UDRCF                     USART_ICR_UDRCF           /*!< UnderRun Error Clear Flag        */
#define USART_CLEAR_TXFECF                    USART_ICR_TXFECF          /*!< TXFIFO empty clear flag          */
/**
  * @}
  */

/** @defgroup USART_Interruption_Mask    USART Interruption Flags Mask
  * @{
  */
#define USART_IT_MASK                             ((uint16_t)0x001FU)     /*!< USART interruptions flags mask */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup USART_Exported_Macros USART Exported Macros
  * @{
  */

/** @brief Reset USART handle state.
  * @param  __HANDLE__: USART handle.
  * @retval None
  */
#define __HAL_USART_RESET_HANDLE_STATE(__HANDLE__)  ((__HANDLE__)->State = HAL_USART_STATE_RESET)

/** @brief  Check whether the specified USART flag is set or not.
  * @param  __HANDLE__: specifies the USART Handle
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg USART_FLAG_TXFT: TXFIFO threshold flag
  *            @arg USART_FLAG_RXFT: RXFIFO threshold flag
  *            @arg USART_FLAG_RXFF:  RXFIFO Full flag
  *            @arg USART_FLAG_TXFE:  TXFIFO Empty flag
  *            @arg USART_FLAG_REACK: Receive enable ackowledge flag
  *            @arg USART_FLAG_TEACK: Transmit enable ackowledge flag
  *            @arg USART_FLAG_BUSY:  Busy flag
  *            @arg USART_FLAG_TXE:   Transmit data register empty flag
  *            @arg USART_FLAG_TC:    Transmission Complete flag
  *            @arg USART_FLAG_RXNE:  Receive data register not empty flag
  *            @arg USART_FLAG_IDLE:  Idle Line detection flag
  *            @arg USART_FLAG_ORE:   OverRun Error flag
  *            @arg USART_FLAG_UDR:   UnderRun Error flag
  *            @arg USART_FLAG_NE:    Noise Error flag
  *            @arg USART_FLAG_FE:    Framing Error flag
  *            @arg USART_FLAG_PE:    Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_USART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the specified USART pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg USART_FLAG_TXFT:  TXFIFO threshold flag
  *            @arg USART_FLAG_RXFT:  RXFIFO threshold flag
  *            @arg USART_FLAG_RXFF:  RXFIFO Full flag
  *            @arg USART_FLAG_TXFE:  TXFIFO Empty flag
  *            @arg USART_FLAG_REACK: Receive enable ackowledge flag
  *            @arg USART_FLAG_TEACK: Transmit enable ackowledge flag
  *            @arg USART_FLAG_WUF:   Wake up from stop mode flag
  *            @arg USART_FLAG_RWU:   Receiver wake up flag (is the USART in mute mode)
  *            @arg USART_FLAG_SBKF:  Send Break flag
  *            @arg USART_FLAG_CMF:   Character match flag
  *            @arg USART_FLAG_BUSY:  Busy flag
  *            @arg USART_FLAG_ABRF:  Auto Baud rate detection flag
  *            @arg USART_FLAG_ABRE:  Auto Baud rate detection error flag
  *            @arg USART_FLAG_RTOF:  Receiver timeout flag
  *            @arg USART_FLAG_LBD:   LIN Break detection flag
  *            @arg USART_FLAG_TXE:   Transmit data register empty flag
  *            @arg USART_FLAG_TC:    Transmission Complete flag
  *            @arg USART_FLAG_RXNE:  Receive data register not empty flag
  *            @arg USART_FLAG_IDLE:  Idle Line detection flag
  *            @arg USART_FLAG_ORE:   OverRun Error flag
  *            @arg USART_FLAG_NE:    Noise Error flag
  *            @arg USART_FLAG_FE:    Framing Error flag
  *            @arg USART_FLAG_PE:    Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_USART_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))


/** @brief  Enable the specified USART interrupt.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __INTERRUPT__: specifies the USART interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_RXFF: RXFIFO Full interrupt
  *            @arg USART_IT_TXFE: TXFIFO Empty interrupt
  *            @arg USART_IT_RXFT: RXFIFO threshold interrupt
  *            @arg USART_IT_TXFT: TXFIFO threshold interrupt
  *            @arg USART_IT_TXE : Transmit Data Register empty interrupt
  *            @arg USART_IT_TC  : Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_PE  : Parity Error interrupt
  *            @arg USART_IT_ERR : Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_USART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((((uint8_t)(__INTERRUPT__)) >> 5U) == 1)? ((__HANDLE__)->Instance->CR1 |= (1U << ((__INTERRUPT__) & USART_IT_MASK))): \
                                                            ((((uint8_t)(__INTERRUPT__)) >> 5U) == 2)? ((__HANDLE__)->Instance->CR2 |= (1U << ((__INTERRUPT__) & USART_IT_MASK))): \
                                                            ((__HANDLE__)->Instance->CR3 |= (1U << ((__INTERRUPT__) & USART_IT_MASK))))

/** @brief  Disable the specified USART interrupt.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __INTERRUPT__: specifies the USART interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_RXFF: RXFIFO Full interrupt
  *            @arg USART_IT_TXFE: TXFIFO Empty interrupt
  *            @arg USART_IT_RXFT: RXFIFO threshold interrupt
  *            @arg USART_IT_TXFT: TXFIFO threshold interrupt
  *            @arg USART_IT_TXE : Transmit Data Register empty interrupt
  *            @arg USART_IT_TC  : Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_PE  : Parity Error interrupt
  *            @arg USART_IT_ERR : Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_USART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((((uint8_t)(__INTERRUPT__)) >> 5U) == 1)? ((__HANDLE__)->Instance->CR1 &= ~ (1U << ((__INTERRUPT__) & USART_IT_MASK))): \
                                                            ((((uint8_t)(__INTERRUPT__)) >> 5U) == 2)? ((__HANDLE__)->Instance->CR2 &= ~ (1U << ((__INTERRUPT__) & USART_IT_MASK))): \
                                                            ((__HANDLE__)->Instance->CR3 &= ~ (1U << ((__INTERRUPT__) & USART_IT_MASK))))


/** @brief  Check whether the specified USART interrupt has occurred or not.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __IT__: specifies the USART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_RXFF: RXFIFO Full interrupt
  *            @arg USART_IT_TXFE: TXFIFO Empty interrupt
  *            @arg USART_IT_RXFT: RXFIFO threshold interrupt
  *            @arg USART_IT_TXFT: TXFIFO threshold interrupt
  *            @arg USART_IT_TXE : Transmit Data Register empty interrupt
  *            @arg USART_IT_TC  : Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_ORE : OverRun Error interrupt
  *            @arg USART_IT_UDR : UnderRun Error interrupt
  *            @arg USART_IT_NE  : Noise Error interrupt
  *            @arg USART_IT_FE  : Framing Error interrupt
  *            @arg USART_IT_PE  : Parity Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_USART_GET_IT(__HANDLE__, __IT__) ((__HANDLE__)->Instance->ISR & ((uint32_t)1 << ((__IT__)>> 0x08)))

/** @brief  Check whether the specified USART interrupt source is enabled or not.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __IT__: specifies the USART interrupt source to check.
  *          This parameter can be one of the following values:
   *           @arg USART_IT_RXFF: RXFIFO Full interrupt
  *            @arg USART_IT_TXFE: TXFIFO Empty interrupt
  *            @arg USART_IT_RXFT: RXFIFO threshold interrupt
  *            @arg USART_IT_TXFT: TXFIFO threshold interrupt
  *            @arg USART_IT_TXE : Transmit Data Register empty interrupt
  *            @arg USART_IT_TC  : Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_ORE : OverRun Error interrupt
  *            @arg USART_IT_NE  : Noise Error interrupt
  *            @arg USART_IT_FE  : Framing Error interrupt
  *            @arg USART_IT_PE  : Parity Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_USART_GET_IT_SOURCE(__HANDLE__, __IT__) ((((((uint8_t)(__IT__)) >> 5) == 1)? (__HANDLE__)->Instance->CR1:(((((uint8_t)(__IT__)) >> 5) == 2)? \
                                                   (__HANDLE__)->Instance->CR2 : (__HANDLE__)->Instance->CR3)) & ((uint32_t)1 << \
                                                   (((uint16_t)(__IT__)) & USART_IT_MASK)))


/** @brief  Clear the specified USART ISR flag, in setting the proper ICR register flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __IT_CLEAR__: specifies the interrupt clear register flag that needs to be set
  *                       to clear the corresponding interrupt.
  *          This parameter can be one of the following values:
  *            @arg USART_CLEAR_PEF: Parity Error Clear Flag
  *            @arg USART_CLEAR_FEF: Framing Error Clear Flag
  *            @arg USART_CLEAR_NEF: Noise detected Clear Flag
  *            @arg USART_CLEAR_OREF: OverRun Error Clear Flag
  *            @arg USART_CLEAR_IDLEF: IDLE line detected Clear Flag
  *            @arg USART_CLEAR_TCF: Transmission Complete Clear Flag
  *            @arg USART_CLEAR_UDRCF: UnderRun Error Clear Flag
  *            @arg USART_CLEAR_TXFECF: TXFIFO empty Clear Flag
  * @retval None
  */
#define __HAL_USART_CLEAR_IT(__HANDLE__, __IT_CLEAR__) ((__HANDLE__)->Instance->ICR = (uint32_t)(__IT_CLEAR__))

/** @brief  Clear the USART PE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_PEFLAG(__HANDLE__)   __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_PEF)

/** @brief  Clear the USART FE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_FEFLAG(__HANDLE__)   __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_FEF)

/** @brief  Clear the USART NE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_NEFLAG(__HANDLE__)  __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_NEF)

/** @brief  Clear the USART ORE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_OREFLAG(__HANDLE__)   __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_OREF)

/** @brief  Clear the USART IDLE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_IDLEFLAG(__HANDLE__)   __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_IDLEF)

/** @brief  Clear the USART UDR pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_UDRFLAG(__HANDLE__)   __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_UDRCF)

/** @brief  Clear the USART TX FIFO empty clear flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_CLEAR_TXFECF(__HANDLE__)   __HAL_USART_CLEAR_IT((__HANDLE__), USART_CLEAR_TXFECF)



/** @brief  Set a specific USART request flag.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __REQ__: specifies the request flag to set.
  *          This parameter can be one of the following values:
  *            @arg USART_RXDATA_FLUSH_REQUEST: Receive Data flush Request
  *            @arg USART_TXDATA_FLUSH_REQUEST: Transmit data flush Request
  *
  * @retval None
  */
#define __HAL_USART_SEND_REQ(__HANDLE__, __REQ__)      ((__HANDLE__)->Instance->RQR |= (__REQ__))

/** @brief  Enable the USART one bit sample method.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  Disable the USART one bit sample method.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT))

/** @brief  Enable USART.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR1 |=  USART_CR1_UE)

/** @brief  Disable USART.
  * @param  __HANDLE__: specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_DISABLE(__HANDLE__)                ((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_UE)

/**
  * @}
  */

/* Private variables -----------------------------------------------------*/
/** @defgroup USART_Private_Variables   USART Private Variables
  * @{
  */
static const uint16_t USARTPrescTable[12] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256};
/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @defgroup USART_Private_Macros   USART Private Macros
  * @{
  */

/** @brief  Report the USART clock source.
  * @param  __HANDLE__: specifies the USART Handle.
  * @param  __CLOCKSOURCE__: output variable.
  * @retval the USART clocking source, written in __CLOCKSOURCE__.
  */
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)       \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
       switch(__HAL_RCC_GET_USART1_SOURCE())                   \
       {                                                       \
        case RCC_USART1CLKSOURCE_D2PCLK2:                      \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_D2PCLK2;       \
          break;                                               \
        case RCC_USART1CLKSOURCE_PLL2:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL2;          \
          break;                                               \
        case RCC_USART1CLKSOURCE_PLL3:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL3;          \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_CSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_CSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
       switch(__HAL_RCC_GET_USART2_SOURCE())                   \
       {                                                       \
        case RCC_USART2CLKSOURCE_D2PCLK1:                      \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_D2PCLK1;       \
          break;                                               \
        case RCC_USART2CLKSOURCE_PLL2:                        \
           (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL2;         \
          break;                                               \
        case RCC_USART2CLKSOURCE_PLL3:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL3;          \
          break;                                               \
        case RCC_USART2CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART2CLKSOURCE_CSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_CSI;           \
          break;                                               \
        case RCC_USART2CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
       switch(__HAL_RCC_GET_USART3_SOURCE())                   \
       {                                                       \
        case RCC_USART3CLKSOURCE_D2PCLK1:                      \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_D2PCLK1;       \
          break;                                               \
        case RCC_USART3CLKSOURCE_PLL2:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL2;          \
          break;                                               \
        case RCC_USART3CLKSOURCE_PLL3:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL3;          \
          break;                                               \
        case RCC_USART3CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART3CLKSOURCE_CSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_CSI;           \
          break;                                               \
        case RCC_USART3CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART6)                  \
    {                                                          \
       switch(__HAL_RCC_GET_USART6_SOURCE())                   \
       {                                                       \
        case RCC_USART6CLKSOURCE_D2PCLK2:                      \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_D2PCLK2;       \
          break;                                               \
        case RCC_USART6CLKSOURCE_PLL2:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL2;          \
          break;                                               \
        case RCC_USART6CLKSOURCE_PLL3:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PLL3;          \
          break;                                               \
        case RCC_USART6CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART6CLKSOURCE_CSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_CSI;           \
          break;                                               \
        case RCC_USART6CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
       }                                                       \
    }                                                          \
  } while(0)

/** @brief  BRR division operation to set BRR register in 8-bit oversampling mode.
  * @param  __PCLK__: USART clock.
  * @param  __BAUD__: Baud rate set by the user.
  * @param  __PRESCALER__: UART prescaler value.
  * @retval Division result
  */
#define USART_DIV_SAMPLING8(__PCLK__, __BAUD__, __PRESCALER__)   (((((__PCLK__)/USARTPrescTable[(__PRESCALER__)])*2) + ((__BAUD__)/2)) / (__BAUD__))

/** @brief  Check USART Baud rate.
  * @param  __BAUDRATE__: Baudrate specified by the user.
  *         The maximum Baud Rate is derived from the maximum clock on H7 (i.e. 100 MHz)
  *         divided by the smallest oversampling used on the USART (i.e. 8).
  * @retval Test result (TRUE or FALSE).
  */
#define IS_USART_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 12500001U)

/**
  * @brief Ensure that USART frame number of stop bits is valid.
  * @param __STOPBITS__: USART frame number of stop bits.
  * @retval SET (__STOPBITS__ is valid) or RESET (__STOPBITS__ is invalid)
  */
#define IS_USART_STOPBITS(__STOPBITS__) (((__STOPBITS__) == USART_STOPBITS_0_5) || \
                                         ((__STOPBITS__) == USART_STOPBITS_1)   || \
                                         ((__STOPBITS__) == USART_STOPBITS_1_5) || \
                                         ((__STOPBITS__) == USART_STOPBITS_2))

/**
  * @brief Ensure that USART frame parity is valid.
  * @param __PARITY__: USART frame parity.
  * @retval SET (__PARITY__ is valid) or RESET (__PARITY__ is invalid)
  */
#define IS_USART_PARITY(__PARITY__) (((__PARITY__) == USART_PARITY_NONE) || \
                                     ((__PARITY__) == USART_PARITY_EVEN) || \
                                     ((__PARITY__) == USART_PARITY_ODD))

/**
  * @brief Ensure that USART communication mode is valid.
  * @param __MODE__: USART communication mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_USART_MODE(__MODE__) ((((__MODE__) & (uint32_t)0xFFFFFFF3U) == 0x00U) && ((__MODE__) != (uint32_t)0x00U))

/**
  * @brief Ensure that USART oversampling is valid.
  * @param __SAMPLING__: USART oversampling.
  * @retval SET (__SAMPLING__ is valid) or RESET (__SAMPLING__ is invalid)
  */
#define IS_USART_OVERSAMPLING(__SAMPLING__) (((__SAMPLING__) == USART_OVERSAMPLING_16) || \
                                             ((__SAMPLING__) == USART_OVERSAMPLING_8))

/**
  * @brief Ensure that USART clock state is valid.
  * @param __CLOCK__: USART clock state.
  * @retval SET (__CLOCK__ is valid) or RESET (__CLOCK__ is invalid)
  */
#define IS_USART_CLOCK(__CLOCK__) (((__CLOCK__) == USART_CLOCK_DISABLE) || \
                                   ((__CLOCK__) == USART_CLOCK_ENABLE))

/**
  * @brief Ensure that USART frame polarity is valid.
  * @param __CPOL__: USART frame polarity.
  * @retval SET (__CPOL__ is valid) or RESET (__CPOL__ is invalid)
  */
#define IS_USART_POLARITY(__CPOL__) (((__CPOL__) == USART_POLARITY_LOW) || ((__CPOL__) == USART_POLARITY_HIGH))

/**
  * @brief Ensure that USART frame phase is valid.
  * @param __CPHA__: USART frame phase.
  * @retval SET (__CPHA__ is valid) or RESET (__CPHA__ is invalid)
  */
#define IS_USART_PHASE(__CPHA__) (((__CPHA__) == USART_PHASE_1EDGE) || ((__CPHA__) == USART_PHASE_2EDGE))

/**
  * @brief Ensure that USART frame last bit clock pulse setting is valid.
  * @param __LASTBIT__: USART frame last bit clock pulse setting.
  * @retval SET (__LASTBIT__ is valid) or RESET (__LASTBIT__ is invalid)
  */
#define IS_USART_LASTBIT(__LASTBIT__) (((__LASTBIT__) == USART_LASTBIT_DISABLE) || \
                                       ((__LASTBIT__) == USART_LASTBIT_ENABLE))

/**
  * @brief Ensure that USART request parameter is valid.
  * @param __PARAM__: USART request parameter.
  * @retval SET (__PARAM__ is valid) or RESET (__PARAM__ is invalid)
  */
#define IS_USART_REQUEST_PARAMETER(__PARAM__) (((__PARAM__) == USART_RXDATA_FLUSH_REQUEST) || \
                                               ((__PARAM__) == USART_TXDATA_FLUSH_REQUEST))

/**
  * @brief Ensure that USART Prescaler is valid.
  * @param __PRESCALER__: USART Prescaler value.
  * @retval SET (__PRESCALER__ is valid) or RESET (__PRESCALER__ is invalid)
  */
#define IS_USART_PRESCALER(__PRESCALER__) (((__PRESCALER__) == USART_PRESCALER_DIV1) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV2) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV4) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV6) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV8) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV10) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV12) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV16) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV32) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV64) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV128) || \
                                           ((__PRESCALER__) == USART_PRESCALER_DIV256))

/**
  * @brief Ensure that USART NSS is valid.
  * @param __NSS__: USART Negative Slave Select pin management.
  * @retval SET (__NSS__ is valid) or RESET (__NSS__ is invalid)
  */
#define IS_USART_NSS(__NSS__) (((__NSS__) == USART_NSS_HW) || ((__NSS__) == USART_NSS_SW))

/**
  * @brief Ensure that USART FIFO mode is valid.
  * @param __STATE__: USART FIFO mode.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_USART_FIFO_MODE_STATE(__STATE__) (((__STATE__) == USART_FIFOMODE_DISABLE ) || \
                                             ((__STATE__) == USART_FIFOMODE_ENABLE))

/**
  * @brief Ensure that USART TXFIFO threshold level is valid.
  * @param __THRESHOLD__: USART TXFIFO threshold level.
  * @retval SET (__THRESHOLD__ is valid) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_USART_TXFIFO_THRESHOLD(__THRESHOLD__) (((__THRESHOLD__) == USART_TXFIFO_THRESHOLD_1_8) || \
                                                  ((__THRESHOLD__) == USART_TXFIFO_THRESHOLD_1_4) || \
                                                  ((__THRESHOLD__) == USART_TXFIFO_THRESHOLD_1_2) || \
                                                  ((__THRESHOLD__) == USART_TXFIFO_THRESHOLD_3_4) || \
                                                  ((__THRESHOLD__) == USART_TXFIFO_THRESHOLD_7_8) || \
                                                  ((__THRESHOLD__) == USART_TXFIFO_THRESHOLD_8_8))

/**
  * @brief Ensure that USART RXFIFO threshold level is valid.
  * @param __THRESHOLD__: USART RXFIFO threshold level.
  * @retval SET (__THRESHOLD__ is valid) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_USART_RXFIFO_THRESHOLD(__THRESHOLD__) (((__THRESHOLD__) == USART_RXFIFO_THRESHOLD_1_8) || \
                                                  ((__THRESHOLD__) == USART_RXFIFO_THRESHOLD_1_4) || \
                                                  ((__THRESHOLD__) == USART_RXFIFO_THRESHOLD_1_2) || \
                                                  ((__THRESHOLD__) == USART_RXFIFO_THRESHOLD_3_4) || \
                                                  ((__THRESHOLD__) == USART_RXFIFO_THRESHOLD_7_8) || \
                                                  ((__THRESHOLD__) == USART_RXFIFO_THRESHOLD_8_8))

/**
  * @brief Ensure that USART Slave Mode is valid.
  * @param __STATE__: USART Slave Mode.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_USART_SLAVEMODE(__STATE__)   (((__STATE__) == USART_SLAVEMODE_DISABLE ) || \
                                         ((__STATE__) == USART_SLAVEMODE_ENABLE))

/**
  * @}
  */

/* Include USART HAL Extended module */
#include "stm32h7xx_hal_usart_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USART_Exported_Functions USART Exported Functions
  * @{
  */

/** @addtogroup USART_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *husart);
void HAL_USART_MspInit(USART_HandleTypeDef *husart);
void HAL_USART_MspDeInit(USART_HandleTypeDef *husart);

/**
  * @}
  */

/** @addtogroup USART_Exported_Functions_Group2 IO operation functions
  * @{
  */

/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_USART_TransmitReceive(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_TransmitReceive_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,  uint16_t Size);
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_TransmitReceive_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *husart);
/* Transfer Abort functions */
HAL_StatusTypeDef HAL_USART_Abort(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_Abort_IT(USART_HandleTypeDef *husart);

void HAL_USART_IRQHandler(USART_HandleTypeDef *husart);
void HAL_USART_TxHalfCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_RxHalfCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_TxRxCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart);
void HAL_USART_AbortCpltCallback (USART_HandleTypeDef *husart);

/**
  * @}
  */

/* Peripheral Control functions ***********************************************/

/** @addtogroup USART_Exported_Functions_Group4 Peripheral State and Error functions
  * @{
  */

/* Peripheral State and Error functions ***************************************/
HAL_USART_StateTypeDef HAL_USART_GetState(USART_HandleTypeDef *husart);
uint32_t               HAL_USART_GetError(USART_HandleTypeDef *husart);

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

#endif /* __STM32H7xx_HAL_USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
