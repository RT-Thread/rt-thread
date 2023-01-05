/*!
 * @file        tsc_dxs.c
 *
 * @brief       This file contains all functions to manage the
 *              Detection Exclusion System (Dxs) algorithm

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
#include "tsc_dxs.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_DXS_Driver TSC DXS Driver
  @{
*/

/** @defgroup TSC_DXS_Macros Macros
  @{
*/

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

/*!
 * @brief       Detection Exclusion System on the first object in detect state
 *
 * @param       objgrp: Pointer to the objects group to process
 *
 * @retval      None
 */
void TSC_Dxs_FirstObj(CONST TSC_ObjectGroup_T* objgrp)
{
#if TOUCH_USE_DXS > 0

    TSC_tIndex_T       idxObj;
    TSC_tIndex_T       objLock = 0;
    CONST TSC_Object_T* pObj;
    CONST TSC_Object_T* pObjadd = 0;

    /* Exit if no object are in DETECT state */
    if ((objgrp->StateMask & TSC_STATE_DETECT_BIT_MASK) == 0)
    {
        return;
    }

    pObj = objgrp->p_Obj;

    /* Process all objects */
    for (idxObj = 0; idxObj < objgrp->NbObjects; idxObj++)
    {
        TSC_Obj_ConfigGlobalObj(pObj);

        switch (FOR_OBJ_TYPE)
        {
#if TOUCH_TOTAL_KEYS > 0
            case TSC_OBJ_TOUCHKEY:
            case TSC_OBJ_TOUCHKEYB:
                if (FOR_KEY_STATEID == TSC_STATEID_DETECT)
                {
                    if (FOR_KEY_DXSLOCK == TSC_FALSE)
                    {
                        FOR_KEY_STATEID = TSC_STATEID_TOUCH;
                        FOR_KEY_CHANGE = TSC_STATE_CHANGED;
                        if ((!pObjadd) && (!objLock))
                        {
                            pObjadd = pObj;
                        }
                    }
                    else
                    {
                        if (objLock)
                        {
                            FOR_KEY_STATEID = TSC_STATEID_TOUCH;
                            FOR_KEY_CHANGE = TSC_STATE_CHANGED;
                        }
                        else
                        {
                            objLock = 1;
                            pObjadd = 0;
                        }
                    }
                }
                break;
#endif

#if TOUCH_TOTAL_LNRTS > 0
            case TSC_OBJ_LINEAR:
            case TSC_OBJ_LINEARB:
            case TSC_OBJ_ROTARY:
            case TSC_OBJ_ROTARYB:
                if (FOR_LINROT_STATEID == TSC_STATEID_DETECT)
                {
                    if (FOR_LINROT_DXSLOCK == TSC_FALSE)
                    {
                        FOR_LINROT_STATEID = TSC_STATEID_TOUCH;
                        FOR_LINROT_CHANGE = TSC_STATE_CHANGED;
                        if ((!pObjadd) && (!objLock))
                        {
                            pObjadd = pObj;
                        }
                    }
                    else
                    {
                        if (objLock)
                        {
                            FOR_LINROT_STATEID = TSC_STATEID_TOUCH;
                            FOR_LINROT_CHANGE = TSC_STATE_CHANGED;
                        }
                        else
                        {
                            objLock = 1;
                            pObjadd = 0;
                        }
                    }
                }
                break;
#endif
            default:
                break;
        }
        pObj++;
    }

    /* Change state from TOUCH to DETECT + DxsLock flag on the candidate object only */
    if (pObjadd)
    {
        TSC_Obj_ConfigGlobalObj(pObjadd);

        switch (FOR_OBJ_TYPE)
        {
#if TOUCH_TOTAL_KEYS > 0
            case TSC_OBJ_TOUCHKEY:
            case TSC_OBJ_TOUCHKEYB:
                FOR_KEY_STATEID = TSC_STATEID_DETECT;
                FOR_KEY_CHANGE = TSC_STATE_CHANGED;
                FOR_KEY_DXSLOCK = TSC_TRUE;
                break;
#endif

#if TOUCH_TOTAL_LNRTS > 0
            case TSC_OBJ_LINEAR:
            case TSC_OBJ_LINEARB:
            case TSC_OBJ_ROTARY:
            case TSC_OBJ_ROTARYB:
                FOR_LINROT_STATEID = TSC_STATEID_DETECT;
                FOR_LINROT_CHANGE = TSC_STATE_CHANGED;
                FOR_LINROT_DXSLOCK = TSC_TRUE;
                break;
#endif
            default:
                break;
        }
    }
#endif /*!< TOUCH_USE_DXS > 0 */
}

/**@} end of group TSC_DXS_Functions */
/**@} end of group TSC_DXS_Driver */
/**@} end of group TSC_Driver_Library */
