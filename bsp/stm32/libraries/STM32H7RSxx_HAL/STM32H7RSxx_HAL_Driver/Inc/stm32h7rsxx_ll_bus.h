/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_bus.h
  * @author  MCD Application Team
  * @brief   Header file of BUS LL module.
  *
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
  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB & APB peripherals, 1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_LL_BUS_H
#define STM32H7RSxx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */
#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

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
#define LL_AHB1_GRP1_PERIPH_GPDMA1         RCC_AHB1ENR_GPDMA1EN
#define LL_AHB1_GRP1_PERIPH_ADC12          RCC_AHB1ENR_ADC12EN
#define LL_AHB1_GRP1_PERIPH_ETH1MAC        RCC_AHB1ENR_ETH1MACEN
#define LL_AHB1_GRP1_PERIPH_ETH1TX         RCC_AHB1ENR_ETH1TXEN
#define LL_AHB1_GRP1_PERIPH_ETH1RX         RCC_AHB1ENR_ETH1RXEN
#define LL_AHB1_GRP1_PERIPH_USBOTGHS       RCC_AHB1ENR_OTGHSEN
#define LL_AHB1_GRP1_PERIPH_USBOTGFS       RCC_AHB1ENR_OTGFSEN
#define LL_AHB1_GRP1_PERIPH_USBPHYC        RCC_AHB1ENR_USBPHYCEN
#define LL_AHB1_GRP1_PERIPH_ADF1           RCC_AHB1ENR_ADF1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_PSSI           RCC_AHB2ENR_PSSIEN
#define LL_AHB2_GRP1_PERIPH_SDMMC2         RCC_AHB2ENR_SDMMC2EN
#define LL_AHB2_GRP1_PERIPH_CORDIC         RCC_AHB2ENR_CORDICEN
#define LL_AHB2_GRP1_PERIPH_AHBSRAM1       RCC_AHB2ENR_SRAM1EN
#define LL_AHB2_GRP1_PERIPH_AHBSRAM2       RCC_AHB2ENR_SRAM2EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB3_GRP1_PERIPH  AHB3 GRP1 PERIPH
  * @{
  */
#define LL_AHB3_GRP1_PERIPH_RNG            RCC_AHB3ENR_RNGEN
#define LL_AHB3_GRP1_PERIPH_HASH           RCC_AHB3ENR_HASHEN
#if defined(CRYP)
#define LL_AHB3_GRP1_PERIPH_CRYP           RCC_AHB3ENR_CRYPEN
#endif /* CRYP */
#if defined(SAES)
#define LL_AHB3_GRP1_PERIPH_SAES           RCC_AHB3ENR_SAESEN
#endif /* SAES */
#define LL_AHB3_GRP1_PERIPH_PKA            RCC_AHB3ENR_PKAEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_GRP1_PERIPH  AHB4 GRP1 PERIPH
  * @{
  */
#define LL_AHB4_GRP1_PERIPH_GPIOA          RCC_AHB4ENR_GPIOAEN
#define LL_AHB4_GRP1_PERIPH_GPIOB          RCC_AHB4ENR_GPIOBEN
#define LL_AHB4_GRP1_PERIPH_GPIOC          RCC_AHB4ENR_GPIOCEN
#define LL_AHB4_GRP1_PERIPH_GPIOD          RCC_AHB4ENR_GPIODEN
#define LL_AHB4_GRP1_PERIPH_GPIOE          RCC_AHB4ENR_GPIOEEN
#define LL_AHB4_GRP1_PERIPH_GPIOF          RCC_AHB4ENR_GPIOFEN
#define LL_AHB4_GRP1_PERIPH_GPIOG          RCC_AHB4ENR_GPIOGEN
#define LL_AHB4_GRP1_PERIPH_GPIOH          RCC_AHB4ENR_GPIOHEN
#define LL_AHB4_GRP1_PERIPH_GPIOM          RCC_AHB4ENR_GPIOMEN
#define LL_AHB4_GRP1_PERIPH_GPION          RCC_AHB4ENR_GPIONEN
#define LL_AHB4_GRP1_PERIPH_GPIOO          RCC_AHB4ENR_GPIOOEN
#define LL_AHB4_GRP1_PERIPH_GPIOP          RCC_AHB4ENR_GPIOPEN
#define LL_AHB4_GRP1_PERIPH_CRC            RCC_AHB4ENR_CRCEN
#define LL_AHB4_GRP1_PERIPH_BKPRAM         RCC_AHB4ENR_BKPRAMEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB5_GRP1_PERIPH  AHB5 GRP1 PERIPH
  * @{
  */
#define LL_AHB5_GRP1_PERIPH_HPDMA1         RCC_AHB5ENR_HPDMA1EN
#define LL_AHB5_GRP1_PERIPH_DMA2D          RCC_AHB5ENR_DMA2DEN
#define LL_AHB5_GRP1_PERIPH_JPEG           RCC_AHB5ENR_JPEGEN
#define LL_AHB5_GRP1_PERIPH_FMC            RCC_AHB5ENR_FMCEN
#define LL_AHB5_GRP1_PERIPH_XSPI1          RCC_AHB5ENR_XSPI1EN
#define LL_AHB5_GRP1_PERIPH_XSPI2          RCC_AHB5ENR_XSPI2EN
#define LL_AHB5_GRP1_PERIPH_XSPIM          RCC_AHB5ENR_XSPIMEN
#define LL_AHB5_GRP1_PERIPH_SDMMC1         RCC_AHB5ENR_SDMMC1EN
#define LL_AHB5_GRP1_PERIPH_GFXMMU         RCC_AHB5ENR_GFXMMUEN
#if defined(GPU2D)
#define LL_AHB5_GRP1_PERIPH_GPU2D          RCC_AHB5ENR_GPU2DEN
#endif /* GPU2D */

#define LL_AHB5_GRP1_PERIPH_FLASH          RCC_AHB5LPENR_FLASHLPEN
#define LL_AHB5_GRP1_PERIPH_AXISRAM        RCC_AHB5LPENR_AXISRAMLPEN
#define LL_AHB5_GRP1_PERIPH_DTCM1          RCC_AHB5LPENR_DTCM1LPEN
#define LL_AHB5_GRP1_PERIPH_DTCM2          RCC_AHB5LPENR_DTCM2LPEN
#define LL_AHB5_GRP1_PERIPH_ITCM           RCC_AHB5LPENR_ITCMLPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_TIM2           RCC_APB1ENR1_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3           RCC_APB1ENR1_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM4           RCC_APB1ENR1_TIM4EN
#define LL_APB1_GRP1_PERIPH_TIM5           RCC_APB1ENR1_TIM5EN
#define LL_APB1_GRP1_PERIPH_TIM6           RCC_APB1ENR1_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7           RCC_APB1ENR1_TIM7EN
#define LL_APB1_GRP1_PERIPH_TIM12          RCC_APB1ENR1_TIM12EN
#define LL_APB1_GRP1_PERIPH_TIM13          RCC_APB1ENR1_TIM13EN
#define LL_APB1_GRP1_PERIPH_TIM14          RCC_APB1ENR1_TIM14EN
#define LL_APB1_GRP1_PERIPH_LPTIM1         RCC_APB1ENR1_LPTIM1EN
#define LL_APB1_GRP1_PERIPH_WWDG           RCC_APB1ENR1_WWDGEN
#define LL_APB1_GRP1_PERIPH_SPI2           RCC_APB1ENR1_SPI2EN
#define LL_APB1_GRP1_PERIPH_SPI3           RCC_APB1ENR1_SPI3EN
#define LL_APB1_GRP1_PERIPH_SPDIFRX        RCC_APB1ENR1_SPDIFRXEN
#define LL_APB1_GRP1_PERIPH_USART2         RCC_APB1ENR1_USART2EN
#define LL_APB1_GRP1_PERIPH_USART3         RCC_APB1ENR1_USART3EN
#define LL_APB1_GRP1_PERIPH_UART4          RCC_APB1ENR1_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5          RCC_APB1ENR1_UART5EN
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_APB1ENR1_I2C1_I3C1EN
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_APB1ENR1_I2C2EN
#define LL_APB1_GRP1_PERIPH_I2C3           RCC_APB1ENR1_I2C3EN
#define LL_APB1_GRP1_PERIPH_I3C1           RCC_APB1ENR1_I2C1_I3C1EN
#define LL_APB1_GRP1_PERIPH_CEC            RCC_APB1ENR1_CECEN
#define LL_APB1_GRP1_PERIPH_UART7          RCC_APB1ENR1_UART7EN
#define LL_APB1_GRP1_PERIPH_UART8          RCC_APB1ENR1_UART8EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_CRS            RCC_APB1ENR2_CRSEN
#define LL_APB1_GRP2_PERIPH_MDIOS          RCC_APB1ENR2_MDIOSEN
#define LL_APB1_GRP2_PERIPH_FDCAN          RCC_APB1ENR2_FDCANEN
#define LL_APB1_GRP2_PERIPH_UCPD1          RCC_APB1ENR2_UCPD1EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_USART1         RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#define LL_APB2_GRP1_PERIPH_SPI4           RCC_APB2ENR_SPI4EN
#define LL_APB2_GRP1_PERIPH_TIM15          RCC_APB2ENR_TIM15EN
#define LL_APB2_GRP1_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
#define LL_APB2_GRP1_PERIPH_TIM9           RCC_APB2ENR_TIM9EN
#define LL_APB2_GRP1_PERIPH_SPI5           RCC_APB2ENR_SPI5EN
#define LL_APB2_GRP1_PERIPH_SAI1           RCC_APB2ENR_SAI1EN
#define LL_APB2_GRP1_PERIPH_SAI2           RCC_APB2ENR_SAI2EN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB4_GRP1_PERIPH  APB4 GRP1 PERIPH
  * @{
  */
#define LL_APB4_GRP1_PERIPH_SBS            RCC_APB4ENR_SBSEN
#define LL_APB4_GRP1_PERIPH_LPUART1        RCC_APB4ENR_LPUART1EN
#define LL_APB4_GRP1_PERIPH_SPI6           RCC_APB4ENR_SPI6EN
#define LL_APB4_GRP1_PERIPH_LPTIM2         RCC_APB4ENR_LPTIM2EN
#define LL_APB4_GRP1_PERIPH_LPTIM3         RCC_APB4ENR_LPTIM3EN
#define LL_APB4_GRP1_PERIPH_LPTIM4         RCC_APB4ENR_LPTIM4EN
#define LL_APB4_GRP1_PERIPH_LPTIM5         RCC_APB4ENR_LPTIM5EN
#define LL_APB4_GRP1_PERIPH_VREF           RCC_APB4ENR_VREFEN
#define LL_APB4_GRP1_PERIPH_RTCAPB         RCC_APB4ENR_RTCAPBEN
#define LL_APB4_GRP1_PERIPH_DTS            RCC_APB4ENR_DTSEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB5_GRP1_PERIPH  APB5 GRP1 PERIPH
  * @{
  */
#if defined(LTDC)
#define LL_APB5_GRP1_PERIPH_LTDC           RCC_APB5ENR_LTDCEN
#endif /* LTDC */
#define LL_APB5_GRP1_PERIPH_DCMIPP         RCC_APB5ENR_DCMIPPEN
#define LL_APB5_GRP1_PERIPH_GFXTIM         RCC_APB5ENR_GFXTIMEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_CKGA_PERIPH  CKGA (AXI Clocks Gating) PERIPH
  * @{
  */
#define LL_CKGA_PERIPH_AXI                 RCC_CKGDISR_AXICKG
#define LL_CKGA_PERIPH_AHBM                RCC_CKGDISR_AHBMCKG
#define LL_CKGA_PERIPH_SDMMC1              RCC_CKGDISR_SDMMC1CKG
#define LL_CKGA_PERIPH_HPDMA1              RCC_CKGDISR_HPDMA1CKG
#define LL_CKGA_PERIPH_CPU                 RCC_CKGDISR_CPUCKG
#if defined(GPU2D)
#define LL_CKGA_PERIPH_GPU2DS1             RCC_CKGDISR_GPU2DS1CKG
#define LL_CKGA_PERIPH_GPU2DS0             RCC_CKGDISR_GPU2DS0CKG
#define LL_CKGA_PERIPH_GPU2DCL             RCC_CKGDISR_GPU2DCLCKG
#endif /* GPU2D */
#define LL_CKGA_PERIPH_DCMIPP              RCC_CKGDISR_DCMIPPCKG
#define LL_CKGA_PERIPH_DMA2D               RCC_CKGDISR_DMA2DCKG
#define LL_CKGA_PERIPH_GFXMMUS             RCC_CKGDISR_GFXMMUSCKG
#if defined(LTDC)
#define LL_CKGA_PERIPH_LTDC                RCC_CKGDISR_LTDCCKG
#endif /* LTDC */
#define LL_CKGA_PERIPH_GFXMMUM             RCC_CKGDISR_GFXMMUMCKG
#define LL_CKGA_PERIPH_AHBS                RCC_CKGDISR_AHBSCKG
#define LL_CKGA_PERIPH_FMC                 RCC_CKGDISR_FMCCKG
#define LL_CKGA_PERIPH_XSPI1               RCC_CKGDISR_XSPI1CKG
#define LL_CKGA_PERIPH_XSPI2               RCC_CKGDISR_XSPI2CKG
#define LL_CKGA_PERIPH_AXIRAM1             RCC_CKGDISR_AXISRAM1CKG
#define LL_CKGA_PERIPH_AXIRAM2             RCC_CKGDISR_AXISRAM2CKG
#define LL_CKGA_PERIPH_AXIRAM3             RCC_CKGDISR_AXISRAM3CKG
#define LL_CKGA_PERIPH_AXIRAM4             RCC_CKGDISR_AXISRAM4CKG
#define LL_CKGA_PERIPH_FLASH               RCC_CKGDISR_FLASHCKG
#define LL_CKGA_PERIPH_EXTI                RCC_CKGDISR_EXTICKG
#define LL_CKGA_PERIPH_JTAG                RCC_CKGDISR_JTAGCKG
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
  * @rmtoll AHB1ENR      GPDMA1EN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ADC12EN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ETH1MACEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ETH1TXEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ETH1RXEN      LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      OTGFSEN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      OTGHSEN       LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      USBPHYCEN     LL_AHB1_GRP1_EnableClock\n
  *         AHB1ENR      ADF1EN        LL_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
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
  * @rmtoll AHB1ENR      GPDMA1EN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ADC12EN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ETH1MACEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ETH1TXEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ETH1RXEN      LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      OTGHSEN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      OTGFSEN       LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      USBPHYCEN     LL_AHB1_GRP1_IsEnabledClock\n
  *         AHB1ENR      ADF1EN        LL_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB1ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHB1ENR      GPDMA1EN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ADC12EN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ETH1MACEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ETH1TXEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ETH1RXEN      LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      OTGHSEN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      OTGFSEN       LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      USBPHYCEN     LL_AHB1_GRP1_DisableClock\n
  *         AHB1ENR      ADF1EN        LL_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHB1RSTR     GPDMA1RST     LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     ADC12RST      LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     ETH1RST       LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     OTGHSRST      LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     OTGFSRST      LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     USBPHYCRST    LL_AHB1_GRP1_ForceReset\n
  *         AHB1RSTR     ADF1RST       LL_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHB1RSTR     GPDMA1RST     LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     ADC12RST      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     ETH1RST       LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     OTGHSRST      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     OTGFSRST      LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     USBPHYCRST    LL_AHB1_GRP1_ReleaseReset\n
  *         AHB1RSTR     ADF1RST       LL_AHB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

/**
  * @brief  Enable AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB1LPENR    GPDMA1LPEN    LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ADC12LPEN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ETH1MACLPEN   LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ETH1TXLPEN    LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ETH1RXLPEN    LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    OTGHSLPEN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    OTGFSLPEN     LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    USBPHYCLPEN   LL_AHB1_GRP1_EnableClockSleep\n
  *         AHB1LPENR    ADF1LPEN      LL_AHB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB1LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB1LPENR    GPDMA1LPEN    LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ADC12LPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ETH1MACLPEN   LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ETH1TXLPEN    LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ETH1RXLPEN    LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    OTGHSLPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    OTGHSLPEN     LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    USBPHYCLPEN   LL_AHB1_GRP1_DisableClockSleep\n
  *         AHB1LPENR    ADF1LPEN      LL_AHB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGHS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBOTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_USBPHYC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2 AHB2
  * @{
  */

/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      PSSIEN        LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      SDMMC2EN      LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      CORDICEN      LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      AHBSRAM1EN    LL_AHB2_GRP1_EnableClock\n
  *         AHB2ENR      AHBSRAM2EN    LL_AHB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
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
  * @rmtoll AHB2ENR      PSSIEN        LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      SDMMC2EN      LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      CORDICEN      LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      AHBSRAM1EN    LL_AHB2_GRP1_IsEnabledClock\n
  *         AHB2ENR      AHBSRAM2EN    LL_AHB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB2ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll AHB2ENR      PSSIEN        LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      SDMMC2EN      LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      CORDICEN      LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      AHBSRAM1EN    LL_AHB2_GRP1_DisableClock\n
  *         AHB2ENR      AHBSRAM2EN    LL_AHB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTR     PSSIRST        LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     SDMMC2RST      LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTR     CORDICRST      LL_AHB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTR     PSSIRST        LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     SDMMC2RST      LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTR     CORDICRST      LL_AHB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR, Periphs);
}

/**
  * @brief  Enable AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB2LPENR    PSSILPEN      LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    SDMMC2LPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    CORDICLPEN    LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    AHBSRAM1LPEN  LL_AHB2_GRP1_EnableClockSleep\n
  *         AHB2LPENR    AHBSRAM2LPEN  LL_AHB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB2LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB2LPENR    PSSILPEN      LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    SDMMC2LPEN    LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    CORDICLPEN    LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    AHBSRAM1LPEN  LL_AHB2_GRP1_DisableClockSleep\n
  *         AHB2LPENR    AHBSRAM2LPEN  LL_AHB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_PSSI
  *         @arg @ref LL_AHB2_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB3 AHB3
  * @{
  */

/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      RNGEN         LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      HASHEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      CRYPEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      SAESEN        LL_AHB3_GRP1_EnableClock\n
  *         AHB3ENR      PKAEN         LL_AHB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
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
  * @rmtoll AHB3ENR      RNGEN         LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      HASHEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      CRYPEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      SAESEN        LL_AHB3_GRP1_IsEnabledClock\n
  *         AHB3ENR      PKAEN         LL_AHB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB3ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB3 peripherals clock.
  * @rmtoll AHB3ENR      RNGEN         LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      HASHEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      CRYPEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      SAESEN        LL_AHB3_GRP1_DisableClock\n
  *         AHB3ENR      PKAEN         LL_AHB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3ENR, Periphs);
}

/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll AHB3RSTR     RNGRST        LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     HASHRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     CRYPRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     SAESRST       LL_AHB3_GRP1_ForceReset\n
  *         AHB3RSTR     PKARST        LL_AHB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Release AHB3 peripherals reset.
  * @rmtoll AHB3RSTR     RNGRST        LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     HASHRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     CRYPRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     SAESRST       LL_AHB3_GRP1_ReleaseReset\n
  *         AHB3RSTR     PKARST        LL_AHB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3RSTR, Periphs);
}

/**
  * @brief  Enable AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB3LPENR    RNGLPEN       LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    HASHLPEN      LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    CRYPLPEN      LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    SAESLPEN      LL_AHB3_GRP1_EnableClockSleep\n
  *         AHB3LPENR    PKALPEN       LL_AHB3_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB3LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB3 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB3LPENR    RNGLPEN       LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    HASHLPEN      LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    CRYPLPEN      LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    SAESLPEN      LL_AHB3_GRP1_DisableClockSleep\n
  *         AHB3LPENR    PKALPEN       LL_AHB3_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_CRYP (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB3_GRP1_PERIPH_PKA
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4 AHB4
  * @{
  */

/**
  * @brief  Enable AHB4 peripherals clock.
  * @rmtoll AHB4ENR      GPIOAEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOBEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOCEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIODEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOEEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOFEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOGEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOHEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOMEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIONEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOOEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      GPIOPEN       LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      CRCEN         LL_AHB4_GRP1_EnableClock\n
  *         AHB4ENR      BKPRAMEN      LL_AHB4_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB4ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB4ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clock is enabled or not
  * @rmtoll AHB4ENR      GPIOAEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOBEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOCEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIODEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOEEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOFEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOGEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOHEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOMEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIONEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOOEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      GPIOPEN       LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      CRCEN         LL_AHB4_GRP1_IsEnabledClock\n
  *         AHB4ENR      BKPRAMEN      LL_AHB4_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB4ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB4 peripherals clock.
  * @rmtoll AHB4ENR      GPIOAEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOBEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOCEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIODEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOEEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOFEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOGEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOHEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOMEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIONEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOOEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      GPIOPEN       LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      CRCEN         LL_AHB4_GRP1_DisableClock\n
  *         AHB4ENR      BKPRAMEN      LL_AHB4_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4ENR, Periphs);
}

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll AHB4RSTR     GPIOARST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOBRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOCRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIODRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOERST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOFRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOGRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOHRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOMRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIONRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOORST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     GPIOPRST      LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     CRCRST        LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTR     BKPRAMRST     LL_AHB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB4RSTR, Periphs);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll AHB4RSTR     GPIOARST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOBRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOCRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIODRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOERST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOFRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOGRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOHRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOMRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIONRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOORST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     GPIOPRST      LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTR     CRCRST        LL_AHB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4RSTR, Periphs);
}

/**
  * @brief  Enable AHB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB4LPENR    GPIOALPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOBLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOCLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIODLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOELPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOFLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOGLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOHLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOMLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIONLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOOLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    GPIOPLPEN     LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    CRCLPEN       LL_AHB4_GRP1_EnableClockSleep\n
  *         AHB4LPENR    BKPRAMLPEN    LL_AHB4_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB4LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB4LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB4LPENR    GPIOALPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOBLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOCLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIODLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOELPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOFLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOGLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOHLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOMLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIONLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOOLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    GPIOPLPEN     LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    CRCLPEN       LL_AHB4_GRP1_DisableClockSleep\n
  *         AHB4LPENR    BKPRAMLPEN    LL_AHB4_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOM
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPION
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOO
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOP
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB4LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB5 AHB5
  * @{
  */

/**
  * @brief  Enable AHB5 peripherals clock.
  * @rmtoll AHB5ENR      HPDMA1EN      LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      DMA2DEN       LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      JPEGEN        LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      FMCEN         LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      XSPI1EN       LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      XSPI2EN       LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      XSPIMEN       LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      SDMMC1EN      LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      GFXMMUEN      LL_AHB5_GRP1_EnableClock\n
  *         AHB5ENR      GPU2DEN       LL_AHB5_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB5ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB5ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB5 peripheral clock is enabled or not
  * @rmtoll AHB5ENR      HPDMA1EN      LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      DMA2DEN       LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      JPEGEN        LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      FMCEN         LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      XSPI1EN       LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      XSPI2EN       LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      XSPIMEN       LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      SDMMC1EN      LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      GFXMMUEN      LL_AHB5_GRP1_IsEnabledClock\n
  *         AHB5ENR      GPU2DEN       LL_AHB5_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_AHB5_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->AHB5ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB5 peripherals clock.
  * @rmtoll AHB5ENR      HPDMA1EN      LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      DMA2DEN       LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      JPEGEN        LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      FMCEN         LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      XSPI1EN       LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      XSPI2EN       LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      XSPIMEN       LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      SDMMC1EN      LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      GFXMMUEN      LL_AHB5_GRP1_DisableClock\n
  *         AHB5ENR      GPU2DEN       LL_AHB5_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB5ENR, Periphs);
}

/**
  * @brief  Force AHB5 peripherals reset.
  * @rmtoll AHB5RSTR     HPDMA1RST     LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     DMA2DRST      LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     JPEGRST       LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     FMCRST        LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     XSPI1RST      LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     XSPI2RST      LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     XSPIMRST      LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     SDMMC1RST     LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     GFXMMURST     LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTR     GPU2DRST      LL_AHB5_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB5RSTR, Periphs);
}

/**
  * @brief  Release AHB5 peripherals reset.
  * @rmtoll AHB5RSTR     HPDMA1RST     LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     DMA2DRST      LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     JPEGRST       LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     FMCRST        LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     XSPI1RST      LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     XSPI2RST      LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     XSPIMRST      LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     SDMMC1RST     LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     GFXMMURST     LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTR     GPU2DRST      LL_AHB5_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB5RSTR, Periphs);
}

/**
  * @brief  Enable AHB5 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB5LPENR    HPDMA1LPEN    LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    DMA2DLPEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    JPEGLPEN      LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    FMCLPEN       LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    XSPI1LPEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    XSPI2LPEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    XSPIMLPEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    SDMMC1LPEN    LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    GFXMMULPEN    LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    GPU2DLPEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    AXISRAMPLEN   LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    DTCM1PLEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    DTCM2PLEN     LL_AHB5_GRP1_EnableClockSleep\n
  *         AHB5LPENR    ITCMPLEN      LL_AHB5_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXISRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ITCM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB5LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHB5LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB5 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll AHB5LPENR    HPDMA1LPEN    LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    DMA2DLPEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    FLASHLPEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    JPEGLPEN      LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    FMCLPEN       LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    XSPI1LPEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    XSPI2LPEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    XSPIMLPEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    SDMMC1LPEN    LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    GFXMMULPEN    LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    GPU2DLPEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    AXISRAMPLEN   LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    DTCM1PLEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    DTCM2PLEN     LL_AHB5_GRP1_DisableClockSleep\n
  *         AHB5LPENR    ITCMPLEN      LL_AHB5_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DMA2D
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB5_GRP1_PERIPH_JPEG (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPIM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GFXMMU (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_GPU2D (*)
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXISRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ITCM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB5LPENR, Periphs);
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
  *         APB1ENR1     TIM12EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM13EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     TIM14EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     LPTIM1EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPI3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     SPDIFRXEN     LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I2C3EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     I3C1EN        LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     CECEN         LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART7EN       LL_APB1_GRP1_EnableClock\n
  *         APB1ENR1     UART8EN       LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
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
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM5EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM12EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM13EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     TIM14EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     LPTIM1EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     WWDGEN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPI3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     SPDIFRXEN     LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I2C3EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     I3C1EN        LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     CECEN         LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART7EN       LL_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR1     UART8EN       LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR1, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR1     TIM2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM4EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM5EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM6EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM7EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM12EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM13EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     TIM14EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     LPTIM1EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPI3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     SPDIFRXEN     LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART2EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     USART3EN      LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART4EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART5EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C2EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I2C3EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     I3C1EN        LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     CECEN         LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART7EN       LL_APB1_GRP1_DisableClock\n
  *         APB1ENR1     UART8EN       LL_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR1, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR1    TIM2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM4RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM5RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM6RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM7RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM12RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM13RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    TIM14RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    LPTIM1RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    WWDGRST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    SPI2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    SPI3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    SPDIFRXRST    LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    USART2RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    USART3RST     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    UART4RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    UART5RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I2C1RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I2C2RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I2C3RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    I3C1RST       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    CECRST        LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    UART7RST      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTR1    UART8RST      LL_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR1    TIM2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM4RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM5RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM6RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM7RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM12RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM13RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    TIM14RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    LPTIM1RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    WWDGRST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    SPI2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    SPI3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    SPDIFRXRST    LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    USART2RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    USART3RST     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    UART4RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    UART5RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I2C1RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I2C2RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I2C3RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    I3C1RST       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    CECRST        LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    UART7RST      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR1    UART8RST      LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR1, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1LPENR1   TIM2LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM3LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM4LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM5LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM6LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM7LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM12LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM13LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   TIM14LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   LPTIM1LPEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   WWDGLPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   SPI2LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   SPI3LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   SPDIFRXLPEN   LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   USART2LPEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   USART3LPEN    LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   UART4LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   UART5LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   I2C1LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   I2C2LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   I2C3LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   I3C1LPEN      LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   CECLPEN       LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   DAC12LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   UART7LPEN     LL_APB1_GRP1_EnableClockSleep\n
  *         APB1LPENR1   UART8LPEN     LL_APB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1LPENR1, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1LPENR1, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1LPENR1   TIM2LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM3LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM4LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM5LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM6LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM7LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM12LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM13LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   TIM14LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   LPTIM1LPEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   WWDGLPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   SPI2LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   SPI3LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   SPDIFRXLPEN   LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   USART2LPEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   USART3LPEN    LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   UART4LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   UART5LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   I2C1LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   I2C2LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   I2C3LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   I3C1LPEN      LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   CECLPEN       LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   UART7LPEN     LL_APB1_GRP1_DisableClockSleep\n
  *         APB1LPENR1   UART8LPEN     LL_APB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIFRX
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CEC
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LPENR1, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll APB1ENR2     CRSEN         LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     MDIOSEN       LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     FDCANEN       LL_APB1_GRP2_EnableClock\n
  *         APB1ENR2     UCPD1EN       LL_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
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
  * @rmtoll APB1ENR2     CRSEN         LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     MDIOSEN       LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     FDCANEN       LL_APB1_GRP2_IsEnabledClock\n
  *         APB1ENR2     UCPD1EN       LL_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB1ENR2, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll APB1ENR2     CRSEN         LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     MDIOSEN       LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     FDCANEN       LL_APB1_GRP2_DisableClock\n
  *         APB1ENR2     UCPD1EN       LL_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR2, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTR2    CRSRST        LL_APB1_GRP2_ForceReset\n
  *         APB1ENR2     MDIOSRST      LL_APB1_GRP2_ForceReset\n
  *         APB1ENR2     FDCANRST      LL_APB1_GRP2_ForceReset\n
  *         APB1ENR2     UCPD1RST      LL_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTR2    CRSRST        LL_APB1_GRP2_ReleaseReset\n
  *         APB1ENR2     MDIOSRST      LL_APB1_GRP2_ReleaseReset\n
  *         APB1ENR2     FDCANRST      LL_APB1_GRP2_ReleaseReset\n
  *         APB1ENR2     UCPD1RST      LL_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR2, Periphs);
}

/**
  * @brief  Enable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1LPENR2   CRSLPEN       LL_APB1_GRP2_EnableClockSleep\n
  *         APB1LPENR2   MDIOSLPEN     LL_APB1_GRP2_EnableClockSleep\n
  *         APB1LPENR2   FDCANLPEN     LL_APB1_GRP2_EnableClockSleep\n
  *         APB1LPENR2   UCPD1LPEN     LL_APB1_GRP2_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1LPENR2, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1LPENR2, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB1 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB1LPENR2   CRSLPEN       LL_APB1_GRP2_DisableClockSleep\n
  *         APB1LPENR2   MDIOSLPEN     LL_APB1_GRP2_DisableClockSleep\n
  *         APB1LPENR2   FDCANLPEN     LL_APB1_GRP2_DisableClockSleep\n
  *         APB1LPENR2   UCPD1LPEN     LL_APB1_GRP2_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_MDIOS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LPENR2, Periphs);
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
  *         APB2ENR      USART1EN      LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI4EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      TIM9EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SPI5EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_EnableClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
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
  *         APB2ENR      USART1EN      LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI4EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      TIM9EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SPI5EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_IsEnabledClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB2ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll APB2ENR      TIM1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      USART1EN      LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI4EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM15EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM16EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM17EN       LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      TIM9EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SPI5EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI1EN        LL_APB2_GRP1_DisableClock\n
  *         APB2ENR      SAI2EN        LL_APB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
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
  * @rmtoll APB2RSTR     TIM1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     USART1RST     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI4RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM15RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM16RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM17RST      LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     TIM9RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SPI5RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SAI1RST       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTR     SAI2RST       LL_APB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
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
  * @rmtoll APB2RSTR     TIM1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     USART1RST     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI4RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM15RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM16RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM17RST      LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     TIM9RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SPI5RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SAI1RST       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTR     SAI2RST       LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Enable APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB2LPENR    TIM1LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    USART1LPEN    LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SPI1LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SPI4LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM15LPEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM16LPEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM17LPEN     LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    TIM9LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SPI5LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SAI1LPEN      LL_APB2_GRP1_EnableClockSleep\n
  *         APB2LPENR    SAI2LPEN      LL_APB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB2 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB2LPENR    TIM1LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    USART1LPEN    LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SPI1LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SPI4LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM15LPEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM16LPEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM17LPEN     LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    TIM9LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SPI5LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SAI1LPEN      LL_APB2_GRP1_DisableClockSleep\n
  *         APB2LPENR    SAI2LPEN      LL_APB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4 APB4
  * @{
  */

/**
  * @brief  Enable APB4 peripherals clock.
  * @rmtoll APB4ENR      SBSEN         LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPUART1EN     LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      SPI6EN        LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM2EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM3EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM4EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      LPTIM5EN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      VREFEN        LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      RTCAPBEN      LL_APB4_GRP1_EnableClock\n
  *         APB4ENR      DTSEN         LL_APB4_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB4ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB4ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB4 peripheral clock is enabled or not
  * @rmtoll APB4ENR      SBSEN         LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPUART1EN     LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      SPI6EN        LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM2EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM3EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM4EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      LPTIM5EN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      VREFEN        LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      RTCAPBEN      LL_APB4_GRP1_IsEnabledClock\n
  *         APB4ENR      DTSEN         LL_APB4_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB4_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB4ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB4 peripherals clock.
  * @rmtoll APB4ENR      SBSEN         LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPUART1EN     LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      SPI6EN        LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM2EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM3EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM4EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      LPTIM5EN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      VREFEN        LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      RTCAPBEN      LL_APB4_GRP1_DisableClock\n
  *         APB4ENR      DTSEN         LL_APB4_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB4ENR, Periphs);
}

/**
  * @brief  Force APB4 peripherals reset.
  * @rmtoll APB4RSTR     SBSRST        LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPUART1RST    LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     SPI6RST       LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM2RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM3RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM4RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     LPTIM5RST     LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     VREFRST       LL_APB4_GRP1_ForceReset\n
  *         APB4RSTR     DTSRST        LL_APB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB4RSTR, Periphs);
}

/**
  * @brief  Release APB4 peripherals reset.
  * @rmtoll APB4RSTR     SBSRST        LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPUART1RST    LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     SPI6RST       LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM2RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM3RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM4RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     LPTIM5RST     LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     VREFRST       LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTR     DTSRST        LL_APB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB4RSTR, Periphs);
}

/**
  * @brief  Enable APB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB4LPENR    SBSLPEN       LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPUART1LPEN   LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    SPI6LPEN      LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM2LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM3LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM4LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    LPTIM5LPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    VREFLPEN      LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    RTCAPBLPEN    LL_APB4_GRP1_EnableClockSleep\n
  *         APB4LPENR    DTSLPEN       LL_APB4_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB4LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB4LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB4 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB4LPENR    SBSLPEN       LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPUART1LPEN   LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    SPI6LPEN      LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM2LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM3LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM4LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    LPTIM5LPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    VREFLPEN      LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    RTCAPBLPEN    LL_APB4_GRP1_DisableClockSleep\n
  *         APB4LPENR    DTSLPEN       LL_APB4_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB4LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB5 APB5
  * @{
  */

/**
  * @brief  Enable APB5 peripherals clock.
  * @rmtoll APB5ENR      LTDCEN        LL_APB5_GRP1_EnableClock\n
  *         APB5ENR      DCMIPPEN      LL_APB5_GRP1_EnableClock\n
  *         APB5ENR      GFXTIMEN      LL_APB5_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB5ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB5ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB5 peripheral clock is enabled or not
  * @rmtoll APB5ENR      LTDCEN        LL_APB5_GRP1_IsEnabledClock\n
  *         APB5ENR      DCMIPPEN      LL_APB5_GRP1_IsEnabledClock\n
  *         APB5ENR      GFXTIMEN      LL_APB5_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_APB5_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->APB5ENR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB5 peripherals clock.
  * @rmtoll APB5ENR      LTDCEN        LL_APB5_GRP1_DisableClock\n
  *         APB5ENR      DCMIPPEN      LL_APB5_GRP1_DisableClock\n
  *         APB5ENR      GFXTIMEN      LL_APB5_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB5ENR, Periphs);
}

/**
  * @brief  Force APB5 peripherals reset.
  * @rmtoll APB5RSTR     LTDCRST       LL_APB5_GRP1_ForceReset\n
  *         APB5RSTR     DCMIPPRST     LL_APB5_GRP1_ForceReset\n
  *         APB5RSTR     GFXTIMRST     LL_APB5_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB5RSTR, Periphs);
}

/**
  * @brief  Release APB5 peripherals reset.
  * @rmtoll APB5RSTR     LTDCRST       LL_APB5_GRP1_ReleaseReset\n
  *         APB5RSTR     DCMIPPRST     LL_APB5_GRP1_ForceReset\n
  *         APB5RSTR     GFXTIMRST     LL_APB5_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB5RSTR, Periphs);
}

/**
  * @brief  Enable APB5 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB5LPENR    LTDCLPEN      LL_APB5_GRP1_EnableClockSleep\n
  *         APB5LPENR    DCMIPPLPEN    LL_APB5_GRP1_EnableClockSleep\n
  *         APB5LPENR    GFXTIMLPEN    LL_APB5_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB5LPENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB5LPENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB5 peripherals clock during Low Power (Sleep) mode.
  * @rmtoll APB5LPENR    LTDCLPEN      LL_APB5_GRP1_DisableClockSleep\n
  *         APB5LPENR    DCMIPPLPEN    LL_APB5_GRP1_DisableClockSleep\n
  *         APB5LPENR    GFXTIMLPEN    LL_APB5_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_LTDC (*)
  *         @arg @ref LL_APB5_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB5_GRP1_PERIPH_GFXTIM
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_DisableClockSleep(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB5LPENR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_CKGA CKGA (AXI Clocks Gating)
  * @{
  */

/**
  * @brief  Enable clock gating for AXI bus peripherals.
  * @rmtoll CKGDISR      AXICKG      LL_CKGA_Enable\n
  *         CKGDISR      AHBMCKG     LL_CKGA_Enable\n
  *         CKGDISR      SDMMC1CKG   LL_CKGA_Enable\n
  *         CKGDISR      HPDMA1CKG   LL_CKGA_Enable\n
  *         CKGDISR      CPUCKG      LL_CKGA_Enable\n
  *         CKGDISR      GPU2DS0CKG  LL_CKGA_Enable\n
  *         CKGDISR      GPU2DS1CKG  LL_CKGA_Enable\n
  *         CKGDISR      GPUCLCKG    LL_CKGA_Enable\n
  *         CKGDISR      DCMIPPCKG   LL_CKGA_Enable\n
  *         CKGDISR      DMA2DCKG    LL_CKGA_Enable\n
  *         CKGDISR      GFXMMUSCKG  LL_CKGA_Enable\n
  *         CKGDISR      LTDCCKG     LL_CKGA_Enable\n
  *         CKGDISR      GFXMMUMCKG  LL_CKGA_Enable\n
  *         CKGDISR      AHBSCKG     LL_CKGA_Enable\n
  *         CKGDISR      FMCCKG      LL_CKGA_Enable\n
  *         CKGDISR      XSPI2CKG    LL_CKGA_Enable\n
  *         CKGDISR      XSPI1CKG    LL_CKGA_Enable\n
  *         CKGDISR      AXIRAM1CKG  LL_CKGA_Enable\n
  *         CKGDISR      AXIRAM2CKG  LL_CKGA_Enable\n
  *         CKGDISR      AXIRAM3CKG  LL_CKGA_Enable\n
  *         CKGDISR      AXIRAM4CKG  LL_CKGA_Enable\n
  *         CKGDISR      FLASHCKG    LL_CKGA_Enable\n
  *         CKGDISR      EXTICKG     LL_CKGA_Enable\n
  *         CKGDISR      JTAGCKG     LL_CKGA_Enable
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CKGA_PERIPH_AXI
  *         @arg @ref LL_CKGA_PERIPH_AHBM
  *         @arg @ref LL_CKGA_PERIPH_AHBS
  *         @arg @ref LL_CKGA_PERIPH_SDMMC1
  *         @arg @ref LL_CKGA_PERIPH_HPDMA1
  *         @arg @ref LL_CKGA_PERIPH_CPU
  *         @arg @ref LL_CKGA_PERIPH_GPU2DS0 (*)
  *         @arg @ref LL_CKGA_PERIPH_GPU2DS1 (*)
  *         @arg @ref LL_CKGA_PERIPH_GPU2DCL (*)
  *         @arg @ref LL_CKGA_PERIPH_DMA2D
  *         @arg @ref LL_CKGA_PERIPH_DCMIPP
  *         @arg @ref LL_CKGA_PERIPH_LTDC (*)
  *         @arg @ref LL_CKGA_PERIPH_FLASH
  *         @arg @ref LL_CKGA_PERIPH_XSPI2
  *         @arg @ref LL_CKGA_PERIPH_XSPI1
  *         @arg @ref LL_CKGA_PERIPH_FMC
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM1
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM2
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM3
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM4
  *         @arg @ref LL_CKGA_PERIPH_GFXMMUM
  *         @arg @ref LL_CKGA_PERIPH_GFXMMUS
  *         @arg @ref LL_CKGA_PERIPH_EXTI
  *         @arg @ref LL_CKGA_PERIPH_JTAG
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_CKGA_Enable(uint32_t Periphs)
{
  CLEAR_BIT(RCC->CKGDISR, Periphs);
}

/**
  * @brief  Check if AXI bus peripherals clock gating is enabled or not
  * @rmtoll CKGDISR      AXICKG      LL_CKGA_IsEnabledClock\n
  *         CKGDISR      AHBMCKG     LL_CKGA_IsEnabledClock\n
  *         CKGDISR      SDMMC1CKG   LL_CKGA_IsEnabledClock\n
  *         CKGDISR      HPDMA1CKG   LL_CKGA_IsEnabledClock\n
  *         CKGDISR      CPUCKG      LL_CKGA_IsEnabledClock\n
  *         CKGDISR      GPU2DS0CKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      GPU2DS1CKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      GPU2DCLCKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      DCMIPPCKG   LL_CKGA_IsEnabledClock\n
  *         CKGDISR      DMA2DCKG    LL_CKGA_IsEnabledClock\n
  *         CKGDISR      GFXMMUSCKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      LTDCCKG     LL_CKGA_IsEnabledClock\n
  *         CKGDISR      GFXMMUMCKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      AHBSCKG     LL_CKGA_IsEnabledClock\n
  *         CKGDISR      FMCCKG      LL_CKGA_IsEnabledClock\n
  *         CKGDISR      XSPI2CKG    LL_CKGA_IsEnabledClock\n
  *         CKGDISR      XSPI1CKG    LL_CKGA_IsEnabledClock\n
  *         CKGDISR      AXIRAM1CKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      AXIRAM2CKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      AXIRAM3CKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      AXIRAM4CKG  LL_CKGA_IsEnabledClock\n
  *         CKGDISR      FLASHCKG    LL_CKGA_IsEnabledClock\n
  *         CKGDISR      EXTICKG     LL_CKGA_IsEnabledClock\n
  *         CKGDISR      JTAGCKG     LL_CKGA_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CKGA_PERIPH_AXI
  *         @arg @ref LL_CKGA_PERIPH_AHBM
  *         @arg @ref LL_CKGA_PERIPH_AHBS
  *         @arg @ref LL_CKGA_PERIPH_SDMMC1
  *         @arg @ref LL_CKGA_PERIPH_HPDMA1
  *         @arg @ref LL_CKGA_PERIPH_CPU
  *         @arg @ref LL_CKGA_PERIPH_GPU2DS0 (*)
  *         @arg @ref LL_CKGA_PERIPH_GPU2DS1 (*)
  *         @arg @ref LL_CKGA_PERIPH_GPU2DCL (*)
  *         @arg @ref LL_CKGA_PERIPH_DMA2D
  *         @arg @ref LL_CKGA_PERIPH_DCMIPP
  *         @arg @ref LL_CKGA_PERIPH_LTDC (*)
  *         @arg @ref LL_CKGA_PERIPH_FLASH
  *         @arg @ref LL_CKGA_PERIPH_XSPI2
  *         @arg @ref LL_CKGA_PERIPH_XSPI1
  *         @arg @ref LL_CKGA_PERIPH_FMC
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM1
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM2
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM3
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM4
  *         @arg @ref LL_CKGA_PERIPH_GFXMMUM
  *         @arg @ref LL_CKGA_PERIPH_GFXMMUS
  *         @arg @ref LL_CKGA_PERIPH_EXTI
  *         @arg @ref LL_CKGA_PERIPH_JTAG
  *
  *         (*) value not defined in all devices.
  * @retval uint32_t
  */
__STATIC_INLINE uint32_t LL_CKGA_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->CKGDISR, Periphs) == 0U) ? 1U : 0U);
}

/**
  * @brief  Disable clock gating for AXI bus peripherals.
  * @rmtoll CKGDISR      AXICKG      LL_CKGA_Disable\n
  *         CKGDISR      AHBMCKG     LL_CKGA_Disable\n
  *         CKGDISR      SDMMC1CKG   LL_CKGA_Disable\n
  *         CKGDISR      HPDMA1CKG   LL_CKGA_Disable\n
  *         CKGDISR      CPUCKG      LL_CKGA_Disable\n
  *         CKGDISR      GPU2DS0CKG  LL_CKGA_Disable\n
  *         CKGDISR      GPU2DS1CKG  LL_CKGA_Disable\n
  *         CKGDISR      GPUCLCKG    LL_CKGA_Disable\n
  *         CKGDISR      DCMIPPCKG   LL_CKGA_Disable\n
  *         CKGDISR      DMA2DCKG    LL_CKGA_Disable\n
  *         CKGDISR      GFXMMUSCKG  LL_CKGA_Disable\n
  *         CKGDISR      LTDCCKG     LL_CKGA_Disable\n
  *         CKGDISR      GFXMMUMCKG  LL_CKGA_Disable\n
  *         CKGDISR      AHBSCKG     LL_CKGA_Disable\n
  *         CKGDISR      FMCCKG      LL_CKGA_Disable\n
  *         CKGDISR      XSPI2CKG    LL_CKGA_Disable\n
  *         CKGDISR      XSPI1CKG    LL_CKGA_Disable\n
  *         CKGDISR      AXIRAM1CKG  LL_CKGA_Disable\n
  *         CKGDISR      AXIRAM2CKG  LL_CKGA_Disable\n
  *         CKGDISR      AXIRAM3CKG  LL_CKGA_Disable\n
  *         CKGDISR      AXIRAM4CKG  LL_CKGA_Disable\n
  *         CKGDISR      FLASHCKG    LL_CKGA_Disable\n
  *         CKGDISR      EXTICKG     LL_CKGA_Disable\n
  *         CKGDISR      JTAGCKG     LL_CKGA_Disable
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CKGA_PERIPH_AXI
  *         @arg @ref LL_CKGA_PERIPH_AHBM
  *         @arg @ref LL_CKGA_PERIPH_AHBS
  *         @arg @ref LL_CKGA_PERIPH_SDMMC1
  *         @arg @ref LL_CKGA_PERIPH_HPDMA1
  *         @arg @ref LL_CKGA_PERIPH_CPU
  *         @arg @ref LL_CKGA_PERIPH_GPU2DS0
  *         @arg @ref LL_CKGA_PERIPH_GPU2DS1
  *         @arg @ref LL_CKGA_PERIPH_GPU2DCL
  *         @arg @ref LL_CKGA_PERIPH_DMA2D
  *         @arg @ref LL_CKGA_PERIPH_DCMIPP
  *         @arg @ref LL_CKGA_PERIPH_LTDC
  *         @arg @ref LL_CKGA_PERIPH_FLASH
  *         @arg @ref LL_CKGA_PERIPH_XSPI2
  *         @arg @ref LL_CKGA_PERIPH_XSPI1
  *         @arg @ref LL_CKGA_PERIPH_FMC
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM1
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM2
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM3
  *         @arg @ref LL_CKGA_PERIPH_AXIRAM4
  *         @arg @ref LL_CKGA_PERIPH_GFXMMUM
  *         @arg @ref LL_CKGA_PERIPH_GFXMMUS
  *         @arg @ref LL_CKGA_PERIPH_EXTI
  *         @arg @ref LL_CKGA_PERIPH_JTAG
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_CKGA_Disable(uint32_t Periphs)
{
  SET_BIT(RCC->CKGDISR, Periphs);
}
/**
  * @}
  */

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

#endif /* STM32H7RSxx_LL_BUS_H */
