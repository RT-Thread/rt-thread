/**
  *********************************************************************************
  *
  * @file    utils.h
  * @brief   This file contains the Utilities functions/types for the driver.
  *
  * @version V1.0
  * @date    07 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          07 Nov 2019     AE Team         The first version
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

#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include "type.h"
#ifdef ES32F36xx
#include "es32f36xx.h"
#elif ES32F39xx
#include "es32f39xx.h"
#elif ES32F336x
#include "es32f336x.h"
#endif

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup UTILS
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
	OK      = 0x0U,	/**< OK */
	ERROR   = 0x1U,	/**< ERROR */
	BUSY    = 0x2U,	/**< BUSY */
	TIMEOUT = 0x3U,	/**< TIMEOUT */
} ald_status_t;

/**
  * @brief NVIC Preemption Priority Group
  */
typedef enum {
	NVIC_PRIORITY_GROUP_0 = 0x7U,	/**< 0-bits for pre-emption priority 4-bits for subpriority */
	NVIC_PRIORITY_GROUP_1 = 0x6U,	/**< 1-bits for pre-emption priority 3-bits for subpriority */
	NVIC_PRIORITY_GROUP_2 = 0x5U,	/**< 2-bits for pre-emption priority 2-bits for subpriority */
	NVIC_PRIORITY_GROUP_3 = 0x4U,	/**< 3-bits for pre-emption priority 1-bits for subpriority */
	NVIC_PRIORITY_GROUP_4 = 0x3U,	/**< 4-bits for pre-emption priority 0-bits for subpriority */
} nvic_priority_group_t;

/**
  * @brief  SysTick interval definition
  */
typedef enum {
	SYSTICK_INTERVAL_1MS    = 1000U,	/**< Interval is 1ms */
	SYSTICK_INTERVAL_10MS   = 100U,		/**< Interval is 10ms */
	SYSTICK_INTERVAL_100MS  = 10U,		/**< Interval is 100ms */
	SYSTICK_INTERVAL_1000MS = 1U,		/**< Interval is 1s */
} systick_interval_t;
/**
  * @}
  */

/** @defgroup ALD_Public_Macros Public Macros
  * @{
  */
#define ALD_MAX_DELAY	0xFFFFFFFFU
#define IS_BIT_SET(reg, bit)	(((reg) & (bit)) != RESET)
#define IS_BIT_CLR(reg, bit)	(((reg) & (bit)) == RESET)
#define RESET_HANDLE_STATE(x)	((x)->state = 0)
#define __LOCK(x)			\
do {					\
	if ((x)->lock == LOCK) {	\
		return BUSY;		\
	}				\
	else {				\
		(x)->lock = LOCK;	\
	}				\
} while (0)
#define __UNLOCK(x)			\
do {					\
	(x)->lock = UNLOCK;		\
} while (0)
#define ALD_PANIC() 	\
do {			\
	while (1)	\
		;	\
} while (0)
/**
  * @}
  */

/** @defgroup ALD_Private_Macros Private Macros
  * @{
  */
#define MCU_UID0_ADDR	0x000803E0U
#define MCU_UID1_ADDR	0x000803E8U
#define MCU_UID2_ADDR	0x000803ECU
#define MCU_CHIPID_ADDR	0x000803F8U
#define DWT_CR		*(uint32_t *)0xE0001000U
#define DWT_CYCCNT	*(volatile uint32_t *)0xE0001004U
#define DEM_CR		*(uint32_t *)0xE000EDFCU
#define DEM_CR_TRCENA	(1U << 24)
#define DWT_CR_CYCCNTEA	(1U << 0)
#define IS_PREEMPT_PRIO(x)	((x) < 16)
#define IS_SUB_PRIO(x)		((x) < 16)
#define IS_SYSTICK_INTERVAL(x)	(((x) == SYSTICK_INTERVAL_1MS)   || \
                                 ((x) == SYSTICK_INTERVAL_10MS)  || \
                                 ((x) == SYSTICK_INTERVAL_100MS) || \
                                 ((x) == SYSTICK_INTERVAL_1000MS))
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
void ald_systick_interval_select(systick_interval_t value);

/**
  * @}
  */

/** @addtogroup ALD_Public_Functions_Group2
  * @{
  */
/* Peripheral Control functions */
void ald_inc_tick(void);
void ald_systick_irq_cbk(void);      
void ald_delay_ms(__IO uint32_t delay);
void ald_delay_us(__IO uint32_t delay);
uint32_t ald_get_tick(void);
void ald_suspend_tick(void);
void ald_resume_tick(void);
uint32_t ald_get_ald_version(void);
void ald_flash_wait_config(uint8_t cycle);
ald_status_t ald_wait_flag(uint32_t *reg, uint32_t bit, flag_status_t status, uint32_t timeout);
void ald_mcu_irq_config(IRQn_Type irq, uint8_t preempt_prio, uint8_t sub_prio, type_func_t status);
void ald_mcu_timestamp_init(void);
uint32_t ald_mcu_get_timestamp(void);
uint32_t ald_mcu_get_cpu_id(void);
void ald_mcu_get_uid(uint8_t *buf);
uint32_t ald_mcu_get_chipid(void);
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

#endif /* __UTILS_H__ */
