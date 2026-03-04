/**
 ****************************************************************************************
 *
 * @file bass.h
 *
 * @brief Header file - Battery Service Server Role
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef _BASS_H_
#define _BASS_H_

/**
 ****************************************************************************************
 * @addtogroup BAPS Battery 'Profile' Server
 * @ingroup BAP
 * @brief Battery 'Profile' Server
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_BATT_SERVER)

#include "bass_task.h"
#include "prf_types.h"
#include "prf.h"

/*
 * DEFINES
 ****************************************************************************************
 */

///Maximum number of Battery Server task instances
#define BASS_IDX_MAX     0x01

#define BAS_CFG_FLAG_MANDATORY_MASK       (0x07)
#define BAS_CFG_FLAG_NTF_SUP_MASK         (0x08)
#define BAS_CFG_FLAG_MTP_BAS_MASK         (0x10)

#define BASS_FLAG_NTF_CFG_BIT             (0x02)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/// Possible states of the BASS task
enum bass_state
{
    /// Idle state
    BASS_IDLE,
    /// busy state
    BASS_BUSY,
    /// Number of defined states.
    BASS_STATE_MAX
};

/// Battery Service Attributes Indexes
enum
{
    BAS_IDX_SVC,

    BAS_IDX_BATT_LVL_CHAR,
    BAS_IDX_BATT_LVL_VAL,
    BAS_IDX_BATT_LVL_NTF_CFG,
    BAS_IDX_BATT_LVL_PRES_FMT,

    BAS_IDX_NB,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Battery 'Profile' Server environment variable
struct bass_env_tag
{
    /// profile environment
    prf_env_t prf_env;
    /// Battery Level Characteristic Presentation Format - Should not change during connection
    struct prf_char_pres_fmt batt_level_pres_format[BASS_NB_BAS_INSTANCES_MAX];
    /// On-going operation
    struct ke_msg * operation;
    /// BAS Services Start Handle
    uint16_t start_hdl;
    /// Level of the battery
    uint8_t batt_lvl[BASS_NB_BAS_INSTANCES_MAX];
    /// BASS task state
    ke_state_t state[BASS_IDX_MAX];
    /// Notification configuration of peer devices.
    uint8_t ntf_cfg[BLE_CONNECTION_MAX];
    /// Database features
    uint8_t features;
    /// Number of BAS
    uint8_t svc_nb;
    /// Cursor on connection used to notify peer devices when battery level changes
    uint8_t cursor;
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Retrieve BAS service profile interface
 *
 * @return BAS service profile interface
 ****************************************************************************************
 */
const struct prf_task_cbs* bass_prf_itf_get(void);

/**
 ****************************************************************************************
 * @brief Retrieve Attribute handle from service and attribute index
 *
 * @param[in] svc_idx BAS Service index
 * @param[in] att_idx Attribute index
 *
 * @return BAS attribute handle or INVALID HANDLE if nothing found
 ****************************************************************************************
 */
uint16_t bass_get_att_handle(uint8_t svc_idx, uint8_t att_idx);

/**
 ****************************************************************************************
 * @brief Retrieve Service and attribute index form attribute handle
 *
 * @param[out] handle  Attribute handle
 * @param[out] svc_idx BAS Service index
 * @param[out] att_idx Attribute index
 *
 * @return Success if attribute and service index found, else Application error
 ****************************************************************************************
 */
uint8_t bass_get_att_idx(uint16_t handle, uint8_t *svc_idx, uint8_t *att_idx);

/**
 ****************************************************************************************
 * @brief  This function fully manage notification of battery level to peer(s) device(s)
 *         according to on-going operation requested by application:
 *            - Modification of Battery Level
 *            - Indicate to a known device that battery level has change
 ****************************************************************************************
 */
void bass_exe_operation(void);

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */

extern const struct ke_state_handler bass_default_handler;


#endif /* #if (BLE_BATT_SERVER) */

/// @} BASS

#endif /* _BASS_H_ */
