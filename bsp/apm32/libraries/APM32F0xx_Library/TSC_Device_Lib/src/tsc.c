/*!
 * @file        tsc.c
 *
 * @brief       This file contains the Touch Driver main functions.
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

/* Includes */
#include "tsc.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @defgroup TSC_Macros Macros
  @{
*/

/**@} end of group TSC_Macros */

/** @defgroup TSC_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Enumerations */

/** @defgroup TSC_Variables Variables
  @{
*/

/* Global variables used by main() and TSC modules */
TSC_Globals_T  TSC_Globals;

/**@} end of group TSC_Variables */

/** @defgroup TSC_Functions Functions
  @{
*/

/*!
 * @brief       Config the TSC GPIO interface
 *
 * @param       block: Array holding all the blocks
 *
 * @retval      pointer to a TSC_STATUS_T structure
 */
TSC_STATUS_T TSC_Config(CONST TSC_Block_T* block)
{
    TSC_STATUS_T retval;

    /* Read blocks array */
    TSC_Globals.Block_Array = block;

    retval = TSC_Time_Config();

    if (retval == TSC_STATUS_OK)
    {
        retval = TSC_Acq_Config();
    }

    return retval;
}

/**@} end of group TSC_Functions */
/**@} end of group TSC_Driver */
/**@} end of group TSC_Driver_Library */
