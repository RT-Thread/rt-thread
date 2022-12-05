/**
 ****************************************************************************************
 *
 * @file co_llcp.h
 *
 * @brief This file contains the LLCP Bluetooth defines, enumerations and structures
 *        definitions for use by all modules in RW stack.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 ****************************************************************************************
 */

#ifndef CO_LLCP_H_
#define CO_LLCP_H_

/**
 ****************************************************************************************
 * @addtogroup CO_BT
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "co_bt.h"
/*
 * DEFINES
 ****************************************************************************************
 */
#define LLCP_OPCODE_MASK      (0xFF)
#define LLCP_OPCODE_POS       (0)
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/// Control packet opcode
enum co_llcp_opcode
{
    /// Connection update request
    LLCP_CONNECTION_UPDATE_IND_OPCODE,
    /// Channel map request
    LLCP_CHANNEL_MAP_IND_OPCODE,
    /// Termination indication
    LLCP_TERMINATE_IND_OPCODE,
    /// Encryption request
    LLCP_ENC_REQ_OPCODE,
    /// Encryption response
    LLCP_ENC_RSP_OPCODE,
    /// Start encryption request
    LLCP_START_ENC_REQ_OPCODE,
    /// Start encryption response
    LLCP_START_ENC_RSP_OPCODE,
    /// Unknown response
    LLCP_UNKNOWN_RSP_OPCODE,
    /// Feature request
    LLCP_FEATURE_REQ_OPCODE,
    /// Feature response
    LLCP_FEATURE_RSP_OPCODE,
    /// Pause encryption request
    LLCP_PAUSE_ENC_REQ_OPCODE,
    /// Pause encryption response
    LLCP_PAUSE_ENC_RSP_OPCODE,
    /// Version indication
    LLCP_VERSION_IND_OPCODE,
    /// Reject indication
    LLCP_REJECT_IND_OPCODE,
#if !(BLE_QUALIF)
    /// Slave feature request
    LLCP_SLAVE_FEATURE_REQ_OPCODE,
    /// Connection parameters request
    LLCP_CONNECTION_PARAM_REQ_OPCODE,
    /// Connection parameters response
    LLCP_CONNECTION_PARAM_RSP_OPCODE,
    /// Reject indication extended
    LLCP_REJECT_IND_EXT_OPCODE,
    /// Ping request
    LLCP_PING_REQ_OPCODE,
    /// Ping response
    LLCP_PING_RSP_OPCODE,
    /// Length request
    LLCP_LENGTH_REQ_OPCODE,
    /// Length response
    LLCP_LENGTH_RSP_OPCODE,
#endif // !(BLE_QUALIF)
    /// Opcode length
    LLCP_OPCODE_MAX_OPCODE,

    #if (BLE_TESTER)
    LLCP_OPCODE_DEBUG = 0xFF,
    #endif // (BLE_TESTER)
};

/// PDU lengths (including opcode)
enum co_llcp_length
{
   LLCP_CON_REQ_LEN           = 34,
   LLCP_CON_UPD_IND_LEN       = 12,
   LLCP_CH_MAP_REQ_LEN        = 8,
   LLCP_TERM_IND_LEN          = 2,
   LLCP_ENC_REQ_LEN           = 23,
   LLCP_ENC_RSP_LEN           = 13,
   LLCP_ST_ENC_REQ_LEN        = 1,
   LLCP_ST_ENC_RSP_LEN        = 1,
   LLCP_UNKN_RSP_LEN          = 2,
   LLCP_FEAT_REQ_LEN          = 9,
   LLCP_FEAT_RSP_LEN          = 9,
   LLCP_PA_ENC_REQ_LEN        = 1,
   LLCP_PA_ENC_RSP_LEN        = 1,
   LLCP_VERS_IND_LEN          = 6,
   LLCP_REJ_IND_LEN           = 2,
   LLCP_SLAVE_FEATURE_REQ_LEN = 9,
   LLCP_REJECT_IND_EXT_LEN    = 3,
   LLCP_CON_PARAM_REQ_LEN     = 24,
   LLCP_CON_PARAM_RSP_LEN     = 24,
   LLCP_PING_REQ_LEN          = 1,
   LLCP_PING_RSP_LEN          = 1,
   LLCP_LENGTH_REQ_LEN        = 9,
   LLCP_LENGTH_RSP_LEN        = 9,
   LLCP_PDU_LENGTH_MAX        = 34
};

/*
 * MESSAGES
 ****************************************************************************************
 */


/// LLCP_CONNECTION_UPDATE_REQ structure.
struct  llcp_con_upd_ind
{
    /// opcode
    uint8_t         opcode;
    /// window size
    uint8_t         win_size;
    /// window offset
    uint16_t        win_off;
    /// interval
    uint16_t        interv;
    /// latency
    uint16_t        latency;
    /// timeout
    uint16_t        timeout;
    /// instant
    uint16_t        instant;
};

/// LLCP_CHANNEL_MAP_IND structure.
struct  llcp_channel_map_ind
{
    /// opcode
    uint8_t            opcode;
    /// channel mapping
    struct le_chnl_map ch_map;
    /// instant
    uint16_t           instant;
};

/// LLCP_TERMINATE_IND structure.
struct  llcp_terminate_ind
{
    /// opcode
    uint8_t         opcode;
    /// termination code
    uint8_t         err_code;
};

/// LLCP_ENC_REQ structure.
struct  llcp_enc_req
{
    /// opcode
    uint8_t             opcode;
    /// random value
    struct rand_nb      rand;
    /// ediv
    uint8_t             ediv[2];
    /// skdm
    struct sess_k_div_x   skdm;
    /// ivm
    struct init_vect    ivm;
};

/// LLCP_ENC_RSP structure.
struct  llcp_enc_rsp
{
    /// opcode
    uint8_t             opcode;
    /// skds
    struct sess_k_div_x   skds;
    /// ivs
    struct init_vect    ivs;
};

/// LLCP_START_ENC_REQ structure.
struct  llcp_start_enc_req
{
    /// opcode
    uint8_t             opcode;
};

/// LLCP_START_ENC_RSP structure.
struct  llcp_start_enc_rsp
{
    /// opcode
    uint8_t             opcode;
};

/// LLCP_UNKNOWN_RSP structure.
struct  llcp_unknown_rsp
{
    /// opcode
    uint8_t         opcode;
    /// unknown type
    uint8_t         unk_type;
};

/// LLCP_FEATURE_REQ structure.
struct  llcp_feats_req
{
    /// opcode
    uint8_t             opcode;
    /// le features
    struct le_features  feats;
};

/// LLCP_FEATURE_RSP structure.
struct  llcp_feats_rsp
{
    /// opcode
    uint8_t             opcode;
    /// le features
    struct le_features  feats;
};

/// LLCP_PAUSE_ENC_REQ structure.
struct  llcp_pause_enc_req
{
    /// opcode
    uint8_t             opcode;
};

/// LLCP_PAUSE_ENC_RSP structure.
struct  llcp_pause_enc_rsp
{
    /// opcode
    uint8_t             opcode;
};

/// LLCP_VERS_IND structure
struct llcp_vers_ind
{
    /// opcode
    uint8_t     opcode;
    /// version
    uint8_t     vers;
    /// company id
    uint16_t    compid;
    /// sub version
    uint16_t    subvers;
};

/// LLCP_REJECT_IND structure.
struct  llcp_reject_ind
{
    /// opcode
    uint8_t         opcode;
    /// reject reason
    uint8_t         err_code;
};

/// LLCP_SLAVE_FEATURE_REQ structure.
struct  llcp_slave_feature_req
{
    /// opcode
    uint8_t             opcode;
    /// le features
    struct le_features  feats;
};

/// LLCP_CONNECTION_PARAM_REQ structure.
struct  llcp_con_param_req
{
    /// opcode
    uint8_t         opcode;
    /// minimum value of connInterval
    uint16_t        interval_min;
    /// maximum value of connInterval
    uint16_t        interval_max;
    /// connSlaveLatency value
    uint16_t        latency;
    /// connSupervisionTimeout value
    uint16_t        timeout;
    /// preferred periodicity
    uint8_t         pref_period;
    /// ReferenceConnEventCount
    uint16_t        ref_con_event_count;
    /// Offset0
    uint16_t        offset0;
    /// Offset1
    uint16_t        offset1;
    /// Offset2
    uint16_t        offset2;
    /// Offset3
    uint16_t        offset3;
    /// Offset4
    uint16_t        offset4;
    /// Offset5
    uint16_t        offset5;
};

/// LLCP_CONNECTION_PARAM_RSP structure.
struct  llcp_con_param_rsp
{
    /// opcode
    uint8_t          opcode;
    /// minimum value of connInterval
    uint16_t         interval_min;
    /// maximum value of connInterval
    uint16_t         interval_max;
    /// connSlaveLatency value
    uint16_t         latency;
    /// connSupervisionTimeout value
    uint16_t         timeout;
    /// preferred periodicity
    uint8_t          pref_period;
    /// ReferenceConnEventCount
    uint16_t         ref_con_event_count;
    /// Offset0
    uint16_t         offset0;
    /// Offset1
    uint16_t         offset1;
    /// Offset2
    uint16_t         offset2;
    /// Offset3
    uint16_t         offset3;
    /// Offset4
    uint16_t         offset4;
    /// Offset5
    uint16_t         offset5;
};

/// LLCP_REJECT_IND structure.
struct  llcp_reject_ind_ext
{
    /// opcode
    uint8_t         opcode;
    /// rejected opcode
    uint8_t         rej_opcode;
    /// reject reason
    uint8_t         err_code;
};

/// LLCP_PING_REQ structure.
struct  llcp_ping_req
{
    /// opcode
    uint8_t         opcode;
};

/// LLCP_PING_RSP structure.
struct  llcp_ping_rsp
{
    /// opcode
    uint8_t         opcode;
};

/// LLCP_LENGTH_REQ structure.
struct  llcp_length_req
{
    /// opcode
    uint8_t     opcode;
    /// The max size in reception
    uint16_t    max_rx_octets;
    /// The max time in reception
    uint16_t    max_rx_time;
    /// The max size in transmission
    uint16_t    max_tx_octets;
    /// The max time in transmission
    uint16_t    max_tx_time;
};

/// LLCP_LENGTH_RSP structure.
struct  llcp_length_rsp
{
    /// opcode
    uint8_t     opcode;
    /// The max size in reception
    uint16_t    max_rx_octets;
    /// The max time in reception
    uint16_t    max_rx_time;
    /// The max size in transmission
    uint16_t    max_tx_octets;
    /// The max time in transmission
    uint16_t    max_tx_time;
};

/// LLCP pdu format
union llcp_pdu
{
    /// opcode
    uint8_t  opcode;

    struct llcp_con_upd_ind       con_up_req;
    struct llcp_channel_map_ind   channel_map_req;
    struct llcp_terminate_ind     terminate_ind;
    struct llcp_enc_req           enc_req;
    struct llcp_enc_rsp           enc_rsp;
    struct llcp_start_enc_req     start_enc_req;
    struct llcp_start_enc_rsp     start_enc_rsp;
    struct llcp_unknown_rsp       unknown_rsp;
    struct llcp_feats_req         feats_req;
    struct llcp_feats_rsp         feats_rsp;
    struct llcp_pause_enc_req     pause_enc_req;
    struct llcp_pause_enc_rsp     pause_enc_rsp;
    struct llcp_vers_ind          vers_ind;
    struct llcp_reject_ind        reject_ind;
    struct llcp_slave_feature_req slave_feature_req;
    struct llcp_con_param_req     con_param_req;
    struct llcp_con_param_rsp     con_param_rsp;
    struct llcp_reject_ind_ext    reject_ind_ext;
    struct llcp_ping_req          ping_req;
    struct llcp_ping_rsp          ping_rsp;
    struct llcp_length_req        length_req;
    struct llcp_length_rsp        length_rsp;
};

/// @} CO_BT
#endif // CO_LLCP_H_
