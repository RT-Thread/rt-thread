/**
  *********************************************************************************
  *
  * @file    ald_dbgc.h
  * @brief   DEBUGCON module driver.
  *
  * @version V1.0
  * @date    04 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_DBGC_H__
#define __ALD_DBGC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup DBGC DBGC
  * @brief DBGC module driver
  * @{
  */



/** @defgroup DBGC_Public_Types DBGC Public Types
  * @{
  */
/**
  * @brief Debug mode select
  */
typedef enum {
	DEBC_MODE_SLEEP   = (1u << 0),	/**< Sleep mode */
	DEBC_MODE_STOP1   = (1u << 1),	/**< STOP1 mode */
	DEBC_MODE_STOP2   = (1u << 2),	/**< STOP2 mode */
	DEBC_MODE_STANDBY = (1u << 3),	/**< Standby mode */
} dbgc_mode_t;

/**
  * @brief Debug peripheral select
  */
typedef enum {
	DEBC_PERH_TIMER0  = (1u << 0),			/**< AD16C4T0 */
	DEBC_PERH_TIMER1  = (1u << 1),			/**< BS16T0 */
	DEBC_PERH_TIMER2  = (1u << 2),			/**< GP16C2T0 */
	DEBC_PERH_TIMER3  = (1u << 3),			/**< GP16C2T1 */
	DEBC_PERH_TIMER4  = (1u << 4),			/**< BS16T1 */
	DEBC_PERH_TIMER5  = (1u << 5),			/**< BS16T2 */
	DEBC_PERH_TIMER6  = (1u << 6),			/**< GP16C4T0 */
	DEBC_PERH_TIMER7  = (1u << 7),			/**< BS16T3 */
	DEBC_PERH_I2C0    = (1u << 8),			/**< I2C0 SMBUS */
	DEBC_PERH_I2C1    = (1u << 9),			/**< I2C1 SMBUS */
	DEBC_PERH_CAN     = (1u << 12),			/**< CAN */
	DEBC_PERH_LPTIM0  = (1u << 0)  | (1u << 16),	/**< LPTIM0 */
	DEBC_PERH_IWDT    = (1u << 8)  | (1u << 16),	/**< IWDT */
	DEBC_PERH_WWDT    = (1u << 9)  | (1u << 16),	/**< WWDT */
	DEBC_PERH_RTC     = (1u << 10) | (1u << 16),	/**< RTC */
} dbgc_perh_t;
/**
  * @}
  */

/** @defgroup DBGC_Public_Functions DBGC Public Functions
  * @{
  */
/**
  * @brief  Gets version.
  * @retval Version
  */
__INLINE uint32_t ald_dbgc_get_rev_id(void)
{
	return (DBGC->IDCODE >> 16);
}

/**
  * @brief  Gets core id.
  * @retval Core id
  */
__INLINE uint32_t ald_dbgc_get_core_id(void)
{
	return (DBGC->IDCODE >> 12) & 0xF;
}

/**
  * @brief  Gets device id
  * @retval device id
  */
__INLINE uint32_t ald_dbgc_get_device_id(void)
{
	return DBGC->IDCODE & 0xFFF;
}

/**
  * @brief  Configures low power debug mode
  * @param  mode: The mode of low power.
  * @param  state: ENABLE/DISABLE
  * @retval None
  */
__INLINE void ald_dbgc_mode_config(dbgc_mode_t mode, type_func_t state)
{
	if (state)
		SET_BIT(DBGC->CR, mode);
	else
		CLEAR_BIT(DBGC->CR, mode);
}

/**
  * @brief  Configures peripheral debug mode
  * @param  perh: The peripheral.
  * @param  state: ENABLE/DISABLE
  * @retval None
  */
__INLINE void ald_dbgc_perh_config(dbgc_perh_t perh, type_func_t state)
{
	if ((perh >> 16) & 0x1) {
		if (state)
			SET_BIT(DBGC->APB2FZ, perh);
		else
			CLEAR_BIT(DBGC->APB2FZ, perh);
	}
	else {
		if (state)
			SET_BIT(DBGC->APB1FZ, perh);
		else
			CLEAR_BIT(DBGC->APB1FZ, perh);
	}
}
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

#endif
