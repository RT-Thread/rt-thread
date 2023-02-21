/*!
 * @file        tsc_types.h
 *
 * @brief       This file contains all general structures definition.
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
#ifndef __TSC_TYPES_H
#define __TSC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Types_Driver TSC Types Driver
  @{
*/

/** @defgroup TSC_Types_Macros Macros
  @{
*/

#define TSC_ACQ_STATUS_ERROR_MASK (0x02) /*!< Associated to TSC_ACQ_STATUS_T */

#define TSC_OBJ_STATUS_ACQ_MASK   (0x01) /*!< Associated to TSC_OBJ_STATUS_T */
#define TSC_OBJ_STATUS_BURST_MASK (0x02) /*!< Associated to TSC_OBJ_STATUS_T */


#define TSC_STATE_ERROR_BIT_MASK    (0x80) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_OFF_BIT_MASK      (0x40) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_DEBOUNCE_BIT_MASK (0x20) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_CALIB_BIT_MASK    (0x10) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_TOUCH_BIT_MASK    (0x08) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_DETECT_BIT_MASK   (0x04) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_PROX_BIT_MASK     (0x02) /*!< Associated to TSC_STATEMASK_T */
#define TSC_STATE_RELEASE_BIT_MASK  (0x01) /*!< Associated to TSC_STATEMASK_T */

/**@} end of group TSC_Types_Macros */

/** @defgroup TSC_Types_Enumerations Enumerations
  @{
*/

/**
 * @brief    Generic Boolean status
 */
typedef enum
{
    TSC_FALSE = 0, /*!< A False value */
    TSC_TRUE  = 1  /*!< A True value */
} TSC_BOOL_T;

/**
 * @brief    Generic status returned by functions
 */
typedef enum
{
    TSC_STATUS_OK      = 0, /*!< The function has been executed correctly */
    TSC_STATUS_BUSY    = 1, /*!< The function is in a Busy state */
    TSC_STATUS_ERROR   = 2  /*!< The function has been executed not correctly */
} TSC_STATUS_T;

/**
 * @brief    DataReady status : 1 bit
 *           Used by acquisition to indicate if a new measurement is ready or not.
 */
typedef enum
{
    TSC_DATA_NOT_READY = 0, /*!< No new measurement or measurement treated */
    TSC_DATA_READY     = 1  /*!< A new measurement is ready */
} TSC_DATA_T;

/**
 * @brief    State change status
 */
typedef enum
{
    TSC_STATE_NOT_CHANGED = 0, /*!< The object has the same state */
    TSC_STATE_CHANGED     = 1  /*!< The object has changed of state */
} TSC_STATE_T;


/**
 * @brief    Acquisition status
 */
typedef enum
{
    TSC_ACQ_STATUS_OK        = 0,                                   /*!< The acquisition is correct */
    TSC_ACQ_STATUS_NOISE     = 1,                                   /*!< Noise detected during the acquisition */
    TSC_ACQ_STATUS_ERROR_MIN = TSC_ACQ_STATUS_ERROR_MASK,           /*!< The measure is below the minimum threshold */
    TSC_ACQ_STATUS_ERROR_MAX = (TSC_ACQ_STATUS_ERROR_MASK | 0x01)   /*!< The measure is above the maximum threshold */
} TSC_ACQ_STATUS_T;

/**
 * @brief    Block status
 */
typedef enum
{
    TSC_BLOCK_STATUS_DISABLED = 0, /*!< The block is disabled */
    TSC_BLOCK_STATUS_ENABLED  = 1  /*!< The block is enabled */
} TSC_BLOCK_STATUS_T;

/**
 * @brief    Zone status
 */
typedef enum
{
    TSC_ZONE_STATUS_DISABLED = 0, /*!< The zone is disabled */
    TSC_ZONE_STATUS_ENABLED  = 1  /*!< The zone is enabled */
} TSC_ZONE_STATUS_T;

/**
 * @brief    Object status
 */
typedef enum
{
    TSC_OBJ_STATUS_OFF        = 0,                                                    /*!< No burst and no acquisition */
    TSC_OBJ_STATUS_BURST_ONLY = TSC_OBJ_STATUS_BURST_MASK,                            /*!< Burst only */
    TSC_OBJ_STATUS_ON         = (TSC_OBJ_STATUS_BURST_MASK | TSC_OBJ_STATUS_ACQ_MASK) /*!< Burst and acquisition */
} TSC_OBJ_STATUS_T;

/**
 * @brief    Object state masks
 */
typedef enum
{
    /* Calibration states */
    TSC_STATEMASK_CALIB              = TSC_STATE_CALIB_BIT_MASK,                                                               /*!< 0x10 */
    TSC_STATEMASK_DEB_CALIB          = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_CALIB_BIT_MASK),                               /*!< 0x30 */
    /* Release states */
    TSC_STATEMASK_RELEASE            = TSC_STATE_RELEASE_BIT_MASK,                                                             /*!< 0x01 */
    TSC_STATEMASK_DEB_RELEASE_PROX   = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_RELEASE_BIT_MASK | TSC_STATE_PROX_BIT_MASK),   /*!< 0x23 */
    TSC_STATEMASK_DEB_RELEASE_DETECT = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_RELEASE_BIT_MASK | TSC_STATE_DETECT_BIT_MASK), /*!< 0x25 */
    TSC_STATEMASK_DEB_RELEASE_TOUCH  = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_RELEASE_BIT_MASK | TSC_STATE_TOUCH_BIT_MASK),  /*!< 0x29 */
    /* Proximity states */
    TSC_STATEMASK_PROX               = TSC_STATE_PROX_BIT_MASK,                                                                /*!< 0x02 */
    TSC_STATEMASK_DEB_PROX           = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_PROX_BIT_MASK),                                /*!< 0x22 */
    TSC_STATEMASK_DEB_PROX_DETECT    = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_PROX_BIT_MASK | TSC_STATE_DETECT_BIT_MASK),    /*!< 0x26 */
    TSC_STATEMASK_DEB_PROX_TOUCH     = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_PROX_BIT_MASK | TSC_STATE_TOUCH_BIT_MASK),     /*!< 0x2A */
    /* Detect states */
    TSC_STATEMASK_DETECT             = TSC_STATE_DETECT_BIT_MASK,                                                              /*!< 0x04 */
    TSC_STATEMASK_DEB_DETECT         = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_DETECT_BIT_MASK),                              /*!< 0x24 */
    /* Touch state */
    TSC_STATEMASK_TOUCH              = TSC_STATE_TOUCH_BIT_MASK,                                                               /*!< 0x08 */
    /* Error states */
    TSC_STATEMASK_ERROR              = TSC_STATE_ERROR_BIT_MASK,                                                               /*!< 0x80 */
    TSC_STATEMASK_DEB_ERROR_CALIB    = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_ERROR_BIT_MASK | TSC_STATE_CALIB_BIT_MASK),    /*!< 0xB0 */
    TSC_STATEMASK_DEB_ERROR_RELEASE  = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_ERROR_BIT_MASK | TSC_STATE_RELEASE_BIT_MASK),  /*!< 0xA1 */
    TSC_STATEMASK_DEB_ERROR_PROX     = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_ERROR_BIT_MASK | TSC_STATE_PROX_BIT_MASK),     /*!< 0xA2 */
    TSC_STATEMASK_DEB_ERROR_DETECT   = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_ERROR_BIT_MASK | TSC_STATE_DETECT_BIT_MASK),   /*!< 0xA4 */
    TSC_STATEMASK_DEB_ERROR_TOUCH    = (TSC_STATE_DEBOUNCE_BIT_MASK | TSC_STATE_ERROR_BIT_MASK | TSC_STATE_TOUCH_BIT_MASK),    /*!< 0xA8 */
    /* OFF state */
    TSC_STATEMASK_OFF                = TSC_STATE_OFF_BIT_MASK,                                                                 /*!< 0x40 */
    /* Other states not associated to a state id */
    TSC_STATEMASK_ACTIVE             = (TSC_STATE_PROX_BIT_MASK | TSC_STATE_DETECT_BIT_MASK | TSC_STATE_TOUCH_BIT_MASK | TSC_STATE_CALIB_BIT_MASK | TSC_STATE_DEBOUNCE_BIT_MASK), /*!< 0x3E */
    TSC_STATEMASK_UNKNOWN            = 0                                                                                       /*!< 0x00 */
} TSC_STATEMASK_T;

/**
 * @brief    Object state identifiers
 */
typedef enum
{
    /* Calibration states */
    TSC_STATEID_CALIB              = 0,  /*!<  0 - Object is in Calibration */
    TSC_STATEID_DEB_CALIB          = 1,  /*!<  1 - Object is in Debounce Calibration */
    /* Release states */
    TSC_STATEID_RELEASE            = 2,  /*!<  2 - Object is released */
    TSC_STATEID_DEB_RELEASE_PROX   = 3,  /*!<  3 - Object is in Debounce Release from Proximity state */
    TSC_STATEID_DEB_RELEASE_DETECT = 4,  /*!<  4 - Object is in Debounce Release from Detect state */
    TSC_STATEID_DEB_RELEASE_TOUCH  = 5,  /*!<  5 - Object is in Debounce Release from Touch state */
    /* Proximity states */
    TSC_STATEID_PROX               = 6,  /*!<  6 - Object is in Proximity */
    TSC_STATEID_DEB_PROX           = 7,  /*!<  7 - Object is in Debounce Proximity from Release state */
    TSC_STATEID_DEB_PROX_DETECT    = 8,  /*!<  8 - Object is in Debounce Proximity from Detect state */
    TSC_STATEID_DEB_PROX_TOUCH     = 9,  /*!<  9 - Object is in Debounce Proximity from Detect state */
    /* Detect states */
    TSC_STATEID_DETECT             = 10, /*!< 10 - Object is in Detect */
    TSC_STATEID_DEB_DETECT         = 11, /*!< 11 - Object is in Debounce Detect */
    /* Touch state */
    TSC_STATEID_TOUCH              = 12, /*!< 12 - Object is in Touch */
    /* Error states */
    TSC_STATEID_ERROR              = 13, /*!< 13 - Object is in Error */
    TSC_STATEID_DEB_ERROR_CALIB    = 14, /*!< 14 - Object is in Debounce Error from Calibration */
    TSC_STATEID_DEB_ERROR_RELEASE  = 15, /*!< 15 - Object is in Debounce Error from Release */
    TSC_STATEID_DEB_ERROR_PROX     = 16, /*!< 16 - Object is in Debounce Error from Proximity */
    TSC_STATEID_DEB_ERROR_DETECT   = 17, /*!< 17 - Object is in Debounce Error from Detect */
    TSC_STATEID_DEB_ERROR_TOUCH    = 18, /*!< 18 - Object is in Debounce Error from Touch */
    /* Other states */
    TSC_STATEID_OFF                = 19  /*!< 19 - Object is OFF (no burst, no acquisition) */
} TSC_STATEID_T;

/**@} end of group TSC_Types_Enumerations */

/** @defgroup TSC_Types_Structures Structures
  @{
*/

/**
 * @brief    Object state
 */
typedef struct
{
    TSC_STATEMASK_T StateMask; /*!< Current state mask */
    void(* StateFunc)(void);   /*!< Function executed in the state */
} TSC_State_T;

/**
 * @brief    Touchkey methods
 */
typedef struct
{
    void(* Config)(void);  /*!< Used to configure the TouchKey sensor */
    void(* Process)(void); /*!< Used to execute the TouchKey sensor state machine */
} TSC_TouchKeyMethods_T;

/**
 * @brief    Linear/Rotary methods
 */
typedef struct
{
    void(* Config)(void);               /*!< Used to configure the Linear/Rotary sensor */
    void(* Process)(void);              /*!< Used to execute the Linear/Rotary sensor state machine */
    TSC_STATUS_T(* CalcPosition)(void); /*!< Used to calculate the Linear/Rotary sensor position */
} TSC_LinRotMethods_T;

/**@} end of group TSC_Types_Structures */

/** @defgroup TSC_Types_Variables Variables
  @{
*/

/**@} end of group TSC_Types_Variables */

/** @defgroup TSC_Types_Functions Functions
  @{
*/

/**@} end of group TSC_Types_Functions */

#ifdef __cplusplus
}
#endif

#endif /* __TSC_TYPES_H */

/**@} end of group TSC_Types_Driver */
/**@} end of group TSC_Driver_Library */
