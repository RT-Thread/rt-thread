/**
  *********************************************************************************
  *
  * @file    ald_pmu.h
  * @brief   Header file of PMU module driver.
  *
  * @version V1.0
  * @date    08 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          08 Mar. 2023    Lisq            The first version
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

#ifndef __ALD_PMU_H__
#define __ALD_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"
#include "ald_syscfg.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup PMU
  * @{
  */

/** @defgroup PMU_Public_Macros PMU Public Macros
  * @{
  */
#define ALD_PMU_LPSTOP_ENABLE()             \
do {                            \
    SYSCFG_UNLOCK();                \
    SET_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);        \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_LPSTOP_DISABLE()                \
do {                            \
    SYSCFG_UNLOCK();                \
    CLEAR_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);  \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_FLASH_STOP_DISABLE()                \
do {                            \
    SYSCFG_UNLOCK();                \
    CLEAR_BIT(PMU->CR, PMU_CR_FSTOP_MSK);       \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_FLASH_STOP_ENABLE()             \
do {                            \
    SYSCFG_UNLOCK();                \
    SET_BIT(PMU->CR, PMU_CR_FSTOP_MSK);     \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_BGSTOP_ENABLE()             \
do {                            \
    SYSCFG_UNLOCK();                \
    SET_BIT(PMU->CR, PMU_CR_BGSTOP_MSK);        \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_BGSTOP_DISABLE()                \
do {                            \
    SYSCFG_UNLOCK();                \
    CLEAR_BIT(PMU->CR, PMU_CR_BGSTOP_MSK);  \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_VROSCEN_ENABLE()                \
do {                            \
    SYSCFG_UNLOCK();                \
    SET_BIT(PMU->CR, PMU_CR_VROSCEN_MSK);   \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_VROSCEN_DISABLE()               \
do {                            \
    SYSCFG_UNLOCK();                \
    CLEAR_BIT(PMU->CR, PMU_CR_VROSCEN_MSK); \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_STPRTNEN_ENABLE()               \
do {                            \
    SYSCFG_UNLOCK();                \
    SET_BIT(PMU->CR, PMU_CR_STPRTNEN_MSK);  \
    SYSCFG_LOCK();                  \
} while (0)
#define ALD_PMU_STPRTNEN_DISABLE()              \
do {                            \
    SYSCFG_UNLOCK();                \
    CLEAR_BIT(PMU->CR, PMU_CR_STPRTNEN_MSK);    \
    SYSCFG_LOCK();                  \
} while (0)

#define ALD_PMU_GET_LVD_STATUS()    (READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDO_MSK, PMU_LVDCR_LVDO_POS))
/**
  * @}
  */


/** @defgroup PMU_Public_Types PMU Public Types
  * @{
  */
/**
  * @brief Low power mode
  */
typedef enum {
    ALD_PMU_LP_STOP   = 0x0U,   /**< Stop */
} ald_pmu_lp_mode_t;

typedef enum {
    ALD_PMU_SR_WUF    = (1U << 0),  /**< WakeUp status */
} ald_pmu_status_t;

/**
  * @brief LVD voltage select
  */
typedef enum {
    ALD_PMU_LVD_VOL_SEL_2_2 = 0x0U, /**< 2.2V */
    ALD_PMU_LVD_VOL_SEL_2_4 = 0x1U, /**< 2.4V */
    ALD_PMU_LVD_VOL_SEL_2_6 = 0x2U, /**< 2.6V */
    ALD_PMU_LVD_VOL_SEL_2_8 = 0x3U, /**< 2.8V */
    ALD_PMU_LVD_VOL_SEL_3_0 = 0x4U, /**< 3.0V */
    ALD_PMU_LVD_VOL_SEL_3_6 = 0x5U, /**< 3.6V */
    ALD_PMU_LVD_VOL_SEL_4_0 = 0x6U, /**< 4.0V */
    ALD_PMU_LVD_VOL_SEL_4_6 = 0x7U, /**< 4.6V */
} ald_pmu_lvd_voltage_sel_t;

/**
  * @brief LVD trigger mode
  */
typedef enum {
    ALD_PMU_LVD_TRIGGER_RISING_EDGE    = 0x0U,  /**< Rising edge */
    ALD_PMU_LVD_TRIGGER_FALLING_EDGE   = 0x1U,  /**< Falling edge */
    ALD_PMU_LVD_TRIGGER_HIGH_LEVEL     = 0x2U,  /**< High level */
    ALD_PMU_LVD_TRIGGER_LOW_LEVEL      = 0x3U,  /**< Low level */
    ALD_PMU_LVD_TRIGGER_RISING_FALLING = 0x4U,  /**< Rising and falling edge */
} ald_pmu_lvd_trigger_mode_t;

/**
  * @}
  */

/**
  * @defgroup PMU_Private_Macros PMU Private Macros
  * @{
  */
#define IS_PMU_LP_MODE(x)       (((x) == ALD_PMU_LP_STOP))
#define IS_PMU_STATUS(x)        (((x) == ALD_PMU_SR_WUF))
#define IS_PMU_LVD_VOL_SEL(x)       (((x) == ALD_PMU_LVD_VOL_SEL_2_2) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_2_4) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_2_6) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_2_8) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_3_0) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_3_6) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_4_0) || \
                                         ((x) == ALD_PMU_LVD_VOL_SEL_4_6))
#define IS_PMU_LVD_TRIGGER_MODE(x)  (((x) == ALD_PMU_LVD_TRIGGER_RISING_EDGE)  || \
                                         ((x) == ALD_PMU_LVD_TRIGGER_FALLING_EDGE) || \
                                         ((x) == ALD_PMU_LVD_TRIGGER_HIGH_LEVEL)   || \
                                         ((x) == ALD_PMU_LVD_TRIGGER_LOW_LEVEL)    || \
                                         ((x) == ALD_PMU_LVD_TRIGGER_RISING_FALLING))
/**
  * @}
  */

/** @addtogroup PMU_Public_Functions
  * @{
  */
void ald_pmu_sleep_enter(void);
void ald_pmu_stop_enter(void);

flag_status_t ald_pmu_get_status(ald_pmu_status_t sr);
void ald_pmu_clear_status(ald_pmu_status_t sr);
/**
  * @}
  */
/** @addtogroup PMU_Public_Functions_Group2
  * @{
  */
/* LVD configure */
void ald_pmu_lvd_config(ald_pmu_lvd_voltage_sel_t sel, ald_pmu_lvd_trigger_mode_t mode, type_func_t state);
void ald_lvd_irq_handler(void);
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

#endif /* __ALD_PMU_H__ */
