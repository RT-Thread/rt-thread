/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup LAYER3_SWITCH
 * @{
 **********************************************************************************************************************/

#ifndef R_LAYER3_SWITCH_H
#define R_LAYER3_SWITCH_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_layer3_switch_cfg.h"
#include "r_ether_switch_api.h"
#include "r_ether_phy_api.h"
#include "r_gptp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** GWCA descriptor. */
typedef struct st_layer3_switch_basic_descriptor
{
#if ((defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || (defined(__ARMCC_VERSION) && \
    !defined(__ARM_BIG_ENDIAN)) || (defined(__ICCARM__) && (__LITTLE_ENDIAN__)))

    /* Little endian. */
    volatile uint8_t  ds_l;            ///< 0.. 8 (8 bits),   Descriptor size (low).
    volatile uint8_t  ds_h  : 4;       ///< 9..12 (4 bits),   Descriptor size (High).
    volatile uint8_t  info0 : 4;       ///< 12..15 (4 bits),  Information 0.
    volatile uint8_t  err   : 3;       ///< 16..18 (3 bits),  Error, data size error, AXI bus error.
    volatile uint8_t  die   : 1;       ///< 19 (1 bit),       Descriptor interrupt enable.
    volatile uint8_t  dt    : 4;       ///< 20..23 (4 bits),  Descriptor type.
    volatile uint8_t  ptr_h;           ///< 24..31 (8 bits),  Pointer (High).
    volatile uint32_t ptr_l;           ///< 32..63 (32 bits), Pointer (Low).
#endif
} layer3_switch_basic_descriptor_t;

/** GWCA extended descriptor. */
typedef struct st_layer3_switch_descriptor
{
    /* Little endian. */
#if ((defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || (defined(__ARMCC_VERSION) && \
    !defined(__ARM_BIG_ENDIAN)) || (defined(__ICCARM__) && (__LITTLE_ENDIAN__)))

    volatile layer3_switch_basic_descriptor_t basic; ///< Basic descriptor fields.

    /* Extended descriptor fields. */
    union
    {
        /* INFO1 of RX descriptor. */
        struct st_info1_rx
        {
            volatile uint8_t  fi      : 1;   ///< 0 (1 bit),        FCS in.
            volatile uint8_t  sec     : 1;   ///< 1 (1 bit),        Secure descriptor.
            volatile uint8_t  fmt     : 1;   ///< 2 (1 bit),        Descriptor format.
            volatile uint8_t  txc     : 1;   ///< 3 (1 bit),        TX Time stamp capture.
            volatile uint8_t  iet     : 1;   ///< 4 (1 bit),        Time stamp insertion request.
            volatile uint8_t  crt     : 1;   ///< 5 (1 bit),        Residence time calculation request.
            volatile uint8_t  tn      : 1;   ///< 6 (1 bit),        Timer utilized for capture/insertion.
            volatile          uint8_t : 1;   ///< 7 (1 bit),        Reserved.
            volatile uint8_t  tsun;          ///< 8..15 (8 bits),   Time stamp unique number.
            volatile uint8_t  saef;          ///< 16..23 (8 bits),  Source agent error flags.
            volatile uint8_t  rn;            ///< 24..31 (8 bits),  Routing number.
            volatile          uint32_t :  3; ///< 32..34 (3 bits),  Reserved.
            volatile uint32_t rv       : 1;  ///< 35 (1 bit),       Routing valid.
            volatile uint32_t spn      : 3;  ///< 36..38 (3 bits),  Source port number.
            volatile          uint32_t : 1;  ///< 39 (1 bit),       Reserved.
            volatile uint32_t fesf     : 24; ///< 40..63 (24 bits), Forwarding engine status flags.
        } info1_rx;

        /* INFO1 of TX descriptor. */
        struct st_info1_tx
        {
            volatile uint8_t fi      : 1; ///< 0 (1 bit),       FCS in.
            volatile uint8_t sec     : 1; ///< 1 (1 bit),       Secure descriptor.
            volatile uint8_t fmt     : 1; ///< 2 (1 bit),       Descriptor format.
            volatile uint8_t txc     : 1; ///< 3 (1 bit),       TX Time stamp capture.
            volatile uint8_t iet     : 1; ///< 4 (1 bit),       Time stamp insertion request.
            volatile uint8_t crt     : 1; ///< 5 (1 bit),       Residence time calculation request.
            volatile uint8_t tn      : 1; ///< 6 (1 bit),       Timer utilized for capture/insertion.
            volatile         uint8_t : 1; ///< 7 (1 bit),       Reserved.
            volatile uint8_t tsun;        ///< 8..15 (8 bits),  Time stamp unique number.
            volatile uint8_t rn;          ///< 16..23 (8 bits), Routing number.
            volatile         uint8_t : 3; ///< 24..26 (3 bits), Reserved.
            volatile uint8_t rv      : 1; ///< 27 (1 bit),      Routing valid.
            volatile uint8_t ipv     : 3; ///< 28..30 (3 bits), Internal priority value.
            volatile uint8_t fw      : 1; ///< 31 (1 bit),      FCS contained in frame is wrong.
            volatile uint8_t csd0    : 7; ///< 32..38 (7 bits), CPU sub destination for GWCA0.
            volatile         uint8_t : 1; ///< 39 (1 bit),      Reserved.
            volatile uint8_t reserved1;   ///< 40..47 (8 bits), Reserved.
            volatile uint8_t dv      : 7; ///< 48..54 (7 bits), Destination vector.
            volatile         uint8_t : 1; ///< 55 (1 bit),      Reserved.
            volatile uint8_t reserved2;   ///< 56..63 (8 bits), Reserved.
        } info1_tx;
    };

 #if LAYER3_SWITCH_CFG_GPTP_ENABLE

    /* Reception descriptor TS fields. */
    union
    {
        /* Reception direct descriptor TS. */
        struct st_reception_direct_descriptor
        {
            volatile uint8_t  csd0    : 7; ///< 0..6 (7 bit),    CPU sub destination for GWCA0
            volatile          uint8_t : 1; ///< 7 (1 bit),       Reserved
            volatile uint8_t  csd1    : 7; ///< 8..14 (7 bit),   CPU sub destination for GWCA1
            volatile          uint8_t : 1; ///< 15 (1 bit),      Reserved
            volatile uint8_t  dv      : 7; ///< 16..22 (7 bit),  Destination vector
            volatile          uint8_t : 1; ///< 23 (1 bit),      Reserved
            volatile uint8_t  reserved1;   ///< 24..31 (8 bit),  Reserved
            volatile uint32_t reserved2;   ///< 32..63 (32 bit), Reserved
        } reception_direct_descriptor;

        /* Reception ethernet descriptor TS. */
        struct st_reception_ethernet_descriptor
        {
            volatile uint32_t tsns : 30; ///< 0..29 (30 bit),  Timestamp nanosecond [gPTP] PCH header timestamp
            volatile uint32_t tsv  : 1;  ///< 30 (1 bit),      Timestamp valid
            volatile uint32_t tsd  : 1;  ///< 31 (1 bit),      Timestamp default
            volatile uint32_t tss;       ///< 32..63 (32 bit), Timestamp second [gPTP] PCH header timestamp
        } reception_ethernet_descriptor;
    };
 #endif
#endif
} layer3_switch_descriptor_t;

/**
 * GWCA TS reception process descriptor.
 */
typedef struct st_layer3_switch_ts_reception_process_descriptor
{
    /* Little endian. */
#if ((defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || (defined(__ARMCC_VERSION) && \
    !defined(__ARM_BIG_ENDIAN)) || (defined(__ICCARM__) && (__LITTLE_ENDIAN__)))
    union
    {
        struct st_ts_reception_descriptor_basic
        {
            volatile uint8_t  ds_l;      ///< 0..7 (8 bit),     Descriptor size
            volatile uint8_t  ds_h  : 4; ///< 8..11 (4 bit),    Descriptor size
            volatile uint8_t  info0 : 4; ///< 12..15 (4 bit),   Information 0
            volatile uint8_t  err   : 1; ///< 16 (1 bit),       Error
            volatile uint8_t  dse   : 1; ///< 17 (1 bit),       Data Size Error
            volatile uint8_t  axie  : 1; ///< 18 (1 bit),       AXI Bus Error
            volatile uint8_t  die   : 1; ///< 19 (1 bit),       Descriptor Interrupt Enable
            volatile uint8_t  dt    : 4; ///< 20..23 (4 bit),   Descriptor Type
            volatile uint8_t  ptr_h;     ///< 24..31 (8 bit),   Pointer
            volatile uint32_t ptr_l;     ///< 32..63 (32 bit),  Pointer
            volatile uint32_t reserved1; ///< 64..95 (32 bit),  Reserved
            volatile uint32_t reserved2; ///< 96..127 (32 bit), Reserved
        } ts_reception_descriptor_basic;

        struct st_ts_reception_descriptor_result
        {
            volatile uint8_t  ds_l;          ///< 0..7 (8 bit),     Descriptor size
            volatile uint8_t  ds_h  : 4;     ///< 8..11 (4 bit),    Descriptor size
            volatile uint8_t  info0 : 4;     ///< 12..15 (4 bit),   Information 0
            volatile uint8_t  err   : 1;     ///< 16 (1 bit),       Error
            volatile uint8_t  dse   : 1;     ///< 17 (1 bit),       Data Size Error
            volatile uint8_t  axie  : 1;     ///< 18 (1 bit),       AXI Bus Error
            volatile uint8_t  die   : 1;     ///< 19 (1 bit),       Descriptor Interrupt Enable
            volatile uint8_t  dt    : 4;     ///< 20..23 (4 bit),   Descriptor Type
            volatile uint8_t  ptr;           ///< 24..31 (8 bit),   Pointer
            volatile uint8_t  tsun;          ///< 32..39 (8 bit),   Timestamp unique number
            volatile uint8_t  spn      : 2;  ///< 40..41 (2 bit),   Port number from which the timestamp corresponding frame entered the switch
            volatile          uint8_t  : 6;  ///< 42..47 (6 bit),   Reserved
            volatile uint8_t  dpn      : 1;  ///< 48 (1 bit),       Port number by which the timestamp has been taken
            volatile          uint8_t  : 7;  ///< 49..55 (7 bit),   Reserved
            volatile uint8_t  tn       : 1;  ///< 56 (1 bit),       Timer Number
            volatile          uint8_t  : 7;  ///< 57..63 (7 bit),   Reserved
            volatile uint32_t tsns     : 30; ///< 64..93 (30 bit),  Timestamp nanosecond
            volatile          uint32_t : 2;  ///< 94..95 (2 bit),   Reserved
            volatile uint32_t tss;           ///< 96..127 (32 bit), Timestamp second
        } ts_reception_descriptor_result;
    };
#endif
} layer3_switch_ts_reception_process_descriptor_t;

/** GWCA descriptor type. */
typedef enum e_layer3_switch_descriptor_type
{
    LAYER3_SWITCH_DESCRIPTOR_TYPE_LINKFIX      = 0U,  ///< Linkfix. Control element pointing to next descriptor in chain.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_IS    = 1U,  ///< Frame Empty Incremental Start.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_IC    = 2U,  ///< Frame Empty Incremental Continue.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_ND    = 3U,  ///< Frame Empty No Data Storage.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY       = 4U,  ///< Frame Empty.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_START = 5U,  ///< Frame Empty Start.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_MID   = 6U,  ///< Frame Empty Mid.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_END   = 7U,  ///< Frame Empty End.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FSINGLE      = 8U,  ///< Frame Single.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FSTART       = 9U,  ///< Frame Start.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FMID         = 10U, ///< Frame Mid.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_FEND         = 11U, ///< Frame End.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY       = 12U, ///< Link Empty.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_EEMPTY       = 13U, ///< EOS Empty.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_LINK         = 14U, ///< Link.
    LAYER3_SWITCH_DESCRIPTOR_TYPE_EOS          = 15U, ///< End of Set.
} layer3_switch_descriptor_type_t;

/** Bitmasks for each port. */
typedef enum e_layer3_switch_port_bitmask
{
    LAYER3_SWITCH_PORT_BITMASK_PORT0 = (1U << 0U), ///< Port 0
    LAYER3_SWITCH_PORT_BITMASK_PORT1 = (1U << 1U), ///< Port 1
    LAYER3_SWITCH_PORT_BITMASK_PORT2 = (1U << 2U), ///< Port 2
} layer3_switch_port_bitmask_t;

/** Descriptor queue type. */
typedef enum e_layer3_switch_queue_type
{
    LAYER3_SWITCH_QUEUE_TYPE_RX = 0U,  ///< Reception queue.
    LAYER3_SWITCH_QUEUE_TYPE_TX = 1U,  ///< Transmission queue.
} layer3_switch_queue_type_t;

/** Descriptor format type. */
typedef enum e_layer3_switch_descriptor_format
{
    LAYER3_SWITCH_DISCRIPTOR_FORMTAT_BASIC        = 0U, ///< Using basic descriptor.
    LAYER3_SWITCH_DISCRIPTOR_FORMTAT_EXTENDED     = 1U, ///< Using extended descriptor with additional fields.
    LAYER3_SWITCH_DISCRIPTOR_FORMTAT_TX_TIMESTAMP = 2U, ///< Using TX timestamp descriptor.
} layer3_switch_descriptor_format_t;

/** Write back mode. */
typedef enum e_layer3_switch_write_back_mode
{
    LAYER3_SWITCH_WRITE_BACK_MODE_FULL    = 0U, ///< All fields are updated by hardware.
    LAYER3_SWITCH_WRITE_BACK_MODE_DISABLE = 1U, ///< No fields are updated by hardware.
    LAYER3_SWITCH_WRITE_BACK_MODE_KEEP_DT = 2U, ///< Fields exclude DT are updated by hardware.
} layer3_switch_write_back_mode_t;

/** IP version options. */
typedef enum e_layer3_switch_ip_version
{
    LAYER3_SWITCH_IP_VERSION_NONE = 0U, ///< Not IP packet.
    LAYER3_SWITCH_IP_VERSION_IPV4 = 1U, ///< IPv4 packet.
    LAYER3_SWITCH_IP_VERSION_IPV6 = 2U, ///< IPv6 packet.
} layer3_switch_ip_version_t;

/** Direction of IP address. */
typedef enum e_layer3_switch_ip_address_direction
{
    LAYER3_SWITCH_IP_ADDRESS_DIRECTION_SOURCE      = 0U, ///< Use IP source address in stream ID.
    LAYER3_SWITCH_IP_ADDRESS_DIRECTION_DESTINATION = 1U, ///< Use IP destination address in stream ID.
} layer3_switch_ip_address_direction_t;

/** Magic packet detection options. */
typedef enum e_layer3_switch_magic_packet_detection
{
    LAYER3_SWITCH_MAGIC_PACKET_DETECTION_ENABLE  = 1U, ///< Enable magic packet detection.
    LAYER3_SWITCH_MAGIC_PACKET_DETECTION_DISABLE = 0U, ///< Disable magic packet detection.
} layer3_switch_magic_packet_detection_t;

/** VLAN detection mode. */
typedef enum e_layer3_switch_vlan_mode
{
    LAYER3_SWITCH_VLAN_MODE_NO_VLAN = 0U, ///< Not use VLAN feature.
    LAYER3_SWITCH_VLAN_MODE_C_TAG   = 1U, ///< Detect and use VLAN C-TAG.
    LAYER3_SWITCH_VLAN_MODE_SC_TAG  = 2U, ///< Detect and use VLAN SC-TAG.
} layer3_switch_vlan_mode_t;

/** VLAN ingress mode determines whether the switch operates with tagged VLAN or port-based VLAN. */
typedef enum e_layer3_switch_vlan_ingress_mode
{
    LAYER3_SWITCH_VLAN_INGRESS_MODE_TAG_BASED  = 0U, ///< Use VLAN ID of the incoming frame.
    LAYER3_SWITCH_VLAN_INGRESS_MODE_PORT_BASED = 1U, ///< Use VLAN ID of the incoming port.
} layer3_switch_vlan_ingress_mode_t;

/** VLAN egress mode determines the VLAN tag that is added to output frames. */
typedef enum e_layer3_switch_vlan_egress_mode
{
    LAYER3_SWITCH_VLAN_EGRESS_MODE_NO_VLAN   = 0U, ///< Frame always outgoing without VLAN TAG.
    LAYER3_SWITCH_VLAN_EGRESS_MODE_C_TAG     = 1U, ///< Frame outgoing with C-TAG of incoming frame.
    LAYER3_SWITCH_VLAN_EGRESS_MODE_HW_C_TAG  = 2U, ///< Frame always outgoing with C-TAG of output port.
    LAYER3_SWITCH_VLAN_EGRESS_MODE_SC_TAG    = 3U, ///< Frame always outgoing with SC-TAG of incoming frame.
    LAYER3_SWITCH_VLAN_EGRESS_MODE_HW_SC_TAG = 4U, ///< Frame always outgoing with SC-TAG of output port.
} layer3_switch_vlan_egress_mode_t;

/** IP protocols type. */
typedef enum e_layer3_switch_ip_protocol
{
    LAYER3_SWITCH_IP_PROTOCOL_TCP = 0x06U, ///< IP protocol is TCP.
    LAYER3_SWITCH_IP_PROTOCOL_UDP = 0x11U, ///< IP protocol is UDP.
} layer3_switch_ip_protocol_t;

/** R-TAG filed update options. */
typedef enum e_layer3_switch_forwarding_r_tag
{
    LAYER3_SWITCH_FORWARDING_R_TAG_UPDATE           = 0U, ///< Incoming frame with R-TAG will be updated with new R-TAG.
    LAYER3_SWITCH_FORWARDING_R_TAG_ALWAYS_ADD       = 1U, ///< ALl incoming frame will be added new R-TAG.
    LAYER3_SWITCH_FORWARDING_R_TAG_ALWAYS_ELIMINATE = 2U, ///< ALl incoming frame will be removed R-TAG.
} layer3_switch_forwarding_r_tag_t;

/** Frame filters options for layer3 forwarding. */
typedef enum e_layer3_switch_l3_filter_bitmask
{
    LAYER3_SWITCH_L3_FILTER_BITMASK_MAC_DESTINATION        = 0x1U,    ///< Enable MAC destination address.
    LAYER3_SWITCH_L3_FILTER_BITMASK_MAC_SOURCE             = 0x2U,    ///< Enable MAC source address.
    LAYER3_SWITCH_L3_FILTER_BITMASK_STAG_ID                = 0x4U,    ///< Enable VLAN ID of S-TAG.
    LAYER3_SWITCH_L3_FILTER_BITMASK_STAG_PCP               = 0x8U,    ///< Enable PCP of S-TAG.
    LAYER3_SWITCH_L3_FILTER_BITMASK_STAG_DEI               = 0x10U,   ///< Enable DEI of S-TAG.
    LAYER3_SWITCH_L3_FILTER_BITMASK_CTAG_ID                = 0x20U,   ///< Enable VLAN ID of C-TAG.
    LAYER3_SWITCH_L3_FILTER_BITMASK_CTAG_PCP               = 0x40U,   ///< Enable PCP of C-TAG.
    LAYER3_SWITCH_L3_FILTER_BITMASK_CTAG_DEI               = 0x80U,   ///< Enable DEI of C-TAG.
    LAYER3_SWITCH_L3_FILTER_BITMASK_IP_SOURCE_ADDRESS      = 0x100U,  ///< Enable IP source address.
    LAYER3_SWITCH_L3_FILTER_BITMASK_IP_DESTINATION_ADDRESS = 0x200U,  ///< Enable IP destination address.
    LAYER3_SWITCH_L3_FILTER_BITMASK_PROTOCOL               = 0x400U,  ///< Enable IP protocol.
    LAYER3_SWITCH_L3_FILTER_BITMASK_IP_SOURCE_PORT         = 0x800U,  ///< Enable layer4 source port.
    LAYER3_SWITCH_L3_FILTER_BITMASK_IP_DESTINATION_PORT    = 0x1000U, ///< Enable layer4 destination port.
} layer3_switch_l3_filter_bitmask_t;

/** Enable L2/L3 update feature. */
typedef enum e_layer3_switch_l3_update_bitmask
{
    LAYER3_SWITCH_L3_UPDATE_BITMASK_TTL             = 0x1U,   ///< Update TTL
    LAYER3_SWITCH_L3_UPDATE_BITMASK_MAC_DESTINATION = 0x2U,   ///< Update MAC destination address.
    LAYER3_SWITCH_L3_UPDATE_BITMASK_MAC_SOURCE      = 0x4U,   ///< Update MAC source address.
    LAYER3_SWITCH_L3_UPDATE_BITMASK_CTAG_ID         = 0x8U,   ///< Update VLAN ID of C-TAG
    LAYER3_SWITCH_L3_UPDATE_BITMASK_CTAG_PCP        = 0x10U,  ///< Update PCP of C-TAG
    LAYER3_SWITCH_L3_UPDATE_BITMASK_CTAG_DEI        = 0x20U,  ///< Update DEI of C-TAG
    LAYER3_SWITCH_L3_UPDATE_BITMASK_STAG_ID         = 0x40U,  ///< Update VLAN ID of C-TAG
    LAYER3_SWITCH_L3_UPDATE_BITMASK_STAG_PCP        = 0x80U,  ///< Update PCP of C-TAG
    LAYER3_SWITCH_L3_UPDATE_BITMASK_STAG_DEI        = 0x100U, ///< Update DEI of C-TAG
} layer3_switch_l3_update_bitmask_t;

/** Table entry type for forwarding feature. */
typedef enum e_layer3_switch_table_entry_type
{
    LAYER3_SWITCH_TABLE_ENTRY_TYPE_EMPTY  = 0U, ///< Entry is not initialized yet.
    LAYER3_SWITCH_TABLE_ENTRY_TYPE_MAC    = 1U, ///< Entry of MAC table.
    LAYER3_SWITCH_TABLE_ENTRY_TYPE_VLAN   = 2U, ///< Entry of VLAN table.
    LAYER3_SWITCH_TABLE_ENTRY_TYPE_LAYER3 = 3U, ///< Entry of Layer3 table.
} layer3_switch_table_entry_type_t;

/** Table status for forwarding feature. */
typedef enum e_layer3_switch_table_status
{
    LAYER3_SWITCH_TABLE_STATUS_UNINITIALIZED = 0, ///< Forwarding table is uninitialized
    LAYER3_SWITCH_TABLE_STATUS_INITIALIZED   = 1  ///< Forwarding table is initialized
} layer3_switch_table_status_t;

/** TAS gate state. */
typedef enum e_layer3_switch_tas_gate_state
{
    LAYER3_SWITCH_TAS_GATE_STATE_CLOSE = 0, ///< Gate is closed.
    LAYER3_SWITCH_TAS_GATE_STATE_OPEN  = 1  ///< Gate is opened.
} layer3_switch_tas_gate_state_t;

/** Enable or disable rx timestamp storage. */
typedef enum e_layer3_switch_rx_timestamp_storage
{
    LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_DISABLE = 0U, ///< Timestamp is not added in the descriptor.
    LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_ENABLE  = 1U, ///< Timestamp is added in the descriptor.
} layer3_switch_rx_timestamp_storage_t;

/** Used or not timestamp descriptor queue. */
typedef enum e_layer3_switch_ts_descriptor_queue_status
{
    LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_STATUS_UNUSED = 0U, ///< TS descriptor queue is unused.
    LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_STATUS_USED   = 1U, ///< TS descriptor queue is used.
} layer3_switch_ts_descriptor_queue_status_t;

/**  Configuration of FRER feature. */
typedef struct st_layer3_switch_frer_cfg
{
    uint32_t sys_clock;                ///< Timeout check time.
    uint32_t timeout_enable;           ///< Timeout check valid.
    uint32_t check_period;             ///< Microsecond prescaler used to creates an internal clock for aging at 1 MHz to derive the timeout 1 kHz clock.
} layer3_switch_frer_cfg_t;

/** FRER table entry. */
typedef struct st_layer3_switch_frer_entry
{
    uint32_t take_no_sequence;            ///< Reject frames without R-TAG.
    uint32_t sequence_history_len;        ///< Sequence history length.
    uint32_t set_recovery_remaining_tick; ///< Time in tick before timeout.
} layer3_switch_frer_entry_t;

/** Configuration of FRER entry (individual and sequence recovery). */
typedef struct st_layer3_switch_frer_entry_cfg
{
    layer3_switch_frer_entry_t   individual_recovery; ///< FRER table entry for individual recovery.
    layer3_switch_frer_entry_t * p_sequence_recovery; ///< Pointer to FRER entry(sequence recovery) information referenced by `FRERN` in this FRER entry(individual recovery).
    uint32_t sequence_recovery_id;
} layer3_switch_frer_entry_cfg_t;

/** Status of FRER sequence recovery table. */
typedef struct st_layer3_switch_frer_sequence_recovery_status
{
    bool     learned;                  ///< Flags whether the FRER entry(sequence recovery) related to this entry has been learned.
    uint32_t frer_entry_index;         ///< Real FRER table index of the FRER entry(sequence recovery) related to this entry.
} layer3_switch_frer_sequence_recovery_status_t;

/** Configuration of a descriptor queue. */
typedef struct st_layer3_switch_descriptor_queue_cfg
{
    layer3_switch_descriptor_format_t                 descriptor_format;     ///< Enable or disable extended descriptors.
    layer3_switch_queue_type_t                        type;                  ///< Reception queue or transmission queue.
    layer3_switch_write_back_mode_t                   write_back_mode;       ///< Configure write-back to descriptor fields.
    layer3_switch_descriptor_t                      * p_descriptor_array;    ///< Descriptor array that use to create queue.
    layer3_switch_ts_reception_process_descriptor_t * p_ts_descriptor_array; ///< TS descriptor array that use to create queue.
    layer3_switch_rx_timestamp_storage_t              rx_timestamp_storage;  ///< Configure RX timestamp storage.
    uint32_t array_length;                                                   ///< Length of descriptor array. This length includes terminate descriptor at the end.
    uint32_t ports;                                                          ///< Bitmap of ports that use this queue.
} layer3_switch_descriptor_queue_cfg_t;

/** Configuration of Credit Based Shaper. */
typedef struct st_layer3_switch_cbs_cfg
{
    uint8_t band_width_list[8];        ///< CBS band width [%] of each queue.
    uint8_t max_burst_num_list[8];     ///< Maximum burst frame number of each queue.
} layer3_switch_cbs_cfg_t;

/** Configuration of each Ethernet port. */
typedef struct st_layer3_switch_port_cfg
{
    uint8_t                 * p_mac_address;                    ///< Pointer to MAC address.
    bool                      forwarding_to_cpu_enable;         ///< Enable or disable reception on CPU.
    layer3_switch_cbs_cfg_t * p_cbs_cfg;                        ///< Pointer to CBS configuration.
    void (* p_callback)(ether_switch_callback_args_t * p_args); ///< Callback provided when an ISR occurs.
    ether_switch_callback_args_t * p_callback_memory;           ///< Pointer to optional callback argument memory
    void * p_context;                                           ///< Pointer to context to be passed into callback function
} layer3_switch_port_cfg_t;

/** Status of a descriptor queue. */
typedef struct st_layer3_switch_descriptor_queue_status
{
    uint32_t head;                                            ///< Index at the head of the queue. This used for GetDescriptor API.
    uint32_t tail;                                            ///< Index at the tail of the queue. This used for SetDescriptor API.
    bool     created;                                         ///< This queue is already created.
    layer3_switch_descriptor_queue_cfg_t const * p_queue_cfg; ///< Configuration of this queue.
    bool rx_available;                                        ///< Indicates whether the queue is available for reception.
} layer3_switch_descriptor_queue_status_t;

/** IP address offset for creating IPv6 filter of Layer3 forwarding. */
typedef struct st_layer3_switch_ipv6_filter_address_offset
{
    uint8_t offset;                                 ///< Offset of IPv6 address.
    layer3_switch_ip_address_direction_t direction; ///< Select source or destination.
} layer3_switch_ipv6_filter_address_offset_t;

/** Configuration of stream filter in Layer3 forwarding. */
typedef struct st_layer3_switch_l3_stream_filter_cfg
{
    uint16_t filter_field_bitmask;                            ///< Bitmask of which feilds is enabled in stream filter. Use @ref layer3_switch_l3_filter_bitmask_t.
    layer3_switch_ipv6_filter_address_offset_t ipv6_address0; ///< Offset of IPv6 address 0.
    layer3_switch_ipv6_filter_address_offset_t ipv6_address1; ///< Offset of IPv6 address 1.
} layer3_switch_l3_stream_filter_cfg_t;

/* Stream ID of Layer3 forwarding entry. This structure is used internally only. */
typedef struct st_layer3_switch_stream_id
{
    uint8_t frame_format_code;         ///< Format code that implies which filter created this stream ID.
    union
    {
        uint32_t words[4];             ///< Stream ID as words.
        uint8_t  bytes[16];            ///< Stream ID as bytes.
    };
} layer3_switch_stream_id_t;

/** VLAN tag structure. */
typedef struct st_layer3_switch_frame_vlan_tag
{
    uint16_t pcp : 3;                  ///< Priority Code Point (3 bit).
    uint16_t dei : 1;                  ///< Drop Eligible Indicator (1 bit).
    uint16_t id  : 12;                 ///< VLAN ID (12 bit).
} layer3_switch_frame_vlan_tag_t;

/** Frame filter of a MAC/VLAN/Layer3 forwarding entry. Set values for members required for filtering. */
typedef struct st_layer3_switch_frame_filter
{
    /* Entry type. */
    layer3_switch_table_entry_type_t entry_type; ///< Type of this entry. Select MAC, VLAN or Layer3.

    /* Used for MAC and Layer3 entry. */
    uint8_t * p_destination_mac_address;         ///< Destination MAC address.
    uint8_t * p_source_mac_address;              ///< Source MAC address.

    /* Used for VLAN and Layer3 entry. */
    layer3_switch_frame_vlan_tag_t vlan_c_tag;   ///< VLAN C-TAG.
    layer3_switch_frame_vlan_tag_t vlan_s_tag;   ///< VLAN S-TAG.

    /* Used for Layer3 table. */
    layer3_switch_ip_version_t ip_version;       ///< IP version. Select IPv4, IPv6, or not IP packet.
    uint8_t   protocol;                          ///< IP protocol
    uint8_t * p_source_ip_address;               ///< Source IP address.
    uint8_t * p_destination_ip_address;          ///< Destination IP address.
    uint16_t  layer4_source_port;                ///< TCP/UDP source port.
    uint16_t  layer4_destination_port;           ///< TCP/UDP destination port.
} layer3_switch_frame_filter_t;

/** Store filter information of Layer3 forwarding entry. */
typedef struct st_layer3_switch_l3_filter
{
    layer3_switch_frame_filter_t frame; ///< Target frame format that used to Layer3 forwarding.
} layer3_switch_l3_filter_t;

/** Configuration of a L2/L3 update feature for output frames. */
typedef struct st_layer3_switch_l3_update_config
{
    uint32_t  enable_destination_ports;                 ///< Destination ports that this update config is enabled.
    uint32_t  update_field_bitmask;                     ///< Bit mask of which fields will be updated. Use @ref layer3_switch_l3_update_bitmask_t.
    uint8_t * p_mac_destination_address;                ///< MAC Destination Address.
    layer3_switch_frame_vlan_tag_t   vlan_c_tag;        ///< VLAN C-tag.
    layer3_switch_frame_vlan_tag_t   vlan_s_tag;        ///< VLAN S-tag.
    layer3_switch_forwarding_r_tag_t r_tag_update_mode; ///< R-TAG update setting.
    bool sequence_number_generation_enable;             ///< Flags whether sequence number generation (FRER) is enabled for this entry.
} layer3_switch_l3_update_config_t;

/** Table entry configuration of MAC/VLAN/Layer3 forwarding. */
typedef struct st_layer3_switch_table_entry_cfg
{
    /* Entry settings. */
    bool entry_enable;                                 ///< Enable or disable entry. If this field is false, entry will be removed.
    bool security_enable;                              ///< Entry is secure or not.

    /* FRER setting. */
    layer3_switch_frer_entry_cfg_t * p_frer_entry_cfg; ///< Configuration of the FRER entry(individual recovery) for this L3 entry (set to `NULL` : FRER is not valid in this L3 entry).

    /* Forwarding settings. */
    uint32_t destination_ports;                        ///< Destination ports of forwarding.
    uint32_t source_ports;                             ///< Source ports that enable forwarding of incoming frame.
    uint32_t destination_queue_index;                  ///< Destination queue. This fields is only used when a destination port is CPU.
    uint32_t internal_priority_update_enable;          ///< Enable to update internal priority
    uint32_t internal_priority_update_value;           ///< Internal priority when updating is enabled.

    /* Forwarding protocol specific features. */
    union
    {
        /* MAC forwarding entry fields. */
        struct st_mac
        {
            bool dinamic_entry;        ///< This entry is dynamic entry or not. Dynamic entry enable aging feature.
        } mac;

        /* Layer3 forwarding specific feature. */
        struct st_layer3
        {
            layer3_switch_l3_update_config_t * p_update_configs; ///< Pointer to an array of a L2/L3 update configurations.
            uint32_t number_of_configs;                          ///< Number of the update configs.
        } layer3;
    };
} layer3_switch_table_entry_cfg_t;

/** Table entry of MAC/VLAN/Layer3 forwarding. */
typedef struct st_layer3_switch_table_entry
{
    layer3_switch_frame_filter_t    target_frame; ///< Target frame of forwarding by this entry.
    layer3_switch_table_entry_cfg_t entry_cfg;    ///< Configuration of this entry.
} layer3_switch_table_entry_t;

/** Configuration of forwarding feature for each port. */
typedef struct st_layer3_switch_forwarding_port_cfg
{
    /* MAC table configuration. */
    bool mac_table_enable;                               ///< Enable MAC table and forwarding feature.
    bool mac_reject_unknown;                             ///< Reject frame with unknown MAC address.
    bool mac_hardware_learning_enable;                   ///< Enable hardware learning and migration.

    /* VLAN table configuration. */
    bool vlan_table_enable;                              ///< Enable VLAN table and forwarding feature.
    bool vlan_reject_unknown;                            ///< Reject frame with unknown VLAN ID.
    layer3_switch_vlan_ingress_mode_t vlan_ingress_mode; ///< Select Tag-based VLAN or Port-based VLAN for incoming frame.
    layer3_switch_vlan_egress_mode_t  vlan_egress_mode;  ///< Tagging/untagging mode for outgoing frame.
    layer3_switch_frame_vlan_tag_t    vlan_s_tag;        ///< S-TAG of this port. When egress mode is hardware SC-TAG, add this to outgoing frame.
    layer3_switch_frame_vlan_tag_t    vlan_c_tag;        ///< C-TAG of this port. When egress mode is hardware C-TAG, add this to outgoing frame.

    /* Layer3 table configuration. */
    bool layer3_table_enable;                            ///< Enable Layer3 table and forwarding feature.
    bool layer3_reject_unknown;                          ///< Reject frame that not found in Layer3 table.
    bool layer3_ipv4_filter_enable;                      ///< Enable IPv4 stream filter.
    bool layer3_ipv6_filter_enable;                      ///< Enable IPv6 stream filter.
    bool layer3_l2_filter_enable;                        ///< Enable L2 stream filter.
} layer3_switch_forwarding_port_cfg_t;

/** Forwarding table containing MAC/VLAN/Layer3 forwarding entries. */
typedef struct st_layer3_switch_table
{
    layer3_switch_table_entry_t * p_mac_entry_list;  ///< List of MAC entries.
    uint32_t mac_list_length;                        ///< Length of the MAC entry list.
    layer3_switch_table_entry_t * p_vlan_entry_list; ///< List of VLAN entries.
    uint32_t vlan_list_length;                       ///< Length of the VLAN entry list.
    layer3_switch_table_entry_t * p_l3_entry_list;   ///< List of Layer3 entries.
    uint32_t l3_list_length;                         ///< Length of the Layer3 entry list.
} layer3_switch_table_t;

/** Configuration of the forwarding table. */
typedef struct st_layer3_switch_table_cfg
{
    layer3_switch_table_t             * p_table;                                           ///< Pointer to forwarding table.
    layer3_switch_forwarding_port_cfg_t port_cfg_list[BSP_FEATURE_ETHER_NUM_CHANNELS + 1]; ///< Forwarding configuration of each port.
    uint32_t unsecure_entry_maximum_num;                                                   ///< Maximum number of unsecure entries.

    /* MAC table configuration. */
    bool     mac_entry_aging_enable;                                                       ///< Enable aging feature of MAC table.
    uint32_t mac_entry_aging_time_sec;                                                     ///< Time[s] to delete an entry by aging.

    /* VLAN table configuration. */
    layer3_switch_vlan_mode_t vlan_mode;                                                   ///< VLAN mode options: NO VLAN, C-TAG, or SC-TAG.

    /* Layer3 table configuration. */
    layer3_switch_l3_stream_filter_cfg_t l3_stream_filter_cfg;                             ///< Configuration of stream filter in Layer3 forwarding.
    layer3_switch_frer_cfg_t             frer_cfg;                                         ///< Configuration of FRER feature.
} layer3_switch_table_cfg_t;

/** ESWM extension configures each Ethernet port and forwarding feature. */
typedef struct st_layer3_switch_extended_cfg
{
    ether_phy_instance_t const * p_ether_phy_instances[BSP_FEATURE_ETHER_NUM_CHANNELS]; ///< List of pointers to ETHER_PHY instance.
    gptp_instance_t const      * p_gptp_instance;                                       ///< Pointer to a gPTP instance.
    uint32_t  fowarding_target_port_masks[BSP_FEATURE_ETHER_NUM_CHANNELS];              ///< List of ports to which incoming frames are forwarded.
    uint8_t * p_mac_addresses[BSP_FEATURE_ETHER_NUM_CHANNELS];                          // [DEPRECATED] MAC address of each port.
    uint32_t  ipv_queue_depth_list[BSP_FEATURE_ETHER_NUM_CHANNELS][8];                  ///< List of IPV queue depth for each port.
    layer3_switch_l3_filter_t * l3_filter_list;                                         ///< Filter list of layer3 routing.
    uint32_t l3_filter_list_length;                                                     ///< Length of Layer3 filter list.
    layer3_switch_port_cfg_t * p_port_cfg_list[BSP_FEATURE_ETHER_NUM_CHANNELS];         ///< Configuration for each port.
    IRQn_Type etha_error_irq_port_0;                                                    ///< ETHA error interrupt number for port 0.
    IRQn_Type etha_error_irq_port_1;                                                    ///< ETHA error interrupt number for port 1.
    uint8_t   etha_error_ipl_port_0;                                                    ///< ETHA error interrupt priority for port 0.
    uint8_t   etha_error_ipl_port_1;                                                    ///< ETHA error interrupt priority for port 1.
    uint8_t   gptp_timer_numbers[BSP_FEATURE_ESWM_GPTP_TIMER_NUM];                      ///< List of timer numbers for transmission/reception timestamp.
} layer3_switch_extended_cfg_t;

/** LAYER3_SWITCH control block. DO NOT INITIALIZE. Initialization occurs when @ref ether_switch_api_t::open is called. */
typedef struct st_layer3_switch_instance_ctrl
{
    uint32_t open;                                                                                                 ///< Used to determine if the channel is configured
    ether_switch_cfg_t const * p_cfg;                                                                              ///< Pointer to initial configurations.
    R_GWCA0_Type             * p_gwca_reg;                                                                         ///< Pointer to GWCA register.

    uint32_t allocated_descriptor_queue_index;                                                                     ///< Index of the descriptor pool.
    layer3_switch_basic_descriptor_t        p_descriptor_queue_list[LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM];        ///< Descriptor queue lists used by hardware.
    layer3_switch_descriptor_queue_status_t p_queues_status[LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM];                ///< Status of each descriptor queues.
    layer3_switch_port_cfg_t                p_port_cfg_list[BSP_FEATURE_ETHER_NUM_CHANNELS];                       ///< Configuration for each port.

    /* Forwarding features. */
    layer3_switch_table_status_t table_status;                                                                     ///< Forwarding table is initialized or not.
    uint32_t l3_entry_count;                                                                                       ///< Counts of valid LAYER3 entry.
    uint8_t  l3_routing_number;                                                                                    ///< Routing number for L2/L3 update feature.
    uint8_t  l3_remapping_number;                                                                                  ///< Remapping number for L2/L3 update feature.

    /* Timestamp features. */
    layer3_switch_ts_descriptor_queue_status_t ts_descriptor_queue_status_list[
        BSP_FEATURE_ESWM_TS_DESCRIPTOR_QUEUE_MAX_NUM];                                                             ///< Status of TS reception descriptor queues.

    /* FRER features. */
    uint32_t valid_frer_entry_num;                                                                                 ///< Number of valid FRER entry.
    layer3_switch_frer_sequence_recovery_status_t frer_sequence_recovery_status[BSP_FEATURE_ESWM_FRER_TABLE_SIZE]; ///< Status of table for each FRER sequence recovery entry.
    uint32_t used_frer_sequence_generator_num;                                                                     ///< Number of the sequence number generator.

    void (* p_callback)(ether_switch_callback_args_t * p_args);                                                    ///< Callback provided when an ISR occurs.
    ether_switch_callback_args_t * p_callback_memory;                                                              ///< Pointer to optional callback argument memory
    void * p_context;                                                                                              ///< Pointer to context to be passed into callback function
} layer3_switch_instance_ctrl_t;

/** Configuration of the gate operation. */
typedef struct st_layer3_switch_etha_tas_entry
{
    layer3_switch_tas_gate_state_t state; ///< Gate state.
    uint32_t time;                        ///< Time associated with the entry gate state [nsec].
} layer3_switch_tas_entry_t;

/** Configuration of the gate. */
typedef struct st_layer3_switch_tas_gate_cfg
{
    layer3_switch_tas_gate_state_t initial_gate_state; ///< Initial gate state when the cycle starts.
    uint8_t tas_entry_num;                             ///< Number of TAS entries included in this gate.
    layer3_switch_tas_entry_t * p_tas_entry_list;      ///< List of TAS entries included in this gate.
} layer3_switch_tas_gate_cfg_t;

/** Configuration of the TAS. */
typedef struct st_layer3_switch_tas_cfg
{
    uint8_t  gptp_timer_number;                    ///< gPTP timer number.
    uint32_t cycle_time_start_high;                ///< Upper 32 bits of TAS cycle start time [nsec].
    uint32_t cycle_time_start_low;                 ///< Lower 32 bits of TAS cycle start time [nsec].
    uint32_t cycle_time;                           ///< TAS cycle time [nsec].
    layer3_switch_tas_gate_cfg_t gate_cfg_list[8]; ///< List of TAS gate configurations.
} layer3_switch_tas_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_switch_api_t g_ether_switch_on_layer3_switch;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_Open(ether_switch_ctrl_t * const p_ctrl, ether_switch_cfg_t const * const p_cfg);

fsp_err_t R_LAYER3_SWITCH_Close(ether_switch_ctrl_t * const p_ctrl);

fsp_err_t R_LAYER3_SWITCH_CreateDescriptorQueue(ether_switch_ctrl_t * const                        p_ctrl,
                                                uint32_t * const                                   p_queue_index,
                                                layer3_switch_descriptor_queue_cfg_t const * const p_queue_cfg);

fsp_err_t R_LAYER3_SWITCH_SetDescriptor(ether_switch_ctrl_t * const              p_ctrl,
                                        uint32_t                                 queue_index,
                                        layer3_switch_descriptor_t const * const p_descriptor);

fsp_err_t R_LAYER3_SWITCH_GetDescriptor(ether_switch_ctrl_t * const        p_ctrl,
                                        uint32_t                           queue_index,
                                        layer3_switch_descriptor_t * const p_descriptor);

fsp_err_t R_LAYER3_SWITCH_StartDescriptorQueue(ether_switch_ctrl_t * const p_ctrl, uint32_t queue_index);

fsp_err_t R_LAYER3_SWITCH_CallbackSet(ether_switch_ctrl_t * const          p_ctrl,
                                      void (                             * p_callback)(ether_switch_callback_args_t *),
                                      void * const                         p_context,
                                      ether_switch_callback_args_t * const p_callback_memory);

fsp_err_t R_LAYER3_SWITCH_ConfigurePort(ether_switch_ctrl_t * const p_ctrl,
                                        uint8_t                     port,
                                        layer3_switch_port_cfg_t  * p_port_cfg);

fsp_err_t R_LAYER3_SWITCH_AddTableEntry(ether_switch_ctrl_t * const                   p_ctrl,
                                        layer3_switch_frame_filter_t const * const    p_target_frame,
                                        layer3_switch_table_entry_cfg_t const * const p_entry_cfg);
fsp_err_t R_LAYER3_SWITCH_SearchTableEntry(ether_switch_ctrl_t * const                p_ctrl,
                                           layer3_switch_frame_filter_t const * const p_target_frame,
                                           layer3_switch_table_entry_cfg_t * const    p_entry_cfg);
fsp_err_t R_LAYER3_SWITCH_ConfigureTable(ether_switch_ctrl_t * const             p_ctrl,
                                         layer3_switch_table_cfg_t const * const p_table_cfg);
fsp_err_t R_LAYER3_SWITCH_GetTable(ether_switch_ctrl_t * const p_ctrl, layer3_switch_table_t * const p_table);
fsp_err_t R_LAYER3_SWITCH_ConfigureTAS(ether_switch_ctrl_t * const p_ctrl,
                                       uint8_t                     port,
                                       layer3_switch_tas_cfg_t   * p_tas_cfg);
fsp_err_t R_LAYER3_SWITCH_EnableTAS(ether_switch_ctrl_t * const p_ctrl, uint8_t port);

/*******************************************************************************************************************//**
 * @} (end addtogroup LAYER3_SWITCH)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_LAYER3_SWITCH_H
