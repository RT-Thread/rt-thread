/**
 ****************************************************************************************
 *
 * @file bass_task.h
 *
 * @brief Header file - Battery Service Server Role Task.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */


#ifndef _BASS_TASK_H_
#define _BASS_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup BAPSTASK Task
 * @ingroup BAPS
 * @brief Battery 'Profile' Task.
 *
 * The BAPS_TASK is responsible for handling the messages coming in and out of the
 * @ref BAPS block of the BLE Host.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "prf_types.h"
#include "rwip_task.h" // Task definitions

/*
 * DEFINES
 ****************************************************************************************
 */

#define BAS_BATTERY_LVL_MAX               (100)


///Maximal number of BAS that can be added in the DB
#define BASS_NB_BAS_INSTANCES_MAX         (2)


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/// Messages for Battery Server
enum bass_msg_id
{
    /// Start the Battery Server - at connection used to restore bond data
    BASS_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_BASS),
    /// Confirmation of the Battery Server start
    BASS_ENABLE_RSP,
    /// Battery Level Value Update Request
    BASS_BATT_LEVEL_UPD_REQ,
    /// Inform APP if Battery Level value has been notified or not
    BASS_BATT_LEVEL_UPD_RSP,
    /// Inform APP that Battery Level Notification Configuration has been changed - use to update bond data
    BASS_BATT_LEVEL_NTF_CFG_IND,
};

/// Features Flag Masks
enum bass_features
{
    /// Battery Level Characteristic doesn't support notifications
    BAS_BATT_LVL_NTF_NOT_SUP,
    /// Battery Level Characteristic support notifications
    BAS_BATT_LVL_NTF_SUP,
};


/*
 * APIs Structures
 ****************************************************************************************
 */

/// Parameters for the database creation
struct bass_db_cfg
{
    /// Number of BAS to add
    uint8_t bas_nb;
    /// Features of each BAS instance
    uint8_t features[BASS_NB_BAS_INSTANCES_MAX];
    /// Battery Level Characteristic Presentation Format - Should not change during connection
    struct prf_char_pres_fmt batt_level_pres_format[BASS_NB_BAS_INSTANCES_MAX];
};

/// Parameters of the @ref BASS_ENABLE_REQ message
struct bass_enable_req
{
    /// connection index
    uint8_t  conidx;
    /// Notification Configuration
    uint8_t  ntf_cfg;
    /// Old Battery Level used to decide if notification should be triggered
    uint8_t  old_batt_lvl[BASS_NB_BAS_INSTANCES_MAX];
};

/// Parameters of the @ref BASS_ENABLE_RSP message
struct bass_enable_rsp
{
    /// connection index
    uint8_t conidx;
    ///status
    uint8_t status;
};

///Parameters of the @ref BASS_BATT_LEVEL_UPD_REQ message
struct bass_batt_level_upd_req
{
    /// BAS instance
    uint8_t bas_instance;
    /// Battery Level
    uint8_t batt_level;
};

///Parameters of the @ref BAPS_BATT_LEVEL_UPD_RSP message
struct bass_batt_level_upd_rsp
{
    ///status
    uint8_t status;
};

///Parameters of the @ref BASS_BATT_LEVEL_NTF_CFG_IND message
struct bass_batt_level_ntf_cfg_ind
{
    /// connection index
    uint8_t  conidx;
    ///Notification Configuration
    uint8_t  ntf_cfg;
};

/// @} BASSTASK

#endif /* _BASS_TASK_H_ */
