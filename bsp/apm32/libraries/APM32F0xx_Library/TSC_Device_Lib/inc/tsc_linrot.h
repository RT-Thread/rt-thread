/*!
 * @file        tsc_linrot.h
 *
 * @brief       This file contains external declarations of the tsc_linrot.c file.
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
#ifndef __TOUCH_LINROT_H
#define __TOUCH_LINROT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "tsc_acq.h"
#include "tsc_time.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Linrot_Driver TSC Linrot Driver
  @{
*/

/** @defgroup TSC_Linrot_Macros Macros
  @{
*/

#define TSC_SCTCOMP_3CH_LIN_M1 ((TSC_tNum_T)(128))
#define TSC_POSCORR_3CH_LIN_M1 ((TSC_tNum_T)( 64))
#define TSC_SCTCOMP_3CH_LIN_M2 ((TSC_tNum_T)(256))
#define TSC_POSCORR_3CH_LIN_M2 ((TSC_tNum_T)(256))

#define TSC_SCTCOMP_3CH_LIN_H  ((TSC_tNum_T)(128))
#define TSC_POSCORR_3CH_LIN_H  ((TSC_tNum_T)(128))

#define TSC_SCTCOMP_3CH_ROT_M  ((TSC_tNum_T)( 85))

#define TSC_SCTCOMP_4CH_LIN_M1 ((TSC_tNum_T)( 85))
#define TSC_POSCORR_4CH_LIN_M1 ((TSC_tNum_T)( 43))
#define TSC_SCTCOMP_4CH_LIN_M2 ((TSC_tNum_T)(128))
#define TSC_POSCORR_4CH_LIN_M2 ((TSC_tNum_T)(128))

#define TSC_SCTCOMP_4CH_LIN_H  ((TSC_tNum_T)( 85))
#define TSC_POSCORR_4CH_LIN_H  ((TSC_tNum_T)( 85))

#define TSC_SCTCOMP_4CH_ROT_M  ((TSC_tNum_T)( 64))

#define TSC_SCTCOMP_5CH_LIN_M1 ((TSC_tNum_T)( 64))
#define TSC_POSCORR_5CH_LIN_M1 ((TSC_tNum_T)( 32))
#define TSC_SCTCOMP_5CH_LIN_M2 ((TSC_tNum_T)( 85))
#define TSC_POSCORR_5CH_LIN_M2 ((TSC_tNum_T)( 85))

#define TSC_SCTCOMP_5CH_LIN_H  ((TSC_tNum_T)( 64))
#define TSC_POSCORR_5CH_LIN_H  ((TSC_tNum_T)( 64))

#define TSC_SCTCOMP_5CH_ROT_M  ((TSC_tNum_T)( 51))

#define TSC_SCTCOMP_5CH_ROT_D  ((TSC_tNum_T)( 26))

#define TSC_SCTCOMP_6CH_LIN_M1 ((TSC_tNum_T)( 51))
#define TSC_POSCORR_6CH_LIN_M1 ((TSC_tNum_T)( 25))
#define TSC_SCTCOMP_6CH_LIN_M2 ((TSC_tNum_T)( 64))
#define TSC_POSCORR_6CH_LIN_M2 ((TSC_tNum_T)( 64))

#define TSC_SCTCOMP_6CH_LIN_H  ((TSC_tNum_T)( 51))
#define TSC_POSCORR_6CH_LIN_H  ((TSC_tNum_T)( 51))

#define TSC_SCTCOMP_6CH_ROT_M  ((TSC_tNum_T)( 43))

/**@} end of group TSC_Linrot_Macros */

/** @defgroup TSC_Linrot_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Linrot_Enumerations */

/** @defgroup TSC_Linrot_Structures Structures
  @{
*/

/**
 * @brief   Contains all data related to Linear and Rotary sensor.
 *          Variables of this structure type must be placed in RAM only.
 */
typedef struct
{
    TSC_STATEID_T          StateId;              /*!< Current state identifier */
    TSC_tsignPosition_T    RawPosition;          /*!< Raw position */
    TSC_tsignPosition_T    Position;             /*!< Scaled position */
    TSC_tCounter_T         CounterDebounce;      /*!< Counter for debounce and calibration management */
    unsigned int           CounterDTO       : 6; /*!< Counter for DTO management (TSC_tCounter_T) */
    unsigned int           Change           : 1; /*!< The State is different from the previous one (TSC_STATE_T) */
    unsigned int           PosChange        : 1; /*!< The RawPosition/Position is different from the previous one (TSC_STATE_T) */
    unsigned int           CounterDirection : 6; /*!< Counter for direction debounce management (TSC_tCounter_T) */
    unsigned int           DxsLock          : 1; /*!< The State is locked by the DxS (TSC_BOOL_T) */
    unsigned int           Direction        : 1; /*!< Movement direction (TSC_BOOL_T) */
} TSC_LinRotData_T;

/**
 * @brief   Contains all parameters related to Linear and Rotary sensor.
 *          Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
    /* Thresholds */
#if TOUCH_USE_PROX > 0
    TSC_tThreshold_T       ProxInTh;             /*!< Proximity state in threshold */
    TSC_tThreshold_T       ProxOutTh;            /*!< Proximity state out threshold */
#endif
    TSC_tThreshold_T       DetectInTh;           /*!< Detection state in threshold */
    TSC_tThreshold_T       DetectOutTh;          /*!< Detection state out threshold */
    TSC_tThreshold_T       CalibTh;              /*!< Calibration state threshold */

    /* Debounce counters */
    TSC_tCounter_T         CounterDebCalib;      /*!< Debounce counter to enter in Calibration state */
#if TOUCH_USE_PROX > 0
    TSC_tCounter_T         CounterDebProx;       /*!< Debounce counter to enter in Proximity state */
#endif
    TSC_tCounter_T         CounterDebDetect;     /*!< Debounce counter to enter in Detect state */
    TSC_tCounter_T         CounterDebRelease;    /*!< Debounce counter to enter in Release state */
    TSC_tCounter_T         CounterDebError;      /*!< Debounce counter to enter in Error state */
    TSC_tCounter_T         CounterDebDirection;  /*!< Debounce counter for the direction change */

    /* Other parameters */
    TSC_tCounter_T         Resolution;           /*!< Position resolution */
    TSC_tsignPosition_T    DirChangePos;         /*!< Direction change position threshold */
} TSC_LinRotParam_T;

/**
 * @brief   Contains all parameters related to Linear and Rotary sensor.
 *          Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
    TSC_LinRotData_T*           p_Data;       /*!< Data (state id, counter, flag, ...) */
    TSC_LinRotParam_T*          p_Param;      /*!< Parameters (thresholds, debounce, ...) */
    TSC_Channel_Data_T*         p_ChD;        /*!< First Channel Data (Meas, Refer, Delta, ...) */
    TSC_tNum_T                  NumChannel;   /*!< Number of channels */
    CONST uint16_t*             p_DeltaCoeff; /*!< Coefficient to apply on Delta */
    CONST TSC_tPosition_T*      p_PosOff;     /*!< Position offset table */
    TSC_tNum_T                  SctComp;      /*!< Sector Computation */
    TSC_tNum_T                  PosCorr;      /*!< Position Correction */
    CONST TSC_State_T*          p_SM;         /*!< State Machine */
    CONST TSC_LinRotMethods_T*  p_Methods;    /*!< Methods */
} TSC_LinRot_T;

/**
 * @brief   Contains all parameters related to Linear and Rotary sensor.
 *          Variables of this structure type can be placed in RAM or ROM.
 *          Basic sensor does not contain its own state machine and methods.
 *          It used default ones instead to gain memory space.
 */
typedef struct
{
    TSC_LinRotData_T*           p_Data;       /*!< Data (state id, counter, flag, ...) */
    TSC_LinRotParam_T*          p_Param;      /*!< Parameters (thresholds, debounce, ...) */
    TSC_Channel_Data_T*         p_ChD;        /*!< First Channel Data (Meas, Refer, Delta, ...) */
    TSC_tNum_T                  NumChannel;   /*!< Number of channels */
    CONST uint16_t*             p_DeltaCoeff; /*!< Coefficient to apply on Delta */
    CONST TSC_tPosition_T*      p_PosOff;     /*!< Position offset table */
    TSC_tNum_T                  SctComp;      /*!< Sector Computation */
    TSC_tNum_T                  PosCorr;      /*!< Position Correction */
} TSC_LinRotB_T;

/**@} end of group TSC_Linrot_Structures */

/** @defgroup TSC_Linrot_Variables Variables
  @{
*/

/* Position offset constant tables and corrections */
extern CONST TSC_tPosition_T TSC_POSOFF_3CH_LIN_M1[3][3];
extern CONST TSC_tPosition_T TSC_POSOFF_3CH_LIN_M2[3][3];
extern CONST TSC_tPosition_T TSC_POSOFF_3CH_LIN_H[3][3];
extern CONST TSC_tPosition_T TSC_POSOFF_3CH_ROT_M[3][3];

extern CONST TSC_tPosition_T TSC_POSOFF_4CH_LIN_M1[4][4];
extern CONST TSC_tPosition_T TSC_POSOFF_4CH_LIN_M2[4][4];
extern CONST TSC_tPosition_T TSC_POSOFF_4CH_LIN_H[4][4];
extern CONST TSC_tPosition_T TSC_POSOFF_4CH_ROT_M[4][4];

extern CONST TSC_tPosition_T TSC_POSOFF_5CH_LIN_M1[5][5];
extern CONST TSC_tPosition_T TSC_POSOFF_5CH_LIN_M2[5][5];
extern CONST TSC_tPosition_T TSC_POSOFF_5CH_LIN_H[5][5];
extern CONST TSC_tPosition_T TSC_POSOFF_5CH_ROT_M[5][5];
extern CONST TSC_tPosition_T TSC_POSOFF_5CH_ROT_D[5][5];

extern CONST TSC_tPosition_T TSC_POSOFF_6CH_LIN_M1[6][6];
extern CONST TSC_tPosition_T TSC_POSOFF_6CH_LIN_M2[6][6];
extern CONST TSC_tPosition_T TSC_POSOFF_6CH_LIN_H[6][6];
extern CONST TSC_tPosition_T TSC_POSOFF_6CH_ROT_M[6][6];

/**@} end of group TSC_Linrot_Variables */

/** @defgroup TSC_Linrot_Functions Functions
  @{
*/

/* "Object methods" functions */
void TSC_Linrot_Config(void);
void TSC_Linrot_Process(void);
TSC_STATUS_T TSC_Linrot_CalcPos(void);

/* Utility functions */
void TSC_Linrot_ConfigCalibrationState(TSC_tCounter_T delay);
void TSC_Linrot_ConfigOffState(void);
void TSC_Linrot_ConfigBurstOnlyState(void);
TSC_STATEID_T TSC_Linrot_ReadStateId(void);
TSC_STATEMASK_T TSC_Linrot_ReadStateMask(void);
TSC_tNum_T TSC_Linrot_ReadChangeFlag(void);

/* State machine functions */
void TSC_Linrot_ProcessCalibrationState(void);
void TSC_Linrot_ProcessDebCalibrationState(void);
void TSC_Linrot_ProcessReleaseState(void);
void TSC_Linrot_ProcessDebReleaseProxState(void);
void TSC_Linrot_ProcessDebReleaseDetectState(void);
void TSC_Linrot_ProcessDebReleaseTouchState(void);
void TSC_Linrot_ProcessProxState(void);
void TSC_Linrot_ProcessDebProxState(void);
void TSC_Linrot_ProcessDebProxDetectState(void);
void TSC_Linrot_ProcessDebProxTouchState(void);
void TSC_Linrot_ProcessDetectState(void);
void TSC_Linrot_ProcessDebDetectState(void);
void TSC_Linrot_ProcessTouchState(void);
void TSC_Linrot_ProcessDebTouchState(void);
void TSC_Linrot_ProcessDebErrorState(void);

/* Private functions */
void TSC_Linrot_ReadTimeForDTO(void);
void TSC_Linrot_Process_AllChannel_Status(TSC_OBJ_STATUS_T status);
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DataReady(void);
TSC_STATUS_T TSC_Linrot_Process_AllChannel_AcqStatus(TSC_ACQ_STATUS_T status);
TSC_STATUS_T TSC_Linrot_Process_OneChannel_AcqStatusError(void);
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DeltaBelowEquMinus(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd);
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DeltaAboveEqu(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd);
TSC_STATUS_T TSC_Linrot_Process_OneChannel_DeltaAbove(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd);
TSC_STATUS_T TSC_Linrot_Process_AllChannel_DeltaBelowEqu(TSC_tThreshold_T threshold, TSC_tIndex_T Cmd);
void TSC_Linrot_Process_AllChannel_ClearRef(void);
TSC_tDelta_T TSC_Linrot_NormDelta(TSC_Channel_Data_T* channel, TSC_tIndex_T index);

#ifdef __cplusplus
}
#endif

#endif /* __TSC_LINROT_H */

/**@} end of group TSC_Linrot_Functions */
/**@} end of group TSC_Linrot_Driver */
/**@} end of group TSC_Driver_Library */
