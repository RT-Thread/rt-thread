/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_conf.h
  * @author  MCD Application Team
  * @brief   HAL configuration template file.
  *          This file should be copied to the application folder and renamed
  *          to stm32h7rsxx_hal_conf.h.
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
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_CONF_H
#define STM32H7RSxx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the HAL driver
  */
#define HAL_MODULE_ENABLED
/* #define HAL_ADC_MODULE_ENABLED   */
/* #define HAL_CEC_MODULE_ENABLED   */
/* #define HAL_CORDIC_MODULE_ENABLED   */
/* #define HAL_CRC_MODULE_ENABLED   */
/* #define HAL_CRYP_MODULE_ENABLED   */
#define HAL_DCMIPP_MODULE_ENABLED
/* #define HAL_DMA2D_MODULE_ENABLED   */
/* #define HAL_DTS_MODULE_ENABLED   */
/* #define HAL_ETH_MODULE_ENABLED   */
/* #define HAL_FDCAN_MODULE_ENABLED   */
/* #define HAL_GFXMMU_MODULE_ENABLED   */
/* #define HAL_GFXTIM_MODULE_ENABLED   */
/* #define HAL_GPU2D_MODULE_ENABLED   */
/* #define HAL_HASH_MODULE_ENABLED   */
/* #define HAL_HCD_MODULE_ENABLED   */
#define HAL_I2C_MODULE_ENABLED
/* #define HAL_I2S_MODULE_ENABLED   */
/* #define HAL_I3C_MODULE_ENABLED   */
/* #define HAL_ICACHE_MODULE_ENABLED   */
/* #define HAL_IRDA_MODULE_ENABLED   */
/* #define HAL_IWDG_MODULE_ENABLED   */
/* #define HAL_JPEG_MODULE_ENABLED   */
/* #define HAL_LPTIM_MODULE_ENABLED   */
#define HAL_LTDC_MODULE_ENABLED
/* #define HAL_MCE_MODULE_ENABLED   */
/* #define HAL_MDF_MODULE_ENABLED   */
#define HAL_MMC_MODULE_ENABLED
/* #define HAL_NAND_MODULE_ENABLED   */
/* #define HAL_NOR_MODULE_ENABLED   */
#define HAL_PCD_MODULE_ENABLED
/* #define HAL_PKA_MODULE_ENABLED   */
/* #define HAL_PSSI_MODULE_ENABLED   */
/* #define HAL_RAMECC_MODULE_ENABLED   */
/* #define HAL_RCC_MODULE_ENABLED   */
/* #define HAL_RNG_MODULE_ENABLED   */
/* #define HAL_RTC_MODULE_ENABLED   */
#define HAL_SAI_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED
/* #define HAL_SDIO_MODULE_ENABLED   */
/* #define HAL_SDRAM_MODULE_ENABLED   */
/* #define HAL_SMARTCARD_MODULE_ENABLED   */
/* #define HAL_SMBUS_MODULE_ENABLED   */
/* #define HAL_SPDIFRX_MODULE_ENABLED   */
#define HAL_SPI_MODULE_ENABLED
/* #define HAL_SRAM_MODULE_ENABLED   */
/* #define HAL_TIM_MODULE_ENABLED   */
#define HAL_UART_MODULE_ENABLED
/* #define HAL_USART_MODULE_ENABLED   */
/* #define HAL_WWDG_MODULE_ENABLED   */
/* #define HAL_XSPI_MODULE_ENABLED   */
#define HAL_GPIO_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

/* ########################## Oscillator Values adaptation ####################*/
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    24000000UL /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT    100UL   /*!< Time out for HSE start up (in ms) */
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
#define HSI_VALUE          64000000UL /*!< Value of the Internal oscillator in Hz */
#endif /* HSI_VALUE */

/**
  * @brief Internal Low-power oscillator (CSI) default value.
  *        This value is the default CSI range value after Reset.
  */
#if !defined  (CSI_VALUE)
#define CSI_VALUE          4000000UL  /*!< Value of the Internal oscillator in Hz */
#endif /* CSI_VALUE */

/**
 * @brief Internal High Speed oscillator (HSI48) value for USB OTG FS and RNG.
 *        This internal oscillator is mainly dedicated to provide a high precision clock to
 *        the USB peripheral by means of a special Clock Recovery System (CRS) circuitry.
 *        When the CRS is not used, the HSI48 RC oscillator runs on it default frequency
 *        which is subject to manufacturing process variations.
  */
  #if !defined  (HSI48_VALUE)
  #define HSI48_VALUE        48000000UL /*!< Value of the Internal High Speed oscillator for USB OTG FS/RNG in Hz.
                                            The real value my vary depending on manufacturing process variations. */
  #endif /* HSI48_VALUE */

/**
* @brief Internal Low Speed oscillator (LSI) value.
  */
#if !defined  (LSI_VALUE)
#define LSI_VALUE  32000UL              /*!< LSI Typical Value in Hz.
                                            Value of the Internal Low Speed oscillator in Hz.
                                              The real value may vary depending on the variations
                                              in voltage and temperature.*/
#endif /* LSI_VALUE */

/**
* @brief External Low Speed oscillator (LSE) value.
*/
#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768UL /*!< Value of the External oscillator in Hz*/
#endif /* LSE_VALUE */

#if !defined  (LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT    5000UL   /*!< Time out for LSE start up (in ms) */
#endif /* LSE_STARTUP_TIMEOUT */

/**
  * @brief External clock source for digital audio interfaces: SPI/I2S, SAI and ADF
  *        This value is used by the RCC HAL module to provide the digital audio interfaces
  *        frequency. This clock source is inserted directly through I2S_CKIN pad.
  */
#if !defined  (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE      48000UL /*!< Value of the external clock source in Hz */
#endif /* EXTERNAL_CLOCK_VALUE */

/* Tip: To avoid modifying this file each time you need to use different HSE,
   ===  you can define the HSE value in your toolchain compiler preprocessor. */

/* ########################### System Configuration ######################### */
/**
  * @brief This is the HAL system configuration section
  */
#define  VDD_VALUE                    3300UL /*!< Value of VDD in mv */
#define  TICK_INT_PRIORITY            (15UL)/*!< tick interrupt priority (lowest by default) */
#define  USE_RTOS                     0U

/* ########################## Assert Selection ############################## */
/**
* @brief Uncomment the line below to expanse the "assert_param" macro in the
*        HAL drivers code
*/
/* #define USE_FULL_ASSERT    1U */

/* ################## Register callback feature configuration ############### */
/**
* @brief Set below the peripheral configuration  to "1U" to add the support
*        of HAL callback registration/unregistration feature for the HAL
*        driver(s). This allows user application to provide specific callback
*        functions thanks to HAL_PPP_RegisterCallback() rather than overwriting
*        the default weak callback functions (see each stm32h7rsxx_hal_ppp.h file
*        for possible callback identifiers defined in HAL_PPP_CallbackIDTypeDef
*        for each PPP peripheral).
*/
#define USE_HAL_ADC_REGISTER_CALLBACKS        0U
#define USE_HAL_CEC_REGISTER_CALLBACKS        0U
#define USE_HAL_CORDIC_REGISTER_CALLBACKS     0U
#define USE_HAL_CRYP_REGISTER_CALLBACKS       0U
#define USE_HAL_DCMIPP_REGISTER_CALLBACKS     0U
#define USE_HAL_FDCAN_REGISTER_CALLBACKS      0U
#define USE_HAL_GFXMMU_REGISTER_CALLBACKS     0U
#define USE_HAL_HASH_REGISTER_CALLBACKS       0U
#define USE_HAL_I2C_REGISTER_CALLBACKS        0U
#define USE_HAL_I2S_REGISTER_CALLBACKS        0U
#define USE_HAL_IRDA_REGISTER_CALLBACKS       0U
#define USE_HAL_JPEG_REGISTER_CALLBACKS       0U
#define USE_HAL_LPTIM_REGISTER_CALLBACKS      0U
#define USE_HAL_MDF_REGISTER_CALLBACKS        0U
#define USE_HAL_MMC_REGISTER_CALLBACKS        0U
#define USE_HAL_NAND_REGISTER_CALLBACKS       0U
#define USE_HAL_NOR_REGISTER_CALLBACKS        0U
#define USE_HAL_PCD_REGISTER_CALLBACKS        0U
#define USE_HAL_PKA_REGISTER_CALLBACKS        0U
#define USE_HAL_PSSI_REGISTER_CALLBACKS       0U
#define USE_HAL_RNG_REGISTER_CALLBACKS        0U
#define USE_HAL_RTC_REGISTER_CALLBACKS        0U
#define USE_HAL_SAI_REGISTER_CALLBACKS        0U
#define USE_HAL_SD_REGISTER_CALLBACKS         0U
#define USE_HAL_SDIO_REGISTER_CALLBACKS       0U
#define USE_HAL_SDRAM_REGISTER_CALLBACKS      0U
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS  0U
#define USE_HAL_SMBUS_REGISTER_CALLBACKS      0U
#define USE_HAL_SPDIFRX_REGISTER_CALLBACKS    0U
#define USE_HAL_SPI_REGISTER_CALLBACKS        0U
#define USE_HAL_SRAM_REGISTER_CALLBACKS       0U
#define USE_HAL_TIM_REGISTER_CALLBACKS        0U
#define USE_HAL_UART_REGISTER_CALLBACKS       0U
#define USE_HAL_USART_REGISTER_CALLBACKS      0U
#define USE_HAL_WWDG_REGISTER_CALLBACKS       0U
#define USE_HAL_XSPI_REGISTER_CALLBACKS       0U

/* ################## SPI peripheral configuration ########################## */

/* CRC FEATURE: Use to activate CRC feature inside HAL SPI Driver
* Activated: CRC code is present inside driver
* Deactivated: CRC code cleaned from driver
*/

#define USE_SPI_CRC                   1U

/* ################## CRYP peripheral configuration ########################## */

/**
  * @brief  For code optimization purpose, uncomment and set to "1U" the USE_HAL_CRYP_ONLY or USE_HAL_SAES_ONLY,
  *         to use only one peripheral. Both defines cannot be set to "1U" at the same time.
  */

/* #define USE_HAL_CRYP_ONLY       1U */
/* #define USE_HAL_SAES_ONLY       0U */

#define USE_HAL_CRYP_SUSPEND_RESUME   0U

/* ################## HASH peripheral configuration ########################## */

#define USE_HAL_HASH_SUSPEND_RESUME   0U

/* ################## SDMMC peripheral configuration ######################### */

#define USE_SD_TRANSCEIVER            0U

/* ################## SDIO peripheral configuration ######################### */

#define USE_SDIO_TRANSCEIVER          0U
#define SDIO_MAX_IO_NUMBER            7U

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file
  */

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32h7rsxx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32h7rsxx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32h7rsxx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CEC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_cec.h"
#endif /* HAL_CEC_MODULE_ENABLED */

#ifdef HAL_CORDIC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_cordic.h"
#endif /* HAL_CORDIC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_CRYP_MODULE_ENABLED
  #include "stm32h7rsxx_hal_cryp.h"
#endif /* HAL_CRYP_MODULE_ENABLED */

#ifdef HAL_DCMIPP_MODULE_ENABLED
  #include "stm32h7rsxx_hal_dcmipp.h"
#endif /* HAL_DCMIPP_MODULE_ENABLED */

#ifdef HAL_DMA2D_MODULE_ENABLED
  #include "stm32h7rsxx_hal_dma2d.h"
#endif /* HAL_DMA2D_MODULE_ENABLED */

#ifdef HAL_DTS_MODULE_ENABLED
  #include "stm32h7rsxx_hal_dts.h"
#endif /* HAL_DTS_MODULE_ENABLED */

#ifdef HAL_ETH_MODULE_ENABLED
  #include "stm32h7rsxx_hal_eth.h"
#endif /* HAL_ETH_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
  #include "stm32h7rsxx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_FDCAN_MODULE_ENABLED
  #include "stm32h7rsxx_hal_fdcan.h"
#endif /* HAL_FDCAN_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32h7rsxx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_GFXMMU_MODULE_ENABLED
  #include "stm32h7rsxx_hal_gfxmmu.h"
#endif /* HAL_GFXMMU_MODULE_ENABLED */

#ifdef HAL_GFXTIM_MODULE_ENABLED
  #include "stm32h7rsxx_hal_gfxtim.h"
#endif /* HAL_GFXTIM_MODULE_ENABLED */

#ifdef HAL_GPU2D_MODULE_ENABLED
  #include "stm32h7rsxx_hal_gpu2d.h"
#endif /* HAL_GPU2D_MODULE_ENABLED */

#ifdef HAL_HASH_MODULE_ENABLED
  #include "stm32h7rsxx_hal_hash.h"
#endif /* HAL_HASH_MODULE_ENABLED */

#ifdef HAL_HCD_MODULE_ENABLED
  #include "stm32h7rsxx_hal_hcd.h"
#endif /* HAL_HCD_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
  #include "stm32h7rsxx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
 #include "stm32h7rsxx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_I3C_MODULE_ENABLED
  #include "stm32h7rsxx_hal_i3c.h"
#endif /* HAL_I3C_MODULE_ENABLED */

#ifdef HAL_ICACHE_MODULE_ENABLED
  #include "stm32h7rsxx_hal_icache.h"
#endif /* HAL_ICACHE_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
  #include "stm32h7rsxx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
  #include "stm32h7rsxx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_JPEG_MODULE_ENABLED
  #include "stm32h7rsxx_hal_jpeg.h"
#endif /* HAL_JPEG_MODULE_ENABLED */

#ifdef HAL_LTDC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_ltdc.h"
#endif /* HAL_LTDC_MODULE_ENABLED */

#ifdef HAL_LPTIM_MODULE_ENABLED
  #include "stm32h7rsxx_hal_lptim.h"
#endif /* HAL_LPTIM_MODULE_ENABLED */

#ifdef HAL_MCE_MODULE_ENABLED
  #include "stm32h7rsxx_hal_mce.h"
#endif /* HAL_MCE_MODULE_ENABLED */

#ifdef HAL_MDF_MODULE_ENABLED
  #include "stm32h7rsxx_hal_mdf.h"
#endif /* HAL_MDF_MODULE_ENABLED */

#ifdef HAL_MMC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_mmc.h"
#endif /* HAL_MMC_MODULE_ENABLED */

#ifdef HAL_NAND_MODULE_ENABLED
  #include "stm32h7rsxx_hal_nand.h"
#endif /* HAL_NAND_MODULE_ENABLED */

#ifdef HAL_NOR_MODULE_ENABLED
  #include "stm32h7rsxx_hal_nor.h"
#endif /* HAL_NOR_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
  #include "stm32h7rsxx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_PKA_MODULE_ENABLED
  #include "stm32h7rsxx_hal_pka.h"
#endif /* HAL_PKA_MODULE_ENABLED */

#ifdef HAL_PSSI_MODULE_ENABLED
  #include "stm32h7rsxx_hal_pssi.h"
#endif /* HAL_PSSI_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
  #include "stm32h7rsxx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RAMECC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_ramecc.h"
#endif /* HAL_RAMECC_MODULE_ENABLED */

#ifdef HAL_RNG_MODULE_ENABLED
  #include "stm32h7rsxx_hal_rng.h"
#endif /* HAL_RNG_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
  #include "stm32h7rsxx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SAI_MODULE_ENABLED
  #include "stm32h7rsxx_hal_sai.h"
#endif /* HAL_SAI_MODULE_ENABLED */

#ifdef HAL_SD_MODULE_ENABLED
  #include "stm32h7rsxx_hal_sd.h"
#endif /* HAL_SD_MODULE_ENABLED */

#ifdef HAL_SDIO_MODULE_ENABLED
#include "stm32h7rsxx_hal_sdio.h"
#endif /* HAL_SDIO_MODULE_ENABLED */

#ifdef HAL_SDRAM_MODULE_ENABLED
  #include "stm32h7rsxx_hal_sdram.h"
#endif /* HAL_SDRAM_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
  #include "stm32h7rsxx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_SMBUS_MODULE_ENABLED
  #include "stm32h7rsxx_hal_smbus.h"
#endif /* HAL_SMBUS_MODULE_ENABLED */

#ifdef HAL_SPDIFRX_MODULE_ENABLED
  #include "stm32h7rsxx_hal_spdifrx.h"
#endif /* HAL_SPDIFRX_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
  #include "stm32h7rsxx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_SRAM_MODULE_ENABLED
  #include "stm32h7rsxx_hal_sram.h"
#endif /* HAL_SRAM_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
  #include "stm32h7rsxx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
  #include "stm32h7rsxx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
  #include "stm32h7rsxx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
  #include "stm32h7rsxx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_XSPI_MODULE_ENABLED
  #include "stm32h7rsxx_hal_xspi.h"
#endif /* HAL_XSPI_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t *file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_CONF_H */

