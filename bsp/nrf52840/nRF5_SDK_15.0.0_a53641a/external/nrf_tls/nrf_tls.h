/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
/**@file nrf_tls.h
 *
 * @defgroup iot_nrf_tls TLS on nRF5x
 * @ingroup iot_sdk_common
 * @{
 * @brief TLS interface on nRF5x.
 *
 * @details Defines TLS interface for securing UDP/TCP transport using DTLS/TLS respectively.
 *          The interface integrates TLS library with needed libraries/drivers on the nRF.
 *
 */

#ifndef NRF_TLS_H__
#define NRF_TLS_H__

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Maximum number of TLS instances to be supported. */
#define NRF_TLS_INVALID_INSTANCE_IDENTIFIER 0xFFFFFFFF

/**@brief Initializes the TLS instance. */
#define NRF_TLS_INTSANCE_INIT(INSTANCE)                                                            \
        do                                                                                         \
        {                                                                                          \
            (INSTANCE)->transport_id = NRF_TLS_INVALID_INSTANCE_IDENTIFIER;                        \
            (INSTANCE)->instance_id  = NRF_TLS_INVALID_INSTANCE_IDENTIFIER;                        \
        }while(0)

/**@brief Transport type definitions. The type determines whether TLS or DTLS shall be used. */
typedef enum
{
    NRF_TLS_TYPE_STREAM,                                             /**< TCP transport, TLS to be used for the instance. */
    NRF_TLS_TYPE_DATAGRAM                                            /**< UDP transport, DTLS to be used for the instance. */
} nrf_transport_type_t;

/**@brief TLS/DTLS roles definition. */
typedef enum
{
    NRF_TLS_ROLE_CLIENT,                                             /**< Client role. */
    NRF_TLS_ROLE_SERVER                                              /**< Server role. */
} nrf_tls_role_t;

/**@brief TLS Instance identifier*/
typedef struct
{
    uint32_t transport_id;                                           /**< Identifies the TCP/UDP transport which is being secured. */
    uint32_t instance_id;                                            /**< Identifies the TLS instance. */
} nrf_tls_instance_t;

/**@brief Information needed when using Pre-shared key ciphers. */
typedef struct
{
    const uint8_t   * p_identity;                                     /**< Client identity. */
    const uint8_t   * p_secret_key;                                   /**< Secret Preshared Key. */
    uint16_t          identity_len;                                   /**< Length of the client identity. */
    uint16_t          secret_key_len;                                 /**< Length of the preshared key. */
} nrf_tls_preshared_key_t;

/**@brief Information provided when using Raw Public key ciphers. */
typedef struct
{
    const uint8_t   * p_private_key;                                 /**< Private key. */
    const uint8_t   * p_public_key;                                  /**< Raw public key. */
    uint16_t          private_key_len;                               /**< Length of the private key. */
    uint16_t          public_key_len;                                /**< Length of the raw public key. */
} nrf_tls_raw_key_t;

/**@brief Certificate to be used when using certificates for key derivation. */
typedef struct
{
    const uint8_t   * p_private_key;                                 /**< Private key. */
    const uint8_t   * p_certificate;                                 /**< Own certificate in PEM format. */
    uint16_t          private_key_len;                               /**< Length of the private key. */
    uint16_t          certificate_len;                               /**< Length of the certificate. */
} nrf_tls_certificate_t;

/**@brief Key settings to be used for TLS instance. */
typedef struct
{
    nrf_tls_certificate_t           * p_own_certificate;             /**< Own certificate to be used for the instance. Can be NULL. */
    uint8_t                         * p_ca_cert_pem;                 /**< CA certificate in PEM formart. */
    uint16_t                          ca_cert_pem_len;               /**< Length of the CA certificate. */
    nrf_tls_preshared_key_t         * p_psk;                         /**< Identitiy and shared secret in case pre-shared key is used. Can be NULL. */
    nrf_tls_raw_key_t               * p_raw_key;                     /**< Public and private key in case RAW keys are used. This method is not currently supported. */
} nrf_tls_key_settings_t;

/**@brief Transport write function registered for the instance.
 *
 * @details Function registered with the interface to write on the transport interface.
 *          The application shall implement the function registered here to ensure handshake
 *          messages and encrypted data can be written by the interface/TLS library on the
 *          transport.
 *
 * @param[in]    p_instance    Identifies the instance on which transport write is requested.
 *                             Shall not be NULL.
 * @param[in]    p_data        Pointer to data to be written on the instance.
 *                             Shall not be NULL.
 * @param[in]    datalen       Length of data to be written on the transport.
 *
 * @retval      NRF_SUCCESS    If the procedure was successful, else an error code indicating reason
 *                             for failure.
 */
typedef uint32_t (*nrf_tls_output_t)(nrf_tls_instance_t const * p_instance,
                                     uint8_t            const * p_data,
                                     uint32_t                   datalen);

/**@brief Options when requesting an TLS instance. */
typedef struct
{
    nrf_tls_output_t                  output_fn;                     /**< Function registered to deliver output of TLS operations on a TLS interface. Shall not be NULL. */
    uint8_t                           transport_type;                /**< Indicates type of transport being secured. @ref nrf_transport_type_t for possible transports. */
    uint8_t                           role;                          /**< Indicates role to be played, server or client. @ref nrf_tls_role_t for possible roles. */
    nrf_tls_key_settings_t          * p_key_settings;                /**< Provide key configurations/certificates here. */
} nrf_tls_options_t;

/**@brief Initialize TLS interface.
 *
 * @details This function initializes TLS interface. Initialization includes initializing the TLS
 *          library, RNG driver, and any other dependencies. This API shall be called before using
 *          any other APIs of the interface.
 *
 * @retval       NRF_SUCCESS   If the procedure is successful, else, an error code indicating
 *                             reason for failure. If the procedure fails, the application shall
 *                             not proceed with using other APIs of the interface.
 */
uint32_t nrf_tls_init(void);


/**@brief Allocate an TLS/DTLS instance.
 *
 * @details This function allocates an instance for TLS/DTLS. Options indicate whether DTLS/TLS will
 *          be used and role is server or client.
 *
 * @param[inout] p_instance    Instance with transport id set by the application to identify the
 *                             transport being secured. If the procedure is successful, the
 *                             instance id is allocated by the interface. The application is
 *                             expected to remember the instance information for all subsequent
 *                             procedures on the transport.
 *                             Shall not be NULL.
 * @param[in]    p_options     Pointer to options that indicate transport type, role, keys etc.
 *                             Output function registered is used write TLS/DTLS data on the
 *                             raw transport (TCP.UDP) for the instance.
 *                             Shall not be NULL.
 * @note
 *
 * @retval       NRF_SUCCESS   If the procedure is successful, else, an error code indicating
 *                             reason for failure. If the procedure succeeds, the application
 *                             shall use the instance allocated for all subsequent procedures on
 *                             the instance.
 */
uint32_t nrf_tls_alloc(nrf_tls_instance_t      * p_instance,
                       nrf_tls_options_t const * p_options);


/**@brief Free the TLS/DTLS instance.
 *
 * @details This function frees the instance allocated for TLS/DTLS. All sessions, buffered data
*           related to instance are freed as well by this API.
 *
 * @param[in]     p_instance   Identifies the instance being freed.
 *                             Shall not be NULL.
 *
 * @retval        NRF_SUCCESS  If the procedure is successful, else, an error code indicating
 *                             reason for failure. If the procedure succeeds, the application
 *                             shall use the instance allocated for all subsequent procedures on
 *                             the instance.
 */
uint32_t nrf_tls_free(nrf_tls_instance_t const * p_instance);


/**@brief Write data on the TLS/DTLS instance.
 *
 * @details This function writes data on the TLS/DTLS instance. The requested data is encrypted
 *          and padded based on cipher configuration and selected cipher during handshake.
 *          If no sessions exists already with the peer, a handshake is initiated automatically
 *          by the interface, if the role played on the instance is a client role. Requested data to
 *          be written is buffered until a session is established.
 *
 * @param[in]    p_instance    Identifies the instance on which write is requested.
 *                             Shall not be NULL.
 * @param[in]    p_data        Pointer to data to be written on the instance.
 *                             Shall not be NULL.
 * @param[inout] p_datalen     Pointer to size of data to be written. The actual size written can
 *                             be smaller than requested and is indicated here if the procedure is
 *                             successful. The application shall check for the actual size written
 *                             and make subsequent requests in case the right was partial.
 *                             Shall not be NULL.
 *
 * @retval     NRF_SUCCESS     If the procedure is successful, else, an error code indicating
 *                             reason for failure. If the procedure succeeds, the application
 *                             shall check for the actual size written and make subsequent
 *                             requests in case the right was partial.
 */
uint32_t nrf_tls_write(nrf_tls_instance_t const * p_instance,
                       uint8_t            const * p_data,
                       uint32_t                 * p_datalen);


/**@brief Read data from the TLS/DTLS instance.
 *
 * @details This function reads data from the TLS/DTLS interface. The read data is
 *          decrypted based on cipher configuration and selected cipher during handshake.
 *          If no data is available on the instance, the API indicates so with an error code.
 *          It is possible to request size of data that can be read by passing a NULL parameter on
 *          the data.
 *
 * @param[in]    p_instance    Identifies the instance on which read is requested.
 *                             Shall not be NULL.
 * @param[in]    p_data        Pointer to data where read data is to be copied.
 *                             Can be NULL. In case, this parameter is NULL, size of bytes that
 *                             are available to read is returned in the p_datalen parameter.
 * @param[inout] p_datalen     Pointer to size of data to be read. The application shall ensure that
 *                             the memory pointed to by p_data parameter is the size indicated.
 *                             The actual size read can be smaller than requested and is indicated
 *                             here if the procedure is successful. The application should check for
*                              the actual size read.
 *                             Shall not be NULL.
 *
 * @retval     NRF_SUCCESS     If the procedure is successful, else, an error code indicating
 *                             reason for failure. If the procedure succeeds, the application
 *                             should check for the actual size read.
 */
uint32_t nrf_tls_read(nrf_tls_instance_t const * p_instance,
                      uint8_t                  * p_data,
                      uint32_t                 * p_datalen);


/**@brief Function to input data read on the transport to the TLS library.
 *
 * @details Function to input data read on the transport to TLS library for further processing.
 *          Further processing could include advancing the  handshake or decrypting the received
 *          data based on the state of TLS session.
 *
 * @param[in]    p_instance    Identifies the instance on which transport write is requested.
 *                             Shall not be NULL.
 * @param[in]    p_data        Pointer to data to be processed on the instance.
 *                             Shall not be NULL.
 * @param[in]    datalen       Length of data to be written on the transport.
 *
 * @retval       NRF_SUCCESS   If the procedure was successful, else an error code indicating reason
 *                             for failure.
 */
uint32_t nrf_tls_input(nrf_tls_instance_t const * p_instance,
                       uint8_t            const * p_data,
                       uint32_t                   datalen);


/**@brief Function to continue TLS/DTLS operation after a busy state on transport.
 *
 * @details The transport writes requested by the TLS interface may return failure if transport
 *          data flow was off. In order to resume and retry the operations, this function shall be
 *          called periodically. This function shall be called in order to ensure TLS interface
 *          and the library behaves as expected.
 */
void nrf_tls_process(void);

#ifdef __cplusplus
}
#endif

#endif // NRF_TLS_H__

/** @} */
