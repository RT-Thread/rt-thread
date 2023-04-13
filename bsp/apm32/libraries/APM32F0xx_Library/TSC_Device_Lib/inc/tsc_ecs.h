/*!
 * @file        tsc_ecs.h
 *
 * @brief       This file contains external declarations of the tsc_ecs.c file.
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
#ifndef __TOUCH_ECS_H
#define __TOUCH_ECS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "tsc_object.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_ECS_Driver TSC ECS Driver
  @{
*/

/** @defgroup TSC_ECS_Macros Macros
  @{
*/

#define FOR_OBJ_TYPE     TSC_Globals.For_Obj->Type
#define FOR_KEY_REF      TSC_Globals.For_Key->p_ChD->Refer
#define FOR_KEY_REFREST  TSC_Globals.For_Key->p_ChD->RefRest
#define FOR_KEY_DELTA    TSC_Globals.For_Key->p_ChD->Delta
#define FOR_KEY_STATEID  TSC_Globals.For_Key->p_Data->StateId

#define FOR_LINROT_STATEID      TSC_Globals.For_LinRot->p_Data->StateId
#define FOR_LINROT_NB_CHANNELS  TSC_Globals.For_LinRot->NumChannel

/**@} end of group TSC_ECS_Macros */

/** @defgroup TSC_ECS_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_ECS_Enumerations */

/** @defgroup TSC_ECS_Structures Structures
  @{
*/

/**@} end of group TSC_ECS_Structures */

/** @defgroup TSC_ECS_Variables Variables
  @{
*/

/**@} end of group TSC_ECS_Variables */

/** @defgroup TSC_ECS_Functions Functions
  @{
*/

TSC_tKCoeff_T TSC_Ecs_CalculateK(TSC_ObjectGroup_T* objgrp, TSC_tKCoeff_T kDiffer, TSC_tKCoeff_T kSame);
void TSC_Ecs_ProcessK(TSC_ObjectGroup_T* objgrp, TSC_tKCoeff_T kCoeff);
TSC_STATUS_T TSC_Ecs_Process(TSC_ObjectGroup_T* objgrp);

#ifdef __cplusplus
}
#endif

#endif /* __TSC_ECS_H */

/**@} end of group TSC_ECS_Functions*/
/**@} end of group TSC_ECS_Driver */
/**@} end of group TSC_Driver_Library*/
