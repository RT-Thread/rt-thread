/**
  *********************************************************************************
  *
  * @file    ald_cmu.h
  * @brief   Header file of CMU module driver.
  *
  * @version V1.0
  * @date    22 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_CMU_H__
#define __ALD_CMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "ald_syscfg.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup CMU
  * @{
  */

/** @defgroup CMU_Public_Macros CMU Public Macros
  * @{
  */
#define CMU_HRC_SEL_BY_SW()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->CFGR, CMU_CFGR_HRCFCS_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_HRC_SEL_BY_CFGW()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->CFGR, CMU_CFGR_HRCFCS_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_HRC_DIV_1MHZ_ENABLE()			\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->CLKENR, CMU_CLKENR_HRC1MEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_HRC_DIV_1MHZ_DISABLE()			\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HRC1MEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_HOSC_DIV_1MHZ_ENABLE()			\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSC1MEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_HOSC_DIV_1MHZ_DISABLE()			\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSC1MEN_MSK);\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LOSC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LOSC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LRC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LRC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_ULRC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->CLKENR, CMU_CLKENR_ULRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_ULRC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_ULRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)

/* Low power mode control */
#define CMU_LP_LRC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->LPENR, CMU_LPENR_LRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_LRC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_LRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_LOSC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->LPENR, CMU_LPENR_LOSCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_LOSC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_LOSCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_HRC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->LPENR, CMU_LPENR_HRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_HRC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_HRCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_HOSC_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(CMU->LPENR, CMU_LPENR_HOSCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define CMU_LP_HOSC_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(CMU->LPENR, CMU_LPENR_HOSCEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
/**
  * @}
  */


/** @defgroup CMU_Public_Types CMU Public Types
  * @{
  */
/**
  * @brief CMU state structure definition
  */
typedef	enum {
	CMU_CLOCK_HRC  = 0x1U,	/**< HRC */
	CMU_CLOCK_LRC  = 0x2U,	/**< LRC */
	CMU_CLOCK_LOSC = 0x3U,	/**< LOSC */
	CMU_CLOCK_PLL1 = 0x4U,	/**< PLL1 */
	CMU_CLOCK_HOSC = 0x5U,	/**< HOSC */
} cmu_clock_t;

/**
  * @brief PLL1 output clock
  */
typedef enum {
	CMU_PLL1_OUTPUT_36M = 0x0U,	/**< x9  (36MHz) */
	CMU_PLL1_OUTPUT_48M = 0x1U,	/**< x12 (48MHz) */
#if defined(ES32F36xx) || defined(ES32F39xx)
	CMU_PLL1_OUTPUT_72M = 0x2U,	/**< x18 (72MHz) */
	CMU_PLL1_OUTPUT_96M = 0x3U,	/**< x24 (96MHz) */
#endif
} cmu_pll1_output_t;

/**
  * @brief PLL1 referance clock
  */
typedef enum {
	CMU_PLL1_INPUT_HRC_6  = 0x0U,	/**< HRC  / 6 */
	CMU_PLL1_INPUT_PLL2   = 0x1U,	/**< PLL2 */
	CMU_PLL1_INPUT_HOSC   = 0x2U,	/**< HOSC / 1 */
	CMU_PLL1_INPUT_HOSC_2 = 0x3U,	/**< HOSC / 2 */
	CMU_PLL1_INPUT_HOSC_3 = 0x4U,	/**< HOSC / 3 */
	CMU_PLL1_INPUT_HOSC_4 = 0x5U,	/**< HOSC / 4 */
	CMU_PLL1_INPUT_HOSC_5 = 0x6U,	/**< HOSC / 5 */
	CMU_PLL1_INPUT_HOSC_6 = 0x7U,	/**< HOSC / 6 */
} cmu_pll1_input_t;

/**
  * @brief HOSC range
  */
typedef enum {
	CMU_HOSC_2M  = 0x0U,	/**< 0~2MHz */
	CMU_HOSC_4M  = 0x1U,	/**< 2~4MHz */
	CMU_HOSC_8M  = 0x2U,	/**< 4~8MHz */
	CMU_HOSC_16M = 0x3U,	/**< 8~16MHz */
	CMU_HOSC_24M = 0x4U,	/**< 16~24MHz */
} cmu_hosc_range_t;

/**
  * @brief Safe clock source type
  */
typedef enum {
	CMU_SAFE_CLK_HOSC = 0x0U,	/**< HOSC */
	CMU_SAFE_CLK_LOSC = 0x1U,	/**< LOSC */
	CMU_SAFE_CLK_PLL  = 0x2U,	/**< PLL */
} cmu_clock_safe_type_t;

/**
  * @brief Frequency division select bit
  */
typedef enum {
	CMU_DIV_1    = 0x0U,	/**< Division by 1 */
	CMU_DIV_2    = 0x1U,	/**< Division by 2 */
	CMU_DIV_4    = 0x2U,	/**< Division by 4 */
	CMU_DIV_8    = 0x3U,	/**< Division by 8 */
	CMU_DIV_16   = 0x4U,	/**< Division by 16 */
	CMU_DIV_32   = 0x5U,	/**< Division by 32 */
	CMU_DIV_64   = 0x6U,	/**< Division by 64 */
	CMU_DIV_128  = 0x7U,	/**< Division by 128 */
	CMU_DIV_256  = 0x8U,	/**< Division by 256 */
	CMU_DIV_512  = 0x9U,	/**< Division by 512 */
	CMU_DIV_1024 = 0xAU,	/**< Division by 1024 */
	CMU_DIV_2048 = 0xBU,	/**< Division by 2048 */
	CMU_DIV_4096 = 0xCU,	/**< Division by 4096 */
} cmu_div_t;

/**
  * @brief Bus type
  */
typedef enum {
	CMU_HCLK_1 = 0x0U,	/**< AHB1 bus */
	CMU_HCLK_2 = 0x1U,	/**< AHB2 bus */
	CMU_SYS    = 0x2U,	/**< SYS bus */
	CMU_PCLK_1 = 0x3U,	/**< APB1 bus */
	CMU_PCLK_2 = 0x4U,	/**< APB2 bus */
} cmu_bus_t;

/**
  * @brief Output high clock select
  */
typedef enum {
	CMU_OUTPUT_HIGH_SEL_HOSC   = 0x0U,	/**< Select HOSC */
	CMU_OUTPUT_HIGH_SEL_LOSC   = 0x1U,	/**< Select LOSC */
	CMU_OUTPUT_HIGH_SEL_HRC    = 0x2U,	/**< Select HRC */
	CMU_OUTPUT_HIGH_SEL_LRC    = 0x3U,	/**< Select LRC */
	CMU_OUTPUT_HIGH_SEL_HOSM   = 0x4U,	/**< Select HOSM */
	CMU_OUTPUT_HIGH_SEL_PLL1   = 0x5U,	/**< Select PLL1 */
	CMU_OUTPUT_HIGH_SEL_PLL2   = 0x6U,	/**< Select PLL2 */
	CMU_OUTPUT_HIGH_SEL_SYSCLK = 0x7U,	/**< Select SYSCLK */
} cmu_output_high_sel_t;

/**
  * @brief Output frequency division
  */
typedef enum {
	CMU_OUTPUT_DIV_1   = 0x0U,	/**< Division by 1 */
	CMU_OUTPUT_DIV_2   = 0x1U,	/**< Division by 2 */
	CMU_OUTPUT_DIV_4   = 0x2U,	/**< Division by 4 */
	CMU_OUTPUT_DIV_8   = 0x3U,	/**< Division by 8 */
	CMU_OUTPUT_DIV_16  = 0x4U,	/**< Division by 16 */
	CMU_OUTPUT_DIV_32  = 0x5U,	/**< Division by 32 */
	CMU_OUTPUT_DIV_64  = 0x6U,	/**< Division by 64 */
	CMU_OUTPUT_DIV_128 = 0x7U,	/**< Division by 128 */
} cmu_output_high_div_t;

/**
  * @brief Output low clock select
  */
typedef enum {
	CMU_OUTPUT_LOW_SEL_LOSC = 0x0U,	/**< Select LOSC */
	CMU_OUTPUT_LOW_SEL_LRC  = 0x1U,	/**< Select LRC */
	CMU_OUTPUT_LOW_SEL_LOSM = 0x2U,	/**< Select LOSM */
	CMU_OUTPUT_LOW_SEL_BUZZ = 0x3U,	/**< Select BUZZ */
	CMU_OUTPUT_LOW_SEL_ULRC = 0x4U,	/**< Select ULRC */
} cmu_output_low_sel_t;

/**
  * @brief BUZZ frequency division
  */
typedef enum {
	CMU_BUZZ_DIV_2   = 0x0U,	/**< Division by 2 */
	CMU_BUZZ_DIV_4   = 0x1U,	/**< Division by 4 */
	CMU_BUZZ_DIV_8   = 0x2U,	/**< Division by 8 */
	CMU_BUZZ_DIV_16  = 0x3U,	/**< Division by 16 */
	CMU_BUZZ_DIV_32  = 0x4U,	/**< Division by 32 */
	CMU_BUZZ_DIV_64  = 0x5U,	/**< Division by 64 */
	CMU_BUZZ_DIV_128 = 0x6U,	/**< Division by 128 */
	CMU_BUZZ_DIV_256 = 0x7U,	/**< Division by 256 */
} cmu_buzz_div_t;

/**
  * @brief Low power peripheral clock select
  */
typedef enum {
	CMU_LP_PERH_CLOCK_SEL_PCLK2   = 0x0U,	/**< Select PCLK2 */
	CMU_LP_PERH_CLOCK_SEL_PLL1    = 0x1U,	/**< Select PLL1 */
	CMU_LP_PERH_CLOCK_SEL_PLL2    = 0x2U,	/**< Select PLL2 */
	CMU_LP_PERH_CLOCK_SEL_HRC     = 0x3U,	/**< Select HRC */
	CMU_LP_PERH_CLOCK_SEL_HOSC    = 0x4U,	/**< Select HOSC */
	CMU_LP_PERH_CLOCK_SEL_LRC     = 0x5U,	/**< Select LRC */
	CMU_LP_PERH_CLOCK_SEL_LOSC    = 0x6U,	/**< Select LOSC */
	CMU_LP_PERH_CLOCK_SEL_ULRC    = 0x7U,	/**< Select ULRC */
	CMU_LP_PERH_CLOCK_SEL_HRC_1M  = 0x8U,	/**< Select HRC down to 1MHz */
	CMU_LP_PERH_CLOCK_SEL_HOSC_1M = 0x9U,	/**< Select HOSC down to 1MHz  */
	CMU_LP_PERH_CLOCK_SEL_LOSM    = 0xAU,	/**< Select LOSM */
	CMU_LP_PERH_CLOCK_SEL_HOSM    = 0xBU,	/**< Select HOSM */
} cmu_lp_perh_clock_sel_t;

/**
  * @brief LCD clock select
  */
typedef enum {
	CMU_LCD_SEL_LOSM    = 0x0U,	/**< Select LOSM */
	CMU_LCD_SEL_LOSC    = 0x1U,	/**< Select LOSC */
	CMU_LCD_SEL_LRC     = 0x2U,	/**< Select LRC */
	CMU_LCD_SEL_ULRC    = 0x3U,	/**< Select ULRC */
	CMU_LCD_SEL_HRC_1M  = 0x4U,	/**< Select HRC down to 1MHz */
	CMU_LCD_SEL_HOSC_1M = 0x5U,	/**< Select HOSC down to 1MHz */
} cmu_lcd_clock_sel_t;

/**
  * @brief QSPI clock select
  */
typedef enum {
	CMU_QSPI_CLOCK_SEL_PCLK1 = 0x0U,	/**< Select PCLK1 */
	CMU_QSPI_CLOCK_SEL_HCLK2 = 0x1U,	/**< Select HCLK2 */
	CMU_QSPI_CLOCK_SEL_HRC   = 0x2U,	/**< Select HRC */
	CMU_QSPI_CLOCK_SEL_HOSC  = 0x3U,	/**< Select HOSC */
	CMU_QSPI_CLOCK_SEL_PLL1  = 0x4U,	/**< Select PLL1 */
	CMU_QSPI_CLOCK_SEL_HOSM  = 0x5U,	/**< Select HOSC security management */
} cmu_qspi_clock_sel_t;

/**
  * @brief USB clock select
  */
typedef enum {
	CMU_USB_CLOCK_SEL_HOSC  = 0x0U,	/**< Select HOSC */
	CMU_USB_CLOCK_SEL_HRC   = 0x1U,	/**< Select HRC */
	CMU_USB_CLOCK_SEL_PCLK1 = 0x2U,	/**< Select PCLK1 */
	CMU_USB_CLOCK_SEL_PLL1  = 0x3U,	/**< Select PLL1 */
	CMU_USB_CLOCK_SEL_HOSM  = 0x4U,	/**< Select HOSC security management */
} cmu_usb_clock_sel_t;

/**
  * @brief USB clock division
  */
typedef enum {
	CMU_USB_DIV_1    = 0x0U,	/**< Division by 1 */
	CMU_USB_DIV_2    = 0x1U,	/**< Division by 2 */
	CMU_USB_DIV_4    = 0x2U,	/**< Division by 4 */
	CMU_USB_DIV_8    = 0x3U,	/**< Division by 8 */
	CMU_USB_DIV_16   = 0x4U,	/**< Division by 16 */
	CMU_USB_DIV_32   = 0x5U,	/**< Division by 32 */
	CMU_USB_DIV_64   = 0x6U,	/**< Division by 64 */
	CMU_USB_DIV_128  = 0x7U,	/**< Division by 128 */
	CMU_USB_DIV_256  = 0x8U,	/**< Division by 256 */
	CMU_USB_DIV_512  = 0x9U,	/**< Division by 512 */
	CMU_USB_DIV_1024 = 0xAU,	/**< Division by 1024 */
	CMU_USB_DIV_2048 = 0xBU,	/**< Division by 2048 */
	CMU_USB_DIV_4096 = 0xCU,	/**< Division by 4096 */
} cmu_usb_div_t;

/**
  * @brief Peripheral clock enable/disable
  * @verbatim
      In this module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> AD16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T0
      TIMER7 ----> GP16C4T1

      2. For ES32F393x/ES32F336x/ES32F392x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> GP16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T2
      TIMER7 ----> GP16C4T3
    @endverbatim
  */
typedef enum {
	CMU_PERH_GPIO    = (1U << 0),			/**< GPIO */
	CMU_PERH_CRC     = (1U << 1),			/**< CRC */
	CMU_PERH_CALC    = (1U << 2),			/**< CALC */
	CMU_PERH_CRYPT   = (1U << 3),			/**< CRYPT */
	CMU_PERH_TRNG    = (1U << 4),			/**< TRNG */
	CMU_PERH_PIS     = (1U << 5),			/**< PIS */
	CMU_PERH_EBI     = (1U << 6),			/**< EBI */
	CMU_PERH_QSPI_H  = (1U << 7),			/**< QSPI AHB */
	CMU_PERH_DMA     = (1U << 8),			/**< DMA */
	CMU_PERH_USB     = (1U << 10),			/**< USB */
	CMU_PERH_ECC     = (1U << 11),			/**< ECC */
	CMU_PERH_TIMER0  = (1U << 0)  | (1U << 27),	/**< TIMER0 */
	CMU_PERH_TIMER1  = (1U << 1)  | (1U << 27),	/**< TIMER1 */
	CMU_PERH_TIMER2  = (1U << 2)  | (1U << 27),	/**< TIMER2 */
	CMU_PERH_TIMER3  = (1U << 3)  | (1U << 27),	/**< TIMER3 */
	CMU_PERH_TIMER4  = (1U << 4)  | (1U << 27),	/**< TIMER4 */
	CMU_PERH_TIMER5  = (1U << 5)  | (1U << 27),	/**< TIMER5 */
	CMU_PERH_TIMER6  = (1U << 6)  | (1U << 27),	/**< TIMER6 */
	CMU_PERH_TIMER7  = (1U << 7)  | (1U << 27),	/**< TIMER7 */
	CMU_PERH_UART0   = (1U << 8)  | (1U << 27),	/**< UART0 */
	CMU_PERH_UART1   = (1U << 9)  | (1U << 27),	/**< UART1 */
	CMU_PERH_UART2   = (1U << 10) | (1U << 27),	/**< UART2 */
	CMU_PERH_UART3   = (1U << 11) | (1U << 27),	/**< UART3 */
	CMU_PERH_UART4   = (1U << 12) | (1U << 27),	/**< UART4 */
	CMU_PERH_UART5   = (1U << 13) | (1U << 27),	/**< UART5 */
	CMU_PERH_SPI0    = (1U << 16) | (1U << 27),	/**< SPI0 */
	CMU_PERH_SPI1    = (1U << 17) | (1U << 27),	/**< SPI1 */
	CMU_PERH_SPI2    = (1U << 18) | (1U << 27),	/**< SPI2 */
	CMU_PERH_I2C0    = (1U << 20) | (1U << 27),	/**< I2C0 */
	CMU_PERH_I2C1    = (1U << 21) | (1U << 27),	/**< I2C1 */
	CMU_PERH_CAN     = (1U << 24) | (1U << 27),	/**< CAN */
	CMU_PERH_QSPI_P  = (1U << 25) | (1U << 27),	/**< QSPI APB */
	CMU_PERH_LPTIM0  = (1U << 0)  | (1U << 28),	/**< LPTIM0 */
	CMU_PERH_LPUART0 = (1U << 2)  | (1U << 28),	/**< LPUART0 */
	CMU_PERH_ADC0    = (1U << 4)  | (1U << 28),	/**< ADC0 */
	CMU_PERH_ADC1    = (1U << 5)  | (1U << 28),	/**< ADC1 */
	CMU_PERH_ACMP0   = (1U << 6)  | (1U << 28),	/**< ACMP0 */
	CMU_PERH_ACMP1   = (1U << 7)  | (1U << 28),	/**< ACMP1 */
	CMU_PERH_OPAMP   = (1U << 8)  | (1U << 28),	/**< OPAMP */
	CMU_PERH_DAC0    = (1U << 9)  | (1U << 28),	/**< DAC0 */
	CMU_PERH_ACMP2   = (1U << 11) | (1U << 28),	/**< ACMP2 */
	CMU_PERH_WWDT    = (1U << 12) | (1U << 28),	/**< WWDT */
	CMU_PERH_LCD     = (1U << 13) | (1U << 28),	/**< LCD */
	CMU_PERH_IWDT    = (1U << 14) | (1U << 28),	/**< IWDT */
	CMU_PERH_RTC     = (1U << 15) | (1U << 28),	/**< RTC */
	CMU_PERH_TSENSE  = (1U << 16) | (1U << 28),	/**< TSENSE */
	CMU_PERH_BKPC    = (1U << 17) | (1U << 28),	/**< BKPC */
	CMU_PERH_DBGC    = (1U << 19) | (1U << 28),	/**< DBGC */
	CMU_PERH_ALL     = (0x7FFFFFFFU),		/**< ALL */
} cmu_perh_t;

/**
  * @brief CMU interrupt type
  */
typedef enum {
	CMU_LOSC_STOP    = 0x0U,	/**< LOSC STOP INTERRUPT */
	CMU_HOSC_STOP    = 0x1U,	/**< HOSC STOP INTERRUPT */
	CMU_PLL1_UNLOCK  = 0x2U,	/**< PLL1 UNLOCK INTERRUPT */
	CMU_LOSC_START   = 0x3U,	/**< LOSC START INTERRUPT */
	CMU_HOSC_START   = 0x4U,	/**< HOSC START INTERRUPT */
} cmu_security_t;

/**
  * @brief CMU clock state type
  */
typedef enum {
	CMU_CLOCK_STATE_HOSCACT = (1U << 0),	/**< HOSC active */
	CMU_CLOCK_STATE_LOSCACT = (1U << 1),	/**< LOSC active */
	CMU_CLOCK_STATE_HRCACT  = (1U << 2),	/**< HRC active */
	CMU_CLOCK_STATE_LRCACT  = (1U << 3),	/**< LRC active */
	CMU_CLOCK_STATE_ULRCACT = (1U << 4),	/**< ULRC active */
	CMU_CLOCK_STATE_PLL1ACT = (1U << 8),	/**< PLL1 active */
	CMU_CLOCK_STATE_PLL2ACT = (1U << 9),	/**< PLL2 active */
	CMU_CLOCK_STATE_HOSCRDY = (1U << 16),	/**< HOSC ready */
	CMU_CLOCK_STATE_LOSCRDY = (1U << 17),	/**< LOSC ready */
	CMU_CLOCK_STATE_HRCRDY  = (1U << 18),	/**< HRC ready */
	CMU_CLOCK_STATE_LRCRDY  = (1U << 19),	/**< LRC ready */
	CMU_CLOCK_STATE_PLL1RDY = (1U << 24),	/**< PLL1 ready */
	CMU_CLOCK_STATE_PLL2RDY = (1U << 25),	/**< PLL2 ready */
} cmu_clock_state_t;

/**
  * @brief Stop1 clock select type
  */
typedef enum {
	CMU_STOP1_CLOCK_LRC     = 0x0U,	/**< LRC */
	CMU_STOP1_CLOCK_HRC_24M = 0x1U,	/**< HRC 24MHz */
	CMU_STOP1_CLOCK_HRC_2M  = 0x2U,	/**< HRC 2MHz */
	CMU_STOP1_CLOCK_HRC_1M  = 0x3U,	/**< HRC divides to 1MHz */
	CMU_STOP1_CLOCK_HOSC    = 0x4U,	/**< HOSC */
	CMU_STOP1_CLOCK_HOSC_1M = 0x5U,	/**< HOSC divides to 1MHz */
	CMU_STOP1_CLOCK_HOSCM   = 0x6U,	/**< HOSC security management */
} cmu_stop1_clock_t;

/**
  * @}
  */

/**
  * @defgroup CMU_Private_Macros CMU Private Macros
  * @{
  */
#define IS_CMU_CLOCK(x)		(((x) == CMU_CLOCK_HRC)  || \
                                 ((x) == CMU_CLOCK_LRC)  || \
                                 ((x) == CMU_CLOCK_LOSC) || \
                                 ((x) == CMU_CLOCK_PLL1) || \
                                 ((x) == CMU_CLOCK_HOSC))
#if defined(ES32F36xx) || defined(ES32F39xx)
#define IS_CMU_PLL1_OUTPUT(x)	(((x) == CMU_PLL1_OUTPUT_36M) || \
                                 ((x) == CMU_PLL1_OUTPUT_48M) || \
                                 ((x) == CMU_PLL1_OUTPUT_72M) || \
                                 ((x) == CMU_PLL1_OUTPUT_96M))
#endif
#ifdef ES32F336x
#define IS_CMU_PLL1_OUTPUT(x)	(((x) == CMU_PLL1_OUTPUT_36M) || \
                                 ((x) == CMU_PLL1_OUTPUT_48M))
#endif
#define IS_CMU_PLL1_INPUT(x)	(((x) == CMU_PLL1_INPUT_HRC_6)  || \
                                 ((x) == CMU_PLL1_INPUT_PLL2)   || \
                                 ((x) == CMU_PLL1_INPUT_HOSC)   || \
                                 ((x) == CMU_PLL1_INPUT_HOSC_2) || \
                                 ((x) == CMU_PLL1_INPUT_HOSC_3) || \
                                 ((x) == CMU_PLL1_INPUT_HOSC_4) || \
                                 ((x) == CMU_PLL1_INPUT_HOSC_5) || \
                                 ((x) == CMU_PLL1_INPUT_HOSC_6))
#define IS_CMU_HOSC_RANGE(x)	(((x) == CMU_HOSC_2M)  || \
                                 ((x) == CMU_HOSC_4M)  || \
                                 ((x) == CMU_HOSC_8M)  || \
                                 ((x) == CMU_HOSC_16M) || \
                                 ((x) == CMU_HOSC_24M))
#define IS_CMU_DIV(x)		(((x) == CMU_DIV_1)    || \
                                 ((x) == CMU_DIV_2)    || \
                                 ((x) == CMU_DIV_4)    || \
                                 ((x) == CMU_DIV_8)    || \
                                 ((x) == CMU_DIV_16)   || \
                                 ((x) == CMU_DIV_32)   || \
                                 ((x) == CMU_DIV_64)   || \
                                 ((x) == CMU_DIV_128)  || \
                                 ((x) == CMU_DIV_256)  || \
                                 ((x) == CMU_DIV_512)  || \
                                 ((x) == CMU_DIV_1024) || \
                                 ((x) == CMU_DIV_2048) || \
                                 ((x) == CMU_DIV_4096))
#define IS_CMU_BUS(x)		(((x) == CMU_HCLK_1) || \
                                 ((x) == CMU_HCLK_2) || \
                                 ((x) == CMU_SYS)    || \
                                 ((x) == CMU_PCLK_1) || \
                                 ((x) == CMU_PCLK_2))
#define IS_CMU_OUTPUT_HIGH_SEL(x)	(((x) == CMU_OUTPUT_HIGH_SEL_HOSC) || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_LOSC) || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_HRC)  || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_LRC)  || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_HOSM) || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_PLL1) || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_PLL2) || \
                                         ((x) == CMU_OUTPUT_HIGH_SEL_SYSCLK))
#define IS_CMU_OUTPUT_HIGH_DIV(x)	(((x) == CMU_OUTPUT_DIV_1)  || \
                                         ((x) == CMU_OUTPUT_DIV_2)  || \
                                         ((x) == CMU_OUTPUT_DIV_4)  || \
                                         ((x) == CMU_OUTPUT_DIV_8)  || \
                                         ((x) == CMU_OUTPUT_DIV_16) || \
                                         ((x) == CMU_OUTPUT_DIV_32) || \
                                         ((x) == CMU_OUTPUT_DIV_64) || \
                                         ((x) == CMU_OUTPUT_DIV_128))
#define IS_CMU_OUTPUT_LOW_SEL(x)	(((x) == CMU_OUTPUT_LOW_SEL_LOSC) || \
                                         ((x) == CMU_OUTPUT_LOW_SEL_LRC ) || \
                                         ((x) == CMU_OUTPUT_LOW_SEL_LOSM) || \
                                         ((x) == CMU_OUTPUT_LOW_SEL_BUZZ) || \
                                         ((x) == CMU_OUTPUT_LOW_SEL_ULRC))
#define IS_CMU_SAFE_CLOCK_TYPE(x)	(((x) == CMU_SAFE_CLK_HOSC) || \
                                         ((x) == CMU_SAFE_CLK_LOSC) || \
                                         ((x) == CMU_SAFE_CLK_PLL))
#define IS_CMU_BUZZ_DIV(x)	(((x) == CMU_BUZZ_DIV_2)   || \
                                 ((x) == CMU_BUZZ_DIV_4)   || \
                                 ((x) == CMU_BUZZ_DIV_8)   || \
                                 ((x) == CMU_BUZZ_DIV_16)  || \
                                 ((x) == CMU_BUZZ_DIV_32)  || \
                                 ((x) == CMU_BUZZ_DIV_64)  || \
                                 ((x) == CMU_BUZZ_DIV_128) || \
                                 ((x) == CMU_BUZZ_DIV_256))
#define IS_CMU_LP_PERH_CLOCK_SEL(x)	(((x) == CMU_LP_PERH_CLOCK_SEL_PCLK2)   || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_PLL1)    || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_PLL2)    || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_HRC)     || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_HOSC)    || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_LRC)     || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_LOSC)    || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_ULRC)    || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_HRC_1M)  || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_HOSC_1M) || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_LOSM)    || \
                                         ((x) == CMU_LP_PERH_CLOCK_SEL_HOSM))
#define IS_CMU_LCD_CLOCK_SEL(x)	(((x) == CMU_LCD_SEL_LOSM)   || \
                                 ((x) == CMU_LCD_SEL_LOSC)   || \
                                 ((x) == CMU_LCD_SEL_LRC)    || \
                                 ((x) == CMU_LCD_SEL_ULRC)   || \
                                 ((x) == CMU_LCD_SEL_HRC_1M) || \
                                 ((x) == CMU_LCD_SEL_HOSC_1M))
#define IS_CMU_QSPI_CLOCK_SEL(x)	(((x) == CMU_QSPI_CLOCK_SEL_PCLK1) || \
                                         ((x) == CMU_QSPI_CLOCK_SEL_HCLK2) || \
                                         ((x) == CMU_QSPI_CLOCK_SEL_HRC)   || \
                                         ((x) == CMU_QSPI_CLOCK_SEL_HOSC)  || \
                                         ((x) == CMU_QSPI_CLOCK_SEL_PLL1)  || \
                                         ((x) == CMU_QSPI_CLOCK_SEL_HOSM))
#define IS_CMU_USB_CLOCK_SEL(x)	(((x) == CMU_USB_CLOCK_SEL_HOSC)  || \
                                 ((x) == CMU_USB_CLOCK_SEL_HRC)   || \
                                 ((x) == CMU_USB_CLOCK_SEL_PCLK1) || \
                                 ((x) == CMU_USB_CLOCK_SEL_PLL1)  || \
                                 ((x) == CMU_USB_CLOCK_SEL_HOSM))
#define IS_CMU_USB_DIV(x)	(((x) == CMU_USB_DIV_1)    || \
                                 ((x) == CMU_USB_DIV_2)    || \
                                 ((x) == CMU_USB_DIV_4)    || \
                                 ((x) == CMU_USB_DIV_8)    || \
                                 ((x) == CMU_USB_DIV_16)   || \
                                 ((x) == CMU_USB_DIV_32)   || \
                                 ((x) == CMU_USB_DIV_64)   || \
                                 ((x) == CMU_USB_DIV_128)  || \
                                 ((x) == CMU_USB_DIV_256)  || \
                                 ((x) == CMU_USB_DIV_512)  || \
                                 ((x) == CMU_USB_DIV_1024) || \
                                 ((x) == CMU_USB_DIV_2048) || \
                                 ((x) == CMU_USB_DIV_4096))
#define IS_CMU_PERH(x)		(((x) == CMU_PERH_GPIO)    || \
                                 ((x) == CMU_PERH_CRC)     || \
                                 ((x) == CMU_PERH_CALC)    || \
                                 ((x) == CMU_PERH_CRYPT)   || \
                                 ((x) == CMU_PERH_TRNG)    || \
                                 ((x) == CMU_PERH_PIS)     || \
				 ((x) == CMU_PERH_EBI)     || \
				 ((x) == CMU_PERH_QSPI_H)  || \
				 ((x) == CMU_PERH_DMA)     || \
				 ((x) == CMU_PERH_USB)     || \
				 ((x) == CMU_PERH_ECC)     || \
                                 ((x) == CMU_PERH_TIMER0)  || \
                                 ((x) == CMU_PERH_TIMER1)  || \
                                 ((x) == CMU_PERH_TIMER2)  || \
                                 ((x) == CMU_PERH_TIMER3)  || \
                                 ((x) == CMU_PERH_TIMER4)  || \
                                 ((x) == CMU_PERH_TIMER5)  || \
                                 ((x) == CMU_PERH_TIMER6)  || \
                                 ((x) == CMU_PERH_TIMER7)  || \
                                 ((x) == CMU_PERH_UART0)   || \
                                 ((x) == CMU_PERH_UART1)   || \
                                 ((x) == CMU_PERH_UART2)   || \
                                 ((x) == CMU_PERH_UART3)   || \
                                 ((x) == CMU_PERH_UART4)   || \
                                 ((x) == CMU_PERH_UART5)   || \
                                 ((x) == CMU_PERH_SPI0)    || \
                                 ((x) == CMU_PERH_SPI1)    || \
                                 ((x) == CMU_PERH_SPI2)    || \
                                 ((x) == CMU_PERH_I2C0)    || \
                                 ((x) == CMU_PERH_I2C1)    || \
                                 ((x) == CMU_PERH_CAN)     || \
				 ((x) == CMU_PERH_QSPI_P)  || \
                                 ((x) == CMU_PERH_LPTIM0)  || \
                                 ((x) == CMU_PERH_LPUART0) || \
                                 ((x) == CMU_PERH_ADC0)    || \
                                 ((x) == CMU_PERH_ADC1)    || \
                                 ((x) == CMU_PERH_ACMP0)   || \
                                 ((x) == CMU_PERH_ACMP1)   || \
                                 ((x) == CMU_PERH_OPAMP)   || \
                                 ((x) == CMU_PERH_DAC0)    || \
				 ((x) == CMU_PERH_ACMP2)   || \
                                 ((x) == CMU_PERH_WWDT)    || \
                                 ((x) == CMU_PERH_LCD)     || \
                                 ((x) == CMU_PERH_IWDT)    || \
                                 ((x) == CMU_PERH_RTC)     || \
                                 ((x) == CMU_PERH_TSENSE)  || \
                                 ((x) == CMU_PERH_BKPC)    || \
                                 ((x) == CMU_PERH_DBGC)    || \
                                 ((x) == CMU_PERH_ALL))
#define IS_CMU_CLOCK_STATE(x)	(((x) == CMU_CLOCK_STATE_HOSCACT) || \
                                 ((x) == CMU_CLOCK_STATE_LOSCACT) || \
				 ((x) == CMU_CLOCK_STATE_HRCACT)  || \
				 ((x) == CMU_CLOCK_STATE_LRCACT)  || \
				 ((x) == CMU_CLOCK_STATE_ULRCACT) || \
				 ((x) == CMU_CLOCK_STATE_PLL1ACT) || \
				 ((x) == CMU_CLOCK_STATE_PLL2ACT) || \
				 ((x) == CMU_CLOCK_STATE_HOSCRDY) || \
				 ((x) == CMU_CLOCK_STATE_LOSCRDY) || \
				 ((x) == CMU_CLOCK_STATE_HRCRDY)  || \
				 ((x) == CMU_CLOCK_STATE_LRCRDY)  || \
				 ((x) == CMU_CLOCK_STATE_PLL1RDY) || \
				 ((x) == CMU_CLOCK_STATE_PLL2RDY))
#define IS_CMU_STOP1_CLOCK(x)	(((x) == CMU_STOP1_CLOCK_LRC) || \
                                 ((x) == CMU_STOP1_CLOCK_HRC_24M) || \
				 ((x) == CMU_STOP1_CLOCK_HRC_2M)  || \
				 ((x) == CMU_STOP1_CLOCK_HRC_1M)  || \
				 ((x) == CMU_STOP1_CLOCK_HOSC) || \
				 ((x) == CMU_STOP1_CLOCK_HOSC_1M) || \
				 ((x) == CMU_STOP1_CLOCK_HOSCM))
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions
  * @{
  */
/** @addtogroup CMU_Public_Functions_Group1
  * @{
  */
/* System clock configure */
ald_status_t ald_cmu_clock_config_default(void);
ald_status_t ald_cmu_clock_config(cmu_clock_t clk, uint32_t clock);
void ald_cmu_pll1_config(cmu_pll1_input_t input, cmu_pll1_output_t output);
uint32_t ald_cmu_get_clock(void);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group2
  * @{
  */
/* BUS division control */
void ald_cmu_div_config(cmu_bus_t bus, cmu_div_t div);
uint32_t ald_cmu_get_hclk1_clock(void);
uint32_t ald_cmu_get_hclk2_clock(void);
uint32_t ald_cmu_get_sys_clock(void);
uint32_t ald_cmu_get_pclk1_clock(void);
uint32_t ald_cmu_get_pclk2_clock(void);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group3
  * @{
  */
/* Clock safe configure */
void ald_cmu_hosc_safe_config(cmu_hosc_range_t clock, type_func_t status);
void ald_cmu_losc_safe_config(type_func_t status);
void ald_cmu_pll_safe_config(type_func_t status);
uint32_t ald_cmu_current_clock_source_get(cmu_clock_safe_type_t type);
flag_status_t ald_cmu_get_clock_state(cmu_clock_state_t sr);
void ald_cmu_irq_handler(void);
void ald_cmu_irq_cbk(cmu_security_t se);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group4
  * @{
  */
/* Clock output configure */
void ald_cmu_output_high_clock_config(cmu_output_high_sel_t sel,
		cmu_output_high_div_t div, type_func_t status);
void ald_cmu_output_low_clock_config(cmu_output_low_sel_t sel, type_func_t status);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group5
  * @{
  */
/* Peripheral Clock configure */
void ald_cmu_buzz_config(cmu_buzz_div_t div, uint16_t dat, type_func_t status);
void ald_cmu_lptim0_clock_select(cmu_lp_perh_clock_sel_t clock);
void ald_cmu_lpuart0_clock_select(cmu_lp_perh_clock_sel_t clock);
void ald_cmu_lcd_clock_select(cmu_lcd_clock_sel_t clock);
void ald_cmu_qspi_clock_select(cmu_qspi_clock_sel_t clock);
void ald_cmu_usb_clock_config(cmu_usb_clock_sel_t clock, cmu_usb_div_t div);
void ald_cmu_perh_clock_config(cmu_perh_t perh, type_func_t status);
void ald_cmu_stop1_clock_sel(cmu_stop1_clock_t clock);
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

#endif /* __ALD_CMU_H__ */
