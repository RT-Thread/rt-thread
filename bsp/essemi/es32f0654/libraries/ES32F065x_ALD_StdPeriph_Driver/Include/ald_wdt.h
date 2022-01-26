/**
 *********************************************************************************
 *
 * @file    ald_wdt.h
 * @brief   Header file of WDT module driver.
 *
 * @version V1.0
 * @date    18 Dec 2017
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

#ifndef __ALD_WDT_H__
#define __ALD_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
 * @{
 */

/** @addtogroup WDT
 * @{
 */

/** @defgroup WDT_Public_Types WDT Public Types
 * @{
 */

/**
  * @brief Wwdt no dog window
  */
typedef enum {
	WWDT_WIN_25 = 0x0U,	/**< No dog window size: 25% */
	WWDT_WIN_50 = 0x1U,	/**< No dog window size: 50% */
	WWDT_WIN_75 = 0x2U,	/**< No dog window size: 75% */
	WWDT_WIN_00 = 0x3U,	/**< No dog window size: 0% */
} wwdt_win_t;

/**
 * @}
 */

/**
 * @defgroup WDT_Private_Macros WDT Private Macros
 * @{
 */
#define WWDT_UNLOCK() {WRITE_REG(WWDT->LOCK, 0x1ACCE551U);}
#define WWDT_LOCK()   {WRITE_REG(WWDT->LOCK, 0xFFFFFFFFU);}
#define IWDT_UNLOCK() {WRITE_REG(IWDT->LOCK, 0x1ACCE551U);}
#define IWDT_LOCK()   {WRITE_REG(IWDT->LOCK, 0xFFFFFFFFU);}

/**
 * @}
 */

/**
 * @addtogroup WDT_Private_Macros WDT Private Macros
 * @{
 */
#define IS_WWDT_WIN_TYPE(x)     ((x == WWDT_WIN_25) || \
                                 (x == WWDT_WIN_50) || \
                                 (x == WWDT_WIN_75) || \
                                 (x == WWDT_WIN_00))
#define IS_FUNC_STATE(x)	(((x) == DISABLE) || \
				 ((x) == ENABLE))
/**
 * @}
 */

/** @addtogroup WWDT_Public_Functions
 * @{
 */
void ald_wwdt_init(uint32_t load, wwdt_win_t win, type_func_t interrupt);
void ald_wwdt_start(void);
uint32_t ald_wwdt_get_value(void);
it_status_t ald_wwdt_get_flag_status(void);
void ald_wwdt_clear_flag_status(void);
void ald_wwdt_feed_dog(void);
/**
 * @}
 */

/** @addtogroup IWDT_Public_Functions
 * @{
 */
void ald_iwdt_init(uint32_t load, type_func_t interrupt);
void ald_iwdt_start(void);
uint32_t ald_iwdt_get_value(void);
it_status_t ald_iwdt_get_flag_status(void);
void ald_iwdt_clear_flag_status(void);
void ald_iwdt_feed_dog(void);
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

#endif /* __ALD_WDT_H__ */
