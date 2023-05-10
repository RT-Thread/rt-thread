/**
  *********************************************************************************
  *
  * @file    ald_cmu.h
  * @brief   Header file of CMU module driver.
  *
  * @version V1.0
  * @date    30 Jan. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          30 Jan. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#ifndef __ALD_CMU_H__
#define __ALD_CMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ald_syscfg.h"


/** @addtogroup ALD
  * @{
  */

/** @addtogroup CMU
  * @{
  */

/** @defgroup CMU_Public_Macros CMU Public Macros
  * @{
  */

/**
  * @}
  */


/** @defgroup CMU_Public_Types CMU Public Types
  * @{
  */
/**
  * @brief CMU state structure definition
  */
typedef enum
{
    ALD_CMU_CLOCK_HRC48M  = 0x1U,   /**< HRC48M */
    ALD_CMU_CLOCK_LRC     = 0x2U,   /**< LRC */
    ALD_CMU_CLOCK_HOSC    = 0x3U,   /**< HOSC */
    ALD_CMU_CLOCK_PLL     = 0x4U,   /**< PLL */
    ALD_CMU_CLOCK_HRC4M   = 0x5U,   /**< HRC4M */
} ald_cmu_clock_t;

/**
  * @brief PLL output clock
  */
typedef enum
{
    ALD_CMU_PLL_OUTPUT_72M = 0x0U,  /**< 72MHz */
    ALD_CMU_PLL_OUTPUT_64M = 0x2U,  /**< 64MHz */
    ALD_CMU_PLL_OUTPUT_48M = 0x3U,  /**< 48MHz */
} ald_cmu_pll_output_t;

/**
  * @brief PLL referance clock
  */
typedef enum
{
    ALD_CMU_PLL_INPUT_HRC4M   = 0x0U,   /**< HRC4M */
    ALD_CMU_PLL_INPUT_HOSC4M  = 0x1U,   /**< HOSC4M */
    ALD_CMU_PLL_INPUT_HOSC8M  = 0x2U,   /**< HOSC8M */
    ALD_CMU_PLL_INPUT_HOSC16M = 0x3U,   /**< HOSC16M */
} ald_cmu_pll_input_t;

/**
  * @brief HOSC range
  */
typedef enum {
    ALD_CMU_HOSC_1M_2M   = 0x0U,    /**< 1~2MHz */
    ALD_CMU_HOSC_2M_4M   = 0x1U,    /**< 2~4MHz */
    ALD_CMU_HOSC_4M_8M   = 0x2U,    /**< 4~8MHz */
    ALD_CMU_HOSC_8M_16M  = 0x3U,    /**< 8~16MHz */
    ALD_CMU_HOSC_16M_24M = 0x4U,    /**< 16~24MHz */
} ald_cmu_hosc_range_t;

/**
  * @brief Frequency division select bit
  */
typedef enum
{
    ALD_CMU_DIV_1    = 0x0U,     /**< Division by 1 */
    ALD_CMU_DIV_2    = 0x1U,     /**< Division by 2 */
    ALD_CMU_DIV_4    = 0x2U,     /**< Division by 4 */
    ALD_CMU_DIV_8    = 0x3U,     /**< Division by 8 */
    ALD_CMU_DIV_16   = 0x4U,     /**< Division by 16 */
    ALD_CMU_DIV_32   = 0x5U,     /**< Division by 32 */
    ALD_CMU_DIV_64   = 0x6U,     /**< Division by 64 */
    ALD_CMU_DIV_128  = 0x7U,     /**< Division by 128 */
    ALD_CMU_DIV_256  = 0x8U,     /**< Division by 256 */
    ALD_CMU_DIV_512  = 0x9U,     /**< Division by 512 */
    ALD_CMU_DIV_1024 = 0xAU,     /**< Division by 1024 */
    ALD_CMU_DIV_2048 = 0xBU,     /**< Division by 2048 */
    ALD_CMU_DIV_4096 = 0xCU,     /**< Division by 4096 */
} ald_cmu_div_t;

/**
  * @brief BUZZ frequency division
  */
typedef enum {
    ALD_CMU_BUZZ_DIV_2   = 0x0U,    /**< Division by 2 */
    ALD_CMU_BUZZ_DIV_4   = 0x1U,    /**< Division by 4 */
    ALD_CMU_BUZZ_DIV_8   = 0x2U,    /**< Division by 8 */
    ALD_CMU_BUZZ_DIV_16  = 0x3U,    /**< Division by 16 */
    ALD_CMU_BUZZ_DIV_32  = 0x4U,    /**< Division by 32 */
    ALD_CMU_BUZZ_DIV_64  = 0x5U,    /**< Division by 64 */
    ALD_CMU_BUZZ_DIV_128 = 0x6U,    /**< Division by 128 */
    ALD_CMU_BUZZ_DIV_256 = 0x7U,    /**< Division by 256 */
} ald_cmu_buzz_div_t;

/**
  * @brief Safe clock source type
  */
typedef enum {
    ALD_CMU_SAFE_CLK_PLL = 0x0U,    /**< PLL */
} ald_cmu_clock_safe_type_t;

/**
  * @brief Bus type
  */
typedef enum
{
    ALD_CMU_SYS    = 0x1U,     /**< SYS bus */
    ALD_CMU_PCLK   = 0x2U,     /**< APB bus */
} ald_cmu_bus_t;

/**
  * @brief Output frequency division
  */
typedef enum {
    ALD_CMU_OUTPUT_DIV_1   = 0x0U,  /**< Division by 1 */
    ALD_CMU_OUTPUT_DIV_2   = 0x1U,  /**< Division by 2 */
    ALD_CMU_OUTPUT_DIV_4   = 0x2U,  /**< Division by 4 */
    ALD_CMU_OUTPUT_DIV_8   = 0x3U,  /**< Division by 8 */
    ALD_CMU_OUTPUT_DIV_16  = 0x4U,  /**< Division by 16 */
    ALD_CMU_OUTPUT_DIV_32  = 0x5U,  /**< Division by 32 */
    ALD_CMU_OUTPUT_DIV_64  = 0x6U,  /**< Division by 64 */
    ALD_CMU_OUTPUT_DIV_128 = 0x7U,  /**< Division by 128 */
} ald_cmu_output_high_div_t;

/**
  * @brief Output high clock select
  */
typedef enum {
    ALD_CMU_OUTPUT_HIGH_SEL_HOSC    = 0x0U, /**< Select HOSC */
    ALD_CMU_OUTPUT_HIGH_SEL_HOSM    = 0x1U, /**< Select HOSM */
    ALD_CMU_OUTPUT_HIGH_SEL_HRC4M   = 0x2U, /**< Select HRC4M */
    ALD_CMU_OUTPUT_HIGH_SEL_LRC     = 0x3U, /**< Select LRC */
    ALD_CMU_OUTPUT_HIGH_SEL_SYSCLK  = 0x4U, /**< Select SYSCLK */
    ALD_CMU_OUTPUT_HIGH_SEL_HOSC32K = 0x5U, /**< Select HOSC32K */
    ALD_CMU_OUTPUT_HIGH_SEL_HRC48M  = 0x6U, /**< Select HRC48M */
    ALD_CMU_OUTPUT_HIGH_SEL_PLL     = 0x7U, /**< Select PLL */
} ald_cmu_output_high_sel_t;

/**
  * @brief Output low clock select
  */
typedef enum {
    ALD_CMU_OUTPUT_LOW_SEL_LRC  = 0x0U, /**< Select LRC */
    ALD_CMU_OUTPUT_LOW_SEL_BUZZ = 0x1U, /**< Select BUZZ */
} ald_cmu_output_low_sel_t;

/**
  * @brief Peripheral clock enable/disable
  */
typedef enum {
    ALD_CMU_PERH_GPIO      = (1U << 0),                 /**< GPIO */
    ALD_CMU_PERH_CRC       = (1U << 1),                 /**< CRC */
    ALD_CMU_PERH_DMA       = (1U << 2),                 /**< DMA */
    ALD_CMU_PERH_PIS       = (1U << 5),                 /**< PIS */
    ALD_CMU_PERH_USB       = (1U << 6),                 /**< USB */
    ALD_CMU_PERH_CSU       = (1U << 7),                 /**< CSU */
    ALD_CMU_PERH_AD16C4T0  = (1U << 0)  | (1U << 27),   /**< AD16C4T0 */
    ALD_CMU_PERH_BS16T0    = (1U << 1)  | (1U << 27),   /**< BS16T0 */
    ALD_CMU_PERH_GP16C4T0  = (1U << 2)  | (1U << 27),   /**< CP16C4T0 */
    ALD_CMU_PERH_GP16C4T1  = (1U << 3)  | (1U << 27),   /**< GP16C4T1 */
    ALD_CMU_PERH_GP16C4T2  = (1U << 4)  | (1U << 27),   /**< GP16C4T2 */
    ALD_CMU_PERH_EUART0    = (1U << 8)  | (1U << 27),   /**< EUART0 */
    ALD_CMU_PERH_EUART1    = (1U << 9)  | (1U << 27),   /**< EUART1 */
    ALD_CMU_PERH_CUART0    = (1U << 12) | (1U << 27),   /**< CUART0 */
    ALD_CMU_PERH_CUART1    = (1U << 13) | (1U << 27),   /**< CUART1 */
    ALD_CMU_PERH_CUART2    = (1U << 14) | (1U << 27),   /**< CUART2 */
    ALD_CMU_PERH_SPI0      = (1U << 16) | (1U << 27),   /**< SPI0 */
    ALD_CMU_PERH_SPI1      = (1U << 17) | (1U << 27),   /**< SPI1 */
    ALD_CMU_PERH_I2C0      = (1U << 20) | (1U << 27),   /**< I2C0 */
    ALD_CMU_PERH_I2C1      = (1U << 21) | (1U << 27),   /**< I2C1 */
    ALD_CMU_PERH_WWDT      = (1U << 22) | (1U << 27),   /**< WWDT */
    ALD_CMU_PERH_IWDT      = (1U << 23) | (1U << 27),   /**< IWDT */
    ALD_CMU_PERH_DBGC      = (1U << 24) | (1U << 27),   /**< DBGC */
    ALD_CMU_PERH_ADC       = (1U << 25) | (1U << 27),   /**< ADC */
    ALD_CMU_PERH_ALL       = (0x7FFFFFFFU),             /**< ALL */
} ald_cmu_perh_t;

/**
  * @brief CMU interrupt type
  */
typedef enum {
    ALD_CMU_HOSC_STOP    = 0x0U,    /**< HOSC STOP INTERRUPT */
    ALD_CMU_PLL_UNLOCK   = 0x1U,    /**< PLL UNLOCK INTERRUPT */
    ALD_CMU_HOSC_START   = 0x2U,    /**< HOSC START INTERRUPT */
} ald_cmu_security_t;

/**
  * @brief CMU clock state type
  */
typedef enum {
    ALD_CMU_CLOCK_STATE_HOSCACT   = (1U << 0),  /**< HOSC active */
    ALD_CMU_CLOCK_STATE_PLLACT    = (1U << 1),  /**< PLL active */
    ALD_CMU_CLOCK_STATE_HRC4MACT  = (1U << 2),  /**< HRC4M active */
    ALD_CMU_CLOCK_STATE_HRC48MACT = (1U << 3),  /**< HRC48M active */
    ALD_CMU_CLOCK_STATE_HOSCRDY   = (1U << 16), /**< HOSC ready */
    ALD_CMU_CLOCK_STATE_HRC4MRDY  = (1U << 17), /**< HRC4M ready */
    ALD_CMU_CLOCK_STATE_HRC48MRDY = (1U << 18), /**< HRC48M ready */
    ALD_CMU_CLOCK_STATE_LRCRDY    = (1U << 19), /**< LRC ready */
    ALD_CMU_CLOCK_STATE_PLLRDY    = (1U << 24), /**< PLL ready */
} ald_cmu_clock_state_t;

/**
  * @}
  */

/**
  * @defgroup CMU_Private_Macros CMU Private Macros
  * @{
  */
#define IS_CMU_CLOCK(x)     (((x) == ALD_CMU_CLOCK_HRC48M)  || \
                                 ((x) == ALD_CMU_CLOCK_LRC)  || \
                                 ((x) == ALD_CMU_CLOCK_HOSC) || \
                                 ((x) == ALD_CMU_CLOCK_PLL) || \
                                 ((x) == ALD_CMU_CLOCK_HRC4M))
#define IS_CMU_PLL_INPUT(x) (((x) == ALD_CMU_PLL_INPUT_HRC4M)  || \
                                 ((x) == ALD_CMU_PLL_INPUT_HOSC4M)   || \
                                 ((x) == ALD_CMU_PLL_INPUT_HOSC8M)   || \
                                 ((x) == ALD_CMU_PLL_INPUT_HOSC16M))
#define IS_CMU_PLL_OUTPUT(x)    (((x) == ALD_CMU_PLL_OUTPUT_48M) || \
                                 ((x) == ALD_CMU_PLL_OUTPUT_64M) || \
                                 ((x) == ALD_CMU_PLL_OUTPUT_72M))
#define IS_CMU_HOSC_RANGE(x)    (((x) == ALD_CMU_HOSC_1M_2M)  || \
                                 ((x) == ALD_CMU_HOSC_2M_4M)  || \
                                 ((x) == ALD_CMU_HOSC_4M_8M)  || \
                                 ((x) == ALD_CMU_HOSC_8M_16M) || \
                                 ((x) == ALD_CMU_HOSC_16M_24M))
#define IS_CMU_DIV(x)       (((x) == ALD_CMU_DIV_1)    || \
                                 ((x) == ALD_CMU_DIV_2)    || \
                                 ((x) == ALD_CMU_DIV_4)    || \
                                 ((x) == ALD_CMU_DIV_8)    || \
                                 ((x) == ALD_CMU_DIV_16)   || \
                                 ((x) == ALD_CMU_DIV_32)   || \
                                 ((x) == ALD_CMU_DIV_64)   || \
                                 ((x) == ALD_CMU_DIV_128)  || \
                                 ((x) == ALD_CMU_DIV_256)  || \
                                 ((x) == ALD_CMU_DIV_512)  || \
                                 ((x) == ALD_CMU_DIV_1024) || \
                                 ((x) == ALD_CMU_DIV_2048) || \
                                 ((x) == ALD_CMU_DIV_4096))
#define IS_CMU_BUS(x)       (((x) == ALD_CMU_PCLK) || \
                                 ((x) == ALD_CMU_SYS))
#define IS_CMU_OUTPUT_HIGH_SEL(x)   (((x) == ALD_CMU_OUTPUT_HIGH_SEL_HOSC) || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_HOSM) || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_HRC4M)  || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_LRC)  || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_SYSCLK) || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_HOSC32K) || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_HRC48M) || \
                                         ((x) == ALD_CMU_OUTPUT_HIGH_SEL_PLL))
#define IS_CMU_OUTPUT_HIGH_DIV(x)   (((x) == ALD_CMU_OUTPUT_DIV_1)  || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_2)  || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_4)  || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_8)  || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_16) || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_32) || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_64) || \
                                         ((x) == ALD_CMU_OUTPUT_DIV_128))
#define IS_CMU_OUTPUT_LOW_SEL(x)    (((x) == ALD_CMU_OUTPUT_LOW_SEL_LRC) || \
                                         ((x) == ALD_CMU_OUTPUT_LOW_SEL_BUZZ))
#define IS_CMU_SAFE_CLOCK_TYPE(x)   (((x) == ALD_CMU_SAFE_CLK_PLL))
#define IS_CMU_BUZZ_DIV(x)  (((x) == ALD_CMU_BUZZ_DIV_2)   || \
                                 ((x) == ALD_CMU_BUZZ_DIV_4)   || \
                                 ((x) == ALD_CMU_BUZZ_DIV_8)   || \
                                 ((x) == ALD_CMU_BUZZ_DIV_16)  || \
                                 ((x) == ALD_CMU_BUZZ_DIV_32)  || \
                                 ((x) == ALD_CMU_BUZZ_DIV_64)  || \
                                 ((x) == ALD_CMU_BUZZ_DIV_128) || \
                                 ((x) == ALD_CMU_BUZZ_DIV_256))
#define IS_CMU_PERH(x)      (((x) == ALD_CMU_PERH_GPIO)    || \
                                 ((x) == ALD_CMU_PERH_CRC)     || \
                                 ((x) == ALD_CMU_PERH_DMA)    || \
                                 ((x) == ALD_CMU_PERH_PIS)   || \
                                 ((x) == ALD_CMU_PERH_USB)    || \
                                 ((x) == ALD_CMU_PERH_CSU)     || \
                                 ((x) == ALD_CMU_PERH_AD16C4T0)  || \
                                 ((x) == ALD_CMU_PERH_BS16T0)  || \
                                 ((x) == ALD_CMU_PERH_GP16C4T0)  || \
                                 ((x) == ALD_CMU_PERH_GP16C4T1)  || \
                                 ((x) == ALD_CMU_PERH_GP16C4T2)  || \
                                 ((x) == ALD_CMU_PERH_EUART0)  || \
                                 ((x) == ALD_CMU_PERH_EUART1)  || \
                                 ((x) == ALD_CMU_PERH_CUART0)  || \
                                 ((x) == ALD_CMU_PERH_CUART1)   || \
                                 ((x) == ALD_CMU_PERH_CUART2)   || \
                                 ((x) == ALD_CMU_PERH_SPI0)    || \
                                 ((x) == ALD_CMU_PERH_SPI1)    || \
                                 ((x) == ALD_CMU_PERH_I2C0)    || \
                                 ((x) == ALD_CMU_PERH_I2C1)    || \
                                 ((x) == ALD_CMU_PERH_WWDT)     || \
                                 ((x) == ALD_CMU_PERH_IWDT)  || \
                                 ((x) == ALD_CMU_PERH_DBGC)    || \
                                 ((x) == ALD_CMU_PERH_ADC)    || \
                                 ((x) == ALD_CMU_PERH_ALL))
#define IS_CMU_CLOCK_STATE(x)   (((x) == ALD_CMU_CLOCK_STATE_HOSCACT) || \
                                 ((x) == ALD_CMU_CLOCK_STATE_PLLACT) || \
                 ((x) == ALD_CMU_CLOCK_STATE_HRC4MACT)  || \
                 ((x) == ALD_CMU_CLOCK_STATE_HRC48MACT)  || \
                 ((x) == ALD_CMU_CLOCK_STATE_HOSCRDY) || \
                 ((x) == ALD_CMU_CLOCK_STATE_HRC4MRDY) || \
                 ((x) == ALD_CMU_CLOCK_STATE_HRC48MRDY) || \
                 ((x) == ALD_CMU_CLOCK_STATE_LRCRDY) || \
                 ((x) == ALD_CMU_CLOCK_STATE_PLLRDY))
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
ald_status_t ald_cmu_clock_config(ald_cmu_clock_t clk, uint32_t clock);
void ald_cmu_pll_config(ald_cmu_pll_input_t input, ald_cmu_pll_output_t output);
uint32_t ald_cmu_get_clock(void);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group2
  * @{
  */
/* BUS division control */
void ald_cmu_div_config(ald_cmu_bus_t bus, ald_cmu_div_t div);
uint32_t ald_cmu_get_sys_clock(void);
uint32_t ald_cmu_get_pclk_clock(void);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group3
  * @{
  */
/* Clock safe configure */
void ald_cmu_hosc_safe_config(ald_cmu_hosc_range_t clock, type_func_t status);
void ald_cmu_pll_safe_config(type_func_t status);
uint32_t ald_cmu_pulmcr_current_clock_source_get(void);
flag_status_t ald_cmu_get_clock_state(ald_cmu_clock_state_t sr);
void ald_cmu_irq_handler(void);
void ald_cmu_irq_cbk(ald_cmu_security_t se);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group4
  * @{
  */
/* Clock output configure */
void ald_cmu_output_high_clock_config(ald_cmu_output_high_sel_t sel,
        ald_cmu_output_high_div_t div, type_func_t status);
void ald_cmu_output_low_clock_config(ald_cmu_output_low_sel_t sel, type_func_t status);
/**
  * @}
  */

/** @addtogroup CMU_Public_Functions_Group5
  * @{
  */
/* Peripheral Clock configure */
void ald_cmu_buzz_config(ald_cmu_buzz_div_t div, uint16_t dat, type_func_t status);
void ald_cmu_perh_clock_config(ald_cmu_perh_t perh, type_func_t status);
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
#endif /* __cplusplus */

#endif /* __ALD_CMU_H__ */
