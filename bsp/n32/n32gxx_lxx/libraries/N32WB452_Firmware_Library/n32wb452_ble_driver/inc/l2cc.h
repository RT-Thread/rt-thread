/**
 ****************************************************************************************
 *
 * @file l2cc.h
 *
 * @brief Header file - L2CC.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef L2CC_H_
#define L2CC_H_

/**
 ****************************************************************************************
 * @addtogroup L2CC L2CAP Controller
 * @ingroup L2C
 * @brief L2CAP block for data processing and per device connection
 *
 * The L2CC is responsible for all the data processing related
 * functions of the L2CAP block per device connection.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_L2CC)

#include "l2cc_task.h"
#include "l2cc_pdu.h"

#include <stdint.h>
#include <stdbool.h>
#include "co_list.h"
#include "ke_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Generic way to creates and allocate a Signaling PDU message that can be then
 *        sent to peer device
 *
 * @param[in] conidx        Connection Index
 * @param[in] code          PDU code
 * @param[in] src_id        Source task ID
 *
 * @return Pointer to the PDU payload
 ****************************************************************************************
 */
#define L2CC_SIG_PDU_ALLOC(conidx, code, src_id, type) \
    ((struct type*) l2cc_pdu_alloc(conidx, L2C_CID_LE_SIGNALING, code, src_id, 0))

/// from PDU, retrieve the send command
#define L2CC_PDU_TO_CMD(_pdu) \
    ((struct l2cc_pdu_send_cmd*) (((uint8_t*)_pdu) - offsetof(struct l2cc_pdu_send_cmd, pdu.data.code)))

/// from PDU, retrieve the receive indication
#define L2CC_PDU_TO_IND(_pdu) \
    ((struct l2cc_pdu_recv_ind*) (((uint8_t*)_pdu) - offsetof(struct l2cc_pdu_recv_ind, pdu.data.code)))


/**
 ****************************************************************************************
 * @brief Generic way to creates and allocate a SMP PDU message that can be then sent to
 *        peer device
 *
 * @param[in] conidx        Connection Index
 * @param[in] code          PDU code
 * @param[in] src_id        Source task ID
 *
 * @return Pointer to the PDU payload
 ****************************************************************************************
 */
#define L2CC_SMP_PDU_ALLOC(conidx, code, src_id, type) \
    ((struct type*) l2cc_pdu_alloc(conidx, L2C_CID_SECURITY, code, src_id, 0))


/**
 ****************************************************************************************
 * @brief Generic way to creates and allocate an ATT PDU message that can be then sent to
 *        peer device
 *
 * @param[in] conidx        Connection Index
 * @param[in] code          PDU code
 * @param[in] src_id        Source task ID
 *
 * @return Pointer to the PDU payload
 ****************************************************************************************
 */
#define L2CC_ATT_PDU_ALLOC(conidx, code, src_id, type)\
    ((struct type*) l2cc_pdu_alloc(conidx, L2C_CID_ATTRIBUTE, code, src_id, 0))


/**
 ****************************************************************************************
 * @brief Generic way to creates and allocate an ATT PDU message that can be then sent to
 *        peer device
 *
 * @param[in] conidx        Connection Index
 * @param[in] code          PDU code
 * @param[in] src_id        Source task ID
 * @param[in] length        Dynamic payload length to allocate
 *
 * @return Pointer to the PDU payload
 ****************************************************************************************
 */
#define L2CC_ATT_PDU_ALLOC_DYN(conidx, code, src_id, type, length)\
    ((struct type*) l2cc_pdu_alloc(conidx, L2C_CID_ATTRIBUTE, code, src_id, length))

/*
 * INTERNAL MESSAGES API TYPES
 ****************************************************************************************
 */



/// Send Debug PDU data
struct l2cc_dbg_pdu_send_cmd
{
    /// L2CC request type (@see enum l2cc_operation):
    /// - L2CC_DBG_PDU_SEND: Send a PDU
    uint8_t operation;
    /// offset value information
    uint16_t offset;
    /// PDU Data
    struct l2cc_dbg_pdu pdu;
};

/// Debug PDU data received
struct l2cc_dbg_pdu_recv_ind
{
    /// Status information
    uint8_t status;
    /// offset value information
    uint16_t offset;
    /// PDU Data
    struct l2cc_dbg_pdu pdu;
};

/// Send Legacy PDU data
struct l2cc_pdu_send_cmd
{
    /// L2CC request type (@see enum l2cc_operation):
    /// - L2CC_PDU_SEND: Send internal LE Legacy PDU
    uint8_t operation;
    /// offset value information
    uint16_t offset;
    /// PDU Data
    struct l2cc_pdu pdu;
};


/// Legacy PDU data received
struct l2cc_pdu_recv_ind
{
    /// Status information
    uint8_t status;
    /// offset value information
    uint16_t offset;
    /// PDU Data
    struct l2cc_pdu pdu;
};

/// Operation type
enum l2cc_op_type
{
    /// Operation used for signaling protocol message exchange
    L2CC_OP_SIG      = 0x00,
    /// Max number of operations
    L2CC_OP_MAX,
};

/*
 * STRUCTURES
 ****************************************************************************************
 */



/// L2CAP environment structure
struct l2cc_env_tag
{
    /// Ongoing operation
    void* operation[L2CC_OP_MAX];

    /// Buffer in TX queue
    struct co_list tx_queue;
    /// Buffer currently receiving data
    struct ke_msg* rx_buffer;
    #if (BLE_LECB)
    /// List of LE credit based connections
    struct co_list lecb_list;
    #endif // (BLE_LECB)

    /// Length of PDU still expected
    uint16_t rx_pdu_rem_len;

};



/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Generic way to creates and allocate a PDU message that can be then sent to peer
 *        device
 *
 * @note use L2CC_SIG_PDU_ALLOC, L2CC_SMP_PDU_ALLOC, L2CC_ATT_PDU_ALLOC
 *       or L2CC_ATT_PDU_ALLOC_DYN instead of direct function call
 *
 * @param[in] conidx        Connection Index
 * @param[in] cid           Channel Identifier
 * @param[in] code          PDU code
 * @param[in] src_id        Source task ID
 * @param[in] length        Dynamic payload length to allocate
 *
 * @return Generic pointer to the PDU payload
 ****************************************************************************************
 */
void* l2cc_pdu_alloc(uint8_t conidx, uint16_t cid, uint8_t code, ke_task_id_t src_id, uint16_t length);

/**
 ****************************************************************************************
 * @brief Generic way to send the PDU message
 *
 * @param[in] pdu           PDU message to send to peer device
 ****************************************************************************************
 */
void l2cc_pdu_send(void* pdu);

#endif //(BLE_L2CC)

/// @} L2CC

#endif // L2CC_H_
