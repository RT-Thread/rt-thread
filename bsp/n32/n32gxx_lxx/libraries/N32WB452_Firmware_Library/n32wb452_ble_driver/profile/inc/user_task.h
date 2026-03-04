#include "rwip_task.h" // Task definitions
#include "stdbool.h"
#include "ble_arch.h"
struct user_db_cfg
{
    ///  Feature (@see enum user_features)
    uint8_t features;

    uint16_t rxlen;
    uint16_t txlen;
    uint8_t *prx;
    uint8_t *ptx;
    /// Measurement interval timer enable
    bool timer_enable;

};

/// Parameters of the @ref HTPT_ENABLE_REQ message
struct user_enable_req
{
    /// Connection index
    uint8_t conidx;
    /// Notification configuration (Bond Data to restore: @see enum htpt_ntf_ind_cfg)
    uint8_t  ntf_ind_cfg;


};
struct user_notify_req
{
    uint8_t  att_idx;
    uint16_t send_param_length;
    uint8_t send_param_payload[__ARRAY_EMPTY];
};
/// Parameters of the @ref HTPT_ENABLE_RSP message
struct user_enable_rsp
{
    /// Connection index
    uint8_t conidx;
    /// Status of enable request
    uint8_t status;
};
/// Parameters of the @ref HTPT_TEMP_SEND_RSP message
struct user_notify_rsp
{
    /// Status
    uint8_t status;
};
struct user_write_rsp
{
    /// Status
    uint16_t len;
    uint8_t status;
};
struct user_read_rsp
{
    /// Status
    uint8_t status;
};
struct user_upd_rsp
{
    /// status
    uint8_t status;
};
/// Parameters of the @ref HTPT_CFG_INDNTF_IND message
struct user_cfg_indntf_ind
{
    /// connection index
    uint8_t  conidx;
    /// Notification Configuration (@see enum htpt_ntf_ind_cfg)
    uint8_t  ntf_ind_cfg;
};
/// Messages for Health Thermometer Profile Thermometer
enum user_msg_id
{
    /// Start the Health Thermometer Profile Thermometer profile - at connection
    USER_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_USER),
    /// Enable confirmation
    USER_ENABLE_RSP,

    /// Send DATA value
    USER_DATA_WRITE_REQ,
    /// Send DATA response
    USER_DATA_WRITE_RSP,

     /// RECEIVE DATA value
    USER_DATA_READ_REQ,
    /// RECEIVE DATA response
    USER_DATA_READ_RSP,

        /// Indicate Measurement Interval
    USER_NOTIFY_REQ,
    /// Send Measurement Interval response
    USER_NOTIFY_RSP,

    /// Indicate Measurement Interval
    USER_INTV_REQ,
    /// Send Measurement Interval response
    USER_INTV_RSP,
      /// Inform APP that Indication Configuration has been changed - use to update bond data
    USER_CFG_INDNTF_IND,
};
/// Database Feature Configuration Flags
enum user_features
{
    /// Indicate if READ_WRITE Char. is supported
    USER_READ_WRITE_CHAR_SUP        = 0x01,
    /// Indicate if DATA_NOTIFY Char. is supported
    USER_DATA_NOTIFY_CHAR_SUP      = 0x02,
    /// Indicate if DATA_WRITE Char. is supported
    USER_DATA_WRITE_CHAR_SUP        = 0x04,
    /// Indicate if indication Char. supports indications
    USER_DATA_IND_CHAR_SUP         = 0x08,
    /// All Features supported
    USER_ALL_FEAT_SUP              = 0xF,
};
enum user_ntf_ind_cfg
{
    USER_DATA_NTF_IND_DISABLE = 0,
    ///  数据发送方式为notify
    USER_DATA_NTF    = (1 << 0),
    ///   数据发送方式为indication
    USER_DATA_IND    = (1 << 1),
};





