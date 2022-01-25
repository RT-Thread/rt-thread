/**
  ******************************************************************************
  * @brief   RCC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_RCC_H
#define __GD32F10X_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Types
  * @{
  */

/**
  * @brief  RCC Initial Parameters
  */

typedef struct {
    uint32_t CK_SYS_Frequency;             /*!< The frequency of the CK_SYS.     */
    uint32_t AHB_Frequency;                /*!< The frequency of the AHB.        */
    uint32_t APB1_Frequency;              /*!< The frequency of the APB1.       */
    uint32_t APB2_Frequency;              /*!< The frequency of the APB2.       */
    uint32_t ADCCLK_Frequency;            /*!< The frequency of the ADCCLK.     */
} RCC_ClocksPara;

/**
  * @}
  */

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSE_configuration
  * @{
  */

#define RCC_HSE_OFF                      ((uint32_t)0x00000000)
#define RCC_HSE_ON                       RCC_GCCR_HSEEN
#define RCC_HSE_BYPASS                   RCC_GCCR_HSEEN | RCC_GCCR_HSEBPS

/**
  * @}
  */

/** @defgroup RCC_PLL_input_clock_source
  * @{
  */

#define RCC_PLLSOURCE_HSI_DIV2           RCC_GCFGR_PLLSEL_HSI_DIV2

#ifdef GD32F10X_CL
#define RCC_PLLSOURCE_PREDIV1            RCC_GCFGR_PLLSEL_PREDIV1

#else
#define RCC_PLLSOURCE_HSE_DIV1           ((uint32_t)0x00010000)
#define RCC_PLLSOURCE_HSE_DIV2           ((uint32_t)0x00030000)
#endif /* GD32F10X_CL */
/**
  * @}
  */

/** @defgroup RCC_PLL_Multiplication_factor
  * @{
  */


#define  RCC_PLLMUL_2                         RCC_GCFGR_PLLMF2
#define  RCC_PLLMUL_3                         RCC_GCFGR_PLLMF3
#define  RCC_PLLMUL_4                         RCC_GCFGR_PLLMF4
#define  RCC_PLLMUL_5                         RCC_GCFGR_PLLMF5
#define  RCC_PLLMUL_6                         RCC_GCFGR_PLLMF6
#define  RCC_PLLMUL_7                         RCC_GCFGR_PLLMF7
#define  RCC_PLLMUL_8                         RCC_GCFGR_PLLMF8
#define  RCC_PLLMUL_9                         RCC_GCFGR_PLLMF9
#define  RCC_PLLMUL_10                        RCC_GCFGR_PLLMF10
#define  RCC_PLLMUL_11                        RCC_GCFGR_PLLMF11
#define  RCC_PLLMUL_12                        RCC_GCFGR_PLLMF12
#define  RCC_PLLMUL_13                        RCC_GCFGR_PLLMF13
#define  RCC_PLLMUL_14                        RCC_GCFGR_PLLMF14

#define  RCC_PLLMUL_16                        RCC_GCFGR_PLLMF16
#define  RCC_PLLMUL_17                        RCC_GCFGR_PLLMF17
#define  RCC_PLLMUL_18                        RCC_GCFGR_PLLMF18
#define  RCC_PLLMUL_19                        RCC_GCFGR_PLLMF19
#define  RCC_PLLMUL_20                        RCC_GCFGR_PLLMF20
#define  RCC_PLLMUL_21                        RCC_GCFGR_PLLMF21
#define  RCC_PLLMUL_22                        RCC_GCFGR_PLLMF22
#define  RCC_PLLMUL_23                        RCC_GCFGR_PLLMF23
#define  RCC_PLLMUL_24                        RCC_GCFGR_PLLMF24
#define  RCC_PLLMUL_25                        RCC_GCFGR_PLLMF25
#define  RCC_PLLMUL_26                        RCC_GCFGR_PLLMF26
#define  RCC_PLLMUL_27                        RCC_GCFGR_PLLMF27
#define  RCC_PLLMUL_28                        RCC_GCFGR_PLLMF28
#define  RCC_PLLMUL_29                        RCC_GCFGR_PLLMF29
#define  RCC_PLLMUL_30                        RCC_GCFGR_PLLMF30
#define  RCC_PLLMUL_31                        RCC_GCFGR_PLLMF31
#define  RCC_PLLMUL_32                        RCC_GCFGR_PLLMF32

#ifdef GD32F10X_CL
#define  RCC_PLLMUL_6_5                       RCC_GCFGR_PLLMF6_5
#else
#define  RCC_PLLMUL_15                        RCC_GCFGR_PLLMF15

#endif /* GD32F10X_CL */
/**
  * @}
  */

#ifdef GD32F10X_CL
/** @defgroup RCC_PREDIV1_division_factor
  * @{
  */

#define  RCC_PREDIV1_DIV1               RCC_GCFGR2_PREDV1_DIV1
#define  RCC_PREDIV1_DIV2               RCC_GCFGR2_PREDV1_DIV2
#define  RCC_PREDIV1_DIV3               RCC_GCFGR2_PREDV1_DIV3
#define  RCC_PREDIV1_DIV4               RCC_GCFGR2_PREDV1_DIV4
#define  RCC_PREDIV1_DIV5               RCC_GCFGR2_PREDV1_DIV5
#define  RCC_PREDIV1_DIV6               RCC_GCFGR2_PREDV1_DIV6
#define  RCC_PREDIV1_DIV7               RCC_GCFGR2_PREDV1_DIV7
#define  RCC_PREDIV1_DIV8               RCC_GCFGR2_PREDV1_DIV8
#define  RCC_PREDIV1_DIV9               RCC_GCFGR2_PREDV1_DIV9
#define  RCC_PREDIV1_DIV10              RCC_GCFGR2_PREDV1_DIV10
#define  RCC_PREDIV1_DIV11              RCC_GCFGR2_PREDV1_DIV11
#define  RCC_PREDIV1_DIV12              RCC_GCFGR2_PREDV1_DIV12
#define  RCC_PREDIV1_DIV13              RCC_GCFGR2_PREDV1_DIV13
#define  RCC_PREDIV1_DIV14              RCC_GCFGR2_PREDV1_DIV14
#define  RCC_PREDIV1_DIV15              RCC_GCFGR2_PREDV1_DIV15
#define  RCC_PREDIV1_DIV16              RCC_GCFGR2_PREDV1_DIV16

/**
  * @}
  */


/** @defgroup RCC_PREDIV1_clock_source
  * @{
  */

#define  RCC_PREDIV1_SOURCE_HSE         RCC_GCFGR2_PREDV1SEL_HSE
#define  RCC_PREDIV1_SOURCE_PLL2        RCC_GCFGR2_PREDV1SEL_PLL2

/**
  * @}
  */


/** @defgroup RCC_PREDIV2_division_factor
  * @{
  */
#define  RCC_PREDIV2_DIV1               RCC_GCFGR2_PREDV2_DIV1
#define  RCC_PREDIV2_DIV2               RCC_GCFGR2_PREDV2_DIV2
#define  RCC_PREDIV2_DIV3               RCC_GCFGR2_PREDV2_DIV3
#define  RCC_PREDIV2_DIV4               RCC_GCFGR2_PREDV2_DIV4
#define  RCC_PREDIV2_DIV5               RCC_GCFGR2_PREDV2_DIV5
#define  RCC_PREDIV2_DIV6               RCC_GCFGR2_PREDV2_DIV6
#define  RCC_PREDIV2_DIV7               RCC_GCFGR2_PREDV2_DIV7
#define  RCC_PREDIV2_DIV8               RCC_GCFGR2_PREDV2_DIV8
#define  RCC_PREDIV2_DIV9               RCC_GCFGR2_PREDV2_DIV9
#define  RCC_PREDIV2_DIV10              RCC_GCFGR2_PREDV2_DIV10
#define  RCC_PREDIV2_DIV11              RCC_GCFGR2_PREDV2_DIV11
#define  RCC_PREDIV2_DIV12              RCC_GCFGR2_PREDV2_DIV12
#define  RCC_PREDIV2_DIV13              RCC_GCFGR2_PREDV2_DIV13
#define  RCC_PREDIV2_DIV14              RCC_GCFGR2_PREDV2_DIV14
#define  RCC_PREDIV2_DIV15              RCC_GCFGR2_PREDV2_DIV15
#define  RCC_PREDIV2_DIV16              RCC_GCFGR2_PREDV2_DIV16

/**
  * @}
  */


/** @defgroup RCC_PLL2_multiplication_factor
  * @{
  */
#define  RCC_PLL2MUL_8                  RCC_GCFGR2_PLL2MF8
#define  RCC_PLL2MUL_9                  RCC_GCFGR2_PLL2MF9
#define  RCC_PLL2MUL_10                 RCC_GCFGR2_PLL2MF10
#define  RCC_PLL2MUL_11                 RCC_GCFGR2_PLL2MF11
#define  RCC_PLL2MUL_12                 RCC_GCFGR2_PLL2MF12
#define  RCC_PLL2MUL_13                 RCC_GCFGR2_PLL2MF13
#define  RCC_PLL2MUL_14                 RCC_GCFGR2_PLL2MF14
#define  RCC_PLL2MUL_16                 RCC_GCFGR2_PLL2MF16
#define  RCC_PLL2MUL_20                 RCC_GCFGR2_PLL2MF20

/**
  * @}
  */


/** @defgroup RCC_PLL3_multiplication_factor
  * @{
  */
#define  RCC_PLL3MUL_8                  RCC_GCFGR2_PLL3MF8
#define  RCC_PLL3MUL_9                  RCC_GCFGR2_PLL3MF9
#define  RCC_PLL3MUL_10                 RCC_GCFGR2_PLL3MF10
#define  RCC_PLL3MUL_11                 RCC_GCFGR2_PLL3MF11
#define  RCC_PLL3MUL_12                 RCC_GCFGR2_PLL3MF12
#define  RCC_PLL3MUL_13                 RCC_GCFGR2_PLL3MF13
#define  RCC_PLL3MUL_14                 RCC_GCFGR2_PLL3MF14
#define  RCC_PLL3MUL_16                 RCC_GCFGR2_PLL3MF16
#define  RCC_PLL3MUL_20                 RCC_GCFGR2_PLL3MF20

/**
  * @}
  */
#endif /* GD32F10X_CL */


/** @defgroup RCC_System_Clock_Source
  * @{
  */
#define  RCC_SYSCLKSOURCE_HSI                RCC_GCFGR_SCS_HSI
#define  RCC_SYSCLKSOURCE_HSE                RCC_GCFGR_SCS_HSE
#define  RCC_SYSCLKSOURCE_PLLCLK             RCC_GCFGR_SCS_PLL

/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source
  * @{
  */
#define  RCC_SYSCLK_DIV1                     RCC_GCFGR_AHBPS_DIV1
#define  RCC_SYSCLK_DIV2                     RCC_GCFGR_AHBPS_DIV2
#define  RCC_SYSCLK_DIV4                     RCC_GCFGR_AHBPS_DIV4
#define  RCC_SYSCLK_DIV8                     RCC_GCFGR_AHBPS_DIV8
#define  RCC_SYSCLK_DIV16                    RCC_GCFGR_AHBPS_DIV16
#define  RCC_SYSCLK_DIV64                    RCC_GCFGR_AHBPS_DIV64
#define  RCC_SYSCLK_DIV128                   RCC_GCFGR_AHBPS_DIV128
#define  RCC_SYSCLK_DIV256                   RCC_GCFGR_AHBPS_DIV256
#define  RCC_SYSCLK_DIV512                   RCC_GCFGR_AHBPS_DIV512

/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Source
  * @{
  */
#define  RCC_APB1AHB_DIV1                    RCC_GCFGR_APB1PS_DIV1
#define  RCC_APB1AHB_DIV2                    RCC_GCFGR_APB1PS_DIV2
#define  RCC_APB1AHB_DIV4                    RCC_GCFGR_APB1PS_DIV4
#define  RCC_APB1AHB_DIV8                    RCC_GCFGR_APB1PS_DIV8
#define  RCC_APB1AHB_DIV16                   RCC_GCFGR_APB1PS_DIV16

#define  RCC_APB2AHB_DIV1                    RCC_GCFGR_APB2PS_DIV1
#define  RCC_APB2AHB_DIV2                    RCC_GCFGR_APB2PS_DIV2
#define  RCC_APB2AHB_DIV4                    RCC_GCFGR_APB2PS_DIV4
#define  RCC_APB2AHB_DIV8                    RCC_GCFGR_APB2PS_DIV8
#define  RCC_APB2AHB_DIV16                   RCC_GCFGR_APB2PS_DIV16
/**
  * @}
  */

/** @defgroup RCC_ADC_clock_source
  * @{
  */
#define  RCC_ADCCLK_APB2_DIV2                RCC_GCFGR_ADCPS_DIV2
#define  RCC_ADCCLK_APB2_DIV4                RCC_GCFGR_ADCPS_DIV4
#define  RCC_ADCCLK_APB2_DIV6                RCC_GCFGR_ADCPS_DIV6
#define  RCC_ADCCLK_APB2_DIV8                RCC_GCFGR_ADCPS_DIV8
#define  RCC_ADCCLK_APB2_DIV12               RCC_GCFGR_ADCPS_DIV12
#define  RCC_ADCCLK_APB2_DIV16               RCC_GCFGR_ADCPS_DIV16

/**
  * @}
  */

#ifdef GD32F10X_CL
/** @defgroup RCC_USB_OTG_clock_source
  * @{
  */
#define  RCC_OTGCLK_PLL_DIV1                RCC_GCFGR_OTGFSPS_Div1
#define  RCC_OTGCLK_PLL_DIV1_5              RCC_GCFGR_OTGFSPS_Div1_5
#define  RCC_OTGCLK_PLL_DIV2                RCC_GCFGR_OTGFSPS_Div2
#define  RCC_OTGCLK_PLL_DIV2_5              RCC_GCFGR_OTGFSPS_Div2_5

/**
  * @}
  */

#else
/** @defgroup RCC_USB_clock_source
  * @{
  */
#define  RCC_USBCLK_PLL_DIV1                RCC_GCFGR_USBPS_Div1
#define  RCC_USBCLK_PLL_DIV1_5              RCC_GCFGR_USBPS_Div1_5
#define  RCC_USBCLK_PLL_DIV2                RCC_GCFGR_USBPS_Div2
#define  RCC_USBCLK_PLL_DIV2_5              RCC_GCFGR_USBPS_Div2_5

/**
  * @}
  */
#endif /* GD32F10X_CL */



/** @defgroup RCC_CK_OUT_Clock_Source
  * @{
  */
#ifdef GD32F10X_CL
#define  RCC_CKOUTSRC_NOCLOCK               RCC_GCFGR_CKOUTSEL_NoClock
#define  RCC_CKOUTSRC_SYSCLK                RCC_GCFGR_CKOUTSEL_SYSCLK
#define  RCC_CKOUTSRC_HSI                   RCC_GCFGR_CKOUTSEL_HSI
#define  RCC_CKOUTSRC_HSE                   RCC_GCFGR_CKOUTSEL_HSE
#define  RCC_CKOUTSRC_PLLCLK_DIV2           RCC_GCFGR_CKOUTSEL_PLL_DIV2
#define  RCC_CKOUTSRC_PLL2CLK               RCC_GCFGR_CKOUTSEL_PLL2
#define  RCC_CKOUTSRC_PLL3CLK               RCC_GCFGR_CKOUTSEL_PLL3
#define  RCC_CKOUTSRC_PLL3CLK_DIV2          RCC_GCFGR_CKOUTSEL_PLL3_DIV2
#define  RCC_CKOUTSRC_EXT1                  RCC_GCFGR_CKOUTSEL_EXT1

#else
#define  RCC_CKOUTSRC_NOCLOCK               RCC_GCFGR_CKOUTSEL_NoClock
#define  RCC_CKOUTSRC_SYSCLK                RCC_GCFGR_CKOUTSEL_SYSCLK
#define  RCC_CKOUTSRC_HSI                   RCC_GCFGR_CKOUTSEL_HSI
#define  RCC_CKOUTSRC_HSE                   RCC_GCFGR_CKOUTSEL_HSE
#define  RCC_CKOUTSRC_PLLCLK_DIV2           RCC_GCFGR_CKOUTSEL_PLL_DIV2

#endif /* GD32F10X_CL */

/**
  * @}
  */

/** @defgroup RCC_Interrupt_Source
  * @{
  */
#define  RCC_INT_LSISTB                      ((uint8_t)0x01)
#define  RCC_INT_LSESTB                      ((uint8_t)0x02)
#define  RCC_INT_HSISTB                      ((uint8_t)0x04)
#define  RCC_INT_HSESTB                      ((uint8_t)0x08)
#define  RCC_INT_PLLSTB                      ((uint8_t)0x10)
#define  RCC_INT_CKM                         ((uint8_t)0x80)

#ifdef GD32F10X_CL
#define  RCC_INT_PLL2STB                     ((uint8_t)0x20)
#define  RCC_INT_PLL3STB                     ((uint8_t)0x40)
#endif /* GD32F10X_CL */

/**
  * @}
  */

#ifdef GD32F10X_CL
/** @defgroup RCC_I2S2_clock_source
  * @{
  */
#define  RCC_I2S2CLK_SYSCLK        RCC_GCFGR2_I2S2SEL_CK_SYS
#define  RCC_I2S2CLK_PLL3          RCC_GCFGR2_I2S2SEL_PLL3

/**
  * @}
  */

/** @defgroup RCC_I2S3_clock_source
  * @{
  */
#define  RCC_I2S3CLK_SYSCLK        RCC_GCFGR2_I2S3SEL_CK_SYS
#define  RCC_I2S3CLK_PLL3          RCC_GCFGR2_I2S3SEL_PLL3

/**
  * @}
  */
#endif /* GD32F10X_CL */



/** @defgroup RCC_LSE_configuration
  * @{
  */
#define RCC_LSE_OFF                         ((uint32_t)0x00000000)
#define RCC_LSE_EN                           RCC_BDCR_LSEEN
#define RCC_LSE_BYPASS                      ((uint32_t)(RCC_BDCR_LSEEN | RCC_BDCR_LSEBPS))

/**
  * @}
  */

/** @defgroup RCC_RTC_clock_source
  * @{
  */
#define RCC_RTCCLKSOURCE_LSE             RCC_BDCR_RTCSEL_LSE
#define RCC_RTCCLKSOURCE_LSI             RCC_BDCR_RTCSEL_LSI
#define RCC_RTCCLKSOURCE_HSE_DIV128      RCC_BDCR_RTCSEL_HSE128

/**
  * @}
  */

/** @defgroup RCC_AHB_peripheral
  * @{
  */
#define  RCC_AHBPERIPH_DMA1               RCC_AHBCCR_DMA1EN
#define  RCC_AHBPERIPH_DMA2               RCC_AHBCCR_DMA2EN
#define  RCC_AHBPERIPH_SRAM               RCC_AHBCCR_SRAMEN
#define  RCC_AHBPERIPH_FMC                RCC_AHBCCR_FMCEN
#define  RCC_AHBPERIPH_CRC                RCC_AHBCCR_CRCEN
#define  RCC_AHBPERIPH_EXMC               RCC_AHBCCR_EXMCEN

#ifdef GD32F10X_CL
#define  RCC_AHBPERIPH_OTG_FS             RCC_AHBCCR_OTGFSEN
#define  RCC_AHBPERIPH_ETH_MAC            RCC_AHBCCR_ETHMACEN
#define  RCC_AHBPERIPH_ETH_MAC_RX         RCC_AHBCCR_ETHMACRXEN
#define  RCC_AHBPERIPH_ETH_MAC_TX         RCC_AHBCCR_ETHMACTXEN

#else
#define  RCC_AHBPERIPH_SDIO               RCC_AHBCCR_SDIOEN
#endif/* GD32F10X_CL */

/**
  * @}
  */

/** @defgroup RCC_AHB_Peripherals_RST
  * @{
  */
#ifdef GD32F10X_CL
#define  RCC_AHBPERIPH_OTGFSRST          RCC_AHBRCR_OTGFSRST
#define  RCC_AHBPERIPH_ETHMACRST         RCC_AHBRCR_ETHMACRST

#endif/* GD32F10X_CL */

/**
  * @}
  */

/** @defgroup RCC_APB2_peripheral
  * @{
  */
#define  RCC_APB2PERIPH_AF                RCC_APB2CCR_AFEN
#define  RCC_APB2PERIPH_GPIOA             RCC_APB2CCR_PAEN
#define  RCC_APB2PERIPH_GPIOB             RCC_APB2CCR_PBEN
#define  RCC_APB2PERIPH_GPIOC             RCC_APB2CCR_PCEN
#define  RCC_APB2PERIPH_GPIOD             RCC_APB2CCR_PDEN
#define  RCC_APB2PERIPH_GPIOE             RCC_APB2CCR_PEEN
#define  RCC_APB2PERIPH_GPIOF             RCC_APB2CCR_PFEN
#define  RCC_APB2PERIPH_GPIOG             RCC_APB2CCR_PGEN
#define  RCC_APB2PERIPH_ADC0              RCC_APB2CCR_ADC0EN
#define  RCC_APB2PERIPH_ADC1              RCC_APB2CCR_ADC1EN
#define  RCC_APB2PERIPH_TIMER0            RCC_APB2CCR_TIMER0EN
#define  RCC_APB2PERIPH_SPI1              RCC_APB2CCR_SPI1EN
#define  RCC_APB2PERIPH_TIMER7            RCC_APB2CCR_TIMER7EN
#define  RCC_APB2PERIPH_USART1            RCC_APB2CCR_USART1EN
#define  RCC_APB2PERIPH_ADC2              RCC_APB2CCR_ADC2EN
#define  RCC_APB2PERIPH_TIMER8            RCC_APB2CCR_TIMER8EN
#define  RCC_APB2PERIPH_TIMER9           RCC_APB2CCR_TIMER9EN
#define  RCC_APB2PERIPH_TIMER10           RCC_APB2CCR_TIMER10EN

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals_RST
  * @{
  */
#define  RCC_APB2PERIPH_AFRST             RCC_APB2RCR_AFRST
#define  RCC_APB2PERIPH_GPIOARST          RCC_APB2RCR_PARST
#define  RCC_APB2PERIPH_GPIOBRST          RCC_APB2RCR_PBRST
#define  RCC_APB2PERIPH_GPIOCRST          RCC_APB2RCR_PCRST
#define  RCC_APB2PERIPH_GPIODRST          RCC_APB2RCR_PDRST
#define  RCC_APB2PERIPH_GPIOERST          RCC_APB2RCR_PERST
#define  RCC_APB2PERIPH_GPIOFRST          RCC_APB2RCR_PFRST
#define  RCC_APB2PERIPH_GPIOGRST          RCC_APB2RCR_PGRST
#define  RCC_APB2PERIPH_ADC0RST           RCC_APB2RCR_ADC0RST
#define  RCC_APB2PERIPH_ADC1RST           RCC_APB2RCR_ADC1RST
#define  RCC_APB2PERIPH_TIMER0RST         RCC_APB2RCR_TIMER0RST
#define  RCC_APB2PERIPH_SPI1RST           RCC_APB2RCR_SPI1RST
#define  RCC_APB2PERIPH_TIMER7RST         RCC_APB2RCR_TIMER7RST
#define  RCC_APB2PERIPH_USART0RST         RCC_APB2RCR_USART0RST
#define  RCC_APB2PERIPH_ADC2RST           RCC_APB2RCR_ADC2RST
#define  RCC_APB2PERIPH_TIMER8RST         RCC_APB2RCR_TIMER8RST
#define  RCC_APB2PERIPH_TIMER9RST         RCC_APB2RCR_TIMER9RST
#define  RCC_APB2PERIPH_TIMER10RST        RCC_APB2RCR_TIMER10RST

/**
  * @}
  */

/** @defgroup RCC_APB1_peripheral
  * @{
  */
#define  RCC_APB1PERIPH_TIMER1            RCC_APB1CCR_TIMER1EN
#define  RCC_APB1PERIPH_TIMER2            RCC_APB1CCR_TIMER2EN
#define  RCC_APB1PERIPH_TIMER3            RCC_APB1CCR_TIMER3EN
#define  RCC_APB1PERIPH_TIMER4            RCC_APB1CCR_TIMER4EN
#define  RCC_APB1PERIPH_TIMER5            RCC_APB1CCR_TIMER5EN
#define  RCC_APB1PERIPH_TIMER6            RCC_APB1CCR_TIMER6EN
#define  RCC_APB1PERIPH_TIMER11           RCC_APB1CCR_TIMER11EN
#define  RCC_APB1PERIPH_TIMER12           RCC_APB1CCR_TIMER12EN
#define  RCC_APB1PERIPH_TIMER13           RCC_APB1CCR_TIMER13EN
#define  RCC_APB1PERIPH_WWDG              RCC_APB1CCR_WWDGEN
#define  RCC_APB1PERIPH_SPI2              RCC_APB1CCR_SPI2EN
#define  RCC_APB1PERIPH_SPI3              RCC_APB1CCR_SPI3EN
#define  RCC_APB1PERIPH_USART2            RCC_APB1CCR_USART2EN
#define  RCC_APB1PERIPH_USART3            RCC_APB1CCR_USART3EN
#define  RCC_APB1PERIPH_UART4             RCC_APB1CCR_UART4EN
#define  RCC_APB1PERIPH_UART5             RCC_APB1CCR_UART5EN
#define  RCC_APB1PERIPH_I2C1              RCC_APB1CCR_I2C1EN
#define  RCC_APB1PERIPH_I2C2              RCC_APB1CCR_I2C2EN
#define  RCC_APB1PERIPH_USB               RCC_APB1CCR_USBEN
#define  RCC_APB1PERIPH_CAN1              RCC_APB1CCR_CAN1EN
#define  RCC_APB1PERIPH_CAN2              RCC_APB1CCR_CAN2EN
#define  RCC_APB1PERIPH_BKP               RCC_APB1CCR_BKPEN
#define  RCC_APB1PERIPH_PWR               RCC_APB1CCR_PWREN
#define  RCC_APB1PERIPH_DAC               RCC_APB1CCR_DACEN

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripherals_RST
  * @{
  */
#define  RCC_APB1PERIPH_TIMER1RST         RCC_APB1RCR_TIMER1RST
#define  RCC_APB1PERIPH_TIMER2RST         RCC_APB1RCR_TIMER2RST
#define  RCC_APB1PERIPH_TIMER3RST         RCC_APB1RCR_TIMER3RST
#define  RCC_APB1PERIPH_TIMER4RST         RCC_APB1RCR_TIMER4RST
#define  RCC_APB1PERIPH_TIMER5RST         RCC_APB1RCR_TIMER5RST
#define  RCC_APB1PERIPH_TIMER6RST         RCC_APB1RCR_TIMER6RST
#define  RCC_APB1PERIPH_TIMER11RST        RCC_APB1RCR_TIMER11RST
#define  RCC_APB1PERIPH_TIMER12RST        RCC_APB1RCR_TIMER12RST
#define  RCC_APB1PERIPH_TIMER13RST        RCC_APB1RCR_TIMER13RST
#define  RCC_APB1PERIPH_WWDGRST           RCC_APB1RCR_WWDGRST
#define  RCC_APB1PERIPH_SPI2RST           RCC_APB1RCR_SPI2RST
#define  RCC_APB1PERIPH_SPI3RST           RCC_APB1RCR_SPI3RST
#define  RCC_APB1PERIPH_USART1RST         RCC_APB1RCR_USART1RST
#define  RCC_APB1PERIPH_USART2RST         RCC_APB1RCR_USART2RST
#define  RCC_APB1PERIPH_UART3RST          RCC_APB1RCR_UART3RST
#define  RCC_APB1PERIPH_UART4RST          RCC_APB1RCR_UART4RST
#define  RCC_APB1PERIPH_I2C1RST           RCC_APB1RCR_I2C1RST
#define  RCC_APB1PERIPH_I2C2RST           RCC_APB1RCR_I2C2RST
#define  RCC_APB1PERIPH_USBRST            RCC_APB1RCR_USBRST
#define  RCC_APB1PERIPH_CAN1RST           RCC_APB1RCR_CAN1RST
#define  RCC_APB1PERIPH_CAN2RST           RCC_APB1RCR_CAN2RST
#define  RCC_APB1PERIPH_BKPRST            RCC_APB1RCR_BKPRST
#define  RCC_APB1PERIPH_PWRRST            RCC_APB1RCR_PWRRST
#define  RCC_APB1PERIPH_DACRST            RCC_APB1RCR_DACRST

/**
  * @}
  */

/** @defgroup RCC_Flag
  * @{
  */
/* The flag to check is in GCCR register */
#define RCC_FLAG_HSISTB                  ((uint8_t)0x21)
#define RCC_FLAG_HSESTB                  ((uint8_t)0x31)
#define RCC_FLAG_PLLSTB                  ((uint8_t)0x39)

/* The flag to check is in BDCR register */
#define RCC_FLAG_LSESTB                  ((uint8_t)0x41)

/* The flag to check is in GCSR register */
#define RCC_FLAG_LSISTB                  ((uint8_t)0x61)

#define RCC_FLAG_EPRST                   ((uint8_t)0x7A)
#define RCC_FLAG_POPDRST                 ((uint8_t)0x7B)
#define RCC_FLAG_SWRRST                  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)
#define RCC_FLAG_LPRRST                  ((uint8_t)0x7F)

#ifdef GD32F10X_CL
/* The flag to check is in GCCR register */
#define RCC_FLAG_PLL2STB                 ((uint8_t)0x3B)
#define RCC_FLAG_PLL3STB                 ((uint8_t)0x3D)

#endif/* GD32F10X_CL */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions
  * @{
  */
/* Reset the RCC clock configuration to the default reset state */

void RCC_DeInit(void);

/* Internal/external clocks, PLL, CKM and CK_OUT configuration functions */

void RCC_HSEConfig(uint32_t RCC_HSE);
TypeState RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSI_Enable(TypeState NewValue);
void RCC_PLLConfig(uint32_t RCC_PLLSelect, uint32_t RCC_PLLMF);
void RCC_PLL_Enable(TypeState NewValue);
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSI_Enable(TypeState NewValue);
void RCC_HSEClockMonitor_Enable(TypeState NewValue);
void RCC_CKOUTSRCConfig(uint32_t RCC_CKOUTSRC);

#ifdef  GD32F10X_CL
void RCC_PREDV1Config(uint32_t RCC_PREDV1_Source, uint32_t RCC_PREDV1_Div);
void RCC_PREDV2Config(uint32_t RCC_PREDV2_Div);
void RCC_PLL2Config(uint32_t RCC_PLL2MF);
void RCC_PLL2_Enable(TypeState NewValue);
void RCC_PLL3Config(uint32_t RCC_PLL3MF);
void RCC_PLL3_Enable(TypeState NewValue);
#endif /* GD32F10X_CL */

/* System, AHB, APB1 and APB2 busses clocks configuration functions */

void RCC_CK_SYSConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetCK_SYSSource(void);
void RCC_AHBConfig(uint32_t RCC_CK_SYSDiv);
void RCC_APB1Config(uint32_t RCC_APB1);
void RCC_APB2Config(uint32_t RCC_APB2);

#ifndef GD32F10X_CL
void RCC_USBCLKConfig(uint32_t RCC_USBCLK);
#else
void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLK);
#endif /* GD32F10X_CL */

void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK);

#ifdef GD32F10X_CL
void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLK);
void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLK);
#endif /* GD32F10X_CL */

void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_GetClocksFreq(RCC_ClocksPara *RCC_Clocks);

/* Peripheral clocks configuration functions */

void RCC_AHBPeriphClock_Enable(uint32_t RCC_AHBPeriph, TypeState NewValue);
void RCC_APB2PeriphClock_Enable(uint32_t RCC_APB2Periph, TypeState NewValue);
void RCC_APB1PeriphClock_Enable(uint32_t RCC_APB1Periph, TypeState NewValue);
void RCC_RTCCLK_Enable(TypeState NewValue);

#ifdef GD32F10X_CL
void RCC_AHBPeriphReset_Enable(uint32_t RCC_AHBPeriphRST, TypeState NewValue);
#endif /* GD32F10X_CL */

void RCC_APB2PeriphReset_Enable(uint32_t RCC_APB2PeriphRST, TypeState NewValue);
void RCC_APB1PeriphReset_Enable(uint32_t RCC_APB1PeriphRST, TypeState NewValue);
void RCC_BackupReset_Enable(TypeState NewValue);

/* Interrupts and flags management functions */

void RCC_INTConfig(uint8_t RCC_INT, TypeState NewValue);
TypeState RCC_GetIntBitState(uint8_t RCC_INT);
void RCC_ClearIntBitState(uint8_t RCC_INT);
TypeState RCC_GetBitState(uint8_t RCC_FLAG);
void RCC_ClearBitState(void);

void RCC_KERNELVOLConfig(uint32_t RCC_KERNEL_VOL);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10x_RCC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

