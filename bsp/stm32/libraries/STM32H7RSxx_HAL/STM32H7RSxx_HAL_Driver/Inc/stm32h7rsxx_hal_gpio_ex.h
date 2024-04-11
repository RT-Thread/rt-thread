/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_GPIO_EX_H
#define STM32H7RSxx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/

/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */

/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */

/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO                        ((uint8_t)0x00)  /*!< MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF0_JTAG                       ((uint8_t)0x00)  /*!< JTAG Alternate Function mapping                */
#define GPIO_AF0_SWD                        ((uint8_t)0x00)  /*!< SWD Alternate Function mapping                 */
#define GPIO_AF0_RTC                        ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping             */
#define GPIO_AF0_TRACE                      ((uint8_t)0x00)  /*!< TRACE Alternate Function mapping               */
#define GPIO_AF0_PWR                        ((uint8_t)0x00)  /*!< PWR Alternate Function mapping                 */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_ADF1                       ((uint8_t)0x01)  /*!< ADF1 Alternate Function mapping      */
#define GPIO_AF1_LPTIM1                     ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping    */
#define GPIO_AF1_TIM1                       ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping      */
#define GPIO_AF1_TIM2                       ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping      */
#define GPIO_AF1_TIM16                      ((uint8_t)0x01)  /*!< TIM16 Alternate Function mapping     */
#define GPIO_AF1_TIM17                      ((uint8_t)0x01)  /*!< TIM17 Alternate Function mapping     */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_GFXTIM                     ((uint8_t)0x02)  /*!< GFXTIM Alternate Function mapping    */
#define GPIO_AF2_SAI1                       ((uint8_t)0x02)  /*!< SAI1 Alternate Function mapping      */
#define GPIO_AF2_TIM2                       ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping      */
#define GPIO_AF2_TIM3                       ((uint8_t)0x02)  /*!< TIM3 Alternate Function mapping      */
#define GPIO_AF2_TIM4                       ((uint8_t)0x02)  /*!< TIM4 Alternate Function mapping      */
#define GPIO_AF2_TIM5                       ((uint8_t)0x02)  /*!< TIM5 Alternate Function mapping      */
#define GPIO_AF2_TIM12                      ((uint8_t)0x02)  /*!< TIM12 Alternate Function mapping     */
#define GPIO_AF2_TIM15                      ((uint8_t)0x02)  /*!< TIM15 Alternate Function mapping     */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_ADF1                       ((uint8_t)0x03)  /*!< ADF1 Alternate Function mapping      */
#define GPIO_AF3_LPTIM2                     ((uint8_t)0x03)  /*!< LPTIM2 Alternate Function mapping    */
#define GPIO_AF3_LPTIM3                     ((uint8_t)0x03)  /*!< LPTIM3 Alternate Function mapping    */
#define GPIO_AF3_LPTIM4                     ((uint8_t)0x03)  /*!< LPTIM4 Alternate Function mapping    */
#define GPIO_AF3_LPTIM5                     ((uint8_t)0x03)  /*!< LPTIM5 Alternate Function mapping    */
#define GPIO_AF3_LPUART1                    ((uint8_t)0x03)  /*!< LPUART1 Alternate Function mapping   */
#define GPIO_AF3_TIM9                       ((uint8_t)0x03)  /*!< TIM9 Alternate Function mapping      */
#define GPIO_AF3_USART3                     ((uint8_t)0x03)  /*!< USART3 Alternate Function mapping    */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_CEC                        ((uint8_t)0x04)  /*!< CEC Alternate Function mapping       */
#define GPIO_AF4_DCMIPP                     ((uint8_t)0x04)  /*!< DCMIPP Alternate Function mapping    */
#define GPIO_AF4_ETH                        ((uint8_t)0x04)  /*!< ETH Alternate Function mapping       */
#define GPIO_AF4_I2C1                       ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping      */
#define GPIO_AF4_I2C2                       ((uint8_t)0x04)  /*!< I2C2 Alternate Function mapping      */
#define GPIO_AF4_I2C3                       ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping      */
#define GPIO_AF4_I3C1                       ((uint8_t)0x04)  /*!< I3C1 Alternate Function mapping      */
#define GPIO_AF4_TIM15                      ((uint8_t)0x04)  /*!< TIM15 Alternate Function mapping     */
#define GPIO_AF4_USART1                     ((uint8_t)0x04)  /*!< USART1 Alternate Function mapping    */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_CEC                        ((uint8_t)0x05)  /*!< CEC Alternate Function mapping       */
#define GPIO_AF5_DCMIPP                     ((uint8_t)0x05)  /*!< DCMIPP Alternate Function mapping    */
#define GPIO_AF5_SPI1                       ((uint8_t)0x05)  /*!< SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF5_SPI2                       ((uint8_t)0x05)  /*!< SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3                       ((uint8_t)0x05)  /*!< SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_SPI4                       ((uint8_t)0x05)  /*!< SPI4 Alternate Function mapping      */
#define GPIO_AF5_SPI5                       ((uint8_t)0x05)  /*!< SPI5 Alternate Function mapping      */
#define GPIO_AF5_SPI6                       ((uint8_t)0x05)  /*!< SPI6/I2S6 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_PSSI                       ((uint8_t)0x06)  /*!< PSSI Alternate Function mapping      */
#define GPIO_AF6_SAI1                       ((uint8_t)0x06)  /*!< SAI1 Alternate Function mapping      */
#define GPIO_AF6_SDMMC1                     ((uint8_t)0x06)  /*!< SDMMC1 Alternate Function mapping    */
#define GPIO_AF6_SPI3                       ((uint8_t)0x06)  /*!< SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_SPI4                       ((uint8_t)0x06)  /*!< SPI4 Alternate Function mapping      */
#define GPIO_AF6_UART4                      ((uint8_t)0x06)  /*!< UART4 Alternate Function mapping     */
#define GPIO_AF6_UCPD                       ((uint8_t)0x06)  /*!< UCPD Alternate Function mapping      */

/**
  * @brief  AF 7 selection
  */
#define GPIO_AF7_FMC                        ((uint8_t)0x07)  /*!< FMC Alternate Function mapping       */
#define GPIO_AF7_SDMMC1                     ((uint8_t)0x07)  /*!< SDMMC1 Alternate Function mapping    */
#define GPIO_AF7_SPI2                       ((uint8_t)0x07)  /*!< SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF7_SPI3                       ((uint8_t)0x07)  /*!< SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF7_SPI6                       ((uint8_t)0x07)  /*!< SPI6/I2S6 Alternate Function mapping */
#define GPIO_AF7_USART1                     ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping    */
#define GPIO_AF7_USART2                     ((uint8_t)0x07)  /*!< USART2 Alternate Function mapping    */
#define GPIO_AF7_USART3                     ((uint8_t)0x07)  /*!< USART3 Alternate Function mapping    */
#define GPIO_AF7_UART7                      ((uint8_t)0x07)  /*!< UART7 Alternate Function mapping     */

/**
  * @brief  AF 8 selection
  */
#define GPIO_AF8_GFXTIM                     ((uint8_t)0x08)  /*!< GFXTIM Alternate Function mapping    */
#define GPIO_AF8_LPUART1                    ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping   */
#define GPIO_AF8_PSSI                       ((uint8_t)0x08)  /*!< PSSI Alternate Function mapping      */
#define GPIO_AF8_SAI2                       ((uint8_t)0x08)  /*!< SAI2 Alternate Function mapping      */
#define GPIO_AF8_SDMMC1                     ((uint8_t)0x08)  /*!< SDMMC1 Alternate Function mapping    */
#define GPIO_AF8_SPDIFRX                    ((uint8_t)0x08)  /*!< SPDIFRX Alternate Function mapping   */
#define GPIO_AF8_SPI6                       ((uint8_t)0x08)  /*!< SPI6/I2S6 Alternate Function mapping */
#define GPIO_AF8_UART4                      ((uint8_t)0x08)  /*!< UART4 Alternate Function mapping     */
#define GPIO_AF8_UART5                      ((uint8_t)0x08)  /*!< UART5 Alternate Function mapping     */
#define GPIO_AF8_UART8                      ((uint8_t)0x08)  /*!< UART8 Alternate Function mapping     */

/**
  * @brief  AF 9 selection
  */
#define GPIO_AF9_FDCAN1                     ((uint8_t)0x09)  /*!< FDCAN1 Alternate Function mapping                */
#define GPIO_AF9_FDCAN2                     ((uint8_t)0x09)  /*!< FDCAN2 Alternate Function mapping                */
#define GPIO_AF9_FMC                        ((uint8_t)0x09)  /*!< FMC Alternate Function mapping                   */
#define GPIO_AF9_XSPIM_P1                   ((uint8_t)0x09)  /*!< XSPIM Manager Port 1 Alternate Function mapping  */
#define GPIO_AF9_XSPIM_P2                   ((uint8_t)0x09)  /*!< XSPIM Manager Port 2 Alternate Function mapping  */
#define GPIO_AF9_PSSI                       ((uint8_t)0x09)  /*!< PSSI Alternate Function mapping                  */
#define GPIO_AF9_SDMMC2                     ((uint8_t)0x09)  /*!< SDMMC2 Alternate Function mapping                */
#define GPIO_AF9_SPDIFRX                    ((uint8_t)0x09)  /*!< SPDIFRX Alternate Function mapping               */
#define GPIO_AF9_SPI5                       ((uint8_t)0x09)  /*!< SPI5 Alternate Function mapping                  */
#define GPIO_AF9_TIM13                      ((uint8_t)0x09)  /*!< TIM13 Alternate Function mapping                 */
#define GPIO_AF9_TIM14                      ((uint8_t)0x09)  /*!< TIM14 Alternate Function mapping                 */

/**
  * @brief  AF 10 selection
  */
#define GPIO_AF10_CRS                       ((uint8_t)0x0A)  /*!< CRS Alternate Function mapping       */
#define GPIO_AF10_FMC                       ((uint8_t)0x0A)  /*!< FMC Alternate Function mapping       */
#define GPIO_AF10_LTDC                      ((uint8_t)0x0A)  /*!< LTDC Alternate Function mapping      */
#define GPIO_AF10_OTG_FS                    ((uint8_t)0x0A)  /*!< OTG FS Alternate Function mapping    */
#define GPIO_AF10_OTG_HS                    ((uint8_t)0x0A)  /*!< OTG HS Alternate Function mapping    */
#define GPIO_AF10_SAI2                      ((uint8_t)0x0A)  /*!< SAI2 Alternate Function mapping      */
#define GPIO_AF10_SDMMC2                    ((uint8_t)0x0A)  /*!< SDMMC2 Alternate Function mapping    */
#define GPIO_AF10_SPI1                      ((uint8_t)0x0A)  /*!< SPI1/I2S1 Alternate Function mapping */

/**
  * @brief  AF 11 selection
  */
#define GPIO_AF11_ETH                       ((uint8_t)0x0B)  /*!< ETH Alternate Function mapping       */
#define GPIO_AF11_LTDC                      ((uint8_t)0x0B)  /*!< LTDC Alternate Function mapping      */
#define GPIO_AF11_MDIOS                     ((uint8_t)0x0B)  /*!< MDIOS Alternate Function mapping     */
#define GPIO_AF11_SDMMC1                    ((uint8_t)0x0B)  /*!< SDMMC1 Alternate Function mapping    */
#define GPIO_AF11_SDMMC2                    ((uint8_t)0x0B)  /*!< SDMMC2 Alternate Function mapping    */
#define GPIO_AF11_UART7                     ((uint8_t)0x0B)  /*!< UART7 Alternate Function mapping     */

/**
  * @brief  AF 12 selection
  */
#define GPIO_AF12_FMC                       ((uint8_t)0x0C)  /*!< FMC Alternate Function mapping       */
#define GPIO_AF12_GFXTIM                    ((uint8_t)0x0C)  /*!< GFXTIM Alternate Function mapping    */
#define GPIO_AF12_LTDC                      ((uint8_t)0x0C)  /*!< TIM1 Alternate Function mapping      */
#define GPIO_AF12_SDMMC1                    ((uint8_t)0x0C)  /*!< SDMMC1 Alternate Function mapping    */

/**
  * @brief  AF 13 selection
  */
#define GPIO_AF13_DCMIPP                    ((uint8_t)0x0D)  /*!< DCMIPP Alternate Function mapping    */
#define GPIO_AF13_GFXTIM                    ((uint8_t)0x0D)  /*!< GFXTIM Alternate Function mapping    */
#define GPIO_AF13_LTDC                      ((uint8_t)0x0D)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief  AF 14 selection
  */
#define GPIO_AF14_FMC                       ((uint8_t)0x0E)  /*!< FMC Alternate Function mapping       */
#define GPIO_AF14_LTDC                      ((uint8_t)0x0E)  /*!< LTDC Alternate Function mapping      */
#define GPIO_AF14_MDIOS                     ((uint8_t)0x0E)  /*!< MDIOS Alternate Function mapping     */
#define GPIO_AF14_PSSI                      ((uint8_t)0x0E)  /*!< PSSI Alternate Function mapping      */
#define GPIO_AF14_TIM1                      ((uint8_t)0x0E)  /*!< TIM1 Alternate Function mapping      */
#define GPIO_AF14_UART5                     ((uint8_t)0x0E)  /*!< UART5 Alternate Function mapping     */

/**
  * @brief  AF 15 selection
  */
#define GPIO_AF15_EVENTOUT                  ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping  */

#define IS_GPIO_AF(AF)                      ((AF) <= (uint8_t)0x0F)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Macros GPIOEx Exported Macros
  * @{
  */

/** @defgroup GPIOEx_Get_Port_Index GPIOEx Get Port Index
  * @{
  */
#define GPIO_GET_INDEX(__GPIOx__)           (((uint32_t )(__GPIOx__) & (~GPIOA_BASE)) >> 10)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_GPIO_EX_H */

