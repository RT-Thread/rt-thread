/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef MAC_COMMON_H_INCLUDED
#define MAC_COMMON_H_INCLUDED

#include <stdint.h>
#include "phy_common.h"

#if (CONFIG_SECURE == 1)
#include "mac_security.h"
#endif

/** @file
 * Types and declarations common for different MLME transactions listed here.
 *
 * @defgroup mac_common MAC Common API
 * @ingroup mac_15_4
 * @{
 * @brief Module for declaring MAC Common API.
 * @details The Common MAC module contains declarations of commonly used MAC routines and necessary
 * macros and types.
 */

/**@brief Maximum interval for acknowledgement frame to arrive in microseconds.
 *
 * macAckWaitDuration = aUnitBackoffPeriod(only for beacon enabled PAN) +
 *                      aTurnaroundTime +
 *                      phySHRDuration + ceil(6 * phySymbolsPerOctet) =
 *                      20 + 12 + 10 + 6 * 2 =
 *                      54 symbols / 62.5 ksymbols/s = 864 us (544 us for beacon disabled PAN)
 */
#if (CONFIG_BEACON_ENABLED == 1)
#define macAckWaitDuration                864
#else
#define macAckWaitDuration                544
#endif

/**@brief The maximum number of octets added by the MAC
 * sublayer to the MAC payload of a beacon frame.
 */
#define aMaxBeaconOverhead                75

/**@brief The number of symbols forming the basic time period
 * used by the CSMA-CA algorithm.
 */
#define aUnitBackoffPeriod                20UL

/**@brief The number of symbols forming a superframe slot
 * when the superframe order is equal to 0.
 */
#define aBaseSlotDuration                 60UL

/**@brief The number of slots contained in any superframe. */
#define aNumSuperframeSlots               16UL

/**@brief The number of symbols forming a superframe when
 * the superframe order is equal to 0.
 */
#define aBaseSuperframeDuration          (aBaseSlotDuration * aNumSuperframeSlots)

/**@brief The maximum size, in octets, of a beacon payload. */
#define aMaxBeaconPayloadLength          (aMaxPHYPacketSize - aMaxBeaconOverhead)

/**@brief The maximum number of octets added by the MAC
 * sublayer to the PSDU without security.
 */
#define aMaxMPDUUnsecuredOverhead         25

/**@brief The maximum number of octets that can be transmitted in the MAC Payload
 * field of an unsecured MAC frame that will be guaranteed not to exceed aMaxPHYPacketSize.
 */
#define aMaxMACSafePayloadSize           (aMaxPHYPacketSize - aMaxMPDUUnsecuredOverhead)

/**@brief The minimum number of octets added by the MAC sublayer to the PSDU.*/
#define aMinMPDUOverhead                  9

/**@brief The maximum number of octets that can be transmitted in the MAC
 * Payload field.
 */
#define aMaxMACPayloadSize               (aMaxPHYPacketSize - aMinMPDUOverhead)

/**@brief The maximum size of an MPDU, in octets, that can be followed by a SIFS period. */
#define aMaxSIFSFrameSize                 18

/**@brief The minimum number of symbols forming the CAP.
 *
 * @details This ensures that MAC commands can still be transferred to devices
 * when GTSs are being used.
 */
#define aMinCAPLength                     440

/**@brief The number of superframes in which a GTS descriptor exists
 * in the beacon frame of the PAN coordinator.
 */
#define aGTSDescPersistenceTime           4

/**@brief The number of consecutive lost beacons that will cause the MAC sublayer
 * of a receiving device to declare a loss of synchronization.
 */
#define aMaxLostBeacons                   4

/**@brief   Maximum number of battery life extension periods. */
#define MAC_MIN_BATT_LIFE_EXT_PERIODS     6
/**@brief   Minimum number of battery life extension periods. */
#define MAC_MAX_BATT_LIFE_EXT_PERIODS     41

/**@brief   Minimum value for macBeaconOrder parameter. */
#define MAC_MIN_BEACON_ORDER              0
/**@brief   Maximum value for macBeaconOrder parameter. */
#define MAC_MAX_BEACON_ORDER              15

/**@brief   Minimum value for macMaxCSMABackoffs parameter. */
#define MAC_MIN_MAX_CSMA_BACKOFFS         0
/**@brief   Maximum value for macMaxCSMABackoffs parameter. */
#define MAC_MAX_MAX_CSMA_BACKOFFS         5

/**@brief   Minimum value for macMinBE parameter. */
#define MAC_MIN_MIN_BE                    0

/**@brief   Minimum value for macMaxBE parameter. */
#define MAC_MIN_MAX_BE                    3
/**@brief   Maximum value for macMaxBE parameter. */
#define MAC_MAX_MAX_BE                    8

/**@brief   Minimum value for macSuperframeOrder parameter. */
#define MAC_MIN_SUPERFRAME_ORDER          0
/**@brief   Maximum value for macSuperframeOrder parameter. */
#define MAC_MAX_SUPERFRAME_ORDER          15

/**@brief   Minimum value for macMaxFrameRetries parameter. */
#define MAC_MIN_MAX_FRAME_RETRIES         0
/**@brief   Maximum value for macMaxFrameRetries parameter. */
#define MAC_MAX_MAX_FRAME_RETRIES         7

/**@brief   Minimum value for macResponseWaitTime parameter. */
#define MAC_MIN_RESPONSE_WAIT_TIME        2
/**@brief   Maximum value for macResponseWaitTime parameter. */
#define MAC_MAX_RESPONSE_WAIT_TIME        64

/**@brief A handy macro for a never initialized short address. */
#define MAC_SHORT_ADDRESS_NOT_SET         0xFFFF

/**@brief A handy macro for a never initialized short address. */
#define MAC_EXTENDED_ADDRESS_NOT_SET      0xFFFFFFFFFFFFFFFFULL

/**@brief A value of MAC beacon order attribute which determines
 * a state with no periodic beacons.
 */
#define MAC_NO_BEACONS                    15

/**@brief A handy macro for broadcast address. */
#define MAC_BROADCAST_SHORT_ADDRESS       0xFFFF

/**@brief A handy macro for unknown PAN ID. */
#define MAC_BROADCAST_PANID               0xFFFF

/**@brief Short address field value that is used when the device does not
 * support short addressing mode.
 */
#define MAC_EXTENDED_ADDRESS_ONLY         0xFFFE

/**@brief Final CAP slot field value in the beacon for non-beacon enabled PAN. */
#define MAC_FINAL_CAP_SLOT_NBPAN          15

/**@brief Total amount of slots available in beacon enabled PAN. */
#define MAC_SLOT_AMOUNT                   16

/**@brief This is the value of auto request key index until it has been set. */
#define MAC_SECURITY_KEY_INDEX_NOT_SET    0xFF

/**@brief Length of short MAC address in bytes. */
#define MAC_ADDR_SHORT_LEN                2

/**@brief Length of extended MAC address in bytes. */
#define MAC_ADDR_EXTENDED_LEN             8

/**@brief Length of PAN ID field in bytes. */
#define MAC_PAN_ID_LEN                    2

/**@brief MAC footer (FCS) size. */
#define MAC_MFR_SIZE                      2

/**@brief   Maximum auxiliary header length */
#if (CONFIG_SECURE == 1)
#define MAC_MAX_AUX_HEADER_SIZE  14
#else
#define MAC_MAX_AUX_HEADER_SIZE  0
#endif

/**@brief   Maximum MAC header length */
#define MAC_MAX_MHR_SIZE         (PHY_MAX_HEADER_SIZE + \
                                  2 /* Frame control */ + \
                                  1 /* Data sequence number */ + \
                                  2 * (sizeof(uint16_t) + (sizeof(uint64_t))) /* Two PAN IDs and extended addresses */ + \
                                  MAC_MAX_AUX_HEADER_SIZE)
/**@brief   Maximum MAC header length for beacon frame */
#define MAC_MAX_BCN_MHR_SIZE     (PHY_MAX_HEADER_SIZE + \
                                  2 /* Frame control field */ + \
                                  1 /* Beacon sequence number */ + \
                                  sizeof(uint16_t) /* PAN ID */ + \
                                  sizeof(uint64_t) /* Extended address */ + \
                                  MAC_MAX_AUX_HEADER_SIZE)


/**@brief   Memory which should be reserved for MAC fields  */
#if (CONFIG_SECURE == 1)
#define MAC_MEMORY_RESERVE       (MAC_MAX_MHR_SIZE + MAX_MIC_SIZE + MAC_MFR_SIZE)
#else
#define MAC_MEMORY_RESERVE       (MAC_MAX_MHR_SIZE + MAC_MFR_SIZE)
#endif

/**@brief   Offset of MAC payload in the frame buffer */
#define MAC_MAX_MSDU_OFFSET           MAC_MAX_MHR_SIZE

/**@brief Possible MAC frame types. */
typedef enum
{
    MAC_BEACON,                         /**< Frame is a beacon. */
    MAC_DATA,                           /**< Frame is a data frame. */
    MAC_ACK,                            /**< Frame is a MAC ACKnowledgement. */
    MAC_COMMAND                         /**< Frame is a MAC command. */
} mac_frame_type_t;

/**@brief MAC ADDRESS. */
typedef union
{
    uint16_t short_address;             /**< 16-bit short address. */
    uint64_t long_address;              /**< 64-bit long address. */
} mac_addr_t;

/**@brief MAC ADDR MODE. */
typedef enum
{
    MAC_ADDR_NONE  = 0,                 /**< NO address is used. */
    MAC_ADDR_SHORT = 2,                 /**< Short address is used. */
    MAC_ADDR_LONG  = 3                  /**< Long address is used. */
} mac_addr_mode_t;

typedef enum
{
    MAC_FRAME_VERSION_2003,             /**< IEEE 802.15.4-2003 compliant. */
    MAC_FRAME_VERSION_2006              /**< IEEE 802.15.4-2006 compliant. */
} mac_frame_version_t;

/**
 * @brief MAC status
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.17
 * excluding:
 * MAC_IS_NOT_AVAILABLE
 * This status is necessary for synchronous API.
 */
typedef enum
{
    MAC_SUCCESS                   = 0x00, /* 0   */     /**< Operation is successful. */
    MAC_COUNTER_ERROR             = 0xDB, /* 219 */     /**< The frame counter purportedly applied
                                                             by the originator of the received
                                                             frame is invalid. */
    MAC_IMPROPER_KEY_TYPE         = 0xDC, /* 220 */     /**< The key purportedly applied by the
                                                             originator of the received frame is
                                                             not allowed to be used with that
                                                             frame type according to the key usage
                                                             policy of the recipient. */
    MAC_IMPROPER_SECURITY_LEVEL   = 0xDD, /* 221 */     /**< The security level purportedly applied
                                                             by the originator of the received
                                                             frame does not meet the minimum
                                                             security level required/expected by
                                                             the recipient for that frame type. */
    MAC_UNSUPPORTED_LEGACY        = 0xDE, /* 222 */     /**< The received frame was purportedly
                                                             secured using security based on IEEE
                                                             Std 802.15.4-2003, and such security
                                                             is not supported by this standard. */
    MAC_UNSUPPORTED_SECURITY      = 0xDF, /* 223 */     /**< The security purportedly applied by
                                                             the originator of the received frame
                                                             is not supported. */
    MAC_BEACON_LOSS               = 0xE0, /* 224 */     /**< The beacon was lost following a
                                                             synchronization request. */
    MAC_CHANNEL_ACCESS_FAILURE    = 0xE1, /* 225 */     /**< A transmission could not take place
                                                             due to activity on the channel, i.e.
                                                             the CSMA-CA mechanism has failed. */
    MAC_DENIED                    = 0xE2, /* 226 */     /**< The GTS request has been denied by
                                                             the PAN coordinator. */
    MAC_DISABLE_TRX_FAILURE       = 0xE3, /* 227 */     /**< The attempt to disable the
                                                             transceiver has failed. */
    MAC_SECURITY_ERROR            = 0xE4, /* 228 */     /**< Cryptographic processing of the
                                                             received secured frame failed. */
    MAC_FRAME_TOO_LONG            = 0xE5, /* 229 */     /**< Either a frame resulting from
                                                             processing has a length that is
                                                             greater than aMaxPHYPacketSize or
                                                             a requested transaction is too large
                                                             to fit in the CAP or GTS. */
    MAC_INVALID_GTS               = 0xE6, /* 230 */     /**< The requested GTS transmission failed
                                                             because the specified GTS either did
                                                             not have a transmit GTS direction or
                                                             was not defined. */
    MAC_INVALID_HANDLE            = 0xE7, /* 231 */     /**< A request to purge an MSDU from the
                                                             transaction queue was made using an
                                                             MSDU handle that was not found in
                                                             the transaction table. */
    MAC_INVALID_PARAMETER         = 0xE8, /* 232 */     /**< A parameter in the primitive is
                                                             either not supported or is out of
                                                             the valid range. */
    MAC_NO_ACK                    = 0xE9, /* 233 */     /**< No acknowledgment was received after
                                                             macMaxFrameRetries. */
    MAC_NO_BEACON                 = 0xEA, /* 234 */     /**< A scan operation failed to find any
                                                             network beacons. */
    MAC_NO_DATA                   = 0xEB, /* 235 */     /**< No response data was available
                                                             following a request. */
    MAC_NO_SHORT_ADDRESS          = 0xEC, /* 236 */     /**< The operation failed because a 16-bit
                                                             short address was not allocated. */
    MAC_OUT_OF_CAP                = 0xED, /* 237 */     /**< A receiver enable request was
                                                             unsuccessful because it could not be
                                                             completed within the CAP.
                                                             @note The enumeration description is
                                                             not used in this standard, and it is
                                                             included only to meet the backwards
                                                             compatibility requirements for
                                                             IEEE Std 802.15.4-2003. */
    MAC_PAN_ID_CONFLICT           = 0xEE, /* 238 */     /**< A PAN identifier conflict has been
                                                             detected and communicated to the PAN
                                                             coordinator. */
    MAC_REALIGNMENT               = 0xEF, /* 239 */     /**< A coordinator realignment command has
                                                             been received. */
    MAC_TRANSACTION_EXPIRED       = 0xF0, /* 240 */     /**< The transaction has expired and its
                                                             information was discarded. */
    MAC_TRANSACTION_OVERFLOW      = 0xF1, /* 241 */     /**< There is no capacity to store the
                                                             transaction. */
    MAC_TX_ACTIVE                 = 0xF2, /* 242 */     /**< The transceiver was in the transmitter
                                                             enabled state when the receiver was
                                                             requested to be enabled.
                                                             @note The enumeration description is
                                                             not used in this standard, and it is
                                                             included only to meet the backwards
                                                             compatibility requirements for
                                                             IEEE Std 802.15.4-2003. */
    MAC_UNAVAILABLE_KEY           = 0xF3, /* 243 */     /**< The key purportedly used by the
                                                             originator of the received frame is
                                                             not available or, if available, the
                                                             originating device is not known or is
                                                             blacklisted with that particular
                                                             key. */
    MAC_UNSUPPORTED_ATTRIBUTE     = 0xF4, /* 244 */     /**< A SET/GET request was issued with the
                                                             identifier of a PIB attribute that is
                                                             not supported. */
    MAC_INVALID_ADDRESS           = 0xF5, /* 245 */     /**< A request to send data was
                                                             unsuccessful because neither the source
                                                             address parameters nor the destination
                                                             address parameters were present. */
    MAC_ON_TIME_TOO_LONG          = 0xF6, /* 246 */     /**< A receiver enable request was
                                                             unsuccessful because it specified a
                                                             number of symbols that was longer than
                                                             the beacon interval. */
    MAC_PAST_TIME                 = 0xF7, /* 247 */     /**< A receiver enable request was
                                                             unsuccessful because it could not be
                                                             completed within the current superframe
                                                             and was not permitted to be deferred
                                                             until the next superframe. */
    MAC_TRACKING_OFF              = 0xF8, /* 248 */     /**< The device was instructed to start
                                                             sending beacons based on the timing
                                                             of the beacon transmissions of its
                                                             coordinator, but the device is not
                                                             currently tracking the beacon of its
                                                             coordinator. */
    MAC_INVALID_INDEX             = 0xF9, /* 249 */     /**< An attempt to write to a MAC PIB
                                                             attribute that is in a table failed
                                                             because the specified table index
                                                             was out of range. */
    MAC_LIMIT_REACHED             = 0xFA, /* 250 */     /**< A scan operation terminated
                                                             prematurely because the number of
                                                             PAN descriptors stored reached an
                                                             implementation specified maximum. */
    MAC_READ_ONLY                 = 0xFB, /* 251 */     /**< A SET/GET request was issued with the
                                                             identifier of an attribute that is
                                                             read only. */
    MAC_SCAN_IN_PROGRESS          = 0xFC, /* 252 */     /**< A request to perform a scan operation
                                                             failed because the MLME was in the
                                                             process of performing a previously
                                                             initiated scan operation. */
    MAC_SUPERFRAME_OVERLAP        = 0xFD, /* 253 */     /**< The device was instructed to start
                                                             sending beacons based on the timing
                                                             of the beacon transmissions of its
                                                             coordinator, but the instructed start
                                                             time overlapped the transmission time
                                                             of the beacon of its coordinator. */
    /* Statuses out from standard. It is used for synchronous API */
    MAC_IS_NOT_AVAILABLE          = 0xFF  /* 255 */     /**< MAC is not available. */
} mac_status_t;

/**
 * @brief   Payload descriptor.
 *
 * @details Not covered by the standard.
 *          Contains information sufficient to allow the next higher layer to clean
 *          the memory allocated for incoming frames.
 */
typedef struct
{
    /**
     * Pointer to the set of octets forming the frame payload being indicated by
     * the MAC sublayer entity.
     */
    uint8_t               * p_payload;
    /**
     * Offset of the payload data relative to the beginning of the frame.
     * Equal to the MAC header.
     */
    uint8_t                 payload_offset;
} mac_payload_descriptor_t;

/** @brief Command frame IDs defined by the MAC sublayer that are listed
 *  in Table 82 of the standard.
 */
typedef enum
{
    MAC_CMD_ASSOC_REQ            = 0x01, /**< Association request.*/
    MAC_CMD_ASSOC_RESP           = 0x02, /**< Association response.*/
    MAC_CMD_DISASSOC_NTF         = 0x03, /**< Disassociation notification.*/
    MAC_CMD_DATA_REQ             = 0x04, /**< Data request.*/
    MAC_CMD_PANID_CONFLICT_NTF   = 0x05, /**< PAN ID conflict notification.*/
    MAC_CMD_ORPHAN_NTF           = 0x06, /**< Orphan notification.*/
    MAC_CMD_BEACON_REQ           = 0x07, /**< Beacon request.*/
    MAC_CMD_COORD_REALIGN        = 0x08, /**< Coordinator realignment.*/
    MAC_CMD_GTS_REQ              = 0x09  /**< GTS request.*/
} mac_command_id_t;
/** @} */


#endif // MAC_COMMON_H_INCLUDED
