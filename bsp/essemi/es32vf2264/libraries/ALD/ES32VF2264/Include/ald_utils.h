/**
  *********************************************************************************
  *
  * @file    ald_utils.h
  * @brief   This file contains the Utilities functions/types for the driver.
  *
  * @version V1.0
  * @date    8 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          8 Feb. 2023     Lisq            The first version
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

#ifndef __ALD_UTILS_H__
#define __ALD_UTILS_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include "es32vf2264.h"
#include "type.h"

/** @addtogroup ALD
  * @{
  */

/** @addtogroup ALD_UTILS
  * @{
  */

/** @defgroup ALD_Public_Types Public Types
  * @{
  */
/**
  * @brief  SysTick interval
  */
extern uint32_t __systick_interval;

/**
  * @brief  ALD Status structures definition
  */
typedef enum {
    ALD_OK      = 0x0U, /**< OK */
    ALD_ERROR   = 0x1U, /**< ERROR */
    ALD_BUSY    = 0x2U, /**< BUSY */
    ALD_TIMEOUT = 0x3U, /**< TIMEOUT */
} ald_status_t;

/**
  * @brief  SysTick interval definition
  */
typedef enum {
    ALD_SYSTICK_INTERVAL_1MS    = 1000U,    /**< Interval is 1ms */
    ALD_SYSTICK_INTERVAL_10MS   = 100U,     /**< Interval is 10ms */
    ALD_SYSTICK_INTERVAL_100MS  = 10U,      /**< Interval is 100ms */
    ALD_SYSTICK_INTERVAL_1000MS = 1U,       /**< Interval is 1s */
} ald_systick_interval_t;
/**
  * @}
  */

/** @defgroup ALD_Public_Macros Public Macros
  * @{
  */
#define ALD_MAX_DELAY   0xFFFFFFFFU
#define IS_BIT_SET(reg, bit)    (((reg) & (bit)) != RESET)
#define IS_BIT_CLR(reg, bit)    (((reg) & (bit)) == RESET)
#define ALD_RESET_HANDLE_STATE(x)   ((x)->state = 0)
#define __LOCK(x)           \
do {                    \
    if ((x)->lock == LOCK) {    \
        return ALD_BUSY;        \
    }               \
    else {              \
        (x)->lock = LOCK;   \
    }               \
} while (0)
#define __UNLOCK(x)         \
do {                    \
    (x)->lock = UNLOCK;     \
} while (0)
#define ALD_PANIC()     \
do {            \
    while (1)   \
        ;   \
} while (0)

/**
  * @brief  Nested IRQ start : Save CSR and enable global interrupt.
  */
#define ALD_NEST_INT_START() \
    volatile uint32_t val_mcause, val_mstatus, val_mepc; \
    __ASM volatile("csrr %0, mcause" : "=r"(val_mcause)); \
    __ASM volatile("csrr %0, mepc" : "=r"(val_mepc)); \
    __ASM volatile("csrr %0, mstatus" : "=r"(val_mstatus)); \
    __enable_irq(); \

/**
  * @brief  Nested IRQ end : Restore CSR and disable global interrupt.
  */
#define ALD_NEST_INT_END() \
    __disable_irq(); \
    __ASM volatile("csrw mstatus, %0" : : "r"(val_mstatus));\
    __ASM volatile("csrw mepc, %0" : : "r"(val_mepc));\
    __ASM volatile("csrw mcause, %0" : : "r"(val_mcause));\

/**
  * @}
  */

/** @defgroup ALD_Private_Macros Private Macros
  * @{
  */
#define IS_SYSTICK_INTERVAL(x)  (((x) == ALD_SYSTICK_INTERVAL_1MS)   || \
                                 ((x) == ALD_SYSTICK_INTERVAL_10MS)  || \
                                 ((x) == ALD_SYSTICK_INTERVAL_100MS) || \
                                 ((x) == ALD_SYSTICK_INTERVAL_1000MS))
/**
  * @}
  */

/** @addtogroup ALD_Public_Functions
  * @{
  */

/** @addtogroup ALD_Public_Functions_Group1
  * @{
  */

/* Initialization functions */
void ald_cmu_init(void);
void ald_tick_init(uint32_t prio);
void ald_systick_interval_select(ald_systick_interval_t value);

/**
  * @}
  */

/** @addtogroup ALD_Public_Functions_Group2
  * @{
  */
/* Peripheral Control functions */
void ald_inc_tick(void);
void ald_systick_irq_cbk(void);
void ald_delay_1ms(__IO uint32_t delay);
void ald_delay_1us(__IO uint32_t delay);
uint32_t ald_get_tick(void);
uint32_t ald_get_ald_version(void);
void ald_flash_wait_config(uint8_t cycle);
ald_status_t ald_wait_flag(uint32_t *reg, uint32_t bit, flag_status_t status, uint32_t timeout);
void ald_mcu_irq_config(IRQn_Type irq, uint8_t prio, type_func_t status);
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

#endif /* __ALD_UTILS_H__ */
