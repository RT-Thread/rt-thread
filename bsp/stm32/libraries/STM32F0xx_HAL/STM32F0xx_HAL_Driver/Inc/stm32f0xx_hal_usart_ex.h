/**
  ******************************************************************************
  * @file    stm32f0xx_hal_usart_ex.h
  * @author  MCD Application Team
  * @brief   Header file of USART HAL Extended module.
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
#ifndef STM32F0xx_HAL_USART_EX_H
#define STM32F0xx_HAL_USART_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup USARTEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup USARTEx_Exported_Constants USARTEx Exported Constants
  * @{
  */

/** @defgroup USARTEx_Word_Length USARTEx Word Length
  * @{
  */
#if  defined(USART_CR1_M0)&& defined(USART_CR1_M1)
#define USART_WORDLENGTH_7B                  (USART_CR1_M1)   /*!< 7-bit long USART frame */
#define USART_WORDLENGTH_8B                  (0x00000000U)              /*!< 8-bit long USART frame */
#define USART_WORDLENGTH_9B                  (USART_CR1_M0)   /*!< 9-bit long USART frame */
#elif  defined(USART_CR1_M)
#define USART_WORDLENGTH_8B                  (0x00000000U)              /*!< 8-bit long USART frame */
#define USART_WORDLENGTH_9B                  (USART_CR1_M)    /*!< 9-bit long USART frame */
#endif
/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup USARTEx_Private_Macros USARTEx Private Macros
  * @{
  */

/** @brief  Report the USART clock source.
  * @param  __HANDLE__ specifies the USART Handle.
  * @param  __CLOCKSOURCE__ output variable.
  * @retval the USART clocking source, written in __CLOCKSOURCE__.
  */
/** @brief  Report the UART clock source.
  * @param  __HANDLE__ specifies the UART Handle.
  * @param  __CLOCKSOURCE__ output variable.
  * @retval UART clocking source, written in __CLOCKSOURCE__.
  */

#if defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx)
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                         \
     switch(__HAL_RCC_GET_USART1_SOURCE())                     \
     {                                                         \
      case RCC_USART1CLKSOURCE_PCLK1:                          \
        (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;           \
        break;                                                 \
      case RCC_USART1CLKSOURCE_HSI:                            \
        (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;             \
        break;                                                 \
      case RCC_USART1CLKSOURCE_SYSCLK:                         \
        (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;          \
        break;                                                 \
      case RCC_USART1CLKSOURCE_LSE:                            \
        (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;             \
        break;                                                 \
      default:                                                 \
        (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;       \
        break;                                                 \
     }                                                         \
  } while(0)
#elif defined (STM32F030x8) || defined (STM32F070x6) ||  defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F051x8) || defined (STM32F058xx)
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
       switch(__HAL_RCC_GET_USART1_SOURCE())                   \
       {                                                       \
        case RCC_USART1CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;         \
    }                                                          \
  } while(0)
#elif defined (STM32F070xB)
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
       switch(__HAL_RCC_GET_USART1_SOURCE())                   \
       {                                                       \
        case RCC_USART1CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART4)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;         \
    }                                                          \
  } while(0)
#elif defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
       switch(__HAL_RCC_GET_USART1_SOURCE())                   \
       {                                                       \
        case RCC_USART1CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
       switch(__HAL_RCC_GET_USART2_SOURCE())                   \
       {                                                       \
        case RCC_USART2CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART2CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART2CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART2CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART4)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;         \
    }                                                          \
  } while(0)
#elif defined(STM32F091xC) || defined (STM32F098xx)
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
       switch(__HAL_RCC_GET_USART1_SOURCE())                   \
       {                                                       \
        case RCC_USART1CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
       switch(__HAL_RCC_GET_USART2_SOURCE())                   \
       {                                                       \
        case RCC_USART2CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART2CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART2CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART2CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
       switch(__HAL_RCC_GET_USART3_SOURCE())                   \
       {                                                       \
        case RCC_USART3CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART3CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART3CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART3CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART4)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART5)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART6)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART7)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART8)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;         \
    }                                                          \
  } while(0)
#elif defined(STM32F030xC)
#define USART_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__) \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
       switch(__HAL_RCC_GET_USART1_SOURCE())                   \
       {                                                       \
        case RCC_USART1CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_HSI;           \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_SYSCLK;        \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_LSE;           \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;     \
          break;                                               \
       }                                                       \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART4)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART5)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else if((__HANDLE__)->Instance == USART6)                  \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_PCLK1;             \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = USART_CLOCKSOURCE_UNDEFINED;         \
    }                                                          \
  } while(0)
#endif /* defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx) */
/** @brief  Compute the USART mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  * @note   If PCE = 1, the parity bit is not included in the data extracted
  *         by the reception API().
  *         This masking operation is not carried out in the case of
  *         DMA transfers.
  * @param  __HANDLE__ specifies the USART Handle.
  * @retval None, the mask to apply to USART RDR register is stored in (__HANDLE__)->Mask field.
  */
#if  defined(USART_CR1_M0)&& defined(USART_CR1_M1)
#define USART_MASK_COMPUTATION(__HANDLE__)                            \
  do {                                                                \
    if ((__HANDLE__)->Init.WordLength == USART_WORDLENGTH_9B)         \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == USART_PARITY_NONE)             \
      {                                                               \
        (__HANDLE__)->Mask = 0x01FFU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU;                                 \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == USART_WORDLENGTH_8B)    \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == USART_PARITY_NONE)             \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU;                                 \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == USART_WORDLENGTH_7B)    \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == USART_PARITY_NONE)             \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x003FU;                                 \
      }                                                               \
    }                                                                 \
    else                                                              \
    {                                                                 \
      (__HANDLE__)->Mask = 0x0000U;                                   \
    }                                                                 \
  } while(0U)
#elif  defined(USART_CR1_M)
#define USART_MASK_COMPUTATION(__HANDLE__)                            \
  do {                                                                \
    if ((__HANDLE__)->Init.WordLength == USART_WORDLENGTH_9B)         \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == USART_PARITY_NONE)             \
      {                                                               \
        (__HANDLE__)->Mask = 0x01FFU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU;                                 \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == USART_WORDLENGTH_8B)    \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == USART_PARITY_NONE)             \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU;                                 \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU;                                 \
      }                                                               \
    }                                                                 \
    else                                                              \
    {                                                                 \
      (__HANDLE__)->Mask = 0x0000U;                                   \
    }                                                                 \
  } while(0U)
#endif

/**
  * @brief Ensure that USART frame length is valid.
  * @param __LENGTH__ USART frame length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#if  defined(USART_CR1_M0)&& defined(USART_CR1_M1)
#define IS_USART_WORD_LENGTH(__LENGTH__) (((__LENGTH__) == USART_WORDLENGTH_7B) || \
                                          ((__LENGTH__) == USART_WORDLENGTH_8B) || \
                                          ((__LENGTH__) == USART_WORDLENGTH_9B))
#elif  defined(USART_CR1_M)
#define IS_USART_WORD_LENGTH(__LENGTH__) (((__LENGTH__) == USART_WORDLENGTH_8B) || \
                                          ((__LENGTH__) == USART_WORDLENGTH_9B))
#endif


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup USARTEx_Exported_Functions
  * @{
  */

/** @addtogroup USARTEx_Exported_Functions_Group1
  * @{
  */

/* IO operation functions *****************************************************/

/**
  * @}
  */

/** @addtogroup USARTEx_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions ***********************************************/

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

#endif /* STM32F0xx_HAL_USART_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
