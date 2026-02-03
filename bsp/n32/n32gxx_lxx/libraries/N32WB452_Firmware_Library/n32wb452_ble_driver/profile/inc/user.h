/**
 ****************************************************************************************
 *
 * @file user.h
 *
 * @brief Header file - user defined.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef USER_H_
#define USER_H_


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_APP_USER)
#include <stdint.h>
#include <stdbool.h>
//#include "htp_common.h"
#include "prf_types.h"
#include "prf_utils.h"
#include "prf.h"
#include "gap.h"

/*
 * MACROS
 ****************************************************************************************
 */
#define USER_IS_FEATURE_SUPPORTED(feat, bit_mask) (((feat & bit_mask) == bit_mask))

#define USER_HANDLE(idx) (user_att_hdl_get(user_env, (idx)))

#define USER_IDX(hdl)    (user_att_idx_get(user_env, (hdl)))

/*
 * DEFINES
 ****************************************************************************************
 */
#define USER_DATA_LEN_MAX            (1024)//(64)

#define USER_READ_WRITE_ATT_NB            (3)
#define USER_DTAA_NOTIFY_ATT_NB           (3)
#define USER_DATA_WRITE_ATT_NB           (2)
#define USER_DATA_INTV_ATT_NB             (3)

#define USER_IND_NTF_CFG_MAX_LEN          (2)
/// Possible states of the HTPT task
enum user_state
{
    /// Idle state
    USER_IDLE,
    /// Busy state
    USER_BUSY,

    /// Number of defined states.
    USER_STATE_MAX
};
///Attributes database elements
/// 修改服务列表
enum user_att_db_list
{
    USER_IDX_SVC,

    USER_IDX_WRITE_NOTIFY_CHAR,
    USER_IDX_WRITE_NOTIFY_VAL,
    USER_IDX_WRITE_NOTIFY_CFG,

#ifdef BLE_OTA_WRITE_CHAR_EN
    USER_IDX_READ_NOTIFY_CHAR,
    USER_IDX_READ_NOTIFY_VAL,
    USER_IDX_WRITE_NOTIFY2_CFG,
#endif
    USER_IDX_NB,
};
/// ongoing operation information
struct user_op
{
     /// Operation
     uint8_t op;
     /// Cursor on connection
     uint8_t cursor;
     /// Handle of the attribute to indicate/notify
     uint16_t handle;
     /// Task that request the operation that should receive completed message response
     uint16_t dest_id;
     /// Packed notification/indication data size
     uint8_t length;
     /// used to know on which device interval update has been requested, and to prevent
     /// indication to be triggered on this connection index
     uint8_t conidx;
     /// Packed notification/indication data
     uint8_t data[__ARRAY_EMPTY];
};

//Health Thermometer Profile Thermometer Environment Variable
struct user_env_tag
{
    /// profile environment
    prf_env_t prf_env;
    /// On-going operation
    struct user_op * operation;
    /// Service Start Handle
    uint16_t shdl;
    /// Database configuration
    uint16_t features;
    uint8_t ntf_ind_cfg[USER_IDX_NB];
    ke_state_t state[1];

   // uint8_t data[ATT_VALUE_LEN_MAX/*__ARRAY_EMPTY*/];

    uint16_t receive_length;
    uint8_t *receive_data;
    bool  receive_flag;
    bool receive_header;
    uint16_t receive_current_length;
    uint16_t send_current_length;    //wait to check
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
 * @brief Compute the offset of the valid range descriptor.
 * The Measurement Interval characteristic has two optional descriptors. In the database,
 * the Client Characteristic Configuration descriptor will always be placed just after the
 * characteristic value. Thus, this function checks if the CCC descriptor has been added.
 * @return     0 if Measurement Interval Char. is not writable (no Valid Range descriptor)
 *             1 if Measurement Interval Char. doesn't support indications (no CCC descriptor)
 *             2 otherwise
 ****************************************************************************************
 */
uint8_t user_get_valid_rge_offset(uint16_t features);

/**
 ****************************************************************************************
 * @brief Retrieve HTS service profile interface
 *
 * @return HTS service profile interface
 ****************************************************************************************
 */
const struct prf_task_cbs* user_prf_itf_get(void);
//const struct prf_task_cbs* user1_prf_itf_get(void);
//const struct prf_task_cbs* user2_prf_itf_get(void);
uint16_t user_att_hdl_get(struct user_env_tag* htpt_env, uint8_t att_idx);

/**
 ****************************************************************************************
 * @brief Retrieve attribute index from attribute handle
 *
 * @param[in] htpt_env   Environment variable
 * @param[in] handle     Attribute Handle
 *
 * @return attribute Index
 ****************************************************************************************
 */
uint8_t user_att_idx_get(struct user_env_tag* htpt_env, uint16_t handle);

void user_exe_operation(void);

uint8_t user_update_ntf_ind_cfg(uint8_t conidx, uint8_t cfg, uint16_t valid_val,uint8_t idx,uint16_t value);

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler user_default_handler;
//extern const struct ke_state_handler user1_default_handler;
//extern const struct ke_state_handler user2_default_handler;

#endif //BLE_HT_THERMOM

/// @} HTPT

#endif // HTPT_H_

