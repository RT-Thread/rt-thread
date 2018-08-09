/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
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
/** @file iot_defines.h
 *
 * @defgroup iot_defines IoT Defines
 * @ingroup iot_sdk_common
 * @{
 * @brief Common IoT definitions that are needed by IoT modules.
 *
 * @details This module abstracts common data structures and constants related to IoT.
 *          These definitions can be used by all the IoT modules.
 */

#ifndef IOT_DEFINES_H__
#define IOT_DEFINES_H__

#include <stdint.h>
#include <sdk_config.h>
#include <nrf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Host to network byte-orders on half word. */
//lint -emacro((572),HTONS) // Suppress warning 572 "Excessive shift value"
#define HTONS(val)  ((uint16_t)((((val) & 0xff00) >> 8) | ((((val) & 0x00ff) << 8))))

/**@brief Host to network byte-orders on full word. */
//lint -emacro((572),HTONL) // Suppress warning 572 "Excessive shift value"
#define HTONL(val)  ((((uint32_t) (val) & 0xff000000) >> 24)  |                                    \
                     (((uint32_t) (val) & 0x00ff0000) >> 8)   |                                    \
                     (((uint32_t) (val) & 0x0000ff00) << 8)   |                                    \
                     (((uint32_t) (val) & 0x000000ff) << 24))

/**@brief Network to host byte-orders on half word. */
#define NTOHS(val)  HTONS(val)

/**@brief Network to host byte-orders on full word. */
#define NTOHL(val)  HTONL(val)

#if defined(NRF52) || defined(NRF52_SERIES)

#define EUI_64_ADDR_SIZE                        8                                                   /**< Size of EUI-64. */
#define IPV6_ADDR_SIZE                          16                                                  /**< Size of IPv6 128-bit address. */
#define IPV6_CONTEXT_IDENTIFIER_NONE            0xFF                                                /**< No context identifier in use. */

#if (BLE_6LOWPAN_LEGACY_MODE == 1)
#define IPV6_IID_FLIP_VALUE                     0x02                                                /**< Value XORed with the first byte of EUI-64 to get IID. In some older Linux implementation, this value could be 0x03. */
#define IPV6_LL_ADDR_SIZE                       8                                                   /**< The link-layer address size used in Neighbor Discovery messages. */
#else
#define IPV6_IID_FLIP_VALUE                     0x00                                                /**< RFC 7668 specifies that no bit is flipped when IID is generated from a Bluetooth Device Address. */
#define IPV6_LL_ADDR_SIZE                       6                                                   /**< The link-layer address size used in Neighbor Discovery messages. */
#endif

#define IPV6_IP_HEADER_SIZE                     40                                                  /**< IPv6 header size. */
#define ICMP6_HEADER_SIZE                       8                                                   /**< ICMP header size. */
#define UDP_HEADER_SIZE                         8                                                   /**< UDP header size. */
#define COAP_HEADER_SIZE                        4                                                   /**< CoAP header size. */

#define IPV6_DEFAULT_VER_TC                     0x60                                                /**< Default value of version and traffic class fields in IPv6 header. */
#define IPV6_DEFAULT_TC_FL                      0x00                                                /**< Default value of traffic class and flow label fields in IPv6 header. */
#define IPV6_DEFAULT_FL                         0x00                                                /**< Default value of the flow label's two last bytes in IPv6 header. */

#define IPV6_NEXT_HEADER_TCP                    6                                                   /**< TCP: protocol number. */
#define IPV6_NEXT_HEADER_UDP                    17                                                  /**< UDP: protocol number. */
#define IPV6_NEXT_HEADER_ICMP6                  58                                                  /**< ICMPv6: protocol number. */
#define IPV6_NEXT_HEADER_RESERVED               255                                                 /**< Reserved value. */

/**@defgroup icmp6_type ICMPv6 message types.
 * @ingroup iot_defines
 * @{
 */

/**@defgroup icmp6_error_type ICMPv6 error messages.
 * @ingroup icmp6_type
 * @{
 */
#define ICMP6_TYPE_DESTINATION_UNREACHABLE      1                                                   /**< ICMPv6: Destination unreachable error message. */
#define ICMP6_TYPE_PACKET_TOO_LONG              2                                                   /**< ICMPv6: Packet too long error message. */
#define ICMP6_TYPE_TIME_EXCEED                  3                                                   /**< ICMPv6: Time-out error message. */
#define ICMP6_TYPE_PARAMETER_PROBLEM            4                                                   /**< ICMPv6: Parameter problem error message. */
/** @} */
#define ICMP6_TYPE_ECHO_REQUEST                 128                                                 /**< ICMPv6: Echo request message. */
#define ICMP6_TYPE_ECHO_REPLY                   129                                                 /**< ICMPv6: Echo reply message. */
#define ICMP6_TYPE_ROUTER_SOLICITATION          133                                                 /**< ICMPv6: Neighbor discovery, router solicitation message. */
#define ICMP6_TYPE_ROUTER_ADVERTISEMENT         134                                                 /**< ICMPv6: Neighbor discovery, router advertisement message. */
#define ICMP6_TYPE_NEIGHBOR_SOLICITATION        135                                                 /**< ICMPv6: Neighbor discovery, neighbor solicitation message. */
#define ICMP6_TYPE_NEIGHBOR_ADVERTISEMENT       136                                                 /**< ICMPv6: Neighbor discovery, neighbor advertisement message. */
/** @} */

/**@brief Initializes IPv6 address. */
#define IPV6_ADDRESS_INITIALIZE(ADDR)                                                              \
        memset((ADDR)->u8, 0, IPV6_ADDR_SIZE)

/**@brief Checks if prefixes match. Length in bits. */
#define IPV6_ADDRESS_PREFIX_CMP(prefix, prefix2, length)                                           \
          ((0 == memcmp(prefix, prefix2, (length>>3) - ((length & 0x7) ? 1 : 0) )) &&              \
          (((prefix[(length>>3)] & (((0xff00) >> (length & 0x7))))) ==                             \
           (prefix2[(length>>3)] & (((0xff00) >> (length & 0x7))))) \
          )

/**@brief Sets address prefix. Length in bits. */
#define IPV6_ADDRESS_PREFIX_SET(pfx_to, pfx_from, length)                                          \
          do {                                                                                     \
             memcpy(pfx_to, pfx_from, length>>3);                                                  \
             if (length & 0x7) {                                                                   \
                uint8_t mask = ((0xff00) >> (length & 0x7));                                       \
                uint8_t last = pfx_from[length>>3] & mask;                                         \
                pfx_to[length>>3] &= ~mask;                                                        \
                pfx_to[length>>3] |= last;                                                         \
             }                                                                                     \
          } while (0)

/**@brief Creates EUI-64 address from EUI-48.
 */
#define IPV6_EUI64_CREATE_FROM_EUI48(eui64, eui48, addr_type)                                      \
             eui64[0] = eui48[5];                                                                  \
             eui64[1] = eui48[4];                                                                  \
             eui64[2] = eui48[3];                                                                  \
             eui64[3] = 0xFF;                                                                      \
             eui64[4] = 0xFE;                                                                      \
             eui64[5] = eui48[2];                                                                  \
             eui64[6] = eui48[1];                                                                  \
             eui64[7] = eui48[0];                                                                  \
             if ((addr_type) == BLE_GAP_ADDR_TYPE_PUBLIC)                                           \
             {                                                                                     \
                 eui64[0] &= ~(IPV6_IID_FLIP_VALUE);                                               \
             }                                                                                     \
             else                                                                                  \
             {                                                                                     \
                 eui64[0] |= IPV6_IID_FLIP_VALUE;                                                  \
             }

/**@brief Creates link-local address from EUI-64. */
#define IPV6_CREATE_LINK_LOCAL_FROM_EUI64(addr, eui64)                                             \
         (addr)->u32[0] = HTONL(0xFE800000);                                                       \
         (addr)->u32[1] = 0;                                                                       \
          memcpy((addr)->u8 + 8, eui64, EUI_64_ADDR_SIZE);                                         \
         (addr)->u8[8] ^= IPV6_IID_FLIP_VALUE;

/**@brief Checks if address is a link-local address. */
#define IPV6_ADDRESS_IS_LINK_LOCAL(addr)                                                           \
          ((addr)->u16[0] == HTONS(0xfe80))

/**@brief Checks if address is a multicast address. */
#define IPV6_ADDRESS_IS_MULTICAST(addr)                                                            \
          ((addr)->u8[0] == 0xff)

/**@brief Checks if address is a multicast all-node address. */
#define IPV6_ADDRESS_IS_ALL_NODE(addr)                                                             \
          (((addr)->u32[0] == HTONL(0xff020000)) &&                                                \
           ((addr)->u32[1] == 0) &&                                                                \
           ((addr)->u32[2] == 0) &&                                                                \
           ((addr)->u32[3] == HTONL(0x01)))

/**@brief Checks if address is a multicast all-router address. */
#define IPV6_ADDRESS_IS_ALL_ROUTER(addr)                                                           \
          (((addr)->u32[0] == HTONL(0xff020000)) &&                                                \
           ((addr)->u32[1] == 0) &&                                                                \
           ((addr)->u32[2] == 0) &&                                                                \
           ((addr)->u32[3] == HTONL(0x02)))

/**@brief Checks if address is a multicast MLDv2 address. */
#define IPV6_ADDRESS_IS_MLDV2_MCAST(addr)                                                          \
          (((addr)->u32[0] == HTONL(0xff020000)) &&                                                \
           ((addr)->u32[1] == 0) &&                                                                \
           ((addr)->u32[2] == 0) &&                                                                \
           ((addr)->u32[3] == HTONL(0x16)))

/**@brief Checks if address is a multicast all-node address. */
#define IPV6_ADDRESS_IS_MULTICAST_SOLICITED_NODE(addr)                                             \
          (((addr)->u32[0] == HTONL(0xff020000)) &&                                                \
           ((addr)->u32[1] == 0) &&                                                                \
           ((addr)->u32[2] == HTONL(0x00000001)) &&                                                \
           ((addr)->u8[12] == 0xFF))

/**@brief Checks if address is an unspecified address. */
#define IPV6_ADDRESS_IS_UNSPECIFIED(addr)                                                          \
          (((addr)->u32[0] == 0) &&                                                                \
           ((addr)->u32[1] == 0) &&                                                                \
           ((addr)->u32[2] == 0) &&                                                                \
           ((addr)->u32[3] == 0)                                                                   \
          )

/**@brief Compares two IPv6 addresses. */
#define IPV6_ADDRESS_CMP(addr1, addr2)                                                             \
        memcmp((addr1)->u8, (addr2)->u8, IPV6_ADDR_SIZE)

/**@brief Swaps two IPv6 addresses. */
#define IPV6_ADDRESS_SWAP(addr1, addr2)                                                            \
         do {                                                                                      \
           ipv6_addr_t addr_temp;                                                                  \
                                                                                                   \
           addr_temp = *addr1;                                                                     \
           *addr1    = *addr2;                                                                     \
           *addr2    = addr_temp;                                                                  \
         } while (0);

/**@brief Prints an IPV6 address. */
#define IPV6_ADDRESS_LOG(addr)                                                                     \
  NRF_LOG_RAW_INFO("%02x%02x:%02x%02x:",(addr).u8[0],(addr).u8[1],(addr).u8[2],(addr).u8[3]);      \
  NRF_LOG_RAW_INFO("%02x%02x:%02x%02x:",(addr).u8[4],(addr).u8[5],(addr).u8[6],(addr).u8[7]);      \
  NRF_LOG_RAW_INFO("%02x%02x:%02x%02x:",(addr).u8[8],(addr).u8[9],(addr).u8[10],(addr).u8[11]);    \
  NRF_LOG_RAW_INFO("%02x%02x:%02x%02x\r\n",(addr).u8[12],(addr).u8[13],(addr).u8[14],(addr).u8[15]);

/**< EUI 64 data type. */
typedef struct
{
    uint8_t identifier[EUI_64_ADDR_SIZE];                                                           /**< 64-bit identifier. */
} eui64_t;

/**< IPv6 address data type. */
typedef union
{
    uint8_t  u8[16];
    uint16_t u16[8];
    uint32_t u32[4];
} ipv6_addr_t;

extern ipv6_addr_t                              ipv6_addr_any;
#define IPV6_ADDR_ANY                           &ipv6_addr_any                                      /**< IPV6 address represents any address. */

extern eui64_t                                  eui64_local_iid;                                    /**< External variable assumed to be implemented in the application with desired EUI-64 to be used as the IID for SLAAC. */
#define EUI64_LOCAL_IID                         &eui64_local_iid                                    /**< EUI-64 IID of the device. */

/** @brief IPv6 address states. */
typedef enum
{
    IPV6_ADDR_STATE_UNUSED = 0,                                                                     /**< IPv6 address is unused. */
    IPV6_ADDR_STATE_TENTATIVE,                                                                      /**< IPv6 tentative address; DUD must be performed. */
    IPV6_ADDR_STATE_PREFERRED,                                                                      /**< IPv6 preferred address; normal. state. */
    IPV6_ADDR_STATE_DEPRECATED                                                                      /**< IPv6 deprecated address. */
} ipv6_addr_state_t;

/**< IPv6 header structure. */
typedef struct
{
    uint8_t     version_traffic_class;                                                              /**< Version and traffic class field. */
    uint8_t     traffic_class_flowlabel;                                                            /**< Traffic class and flow label field. */
    uint16_t    flowlabel;                                                                          /**< Flow label, 2nd part of field. */
    uint16_t    length;                                                                             /**< Length of IPv6 payload field. */
    uint8_t     next_header;                                                                        /**< Next header field. */
    uint8_t     hoplimit;                                                                           /**< Hop limit field. */
    ipv6_addr_t srcaddr;                                                                            /**< IPv6 source address field. */
    ipv6_addr_t destaddr;                                                                           /**< IPv6 destination address field. */
} ipv6_header_t;

/**< IPv6 UDP header structure. */
typedef struct
{
    uint16_t srcport;                                                                               /**< Source port. */
    uint16_t destport;                                                                              /**< Destination port. */
    uint16_t length;                                                                                /**< Length of data with UDP header. */
    uint16_t checksum;                                                                              /**< UDP checksum field. */
} udp6_header_t;

/**< IPv6 ICMP header structure. */
typedef struct
{
    uint8_t  type;                                                                                  /**< Type of ICMP message. See @ref icmp6_type for possible values. */
    uint8_t  code;                                                                                  /**< Code related to the type field. */
    uint16_t checksum;                                                                              /**< ICMP6 checksum field. */
    union                                                                                           /**< Message specific fields if any. */
    {
        uint32_t mtu;                                                                               /**< MTU of next hop limit. Used only with Packet Too Big Error Message. */
        uint32_t unused;                                                                            /**< Unused fields for error messages that do not have any auxiliary information. */
        uint32_t offset;                                                                            /**< Offset field used only with Parameter Problem error message. */
        struct {                                                                                    /**< Identifier and sequence number information specific associated with echo request and response. */
            uint16_t id;                                                                            /**< Identifier. */
            uint16_t sequence;                                                                      /**< Sequence number. */
        } echo;
    } sp;
} icmp6_header_t;

#endif // NRF52

#ifdef __cplusplus
}
#endif

#endif //IOT_DEFINES_H__

/**@} */
