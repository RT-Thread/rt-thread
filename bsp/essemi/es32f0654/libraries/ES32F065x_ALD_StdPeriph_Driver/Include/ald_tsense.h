/**
  *********************************************************************************
  *
  * @file    ald_tsense.h
  * @brief   Header file of TSENSE module driver.
  *
  * @version V1.0
  * @date    15 Dec 2017
  * @author  AE Team
  * @note
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
  *
  ********************************************************************************
  */

#ifndef __ALD_TSENSE_H__
#define __ALD_TSENSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup TSENSE
  * @{
  */

/** @defgroup TSENSE_Public_Macros TSENSE Public Macros
  * @{
  */
#define TSENSE_LOCK()		(WRITE_REG(TSENSE->WPR, 0x0U))
#define TSENSE_UNLOCK()		(WRITE_REG(TSENSE->WPR, 0xA55A9669U))
#define TSENSE_ENABLE()					\
do {							\
	TSENSE_UNLOCK();				\
	SET_BIT(TSENSE->CR, TSENSE_CR_EN_MSK);		\
	TSENSE_LOCK();					\
} while (0)
#define TSENSE_DISABLE()				\
do {							\
	TSENSE_UNLOCK();				\
	CLEAR_BIT(TSENSE->CR, TSENSE_CR_EN_MSK);	\
	TSENSE_LOCK();					\
} while (0)
#define TSENSE_REQ_ENABLE()				\
do {							\
	TSENSE_UNLOCK();				\
	SET_BIT(TSENSE->CR, TSENSE_CR_REQEN_MSK);	\
	TSENSE_LOCK();					\
} while (0)
#define TSENSE_REQ_DISABLE()				\
do {							\
	TSENSE_UNLOCK();				\
	CLEAR_BIT(TSENSE->CR, TSENSE_CR_REQEN_MSK);	\
	TSENSE_LOCK();					\
} while (0)
#define TSENSE_CTN_ENABLE()				\
do {							\
	TSENSE_UNLOCK();				\
	SET_BIT(TSENSE->CR, TSENSE_CR_CTN_MSK);		\
	TSENSE_LOCK();					\
} while (0)
#define TSENSE_CTN_DISABLE()				\
do {							\
	TSENSE_UNLOCK();				\
	CLEAR_BIT(TSENSE->CR, TSENSE_CR_CTN_MSK);	\
	TSENSE_LOCK();					\
} while (0)
#define TSENSE_RESET()					\
do {							\
	TSENSE_UNLOCK();				\
	SET_BIT(TSENSE->CR, TSENSE_CR_RST_MSK);		\
	TSENSE_LOCK();					\
} while (0)
#define	TSENSE_LTGR_WR(data)				\
do {							\
	TSENSE_UNLOCK();				\
	WRITE_REG(TSENSE->LTGR, (data));		\
	TSENSE_LOCK();					\
} while (0)
#define	TSENSE_HTGR_WR(data)				\
do {							\
	TSENSE_UNLOCK();				\
	WRITE_REG(TSENSE->HTGR, (data));		\
	TSENSE_LOCK();					\
} while (0)
#define	TSENSE_TBDR_WR(data)				\
do {							\
	TSENSE_UNLOCK();				\
	WRITE_REG(TSENSE->TBDR, (data));		\
	TSENSE_LOCK();					\
} while (0)
#define	TSENSE_TCALBDR_WR(data)				\
do {							\
	TSENSE_UNLOCK();				\
	WRITE_REG(TSENSE->TCALBDR, (data));		\
	TSENSE_LOCK();					\
} while (0)
/**
  * @}
  */

/** @defgroup TSENSE_Public_Types TSENSE Public Types
  * @{
  */
/**
  * @brief Temperature update time
  */
typedef enum {
	TSENSE_UPDATE_CYCLE_3 = 0x3U,	/**< 3 Cycles */
	TSENSE_UPDATE_CYCLE_4 = 0x4U,	/**< 4 Cycles */
	TSENSE_UPDATE_CYCLE_5 = 0x5U,	/**< 5 Cycles */
	TSENSE_UPDATE_CYCLE_6 = 0x6U,	/**< 6 Cycles */
	TSENSE_UPDATE_CYCLE_7 = 0x7U,	/**< 7 Cycles */
} tsense_update_cycle_t;

/**
  * @brief Temperature output mode
  */
typedef enum {
	TSENSE_OUTPUT_MODE_200  = 0x0U,	/**< 200 cycles update one temperature */
	TSENSE_OUTPUT_MODE_400  = 0x1U,	/**< 400 cycles update one temperature */
	TSENSE_OUTPUT_MODE_800  = 0x2U,	/**< 800 cycles update one temperature */
	TSENSE_OUTPUT_MODE_1600 = 0x3U,	/**< 1600 cycles update one temperature */
	TSENSE_OUTPUT_MODE_3200 = 0x4U,	/**< 3200 cycles update one temperature */
} tsense_output_mode_t;

/**
  * @brief Source select
  */
typedef enum {
	TSENSE_SOURCE_LOSC        = 0x0U,	/**< LOSC */
	TSENSE_SOURCE_LRC         = 0x1U,	/**< LRC */
} tsense_source_sel_t;


/**
  * @brief Define callback function type
  */
typedef void (*tsense_cbk)(uint16_t value, ald_status_t status);
/**
  * @}
  */

/**
  * @defgroup TSENSE_Private_Macros TSENSE Private Macros
  * @{
  */
#define IS_TSENSE_SOURCE_SEL(x)	(((x) == TSENSE_SOURCE_LOSC) || \
                                 ((x) == TSENSE_SOURCE_LRC))
/**
  * @}
  */

/** @addtogroup TSENSE_Public_Functions
  * @{
  */
/** @addtogroup TSENSE_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
extern void ald_tsense_init(void);
extern void ald_tsense_source_select(tsense_source_sel_t sel);
/**
  * @}
  */
/** @addtogroup TSENSE_Public_Functions_Group2
  * @{
  */
/* Control functions */
extern ald_status_t ald_tsense_get_value(uint16_t *tsense);
extern void ald_tsense_get_value_by_it(tsense_cbk cbk);
extern void ald_tsense_irq_handler(void);
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

#endif /* __ALD_TSENSE_H__ */
