/*!
 * @file        tsc_ecs.c
 *
 * @brief       This file contains all functions to manage the ECS
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
#include "tsc_ecs.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_ECS_Driver TSC ECS Driver
  @{
*/

/** @defgroup TSC_ECS_Macros Macros
  @{
*/

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

/*!
 * @brief       Calculate the K coefficient
 *
 * @param       kDiffer: K coefficient when objects have different delta variation
 *
 * @param       kSame: K coefficient when objects have the same delta variation
 *
 * @retval      K coefficient (differ or same)
 */
TSC_tKCoeff_T TSC_Ecs_CalculateK(TSC_ObjectGroup_T* objgrp, TSC_tKCoeff_T kDiffer, TSC_tKCoeff_T kSame)
{
    TSC_tIndex_T   idxObj;
    TSC_tIndex_T   idxChannel;
    TSC_tDelta_T   value = 0;
    TSC_tDelta_T   Cmd = 1;
    TSC_tDelta_T   Dir = 0;
    TSC_tNum_T     numChannel = 0;
    TSC_tKCoeff_T  retval = kDiffer;
    TSC_Channel_Data_T* p_Ch = 0;
    CONST TSC_Object_T* pObj;

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
                if (FOR_KEY_STATEID != TSC_STATEID_RELEASE)
                {
                    pObj++;
                    continue;
                }
                numChannel = 1;
                p_Ch = TSC_Globals.For_Key->p_ChD;
                break;
#endif

#if TOUCH_TOTAL_LNRTS > 0
            case TSC_OBJ_LINEAR:
            case TSC_OBJ_LINEARB:
            case TSC_OBJ_ROTARY:
            case TSC_OBJ_ROTARYB:
                if (FOR_LINROT_STATEID != TSC_STATEID_RELEASE)
                {
                    pObj++;
                    continue;
                }
                numChannel = FOR_LINROT_NB_CHANNELS;
                p_Ch = TSC_Globals.For_LinRot->p_ChD;
                break;
#endif
            default:
                break;
        }

        /* Check all channels of current object */
        for (idxChannel = 0; idxChannel < numChannel; idxChannel++)
        {
            value = p_Ch->Delta;

            if (value)
            {
                if (value >= 0)
                {
                    if (Dir > 0)
                    {
                        Dir = 1;
                    }
                    else
                    {
                        Cmd = 0;
                    }
                }
                else
                {
                    if (Dir < 0)
                    {
                        Dir = -1;
                    }
                    else
                    {
                        Cmd = 0;
                    }
                }
            }
            else
            {
                Cmd = 0;
            }
            p_Ch++;
        }
        pObj++;
    }

    if (Cmd)
    {
        retval = kSame;
    }
    return retval;
}

/*!
 * @brief       Calculate the new Reference on a group of objects
 *
 * @param       objgrp: Pointer to the objects group to process
 *
 * @param       kCoeff: K coefficient to apply
 *
 * @retval      None
 */
void TSC_Ecs_ProcessK(TSC_ObjectGroup_T* objgrp, TSC_tKCoeff_T kCoeff)
{
    TSC_tIndex_T        idxObj;
    TSC_tIndex_T        idxChannel;
    CONST TSC_Object_T*  pObj;
    TSC_tKCoeff_T       kCoeffComp;
    uint32_t            meas, refer;
    TSC_tNum_T          numChannel = 0;
    TSC_Channel_Data_T*  p_Ch = 0;
    void(*pFunc_SetStateCalibration)(TSC_tCounter_T delay) = 0;

    pObj = objgrp->p_Obj;

    /* Calculate the K coefficient complement */
    kCoeffComp = (0xFF ^ kCoeff) + 1;

    /* Process all objects */
    for (idxObj = 0; idxObj < objgrp->NbObjects; idxObj++)
    {
        TSC_Obj_ConfigGlobalObj(pObj);

        switch (FOR_OBJ_TYPE)
        {
#if TOUCH_TOTAL_KEYS > 0
            case TSC_OBJ_TOUCHKEY:
            case TSC_OBJ_TOUCHKEYB:
                if (FOR_KEY_STATEID != TSC_STATEID_RELEASE)
                {
                    pObj++;
                    continue;
                }
                numChannel = 1;
                p_Ch = TSC_Globals.For_Key->p_ChD;
                pFunc_SetStateCalibration = &TSC_TouchKey_ConfigCalibrationState;
                break;
#endif

#if TOUCH_TOTAL_LNRTS > 0
            case TSC_OBJ_LINEAR:
            case TSC_OBJ_LINEARB:
            case TSC_OBJ_ROTARY:
            case TSC_OBJ_ROTARYB:
                if (FOR_LINROT_STATEID != TSC_STATEID_RELEASE)
                {
                    pObj++;
                    continue;
                }
                numChannel = FOR_LINROT_NB_CHANNELS;
                p_Ch = TSC_Globals.For_LinRot->p_ChD;
                pFunc_SetStateCalibration = &TSC_Linrot_ConfigCalibrationState;
                break;
#endif
            default:
                break;
        }

        /* Calculate the new reference + rest for all channels */
        for (idxChannel = 0; idxChannel < numChannel; idxChannel++)
        {
            meas = TSC_Acq_ComputeMeas(p_Ch->Refer, p_Ch->Delta);
            meas <<= 8;

            refer = (uint32_t)(p_Ch->Refer);
            refer <<= 8;
            refer += p_Ch->RefRest;
            refer *= kCoeffComp;
            refer += (kCoeff * meas);

            p_Ch->RefRest = (TSC_tRefRest_T)((refer >> 8) & 0xFF);
            p_Ch->Refer = (TSC_tRefer_T)(refer >> 16);

            /* Go in Calibration state in the Reference is out of Range */
            if (TSC_Acq_TestReferenceRange(p_Ch) == TSC_TRUE)
            {
                pFunc_SetStateCalibration(0);
            }
            p_Ch++;
        }
        pObj++;
    }
}

/*!
 * @brief       ECS algorithm on a group of objects
 *              The ECS is only performed if at least an object is in Release state and
 *              if no objects are in active states (Prox, Detect or Touch)
 *              An optional delay is added after the ECS condition (all sensors in Release state) is reached.
 *
 * @param       objgrp: Pointer to the objects group to process
 *
 * @retval      Status
 */
TSC_STATUS_T TSC_Ecs_Process(TSC_ObjectGroup_T* objgrp)
{
    TSC_tKCoeff_T myKcoeff;
    TSC_STATUS_T  retval;

    if ((objgrp->StateMask & TSC_STATE_RELEASE_BIT_MASK) && !(objgrp->StateMask & TSC_STATEMASK_ACTIVE))
    {
#if TOUCH_ECS_DELAY > 0
        if (!objgrp->wait)
        {
            disableInterrupts();
            objgrp->time = TSC_Globals.Tick_ms;
            enableInterrupts();
            objgrp->wait = 1;
            objgrp->execution = 0;
        }
#else
        objgrp->execution = 1;
#endif
    }
    else
    {
#if TOUCH_ECS_DELAY > 0
        objgrp->wait = 0;
#endif
        objgrp->execution = 0;
    }

#if TOUCH_ECS_DELAY > 0
    if (objgrp->wait && (!objgrp->execution))
    {
        if (TSC_Time_Delay_ms(TOUCH_ECS_DELAY, &objgrp->time) == TSC_STATUS_OK)
        {
            objgrp->execution = 1;
        }
    }
#endif

    if (objgrp->execution == 0)
    {
        retval = TSC_STATUS_BUSY;
    }
    else
    {
        /* Calculate the K coefficient */
        myKcoeff = TSC_Ecs_CalculateK(objgrp, TOUCH_ECS_K_DIFFER, TOUCH_ECS_K_SAME);
        /* Process the objects */
        TSC_Ecs_ProcessK(objgrp, myKcoeff);
        retval = TSC_STATUS_OK;
    }
    return retval;
}

/**@} end of group TSC_ECS_Functions */
/**@} end of group TSC_ECS_Driver */
/**@} end of group TSC_Driver_Library */
