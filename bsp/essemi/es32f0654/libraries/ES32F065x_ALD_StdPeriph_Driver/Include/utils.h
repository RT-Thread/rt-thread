/**
  *********************************************************************************
  *
  * @file    utils.h
  * @brief   This file contains the Utilities functions/types for the driver.
  *
  * @version V1.0
  * @date    07 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include "ald_conf.h"
#include "type.h"
#include "es32f065x.h"


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
	OK      = 0x0U,	/**< Status: OK */
	ERROR   = 0x1U,	/**< Status: ERROR */
	BUSY    = 0x2U,	/**< Status: BUSY */
	TIMEOUT = 0x3U,	/**< Status: TIMEOUT */
} ald_status_t;

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
#define __LOCK(x)				\
	do {					\
		if ((x)->lock == LOCK) {	\
			return BUSY;		\
		}				\
		else {				\
			(x)->lock = LOCK;	\
		}				\
	} while (0)

#define __UNLOCK(x)				\
	do {					\
		(x)->lock = UNLOCK;		\
	} while (0)

/**
  * @}
  */

/** @defgroup ALD_Private_Macros Private Macros
  * @{
  */
#define MCU_UID0_ADDR	0x000403E0U
#define MCU_UID1_ADDR	0x000403E8U
#define MCU_UID2_ADDR	0x000403F0U
#define MCU_CHIPID_ADDR	0x000403F8U
#define IS_PRIO(x)	((x) < 4)
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
void ald_inc_tick_weak(void);
void ald_delay_ms(__IO uint32_t delay);
uint32_t ald_get_tick(void);
void ald_suspend_tick(void);
void ald_resume_tick(void);
void ald_systick_irq_cbk(void);
void ald_inc_tick(void);
uint32_t ald_get_ald_version(void);
ald_status_t ald_wait_flag(uint32_t *reg, uint32_t bit, flag_status_t status, uint32_t timeout);
void ald_mcu_irq_config(IRQn_Type irq, uint8_t prio, type_func_t status);
uint32_t ald_mcu_get_tick(void);
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
