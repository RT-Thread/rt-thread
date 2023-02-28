/*!
 * @file        tsc_time.h
 *
 * @brief       This file contains external declarations of the tsc_time.c file.
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __TOUCH_TIME_H
#define __TOUCH_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"
#include "tsc_types.h"
#include "tsc_acq.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Time_Driver TSC Time Driver
  @{
*/

/** @defgroup TSC_Time_Macros Macros
  @{
*/

/**@} end of group TSC_Time_Macros */

/** @defgroup TSC_Time_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Time_Enumerations */

/** @defgroup TSC_Time_Structures Structures
  @{
*/
/**@} end of group TSC_Time_Structures */

/** @defgroup TSC_Time_Variables Variables
  @{
*/
/**@} end of group TSC_Time_Variables */

/** @defgroup TSC_Time_Functions Functions
  @{
*/

TSC_STATUS_T TSC_Time_Config(void);
void TSC_Time_ProcessInterrupt(void);
TSC_STATUS_T TSC_Time_Delay_ms(TSC_tTick_ms_T delay_ms, __IO TSC_tTick_ms_T* last_tick);
TSC_STATUS_T TSC_Time_Delay_sec(TSC_tTick_sec_T delay_sec, __IO TSC_tTick_sec_T* last_tick);
void TSC_CallBack_TimerTick(void);

#ifdef __cplusplus
}
#endif

#endif /* __TSC_TIME_H */

/**@} end of group TSC_Time_Functions */
/**@} end of group TSC_Time_Driver */
/**@} end of group TSC_Driver_Library */
