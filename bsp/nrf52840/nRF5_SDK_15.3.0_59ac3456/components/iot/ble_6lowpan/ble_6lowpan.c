/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_sdk_6lowpan 6LoWPAN Adaptation Layer
 * @{
 * @ingroup ble_sdk_iot
 * @brief 6LoWPAN Adaptation Layer
 *
 * @details This module enables 6LoWPAN over Bluetooth Low Energy.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_soc.h"
#include "nordic_common.h"
#include "ble_ipsp.h"
#include "ble_6lowpan.h"
#include "iot_common.h"
#include "iot_context_manager.h"
#include "app_util_platform.h"
#include "mem_manager.h"

/**
 * @defgroup ble_sdk_6lowpan Module's Log Macros
 * @details Macros used for creating module logs which can be useful in understanding handling
 *          of events or actions on API requests. These are intended for debugging purposes and
 *          can be enabled by defining the IOT_BLE_6LOWPAN_CONFIG_LOG_ENABLED.
 * @note If NRF_LOG_ENABLED is disabled, having IOT_BLE_6LOWPAN_CONFIG_LOG_ENABLED
 *       has no effect.
 * @{
 */

#if IOT_BLE_6LOWPAN_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME 6lowpan

#define NRF_LOG_LEVEL       IOT_BLE_6LOWPAN_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_BLE_6LOWPAN_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_BLE_6LOWPAN_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define BLE_6LOWPAN_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define BLE_6LOWPAN_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define BLE_6LOWPAN_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define BLE_6LOWPAN_ENTRY() BLE_6LOWPAN_TRC(">> %s", __func__)
#define BLE_6LOWPAN_EXIT()  BLE_6LOWPAN_TRC("<< %s", __func__)

#else // IOT_BLE_6LOWPAN_CONFIG_LOG_ENABLED

#define BLE_6LOWPAN_TRC(...)                                                                           /**< Disables traces. */
#define BLE_6LOWPAN_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define BLE_6LOWPAN_ERR(...)                                                                           /**< Disables error logs. */

#define BLE_6LOWPAN_ENTRY(...)
#define BLE_6LOWPAN_EXIT(...)

#endif // IOT_BLE_6LOWPAN_CONFIG_LOG_ENABLED



/** @} */

/**
 * @defgroup ble_6lowpan_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define BLE_6LOWPAN_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_6lowpan_mutex)                                  /**< Lock module using mutex */
#define BLE_6LOWPAN_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_6lowpan_mutex)                                /**< Unlock module using mutex */
/** @} */

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          BLE_6LOWPAN_DISABLE_API_PARAM_CHECK should be set to 0 to enable these checks.
 *
 * @{
 */

#if (BLE_6LOWPAN_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
    if (m_event_handler == NULL)                                                                   \
    {                                                                                              \
        return (SDK_ERR_MODULE_NOT_INITIALIZED | BLE_6LOWPAN_ERR_BASE);                            \
    }

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | BLE_6LOWPAN_ERR_BASE);                                            \
    }

/**@brief Check if packet has at least IP Header in it (40 bytes). */
#define PACKET_LENGTH_CHECK(PARAM)                                                                 \
    if ((PARAM) < IPV6_IP_HEADER_SIZE)                                                             \
    {                                                                                              \
        return (NRF_ERROR_INVALID_PARAM | BLE_6LOWPAN_ERR_BASE);                                   \
    }

#else // BLE_6LOWPAN_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define NULL_PARAM_CHECK(PARAM)
#define PACKET_LENGTH_CHECK(PARAM)

#endif // BLE_6LOWPAN_DISABLE_API_PARAM_CHECK

/** @} */

/**@brief Maximum different between compressed and uncompressed packet. */
#define IPHC_MAX_COMPRESSED_DIFF (IPV6_IP_HEADER_SIZE + UDP_HEADER_SIZE - 7)

/**@brief Transmit FIFO mask. */
#define TX_FIFO_MASK (BLE_6LOWPAN_TX_FIFO_SIZE - 1)

/**@brief Value and position of IPHC dispatch. */
#define IPHC_START_DISPATCH               0x03
#define IPHC_START_DISPATCH_POS           5

/**@brief Values and positions of IPHC fields. */
#define IPHC_TF_MASK                      0x18
#define IPHC_TF_POS                       3
#define IPHC_NH_MASK                      0x04
#define IPHC_NH_POS                       2
#define IPHC_HLIM_MASK                    0x03
#define IPHC_HLIM_POS                     0
#define IPHC_CID_MASK                     0x80
#define IPHC_CID_POS                      7
#define IPHC_SAC_MASK                     0x40
#define IPHC_SAC_POS                      6
#define IPHC_SAM_MASK                     0x30
#define IPHC_SAM_POS                      4
#define IPHC_M_MASK                       0x08
#define IPHC_M_POS                        3
#define IPHC_DAC_MASK                     0x04
#define IPHC_DAC_POS                      2
#define IPHC_DAM_MASK                     0x03
#define IPHC_DAM_POS                      0

/**@brief IPHC Traffic Flow compression. */
#define IPHC_TF_DSCP_MASK                 0x3F
#define IPHC_TF_ECN_MASK                  0xC0
#define IPHC_TF_ECN_POS                   6

/**@brief IPHC values of fields. */
#define IPHC_TF_00                        0x00
#define IPHC_TF_01                        0x01
#define IPHC_TF_10                        0x02
#define IPHC_TF_11                        0x03
#define IPHC_NH_0                         0x00
#define IPHC_NH_1                         0x01
#define IPHC_HLIM_00                      0x00
#define IPHC_HLIM_01                      0x01
#define IPHC_HLIM_10                      0x02
#define IPHC_HLIM_11                      0x03
#define IPHC_CID_0                        0x00
#define IPHC_CID_1                        0x01
#define IPHC_SAC_0                        0x00
#define IPHC_SAC_1                        0x01
#define IPHC_SAM_00                       0x00
#define IPHC_SAM_01                       0x01
#define IPHC_SAM_10                       0x02
#define IPHC_SAM_11                       0x03
#define IPHC_M_0                          0x00
#define IPHC_M_1                          0x01
#define IPHC_DAC_0                        0x00
#define IPHC_DAC_1                        0x01
#define IPHC_DAM_00                       0x00
#define IPHC_DAM_01                       0x01
#define IPHC_DAM_10                       0x02
#define IPHC_DAM_11                       0x03

/**@brief IPHC Context Identifier compression. */
#define IPHC_CID_SOURCE_MASK              0xF0
#define IPHC_CID_SOURCE_POS               4
#define IPHC_CID_DESTINATION_MASK         0x0F
#define IPHC_CID_DESTINATION_POS          0

/**@brief IPHC Next Header Compression dispatches. */
#define IPHC_NHC_UDP_DISPATCH             0xF0
#define IPHC_NHC_UDP_MASK                 0xF8
#define IPHC_NHC_EXT_DISPATCH             0xE0
#define IPHC_NHC_EXT_MASK                 0xF0

/**@brief IPHC Next Header Compression UDP fields. */
#define IPHC_NHC_UDP_CSUM_MASK            0x04
#define IPHC_NHC_UDP_CSUM_POS             0x02
#define IPHC_NHC_UDP_PORTS_MASK           0x03
#define IPHC_NHC_UDP_PORTS_POS            0x00
#define IPHC_NHC_UDP_PORTS_00             0x00
#define IPHC_NHC_UDP_PORTS_01             0x01
#define IPHC_NHC_UDP_PORTS_10             0x02
#define IPHC_NHC_UDP_PORTS_11             0x03

#define IPHC_NHC_UDP_COMPRESSION_MAX_MASK 0xFFF0
#define IPHC_NHC_UDP_COMPRESSION_MAX      0xF0B0
#define IPHC_NHC_UDP_COMPRESSION_MIN_MASK 0xFF00
#define IPHC_NHC_UDP_COMPRESSION_MIN      0xF000

/**@brief IPHC Next Header Compression Extended Header fields. */
#define IPHC_NHC_EXT_EID_MASK             0x0E
#define IPHC_NHC_EXT_EID_POS              0x01
#define IPHC_NHC_EXT_EID_HOP_BY_HOP       0x00
#define IPHC_NHC_EXT_EID_ROUTING          0x01
#define IPHC_NHC_EXT_EID_FRAGMENT         0x02
#define IPHC_NHC_EXT_EID_DESTINATION      0x03
#define IPHC_NHC_EXT_EID_MOBILITY         0x04
#define IPHC_NHC_EXT_EID_IPV6             0x07

/**@brief IPHC default value of IPv6 Header fields. */
#define IPHC_IPHEADER_VER_TC              0x60
#define IPHC_IPHEADER_TC_FL               0x00
#define IPHC_IPHEADER_FL                  0x00

/**@brief Check if address can be fully elidable. */
#define IPV6_ADDRESS_IS_FULLY_ELIDABLE(ll_addr, addr)             \
    (((addr)->u8[8] == (((ll_addr[0]) ^ IPV6_IID_FLIP_VALUE))) && \
     ((addr)->u8[9] == ll_addr[1]) &&                             \
     ((addr)->u8[10] == ll_addr[2]) &&                            \
     ((addr)->u8[11] == ll_addr[3]) &&                            \
     ((addr)->u8[12] == ll_addr[4]) &&                            \
     ((addr)->u8[11] == 0xff) &&                                  \
     ((addr)->u8[12] == 0xfe) &&                                  \
     ((addr)->u8[13] == ll_addr[5]) &&                            \
     ((addr)->u8[14] == ll_addr[6]) &&                            \
     ((addr)->u8[15] == ll_addr[7])                               \
    )

/**@brief Check if address is 16-bit and can be compressed.
 *        16-bit COMPRESSABLE format: ::0000:00ff:fe00:XXXX.
 */
#define IPV6_ADDRESS_IS_16_BIT_COMPRESSABLE(addr)       \
    (((addr)->u8[8] == 0) &&                            \
     ((addr)->u8[9] == 0) &&                            \
     ((addr)->u8[10] == 0) &&                           \
     ((addr)->u8[11] == 0xff) &&                        \
     ((addr)->u8[12] == 0xfe) &&                        \
     ((addr)->u8[13] == 0)                              \
    )

/**@brief Check if address is 48-bit multi-cast and can be compressed.
 *        48-bit COMPRESSABLE format: FFXX::00XX:XXXX:XXXX.
 */
#define IPV6_ADDRESS_IS_48_BIT_MCAST_COMPRESSABLE(addr) \
    (((addr)->u16[1] == 0) &&                           \
     ((addr)->u16[2] == 0) &&                           \
     ((addr)->u16[3] == 0) &&                           \
     ((addr)->u16[4] == 0) &&                           \
     ((addr)->u8[10] == 0)                              \
    )

/**@brief Check if address is 32-bit multi-cast and can be compressed.
 *        32-bit COMPRESSABLE format: FFXX::00XX:XXXX.
 */
#define IPV6_ADDRESS_IS_32_BIT_MCAST_COMPRESSABLE(addr) \
    (((addr)->u16[1] == 0) &&                           \
     ((addr)->u32[1] == 0) &&                           \
     ((addr)->u32[2] == 0) &&                           \
     ((addr)->u8[12] == 0)                              \
    )

/**@brief Check if address is 8-bit multi-cast and can be compressed.
 *        8-bit COMPRESSABLE format: FF02::XX.
 */
#define IPV6_ADDRESS_IS_8_BIT_MCAST_COMPRESSABLE(addr)  \
    (((addr)->u8[1] == 2) &&                            \
     ((addr)->u16[1] == 0) &&                           \
     ((addr)->u32[1] == 0) &&                           \
     ((addr)->u32[2] == 0) &&                           \
     ((addr)->u16[6] == 0) &&                           \
     ((addr)->u8[14] == 0)                              \
    )

/******************************************************************************
 * 6LoWPAN Core and Transport structures.
 ******************************************************************************/

/**@brief Element of TX Queue. */
typedef struct
{
    uint8_t * p_mem_block;                                                                          /**< Base address of memory block, using for release the buffer. */
    uint8_t * p_data;                                                                               /**< Pointer to TX Data. */
    uint16_t  data_len;                                                                             /**< Size of TX data.  */
} tx_packet_t;

/**@brief A TX Queue (FIFO) structure. */
typedef struct
{
    tx_packet_t       packets[BLE_6LOWPAN_TX_FIFO_SIZE];                                            /**< Array of TX packet in FIFO.              */
    volatile uint32_t read_pos;                                                                     /**< Next read position in the FIFO buffer.   */
    volatile uint32_t write_pos;                                                                    /**< Next write position in the FIFO buffer.  */
} tx_fifo_t;

/**@brief Transport instance structure. */
typedef struct
{
    iot_interface_t         interface;
    ble_ipsp_handle_t       handle;
    tx_fifo_t               tx_fifo;
    tx_packet_t           * p_tx_cur_packet;
} transport_instance_t;

/******************************************************************************
 * @name Global variables
 *****************************************************************************/

/**@brief Application Event Handler. */
static ble_6lowpan_evt_handler_t m_event_handler = NULL;

/**@brief Hop Limit options. */
static const uint8_t m_hop_limit[] = {0, 1, 64, 255};

/**@brief Link-local prefix. */
static const uint8_t m_link_local_prefix[] = {0xFE, 0x80};

/**@brief Additional extenders for EUI-48. */
static const uint8_t m_link_local_16_middle[] = {0xFF, 0xFE};

/**@brief nRF EUI-64 link-layer address */
static eui64_t m_ll_addr = {{0, 0, 0, 0, 0, 0, 0, 0}};

/**@brief Transport interfaces table. */
static transport_instance_t m_instances[BLE_6LOWPAN_MAX_INTERFACE];

/**@brief Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
SDK_MUTEX_DEFINE(m_6lowpan_mutex)

/******************************************************************************
 * @name 6LoWPAN core functions
 *****************************************************************************/

/**@brief Function for checking if IID can be completely elided. This situation
 *        may happen when receiver can still reconstruct IPv6 address by using context
 *        prefix and Link Layer address.
 *
 * @param[in]   p_addr     Pointer to IPv6 address.
 * @param[in]   p_context  Pointer to context entry that is compressed with.
 * @param[in]   p_ll_addr  Pointer to link layer address of BT-LE device.
 *
 * @return      True if IID can be elided, False otherwise.
 */
static bool is_context_cover_iid(const ipv6_addr_t   * p_addr,
                                 const iot_context_t * p_context,
                                 const eui64_t       * p_ll_addr)
{
    uint32_t start_byte, offset;

    // Context covers IPv6 address by its size.
    if (p_context->prefix_len == 128)
    {
        return true;
    }

    // Check if IID can be retrieved in case of longer prefix than 64 bits.
    if (p_context->prefix_len > 64)
    {
        // Check only IID fields that are not covered by context prefix.
        start_byte = p_context->prefix_len >> 3;
        offset = p_context->prefix_len % 8;

        // Check all bytes from the second one.
        if (start_byte == 15 ||
            0 == memcmp(&p_addr->u8[start_byte+1], &p_ll_addr->identifier[start_byte-7], 15-start_byte))
        {
            // Then check first byte.
            return (p_addr->u8[start_byte] << offset) == (p_ll_addr->identifier[start_byte-8] << offset);
        }
    }

    return false;
}

/**@brief Function for decoding Next Header Compression.
 *        It supports UDP header decompression.
 *
 * @param[in]   p_iphc   Pointer to currently process IPHC field.
 * @param[in]   p_data   Pointer to constructing uncompressed IP packet.
 * @param[in]   p_length Place of UDP header in case of Extension Header.
 * @param[out]  p_length Length of the constructed uncompressed header.
 *
 * @return      Number of processed IPHC field.
 */
static uint32_t iphc_nhc_decode(uint8_t * p_iphc, uint8_t * p_data, uint16_t * p_length)
{
    uint8_t   nhc_dispatch = *p_iphc;
    uint8_t * p_nhc        = p_iphc;

    ipv6_header_t * iphdr = (ipv6_header_t *)&p_data[0];

    // UDP Next Header Compression.
    if ((nhc_dispatch & IPHC_NHC_UDP_MASK) == IPHC_NHC_UDP_DISPATCH)
    {
        udp6_header_t * udphdr = (udp6_header_t * )&p_data[IPV6_IP_HEADER_SIZE + *p_length];

        iphdr->next_header = IPV6_NEXT_HEADER_UDP;

        // Start length from UDP Header Size.
        *p_length += UDP_HEADER_SIZE;
        p_nhc     += 1;

        switch ((nhc_dispatch & IPHC_NHC_UDP_PORTS_MASK) >> IPHC_NHC_UDP_PORTS_POS)
        {
            case IPHC_NHC_UDP_PORTS_00:
                memcpy(&udphdr->srcport, p_nhc, 2);
                memcpy(&udphdr->destport, p_nhc + 2, 2);
                p_nhc += 4;
                break;

            case IPHC_NHC_UDP_PORTS_01:
                memcpy(&udphdr->srcport, p_nhc, 2);
                udphdr->destport = HTONS(IPHC_NHC_UDP_COMPRESSION_MIN | *(p_nhc + 2));
                p_nhc           += 3;
                break;

            case IPHC_NHC_UDP_PORTS_10:
                udphdr->srcport = HTONS(IPHC_NHC_UDP_COMPRESSION_MIN | *p_nhc);
                memcpy(&udphdr->destport, p_nhc + 1, 2);
                p_nhc += 3;
                break;

            case IPHC_NHC_UDP_PORTS_11:
                udphdr->srcport  = HTONS((IPHC_NHC_UDP_COMPRESSION_MAX | ((*p_nhc & 0xf0) >> 4)));
                udphdr->destport = HTONS((IPHC_NHC_UDP_COMPRESSION_MAX | ((*p_nhc & 0x0f))));
                p_nhc           += 1;
                break;
        }

        if ((nhc_dispatch & IPHC_NHC_UDP_CSUM_MASK) >> IPHC_NHC_UDP_CSUM_POS)
        {
            udphdr->checksum = 0;
        }
        else
        {
            memcpy(&udphdr->checksum, p_nhc, 2);
            p_nhc += 2;
        }
    }

    return (p_nhc - p_iphc);
}

/**@brief Function for encoding Next Header Compression.
 *        It supports UDP header compression.
 *
 * @param[in]   p_iphc   Pointer to currently process IPHC field.
 * @param[in]   p_data   Pointer to constructing uncompressed IP packet.
 * @param[in]   p_length Place of UDP header in case of Extension Header.
 * @param[out]  p_length Length of the constructed uncompressed header.
 *
 * @return      Number of processed IPHC field.
 */
static uint32_t iphc_nhc_encode(uint8_t * p_iphc, const uint8_t * p_data, uint16_t * p_length)
{
    uint8_t      * p_nhc = p_iphc;
    ipv6_header_t * iphdr = (ipv6_header_t *)p_data;

    switch (iphdr->next_header)
    {
        case IPV6_NEXT_HEADER_UDP:
        {
            udp6_header_t * udphdr = (udp6_header_t * )&p_data[IPV6_IP_HEADER_SIZE + *p_length];
            *p_iphc = IPHC_NHC_UDP_DISPATCH;
            p_nhc  += 1;

            // Full 4-bit compression for source and destination ports.
            if ( ((HTONS(udphdr->srcport) & IPHC_NHC_UDP_COMPRESSION_MAX_MASK) ==
                  IPHC_NHC_UDP_COMPRESSION_MAX) &&
                 ((HTONS(udphdr->destport) & IPHC_NHC_UDP_COMPRESSION_MAX_MASK) ==
                  IPHC_NHC_UDP_COMPRESSION_MAX))
            {
                *p_iphc |= (IPHC_NHC_UDP_PORTS_11 >> IPHC_NHC_UDP_PORTS_POS);

                *p_nhc =
                    (((HTONS(udphdr->srcport) & 0x0f) << 4) | (HTONS(udphdr->destport) & 0x0f));
                p_nhc += 1;
            }
            // Source port compressed, destination in-line.
            else if ((HTONS(udphdr->srcport) & IPHC_NHC_UDP_COMPRESSION_MIN_MASK) ==
                     IPHC_NHC_UDP_COMPRESSION_MIN)
            {
                *p_iphc |= (IPHC_NHC_UDP_PORTS_10 >> IPHC_NHC_UDP_PORTS_POS);

                *p_nhc = (HTONS(udphdr->srcport) & 0xff);
                p_nhc += 1;

                memcpy(p_nhc, &udphdr->destport, 2);
                p_nhc += 2;
            }
            // Source port in-line, destination compressed.
            else if ((HTONS(udphdr->destport) & IPHC_NHC_UDP_COMPRESSION_MIN_MASK) ==
                     IPHC_NHC_UDP_COMPRESSION_MIN)
            {
                *p_iphc |= (IPHC_NHC_UDP_PORTS_01 >> IPHC_NHC_UDP_PORTS_POS);

                memcpy(p_nhc, &udphdr->srcport, 2);
                p_nhc += 2;

                *p_nhc = (HTONS(udphdr->destport) & 0xff);
                p_nhc += 1;
            }
            // Source and destination port in-line.
            else
            {
                *p_iphc |= (IPHC_NHC_UDP_PORTS_00 >> IPHC_NHC_UDP_PORTS_POS);

                memcpy(p_nhc, &udphdr->srcport, 2);
                memcpy(p_nhc + 2, &udphdr->destport, 2);
                p_nhc += 4;
            }

            // Checksum always in-line, [RFC4944] disallows the compression of the
            // UDP checksum. The compressor MUST NOT set the C bit unless it has received
            // authorization.
            memcpy(p_nhc, &udphdr->checksum, 2);
            p_nhc += 2;

            // Set UDP ext header size.
            *p_length = UDP_HEADER_SIZE;

            break;
        }
    }

    return (p_nhc - p_iphc);
}


 /**@brief Function for checking if it's possible to use NHC.
 *
 * @param[in]   next_header Value of Next Header field in IPv6 packet.
 *
 * @return      Returns 1 if header can be compressed, otherwise 0.
 */
static uint32_t iphc_nhc_compressable(uint8_t next_header)
{
    switch (next_header)
    {
        case IPV6_NEXT_HEADER_UDP:
            return 1;
    }

    return 0;
}


/**@brief Function for decoding IPHC (IP Header Compression) defined in
 *        IETF RFC 6282.
 *
 * @param[in]   p_instance   Transport instance from where packet came.
 * @param[in]   p_input      Pointer to received packet from IPSP module.
 * @param[in]   input_len    Length of received packet.
 * @param[in]   p_output     Pointer to allocated buffer for decompressed packet.
 * @param[out]  p_output     Pointer to decompressed IPv6 packet.
 * @param[out]  p_output_len Length of decompressed IPv6 packet.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t iphc_decode(iot_interface_t      * p_interface,
                            uint8_t              * p_output,
                            uint16_t             * p_output_len,
                            uint8_t              * p_input,
                            uint16_t               input_len,
                            iot_context_id_t     * p_rx_contexts)
{
    uint32_t                retval      = NRF_SUCCESS;
    uint32_t                err_code    = NRF_SUCCESS;
    uint8_t               * p_iphc      = p_input;
    uint8_t                 sci         = IPV6_CONTEXT_IDENTIFIER_NONE;
    uint8_t                 dci         = IPV6_CONTEXT_IDENTIFIER_NONE;
    uint16_t                nhc_length  = 0;
    iot_context_t         * p_ctx       = NULL;

    // IPv6 headers used in decompression.
    ipv6_header_t         * p_iphdr     = (ipv6_header_t *)p_output;
    udp6_header_t         * p_udphdr    = (udp6_header_t *)&p_output[IPV6_IP_HEADER_SIZE];

    // Check if format of packet is correct.
    if ((p_input[0] >> IPHC_START_DISPATCH_POS) != IPHC_START_DISPATCH)
    {
        BLE_6LOWPAN_ERR("[6LoWPAN] Packet has incorrect IPHC structure!");

        return NRF_ERROR_INVALID_DATA;
    }

    // IPHC basic form has 2 bytes.
    p_iphc += 2;

    // RFC6282: An additional 8-bit Context Identifier Extension field
    // immediately follows the Destination Address Mode (DAM) field.
    if ((p_input[1] & IPHC_CID_MASK))
    {
        sci     = ((*p_iphc & IPHC_CID_SOURCE_MASK) >> IPHC_CID_SOURCE_POS);
        dci     = ((*p_iphc & IPHC_CID_DESTINATION_MASK) >> IPHC_CID_DESTINATION_POS);
        p_iphc += 1;
    }

    // Set proper context identifiers.
    p_rx_contexts->src_cntxt_id  = sci;
    p_rx_contexts->dest_cntxt_id = dci;

    switch ((p_input[0] & IPHC_TF_MASK) >> IPHC_TF_POS)
    {
        case IPHC_TF_11:
            // Elide Traffic Class and Flow Label.
            p_iphdr->version_traffic_class   = IPHC_IPHEADER_VER_TC;
            p_iphdr->traffic_class_flowlabel = IPHC_IPHEADER_TC_FL;
            p_iphdr->flowlabel               = IPHC_IPHEADER_FL;
            break;

        case IPHC_TF_10:
            // Elide Flow Label.
            p_iphdr->version_traffic_class   = IPHC_IPHEADER_VER_TC | ((*p_iphc & IPHC_TF_DSCP_MASK) >> 2);
            p_iphdr->traffic_class_flowlabel = ((*p_iphc & 0x03) << 6) |
                                             ((*p_iphc & IPHC_TF_ECN_MASK) >> 2);
            p_iphdr->flowlabel = IPHC_IPHEADER_FL;
            p_iphc          += 1;
            break;

        case IPHC_TF_01:
            // Elide DSCP, carry ECN and Flow Label.
            p_iphdr->version_traffic_class   = IPHC_IPHEADER_VER_TC;
            p_iphdr->traffic_class_flowlabel = ((*p_iphc & IPHC_TF_ECN_MASK) >> 2) |
                                             ((*p_iphc & 0x0f));
            memcpy(&p_iphdr->flowlabel, p_iphc + 1, 2);
            p_iphc += 3;
            break;

        case IPHC_TF_00:
            // Flow Label and Traffic Class in-line.
            p_iphdr->version_traffic_class   = IPHC_IPHEADER_VER_TC | ((*p_iphc & IPHC_TF_DSCP_MASK) >> 2);
            p_iphdr->traffic_class_flowlabel = ((*p_iphc & 0x03) << 6) |
                                             ((*p_iphc & IPHC_TF_ECN_MASK) >> 2) |
                                             ((*(p_iphc + 1) & 0x0f));
            memcpy(&p_iphdr->flowlabel, p_iphc + 2, 2);
            p_iphc += 4;
            break;
    }

    if (!((p_input[0] & IPHC_NH_MASK)))
    {
        // Set next header.
        p_iphdr->next_header = *p_iphc++;
    }

    if ((p_input[0] & IPHC_HLIM_MASK))
    {
        p_iphdr->hoplimit = m_hop_limit[((p_input[0] & IPHC_HLIM_MASK) >> IPHC_HLIM_POS)];
    }
    else
    {
        p_iphdr->hoplimit = *p_iphc++;
    }

    // Clear IPv6 addresses.
    memset(p_iphdr->srcaddr.u8, 0, IPV6_ADDR_SIZE);
    memset(p_iphdr->destaddr.u8, 0, IPV6_ADDR_SIZE);

    // Source address decompression.
    if ((p_input[1] & IPHC_SAC_MASK) >> IPHC_SAC_POS)
    {
        if ( ((p_input[1] & IPHC_SAM_MASK) >> IPHC_SAM_POS) == IPHC_SAM_00 )
        {
            // Unspecified address.
            memset(p_iphdr->srcaddr.u8, 0, IPV6_ADDR_SIZE);
        }
        else
        {
            switch ((p_input[1] & IPHC_SAM_MASK) >> IPHC_SAM_POS)
            {
                case IPHC_SAM_01:
                    // 64 bits in-line, first IID then prefix in case prefix > 64.
                    memcpy(p_iphdr->srcaddr.u8 + 8, p_iphc, 8);
                    p_iphc += 8;
                    break;

                case IPHC_SAM_10:
                    // 16 bits in-line.
                    memcpy(p_iphdr->srcaddr.u8 + 14, p_iphc, 2);
                    memcpy(p_iphdr->srcaddr.u8 + 11, m_link_local_16_middle, 2);
                    p_iphc += 2;
                    break;

                case IPHC_SAM_11:
                    // Take the address from lower layer.
                    memcpy(p_iphdr->srcaddr.u8 + 8, p_interface->peer_addr.identifier, 8);
                    p_iphdr->srcaddr.u8[8] ^= IPV6_IID_FLIP_VALUE;
                    break;
            }

            /* Look up for context */
            BLE_6LOWPAN_MUTEX_UNLOCK();
            err_code = iot_context_manager_get_by_cid(p_interface, sci, &p_ctx);
            BLE_6LOWPAN_MUTEX_LOCK();

            if (err_code == NRF_SUCCESS)
            {
              /* Add prefix */
              IPV6_ADDRESS_PREFIX_SET(p_iphdr->srcaddr.u8, p_ctx->prefix.u8, p_ctx->prefix_len);
            }
            else
            {
              /* Set error and continue decompression. */
              retval = BLE_6LOWPAN_CID_NOT_FOUND;

              BLE_6LOWPAN_ERR("Cannot find context identifier in the context table.");
            }
        }
    }
    else
    {
        switch ((p_input[1] & IPHC_SAM_MASK) >> IPHC_SAM_POS)
        {
            case IPHC_SAM_00:
                // Full 128-bits in-line.
                memcpy(p_iphdr->srcaddr.u8, p_iphc, IPV6_ADDR_SIZE);
                p_iphc += IPV6_ADDR_SIZE;
                break;

            case IPHC_SAM_01:
                // 64 bits in-line, first IID then prefix in case prefix > 64.
                memcpy(p_iphdr->srcaddr.u8, m_link_local_prefix, 2);
                memcpy(p_iphdr->srcaddr.u8 + 8, p_iphc, 8);
                p_iphc += 8;
                break;

            case IPHC_SAM_10:
                // 16 bits in-line.
                memcpy(p_iphdr->srcaddr.u8, m_link_local_prefix, 2);
                memcpy(p_iphdr->srcaddr.u8 + 11, m_link_local_16_middle, 2);
                memcpy(p_iphdr->srcaddr.u8 + 14, p_iphc, 2);
                p_iphc += 2;
                break;

            case IPHC_SAM_11:
                memcpy(p_iphdr->srcaddr.u8, m_link_local_prefix, 2);
                memcpy(p_iphdr->srcaddr.u8 + 8, p_interface->peer_addr.identifier, 8);
                p_iphdr->srcaddr.u8[8] ^= IPV6_IID_FLIP_VALUE;
                break;
        }
    }

    // Destination address decompression.
    if ((p_input[1] & IPHC_DAC_MASK) >> IPHC_DAC_POS)
    {
        if ((p_input[1] & IPHC_M_MASK) >> IPHC_M_POS)
        {
            switch ((p_input[1] & IPHC_DAM_MASK) >> IPHC_DAM_POS)
            {
                case IPHC_DAM_00:
                    // 48-bits in-line.
                    p_iphdr->destaddr.u8[0] = 0xff;
                    memcpy(p_iphdr->destaddr.u8 + 1, p_iphc, 2);
                    memcpy(p_iphdr->destaddr.u8 + 12, p_iphc + 2, 4);
                    p_iphc += 6;
                    break;

                default:
                    BLE_6LOWPAN_ERR("Reserved value in IPHC header!");
                    return NRF_ERROR_INVALID_DATA;
            }
        }
        else
        {
            switch ((p_input[1] & IPHC_DAM_MASK) >> IPHC_DAM_POS)
            {
                case IPHC_DAM_01:
                    // 64 bits in-line.
                    memcpy(p_iphdr->destaddr.u8 + 8, p_iphc, 8);
                    p_iphc += 8;
                    break;

                case IPHC_DAM_10:
                    // 16 bits in-line.
                    memcpy(p_iphdr->destaddr.u8 + 11, m_link_local_16_middle, 2);
                    memcpy(p_iphdr->destaddr.u8 + 14, p_iphc, 2);
                    p_iphc += 2;
                    break;

                case IPHC_DAM_11:
                    // Take the address from lower layer.
                    memcpy(p_iphdr->destaddr.u8 + 8, p_interface->local_addr.identifier, 8);
                    p_iphdr->destaddr.u8[8] ^= IPV6_IID_FLIP_VALUE;
                    break;

                default:
                    BLE_6LOWPAN_ERR("Reserved value in IPHC header!");
                    return NRF_ERROR_INVALID_DATA;
            }

            /* Look up for context */
            BLE_6LOWPAN_MUTEX_UNLOCK();
            err_code = iot_context_manager_get_by_cid(p_interface, dci, &p_ctx);
            BLE_6LOWPAN_MUTEX_LOCK();

            if (err_code == NRF_SUCCESS)
            {
              /* Add prefix */
              IPV6_ADDRESS_PREFIX_SET(p_iphdr->destaddr.u8, p_ctx->prefix.u8, p_ctx->prefix_len);
            }
            else
            {
              /* Set error and continue decompression. */
              retval = BLE_6LOWPAN_CID_NOT_FOUND;

              BLE_6LOWPAN_ERR("Cannot find context identifier in the context table.");
            }
        }
    }
    else
    {
        if ((p_input[1] & IPHC_M_MASK) >> IPHC_M_POS)
        {
            switch ((p_input[1] & IPHC_DAM_MASK) >> IPHC_DAM_POS)
            {
                case IPHC_DAM_00:
                    // 128 bits in-line.
                    memcpy(p_iphdr->destaddr.u8, p_iphc, IPV6_ADDR_SIZE);
                    p_iphc += IPV6_ADDR_SIZE;
                    break;

                case IPHC_DAM_01:
                    // 48 bits in-line.
                    p_iphdr->destaddr.u8[0] = 0xFF;
                    p_iphdr->destaddr.u8[1] = *p_iphc;
                    memcpy(p_iphdr->destaddr.u8 + 11, p_iphc + 1, 5);
                    p_iphc += 6;
                    break;

                case IPHC_DAM_10:
                    // 32 bits in-line.
                    p_iphdr->destaddr.u8[0] = 0xFF;
                    p_iphdr->destaddr.u8[1] = *p_iphc;
                    memcpy(p_iphdr->destaddr.u8 + 13, p_iphc + 1, 3);
                    p_iphc += 4;
                    break;

                case IPHC_DAM_11:
                    // 8 bits in-line.
                    p_iphdr->destaddr.u8[0]  = 0xFF;
                    p_iphdr->destaddr.u8[1]  = 0x02;
                    p_iphdr->destaddr.u8[15] = *p_iphc;
                    p_iphc                  += 1;
                    break;
            }
        }
        else
        {
            switch ((p_input[1] & IPHC_DAM_MASK) >> IPHC_DAM_POS)
            {
                case IPHC_DAM_00:
                    // 128 bits in-line.
                    memcpy(p_iphdr->destaddr.u8, p_iphc, IPV6_ADDR_SIZE);
                    p_iphc += IPV6_ADDR_SIZE;
                    break;

                case IPHC_DAM_01:
                    // 64 bits in-line, first IID then prefix in case prefix > 64.
                    memcpy(p_iphdr->destaddr.u8, m_link_local_prefix, 2);
                    memcpy(p_iphdr->destaddr.u8 + 8, p_iphc, 8);
                    p_iphc += 8;
                    break;

                case IPHC_DAM_10:
                    // 16 bits in-line.
                    memcpy(p_iphdr->destaddr.u8, m_link_local_prefix, 2);
                    memcpy(p_iphdr->destaddr.u8 + 11, m_link_local_16_middle, 2);
                    memcpy(p_iphdr->destaddr.u8 + 14, p_iphc, 2);
                    p_iphc += 2;
                    break;

                case IPHC_DAM_11:
                    // Take the address from lower layer.
                    memcpy(p_iphdr->destaddr.u8, m_link_local_prefix, 2);
                    memcpy(p_iphdr->destaddr.u8 + 8, p_interface->local_addr.identifier, 8);
                    p_iphdr->destaddr.u8[8] ^= IPV6_IID_FLIP_VALUE;
                    break;
            }
        }
    }

    // Perform next header compression.
    if (((p_input[0] & IPHC_NH_MASK) >> IPHC_NH_POS))
    {
        p_iphc += iphc_nhc_decode(p_iphc, p_output, &nhc_length);

        if (nhc_length == 0)
        {
            // Unknown NHC field.
            BLE_6LOWPAN_ERR("IPHC contains unsupported NHC header!");

            return NRF_ERROR_INVALID_DATA;
        }
    }

    // Calculate IPv6 Header Length.
    p_iphdr->length = input_len - (p_iphc - p_input);

    // Check if IPHC contains more bytes than whole packet.
    if (p_iphdr->length > input_len)
    {
        // We cannot decompress it.
        BLE_6LOWPAN_ERR("IPHC contains more bytes than expected!");

        return NRF_ERROR_INVALID_DATA;
    }

    // Copy the data.
    memcpy(p_output + IPV6_IP_HEADER_SIZE + nhc_length, p_iphc, p_iphdr->length);

    // Add uncompressed headers length if any.
    p_iphdr->length += nhc_length;

    // Return length of whole IPv6 packet.
    *p_output_len = p_iphdr->length + IPV6_IP_HEADER_SIZE;

    // Keep proper endianness.
    p_iphdr->length = HTONS(p_iphdr->length);

    // Restore UDP length if compression was used.
    if ( p_iphdr->next_header == IPV6_NEXT_HEADER_UDP )
    {
        memcpy(&p_udphdr->length, &p_iphdr->length, 2);
    }

    return retval;
}


/**@brief Function for encoding IPHC (IP Header Compression) defined in
 *        IETF RFC 6282. Instead of having separate buffer for compression,
 *        needed compression is performed on the IPv6 packet and buffer holding
 *        the packet is reused to overwrite the headers compressed.
 *
 * @param[in]   p_interface  IoT interface where packet must be sent.
 * @param[in]   p_input      Pointer to full IPv6 packet.
 * @param[in]   input_len    Length of IPv6 packet.
 * @param[out]  p_output     Pointer to place of start IPHC packet.
 * @param[out]  p_output_len Length of compressed packet.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t iphc_encode(const iot_interface_t  * p_interface,
                            uint8_t               ** p_output,
                            uint16_t               * p_output_len,
                            const uint8_t          * p_input,
                            uint16_t                 input_len)
{
    // Create a buffer with maximum of IPHC value.
    uint32_t                err_code;
    uint8_t                 iphc_buff[IPV6_IP_HEADER_SIZE + UDP_HEADER_SIZE];
    uint8_t                 traffic_class;
    uint8_t               * p_iphc         = &iphc_buff[2];
    uint16_t                iphc_len       = 0;
    uint16_t                nhc_length     = 0;
    iot_context_t         * p_ctx          = NULL;
    uint8_t                 sci            = p_interface->tx_contexts.src_cntxt_id;
    uint8_t                 dci            = p_interface->tx_contexts.dest_cntxt_id;
    bool                    sci_cover      = false;
    bool                    dci_cover      = false;

    // IPv6 header.
    ipv6_header_t * p_iphdr = (ipv6_header_t *)p_input;

    *p_iphc = 0;

    // Set IPHC dispatch.
    iphc_buff[0] = IPHC_START_DISPATCH << IPHC_START_DISPATCH_POS;

    // Check if address can be compressed using context identifier.
    if (sci == IPV6_CONTEXT_IDENTIFIER_NONE)
    {
        BLE_6LOWPAN_MUTEX_UNLOCK();
        err_code = iot_context_manager_get_by_addr(p_interface, &p_iphdr->srcaddr, &p_ctx);
        BLE_6LOWPAN_MUTEX_LOCK();

        if (err_code == NRF_SUCCESS)
        {
            sci_cover = is_context_cover_iid(&p_iphdr->srcaddr, p_ctx, &p_interface->local_addr);
            sci = p_ctx->context_id;
        }
    }

    if (dci == IPV6_CONTEXT_IDENTIFIER_NONE)
    {
        BLE_6LOWPAN_MUTEX_UNLOCK();
        err_code = iot_context_manager_get_by_addr(p_interface, &p_iphdr->destaddr, &p_ctx);
        BLE_6LOWPAN_MUTEX_LOCK();

        if (err_code == NRF_SUCCESS)
        {
            dci_cover = is_context_cover_iid(&p_iphdr->destaddr, p_ctx, &p_interface->peer_addr);
            dci = p_ctx->context_id;
        }
    }

    if (((sci != IPV6_CONTEXT_IDENTIFIER_NONE) || dci != IPV6_CONTEXT_IDENTIFIER_NONE))
    {
        iphc_buff[1] = (IPHC_CID_1 << IPHC_CID_POS);

        // Add Source Context if exists.
        if (sci != IPV6_CONTEXT_IDENTIFIER_NONE)
        {
            *p_iphc |= (sci << 4);
        }

        // Add Destination Context if exists.
        if (dci != IPV6_CONTEXT_IDENTIFIER_NONE)
        {
            *p_iphc |= dci;
        }

        p_iphc += 1;
    }
    else
    {
        // Unset Context Identifier bit.
        iphc_buff[1] = (IPHC_CID_0 << IPHC_CID_POS);
    }

    // Change ECN with DSCP in Traffic Class.
    traffic_class  = (p_iphdr->version_traffic_class & 0x0f) << 4;
    traffic_class |= ((p_iphdr->traffic_class_flowlabel & 0xf0) >> 4);
    traffic_class  = (((traffic_class & 0x03) << 6) | (traffic_class >> 2));

    if ((p_iphdr->flowlabel == 0) && ((p_iphdr->traffic_class_flowlabel & 0x0f) == 0))
    {
        if (traffic_class == 0)
        {
            // Elide Flow Label and Traffic Class.
            iphc_buff[0] |= (IPHC_TF_11 << IPHC_TF_POS);
        }
        else
        {
            // Elide Flow Label and carry Traffic Class in-line.
            iphc_buff[0] |= (IPHC_TF_10 << IPHC_TF_POS);

            *p_iphc++ = traffic_class;
        }
    }
    else
    {
        if (traffic_class & IPHC_TF_DSCP_MASK)
        {
            // Carry Flow Label and Traffic Class in-line.
            iphc_buff[0] |= (IPHC_TF_00 << IPHC_TF_POS);

            *p_iphc++ = traffic_class;
            *p_iphc++ = (p_iphdr->traffic_class_flowlabel & 0x0f);
            memcpy(p_iphc, &p_iphdr->flowlabel, 2);
            p_iphc += 2;
        }
        else
        {
            // Carry Flow Label and ECN only with 2-bit padding.
            iphc_buff[0] |= (IPHC_TF_01 << IPHC_TF_POS);

            *p_iphc++ =
                ((traffic_class & IPHC_TF_ECN_MASK) | (p_iphdr->traffic_class_flowlabel & 0x0f));
            memcpy(p_iphc, &p_iphdr->flowlabel, 2);
            p_iphc += 2;
        }
    }

    // Checks if next header is compressed.
    if (iphc_nhc_compressable(p_iphdr->next_header))
    {
        iphc_buff[0] |= (IPHC_NH_1 << IPHC_NH_POS);
    }
    else
    {
        iphc_buff[0] |= (IPHC_NH_0 << IPHC_NH_POS);
        *p_iphc++     = p_iphdr->next_header;
    }

    // Hop limit compression.
    switch (p_iphdr->hoplimit)
    {
        case 1:
            iphc_buff[0] |= (IPHC_HLIM_01 << IPHC_HLIM_POS);
            break;

        case 64:
            iphc_buff[0] |= (IPHC_HLIM_10 << IPHC_HLIM_POS);
            break;

        case 255:
            iphc_buff[0] |= (IPHC_HLIM_11 << IPHC_HLIM_POS);
            break;

        default:
            // Carry Hop Limit in-line.
            iphc_buff[0] |= (IPHC_HLIM_00 << IPHC_HLIM_POS);
            *p_iphc++     = p_iphdr->hoplimit;
            break;
    }

    // Source address compression.
    if (IPV6_ADDRESS_IS_UNSPECIFIED(&p_iphdr->srcaddr))
    {
        iphc_buff[1] |= (IPHC_SAC_1  << IPHC_SAC_POS);
        iphc_buff[1] |= (IPHC_SAM_00 << IPHC_SAM_POS);
    }
    else if (sci != IPV6_CONTEXT_IDENTIFIER_NONE || IPV6_ADDRESS_IS_LINK_LOCAL(&p_iphdr->srcaddr))
    {
        if (sci != IPV6_CONTEXT_IDENTIFIER_NONE)
        {
            // Set stateful source address compression.
            iphc_buff[1] |= (IPHC_SAC_1 << IPHC_SAC_POS);
        }

        if (IPV6_ADDRESS_IS_FULLY_ELIDABLE(p_interface->local_addr.identifier,
                                           &p_iphdr->srcaddr)
                                           ||
                                           sci_cover == true)
        {
            iphc_buff[1] |= (IPHC_SAM_11 << IPHC_SAM_POS);
        }
        else if (IPV6_ADDRESS_IS_16_BIT_COMPRESSABLE(&p_iphdr->srcaddr))
        {
            iphc_buff[1] |= (IPHC_SAM_10 << IPHC_SAM_POS);
            memcpy(p_iphc, &p_iphdr->srcaddr.u8[14], 2);
            p_iphc += 2;
        }
        else
        {
            iphc_buff[1] |= (IPHC_SAM_01 << IPHC_SAM_POS);
            memcpy(p_iphc, &p_iphdr->srcaddr.u8[8], 8);
            p_iphc += 8;
        }
    }
    else
    {
        // Carry full source address in-line.
        iphc_buff[1] |= (IPHC_SAC_0  << IPHC_SAC_POS);
        iphc_buff[1] |= (IPHC_SAM_00 << IPHC_SAM_POS);
        memcpy(p_iphc, p_iphdr->srcaddr.u8, IPV6_ADDR_SIZE);
        p_iphc += IPV6_ADDR_SIZE;
    }

    // Destination compression.
    if (IPV6_ADDRESS_IS_MULTICAST(&p_iphdr->destaddr))
    {
        iphc_buff[1] |= (IPHC_M_1 << IPHC_M_POS);

        if (dci != IPV6_CONTEXT_IDENTIFIER_NONE)
        {
            iphc_buff[1] |= (IPHC_DAC_1 << IPHC_DAC_POS);
            iphc_buff[1] |= (IPHC_DAM_00 << IPHC_DAM_POS);

            p_iphdr->destaddr.u8[0] = 0xff;
            memcpy(p_iphc, &p_iphdr->destaddr.u8[1], 2);
            memcpy(p_iphc + 2, &p_iphdr->destaddr.u8[12], 4);
            p_iphc += 6;
        }
        else if (IPV6_ADDRESS_IS_8_BIT_MCAST_COMPRESSABLE(&p_iphdr->destaddr))
        {
            iphc_buff[1] |= (IPHC_DAC_0 << IPHC_DAC_POS);
            iphc_buff[1] |= (IPHC_DAM_11 << IPHC_DAM_POS);
            *p_iphc++     = p_iphdr->destaddr.u8[15];

        }
        else if (IPV6_ADDRESS_IS_32_BIT_MCAST_COMPRESSABLE(&p_iphdr->destaddr))
        {
            iphc_buff[1] |= (IPHC_DAC_0 << IPHC_DAC_POS);
            iphc_buff[1] |= (IPHC_DAM_10 << IPHC_DAM_POS);

            *p_iphc = p_iphdr->destaddr.u8[1];
            memcpy(p_iphc + 1, &p_iphdr->destaddr.u8[13], 3);
            p_iphc += 4;
        }
        else if (IPV6_ADDRESS_IS_48_BIT_MCAST_COMPRESSABLE(&p_iphdr->destaddr))
        {
            iphc_buff[1] |= (IPHC_DAC_0 << IPHC_DAC_POS);
            iphc_buff[1] |= (IPHC_DAM_01 << IPHC_DAM_POS);

            *p_iphc = p_iphdr->destaddr.u8[1];
            memcpy(p_iphc + 1, &p_iphdr->destaddr.u8[11], 5);
            p_iphc += 6;
        }
        else
        {
            // Carry full destination multi-cast address in-line.
            iphc_buff[1] |= (IPHC_DAC_0 << IPHC_DAC_POS);
            iphc_buff[1] |= (IPHC_DAM_00 << IPHC_DAM_POS);
            memcpy(p_iphc, p_iphdr->destaddr.u8, IPV6_ADDR_SIZE);
            p_iphc += IPV6_ADDR_SIZE;
        }
    }
    else
    {
        iphc_buff[1] |= (IPHC_M_0 << IPHC_M_POS);

        if (dci != IPV6_CONTEXT_IDENTIFIER_NONE || IPV6_ADDRESS_IS_LINK_LOCAL(&p_iphdr->destaddr))
        {
            if (dci != IPV6_CONTEXT_IDENTIFIER_NONE)
            {
                iphc_buff[1] |= (IPHC_DAC_1 << IPHC_DAC_POS);
            }

            if (IPV6_ADDRESS_IS_FULLY_ELIDABLE(p_interface->peer_addr.identifier,
                                               &p_iphdr->destaddr)
                                               ||
                                               dci_cover == true)
            {
                iphc_buff[1] |= (IPHC_DAM_11 << IPHC_DAM_POS);
            }
            else if (IPV6_ADDRESS_IS_16_BIT_COMPRESSABLE(&p_iphdr->destaddr))
            {
                iphc_buff[1] |= (IPHC_DAM_10 << IPHC_DAM_POS);
                memcpy(p_iphc, &p_iphdr->destaddr.u8[14], 2);
                p_iphc += 2;
            }
            else
            {
                iphc_buff[1] |= (IPHC_DAM_01 << IPHC_DAM_POS);
                memcpy(p_iphc, &p_iphdr->destaddr.u8[8], 8);
                p_iphc += 8;
            }
        }
        else
        {
            // Carry full destination address in-line.
            iphc_buff[1] |= (IPHC_DAC_0  << IPHC_DAC_POS);
            iphc_buff[1] |= (IPHC_DAM_00 << IPHC_DAM_POS);
            memcpy(p_iphc, p_iphdr->destaddr.u8, IPV6_ADDR_SIZE);
            p_iphc += IPV6_ADDR_SIZE;
        }
    }

    if ( iphc_buff[0] & IPHC_NH_MASK)
    {
        p_iphc += iphc_nhc_encode(p_iphc, p_input, &nhc_length);
    }

    // Calculate IPHC size.
    iphc_len = (p_iphc - iphc_buff);

    // Calculate IPv6 packet size.
    *p_output_len = input_len - (IPV6_IP_HEADER_SIZE - iphc_len + nhc_length);

    // Use p_data as final buffer (since IPHC+NHC <= IPv6 Header + NHC (UDP)).
    memcpy((uint8_t *)&p_input[IPV6_IP_HEADER_SIZE + nhc_length - iphc_len], iphc_buff, iphc_len);

    // Set correct address of output data.
    *p_output = (uint8_t *) &p_input[IPV6_IP_HEADER_SIZE + nhc_length - iphc_len];

    return NRF_SUCCESS;
}


/******************************************************************************
 * @name 6LoWPAN transport functions
 *****************************************************************************/

/**@brief Function for notifying application of an error in an ongoing procedure.
 *
 * @param[in]   p_interface  Pointer to 6LoWPAN interface.
 * @param[in]   err_code     Internally error code.
 *
 * @return      None.
 */
static void app_notify_error(iot_interface_t * p_interface,
                             uint32_t          err_code)
{
    ble_6lowpan_event_t event;

    event.event_id     = BLE_6LO_EVT_ERROR;
    event.event_result = err_code;

    BLE_6LOWPAN_MUTEX_UNLOCK();

    m_event_handler(p_interface, &event);

    BLE_6LOWPAN_MUTEX_LOCK();
}


/**@brief Function for notifying application of the new packet received.
 *
 * @param[in]   p_interface   Pointer to iot interface.
 * @param[in]   p_packet      Pointer to decompressed IPv6 packet.
 * @param[in]   packet_len    Length of IPv6 packet.
 * @param[in]   result        Processing result of packet. Could be NRF_SUCCESS, or
 *                            NRF_ERROR_NOT_FOUND if context identifier is unknown.
 * @param[in]  p_rx_contexts  Received contexts if any.
 *
 * @return      None.
 */
static void app_notify_rx_data(iot_interface_t  * p_interface,
                               uint8_t          * p_packet,
                               uint16_t           packet_len,
                               uint32_t           result,
                               iot_context_id_t * p_rx_contexts)
{
    ble_6lowpan_event_t event;

    event.event_id                               = BLE_6LO_EVT_INTERFACE_DATA_RX;
    event.event_result                           = result;
    event.event_param.rx_event_param.p_packet    = p_packet;
    event.event_param.rx_event_param.packet_len  = packet_len;
    event.event_param.rx_event_param.rx_contexts = *(p_rx_contexts);

    BLE_6LOWPAN_MUTEX_UNLOCK();

    m_event_handler(p_interface, &event);

    BLE_6LOWPAN_MUTEX_LOCK();
}


/**@brief Function for notifying application of the new interface established.
 *
 * @param[in]   p_interface  Pointer to new iot interface.
 *
 * @return      None.
 */
static void app_notify_interface_add(iot_interface_t * p_interface)
{
    ble_6lowpan_event_t event;

    event.event_id     = BLE_6LO_EVT_INTERFACE_ADD;
    event.event_result = NRF_SUCCESS;

    BLE_6LOWPAN_MUTEX_UNLOCK();

    m_event_handler(p_interface, &event);

    BLE_6LOWPAN_MUTEX_LOCK();
}


/**@brief Function for notifying application of the interface disconnection.
 *
 * @param[in]   p_interface  Pointer to removed iot interface.
 *
 * @return      None.
 */
static void app_notify_interface_delete(iot_interface_t * p_interface)
{
    ble_6lowpan_event_t event;

    event.event_id     = BLE_6LO_EVT_INTERFACE_DELETE;
    event.event_result = NRF_SUCCESS;

    BLE_6LOWPAN_MUTEX_UNLOCK();

    m_event_handler(p_interface, &event);

    BLE_6LOWPAN_MUTEX_LOCK();
}


/**@brief Function for initialize transmit FIFO.
 *
 * @param[in]   p_fifo  Pointer to transmit FIFO instance.
 *
 * @return      None.
 */
static void tx_fifo_init(tx_fifo_t * p_fifo)
{
    memset(p_fifo->packets, 0, BLE_6LOWPAN_TX_FIFO_SIZE * sizeof (tx_packet_t));
    p_fifo->read_pos  = 0;
    p_fifo->write_pos = 0;
}


/**@brief Function for putting new packet to transmit FIFO.
 *
 * @param[in]   p_fifo   Pointer to transmit FIFO instance.
 * @param[in]   p_packet Pointer to new packet.
 *
 * @return      NRF_SUCCESS on success, otherwise NRF_ERROR_NO_MEM error.
 */
static uint32_t tx_fifo_put(tx_fifo_t * p_fifo, tx_packet_t * p_packet)
{
    uint32_t err_code = BLE_6LOWPAN_TX_FIFO_FULL;

    // To prevent "The order of volatile accesses is undefined in this statement"
    // in subsequent conditional statement.
    uint32_t write_pos = p_fifo->write_pos;
    uint32_t read_pos  = p_fifo->read_pos;

    if ((write_pos - read_pos) <= TX_FIFO_MASK)
    {
        p_fifo->packets[p_fifo->write_pos & TX_FIFO_MASK].p_data      = p_packet->p_data;
        p_fifo->packets[p_fifo->write_pos & TX_FIFO_MASK].data_len    = p_packet->data_len;
        p_fifo->packets[p_fifo->write_pos & TX_FIFO_MASK].p_mem_block = p_packet->p_mem_block;

        p_fifo->write_pos++;

        err_code = NRF_SUCCESS;
    }

    return err_code;
}


/**@brief Function for popping currently processed packet in transmit FIFO.
 *        It releases element on FIFO only when processing of the element is done.
 *
 * @param[in]   p_fifo   Pointer to transmit FIFO instance.
 *
 * @return      None.
 */
static void tx_fifo_release(tx_fifo_t * p_fifo)
{
    p_fifo->read_pos++;
}


/**@brief Function for reading front element of transmit FIFO.
 *        After finish processing element in queue, it must be
 *        released using tx_fifo_release function.
 *
 * @param[in]   p_fifo    Pointer to transmit FIFO instance.
 * @param[in]   pp_packet Pointer to front packet.
 *
 * @return      NRF_SUCCESS on success, otherwise NRF_ERROR_NO_MEM error.
 */
static uint32_t tx_fifo_get(tx_fifo_t * p_fifo, tx_packet_t * * pp_packet)
{
    uint32_t err_code = NRF_ERROR_NOT_FOUND;

    // To prevent "The order of volatile accesses is undefined in this statement"
    // in subsequent conditional statement.
    uint32_t write_pos = p_fifo->write_pos;
    uint32_t read_pos  = p_fifo->read_pos;

    if ((write_pos - read_pos) != 0)
    {
        *pp_packet = &p_fifo->packets[p_fifo->read_pos & TX_FIFO_MASK];
        err_code   = NRF_SUCCESS;
    }

    return err_code;
}


/**@brief Function for searching transport interface by given IPSP handle.
 *
 * @param[in]   p_ipsp_handle Pointer to IPSP handle.
 *
 * @return      Transport interface related with IPSP handle, or NULL if not found.
 */
static transport_instance_t * interface_get_by_handle(const ble_ipsp_handle_t * p_ipsp_handle)
{
    uint32_t index;

    for (index = 0; index < BLE_6LOWPAN_MAX_INTERFACE; index++)
    {
        if (m_instances[index].handle.cid         == p_ipsp_handle->cid &&
            m_instances[index].handle.conn_handle == p_ipsp_handle->conn_handle)
        {
            return &m_instances[index];
        }
    }

    return NULL;
}


/**@brief Function for initializing transport instance.
 *
 * @param[in]   index  Index of instance.
 *
 * @return      None.
 */
static void instance_init(uint32_t index)
{
    memset(&m_instances[index], 0, sizeof (transport_instance_t));
    m_instances[index].handle.cid            = BLE_L2CAP_CID_INVALID;
    m_instances[index].p_tx_cur_packet       = NULL;
    m_instances[index].interface.p_transport = (void *) index;
}


/**@brief Function for resetting specific 6lowpan interface.
 *
 * @param[in]   p_interface  Pointer to transport interface.
 *
 * @return      None.
 */
static void interface_reset(transport_instance_t * p_instance)
{
    uint32_t index;
    uint32_t instance_id = (uint32_t) p_instance->interface.p_transport;

    // Free all queued packets.
    for (index = 0; index < BLE_6LOWPAN_TX_FIFO_SIZE; index++)
    {
        if (m_instances[instance_id].tx_fifo.packets[index].p_mem_block != NULL)
        {
            nrf_free(m_instances[instance_id].tx_fifo.packets[index].p_mem_block);
        }
    }

    instance_init (instance_id);
}


/**@brief Function for adding new transport instance.
 *
 * @param[in]   p_peer_addr   Pointer EUI-64 of peer address.
 * @param[in]   p_ipsp_handle Pointer IPSP handle, related with L2CAP CoC channel.
 * @param[out]  pp_instance   Pointer to added transport instances, if operation succeeded.
 *
 * @return      NRF_SUCCESS on success, otherwise NRF_ERROR_NO_MEM error.
 */
static uint32_t interface_add(const eui64_t             * p_peer_addr,
                              const ble_ipsp_handle_t   * p_ipsp_handle,
                              transport_instance_t     ** pp_instance)
{
    uint32_t index;

    for (index = 0; index < BLE_6LOWPAN_MAX_INTERFACE; index++)
    {
        if (m_instances[index].handle.cid == BLE_L2CAP_CID_INVALID)
        {
            m_instances[index].handle.cid                          = p_ipsp_handle->cid;
            m_instances[index].handle.conn_handle                  = p_ipsp_handle->conn_handle;
            m_instances[index].interface.tx_contexts.src_cntxt_id  = IPV6_CONTEXT_IDENTIFIER_NONE;
            m_instances[index].interface.tx_contexts.dest_cntxt_id = IPV6_CONTEXT_IDENTIFIER_NONE;

            memcpy(&m_instances[index].interface.peer_addr, p_peer_addr, sizeof (eui64_t));
            memcpy(&m_instances[index].interface.local_addr, &m_ll_addr, sizeof (eui64_t));

            // Initialize TX FIFO.
            tx_fifo_init(&m_instances[index].tx_fifo);

            *pp_instance = &m_instances[index];

            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NO_MEM;
}


/**@brief Function for checking if any transmission is currently processing on specific interface.
 *        Current version of L2CAP CoC in SoftDevice has limitation to send one packet at same
 *        time.
 *
 * @param[in]   p_instance  Pointer to transport instance.
 *
 * @return      TRUE if interface not sending any packets, FALSE if busy.
 */
static bool tx_is_free(transport_instance_t * p_instance)
{
    return (NULL == p_instance->p_tx_cur_packet);
}


/**@brief Function uses for indicating transmission complete on specific interface.
 *
 * @param[in]   p_instance  Pointer to transport instance.
 *
 * @return      None.
 */
static void tx_complete(transport_instance_t * p_instance)
{
    BLE_6LOWPAN_TRC("[CID 0x%04X]: Transmission complete.",
                    p_instance->handle.cid);

    // Free the transmit buffer.
    nrf_free(p_instance->p_tx_cur_packet->p_mem_block);
    p_instance->p_tx_cur_packet = NULL;

    // Release last processed packet.
    tx_fifo_release(&p_instance->tx_fifo);
}


/**@brief Function for sending front packet from transmit FIFO on specific interface.
 *
 * @param[in]   p_instance  Pointer to transport instance.
 *
 * @return      None.
 */
static void tx_send(transport_instance_t * p_instance)
{
    uint32_t err_code = NRF_SUCCESS;

    if (NRF_SUCCESS == tx_fifo_get(&p_instance->tx_fifo,
                                   &p_instance->p_tx_cur_packet))
    {
        err_code = ble_ipsp_send(&p_instance->handle,
                                 p_instance->p_tx_cur_packet->p_data,
                                 p_instance->p_tx_cur_packet->data_len);

        if (NRF_SUCCESS != err_code)
        {
            BLE_6LOWPAN_TRC("Cannot send the packet, error = 0x%08lX", err_code);

            app_notify_error(&p_instance->interface, err_code);

            tx_complete(p_instance);

            // Try to send another packet.
            tx_send(p_instance);
        }
    }
}

/**@brief Callback registered with IPSP to receive asynchronous events from the module.
 *
 * @param[in]   p_handle  Pointer to IPSP handle.
 * @param[in]   p_evt     Pointer to specific event, generated by IPSP module.
 *
 * @return      NRF_SUCCESS on success, otherwise NRF_ERROR_NO_MEM error.
 */
static uint32_t ipsp_evt_handler(ble_ipsp_handle_t const * p_handle, ble_ipsp_evt_t const * p_evt)
{
    BLE_6LOWPAN_ENTRY();

    VERIFY_MODULE_IS_INITIALIZED();

    uint32_t               mem_size;
    uint16_t               buff_len;
    eui64_t                peer_addr;
    iot_context_id_t       rx_contexts;
    uint32_t               retval       = NRF_SUCCESS;
    transport_instance_t * p_instance   = NULL;
    uint8_t              * p_buff       = NULL;

    BLE_6LOWPAN_MUTEX_LOCK();

    p_instance = interface_get_by_handle(p_handle);

    switch (p_evt->evt_id)
    {
        case BLE_IPSP_EVT_CHANNEL_CONNECTED:
        {
            BLE_6LOWPAN_TRC("[CID 0x%04X]: >> BLE_IPSP_EVT_CHANNEL_CONNECTED",
                            p_handle->cid);
            BLE_6LOWPAN_TRC("New channel established.");

            if (p_instance == NULL)
            {
                IPV6_EUI64_CREATE_FROM_EUI48(peer_addr.identifier,
                                        p_evt->p_evt_param->p_peer->addr,
                                        p_evt->p_evt_param->p_peer->addr_type);

                // Add interface to internal table.
                retval = interface_add(&peer_addr, p_handle, &p_instance);

                if (NRF_SUCCESS == retval)
                {
                    BLE_6LOWPAN_TRC("Added new IPSP interface.");

                    // Notify application.
                    app_notify_interface_add(&p_instance->interface);
                }
                else
                {
                    BLE_6LOWPAN_ERR("Cannot add new interface. Table is full.");
                    UNUSED_VARIABLE(ble_ipsp_disconnect(p_handle));
                }
            }
            else
            {
                // Got a connection event, when already connected.
                UNUSED_VARIABLE(ble_ipsp_disconnect(p_handle));
            }

            break;
        }

        case BLE_IPSP_EVT_CHANNEL_DISCONNECTED:
        {
            BLE_6LOWPAN_TRC("[CID 0x%04X]: >> BLE_IPSP_EVT_CHANNEL_DISCONNECTED",
                            p_handle->cid);
            BLE_6LOWPAN_TRC("Channel disconnection.");

            if (NULL != p_instance)
            {
                BLE_6LOWPAN_TRC("Removed IPSP interface.");

                // Notify application.
                app_notify_interface_delete(&p_instance->interface);

                // Remove interface from internal table.
                interface_reset(p_instance);
            }

            break;
        }

        case BLE_IPSP_EVT_CHANNEL_DATA_RX:
        {

            if (NULL != p_instance)
            {
                const uint16_t packet_len = MIN(p_evt->p_evt_param->p_l2cap_evt->params.rx.sdu_buf.len,
                                                p_evt->p_evt_param->p_l2cap_evt->params.rx.sdu_len);

                BLE_6LOWPAN_TRC("[CID 0x%04X]: >> BLE_IPSP_EVT_CHANNEL_DATA_RX",
                                p_handle->cid);

                BLE_6LOWPAN_DUMP(p_evt->p_evt_param->p_l2cap_evt->params.rx.sdu_buf.p_data,
                                 packet_len);

                BLE_6LOWPAN_TRC("Processing received data.");

                mem_size = packet_len + IPHC_MAX_COMPRESSED_DIFF;

                // Try to allocate memory for incoming data.
                retval = nrf_mem_reserve(&p_buff, &mem_size);

                if (retval == NRF_SUCCESS)
                {
                    // Decompress IPHC data into IPv6 packet.
                    retval = iphc_decode(&p_instance->interface,
                                         p_buff,
                                         &buff_len,
                                         p_evt->p_evt_param->p_l2cap_evt->params.rx.sdu_buf.p_data,
                                         packet_len,
                                         &rx_contexts);

                    // Do not discard if packet decompressed successfully,
                    // otherwise error in Context based decompression.
                    if (retval == NRF_SUCCESS || retval == BLE_6LOWPAN_CID_NOT_FOUND)
                    {
                        if ((p_evt->evt_result == NRF_ERROR_BLE_IPSP_RX_PKT_TRUNCATED) &&
                            (retval == NRF_SUCCESS))
                        {
                            // Inform the application that the packet is truncated.
                            retval = NRF_ERROR_BLE_IPSP_RX_PKT_TRUNCATED;
                        }

                        BLE_6LOWPAN_TRC("Decompressed packet:");
                        BLE_6LOWPAN_DUMP(p_buff, buff_len);

                        // Notify application.
                        app_notify_rx_data(&p_instance->interface,
                                           p_buff,
                                           buff_len,
                                           retval,
                                           &rx_contexts);
                    }
                    else
                    {
                        BLE_6LOWPAN_ERR("Decompression failed!");

                        nrf_free(p_buff);
                    }
                }
                else
                {
                    BLE_6LOWPAN_ERR(
                        "No buffer in memory pool available, packet dropped!");
                }
            }
            else
            {
                BLE_6LOWPAN_ERR("Got data to unknown interface!");
            }

            break;
        }

        case BLE_IPSP_EVT_CHANNEL_DATA_TX_COMPLETE:
        {
            BLE_6LOWPAN_TRC("[CID 0x%04X]: >> BLE_IPSP_EVT_CHANNEL_DATA_TX_COMPLETE",
                            p_handle->cid);

            // Free TX buffer.
            tx_complete(p_instance);

            // Try to send another packet.
            tx_send(p_instance);

            break;
        }

        default:
            break;
    }

    BLE_6LOWPAN_MUTEX_UNLOCK();

    BLE_6LOWPAN_EXIT();

    return retval;
}

/******************************************************************************
 * @name 6LoWPAN API functions
 *****************************************************************************/

uint32_t ble_6lowpan_init(const ble_6lowpan_init_t * p_init)
{
    BLE_6LOWPAN_ENTRY();

    uint32_t        index;
    uint32_t        retval = NRF_SUCCESS;
    ble_ipsp_init_t ipsp_init_params;

    NULL_PARAM_CHECK(p_init);
    NULL_PARAM_CHECK(p_init->p_eui64);
    NULL_PARAM_CHECK(p_init->event_handler);

    // Check if the transmit FIFO size is a power of two.
    if (!IS_POWER_OF_TWO(BLE_6LOWPAN_TX_FIFO_SIZE))
    {
        return NRF_ERROR_INVALID_LENGTH | BLE_6LOWPAN_ERR_BASE;
    }

    SDK_MUTEX_INIT(m_6lowpan_mutex);

    BLE_6LOWPAN_MUTEX_LOCK();

    // Store EUI64 in internal variable.
    memcpy(m_ll_addr.identifier, p_init->p_eui64->identifier, EUI_64_ADDR_SIZE);

    // Set application event handler.
    m_event_handler = p_init->event_handler;

    // Clear transport interfaces table.
    for (index = 0; index < BLE_6LOWPAN_MAX_INTERFACE; index++)
    {
        instance_init(index);
    }

    // IPSP module initialization.
    ipsp_init_params.evt_handler = ipsp_evt_handler;

    // Initialize the IPSP module.
    retval = ble_ipsp_init(&ipsp_init_params);

    BLE_6LOWPAN_MUTEX_UNLOCK();

    BLE_6LOWPAN_EXIT();

    return retval;
}


uint32_t  ble_6lowpan_interface_disconnect(const iot_interface_t * p_interface)
{
    BLE_6LOWPAN_ENTRY();

    VERIFY_MODULE_IS_INITIALIZED();

    NULL_PARAM_CHECK(p_interface);

    uint32_t               retval;
    transport_instance_t * p_instance = &m_instances[(uint32_t)p_interface->p_transport];

    BLE_6LOWPAN_MUTEX_LOCK();

    retval = ble_ipsp_disconnect(&p_instance->handle);

    BLE_6LOWPAN_MUTEX_UNLOCK();

    BLE_6LOWPAN_EXIT();

    return retval;
}


uint32_t ble_6lowpan_interface_send(const iot_interface_t * p_interface,
                                    const uint8_t         * p_packet,
                                    uint16_t                packet_len)
{
    BLE_6LOWPAN_ENTRY();

    VERIFY_MODULE_IS_INITIALIZED();

    NULL_PARAM_CHECK(p_packet);
    NULL_PARAM_CHECK(p_interface);
    PACKET_LENGTH_CHECK(packet_len);

    uint32_t               retval        = NRF_SUCCESS;
    uint8_t              * p_output_buff = NULL;
    uint16_t               output_len;
    tx_packet_t            tx_packet;
    transport_instance_t * p_instance = &m_instances[(uint32_t)p_interface->p_transport];

    BLE_6LOWPAN_MUTEX_LOCK();

    BLE_6LOWPAN_TRC("Uncompressed packet:");
    BLE_6LOWPAN_DUMP((uint8_t *)p_packet, packet_len);

    // Encode IP packet into IPHC.
    retval = iphc_encode(p_interface,
                         &p_output_buff,
                         &output_len,
                         p_packet,
                         packet_len);

    if (NRF_SUCCESS == retval)
    {
        BLE_6LOWPAN_TRC("Successfully compressed packet.");

        tx_packet.p_data      = p_output_buff;
        tx_packet.data_len    = output_len;
        tx_packet.p_mem_block = (uint8_t *)p_packet;

        retval = tx_fifo_put(&p_instance->tx_fifo, &tx_packet);

        if (NRF_SUCCESS == retval)
        {
            BLE_6LOWPAN_TRC("Compressed packet:");
            BLE_6LOWPAN_DUMP(p_output_buff, output_len);

            // Send packet immediately if transport interface is not busy.
            if (tx_is_free(p_instance))
            {
                tx_send(p_instance);
            }
        }
        else
        {
            BLE_6LOWPAN_ERR("No place in TX queue!");
        }
    }
    else
    {
        BLE_6LOWPAN_ERR("Error while compression!");
    }

    BLE_6LOWPAN_MUTEX_UNLOCK();

    BLE_6LOWPAN_EXIT();

    return retval;
}
