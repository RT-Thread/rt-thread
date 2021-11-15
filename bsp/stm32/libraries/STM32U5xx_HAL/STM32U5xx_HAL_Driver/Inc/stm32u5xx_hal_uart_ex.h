/**
  ******************************************************************************
  * @file    stm32u5xx_hal_uart_ex.h
  * @author  MCD Application Team
  * @brief   Header file of UART HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_UART_EX_H
#define STM32U5xx_HAL_UART_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup UARTEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup UARTEx_Exported_Types UARTEx Exported Types
  * @{
  */

/**
  * @brief  UART wake up from stop mode parameters
  */
typedef struct
{
  uint32_t WakeUpEvent;        /*!< Specifies which event will activate the Wakeup from Stop mode flag (WUF).
                                    This parameter can be a value of @ref UART_WakeUp_from_Stop_Selection.
                                    If set to UART_WAKEUP_ON_ADDRESS, the two other fields below must
                                    be filled up. */

  uint16_t AddressLength;      /*!< Specifies whether the address is 4 or 7-bit long.
                                    This parameter can be a value of @ref UARTEx_WakeUp_Address_Length.  */

  uint8_t Address;             /*!< UART/USART node address (7-bit long max). */
} UART_WakeUpTypeDef;

/**
  * @brief  UART Autonomous mode parameters
  */
typedef struct
{
  uint32_t AutonomousModeState;  /*!< Specifies the autonomous mode state.This parameter can be a value of
                                      @ref UARTEx_Autonomous_mode.*/

  uint32_t TriggerSelection;     /*!< Specifies which trigger will activate the Transmission automatically.
                                      This parameter can be a value of @ref UARTEx_Autonomous_Trigger_selection
                                      or @ref LPUARTEx_Autonomous_Trigger_selection.*/

  uint32_t TriggerPolarity;      /*!< Specifies the autonomous mode trigger signal polarity.
                                      This parameter can be a value of @ref UARTEx_Autonomous_Trigger_Polarity */

  uint32_t DataSize;             /*!< Specifies the transmitted data size in byte */

  uint32_t IdleFrame;            /*!< Specifies whether the IDLE frame transmission is enabled or disabled.
                                      This parameter can be a value of @ref UARTEx_Autonomous_IDLE_FRAME. */
} UART_AutonomousModeConfTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UARTEx_Exported_Constants UARTEx Exported Constants
  * @{
  */

/** @defgroup UARTEx_Word_Length UARTEx Word Length
  * @{
  */
#define UART_WORDLENGTH_7B          USART_CR1_M1   /*!< 7-bit long UART frame */
#define UART_WORDLENGTH_8B          0x00000000U    /*!< 8-bit long UART frame */
#define UART_WORDLENGTH_9B          USART_CR1_M0   /*!< 9-bit long UART frame */
/**
  * @}
  */

/** @defgroup UARTEx_WakeUp_Address_Length UARTEx WakeUp Address Length
  * @{
  */
#define UART_ADDRESS_DETECT_4B      0x00000000U      /*!< 4-bit long wake-up address */
#define UART_ADDRESS_DETECT_7B      USART_CR2_ADDM7  /*!< 7-bit long wake-up address */
/**
  * @}
  */

/** @defgroup UARTEx_FIFO_mode UARTEx FIFO mode
  * @brief    UART FIFO mode
  * @{
  */
#define UART_FIFOMODE_DISABLE       0x00000000U       /*!< FIFO mode disable */
#define UART_FIFOMODE_ENABLE        USART_CR1_FIFOEN  /*!< FIFO mode enable  */
/**
  * @}
  */

/** @defgroup UARTEx_TXFIFO_threshold_level UARTEx TXFIFO threshold level
  * @brief    UART TXFIFO threshold level
  * @{
  */
#define UART_TXFIFO_THRESHOLD_1_8   0x00000000U                               /*!< TX FIFO reaches 1/8 of its depth */
#define UART_TXFIFO_THRESHOLD_1_4   USART_CR3_TXFTCFG_0                       /*!< TX FIFO reaches 1/4 of its depth */
#define UART_TXFIFO_THRESHOLD_1_2   USART_CR3_TXFTCFG_1                       /*!< TX FIFO reaches 1/2 of its depth */
#define UART_TXFIFO_THRESHOLD_3_4   (USART_CR3_TXFTCFG_0|USART_CR3_TXFTCFG_1) /*!< TX FIFO reaches 3/4 of its depth */
#define UART_TXFIFO_THRESHOLD_7_8   USART_CR3_TXFTCFG_2                       /*!< TX FIFO reaches 7/8 of its depth */
#define UART_TXFIFO_THRESHOLD_8_8   (USART_CR3_TXFTCFG_2|USART_CR3_TXFTCFG_0) /*!< TX FIFO becomes empty            */
/**
  * @}
  */

/** @defgroup UARTEx_RXFIFO_threshold_level UARTEx RXFIFO threshold level
  * @brief    UART RXFIFO threshold level
  * @{
  */
#define UART_RXFIFO_THRESHOLD_1_8   0x00000000U                               /*!< RX FIFO reaches 1/8 of its depth */
#define UART_RXFIFO_THRESHOLD_1_4   USART_CR3_RXFTCFG_0                       /*!< RX FIFO reaches 1/4 of its depth */
#define UART_RXFIFO_THRESHOLD_1_2   USART_CR3_RXFTCFG_1                       /*!< RX FIFO reaches 1/2 of its depth */
#define UART_RXFIFO_THRESHOLD_3_4   (USART_CR3_RXFTCFG_0|USART_CR3_RXFTCFG_1) /*!< RX FIFO reaches 3/4 of its depth */
#define UART_RXFIFO_THRESHOLD_7_8   USART_CR3_RXFTCFG_2                       /*!< RX FIFO reaches 7/8 of its depth */
#define UART_RXFIFO_THRESHOLD_8_8   (USART_CR3_RXFTCFG_2|USART_CR3_RXFTCFG_0) /*!< RX FIFO becomes full             */
/**
  * @}
  */

/** @defgroup UARTEx_Autonomous_mode UARTEx Autonomous Mode
  * @brief    UART Autonomous mode
  * @{
  */
#define UART_AUTONOMOUS_MODE_DISABLE  0x00000000U          /*!< Autonomous mode disable */
#define UART_AUTONOMOUS_MODE_ENABLE   USART_AUTOCR_TRIGEN  /*!< Autonomous mode enable  */
/**
  * @}
  */

/** @defgroup UARTEx_Autonomous_Trigger_Polarity UARTEx Autonomous Trigger Polarity
  * @brief    UART Trigger polarity edge selection
  * @{
  */
#define UART_TRIG_POLARITY_RISING   0x00000000U           /*!< UART triggered on rising edge  */
#define UART_TRIG_POLARITY_FALLING  USART_AUTOCR_TRIGPOL  /*!< UART triggered on falling edge */
/**
  * @}
  */

/** @defgroup UARTEx_Autonomous_IDLE_FRAME UARTEx Autonomous IDLE Frame
  * @brief    UART IDLE frame transmission
  * @{
  */
#define UART_IDLE_FRAME_ENABLE      0x00000000U          /*!< IDLE Frame sent after enabling the transmitter */
#define UART_IDLE_FRAME_DISABLE     USART_AUTOCR_IDLEDIS /*!< IDLE Frame not sent after enabling the transmitter */
/**
  * @}
  */

/** @defgroup UARTEx_Autonomous_Trigger_selection UARTEx Autonomous trigger selection
  * @brief    UART Autonomous Trigger selection
  * @{
  */
#define UART_GPDMA1_CH0_TCF_TRG   0U   /*!< UART GPDMA1 channel0 Internal Trigger  */
#define UART_GPDMA1_CH1_TCF_TRG   1U   /*!< UART GPDMA1 channel1 Internal Trigger  */
#define UART_GPDMA1_CH2_TCF_TRG   2U   /*!< UART GPDMA1 channel2 Internal Trigger  */
#define UART_GPDMA1_CH3_TCF_TRG   3U   /*!< UART GPDMA1 channel3 Internal Trigger  */
#define UART_EXTI_LINE6_TRG       4U   /*!< UART EXTI line 6 Internal Trigger      */
#define UART_EXTI_LINE9_TRG       5U   /*!< UART EXTI line 9 Internal Trigger      */
#define UART_LPTIM1_OUT_TRG       6U   /*!< UART LPTIM1 out Internal Trigger       */
#define UART_LPTIM2_OUT_TRG       7U   /*!< UART LPTIM2 out Internal Trigger       */
#define UART_COMP1_OUT_TRG        8U   /*!< UART COMP1 out Internal Trigger        */
#define UART_COMP2_OUT_TRG        9U   /*!< UART COMP2 out Internal Trigger        */
#define UART_RTC_ALRA_TRG         10U  /*!< UART RTC alarm Internal Trigger        */
#define UART_RTC_WUT_TRG          11U  /*!< UART RTC wakeup Internal Trigger       */
/**
  * @}
  */

/** @defgroup LPUARTEx_Autonomous_Trigger_selection LPUARTEx Autonomous trigger selection
  * @brief    LPUART Autonomous Trigger selection
  * @{
  */
#define LPUART_LPDMA1_CH0_TCF_TRG   0U   /*!< LPUART LPDMA1 channel0 Internal Trigger  */
#define LPUART_LPDMA1_CH1_TCF_TRG   1U   /*!< LPUART LPDMA1 channel1 Internal Trigger  */
#define LPUART_LPDMA1_CH2_TCF_TRG   2U   /*!< LPUART LPDMA1 channel2 Internal Trigger  */
#define LPUART_LPDMA1_CH3_TCF_TRG   3U   /*!< LPUART LPDMA1 channel3 Internal Trigger  */
#define LPUART_EXTI_LINE6_TRG       4U   /*!< LPUART EXTI line 6 Internal Trigger      */
#define LPUART_EXTI_LINE8_TRG       5U   /*!< LPUART EXTI line 8 Internal Trigger      */
#define LPUART_LPTIM1_OUT_TRG       6U   /*!< LPUART LPTIM1 out Internal Trigger       */
#define LPUART_LPTIM3_OUT_TRG       7U   /*!< LPUART LPTIM3 out Internal Trigger       */
#define LPUART_COMP1_OUT_TRG        8U   /*!< LPUART COMP1 out Internal Trigger        */
#define LPUART_COMP2_OUT_TRG        9U   /*!< LPUART COMP2 out Internal Trigger        */
#define LPUART_RTC_ALRA_TRG         10U  /*!< LPUART RTC alarm Internal Trigger        */
#define LPUART_RTC_WUT_TRG          11U  /*!< LPUART RTC wakeup Internal Trigger       */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup UARTEx_Exported_Functions
  * @{
  */

/** @addtogroup UARTEx_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t Polarity, uint32_t AssertionTime,
                                   uint32_t DeassertionTime);

/**
  * @}
  */

/** @addtogroup UARTEx_Exported_Functions_Group2
  * @{
  */

void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart);

void HAL_UARTEx_RxFifoFullCallback(UART_HandleTypeDef *huart);
void HAL_UARTEx_TxFifoEmptyCallback(UART_HandleTypeDef *huart);

/**
  * @}
  */

/** @addtogroup UARTEx_Exported_Functions_Group3
  * @{
  */

/* Peripheral Control functions  **********************************************/
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength);

HAL_StatusTypeDef HAL_UARTEx_EnableFifoMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableFifoMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_SetTxFifoThreshold(UART_HandleTypeDef *huart, uint32_t Threshold);
HAL_StatusTypeDef HAL_UARTEx_SetRxFifoThreshold(UART_HandleTypeDef *huart, uint32_t Threshold);

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/* Autonomous Mode Control functions  **********************************************/
HAL_StatusTypeDef HAL_UARTEx_SetConfigAutonomousMode(UART_HandleTypeDef *huart,
                                                     UART_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_UARTEx_GetConfigAutonomousMode(UART_HandleTypeDef *huart,
                                                     UART_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_UARTEx_ClearConfigAutonomousMode(UART_HandleTypeDef *huart);


/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup UARTEx_Private_Macros UARTEx Private Macros
  * @{
  */

/** @brief  Report the UART clock source.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __CLOCKSOURCE__ output variable.
  * @retval UART clocking source, written in __CLOCKSOURCE__.
  */
#if defined(USART6)
#define UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                  \
    if((__HANDLE__)->Instance == USART1)                \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART1;         \
    }                                                   \
    else if((__HANDLE__)->Instance == USART2)           \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART2;         \
    }                                                   \
    else if((__HANDLE__)->Instance == USART3)           \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART3;         \
    }                                                   \
    else if((__HANDLE__)->Instance == UART4)            \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_UART4;          \
    }                                                   \
    else if((__HANDLE__)->Instance == UART5)            \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_UART5;          \
    }                                                   \
    else if((__HANDLE__)->Instance == USART6)           \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART6;         \
    }                                                   \
    else if((__HANDLE__)->Instance == LPUART1)          \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_LPUART1;        \
    }                                                   \
    else                                                \
    {                                                   \
      (__CLOCKSOURCE__) = 0U;                           \
    }                                                   \
  } while(0U)
#else
#define UART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                  \
    if((__HANDLE__)->Instance == USART1)                \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART1;         \
    }                                                   \
    else if((__HANDLE__)->Instance == USART2)           \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART2;         \
    }                                                   \
    else if((__HANDLE__)->Instance == USART3)           \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_USART3;         \
    }                                                   \
    else if((__HANDLE__)->Instance == UART4)            \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_UART4;          \
    }                                                   \
    else if((__HANDLE__)->Instance == UART5)            \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_UART5;          \
    }                                                   \
    else if((__HANDLE__)->Instance == LPUART1)          \
    {                                                   \
      (__CLOCKSOURCE__) = RCC_PERIPHCLK_LPUART1;        \
    }                                                   \
    else                                                \
    {                                                   \
      (__CLOCKSOURCE__) = 0U;                           \
    }                                                   \
  } while(0U)
#endif /* USART6 */

/** @brief  Report the UART mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  * @note   If PCE = 1, the parity bit is not included in the data extracted
  *         by the reception API().
  *         This masking operation is not carried out in the case of
  *         DMA transfers.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None, the mask to apply to UART RDR register is stored in (__HANDLE__)->Mask field.
  */
#define UART_MASK_COMPUTATION(__HANDLE__)                             \
  do {                                                                \
    if ((__HANDLE__)->Init.WordLength == UART_WORDLENGTH_9B)          \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == UART_PARITY_NONE)              \
      {                                                               \
        (__HANDLE__)->Mask = 0x01FFU ;                                \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU ;                                \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == UART_WORDLENGTH_8B)     \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == UART_PARITY_NONE)              \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU ;                                \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU ;                                \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == UART_WORDLENGTH_7B)     \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == UART_PARITY_NONE)              \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU ;                                \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x003FU ;                                \
      }                                                               \
    }                                                                 \
    else                                                              \
    {                                                                 \
      (__HANDLE__)->Mask = 0x0000U;                                   \
    }                                                                 \
  } while(0U)

/**
  * @brief Ensure that UART frame length is valid.
  * @param __LENGTH__ UART frame length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#define IS_UART_WORD_LENGTH(__LENGTH__) (((__LENGTH__) == UART_WORDLENGTH_7B) || \
                                         ((__LENGTH__) == UART_WORDLENGTH_8B) || \
                                         ((__LENGTH__) == UART_WORDLENGTH_9B))

/**
  * @brief Ensure that UART wake-up address length is valid.
  * @param __ADDRESS__ UART wake-up address length.
  * @retval SET (__ADDRESS__ is valid) or RESET (__ADDRESS__ is invalid)
  */
#define IS_UART_ADDRESSLENGTH_DETECT(__ADDRESS__) (((__ADDRESS__) == UART_ADDRESS_DETECT_4B) || \
                                                   ((__ADDRESS__) == UART_ADDRESS_DETECT_7B))

/**
  * @brief Ensure that UART TXFIFO threshold level is valid.
  * @param __THRESHOLD__ UART TXFIFO threshold level.
  * @retval SET (__THRESHOLD__ is valid) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_UART_TXFIFO_THRESHOLD(__THRESHOLD__) (((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_1_8) || \
                                                 ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_1_4) || \
                                                 ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_1_2) || \
                                                 ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_3_4) || \
                                                 ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_7_8) || \
                                                 ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_8_8))

/**
  * @brief Ensure that UART RXFIFO threshold level is valid.
  * @param __THRESHOLD__ UART RXFIFO threshold level.
  * @retval SET (__THRESHOLD__ is valid) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_UART_RXFIFO_THRESHOLD(__THRESHOLD__) (((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_1_8) || \
                                                 ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_1_4) || \
                                                 ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_1_2) || \
                                                 ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_3_4) || \
                                                 ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_7_8) || \
                                                 ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_8_8))

/**
  * @brief Ensure that UART Trigger polarity state is valid.
  * @param __POLARITY__ UART Trigger polarity.
  * @retval SET (__POLARITY__ is valid) or RESET (__POLARITY__ is invalid)
  */
#define IS_UART_TRIGGER_POLARITY(__POLARITY__)  (((__POLARITY__) == UART_TRIG_POLARITY_RISING) ||\
                                                 ((__POLARITY__) == UART_TRIG_POLARITY_FALLING))

/**
  * @brief Ensure that UART IDLE Frame Transmit state is valid.
  * @param __IDLE__ UART IDLE Frame Transmit state.
  * @retval SET (__IDLE__ is valid) or RESET (__IDLE__ is invalid)
  */
#define IS_UART_IDLE_FRAME_TRANSMIT(__IDLE__)  (((__IDLE__) == UART_IDLE_FRAME_ENABLE) ||\
                                                ((__IDLE__) == UART_IDLE_FRAME_DISABLE))

/**
  * @brief Ensure that UART Trigger source selection is valid.
  * @param __SOURCE__ UART Trigger source selection.
  * @retval SET (__SOURCE__ is valid) or RESET (__SOURCE__ is invalid)
  */
#define IS_UART_TRIGGER_SELECTION(__SOURCE__)    ((__SOURCE__) <= 11U)

/**
  * @brief Ensure that LPUART Trigger source selection is valid.
  * @param __SOURCE__ LPUART Trigger source selection.
  * @retval SET (__SOURCE__ is valid) or RESET (__SOURCE__ is invalid)
  */
#define IS_LPUART_TRIGGER_SELECTION(__SOURCE__)  ((__SOURCE__) <= 11U)

/**
  * @brief Ensure that the number of transferred data is valid.
  * @param __SOURCE__ UART TX data size.
  * @retval SET (__SOURCE__ is valid) or RESET (__SOURCE__ is invalid)
  */
#define IS_UART_TX_DATA_SIZE(__SOURCE__)  ((__SOURCE__) <= 0xFFFFU)

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

#endif /* STM32U5xx_HAL_UART_EX_H */
