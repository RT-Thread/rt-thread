/*!
 * @file        tsc_linrot.c
 *
 * @brief       This file contains all functions to manage Linear and Rotary sensors.
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
#include "tsc_linrot.h"

#if TOUCH_TOTAL_LNRTS > 0

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Linrot_Driver TSC Linrot Driver
  @{
*/

/** @defgroup TSC_Linrot_Macros Macros
  @{
*/

#define FOR_OBJ_TYPE              TSC_Globals.For_Obj->Type

#define FOR_STATEID               TSC_Globals.For_LinRot->p_Data->StateId
#define FOR_RAW_POSITION          TSC_Globals.For_LinRot->p_Data->RawPosition
#define FOR_POSITION              TSC_Globals.For_LinRot->p_Data->Position
#define FOR_CHANGE                TSC_Globals.For_LinRot->p_Data->Change
#define FOR_POSCHANGE             TSC_Globals.For_LinRot->p_Data->PosChange
#define FOR_COUNTER_DEB           TSC_Globals.For_LinRot->p_Data->CounterDebounce
#define FOR_COUNTER_DIR           TSC_Globals.For_LinRot->p_Data->CounterDirection
#define FOR_COUNTER_DTO           TSC_Globals.For_LinRot->p_Data->CounterDTO
#define FOR_DXSLOCK               TSC_Globals.For_LinRot->p_Data->DxsLock
#define FOR_DIRECTION             TSC_Globals.For_LinRot->p_Data->Direction

#define FOR_PROXIN_TH             TSC_Globals.For_LinRot->p_Param->ProxInTh
#define FOR_PROXOUT_TH            TSC_Globals.For_LinRot->p_Param->ProxOutTh
#define FOR_DETECTIN_TH           TSC_Globals.For_LinRot->p_Param->DetectInTh
#define FOR_DETECTOUT_TH          TSC_Globals.For_LinRot->p_Param->DetectOutTh
#define FOR_CALIB_TH              TSC_Globals.For_LinRot->p_Param->CalibTh

#define FOR_RESOLUTION            TSC_Globals.For_LinRot->p_Param->Resolution
#define FOR_DIR_CHG_POS           TSC_Globals.For_LinRot->p_Param->DirChangePos

#define FOR_COUNTER_DEB_CALIB     TSC_Globals.For_LinRot->p_Param->CounterDebCalib
#define FOR_COUNTER_DEB_PROX      TSC_Globals.For_LinRot->p_Param->CounterDebProx
#define FOR_COUNTER_DEB_DETECT    TSC_Globals.For_LinRot->p_Param->CounterDebDetect
#define FOR_COUNTER_DEB_RELEASE   TSC_Globals.For_LinRot->p_Param->CounterDebRelease
#define FOR_COUNTER_DEB_ERROR     TSC_Globals.For_LinRot->p_Param->CounterDebError
#define FOR_COUNTER_DEB_DIRECTION TSC_Globals.For_LinRot->p_Param->CounterDebDirection

#define FOR_NB_CHANNELS           TSC_Globals.For_LinRot->NumChannel
#define FOR_SCT_COMP              TSC_Globals.For_LinRot->SctComp
#define FOR_POS_CORR              TSC_Globals.For_LinRot->PosCorr

#if TOUCH_DTO > 0
    #define DTO_READ_TIME  {TSC_Linrot_ReadTimeForDTO();}
#else
    #define DTO_READ_TIME
#endif

#define DIRECTION_CHANGE_MAX_DISPLACEMENT (255)
#define DIRECTION_CHANGE_TOTAL_STEPS      (256)
#define RESOLUTION_CALCULATION            (8)

/**@} end of group TSC_Linrot_Macros */

/** @defgroup TSC_Linrot_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Linrot_Enumerations */

/** @defgroup TSC_Linrot_Structures Structures
  @{
*/

/**@} end of group TSC_Linrot_Structures */

/** @defgroup TSC_Linrot_Variables Variables
  @{
*/

static TSC_tNum_T CalibDiv;

/**
 * @brief   3 CHANNELS - CH1 CH2 CH3
 *            LINEAR - MONO - 0/255 at extremities
 */
#if TOUCH_USE_3CH_LIN_M1 > 0
CONST TSC_tPosition_T TSC_POSOFF_3CH_LIN_M1[3][3] =
{
    {    0,  -96,    0 },
    {   32,    0, -160 },
    {    0,   96,    0 }
};
#endif

/**
 * @brief   3 CHANNELS - CH1 CH2 CH3
 *            LINEAR - MONO
 */
#if TOUCH_USE_3CH_LIN_M2 > 0
CONST TSC_tPosition_T TSC_POSOFF_3CH_LIN_M2[3][3] =
{
    {    0, -192,    0 },
    {   64,    0, -320 },
    {    0,  192,    0 }
};
#endif

/**
 * @brief   3 CHANNELS - CH1 CH2 CH3 CH1
 *            LINEAR - HALF-ENDED
 */
#if TOUCH_USE_3CH_LIN_H > 0
CONST TSC_tPosition_T TSC_POSOFF_3CH_LIN_H[3][3] =
{
    {    0,  -96,  160 },
    {   32,    0, -160 },
    { -224,   96,    0 }
};
#endif

/**
 * @brief   3 CHANNELS - CH1 CH2 CH3
 *            ROTARY - MONO
 */
#if TOUCH_USE_3CH_ROT_M > 0
CONST TSC_tPosition_T TSC_POSOFF_3CH_ROT_M[3][3] =
{
    {    0,  -64,  107 },
    {   21,    0, -107 },
    { -149,   64,    0 }
};
#endif

/**
 * @brief   4 CHANNELS - CH1 CH2 CH3 CH4
 *            LINEAR - MONO - 0/255 at extremities
 */
#if TOUCH_USE_4CH_LIN_M1 > 0
CONST TSC_tPosition_T TSC_POSOFF_4CH_LIN_M1[4][4] =
{
    {    0,  -64,    0,    0 },
    {   21,    0, -107,    0 },
    {    0,   64,    0, -149 },
    {    0,    0,  107,    0 }
};
#endif

/**
 * @brief   4 CHANNELS - CH1 CH2 CH3 CH4
 *            LINEAR - MONO
 */
#if TOUCH_USE_4CH_LIN_M2 > 0
CONST TSC_tPosition_T TSC_POSOFF_4CH_LIN_M2[4][4] =
{
    {    0,  -96,    0,    0 },
    {   32,    0, -160,    0 },
    {    0,   96,    0, -224 },
    {    0,    0,  160,    0 }
};
#endif

/**
 * @brief   4 CHANNELS - CH1 CH2 CH3 CH4 CH1
 *            LINEAR - MONO - HALF-ENDED
 */
#if TOUCH_USE_4CH_LIN_H > 0
CONST TSC_tPosition_T TSC_POSOFF_4CH_LIN_H[4][4] =
{
    {    0,  -64,    0,  149 },
    {   21,    0, -107,    0 },
    {    0,   64,    0, -149 },
    { -192,    0,  107,    0 }
};
#endif

/**
 * @brief   4 CHANNELS - CH1 CH2 CH3 CH4
 *            ROTARY - MONO
 */
#if TOUCH_USE_4CH_ROT_M > 0
CONST TSC_tPosition_T TSC_POSOFF_4CH_ROT_M[4][4] =
{
    {    0,  -48,    0,  112 },
    {   16,    0,  -80,    0 },
    {    0,   48,    0, -112 },
    { -144,    0,   80,    0 }
};
#endif

/**
 * @brief   5 CHANNELS - CH1 CH2 CH3 CH4 CH5
 *            LINEAR - MONO - 0/255 at extremities
 */
#if TOUCH_USE_5CH_LIN_M1 > 0
CONST TSC_tPosition_T TSC_POSOFF_5CH_LIN_M1[5][5] =
{
    {    0,  -48,    0,    0,    0 },
    {   16,    0,  -80,    0,    0 },
    {    0,   48,    0, -112,    0 },
    {    0,    0,   80,    0, -144 },
    {    0,    0,    0,  112,    0 }
};
#endif

/**
 * @brief   5 CHANNELS - CH1 CH2 CH3 CH4 CH5
 *            LINEAR - MONO
 */
#if TOUCH_USE_5CH_LIN_M2 > 0
CONST TSC_tPosition_T TSC_POSOFF_5CH_LIN_M2[5][5] =
{
    {    0,  -64,    0,    0,    0 },
    {   21,    0, -107,    0,    0 },
    {    0,   64,    0, -149,    0 },
    {    0,    0,  107,    0, -192 },
    {    0,    0,    0,  149,    0 }
};
#endif

/**
 * @brief   5 CHANNELS - CH1 CH2 CH3 CH4 CH5 CH1
 *            LINEAR - HALF-ENDED
 */
#if TOUCH_USE_5CH_LIN_H > 0
CONST TSC_tPosition_T TSC_POSOFF_5CH_LIN_H[5][5] =
{
    {    0,  -48,    0,    0,  144 },
    {   16,    0,  -80,    0,    0 },
    {    0,   48,    0, -112,    0 },
    {    0,    0,   80,    0, -144 },
    { -176,    0,    0,  112,    0 }
};
#endif

/**
 * @brief   5 CHANNELS - CH1 CH2 CH3 CH4 CH5
 *            ROTARY - MONO
 */
#if TOUCH_USE_5CH_ROT_M > 0
CONST TSC_tPosition_T TSC_POSOFF_5CH_ROT_M[5][5] =
{
    {   0,  -38,    0,    0,  115 },
    {  13,    0,  -64,    0,    0 },
    {   0,   38,    0,  -90,    0 },
    {   0,    0,   64,    0, -115 },
    {-141,    0,    0,   90,    0 }
};
#endif

/**
 * @brief   5 CHANNELS - CH1 CH2 CH3 CH4 CH5 CH1 CH3 CH5 CH2 CH4
 *            ROTARY - DUAL
 */
#if TOUCH_USE_5CH_ROT_D > 0
CONST TSC_tPosition_T TSC_POSOFF_5CH_ROT_D[5][5] =
{
    {   0,  -19,  -83,  122,   58 },
    {   6,    0,  -32, -122,   96 },
    {  70,   19,    0,  -45,  -96 },
    {-134,  109,   32,    0,  -58 },
    { -70, -109,   83,   45,    0 }
};
#endif

/**
 * @brief   6 CHANNELS - CH1 CH2 CH3 CH4 CH5 CH6
 *            LINEAR - MONO - 0/255 at extremities
 */
#if TOUCH_USE_6CH_LIN_M1 > 0
CONST TSC_tPosition_T TSC_POSOFF_6CH_LIN_M1[6][6] =
{
    {   0,  -38,    0,    0,    0,    0 },
    {  13,    0,  -64,    0,    0,    0 },
    {   0,   38,    0,  -90,    0,    0 },
    {   0,    0,   64,    0, -115,    0 },
    {   0,    0,    0,   90,    0, -141 },
    {   0,    0,    0,    0,  115,    0 }
};
#endif

/**
 * @brief   6 CHANNELS - CH1 CH2 CH3 CH4 CH5 CH6
 *            LINEAR - MONO
 */
#if TOUCH_USE_6CH_LIN_M2 > 0
CONST TSC_tPosition_T TSC_POSOFF_6CH_LIN_M2[6][6] =
{
    {   0,  -48,    0,    0,    0,    0 },
    {  16,    0,  -80,    0,    0,    0 },
    {   0,   48,    0, -112,    0,    0 },
    {   0,    0,   80,    0, -144,    0 },
    {   0,    0,    0,  112,    0, -176 },
    {   0,    0,    0,    0,  144,    0 }
};
#endif

/**
 * @brief   6 CHANNELS - CH1 CH2 CH3 CH4 CH5 CH6 CH1
 *            LINEAR - HALF-ENDED
 */
#if TOUCH_USE_6CH_LIN_H > 0
CONST TSC_tPosition_T TSC_POSOFF_6CH_LIN_H[6][6] =
{
    {   0,  -38,    0,    0,    0,  141 },
    {  13,    0,  -64,    0,    0,    0 },
    {   0,   38,    0,  -90,    0,    0 },
    {   0,    0,   64,    0, -115,    0 },
    {   0,    0,    0,   90,    0, -141 },
    {-166,    0,    0,    0,  115,    0 }
};
#endif

/**
 * @brief   6 CHANNELS - CH1 CH2 CH3 CH4 CH5 CH6
 *            ROTARY - MONO
 */
#if TOUCH_USE_6CH_ROT_M > 0
CONST TSC_tPosition_T TSC_POSOFF_6CH_ROT_M[6][6] =
{
    {   0,  -32,    0,    0,    0,  117 },
    {  11,    0,  -53,    0,    0,    0 },
    {   0,   32,    0,  -75,    0,    0 },
    {   0,    0,   53,    0,  -96,    0 },
    {   0,    0,    0,   75,    0, -117 },
    {-139,    0,    0,    0,   96,    0 }
};
#endif

/**@} end of group TSC_Linrot_Variables */

/** @defgroup TSC_Linrot_Functions Functions
  @{
*/

/** @defgroup "Object_methods" Functions
  @{
*/

/*!
 * @brief       The parameters with default values from configuration file
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_Config(void)
{
    /* Thresholds */
#if TOUCH_USE_PROX > 0
    FOR_PROXIN_TH    = TOUCH_LINROT_PROX_IN_TH;
    FOR_PROXOUT_TH   = TOUCH_LINROT_PROX_OUT_TH;
#endif
    FOR_DETECTIN_TH  = TOUCH_LINROT_DETECT_IN_TH;
    FOR_DETECTOUT_TH = TOUCH_LINROT_DETECT_OUT_TH;
    FOR_CALIB_TH     = TOUCH_LINROT_CALIB_TH;

    /* Debounce counters */
    FOR_COUNTER_DEB_CALIB   = TOUCH_DEBOUNCE_CALIB;
#if TOUCH_USE_PROX > 0
    FOR_COUNTER_DEB_PROX    = TOUCH_DEBOUNCE_PROX;
#endif
    FOR_COUNTER_DEB_DETECT  = TOUCH_DEBOUNCE_DETECT;
    FOR_COUNTER_DEB_RELEASE = TOUCH_DEBOUNCE_RELEASE;
    FOR_COUNTER_DEB_ERROR   = TOUCH_DEBOUNCE_ERROR;

    /* Other parameters for linear/rotary only */
    FOR_RESOLUTION            = TOUCH_LINROT_RESOLUTION;
    FOR_DIR_CHG_POS           = TOUCH_LINROT_DIR_CHG_POS;
    FOR_COUNTER_DEB_DIRECTION = TOUCH_LINROT_DIR_CHG_DEB;

    /* Config state */
    TSC_Linrot_ConfigCalibrationState(TOUCH_CALIB_DELAY);
}

/*!
 * @brief       Process the State Machine
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_Process(void)
{
    TSC_STATEID_T stateID;

    /* Check if at least one channel has a data ready */
    if ((TSC_Linrot_Process_OneChannel_DataReady() == TSC_STATUS_OK) || (FOR_STATEID == TSC_STATEID_OFF))
    {
        stateID = FOR_STATEID;

#if TOUCH_TOTAL_LINROTS > 0
        if ((TSC_Globals.For_Obj->Type == TSC_OBJ_LINEAR) ||
                (TSC_Globals.For_Obj->Type == TSC_OBJ_ROTARY))
        {
            TSC_Globals.For_LinRot->p_SM[FOR_STATEID].StateFunc();
        }
#endif

#if TOUCH_TOTAL_LINROTS_B > 0
        if ((TSC_Globals.For_Obj->Type == TSC_OBJ_LINEARB) ||
                (TSC_Globals.For_Obj->Type == TSC_OBJ_ROTARYB))
        {
            TSC_Params.p_LinRotSta[FOR_STATEID].StateFunc();
        }
#endif

        if (FOR_STATEID != stateID)
        {
            FOR_CHANGE = TSC_STATE_CHANGED;
        }
        else
        {
            FOR_CHANGE = TSC_STATE_NOT_CHANGED;
        }

#if TOUCH_USE_DXS > 0
        if (FOR_STATEID != TSC_STATEID_DETECT)
        {
            FOR_DXSLOCK = TSC_FALSE;
        }
        if (FOR_STATEID == TSC_STATEID_TOUCH)
        {
            FOR_STATEID = TSC_STATEID_DETECT;
        }
#endif
    }
}

/*!
 * @brief       Calculate the position
 *
 * @param       None
 *
 * @retval      Status Return OK if position calculation is correct
 *
 * @note        The position is calculated only if the number of channels is greater than 2
 */
TSC_STATUS_T TSC_Linrot_CalcPos(void)
{
    TSC_tIndex_T     index;
    TSC_tDelta_T     normDelta;
    TSC_tNum_T       minor, major;
    TSC_tNum_T       sector = 0;
    TSC_tNum_T       prePosition = 0;
    TSC_tPosition_T  curPosition = 0;
    TSC_tsignPosition_T   updatePosition = 0;
    static TSC_tIndex_T   index1, index2;
    static TSC_tDelta_T   delta1, delta2, delta3;

    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;

    index1 = 0;
    index2 = 0;
    delta1 = 0;
    delta2 = 0;
    delta3 = 0;

    FOR_POSCHANGE = TSC_STATE_NOT_CHANGED;

    if (FOR_NB_CHANNELS < 3)
    {
        return TSC_STATUS_ERROR;
    }

    /**
     *  Sort the channels' delta
     *    - delta1 and index1 = biggest
     *    - delta2 and index2 = middle
     *    - delta3 and index3 = lowest
     */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
#if TOUCH_LINROT_USE_NORMDELTA > 0
        normDelta = TSC_Linrot_NormDelta(p_Ch, index);
#else
        normDelta = p_Ch->Delta;
#endif

        if (normDelta < 0)
        {
            normDelta = 0;
        }

        if (normDelta <= delta1)
        {
            if (normDelta <= delta2)
            {
                if (normDelta > delta3)
                {
                    delta3 = normDelta;
                }
            }
            else
            {
                delta3 = delta2;
                delta2 = normDelta;
                index2 = index;
            }
        }
        else
        {
            delta3 = delta2;
            delta2 = delta1;
            delta1 = normDelta;
            index2 = index1;
            index1 = index;
        }
        p_Ch++;
    }

    if (delta2 < ((TSC_tThreshold_T)(FOR_DETECTOUT_TH >> 1) - 1))
    {
        return TSC_STATUS_ERROR;
    }

    /******************** Position calculation **********************/

    /**
     *   B = Biggest  signal measured (Delta1/Index1)
     *   M = Middle   signal measured (Delta2/Index2)
     *   S = Smallest signal measured (Delta3/Index3)
     *
     * - The equation to find the position is:
     *   Position = Offset +/- [ Sector_Size x ( Major / (Major + Minor) ) ]
     *
     * - The Offset is the position of the middle of the Middle signal segment.
     *   All the Offset values are stored in the ROM table Table_POSITION_OFFSET.
     *
     * - Major = Biggest - Smallest signals
     *   Minor = Middle - Smallest signals
     *
     * - The Sector_Size depends of the number of channels used
     */

    /* Calculates the Major and Minor parameters */
    minor = (TSC_tNum_T)(delta2 - delta3); /*!<Middle - Smallest signals */
    major = (TSC_tNum_T)(delta1 - delta3); /*!<Biggest - Smallest signals */

    /* Select the offset position in the position offset constant table */
    curPosition = *(TSC_Globals.For_LinRot->p_PosOff + (index1 * FOR_NB_CHANNELS) + index2);
    sector = FOR_SCT_COMP;
    prePosition = FOR_POS_CORR;

    /* Calculates: [ Sector_Size x ( Major / (Major + Minor) ) ] */
    sector = major * sector;
    sector = sector / (major + minor);

    /* Use the sign bit from position table to define the interpretation direction.
        The NewPosition is multiplied by 2 because the Offset stored in the ROM
        table is divided by 2... */
    if (curPosition <= 0) /*!<Means Offset is <= 0 in the ROM table */
    {
        curPosition = (TSC_tPosition_T)((-curPosition) << 1);
        curPosition -= sector;
    }
    else /*!<Means Offset is > 0 in the position table */
    {
        curPosition = (TSC_tPosition_T)(curPosition << 1);
        curPosition += sector;
    }

    /* Position is calculated differently if LINEAR or ROTARY sensor */
    if ((FOR_OBJ_TYPE == TSC_OBJ_LINEAR) || (FOR_OBJ_TYPE == TSC_OBJ_LINEARB))
    {
        /* First adjustment used to shift all the values to obtain the "zero" */
        if (curPosition <= 0)
        {
            curPosition = curPosition + (256 - prePosition);
        }
        else
        {
            curPosition -= prePosition;
        }
        /*!<Second adjustment used to clamp the values at both ends of sensor */
        if (curPosition > 255)
        {
            curPosition = 255;
        }
        if (curPosition < 0)
        {
            curPosition = 0;
        }
    }
    else /*!<ROTARY sensor: keep only the low byte */
    {
        curPosition = (TSC_tsignPosition_T)curPosition;
    }

    /******************** Direction Change Process **********************/

    if (FOR_DIRECTION != TSC_TRUE) /*!<Clockwise direction */
    {
        /* Check Direction changed and Position overflow from 0xFF to 0x00 not realized */
        if (((TSC_tsignPosition_T)curPosition < FOR_RAW_POSITION) && ((FOR_RAW_POSITION - (TSC_tsignPosition_T)curPosition) < DIRECTION_CHANGE_MAX_DISPLACEMENT))
        {
            if ((curPosition + FOR_DIR_CHG_POS) <= FOR_RAW_POSITION)
            {
                FOR_COUNTER_DIR--;
                if (FOR_COUNTER_DIR)
                {
                    return TSC_STATUS_ERROR;
                }
                else
                {
                    FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                    FOR_DIRECTION = TSC_TRUE;  /*!<Clockwise direction */
                }
            }
            else
            {
                FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                return TSC_STATUS_ERROR;
            }
        }
        /* Check position overflow from 0x00 to 0xFF to be filtered */
        if (curPosition > (uint16_t)(FOR_RAW_POSITION + DIRECTION_CHANGE_MAX_DISPLACEMENT))
        {
            if ((curPosition + FOR_DIR_CHG_POS) <= (uint16_t)(FOR_RAW_POSITION + DIRECTION_CHANGE_TOTAL_STEPS))
            {
                FOR_COUNTER_DIR--;
                if (FOR_COUNTER_DIR)
                {
                    return TSC_STATUS_ERROR;
                }
                else
                {
                    FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                    FOR_DIRECTION = TSC_TRUE;  /*!<Clockwise direction */
                }
            }
            else
            {
                FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                return TSC_STATUS_ERROR;
            }
        }
    }
    else /*!<Anticlockwise direction */
    {
        /* Check Direction changed and Position overflow from 0x00 to 0xFF not realized */
        if (((TSC_tsignPosition_T)curPosition > FOR_RAW_POSITION) && (((TSC_tsignPosition_T)curPosition - FOR_RAW_POSITION) < DIRECTION_CHANGE_MAX_DISPLACEMENT))
        {
            if (curPosition >= (uint16_t)(FOR_RAW_POSITION + FOR_DIR_CHG_POS))
            {
                FOR_COUNTER_DIR--;
                if (FOR_COUNTER_DIR)
                {
                    return TSC_STATUS_ERROR;
                }
                else
                {
                    FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                    FOR_DIRECTION = TSC_FALSE;  /*!<Clockwise direction */
                }
            }
            else
            {
                FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                return TSC_STATUS_ERROR;
            }
        }
        /* Check position overflow from 0xFF to 0x00 to be filtered */
        if ((curPosition + DIRECTION_CHANGE_MAX_DISPLACEMENT) < FOR_RAW_POSITION)
        {
            if ((curPosition + DIRECTION_CHANGE_TOTAL_STEPS) >= (uint16_t)(FOR_RAW_POSITION + FOR_DIR_CHG_POS))
            {
                FOR_COUNTER_DIR--;
                if (FOR_COUNTER_DIR)
                {
                    return TSC_STATUS_ERROR;
                }
                else
                {
                    FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                    FOR_DIRECTION = TSC_FALSE;  /*!<Clockwise direction */
                }
            }
            else
            {
                FOR_COUNTER_DIR = FOR_COUNTER_DEB_DIRECTION;
                return TSC_STATUS_ERROR;
            }
        }
    }

    /******************** Final result **********************/

    FOR_RAW_POSITION = (TSC_tsignPosition_T)curPosition;

    updatePosition = (TSC_tsignPosition_T)((TSC_tsignPosition_T)curPosition >> (RESOLUTION_CALCULATION - FOR_RESOLUTION));

    if (FOR_POSITION != updatePosition)
    {
        FOR_POSITION = updatePosition;
        FOR_POSCHANGE = TSC_STATE_CHANGED;
        return TSC_STATUS_OK;
    }
    else
    {
        return TSC_STATUS_ERROR;
    }
}

/**@} "Object_methods" Functions */

/** @defgroup Utility Functions
  @{
*/

/*!
 * @brief     Go in Calibration state
 *
 * @param     delay Delay before calibration starts (stabilization of noise filter)
 *
 * @retval    None
 */
void TSC_Linrot_ConfigCalibrationState(TSC_tCounter_T delay)
{
    FOR_STATEID = TSC_STATEID_CALIB;
    FOR_CHANGE = TSC_STATE_CHANGED;
    TSC_Linrot_Process_AllChannel_Status(TSC_OBJ_STATUS_ON);

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
        different from 0 in order to stabilize the filter */
    FOR_COUNTER_DEB = (TSC_tCounter_T)(delay + (TSC_tCounter_T)TSC_Params.NumCalibSample);
    TSC_Linrot_Process_AllChannel_ClearRef();
}

/*!
 * @brief       Go in Off state with sensor "off"
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ConfigOffState(void)
{
    FOR_STATEID = TSC_STATEID_OFF;
    FOR_CHANGE = TSC_STATE_CHANGED;
    TSC_Linrot_Process_AllChannel_Status(TSC_OBJ_STATUS_OFF);
}

/*!
 * @brief       Go in Off state with sensor in "Burst mode only"
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ConfigBurstOnlyState(void)
{
    FOR_STATEID = TSC_STATEID_OFF;
    FOR_CHANGE = TSC_STATE_CHANGED;
    TSC_Linrot_Process_AllChannel_Status(TSC_OBJ_STATUS_BURST_ONLY);
}

/*!
 * @brief       Return the current state identifier
 *
 * @param       None
 *
 * @retval      State id
 */
TSC_STATEID_T TSC_Linrot_ReadStateId(void)
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
TSC_STATEMASK_T TSC_Linrot_ReadStateMask(void)
{
    TSC_STATEMASK_T state_mask = TSC_STATEMASK_UNKNOWN;

    switch (TSC_Globals.For_Obj->Type)
    {
#if TOUCH_TOTAL_LINROTS > 0
        case TSC_OBJ_LINEAR:
        case TSC_OBJ_ROTARY:
            state_mask = TSC_Globals.For_LinRot->p_SM[FOR_STATEID].StateMask;
            break;
#endif

#if TOUCH_TOTAL_LINROTS_B > 0
        case TSC_OBJ_LINEARB:
        case TSC_OBJ_ROTARYB:
            state_mask = TSC_Params.p_LinRotSta[FOR_STATEID].StateMask;
            break;
#endif
        default:
            break;
    }
    return state_mask;
}

/*!
 * @brief       Return the Change flag
 *
 * @param       None
 *
 * @retval      Change flag status
 */
TSC_tNum_T TSC_Linrot_ReadChangeFlag(void)
{
    return (FOR_CHANGE);
}

/**@} Utility Functions */

/** @defgroup State_machine Functions
  @{
*/

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Debounce Release processing (previous state = Proximity)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ProcessDebReleaseProxState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0))
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
    else
    {
        /* Go back to the previous state */
        FOR_STATEID = TSC_STATEID_PROX;
    }
}
#endif /*!<if TOUCH_USE_PROX > 0 */

/*!
 * @brief       Debounce Release processing (previous state = Detect)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ProcessDebReleaseDetectState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_DETECTOUT_TH, 1))
        {
#if TOUCH_USE_PROX > 0
            if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0) == TSC_STATUS_OK)
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
            FOR_STATEID = TSC_STATEID_DETECT;
        }
    }
    else
    {
        FOR_STATEID = TSC_STATEID_DETECT;
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
void TSC_Linrot_ProcessDebReleaseTouchState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_DETECTOUT_TH, 1))
        {
#if TOUCH_USE_PROX > 0
            if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0) == TSC_STATUS_OK)
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
            FOR_STATEID = TSC_STATEID_TOUCH;
        }
    }
    else
    {
        FOR_STATEID = TSC_STATEID_TOUCH;
    }
}

/*!
 * @brief       Release state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ProcessReleaseState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_DETECTIN_TH, 1) == TSC_STATUS_OK)
        {
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
        if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_PROXIN_TH, 0) == TSC_STATUS_OK)
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

        /* Check delta for re-calibration */
        if (TSC_Linrot_Process_OneChannel_DeltaBelowEquMinus(FOR_CALIB_TH, 1) == TSC_STATUS_OK)
        {
            FOR_COUNTER_DEB = FOR_COUNTER_DEB_CALIB;
            if (FOR_COUNTER_DEB)
            {
                FOR_STATEID = TSC_STATEID_DEB_CALIB;
            }
            else
            {
                TSC_Linrot_ConfigCalibrationState(0);
            }
        }
    }
    else
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
}

/*!
 * @brief       Debounce Calibration processing (previous state = Release)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ProcessDebCalibrationState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaBelowEquMinus(FOR_CALIB_TH, 1))
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
                TSC_Linrot_ConfigCalibrationState(0);
            }
        }
    }
    else
    {
        FOR_STATEID = TSC_STATEID_RELEASE;
    }
}

/*!
 * @brief       Calibration state processing
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ProcessCalibrationState(void)
{
    TSC_tMeas_T   newMeas;
    TSC_tIndex_T  index;
    TSC_Channel_Data_T* p_Ch;

#if TOUCH_CALIB_DELAY > 0
    /* Noise filter stabilization time */
    if (FOR_COUNTER_DEB > (TSC_tCounter_T)TSC_Params.NumCalibSample)
    {
        FOR_COUNTER_DEB--;
        return;
    }
#endif

    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        /* Process all channels */
        p_Ch = TSC_Globals.For_LinRot->p_ChD;

        for (index = 0; index < FOR_NB_CHANNELS; index++)
        {
            /* Read the new measure or Calculate it */
#if TOUCH_USE_MEAS > 0
            newMeas = p_Ch->Meas;
#else
            newMeas = TSC_Acq_ComputeMeas(p_Ch->Refer, p_Ch->Delta);
#endif

            /* Verify the first Reference value */
            if (FOR_COUNTER_DEB != (TSC_tCounter_T)TSC_Params.NumCalibSample)
            {
                p_Ch->Refer += newMeas;

                if (p_Ch->Refer < newMeas)
                {
                    p_Ch->Refer = 0;
                    FOR_STATEID = TSC_STATEID_ERROR;
                    return;
                }
            }
            else
            {
                if (TSC_Acq_TestFirstReference(p_Ch, newMeas))
                {
                    p_Ch->Refer = newMeas;
                }
                else
                {
                    p_Ch->Refer = 0;
                    return;
                }
            }
            p_Ch++;
        }

        if (FOR_COUNTER_DEB > 0)
        {
            FOR_COUNTER_DEB--;
        }
        if (FOR_COUNTER_DEB == 0)
        {
            /* Process all channels */
            p_Ch = TSC_Globals.For_LinRot->p_ChD;

            for (index = 0; index < FOR_NB_CHANNELS; index++)
            {
                p_Ch->Refer >>= CalibDiv;
                p_Ch->RefRest = 0;
                p_Ch->Delta = 0;
                p_Ch++;
            }
            FOR_STATEID = TSC_STATEID_RELEASE;
        }
    }
    else
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
}

#if TOUCH_USE_PROX > 0
/*!
 * @brief       Debounce Proximity processing (previous state = Release)
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Linrot_ProcessDebProxState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_DETECTIN_TH, 1) == TSC_STATUS_OK)
        {
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

        if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_PROXIN_TH, 0))
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
    else
    {
        FOR_STATEID = TSC_STATEID_RELEASE;
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
void TSC_Linrot_ProcessDebProxDetectState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_DETECTOUT_TH, 1) == TSC_STATUS_OK)
        {
            FOR_STATEID = TSC_STATEID_DETECT;
            return;
        }

        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0))
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
    else
    {
        FOR_STATEID = TSC_STATEID_DETECT;
    }
}
#endif

#if TOUCH_USE_PROX > 0
/*!
 * @brief      Debounce Proximity processing (previous state = Touch)
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ProcessDebProxTouchState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_DETECTOUT_TH, 1) == TSC_STATUS_OK)
        {
            FOR_STATEID = TSC_STATEID_TOUCH;
            return;
        }

        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0))
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
    else
    {
        FOR_STATEID = TSC_STATEID_TOUCH;
    }
}
#endif

#if TOUCH_USE_PROX > 0
/*!
 * @brief     roximity state processing
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ProcessProxState(void)
{
#if TOUCH_DTO > 0
    TSC_tTick_sec_T tick_detected;
#endif

    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_DETECTIN_TH, 1) == TSC_STATUS_OK)
        {
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

        if (TSC_Linrot_Process_AllChannel_DeltaBelowEqu(FOR_PROXOUT_TH, 0) == TSC_STATUS_OK)
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

        /* Stay in Proximity state */
#if TOUCH_DTO > 0
        /* Detection Time Out (DTO) processing */
        if ((TSC_Params.DTO > 1) && (TSC_Params.DTO < 64))
        {
            tick_detected = FOR_COUNTER_DTO;
            /* Enter in calibration state if the DTO duration has elapsed */
            if (TSC_Time_Delay_sec(TSC_Params.DTO, &tick_detected) == TSC_STATUS_OK)
            {
                TSC_Linrot_ConfigCalibrationState(0);
            }
        }
#endif
    }
    else
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
}
#endif

/*!
 * @brief      Debounce Detect processing (previous state = Release or Proximity)
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ProcessDebDetectState(void)
{
    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_DETECTIN_TH, 1))
        {
#if TOUCH_USE_PROX > 0
            if (TSC_Linrot_Process_OneChannel_DeltaAboveEqu(FOR_PROXIN_TH, 0))
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
    else
    {
        FOR_STATEID = TSC_STATEID_RELEASE;
    }
}

/*!
 * @brief      Detect state processing
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ProcessDetectState(void)
{
#if TOUCH_DTO > 0
    TSC_STATUS_T pos_sts;
    TSC_tTick_sec_T tick_detected;
#endif

    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_DETECTOUT_TH, 1) == TSC_STATUS_OK)
        {
            /* Calculate position */
            if ((FOR_OBJ_TYPE == TSC_OBJ_LINEAR) || (FOR_OBJ_TYPE == TSC_OBJ_ROTARY))
            {
#if TOUCH_DTO > 0
                pos_sts = TSC_Globals.For_LinRot->p_Methods->CalcPosition();
#else
                TSC_Globals.For_LinRot->p_Methods->CalcPosition();
#endif
            }
            else /*!<TSC_OBJ_LINEARB or TSC_OBJ_ROTARYB */
            {
#if TOUCH_DTO > 0
                pos_sts = TSC_Params.p_LinRotMet->CalcPosition();
#else
                TSC_Params.p_LinRotMet->CalcPosition();
#endif
            }
#if TOUCH_DTO > 0
            /* Detection Time Out (DTO) processing, Only if the Position has NOT changed */
            if (pos_sts)
            {
                if ((TSC_Params.DTO > 1) && (TSC_Params.DTO < 64))
                {
                    tick_detected = FOR_COUNTER_DTO;
                    /* Enter in calibration state if the DTO duration has elapsed */
                    if (TSC_Time_Delay_sec(TSC_Params.DTO, &tick_detected) == TSC_STATUS_OK)
                    {
                        TSC_Linrot_ConfigCalibrationState(0);
                    }
                }
            }
            else
            {
                DTO_READ_TIME;
            }
#endif
            return;
        }

#if TOUCH_USE_PROX > 0
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0) == TSC_STATUS_OK)
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
    else
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
}

/*!
 * @brief      Touch state processing, Same as Detect state
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ProcessTouchState(void)
{
#if TOUCH_DTO > 0
    TSC_STATUS_T pos_sts;
    TSC_tTick_sec_T tick_detected;
#endif

    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_DETECTOUT_TH, 1) == TSC_STATUS_OK)
        {
            /* Calculate position */
            if ((FOR_OBJ_TYPE == TSC_OBJ_LINEAR) || (FOR_OBJ_TYPE == TSC_OBJ_ROTARY))
            {
#if TOUCH_DTO > 0
                pos_sts = TSC_Globals.For_LinRot->p_Methods->CalcPosition();
#else
                TSC_Globals.For_LinRot->p_Methods->CalcPosition();
#endif
            }
            else /* TSC_OBJ_LINEARB or TSC_OBJ_ROTARYB */
            {
#if TOUCH_DTO > 0
                pos_sts = TSC_Params.p_LinRotMet->CalcPosition();
#else
                TSC_Params.p_LinRotMet->CalcPosition();
#endif
            }
#if TOUCH_DTO > 0
            /* Detection Time Out (DTO) processing, Only if the Position has NOT changed */
            if (pos_sts)
            {
                if ((TSC_Params.DTO > 1) && (TSC_Params.DTO < 64))
                {
                    tick_detected = FOR_COUNTER_DTO;
                    /* Enter in calibration state if the DTO duration has elapsed */
                    if (TSC_Time_Delay_sec(TSC_Params.DTO, &tick_detected) == TSC_STATUS_OK)
                    {
                        TSC_Linrot_ConfigCalibrationState(0);
                    }
                }
            }
            else
            {
                DTO_READ_TIME;
            }
#endif
            return;
        }

#if TOUCH_USE_PROX > 0
        if (TSC_Linrot_Process_OneChannel_DeltaAbove(FOR_PROXOUT_TH, 0) == TSC_STATUS_OK)
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
    else
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
}

/*!
 * @brief      Debounce error state processing
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ProcessDebErrorState(void)
{
    volatile TSC_STATEMASK_T mask;

    if (TSC_Linrot_Process_OneChannel_AcqStatusError())
    {
        mask = TSC_Linrot_ReadStateMask();
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
            TSC_Linrot_ConfigCalibrationState(0);
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
            FOR_STATEID = TSC_STATEID_ERROR;
        }
    }
}

/**@} State_machine Functions */

/** @defgroup Private Functions
  @{
*/

/*!
 * @brief      Read the current time in second and affect it to the DTO counter (Private)
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_ReadTimeForDTO(void)
{
    disableInterrupts();
    FOR_COUNTER_DTO = (TSC_tCounter_T)TSC_Globals.Tick_sec;
    enableInterrupts();
}

/*!
 * @brief      Set all channels status to ON, OFF or BURST only
 *
 * @param      status: Channel status
 *
 * @retval     None
 */
void TSC_Linrot_Process_AllChannel_Status(TSC_OBJ_STATUS_T status)
{
    TSC_tIndex_T index;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;
    /* Config channels status */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
        p_Ch->Flag.ObjStatus = status;
        p_Ch++;
    }
}

/*!
 * @brief      Check if at least one channel has a data ready
 *
 * @param      None
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DataReady(void)
{
    TSC_tIndex_T index;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;
    TSC_STATUS_T retval = TSC_STATUS_ERROR;
    /* Return OK if at least one channel has a data ready */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
        if (p_Ch->Flag.DataReady == TSC_DATA_READY)
        {
            p_Ch->Flag.DataReady = TSC_DATA_NOT_READY;
            retval = TSC_STATUS_OK;
        }
        p_Ch++;
    }
    return retval;
}

/*!
 * @brief      Check if all channels are equal to the status passed
 *
 * @param      status: Channel status
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_AllChannel_AcqStatus(TSC_ACQ_STATUS_T status)
{
    TSC_tIndex_T index;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;
    /* Return OK if ALL channels have the correct acq status */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
        if (p_Ch->Flag.AcqStatus != status)
        {
            return TSC_STATUS_ERROR;
        }
        p_Ch++;
    }
    return TSC_STATUS_OK;
}

/*!
 * @brief      Check if at least one channel is in error
 *
 * @param      None
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_OneChannel_AcqStatusError(void)
{
    TSC_tIndex_T index;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;
    /* Return OK if at least one channel is in acquisition error min or max */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
        if (p_Ch->Flag.AcqStatus & TSC_ACQ_STATUS_ERROR_MASK)
        {
            return TSC_STATUS_OK;
        }
        p_Ch++;
    }
    return TSC_STATUS_ERROR;
}

/*!
 * @brief      Check if at least one channel is below or equal a threshold (inverted)
 *
 * @param      threshold: Threshold
 *
 * @param      Cmd: Enable or Disable the multiplier coefficient on threshold
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DeltaBelowEquMinus(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd)
{
    TSC_tIndex_T index;
    TSC_tDelta_T normDelta;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;

#if TOUCH_COEFF_TH > 0
    uint16_t nowThreshold;
    if (Cmd != ENABLE)
    {
        nowThreshold = threshold;
    }
    else
    {
        nowThreshold = (uint16_t)((uint16_t)threshold << TOUCH_COEFF_TH);
    }
#endif

    /* Return OK if at least one channel is below or equal the threshold */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
#if TOUCH_LINROT_USE_NORMDELTA > 0
        normDelta = TSC_Linrot_NormDelta(p_Ch, index);
#else
        normDelta = p_Ch->Delta;
#endif

#if TOUCH_COEFF_TH > 0
        if (normDelta <= -nowThreshold)
#else
        if (normDelta <= -threshold)
#endif
        {
            return TSC_STATUS_OK;
        }
        p_Ch++;
    }
    return TSC_STATUS_ERROR;
}

/*!
 * @brief      Check if at least one channel is above or equal a threshold
 *
 * @param      threshold: Threshold
 *
 * @param      Cmd: Enable or Disable the multiplier coefficient on threshold
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DeltaAboveEqu(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd)
{
    TSC_tIndex_T index;
    TSC_tDelta_T normDelta;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;

#if TOUCH_COEFF_TH > 0
    uint16_t nowThreshold;
    if (Cmd != ENABLE)
    {
        nowThreshold = threshold;
    }
    else
    {
        nowThreshold = (uint16_t)((uint16_t)threshold << TOUCH_COEFF_TH);
    }
#endif

    /* Return OK if at least one channel is above or equal the threshold */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
#if TOUCH_LINROT_USE_NORMDELTA > 0
        normDelta = TSC_Linrot_NormDelta(p_Ch, index);
#else
        normDelta = p_Ch->Delta;
#endif

#if TOUCH_COEFF_TH > 0
        if (normDelta >= nowThreshold)
#else
        if (normDelta >= threshold)
#endif
        {
#if TOUCH_COEFF_TH > 0
            if (normDelta < 0)
            {
                p_Ch++;
                continue;
            }
#endif
            return TSC_STATUS_OK;
        }
        p_Ch++;
    }
    return TSC_STATUS_ERROR;
}

/*!
 * @brief      Check if at least one channel is stricly above a threshold
 *
 * @param      threshold: Threshold
 *
 * @param      Cmd: Enable or Disable the multiplier coefficient on threshold
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DeltaAbove(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd)
{
    TSC_tIndex_T index;
    TSC_tDelta_T normDelta;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;

#if TOUCH_COEFF_TH > 0
    uint16_t nowThreshold;
    if (Cmd != ENABLE)
    {
        nowThreshold = threshold;
    }
    else
    {
        nowThreshold = (uint16_t)((uint16_t)threshold << TOUCH_COEFF_TH);
    }
#endif

    /* Return OK if at least one channel is above the threshold */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
#if TOUCH_LINROT_USE_NORMDELTA > 0
        normDelta = TSC_Linrot_NormDelta(p_Ch, index);
#else
        normDelta = p_Ch->Delta;
#endif

#if TOUCH_COEFF_TH > 0
        if (normDelta > nowThreshold)
#else
        if (normDelta > threshold)
#endif
        {
#if TOUCH_COEFF_TH > 0
            if (normDelta < 0)
            {
                p_Ch++;
                continue;
            }
#endif
            return TSC_STATUS_OK;
        }
        p_Ch++;
    }
    return TSC_STATUS_ERROR;
}

/*!
 * @brief      Check if all channels are below or equal a threshold
 *
 * @param      threshold: Threshold
 *
 * @param      Cmd: Enable or Disable the multiplier coefficient on threshold
 *
 * @retval     Status
 */
TSC_STATUS_T TSC_Linrot_Process_AllChannel_DeltaBelowEqu(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd)
{
    TSC_tIndex_T index;
    TSC_tDelta_T normDelta;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;

#if TOUCH_COEFF_TH > 0
    uint16_t nowThreshold;
    if (Cmd != ENABLE)
    {
        nowThreshold = threshold;
    }
    else
    {
        nowThreshold = (uint16_t)((uint16_t)threshold << TOUCH_COEFF_TH);
    }
#endif

    /* Return OK if ALL channels are below or equal the threshold */
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
#if TOUCH_LINROT_USE_NORMDELTA > 0
        normDelta = TSC_Linrot_NormDelta(p_Ch, index);
#else
        normDelta = p_Ch->Delta;
#endif

#if TOUCH_COEFF_TH > 0
        if (normDelta > nowThreshold)
#else
        if (normDelta > threshold)
#endif
        {
#if TOUCH_COEFF_TH > 0
            if (normDelta < 0)
            {
                p_Ch++;
                continue;
            }
#endif
            return TSC_STATUS_ERROR;
        }
        p_Ch++;
    }
    return TSC_STATUS_OK;
}

/*!
 * @brief      Clear the Reference and ReferenceRest for all channels
 *
 * @param      None
 *
 * @retval     None
 */
void TSC_Linrot_Process_AllChannel_ClearRef(void)
{
    TSC_tIndex_T index;
    TSC_Channel_Data_T* p_Ch = TSC_Globals.For_LinRot->p_ChD;
    for (index = 0; index < FOR_NB_CHANNELS; index++)
    {
        p_Ch->Refer = 0;
        p_Ch->RefRest = 0;
        p_Ch++;
    }
}

/*!
 * @brief      Normalize a Delta value
 *
 * @param      channel: Pointer to the current channel
 *
 * @param      index: Index of the channel
 *
 * @retval     Normalized Delta value
 */
TSC_tDelta_T TSC_Linrot_NormDelta(TSC_Channel_Data_T* channel, TSC_tIndex_T index)
{
    uint32_t tmpdelta = channel->Delta;

    if (TSC_Globals.For_LinRot->p_DeltaCoeff[index] != 0x0100)
    {
        tmpdelta = (uint32_t)(tmpdelta * TSC_Globals.For_LinRot->p_DeltaCoeff[index]);
        tmpdelta = tmpdelta >> (uint8_t)8;
    }
    return (TSC_tDelta_T)tmpdelta;
}
#endif /*!<#if TOUCH_TOTAL_LNRTS > 0 */

/**@} Private Functions */

/**@} end of group TSC_Linrot_Functions */
/**@} end of group TSC_Linrot_Driver */
/**@} end of group TSC_Driver_Library */
