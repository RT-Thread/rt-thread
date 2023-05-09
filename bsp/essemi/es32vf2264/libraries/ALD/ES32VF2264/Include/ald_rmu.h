/**
  *********************************************************************************
  *
  * @file    ald_rmu.h
  * @brief   Header file of RMU module driver.
  *
  * @version V1.0
  * @date    09 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          09 Mar. 2023    Lisq            The first version
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

#ifndef __ALD_RMU_H__
#define __ALD_RMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup RMU
  * @{
  */

/** @defgroup RMU_Public_Types RMU Public Types
  * @{
  */
/**
  * @brief RMU BOR fliter
  */
typedef enum {
    ALD_RMU_BORFLT_1 = 0x1U,    /**< 1 cycle  */
    ALD_RMU_BORFLT_2 = 0x2U,    /**< 2 cycles */
    ALD_RMU_BORFLT_3 = 0x3U,    /**< 3 cycles */
    ALD_RMU_BORFLT_4 = 0x4U,    /**< 4 cycles */
    ALD_RMU_BORFLT_5 = 0x5U,    /**< 5 cycles */
    ALD_RMU_BORFLT_6 = 0x6U,    /**< 6 cycles */
    ALD_RMU_BORFLT_7 = 0x7U,    /**< 7 cycles */
} ald_rmu_bor_filter_t;

/**
  * @brief RMU reset status
  */
typedef enum {
    ALD_RMU_RST_POR    = (1U << 0),   /**< POR */
    ALD_RMU_RST_WAKEUP = (1U << 1),   /**< WAKEUP */
    ALD_RMU_RST_BOR    = (1U << 2),   /**< BOR */
    ALD_RMU_RST_NMRST  = (1U << 3),   /**< NMRST */
    ALD_RMU_RST_IWDT   = (1U << 4),   /**< IWDT */
    ALD_RMU_RST_WWDT   = (1U << 5),   /**< WWDT */
    ALD_RMU_RST_LOCKUP = (1U << 6),   /**< LOCKUP */
    ALD_RMU_RST_CHIP   = (1U << 7),   /**< CHIP */
    ALD_RMU_RST_MCU    = (1U << 8),   /**< MCU */
    ALD_RMU_RST_CPU    = (1U << 9),   /**< CPU */
    ALD_RMU_RST_CFG    = (1U << 10),  /**< CFG */
    ALD_RMU_RST_CFGERR = (1U << 16),  /**< CFG Error */
    ALD_RMU_RST_ALL    = (0xFFFFFU),  /**< ALL */
} ald_rmu_state_t;

/**
  * @brief RMU periperal select bit
  */
typedef enum {
    ALD_RMU_PERH_GPIO    = (1U << 0),           /**< AHB1: GPIO */
    ALD_RMU_PERH_CRC     = (1U << 1),           /**< AHB1: CRC */
    ALD_RMU_PERH_DMA     = (1U << 2),           /**< AHB1: DMA */
    ALD_RMU_PERH_PIS     = (1U << 5),           /**< AHB1: PIS */
    ALD_RMU_PERH_USB     = (1U << 6),           /**< AHB1: USB */
    ALD_RMU_PERH_CSU     = (1U << 7),           /**< AHB1: CSU */

    ALD_RMU_PERH_CHIP    = (1U << 0)  | (1U << 27), /**< AHB2: CHIP */
    ALD_RMU_PERH_CPU     = (1U << 1)  | (1U << 27), /**< AHB2: CPU */

    ALD_RMU_PERH_AD16C4T  = (1U << 0)  | (1U << 28), /**< APB: AD16C4T */
    ALD_RMU_PERH_BS16T0   = (1U << 1)  | (1U << 28), /**< APB: BS16T0 */
    ALD_RMU_PERH_GP16C4T0 = (1U << 2)  | (1U << 28), /**< APB: GP16C4T0 */
    ALD_RMU_PERH_GP16C4T1 = (1U << 3)  | (1U << 28), /**< APB: GP16C4T1 */
    ALD_RMU_PERH_GP16C4T2 = (1U << 4)  | (1U << 28), /**< APB: GP16C4T2 */
    ALD_RMU_PERH_EUART0   = (1U << 8)  | (1U << 28), /**< APB: EUART0 */
    ALD_RMU_PERH_EUART1   = (1U << 9)  | (1U << 28), /**< APB: EUART1 */
    ALD_RMU_PERH_CUART0   = (1U << 12) | (1U << 28), /**< APB: CUART0 */
    ALD_RMU_PERH_CUART1   = (1U << 13) | (1U << 28), /**< APB: CUART1 */
    ALD_RMU_PERH_CUART2   = (1U << 14) | (1U << 28), /**< APB: CUART2 */
    ALD_RMU_PERH_SPI0     = (1U << 16) | (1U << 28), /**< APB: SPI0 */
    ALD_RMU_PERH_SPI1     = (1U << 17) | (1U << 28), /**< APB: SPI1 */
    ALD_RMU_PERH_I2C0    = (1U << 20) | (1U << 28),  /**< APB: I2C0 */
    ALD_RMU_PERH_I2C1    = (1U << 21) | (1U << 28),  /**< APB: I2C1 */
    ALD_RMU_PERH_WWDT    = (1U << 22) | (1U << 28),  /**< APB: WWDT */
    ALD_RMU_PERH_IWDT    = (1U << 23) | (1U << 28),  /**< APB: IWDT */
    ALD_RMU_PERH_DBGCON  = (1U << 24) | (1U << 28),  /**< APB: DBGCON */
    ALD_RMU_PERH_ADC     = (1U << 25) | (1U << 28),  /**< APB: ADC */
} ald_rmu_peripheral_t;
/**
  * @}
  */

/**
  * @defgroup RMU_Private_Macros RMU Private Macros
  * @{
  */
#define IS_RMU_BORFLT(x)    (((x) == ALD_RMU_BORFLT_1) || \
                                 ((x) == ALD_RMU_BORFLT_2) || \
                                 ((x) == ALD_RMU_BORFLT_3) || \
                                 ((x) == ALD_RMU_BORFLT_4) || \
                                 ((x) == ALD_RMU_BORFLT_5) || \
                                 ((x) == ALD_RMU_BORFLT_6) || \
                                 ((x) == ALD_RMU_BORFLT_7))
#define IS_RMU_STATE(x)     (((x) == ALD_RMU_RST_POR)    || \
                                 ((x) == ALD_RMU_RST_WAKEUP) || \
                                 ((x) == ALD_RMU_RST_BOR)    || \
                                 ((x) == ALD_RMU_RST_NMRST)  || \
                                 ((x) == ALD_RMU_RST_IWDT)   || \
                                 ((x) == ALD_RMU_RST_WWDT)   || \
                                 ((x) == ALD_RMU_RST_LOCKUP) || \
                                 ((x) == ALD_RMU_RST_CHIP)   || \
                                 ((x) == ALD_RMU_RST_MCU)    || \
                                 ((x) == ALD_RMU_RST_CPU)    || \
                                 ((x) == ALD_RMU_RST_CFG)    || \
                                 ((x) == ALD_RMU_RST_CFGERR)    || \
                                 ((x) == ALD_RMU_RST_ALL))
#define IS_RMU_STATE_CLEAR(x)   (((x) == ALD_RMU_RST_POR)    || \
                                 ((x) == ALD_RMU_RST_WAKEUP) || \
                                 ((x) == ALD_RMU_RST_BOR)    || \
                                 ((x) == ALD_RMU_RST_NMRST)  || \
                                 ((x) == ALD_RMU_RST_IWDT)   || \
                                 ((x) == ALD_RMU_RST_WWDT)   || \
                                 ((x) == ALD_RMU_RST_LOCKUP) || \
                                 ((x) == ALD_RMU_RST_CHIP)   || \
                                 ((x) == ALD_RMU_RST_MCU)    || \
                                 ((x) == ALD_RMU_RST_CPU)    || \
                                 ((x) == ALD_RMU_RST_CFG)    || \
                                 ((x) == ALD_RMU_RST_ALL))
#define IS_RMU_PERH(x)      (((x) == ALD_RMU_PERH_GPIO)    || \
                                 ((x) == ALD_RMU_PERH_CRC)     || \
                                 ((x) == ALD_RMU_PERH_DMA)    || \
                                 ((x) == ALD_RMU_PERH_PIS)     || \
                                 ((x) == ALD_RMU_PERH_USB)     || \
                                 ((x) == ALD_RMU_PERH_CSU)     || \
                                 ((x) == ALD_RMU_PERH_CHIP)    || \
                                 ((x) == ALD_RMU_PERH_CPU)     || \
                                 ((x) == ALD_RMU_PERH_AD16C4T)  || \
                                 ((x) == ALD_RMU_PERH_BS16T0)  || \
                                 ((x) == ALD_RMU_PERH_GP16C4T0)  || \
                                 ((x) == ALD_RMU_PERH_GP16C4T1)  || \
                                 ((x) == ALD_RMU_PERH_GP16C4T2)  || \
                                 ((x) == ALD_RMU_PERH_EUART0)   || \
                                 ((x) == ALD_RMU_PERH_EUART1)   || \
                                 ((x) == ALD_RMU_PERH_CUART0)   || \
                                 ((x) == ALD_RMU_PERH_CUART1)   || \
                                 ((x) == ALD_RMU_PERH_CUART2)   || \
                                 ((x) == ALD_RMU_PERH_SPI0)    || \
                                 ((x) == ALD_RMU_PERH_SPI1)    || \
                                 ((x) == ALD_RMU_PERH_I2C0)    || \
                                 ((x) == ALD_RMU_PERH_I2C1)    || \
                                 ((x) == ALD_RMU_PERH_WWDT)    || \
                                 ((x) == ALD_RMU_PERH_IWDT)    || \
                                 ((x) == ALD_RMU_PERH_DBGCON)     || \
                                 ((x) == ALD_RMU_PERH_ADC))
/**
  * @}
  */

/** @addtogroup RMU_Public_Functions
  * @{
  */
void ald_rmu_bor_config(ald_rmu_bor_filter_t flt);
uint32_t ald_rmu_get_reset_status(ald_rmu_state_t state);
void ald_rmu_clear_reset_status(ald_rmu_state_t state);
void ald_rmu_reset_periperal(ald_rmu_peripheral_t perh);
void ald_rmu_reset_system(void);
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

#endif /* __ALD_RMU_H__ */
