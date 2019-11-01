/**
  *********************************************************************************
  *
  * @file    ald_cmu.h
  * @brief   Header file of CMU module driver.
  *
  * @version V1.0
  * @date    22 Nov 2017
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
typedef	enum
{
    CMU_CLOCK_HRC  = 0x1,	/**< HRC */
    CMU_CLOCK_LRC  = 0x2,	/**< LRC */
    CMU_CLOCK_LOSC = 0x3,	/**< LOSC */
    CMU_CLOCK_PLL1 = 0x4,	/**< PLL1 */
    CMU_CLOCK_HOSC = 0x5,	/**< HOSC */
} cmu_clock_t;

/**
  * @brief PLL1 output clock
  */
typedef enum
{
    CMU_PLL1_OUTPUT_32M = 0x0,	/**< x8  (32MHz) */
    CMU_PLL1_OUTPUT_48M = 0x1,	/**< x12 (48MHz) */
} cmu_pll1_output_t;

/**
  * @brief PLL1 referance clock
  */
typedef enum
{
    CMU_PLL1_INPUT_HRC_6  = 0x0,	/**< HRC  / 6 */
    CMU_PLL1_INPUT_PLL2   = 0x1,	/**< PLL2 */
    CMU_PLL1_INPUT_HOSC   = 0x2,	/**< HOSC / 1 */
    CMU_PLL1_INPUT_HOSC_2 = 0x3,	/**< HOSC / 2 */
    CMU_PLL1_INPUT_HOSC_3 = 0x4,	/**< HOSC / 3 */
    CMU_PLL1_INPUT_HOSC_4 = 0x5,	/**< HOSC / 4 */
    CMU_PLL1_INPUT_HOSC_5 = 0x6,	/**< HOSC / 5 */
    CMU_PLL1_INPUT_HOSC_6 = 0x7,	/**< HOSC / 6 */
} cmu_pll1_input_t;

/**
  * @brief HOSC range
  */
typedef enum
{
    CMU_HOSC_2M  = 0x0,
    CMU_HOSC_4M  = 0x1,
    CMU_HOSC_8M  = 0x2,
    CMU_HOSC_16M = 0x3,
    CMU_HOSC_24M = 0x4,
} cmu_hosc_range_t;

/**
  * @brief Auto-calibrate input
  */
typedef enum
{
    CMU_AUTO_CALIB_INPUT_LOSE = 0x0,
    CMU_AUTO_CALIB_INPUT_HOSE = 0x1,
} cmu_auto_calib_input_t;

/**
  * @brief Auto-calibrate output
  */
typedef enum
{
    CMU_AUTO_CALIB_OUTPUT_24M = 0x0,
    CMU_AUTO_CALIB_OUTPUT_2M  = 0x1,
} cmu_auto_calib_output_t;

/**
  * @brief Frequency division select bit
  */
typedef enum
{
    CMU_DIV_1    = 0x0,		/**< Division by 1 */
    CMU_DIV_2    = 0x1,		/**< Division by 2 */
    CMU_DIV_4    = 0x2,		/**< Division by 4 */
    CMU_DIV_8    = 0x3,		/**< Division by 8 */
    CMU_DIV_16   = 0x4,		/**< Division by 16 */
    CMU_DIV_32   = 0x5,		/**< Division by 32 */
    CMU_DIV_64   = 0x6,		/**< Division by 64 */
    CMU_DIV_128  = 0x7,		/**< Division by 128 */
    CMU_DIV_256  = 0x8,		/**< Division by 256 */
    CMU_DIV_512  = 0x9,		/**< Division by 512 */
    CMU_DIV_1024 = 0xA,		/**< Division by 1024 */
    CMU_DIV_2048 = 0xB,		/**< Division by 2048 */
    CMU_DIV_4096 = 0xC,		/**< Division by 4096 */
} cmu_div_t;

/**
  * @brief Bus type
  */
typedef enum
{
    CMU_HCLK_1 = 0x0,		/**< AHB1 bus */
    CMU_SYS    = 0x1,		/**< SYS bus */
    CMU_PCLK_1 = 0x2,		/**< APB1 bus */
    CMU_PCLK_2 = 0x3,		/**< APB2 bus */
} cmu_bus_t;

/**
  * @brief Output high clock select
  */
typedef enum
{
    CMU_OUTPUT_HIGH_SEL_HOSC   = 0x0,	/**< Select HOSC */
    CMU_OUTPUT_HIGH_SEL_LOSC   = 0x1,	/**< Select LOSC */
    CMU_OUTPUT_HIGH_SEL_HRC    = 0x2,	/**< Select HRC */
    CMU_OUTPUT_HIGH_SEL_LRC    = 0x3,	/**< Select LRC */
    CMU_OUTPUT_HIGH_SEL_HOSM   = 0x4,	/**< Select HOSM */
    CMU_OUTPUT_HIGH_SEL_PLL1   = 0x5,	/**< Select PLL1 */
    CMU_OUTPUT_HIGH_SEL_PLL2   = 0x6,	/**< Select PLL2 */
    CMU_OUTPUT_HIGH_SEL_SYSCLK = 0x7,	/**< Select SYSCLK */
} cmu_output_high_sel_t;

/**
  * @brief Output frequency division
  */
typedef enum
{
    CMU_OUTPUT_DIV_1   = 0x0,	/**< Division by 1 */
    CMU_OUTPUT_DIV_2   = 0x1,	/**< Division by 2 */
    CMU_OUTPUT_DIV_4   = 0x2,	/**< Division by 4 */
    CMU_OUTPUT_DIV_8   = 0x3,	/**< Division by 8 */
    CMU_OUTPUT_DIV_16  = 0x4,	/**< Division by 16 */
    CMU_OUTPUT_DIV_32  = 0x5,	/**< Division by 32 */
    CMU_OUTPUT_DIV_64  = 0x6,	/**< Division by 64 */
    CMU_OUTPUT_DIV_128 = 0x7,	/**< Division by 128 */
} cmu_output_high_div_t;

/**
  * @brief Output low clock select
  */
typedef enum
{
    CMU_OUTPUT_LOW_SEL_LOSC = 0x0,	/**< Select LOSC */
    CMU_OUTPUT_LOW_SEL_LRC  = 0x1,	/**< Select LRC */
    CMU_OUTPUT_LOW_SEL_LOSM = 0x2,	/**< Select LOSM */
    CMU_OUTPUT_LOW_SEL_BUZZ = 0x3,	/**< Select BUZZ */
    CMU_OUTPUT_LOW_SEL_ULRC = 0x4,	/**< Select ULRC */
} cmu_output_low_sel_t;

/**
  * @brief BUZZ frequency division
  */
typedef enum
{
    CMU_BUZZ_DIV_2   = 0x0,		/**< Division by 2 */
    CMU_BUZZ_DIV_4   = 0x1,		/**< Division by 4 */
    CMU_BUZZ_DIV_8   = 0x2,		/**< Division by 8 */
    CMU_BUZZ_DIV_16  = 0x3,		/**< Division by 16 */
    CMU_BUZZ_DIV_32  = 0x4,		/**< Division by 32 */
    CMU_BUZZ_DIV_64  = 0x5,		/**< Division by 64 */
    CMU_BUZZ_DIV_128 = 0x6,		/**< Division by 128 */
    CMU_BUZZ_DIV_256 = 0x7,		/**< Division by 256 */
} cmu_buzz_div_t;

/**
  * @brief Low power peripheral clock select
  */
typedef enum
{
    CMU_LP_PERH_CLOCK_SEL_PCLK2   = 0x0,	/**< Select PCLK2 */
    CMU_LP_PERH_CLOCK_SEL_PLL1    = 0x1,	/**< Select PLL1 */
    CMU_LP_PERH_CLOCK_SEL_PLL2    = 0x2,	/**< Select PLL2 */
    CMU_LP_PERH_CLOCK_SEL_HRC     = 0x3,	/**< Select HRC */
    CMU_LP_PERH_CLOCK_SEL_HOSC    = 0x4,	/**< Select HOSC */
    CMU_LP_PERH_CLOCK_SEL_LRC     = 0x5,	/**< Select LRC */
    CMU_LP_PERH_CLOCK_SEL_LOSC    = 0x6,	/**< Select LOSC */
    CMU_LP_PERH_CLOCK_SEL_ULRC    = 0x7,	/**< Select ULRC */
    CMU_LP_PERH_CLOCK_SEL_HRC_1M  = 0x8,	/**< Select HRC down to 1MHz */
    CMU_LP_PERH_CLOCK_SEL_HOSC_1M = 0x9,	/**< Select HOSC down to 1MHz  */
    CMU_LP_PERH_CLOCK_SEL_LOSM    = 0xA,	/**< Select LOSM */
    CMU_LP_PERH_CLOCK_SEL_HOSM    = 0xB,	/**< Select HOSM */
} cmu_lp_perh_clock_sel_t;

/**
  * @brief LCD clock select
  */
typedef enum
{
    CMU_LCD_SEL_LOSM    = 0x0,	/**< Select LOSM */
    CMU_LCD_SEL_LOSC    = 0x1,	/**< Select LOSC */
    CMU_LCD_SEL_LRC     = 0x2,	/**< Select LRC */
    CMU_LCD_SEL_ULRC    = 0x3,	/**< Select ULRC */
    CMU_LCD_SEL_HRC_1M  = 0x4,	/**< Select HRC down to 1MHz */
    CMU_LCD_SEL_HOSC_1M = 0x5,	/**< Select HOSC down to 1MHz */
} cmu_lcd_clock_sel_t;

/**
  * @brief Peripheral clock enable/disable
  * @note  ES32F065x:
  *          AD16C4T0--TIMER0
  *          GP16C4T0--TIMER6
  *          GP16C2T0--TIMER2
  *          GP16C2T1--TIMER3
  *          BS16T0----TIMER1
  *          BS16T1----TIMER4
  *          BS16T2----TIMER5
  *          BS16T3----TIMER7
  *
  *        ES32F033x:
  *        ES32F093x:
  *          GP16C4T0--TIMER0
  *          GP16C4T1--TIMER6
  *          GP16C2T0--TIMER2
  *          GP16C2T1--TIMER3
  *          BS16T0----TIMER1
  *          BS16T1----TIMER4
  *          BS16T2----TIMER5
  *          BS16T3----TIMER7
  */
typedef enum
{
    CMU_PERH_GPIO    = (1U << 0),			/**< GPIO */
    CMU_PERH_CRC     = (1U << 1),			/**< CRC */
    CMU_PERH_CALC    = (1U << 2),			/**< CALC */
    CMU_PERH_CRYPT   = (1U << 3),			/**< CRYPT */
    CMU_PERH_TRNG    = (1U << 4),			/**< TRNG */
    CMU_PERH_PIS     = (1U << 5),			/**< PIS */
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
    CMU_PERH_USART0  = (1U << 12) | (1U << 27),	/**< USART0 */
    CMU_PERH_USART1  = (1U << 13) | (1U << 27),	/**< USART1 */
    CMU_PERH_SPI0    = (1U << 16) | (1U << 27),	/**< SPI0 */
    CMU_PERH_SPI1    = (1U << 17) | (1U << 27),	/**< SPI1 */
    CMU_PERH_SPI2    = (1U << 18) | (1U << 27),	/**< SPI2 */
    CMU_PERH_I2C0    = (1U << 20) | (1U << 27),	/**< I2C0 */
    CMU_PERH_I2C1    = (1U << 21) | (1U << 27),	/**< I2C1 */
    CMU_PERH_CAN     = (1U << 24) | (1U << 27),	/**< CAN */
    CMU_PERH_LPTIM0  = (1U << 0)  | (1U << 28),	/**< LPTIM0 */
    CMU_PERH_LPUART0 = (1U << 2)  | (1U << 28),	/**< LPUART0 */
    CMU_PERH_ADC0    = (1U << 4)  | (1U << 28),	/**< ADC0 */
    CMU_PERH_ADC1    = (1U << 5)  | (1U << 28),	/**< ADC1 */
    CMU_PERH_ACMP0   = (1U << 6)  | (1U << 28),	/**< ACMP0 */
    CMU_PERH_ACMP1   = (1U << 7)  | (1U << 28),	/**< ACMP1 */
    CMU_PERH_OPAMP   = (1U << 8)  | (1U << 28),	/**< OPAMP */
    CMU_PERH_DAC0    = (1U << 9)  | (1U << 28),	/**< DAC0 */
    CMU_PERH_WWDT    = (1U << 12) | (1U << 28),	/**< WWDT */
    CMU_PERH_LCD     = (1U << 13) | (1U << 28),	/**< LCD */
    CMU_PERH_IWDT    = (1U << 14) | (1U << 28),	/**< IWDT */
    CMU_PERH_RTC     = (1U << 15) | (1U << 28),	/**< RTC */
    CMU_PERH_TSENSE  = (1U << 16) | (1U << 28),	/**< TSENSE */
    CMU_PERH_BKPC    = (1U << 17) | (1U << 28),	/**< BKPC */
    CMU_PERH_BKRPAM  = (1U << 18) | (1U << 28),	/**< BKPRAM */
    CMU_PERH_DBGC    = (1U << 19) | (1U << 28),	/**< DBGC */
    CMU_PERH_ALL     = (0x7FFFFFFF),		/**< ALL */
} cmu_perh_t;

/**
  * @brief CMU interrupt type
  */
typedef enum
{
    CMU_LOSC_STOP    = 0x0,	/**< LOSC STOP INTERRUPT */
    CMU_HOSC_STOP    = 0x1,	/**< HOSC STOP INTERRUPT */
    CMU_PLL1_UNLOCK  = 0x2,	/**< PLL1 UNLOCK INTERRUPT */
    CMU_LOSC_START   = 0x3,	/**< LOSC START INTERRUPT */
    CMU_HOSC_START   = 0x4,	/**< HOSC START INTERRUPT */
} cmu_security_t;

/**
  * @brief CMU clock state type
  */
typedef enum
{
    CMU_CLOCK_STATE_HOSCACT = (1U << 0),	/**< HOSC active */
    CMU_CLOCK_STATE_LOSCACT = (1U << 1),	/**< LOSC active */
    CMU_CLOCK_STATE_HRCACT  = (1U << 2),	/**< HRC active */
    CMU_CLOCK_STATE_LRCACT  = (1U << 3),	/**< LRC active */
    CMU_CLOCK_STATE_ULRCACT = (1U << 4),	/**< ULRC active */
    CMU_CLOCK_STATE_PLLACT  = (1U << 8),	/**< PLL active */
    CMU_CLOCK_STATE_HOSCRDY = (1U << 16),	/**< HOSC ready */
    CMU_CLOCK_STATE_LOSCRDY = (1U << 17),	/**< LOSC ready */
    CMU_CLOCK_STATE_HRCRDY  = (1U << 18),	/**< HRC ready */
    CMU_CLOCK_STATE_LRCRDY  = (1U << 19),	/**< LRC ready */
    CMU_CLOCK_STATE_PLLRDY  = (1U << 24),	/**< PLL ready */
} cmu_clock_state_t;
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
#define IS_CMU_PLL1_OUTPUT(x)	(((x) == CMU_PLL1_OUTPUT_32M) || \
                                 ((x) == CMU_PLL1_OUTPUT_48M))
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
#define IS_CMU_AUTO_CALIB_INPUT(x)	(((x) == CMU_AUTO_CALIB_INPUT_LOSE) || \
                                     ((x) == CMU_AUTO_CALIB_INPUT_HOSE))
#define IS_CMU_AUTO_CALIB_OUTPUT(x)	(((x) == CMU_AUTO_CALIB_OUTPUT_24M) || \
                                     ((x) == CMU_AUTO_CALIB_OUTPUT_2M))
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
#define IS_CMU_PERH(x)		(((x) == CMU_PERH_GPIO)    || \
                             ((x) == CMU_PERH_CRC)     || \
                             ((x) == CMU_PERH_CALC)    || \
                             ((x) == CMU_PERH_CRYPT)   || \
                             ((x) == CMU_PERH_TRNG)    || \
                             ((x) == CMU_PERH_PIS)     || \
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
                             ((x) == CMU_PERH_USART0)  || \
                             ((x) == CMU_PERH_USART1)  || \
                             ((x) == CMU_PERH_SPI0)    || \
                             ((x) == CMU_PERH_SPI1)    || \
                             ((x) == CMU_PERH_SPI2)    || \
                             ((x) == CMU_PERH_I2C0)    || \
                             ((x) == CMU_PERH_I2C1)    || \
                             ((x) == CMU_PERH_CAN)     || \
                             ((x) == CMU_PERH_LPTIM0)  || \
                             ((x) == CMU_PERH_LPUART0) || \
                             ((x) == CMU_PERH_ADC0)    || \
                             ((x) == CMU_PERH_ADC1)    || \
                             ((x) == CMU_PERH_ACMP0)   || \
                             ((x) == CMU_PERH_ACMP1)   || \
                             ((x) == CMU_PERH_OPAMP)   || \
                             ((x) == CMU_PERH_DAC0)    || \
                             ((x) == CMU_PERH_WWDT)    || \
                             ((x) == CMU_PERH_LCD)     || \
                             ((x) == CMU_PERH_IWDT)    || \
                             ((x) == CMU_PERH_RTC)     || \
                             ((x) == CMU_PERH_TSENSE)    || \
                             ((x) == CMU_PERH_BKPC)    || \
                             ((x) == CMU_PERH_BKRPAM ) || \
                             ((x) == CMU_PERH_DBGC)    || \
                             ((x) == CMU_PERH_ALL))
#define IS_CMU_CLOCK_STATE(x)	(((x) == CMU_CLOCK_STATE_HOSCACT) || \
                                 ((x) == CMU_CLOCK_STATE_LOSCACT) || \
                                 ((x) == CMU_CLOCK_STATE_HRCACT) || \
                                 ((x) == CMU_CLOCK_STATE_LRCACT) || \
                                 ((x) == CMU_CLOCK_STATE_ULRCACT) || \
                                 ((x) == CMU_CLOCK_STATE_PLLACT) || \
                                 ((x) == CMU_CLOCK_STATE_HOSCRDY) || \
                                 ((x) == CMU_CLOCK_STATE_LOSCRDY) || \
                                 ((x) == CMU_CLOCK_STATE_HRCRDY) || \
                                 ((x) == CMU_CLOCK_STATE_LRCRDY) || \
                                 ((x) == CMU_CLOCK_STATE_PLLRDY))
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
int32_t ald_cmu_auto_calib_clock(cmu_auto_calib_input_t input, cmu_auto_calib_output_t freq);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group2
  * @{
  */
/* BUS division control */
void ald_cmu_div_config(cmu_bus_t bus, cmu_div_t div);
uint32_t ald_cmu_get_hclk1_clock(void);
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
void ald_cmu_perh_clock_config(cmu_perh_t perh, type_func_t status);
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
