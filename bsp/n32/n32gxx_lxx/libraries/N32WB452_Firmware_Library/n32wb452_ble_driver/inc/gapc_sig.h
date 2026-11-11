/**
 ****************************************************************************************
 *
 * @file gapc_sig.h
 *
 * @brief Generic Access Profile Controller Signaling PDU Handler.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */

#ifndef _GAPC_SIG_H_
#define _GAPC_SIG_H_


/**
 ****************************************************************************************
 * @addtogroup GAPC_SIG Generic Access Profile Controller Signaling PDU Handler.
 * @ingroup GAPC
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_GAPC)
#include "l2cc_pdu.h"


#if (BLE_CENTRAL)
/**
 ****************************************************************************************
 * @brief Sends parameter response
 *
 * @param[in] conidx        connection index
 * @param[in] result        response result
 * @param[in] pkt_id        Packet identifier
 ****************************************************************************************
 */
void gapc_sig_send_param_resp(uint8_t conidx, uint16_t result, uint8_t pkt_id);
#endif // (BLE_CENTRAL)

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
int gapc_sig_pdu_recv_handler(uint8_t conidx, struct l2cc_pdu *pdu);

#endif // (BLE_GAPC)

#endif // _GAPC_SIG_H_

/// @} GAPC_SIG
