/**
 ****************************************************************************************
 *
 * @file l2cc_sig.h
 *
 * @brief L2CAP Controller Controller Signaling PDU Handler.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */

#ifndef _L2CC_SIG_H_
#define _L2CC_SIG_H_


/**
 ****************************************************************************************
 * @addtogroup L2CC_SIG L2CAP Controller Signaling PDU Handler.
 * @ingroup L2CC
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_L2CC)

#include "l2cc.h"
#include "l2cc_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * MACRO DEFINITIONS
 ****************************************************************************************
 */



/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */



/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Send an L2Cap command rejected signaling packet with command not understood
 * error code.
 *
 * @param[in] conidx        Connection Index
 * @param[in] pkt_id        Packet identifier
 *
 * @param[in] reason        The Reason field describes why the Request packet was rejected
 * @param[in] opt1          Optional param 1
 * @param[in] opt2          Optional param 2
 ****************************************************************************************
 */
void l2cc_sig_send_cmd_reject(uint8_t conidx, uint8_t pkt_id, uint16_t reason, uint16_t opt1, uint16_t opt2);


/**
 ****************************************************************************************
 *  @brief Handles reception of L2CAP signaling messages from peer device.
 *
 * @param[in] conidx        Connection Index
 * @param[in] pdu           PDU Received
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int l2cc_sig_pdu_recv_handler(uint8_t conidx, struct l2cc_pdu *pdu);




#endif // (BLE_L2CC)

#endif // _L2CC_SIG_H_

/// @} L2CC_SIG
