/*!
 * @file        tsc_dxs.h
 *
 * @brief       This file contains external declarations of the tsc_dxs.c file.
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
#ifndef __TOUCH_DXS_H
#define __TOUCH_DXS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "tsc_object.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_DXS_Driver TSC DXS Driver
  @{
*/

/** @defgroup TSC_DXS_Macros Macros
  @{
*/

#define FOR_OBJ_TYPE       TSC_Globals.For_Obj->Type

#define FOR_KEY            TSC_Globals.For_Key
#define FOR_KEY_STATEID    TSC_Globals.For_Key->p_Data->StateId
#define FOR_KEY_DXSLOCK    TSC_Globals.For_Key->p_Data->DxsLock
#define FOR_KEY_CHANGE     TSC_Globals.For_Key->p_Data->Change

#define FOR_LINROT         TSC_Globals.For_LinRot
#define FOR_LINROT_STATEID TSC_Globals.For_LinRot->p_Data->StateId
#define FOR_LINROT_DXSLOCK TSC_Globals.For_LinRot->p_Data->DxsLock
#define FOR_LINROT_CHANGE  TSC_Globals.For_LinRot->p_Data->Change

/**@} end of group TSC_DXS_Macros */

/** @defgroup TSC_DXS_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_DXS_Enumerations */

/** @defgroup TSC_DXS_Structures Structures
  @{
*/

/**@} end of group TSC_DXS_Structures */

/** @defgroup TSC_DXS_Variables Variables
  @{
*/

/**@} end of group TSC_DXS_Variables */

/** @defgroup TSC_DXS_Functions Functions
  @{
*/

void TSC_Dxs_FirstObj(CONST TSC_ObjectGroup_T* objgrp);

#ifdef __cplusplus
}
#endif

#endif /* __TSC_DXS_H */

/**@} end of group TSC_DXS_Functions */
/**@} end of group TSC_DXS_Driver */
/**@} end of group TSC_Driver_Library */
