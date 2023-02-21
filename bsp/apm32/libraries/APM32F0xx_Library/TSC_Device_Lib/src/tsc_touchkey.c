/*!
 * @file        tsc_touchkey.c
 *
 * @brief       This file contains all functions to manage TouchKey sensors.
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
#include "tsc_touchkey.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_TouchKey_Driver TSC TouchKey Driver
  @{
*/

/** @defgroup TSC_TouchKey_Macros Macros
  @{
*/

#if TOUCH_TOTAL_KEYS > 0

#define FOR_MEAS                 TSC_Globals.For_Key->p_ChD->Meas
#define FOR_DELTA                TSC_Globals.For_Key->p_ChD->Delta
#define FOR_REFER                TSC_Globals.For_Key->p_ChD->Refer
#define FOR_REFREST              TSC_Globals.For_Key->p_ChD->RefRest
#define FOR_CHANNEL_DATA         TSC_Globals.For_Key->p_ChD
#define FOR_ACQ_STATUS           TSC_Globals.For_Key->p_ChD->Flag.AcqStatus
#define FOR_OBJ_STATUS           TSC_Globals.For_Key->p_ChD->Flag.ObjStatus
#define FOR_DATA_READY           TSC_Globals.For_Key->p_ChD->Flag.DataReady

#define FOR_STATEID              TSC_Globals.For_Key->p_Data->StateId
#define FOR_CHANGE               TSC_Globals.For_Key->p_Data->Change
#define FOR_COUNTER_DEB          TSC_Globals.For_Key->p_Data->CounterDebounce
#define FOR_COUNTER_DTO          TSC_Globals.For_Key->p_Data->CounterDTO
#define FOR_DXSLOCK              TSC_Globals.For_Key->p_Data->DxsLock

#define FOR_PROXIN_TH            TSC_Globals.For_Key->p_Param->ProxInTh
#define FOR_PROXOUT_TH           TSC_Globals.For_Key->p_Param->ProxOutTh
#define FOR_DETECTIN_TH          TSC_Globals.For_Key->p_Param->DetectInTh
#define FOR_DETECTOUT_TH         TSC_Globals.For_Key->p_Param->DetectOutTh
#define FOR_CALIB_TH             TSC_Globals.For_Key->p_Param->CalibTh

#define FOR_COUNTER_DEB_CALIB    TSC_Globals.For_Key->p_Param->CounterDebCalib
#define FOR_COUNTER_DEB_PROX     TSC_Globals.For_Key->p_Param->CounterDebProx
#define FOR_COUNTER_DEB_DETECT   TSC_Globals.For_Key->p_Param->CounterDebDetect
#define FOR_COUNTER_DEB_RELEASE  TSC_Globals.For_Key->p_Param->CounterDebRelease
#define FOR_COUNTER_DEB_ERROR    TSC_Globals.For_Key->p_Param->CounterDebError

#if TOUCH_DTO > 0
    #define DTO_READ_TIME  {TSC_TouchKey_DTOGetTime();}
#else
    #define DTO_READ_TIME
#endif

#if TOUCH_COEFF_TH > 0
    #define TEST_DELTA(OPER,TH)   (FOR_DELTA OPER (uint16_t)((uint16_t)TH << TOUCH_COEFF_TH))
    #define TEST_DELTA_N(OPER,TH) (FOR_DELTA OPER -((uint16_t)((uint16_t)TH << TOUCH_COEFF_TH)))
    #define TEST_DELTA_NEGATIVE   {if (FOR_DELTA < 0) {return;}}
#else
    #define TEST_DELTA(OPER,TH)   (FOR_DELTA OPER TH)
    #define TEST_DELTA_N(OPER,TH) (FOR_DELTA OPER -(TH))
    #define TEST_DELTA_NEGATIVE
#endif

/**@} end of group TSC_TouchKey_Macros */

/** @defgroup TSC_TouchKey_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_TouchKey_Enumerations */

/** @defgroup TSC_TouchKey_Structures Structures
  @{
*/

/**@} end of group TSC_TouchKey_Structures */

/** @defgroup TSC_TouchKey_Variables Variables
  @{
*/

static TSC_tNum_T CalibDiv;

/**@} end of group TSC_TouchKey_Variables */

/** @defgroup TSC_TouchKey_Functions Functions
  @{
*/

void TSC_TouchKey_DTOGetTime(void);

/*!
 * @brief       Config parameters with default values from configuration file
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_Config(void)
{
    /* Debounce counters */
    FOR_COUNTER_DEB_CALIB   = TOUCH_DEBOUNCE_CALIB;
#if TOUCH_USE_PROX > 0
    FOR_COUNTER_DEB_PROX    = TOUCH_DEBOUNCE_PROX;
#endif
    FOR_COUNTER_DEB_DETECT  = TOUCH_DEBOUNCE_DETECT;
    FOR_COUNTER_DEB_RELEASE = TOUCH_DEBOUNCE_RELEASE;
    FOR_COUNTER_DEB_ERROR   = TOUCH_DEBOUNCE_ERROR;

    /* Thresholds */
#if TOUCH_USE_PROX > 0
    FOR_PROXIN_TH    = TOUCH_KEY_PROX_IN_TH;
    FOR_PROXOUT_TH   = TOUCH_KEY_PROX_OUT_TH;
#endif
    FOR_DETECTIN_TH  = TOUCH_KEY_DETECT_IN_TH;
    FOR_DETECTOUT_TH = TOUCH_KEY_DETECT_OUT_TH;
    FOR_CALIB_TH     = TOUCH_KEY_CALIB_TH;

    /* Config state */
    TSC_TouchKey_ConfigCalibrationState(TOUCH_CALIB_DELAY);
}

/*!
 * @brief       Process the State Machine
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_Process(void)
{
    TSC_STATEID_T stateID;

    if ((FOR_STATEID == TSC_STATEID_OFF) || (FOR_DATA_READY != 0))
    {
        FOR_DATA_READY = TSC_DATA_NOT_READY;
        stateID = FOR_STATEID;

#if TOUCH_TOTAL_TOUCHKEYS > 0
        if (TSC_Globals.For_Obj->Type == TSC_OBJ_TOUCHKEY)
        {
            TSC_Globals.For_Key->p_SM[FOR_STATEID].StateFunc();
        }
#endif

#if TOUCH_TOTAL_TOUCHKEYS_B > 0
        if (TSC_Globals.For_Obj->Type == TSC_OBJ_TOUCHKEYB)
        {
            TSC_Params.p_KeySta[FOR_STATEID].StateFunc();
        }
#endif

        /* Check if the new state has changed */
        if (FOR_STATEID != stateID)
        {
            FOR_CHANGE = TSC_STATE_CHANGED;
        }
        else
        {
            FOR_CHANGE = TSC_STATE_NOT_CHANGED;
        }

#if TOUCH_USE_DXS > 0
        if (FOR_STATEID == TSC_STATEID_TOUCH)
        {
            FOR_STATEID = TSC_STATEID_DETECT;
        }
        if (FOR_STATEID != TSC_STATEID_DETECT)
        {
            FOR_DXSLOCK = TSC_FALSE;
        }
#endif
    }
}

/*!
 * @brief       Go in Calibration state
 *
 * @param       delay: Delay before calibration starts (stabilization of noise filter)
 *
 * @retval      None
 */
void TSC_TouchKey_ConfigCalibrationState(TSC_tCounter_T delay)
{
    FOR_STATEID = TSC_STATEID_CALIB;
    FOR_CHANGE = TSC_STATE_CHANGED;
    FOR_OBJ_STATUS = TSC_OBJ_STATUS_ON;

    if (TSC_Params.NumCalibSample == 4)
    {
        CalibDiv = 2;
    }
    else if (TSC_Params.NumCalibSample == 16)
    {
        CalibDiv = 4;
    }
    else
    {
        TSC_Params.NumCalibSample =  8;
        CalibDiv = 3;
    }
    /* If a noise filter is used, the counter must be initialized to a value
     * different from 0 in order to stabilize the filter. */
    FOR_COUNTER_DEB = (TSC_tCounter_T)(delay + (TSC_tCounter_T)TSC_Params.NumCalibSample);
    FOR_REFER = 0;
}

/*!
 * @brief       Go in Off state with sensor "off"
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ConfigOffState(void)
{
    FOR_STATEID = TSC_STATEID_OFF;
    FOR_CHANGE = TSC_STATE_CHANGED;
    FOR_OBJ_STATUS = TSC_OBJ_STATUS_OFF;
}

/*!
 * @brief       Go in Off state with sensor in "Burst mode only"
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ConfigBurstOnlyState(void)
{
    FOR_STATEID = TSC_STATEID_OFF;
    FOR_CHANGE = TSC_STATE_CHANGED;
    FOR_OBJ_STATUS = TSC_OBJ_STATUS_BURST_ONLY;
}

/*!
 * @brief       Return the current state identifier
 *
 * @param       None
 *
 * @retval      State id
 */
TSC_STATEID_T TSC_TouchKey_ReadStateId(void)
{
    return (FOR_STATEID);
}

/*!
 * @brief       Return the current state mask
 *
 * @param       None
 *
 * @retval      State mask
 */
TSC_STATEMASK_T TSC_TouchKey_ReadStateMask(void)
{
    TSC_STATEMASK_T state_mask = TSC_STATEMASK_UNKNOWN;

#if TOUCH_TOTAL_TOUCHKEYS > 0
    if (TSC_Globals.For_Obj->Type == TSC_OBJ_TOUCHKEY)
    {
        state_mask = TSC_Globals.For_Key->p_SM[FOR_STATEID].StateMask;
    }
#endif

#if TOUCH_TOTAL_TOUCHKEYS_B > 0
    if (TSC_Globals.For_Obj->Type == TSC_OBJ_TOUCHKEYB)
    {
        state_mask = TSC_Params.p_KeySta[FOR_STATEID].StateMask;
    }
#endif

    return state_mask;
}

/*!
 * @brief       Return the Change flag
 *
 * @param       None
 *
 * @retval      Change flag status
 */
TSC_tNum_T TSC_TouchKey_ReadChangeFlag(void)
{
    return (FOR_CHANGE);
}

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Debounce Release processing (previous state = Proximity)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebReleaseProxState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_PROX;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if (FOR_DELTA <= FOR_PROXOUT_TH)
        {
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
        }
        else
        {
            FOR_STATEID = TSC_STATEID_PROX;
        }
    }
}
#endif /*!< if TOUCH_USE_PROX > 0 */

/*!
 * @brief       Debounce Release processing (previous state = Detect)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebReleaseDetectState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_DETECT;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( <=, FOR_DETECTOUT_TH)
        {
#if TOUCH_USE_PROX > 0
            if (FOR_DELTA > FOR_PROXOUT_TH)
            {
                FOR_STATEID = TSC_STATEID_PROX;
                return;
            }
#endif
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
        }
        else
        {
            TEST_DELTA_NEGATIVE;
            FOR_STATEID = TSC_STATEID_DETECT;
        }
    }
}

/*!
 * @brief       Debounce Release processing (previous state = Touch)
 *              Same as Debounce Release Detect processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebReleaseTouchState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_TOUCH;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( <=, FOR_DETECTOUT_TH)
        {
#if TOUCH_USE_PROX > 0
            if (FOR_DELTA > FOR_PROXOUT_TH)
            {
                FOR_STATEID = TSC_STATEID_PROX;
                return;
            }
#endif
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
        }
        else
        {
            TEST_DELTA_NEGATIVE;
            FOR_STATEID = TSC_STATEID_TOUCH;
        }
    }
}

/*!
 * @brief       Release state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessReleaseState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_COUNTER_DEB = FOR_COUNTER_DEB_ERROR;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_ERROR_RELEASE;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( >=, FOR_DETECTIN_TH)
        {
            TEST_DELTA_NEGATIVE;
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_DETECT;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_DETECT;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_DETECT;
                DTO_READ_TIME;
            }
            return;
        }

#if TOUCH_USE_PROX > 0
        if (FOR_DELTA >= FOR_PROXIN_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_PROX;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_PROX;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_PROX;
                DTO_READ_TIME;
            }
            return;
        }
#endif

        /* Check delta for re-calibration
            Warning: the threshold value is inverted in the macro */
        if TEST_DELTA_N( <=, FOR_CALIB_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_CALIB;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_CALIB;
            }
            else
            {
                TSC_TouchKey_ConfigCalibrationState(0);
            }
        }
    }
}

/*!
 * @brief       Debounce Calibration processing (previous state = Release)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebCalibrationState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_RELEASE;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        /* Still below recalibration threshold
            Warning: the threshold value is inverted in the macro */
        if TEST_DELTA_N( >, FOR_CALIB_TH)
        {
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
        else
        {
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                TSC_TouchKey_ConfigCalibrationState(0);
            }
        }
    }
}

/*!
 * @brief       Calibration state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessCalibrationState(void)
{
    TSC_tMeas_T newMeas;

#if TOUCH_CALIB_DELAY > 0
    /* Noise filter stabilization time */
    if (FOR_COUNTER_DEB > (TSC_tCounter_T)TSC_Params.NumCalibSample)
    {
        FOR_COUNTER_DEB--;
        return;
    }
#endif
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_COUNTER_DEB = FOR_COUNTER_DEB_ERROR;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_ERROR_CALIB;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        /* Read the new measure or Calculate it */
#if TOUCH_USE_MEAS > 0
        newMeas = FOR_MEAS;
#else
        newMeas = TSC_Acq_ComputeMeas(FOR_REFER, FOR_DELTA);
#endif

        /* Verify the first Reference value */
        if (FOR_COUNTER_DEB != (TSC_tCounter_T)TSC_Params.NumCalibSample)
        {
            FOR_REFER += newMeas;

            /* Check reference overflow */
            if (FOR_REFER < newMeas)
            {
                FOR_REFER = 0;
                FOR_STATEID = TSC_STATEID_ERROR;
                return;
            }
        }
        else
        {
            if (TSC_Acq_TestFirstReference(FOR_CHANNEL_DATA, newMeas))
            {
                FOR_REFER = newMeas;
            }
            else
            {
                FOR_REFER = 0;
                return;
            }
        }

        if (FOR_COUNTER_DEB > 0)
        {
            FOR_COUNTER_DEB--;
        }
        if (FOR_COUNTER_DEB == 0)
        {
            FOR_REFER >>= CalibDiv;
            FOR_REFREST = 0;
            FOR_DELTA = 0;
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
    }
}

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Debounce Proximity processing (previous state = Release)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebProxState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_RELEASE;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( >=, FOR_DETECTIN_TH)
        {
            TEST_DELTA_NEGATIVE;
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_DETECT;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_DETECT;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_DETECT;
                DTO_READ_TIME;
            }
            return;
        }

        if (FOR_DELTA < FOR_PROXIN_TH)
        {
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
        else
        {
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_PROX;
                DTO_READ_TIME;
            }
        }
    }
}
#endif

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Debounce Proximity processing (previous state = Detect)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebProxDetectState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_DETECT;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( >, FOR_DETECTOUT_TH)
        {
            TEST_DELTA_NEGATIVE;
            FOR_STATEID = TSC_STATEID_DETECT;
            return;
        }

        if (FOR_DELTA <= FOR_PROXOUT_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_RELEASE;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_RELEASE_DETECT;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
        }
        else
        {
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_PROX;
                DTO_READ_TIME;
            }
        }
    }
}
#endif

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Debounce Proximity processing (previous state = Touch)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebProxTouchState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_TOUCH;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( >, FOR_DETECTOUT_TH)
        {
            TEST_DELTA_NEGATIVE;
            FOR_STATEID = TSC_STATEID_TOUCH;
            return;
        }

        if (FOR_DELTA <= FOR_PROXOUT_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_RELEASE;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_RELEASE_TOUCH;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
        }
        else
        {
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_PROX;
                DTO_READ_TIME;
            }
        }
    }
}
#endif

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Proximity state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessProxState(void)
{
#if TOUCH_DTO > 0
    TSC_tTick_sec_T tick_detected;
#endif

    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_COUNTER_DEB = FOR_COUNTER_DEB_ERROR;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_ERROR_PROX;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if (FOR_DELTA <= FOR_PROXOUT_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_RELEASE;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_RELEASE_PROX;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
            return;
        }

        if TEST_DELTA( >=, FOR_DETECTIN_TH)
        {
            TEST_DELTA_NEGATIVE;
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_DETECT;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_DETECT;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_DETECT;
                DTO_READ_TIME;
            }
            return;
        }

        /* Stay in Proximity state */
#if TOUCH_DTO > 0
        /* Detection Time Out (DTO) processing */
        if ((TSC_Params.DTO > 1) && (TSC_Params.DTO < 64))
        {
            /* Read the detected time previously saved */
            tick_detected = FOR_COUNTER_DTO;
            /* Enter in calibration state if the DTO duration has elapsed */
            if (TSC_Time_Delay_sec(TSC_Params.DTO, &tick_detected) == TSC_STATUS_OK)
            {
                TSC_TouchKey_ConfigCalibrationState(0);
            }
        }
#endif
    }
}
#endif

/*!
 * @brief       Debounce Detect processing (previous state = Release or Proximity)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebDetectState(void)
{
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_STATEID = TSC_STATEID_RELEASE;
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( <, FOR_DETECTIN_TH)
        {
#if TOUCH_USE_PROX > 0
            if (FOR_DELTA < FOR_PROXIN_TH)
            {
                FOR_STATEID = TSC_STATEID_RELEASE;
            }
            else
            {
                FOR_COUNTER_DEB = FOR_COUNTER_DEB_PROX;
                if (FOR_COUNTER_DEB)
                {
                    FOR_STATEID = TSC_STATEID_DEB_PROX;
                }
                else
                {
                    FOR_STATEID = TSC_STATEID_PROX;
                    DTO_READ_TIME;
                }
            }
#else
            FOR_STATEID = TSC_STATEID_RELEASE;
#endif
        }
        else
        {
            TEST_DELTA_NEGATIVE;
            if (FOR_COUNTER_DEB > 0)
            {
                FOR_COUNTER_DEB--;
            }
            if (FOR_COUNTER_DEB == 0)
            {
                FOR_STATEID = TSC_STATEID_DETECT;
                DTO_READ_TIME;
            }
        }
    }
}

/*!
 * @brief       Detect state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDetectState(void)
{
#if TOUCH_DTO > 0
    TSC_tTick_sec_T tick_detected;
#endif
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_COUNTER_DEB = FOR_COUNTER_DEB_ERROR;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_ERROR_DETECT;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( >, FOR_DETECTOUT_TH)
        {
            TEST_DELTA_NEGATIVE;
#if TOUCH_DTO > 0
            /* Detection Time Out (DTO) processing */
            if ((TSC_Params.DTO > 1) && (TSC_Params.DTO < 64))
            {
                /* Read the detected time previously saved */
                tick_detected = FOR_COUNTER_DTO;
                /* Enter in calibration state if the DTO duration has elapsed */
                if (TSC_Time_Delay_sec(TSC_Params.DTO, &tick_detected) == TSC_STATUS_OK)
                {
                    TSC_TouchKey_ConfigCalibrationState(0);
                }
            }
#endif
            return;
        }

#if TOUCH_USE_PROX > 0
        if (FOR_DELTA > FOR_PROXOUT_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_PROX;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_PROX_DETECT;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_PROX;
                DTO_READ_TIME;
            }
            return;
        }
#endif

        FOR_COUNTER_DEB = FOR_COUNTER_DEB_RELEASE;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_RELEASE_DETECT;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
    }
}

/*!
 * @brief       Touch state processing, Same as Detect state
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessTouchState(void)
{
#if TOUCH_DTO > 0
    TSC_tTick_sec_T tick_detected;
#endif
    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        FOR_COUNTER_DEB = FOR_COUNTER_DEB_ERROR;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_ERROR_TOUCH;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        if TEST_DELTA( >, FOR_DETECTOUT_TH)
        {
            TEST_DELTA_NEGATIVE;
#if TOUCH_DTO > 0
            /* Detection Time Out (DTO) processing */
            if ((TSC_Params.DTO > 1) && (TSC_Params.DTO < 64))
            {
                /* Read the detected time previously saved */
                tick_detected = FOR_COUNTER_DTO;
                /* Enter in calibration state if the DTO duration has elapsed */
                if (TSC_Time_Delay_sec(TSC_Params.DTO, &tick_detected) == TSC_STATUS_OK)
                {
                    TSC_TouchKey_ConfigCalibrationState(0);
                }
            }
#endif
            return;
        }

#if TOUCH_USE_PROX > 0
        if (FOR_DELTA > FOR_PROXOUT_TH)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_PROX;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_PROX_TOUCH;
            }
            else
            {
                FOR_STATEID = TSC_STATEID_PROX;
                DTO_READ_TIME;
            }
            return;
        }
#endif

        FOR_COUNTER_DEB = FOR_COUNTER_DEB_RELEASE;
        if (FOR_COUNTER_DEB)
        {
            FOR_STATEID = TSC_STATEID_DEB_RELEASE_TOUCH;
        }
        else
        {
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
    }
}

/*!
 * @brief       Debounce error state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_ProcessDebErrorState(void)
{
    volatile TSC_STATEMASK_T mask;

    /* Acquisition error (min or max) */
    if (FOR_ACQ_STATUS & TSC_ACQ_STATUS_ERROR_MASK)
    {
        if (FOR_COUNTER_DEB > 0)
        {
            FOR_COUNTER_DEB--;
        }
        if (FOR_COUNTER_DEB == 0)
        {
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
    else /*!< Acquisition is OK or has NOISE */
    {
        mask = TSC_TouchKey_ReadStateMask();
        mask &= (TSC_STATEMASK_T)(~(TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_ERROR_BIT_MASK));

        if (mask == TSC_STATEMASK_RELEASE)
        {
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
        else if (mask == TSC_STATEMASK_PROX)
        {
            FOR_STATEID = TSC_STATEID_PROX;
        }
        else if (mask == TSC_STATEMASK_DETECT)
        {
            FOR_STATEID = TSC_STATEID_DETECT;
        }
        else if (mask == TSC_STATEMASK_TOUCH)
        {
            FOR_STATEID = TSC_STATEID_TOUCH;
        }
        else
        {
            TSC_TouchKey_ConfigCalibrationState(0);
        }
    }
}

/*!
 * @brief       Read the current time in second and affect it to the DTO counter (Private)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_TouchKey_DTOGetTime(void)
{
    disableInterrupts();
    FOR_COUNTER_DTO = (TSC_tCounter_T)TSC_Globals.Tick_sec;
    enableInterrupts();
}
#endif /*!< #if TOUCH_TOTAL_KEYS > 0 */

/**@} end of group TSC_TouchKey_Functions */
/**@} end of group TSC_TouchKey_Driver */
/**@} end of group TSC_Driver_Library */
