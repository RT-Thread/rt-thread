/**
 ****************************************************************************************
 *
 * @file gattc_task.h
 *
 * @brief Header file - GATTCTASK.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef GATTC_TASK_H_
#define GATTC_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup GATTCTASK Task
 * @ingroup GATTC
 * @brief Handles ALL messages to/from GATT Controller block.
 *
 * The GATTCTASK is responsible for managing the messages coming from
 * the attribute layer and host-level layers for dedicated connection.
 * The task includes services and characteristic discovery, configuration exchanges
 * and attribute value access operations (reading, writing, notification and indication).
 *
 * Messages may originate from @ref ATTC "ATTC", @ref ATTS "ATTS", @ref GAP "GAP"
 * and Application.
 *
 * @{
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "att.h"
#include "rwip_task.h" // Task definitions
//#include "compiler.h"
#include "ble_arch.h"
#include <stdbool.h>
/*
 * DEFINES
 ****************************************************************************************
 */

/// GATT Task messages
enum gattc_msg_id
{
    /* Default event */
    /// Command Complete event
    GATTC_CMP_EVT = TASK_FIRST_MSG(TASK_ID_GATTC),

    /* ATTRIBUTE CLIENT */
    /// Server configuration request
    GATTC_EXC_MTU_CMD,
    /// Indicate that the ATT MTU has been updated (negotiated)
    GATTC_MTU_CHANGED_IND,

    /*Discover All Services */
    /*Discover Services by Service UUID*/
    /*Find Included Services*/
    /*Discover Characteristics by UUID*/
    /*Discover All Characteristics of a Service*/
    /*Discover All Characteristic Descriptors*/
    /// Discovery command
    GATTC_DISC_CMD,
    /* GATT -> HL: Events to Upper layer */
    /*Discover All Services*/
    /// Discovery services indication
    GATTC_DISC_SVC_IND,
    /*Find Included Services*/
    /// Discover included services indication
    GATTC_DISC_SVC_INCL_IND,
    /*Discover All Characteristics of a Service*/
    /// Discover characteristic indication
    GATTC_DISC_CHAR_IND,
    /*Discover All Characteristic Descriptors*/
    /// Discovery characteristic descriptor indication
    GATTC_DISC_CHAR_DESC_IND,

    /*Read Value*/
    /*Read Using UUID*/
    /*Read Long Value*/
    /*Read Multiple Values*/
    /// Read command
    GATTC_READ_CMD,
    /// Read response
    GATTC_READ_IND,

    /*Write without response*/
    /*Write without response with Authentication*/
    /*Write Characteristic Value*/
    /*Signed Write Characteristic Value*/
    /*Write Long Characteristic Value*/
    /*Characteristic Value Reliable Write*/
    /*Write Characteristic Descriptors*/
    /*Write Long Characteristic Descriptors*/
    /*Characteristic Value Reliable Write*/
    /// Write command request
    GATTC_WRITE_CMD,

    /* Cancel / Execute pending write operations */
    /// Execute write characteristic request
    GATTC_EXECUTE_WRITE_CMD,

    /* Reception of an indication or notification from peer device. */
    /// peer device triggers an event (notification)
    GATTC_EVENT_IND,
    /// peer device triggers an event that requires a confirmation (indication)
    GATTC_EVENT_REQ_IND,
    /// Confirm reception of event (trigger a confirmation message)
    GATTC_EVENT_CFM,

    /// Registration to peer device events (Indication/Notification).
    GATTC_REG_TO_PEER_EVT_CMD,

    /* -------------------------- ATTRIBUTE SERVER ------------------------------- */
    /*Notify Characteristic*/
    /*Indicate Characteristic*/
    /// send an event to peer device
    GATTC_SEND_EVT_CMD,

    /* Service Changed Characteristic Indication */
    /**
     * Send a Service Changed indication to a device
     * (message structure is struct gattm_svc_changed_ind_req)
     */
    GATTC_SEND_SVC_CHANGED_CMD,
    /**
     * Inform the application when sending of Service Changed indications has been
     * enabled or disabled
     */
    GATTC_SVC_CHANGED_CFG_IND,

    /* Indicate that read operation is requested. */
    /// Read command indicated to upper layers.
    GATTC_READ_REQ_IND,
    /// REad command confirmation from upper layers.
    GATTC_READ_CFM,

    /* Indicate that write operation is requested. */
    /// Write command indicated to upper layers.
    GATTC_WRITE_REQ_IND,
    /// Write command confirmation from upper layers.
    GATTC_WRITE_CFM,

    /* Indicate that write operation is requested. */
    /// Request Attribute info to upper layer - could be trigger during prepare write
    GATTC_ATT_INFO_REQ_IND,
    /// Attribute info from upper layer confirmation
    GATTC_ATT_INFO_CFM,

    /* ----------------------- SERVICE DISCOVERY PROCEDURE  --------------------------- */
    /// Service Discovery command
    GATTC_SDP_SVC_DISC_CMD,
    /// Service Discovery indicate that a service has been found.
    GATTC_SDP_SVC_IND,

    /* -------------------------- TRANSACTION ERROR EVENT ----------------------------- */
    /// Transaction Timeout Error Event no more transaction will be accepted
    GATTC_TRANSACTION_TO_ERROR_IND,

    /* ------------------------------- Internal API ----------------------------------- */
    /// Client Response timeout indication
    GATTC_CLIENT_RTX_IND,
    /// Server indication confirmation timeout indication
    GATTC_SERVER_RTX_IND,
};


/// request operation type - application interface
enum gattc_operation
{
    /*              Attribute Client Flags              */
    /* No Operation (if nothing has been requested)     */
    /* ************************************************ */
    /// No operation
    GATTC_NO_OP                                    = 0x00,

    /* Operation flags for MTU Exchange                 */
    /* ************************************************ */
    /// Perform MTU exchange
    GATTC_MTU_EXCH,

    /*      Operation flags for discovery operation     */
    /* ************************************************ */
    /// Discover all services
    GATTC_DISC_ALL_SVC,
    /// Discover services by UUID
    GATTC_DISC_BY_UUID_SVC,
    /// Discover included services
    GATTC_DISC_INCLUDED_SVC,
    /// Discover all characteristics
    GATTC_DISC_ALL_CHAR,
    /// Discover characteristic by UUID
    GATTC_DISC_BY_UUID_CHAR,
    /// Discover characteristic descriptor
    GATTC_DISC_DESC_CHAR,

    /* Operation flags for reading attributes           */
    /* ************************************************ */
    /// Read attribute
    GATTC_READ,
    /// Read long attribute
    GATTC_READ_LONG,
    /// Read attribute by UUID
    GATTC_READ_BY_UUID,
    /// Read multiple attribute
    GATTC_READ_MULTIPLE,

    /* Operation flags for writing/modifying attributes */
    /* ************************************************ */
    /// Write attribute
    GATTC_WRITE,
    /// Write no response
    GATTC_WRITE_NO_RESPONSE,
    /// Write signed
    GATTC_WRITE_SIGNED,
    /// Execute write
    GATTC_EXEC_WRITE,

    /* Operation flags for registering to peer device   */
    /* events                                           */
    /* ************************************************ */
    /// Register to peer device events
    GATTC_REGISTER,
    /// Unregister from peer device events
    GATTC_UNREGISTER,

    /* Operation flags for sending events to peer device*/
    /* ************************************************ */
    /// Send an attribute notification
    GATTC_NOTIFY,
    /// Send an attribute indication
    GATTC_INDICATE,
    /// Send a service changed indication
    GATTC_SVC_CHANGED,

    /* Service Discovery Procedure                      */
    /* ************************************************ */
    /// Search specific service
    GATTC_SDP_DISC_SVC,
    /// Search for all services
    GATTC_SDP_DISC_SVC_ALL,
    /// Cancel Service Discovery Procedure
    GATTC_SDP_DISC_CANCEL,
};

/// Service Discovery Attribute type
enum gattc_sdp_att_type
{
    /// No Attribute Information
    GATTC_SDP_NONE,
    /// Included Service Information
    GATTC_SDP_INC_SVC,
    /// Characteristic Declaration
    GATTC_SDP_ATT_CHAR,
    /// Attribute Value
    GATTC_SDP_ATT_VAL,
    /// Attribute Descriptor
    GATTC_SDP_ATT_DESC,
};

/// Command complete event data structure
struct gattc_op_cmd
{
    /// GATT request type
    uint8_t operation;
    /// operation sequence number
    uint16_t seq_num;
};

/// Command complete event data structure
struct gattc_cmp_evt
{
    /// GATT request type
    uint8_t operation;
    /// Status of the request
    uint8_t status;
    /// operation sequence number - provided when operation is started
    uint16_t seq_num;
};


/// Service Discovery Command Structure
struct gattc_exc_mtu_cmd
{
    /// GATT request type
    uint8_t operation;
    /// operation sequence number
    uint16_t seq_num;
};

/// Indicate that the ATT MTU has been updated (negotiated)
struct gattc_mtu_changed_ind
{
    /// Exchanged MTU value
    uint16_t mtu;
    /// operation sequence number
    uint16_t seq_num;
};

/// Service Discovery Command Structure
struct gattc_disc_cmd
{
    /// GATT request type
    uint8_t  operation;
    /// UUID length
    uint8_t  uuid_len;
    /// operation sequence number
    uint16_t seq_num;
    /// start handle range
    uint16_t start_hdl;
    /// start handle range
    uint16_t end_hdl;
    /// UUID
    uint8_t  uuid[__ARRAY_EMPTY];
};


/// Discover Service indication Structure
struct gattc_disc_svc_ind
{
    /// start handle
    uint16_t start_hdl;
    /// end handle
    uint16_t end_hdl;
    /// UUID length
    uint8_t  uuid_len;
    /// service UUID
    uint8_t  uuid[__ARRAY_EMPTY];
};

/// Discover Service indication Structure
struct gattc_disc_svc_incl_ind
{
    /// element handle
    uint16_t attr_hdl;
    /// start handle
    uint16_t start_hdl;
    /// end handle
    uint16_t end_hdl;
    /// UUID length
    uint8_t uuid_len;
    /// included service UUID
    uint8_t uuid[__ARRAY_EMPTY];
};

/// Discovery All Characteristic indication Structure
struct gattc_disc_char_ind
{
    /// database element handle
    uint16_t attr_hdl;
    /// pointer attribute handle to UUID
    uint16_t pointer_hdl;
    /// properties
    uint8_t prop;
    /// UUID length
    uint8_t uuid_len;
    /// characteristic UUID
    uint8_t uuid[__ARRAY_EMPTY];
};

/// Discovery Characteristic Descriptor indication Structure
struct gattc_disc_char_desc_ind
{
    /// database element handle
    uint16_t attr_hdl;
    /// UUID length
    uint8_t uuid_len;
    /// Descriptor UUID
    uint8_t uuid[__ARRAY_EMPTY];
};


/// Simple Read (GATTC_READ or GATTC_READ_LONG)
struct gattc_read_simple
{
    /// attribute handle
    uint16_t handle;
    /// start offset in data payload
    uint16_t offset;
    /// Length of data to read (0 = read all)
    uint16_t length;
};

/// Read by UUID: search UUID and read it's characteristic value (GATTC_READ_BY_UUID)
/// Note: it doesn't perform an automatic read long.
struct gattc_read_by_uuid
{
    /// Start handle
    uint16_t start_hdl;
    /// End handle
    uint16_t end_hdl;
    /// Size of UUID
    uint8_t uuid_len;
    /// UUID value
    uint8_t uuid[__ARRAY_EMPTY];
};

/// Read Multiple short characteristic (GATTC_READ_MULTIPLE)
struct gattc_read_multiple
{
    /// attribute handle
    uint16_t handle;
    /// Known Handle length (shall be != 0)
    uint16_t len;
};

/// Read command (Simple, Long, Multiple, or by UUID)
struct gattc_read_cmd
{
    /// request type
    uint8_t operation;
    /// number of read (only used for multiple read)
    uint8_t nb;
    /// operation sequence number
    uint16_t seq_num;

    /// request union according to read type
    union gattc_read_req
    {
        /// Simple Read (GATTC_READ or GATTC_READ_LONG)
        struct gattc_read_simple simple;
        /// Read by UUID (GATTC_READ_BY_UUID)
        struct gattc_read_by_uuid by_uuid;
        /// Read Multiple short characteristic (GATTC_READ_MULTIPLE)
        struct gattc_read_multiple multiple[1];
    } req;
};

/// Attribute value read indication
struct gattc_read_ind
{
    /// Attribute handle
    uint16_t handle;
    /// Read offset
    uint16_t offset;
    /// Read length
    uint16_t length;
    /// Handle value
    uint8_t value[__ARRAY_EMPTY];
};

/// Write peer attribute value command
struct gattc_write_cmd
{
    /// Request type
    uint8_t operation;
    /// Perform automatic execution
    /// (if false, an ATT Prepare Write will be used this shall be use for reliable write)
    bool auto_execute;
    /// operation sequence number
    uint16_t seq_num;
    /// Attribute handle
    uint16_t handle;
    /// Write offset
    uint16_t offset;
    /// Write length
    uint16_t length;
    /// Internal write cursor shall be initialized to 0
    uint16_t cursor;
    /// Value to write
    uint8_t value[__ARRAY_EMPTY];
};

/// Write peer attribute value command
struct gattc_execute_write_cmd
{
    /// Request type
    uint8_t operation;

    /// [True = perform/False cancel] pending write operations
    bool execute;
    /// operation sequence number
    uint16_t seq_num;
};
/// peer device triggers an event (notification)
struct gattc_event_ind
{
    /// Event Type
    uint8_t type;
    /// Data length
    uint16_t length;
    /// Attribute handle
    uint16_t handle;
    /// Event Value
    uint8_t value[__ARRAY_EMPTY];
};

/// peer device triggers an event that requires a confirmation (indication)
struct gattc_event_req_ind
{
    /// Event Type
    uint8_t type;
    /// Data length
    uint16_t length;
    /// Attribute handle
    uint16_t handle;
    /// Event Value
    uint8_t value[__ARRAY_EMPTY];
};

/// Confirm reception of event (trigger a confirmation message)
struct gattc_event_cfm
{
    /// Attribute handle
    uint16_t handle;
};

/// Register to peer device events command
struct gattc_reg_to_peer_evt_cmd
{
    /// Request type
    uint8_t operation;
    /// operation sequence number
    uint16_t seq_num;
    /// attribute start handle
    uint16_t start_hdl;
    /// attribute end handle
    uint16_t end_hdl;
};

/// Send an event to peer device
struct gattc_send_evt_cmd
{
    /// Request type (notification / indication)
    uint8_t operation;
    /// operation sequence number
    uint16_t seq_num;
    /// characteristic handle
    uint16_t handle;
    /// length of packet to send
    uint16_t length;
    /// data value
    uint8_t  value[__ARRAY_EMPTY];
};

/// Inform that attribute value is requested by lower layers.
struct gattc_read_req_ind
{
    /// Handle of the attribute that has to be read
    uint16_t handle;
};

/// Confirm Read Request requested by GATT to profile
struct gattc_read_cfm
{
    /// Handle of the attribute read
    uint16_t handle;
    /// Data length read
    uint16_t length;
    /// Status of read command execution by upper layers
    uint8_t status;
    /// attribute data value
    uint8_t  value[__ARRAY_EMPTY];
};

/// Inform that a modification of database has been requested by peer device.
struct gattc_write_req_ind
{
    /// Handle of the attribute that has to be written
    uint16_t handle;
    /// offset at which the data has to be written
    uint16_t offset;
    /// Data length to be written
    uint16_t length;
    /// Data to be written in attribute database
    uint8_t  value[__ARRAY_EMPTY];
};

/// Confirm modification of database from upper layer when requested by peer device.
struct gattc_write_cfm
{
    /// Handle of the attribute written
    uint16_t handle;
    /// Status of write command execution by upper layers
    uint8_t status;
};

/// Parameters for @ref GATTC_SEND_SVC_CHANGED_CMD message
struct gattc_send_svc_changed_cmd
{
    /// Request Type
    uint8_t operation;
    /// operation sequence number
    uint16_t seq_num;
    /// Start of Affected Attribute Handle Range
    uint16_t svc_shdl;
    /// End of Affected Attribute Handle Range
    uint16_t svc_ehdl;
};

/// Parameters for @ref GATTC_SVC_CHANGED_CFG_IND and @ref GATTC_SVC_CHANGED_SET_CFG_REQ message
struct gattc_svc_changed_cfg
{
    /**
     * Current value of the Client Characteristic Configuration descriptor for the Service
     * Changed characteristic
     */
    uint16_t ind_cfg;
};


/// Request Attribute info to upper layer - could be trigger during prepare write
struct gattc_att_info_req_ind
{
    /// Handle of the attribute for which info are requested
    uint16_t handle;
};

/// Attribute info from upper layer confirmation
struct gattc_att_info_cfm
{
    /// Handle of the attribute
    uint16_t handle;
    /// Current length of the attribute
    uint16_t length;
    /// use to know if it's possible to modify the attribute
    /// can contains authorization or application error code.
    uint8_t  status;
};


/// Service Discovery command
struct gattc_sdp_svc_disc_cmd
{
    /// GATT Request Type
    /// - GATTC_SDP_DISC_SVC Search specific service
    /// - GATTC_SDP_DISC_SVC_ALL Search for all services
    /// - GATTC_SDP_DISC_CANCEL Cancel Service Discovery Procedure
    uint8_t operation;
    /// Service UUID Length
    uint8_t  uuid_len;
    /// operation sequence number
    uint16_t seq_num;
    /// Search start handle
    uint16_t start_hdl;
    /// Search end handle
    uint16_t end_hdl;
    /// Service UUID
    uint8_t  uuid[ATT_UUID_128_LEN];
};


/// Information about included service
struct gattc_sdp_include_svc
{
    /// Attribute Type
    /// - GATTC_SDP_INC_SVC: Included Service Information
    uint8_t att_type;
    /// Included service UUID Length
    uint8_t uuid_len;
    /// Included Service UUID
    uint8_t  uuid[ATT_UUID_128_LEN];
    /// Included service Start Handle
    uint16_t start_hdl;
    /// Included service End Handle
    uint16_t end_hdl;
};

/// Information about attribute characteristic
struct gattc_sdp_att_char
{
    /// Attribute Type
    /// - GATTC_SDP_ATT_CHAR: Characteristic Declaration
    uint8_t att_type;
    /// Value property
    uint8_t prop;
    /// Value Handle
    uint16_t handle;
};

/// Information about attribute
struct gattc_sdp_att
{
    /// Attribute Type
    /// - GATTC_SDP_ATT_VAL: Attribute Value
    /// - GATTC_SDP_ATT_DESC: Attribute Descriptor
    uint8_t  att_type;
    /// Attribute UUID Length
    uint8_t  uuid_len;
    /// Attribute UUID
    uint8_t  uuid[ATT_UUID_128_LEN];
};

/// Attribute information
union gattc_sdp_att_info
{
    /// Attribute Type
    uint8_t att_type;
    /// Information about attribute characteristic
    struct gattc_sdp_att_char att_char;
    /// Information about included service
    struct gattc_sdp_include_svc inc_svc;
    /// Information about attribute
    struct gattc_sdp_att att;
};


/// Service Discovery indicate that a service has been found.
struct gattc_sdp_svc_ind
{
    /// Service UUID Length
    uint8_t  uuid_len;
    /// Service UUID
    uint8_t  uuid[ATT_UUID_128_LEN];
    /// Service start handle
    uint16_t start_hdl;
    /// Service end handle
    uint16_t end_hdl;
    /// attribute information present in the service
    /// (length = end_hdl - start_hdl)
    union gattc_sdp_att_info info[__ARRAY_EMPTY];
};



/// @} GATTCTASK
#endif // GATTC_TASK_H_
