/**
 ****************************************************************************************
 *
 * @file l2cc_pdu.h
 *
 * @brief Header file - L2CAP LE Credit Based connection management
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */


#ifndef _L2CC_LECB_H_
#define _L2CC_LECB_H_

/**
 ****************************************************************************************
 * @addtogroup L2CC_LECB L2Cap Controller LE Credit Based connection management
 * @ingroup L2CC
 * @brief This module is in charge of LECB connection management
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_LECB)

/*
 * DEFINES
 ****************************************************************************************
 */
/// LE Credit Based fields.
enum l2cc_lecb_fields
{
    /// LE Protocol Service Multiplexer
    L2CC_LECB_LEPSM,
    /// Local channel ID
    L2CC_LECB_LOCAL_CID,
    /// Peer channel ID
    L2CC_LECB_PEER_CID,
};


/// Status of the LE Credit Based connection
///
///    7    6    5    4    3    2    1    0
/// +----+----+----+----+----+----+----+----+
/// |           RFU          |P_I |TX_W|CON |
/// +----+----+----+----+----+----+----+----+
///
/// bit [2]  : Local(0)/Peer (1) initiated connection
/// bit [1]  : TX in Wait state (segment transmission not finished)
/// bit [0]  : LECB Connected
enum l2cc_lecb_state
{
    /// Peer initiated connection
    L2CC_LECB_PEER_INIT_BIT    = (1<<2),
    L2CC_LECB_PEER_INIT_POS    = (2),

    /// TX in Wait state (segment transmission not finished)
    L2CC_LECB_TX_WAIT_BIT      = (1<<1),
    L2CC_LECB_TX_WAIT_POS      = (1),

    /// Channel Connected
    L2CC_LECB_CONNECTED_BIT    = (1<<0),
    L2CC_LECB_CONNECTED_POS    = (0),
};





/*
 * MACRO DEFINITIONS
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */



/// LE credit based information for a link started or on-going.
struct l2cc_lecb_info
{
    /// Pointer to the following list
    struct co_list_hdr hdr;
    /// SDU waiting to be transfered (required for segmentation algorithm)
    struct l2cc_lecb_sdu_send_cmd* tx_sdu;
    /// SDU waiting to be received (required for reassembly algorithm)
    struct l2cc_lecb_sdu_recv_ind* rx_sdu;

    /// LE Protocol/Service Multiplexer
    uint16_t le_psm;

    /// Local channel ID
    uint16_t local_cid;
    /// Local Maximum Transmission Unit
    uint16_t local_mtu;
    /// Local Maximum Packet Size
    uint16_t local_mps;
    /// Local credit
    uint16_t local_credit;

    /// Peer channel ID
    uint16_t peer_cid;
    /// Peer Maximum Transmission Unit
    uint16_t peer_mtu;
    /// Peer Maximum Packet Size
    uint16_t peer_mps;
    /// Peer credit
    uint16_t peer_credit;

    /// Task id requested connection
    ke_task_id_t task_id;

    /// Status of the LE Credit Based connection (@see enum l2cc_lecb_state)
    uint8_t state;

    /// disconnection reason
    uint8_t disc_reason;

    /// Packet identifier - used for LECB negotiation
    uint8_t pkt_id;
};


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Search LE Credit Based channel depending on the parameter
 *
 * @param[in] conidx        Connection Index
 * @param[in] field         Search field (@see enum l2cc_lecb_fields)
 * @param[in] value         Field value to search
 *
 * @return Returns NULL or pointer to the LE Credit Based channel info
 ****************************************************************************************
 */
struct l2cc_lecb_info* l2cc_lecb_find(uint8_t conidx, uint8_t field, uint16_t value);

/**
 ****************************************************************************************
 * @brief End of LECB Connection, free information, and send disconnect indication
 *
 * @param[in] conidx         Connection Index
 * @param[in] lecb           LE Credit Based Connection information
 * @param[in] disconnect_ind True, sends disconnect indication
 ****************************************************************************************
 */
void l2cc_lecb_free(uint8_t conidx, struct l2cc_lecb_info* lecb, bool disconnect_ind);


/**
 ****************************************************************************************
 * @brief Sends LE credit based connection request
 *
 * @param[in] conidx        connection index
 * @param[in] pkt_id        Packet identifier
 * @param[in] scid          Source channel ID
 * @param[in] credits       Credits
 * @param[in] mps           Maximum Packet Size
 * @param[in] mtu           Maximum Transfer Unit
 ****************************************************************************************
 */
void l2cc_lecb_send_con_req(uint8_t conidx, uint8_t pkt_id, uint16_t le_psm, uint16_t scid, uint16_t credits,
                            uint16_t mps, uint16_t mtu);

/**
 ****************************************************************************************
 * @brief Sends LE credit based connection response
 *
 * @param[in] conidx        connection index
 * @param[in] status        status of the connection
 * @param[in] pkt_id        Packet identifier
 * @param[in] dcid          Destination channel ID
 * @param[in] credits       Credits
 * @param[in] mps           Maximum Packet Size
 * @param[in] mtu           Maximum Transfer Unit
 ****************************************************************************************
 */
void l2cc_lecb_send_con_rsp(uint8_t conidx, uint16_t status, uint8_t pkt_id,
                            uint16_t dcid, uint16_t credits, uint16_t mps, uint16_t mtu);

/**
 ****************************************************************************************
 * @brief Sends LE credit based disconnection request
 *
 * @param[in] conidx        connection index
 * @param[in] pkt_id        Packet identifier
 * @param[in] dcid          Destination channel ID
 * @param[in] scid          Source channel ID
 ****************************************************************************************
 */
void l2cc_lecb_send_disc_req(uint8_t conidx, uint8_t pkt_id, uint16_t scid, uint16_t dcid);

/**
 ****************************************************************************************
 * @brief Sends LE credit based disconnection response
 *
 * @param[in] conidx        connection index
 * @param[in] pkt_id        Packet identifier
 * @param[in] dcid          Destination channel ID
 * @param[in] scid          Source channel ID
 ****************************************************************************************
 */
void l2cc_lecb_send_disc_rsp(uint8_t conidx, uint8_t pkt_id, uint16_t dcid, uint16_t scid);
/**
 ****************************************************************************************
 * @brief Sends LE credit based Flow Control credit add message
 *
 * @param[in] conidx        connection index
 * @param[in] pkt_id        Packet identifier
 * @param[in] cid           Source Channel ID
 * @param[in] credits       Credits
 ****************************************************************************************
 */
void l2cc_lecb_send_credit_add(uint8_t conidx, uint8_t pkt_id, uint16_t cid, uint16_t credits);


/**
 ****************************************************************************************
 * @brief Due to an error on LECB link, initiate a disconnection of the channel
 *
 * @param[in] conidx        connection index
 * @param[in] lecb          Information of the channel
 * @param[in] disc_reason   Disconnection reason
 *
 ****************************************************************************************
 */
void l2cc_lecb_init_disconnect(uint8_t conidx, struct l2cc_lecb_info* lecb, uint8_t disc_reason);

/**
 ****************************************************************************************
 * @brief Retrieve LECB error Code from Host error code
 *
 * @param[in] h_err      Host Error code
 *
 * @return LECB Error code
 ****************************************************************************************
 */
uint16_t l2cc_lecb_h2l_err(uint8_t h_err);

#endif //(BLE_LECB)

/// @} L2CC_LECB

#endif /* _L2CC_LECB_H_ */
