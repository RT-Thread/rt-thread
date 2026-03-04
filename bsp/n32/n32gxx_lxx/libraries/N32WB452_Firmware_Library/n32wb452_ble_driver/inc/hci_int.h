/**
 ****************************************************************************************
 *
 * @file hci.h
 *
 * @brief This file contains definitions related to the HCI module.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef HCI_INT_H_
#define HCI_INT_H_

/**
 ****************************************************************************************
 * @addtogroup HCI Host Controller Interface
 *@{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"       // SW configuration

#if (HCI_PRESENT)

#include <stddef.h>          // standard definition
#include <stdint.h>          // standard integer
#include "co_bt.h"           // BT standard definitions

#include "ke_msg.h"          // Kernel message definitions

/*
 * DEFINES
 ****************************************************************************************
 */

/// Macro to get OCF of a known command
#define OCF(cmd)        (HCI_OP2OCF(HCI_##cmd##_CMD_OPCODE))

/// Unknown opcode identifier
#define HCI_OPCODE_UNKNOWN                 0xFFFF

/**
 * Destination field decoding
 *
 * bit |     7 6      | 5 4 | 3..0 |
 * def | Rsvd (pkupk) |  HL |  LL  |
 */
#define HCI_CMD_DEST_LL_POS           0
#define HCI_CMD_DEST_LL_MASK          0x0F
#define HCI_CMD_DEST_HL_POS           4
#define HCI_CMD_DEST_HL_MASK          0x30

/**
 * Destination field decoding
 *
 * bit | 7..2 | 1 0 |
 * def | Rsvd |  HL |
 */
#define HCI_EVT_DEST_HL_POS           0
#define HCI_EVT_DEST_HL_MASK          0x03

#if (HCI_TL_SUPPORT)

/// Special Pack-Unpack settings for HCI commands (parameters and return parameters)
/**
 * Special Pack-Unpack settings for HCI commands (parameters and return parameters)
 *
 * bit |    7    |  6  | 5..0 |
 * def | RET PAR | PAR | Rsvd |
 */
#define HCI_CMD_DEST_SPEC_PAR_PK_POS        6
#define HCI_CMD_DEST_SPEC_PAR_PK_MSK        0x40
#define HCI_CMD_DEST_SPEC_RET_PAR_PK_POS    7
#define HCI_CMD_DEST_SPEC_RET_PAR_PK_MSK    0x80
#define PK_GEN_GEN   (0x00)
#define PK_GEN_SPE   (HCI_CMD_DEST_SPEC_RET_PAR_PK_MSK)
#define PK_SPE_GEN   (HCI_CMD_DEST_SPEC_PAR_PK_MSK)
#define PK_SPE_SPE   (HCI_CMD_DEST_SPEC_RET_PAR_PK_MSK | HCI_CMD_DEST_SPEC_PAR_PK_MSK)

/// Special Pack settings for HCI events
#define PK_GEN           0x00
#define PK_SPE           0x01

/// Macro for building a command descriptor in split mode (with parameters packing/unpacking)
#define CMD(opcode, dest_ll, dest_hl, pkupk, par_size_max, par_fmt, ret_fmt)  {HCI_##opcode##_CMD_OPCODE, (dest_ll<<HCI_CMD_DEST_LL_POS) | (dest_hl<<HCI_CMD_DEST_HL_POS) | pkupk, par_size_max, (void*)par_fmt, (void*)ret_fmt}
/// Macro for building an event descriptor in split mode (with parameters packing/unpacking)
#define EVT(code, dest_hl, pkupk, par_fmt)                      {HCI_##code##_EVT_CODE, (dest_hl<<HCI_EVT_DEST_HL_POS), pkupk, (void*)par_fmt}
/// Macro for building an event descriptor in split mode (with parameters packing/unpacking)
#define LE_EVT(subcode, dest_hl, pkupk, par_fmt)                {HCI_##subcode##_EVT_SUBCODE, (dest_hl<<HCI_EVT_DEST_HL_POS), pkupk, (void*)par_fmt}
/// Macro for building an event descriptor in split mode (with parameters packing/unpacking)
#define DBG_EVT(subcode, dest_hl, pkupk, par_fmt)               {HCI_##subcode##_EVT_SUBCODE, (dest_hl<<HCI_EVT_DEST_HL_POS), pkupk, (void*)par_fmt}

#else //(HCI_TL_SUPPORT)

/// Macro for building a command descriptor in full mode (without parameters packing/unpacking)
#define CMD(opcode, dest_ll, dest_hl, pkupk, par_size_max, par_fmt, ret_fmt)  {HCI_##opcode##_CMD_OPCODE, (dest_ll<<HCI_CMD_DEST_LL_POS) | (dest_hl<<HCI_CMD_DEST_HL_POS)}
/// Macro for building an event descriptor in full mode (without parameters packing/unpacking)
#define EVT(code, dest_hl, pkupk, par_fmt)                      {HCI_##code##_EVT_CODE, (dest_hl<<HCI_EVT_DEST_HL_POS)}
/// Macro for building an event descriptor in full mode (without parameters packing/unpacking)
#define LE_EVT(subcode, dest_hl, pkupk, par_fmt)                {HCI_##subcode##_EVT_SUBCODE, (dest_hl<<HCI_EVT_DEST_HL_POS)}
/// Macro for building an event descriptor in full mode (without parameters packing/unpacking)
#define DBG_EVT(subcode, dest_hl, pkupk, par_fmt)                {HCI_##subcode##_EVT_SUBCODE, (dest_hl<<HCI_EVT_DEST_HL_POS)}

#endif //(HCI_TL_SUPPORT)

/*
 * ENUMERATIONS DEFINITIONS
 ****************************************************************************************
 */

/// Possible destination field values within lower layers
enum HCI_MSG_DEST_LL
{
    MNG,
    CTRL,
    BLE_MNG,
    BLE_CTRL,
    BT_MNG,
    BT_CTRL_CONHDL,
    BT_CTRL_BD_ADDR,
    BT_BCST,
    DBG,
    LL_UNDEF,
};

/// Possible destination field values within higher layers
enum HCI_MSG_DEST_HL
{
    HL_MNG,
    HL_CTRL,
    HL_DATA,
    HL_AM0,
    HL_UNDEF,
};

#if (HCI_TL_SUPPORT)
/// Status returned by generic packer-unpacker
enum HCI_PACK_STATUS
{
    HCI_PACK_OK,
    HCI_PACK_IN_BUF_OVFLW,
    HCI_PACK_OUT_BUF_OVFLW,
    HCI_PACK_WRONG_FORMAT,
    HCI_PACK_ERROR,
};
#endif //(HCI_TL_SUPPORT)

#if  (BT_EMB_PRESENT)
/// Status of BT ACL connection at HCI level
enum HCI_BT_ACL_CON_STATUS
{
    /// ACL link not active
    HCI_BT_ACL_STATUS_NOT_ACTIVE,
    /// ACL link ID associated with BD address
    HCI_BT_ACL_STATUS_BD_ADDR,
    /// ACL link ID associated with BD address + connection handle
    HCI_BT_ACL_STATUS_BD_ADDR_CONHDL,
};
#endif //(BT_EMB_PRESENT)


/*
 * STRUCTURES DEFINITIONS
 ****************************************************************************************
 */

/// HCI command descriptor structure
struct hci_cmd_desc_tab_ref
{
    /// OpCode Group Field (OGF)
    uint8_t ogf;

    /// Number of commands supported in this group
    uint16_t nb_cmds;

    /// Command descriptor table
    const struct hci_cmd_desc_tag* cmd_desc_tab;
};

/// HCI command descriptor structure
struct hci_cmd_desc_tag
{
    /// Command opcode with flags indicating if a special packing or unpacking is needed
    uint16_t opcode;

    /// Destination field (used to find the internal destination task)
    uint8_t dest_field;

    #if (HCI_TL_SUPPORT)
    /// Maximum size of the parameters
    uint8_t  par_size_max;

    /// Parameters format string (or special unpacker)
    void* par_fmt;

    /// Return parameters format string (or special unpacker)
    void* ret_par_fmt;
    #endif //(HCI_TL_SUPPORT)
};

/// HCI event descriptor structure
struct hci_evt_desc_tag
{
    /// Event opcode
    uint8_t code;

    /// Destination field (used to find the internal destination task)
    uint8_t dest_field;

    #if (HCI_TL_SUPPORT)
    /// Flag indicating if a special packing is needed
    uint8_t  special_pack;

    /// Parameters format string (or special unpacker)
    void* par_fmt;
    #endif //(HCI_TL_SUPPORT)
};

#if (HCI_TL_SUPPORT)
/// HCI pack/unpack function pointer type definition
typedef uint16_t (*hci_pkupk_func_t)(uint8_t *out, uint8_t *in, uint16_t* out_len, uint16_t in_len);
#endif //(HCI_TL_SUPPORT)

#if (BT_EMB_PRESENT)
/// HCI Environment context structure
struct hci_bt_acl_con_tag
{
        /**
         * BT ACL connection status
         * - 0x00: Not active
         * - 0x01: link ID associated with BD address
         * - 0x02: link ID associated with BD address + connection handle
         */
        uint8_t state;

        /// BD address associated with link ID
        struct bd_addr bd_addr;
};

/// Condition based on class of device
struct classofdevcondition
{
    /// Class of device
    struct devclass classofdev;
    /// Device mask
    struct devclass class_mask;
};

/// Condition based on device class
union cond
{
    /// Device class
    struct classofdevcondition device_class;
    /// BD address
    struct bd_addr bdaddr;
};

/// Event Filter Record
struct hci_evt_filter_tag
{
    bool        in_use;
    uint8_t     type;
    uint8_t     condition;
    uint8_t     auto_accept;
    union cond  param;
};
#elif (BLE_HOST_PRESENT && !BLE_EMB_PRESENT)
/// HCI Environment context structure
struct hci_ble_acl_con_tag
{
    /// Code
    uint8_t code;
};

#endif //(BT_EMB_PRESENT || (BLE_HOST_PRESENT && !BLE_EMB_PRESENT))

/// HCI Environment context structure
struct hci_env_tag
{
    /// Event mask
    struct evt_mask evt_msk;

    /// Event mask page 2
    struct evt_mask evt_msk_page_2;

    #if (BT_EMB_PRESENT)
    /// Link association table for BT link-oriented messages routing
    struct hci_bt_acl_con_tag bt_acl_con_tab[MAX_NB_ACTIVE_ACL];

    /// Event filters
    struct hci_evt_filter_tag evt_filter[HCI_FILTER_NB];

    /**
     * Current auto-accept command opcode, used to filter the associated CS event
     * Note: assume that there would be 1 auto accept command at the same time
     * Note: could be HCI_Accept_Con, HCI_Accept_sync_Con
     */
    uint16_t auto_accept_opcode;

    #if (MAX_NB_SYNC > 0)
    /**
     * Voice settings used when SCO connection is auto-accepted
     */
    uint16_t voice_settings;
    #endif //(MAX_NB_SYNC > 0)

    /**
     * Auto-reject flag, used to filter the complete event when a request has been auto-rejected
     */
    bool auto_reject;

    #elif (BLE_HOST_PRESENT && !BLE_EMB_PRESENT && (BLE_CENTRAL || BLE_PERIPHERAL))
    /// Link association table for BLE link-oriented messages routing
    struct hci_ble_acl_con_tag ble_acl_con_tab[BLE_CONNECTION_MAX];

    #endif //(BT_EMB_PRESENT || (BLE_HOST_PRESENT && !BLE_EMB_PRESENT))
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

#if BLE_HOST_PRESENT
extern const uint8_t hl_task_type[];
#endif //BLE_HOST_PRESENT

///HCI environment context
extern struct hci_env_tag hci_env;


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
****************************************************************************************
* @brief Look for a command descriptor that could match with the specified opcode
*
* @param[in]  opcode   Command opcode
*
* @return     Pointer the command descriptor (NULL if not found)
*****************************************************************************************
*/
const struct hci_cmd_desc_tag* hci_look_for_cmd_desc(uint16_t opcode);

/**
****************************************************************************************
* @brief Look for an event descriptor that could match with the specified event code
*
* @param[in]  code   event code
*
* @return     Pointer the event descriptor (NULL if not found)
*****************************************************************************************
*/
const struct hci_evt_desc_tag* hci_look_for_evt_desc(uint8_t code);


/**
****************************************************************************************
* @brief Look for an event descriptor that could match with the specified DBG subcode
*
* @param[in]  subcode   DBG event subcode
*
* @return     Pointer the event descriptor (NULL if not found)
*****************************************************************************************
*/
const struct hci_evt_desc_tag* hci_look_for_dbg_evt_desc(uint8_t subcode);

#if (BLE_EMB_PRESENT || BLE_HOST_PRESENT)
/**
****************************************************************************************
* @brief Look for an event descriptor that could match with the specified LE subcode
*
* @param[in]  subcode   LE event subcode
*
* @return     Pointer the event descriptor (NULL if not found)
*****************************************************************************************
*/
const struct hci_evt_desc_tag* hci_look_for_le_evt_desc(uint8_t subcode);

#endif //(BLE_EMB_PRESENT || BLE_HOST_PRESENT)

#if (HCI_TL_SUPPORT)
/**
 ****************************************************************************************
 * @brief Initialize HIC TL part
 *****************************************************************************************
 */
void hci_tl_init(bool reset);

/**
 ****************************************************************************************
 * @brief Send an HCI message over TL
 *
 * @param[in]   msg   Kernel message carrying the HCI message
 *****************************************************************************************
 */
void hci_tl_send(struct ke_msg *msg);

/**
 ****************************************************************************************
 * @brief Pack parameters
 *
 * This function packs parameters according to a specific format. It takes care of the
 * endianess, padding, required by the compiler.
 *
 * @param[inout]   inout       Data Buffer
 * @param[inout]   inout_len   Input: buffer size / Output: size of packed data
 * @param[in]      format      Parameters format
 *
 * @return  Status of the packing operation
 *****************************************************************************************
 */
enum HCI_PACK_STATUS hci_util_pack(uint8_t* inout, uint16_t* inout_len, const char* format);

/**
 ****************************************************************************************
 * @brief Unpack parameters
 *
 * This function unpacks parameters according to a specific format. It takes care of the
 * endianess, padding, required by the compiler.
 *
 * Note: the buffer provided must be large enough to contain the unpacked data.
 *
 * @param[out]    out         Unpacked parameters buffer
 * @param[in]     in          Packed parameters buffer
 * @param[inout]  out_len     Input: buffer size / Output: size of unpacked data
 * @param[in]     in_len      Size of the packed data
 * @param[in]     format      Parameters format
 *
 * @return  Status of the unpacking operation
 *****************************************************************************************
 */
enum HCI_PACK_STATUS hci_util_unpack(uint8_t* out, uint8_t* in, uint16_t* out_len, uint16_t in_len, const char* format);
#endif //(HCI_TL_SUPPORT)

/**
 ****************************************************************************************
 * @brief Initialize Flow Control Structure
 *
 *****************************************************************************************
 */
void hci_fc_init(void);

/**
 ****************************************************************************************
 * @brief count ACL packets sent to Host
 *
 *****************************************************************************************
 */
void hci_fc_acl_packet_sent(void);

/**
 ****************************************************************************************
 * @brief count SCO packets sent to Host
 *
 *****************************************************************************************
 */
void hci_fc_sync_packet_sent(void);

/**
 ****************************************************************************************
 * @brief Calculate number of ACL packets slots available on Host side
 *
 * @return number of packets available
 *****************************************************************************************
 */
uint16_t hci_fc_check_host_available_nb_acl_packets(void);

/**
 ****************************************************************************************
 * @brief Calculate number of SCO packets slots available on Host side
 *
 * @return number of packets available
 *****************************************************************************************
 */
uint16_t hci_fc_check_host_available_nb_sync_packets(void);


#endif //HCI_PRESENT

/// @} HCI

#endif // HCI_INT_H_
