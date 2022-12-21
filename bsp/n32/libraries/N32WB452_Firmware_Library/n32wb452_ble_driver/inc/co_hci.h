/**
 ****************************************************************************************
 *
 * @file co_hci.h
 *
 * @brief This file contains the HCI Bluetooth defines, enumerations and structures
 *        definitions for use by all modules in RW stack.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 ****************************************************************************************
 */

#ifndef CO_HCI_H_
#define CO_HCI_H_

/**
 ****************************************************************************************
 * @addtogroup COMMON Common SW Block
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdbool.h>       // standard boolean definitions
#include <stddef.h>        // standard definitions
#include <stdint.h>        // standard integer definitions

#include "rwip_config.h"   // IP configuration
#include "ble_arch.h" 
//#include "compiler.h"      // compiler definitions

/*
 * DEFINES
 ****************************************************************************************
 */


/******************************************************************************************/
/* -------------------------   H4TL DEFINITIONS Part IV.A    -----------------------------*/
/******************************************************************************************/

///HCI Transport Header length - change if different transport
#define HCI_TRANSPORT_HDR_LEN                       0x01

///UART header: command message type
#define HCI_CMD_MSG_TYPE                            0x01

///UART header: ACL data message type
#define HCI_ACL_MSG_TYPE                            0x02

///UART header: Synchronous data message type
#define HCI_SYNC_MSG_TYPE                           0x03

///UART header: event message type
#define HCI_EVT_MSG_TYPE                            0x04

///UART header: event message type
#define HCI_TCI_MSG_TYPE                            0xFF

/******************************************************************************************/
/* -------------------------   HCI DEFINITIONS Part II.E     -----------------------------*/
/******************************************************************************************/

///HCI Command Opcode byte length
#define HCI_CMD_OPCODE_LEN         (0x02)

///HCI Event code byte length
#define HCI_EVT_CODE_LEN           (0x01)

///HCI Command/Event parameter length field byte length
#define HCI_CMDEVT_PARLEN_LEN      (0x01)

///HCI Command header length
#define HCI_CMD_HDR_LEN            (HCI_CMD_OPCODE_LEN + HCI_CMDEVT_PARLEN_LEN)

///HCI Event header length
#define HCI_EVT_HDR_LEN            (HCI_EVT_CODE_LEN + HCI_CMDEVT_PARLEN_LEN)

/// HCI ACL header: handle and flags decoding
#define HCI_ACL_HDR_HDL_FLAGS_POS  (0)
#define HCI_ACL_HDR_HDL_FLAGS_LEN  (2)
#define HCI_ACL_HDR_HDL_POS        (0)
#define HCI_ACL_HDR_HDL_MASK       (0x0FFF)
#define HCI_ACL_HDR_PB_FLAG_POS    (12)
#define HCI_ACL_HDR_PB_FLAG_MASK   (0x3000)
#define HCI_ACL_HDR_BC_FLAG_POS    (14)
#define HCI_ACL_HDR_BC_FLAG_MASK   (0xC000)
#define HCI_ACL_HDR_DATA_FLAG_POS  (12)
#define HCI_ACL_HDR_DATA_FLAG_MASK (0xF000)

/// HCI ACL header: data length field length
#define HCI_ACL_HDR_DATA_LEN_POS   (HCI_ACL_HDR_HDL_FLAGS_LEN)
#define HCI_ACL_HDR_DATA_LEN_LEN   (2)

///HCI ACL data packet header length
#define HCI_ACL_HDR_LEN            (HCI_ACL_HDR_HDL_FLAGS_LEN + HCI_ACL_HDR_DATA_LEN_LEN)

/// HCI Synchronous header: handle and flags decoding
#define HCI_SYNC_HDR_HDL_FLAGS_POS  (0)
#define HCI_SYNC_HDR_HDL_FLAGS_LEN  (2)
#define HCI_SYNC_HDR_HDL_POS        (0)
#define HCI_SYNC_HDR_HDL_MASK       (0x0FFF)
#define HCI_SYNC_HDR_PSF_FLAG_POS   (12)
#define HCI_SYNC_HDR_PSF_FLAG_MASK  (0x3000)
#define HCI_SYNC_HDR_RES_FLAG_POS   (14)
#define HCI_SYNC_HDR_RES_FLAG_MASK  (0xC000)
#define HCI_SYNC_HDR_DATA_FLAG_POS  (12)
#define HCI_SYNC_HDR_DATA_FLAG_MASK (0xF000)

/// HCI Synchronous header: data length field length
#define HCI_SYNC_HDR_DATA_LEN_POS   (HCI_SYNC_HDR_HDL_FLAGS_LEN)
#define HCI_SYNC_HDR_DATA_LEN_LEN   (1)
#define HCI_SYNC_MAX_DATA_SIZE      (255)

///HCI sync data packet header length
#define HCI_SYNC_HDR_LEN           (HCI_SYNC_HDR_HDL_FLAGS_LEN + HCI_SYNC_HDR_DATA_LEN_LEN)

///HCI Command Complete Event minimum parameter length: 1(nb_pk)+2(opcode)
#define HCI_CCEVT_HDR_PARLEN       (0x03)

///HCI Command Complete Event header length:1(code)+1(len)+1(pk)+2(opcode)
#define HCI_CCEVT_HDR_LEN          (HCI_EVT_HDR_LEN + HCI_CCEVT_HDR_PARLEN)

///HCI Basic Command Complete Event packet length
#define HCI_CCEVT_BASIC_LEN        (HCI_CCEVT_HDR_LEN + 1)

///HCI Command Status Event parameter length - constant
#define HCI_CSEVT_PARLEN           (0x04)

///HCI Command Status Event length:1(code)+1(len)+1(st)+1(pk)+2(opcode)
#define HCI_CSEVT_LEN              (HCI_EVT_HDR_LEN + HCI_CSEVT_PARLEN)

///HCI Reset Command parameter length
#define HCI_RESET_CMD_PARLEN       0

/// Default return parameter length for HCI Command Complete Event
#define HCI_CCEVT_BASIC_RETPAR_LEN 1

/// Max HCI commands param size
#define HCI_MAX_CMD_PARAM_SIZE    255

/// Macro to extract OCF from OPCODE
#define HCI_OP2OCF(opcode)        ((opcode) & 0x03FF)

/// Macro to extract OGF from OPCODE
#define HCI_OP2OGF(opcode)        ((opcode) >> 10 & 0x003F)

/// Macro to create OPCODE from OGF and OCF
#define HCI_OPCODE(ocf, ogf)      (((ogf) << 10) | ocf)

/**************************************************************************************
 **************                       HCI COMMANDS                     ****************
 **************************************************************************************/

///HCI enumeration of possible Command OGF values.
enum
{
    ///HCI Link Control Commands Group OGF code
    LK_CNTL_OGF = 0x01,
    ///HCI Link Policy Commands Group OGF code
    LK_POL_OGF,
    ///HCI Controller and Baseband Commands Group OGF code
    CNTLR_BB_OGF,
    ///HCI Information Parameters Commands Group OGF code
    INFO_PAR_OGF,
    ///HCI Status Commands Group OGF code
    STAT_PAR_OGF,
    ///HCI Test Commands Group OGF code
    TEST_OGF,
    ///HCI Low Energy Commands Group OGF code
    LE_CNTLR_OGF=0x08,
    ///HCI Vendor Specific Group OGF code
    VS_OGF = 0x3F,
    MAX_OGF
};


///Commands Opcodes: OGF(6b) | OCF(10b)
/* Some Abbreviation used in names:
 *  - LK   = Link Key
 *  - RD   = Read
 *  - WR   = Write
 *  - REM  = Remote
 *  - STG  = Settings
 *  - CON  = Connection
 *  - CHG  = Change
 *  - DFT  = Default
 *  - PER  = Periodic
 */

///HCI enumeration of possible Command OP Codes.
enum hci_opcode
{
    HCI_NO_OPERATION_CMD_OPCODE                     = 0x0000,

    //Link Control Commands
    HCI_INQ_CMD_OPCODE                              = 0x0401,
    HCI_INQ_CANCEL_CMD_OPCODE                       = 0x0402,
    HCI_PER_INQ_MODE_CMD_OPCODE                     = 0x0403,
    HCI_EXIT_PER_INQ_MODE_CMD_OPCODE                = 0x0404,
    HCI_CREATE_CON_CMD_OPCODE                       = 0x0405,
    HCI_DISCONNECT_CMD_OPCODE                       = 0x0406,
    HCI_CREATE_CON_CANCEL_CMD_OPCODE                = 0x0408,
    HCI_ACCEPT_CON_REQ_CMD_OPCODE                   = 0x0409,
    HCI_REJECT_CON_REQ_CMD_OPCODE                   = 0x040A,
    HCI_LK_REQ_REPLY_CMD_OPCODE                     = 0x040B,
    HCI_LK_REQ_NEG_REPLY_CMD_OPCODE                 = 0x040C,
    HCI_PIN_CODE_REQ_REPLY_CMD_OPCODE               = 0x040D,
    HCI_PIN_CODE_REQ_NEG_REPLY_CMD_OPCODE           = 0x040E,
    HCI_CHG_CON_PKT_TYPE_CMD_OPCODE                 = 0x040F,
    HCI_AUTH_REQ_CMD_OPCODE                         = 0x0411,
    HCI_SET_CON_ENC_CMD_OPCODE                      = 0x0413,
    HCI_CHG_CON_LK_CMD_OPCODE                       = 0x0415,
    HCI_MASTER_LK_CMD_OPCODE                        = 0x0417,
    HCI_REM_NAME_REQ_CMD_OPCODE                     = 0x0419,
    HCI_REM_NAME_REQ_CANCEL_CMD_OPCODE              = 0x041A,
    HCI_RD_REM_SUPP_FEATS_CMD_OPCODE                = 0x041B,
    HCI_RD_REM_EXT_FEATS_CMD_OPCODE                 = 0x041C,
    HCI_RD_REM_VER_INFO_CMD_OPCODE                  = 0x041D,
    HCI_RD_CLK_OFF_CMD_OPCODE                       = 0x041F,
    HCI_RD_LMP_HDL_CMD_OPCODE                       = 0x0420,
    HCI_SETUP_SYNC_CON_CMD_OPCODE                   = 0x0428,
    HCI_ACCEPT_SYNC_CON_REQ_CMD_OPCODE              = 0x0429,
    HCI_REJECT_SYNC_CON_REQ_CMD_OPCODE              = 0x042A,
    HCI_IO_CAP_REQ_REPLY_CMD_OPCODE                 = 0x042B,
    HCI_USER_CFM_REQ_REPLY_CMD_OPCODE               = 0x042C,
    HCI_USER_CFM_REQ_NEG_REPLY_CMD_OPCODE           = 0x042D,
    HCI_USER_PASSKEY_REQ_REPLY_CMD_OPCODE           = 0x042E,
    HCI_USER_PASSKEY_REQ_NEG_REPLY_CMD_OPCODE       = 0x042F,
    HCI_REM_OOB_DATA_REQ_REPLY_CMD_OPCODE           = 0x0430,
    HCI_REM_OOB_DATA_REQ_NEG_REPLY_CMD_OPCODE       = 0x0433,
    HCI_IO_CAP_REQ_NEG_REPLY_CMD_OPCODE             = 0x0434,
    HCI_ENH_SETUP_SYNC_CON_CMD_OPCODE               = 0x043D,
    HCI_ENH_ACCEPT_SYNC_CON_CMD_OPCODE              = 0x043E,
    HCI_TRUNC_PAGE_CMD_OPCODE                       = 0x043F,
    HCI_TRUNC_PAGE_CAN_CMD_OPCODE                   = 0x0440,
    HCI_SET_CON_SLV_BCST_CMD_OPCODE                 = 0x0441,
    HCI_SET_CON_SLV_BCST_REC_CMD_OPCODE             = 0x0442,
    HCI_START_SYNC_TRAIN_CMD_OPCODE                 = 0x0443,
    HCI_REC_SYNC_TRAIN_CMD_OPCODE                   = 0x0444,
    HCI_REM_OOB_EXT_DATA_REQ_REPLY_CMD_OPCODE       = 0x0445,

    //Link Policy Commands
    HCI_HOLD_MODE_CMD_OPCODE                        = 0x0801,
    HCI_SNIFF_MODE_CMD_OPCODE                       = 0x0803,
    HCI_EXIT_SNIFF_MODE_CMD_OPCODE                  = 0x0804,
    HCI_PARK_STATE_CMD_OPCODE                       = 0x0805,
    HCI_EXIT_PARK_STATE_CMD_OPCODE                  = 0x0806,
    HCI_QOS_SETUP_CMD_OPCODE                        = 0x0807,
    HCI_ROLE_DISCOVERY_CMD_OPCODE                   = 0x0809,
    HCI_SWITCH_ROLE_CMD_OPCODE                      = 0x080B,
    HCI_RD_LINK_POL_STG_CMD_OPCODE                  = 0x080C,
    HCI_WR_LINK_POL_STG_CMD_OPCODE                  = 0x080D,
    HCI_RD_DFT_LINK_POL_STG_CMD_OPCODE              = 0x080E,
    HCI_WR_DFT_LINK_POL_STG_CMD_OPCODE              = 0x080F,
    HCI_FLOW_SPEC_CMD_OPCODE                        = 0x0810,
    HCI_SNIFF_SUB_CMD_OPCODE                        = 0x0811,

    //Controller and Baseband Commands
    HCI_SET_EVT_MASK_CMD_OPCODE                     = 0x0C01,
    HCI_RESET_CMD_OPCODE                            = 0x0C03,
    HCI_SET_EVT_FILTER_CMD_OPCODE                   = 0x0C05,
    HCI_FLUSH_CMD_OPCODE                            = 0x0C08,
    HCI_RD_PIN_TYPE_CMD_OPCODE                      = 0x0C09,
    HCI_WR_PIN_TYPE_CMD_OPCODE                      = 0x0C0A,
    HCI_CREATE_NEW_UNIT_KEY_CMD_OPCODE              = 0x0C0B,
    HCI_RD_STORED_LK_CMD_OPCODE                     = 0x0C0D,
    HCI_WR_STORED_LK_CMD_OPCODE                     = 0x0C11,
    HCI_DEL_STORED_LK_CMD_OPCODE                    = 0x0C12,
    HCI_WR_LOCAL_NAME_CMD_OPCODE                    = 0x0C13,
    HCI_RD_LOCAL_NAME_CMD_OPCODE                    = 0x0C14,
    HCI_RD_CON_ACCEPT_TO_CMD_OPCODE                 = 0x0C15,
    HCI_WR_CON_ACCEPT_TO_CMD_OPCODE                 = 0x0C16,
    HCI_RD_PAGE_TO_CMD_OPCODE                       = 0x0C17,
    HCI_WR_PAGE_TO_CMD_OPCODE                       = 0x0C18,
    HCI_RD_SCAN_EN_CMD_OPCODE                       = 0x0C19,
    HCI_WR_SCAN_EN_CMD_OPCODE                       = 0x0C1A,
    HCI_RD_PAGE_SCAN_ACT_CMD_OPCODE                 = 0x0C1B,
    HCI_WR_PAGE_SCAN_ACT_CMD_OPCODE                 = 0x0C1C,
    HCI_RD_INQ_SCAN_ACT_CMD_OPCODE                  = 0x0C1D,
    HCI_WR_INQ_SCAN_ACT_CMD_OPCODE                  = 0x0C1E,
    HCI_RD_AUTH_EN_CMD_OPCODE                       = 0x0C1F,
    HCI_WR_AUTH_EN_CMD_OPCODE                       = 0x0C20,
    HCI_RD_CLASS_OF_DEV_CMD_OPCODE                  = 0x0C23,
    HCI_WR_CLASS_OF_DEV_CMD_OPCODE                  = 0x0C24,
    HCI_RD_VOICE_STG_CMD_OPCODE                     = 0x0C25,
    HCI_WR_VOICE_STG_CMD_OPCODE                     = 0x0C26,
    HCI_RD_AUTO_FLUSH_TO_CMD_OPCODE                 = 0x0C27,
    HCI_WR_AUTO_FLUSH_TO_CMD_OPCODE                 = 0x0C28,
    HCI_RD_NB_BDCST_RETX_CMD_OPCODE                 = 0x0C29,
    HCI_WR_NB_BDCST_RETX_CMD_OPCODE                 = 0x0C2A,
    HCI_RD_HOLD_MODE_ACTIVITY_CMD_OPCODE            = 0x0C2B,
    HCI_WR_HOLD_MODE_ACTIVITY_CMD_OPCODE            = 0x0C2C,
    HCI_RD_TX_PWR_LVL_CMD_OPCODE                    = 0x0C2D,
    HCI_RD_SYNC_FLOW_CTRL_EN_CMD_OPCODE             = 0x0C2E,
    HCI_WR_SYNC_FLOW_CTRL_EN_CMD_OPCODE             = 0x0C2F,
    HCI_SET_CTRL_TO_HOST_FLOW_CTRL_CMD_OPCODE       = 0x0C31,
    HCI_HOST_BUF_SIZE_CMD_OPCODE                    = 0x0C33,
    HCI_HOST_NB_CMP_PKTS_CMD_OPCODE                 = 0x0C35,
    HCI_RD_LINK_SUPV_TO_CMD_OPCODE                  = 0x0C36,
    HCI_WR_LINK_SUPV_TO_CMD_OPCODE                  = 0x0C37,
    HCI_RD_NB_SUPP_IAC_CMD_OPCODE                   = 0x0C38,
    HCI_RD_CURR_IAC_LAP_CMD_OPCODE                  = 0x0C39,
    HCI_WR_CURR_IAC_LAP_CMD_OPCODE                  = 0x0C3A,
    HCI_SET_AFH_HOST_CH_CLASS_CMD_OPCODE            = 0x0C3F,
    HCI_RD_INQ_SCAN_TYPE_CMD_OPCODE                 = 0x0C42,
    HCI_WR_INQ_SCAN_TYPE_CMD_OPCODE                 = 0x0C43,
    HCI_RD_INQ_MODE_CMD_OPCODE                      = 0x0C44,
    HCI_WR_INQ_MODE_CMD_OPCODE                      = 0x0C45,
    HCI_RD_PAGE_SCAN_TYPE_CMD_OPCODE                = 0x0C46,
    HCI_WR_PAGE_SCAN_TYPE_CMD_OPCODE                = 0x0C47,
    HCI_RD_AFH_CH_ASSESS_MODE_CMD_OPCODE            = 0x0C48,
    HCI_WR_AFH_CH_ASSESS_MODE_CMD_OPCODE            = 0x0C49,
    HCI_RD_EXT_INQ_RSP_CMD_OPCODE                   = 0x0C51,
    HCI_WR_EXT_INQ_RSP_CMD_OPCODE                   = 0x0C52,
    HCI_REFRESH_ENC_KEY_CMD_OPCODE                  = 0x0C53,
    HCI_RD_SP_MODE_CMD_OPCODE                       = 0x0C55,
    HCI_WR_SP_MODE_CMD_OPCODE                       = 0x0C56,
    HCI_RD_LOC_OOB_DATA_CMD_OPCODE                  = 0x0C57,
    HCI_RD_INQ_RSP_TX_PWR_LVL_CMD_OPCODE            = 0x0C58,
    HCI_WR_INQ_TX_PWR_LVL_CMD_OPCODE                = 0x0C59,
    HCI_RD_DFT_ERR_DATA_REP_CMD_OPCODE              = 0x0C5A,
    HCI_WR_DFT_ERR_DATA_REP_CMD_OPCODE              = 0x0C5B,
    HCI_ENH_FLUSH_CMD_OPCODE                        = 0x0C5F,
    HCI_SEND_KEYPRESS_NOTIF_CMD_OPCODE              = 0x0C60,
    HCI_SET_EVT_MASK_PAGE_2_CMD_OPCODE              = 0x0C63,
    HCI_RD_FLOW_CNTL_MODE_CMD_OPCODE                = 0x0C66,
    HCI_WR_FLOW_CNTL_MODE_CMD_OPCODE                = 0x0C67,
    HCI_RD_ENH_TX_PWR_LVL_CMD_OPCODE                = 0x0C68,
    HCI_RD_LE_HOST_SUPP_CMD_OPCODE                  = 0x0C6C,
    HCI_WR_LE_HOST_SUPP_CMD_OPCODE                  = 0x0C6D,
    HCI_SET_MWS_CHANNEL_PARAMS_CMD_OPCODE           = 0x0C6E,
    HCI_SET_EXTERNAL_FRAME_CONFIG_CMD_OPCODE        = 0x0C6F,
    HCI_SET_MWS_SIGNALING_CMD_OPCODE                = 0x0C70,
    HCI_SET_MWS_TRANSPORT_LAYER_CMD_OPCODE          = 0x0C71,
    HCI_SET_MWS_SCAN_FREQ_TABLE_CMD_OPCODE          = 0x0C72,
    HCI_SET_MWS_PATTERN_CONFIG_CMD_OPCODE           = 0x0C73,
    HCI_SET_RES_LT_ADDR_CMD_OPCODE                  = 0x0C74,
    HCI_DEL_RES_LT_ADDR_CMD_OPCODE                  = 0x0C75,
    HCI_SET_CON_SLV_BCST_DATA_CMD_OPCODE            = 0x0C76,
    HCI_RD_SYNC_TRAIN_PARAM_CMD_OPCODE              = 0x0C77,
    HCI_WR_SYNC_TRAIN_PARAM_CMD_OPCODE              = 0x0C78,
    HCI_RD_SEC_CON_HOST_SUPP_CMD_OPCODE             = 0x0C79,
    HCI_WR_SEC_CON_HOST_SUPP_CMD_OPCODE             = 0x0C7A,
    HCI_RD_AUTH_PAYL_TO_CMD_OPCODE                  = 0x0C7B,
    HCI_WR_AUTH_PAYL_TO_CMD_OPCODE                  = 0x0C7C,
    HCI_RD_LOC_OOB_EXT_DATA_CMD_OPCODE              = 0x0C7D,
    HCI_RD_EXT_PAGE_TO_CMD_OPCODE                   = 0x0C7E,
    HCI_WR_EXT_PAGE_TO_CMD_OPCODE                   = 0x0C7F,
    HCI_RD_EXT_INQ_LEN_CMD_OPCODE                   = 0x0C80,
    HCI_WR_EXT_INQ_LEN_CMD_OPCODE                   = 0x0C81,

    //Info Params
    HCI_RD_LOCAL_VER_INFO_CMD_OPCODE                = 0x1001,
    HCI_RD_LOCAL_SUPP_CMDS_CMD_OPCODE               = 0x1002,
    HCI_RD_LOCAL_SUPP_FEATS_CMD_OPCODE              = 0x1003,
    HCI_RD_LOCAL_EXT_FEATS_CMD_OPCODE               = 0x1004,
    HCI_RD_BUFF_SIZE_CMD_OPCODE                     = 0x1005,
    HCI_RD_BD_ADDR_CMD_OPCODE                       = 0x1009,
    HCI_RD_LOCAL_SUPP_CODECS_CMD_OPCODE             = 0x100B,

    //Status Params
    HCI_RD_FAIL_CONTACT_CNT_CMD_OPCODE              = 0x1401,
    HCI_RST_FAIL_CONTACT_CNT_CMD_OPCODE             = 0x1402,
    HCI_RD_LINK_QUAL_CMD_OPCODE                     = 0x1403,
    HCI_RD_RSSI_CMD_OPCODE                          = 0x1405,
    HCI_RD_AFH_CH_MAP_CMD_OPCODE                    = 0x1406,
    HCI_RD_CLK_CMD_OPCODE                           = 0x1407,
    HCI_RD_ENC_KEY_SIZE_CMD_OPCODE                  = 0x1408,
    HCI_GET_MWS_TRANSPORT_LAYER_CONFIG_CMD_OPCODE   = 0x140C,

    //Testing Commands
    HCI_RD_LOOPBACK_MODE_CMD_OPCODE                 = 0x1801,
    HCI_WR_LOOPBACK_MODE_CMD_OPCODE                 = 0x1802,
    HCI_EN_DUT_MODE_CMD_OPCODE                      = 0x1803,
    HCI_WR_SP_DBG_MODE_CMD_OPCODE                   = 0x1804,
    HCI_WR_SEC_CON_TEST_MODE_CMD_OPCODE             = 0x180A,

    /// LE Commands Opcodes
    HCI_LE_SET_EVT_MASK_CMD_OPCODE                  = 0x2001,
    HCI_LE_RD_BUFF_SIZE_CMD_OPCODE                  = 0x2002,
    HCI_LE_RD_LOCAL_SUPP_FEATS_CMD_OPCODE           = 0x2003,
    HCI_LE_SET_RAND_ADDR_CMD_OPCODE                 = 0x2005,
    HCI_LE_SET_ADV_PARAM_CMD_OPCODE                 = 0x2006,
    HCI_LE_RD_ADV_CHNL_TX_PW_CMD_OPCODE             = 0x2007,
    HCI_LE_SET_ADV_DATA_CMD_OPCODE                  = 0x2008,
    HCI_LE_SET_SCAN_RSP_DATA_CMD_OPCODE             = 0x2009,
    HCI_LE_SET_ADV_EN_CMD_OPCODE                    = 0x200A,
    HCI_LE_SET_SCAN_PARAM_CMD_OPCODE                = 0x200B,
    HCI_LE_SET_SCAN_EN_CMD_OPCODE                   = 0x200C,
    HCI_LE_CREATE_CON_CMD_OPCODE                    = 0x200D,
    HCI_LE_CREATE_CON_CANCEL_CMD_OPCODE             = 0x200E,
    HCI_LE_RD_WLST_SIZE_CMD_OPCODE                  = 0x200F,
    HCI_LE_CLEAR_WLST_CMD_OPCODE                    = 0x2010,
    HCI_LE_ADD_DEV_TO_WLST_CMD_OPCODE               = 0x2011,
    HCI_LE_RMV_DEV_FROM_WLST_CMD_OPCODE             = 0x2012,
    HCI_LE_CON_UPDATE_CMD_OPCODE                    = 0x2013,
    HCI_LE_SET_HOST_CH_CLASS_CMD_OPCODE             = 0x2014,
    HCI_LE_RD_CHNL_MAP_CMD_OPCODE                   = 0x2015,
    HCI_LE_RD_REM_USED_FEATS_CMD_OPCODE             = 0x2016,
    HCI_LE_ENC_CMD_OPCODE                           = 0x2017,
    HCI_LE_RAND_CMD_OPCODE                          = 0x2018,
    HCI_LE_START_ENC_CMD_OPCODE                     = 0x2019,
    HCI_LE_LTK_REQ_REPLY_CMD_OPCODE                 = 0x201A,
    HCI_LE_LTK_REQ_NEG_REPLY_CMD_OPCODE             = 0x201B,
    HCI_LE_RD_SUPP_STATES_CMD_OPCODE                = 0x201C,
    HCI_LE_RX_TEST_CMD_OPCODE                       = 0x201D,
    HCI_LE_TX_TEST_CMD_OPCODE                       = 0x201E,
    HCI_LE_TEST_END_CMD_OPCODE                      = 0x201F,
#if !(BLE_QUALIF)
    HCI_LE_REM_CON_PARAM_REQ_REPLY_CMD_OPCODE       = 0x2020,
    HCI_LE_REM_CON_PARAM_REQ_NEG_REPLY_CMD_OPCODE   = 0x2021,
    HCI_LE_SET_DATA_LEN_CMD_OPCODE                  = 0x2022,
    HCI_LE_RD_SUGGTED_DFT_DATA_LEN_CMD_OPCODE       = 0x2023,
    HCI_LE_WR_SUGGTED_DFT_DATA_LEN_CMD_OPCODE       = 0x2024,
    HCI_LE_RD_LOC_P256_PUB_KEY_CMD_OPCODE           = 0x2025,
    HCI_LE_GEN_DHKEY_CMD_OPCODE                     = 0x2026,
    HCI_LE_ADD_DEV_TO_RSLV_LIST_CMD_OPCODE          = 0x2027,
    HCI_LE_RMV_DEV_FROM_RSLV_LIST_CMD_OPCODE        = 0x2028,
    HCI_LE_CLEAR_RSLV_LIST_CMD_OPCODE               = 0x2029,
    HCI_LE_RD_RSLV_LIST_SIZE_CMD_OPCODE             = 0x202A,
    HCI_LE_RD_PEER_RSLV_ADDR_CMD_OPCODE             = 0x202B,
    HCI_LE_RD_LOC_RSLV_ADDR_CMD_OPCODE              = 0x202C,
    HCI_LE_SET_ADDR_RESOL_EN_CMD_OPCODE             = 0x202D,
    HCI_LE_SET_RSLV_PRIV_ADDR_TO_CMD_OPCODE         = 0x202E,
    HCI_LE_RD_MAX_DATA_LEN_CMD_OPCODE               = 0x202F,
#endif

    ///Debug commands - OGF = 0x3F (spec)
    HCI_DBG_RD_MEM_CMD_OPCODE                       = 0xFC01,
    HCI_DBG_WR_MEM_CMD_OPCODE                       = 0xFC02,
    HCI_DBG_DEL_PAR_CMD_OPCODE                      = 0xFC03,
    HCI_DBG_ID_FLASH_CMD_OPCODE                     = 0xFC05,
    HCI_DBG_ER_FLASH_CMD_OPCODE                     = 0xFC06,
    HCI_DBG_WR_FLASH_CMD_OPCODE                     = 0xFC07,
    HCI_DBG_RD_FLASH_CMD_OPCODE                     = 0xFC08,
    HCI_DBG_RD_PAR_CMD_OPCODE                       = 0xFC09,
    HCI_DBG_WR_PAR_CMD_OPCODE                       = 0xFC0A,
    HCI_DBG_WLAN_COEX_CMD_OPCODE                    = 0xFC0B,
    HCI_DBG_WLAN_COEXTST_SCEN_CMD_OPCODE            = 0xFC0D,
    HCI_DBG_BT_SEND_LMP_CMD_OPCODE                  = 0xFC0E,
    HCI_DBG_SET_LOCAL_CLOCK_CMD_OPCODE              = 0xFC0F,
    HCI_DBG_RD_KE_STATS_CMD_OPCODE                  = 0xFC10,
    HCI_DBG_PLF_RESET_CMD_OPCODE                    = 0xFC11,
    HCI_DBG_RD_MEM_INFO_CMD_OPCODE                  = 0xFC12,
    HCI_DBG_HW_REG_RD_CMD_OPCODE                    = 0xFC30,
    HCI_DBG_HW_REG_WR_CMD_OPCODE                    = 0xFC31,
    HCI_DBG_SET_BD_ADDR_CMD_OPCODE                  = 0xFC32,
    HCI_DBG_SET_TYPE_PUB_CMD_OPCODE                 = 0xFC33,
    HCI_DBG_SET_TYPE_RAND_CMD_OPCODE                = 0xFC34,
    HCI_DBG_SET_CRC_CMD_OPCODE                      = 0xFC35,
    HCI_DBG_LLCP_DISCARD_CMD_OPCODE                 = 0xFC36,
    HCI_DBG_RESET_RX_CNT_CMD_OPCODE                 = 0xFC37,
    HCI_DBG_RESET_TX_CNT_CMD_OPCODE                 = 0xFC38,
    HCI_DBG_RF_REG_RD_CMD_OPCODE                    = 0xFC39,
    HCI_DBG_RF_REG_WR_CMD_OPCODE                    = 0xFC3A,
    HCI_DBG_SET_TX_PW_CMD_OPCODE                    = 0xFC3B,
    HCI_DBG_RF_SWITCH_CLK_CMD_OPCODE                = 0xFC3C,
    HCI_DBG_RF_WR_DATA_TX_CMD_OPCODE                = 0xFC3D,
    HCI_DBG_RF_RD_DATA_RX_CMD_OPCODE                = 0xFC3E,
    HCI_DBG_RF_CNTL_TX_CMD_OPCODE                   = 0xFC3F,
    HCI_DBG_RF_SYNC_P_CNTL_CMD_OPCODE               = 0xFC40,
    HCI_TESTER_SET_LE_PARAMS_CMD_OPCODE             = 0xFC40,
    HCI_DBG_WR_DLE_DFT_VALUE_CMD_OPCODE             = 0xFC41,
    HCI_DBG_BLE_TST_LLCP_PT_EN_CMD_OPCODE           = 0xFC42,
    HCI_DBG_BLE_TST_SEND_LLCP_CMD_OPCODE            = 0xFC43,
    HCI_VS_AUDIO_ALLOCATE_CMD_OPCODE                = 0xFC50,
    HCI_VS_AUDIO_CONFIGURE_CMD_OPCODE               = 0xFC51,
    HCI_VS_AUDIO_SET_MODE_CMD_OPCODE                = 0xFC52,
    HCI_VS_AUDIO_RESET_CMD_OPCODE                   = 0xFC53,
    HCI_VS_AUDIO_SET_POINTER_CMD_OPCODE             = 0xFC54,
    HCI_VS_AUDIO_GET_BUFFER_RANGE_CMD_OPCODE        = 0xFC55,

    #if (RW_DEBUG && BT_EMB_PRESENT)
    HCI_DBG_BT_DISCARD_LMP_EN_CMD_OPCODE            = 0xFC44,
    #endif //RW_DEBUG && BT_EMB_PRESENT

    HCI_DBG_MWS_COEX_CMD_OPCODE                     = 0xFC45,
    HCI_DBG_MWS_COEXTST_SCEN_CMD_OPCODE             = 0xFC46,

    #if CRYPTO_UT
    HCI_DBG_TEST_CRYPTO_FUNC_CMD_OPCODE             = 0xFC60,
    #endif //CRYPTO_UT
};

/**************************************************************************************
 **************                        HCI EVENTS                      ****************
 **************************************************************************************/

///Event Codes
enum hci_evt_code
{
    HCI_INQ_CMP_EVT_CODE                           = 0x01,
    HCI_INQ_RES_EVT_CODE                           = 0x02,
    HCI_CON_CMP_EVT_CODE                           = 0x03,
    HCI_CON_REQ_EVT_CODE                           = 0x04,
    HCI_DISC_CMP_EVT_CODE                          = 0x05,
    HCI_AUTH_CMP_EVT_CODE                          = 0x06,
    HCI_REM_NAME_REQ_CMP_EVT_CODE                  = 0x07,
    HCI_ENC_CHG_EVT_CODE                           = 0x08,
    HCI_CHG_CON_LK_CMP_EVT_CODE                    = 0x09,
    HCI_MASTER_LK_CMP_EVT_CODE                     = 0x0A,
    HCI_RD_REM_SUPP_FEATS_CMP_EVT_CODE             = 0x0B,
    HCI_RD_REM_VER_INFO_CMP_EVT_CODE               = 0x0C,
    HCI_QOS_SETUP_CMP_EVT_CODE                     = 0x0D,
    HCI_CMD_CMP_EVT_CODE                           = 0x0E,
    HCI_CMD_STATUS_EVT_CODE                        = 0x0F,
    HCI_HW_ERR_EVT_CODE                            = 0x10,
    HCI_FLUSH_OCCURRED_EVT_CODE                    = 0x11,
    HCI_ROLE_CHG_EVT_CODE                          = 0x12,
    HCI_NB_CMP_PKTS_EVT_CODE                       = 0x13,
    HCI_MODE_CHG_EVT_CODE                          = 0x14,
    HCI_RETURN_LINK_KEYS_EVT_CODE                  = 0x15,
    HCI_PIN_CODE_REQ_EVT_CODE                      = 0x16,
    HCI_LK_REQ_EVT_CODE                            = 0x17,
    HCI_LK_NOTIF_EVT_CODE                          = 0x18,
    HCI_DATA_BUF_OVFLW_EVT_CODE                    = 0x1A,
    HCI_MAX_SLOT_CHG_EVT_CODE                      = 0x1B,
    HCI_RD_CLK_OFF_CMP_EVT_CODE                    = 0x1C,
    HCI_CON_PKT_TYPE_CHG_EVT_CODE                  = 0x1D,
    HCI_QOS_VIOL_EVT_CODE                          = 0x1E,
    HCI_PAGE_SCAN_REPET_MODE_CHG_EVT_CODE          = 0x20,
    HCI_FLOW_SPEC_CMP_EVT_CODE                     = 0x21,
    HCI_INQ_RES_WITH_RSSI_EVT_CODE                 = 0x22,
    HCI_RD_REM_EXT_FEATS_CMP_EVT_CODE              = 0x23,
    HCI_SYNC_CON_CMP_EVT_CODE                      = 0x2C,
    HCI_SYNC_CON_CHG_EVT_CODE                      = 0x2D,
    HCI_SNIFF_SUB_EVT_CODE                         = 0x2E,
    HCI_EXT_INQ_RES_EVT_CODE                       = 0x2F,
    HCI_ENC_KEY_REFRESH_CMP_EVT_CODE               = 0x30,
    HCI_IO_CAP_REQ_EVT_CODE                        = 0x31,
    HCI_IO_CAP_RSP_EVT_CODE                        = 0x32,
    HCI_USER_CFM_REQ_EVT_CODE                      = 0x33,
    HCI_USER_PASSKEY_REQ_EVT_CODE                  = 0x34,
    HCI_REM_OOB_DATA_REQ_EVT_CODE                  = 0x35,
    HCI_SP_CMP_EVT_CODE                            = 0x36,
    HCI_LINK_SUPV_TO_CHG_EVT_CODE                  = 0x38,
    HCI_ENH_FLUSH_CMP_EVT_CODE                     = 0x39,
    HCI_USER_PASSKEY_NOTIF_EVT_CODE                = 0x3B,
    HCI_KEYPRESS_NOTIF_EVT_CODE                    = 0x3C,
    HCI_REM_HOST_SUPP_FEATS_NOTIF_EVT_CODE         = 0x3D,
    HCI_LE_META_EVT_CODE                           = 0x3E,
    HCI_MAX_EVT_MSK_PAGE_1_CODE                    = 0x40,
    HCI_SYNC_TRAIN_CMP_EVT_CODE                    = 0x4F,
    HCI_SYNC_TRAIN_REC_EVT_CODE                    = 0x50,
    HCI_CON_SLV_BCST_REC_EVT_CODE                  = 0x51,
    HCI_CON_SLV_BCST_TO_EVT_CODE                   = 0x52,
    HCI_TRUNC_PAGE_CMP_EVT_CODE                    = 0x53,
    HCI_SLV_PAGE_RSP_TO_EVT_CODE                   = 0x54,
    HCI_CON_SLV_BCST_CH_MAP_CHG_EVT_CODE           = 0x55,
    HCI_AUTH_PAYL_TO_EXP_EVT_CODE                  = 0x57,
    HCI_MAX_EVT_MSK_PAGE_2_CODE                    = 0x58,
    HCI_DBG_META_EVT_CODE                          = 0xFF,

    /// LE Events Subcodes
    HCI_LE_CON_CMP_EVT_SUBCODE                     = 0x01,
    HCI_LE_ADV_REPORT_EVT_SUBCODE                  = 0x02,
    HCI_LE_CON_UPDATE_CMP_EVT_SUBCODE              = 0x03,
    HCI_LE_RD_REM_USED_FEATS_CMP_EVT_SUBCODE       = 0x04,
    HCI_LE_LTK_REQUEST_EVT_SUBCODE                 = 0x05,
    HCI_LE_REM_CON_PARAM_REQ_EVT_SUBCODE           = 0x06,
    HCI_LE_DATA_LEN_CHG_EVT_SUBCODE                = 0x07,
    HCI_LE_RD_LOC_P256_PUB_KEY_CMP_EVT_SUBCODE     = 0x08,
    HCI_LE_GEN_DHKEY_CMP_EVT_SUBCODE               = 0x09,
    HCI_LE_ENH_CON_CMP_EVT_SUBCODE                 = 0x0A,
    HCI_LE_DIR_ADV_REP_EVT_SUBCODE                 = 0x0B,

    /// DBG Events Subcodes
    #if (BLE_EMB_PRESENT && BLE_TESTER)
    HCI_DBG_BLE_TST_LLCP_RECV_EVT_SUBCODE          = 0x01,
    #endif // (BLE_EMB_PRESENT && BLE_TESTER)
    #if (RW_DEBUG)
    HCI_DBG_ASSERT_ERR_EVT_SUBCODE                 = 0x02,
    #endif //(RW_DEBUG)
};

/// Event mask page enum
enum hci_evt_mask_page
{
    /// page 0
    HCI_PAGE_0,
    /// page 1
    HCI_PAGE_1,
    /// page 2
    HCI_PAGE_2,
    /// Default
    HCI_PAGE_DFT
};
/// HCI ACL data RX  packet structure
struct hci_acl_data_rx
{
    /// connection handle
    uint16_t    conhdl;
    /// broadcast and packet boundary flag
    uint8_t     pb_bc_flag;
    /// length of the data
    uint16_t    length;

    #if (BLE_EMB_PRESENT)
    /// Handle of the descriptor containing RX Data
    uint8_t     rx_hdl;
    #else// (BLE_HOST_PRESENT)
    /// Pointer to the data buffer
    uint8_t* buffer;
    #endif // (BLE_EMB_PRESENT) / (BLE_HOST_PRESENT)
};

/// HCI ACL data TX packet structure
struct hci_acl_data_tx
{
    /// connection handle
    uint16_t    conhdl;
    /// broadcast and packet boundary flag
    uint8_t     pb_bc_flag;
    /// length of the data
    uint16_t    length;
    #if (BLE_EMB_PRESENT)
    /// Pointer to the first descriptor containing RX Data
    struct em_buf_node *buf;
    #else // (BLE_HOST_PRESENT)
    /// Pointer to the data buffer
    uint8_t* buffer;
    #endif // (BLE_EMB_PRESENT) / (BLE_HOST_PRESENT)
};

#if (BT_EMB_PRESENT)
/// HCI ACL data packet structure
struct hci_bt_acl_data_tx
{
    /// Buffer element
    struct bt_em_acl_buf_elt* buf_elt;
};

/// HCI ACL data Rx packet structure
struct hci_bt_acl_data_rx
{
    /// EM buffer pointer
    uint16_t buf_ptr;
    /// Data length + Data Flags (PBF + BF)
    uint16_t data_len_flags;
};

/// HCI Synchronous data packet structure
struct hci_bt_sync_data_tx
{
    /// Buffer element
    struct bt_em_sync_buf_elt* buf_elt;
};

/// HCI Synchronous data Rx packet structure
struct hci_bt_sync_data_rx
{
    /// EM buffer pointer
    uint16_t buf_ptr;
    /// Data length
    uint8_t data_len;
    /// Packet status flag
    uint8_t packet_status_flag;
    /// Synchronous link identifier
    uint8_t sync_link_id;
};
#endif // (BT_EMB_PRESENT)


/*
 * HCI COMMANDS PARAMETERS (to classify)
 ****************************************************************************************
 */

/// HCI basic command structure with connection handle
struct hci_basic_conhdl_cmd
{
    /// connection handle
    uint16_t    conhdl;
};

/// HCI basic command structure with BD address
struct hci_basic_bd_addr_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
};

/// HCI Accept connection request command structure
struct hci_accept_con_req_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Page Scan Repetition Mode
    uint8_t         role;
};

/// HCI Accept synchronous connection request command structure
struct hci_accept_sync_con_req_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Transmit bandwidth
    uint32_t    tx_bw;
    ///Receive bandwidth
    uint32_t    rx_bw;
    ///Max latency
    uint16_t    max_lat;
    ///Voice settings
    uint16_t    vx_set;
    ///Retransmission effort
    uint8_t      retx_eff;
    ///Packet type
    uint16_t     pkt_type  ;
};

/// HCI Enhanced Accept synchronous connection request command structure
struct hci_enh_accept_sync_con_cmd
{

    struct bd_addr    bd_addr;            // BD address
    uint32_t          tx_bw;              // Transmit Bandwidth (in B/sec)
    uint32_t          rx_bw;              // Receive Bandwidth (in B/sec)
    uint8_t           tx_cod_fmt[5];      // Transmit Coding Format
    uint8_t           rx_cod_fmt[5];      // Receive Coding Format
    uint16_t          tx_cod_fr_sz;       // Transmit Codec Frame Size (in B)
    uint16_t          rx_cod_fr_sz;       // Receive Codec Frame Size (in B)
    uint32_t          in_bw;              // Input Bandwidth (in B/sec)
    uint32_t          out_bw;             // Output Bandwidth (in B/sec)
    uint8_t           in_cod_fmt[5];      // Input Coding Format
    uint8_t           out_cod_fmt[5];     // Output Coding Format
    uint16_t          in_cod_data_sz;     // Input Coded Data Size (in bits)
    uint16_t          out_cod_data_sz;    // Output Coded Data Size (in bits)
    uint8_t           in_data_fmt;        // Input PCM Data Format
    uint8_t           out_data_fmt;       // Output PCM Data Format
    uint8_t           in_msb_pos;         // Input PCM Sample Payload MSB Position (in bits)
    uint8_t           out_msb_pos;        // Output PCM Sample Payload MSB Position (in bits)
    uint8_t           in_data_path;       // Input Data Path
    uint8_t           out_data_path;      // Output Data Path
    uint8_t           in_tr_unit_sz;      // Input Transport Unit Size (in bits)
    uint8_t           out_tr_unit_sz;     // Output Transport Unit Size (in bits)
    uint16_t          max_lat;            // Max Latency (in ms)
    uint16_t          packet_type;        // Packet Type
    uint8_t           retx_eff;           // Retransmission Effort


};

/// HCI reject connection request command structure
struct hci_reject_con_req_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Reason
    uint8_t         reason;
};

/// HCI reject synchronous connection request command structure
struct hci_reject_sync_con_req_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Reason
    uint8_t         reason;
};

/// HCI link key request reply command structure
struct hci_lk_req_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Key
    struct ltk         key;
};

/// HCI link key request reply command structure
struct hci_pin_code_req_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Pin code length
    uint8_t     pin_len;
    ///Key
    struct pin_code pin;
};

/// HCI switch role command structure
struct hci_switch_role_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Read all flag
    uint8_t role;
};

/// HCI flow specification command parameters structure
struct hci_flow_spec_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Flags
    uint8_t flags;
    ///Flow direction
    uint8_t flow_dir;
    ///Service type
    uint8_t serv_type;
    ///Token rate
    uint32_t tk_rate;
    ///Token buffer size
    uint32_t tk_buf_sz;
    ///Peak bandwidth
    uint32_t pk_bw;
    ///Access latency
    uint32_t acc_lat;
};

/// HCI enhanced flush command parameters structure
struct hci_enh_flush_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Packet Type
    uint8_t pkt_type;
};

/// HCI command complete event structure for the read auto flush TO command
struct hci_rd_auto_flush_to_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Flush timeout
    uint16_t flush_to;
};

/// HCI write flush timeout command parameters structure
struct hci_wr_auto_flush_to_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Flush timeout
    uint16_t flush_to;
};

/// HCI change connection packet type command parameters structure
struct hci_chg_con_pkt_type_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Packet type
    uint16_t pkt_type;
};

/// HCI read link policy settings command parameters structure
struct hci_rd_link_pol_stg_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Link policy
    uint16_t lnk_policy;
};

/// HCI read link policy settings command parameters structure
struct hci_wr_link_pol_stg_cmd
{
    ///Connection handle
    uint16_t    conhdl;
    ///Link policy
    uint16_t lnk_policy;
};

/// HCI sniff mode request command parameters structure
struct hci_sniff_mode_cmd
{
    ///Connection handle
    uint16_t    conhdl;
    ///Sniff max interval
    uint16_t    max_int;
    ///Sniff min interval
    uint16_t    min_int;
    ///Sniff attempt
    uint16_t    attempt;
    ///Sniff timeout
    uint16_t    timeout;
};

/// HCI sniff subrating mode request command parameters structure
struct hci_sniff_sub_cmd
{
    ///Connection handle
    uint16_t    conhdl;
    ///Sniff max latency
    uint16_t    max_lat;
    ///Minimun remote TO
    uint16_t    min_rem_to;
    ///Minimun local TO
    uint16_t    min_loc_to;
};

/// HCI role discovery complete event parameters structure
struct hci_role_discovery_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Role
    uint8_t role;

};

/// HCI read failed contact counter command parameters structure
struct hci_rd_fail_contact_cnt_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Fail contact counter
    uint16_t fail_cnt;
};

/// HCI read link quality complete event parameters structure
struct hci_rd_link_qual_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Quality type
    uint8_t quality;
};

/// HCI read afh channel map complete event parameters structure
struct hci_rd_afh_ch_map_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    /// AFH mode
    uint8_t afh_mode;
    /// AFH channel map
    struct chnl_map afh_map;
};

/// HCI read lmp handle complete event parameters structure
struct hci_rd_lmp_hdl_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///lmp handle
    uint8_t lmp_hdl;
    ///rsvd
    uint32_t rsvd;
};

/// HCI read remote extended features command parameters structure
struct hci_rd_rem_ext_feats_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///page number
    uint8_t pg_nb;
};

/// HCI read encryption key size complete event parameters structure
struct hci_rd_enc_key_size_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Key size
    uint8_t key_sz;
};

/// HCI read enhanced transmit power command parameters structure
struct hci_rd_enh_tx_pwr_lvl_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Type
    uint8_t type;
};

/// HCI read enhanced transmit power complete event parameters structure
struct hci_rd_enh_tx_pwr_lvl_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Transmit power GFSK
    uint8_t pw_gfsk;
    ///Transmit power DQPSK
    uint8_t pw_dqpsk;
    ///Transmit power 8DPSK
    uint8_t pw_8dpsk;
};


/*
 * HCI LINK CONTROL COMMANDS PARAMETERS
 ****************************************************************************************
 */

/// Format of the message of the Group: LINK_CONTROL_COMMANDS
/// HCI Inquiry command parameters structure
struct hci_inq_cmd
{
    ///Lap
    struct lap  lap;
    ///Inquiry Length
    uint8_t     inq_len;
    ///Number of response
    uint8_t     nb_rsp;
};
struct hci_per_inq_mode_cmd
{
    ///Maximum period length
    uint16_t max_per_len;
    ///Minimum period length
    uint16_t min_per_len;
    ///lap
    struct lap lap;
    ///Inquiry length
    uint8_t inq_len;
    ///Number of response
    uint8_t nb_rsp;
};
struct hci_create_con_cmd
{
    /// BdAddr
    struct bd_addr  bd_addr;
    /// Packet Type
    uint16_t        pkt_type;
    /// Page Scan Repetition Mode
    uint8_t         page_scan_rep_mode;
    /// Reserved
    uint8_t         rsvd;
    /**
     * Clock Offset
     *
     * Bits 14-0 : Bits 16-2 of CLKNslave-CLK
     * Bit 15 : Clock_Offset_Valid_Flag
     *   Invalid Clock Offset = 0
     *   Valid Clock Offset = 1
     */
    uint16_t        clk_off;
    /// Allow Switch
    uint8_t         switch_en;
};

/// HCI disconnect command structure
struct hci_disconnect_cmd
{
    /// connection handle
    uint16_t    conhdl;
    /// reason
    uint8_t     reason;
};

/// HCI master link key command structure
struct hci_master_lk_cmd
{
    ///Key flag
    uint8_t key_flag;
};

/// HCI authentication request command parameters structure
struct hci_set_con_enc_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Encryption mode
    uint8_t enc_en;
};

struct hci_rem_name_req_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Page Scan Repetition Mode
    uint8_t         page_scan_rep_mode;
    ///Reserved
    uint8_t         rsvd;
    /**
     * Clock Offset
     *
     * Bits 14-0 : Bits 16-2 of CLKNslave-CLK
     * Bit 15 : Clock_Offset_Valid_Flag
     *   Invalid Clock Offset = 0
     *   Valid Clock Offset = 1
     */
    uint16_t        clk_off;
};

/// HCI remote name request complete event structure
struct hci_rem_name_req_cmp_evt
{
    /// Status
    uint8_t status;
    /// BD Addr
    struct bd_addr bd_addr;
    /// Name
    struct device_name name;
};

/// HCI setup synchronous connection command structure
struct hci_setup_sync_con_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Transmit bandwidth
    uint32_t tx_bw;
    ///Receive bandwidth
    uint32_t rx_bw;
    ///Max latency
    uint16_t max_lat;
    ///Voice setting
    uint16_t vx_set;
    ///Retransmission effort
    uint8_t retx_eff;
    ///Packet type
    uint16_t pkt_type;
};

/// HCI setup synchronous connection command structure
struct hci_enh_setup_sync_con_cmd
{
    uint16_t      conhdl;               // Connection Handle
    uint32_t      tx_bw;                // Transmit Bandwidth (in B/sec)
    uint32_t      rx_bw;                // Receive Bandwidth (in B/sec)
    uint8_t       tx_cod_fmt[5];        // Transmit Coding Format
    uint8_t       rx_cod_fmt[5];        // Receive Coding Format
    uint16_t      tx_cod_fr_sz;         // Transmit Codec Frame Size (in B)
    uint16_t      rx_cod_fr_sz;         // Receive Codec Frame Size (in B)
    uint32_t      in_bw;                // Input Bandwidth (in B/sec)
    uint32_t      out_bw;               // Output Bandwidth (in B/sec)
    uint8_t       in_cod_fmt[5];        // Input Coding Format
    uint8_t       out_cod_fmt[5];       // Output Coding Format
    uint16_t      in_cod_data_sz;       // Input Coded Data Size (in bits)
    uint16_t      out_cod_data_sz;      // Output Coded Data Size (in bits)
    uint8_t       in_data_fmt;          // Input PCM Data Format
    uint8_t       out_data_fmt;         // Output PCM Data Format
    uint8_t       in_msb_pos;           // Input PCM Sample Payload MSB Position (in bits)
    uint8_t       out_msb_pos;          // Output PCM Sample Payload MSB Position (in bits)
    uint8_t       in_data_path;         // Input Data Path
    uint8_t       out_data_path;        // Output Data Path
    uint8_t       in_tr_unit_sz;        // Input Transport Unit Size (in bits)
    uint8_t       out_tr_unit_sz;       // Output Transport Unit Size (in bits)
    uint16_t      max_lat;              // Max Latency (in ms)
    uint16_t      packet_type;          // Packet Type
    uint8_t       retx_eff;             // Retransmission Effort
};

/// HCI io capability request reply command structure
struct hci_io_cap_req_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///IO capability
    uint8_t io_capa;
    ///OOB data present
    uint8_t oob_data_pres;
    ///Authentication requirements
    uint8_t auth_req;

};

/// HCI io capability request negative reply command structure
struct hci_io_cap_req_neg_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Reason
    uint8_t reason;
};

/// HCI user pass key request reply command structure
struct hci_user_passkey_req_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Numeric value
    uint32_t num_val;
};

/// HCI remote oob data request reply command structure
struct hci_rem_oob_data_req_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///hash part
    struct hash oob_c;
    ///random part
    struct randomizer oob_r;
};

/// HCI send key press notification command structure
struct hci_send_keypress_notif_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Notification type
    uint8_t notif_type;
};

/// HCI truncated page command structure
struct hci_trunc_page_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    /// Page Scan Repetition Mode
    uint8_t         page_scan_rep_mode;
    /**
     * Clock Offset
     *
     * Bits 14-0 : Bits 16-2 of CLKNslave-CLK
     * Bit 15 : Clock_Offset_Valid_Flag
     *   Invalid Clock Offset = 0
     *   Valid Clock Offset = 1
     */
    uint16_t        clk_off;
};

/// HCI truncated page cancel command structure
struct hci_trunc_page_can_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
};

/// HCI set connectionless slave broadcast command structure
struct hci_set_con_slv_bcst_cmd
{
    /// Enable
    uint8_t enable;
    /// LT_ADDR
    uint8_t lt_addr;
    /// LPO_Allowed
    uint8_t lpo_allowed;
    /// Packet_Type
    uint16_t packet_type;
    /// Interval_Min (in slots)
    uint16_t interval_min;
    /// Interval_Max (in slots)
    uint16_t interval_max;
    /// CSB_supervisionTO (in slots)
    uint16_t csb_supv_to;
};

/// HCI set connectionless slave broadcast command complete event structure
struct hci_set_con_slv_bcst_cmd_cmp_evt
{
    /// Status
    uint8_t status;
    /// LT_ADDR
    uint8_t lt_addr;
    /// Interval (in slots)
    uint16_t interval;
};

/// HCI set connectionless slave broadcast receive command structure
struct hci_set_con_slv_bcst_rec_cmd
{
    /// Enable
    uint8_t enable;
    /// BD_ADDR
    struct bd_addr  bd_addr;
    /// LT_ADDR
    uint8_t lt_addr;
    /// Interval (in slots)
    uint16_t interval;
    /// Clock_Offset (28 bits) - (CLKNslave – CLK) modulo 2^28
    uint32_t clock_offset;
    /// Next_Connectionless_Slave_Broadcast_Clock (28 bits)
    uint32_t next_csb_clock;
    /// CSB_supervisionTO (in slots)
    uint16_t csb_supv_to;
    /// Remote_Timing_Accuracy (in ppm)
    uint8_t remote_timing_accuracy;
    /// Skip
    uint8_t skip;
    /// Packet_Type
    uint16_t packet_type;
    /// AFH_Channel_Map
    struct chnl_map afh_ch_map;
};

/// HCI set connectionless slave broadcast receive command complete event structure
struct hci_set_con_slv_bcst_rec_cmd_cmp_evt
{
    /// Status
    uint8_t status;
    /// BD_ADDR
    struct bd_addr  bd_addr;
    /// LT_ADDR
    uint8_t lt_addr;
};

/// HCI Receive Synchronization Train command structure
struct hci_rec_sync_train_cmd
{
    /// BD_ADDR
    struct bd_addr  bd_addr;
    /// Synchronization_scanTO (in slots)
    uint16_t sync_scan_to;
    /// Sync_Scan_Window (in slots)
     uint16_t sync_scan_win;
    /// Sync_Scan_Interval (in slots)
     uint16_t sync_scan_int;
};

/// HCI remote oob extended data request reply command structure
struct hci_rem_oob_ext_data_req_reply_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///hash part
    struct hash oob_c_192;
    ///random part
    struct randomizer oob_r_192;
    ///hash part
    struct hash oob_c_256;
    ///random part
    struct randomizer oob_r_256;
};


struct hci_le_generate_dh_key_cmd
{
    uint8_t public_key[64];
};
/*
 * HCI LINK POLICY COMMANDS PARAMETERS
 ****************************************************************************************
 */

/// HCI setup quality of service command structure
struct hci_qos_setup_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Flags
    uint8_t flags;
    ///Service type
    uint8_t serv_type;
    ///Token rate
    uint32_t tok_rate;
    ///Peak bandwidth
    uint32_t pk_bw;
    ///Latency
    uint32_t lat;
    ///Delay variation
    uint32_t del_var;
};

/// HCI command complete event structure for read default link policy command structure
struct hci_rd_dft_link_pol_stg_cmd_cmp_evt
{
    ///Status of the command reception
    uint8_t     status;
    ///Link policy
    uint16_t    link_pol_stg;
};

struct hci_wr_dft_link_pol_stg_cmd
{
        ///Link policy
        uint16_t    link_pol_stg;
};

/*
 * HCI CONTROL & BASEBAND COMMANDS PARAMETERS
 ****************************************************************************************
 */

/// HCI set event mask command structure
struct hci_set_evt_mask_cmd
{
    ///Event Mask
    struct evt_mask    event_mask;
};

/// HCI set event filter command structure
struct hci_set_evt_filter_cmd
{
    /// Filter type
    uint8_t filter_type;

    /// Filters
    union hci_filter
    {
        uint8_t clear_all_filter_reserved;

        /// Inquiry Result Filter
        struct inq_res_filter
        {
            /// Filter Condition type
            uint8_t cond_type;

            /// Filter conditions
            union hci_inq_filter_cond
            {
                /// Reserved value (Inquiry Result Filter - condition type 0x00 has no condition)
                uint8_t cond_0_reserved;

                /// Inquiry Result Filter Condition - condition type 0x01
                struct inq_res_filter_cond_1
                {
                    /// Class_of_Device
                    struct devclass class_of_dev;
                    /// Class_of_Device_Mask
                    struct devclass class_of_dev_msk;
                } cond_1;

                /// Inquiry Result Filter Condition - condition type 0x02
                struct inq_res_filter_cond_2
                {
                    /// BD Address
                    struct bd_addr bd_addr;
                } cond_2;
            } cond;
        } inq_res;

        /// Connection Setup Filter
        struct con_set_filter
        {
            /// Filter Condition type
            uint8_t cond_type;

            /// Filter conditions
            union hci_con_filter_cond
            {
                /// Connection Setup Filter Condition - condition type 0x00
                struct con_set_filter_cond_0
                {
                    /// Auto_Accept_Flag
                    uint8_t auto_accept;
                } cond_0;

                /// Connection Setup Filter Condition - condition type 0x01
                struct con_set_filter_cond_1
                {
                    /// Class_of_Device
                    struct devclass class_of_dev;
                    /// Class_of_Device_Mask
                    struct devclass class_of_dev_msk;
                    /// Auto_Accept_Flag
                    uint8_t auto_accept;
                } cond_1;

                /// Connection Setup Filter Condition - condition type 0x02
                struct con_set_filter_cond_2
                {
                    /// BD Address
                    struct bd_addr bd_addr;
                    /// Auto_Accept_Flag
                    uint8_t auto_accept;
                } cond_2;
            } cond;

        } con_set;

    } filter;
};

/// HCI command completed event structure for the flush command
struct hci_flush_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
};

/// HCI command complete event structure for the Read pin type command
struct hci_rd_pin_type_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///PIN type
    uint8_t   pin_type;
};

struct hci_wr_pin_type_cmd
{
    ///PIN type
    uint8_t pin_type;
};

struct hci_rd_stored_lk_cmd
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Read all flag
    uint8_t rd_all_flag;
};

/// HCI command complete event structure for read stored link key command
struct hci_rd_stored_lk_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Maximum number of key
    uint16_t num_key_max;
    ///Read number of key
    uint16_t num_key_rd;
};

#if BT_EMB_PRESENT
struct hci_wr_stored_lk_cmd
{
        /// Number of key to write
        uint8_t num_key_wr;

        /// BD Address + Key table
        struct bd_addr_plus_key link_keys[HCI_MAX_CMD_PARAM_SIZE / sizeof(struct bd_addr_plus_key)];
};
#endif //BT_EMB_PRESENT

/// HCI command complete event structure for write stored link key command
struct hci_wr_stored_lk_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///number of key written
    uint8_t    num_key_wr;
};

struct hci_del_stored_lk_cmd
{
        ///BdAddr
        struct bd_addr  bd_addr;
        ///Delete all flag
        uint8_t del_all_flag;
};

/// HCI command complete event structure for delete stored link key command
struct hci_del_stored_lk_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Read number of key
    uint16_t num_key_del;
};

struct hci_wr_local_name_cmd
{
        ///Name
        struct device_name  name;
};

/// HCI command complete event structure for the read local name command
struct hci_rd_local_name_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///Name
    uint8_t  name[BD_NAME_SIZE];
};

/// HCI command complete event structure for the Read connection accept to command
struct hci_rd_con_accept_to_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    /// Connection accept timeout (in slots)
    uint16_t    con_acc_to;
};

struct hci_wr_con_accept_to_cmd
{
    /// Connection accept timeout (in slots)
    uint16_t    con_acc_to;
};

/// HCI command complete event structure for the Read page to command
struct hci_rd_page_to_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    /// Page timeout (in slots)
    uint16_t    page_to;
};

struct hci_wr_page_to_cmd
{
    /// Page timeout (in slots)
    uint16_t    page_to;
};

/// HCI command complete event structure for the Read scan enable command
struct hci_rd_scan_en_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///Status of the scan enable
    uint8_t     scan_en;
};

struct hci_wr_scan_en_cmd
{
        ///Status of the scan enable
        uint8_t scan_en;
};

/// HCI command complete event structure for the Read scan activity command
struct hci_rd_page_scan_act_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    /// Page scan interval (in slots)
    uint16_t page_scan_intv;
    /// Page scan window (in slots)
    uint16_t page_scan_win;
};

struct hci_wr_page_scan_act_cmd
{
    /// Page scan interval (in slots)
    uint16_t page_scan_intv;
    /// Page scan window (in slots)
    uint16_t page_scan_win;
};

/// HCI command complete event structure for the Read inquiry scan activity command
struct hci_rd_inq_scan_act_cmd_cmp_evt
{
    /// Status of the command
    uint8_t  status;
    /// Inquiry scan interval (in slots)
    uint16_t inq_scan_intv;
    /// Inquiry scan window (in slots)
    uint16_t inq_scan_win;
};

struct hci_wr_inq_scan_act_cmd
{
    /// Inquiry scan interval (in slots)
    uint16_t inq_scan_intv;
    /// Inquiry scan window (in slots)
    uint16_t inq_scan_win;
};

/// HCI command complete event structure for the Read authentication command
struct hci_rd_auth_en_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///Value of the authentication
    uint8_t    auth_en;
};

struct hci_wr_auth_en_cmd
{
        ///Value of the authentication
        uint8_t auth_en;
};

/// HCI command complete event structure for the read class of device command
struct hci_rd_class_of_dev_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///Class of device
    struct devclass class_of_dev;
};

struct hci_wr_class_of_dev_cmd
{
        ///Class of device
        struct devclass class_of_dev;
};

/// HCI read voice settings complete event
struct hci_rd_voice_stg_cmd_cmp_evt
{
    ///Status of the command reception
    uint8_t     status;
    /// Voice setting
    uint16_t voice_stg;
};

struct hci_wr_voice_stg_cmd
{
    /// voice setting
    uint16_t voice_stg;
};

/// HCI command complete event structure for read number of broadcast retrans command
struct hci_rd_nb_bdcst_retx_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Read number of broadcast retransmission
    uint8_t num_bcst_ret;
};

struct hci_wr_nb_bdcst_retx_cmd
{
        ///Read number of broadcast retransmission
        uint8_t num_bcst_ret;
};

/// HCI command complete event structure for the Read Synchronous Flow Control command
struct hci_rd_sync_flow_ctrl_en_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Synchronous flow control enable
    uint8_t     sync_flow_ctrl_en;
};

struct hci_wr_sync_flow_ctrl_en_cmd
{
    /// Synchronous Flow Control enable
    uint8_t   sync_flow_ctrl_en;
};

///HCI set controller to host flow control command
struct hci_set_ctrl_to_host_flow_ctrl_cmd
{
    ///Flow control enable for controller
    uint8_t flow_cntl;
};

///HCI host buffer size command
struct hci_host_buf_size_cmd
{
    ///Host ACL packet length
    uint16_t    acl_pkt_len;
    ///Host synchronous packet length
    uint8_t     sync_pkt_len;
    ///Host Total number of ACL packets allowed
    uint16_t    nb_acl_pkts;
    ///Host total number of synchronous packets allowed
    uint16_t    nb_sync_pkts;
};

#if BT_EMB_PRESENT
///HCI host number of completed packets command
struct hci_host_nb_cmp_pkts_cmd
{
        ///Number of handles for which the completed packets number is given
        uint8_t     nb_of_hdl;
        ///Array of connection handles
        uint16_t    con_hdl[MAX_NB_ACTIVE_ACL];
        ///Array of number of completed packets values for connection handles.
        uint16_t    nb_comp_pkt[MAX_NB_ACTIVE_ACL];
};
#elif BLE_EMB_PRESENT || BLE_HOST_PRESENT
///HCI host number of completed packets command
struct hci_host_nb_cmp_pkts_cmd
{
    ///Number of handles for which the completed packets number is given
    uint8_t     nb_of_hdl;
    ///Array of connection handles
    uint16_t    con_hdl[BLE_CONNECTION_MAX+1];     // ensure that at least 1 element is present
    ///Array of number of completed packets values for connection handles.
    uint16_t    nb_comp_pkt[BLE_CONNECTION_MAX+1]; // ensure that at least 1 element is present
};
#endif //BLE_EMB_PRESENT || BLE_HOST_PRESENT

/// HCI read link supervision timeout command parameters structure
struct hci_rd_link_supv_to_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Link supervision timeout
    uint16_t lsto_val;
};

/// HCI write link supervision timeout command parameters structure
struct hci_wr_link_supv_to_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Link supervision timeout
    uint16_t lsto_val;
};

/// HCI command complete event structure for the nb of supported IAC command
struct hci_rd_nb_supp_iac_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///nb_of iac
    uint8_t  nb_iac;
};

/// HCI command complete event structure for read current IAC LAP command
struct hci_rd_curr_iac_lap_cmd_cmp_evt
{
    ///Status of the command
    uint8_t     status;
    ///nb of current iac
    uint8_t  nb_curr_iac;
    ///lap
    struct lap iac_lap;
};

/// HCI write current IAC LAP command structure
struct hci_wr_curr_iac_lap_cmd
{
    /// Number of current iac laps
    uint8_t  nb_curr_iac;
    ///lap
    struct lap iac_lap[(HCI_MAX_CMD_PARAM_SIZE / BD_ADDR_LAP_LEN) - 1];
};

struct hci_set_afh_host_ch_class_cmd
{
    ///AFH channel map
    struct chnl_map   afh_ch;
};

/// HCI command complete event structure for write inquiry scan type command structure
struct hci_rd_inq_scan_type_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    /// Inquiry scan type
    uint8_t     inq_scan_type;
};

struct hci_wr_inq_scan_type_cmd
{
    /// Inquiry scan type
    uint8_t     inq_scan_type;
};

/// HCI command complete event structure for read inquiry mode command structure
struct hci_rd_inq_mode_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    /// Inquiry mode
    uint8_t     inq_mode;
};

struct hci_wr_inq_mode_cmd
{
    /// Inquiry mode
    uint8_t     inq_mode;
};

/// HCI command complete event structure for write page scan type command structure
struct hci_rd_page_scan_type_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    /// Page scan type
    uint8_t     page_scan_type;
};

struct hci_wr_page_scan_type_cmd
{
    /// Page scan type
    uint8_t     page_scan_type;
};

/// HCI command complete event structure for read assessment mode command structure
struct hci_rd_afh_ch_assess_mode_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///AFH channel assessment mode
    uint8_t     afh_ch_ass_mode;
};

struct hci_wr_afh_ch_assess_mode_cmd
{
    ///AFH channel assessment mode
    uint8_t     afh_ch_ass_mode;
};

/// HCI command complete event structure for remote name request cancel command
struct hci_rd_ext_inq_rsp_cmd_cmp_evt
{
    ///status
    uint8_t     status;
    ///FEC required
    uint8_t     fec_req;
    ///Extended inquiry response
    struct eir  eir;
};

struct hci_wr_ext_inq_rsp_cmd
{
    ///FEC required
    uint8_t     fec_req;
    ///Extended inquiry response
    struct eir  eir;
};

/// HCI command complete event structure for remote name request cancel command
struct hci_rd_sp_mode_cmd_cmp_evt
{
    ///status
    uint8_t     status;
    ///Simple pairing mode
    uint8_t     sp_mode;
};

struct hci_wr_sp_mode_cmd
{
    ///Simple pairing mode
    uint8_t     sp_mode;
};

/// HCI command complete event structure for read oob data command
struct hci_rd_loc_oob_data_cmd_cmp_evt
{
    ///status
    uint8_t     status;
    ///hash part
    struct hash oob_c;
    ///random part
    struct randomizer oob_r;
};

/// HCI command complete event structure for read inquiry response transmit power command
struct hci_rd_inq_rsp_tx_pwr_lvl_cmd_cmp_evt
{
    ///status
    uint8_t status;
    ///TX power
    uint8_t tx_pwr;
};

struct hci_wr_inq_tx_pwr_lvl_cmd
{
    ///TX power
    int8_t tx_pwr;
};

/// HCI command complete event structure for read erroneous data reporting command
struct hci_rd_dft_err_data_rep_cmd_cmp_evt
{
    ///status
    uint8_t     status;
    ///Erroneous data reporting
    uint8_t     err_data_rep;
};

struct hci_wr_dft_err_data_rep_cmd
{
    ///Erroneous data reporting
    uint8_t err_data_rep;
};

/// HCI read LE Host Supported complete event
struct  hci_rd_le_host_supp_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    ///LE_Supported_Host
    uint8_t le_supported_host;
    ///Simultaneous_LE_Host
    uint8_t simultaneous_le_host;
};

/// HCI write LE Host Supported command
struct  hci_wr_le_host_supp_cmd
{
    ///LE_Supported_Host
    uint8_t le_supported_host;
    ///Simultaneous_LE_Host
    uint8_t simultaneous_le_host;
};

/// HCI Set MWS Channel Parameters command
struct hci_set_mws_channel_params_cmd
{
    ///MWS_Channel_Enable
    uint8_t mws_channel_enable;
    ///MWS_RX_Center_Frequency
    uint16_t mws_rx_center_frequency;
    ///MWS_TX_Center_Frequency
    uint16_t mws_tx_center_frequency;
    ///MWS_RX_Channel_Bandwidth
    uint16_t mws_rx_channel_bandwidth;
    ///MWS_TX_Channel_Bandwidth
    uint16_t mws_tx_channel_bandwidth;
    ///MWS_Channel_Type
    uint8_t mws_channel_type;
};

/// HCI Set External Frame Configuration command
struct hci_set_external_frame_config_cmd
{
    /// Ext_Frame_Duration
    uint16_t ext_fr_duration;
    /// Ext_Frame_Sync_Assert_Offset
    int16_t ext_fr_sync_assert_offset;
    /// Ext_Frame_Sync_Assert_Jitter
    uint16_t ext_fr_sync_assert_jitter;
    /// Ext_Frame_Num_Periods
    uint8_t ext_fr_num_periods;
    /// Period_Duration[i]
    uint16_t period_duration[__ARRAY_EMPTY];
    /// Period_Type[i]
    //uint8_t period_type[__ARRAY_EMPTY];
};

/// HCI Set MWS Signaling command
struct hci_set_mws_signaling_cmd
{
    ///MWS_RX_Assert_Offset
    int16_t mws_rx_assert_offset;
    ///MWS_RX_Assert_Jitter
    uint16_t mws_rx_assert_jitter;
    ///MWS_RX_Deassert_Offset
    int16_t mws_rx_deassert_offset;
    ///MWS_RX_Deassert_Jitter
    uint16_t mws_rx_deassert_jitter;
    ///MWS_TX_Assert_Offset
    int16_t mws_tx_assert_offset;
    ///MWS_TX_Assert_Jitter
    uint16_t mws_tx_assert_jitter;
    ///MWS_TX_Deassert_Offset
    int16_t mws_tx_deassert_offset;
    ///MWS_TX_Deassert_Jitter
    uint16_t mws_tx_deassert_jitter;
    ///MWS_Pattern_Assert_Offset
    int16_t mws_pattern_assert_offset;
    ///MWS_Pattern_Assert_Jitter
    uint16_t mws_pattern_assert_jitter;
    ///MWS_Inactivity_Duration_Assert_Offset
    int16_t mws_inactivity_duration_assert_offset;
    ///MWS_Inactivity_Duration_Assert_Jitter
    uint16_t mws_inactivity_duration_assert_jitter;
    ///MWS_Scan_Frequency_Assert_Offset
    int16_t mws_scan_frequency_assert_offset;
    ///MWS_Scan_Frequency_Assert_Jitter
    uint16_t mws_scan_frequency_assert_jitter;
    ///MWS_Priority_Assert_Offset_Request
    uint16_t mws_priority_assert_offset_request;
};

/// HCI Set MWS Signaling command complete event
struct hci_set_mws_signaling_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    ///Bluetooth_Rx_Priority_Assert_Offset
    int16_t bt_rx_prio_assert_offset;
    ///Bluetooth_Rx_Priority_Assert_Jitter
    uint16_t bt_rx_prio_assert_jitter;
    ///Bluetooth_Rx_Priority_Deassert_Offset
    int16_t bt_rx_prio_deassert_offset;
    ///Bluetooth_Rx_Priority_Deassert_Jitter
    uint16_t bt_rx_prio_deassert_jitter;
    ///802_Rx_Priority_Assert_Offset
    int16_t _802_rx_prio_assert_offset;
    ///802_Rx_Priority_Assert_Jitter
    uint16_t _802_rx_prio_assert_jitter;
    ///802_Rx_Priority_Deassert_Offset
    int16_t _802_rx_prio_deasssert_offset;
    ///802_Rx_Priority_Deassert_Jitter
    uint16_t _802_rx_prio_deassert_jitter;
    ///Bluetooth_Tx_On_Assert_Offset
    int16_t bt_tx_on_assert_offset;
    ///Bluetooth_Tx_On_Assert_Jitter
    uint16_t bt_tx_on_assert_jitter;
    ///Bluetooth_Tx_On_Deassert_Offset
    int16_t bt_tx_on_deassert_offset;
    ///Bluetooth_Tx_On_Deassert_Jitter
    uint16_t bt_tx_on_deassert_jitter;
    ///802_Tx_On_Assert_Offset
    int16_t _802_tx_on_assert_offset;
    ///802_Tx_On_Assert_Jitter
    uint16_t _802_tx_on_assert_jitter;
    ///802_Tx_On_Deassert_Offset
    int16_t _802_tx_on_deassert_offset;
    ///802_Tx_On_Deassert_Jitter
    uint16_t _802_tx_on_deassert_jitter;
};

/// HCI Set MWS Transport Layer command
struct hci_set_mws_transport_layer_cmd
{
    ///Transport_Layer
    uint8_t transport_layer;
    ///To_MWS_Baud_Rate
    uint32_t to_mws_baud_rate;
    ///From_MWS_Baud_Rate
    uint32_t from_mws_baud_rate;
};

/// HCI Set MWS Scan Frequency Table command
struct hci_set_mws_scan_freq_table_cmd
{
    ///Num_Scan_Frequencies
    uint8_t num_scan_frequencies;
    ///Scan_Frequency_Low[i]
    uint16_t scan_frequency_low[1/*__ARRAY_EMPTY*/];
    ///Scan_Frequency_High[i]
    uint16_t scan_frequency_high[1/*__ARRAY_EMPTY*/];
};

/// HCI Set MWS Pattern Configuration command
struct hci_set_mws_pattern_config_cmd
{
    ///MWS_PATTERN_Index
    uint8_t mws_pattern_index;
    ///MWS_PATTERN_NumIntervals
    uint8_t mws_pattern_num_intervals;
    ///MWS_PATTERN_IntervalDuration[i]
    uint16_t mws_pattern_interval_duration[1/*__ARRAY_EMPTY*/];
    ///MWS_PATTERN_IntervalType[i]
    uint8_t mws_pattern_interval_type[1/*__ARRAY_EMPTY*/];
};

/// Hci Get MWS Transport Layer Configuration command complete event
struct hci_get_mws_transport_layer_config_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    ///Num_Transports
    uint8_t num_transports;
    ///Transport_Layer[i]
    uint8_t transport_layer[1/*__ARRAY_EMPTY*/];
    ///Num_Baud_Rates[i]
    uint8_t num_baud_rates[1/*__ARRAY_EMPTY*/];
    ///To_MWS_Baud_Rate[k]
    uint32_t to_mws_baud_rate[1/*__ARRAY_EMPTY*/];
    ///From_MWS_Baud_Rate[k]
    uint32_t from_mws_baud_rate[1/*__ARRAY_EMPTY*/];
};

/// HCI read Secure Connections Host Support complete event
struct  hci_rd_sec_con_host_supp_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    /// Secure Connections Host Support
    uint8_t sec_con_host_supp;
};

/// HCI write Secure Connections Host Support command
struct  hci_wr_sec_con_host_supp_cmd
{
    /// Secure Connections Host Support
    uint8_t sec_con_host_supp;
};

/// HCI write Secure Connections Test Mode command
struct  hci_wr_sec_con_test_mode_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// DM1 ACL-U mode
    uint8_t dm1_acl_u_mode;
    /// eSCO loopback mode
    uint8_t esco_loopback_mode;
};

/// HCI write Secure Connections Test Mode complete event
struct  hci_wr_sec_con_test_mode_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    /// Connection handle
    uint16_t conhdl;
};

/// HCI Set Reserved LT_ADDR command
struct hci_set_res_lt_addr_cmd
{
    /// LT_ADDR
    uint8_t lt_addr;
};

/// HCI Set Reserved LT_ADDR command complete event
struct hci_set_res_lt_addr_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /// LT_ADDR
    uint8_t lt_addr;
};

/// HCI Delete Reserved LT_ADDR command
struct hci_del_res_lt_addr_cmd
{
    /// LT_ADDR
    uint8_t lt_addr;
};

/// HCI Delete Reserved LT_ADDR command complete event
struct hci_del_res_lt_addr_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /// LT_ADDR
    uint8_t lt_addr;
};

/// HCI Set Connectionless Slave Broadcast Data command
struct hci_set_con_slv_bcst_data_cmd
{
    /// LT_ADDR
    uint8_t lt_addr;
    /// Fragment
    uint8_t fragment;
    /// Data_Length (in bytes)
    uint8_t data_length;
    /// Data
    uint8_t data[__ARRAY_EMPTY];
};

/// HCI Set Connectionless Slave Broadcast Data command complete event
struct hci_set_con_slv_bcst_data_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /// LT_ADDR
    uint8_t lt_addr;
};

/// HCI Read Synchronization Train Parameters command complete event
struct hci_rd_sync_train_param_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /// Sync_Train_Interval (in slots)
    uint16_t sync_train_int;
    /// synchronization_trainTO (in slots)
    uint32_t sync_train_to;
    /// Service_Data
    uint8_t service_data;
};

/// HCI Write Synchronization Train Parameters command
struct hci_wr_sync_train_param_cmd
{
    /// Interval_Min (in slots)
    uint16_t int_min;
    /// Interval_Max (in slots)
    uint16_t int_max;
    /// synchronization_trainTO (in slots)
    uint32_t sync_train_to;
    /// Service_Data
    uint8_t service_data;
};

/// HCI Write Synchronization Train Parameters command complete event
struct hci_wr_sync_train_param_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /// Sync_Train_Interval (in slots)
    uint16_t sync_train_int;
};

// HCI Synchronization Train Complete event
struct hci_sync_train_cmp_evt
{
    /// Status
    uint8_t  status;
};

/// HCI read authenticated payload timeout command
struct hci_rd_auth_payl_to_cmd
{
    ///Connection handle
    uint16_t     conhdl;
};

/// HCI command complete event structure for the Read Authenticated Payload Timeout Command
struct hci_rd_auth_payl_to_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Connection handle
    uint16_t     conhdl;
    ///Authenticated payload timeout
    uint16_t     auth_payl_to;
};

/// HCI command complete event structure for read oob extended data command
struct hci_rd_loc_oob_ext_data_cmd_cmp_evt
{
    ///status
    uint8_t     status;
    ///hash part
    struct hash oob_c_192;
    ///random part
    struct randomizer oob_r_192;
    ///hash part
    struct hash oob_c_256;
    ///random part
    struct randomizer oob_r_256;
};

/// HCI read Extended Page Timeout CC event
struct hci_rd_ext_page_to_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /**
     * Extended Page Timeout measured in Number of Baseband slots. Interval Length = N * 0.625 msec (1 Baseband slot)
     * Range for N: 0x0000 (default) - 0xFFFF
     * Time Range: 0 - 40.9 Seconds
     */
    uint16_t ext_page_to;
};

/// HCI write Extended Page Timeout
struct hci_wr_ext_page_to_cmd
{
    /**
     * Extended Page Timeout measured in Number of Baseband slots. Interval Length = N * 0.625 msec (1 Baseband slot)
     * Range for N: 0x0000 (default) - 0xFFFF
     * Time Range: 0 - 40.9 Seconds
     */
    uint16_t ext_page_to;
};

/// HCI read Extended Inquiry Length CC event
struct hci_rd_ext_inq_len_cmd_cmp_evt
{
    /// Status
    uint8_t  status;
    /// Extended Inquiry Length
    uint16_t ext_inq_len;
};

/// HCI write Extended Inquiry Length
struct hci_wr_ext_inq_len_cmd
{
    /// Extended Inquiry Length
    uint16_t ext_inq_len;
};

/*
 * HCI INFORMATIONAL PARAMETERS COMMANDS PARAMETERS
 ****************************************************************************************
 */

///HCI command complete event structure for read local version information
struct hci_rd_local_ver_info_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///HCI version number
    uint8_t     hci_ver;
    ///HCI revision number
    uint16_t    hci_rev;
    ///LMP version
    uint8_t     lmp_ver;
    ///manufacturer name
    uint16_t    manuf_name;
    ///LMP Subversion
    uint16_t    lmp_subver;
};

///HCI command complete event structure for read local supported commands
struct hci_rd_local_supp_cmds_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///Supported Commands structure
    struct supp_cmds    local_cmds;
};

/// HCI command complete event structure for read local supported features command
struct hci_rd_local_supp_feats_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t         status;
    ///Local  supported features
    struct features feats;
};

struct hci_rd_local_ext_feats_cmd
{
    ///Page number
    uint8_t page_nb;
};

/// HCI command complete event structure for read local extended features command
struct hci_rd_local_ext_feats_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Page number
    uint8_t     page_nb;
    ///Maximum page number
    uint8_t     page_nb_max;
    ///Extended LMP features
    struct features ext_feats;
};

///HCI command complete event structure for the Read Buffer Size Command
struct hci_rd_buff_size_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///ACL data packet length controller can receive from host
    uint16_t     hc_data_pk_len;
    ///Synchronous data packet length controller can receive from host
    uint8_t      hc_sync_pk_len;
    ///Total number of ACL data packets controller can receive from host
    uint16_t     hc_tot_nb_data_pkts;
    ///Total number of synchronous data packets controller can receive from host
    uint16_t     hc_tot_nb_sync_pkts;
};

///HCI command complete event structure for read bd address
struct hci_rd_bd_addr_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///BD address
    struct bd_addr      local_addr;
};

/// HCI command complete event structure for read local supported codecs
struct hci_rd_local_supp_codecs_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t               status;
    uint8_t               nb_supp_codecs;
    uint8_t               nb_supp_vendor_specific_codecs;

//    ///Supported Codecs structure
//    struct supp_codecs    local_codecs;
};

/*
 * HCI STATUS PARAMETERS COMMANDS PARAMETERS
 ****************************************************************************************
 */

/// HCI command complete event structure for read rssi
struct hci_rd_rssi_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///RSSI value
    int8_t rssi;
};

struct hci_rd_clk_cmd
{
    ///Connection handle
    uint16_t conhdl;
    ///Which clock
    uint8_t clk_type;
};

/// HCI read clock command structure
struct hci_rd_clk_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Connection handle
    uint16_t conhdl;
    ///clock
    uint32_t clk;
    ///Accuracy
    uint16_t clk_acc;
};


/*
 * HCI TESTING COMMANDS PARAMETERS
 ****************************************************************************************
 */

/// HCI command complete event structure for read loop back mode command
struct hci_rd_loopback_mode_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Local  supported features
    uint8_t     lb_mode;
};

struct hci_wr_loopback_mode_cmd
{
    ///Local  supported features
    uint8_t     lb_mode;
};
struct hci_wr_sp_dbg_mode_cmd
{
    ///Simple pairing mode
    uint8_t     sp_mode;
};


/// * TCI Event subcodes
enum tci_evt_subcode 
{
     TCI_LMP_TX_EVENT    = 0x22,
     TCI_LMP_RX_EVENT    = 0x23,
     TCI_LC_TX_EVENT     = 0x24,
     TCI_LC_RX_EVENT     = 0x25,
     TCI_BB_TX_EVENT     = 0x26,
     TCI_BB_RX_EVENT     = 0x27,
     TCI_HW_ERROR_EVENT  = 0x28,
     TCI_RADIO_EVENT     = 0x30,
     TCI_INTERRUPT_EVENT = 0x40,
};

/// LMP direction
#define TCI_LMP_DIR_TX  0
#define TCI_LMP_DIR_RX  1

/// HCI tci lmp exchange event structure
struct hci_tci_lmp_evt
{
    ///code
    uint8_t  tci_code;
    ///length
    uint8_t  evt_len;
    ///subcode
    uint8_t  subcode;
    ///evt direction
    uint8_t  direction;
    ///lmp evt body
    uint8_t  body[17];
};

/*
 * HCI LE CONTROLLER COMMANDS PARAMETERS
 ****************************************************************************************
 */

///HCI LE Set Event Mask Command parameters structure
struct hci_le_set_evt_mask_cmd
{
    ///LE Event Mask
    struct evt_mask le_mask;
};

///HCI LE Set Random Address Command parameters structure
struct hci_le_set_rand_addr_cmd
{
    ///Random address to set
    struct bd_addr rand_addr;
};

///HCI LE Set Advertising Parameters Command parameters structure
struct hci_le_set_adv_param_cmd
{
    ///Minimum interval for advertising
    uint16_t       adv_intv_min;
    ///Maximum interval for advertising
    uint16_t       adv_intv_max;
    ///Advertising type
    uint8_t        adv_type;
    ///Own address type:  public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        own_addr_type;
    ///Peer address type: public=0 / random=1
    uint8_t        peer_addr_type;
    ///Peer Bluetooth device address
    struct bd_addr peer_addr;
    ///Advertising channel map
    uint8_t        adv_chnl_map;
    ///Advertising filter policy
    uint8_t        adv_filt_policy;
};

///HCI LE Set Advertising Data Command parameters structure
struct hci_le_set_adv_data_cmd
{
    ///Advertising data length
    uint8_t         adv_data_len;
    ///Advertising data - maximum 31 bytes
    struct adv_data data;
};

///HCI LE Set Scan Response Data Command parameters structure
struct hci_le_set_scan_rsp_data_cmd
{
    ///Scan response data length
    uint8_t              scan_rsp_data_len;
    ///Scan response data - maximum 31 bytes
    struct scan_rsp_data data;
};

///HCI LE Set Advertise Enable Command parameters structure
struct hci_le_set_adv_en_cmd
{
    ///Advertising enable - 0=disabled, 1=enabled
    uint8_t        adv_en;
};

///HCI LE Set Scan Parameters Command parameters structure
struct hci_le_set_scan_param_cmd
{
    ///Scan type - 0=passive / 1=active
    uint8_t        scan_type;
    ///Scan interval
    uint16_t       scan_intv;
    ///Scan window size
    uint16_t       scan_window;
    ///Own address type - public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        own_addr_type;
    ///Scan filter policy
    uint8_t        scan_filt_policy;
};

///HCI LE Set Scan Enable Command parameters structure
struct hci_le_set_scan_en_cmd
{
    ///Scan enable - 0=disabled, 1=enabled
    uint8_t        scan_en;
    ///Enable for duplicates filtering - 0 =disabled/ 1=enabled
    uint8_t        filter_duplic_en;
};

///HCI LE Create Connection Command parameters structure
struct hci_le_create_con_cmd
{
    ///Scan interval
    uint16_t       scan_intv;
    ///Scan window size
    uint16_t       scan_window;
    ///Initiator filter policy
    uint8_t        init_filt_policy;
    ///Peer address type - public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        peer_addr_type;
    ///Peer BD address
    struct bd_addr peer_addr;
    ///Own address type - public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        own_addr_type;
    ///Minimum of connection interval
    uint16_t       con_intv_min;
    ///Maximum of connection interval
    uint16_t       con_intv_max;
    ///Connection latency
    uint16_t       con_latency;
    ///Link supervision timeout
    uint16_t       superv_to;
    ///Minimum CE length
    uint16_t       ce_len_min;
    ///Maximum CE length
    uint16_t       ce_len_max;
};

///HCI LE Add Device to White List Command parameters structure
struct hci_le_add_dev_to_wlst_cmd
{
    ///Type of address of the device to be added to the White List - 0=public/1=random
    uint8_t        dev_addr_type;
    ///Address of device to be added to White List
    struct bd_addr dev_addr;
};

///HCI LE Remove Device from White List Command parameters structure
struct hci_le_rmv_dev_from_wlst_cmd
{
    ///Type of address of the device to be removed from the White List - 0=public/1=random
    uint8_t        dev_addr_type;
    ///Address of device to be removed from White List
    struct bd_addr dev_addr;
};


///HCI LE Set Host Channel Classification Command parameters structure
struct hci_le_set_host_ch_class_cmd
{
    ///Channel map
    struct le_chnl_map chmap;
};


///HCI LE Receiver Test Command parameters structure
struct hci_le_rx_test_cmd
{
    ///RX frequency for Rx test
    uint8_t        rx_freq;
};

///HCI LE Transmitter Test Command parameters structure
struct hci_le_tx_test_cmd
{
    ///TX frequency for Tx test
    uint8_t        tx_freq;
    ///TX test data length
    uint8_t        test_data_len;
    ///TX test payload type - see enum
    uint8_t        pk_payload_type;
};

///HCI LE Encrypt Command parameters structure
struct hci_le_enc_cmd
{
    ///Long term key structure
    struct ltk     key;
    ///Pointer to buffer with plain data to encrypt - 16 bytes
    uint8_t        plain_data[16];
};

/// HCI LE Connection Update Command parameters structure
struct hci_le_con_update_cmd
{
    ///Connection Handle
    uint16_t       conhdl;
    ///Minimum of connection interval
    uint16_t       con_intv_min;
    ///Maximum of connection interval
    uint16_t       con_intv_max;
    ///Connection latency
    uint16_t       con_latency;
    ///Link supervision timeout
    uint16_t       superv_to;
    ///Minimum of CE length
    uint16_t       ce_len_min;
    ///Maximum of CE length
    uint16_t       ce_len_max;
};

/// HCI LE Start Encryption Command parameters structure
struct hci_le_start_enc_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Random number - 8B
    struct rand_nb  nb;
    ///Encryption Diversifier
    uint16_t       enc_div;
    ///Long term key
    struct ltk     ltk;
};

/// HCI long term key request reply command parameters structure
struct hci_le_ltk_req_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Long term key
    struct ltk      ltk;
};

/// HCI LE remote connection parameter request reply command parameters structure
struct hci_le_rem_con_param_req_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Interval_Min
    uint16_t        interval_min;
    ///Interval_Max
    uint16_t        interval_max;
    ///Latency
    uint16_t        latency;
    ///Timeout
    uint16_t        timeout;
    ///Minimum_CE_Length
    uint16_t        min_ce_len;
    ///Maximum_CE_Length
    uint16_t        max_ce_len;
};

/// HCI LE remote connection parameter request negative reply command parameters structure
struct hci_le_rem_con_param_req_neg_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Reason
    uint8_t         reason;
};


/// HCI LE Set Data Length  Command parameters structure
struct hci_le_set_data_len_cmd
{
    ///Connection Handle
    uint16_t       conhdl;
    ///Preferred maximum number of payload octets that the local Controller should include
    ///in a single Link Layer Data Channel PDU.
    uint16_t       tx_octets;
    ///Preferred maximum number of microseconds that the local Controller should use to transmit
    ///a single Link Layer Data Channel PDU
    uint16_t       tx_time;
};

/// HCI LE Read Suggested Default Data Length Command
struct hci_le_wr_suggted_dft_data_len_cmd
{
    ///Suggested value for the Controller's maximum transmitted number of payload octets to be used
    uint16_t       suggted_max_tx_octets;
    ///Suggested value for the Controller's maximum packet transmission time to be used
    uint16_t       suggted_max_tx_time;
};

/// HCI LE Add Device to Resolving List Command
struct hci_le_add_dev_to_rslv_list_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
    /// Peer IRK
    struct irk          peer_irk;
    /// Local IRK
    struct irk          local_irk;
};

/// HCI LE Remove Device From Resolving List Command
struct hci_le_rmv_dev_from_rslv_list_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
};

/// HCI LE Read Peer Resolvable Address Command
struct hci_le_rd_peer_rslv_addr_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
};

/// HCI LE Read Local Resolvable Address Command
struct hci_le_rd_loc_rslv_addr_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
};

/// HCI LE Set Address Resolution Enable Command
struct hci_le_set_addr_resol_en_cmd
{
    /// Address Resolution Enable
    uint8_t             enable;
};

/// HCI LE Set Resolvable Private Address Timeout Command
struct hci_le_set_rslv_priv_addr_to_cmd
{
    /// RPA Timeout
    uint16_t            rpa_timeout;
};

/*
 * HCI EVENTS PARAMETERS
 ****************************************************************************************
 */

/// HCI inquiry complete event structure
struct hci_inq_cmp_evt
{
    ///Status of the procedure
    uint8_t status;
};


/// HCI Inquiry result event structure (with only 1 result)
struct hci_inq_res_evt
{

    ///Number of response
    uint8_t     nb_rsp;
    ///BdAddr
    struct bd_addr bd_addr;
    ///Page Scan Repetition Mode
    uint8_t     page_scan_rep_mode;
    ///Reserved
    uint8_t     reserved1;
    ///Reserved
    uint8_t     reserved2;
    ///class of device
    struct devclass class_of_dev;
    ///Clock Offset
    uint16_t        clk_off;

};

/// HCI Inquiry result with rssi event structure (with only 1 result)
struct hci_inq_res_with_rssi_evt
{
    ///Number of response
    uint8_t     nb_rsp;
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Page Scan Repetition Mode
    uint8_t     page_scan_rep_mode;
    ///Reserved
    uint8_t     reserved1;
    ///class of device
    struct devclass class_of_dev;
    ///Clock Offset
    uint16_t     clk_off;
    ///Rssi
    uint8_t      rssi;

};

/// HCI Extended inquiry result indication structure (with only 1 result)
struct hci_ext_inq_res_evt
{
    ///Number of response
    uint8_t     nb_rsp;
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Page Scan Repetition Mode
    uint8_t     page_scan_rep_mode;
    ///Reserved
    uint8_t     reserved1;
    ///class of device
    struct devclass class_of_dev;
    ///Clock Offset
    uint16_t        clk_off;
    ///RSSi
    uint8_t         rssi;
    ///Extended inquiry response data
    struct eir      eir;
};

/// HCI disconnect complete event structure
struct hci_disc_cmp_evt
{
    ///Status of received command
    uint8_t     status;
    ///Connection Handle
    uint16_t    conhdl;
    ///Reason for disconnection
    uint8_t     reason;
};

/// HCI basic command complete event structure
struct hci_basic_cmd_cmp_evt
{
    ///Status of the command reception
    uint8_t status;
};

/// HCI basic command complete event structure with connection handle
struct hci_basic_conhdl_cmd_cmp_evt
{
    /// status
    uint8_t     status;
    /// connection handle
    uint16_t    conhdl;
};

/// HCI basic command complete event structure with BD address
struct hci_basic_bd_addr_cmd_cmp_evt
{
    ///status
   uint8_t         status;
   ///BdAddr
    struct bd_addr bd_addr;
};

/// HCI basic event structure with status and BD address
struct hci_basic_stat_bd_addr_evt
{
    ///status
   uint8_t         status;
   ///BdAddr
    struct bd_addr bd_addr;
};

/// HCI basic event including a connection handle as parameter
struct hci_basic_conhdl_evt
{
    ///Connection handle
    uint16_t     conhdl;
};

/// HCI complete event with status only.
struct hci_cmd_stat_event
{
    /// Status of the command reception
    uint8_t status;
};

/// HCI number of packet complete event structure
struct hci_nb_cmp_pkts_evt
{
    /// number of handles
    uint8_t     nb_of_hdl;
    /// connection handle
    uint16_t    conhdl[1];
    /// number of completed packets
    uint16_t    nb_comp_pkt[1];
};

/// HCI data buffer overflow event structure
struct hci_data_buf_ovflw_evt
{
    ///Link type
    uint8_t link_type;
};

/// HCI Hardware Error Event parameters structure
struct hci_hw_err_evt
{
    /// HW error code
    uint8_t hw_code;
};

/// HCI encryption change event structure
struct hci_enc_change_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Encryption enabled information
    uint8_t     enc_stat;
};

/// HCI encryption key refresh complete event structure
struct hci_enc_key_ref_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
};

/// HCI Authenticated Payload Timeout Expired Event structure
struct hci_auth_payl_to_exp_evt
{
    ///Connection handle
    uint16_t     conhdl;
};

/// HCI command complete event structure for create connection
struct hci_con_cmp_evt
{
    /// Status
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Bluetooth Device address
    struct bd_addr      bd_addr;
    ///Link type
    uint8_t             link_type;
    ///Encryption state
    uint8_t             enc_en;
};

/// HCI command complete event structure for qos setup
struct hci_qos_setup_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Flags
    uint8_t flags;
    ///Service type
    uint8_t serv_type;
    ///Token rate
    uint32_t tok_rate;
    ///Peak bandwidth
    uint32_t pk_bw;
    ///Latency
    uint32_t lat;
    ///Delay variation
    uint32_t del_var;
};

/// HCI flow specification complete event parameters structure
struct hci_flow_spec_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Flags
    uint8_t flags;
    ///Flow direction
    uint8_t flow_dir;
    ///Service type
    uint8_t serv_type;
    ///Token rate
    uint32_t tk_rate;
    ///Token buffer size
    uint32_t tk_buf_sz;
    ///Peak bandwidth
    uint32_t pk_bw;
    ///Access latency
    uint32_t acc_lat;
};

/// HCI role change event parameters structure
struct hci_role_chg_evt
{
    ///Status
    uint8_t status;
    ///BD address
    struct bd_addr bd_addr;
    ///New role
    uint8_t new_role;
};

/// HCI complete event structure for the read clock offset command
struct hci_rd_clk_off_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Clock offset
    uint16_t clk_off_val;
};

/// HCI event structure for the flush occurred event
struct hci_flush_occurred_evt
{
    ///Connection handle
    uint16_t conhdl;
};

/// HCI max slot change event structure
struct hci_max_slot_chg_evt
{
    ///Connection handle
    uint16_t conhdl;
    ///Max slot
    uint8_t max_slot;
};

/// HCI sniff subrating event parameters structure
struct hci_sniff_sub_evt
{
    ///Status.
    uint8_t     status;
    ///Connection handle
    uint16_t    conhdl;
    ///Maximum transmit latency
    uint16_t    max_lat_tx;
    ///Maximum receive latency
    uint16_t    max_lat_rx;
    ///Minimum remote TO
    uint16_t    min_rem_to;
    ///Minimum local TO
    uint16_t    min_loc_to;
};

/// HCI read remote extended features complete event parameters structure
struct hci_rd_rem_ext_feats_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///page number
    uint8_t pg_nb;
    ///page number max
    uint8_t pg_nb_max;
    ///ext LMP features
    struct features ext_feats;
};

/// HCI read remote extended features complete event parameters structure
struct hci_rem_host_supp_feats_notif_evt
{
    ///BD address
    struct bd_addr bd_addr;
    ///ext lmp features
    struct features ext_feats;
};

/// HCI command complete event structure for the read remote supported features command
struct hci_rd_rem_supp_feats_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Remote features
    struct features rem_feats;
};

/// HCI command complete event structure for the read remote information version command
struct hci_rd_rem_ver_info_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///LMP version
    uint8_t     vers;
    ///Manufacturer name
    uint16_t    compid;
    ///LMP subversion
    uint16_t    subvers;
};

/// HCI encryption change event structure
struct hci_enc_chg_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Encryption enabled information
    uint8_t     enc_stat;
};

/// HCI mode change event structure
struct hci_mode_chg_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
    ///Current mode
    uint8_t    cur_mode;
    /// Interval
    uint16_t    interv;
};

/// HCI simple pairing complete event structure
struct hci_sp_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Bluetooth Device address
    struct bd_addr      bd_addr;
};

/// HCI Authentication complete event structure
struct hci_auth_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
};

/// HCI change connection link key complete event structure
struct hci_chg_con_lk_cmp_evt
{
    ///Status
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
};

/// HCI encryption key refresh complete event structure
struct hci_enc_key_refresh_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
};

/// HCI master link key complete event structure
struct hci_master_lk_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
    ///Key flag
    uint8_t key_flag;
};
/// HCI synchronous link connection complete event structure
struct hci_sync_con_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
    ///BD address
    struct bd_addr bd_addr;
    ///Link type
    uint8_t lk_type;
    ///Transmit interval
    uint8_t tx_int;
    ///Retransmission window
    uint8_t ret_win;
    ///rx packet length
    uint16_t rx_pkt_len;
    ///tx packet length
    uint16_t tx_pkt_len;
    ///Air mode
    uint8_t air_mode;

};

/// HCI synchronous connection change event structure
struct hci_sync_con_chg_evt
{
    ///Status for command reception
    uint8_t status;
    ///Synchronous Connection handle
    uint16_t    sync_conhdl;
    ///Transmit interval
    uint8_t tx_int;
    ///Retransmission window
    uint8_t ret_win;
    ///rx packet length
    uint16_t rx_pkt_len;
    ///tx packet length
    uint16_t tx_pkt_len;
};

/// HCI connection packet type change event structure
struct hci_con_pkt_type_chg_evt
{
    ///Status for command reception
    uint8_t status;
    ///Synchronous Connection handle
    uint16_t    sync_conhdl;
    ///Synchronous packet type
    uint16_t    pkt_type;
};

/// HCI link supervision timeout change event structure
struct hci_link_supv_to_chg_evt
{
    ///Connection handle
    uint16_t    conhdl;
    ///Link supervision timeout
    uint16_t    lsto_val;
};

/// HCI link key request event structure
struct hci_lk_req_evt
{
    ///BD address
    struct bd_addr bd_addr;
};

/// HCI encryption key refresh event structure
struct hci_enc_key_refresh_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t    conhdl;
};

/// HCI connection request event structure
struct hci_con_req_evt
{
    ///BD address
    struct bd_addr bd_addr;
    ///Class of device
    struct devclass classofdev;
    ///link type
    uint8_t lk_type;
};

/// HCI quality of service violation event structure
struct hci_qos_viol_evt
{
    ///Connection handle
    uint16_t conhdl;
};

/// HCI io capability response event structure
struct hci_io_cap_rsp_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///IO capability
    uint8_t io_capa;
    ///OOB data present
    uint8_t oob_data_pres;
    ///Authentication requirements
    uint8_t auth_req;

};

/// HCI IO capability response event structure
struct hci_io_cap_req_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
};

/// HCI Return link keys event structure
struct hci_return_link_keys_evt
{
    ///Number of Keys
    uint8_t num_keys;
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Key
    struct ltk      key;
};

/// HCI pin code request event structure
struct hci_pin_code_req_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
};

/// HCI user passkey request event structure
struct hci_user_passkey_req_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
};

/// HCI user passkey notification event structure
struct hci_user_passkey_notif_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Passkey
    uint32_t passkey;
};

/// HCI remote OOB data request event structure
struct hci_rem_oob_data_req_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
};

/// HCI user confirmation request event structure
struct hci_user_cfm_req_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Passkey
    uint32_t passkey;
};

/// HCI keypress notification event structure
struct hci_keypress_notif_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///type
    uint8_t type;
};

/// HCI link key notification event structure
struct hci_lk_notif_evt
{
    ///BdAddr
    struct bd_addr  bd_addr;
    ///Key
    struct ltk  key;
    ///type
    uint8_t key_type;
};


/*
 * HCI LE META EVENTS PARAMETERS
 ****************************************************************************************
 */


// LE event structures

/// HCI command complete event structure for the Read Local Supported Features
struct hci_le_rd_local_supp_feats_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///Local LE supported features
    struct le_features  feats;
};

/// HCI command complete event structure for the Read Advertising Channel Tx Power Command
struct hci_rd_adv_chnl_tx_pw_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Advertising channel Tx power level
    int8_t     adv_tx_pw_lvl;
};

///HCI command complete event structure for the Read White List Size Command
struct hci_rd_wlst_size_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///White List size
    uint8_t     wlst_size;
};

///HCI command complete event structure for the Read Buffer Size Command
struct hci_le_rd_buff_size_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///ACL data packet length that can be sent from host to controller
    uint16_t    hc_data_pk_len;
    ///Total number of ACL data packets that can be sent from host to controller.
    uint8_t     hc_tot_nb_data_pkts;
};

///HCI command complete event structure for LE Rand Command
struct hci_le_rand_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///Random number
    struct rand_nb      nb;
};

///HCI command complete event structure for Read Supported States Command
struct hci_rd_supp_states_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///LE supported states response
    struct le_states    states;
};

///HCI command complete event structure for Test End
struct hci_test_end_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///Number of RX packets - null if TX test was the ended one
    uint16_t            nb_packet_received;
};

///HCI LE Encrypt complete event structure
struct hci_le_enc_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t status;
    ///Encrypted data to return to command source.
    uint8_t encrypted_data[ENC_DATA_LEN];
};

#if BLE_EMB_PRESENT || BLE_HOST_PRESENT
///HCI LE advertising report event structure
struct hci_le_adv_report_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Number of advertising reports in this event
    uint8_t             nb_reports;
    ///Advertising reports structures array
    struct adv_report   adv_rep[BLE_ADV_REPORTS_MAX];
};
#endif //BLE_EMB_PRESENT || BLE_HOST_PRESENT

/// HCI command complete event structure for Read Channel Map Command
struct hci_le_rd_chnl_map_cmd_cmp_evt
{
    ///Status of command reception
    uint8_t            status;
    ///Connection handle
    uint16_t           conhdl;
    ///Channel map
    struct le_chnl_map ch_map;
};

/// HCI command complete event structure for Long Term Key Request Reply Command
struct hci_le_ltk_req_reply_cmd_cmp_evt
{
    ///Status of command reception
    uint8_t        status;
    ///Connection handle
    uint16_t       conhdl;
};

/// HCI command complete event structure for Long Term Key Request Negative Reply Command
struct hci_le_ltk_req_neg_reply_cmd_cmp_evt
{
    ///Status of command reception
    uint8_t        status;
    ///Connection handle
    uint16_t       conhdl;
};

/// HCI command complete event structure for LE Read Suggested Default Data Length Command
struct hci_le_rd_suggted_dft_data_len_cmd_cmp_evt
{
    ///Status of command reception
    uint8_t        status;
    ///Host's suggested value for the Controller's maximum transmitted number of payload octets
    uint16_t       suggted_max_tx_octets;
    ///Host's suggested value for the Controller's maximum packet transmission time
    uint16_t       suggted_max_tx_time;
};
/// HCI command complete event structure for LE Read Maximum Data Length Command
struct hci_le_rd_max_data_len_cmd_cmp_evt
{
    ///Status of command reception
    uint8_t        status;
    ///Maximum number of payload octets that the local Controller supports for transmission
    uint16_t       suppted_max_tx_octets;
    ///Maximum time, in microseconds, that the local Controller supports for transmission
    uint16_t       suppted_max_tx_time;
    ///Maximum number of payload octets that the local Controller supports for reception
    uint16_t       suppted_max_rx_octets;
    ///Maximum time, in microseconds, that the local Controller supports for reception
    uint16_t       suppted_max_rx_time;
};

/// HCI LE Read Peer Resolvable Address Command Complete Event
struct hci_le_rd_peer_rslv_addr_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    /// Peer Resolvable Address
    struct bd_addr      peer_rslv_addr;
};

/// HCI LE Read Local Resolvable Address Command Complete Event
struct hci_le_rd_loc_rslv_addr_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    /// Local Resolvable Address
    struct bd_addr      loc_rslv_addr;
};

/// HCI LE Read Resolving List Size Command Complete Event
struct hci_le_rd_rslv_list_size_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    /// Resolving List Size
    uint8_t             size;
};


/// HCI write authenticated payload timeout command
struct hci_wr_auth_payl_to_cmd
{
    ///Connection handle
    uint16_t     conhdl;
    ///Authenticated payload timeout
    uint16_t     auth_payl_to;
};

/// HCI command complete event structure for the Write Authenticated Payload Timeout Command
struct hci_wr_auth_payl_to_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///Connection handle
    uint16_t     conhdl;
};

/// HCI command complete event structure for HCI LE Connection Update Command
struct hci_le_con_update_cmp_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Connection interval value
    uint16_t            con_interval;
    ///Connection latency value
    uint16_t            con_latency;
    ///Supervision timeout
    uint16_t            sup_to;
};

/// HCI command complete event structure for create connection
struct hci_le_con_cmp_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Device role - 0=Master/ 1=Slave
    uint8_t             role;
    ///Peer address type - 0=public/1=random
    uint8_t             peer_addr_type;
    ///Peer address
    struct bd_addr      peer_addr;
    ///Connection interval
    uint16_t            con_interval;
    ///Connection latency
    uint16_t            con_latency;
    ///Link supervision timeout
    uint16_t            sup_to;
    ///Master clock accuracy
    uint8_t             clk_accuracy;
};

/// HCI LE read remote used feature command parameters structure
struct hci_le_rd_rem_used_feats_cmd
{
    ///Connection handle
    uint16_t            conhdl;
};

/// HCI command complete event structure for HCI LE read remote used feature Command
struct hci_le_rd_rem_used_feats_cmd_cmp_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Le Features used
    struct le_features  feats_used;
};

/// HCI command structure for the read transmit power level command
struct hci_rd_tx_pwr_lvl_cmd
{
    ///Connection handle
    uint16_t    conhdl;
    ///Power Level type: current or maximum
    uint8_t     type;
};

/// HCI command complete event structure for the read transmit power level command
struct hci_rd_tx_pwr_lvl_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Value of TX power level
    uint8_t     tx_pow_lvl;
};

/// HCI read remote information version command parameters structure
struct hci_rd_rem_ver_info_cmd
{
    ///Connection handle
    uint16_t    conhdl;
};

/// HCI LE remote connection parameter request event
struct hci_le_rem_con_param_req_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Connection handle
    uint16_t            conhdl;
    ///Interval_Min
    uint16_t            interval_min;
    ///Interval_Max
    uint16_t            interval_max;
    ///Latency
    uint16_t            latency;
    ///Timeout
    uint16_t            timeout;
};


/// HCI command complete event structure for enhance create connection
struct hci_le_enh_con_cmp_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Device role - 0=Master/ 1=Slave
    uint8_t             role;
    ///Peer address type - 0=public/1=random
    uint8_t             peer_addr_type;
    ///Peer address
    struct bd_addr      peer_addr;
    ///Local Resolvable Private Address
    struct bd_addr      loc_rslv_priv_addr;
    ///Peer Resolvable Private Address
    struct bd_addr      peer_rslv_priv_addr;
    ///Connection interval
    uint16_t            con_interval;
    ///Connection latency
    uint16_t            con_latency;
    ///Link supervision timeout
    uint16_t            sup_to;
    ///Master clock accuracy
    uint8_t             clk_accuracy;
};


struct hci_generate_dhkey_cmp_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Status of received command
    uint8_t             status;
    /// The 32 byte Diffie Helman Key
    uint8_t             dh_key[32];
};


struct hci_rd_local_p256_public_key_cmp_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Status of received command
    uint8_t             status;
    /// The 32 byte Diffie Helman Key
    uint8_t             public_key[64];

};

#if BLE_EMB_PRESENT || BLE_HOST_PRESENT
/// HCI LE Direct Advertising Report Event
struct hci_le_dir_adv_rep_evt
{
    ///LE Subevent code
    uint8_t                 subcode;
    ///Number of reports
    uint8_t                 nb_reports;
    ///Direct Advertising reports structures array
    struct dir_adv_report   adv_rep[BLE_ADV_REPORTS_MAX];
};
#endif //BLE_EMB_PRESENT || BLE_HOST_PRESENT

/// HCI command complete event structure for HCI LE read remote used feature Command
struct hci_le_ltk_request_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Connection handle
    uint16_t            conhdl;
    ///Random number
    struct rand_nb      rand;
    ///Encryption diversifier
    uint16_t            ediv;
};

/// HCI LE META event LE Data Length Change Event
struct hci_le_data_len_chg_evt
{
    ///LE Subevent code
    uint8_t             subcode;
    ///Connection handle
    uint16_t            conhdl;
    ///The maximum number of payload octets in TX
    uint16_t            max_tx_octets;
    ///The maximum time that the local Controller will take to TX
    uint16_t            max_tx_time;
    ///The maximum number of payload octets in RX
    uint16_t            max_rx_octets;
    ///The maximum time that the local Controller will take to RX
    uint16_t            max_rx_time;
};


/// HCI Synchronization Train Received Event
struct hci_sync_train_rec_evt
{
    /// Status
    uint8_t            status;
    /// BD_ADDR
    struct bd_addr     bd_addr;
    /// Clock_Offset (28 bits) - (CLKNslave - CLK) modulo 2^28
    uint32_t           clock_offset;
    /// AFH_Channel_Map
    struct chnl_map    afh_ch_map;
    /// LT_ADDR
    uint8_t            lt_addr;
    /// Next_Broadcast_Instant (28 bits)
    uint32_t next_bcst_instant;
    /// Connectionless_Slave_Broadcast_Interval (in slots)
    uint16_t csb_int;
    /// Service_Data
    uint8_t service_data;
};

/// HCI Connectionless Slave Broadcast Receive Event
struct hci_con_slv_bcst_rec_evt
{
    /// BD_ADDR
    struct bd_addr     bd_addr;
    /// LT_ADDR
    uint8_t            lt_addr;
    /// CLK (28 bits)
    uint32_t           clk;
    /// Offset (28 bits) - (CLKNslave - CLK) modulo 2^28
    uint32_t           offset;
    /// Receive Status
    uint8_t            receive_status;
    /// Fragment
    uint8_t fragment;
    /// Data_Length (in bytes)
    uint8_t data_length;
    /// Data
    uint8_t data[__ARRAY_EMPTY];
};

/// HCI Connectionless Slave Broadcast Timeout Event
struct hci_con_slv_bcst_to_evt
{
    /// BD_ADDR
    struct bd_addr     bd_addr;
    /// LT_ADDR
    uint8_t            lt_addr;
};

/// HCI Connectionless Slave Broadcast Channel Map Change Event
struct hci_con_slv_bcst_ch_map_chg_evt
{
    /// Channel_Map
    struct chnl_map    ch_map;
};


struct hci_le_generate_dhkey_cmp_evt
{
    ///LE Subevent code
    uint8_t      subcode;
    uint8_t      status;
    uint8_t      dh_key[32];
};

struct hci_le_generate_p256_public_key_cmp_evt
{
    ///LE Subevent code
    uint8_t       subcode;
    uint8_t       status;
    t_public_key  public_key;
};

/*
 * HCI VENDOR SPECIFIC COMMANDS PARAMETERS
 ****************************************************************************************
 */

/// Buffer structure
struct buffer_tag
{
    /// length of buffer
    uint8_t length;
    /// data of 128 bytes length
    uint8_t data[128];
};

/// Common structure for Command Complete Event of HCI Debug Read Memory/Flash/Param complete event parameters - vendor specific
struct hci_dbg_basic_rd_data_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    ///buffer structure to return
    struct buffer_tag buf;
};

///HCI Debug read memory variable command parameters - vendor specific
struct hci_dbg_rd_mem_cmd
{
    ///Start address to read
    uint32_t start_addr;
    ///Access size
    uint8_t type;
    ///Length to read
    uint8_t length;
};

///HCI Debug write memory variable command parameters - vendor specific
struct hci_dbg_wr_mem_cmd
{
    ///Start address to read
    uint32_t start_addr;
    ///Access size
    uint8_t type;
    ///buffer structure to return
    struct buffer_tag buf;
};

///HCI Debug delete parameter command parameters - vendor specific
struct hci_dbg_del_param_cmd
{
    ///Parameter tag
    uint16_t param_tag;
};

///HCI Debug erase flash command parameters - vendor specific
struct hci_dbg_er_flash_cmd
{
    ///Flash type
    uint8_t flashtype;
    ///Start offset address
    uint32_t startoffset;
    ///Size to erase
    uint32_t size;
};

///HCI Debug write flash command parameters - vendor specific
struct hci_dbg_wr_flash_cmd
{
    ///Flash type
    uint8_t flashtype;
    ///Start offset address
    uint32_t startoffset;
    ///buffer structure
    struct buffer_tag buf;
};

///HCI Debug read flash command parameters - vendor specific
struct hci_dbg_rd_flash_cmd
{
    ///Flash type
    uint8_t flashtype;
    ///Start offset address
    uint32_t startoffset;
    ///Size to read
    uint8_t size;
};

///HCI Debug read parameter command parameters - vendor specific
struct hci_dbg_rd_par_cmd
{
    ///Parameter tag
    uint16_t param_tag;
};

///HCI Debug read parameters command parameters - vendor specific
struct hci_dbg_wr_par_cmd
{
    ///Parameter tag
    uint16_t param_tag;
    ///Structure buffer
    struct buffer_tag buf;
};

#if CRYPTO_UT
struct hci_dbg_test_crypto_func_cmd
{
    /// Id of Function to be tested
    uint8_t function;
    /// Structure buffer
    struct buffer_tag buf;
};
#endif //CRYPTO_UT

///HCI Debug Read Kernel Statistics complete event parameters - vendor specific
struct hci_dbg_rd_ke_stats_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    ///Max message sent
    uint8_t max_msg_sent;
    ///Max message saved
    uint8_t max_msg_saved;
    ///Max timer used
    uint8_t max_timer_used;
    ///Max heap used
    uint16_t max_heap_used;
    ///Max stack used
    uint16_t max_stack_used;
};


/// HCI Debug Read information about memory usage. - vendor specific
struct hci_dbg_rd_mem_info_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    /// memory size currently used into each heaps.
    uint16_t mem_used[KE_MEM_BLOCK_MAX];
    /// peak of memory usage measured
    uint32_t max_mem_used;
};

///HCI Debug identify Flash command complete event parameters - vendor specific
struct hci_dbg_id_flash_cmd_cmp_evt
{
    ///Status
    uint8_t status;
    ///Flash identity
    uint8_t flash_id;
};

///HCI Debug RF Register read command
struct hci_dbg_rf_reg_rd_cmd
{
    /// register address
    uint16_t addr;
};

///HCI Debug RF Register read command complete event
struct hci_dbg_rf_reg_rd_cmd_cmp_evt
{
    /// status
    uint8_t status;
    /// register address
    uint16_t addr;
    /// register value
    uint32_t value;
};

///HCI Debug RF Register write command
struct hci_dbg_rf_reg_wr_cmd
{
    /// register address
    uint16_t addr;
    /// register value
    uint32_t value;
};

///HCI Debug RF Register write command complete event
struct hci_dbg_rf_reg_wr_cmd_cmp_evt
{
    /// status
    uint8_t status;
    /// address
    uint16_t addr;
};

///HCI Debug platform reset command parameters - vendor specific
struct hci_dbg_plf_reset_cmd
{
    /// reason
    uint8_t reason;
};

#if (RW_DEBUG && BT_EMB_PRESENT)
/// Discard LMP Packets
struct hci_dbg_bt_send_lmp_cmd
{
    /// Connection handle
    uint16_t conhdl;
    ///buffer structure to return
    struct buffer_tag buf;
};

/// Discard LMP Packets
struct hci_dbg_bt_discard_lmp_en_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Enable/Disable LMP discard (0: disable / 1: enable)
    uint8_t enable;
};

/// Set local clock
struct hci_dbg_set_local_clock_cmd
{
    /// Clock (in half-slots)
    uint32_t clock;
};
#endif //(RW_DEBUG && BT_EMB_PRESENT)

#if (RW_WLAN_COEX)
///HCI Debug wlan coexistence command parameters - vendor specific
struct hci_dbg_wlan_coex_cmd
{
    /// State
    uint8_t state;
};
#if (RW_WLAN_COEX_TEST)
///HCI Debug wlan coexistence test scenario command parameters - vendor specific
struct hci_dbg_wlan_coextst_scen_cmd
{
    /// Scenario
    uint32_t scenario;
};
#endif //RW_WLAN_COEX_TEST
#endif //RW_WLAN_COEX

#if (RW_MWS_COEX)
///HCI Debug mws coexistence command parameters - vendor specific
struct hci_dbg_mws_coex_cmd
{
    /// State
    uint8_t state;
};
#if (RW_MWS_COEX_TEST)
///HCI Debug mws coexistence test scenario command parameters - vendor specific
struct hci_dbg_mws_coextst_scen_cmd
{
    /// Scenario
    uint32_t scenario;
};
#endif //RW_MWS_COEX_TEST
#endif //RW_MWS_COEX

///HCI Debug HW Register Read command parameters - vendor specific
struct hci_dbg_hw_reg_rd_cmd
{
    /// register address
    uint16_t reg_addr;
};

///HCI Debug HW Register write command parameters - vendor specific
struct hci_dbg_hw_reg_wr_cmd
{
    /// register address
    uint16_t reg_addr;
    /// extra parameter
    uint16_t reserved;
    /// register value
    uint32_t reg_value;
};

///HCI Debug HW Register Read Complete event parameters - vendor specific
struct hci_dbg_hw_reg_rd_cmd_cmp_evt
{
    /// status
    uint8_t  status;
    /// register address
    uint16_t reg_addr;
    /// register value
    uint32_t reg_value;
};

///HCI Debug HW Register Write Complete event parameters - vendor specific
struct hci_dbg_hw_reg_wr_cmd_cmp_evt
{
    /// status
    uint8_t  status;
    /// register address
    uint16_t reg_addr;
};

///HCI Debug write DLE default value command parameters - vendor specific
struct hci_dbg_wr_dle_dft_value_cmd
{
    /// Max transmit packet size supported
    uint16_t suppted_max_tx_octets;
    /// Max transmit packet time supported
    uint16_t suppted_max_tx_time;
    /// Max receive packet size supported
    uint16_t suppted_max_rx_octets;
    /// Max receive packet time supported
    uint16_t suppted_max_rx_time;

};

#if (BLE_EMB_PRESENT || BLE_HOST_PRESENT)
///HCI Debug bd address write command parameters - vendor specific
struct hci_dbg_set_bd_addr_cmd
{
    ///bd address to set
    struct bd_addr addr;
};

///HCI Debug crc write command parameters - vendor specific
struct hci_dbg_set_crc_cmd
{
    /// Handle pointing to the connection for which CRC has to be modified
    uint16_t conhdl;
    /// CRC to set
    struct crc_init crc;
};

///HCI Debug LLC discard command parameters - vendor specific
struct hci_dbg_llcp_discard_cmd
{
    /// Handle pointing to the connection for which LLCP commands have to be discarded
    uint16_t conhdl;
    /// Flag indicating if the discarding has to be enabled or disabled
    uint8_t enable;
};

///HCI Debug reset RX counter command parameters - vendor specific
struct hci_dbg_reset_rx_cnt_cmd
{
    /// Handle pointing to the connection for which the counter have to be reseted
    uint16_t conhdl;
};

///HCI Debug reset TX counter command parameters - vendor specific
struct hci_dbg_reset_tx_cnt_cmd
{
    /// Handle pointing to the connection for which the counter have to be reseted
    uint16_t conhdl;
};

///HCI Debug Set TX Power Level Command parameters
struct hci_dbg_set_tx_pw_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Power level
    uint8_t  pw_lvl;
};

///HCI Debug configure audio command parameters - vendor specific

struct hci_vs_audio_configure_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Voice channel to be updated
    uint8_t     voice_channel;
    /// Configure transmitter size in bytes
    uint8_t     tx_size;
    /// Configure receiver size in bytes
    uint8_t     rx_size;
    /// Configure transmitter rate
    uint8_t     tx_rate;
    /// Configure receiver rate
    uint8_t     rx_rate;
    /// Configure number of retransmission
    uint8_t     nb_retx;
    /// Audio link priority
    uint8_t     priority;
    /// Encryption mode
    uint8_t     enc_mode;
    /// Channel and mute configuration (@see enum audio_cfg)
    uint8_t     chan_mute_cfg;
    /// Mute Pattern
    uint8_t     mute_pattern;
    /// Audio interval in frame
    uint16_t    interval;
};

struct hci_vs_audio_set_pointer_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Voice channel to be updated
    uint8_t voice_channel;
    /// Rx or Tx selection
    uint8_t rx_tx_select;
    /// Tog to be updated
    uint8_t tog;
    /// Exchange memory pointer
    uint16_t    em_ptr;
};
///HCI Debug set audio mode command parameters - vendor specific.
struct hci_vs_audio_set_mode_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Voice channel to be updated
    uint8_t voice_channel;
    /// Mode
    uint8_t   mode;
};

///HCI Debug set audio mode command parameters - vendor specific
struct hci_vs_audio_reset_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Voice channel to be updated
    uint8_t voice_channel;
};

///HCI Debug set audio mode command parameters - vendor specific
struct hci_vs_audio_allocate_cmd
{
    /// Connection handle
    uint16_t conhdl;
};

///HCI Debug get audio buffer range - vendor specific
struct hci_vs_audio_get_buffer_range_cmd
{
    /// Rx or Tx selection
    uint8_t rx_tx_select;
};


///HCI VS basic command complete event - vendor specific
struct hci_vs_audio_cmd_cmp_evt
{
    /// status
    uint8_t status;
    /// Connection handle
    uint16_t conhdl;
};


///HCI Debug allocate audio voice channel complete event - vendor specific
struct hci_vs_audio_allocate_cmd_cmp_evt
{
    /// status
    uint8_t status;
    /// Connection handle
    uint16_t conhdl;
    /// voice channel allocated
    uint8_t voice_channel;
};

///HCI Debug get audio buffer range complete event - vendor specific
struct hci_vs_audio_get_buffer_range_cmd_cmp_evt
{
    /// status
    uint8_t status;
    /// start address
    uint32_t base_address;
    /// end address
    uint32_t end_address;
};
#if (BLE_TESTER)
///HCI Tester set LE parameters
struct hci_tester_set_le_params_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Tester features
    uint8_t  tester_feats;
    /// Preferred periodicity
    uint8_t  pref_period;
    /// Offset0
    uint16_t  offset0;
    /// Offset1
    uint16_t  offset1;
    /// Offset2
    uint16_t  offset2;
    /// Offset3
    uint16_t  offset3;
    /// Offset4
    uint16_t  offset4;
    /// Offset5
    uint16_t  offset5;
};

/// HCI BLE Tester: enable LLCP pass through mechanism
struct hci_dbg_ble_tst_llcp_pt_en_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// Enable or not LLCP pass through mechanism
    uint8_t  enable;
};

/// HCI BLE Tester: send an LLCP PDU
struct hci_dbg_ble_tst_send_llcp_cmd
{
    /// Connection handle
    uint16_t conhdl;
    /// length of LLCP PDU
    uint8_t  length;
    /// LLCP PDU data
    uint8_t data[26];
};


/// HCI DBG Meta Event trigg when LLCP message received with LLCP pass through mechanism
struct hci_dbg_ble_tst_llcp_recv_evt
{
    ///DBG Subevent code
    uint8_t             subcode;
    ///Connection handle
    uint16_t            conhdl;
    /// length of LLCP message
    uint8_t             length;
    /// LLCP data
    uint8_t             data[26];
};

#endif //(BLE_TESTER)

#endif //BLE_EMB_PRESENT || BLE_HOST_PRESENT

#if (RW_DEBUG)
/// HCI DBG Meta Event indicating a SW assertion error
struct hci_dbg_assert_err_evt
{
    ///DBG Subevent code
    uint8_t             subcode;
    /// Line number
    uint32_t line;
    /// Param0
    uint32_t param0;
    /// Param1
    uint32_t param1;
    /// File name
    uint8_t file[__ARRAY_EMPTY];
};
#endif //(RW_DEBUG)


/// @} CO_BT
#endif // CO_HCI_H_
