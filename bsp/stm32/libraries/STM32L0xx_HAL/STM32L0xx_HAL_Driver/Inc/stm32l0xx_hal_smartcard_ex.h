/**
  ******************************************************************************
  * @file    stm32l0xx_hal_smartcard_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SMARTCARD HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#ifndef STM32L0xx_HAL_SMARTCARD_EX_H
#define STM32L0xx_HAL_SMARTCARD_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined (STM32L010x4) && !defined (STM32L010x6)
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup SMARTCARDEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup SMARTCARDEx_Exported_Constants  SMARTCARD Extended Exported Constants
  * @{
  */

/** @defgroup SMARTCARDEx_Transmission_Completion_Indication SMARTCARD Transmission Completion Indication
  * @{
  */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_TCBGT      SMARTCARD_IT_TCBGT /*!< SMARTCARD transmission complete before guard time */
#endif /* USART_TCBGT_SUPPORT */
#define SMARTCARD_TC         SMARTCARD_IT_TC    /*!< SMARTCARD transmission complete (flag raised when guard time has elapsed) */
/**
  * @}
  */

/** @defgroup SMARTCARDEx_Advanced_Features_Initialization_Type SMARTCARD advanced feature initialization type
  * @{
  */
#define SMARTCARD_ADVFEATURE_NO_INIT                 0x00000000U    /*!< No advanced feature initialization                  */
#define SMARTCARD_ADVFEATURE_TXINVERT_INIT           0x00000001U    /*!< TX pin active level inversion                       */
#define SMARTCARD_ADVFEATURE_RXINVERT_INIT           0x00000002U    /*!< RX pin active level inversion                       */
#define SMARTCARD_ADVFEATURE_DATAINVERT_INIT         0x00000004U    /*!< Binary data inversion                               */
#define SMARTCARD_ADVFEATURE_SWAP_INIT               0x00000008U    /*!< TX/RX pins swap                                     */
#define SMARTCARD_ADVFEATURE_RXOVERRUNDISABLE_INIT   0x00000010U    /*!< RX overrun disable                                  */
#define SMARTCARD_ADVFEATURE_DMADISABLEONERROR_INIT  0x00000020U    /*!< DMA disable on Reception Error                      */
#define SMARTCARD_ADVFEATURE_MSBFIRST_INIT           0x00000080U    /*!< Most significant bit sent/received first            */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_ADVFEATURE_TXCOMPLETION            0x00000100U    /*!< TX completion indication before of after guard time */
#endif /* USART_TCBGT_SUPPORT */
/**
  * @}
  */

/** @defgroup SMARTCARDEx_Flags SMARTCARD Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_FLAG_TCBGT          USART_ISR_TCBGT         /*!< SMARTCARD transmission complete before guard time completion */
#endif /* USART_TCBGT_SUPPORT */
#define SMARTCARD_FLAG_REACK          USART_ISR_REACK         /*!< SMARTCARD receive enable acknowledge flag  */
#define SMARTCARD_FLAG_TEACK          USART_ISR_TEACK         /*!< SMARTCARD transmit enable acknowledge flag */
#define SMARTCARD_FLAG_BUSY           USART_ISR_BUSY          /*!< SMARTCARD busy flag                        */
#define SMARTCARD_FLAG_EOBF           USART_ISR_EOBF          /*!< SMARTCARD end of block flag                */
#define SMARTCARD_FLAG_RTOF           USART_ISR_RTOF          /*!< SMARTCARD receiver timeout flag            */
#define SMARTCARD_FLAG_TXE            USART_ISR_TXE           /*!< SMARTCARD transmit data register empty     */
#define SMARTCARD_FLAG_TC             USART_ISR_TC            /*!< SMARTCARD transmission complete            */
#define SMARTCARD_FLAG_RXNE           USART_ISR_RXNE          /*!< SMARTCARD read data register not empty     */
#define SMARTCARD_FLAG_IDLE           USART_ISR_IDLE          /*!< SMARTCARD idle line detection              */
#define SMARTCARD_FLAG_ORE            USART_ISR_ORE           /*!< SMARTCARD overrun error                    */
#define SMARTCARD_FLAG_NE             USART_ISR_NE            /*!< SMARTCARD noise error                      */
#define SMARTCARD_FLAG_FE             USART_ISR_FE            /*!< SMARTCARD frame error                      */
#define SMARTCARD_FLAG_PE             USART_ISR_PE            /*!< SMARTCARD parity error                     */
/**
  * @}
  */

/** @defgroup SMARTCARDEx_Interrupt_definition SMARTCARD Interrupts Definition
  *        Elements values convention: 000ZZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5 bits)
  *           - XX  : Interrupt source register (2 bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZZ  : Flag position in the ISR register(5 bits)
  * @{
  */
#define SMARTCARD_IT_PE                     0x0028U           /*!< SMARTCARD parity error interruption                 */
#define SMARTCARD_IT_TXE                    0x0727U           /*!< SMARTCARD transmit data register empty interruption */
#define SMARTCARD_IT_TC                     0x0626U           /*!< SMARTCARD transmission complete interruption        */
#define SMARTCARD_IT_RXNE                   0x0525U           /*!< SMARTCARD read data register not empty interruption */
#define SMARTCARD_IT_IDLE                   0x0424U           /*!< SMARTCARD idle line detection interruption          */

#define SMARTCARD_IT_ERR                    0x0060U           /*!< SMARTCARD error interruption         */
#define SMARTCARD_IT_ORE                    0x0300U           /*!< SMARTCARD overrun error interruption */
#define SMARTCARD_IT_NE                     0x0200U           /*!< SMARTCARD noise error interruption   */
#define SMARTCARD_IT_FE                     0x0100U           /*!< SMARTCARD frame error interruption   */

#define SMARTCARD_IT_EOB                    0x0C3BU           /*!< SMARTCARD end of block interruption     */
#define SMARTCARD_IT_RTO                    0x0B3AU           /*!< SMARTCARD receiver timeout interruption */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_IT_TCBGT                  0x1978U           /*!< SMARTCARD transmission complete before guard time completion interruption */
#endif /* USART_TCBGT_SUPPORT */

/**
  * @}
  */

/** @defgroup SMARTCARDEx_IT_CLEAR_Flags SMARTCARD Interruption Clear Flags
  * @{
  */
#define SMARTCARD_CLEAR_PEF                 USART_ICR_PECF    /*!< SMARTCARD parity error clear flag          */
#define SMARTCARD_CLEAR_FEF                 USART_ICR_FECF    /*!< SMARTCARD framing error clear flag         */
#define SMARTCARD_CLEAR_NEF                 USART_ICR_NCF     /*!< SMARTCARD noise error detected clear flag  */
#define SMARTCARD_CLEAR_OREF                USART_ICR_ORECF   /*!< SMARTCARD overrun error clear flag         */
#define SMARTCARD_CLEAR_IDLEF               USART_ICR_IDLECF  /*!< SMARTCARD idle line detected clear flag    */
#define SMARTCARD_CLEAR_TCF                 USART_ICR_TCCF    /*!< SMARTCARD transmission complete clear flag */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_CLEAR_TCBGTF              USART_ICR_TCBGTCF /*!< SMARTCARD transmission complete before guard time completion clear flag */
#endif /* USART_TCBGT_SUPPORT */
#define SMARTCARD_CLEAR_RTOF                USART_ICR_RTOCF   /*!< SMARTCARD receiver time out clear flag     */
#define SMARTCARD_CLEAR_EOBF                USART_ICR_EOBCF   /*!< SMARTCARD end of block clear flag          */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup SMARTCARDEx_Private_Macros SMARTCARD Extended Private Macros
  * @{
  */

/** @brief  Set the Transmission Completion flag
  * @param  __HANDLE__ specifies the SMARTCARD Handle.
  * @note  If TCBGT (Transmission Complete Before Guard Time) flag is not available or if
  *        AdvancedInit.TxCompletionIndication is not already filled, the latter is forced
  *        to SMARTCARD_TC (transmission completion indication when guard time has elapsed).
  * @retval None
  */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_TRANSMISSION_COMPLETION_SETTING(__HANDLE__)                                                \
  do {                                                                                                       \
    if (HAL_IS_BIT_CLR((__HANDLE__)->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_TXCOMPLETION))        \
    {                                                                                                        \
     (__HANDLE__)->AdvancedInit.TxCompletionIndication = SMARTCARD_TC;                                       \
    }                                                                                                        \
    else                                                                                                     \
    {                                                                                                        \
      assert_param(IS_SMARTCARD_TRANSMISSION_COMPLETION((__HANDLE__)->AdvancedInit.TxCompletionIndication)); \
    }                                                                                                        \
  } while(0U)
#else
#define SMARTCARD_TRANSMISSION_COMPLETION_SETTING(__HANDLE__)         \
  do {                                                                \
    (__HANDLE__)->AdvancedInit.TxCompletionIndication = SMARTCARD_TC; \
  } while(0U)
#endif /* USART_TCBGT_SUPPORT */

/** @brief  Return the transmission completion flag.
  * @param  __HANDLE__ specifies the SMARTCARD Handle.
  * @note  Based on AdvancedInit.TxCompletionIndication setting, return TC or TCBGT flag.
  *        When TCBGT flag (Transmission Complete Before Guard Time) is not available, TC flag is
  *        reported.
  * @retval Transmission completion flag
  */
#if defined(USART_TCBGT_SUPPORT)
#define SMARTCARD_TRANSMISSION_COMPLETION_FLAG(__HANDLE__)  \
  (((__HANDLE__)->AdvancedInit.TxCompletionIndication == SMARTCARD_TC) ? (SMARTCARD_FLAG_TC) :  (SMARTCARD_FLAG_TCBGT))
#else
#define SMARTCARD_TRANSMISSION_COMPLETION_FLAG(__HANDLE__)    (SMARTCARD_FLAG_TC)
#endif /* USART_TCBGT_SUPPORT */


/** @brief Ensure that SMARTCARD frame transmission completion used flag is valid.
  * @param __TXCOMPLETE__ SMARTCARD frame transmission completion used flag.
  * @retval SET (__TXCOMPLETE__ is valid) or RESET (__TXCOMPLETE__ is invalid)
  */
#if defined(USART_TCBGT_SUPPORT)
#define IS_SMARTCARD_TRANSMISSION_COMPLETION(__TXCOMPLETE__) (((__TXCOMPLETE__) == SMARTCARD_TCBGT) || \
                                                              ((__TXCOMPLETE__) == SMARTCARD_TC))
#else
#define IS_SMARTCARD_TRANSMISSION_COMPLETION(__TXCOMPLETE__) ((__TXCOMPLETE__) == SMARTCARD_TC)
#endif /* USART_TCBGT_SUPPORT */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SMARTCARDEx_Exported_Functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
/* IO operation methods *******************************************************/

/** @addtogroup SMARTCARDEx_Exported_Functions_Group1
  * @{
  */

/* Peripheral Control functions ***********************************************/
void              HAL_SMARTCARDEx_BlockLength_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint8_t BlockLength);
void              HAL_SMARTCARDEx_TimeOut_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint32_t TimeOutValue);
HAL_StatusTypeDef HAL_SMARTCARDEx_EnableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard);
HAL_StatusTypeDef HAL_SMARTCARDEx_DisableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SMARTCARDEx_Exported_Functions_Group2
  * @{
  */

/* IO operation functions *****************************************************/

/**
  * @}
  */

/** @addtogroup SMARTCARDEx_Exported_Functions_Group3
  * @{
  */

/* Peripheral Control functions ***********************************************/

/**
  * @}
  */

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
#endif /* !defined (STM32L010x4) && !defined (STM32L010x6) */

#ifdef __cplusplus
}
#endif

#endif /* STM32L0xx_HAL_SMARTCARD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
