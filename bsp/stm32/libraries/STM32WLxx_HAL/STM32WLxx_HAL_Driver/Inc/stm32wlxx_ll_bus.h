/**
  ******************************************************************************
  * @file    stm32wlxx_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.
  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.w<
      (+) This delay depends on the peripheral mapping.
        (++) AHB & APB peripherals, 1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32WLxx_LL_BUS_H
#define __STM32WLxx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx.h"

/** @addtogroup STM32WLxx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants BUS Exported Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB1_GRP1_PERIPH  AHB1 GRP1 PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_AHB1_GRP1_PERIPH_DMA1           RCC_AHB1ENR_DMA1EN
#define LL_AHB1_GRP1_PERIPH_DMA2           RCC_AHB1ENR_DMA2EN
#define LL_AHB1_GRP1_PERIPH_DMAMUX1        RCC_AHB1ENR_DMAMUX1EN
#define LL_AHB1_GRP1_PERIPH_CRC            RCC_AHB1ENR_CRCEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_AHB2_GRP1_PERIPH_GPIOA          RCC_AHB2ENR_GPIOAEN
#define LL_AHB2_GRP1_PERIPH_GPIOB          RCC_AHB2ENR_GPIOBEN
#define LL_AHB2_GRP1_PERIPH_GPIOC          RCC_AHB2ENR_GPIOCEN
#define LL_AHB2_GRP1_PERIPH_GPIOH          RCC_AHB2ENR_GPIOHEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB3_GRP1_PERIPH  AHB3 GRP1 PERIPH
  * @{
  */
#define LL_AHB3_GRP1_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_AHB3_GRP1_PERIPH_PKA            RCC_AHB3ENR_PKAEN
#define LL_AHB3_GRP1_PERIPH_AES            RCC_AHB3ENR_AESEN
#define LL_AHB3_GRP1_PERIPH_RNG            RCC_AHB3ENR_RNGEN
#define LL_AHB3_GRP1_PERIPH_HSEM           RCC_AHB3ENR_HSEMEN
#if defined(DUAL_CORE)
#define LL_AHB3_GRP1_PERIPH_IPCC           RCC_AHB3ENR_IPCCEN
#endif /* DUAL_CORE */
#define LL_AHB3_GRP1_PERIPH_SRAM1          RCC_AHB3SMENR_SRAM1SMEN
#define LL_AHB3_GRP1_PERIPH_SRAM2          RCC_AHB3SMENR_SRAM2SMEN
#define LL_AHB3_GRP1_PERIPH_FLASH          RCC_AHB3ENR_FLASHEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_APB1_GRP1_PERIPH_TIM2           RCC_APB1ENR1_TIM2EN
#define LL_APB1_GRP1_PERIPH_RTCAPB         RCC_APB1ENR1_RTCAPBEN
#define LL_APB1_GRP1_PERIPH_WWDG           RCC_APB1ENR1_WWDGEN
#define LL_APB1_GRP1_PERIPH_SPI2           RCC_APB1ENR1_SPI2EN
#define LL_APB1_GRP1_PERIPH_USART2         RCC_APB1ENR1_USART2EN
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_APB1ENR1_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_APB1ENR1_I2C2EN
#define LL_APB1_GRP1_PERIPH_I2C3           RCC_APB1ENR1_I2C3EN
#define LL_APB1_GRP1_PERIPH_DAC            RCC_APB1ENR1_DACEN
#define LL_APB1_GRP1_PERIPH_LPTIM1         RCC_APB1ENR1_LPTIM1EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_APB1_GRP2_PERIPH_LPUART1        RCC_APB1ENR2_LPUART1EN
#define LL_APB1_GRP2_PERIPH_LPTIM2         RCC_APB1ENR2_LPTIM2EN
#define LL_APB1_GRP2_PERIPH_LPTIM3         RCC_APB1ENR2_LPTIM3EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_APB2_GRP1_PERIPH_ADC            RCC_APB2ENR_ADCEN
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#define LL_APB2_GRP1_PERIPH_USART1         RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_GRP1_PERIPH  APB3 GRP1 PERIPH
  * @{
  */
#define LL_APB3_GRP1_PERIPH_ALL            (0xFFFFFFFFU)
#define LL_APB3_GRP1_PERIPH_SUBGHZSPI      RCC_APB3ENR_SUBGHZSPIEN
/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup BUS_LL_EC_C2_AHB1_GRP1_PERIPH  C2 AHB1 GRP1 PERIPH
  * @{
  */
#define LL_C2_AHB1_GRP1_PERIPH_DMA1         RCC_C2AHB1ENR_DMA1EN
#define LL_C2_AHB1_GRP1_PERIPH_DMA2         RCC_C2AHB1ENR_DMA2EN
#define LL_C2_AHB1_GRP1_PERIPH_DMAMUX1      RCC_C2AHB1ENR_DMAMUX1EN
#define LL_C2_AHB1_GRP1_PERIPH_CRC          RCC_C2AHB1ENR_CRCEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_C2_AHB2_GRP1_PERIPH  C2 AHB2 GRP1 PERIPH
  * @{
  */
#define LL_C2_AHB2_GRP1_PERIPH_GPIOA        RCC_C2AHB2ENR_GPIOAEN
#define LL_C2_AHB2_GRP1_PERIPH_GPIOB        RCC_C2AHB2ENR_GPIOBEN
#define LL_C2_AHB2_GRP1_PERIPH_GPIOC        RCC_C2AHB2ENR_GPIOCEN
#define LL_C2_AHB2_GRP1_PERIPH_GPIOH        RCC_C2AHB2ENR_GPIOHEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_C2_AHB3_GRP1_PERIPH  C2 AHB3 GRP1 PERIPH
  * @{
  */
#define LL_C2_AHB3_GRP1_PERIPH_PKA          RCC_C2AHB3ENR_PKAEN
#define LL_C2_AHB3_GRP1_PERIPH_AES          RCC_C2AHB3ENR_AESEN
#define LL_C2_AHB3_GRP1_PERIPH_RNG          RCC_C2AHB3ENR_RNGEN
#define LL_C2_AHB3_GRP1_PERIPH_HSEM         RCC_C2AHB3ENR_HSEMEN
#define LL_C2_AHB3_GRP1_PERIPH_IPCC         RCC_C2AHB3ENR_IPCCEN
#define LL_C2_AHB3_GRP1_PERIPH_FLASH        RCC_C2AHB3ENR_FLASHEN
#define LL_C2_AHB3_GRP1_PERIPH_SRAM1        RCC_C2AHB3SMENR_SRAM1SMEN
#define LL_C2_AHB3_GRP1_PERIPH_SRAM2        RCC_C2AHB3SMENR_SRAM2SMEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_C2_APB1_GRP1_PERIPH  C2 APB1 GRP1 PERIPH
  * @{
  */
#define LL_C2_APB1_GRP1_PERIPH_TIM2         RCC_C2APB1ENR1_TIM2EN
#define LL_C2_APB1_GRP1_PERIPH_RTCAPB       RCC_C2APB1ENR1_RTCAPBEN
#define LL_C2_APB1_GRP1_PERIPH_SPI2         RCC_C2APB1ENR1_SPI2EN
#define LL_C2_APB1_GRP1_PERIPH_USART2       RCC_C2APB1ENR1_USART2EN
#define LL_C2_APB1_GRP1_PERIPH_I2C1         RCC_C2APB1ENR1_I2C1EN
#define LL_C2_APB1_GRP1_PERIPH_I2C2         RCC_C2APB1ENR1_I2C2EN
#define LL_C2_APB1_GRP1_PERIPH_I2C3         RCC_C2APB1ENR1_I2C3EN
#define LL_C2_APB1_GRP1_PERIPH_DAC          RCC_C2APB1ENR1_DACEN
#define LL_C2_APB1_GRP1_PERIPH_LPTIM1       RCC_C2APB1ENR1_LPTIM1EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_C2_APB1_GRP2_PERIPH  C2 APB1 GRP2 PERIPH
  * @{
  */
#define LL_C2_APB1_GRP2_PERIPH_LPUART1      RCC_C2APB1ENR2_LPUART1EN
#define LL_C2_APB1_GRP2_PERIPH_LPTIM2       RCC_C2APB1ENR2_LPTIM2EN
#define LL_C2_APB1_GRP2_PERIPH_LPTIM3       RCC_C2APB1ENR2_LPTIM3EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_C2_APB2_GRP1_PERIPH  C2 APB2 GRP1 PERIPH
  * @{
  */
#define LL_C2_APB2_GRP1_PERIPH_ADC          RCC_C2APB2ENR_ADCEN
#define LL_C2_APB2_GRP1_PERIPH_TIM1         RCC_C2APB2ENR_TIM1EN
#define LL_C2_APB2_GRP1_PERIPH_SPI1         RCC_C2APB2ENR_SPI1EN
#define LL_C2_APB2_GRP1_PERIPH_USART1       RCC_C2APB2ENR_USART1EN
#define LL_C2_APB2_GRP1_PERIPH_TIM16        RCC_C2APB2ENR_TIM16EN
#define LL_C2_APB2_GRP1_PERIPH_TIM17        RCC_C2APB2ENR_TIM17EN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_C2_APB3_GRP1_PERIPH  C2 APB3 GRP1 PERIPH
  * @{
  */
#define LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI    RCC_C2APB3ENR_SUBGHZSPIEN
/**
  * @}
  */
#endif /* DUAL_CORE */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB1 AHB1
  * @{
  */

/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll AHB1ENR      DMA1EN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      DMA2EN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      DMAMUX1EN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      CRCEN         LL_AHB1_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled or not
  * @rmtoll AHB1ENR      DMA1EN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      DMA2EN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      DMAMUX1EN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      CRCEN         LL_AHB1_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHB1ENR      DMA1EN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      DMA2EN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      DMAMUX1EN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      CRCEN         LL_AHB1_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHB1RSTR     DMA1RST       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     DMA2RST       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     DMAMUX1RST    LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     CRCRST        LL_AHB1_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHB1RSTR     DMA1RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     DMA2RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     DMAMUX1RST     LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     CRCRST        LL_AHB1_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Enable AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB1SMENR    DMA1SMEN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SMENR    DMA2SMEN      LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SMENR    DMAMUX1SMEN   LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1SMENR    CRCSMEN       LL_AHB1_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll AHB1SMENR    DMA1SMEN      LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SMENR    DMA2SMEN      LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SMENR    DMAMUX1SMEN   LL_AHB1_GRP1_IsEnabledClockSleep\n
  *         AHB1SMENR    CRCSMEN       LL_AHB1_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB1SMENR    DMA1SMEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SMENR    DMA2SMEN      LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SMENR    DMAMUX1SMEN   LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1SMENR    CRCSMEN       LL_AHB1_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2 AHB2
  * @{
  */

/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      GPIOAEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      GPIOBEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      GPIOCEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      GPIOHEN       LL_AHB2_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled or not
  * @rmtoll AHB2ENR      GPIOAEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      GPIOBEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      GPIOCEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      GPIOHEN       LL_AHB2_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      GPIOAEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      GPIOBEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      GPIOCEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      GPIOHEN       LL_AHB2_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTR     GPIOARST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     GPIOBRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     GPIOCRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     GPIOHRST      LL_AHB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTR     GPIOARST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     GPIOBRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     GPIOCRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     GPIOHRST      LL_AHB2_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Enable AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB2SMENR    GPIOASMEN     LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SMENR    GPIOBSMEN     LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SMENR    GPIOCSMEN     LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2SMENR    GPIOHSMEN     LL_AHB2_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll AHB2SMENR    GPIOASMEN     LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SMENR    GPIOBSMEN     LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SMENR    GPIOCSMEN     LL_AHB2_GRP1_IsEnabledClockSleep\n
  *         AHB2SMENR    GPIOHSMEN     LL_AHB2_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB2SMENR    GPIOASMEN     LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SMENR    GPIOBSMEN     LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SMENR    GPIOCSMEN     LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2SMENR    GPIOHSMEN     LL_AHB2_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB3 AHB3
  * @{
  */

#if defined(DUAL_CORE) /* Switch added for Documentation generation purpose to exclude IPCC in else case*/
/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      PKAEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      AESEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      RNGEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      HSEMEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      IPCCEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */

#else
/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      PKAEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      AESEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      RNGEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      HSEMEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
#endif /* DUAL_CORE */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3ENR, Periphs);
  (void)tmpreg;
}

#if defined(DUAL_CORE) /* Switch added for Documentation generation purpose to exclude IPCC in else case*/
/**
  * @brief  Check if AHB3 peripheral clock is enabled or not
  * @rmtoll AHB3ENR      PKAEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      AESEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      RNGEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      HSEMEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      IPCCEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval uint32_t
  */
#else
/**
  * @brief  Check if AHB3 peripheral clock is enabled or not
  * @rmtoll AHB3ENR      PKAEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      AESEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      RNGEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      HSEMEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval uint32_t
  */

#endif /* DUAL_CORE */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB3ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

#if defined(DUAL_CORE) /* Switch added for Documentation generation purpose to exclude IPCC in else case*/
/**
  * @brief  Disable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      PKAEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      AESEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      RNGEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      HSEMEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      IPCCEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */

#else
/**
  * @brief  Disable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      PKAEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      AESEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      RNGEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      HSEMEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      FLASHEN       LL_AHB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
#endif /* DUAL_CORE */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3ENR, Periphs);
}

#if defined(DUAL_CORE) /* Switch added for Documentation generation purpose to exclude IPCC in else case*/
/**
  * @brief  Force AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     PKARST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     AESRST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     RNGRST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     HSEMRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     IPCCRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     FLASHRST      LL_AHB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
#else
/**
  * @brief  Force AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     PKARST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     AESRST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     RNGRST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     HSEMRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     FLASHRST      LL_AHB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */

#endif /* DUAL_CORE */
__STATIC_INLINE void LL_AHB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3RSTR, Periphs);
}

#if defined(DUAL_CORE) /* Switch added for Documentation generation purpose to exclude IPCC in else case*/
/**
  * @brief  Release AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     PKARST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     AESRST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     RNGRST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     HSEMRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     IPCCRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     FLASHRST      LL_AHB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
#else
/**
  * @brief  Release AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     PKARST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     AESRST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     RNGRST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     HSEMRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     FLASHRST      LL_AHB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */

#endif /* DUAL_CORE */
__STATIC_INLINE void LL_AHB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Enable AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB3SMENR    PKASMEN       LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3SMENR    AESSMEN       LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3SMENR    RNGSMEN       LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB1SMENR    SRAM1SMEN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB3SMENR    SRAM2SMEN     LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3SMENR    FLASHSMEN     LL_AHB3_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB3 peripheral clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll AHB3SMENR    PKASMEN       LL_AHB3_GRP1_IsEnabledClockSleep\n
  *         AHB3SMENR    AESSMEN       LL_AHB3_GRP1_IsEnabledClockSleep\n
  *         AHB3SMENR    RNGSMEN       LL_AHB3_GRP1_IsEnabledClockSleep\n
  *         AHB1SMENR    SRAM1SMEN     LL_AHB3_GRP1_IsEnabledClockSleep\n
  *         AHB3SMENR    SRAM2SMEN     LL_AHB3_GRP1_IsEnabledClockSleep\n
  *         AHB3SMENR    FLASHSMEN     LL_AHB3_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB3SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB3SMENR    PKASMEN       LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3SMENR    AESSMEN       LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3SMENR    RNGSMEN       LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3SMENR    SRAM1SMEN     LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3SMENR    SRAM2SMEN     LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3SMENR    FLASHSMEN     LL_AHB3_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     RTCAPBEN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     DACEN         LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     LPTIM1EN      LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR2     LPUART1EN     LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_EnableClock
  *         APB1ENR2     LPTIM3EN      LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3

  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     RTCAPBEN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     DACEN         LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     LPTIM1EN      LL_APB1_GRP1_IsEnabledClock

  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR2     LPUART1EN     LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_IsEnabledClock
  *         APB1ENR2     LPTIM3EN      LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR2, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     RTCAPBEN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     DACEN         LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     LPTIM1EN      LL_APB1_GRP1_DisableClock

  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR2     LPUART1EN     LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_DisableClock
  *         APB1ENR2     LPTIM3EN      LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR2, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR1    TIM2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    SPI2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    USART2RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I2C1RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I2C2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I2C3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    DACRST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    LPTIM1RST     LL_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR2    LPUART1RST    LL_APB1_GRP2_ForceReset\n
  *         APB1RSTR2    LPTIM2RST     LL_APB1_GRP2_ForceReset
  *         APB1RSTR2    LPTIM3RST     LL_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR1    TIM2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    SPI2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    DACRST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I2C1RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I2C2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I2C3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    DACRST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    LPTIM1RST     LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR2    LPUART1RST    LL_APB1_GRP2_ReleaseReset\n
  *         APB1RSTR2    LPTIM2RST     LL_APB1_GRP2_ReleaseReset
  *         APB1RSTR2    LPTIM3RST     LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1SMENR1   TIM2SMEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   RTCAPBSMEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   WWDGSMEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   SPI2SMEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   USART2SMEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   I2C1SMEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   I2C2SMEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   I2C3SMEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   DACSMEN       LL_APB1_GRP1_EnableClockSleep\n
  *         APB1SMENR1   LPTIM1SMEN    LL_APB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1SMENR2   LPUART1SMEN   LL_APB1_GRP2_EnableClockSleep\n
  *         APB1SMENR2   LPTIM2SMEN    LL_APB1_GRP2_EnableClockSleep
  *         APB1SMENR2   LPTIM3SMEN    LL_APB1_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll APB1SMENR1   TIM2SMEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   RTCAPBSMEN    LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   WWDGSMEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   SPI2SMEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   USART2SMEN    LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   I2C1SMEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   I2C2SMEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   I2C3SMEN      LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   DACSMEN       LL_APB1_GRP1_IsEnabledClockSleep\n
  *         APB1SMENR1   LPTIM1SMEN    LL_APB1_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Check if APB1 clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll APB1SMENR2   LPUART1SMEN   LL_APB1_GRP2_IsEnabledClockSleep\n
  *         APB1SMENR2   LPTIM2SMEN    LL_APB1_GRP2_IsEnabledClockSleep\n
  *         APB1SMENR2   LPTIM3SMEN    LL_APB1_GRP2_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR2, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1SMENR1   TIM2SMEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   RTCAPBSMEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   WWDGSMEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   SPI2SMEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   USART2SMEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   I2C1SMEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   I2C2SMEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   I2C3SMEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   DACSMEN       LL_APB1_GRP1_DisableClockSleep\n
  *         APB1SMENR1   LPTIM1SMEN    LL_APB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SMENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1SMENR2   LPUART1SMEN   LL_APB1_GRP2_DisableClockSleep\n
  *         APB1SMENR2   LPTIM2SMEN    LL_APB1_GRP2_DisableClockSleep
  *         APB1SMENR2   LPTIM3SMEN    LL_APB1_GRP2_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SMENR2, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */

/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll APB2ENR      ADCEN         LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clock is enabled or not
  * @rmtoll APB2ENR      ADCEN         LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      ADCEN         LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTR     ADCRST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     USART1RST     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM16RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM17RST      LL_APB2_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTR     ADCRST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     USART1RST     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM16RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM17RST      LL_APB2_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Enable APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB2SMENR    ADCSMEN       LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SMENR    TIM1SMEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SMENR    SPI1SMEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SMENR    USART1SMEN    LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SMENR    TIM16SMEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2SMENR    TIM17SMEN     LL_APB2_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll APB2SMENR    ADCSMEN       LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SMENR    TIM1SMEN      LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SMENR    SPI1SMEN      LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SMENR    USART1SMEN    LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SMENR    TIM16SMEN     LL_APB2_GRP1_IsEnabledClockSleep\n
  *         APB2SMENR    TIM17SMEN     LL_APB2_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB2SMENR    ADCSMEN       LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SMENR    TIM1SMEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SMENR    SPI1SMEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SMENR    USART1SMEN    LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SMENR    TIM16SMEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2SMENR    TIM17SMEN     LL_APB2_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3 APB3
  * @{
  */

/**
  * @brief  Enable APB3 peripherals clock.
  * @rmtoll APB3ENR    SUBGHZSPIEN     LL_APB3_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clock is enabled or not
  * @rmtoll APB3ENR    SUBGHZSPIEN     LL_APB3_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripherals clock.
  * @rmtoll APB3ENR    SUBGHZSPIEN     LL_APB3_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3ENR, Periphs);
}


/**
  * @brief  Force APB3 peripherals reset.
  * @rmtoll APB3RSTR     SUBGHZSPIRST  LL_APB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Release APB3 peripherals reset.
  * @rmtoll APB3RSTR     SUBGHZSPIRST  LL_APB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Enable APB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB3SMENR  SUBGHZSPISMEN   LL_APB3_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 clock is enabled by the clock gating during CPU1 CSleep mode
  * @rmtoll APB3SMENR  SUBGHZSPISMEN   LL_APB3_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB3SMENR  SUBGHZSPISMEN   LL_APB3_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3SMENR, Periphs);
}


/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup BUS_LL_EF_C2_AHB1 C2 AHB1
  * @{
  */
/**
  * @brief  Enable C2AHB1 peripherals clock.
  * @rmtoll C2AHB1ENR    DMA1EN        LL_C2_AHB1_GRP1_EnableClock\n
  *         C2AHB1ENR    DMA2EN        LL_C2_AHB1_GRP1_EnableClock\n
  *         C2AHB1ENR    DMAMUX1EN     LL_C2_AHB1_GRP1_EnableClock\n
  *         C2AHB1ENR    CRCEN         LL_C2_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2AHB1ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2AHB1ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2AHB1 peripheral clock is enabled or not
  * @rmtoll C2AHB1ENR    DMA1EN        LL_C2_AHB1_GRP1_IsEnabledClock\n
  *         C2AHB1ENR    DMA2EN        LL_C2_AHB1_GRP1_IsEnabledClock\n
  *         C2AHB1ENR    DMAMUX1EN     LL_C2_AHB1_GRP1_IsEnabledClock\n
  *         C2AHB1ENR    CRCEN         LL_C2_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_CRC
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2AHB1ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2AHB1 peripherals clock.
  * @rmtoll C2AHB1ENR    DMA1EN        LL_C2_AHB1_GRP1_DisableClock\n
  *         C2AHB1ENR    DMA2EN        LL_C2_AHB1_GRP1_DisableClock\n
  *         C2AHB1ENR    DMAMUX1EN     LL_C2_AHB1_GRP1_DisableClock\n
  *         C2AHB1ENR    CRCEN         LL_C2_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2AHB1ENR, Periphs);
}

/**
  * @brief  Enable C2AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2AHB1SMENR  DMA1SMEN      LL_C2_AHB1_GRP1_EnableClockSleep\n
  *         C2AHB1SMENR  DMA2SMEN      LL_C2_AHB1_GRP1_EnableClockSleep\n
  *         C2AHB1SMENR  DMAMUX1SMEN   LL_C2_AHB1_GRP1_EnableClockSleep\n
  *         C2AHB1SMENR  CRCSMEN       LL_C2_AHB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2AHB1SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2AHB1SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2AHB1 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2AHB1SMENR  DMA1SMEN      LL_C2_AHB1_GRP1_IsEnabledClockSleep\n
  *         C2AHB1SMENR  DMA2SMEN      LL_C2_AHB1_GRP1_IsEnabledClockSleep\n
  *         C2AHB1SMENR  DMAMUX1SMEN   LL_C2_AHB1_GRP1_IsEnabledClockSleep\n
  *         C2AHB1SMENR  CRCSMEN       LL_C2_AHB1_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_AHB1_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2AHB1SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2AHB1SMENR  DMA1SMEN      LL_C2_AHB1_GRP1_DisableClockSleep\n
  *         C2AHB1SMENR  DMA2SMEN      LL_C2_AHB1_GRP1_DisableClockSleep\n
  *         C2AHB1SMENR  DMAMUX1SMEN   LL_C2_AHB1_GRP1_DisableClockSleep\n
  *         C2AHB1SMENR  CRCSMEN       LL_C2_AHB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMA2
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_C2_AHB1_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2AHB1SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_C2_AHB2 C2 AHB2
  * @{
  */

/**
  * @brief  Enable C2AHB2 peripherals clock.
  * @rmtoll C2AHB2ENR    GPIOAEN       LL_C2_AHB2_GRP1_EnableClock\n
  *         C2AHB2ENR    GPIOBEN       LL_C2_AHB2_GRP1_EnableClock\n
  *         C2AHB2ENR    GPIOCEN       LL_C2_AHB2_GRP1_EnableClock\n
  *         C2AHB2ENR    GPIOHEN       LL_C2_AHB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2AHB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2AHB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2AHB2 peripheral clock is enabled or not
  * @rmtoll C2AHB2ENR    GPIOAEN       LL_C2_AHB2_GRP1_IsEnabledClock\n
  *         C2AHB2ENR    GPIOBEN       LL_C2_AHB2_GRP1_IsEnabledClock\n
  *         C2AHB2ENR    GPIOCEN       LL_C2_AHB2_GRP1_IsEnabledClock\n
  *         C2AHB2ENR    GPIOHEN       LL_C2_AHB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOH
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2AHB2ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2AHB2 peripherals clock.
  * @rmtoll C2AHB2ENR    GPIOAEN       LL_C2_AHB2_GRP1_DisableClock\n
  *         C2AHB2ENR    GPIOBEN       LL_C2_AHB2_GRP1_DisableClock\n
  *         C2AHB2ENR    GPIOCEN       LL_C2_AHB2_GRP1_DisableClock\n
  *         C2AHB2ENR    GPIOHEN       LL_C2_AHB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2AHB2ENR, Periphs);
}

/**
  * @brief  Enable C2AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2AHB2SMENR  GPIOASMEN     LL_C2_AHB2_GRP1_EnableClockSleep\n
  *         C2AHB2SMENR  GPIOBSMEN     LL_C2_AHB2_GRP1_EnableClockSleep\n
  *         C2AHB2SMENR  GPIOCSMEN     LL_C2_AHB2_GRP1_EnableClockSleep\n
  *         C2AHB2SMENR  GPIOHSMEN     LL_C2_AHB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2AHB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2AHB2SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2AHB2 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2AHB2SMENR  GPIOASMEN     LL_C2_AHB2_GRP1_IsEnabledClockSleep\n
  *         C2AHB2SMENR  GPIOBSMEN     LL_C2_AHB2_GRP1_IsEnabledClockSleep\n
  *         C2AHB2SMENR  GPIOCSMEN     LL_C2_AHB2_GRP1_IsEnabledClockSleep\n
  *         C2AHB2SMENR  GPIOHSMEN     LL_C2_AHB2_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_AHB2_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2AHB2SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2AHB2SMENR  GPIOASMEN     LL_C2_AHB2_GRP1_DisableClockSleep\n
  *         C2AHB2SMENR  GPIOBSMEN     LL_C2_AHB2_GRP1_DisableClockSleep\n
  *         C2AHB2SMENR  GPIOCSMEN     LL_C2_AHB2_GRP1_DisableClockSleep\n
  *         C2AHB2SMENR  GPIODSMEN     LL_C2_AHB2_GRP1_DisableClockSleep\n

  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_C2_AHB2_GRP1_PERIPH_GPIOH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2AHB2SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_C2_AHB3 C2 AHB3
  * @{
  */

/**
  * @brief  Enable C2AHB3 peripherals clock.
  * @rmtoll C2AHB3ENR    PKAEN         LL_C2_AHB3_GRP1_EnableClock\n
  *         C2AHB3ENR    AESEN         LL_C2_AHB3_GRP1_EnableClock\n
  *         C2AHB3ENR    RNGEN         LL_C2_AHB3_GRP1_EnableClock\n
  *         C2AHB3ENR    HSEMEN        LL_C2_AHB3_GRP1_EnableClock\n
  *         C2AHB3ENR    IPCCEN        LL_C2_AHB3_GRP1_EnableClock\n
  *         C2AHB3ENR    FLASHEN       LL_C2_AHB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2AHB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2AHB3ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2AHB3 peripheral clock is enabled or not
  * @rmtoll C2AHB3ENR    PKAEN         LL_C2_AHB3_GRP1_IsEnabledClock\n
  *         C2AHB3ENR    AESEN         LL_C2_AHB3_GRP1_IsEnabledClock\n
  *         C2AHB3ENR    RNGEN         LL_C2_AHB3_GRP1_IsEnabledClock\n
  *         C2AHB3ENR    HSEMEN        LL_C2_AHB3_GRP1_IsEnabledClock\n
  *         C2AHB3ENR    IPCCEN        LL_C2_AHB3_GRP1_IsEnabledClock\n
  *         C2AHB3ENR    FLASHEN       LL_C2_AHB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_FLASH
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2AHB3ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2AHB3 peripherals clock.
  * @rmtoll C2AHB3ENR    PKAEN         LL_C2_AHB3_GRP1_DisableClock\n
  *         C2AHB3ENR    AESEN         LL_C2_AHB3_GRP1_DisableClock\n
  *         C2AHB3ENR    RNGEN         LL_C2_AHB3_GRP1_DisableClock\n
  *         C2AHB3ENR    HSEMEN        LL_C2_AHB3_GRP1_DisableClock\n
  *         C2AHB3ENR    IPCCEN        LL_C2_AHB3_GRP1_DisableClock\n
  *         C2AHB3ENR    FLASHEN       LL_C2_AHB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_HSEM
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_IPCC
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2AHB3ENR, Periphs);
}

/**
  * @brief  Enable C2AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2AHB3SMENR  PKASMEN       LL_C2_AHB3_GRP1_EnableClockSleep\n
  *         C2AHB3SMENR  AESSMEN       LL_C2_AHB3_GRP1_EnableClockSleep\n
  *         C2AHB3SMENR  RNGSMEN       LL_C2_AHB3_GRP1_EnableClockSleep\n
  *         C2AHB3SMENR  SRAM1SMEN     LL_C2_AHB3_GRP1_EnableClockSleep\n
  *         C2AHB3SMENR  SRAM2SMEN     LL_C2_AHB3_GRP1_EnableClockSleep\n
  *         C2AHB3SMENR  FLASHSMEN     LL_C2_AHB3_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_SRAM1
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2AHB3SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2AHB3SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2AHB3 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2AHB3SMENR  PKASMEN       LL_C2_AHB3_GRP1_IsEnabledClockSleep\n
  *         C2AHB3SMENR  AESSMEN       LL_C2_AHB3_GRP1_IsEnabledClockSleep\n
  *         C2AHB3SMENR  RNGSMEN       LL_C2_AHB3_GRP1_IsEnabledClockSleep\n
  *         C2AHB3SMENR  SRAM1SMEN     LL_C2_AHB3_GRP1_IsEnabledClockSleep\n
  *         C2AHB3SMENR  SRAM2SMEN     LL_C2_AHB3_GRP1_IsEnabledClockSleep\n
  *         C2AHB3SMENR  FLASHSMEN     LL_C2_AHB3_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_SRAM1
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_AHB3_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2AHB3SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2AHB3SMENR  PKASMEN       LL_C2_AHB3_GRP1_DisableClockSleep\n
  *         C2AHB3SMENR  AESSMEN       LL_C2_AHB3_GRP1_DisableClockSleep\n
  *         C2AHB3SMENR  RNGSMEN       LL_C2_AHB3_GRP1_DisableClockSleep\n
  *         C2AHB3SMENR  SRAM2SMEN     LL_C2_AHB3_GRP1_DisableClockSleep\n
  *         C2AHB3SMENR  FLASHSMEN     LL_C2_AHB3_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_PKA
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_AES
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_C2_AHB3_GRP1_PERIPH_FLASH
  * @retval None
  */
__STATIC_INLINE void LL_C2_AHB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2AHB3SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_C2_APB1 C2 APB1
  * @{
  */

/**
  * @brief  Enable C2APB1 peripherals clock.
  * @rmtoll C2APB1ENR1   TIM2EN        LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   RTCAPBEN      LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   SPI2EN        LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   USART2EN      LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   I2C1EN        LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   I2C2EN        LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   I2C3EN        LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   DACEN         LL_C2_APB1_GRP1_EnableClock\n
  *         C2APB1ENR1   LPTIM1EN      LL_C2_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB1ENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB1ENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable C2APB1 peripherals clock.
  * @rmtoll C2APB1ENR2   LPUART1EN     LL_C2_APB1_GRP2_EnableClock\n
  *         C2APB1ENR2   LPTIM2EN      LL_C2_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB1ENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB1ENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2APB1 peripheral clock is enabled or not
  * @rmtoll C2APB1ENR1   TIM2EN        LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   RTCAPBEN      LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   SPI2EN        LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   USART2EN      LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   I2C1EN        LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   I2C2EN        LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   I2C3EN        LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   DACEN         LL_C2_APB1_GRP1_IsEnabledClock\n
  *         C2APB1ENR1   LPTIM1EN      LL_C2_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_LPTIM1

  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB1ENR1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Check if C2APB1 peripheral clock is enabled or not
  * @rmtoll C2APB1ENR2   LPUART1EN     LL_C2_APB1_GRP2_IsEnabledClock\n
  *         C2APB1ENR2   LPTIM2EN      LL_C2_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM2
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB1ENR2, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2APB1 peripherals clock.
  * @rmtoll C2APB1ENR1   TIM2EN        LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   RTCAPBEN      LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   SPI2EN        LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   USART2EN      LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   I2C1EN        LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   I2C2EN        LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   I2C3EN        LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   DACEN         LL_C2_APB1_GRP1_DisableClock\n
  *         C2APB1ENR1   LPTIM1EN      LL_C2_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB1ENR1, Periphs);
}

/**
  * @brief  Disable C2APB1 peripherals clock.
  * @rmtoll C2APB1ENR2   LPUART1EN     LL_C2_APB1_GRP2_DisableClock\n
  *         C2APB1ENR2   LPTIM2EN      LL_C2_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB1ENR2, Periphs);
}

/**
  * @brief  Enable C2APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB1SMENR1 TIM2SMEN      LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 RTCAPBSMEN    LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 SPI2SMEN      LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 USART2SMEN    LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 I2C1SMEN      LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 I2C2SMEN      LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 I2C3SMEN      LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 DACSMEN       LL_C2_APB1_GRP1_EnableClockSleep\n
  *         C2APB1SMENR1 LPTIM1SMEN    LL_C2_APB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_LPTIM1
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB1SMENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB1SMENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Enable C2APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB1SMENR2 LPUART1SMEN   LL_C2_APB1_GRP2_EnableClockSleep\n
  *         C2APB1SMENR2 LPTIM2SMEN    LL_C2_APB1_GRP2_EnableClockSleep\n
  *         C2APB1SMENR2 LPTIM3SMEN    LL_C2_APB1_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB1SMENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB1SMENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2APB1 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2APB1SMENR1 TIM2SMEN      LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 RTCAPBSMEN    LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 SPI2SMEN      LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 USART2SMEN    LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 I2C1SMEN      LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 I2C2SMEN      LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 I2C3SMEN      LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 DACSMEN       LL_C2_APB1_GRP1_IsEnabledClockSleep\n
  *         C2APB1SMENR1 LPTIM1SMEN    LL_C2_APB1_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_LPTIM1
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_APB1_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB1SMENR1, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Check if C2APB1 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2APB1SMENR2 LPUART1SMEN   LL_C2_APB1_GRP2_IsEnabledClockSleep\n
  *         C2APB1SMENR2 LPTIM2SMEN    LL_C2_APB1_GRP2_IsEnabledClockSleep\n
  *         C2APB1SMENR2 LPTIM3SMEN    LL_C2_APB1_GRP2_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM3
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_APB1_GRP2_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB1SMENR2, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB1SMENR1 TIM2SMEN      LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 RTCAPBSMEN    LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 SPI2SMEN      LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 USART2SMEN    LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 I2C1SMEN      LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 I2C2SMEN      LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 I2C3SMEN      LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 DACSMEN       LL_C2_APB1_GRP1_DisableClockSleep\n
  *         C2APB1SMENR1 LPTIM1SMEN    LL_C2_APB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_DAC
  *         @arg @ref LL_C2_APB1_GRP1_PERIPH_LPTIM1

  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB1SMENR1, Periphs);
}

/**
  * @brief  Disable C2APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB1SMENR2 LPUART1SMEN   LL_C2_APB1_GRP2_DisableClockSleep\n
  *         C2APB1SMENR2 LPTIM2SMEN    LL_C2_APB1_GRP2_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPUART1
  *         @arg @ref LL_C2_APB1_GRP2_PERIPH_LPTIM2
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB1_GRP2_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB1SMENR2, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_C2_APB2 C2 APB2
  * @{
  */

/**
  * @brief  Enable C2APB2 peripherals clock.
  * @rmtoll C2APB2ENR    ADCEN         LL_C2_APB2_GRP1_EnableClock\n
  *         C2APB2ENR    TIM1EN        LL_C2_APB2_GRP1_EnableClock\n
  *         C2APB2ENR    SPI1EN        LL_C2_APB2_GRP1_EnableClock\n
  *         C2APB2ENR    USART1EN      LL_C2_APB2_GRP1_EnableClock\n
  *         C2APB2ENR    TIM16EN       LL_C2_APB2_GRP1_EnableClock\n
  *         C2APB2ENR    TIM17EN       LL_C2_APB2_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2APB2 peripheral clock is enabled or not
  * @rmtoll C2APB2ENR    ADCEN         LL_C2_APB2_GRP1_IsEnabledClock\n
  *         C2APB2ENR    TIM1EN        LL_C2_APB2_GRP1_IsEnabledClock\n
  *         C2APB2ENR    SPI1EN        LL_C2_APB2_GRP1_IsEnabledClock\n
  *         C2APB2ENR    USART1EN      LL_C2_APB2_GRP1_IsEnabledClock\n
  *         C2APB2ENR    TIM16EN       LL_C2_APB2_GRP1_IsEnabledClock\n
  *         C2APB2ENR    TIM17EN       LL_C2_APB2_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM17
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB2ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2APB2 peripherals clock.
  * @rmtoll C2APB2ENR    ADCEN         LL_C2_APB2_GRP1_DisableClock\n
  *         C2APB2ENR    TIM1EN        LL_C2_APB2_GRP1_DisableClock\n
  *         C2APB2ENR    SPI1EN        LL_C2_APB2_GRP1_DisableClock\n
  *         C2APB2ENR    USART1EN      LL_C2_APB2_GRP1_DisableClock\n
  *         C2APB2ENR    TIM16EN       LL_C2_APB2_GRP1_DisableClock\n
  *         C2APB2ENR    TIM17EN       LL_C2_APB2_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB2ENR, Periphs);
}

/**
  * @brief  Enable C2APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB2SMENR  ADCSMEN       LL_C2_APB2_GRP1_EnableClockSleep\n
  *         C2APB2SMENR  TIM1SMEN      LL_C2_APB2_GRP1_EnableClockSleep\n
  *         C2APB2SMENR  SPI1SMEN      LL_C2_APB2_GRP1_EnableClockSleep\n
  *         C2APB2SMENR  USART1SMEN    LL_C2_APB2_GRP1_EnableClockSleep\n
  *         C2APB2SMENR  TIM16SMEN     LL_C2_APB2_GRP1_EnableClockSleep\n
  *         C2APB2SMENR  TIM17SMEN     LL_C2_APB2_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB2SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2APB2 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2APB2SMENR  ADCSMEN       LL_C2_APB2_GRP1_IsEnabledClockSleep\n
  *         C2APB2SMENR  TIM1SMEN      LL_C2_APB2_GRP1_IsEnabledClockSleep\n
  *         C2APB2SMENR  SPI1SMEN      LL_C2_APB2_GRP1_IsEnabledClockSleep\n
  *         C2APB2SMENR  USART1SMEN    LL_C2_APB2_GRP1_IsEnabledClockSleep\n
  *         C2APB2SMENR  TIM16SMEN     LL_C2_APB2_GRP1_IsEnabledClockSleep\n
  *         C2APB2SMENR  TIM17SMEN     LL_C2_APB2_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_APB2_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB2SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB2SMENR  ADCSMEN       LL_C2_APB2_GRP1_DisableClockSleep\n
  *         C2APB2SMENR  TIM1SMEN      LL_C2_APB2_GRP1_DisableClockSleep\n
  *         C2APB2SMENR  SPI1SMEN      LL_C2_APB2_GRP1_DisableClockSleep\n
  *         C2APB2SMENR  USART1SMEN    LL_C2_APB2_GRP1_DisableClockSleep\n
  *         C2APB2SMENR  TIM16SMEN     LL_C2_APB2_GRP1_DisableClockSleep\n
  *         C2APB2SMENR  TIM17SMEN     LL_C2_APB2_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_ADC
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_C2_APB2_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB2SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_C2_APB3 C2 APB3
  * @{
  */

/**
  * @brief  Enable C2APB3 peripherals clock.
  * @rmtoll C2APB3ENR    SUBGHZSPIEN    LL_C2_APB3_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB3ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2APB3 peripheral clock is enabled or not
  * @rmtoll C2APB3ENR    SUBGHZSPIEN    LL_C2_APB3_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_C2_APB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB3ENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2APB3 peripherals clock.
  * @rmtoll C2APB3ENR    SUBGHZSPIEN     LL_C2_APB3_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB3ENR, Periphs);
}

/**
  * @brief  Enable C2APB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB3SMENR  SUBGHZSPISMEN   LL_C2_APB3_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->C2APB3SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->C2APB3SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if C2APB3 peripheral clock is enabled by the clock gating during CPU1 CSleep mode.
  * @rmtoll C2APB3SMENR  SUBGHZSPISMEN   LL_C2_APB3_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_APB3_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->C2APB3SMENR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @brief  Disable C2APB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll C2APB3SMENR  SUBGHZSPISMEN   LL_C2_APB3_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI
  * @retval None
  */
__STATIC_INLINE void LL_C2_APB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->C2APB3SMENR, Periphs);
}

/**
  * @}
  */
#endif /* DUAL_CORE */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WLxx_LL_BUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
