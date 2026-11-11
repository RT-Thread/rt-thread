/**
 ****************************************************************************************
 *
 * @file attc.h
 *
 * @brief Header file - ATTC.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef ATTC_H_
#define ATTC_H_

/**
 ****************************************************************************************
 * @addtogroup ATTC Attribute Client
 * @ingroup ATT
 * @brief Attribute Protocol Client
 *
 * The ATTC module is responsible for handling messages intended for the attribute
 * profile client. It has defined interfaces with @ref ATTM "ATTM".
 *
 * @{
 *
 ****************************************************************************************
 */
#include "rwip_config.h"

#include <stdint.h>
#include "l2cc.h"
#include "ke_task.h"

#if (BLE_ATTC)
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
/*
 * DEFINES
 ****************************************************************************************
 */

/// Allocate a Attribute PDU packet for a specific attribute request.
#define ATTC_ALLOCATE_ATT_REQ(conidx, opcode, pdu_type, value_len)\
    L2CC_ATT_PDU_ALLOC_DYN(conidx, opcode, KE_BUILD_ID(TASK_GATTC, conidx), pdu_type, value_len)

/*
 * DATA STRUCTURES
 ****************************************************************************************
 */

/// Peer device event registration
struct attc_register_evt
{
    /// list header
    struct co_list_hdr hdr;
    /// Attribute start handle
    uint16_t start_hdl;
    /// Attribute end handle
    uint16_t end_hdl;
    /// Task to be notified
    ke_task_id_t task;
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
 * @brief Sends Indication reception confirmation message
 *
 * @param[in] conidx        connection index
 *
 ****************************************************************************************
 */
void attc_send_hdl_cfm(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Sends write execute.
 *
 * @param[in] conidx        connection index
 * @param[in] flag          write execute flag (write or discard)
 *
 ****************************************************************************************
 */
void attc_send_execute(uint8_t conidx, uint8_t flag);


/**
 ****************************************************************************************
 * @brief Send a PDU Attribute request packet
 *
 * @param[in] conidx  Index of the connection with the peer device
 * @param[in] pdu        PDU Packet
 ****************************************************************************************
 */
void attc_send_att_req(uint8_t conidx, void *pdu);

#endif /* (BLE_ATTC) */

#if (BLE_CENTRAL || BLE_PERIPHERAL)
/**
 ****************************************************************************************
 * @brief Handles reception of PDU Packet
 *
 * @param[in] conidx  Index of the connection with the peer device
 * @param[in] param   Received PDU Packet
 *
 * @return If message has been proceed or consumed
 ****************************************************************************************
 */
int attc_l2cc_pdu_recv_handler(uint8_t conidx, struct l2cc_pdu_recv_ind *param);
#endif /* #if (BLE_CENTRAL || BLE_PERIPHERAL) */

/// @} ATTC
#endif // ATT_H_
