/*!
 * @file        tsc_filter.c
 *
 * @brief       This file contains all functions to manage the signal or delta filters.
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
#include "tsc_filter.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Filter_Driver TSC Filter Driver
  @{
*/

/** @defgroup TSC_Filter_Macros Macros
  @{
*/

/**@} end of group TSC_Filter_Macros */

/** @defgroup TSC_Filter_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Filter_Enumerations */

/** @defgroup TSC_Filter_Structures Structures
  @{
*/

/**@} end of group TSC_Filter_Structures */

/** @defgroup TSC_Filter_Variables Variables
  @{
*/

/**@} end of group TSC_Filter_Variables */

/** @defgroup TSC_Filter_Functions Functions
  @{
*/

/*!
 * @brief       Example of measure value filter
 *
 * @param       preMeasn: Previous measure value
 *
 * @param       curMeasn: Current measure value
 *
 * @retval      Filtered measure
 */
TSC_tMeas_T TSC_Filt_MeasFilter(TSC_tMeas_T preMeasn, TSC_tMeas_T curMeasn)
{
    TSC_tMeas_T value;

    value = (TSC_tMeas_T)(curMeasn << ACQ_FILTER_RANGE);

    if (preMeasn)
    {
        if (value <= preMeasn)
        {
            value = preMeasn - ((ACQ_FILTER_COEFF * (preMeasn - value)) >> 8);
        }
        else
        {
            value = preMeasn + ((ACQ_FILTER_COEFF * (value - preMeasn)) >> 8);
        }
    }
    return (value);
}

/*!
 * @brief       Example of delta value filter
 *
 * @param       delta: Delta value to modify
 *
 * @retval      Filtered delta
 */
TSC_tDelta_T TSC_Filt_DeltaFilter(TSC_tDelta_T delta)
{
    return (delta);
}

/**@} end of group TSC_Filter_Functions */
/**@} end of group TSC_Filter_Driver */
/**@} end of group TSC_Driver_Library */

