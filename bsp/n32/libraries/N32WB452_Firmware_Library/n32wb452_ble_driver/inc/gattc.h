/**
 ****************************************************************************************
 *
 * @file gattc.h
 *
 * @brief Header file - GATT Controller.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef GATTC_H_
#define GATTC_H_

/**
 ****************************************************************************************
 * @addtogroup GATTC Generic Attribute Profile Controller
 * @ingroup GATT
 * @brief Generic Attribute Profile Controller.
 *
 * This GATT module is responsible for providing an API for all attribute related operations
 * related to a BLE connection.
 * It is responsible for all the service framework activities using the Attribute protocol
 * for discovering services and for reading and writing characteristic values on a peer device.
 * To achieve this, the GATT interfaces with @ref ATTC "ATTC" and the @ref ATTS "ATTS".
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
/* kernel task */
#include "rwip_config.h"
#if (BLE_GATTC)

#include "co_list.h"


/*
 * DEFINES
 ****************************************************************************************
 */

/// Operation type
enum gattc_op_type
{
    #if (BLE_ATTS)
    /// Operation used to Server Request operations
    GATTC_OP_SERVER,
    #endif // (BLE_ATTS)

    #if (BLE_ATTC)
    /// Operation used to Client Request operations
    GATTC_OP_CLIENT,
    /// Service Discovery Procedure operation
    GATTC_OP_SDP,
    #endif // (BLE_ATTC)

    /// Max number of operations
    GATTC_OP_MAX
};

/*
 * TYPES DEFINITIONS
 ****************************************************************************************
 */

#if (BLE_ATTC)
/// Attribute Client environment variable requirements
struct attc_env
{
    /// List of ATT message used to aggregate long value in a single buffer.
    struct co_list rsp_list;
    /// List that contains peer device event registration
    struct co_list reg_evt;
    /// List that contains data for service discovery
    struct co_list sdp_data;
};
#endif // (BLE_ATTC)

#if (BLE_ATTS)
/// Attribute server environment variables
struct atts_env
{
    /// This is used to merge save all the prepare write request received ,
    /// before receiving the execute or cancel or disconnection.
    struct co_list             prep_wr_req_list;
    /// This list is used to put any data in order to send a response to peer device
    struct co_list             rsp;
    /// List of PDU to process
    struct co_list             pdu_queue;
    /// This structure is used to store in cache latest attribute read value
    struct gattc_read_cfm*     read_cache;
};
#endif // (BLE_ATTS)

/// GATT controller environment variable structure.
struct gattc_env_tag
{
    /// Request operation Kernel message
    void* operation[GATTC_OP_MAX];

    #if (BLE_ATTC)
    struct attc_env client;
    #endif // (BLE_ATTC)

    #if (BLE_ATTS)
    struct atts_env server;
    #endif // (BLE_ATTS)

    /// Current MTU Size
    uint16_t mtu_size;

    /// A transaction timeout occurs, reject next attribute commands
    bool     trans_timeout;
};
/*
 * MACRO DEFINITIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Created link connection parameters (from bond data) has been set, connection
 * ready to be used.
 *
 * @param[in] conidx     Connection Index
 *
 ****************************************************************************************
 */
void gattc_con_enable(uint8_t conidx);


/**
 ****************************************************************************************
 * @brief Gets the negotiated MTU. This function gets the negotiated MTU.
 *
 * @param[in] idx   connection record index
 *
 * @return MTU negotiated
 *
 ****************************************************************************************
 */
uint16_t gattc_get_mtu(uint8_t idx);

/**
 ****************************************************************************************
 * @brief Sets the negotiated MTU This function stores the negotiated MTU.
 *
 * @param[in] idx   connection record index
 * @param[in] mtu   negotiated MTU
 *
 * @return status   indicates if the MTU setting operation is successful
 *
 ****************************************************************************************
 */
void gattc_set_mtu(uint8_t idx, uint16_t mtu);



#endif /* (BLE_GATTC) */

/// @} GATTC
#endif // GATTC_H_
