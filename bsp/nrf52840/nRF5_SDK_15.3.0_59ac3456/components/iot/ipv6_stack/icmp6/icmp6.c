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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "icmp6_api.h"
#include "ipv6_api.h"
#include "icmp6.h"
#include "iot_context_manager.h"
#include "ipv6_utils.h"
#include "iot_common.h"

#if ICMP6_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME icmp6

#define NRF_LOG_LEVEL       ICMP6_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ICMP6_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR ICMP6_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define ICMP6_TRC     NRF_LOG_DEBUG                                                                 /**< Used for getting trace of execution in the module. */
#define ICMP6_ERR     NRF_LOG_ERROR                                                                 /**< Used for logging errors in the module. */
#define ICMP6_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                         /**< Used for dumping octet information to get details of bond information etc. */

#define ICMP6_ENTRY() ICMP6_TRC(">> %s", __func__)
#define ICMP6_EXIT()  ICMP6_TRC("<< %s", __func__)

#else // ICMP6_CONFIG_LOG_ENABLED

#define ICMP6_TRC(...)                                                                              /**< Disables traces. */
#define ICMP6_DUMP(...)                                                                             /**< Disables dumping of octet streams. */
#define ICMP6_ERR(...)                                                                              /**< Disables error logs. */

#define ICMP6_ENTRY(...)
#define ICMP6_EXIT(...)

#endif // ICMP6_CONFIG_LOG_ENABLED

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          ICMP6_DISABLE_API_PARAM_CHECK should be set to 1 to disable these checks.
 *
 * @{
 */
#if (ICMP6_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_ICMP6_ERR_BASE);                          \
        }

/**@brief Macro to check is module is initialized before requesting one of the module
         procedures but does not use any return code. */
#define VERIFY_MODULE_IS_INITIALIZED_VOID()                                                        \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return;                                                                                \
        }

/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_ICMP6_ERR_BASE);                                          \
        }

/**
 * @brief Verify packet buffer is of ICMP6 Type.
 */
#define PACKET_TYPE_CHECK(PACKET)                                                                  \
        if ((PACKET)->type != ICMP6_PACKET_TYPE)                                                   \
        {                                                                                          \
            return (NRF_ERROR_INVALID_PARAM | IOT_ICMP6_ERR_BASE);                                 \
        }


#else // ICMP6_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define VERIFY_MODULE_IS_INITIALIZED_VOID()
#define NULL_PARAM_CHECK(PARAM)
#define PACKET_TYPE_CHECK(PACKET)

#endif // ICMP6_DISABLE_API_PARAM_CHECK
/** @} */

/**
 * @defgroup icmp6_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define ICMP6_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_icmp6_mutex)                                          /**< Lock module using mutex */
#define ICMP6_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_icmp6_mutex)                                        /**< Unlock module using mutex */
/** @} */

#define ND_NS_HEADER_SIZE              20                                                           /**< Size of Neighbour Solicitation message. */
#define ND_NA_HEADER_SIZE              20                                                           /**< Size of Neighbour Advertisement message. */
#define ND_RS_HEADER_SIZE              4                                                            /**< Size of Router Solicitation message. */
#define ND_RA_HEADER_SIZE              12                                                           /**< Size of Router Advertisement message. */
#define ND_PAYLOAD_ADJUST_OFFSET       4                                                            /**< Adjusting ND related payload offset as the general ICMP structure is not upheld. */

#define ND_NA_R_FLAG                   0x80                                                         /**< Router flag. When set, the R-bit indicates that the sender is a router. */
#define ND_NA_S_FLAG                   0x40                                                         /**< Solicited flag. When set, the S-bit indicates that the advertisement was sent in response
                                                                                                         to a Neighbor Solicitation .*/
#define ND_NA_O_FLAG                   0x20                                                         /**< Override flag. When set, the O-bit indicates that the advertisement should override
                                                                                                         an existing cache entry and update the cached link-layer address .*/

#define ND_OPT_TYPE_SLLAO              1                                                            /**< Source Link Layer Address Option. */
#define ND_OPT_TYPE_TLLAO              2                                                            /**< Target Link Layer Address Option. */
#define ND_OPT_TYPE_PIO                3                                                            /**< Prefix Information Option. */
#define ND_OPT_TYPE_RHO                4                                                            /**< Redirected Header Option. */
#define ND_OPT_TYPE_MTU                5                                                            /**< Maximum Transmit Unit Option. */
#define ND_OPT_TYPE_ARO                33                                                           /**< Address Registration Option. */
#define ND_OPT_TYPE_6CO                34                                                           /**< 6LoWPAN Context Option. */
#define ND_OPT_TYPE_6ABRO              35                                                           /**< Authoritative Border Router Option. */

#define ND_OPT_SLLAO_SIZE              (8 * (((IPV6_LL_ADDR_SIZE) / 8) + 1))                        /**< Size of SLLAO option. */
#define ND_OPT_TLLAO_SIZE              (8 * (((IPV6_LL_ADDR_SIZE) / 8) + 1))                        /**< Size of TLLAO option. */
#define ND_OPT_PIO_SIZE                32                                                           /**< Size of PIO option. */
#define ND_OPT_MTU_SIZE                8                                                            /**< Size of MTU option. */
#define ND_OPT_ARO_SIZE                16                                                           /**< Size of ARO option. */
#define ND_OPT_6CO_SIZE                24                                                           /**< Size of 6CO option. */
#define ND_OPT_6ABRO_SIZE              24                                                           /**< Size of 6ABRO option. */

#define ND_OPT_SLLAO_LENGTH            ((ND_OPT_SLLAO_SIZE) / 8)                                    /**< Value of length field in SLLAO option. */
#define ND_OPT_TLLAO_LENGTH            ((ND_OPT_TLLAO_SIZE) / 8)                                    /**< Value of length field in SLLAO option. */
#define ND_OPT_ARO_LENGTH              2                                                            /**< Value of length field in ARO option. */

#define ND_OPT_6CO_CID_MASK            0x0F
#define ND_OPT_6CO_CID_POS             0
#define ND_OPT_6CO_C_MASK              0x10
#define ND_OPT_6CO_C_POS               4

#define ND_OPT_PIO_L_MASK              0x80
#define ND_OPT_PIO_L_POS               7
#define ND_OPT_PIO_A_MASK              0x40
#define ND_OPT_PIO_A_POS               6

#define ND_HOP_LIMIT                   255                                                          /**< Value of Hop Limit used in Neighbour Discovery procedure. */

#define ICMP6_OFFSET                   IPV6_IP_HEADER_SIZE + ICMP6_HEADER_SIZE                      /**< Offset of ICMPv6 packet type. */

#define ERROR_ADDITIONAL_HEADER_SIZE   4                                                            /**< Additional 4 bytes of information every ICMP error message contains. */
#define ERROR_MESSAGE_HEADER_SIZE      (ICMP6_HEADER_SIZE + ERROR_ADDITIONAL_HEADER_SIZE)           /**< Error message header size including type, code, checksum and 32-bit parameter. */
#define ICMP6_ERROR_OFFSET             IPV6_IP_HEADER_SIZE + ERROR_MESSAGE_HEADER_SIZE              /**< Offset for ICMPv6 error message. */

/**@brief Neighbor Solicitation header. */
typedef struct
{
    uint32_t    reserved;                                                                           /**< Reserved field. */
    ipv6_addr_t target_addr;                                                                        /**< Target Address field. */
} icmp6_ns_header_t;

/**@brief Neighbor Advertisement header. */
typedef struct
{
    uint8_t     flags;                                                                              /**< Flags (R,S and O). */
    uint8_t     reserved;                                                                           /**< Reserved field. */
    ipv6_addr_t target_addr;                                                                        /**< Target Address field. */
} icmp6_na_header_t;

/**@brief Router Solicitation message's header. */
typedef struct
{
    uint32_t reserved;                                                                              /**< Reserved field. */
} icmp6_rs_header_t;

/**@brief Option header of ICMPv6 packet. */
typedef struct
{
    uint8_t type;                                                                                   /**< Option type. */
    uint8_t length;                                                                                 /**< Length, in unit of 8 octets. */
} nd_option_t;

/**@brief Source Link Layer Address Option header format. */
typedef struct
{
    uint8_t type;                                                                                   /**< Option type. */
    uint8_t length;                                                                                 /**< Length, units of 8 octets. */
    eui64_t addr;                                                                                   /**< Link-layer address. */
    uint8_t padding[6];                                                                             /**< Padding. */
} nd_option_sllao_t;

/**@brief Target Link Layer Address Option header format. */
typedef struct
{
    uint8_t type;                                                                                   /**< Option type. */
    uint8_t length;                                                                                 /**< Length, units of 8 octets. */
    eui64_t addr;                                                                                   /**< Link-layer address. */
    uint8_t padding[6];                                                                             /**< Padding. */
} nd_option_tllao_t;

/**@brief Prefix Information Option header format. */
typedef struct
{
    uint8_t     type;                                                                               /**< Option type. */
    uint8_t     length;                                                                             /**< Length, units of 8 octets. */
    uint8_t     prefix_length;                                                                      /**< Prefix length. */
    uint8_t     flags;                                                                              /**< Flags (L/A) and reserved. */
    uint32_t    valid_lifetime;                                                                     /**< Valid Lifetime.  */
    uint32_t    preferred_lifetime;                                                                 /**< Preferred Lifetime. */
    uint32_t    reserved;                                                                           /**< Reserved field. */
    ipv6_addr_t prefix;                                                                             /**< Prefix address. */
} nd_option_pio_t;

/**@brief Address Registration Option header format. */
typedef struct
{
    uint8_t  type;                                                                                  /**< Option type. */
    uint8_t  length;                                                                                /**< Length, units of 8 octets. */
    uint8_t  status;                                                                                /**< Status of ARO. */
    uint8_t  reserved;                                                                              /**< Reserved1, split to avoid alignment. */
    uint16_t reserved2;                                                                             /**< Reserved2, split to avoid alignment. */
    uint16_t registration_lifetime;                                                                 /**< Registration Lifetime. */
    eui64_t  eui64;                                                                                 /**< EUI-64 source address. */
} nd_option_aro_t;

/**@brief 6LoWPAN Context Option header format. */
typedef struct
{
    uint8_t     type;                                                                               /**< Option type. */
    uint8_t     length;                                                                             /**< Length, units of 8 octets. */
    uint8_t     context_length;                                                                     /**< Context Length. */
    uint8_t     CID_C;                                                                              /**< 4-bit Context and 1-bit context compression flag. */
    uint16_t    reserved;                                                                           /**< Reserved. */
    uint16_t    valid_lifetime;                                                                     /**< Valid Lifetime. */
    ipv6_addr_t context;                                                                            /**< Context IPv6 Prefix. */
} nd_option_6co_t;

static bool                     m_initialization_state = false;                                     /**< Variable to maintain module initialization state. */
static uint16_t                 m_sequence_number      = 0;                                         /**< Sequence number from ICMPv6 packet. */
static icmp6_receive_callback_t m_event_handler        = NULL;                                      /**< Application event handler. */
SDK_MUTEX_DEFINE(m_icmp6_mutex)                                                                     /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */

/**@brief Function for initializing default values of IP Header for ICMP.
 *
 * @param[in]   p_ip_header   Pointer to IPv6 header.
 * @param[in]   hoplimit      Hop Limit in IPv6 header.
 *
 * @return      None.
 */
static __INLINE void icmp_ip_header(ipv6_header_t * p_ip_header, uint8_t hoplimit)
{
    ipv6_header_init(p_ip_header);
    p_ip_header->next_header = IPV6_NEXT_HEADER_ICMP6;
    p_ip_header->hoplimit    = hoplimit;
}

/**@brief Function for adding SLLAO option to the packet.
 *
 * @param[in]   p_interface  Pointer to IoT interface.
 * @param[in]   p_data       Pointer to the memory where SLLAO option should be added.
 *
 * @return      None.
 */
static __INLINE void add_sllao_opt(const iot_interface_t * p_interface, nd_option_sllao_t * p_sllao)
{
    p_sllao->type   = ND_OPT_TYPE_SLLAO;
    p_sllao->length = ND_OPT_SLLAO_LENGTH;

#if (IPV6_LL_ADDR_SIZE == 6)
    memcpy(p_sllao->addr.identifier, p_interface->local_addr.identifier, 3);
    memcpy(p_sllao->addr.identifier + 3, p_interface->local_addr.identifier + 5, 3);
#else
    // Copy EUI-64 and add padding.
    memcpy(p_sllao->addr.identifier, p_interface->local_addr.identifier, IPV6_LL_ADDR_SIZE);
    memset(p_sllao->padding, 0, 6);
#endif
}

/**@brief Function for adding TLLAO option to the packet.
 *
 * @param[in]   p_interface  Pointer to IoT interface.
 * @param[in]   p_data       Pointer to the memory where TLLAO option should be added.
 *
 * @return      None.
 */
static __INLINE void add_tllao_opt(const iot_interface_t * p_interface, nd_option_tllao_t * p_tllao)
{
    p_tllao->type   = ND_OPT_TYPE_TLLAO;
    p_tllao->length = ND_OPT_TLLAO_LENGTH;

#if (IPV6_LL_ADDR_SIZE == 6)
    memcpy(p_tllao->addr.identifier, p_interface->local_addr.identifier, 3);
    memcpy(p_tllao->addr.identifier + 3, p_interface->local_addr.identifier + 5, 3);
#else
    // Copy EUI-64 and add padding.
    memcpy(p_tllao->addr.identifier, p_interface->local_addr.identifier, IPV6_LL_ADDR_SIZE);
    memset(p_tllao->padding, 0, 6);
#endif
}

/**@brief Function for adding ARO option to packet.
 *
 * @param[in]   p_interface  Pointer to IoT interface.
 * @param[in]   p_data       Pointer to the memory where ARO option should be added.
 * @param[in]   aro_lifetime Lifetime of registration.
 *
 * @return      None.
 */
static __INLINE void add_aro_opt(const iot_interface_t * p_interface,
                                 nd_option_aro_t * p_aro,
                                 uint16_t          aro_lifetime)
{
    p_aro->type                  = ND_OPT_TYPE_ARO;
    p_aro->length                = ND_OPT_ARO_LENGTH;
    p_aro->status                = 0x00;
    p_aro->reserved              = 0x00;
    p_aro->reserved2             = 0x00;
    p_aro->registration_lifetime = HTONS(aro_lifetime);

    // Copy EUI-64 and add padding.
    memcpy(p_aro->eui64.identifier, p_interface->local_addr.identifier, EUI_64_ADDR_SIZE);
}

#if (ICMP6_ENABLE_ND6_MESSAGES_TO_APPLICATION == 1 || ICMP6_ENABLE_ALL_MESSAGES_TO_APPLICATION == 1)

/**@brief Function for notifying application of the ICMPv6 received packet.
 *
 * @param[in]   p_interface    Pointer to external interface from which packet come.
 * @param[in]   p_pbuffer      Pointer to packet buffer of ICMP6_PACKET_TYPE.
 * @param[in]   process_result Result of internal processing packet.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise.
 */
static uint32_t app_notify_icmp_data(iot_interface_t  * p_interface,
                                     iot_pbuffer_t    * p_pbuffer,
                                     uint32_t           process_result)
{
    uint32_t err_code = NRF_SUCCESS;

    if (m_event_handler != NULL)
    {

       ipv6_header_t  * p_ip_header   = (ipv6_header_t *)
                               (p_pbuffer->p_payload - ICMP6_HEADER_SIZE - IPV6_IP_HEADER_SIZE);
       icmp6_header_t * p_icmp_header = (icmp6_header_t *)
                               (p_pbuffer->p_payload - ICMP6_HEADER_SIZE);

        ICMP6_MUTEX_UNLOCK();

        // Change byte order of ICMP header given to application.
        p_icmp_header->checksum = NTOHS(p_icmp_header->checksum);

        err_code = m_event_handler(p_interface,
                                   p_ip_header,
                                   p_icmp_header,
                                   process_result,
                                   p_pbuffer);

        ICMP6_MUTEX_LOCK();
    }

    return err_code;
}

#endif

#if (ICMP6_ENABLE_HANDLE_ECHO_REQUEST_TO_APPLICATION == 0)

/**@brief Function for responding on ECHO REQUEST message.
 *
 * @param[in]   p_interface   Pointer to external interface from which packet come.
 * @param[in]   p_ip_header   Pointer to IPv6 Header.
 * @param[in]   p_icmp_header Pointer to ICMPv6 header.
 * @param[in]   p_packet      Pointer to packet buffer.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise.
 */
static void echo_reply_send(iot_interface_t  * p_interface,
                            ipv6_header_t    * p_ip_header,
                            icmp6_header_t   * p_icmp_header,
                            iot_pbuffer_t    * p_packet)
{
    uint32_t                    err_code;
    uint16_t                    checksum;
    iot_pbuffer_t             * p_pbuffer;
    iot_pbuffer_alloc_param_t   pbuff_param;

    // Headers of new packet.
    ipv6_header_t       * p_reply_ip_header;
    icmp6_header_t      * p_reply_icmp_header;

    ICMP6_TRC("Sending reply on Echo Request.");

    // Requesting buffer for reply
    pbuff_param.flags  = PBUFFER_FLAG_DEFAULT;
    pbuff_param.type   = ICMP6_PACKET_TYPE;
    pbuff_param.length = p_packet->length;

    err_code = iot_pbuffer_allocate(&pbuff_param, &p_pbuffer);
    if (err_code == NRF_SUCCESS)
    {
        p_reply_ip_header   = (ipv6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE -
                                               IPV6_IP_HEADER_SIZE);
        p_reply_icmp_header = (icmp6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE);

        // Change ICMP header.
        p_reply_icmp_header->type     = ICMP6_TYPE_ECHO_REPLY;
        p_reply_icmp_header->code     = 0;
        p_reply_icmp_header->checksum = 0;

        // IPv6 Header initialization.
        icmp_ip_header(p_reply_ip_header, IPV6_DEFAULT_HOP_LIMIT);

        p_reply_ip_header->destaddr = p_ip_header->srcaddr;
        p_reply_ip_header->length   = HTONS(p_pbuffer->length + ICMP6_HEADER_SIZE);

        if (IPV6_ADDRESS_IS_MULTICAST(&p_ip_header->destaddr))
        {
            IPV6_CREATE_LINK_LOCAL_FROM_EUI64(&p_reply_ip_header->srcaddr,
                                              p_interface->local_addr.identifier);
        }
        else
        {
            p_reply_ip_header->srcaddr = p_ip_header->destaddr;
        }

        // Set echo reply parameters.
        p_reply_icmp_header->sp.echo.id       = p_icmp_header->sp.echo.id;
        p_reply_icmp_header->sp.echo.sequence = p_icmp_header->sp.echo.sequence;

        // Copy user data.
        memcpy(p_pbuffer->p_payload,
               p_packet->p_payload,
               p_packet->length);

        // Calculate checksum.
        checksum = p_pbuffer->length + ICMP6_HEADER_SIZE + IPV6_NEXT_HEADER_ICMP6;

        ipv6_checksum_calculate(p_reply_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_reply_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_pbuffer->p_payload - ICMP6_HEADER_SIZE,
                                p_pbuffer->length + ICMP6_HEADER_SIZE,
                                &checksum,
                                false);

        p_reply_icmp_header->checksum = HTONS((~checksum));

        p_pbuffer->p_payload -= ICMP6_OFFSET;
        p_pbuffer->length    += ICMP6_OFFSET;

        // Send IPv6 packet.
        err_code = ipv6_send(p_interface, p_pbuffer);

        if (err_code != NRF_SUCCESS)
        {
            ICMP6_ERR("Cannot send packet buffer!");
        }
    }
    else
    {
        ICMP6_ERR("Failed to allocate packet buffer!");
    }
}
#endif


/**@brief Function for responding on Neighbor Advertisement message.
 *
 * @param[in]   p_interface   Pointer to external interface from which packet come.
 * @param[in]   p_ip_header   Pointer to IPv6 Header.
 * @param[in]   p_icmp_header Pointer to ICMPv6 header.
 * @param[in]   p_target_addr Pointer to the IPv6 address.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise.
 */
static uint32_t na_send(iot_interface_t  * p_interface,
                        ipv6_header_t    * p_ip_header,
                        icmp6_header_t   * p_icmp_header,
                        ipv6_addr_t      * p_target_addr)
{
    uint32_t                    err_code;
    uint16_t                    checksum;
    iot_pbuffer_t             * p_pbuffer;
    iot_pbuffer_alloc_param_t   pbuff_param;

    // Headers of new packet.
    ipv6_header_t     * p_reply_ip_header;
    icmp6_header_t    * p_reply_icmp_header;
    icmp6_na_header_t * p_reply_na_header;
    nd_option_tllao_t * p_reply_opt_tllao_header;

    ICMP6_TRC("Sending reply on Neighbor Solocitation.");

    // Requesting buffer for reply
    pbuff_param.flags  = PBUFFER_FLAG_DEFAULT;
    pbuff_param.type   = ICMP6_PACKET_TYPE;
    pbuff_param.length = ND_NA_HEADER_SIZE + ND_OPT_TLLAO_SIZE - ND_PAYLOAD_ADJUST_OFFSET;

    err_code = iot_pbuffer_allocate(&pbuff_param, &p_pbuffer);
    if (err_code == NRF_SUCCESS)
    {
        p_reply_ip_header        = (ipv6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE -
                                                     IPV6_IP_HEADER_SIZE);
        p_reply_icmp_header      = (icmp6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE);

        p_pbuffer->p_payload -= ND_PAYLOAD_ADJUST_OFFSET;

        p_reply_na_header        = (icmp6_na_header_t *)(p_pbuffer->p_payload);
        p_reply_opt_tllao_header = (nd_option_tllao_t *)(p_pbuffer->p_payload + ND_NA_HEADER_SIZE);

        p_pbuffer->p_payload += ND_PAYLOAD_ADJUST_OFFSET;

        // Change ICMP header.
        p_reply_icmp_header->type     = ICMP6_TYPE_NEIGHBOR_ADVERTISEMENT;
        p_reply_icmp_header->code     = 0;
        p_reply_icmp_header->checksum = 0;

        // IPv6 Header initialization.
        icmp_ip_header(p_reply_ip_header, ND_HOP_LIMIT);

        p_reply_ip_header->srcaddr  = *p_target_addr;
        p_reply_ip_header->destaddr = p_ip_header->srcaddr;
        p_reply_ip_header->length   = HTONS(p_pbuffer->length + ICMP6_HEADER_SIZE);

        p_reply_na_header->flags       = ND_NA_S_FLAG | ND_NA_O_FLAG ;
        p_reply_na_header->reserved    = 0;
        p_reply_na_header->target_addr = *p_target_addr;

        // Add TLLAO option.
        add_tllao_opt(p_interface, p_reply_opt_tllao_header);

        // Calculate checksum.
        checksum = p_pbuffer->length + ICMP6_HEADER_SIZE + IPV6_NEXT_HEADER_ICMP6;

        ipv6_checksum_calculate(p_reply_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_reply_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_pbuffer->p_payload - ICMP6_HEADER_SIZE,
                                p_pbuffer->length + ICMP6_HEADER_SIZE,
                                &checksum,
                                false);

        p_reply_icmp_header->checksum = HTONS((~checksum));

        p_pbuffer->p_payload -= ICMP6_OFFSET;
        p_pbuffer->length    += ICMP6_OFFSET;

        // Send IPv6 packet.
        err_code = ipv6_send(p_interface, p_pbuffer);

        if (err_code != NRF_SUCCESS)
        {
            ICMP6_ERR("Cannot send packet buffer!");
        }
    }
    else
    {
        ICMP6_ERR("Failed to allocate packet buffer!\r\n");
    }

    return err_code;
}


/**@brief Function for parsing Neighbor Solicitation message.
 *
 * @param[in]   p_interface   Pointer to external interface from which packet come.
 * @param[in]   p_ip_header   Pointer to IPv6 Header.
 * @param[in]   p_icmp_header Pointer to ICMPv6 header.
 * @param[in]   p_packet      Pointer to packet buffer.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise.
 */
static uint32_t ns_input(iot_interface_t  * p_interface,
                         ipv6_header_t    * p_ip_header,
                         icmp6_header_t   * p_icmp_header,
                         iot_pbuffer_t    * p_packet)
{
    uint32_t err_code = NRF_SUCCESS;

    // Read target address.
    icmp6_ns_header_t * p_ns_header = (icmp6_ns_header_t *)p_packet->p_payload;

    if (ipv6_address_check(p_interface, &p_ns_header->target_addr) == NRF_SUCCESS)
    {
        err_code = na_send(p_interface, p_ip_header, p_icmp_header, &p_ns_header->target_addr);
    }

    return err_code;
}


/**@brief Function for parsing Router Advertisement message.
 *        Because stack gives all control to application, internal RA parsing take care
 *        only on Context Identifier.
 *
 * @param[in]   p_interface   Pointer to external interface from which packet come.
 * @param[in]   p_ip_header   Pointer to IPv6 Header.
 * @param[in]   p_icmp_header Pointer to ICMPv6 header.
 * @param[in]   p_packet      Pointer to packet buffer.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise.
 */
static uint32_t ra_input(iot_interface_t  * p_interface,
                         ipv6_header_t    * p_ip_header,
                         icmp6_header_t   * p_icmp_header,
                         iot_pbuffer_t    * p_packet)
{
    uint32_t          err_code;
    iot_context_t     context;
    iot_context_t   * p_context;
    uint16_t          curr_opt_offset = ND_RA_HEADER_SIZE;
    nd_option_t     * p_opt           = NULL;
    nd_option_6co_t * p_6co           = NULL;
    nd_option_pio_t * p_pio           = NULL;

    if (!IPV6_ADDRESS_IS_LINK_LOCAL(&p_ip_header->srcaddr))
    {
        return ICMP6_INVALID_PACKET_DATA;
    }

    // Read all option we get.
    while (curr_opt_offset < p_packet->length)
    {
        p_opt = (nd_option_t *)(p_packet->p_payload + curr_opt_offset);

        if (p_opt->length == 0)
        {
            ICMP6_ERR("Invalid zero length option!");
            return ICMP6_INVALID_PACKET_DATA;
        }

        ICMP6_TRC("Option type = 0x%02x!", p_opt->type);

        // Searching for handling options.
        switch (p_opt->type)
        {
            case ND_OPT_TYPE_PIO:
            {
                p_pio = (nd_option_pio_t *)p_opt;

                if (p_pio->prefix_length != 0 &&
                  (p_pio->flags & ND_OPT_PIO_A_MASK) &&
                  !(p_pio->flags & ND_OPT_PIO_L_MASK))
                {
                    // Ignore Link-Local address
                    if (IPV6_ADDRESS_IS_LINK_LOCAL(&p_pio->prefix))
                    {
                        ICMP6_ERR("Ignore Link-Local prefix!");
                        break;
                    }

                    // For now address is automatically set as a preferred.
                    ipv6_addr_conf_t temp_address;

                    // Set IPv6 EUI-64
                    IPV6_CREATE_LINK_LOCAL_FROM_EUI64(&temp_address.addr,
                                                      p_interface->local_addr.identifier);

                    // Add prefix
                    IPV6_ADDRESS_PREFIX_SET(temp_address.addr.u8,
                                            p_pio->prefix.u8,
                                            p_pio->prefix_length);

                    if (p_pio->valid_lifetime != 0)
                    {
                        temp_address.state = IPV6_ADDR_STATE_PREFERRED;

                        err_code = ipv6_address_set(p_interface, &temp_address);

                        if (err_code != NRF_SUCCESS)
                        {
                            ICMP6_ERR("Cannot add new address! Address table full!");
                        }
                    }
                    else
                    {
                        err_code = ipv6_address_remove(p_interface, &temp_address.addr);

                        if (err_code != NRF_SUCCESS)
                        {
                            ICMP6_ERR("Cannot remove address!");
                        }
                    }
                }
                else
                {
                    ICMP6_ERR("Prefix option has incorrect parameters!");
                    return ICMP6_INVALID_PACKET_DATA;
                }

                break;
            }
            case ND_OPT_TYPE_6CO:
            {
                p_6co = (nd_option_6co_t *)p_opt;

                memset(context.prefix.u8, 0, IPV6_ADDR_SIZE);

                context.prefix           = p_6co->context;
                context.prefix_len       = p_6co->context_length;
                context.context_id       = (p_6co->CID_C & ND_OPT_6CO_CID_MASK) >>
                                            ND_OPT_6CO_CID_POS;
                context.compression_flag = (p_6co->CID_C & ND_OPT_6CO_C_MASK) >>
                                            ND_OPT_6CO_C_POS;

                if (p_6co->valid_lifetime == 0)
                {
                    err_code = iot_context_manager_get_by_cid(p_interface,
                                                              context.context_id,
                                                              &p_context);

                    if (err_code == NRF_SUCCESS)
                    {
                        err_code = iot_context_manager_remove(p_interface, p_context);

                        if (err_code == NRF_SUCCESS)
                        {
                            ICMP6_TRC("Removed context! CID = 0x%02x", context.context_id);
                        }
                    }

                }
                else
                {
                    err_code = iot_context_manager_update(p_interface, &context);

                    if (err_code == NRF_SUCCESS)
                    {
                        ICMP6_TRC("New context added! CID = 0x%02x", context.context_id);
                    }
                }

                break;
            }
        }

        // Increment current offset option.
        curr_opt_offset += 8 * p_opt->length;
    }

    return NRF_SUCCESS;
}

/**@brief Function for notifying application of the ICMPv6 received packet.
 *
 * @param[in]   p_interface   Pointer to external interface from which packet come.
 * @param[in]   p_ip_header   Pointer to IPv6 Header.
 * @param[in]   p_icmp_header Pointer to ICMPv6 header.
 * @param[in]   p_packet      Pointer to packet buffer.
 *
 * @return      NRF_SUCCESS after successful processing, error otherwise.
 */
static uint32_t ndisc_input(iot_interface_t  * p_interface,
                            ipv6_header_t    * p_ip_header,
                            icmp6_header_t   * p_icmp_header,
                            iot_pbuffer_t    * p_packet)
{
    uint32_t process_result;

    switch (p_icmp_header->type)
    {
        case ICMP6_TYPE_ROUTER_SOLICITATION:
            ICMP6_ERR("Got unsupported Router Solicitation message.");
            process_result = ICMP6_UNHANDLED_PACKET_TYPE;
        break;

        case ICMP6_TYPE_ROUTER_ADVERTISEMENT:
            ICMP6_TRC("Got Router Advertisement message.");
            process_result = ra_input(p_interface, p_ip_header, p_icmp_header, p_packet);
        break;

        case ICMP6_TYPE_NEIGHBOR_SOLICITATION:
            ICMP6_TRC("Got Neighbour Solicitation message.");
            process_result = ns_input(p_interface, p_ip_header, p_icmp_header, p_packet);
        break;

        case ICMP6_TYPE_NEIGHBOR_ADVERTISEMENT:
            ICMP6_TRC("Got Neighbour Advertisement message.");
            process_result = NRF_SUCCESS;
        break;

        default:
            process_result = ICMP6_UNHANDLED_PACKET_TYPE;
            break;
    }

    return process_result;
}

uint32_t icmp6_error_message(const iot_interface_t             * p_interface,
                             const ipv6_addr_t                 * p_src_addr,
                             const ipv6_addr_t                 * p_dest_addr,
                             const icmp6_error_message_param_t * p_param)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_src_addr);
    NULL_PARAM_CHECK(p_dest_addr);
    NULL_PARAM_CHECK(p_param);
    NULL_PARAM_CHECK(p_param->p_packet);

    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    iot_pbuffer_t             * p_pbuffer;
    ipv6_header_t             * p_ip_header;
    icmp6_header_t            * p_icmp_header;
    iot_pbuffer_alloc_param_t   pbuff_param;
    uint16_t                    checksum;
    uint32_t                    err_code = NRF_SUCCESS;
    const uint32_t              error_packet_length =
                                (MIN(p_param->packet_len,
                                    ICMP6_ERROR_MESSAGE_MAX_SIZE - ICMP6_HEADER_SIZE));

    // Requesting buffer for error message.
    pbuff_param.flags  = PBUFFER_FLAG_DEFAULT;
    pbuff_param.type   = ICMP6_PACKET_TYPE;
    pbuff_param.length = error_packet_length;

    err_code = iot_pbuffer_allocate(&pbuff_param, &p_pbuffer);
    if (err_code == NRF_SUCCESS)
    {
        p_ip_header   = (ipv6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE -
                                          IPV6_IP_HEADER_SIZE);
        p_icmp_header = (icmp6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE);

        // Change ICMP header.
        p_icmp_header->type     = p_param->type;
        p_icmp_header->code     = p_param->code;
        p_icmp_header->checksum = 0;

        switch (p_param->type)
        {
            case ICMP6_TYPE_PACKET_TOO_LONG:
            {
                p_icmp_header->sp.mtu = HTONL(p_param->error_field.mtu);
                break;
            }
            case ICMP6_TYPE_PARAMETER_PROBLEM:
            {
                p_icmp_header->sp.offset = HTONL(p_param->error_field.offset);
                break;
            }
            default:
            {
                p_icmp_header->sp.unused = 0;
                break;
            }
        }

        // IPv6 Header initialization.
        icmp_ip_header(p_ip_header, IPV6_DEFAULT_HOP_LIMIT);

        p_ip_header->srcaddr  = *p_src_addr;
        p_ip_header->destaddr = *p_dest_addr;
        p_ip_header->length   = HTONS(p_pbuffer->length + ICMP6_HEADER_SIZE);

        memcpy(p_pbuffer->p_payload, p_param->p_packet, error_packet_length);

        // Calculate checksum.
        checksum = error_packet_length + IPV6_NEXT_HEADER_ICMP6;

        ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_pbuffer->p_payload - ICMP6_HEADER_SIZE,
                                p_pbuffer->length + ICMP6_HEADER_SIZE,
                                &checksum,
                                false);

        // Update checksum in the packet.
        p_icmp_header->checksum = HTONS((~checksum));

        p_pbuffer->p_payload -= ICMP6_OFFSET;
        p_pbuffer->length    += ICMP6_OFFSET;

        // Send IPv6 packet.
        err_code = ipv6_send(p_interface, p_pbuffer);
    }

    ICMP6_EXIT();

    ICMP6_MUTEX_UNLOCK();

    return err_code;
}

uint32_t icmp6_echo_request(const iot_interface_t  * p_interface,
                            const ipv6_addr_t      * p_src_addr,
                            const ipv6_addr_t      * p_dest_addr,
                            iot_pbuffer_t          * p_request)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_src_addr);
    NULL_PARAM_CHECK(p_dest_addr);
    NULL_PARAM_CHECK(p_request);
    PACKET_TYPE_CHECK(p_request);

    uint32_t              err_code = NRF_SUCCESS;
    uint16_t              checksum;
    ipv6_header_t       * p_ip_header;
    icmp6_header_t      * p_icmp_header;

    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    // Headers of IPv6 packet.
    p_ip_header   = (ipv6_header_t *)(p_request->p_payload - ICMP6_HEADER_SIZE -
                                      IPV6_IP_HEADER_SIZE);
    p_icmp_header = (icmp6_header_t *)(p_request->p_payload - ICMP6_HEADER_SIZE);

    // Change ICMP header.
    p_icmp_header->type     = ICMP6_TYPE_ECHO_REQUEST;
    p_icmp_header->code     = 0;
    p_icmp_header->checksum = 0;

    // IPv6 Header initialization.
    icmp_ip_header(p_ip_header, IPV6_DEFAULT_HOP_LIMIT);

    p_ip_header->srcaddr  = *p_src_addr;
    p_ip_header->destaddr = *p_dest_addr;
    p_ip_header->length   = HTONS(p_request->length + ICMP6_HEADER_SIZE);

    // Set echo reply parameters.
    p_icmp_header->sp.echo.id       = 0;
    p_icmp_header->sp.echo.sequence = HTONS(m_sequence_number);

    // Calculate checksum.
    checksum = p_request->length + ICMP6_HEADER_SIZE + IPV6_NEXT_HEADER_ICMP6;

    ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
    ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
    ipv6_checksum_calculate(p_request->p_payload - ICMP6_HEADER_SIZE,
                            p_request->length + ICMP6_HEADER_SIZE,
                            &checksum,
                            false);

    p_icmp_header->checksum = HTONS((~checksum));

    m_sequence_number++;
    p_request->p_payload -= ICMP6_OFFSET;
    p_request->length    += ICMP6_OFFSET;

    // Send IPv6 packet.
    err_code = ipv6_send(p_interface, p_request);

    ICMP6_EXIT();

    ICMP6_MUTEX_UNLOCK();

    return err_code;
}

uint32_t icmp6_rs_send(const iot_interface_t * p_interface,
                       const ipv6_addr_t     * p_src_addr,
                       const ipv6_addr_t     * p_dest_addr)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_src_addr);
    NULL_PARAM_CHECK(p_dest_addr);

    uint32_t                    err_code = NRF_SUCCESS;
    uint16_t                    checksum;
    iot_pbuffer_t             * p_pbuffer;
    iot_pbuffer_alloc_param_t   pbuff_param;

    // IPv6 Headers.
    ipv6_header_t             * p_ip_header;
    icmp6_header_t            * p_icmp_header;
    icmp6_rs_header_t         * p_rs_header;
    nd_option_sllao_t         * p_sllao_opt;

    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    // Requesting buffer for RS message
    pbuff_param.flags  = PBUFFER_FLAG_DEFAULT;
    pbuff_param.type   = ICMP6_PACKET_TYPE;
    pbuff_param.length = ND_OPT_SLLAO_SIZE;

    err_code = iot_pbuffer_allocate(&pbuff_param, &p_pbuffer);

    if (err_code == NRF_SUCCESS)
    {
        p_ip_header   = (ipv6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE -
                                          IPV6_IP_HEADER_SIZE);
        p_icmp_header = (icmp6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE);
        p_rs_header   = (icmp6_rs_header_t *)(&p_icmp_header->sp.unused);
        p_sllao_opt   = (nd_option_sllao_t *)(p_pbuffer->p_payload);

        // Change ICMP header.
        p_icmp_header->type     = ICMP6_TYPE_ROUTER_SOLICITATION;
        p_icmp_header->code     = 0;
        p_icmp_header->checksum = 0;

        // IPv6 Header initialization.
        icmp_ip_header(p_ip_header, ND_HOP_LIMIT);

        p_ip_header->srcaddr     = *p_src_addr;
        p_ip_header->destaddr    = *p_dest_addr;
        p_ip_header->length      = HTONS(p_pbuffer->length + ICMP6_HEADER_SIZE);

        // Set Router Solicitation parameter.
        p_rs_header->reserved = 0;

        // Add SLLAO option.
        add_sllao_opt(p_interface, p_sllao_opt);

        // Calculate checksum.
        checksum = p_pbuffer->length + ICMP6_HEADER_SIZE + IPV6_NEXT_HEADER_ICMP6;

        ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_pbuffer->p_payload - ICMP6_HEADER_SIZE,
                                p_pbuffer->length + ICMP6_HEADER_SIZE,
                                &checksum,
                                false);

        p_icmp_header->checksum = HTONS((~checksum));

        p_pbuffer->p_payload -= ICMP6_OFFSET;
        p_pbuffer->length    += ICMP6_OFFSET;

        // Send IPv6 packet.
        err_code = ipv6_send(p_interface, p_pbuffer);
    }
    else
    {
        ICMP6_ERR("Failed to allocate packet buffer!");
    }

    ICMP6_EXIT();

    ICMP6_MUTEX_UNLOCK();

    return err_code;
}

uint32_t icmp6_ns_send(const iot_interface_t  * p_interface,
                       const ipv6_addr_t      * p_src_addr,
                       const ipv6_addr_t      * p_dest_addr,
                       const icmp6_ns_param_t * p_param)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_src_addr);
    NULL_PARAM_CHECK(p_dest_addr);
    NULL_PARAM_CHECK(p_param);

    uint32_t                    err_code = NRF_SUCCESS;
    uint16_t                    aro_size = 0;
    uint16_t                    checksum;
    iot_pbuffer_t             * p_pbuffer;
    iot_pbuffer_alloc_param_t   pbuff_param;

    // IPv6 Headers.
    ipv6_header_t             * p_ip_header;
    icmp6_header_t            * p_icmp_header;
    icmp6_ns_header_t         * p_ns_header;
    nd_option_sllao_t         * p_sllao_opt;
    nd_option_aro_t           * p_aro_opt;

    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    if (p_param->add_aro)
    {
        aro_size = ND_OPT_ARO_SIZE;
    }

    // Requesting buffer for NS message
    pbuff_param.flags  = PBUFFER_FLAG_DEFAULT;
    pbuff_param.type   = ICMP6_PACKET_TYPE;
    pbuff_param.length = ND_NS_HEADER_SIZE + ND_OPT_SLLAO_SIZE + \
                         aro_size - ND_PAYLOAD_ADJUST_OFFSET;

    err_code = iot_pbuffer_allocate(&pbuff_param, &p_pbuffer);

    if (err_code == NRF_SUCCESS)
    {
        p_ip_header   = (ipv6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE -
                                          IPV6_IP_HEADER_SIZE);
        p_icmp_header = (icmp6_header_t *)(p_pbuffer->p_payload - ICMP6_HEADER_SIZE);
        p_pbuffer->p_payload -= ND_PAYLOAD_ADJUST_OFFSET;
        p_ns_header   = (icmp6_ns_header_t *)(p_pbuffer->p_payload);
        p_sllao_opt   = (nd_option_sllao_t *)(p_pbuffer->p_payload + ND_NS_HEADER_SIZE);
        p_aro_opt     = (nd_option_aro_t *)(p_pbuffer->p_payload + ND_NS_HEADER_SIZE +
                                            ND_OPT_SLLAO_SIZE);

        p_pbuffer->p_payload += ND_PAYLOAD_ADJUST_OFFSET;

        // Change ICMP header.
        p_icmp_header->type     = ICMP6_TYPE_NEIGHBOR_SOLICITATION;
        p_icmp_header->code     = 0;
        p_icmp_header->checksum = 0;

        // IPv6 Header initialization.
        icmp_ip_header(p_ip_header, ND_HOP_LIMIT);

        p_ip_header->srcaddr  = *p_src_addr;
        p_ip_header->destaddr = *p_dest_addr;
        p_ip_header->length   = HTONS(p_pbuffer->length + ICMP6_HEADER_SIZE);

        // Set Neighbour Solicitation parameter.
        p_ns_header->reserved    = 0;
        p_ns_header->target_addr = p_param->target_addr;

        // Add SLLAO option.
        add_sllao_opt(p_interface, p_sllao_opt);

        if (p_param->add_aro)
        {
            add_aro_opt(p_interface, p_aro_opt, p_param->aro_lifetime);
        }

        // Calculate checksum.
        checksum = p_pbuffer->length + ICMP6_HEADER_SIZE + IPV6_NEXT_HEADER_ICMP6;

        ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_pbuffer->p_payload - ICMP6_HEADER_SIZE,
                                p_pbuffer->length + ICMP6_HEADER_SIZE,
                                &checksum,
                                false);

        p_icmp_header->checksum = HTONS((~checksum));

        p_pbuffer->p_payload -= ICMP6_OFFSET;
        p_pbuffer->length    += ICMP6_OFFSET;

        // Send IPv6 packet.
        err_code = ipv6_send(p_interface, p_pbuffer);
    }
    else
    {
        ICMP6_ERR("Failed to allocate packet buffer!");
    }

    ICMP6_EXIT();

    ICMP6_MUTEX_UNLOCK();

    return err_code;
}


uint32_t icmp6_receive_register(icmp6_receive_callback_t cb)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(cb);
    UNUSED_VARIABLE(m_event_handler);

    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    // Store application event handler.
    m_event_handler = cb;

    ICMP6_EXIT();

    ICMP6_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t icmp6_init(void)
{
    SDK_MUTEX_INIT(m_icmp6_mutex);
    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    // Set application event handler.
    m_event_handler = NULL;

    // Indicate initialization of module.
    m_initialization_state = true;

    ICMP6_EXIT();

    ICMP6_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t icmp6_input(iot_interface_t  * p_interface,
                     ipv6_header_t    * p_ip_header,
                     iot_pbuffer_t    * p_packet)
{
    VERIFY_MODULE_IS_INITIALIZED();

    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_ip_header);
    NULL_PARAM_CHECK(p_packet);

    uint16_t              checksum;
    uint32_t              process_result = NRF_SUCCESS;
    bool                  is_ndisc       = false;
    icmp6_header_t      * p_icmp_header  = (icmp6_header_t *)p_packet->p_payload;
    uint32_t              err_code       = NRF_SUCCESS;

    ICMP6_MUTEX_LOCK();

    ICMP6_ENTRY();

    if (p_packet->length < ICMP6_HEADER_SIZE || p_ip_header->length < ICMP6_HEADER_SIZE)
    {
        ICMP6_ERR("Received malformed packet, which has 0x%08lX bytes.", p_packet->length);
        process_result = ICMP6_MALFORMED_PACKET;
    }
    else
    {
        // Check checksum of packet.
        checksum = p_packet->length + IPV6_NEXT_HEADER_ICMP6;

        ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_packet->p_payload, p_packet->length, &checksum, false);
        checksum = (uint16_t)~checksum;

        // Change pbuffer type.
        p_packet->type       = ICMP6_PACKET_TYPE;
        p_packet->p_payload  = p_packet->p_payload + ICMP6_HEADER_SIZE;
        p_packet->length    -= ICMP6_HEADER_SIZE;

        if (checksum != 0)
        {
            ICMP6_ERR("Bad checksum detected. Got 0x%08x but expected 0x%08x, 0x%08lX",
                           NTOHS(p_icmp_header->checksum), checksum, p_packet->length);
            process_result = ICMP6_BAD_CHECKSUM;
        }
        else
        {
            switch (p_icmp_header->type)
            {
                case ICMP6_TYPE_DESTINATION_UNREACHABLE:
                case ICMP6_TYPE_PACKET_TOO_LONG:
                case ICMP6_TYPE_TIME_EXCEED:
                case ICMP6_TYPE_PARAMETER_PROBLEM:
                {
                    ICMP6_TRC("Got ICMPv6 error message with type = 0x%08x",
                              p_icmp_header->type);
                    p_icmp_header->sp.unused = NTOHL(p_icmp_header->sp.unused);
                    break;
                }
                case ICMP6_TYPE_ECHO_REQUEST:
                case ICMP6_TYPE_ECHO_REPLY:
                {
                    ICMP6_TRC("Got ICMPv6 Echo message with type = 0x%x.", p_icmp_header->type);
                    ICMP6_TRC("From IPv6 Address:");
                    ICMP6_DUMP(p_ip_header->srcaddr.u32, IPV6_ADDR_SIZE);
                    ICMP6_TRC("Identifier: 0x%04x, Sequence Number: 0x%04x",
                              NTOHS(p_icmp_header->sp.echo.id),
                              NTOHS(p_icmp_header->sp.echo.sequence));
                    break;
                }
                case ICMP6_TYPE_ROUTER_SOLICITATION:
                case ICMP6_TYPE_ROUTER_ADVERTISEMENT:
                case ICMP6_TYPE_NEIGHBOR_SOLICITATION:
                case ICMP6_TYPE_NEIGHBOR_ADVERTISEMENT:
                {
                    p_packet->p_payload  = p_packet->p_payload - ND_PAYLOAD_ADJUST_OFFSET;
                    p_packet->length    += ND_PAYLOAD_ADJUST_OFFSET;
                    process_result = ndisc_input(p_interface,
                                                 p_ip_header,
                                                 p_icmp_header,
                                                 p_packet);
                    p_packet->p_payload  = p_packet->p_payload + ND_PAYLOAD_ADJUST_OFFSET;
                    p_packet->length    -= ND_PAYLOAD_ADJUST_OFFSET;
                    is_ndisc = true;
                    break;
                }
                default:
                    process_result = ICMP6_UNHANDLED_PACKET_TYPE;
                    break;
            }

#if (ICMP6_ENABLE_HANDLE_ECHO_REQUEST_TO_APPLICATION == 0)
            if (p_icmp_header->type == ICMP6_TYPE_ECHO_REQUEST)
            {
                echo_reply_send(p_interface, p_ip_header, p_icmp_header, p_packet);
            }
#endif
        }
    }

#if (ICMP6_ENABLE_ALL_MESSAGES_TO_APPLICATION == 1)
    err_code = app_notify_icmp_data(p_interface, p_packet, process_result);
#elif (ICMP6_ENABLE_ND6_MESSAGES_TO_APPLICATION == 1)
    if (is_ndisc)
    {
        err_code = app_notify_icmp_data(p_interface, p_packet, process_result);
    }
#endif

    ICMP6_EXIT();

    UNUSED_VARIABLE(is_ndisc);
    UNUSED_VARIABLE(process_result);

    ICMP6_MUTEX_UNLOCK();

    return err_code;
}
