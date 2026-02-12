/**
 ****************************************************************************************
 *
 * @file co_lmp.h
 *
 * @brief This file contains the HCI Bluetooth defines, enumerations and structures
 *        definitions for use by all modules in RW stack.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 ****************************************************************************************
 */

#ifndef CO_LMP_H_
#define CO_LMP_H_

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

//LMP Opcodes
#define LMP_NAME_REQ_OPCODE                1
#define LMP_NAME_RES_OPCODE                2
#define LMP_ACCEPTED_OPCODE                3
#define LMP_NOT_ACCEPTED_OPCODE            4
#define LMP_CLK_OFF_REQ_OPCODE             5
#define LMP_CLK_OFF_RES_OPCODE             6
#define LMP_DETACH_OPCODE                  7
#define LMP_INRAND_OPCODE                  8
#define LMP_COMBKEY_OPCODE                 9
#define LMP_UNITKEY_OPCODE                10
#define LMP_AURAND_OPCODE                 11
#define LMP_SRES_OPCODE                   12
#define LMP_TEMPRAND_OPCODE               13
#define LMP_TEMPKEY_OPCODE                14
#define LMP_ENC_MODE_REQ_OPCODE           15
#define LMP_ENC_KEY_SIZE_REQ_OPCODE       16
#define LMP_START_ENC_REQ_OPCODE          17
#define LMP_STOP_ENC_REQ_OPCODE           18
#define LMP_SWITCH_REQ_OPCODE             19
#define LMP_HOLD_OPCODE                   20
#define LMP_HOLD_REQ_OPCODE               21
#define LMP_SNIFF_REQ_OPCODE              23
#define LMP_UNSNIFF_REQ_OPCODE            24
#define LMP_PARK_REQ_OPCODE               25
#define LMP_SET_BSWIN_OPCODE              27
#define LMP_MODIF_BEACON_OPCODE           28
#define LMP_UNPARK_BD_REQ_OPCODE          29
#define LMP_UNPARK_PM_REQ_OPCODE          30
#define LMP_INCR_PWR_REQ_OPCODE           31
#define LMP_DECR_PWR_REQ_OPCODE           32
#define LMP_MAX_PWR_OPCODE                33
#define LMP_MIN_PWR_OPCODE                34
#define LMP_AUTO_RATE_OPCODE              35
#define LMP_PREF_RATE_OPCODE              36
#define LMP_VER_REQ_OPCODE                37
#define LMP_VER_RES_OPCODE                38
#define LMP_FEATS_REQ_OPCODE              39
#define LMP_FEATS_RES_OPCODE              40
#define LMP_QOS_OPCODE                    41
#define LMP_QOS_REQ_OPCODE                42
#define LMP_SCO_LINK_REQ_OPCODE           43
#define LMP_RMV_SCO_LINK_REQ_OPCODE       44
#define LMP_MAX_SLOT_OPCODE               45
#define LMP_MAX_SLOT_REQ_OPCODE           46
#define LMP_TIMING_ACCU_REQ_OPCODE        47
#define LMP_TIMING_ACCU_RES_OPCODE        48
#define LMP_SETUP_CMP_OPCODE              49
#define LMP_USE_SEMI_PERM_KEY_OPCODE      50
#define LMP_HOST_CON_REQ_OPCODE           51
#define LMP_SLOT_OFF_OPCODE               52
#define LMP_PAGE_MODE_REQ_OPCODE          53
#define LMP_PAGE_SCAN_MODE_REQ_OPCODE     54
#define LMP_SUPV_TO_OPCODE                55
#define LMP_TEST_ACTIVATE_OPCODE          56
#define LMP_TEST_CTRL_OPCODE              57
#define LMP_ENC_KEY_SIZE_MASK_REQ_OPCODE  58
#define LMP_ENC_KEY_SIZE_MASK_RES_OPCODE  59
#define LMP_SET_AFH_OPCODE                60
#define LMP_ENCAPS_HDR_OPCODE             61
#define LMP_ENCAPS_PAYL_OPCODE            62
#define LMP_SP_CFM_OPCODE                 63
#define LMP_SP_NB_OPCODE                  64
#define LMP_DHKEY_CHK_OPCODE              65
#define LMP_PAUSE_ENC_AES_REQ_OPCODE      66

#define LMP_ESC1_OPCODE                   124
#define LMP_ESC2_OPCODE                   125
#define LMP_ESC3_OPCODE                   126
#define LMP_ESC4_OPCODE                   127

///LMP Escape 4 Extended Opcodes
#define LMP_ACCEPTED_EXT_EXTOPCODE         1
#define LMP_NOT_ACCEPTED_EXT_EXTOPCODE     2
#define LMP_FEATS_REQ_EXT_EXTOPCODE        3
#define LMP_FEATS_RES_EXT_EXTOPCODE        4
#define LMP_CLK_ADJ_EXTOPCODE              5
#define LMP_CLK_ADJ_ACK_EXTOPCODE          6
#define LMP_CLK_ADJ_REQ_EXTOPCODE          7
#define LMP_PKT_TYPE_TBL_REQ_EXTOPCODE    11
#define LMP_ESCO_LINK_REQ_EXTOPCODE       12
#define LMP_RMV_ESCO_LINK_REQ_EXTOPCODE   13
#define LMP_CH_CLASS_REQ_EXTOPCODE        16
#define LMP_CH_CLASS_EXTOPCODE            17
#define LMP_SSR_REQ_EXTOPCODE             21
#define LMP_SSR_RES_EXTOPCODE             22
#define LMP_PAUSE_ENC_REQ_EXTOPCODE       23
#define LMP_RESUME_ENC_REQ_EXTOPCODE      24
#define LMP_IO_CAP_REQ_EXTOPCODE          25
#define LMP_IO_CAP_RES_EXTOPCODE          26
#define LMP_NUM_COMPARISON_FAIL_EXTOPCODE 27
#define LMP_PASSKEY_FAIL_EXTOPCODE        28
#define LMP_OOB_FAIL_EXTOPCODE            29
#define LMP_KEYPRESS_NOTIF_EXTOPCODE      30
#define LMP_PWR_CTRL_REQ_EXTOPCODE        31
#define LMP_PWR_CTRL_RES_EXTOPCODE        32
#define LMP_PING_REQ_EXTOPCODE            33
#define LMP_PING_RES_EXTOPCODE            34

/// PDU lengths (including opcode)
#define LMP_NAME_REQ_LEN                    2
#define LMP_NAME_RES_LEN                    17
#define LMP_ACCEPTED_LEN                    2
#define LMP_NOT_ACCEPTED_LEN                3
#define LMP_CLK_OFF_REQ_LEN                 1
#define LMP_CLK_OFF_RES_LEN                 3
#define LMP_DETACH_LEN                      2
#define LMP_INRAND_LEN                      17
#define LMP_COMBKEY_LEN                     17
#define LMP_UNITKEY_LEN                     17
#define LMP_AURAND_LEN                      17
#define LMP_SRES_LEN                        5
#define LMP_TEMPRAND_LEN                    17
#define LMP_TEMPKEY_LEN                     17
#define LMP_ENC_MODE_REQ_LEN                2
#define LMP_ENC_KEY_SIZE_REQ_LEN            2
#define LMP_START_ENC_REQ_LEN               17
#define LMP_STOP_ENC_REQ_LEN                1
#define LMP_SWITCH_REQ_LEN                  5
#define LMP_HOLD_LEN                        7
#define LMP_HOLD_REQ_LEN                    7
#define LMP_SNIFF_REQ_LEN                   10
#define LMP_UNSNIFF_REQ_LEN                 1
#define LMP_PARK_REQ_LEN                    17
#define LMP_INCR_PWR_REQ_LEN                2
#define LMP_DECR_PWR_REQ_LEN                2
#define LMP_MAX_PWR_LEN                     1
#define LMP_MIN_PWR_LEN                     1
#define LMP_AUTO_RATE_LEN                   1
#define LMP_PREF_RATE_LEN                   2
#define LMP_VER_REQ_LEN                     6
#define LMP_VER_RES_LEN                     6
#define LMP_FEATS_REQ_LEN                   9
#define LMP_FEATS_RES_LEN                   9
#define LMP_QOS_LEN                         4
#define LMP_QOS_REQ_LEN                     4
#define LMP_SCO_LINK_REQ_LEN                7
#define LMP_RMV_SCO_LINK_REQ_LEN            3
#define LMP_MAX_SLOT_LEN                    2
#define LMP_MAX_SLOT_REQ_LEN                2
#define LMP_TIMING_ACCU_REQ_LEN             1
#define LMP_TIMING_ACCU_RES_LEN             3
#define LMP_SETUP_CMP_LEN                   1
#define LMP_USE_SEMI_PERM_KEY_LEN           1
#define LMP_HOST_CON_REQ_LEN                1
#define LMP_SLOT_OFF_LEN                    9
#define LMP_PAGE_MODE_REQ_LEN               3
#define LMP_PAGE_SCAN_MODE_REQ_LEN          3
#define LMP_SUPV_TO_LEN                     3
#define LMP_TEST_ACTIVATE_LEN               1
#define LMP_TEST_CTRL_LEN                   10
#define LMP_ENC_KEY_SIZE_MASK_REQ_LEN       1
#define LMP_ENC_KEY_SIZE_MASK_RES_LEN       3
#define LMP_SET_AFH_LEN                     16
#define LMP_ENCAPS_HDR_LEN                  4
#define LMP_ENCAPS_PAYL_LEN                 17
#define LMP_SP_CFM_LEN                      17
#define LMP_SP_NB_LEN                       17
#define LMP_DHKEY_CHK_LEN                   17
#define LMP_PAUSE_ENC_AES_REQ_LEN           17

/// LMP Escape 4 Extended PDU length (including opcode and ext opcode)
#define LMP_ACCEPTED_EXT_LEN                4
#define LMP_NOT_ACCEPTED_EXT_LEN            5
#define LMP_FEATS_REQ_EXT_LEN               12
#define LMP_FEATS_RES_EXT_LEN               12
#define LMP_CLK_ADJ_LEN                     15
#define LMP_CLK_ADJ_ACK_LEN                 3
#define LMP_CLK_ADJ_REQ_LEN                 6
#define LMP_PKT_TYPE_TBL_REQ_LEN            3
#define LMP_ESCO_LINK_REQ_LEN               16
#define LMP_RMV_ESCO_LINK_REQ_LEN           4
#define LMP_CH_CLASS_REQ_LEN                7
#define LMP_CH_CLASS_LEN                    12
#define LMP_SSR_REQ_LEN                     9
#define LMP_SSR_RES_LEN                     9
#define LMP_PAUSE_ENC_REQ_LEN               2
#define LMP_RESUME_ENC_REQ_LEN              2
#define LMP_IO_CAP_REQ_LEN                  5
#define LMP_IO_CAP_RES_LEN                  5
#define LMP_NUM_COMPARISON_FAIL_LEN         2
#define LMP_PASSKEY_FAIL_LEN                2
#define LMP_OOB_FAIL_LEN                    2
#define LMP_KEYPRESS_NOTIF_LEN              3
#define LMP_PWR_CTRL_REQ_LEN                3
#define LMP_PWR_CTRL_RES_LEN                3
#define LMP_PING_REQ_LEN                    2
#define LMP_PING_RES_LEN                    2

/// Maximum LMP PDU size (including opcode and ext opcode)
#define LMP_MAX_PDU_SIZE         DM1_PACKET_SIZE

/// Position of transaction ID in 1st byte
#define LMP_TR_ID_POS        0
#define LMP_TR_ID_MASK       0x01
/// Position of opcode in 1st byte
#define LMP_OPCODE_POS       1
#define LMP_OPCODE_MASK      0xFE

#define LMP_OPCODE(opcode, tr_id) (((opcode << LMP_OPCODE_POS) & LMP_OPCODE_MASK) | ((tr_id << LMP_TR_ID_POS) & LMP_TR_ID_MASK))
/*
 * MESSAGES
 ****************************************************************************************
 */

///LMP_name_req PDU structure
struct lmp_name_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Offset
    uint8_t  offset;
};

///LMP_name_res PDU structure
struct lmp_name_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Offset
    uint8_t  offset;
    ///Name Length
    uint8_t  length;
    ///Name Fragment
    struct name_vect name_frag;
};

///LMP_accepted PDU structure
struct lmp_accepted
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Opcode of the original LMP
    uint8_t  orig_opcode;
};

///LMP_not_accepted PDU structure
struct lmp_not_accepted
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Opcode of the original LMP
    uint8_t  orig_opcode;
    ///Reason for not accepting the PDU (error code)
    uint8_t  reason;
};

///LMP_clkoffset_req PDU structure
struct lmp_clk_off_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_clkoffset_res PDU structure
struct lmp_clk_off_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Clock Offset value
    uint16_t clk_offset ;
};

///LMP_detach PDU structure
struct lmp_detach
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Reason to detach
    uint8_t  reason;
};

///LMP_in_rand PDU structure
struct lmp_inrand
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Random number
    struct ltk random;
};

///LMP_comb_key PDU structure
struct lmp_combkey
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Random number
    struct ltk random;
};

///LMP_unit_key PDU structure
struct lmp_unitkey
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Key
    struct ltk key;
};

///LMP_au_rand PDU structure
struct lmp_aurand
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Random number
    struct ltk random;
};

///LMP_sres PDU structure
struct lmp_sres
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Authentication Response
    struct sres_nb Sres;
};

///LMP_temp_rand PDU structure
struct lmp_temprand
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Random number
    struct ltk random;
};

///LMP_temp_key PDU structure
struct lmp_tempkey
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Key
    struct ltk key;
};

///LMP_encryption_mode_req PDU structure
struct lmp_enc_mode_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Encryption Mode
    uint8_t  enc_mode;
};

///LMP_encryption_key_size_req PDU structure
struct lmp_enc_key_size_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Key Size
    uint8_t  key_size;
};

///LMP_start_encryption_req PDU structure
struct lmp_start_enc_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Random number
    struct ltk random;
};

///LMP_stop_encryption_req PDU structure
struct lmp_stop_enc_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_switch_req PDU structure
struct lmp_switch_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Switch Instant
    uint32_t switch_inst;
};

///LMP_sniff_req PDU structure
struct lmp_sniff_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Timing Control Flags
    uint8_t  flags;
    ///Dsniff
    uint16_t d_sniff;
    ///Tsniff
    uint16_t t_sniff;
    ///Sniff attempt
    uint16_t sniff_attempt;
    ///Sniff Timeout
    uint16_t sniff_to;
};

///LMP_unsniff_req PDU structure
struct lmp_unsniff_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_incr_power_req PDU structure
struct lmp_incr_pwr_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///For future use
    uint8_t  reserved;
};

///LMP_decr_power_req PDU structure
struct lmp_decr_pwr_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///For future use
    uint8_t  reserved;
};

///LMP_max_power PDU structure
struct lmp_max_pwr
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_min_power PDU structure
struct lmp_min_pwr
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_auto_rate PDU structure
struct lmp_auto_rate
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_preferred_rate PDU structure
struct lmp_pref_rate
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Data Rate
    uint8_t  rate;
};

///LMP_version_req PDU structure
struct lmp_ver_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Version number
    uint8_t  ver;
    ///Company ID
    uint16_t co_id;
    ///Subversion number
    uint16_t subver;
};

///LMP_version_res PDU structure
struct lmp_ver_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Version number
    uint8_t  ver;
    ///Company ID
    uint16_t co_id;
    ///Subversion number
    uint16_t subver;
};

///LMP_features_req PDU structure
struct lmp_feats_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Features
    struct features feats;
};

///LMP_features_res PDU structure
struct lmp_feats_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Features
    struct features feats;
};

///LMP_quality_of_service PDU structure
struct lmp_qos
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Poll interval
    uint16_t poll_intv;
    ///Nbc
    uint8_t  nbc;
};


///LMP_quality_of_service_req PDU structure
struct lmp_qos_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Poll interval
    uint16_t poll_intv;
    ///Nbc
    uint8_t  nbc;
};

///LMP_SCO_link_req PDU structure
struct lmp_sco_link_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///SCO handle
    uint8_t  sco_hdl;
    ///timing control flags
    uint8_t  flags;
    ///Dsco
    uint8_t  d_sco;
    ///Tsco
    uint8_t  t_sco;
    ///SCO packet
    uint8_t  sco_pkt;
    ///Air mode
    uint8_t  air_mode;
};

///LMP_remove_SCO_link_req PDU structure
struct lmp_rmv_sco_link_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///SCO handle
    uint8_t  sco_hdl;
    ///Reason for its removal(error code)
    uint8_t  reason;
};

///LMP_max_slot PDU structure
struct lmp_max_slot
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Max slots
    uint8_t  max_slots;
};


///LMP_max_slot_req PDU structure
struct lmp_max_slot_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Max slots
    uint8_t  max_slots;
};

///LMP_timing_accuracy_req PDU structure
struct lmp_timing_accu_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_timing_accuracy_res PDU structure
struct lmp_timing_accu_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Drift
    uint8_t  drift;
    ///Jitter
    uint8_t  jitter;
};

///LMP_setup_complete PDU structure
struct lmp_setup_cmp
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_use_semi_permanent_key PDU structure
struct lmp_use_semi_perm_key
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_host_connection_req PDU structure
struct lmp_host_con_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_slot_offset PDU structure
struct lmp_slot_off
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Slot Offset
    uint16_t       slot_off;
    ///BD Address
    struct bd_addr addr;
};

///LMP_page_mode_req PDU structure
struct lmp_page_mode_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Paging scheme
    uint8_t  page_scheme;
    ///Paging scheme settings
    uint8_t  page_stg;
};

///LMP_page_scan_mode_req PDU structure
struct lmp_page_scan_mode_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Paging scheme
    uint8_t  page_scheme;
    ///Paging scheme settings
    uint8_t  page_stg;
};

///LMP_supervision_timeout PDU structure
struct lmp_supv_to
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Supervision Timeout
    uint16_t supv_to;
};

///LMP_test_activate PDU structure
struct lmp_test_activate
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_test_control PDU structure
struct lmp_test_ctrl
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Test Scenario
    uint8_t  scenario;
    ///Hopping Mode
    uint8_t  hop;
    ///Tx frequency
    uint8_t  tx_freq;
    ///Rx Frequency
    uint8_t  rx_freq;
    ///Power Control Mode
    uint8_t  pwr_ctrl;
    ///Poll period
    uint8_t  poll_period;
    ///Packet type
    uint8_t  pkt_type;
    ///length of test data
    uint16_t data_len;
};

///LMP_encryption_key_size_mask_req PDU structure
struct lmp_enc_key_size_mask_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
};

///LMP_encryption_key_size_mask_res PDU structure
struct lmp_enc_key_size_mask_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Encryption Key Size Mask
    uint16_t mask;
};

///LMP_set_AFH PDU structure
struct lmp_set_afh
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///AFH Instant
    uint32_t        instant;
    ///AFH Mode
    uint8_t         mode;
    ///AFH channel map
    struct chnl_map map;
};

///LMP_encapsulated_header PDU structure
struct lmp_encaps_hdr
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Encapsulated major type
    uint8_t  maj_type;
    ///Encapsulated minor type
    uint8_t  min_type;
    ///Encapsulated Payload Length
    uint8_t  payl_len;
};

///LMP_encapsulated_payload PDU structure
struct lmp_encaps_payl
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Encapsulated data
    struct byte16 data;
};

///LMP_Simple_Pairing_Confirm PDU structure
struct lmp_sp_cfm
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Commitment Value
    struct byte16 commitment_val ;
};

///LMP_Simple_Pairing_Number PDU structure
struct lmp_sp_nb
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///nonce Value
    struct byte16 nonce;
};

///LMP_DHkey_check PDU structure
struct lmp_dhkey_chk
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Confirmation Value
    struct ltk cfm_val;
};

///LMP_pause_encryption_aes_req PDU structure
struct lmp_pause_enc_aes_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    /// Random Number
    struct ltk rand;
};

/*
 * Extended PDUs parameter structures - Escape 4
 ****************************************************************************************/

///LMP_accepted_ext PDU structure
struct lmp_accepted_ext
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Escape opcode of the original LMP
    uint8_t  orig_esc_opcode;
    ///Extended opcode of the original LMP
    uint8_t  orig_ext_opcode;
};

///LMP_not_accepted_ext PDU structure
struct lmp_not_accepted_ext
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Escape opcode of the original LMP
    uint8_t  orig_esc_opcode;
    ///Extended opcode of the original LMP
    uint8_t  orig_ext_opcode;
    ///Reason
    uint8_t  reason;
};

///LMP_features_req_ext PDU structure
struct lmp_feats_req_ext
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Features page
    uint8_t        page;
    ///Max supported page
    uint8_t        max_page;
    ///Extended features
    struct features ext_feats;
};

///LMP_features_res_ext PDU structure
struct lmp_feats_res_ext
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Features page
    uint8_t        page;
    ///Max supported page
    uint8_t        max_page;
    ///Extended features
    struct features ext_feats;
};

///LMP_clk_adj PDU structure
struct lmp_clk_adj
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Coarse clock adjustment Event ID
    uint8_t  clk_adj_id;
    ///Coarse clock adjustment instant
    uint32_t clk_adj_instant;
    ///Coarse clock adjustment intraslot alignment offset
    int16_t clk_adj_us;
    ///Coarse clock adjustment slot offset
    uint8_t  clk_adj_slots;
    ///Coarse clock adjustment mode (before/after instant)
    uint8_t  clk_adj_mode;
    ///Coarse clock adjustment PDU CLK instant
    uint32_t clk_adj_clk;
};

///LMP_clk_adj_ack PDU structure
struct lmp_clk_adj_ack
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Coarse clock adjustment Event ID
    uint8_t  clk_adj_id;
};

///LMP_clk_adj_req PDU structure
struct lmp_clk_adj_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Coarse clock adjustment intraslot alignment offset
    int16_t clk_adj_us;
    ///Coarse clock adjustment slot offset
    uint8_t  clk_adj_slots;
    ///Corase clock adjustment period
    uint8_t  clk_adj_period;
};

///LMP_packet_type_table_req PDU structure
struct lmp_pkt_type_tbl_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Packet Type table
    uint8_t  pkt_type_tbl;
};

///LMP_eSCO_link_req PDU structure
struct lmp_esco_link_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///eSCO handle
    uint8_t  esco_hdl;
    ///eSCo LT Address
    uint8_t  esco_lt_addr;
    ///timing control flags
    uint8_t  flags;
    ///Desco
    uint8_t  d_esco;
    ///t_esco
    uint8_t  t_esco;
    ///Wesco
    uint8_t  w_esco;
    ///eSCO packet type M2S
    uint8_t  m2s_pkt_type;
    ///eSCO packet type S2M
    uint8_t  s2m_pkt_type;
    ///Packet Length M2S
    uint16_t m2s_pkt_len;
    ///Packet Length S2m
    uint16_t s2m_pkt_len;
    ///Air Mode
    uint8_t  air_mode;
    ///Negotiation state
    uint8_t  negt_st;
};

///LMP_remove_eSCO_link_req PDU structure
struct lmp_rmv_esco_link_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///eSCO handle
    uint8_t  esco_hdl;
    ///Reason
    uint8_t  reason;
};

///LMP_channel_classification_req PDU structure
struct lmp_ch_class_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///AFH reporting mode
    uint8_t  rep_mode;
    ///AFH min interval
    uint16_t min_intv;
    ///AFH max interval
    uint16_t max_intv;
};

///LMP_channel_classification PDU structure
struct lmp_ch_class
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///AFh channel classification
    struct chnl_map ch_class;
};

///LMP_sniff_subrating_req PDU structure
struct lmp_ssr_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Maximum sniff sub-rate
    uint8_t  max_subrate;
    ///Minimum sniff mode timeout
    uint16_t min_to;
    ///Sniff sub-rating instant
    uint32_t inst;
};

///LMP_sniff_subrating_res PDU structure
struct lmp_ssr_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Maximum sniff sub-rate
    uint8_t  max_subrate;
    ///Minimum sniff mode timeout
    uint16_t min_to;
    ///Sniff sub-rating instant
    uint32_t inst;
};

///LMP_pause_encryption_req PDU structure
struct lmp_pause_enc_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

///LMP_resume_encryption_req PDU structure
struct lmp_resume_enc_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

///LMP_IO_capability_req PDU structure
struct lmp_io_cap_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///IO Capabilities
    uint8_t  io_cap;
    /// OOB Authentication data
    uint8_t  oob_auth_data;
    ///Authentication requirements
    uint8_t  auth_req;
};


///LMP_IO_capability_res PDU structure
struct lmp_io_cap_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///IO Capabilities
    uint8_t  io_cap;
    /// OOB Authentication data
    uint8_t  oob_auth_data;
    ///Authentication requirements
    uint8_t  auth_req;
};

///LMP_numeric_comparison_failed PDU structure
struct lmp_num_comparison_fail
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

///LMP_passkey_failed PDU structure
struct lmp_passkey_fail
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

///LMP_oob_failed PDU structure
struct lmp_oob_fail
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

///LMP_keypress_notification PDU structure
struct lmp_keypress_notif
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Notification Type
    uint8_t  type;
};

///LMP_power_control_req PDU structure
struct lmp_pwr_ctrl_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Power adjustment request
    uint8_t pwr_adj;

};

///LMP_power_control_res PDU structure
struct lmp_pwr_ctrl_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
    ///Power adjustment response
    uint8_t pwr_adj;
};

/// LMP_ping_req PDU structure
struct lmp_ping_req
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

/// LMP_ping_res PDU structure
struct lmp_ping_res
{
    ///Opcode (including transaction ID)
    uint8_t  opcode;
    ///Extended opcode
    uint8_t  ext_opcode;
};

/// Union of all the LMP message structures
union lmp_pdu_data
{
    struct lmp_name_req                name_req              ;
    struct lmp_name_res                name_res              ;
    struct lmp_accepted                accepted              ;
    struct lmp_not_accepted            not_accepted          ;
    struct lmp_clk_off_req             clk_off_req           ;
    struct lmp_clk_off_res             clk_off_res           ;
    struct lmp_detach                  detach                ;
    struct lmp_inrand                  inrand                ;
    struct lmp_combkey                 combkey               ;
    struct lmp_unitkey                 unitkey               ;
    struct lmp_aurand                  aurand                ;
    struct lmp_sres                    sres                  ;
    struct lmp_temprand                temprand              ;
    struct lmp_tempkey                 tempkey               ;
    struct lmp_enc_mode_req            enc_mode_req          ;
    struct lmp_enc_key_size_req        enc_key_size_req      ;
    struct lmp_start_enc_req           start_enc_req         ;
    struct lmp_stop_enc_req            stop_enc_req          ;
    struct lmp_switch_req              switch_req            ;
    struct lmp_sniff_req               sniff_req             ;
    struct lmp_unsniff_req             unsniff_req           ;
    struct lmp_incr_pwr_req            incr_pwr_req          ;
    struct lmp_decr_pwr_req            decr_pwr_req          ;
    struct lmp_max_pwr                 max_pwr               ;
    struct lmp_min_pwr                 min_pwr               ;
    struct lmp_auto_rate               auto_rate             ;
    struct lmp_pref_rate               pref_rate             ;
    struct lmp_ver_req                 ver_req               ;
    struct lmp_ver_res                 ver_res               ;
    struct lmp_feats_req               feats_req             ;
    struct lmp_feats_res               feats_res             ;
    struct lmp_clk_adj                 clk_adj               ;
    struct lmp_clk_adj_ack             clk_adj_ack           ;
    struct lmp_clk_adj_req             clk_adj_req           ;
    struct lmp_qos                     qos                   ;
    struct lmp_qos_req                 qos_req               ;
    struct lmp_sco_link_req            sco_link_req          ;
    struct lmp_rmv_sco_link_req        rmv_sco_link_req      ;
    struct lmp_max_slot                max_slot              ;
    struct lmp_max_slot_req            max_slot_req          ;
    struct lmp_timing_accu_req         timing_accu_req       ;
    struct lmp_timing_accu_res         timing_accu_res       ;
    struct lmp_setup_cmp               setup_cmp             ;
    struct lmp_use_semi_perm_key       use_semi_perm_key     ;
    struct lmp_host_con_req            host_con_req          ;
    struct lmp_slot_off                slot_off              ;
    struct lmp_page_mode_req           page_mode_req         ;
    struct lmp_page_scan_mode_req      page_scan_mode_req    ;
    struct lmp_supv_to                 supv_to               ;
    struct lmp_test_activate           test_activate         ;
    struct lmp_test_ctrl               test_ctrl             ;
    struct lmp_enc_key_size_mask_req   enc_key_size_mask_req ;
    struct lmp_enc_key_size_mask_res   enc_key_size_mask_res ;
    struct lmp_set_afh                 set_afh               ;
    struct lmp_encaps_hdr              encaps_hdr            ;
    struct lmp_encaps_payl             encaps_payl           ;
    struct lmp_sp_cfm                  sp_cfm                ;
    struct lmp_sp_nb                   sp_nb                 ;
    struct lmp_dhkey_chk               dhkey_chk             ;
    struct lmp_accepted_ext            accepted_ext          ;
    struct lmp_not_accepted_ext        not_accepted_ext      ;
    struct lmp_feats_req_ext           feats_req_ext         ;
    struct lmp_feats_res_ext           feats_res_ext         ;
    struct lmp_pkt_type_tbl_req        pkt_type_tbl_req      ;
    struct lmp_esco_link_req           esco_link_req         ;
    struct lmp_rmv_esco_link_req       rmv_esco_link_req     ;
    struct lmp_ch_class_req            ch_class_req          ;
    struct lmp_ch_class                ch_class              ;
    struct lmp_ssr_req                 ssr_req               ;
    struct lmp_ssr_res                 ssr_res               ;
    struct lmp_pause_enc_req           pause_enc_req         ;
    struct lmp_resume_enc_req          resume_enc_req        ;
    struct lmp_io_cap_req              io_cap_req            ;
    struct lmp_io_cap_res              io_cap_res            ;
    struct lmp_num_comparison_fail     num_comparison_fail   ;
    struct lmp_passkey_fail            passkey_fail          ;
    struct lmp_oob_fail                oob_fail              ;
    struct lmp_keypress_notif          keypress_notif        ;
    struct lmp_pwr_ctrl_req            pwr_ctrl_req          ;
    struct lmp_pwr_ctrl_res            pwr_ctrl_res          ;
    struct lmp_ping_req                ping_req              ;
    struct lmp_ping_res                ping_res              ;
};


/// @} CO_BT
#endif // CO_LMP_H_
