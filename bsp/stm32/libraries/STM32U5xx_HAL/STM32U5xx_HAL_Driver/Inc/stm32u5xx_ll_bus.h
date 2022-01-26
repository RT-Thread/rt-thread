/**
  ******************************************************************************
  * @file    stm32u5xx_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.

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
  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB , APB peripherals,  1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB , APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_BUS_H
#define STM32U5xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
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
#define LL_AHB1_GRP1_PERIPH_ALL           0xFFFFFFFFU
#define LL_AHB1_GRP1_PERIPH_GPDMA1        RCC_AHB1ENR_GPDMA1EN
#define LL_AHB1_GRP1_PERIPH_CORDIC        RCC_AHB1ENR_CORDICEN
#define LL_AHB1_GRP1_PERIPH_FMAC          RCC_AHB1ENR_FMACEN
#define LL_AHB1_GRP1_PERIPH_MDF1          RCC_AHB1ENR_MDF1EN
#define LL_AHB1_GRP1_PERIPH_FLASH         RCC_AHB1ENR_FLASHEN
#define LL_AHB1_GRP1_PERIPH_CRC           RCC_AHB1ENR_CRCEN
#define LL_AHB1_GRP1_PERIPH_TSC           RCC_AHB1ENR_TSCEN
#define LL_AHB1_GRP1_PERIPH_RAMCFG        RCC_AHB1ENR_RAMCFGEN
#define LL_AHB1_GRP1_PERIPH_DMA2D         RCC_AHB1ENR_DMA2DEN
#define LL_AHB1_GRP1_PERIPH_GTZC1         RCC_AHB1ENR_GTZC1EN
#define LL_AHB1_GRP1_PERIPH_BKPSRAM       RCC_AHB1ENR_BKPSRAMEN
#define LL_AHB1_GRP1_PERIPH_DCACHE1       RCC_AHB1ENR_DCACHE1EN
#define LL_AHB1_GRP1_PERIPH_SRAM1         RCC_AHB1ENR_SRAM1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_AHB2_GRP1_PERIPH_GPIOA          RCC_AHB2ENR1_GPIOAEN
#define LL_AHB2_GRP1_PERIPH_GPIOB          RCC_AHB2ENR1_GPIOBEN
#define LL_AHB2_GRP1_PERIPH_GPIOC          RCC_AHB2ENR1_GPIOCEN
#define LL_AHB2_GRP1_PERIPH_GPIOD          RCC_AHB2ENR1_GPIODEN
#define LL_AHB2_GRP1_PERIPH_GPIOE          RCC_AHB2ENR1_GPIOEEN
#define LL_AHB2_GRP1_PERIPH_GPIOF          RCC_AHB2ENR1_GPIOFEN
#define LL_AHB2_GRP1_PERIPH_GPIOG          RCC_AHB2ENR1_GPIOGEN
#define LL_AHB2_GRP1_PERIPH_GPIOH          RCC_AHB2ENR1_GPIOHEN
#define LL_AHB2_GRP1_PERIPH_GPIOI          RCC_AHB2ENR1_GPIOIEN
#define LL_AHB2_GRP1_PERIPH_ADC1           RCC_AHB2ENR1_ADC1EN
#define LL_AHB2_GRP1_PERIPH_DCMI_PSSI      RCC_AHB2ENR1_DCMI_PSSIEN
#define LL_AHB2_GRP1_PERIPH_USBFS          RCC_AHB2ENR1_OTGEN
#if defined(AES)
#define LL_AHB2_GRP1_PERIPH_AES            RCC_AHB2ENR1_AESEN
#endif /* AES */
#if defined(HASH)
#define LL_AHB2_GRP1_PERIPH_HASH           RCC_AHB2ENR1_HASHEN
#endif /* HASH */
#define LL_AHB2_GRP1_PERIPH_RNG            RCC_AHB2ENR1_RNGEN
#define LL_AHB2_GRP1_PERIPH_PKA            RCC_AHB2ENR1_PKAEN
#if defined(SAES)
#define LL_AHB2_GRP1_PERIPH_SAES           RCC_AHB2ENR1_SAESEN
#endif /* SAES */
#define LL_AHB2_GRP1_PERIPH_OCTOSPIM       RCC_AHB2ENR1_OCTOSPIMEN
#define LL_AHB2_GRP1_PERIPH_OTFDEC1        RCC_AHB2ENR1_OTFDEC1EN
#define LL_AHB2_GRP1_PERIPH_OTFDEC2        RCC_AHB2ENR1_OTFDEC2EN
#define LL_AHB2_GRP1_PERIPH_SDMMC1         RCC_AHB2ENR1_SDMMC1EN
#define LL_AHB2_GRP1_PERIPH_SDMMC2         RCC_AHB2ENR1_SDMMC2EN
#define LL_AHB2_GRP1_PERIPH_SRAM2          RCC_AHB2ENR1_SRAM2EN
#define LL_AHB2_GRP1_PERIPH_SRAM3          RCC_AHB2ENR1_SRAM3EN

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB3_GRP1_PERIPH  AHB3 GRP1 PERIPH
  * @{
  */
#define LL_AHB3_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_AHB3_GRP1_PERIPH_LPGPIO1        RCC_AHB3ENR_LPGPIO1EN
#define LL_AHB3_GRP1_PERIPH_PWR            RCC_AHB3ENR_PWREN
#define LL_AHB3_GRP1_PERIPH_ADC4           RCC_AHB3ENR_ADC4EN
#define LL_AHB3_GRP1_PERIPH_DAC1           RCC_AHB3ENR_DAC1EN
#define LL_AHB3_GRP1_PERIPH_LPDMA1         RCC_AHB3ENR_LPDMA1EN
#define LL_AHB3_GRP1_PERIPH_ADF1           RCC_AHB3ENR_ADF1EN
#define LL_AHB3_GRP1_PERIPH_GTZC2          RCC_AHB3ENR_GTZC2EN
#define LL_AHB3_GRP1_PERIPH_SRAM4          RCC_AHB3SMENR_SRAM4SMEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP2_PERIPH  AHB2 GRP2 PERIPH
  * @{
  */
#define LL_AHB2_GRP2_PERIPH_ALL            0xFFFFFFFFU
#define LL_AHB2_GRP2_PERIPH_FSMC           RCC_AHB2ENR2_FSMCEN
#define LL_AHB2_GRP2_PERIPH_OCTOSPI1       RCC_AHB2ENR2_OCTOSPI1EN
#define LL_AHB2_GRP2_PERIPH_OCTOSPI2       RCC_AHB2ENR2_OCTOSPI2EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL           0xFFFFFFFFU
#define LL_APB1_GRP1_PERIPH_TIM2          RCC_APB1ENR1_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3          RCC_APB1ENR1_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM4          RCC_APB1ENR1_TIM4EN
#define LL_APB1_GRP1_PERIPH_TIM5          RCC_APB1ENR1_TIM5EN
#define LL_APB1_GRP1_PERIPH_TIM6          RCC_APB1ENR1_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7          RCC_APB1ENR1_TIM7EN
#define LL_APB1_GRP1_PERIPH_WWDG          RCC_APB1ENR1_WWDGEN
#define LL_APB1_GRP1_PERIPH_SPI2          RCC_APB1ENR1_SPI2EN
#define LL_APB1_GRP1_PERIPH_USART2        RCC_APB1ENR1_USART2EN
#define LL_APB1_GRP1_PERIPH_USART3        RCC_APB1ENR1_USART3EN
#define LL_APB1_GRP1_PERIPH_UART4         RCC_APB1ENR1_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5         RCC_APB1ENR1_UART5EN
#define LL_APB1_GRP1_PERIPH_I2C1          RCC_APB1ENR1_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2          RCC_APB1ENR1_I2C2EN
#define LL_APB1_GRP1_PERIPH_CRS           RCC_APB1ENR1_CRSEN
/**
  * @}
  */


/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_ALL            0xFFFFFFFFU
#define LL_APB1_GRP2_PERIPH_I2C4           RCC_APB1ENR2_I2C4EN
#define LL_APB1_GRP2_PERIPH_LPTIM2         RCC_APB1ENR2_LPTIM2EN
#define LL_APB1_GRP2_PERIPH_FDCAN1         RCC_APB1ENR2_FDCAN1EN
#define LL_APB1_GRP2_PERIPH_UCPD1          RCC_APB1ENR2_UCPD1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#define LL_APB2_GRP1_PERIPH_TIM8           RCC_APB2ENR_TIM8EN
#define LL_APB2_GRP1_PERIPH_USART1         RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_TIM15          RCC_APB2ENR_TIM15EN
#define LL_APB2_GRP1_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
#define LL_APB2_GRP1_PERIPH_SAI1           RCC_APB2ENR_SAI1EN
#define LL_APB2_GRP1_PERIPH_SAI2           RCC_APB2ENR_SAI2EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_GRP1_PERIPH  APB3 GRP1 PERIPH
  * @{
  */
#define LL_APB3_GRP1_PERIPH_ALL           0xFFFFFFFFU
#define LL_APB3_GRP1_PERIPH_SYSCFG        RCC_APB3ENR_SYSCFGEN
#define LL_APB3_GRP1_PERIPH_SPI3          RCC_APB3ENR_SPI3EN
#define LL_APB3_GRP1_PERIPH_LPUART1       RCC_APB3ENR_LPUART1EN
#define LL_APB3_GRP1_PERIPH_I2C3          RCC_APB3ENR_I2C3EN
#define LL_APB3_GRP1_PERIPH_LPTIM1        RCC_APB3ENR_LPTIM1EN
#define LL_APB3_GRP1_PERIPH_LPTIM3        RCC_APB3ENR_LPTIM3EN
#define LL_APB3_GRP1_PERIPH_LPTIM4        RCC_APB3ENR_LPTIM4EN
#define LL_APB3_GRP1_PERIPH_OPAMP         RCC_APB3ENR_OPAMPEN
#define LL_APB3_GRP1_PERIPH_COMP          RCC_APB3ENR_COMPEN
#define LL_APB3_GRP1_PERIPH_VREF          RCC_APB3ENR_VREFEN
#define LL_APB3_GRP1_PERIPH_RTCAPB        RCC_APB3ENR_RTCAPBEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_SRDAMR_GRP1_PERIPH  SRDAMR GRP1 PERIPH
  * @{
  */
#define LL_SRDAMR_GRP1_PERIPH_ALL            0xFFFFFFFFU
#define LL_SRDAMR_GRP1_PERIPH_SPI3AMEN       RCC_SRDAMR_SPI3AMEN
#define LL_SRDAMR_GRP1_PERIPH_LPUART1AMEN    RCC_SRDAMR_LPUART1AMEN
#define LL_SRDAMR_GRP1_PERIPH_I2C3AMEN       RCC_SRDAMR_I2C3AMEN
#define LL_SRDAMR_GRP1_PERIPH_LPTIM1AMEN     RCC_SRDAMR_LPTIM1AMEN
#define LL_SRDAMR_GRP1_PERIPH_LPTIM3AMEN     RCC_SRDAMR_LPTIM3AMEN
#define LL_SRDAMR_GRP1_PERIPH_LPTIM4AMEN     RCC_SRDAMR_LPTIM4AMEN
#define LL_SRDAMR_GRP1_PERIPH_OPAMPAMEN      RCC_SRDAMR_OPAMPAMEN
#define LL_SRDAMR_GRP1_PERIPH_COMPAMEN       RCC_SRDAMR_COMPAMEN
#define LL_SRDAMR_GRP1_PERIPH_VREFAMEN       RCC_SRDAMR_VREFAMEN
#define LL_SRDAMR_GRP1_PERIPH_RTCAPBAMEN     RCC_SRDAMR_RTCAPBAMEN
#define LL_SRDAMR_GRP1_PERIPH_ADC4AMEN       RCC_SRDAMR_ADC4AMEN
#define LL_SRDAMR_GRP1_PERIPH_LPGPIO1AMEN    RCC_SRDAMR_LPGPIO1AMEN
#define LL_SRDAMR_GRP1_PERIPH_DAC1AMEN       RCC_SRDAMR_DAC1AMEN
#define LL_SRDAMR_GRP1_PERIPH_LPDMA1AMEN     RCC_SRDAMR_LPDMA1AMEN
#define LL_SRDAMR_GRP1_PERIPH_ADF1AMEN       RCC_SRDAMR_ADF1AMEN
#define LL_SRDAMR_GRP1_PERIPH_SRAM4AMEN      RCC_SRDAMR_SRAM4AMEN
/**
  * @}
  */

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
  * @rmtoll AHB1ENR    GPDMA1EN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    CORDICEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    FMACEN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    MDF1EN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    FLASHEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    CRCEN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    TSCEN        LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    RAMCFGEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    DMA2DEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    GTZC1EN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    BKPSRAMEN    LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    DCACHE1EN    LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR    SRAM1EN      LL_AHB1_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
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
  * @rmtoll AHB1ENR    GPDMA1EN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    CORDICEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    FMACEN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    MDF1EN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    FLASHEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    CRCEN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    TSCEN        LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    RAMCFGEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    DMA2DEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    GTZC1EN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    BKPSRAMEN    LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    DCACHEEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR    SRAM1EN      LL_AHB1_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHB1ENR    GPDMA1EN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    CORDICEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    FMACEN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    MDF1EN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    FLASHEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    CRCEN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    TSCEN        LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    RAMCFGEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    DMA2DEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    GTZC1EN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    BKPSRAMEN    LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    DCACHEEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR    SRAM1EN      LL_AHB1_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHB1RSTR    GPDMA1RSTR     LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    CORDICRSTR     LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    FMACRSTR       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    MDF1RSTR       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    CRCRSTR        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    TSCRSTR        LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    RAMCFGRSTR     LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR    DMA2DRSTR      LL_AHB1_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHB1RSTR    GPDMA1RSTR      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    CORDICRSTR      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    FMACRSTR        LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    MDF1RSTR        LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    CRCRSTR         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    TSCRSTR         LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    RAMCFGRSTR      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR    DMA2DRSTR       LL_AHB1_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Enable AHB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB1SMENR   GPDMA1SMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   CORDICSMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   FMACSMEN       LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   MDF1SMEN       LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   FLASHSMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   CRCSMEN        LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   TSCSMEN        LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   RAMCFGSMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   DMA2DSMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   GTZC1SMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   BKPSRAMSMEN    LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   DCACHESMEN     LL_AHB1_GRP1_EnableClockStopSleep\n
  *         AHB1SMENR   SRAM1SMEN      LL_AHB1_GRP1_EnableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB1SMENR   GPDMA1SMEN     LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   CORDICSMEN     LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   FMACSMEN       LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   MDF1SMEN       LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   FLASHSMEN      LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   CRCSMEN        LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   TSCSMEN        LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   RAMCFGSMEN     LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   DMA2DSMEN      LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   GTZC1SMEN      LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   BKPSRAMSMEN    LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  *         AHB1SMENR   DCACHESMEN     LL_AHB1_GRP1_IsEnabledClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB1SMENR   GPDMA1SMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   CORDICSMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   FMACSMEN       LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   MDF1SMEN       LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   FLASHSMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   CRCSMEN        LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   TSCSMEN        LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   RAMCFGSMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   DMA2DSMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   GTZC1SMEN      LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   BKPSRAMSMEN    LL_AHB1_GRP1_DisableClockStopSleep\n
  *         AHB1SMENR   DCACHESMEN     LL_AHB1_GRP1_DisableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_MDF1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TSC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GTZC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2_GRP1_PERIPH AHB2 GRP1 PERIPH
  * @{
  */
/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR1      GPIOAEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOBEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOCEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIODEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOEEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOFEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOGEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOHEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      GPIOIEN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      ADC1EN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      DCMI_PSSIEN   LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      OTGEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      AESEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      HASHEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      RNGEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      PKAEN         LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SAESEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      OCTOSPIMEN    LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      OTFDEC1EN     LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      OTFDEC2EN     LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SDMMC1EN      LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SDMMC2EN      LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SRAM2EN       LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR1      SRAM3EN       LL_AHB2_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2ENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled or not
  * @rmtoll AHB2ENR1      GPIOAEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOBEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOCEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIODEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOEEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOFEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOGEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOHEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      GPIOIEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      ADC1EN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      DCMI_PSSIEN   LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      OTGFSEN       LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      AESEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      HASHEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      RNGEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      PKAEN         LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SAESEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      OCTOSPIMEN    LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      OTFDEC1EN     LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      OTFDEC2EN     LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SDMMC1EN      LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR1      SDMMC2EN      LL_AHB2_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR1      GPIOAEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOBEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOCEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIODEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOEEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOFEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOGEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOHEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      GPIOIEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      ADC1EN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      DCMI_PSSIEN   LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      OTGEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      AESEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      HASHEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      RNGEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      PKAEN         LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SAESEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      OSPIMEN       LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      OTFDEC1EN     LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      OTFDEC2EN     LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SDMMC1EN      LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR1      SDMMC2EN      LL_AHB2_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR1, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTR1     GPIOARST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIOBRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIOCRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIODRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIOERST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIOFRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIOGRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     GPIOHRST      LL_AHB2_GRP1_ForceResetn
  *         AHB2RSTR1     GPIOIRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     ADC1RST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     DCMI_PSSIRST  LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     OTGRST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     AESRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     HASHRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     RNGRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     PKARST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     SAESRST       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     OCTOSPIMRST   LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     OTFDEC1RST    LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR1     OTFDEC2RST    LL_AHB2_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR1, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTR1     GPIOARST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIOBRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIOCRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIODRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIOERST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIOFRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIOGRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     GPIOHRST      LL_AHB2_GRP1_ReleaseResetn
  *         AHB2RSTR1     GPIOIRST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     ADC1RST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     DCMI_PSSIRST  LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     OTGRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     AESRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     HASHRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     RNGRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     PKARST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     SAESRST       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     OCTOSPIMRST   LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     OTFDEC1RST    LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     OTFDEC2RST    LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     SDMMC1RST     LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR1     SDMMC2RST     LL_AHB2_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR1, Periphs);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB2SMENR1    GPIOASMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIOBSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIOCSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIODSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIOESMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIOFSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIOGSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    GPIOHSMEN      LL_AHB2_GRP1_EnableClockStopSleepn
  *         AHB2SMENR1    GPIOISMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    ADC1SMEN       LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    DCMI_PSSISMEN  LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    OTGSMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    AESSMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    HASHSMEN       LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    RNGSMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    PKASMEN        LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    SAESSMEN       LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    OSPIMSMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    OTFDEC1SMEN    LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    OTFDEC2SMEN    LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    SDMMC1SMEN     LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    SDMMC2SMEN     LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    SRAM3SMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    SRAM4SMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2SMENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SMENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB2SMENR1    GPIOASMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIOBSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIOCSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIODSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIOESMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIOFSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIOGSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    GPIOHSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleepn
  *         AHB2SMENR1    GPIOISMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    ADC1SMEN       LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    DCMI_PSSISMEN  LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    OTGSMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    AESSMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    HASHSMEN       LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    RNGSMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    PKASMEN        LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    SAESSMEN       LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    OSPIMSMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    OTFDEC1SMEN    LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    OTFDEC2SMEN    LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    SDMMC1SMEN     LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    SDMMC2SMEN     LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    SRAM3SMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  *         AHB2SMENR1    SRAM4SMEN      LL_AHB2_GRP1_IsEnabledClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2SMENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB2SMENR1    GPIOASMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIOBSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIOCSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIODSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIOESMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIOFSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIOGSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    GPIOHSMEN      LL_AHB2_GRP1_DisableClockStopSleepn
  *         AHB2SMENR1    GPIOISMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    ADC1SMEN       LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    DCMI_PSSISMEN  LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    OTGSMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    AESSMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    HASHSMEN       LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    RNGSMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    PKASMEN        LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    SAESSMEN       LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    OSPIMSMEN      LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    OTFDEC1SMEN    LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    OTFDEC2SMEN    LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    SDMMC1SMEN     LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    SDMMC2SMEN     LL_AHB2_GRP1_DisableClockStopSleep\n
  *         AHB2SMENR1    SRAM3SMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  *         AHB2SMENR1    SRAM4SMEN      LL_AHB2_GRP1_EnableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_GPIOI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DCMI_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBFS
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB2_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OCTOSPIM
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_OTFDEC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SRAM3
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2SMENR1, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB3 AHB3
  * @{
  */
/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll AHB3ENR  LPGPIO1EN     LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR  PWREN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR  ADC4EN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR  DAC1EN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR  LPDMA1EN      LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR  ADF1EN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR  GTZC2EN       LL_AHB3_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB3 peripheral clock is enabled or not
  * @rmtoll AHB3ENR  LPGPIO1EN     LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR  PWREN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR  ADC4EN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR  DAC1EN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR  LPDMA1EN      LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR  ADF1EN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR  GTZC2EN       LL_AHB3_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB3ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 peripherals clock.
  * @rmtoll AHB3ENR  LPGPIO1EN     LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR  PWREN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR  ADC4EN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR  DAC1EN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR  LPDMA1EN      LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR  ADF1EN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR  GTZC2EN       LL_AHB3_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3ENR, Periphs);
}

/**
  * @brief  Force AHB3 peripherals reset.
  * @rmtoll AHB3RSTR  LPGPIO1RST     LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR  PWRRST         LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR  ADC4RST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR  DAC1RST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR  LPDMA1RST      LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR  ADF1RST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR  GTZC2RST       LL_AHB3_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Release AHB3 peripherals reset.
  * @rmtoll AHB3RSTR  LPGPIO1RST     LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR  PWRRST         LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR  ADC4RST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR  DAC1RST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR  LPDMA1RST      LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR  ADF1RST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR  GTZC2RST       LL_AHB3_GRP1_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Enable AHB3 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB3SMENR  LPGPIO1SMEN    LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  PWRSMEN        LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  ADC4SMEN       LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  DAC1SMEN       LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  LPDMA1SMEN     LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  ADF1SMEN       LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  GTZC2SMEN      LL_AHB3_GRP1_EnableClockStopSleep\n
  *         AHB3SMENR  SRAM4SMEN      LL_AHB3_GRP1_EnableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM4
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3SMENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB3 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB3SMENR  LPGPIO1SMEN    LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  PWRSMEN        LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  ADC4SMEN       LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  DAC1SMEN       LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  LPDMA1SMEN     LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  ADF1SMEN       LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  GTZC2SMEN      LL_AHB3_GRP1_IsEnabledClockStopSleep\n
  *         AHB3SMENR  SRAM4SMEN      LL_AHB3_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM4
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB3SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB3SMENR  LPGPIO1SMEN    LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  PWRSMEN        LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  ADC4SMEN       LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  DAC1SMEN       LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  LPDMA1SMEN     LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  ADF1SMEN       LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  GTZC2SMEN      LL_AHB3_GRP1_DisableClockStopSleep\n
  *         AHB3SMENR  SRAM4SMEN      LL_AHB3_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPGPIO1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PWR
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC4
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_LPDMA1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADF1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_GTZC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SRAM4
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2_GRP2_PERIPH AHB2 GRP2 PERIPH
  * @{
  */
/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR2  FSMCEN            LL_AHB2_GRP2_EnableClock\n
  *         AHB2ENR2  OCTOSPI1EN        LL_AHB2_GRP2_EnableClock\n
  *         AHB2ENR2  OCTOSPI2EN        LL_AHB2_GRP2_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2ENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clock is enabled or not
  * @rmtoll AHB2ENR2  FSMCEN            LL_AHB2_GRP2_IsEnabledClock\n
  *         AHB2ENR2  OCTOSPI1EN        LL_AHB2_GRP2_IsEnabledClock\n
  *         AHB2ENR2  OCTOSPI2EN        LL_AHB2_GRP2_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripherals clock.
  * @rmtoll AHB2ENR2  FSMCEN            LL_AHB2_GRP2_DisableClock\n
  *         AHB2ENR2  OCTOSPI1EN        LL_AHB2_GRP2_DisableClock\n
  *         AHB2ENR2  OCTOSPI2EN        LL_AHB2_GRP2_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR2, Periphs);
}

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll AHB2RSTR2  FSMCRST            LL_AHB2_GRP2_ForceReset\n
  *         AHB2RSTR2  OCTOSPI1RST        LL_AHB2_GRP2_ForceReset\n
  *         AHB2RSTR2  OCTOSPI2RST        LL_AHB2_GRP2_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR2, Periphs);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll AHB2RSTR2  FSMCRST            LL_AHB2_GRP2_ReleaseReset\n
  *         AHB2RSTR2  OCTOSPI1RST        LL_AHB2_GRP2_ReleaseReset\n
  *         AHB2RSTR2  OCTOSPI2RST        LL_AHB2_GRP2_ReleaseReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR2, Periphs);
}

/**
  * @brief  Enable AHB4 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB2SMENR2  FSMCSMEN            LL_AHB2_GRP2_EnableClockStopSleep\n
  *         AHB2SMENR2  OCTOSPI1SMEN        LL_AHB2_GRP2_EnableClockStopSleep\n
  *         AHB2SMENR2  OCTOSPI2SMEN        LL_AHB2_GRP2_EnableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2SMENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2SMENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll AHB2SMENR2  FSMCSMEN            LL_AHB2_GRP2_IsEnabledClockStopSleep\n
  *         AHB2SMENR2  OCTOSPI1SMEN        LL_AHB2_GRP2_IsEnabledClockStopSleep\n
  *         AHB2SMENR2  OCTOSPI2SMEN        LL_AHB2_GRP2_IsEnabledClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP2_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2SMENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripheral clocks in Sleep and Stop modes
  * @rmtoll AHB2SMENR2  FSMCSMEN            LL_AHB2_GRP2_DisableClockStopSleep\n
  *         AHB2SMENR2  OCTOSPI1SMEN        LL_AHB2_GRP2_DisableClockStopSleep\n
  *         AHB2SMENR2  OCTOSPI2SMEN        LL_AHB2_GRP2_DisableClockStopSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP2_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP2_PERIPH_FSMC
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI1
  *         @arg @ref LL_AHB2_GRP2_PERIPH_OCTOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP2_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2SMENR2, Periphs);
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
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM5EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     CRSEN         LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
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
  * @rmtoll APB1ENR2     I2C4EN        LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     FDCAN1EN      LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     UCPD1EN       LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
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
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM5EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     CRSEN         LL_APB1_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR2     I2C4EN        LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     FDCAN1EN      LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     UCPD1EN       LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM5EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     CRSEN         LL_APB1_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR1, Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR2     I2C4EN        LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     LPTIM2EN      LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     FDCAN1EN      LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     UCPD1EN       LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR2, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR1     TIM2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM4RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM5RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM6RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     TIM7RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     SPI2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     USART2RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     USART3RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     UART4RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     UART5RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     I2C1RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     I2C2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1     CRSRST        LL_APB1_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR2     I2C4RST       LL_APB1_GRP2_DisableClock\n
  *         APB1RSTR2     LPTIM2RST     LL_APB1_GRP2_DisableClock\n
  *         APB1RSTR2     FDCAN1RST     LL_APB1_GRP2_DisableClock\n
  *         APB1RSTR2     UCPDRST       LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR1     TIM2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM4RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM5RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM6RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     TIM7RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     SPI2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     USART2RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     USART3RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     UART4RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     UART5RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     I2C1RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     I2C2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1     CRSRST        LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR2     I2C4RST       LL_APB1_GRP2_ReleaseReset\n
  *         APB1RSTR2     LPTIM2RST     LL_APB1_GRP2_ReleaseReset\n
  *         APB1RSTR2     FDCAN1RST     LL_APB1_GRP2_ReleaseReset\n
  *         APB1RSTR2     UCPD1RST      LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB1SMENR1     TIM2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     TIM3SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     TIM4SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     TIM5SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     TIM6SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     TIM7SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     SPI2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     USART2SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     USART3SMEN     LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     UART4SMEN      LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     UART5SMEN      LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     I2C1SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     I2C2SMEN       LL_APB1_GRP1_EnableClockStopSleep\n
  *         APB1SMENR1     CRSSMEN        LL_APB1_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB1SMENR1     TIM2SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     TIM3SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     TIM4SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     TIM5SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     TIM6SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     TIM7SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     SPI2SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     USART2SMEN     LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     USART3SMEN     LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     UART4SMEN      LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     UART5SMEN      LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     I2C1SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     I2C2SMEN       LL_APB1_GRP1_IsEnabledClockStopSleep\n
  *         APB1SMENR1     CRSSMEN        LL_APB1_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR1, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB1SMENR1     TIM2SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     TIM3SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     TIM4SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     TIM5SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     TIM6SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     TIM7SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     SPI2SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     USART2SMEN     LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     USART3SMEN     LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     UART4SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     UART5SMEN      LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     I2C1SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     I2C2SMEN       LL_APB1_GRP1_DisableClockStopSleep\n
  *         APB1SMENR1     CRSSMEN        LL_APB1_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1SMENR1, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB1SMENR2    I2C4SMEN       LL_APB1_GRP2_EnableClockStopSleep\n
  *         APB1SMENR2    LPTIM2SMEN     LL_APB1_GRP2_EnableClockStopSleep\n
  *         APB1SMENR2    FDCAN1SMEN     LL_APB1_GRP2_EnableClockStopSleep\n
  *         APB1SMENR2    UCPD1SMEN      LL_APB1_GRP2_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1SMENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1SMENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB1SMENR2    I2C4SMEN       LL_APB1_GRP2_IsEnabledClockStopSleep\n
  *         APB1SMENR2    LPTIM2SMEN     LL_APB1_GRP2_IsEnabledClockStopSleep\n
  *         APB1SMENR2    FDCAN1SMEN     LL_APB1_GRP2_IsEnabledClockStopSleep\n
  *         APB1SMENR2    UCPD1SMEN      LL_APB1_GRP2_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1SMENR2, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB1SMENR2    I2C4SMEN       LL_APB1_GRP2_DisableClockStopSleep\n
  *         APB1SMENR2    LPTIM2SMEN     LL_APB1_GRP2_DisableClockStopSleep\n
  *         APB1SMENR2    FDCAN1SMEN     LL_APB1_GRP2_DisableClockStopSleep\n
  *         APB1SMENR2    UCPD1SMEN      LL_APB1_GRP2_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_I2C4
  *         @arg @ref LL_APB1_GRP2_PERIPH_LPTIM2
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN1
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockStopSleep(uint32_t Periphs)
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
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
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
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_IsEnabledClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM8EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTR      TIM1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      SPI1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM8RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      USART1RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM15RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM16RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      TIM17RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      SAI1RST        LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR      SAI2RST        LL_APB2_GRP1_ForceReset\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTR      TIM1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      SPI1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM8RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      USART1RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM15RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM16RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      TIM17RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      SAI1RST        LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR      SAI2RST        LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Enable APB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB2SMENR     TIM1SMEN       LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     SPI1SMEN       LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     TIM8SMEN       LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     USART1SMEN     LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     TIM15SMEN      LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     TIM16SMEN      LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     TIM17SMEN      LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     SAI1SMEN       LL_APB2_GRP1_EnableClockStopSleep\n
  *         APB2SMENR     SAI2SMEN       LL_APB2_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2SMENR, Periphs);
  (void)tmpreg;
}


/**
  * @brief  Check if APB2 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB2SMENR     TIM1SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     SPI1SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     TIM8SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     USART1SMEN     LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     TIM15SMEN      LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     TIM16SMEN      LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     TIM17SMEN      LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     SAI1SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep\n
  *         APB2SMENR     SAI2SMEN       LL_APB2_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB2SMENR     TIM1SMEN        LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     SPI1SMEN        LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     TIM8SMEN        LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     USART1SMEN      LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     TIM15SMEN       LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     TIM16SMEN       LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     TIM17SMEN       LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     SAI1SMEN        LL_APB2_GRP1_DisableClockStopSleep\n
  *         APB2SMENR     SAI2SMEN        LL_APB2_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockStopSleep(uint32_t Periphs)
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
  * @rmtoll APB3ENR      SYSCFGEN       LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      SPI3EN         LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPUART1EN      LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      I2C3EN         LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPTIM1EN       LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPTIM3EN       LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      LPTIM4EN       LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      OPAMPEN        LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      COMPEN         LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      VREFEN         LL_APB3_GRP1_EnableClock\n
  *         APB3ENR      RTCAPBEN       LL_APB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
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
  * @rmtoll APB3ENR      SYSCFGEN       LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      SPI3EN         LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPUART1EN      LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      I2C3EN         LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPTIM1EN       LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPTIM3EN       LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      LPTIM4EN       LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      OPAMPEN        LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      COMPEN         LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      VREFEN         LL_APB3_GRP1_IsEnabledClock\n
  *         APB3ENR      RTCAPBEN       LL_APB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3ENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB3ENR      SYSCFGEN       LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      SPI3EN         LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPUART1EN      LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      I2C3EN         LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPTIM1EN       LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPTIM3EN       LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      LPTIM4EN       LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      OPAMPEN        LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      COMPEN         LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      VREFEN         LL_APB3_GRP1_DisableClock\n
  *         APB3ENR      RTCAPBEN       LL_APB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3ENR, Periphs);
}

/**
  * @brief  Force APB3 peripherals reset.
  * @rmtoll APB3RSTR     SYSCFGRST     LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     SPI3RST       LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     LPUART1RST    LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     I2C3RST       LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     LPTIM1RST     LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     LPTIM3RST     LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     LPTIM4RST     LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     OPAMPRST      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     COMPRST       LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     VREFRST       LL_APB3_GRP1_ForceReset\n
  *         APB3RSTR     RTCAPBRST     LL_APB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Release APB3 peripherals reset.
  * @rmtoll APB3RSTR     SYSCFGRST     LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     SPI3RST       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     LPUART1RST    LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     I2C3RST       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     LPTIM1RST     LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     LPTIM3RST     LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     LPTIM4RST     LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     OPAMPRST      LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     COMPRST       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     VREFRST       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTR     RTCAPBRST     LL_APB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3RSTR, Periphs);
}

/**
  * @brief  Enable APB3 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB3SMENR    SYSCFGSMEN    LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    SPI3SMEN      LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    LPUART1SMEN   LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    I2C3SMEN      LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    LPTIM1SMEN    LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    LPTIM3SMEN    LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    LPTIM4SMEN    LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    OPAMPSMEN     LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    COMPSMEN      LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    VREFSMEN      LL_APB3_GRP1_EnableClockStopSleep\n
  *         APB3SMENR    RTCAPBSMEN    LL_APB3_GRP1_EnableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClockStopSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB3SMENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB3SMENR, Periphs);
  (void)tmpreg;
}


/**
  * @brief  Check if APB3 peripheral clocks in Sleep and Stop modes is enabled or not
  * @rmtoll APB3SMENR    SYSCFGSMEN    LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    SPI3SMEN      LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    LPUART1SMEN   LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    I2C3SMEN      LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    LPTIM1SMEN    LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    LPTIM3SMEN    LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    LPTIM4SMEN    LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    OPAMPSMEN     LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    COMPSMEN      LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    VREFSMEN      LL_APB3_GRP1_IsEnabledClockStopSleep\n
  *         APB3SMENR    RTCAPBSMEN    LL_APB3_GRP1_IsEnabledClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClockStopSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB3SMENR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripheral clocks in Sleep and Stop modes
  * @rmtoll APB3SMENR    SYSCFGSMEN     LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    SPI3SMEN       LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    LPUART1SMEN    LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    I2C3SMEN       LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    LPTIM1SMEN     LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    LPTIM3SMEN     LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    LPTIM4SMEN     LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    OPAMPSMEN      LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    COMPSMEN       LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    VREFSMEN       LL_APB3_GRP1_DisableClockStopSleep\n
  *         APB3SMENR    RTCAPBSMEN     LL_APB3_GRP1_DisableClockStopSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClockStopSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB3SMENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_S2DAMR S2DAMR
  * @{
  */

/**
  * @brief  Enable SRDAMR peripheral clocks in autonomous mode
  * @rmtoll S2DAMR   SPI3AMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   LPUART1AMEN   LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   I2C3AMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   LPTIM1AMEN    LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   LPTIM3AMEN    LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   LPTIM4AMEN    LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   OPAMPAMEN     LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   COMPAMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   VREFAMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   VREFRST       LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   RTCAPBAMEN    LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   ADC4AMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   LPGPIO1AMEN   LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   DAC1AMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   LPDMA1AMEN    LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   ADF1AMEN      LL_SRDAMR_GRP1_EnableAutonomousClock\n
  *         S2DAMR   SRAM4AMEN     LL_SRDAMR_GRP1_EnableAutonomousClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ALL
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_SPI3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPUART1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_I2C3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM4AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_OPAMPAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_COMPAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_VREFAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_RTCAPBAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ADC4AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPGPIO1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_DAC1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPDMA1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ADF1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_SRAM4AMEN
   * @retval None
  */
__STATIC_INLINE void LL_SRDAMR_GRP1_EnableAutonomousClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->SRDAMR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->SRDAMR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if S2DAMR peripheral clock is enabled or not
  * @rmtoll S2DAMR   SPI3AMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   LPUART1AMEN   LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   I2C3AMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   LPTIM1AMEN    LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   LPTIM3AMEN    LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   LPTIM4AMEN    LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   OPAMPAMEN     LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   COMPAMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   VREFAMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   VREFRST       LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   RTCAPBAMEN    LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   ADC4AMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   LPGPIO1AMEN   LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   DAC1AMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   LPDMA1AMEN    LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   ADF1AMEN      LL_SRDAMR_GRP1_IsEnabledAutonomousClock\n
  *         S2DAMR   SRAM4AMEN     LL_SRDAMR_GRP1_IsEnabledAutonomousClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ALL
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_SPI3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPUART1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_I2C3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM4AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_OPAMPAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_COMPAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_VREFAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_RTCAPBAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ADC4AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPGPIO1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_DAC1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPDMA1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ADF1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_SRAM4AMEN
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SRDAMR_GRP1_IsEnabledAutonomousClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->SRDAMR, Periphs) == Periphs) ? 1UL : 0UL);
}

/**
  * @brief  Disable S2DAMR peripheral clocks in Sleep and Stop modes
  * @rmtoll S2DAMR   SPI3AMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   LPUART1AMEN   LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   I2C3AMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   LPTIM1AMEN    LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   LPTIM3AMEN    LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   LPTIM4AMEN    LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   OPAMPAMEN     LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   COMPAMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   VREFAMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   VREFRST       LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   RTCAPBAMEN    LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   ADC4AMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   LPGPIO1AMEN   LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   DAC1AMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   LPDMA1AMEN    LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   ADF1AMEN      LL_SRDAMR_GRP1_DisableAutonomousClock\n
  *         S2DAMR   SRAM4AMEN     LL_SRDAMR_GRP1_DisableAutonomousClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ALL
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_SPI3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPUART1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_I2C3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM3AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPTIM4AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_OPAMPAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_COMPAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_VREFAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_RTCAPBAMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ADC4AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPGPIO1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_DAC1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_LPDMA1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_ADF1AMEN
  *         @arg @ref LL_SRDAMR_GRP1_PERIPH_SRAM4AMEN
  * @retval None
  */
__STATIC_INLINE void LL_SRDAMR_GRP1_DisableAutonomousClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->SRDAMR, Periphs);
}
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
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_BUS_H */
