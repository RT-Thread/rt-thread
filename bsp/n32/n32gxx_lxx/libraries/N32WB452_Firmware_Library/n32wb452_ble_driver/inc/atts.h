/**
 ****************************************************************************************
 *
 * @file atts.h
 *
 * @brief Header file - ATTS.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef ATTS_H_
#define ATTS_H_

/**
 ****************************************************************************************
 * @addtogroup ATTS Attribute Server
 * @ingroup ATT
 * @brief Attribute Protocol Server
 *
 * The ATTS module is responsible for handling messages intended for the attribute
 * profile server. It has defined interfaces with @ref ATTM "ATTM".
 *
 *
 * @{
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_ATTS)
#include "att.h"
//#include "compiler.h"
#include "ble_arch.h"
#include <stdbool.h>
#include "co_list.h"
#include "gattc_task.h"
#include "l2cc.h"

/*
 * DEFINES
 ****************************************************************************************
 */



/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 * Confirmation of write signed (signature verified)
 *
 * @param[in] conidx    Connection Index
 * @param[in] length    Signed Data Length
 * @param[in] sign_data Signed Data
 */
void atts_write_signed_cfm(uint8_t conidx, uint16_t length, uint8_t* sign_data);


/**
 ****************************************************************************************
 * @brief Send an attribute error response to peer.
 *
 * @param[in] conidx            Index of the connection with the peer device
 * @param[in] opcode            failing operation code
 * @param[in] uuid              attribute UUID
 * @param[in] error             error code
 ****************************************************************************************
 */
void atts_send_error(uint8_t conidx, uint8_t opcode, uint16_t uuid, uint8_t error);


/**
 ****************************************************************************************
 * @brief Format the Write Response PDU and send it after receiving a Write Request PDU
 * @param[in] conidx Index of the connection with the peer device
 * @param[in] atthdl  Attribute handle for which to send the response
 * @param[in] status  ATT error code
 ****************************************************************************************
 */
void atts_write_rsp_send(uint8_t conidx, uint16_t atthdl, uint8_t status);


/**
 ****************************************************************************************
 * @brief Sends a value notification/indication command
 *
 * @param[in] conidx    Connection Index
 * @param[in] event     Event parameters to send
 *
 * @return If notification can be sent or not
 ****************************************************************************************
 */
uint8_t atts_send_event(uint8_t conidx, struct gattc_send_evt_cmd *event);


/**
 * @brief  Clear allocated prepare write temporary data.
 *
 * @param[in] conidx            connection index
 */
void atts_clear_prep_data(uint8_t conidx);


/**
 * @brief  Clear allocated temporary data used for ATTS response.
 *
 * @param[in] conidx            connection index
 */
void atts_clear_rsp_data(uint8_t conidx);

/**
 * @brief  Clear temporary attribute read data present in cache.
 *
 * @param[in] conidx            connection index
 */
void atts_clear_read_cache(uint8_t conidx);

/**
 * @brief  Process execution of a received ATTS PDU.
 *
 * @param conidx            connection index
 */
void atts_process_pdu(uint8_t conidx);

/// @} ATTS
#endif /* (BLE_ATTS) */

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
int atts_l2cc_pdu_recv_handler(uint8_t conidx, struct l2cc_pdu_recv_ind *param);
#endif /* #if (BLE_CENTRAL || BLE_PERIPHERAL) */

#endif // ATTS_H_
