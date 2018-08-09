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
#ifndef PEER_MANAGER_INTERNAL_H__
#define PEER_MANAGER_INTERNAL_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "ble.h"
#include "ble_gap.h"
#include "peer_manager_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @file peer_manager_types.h
 *
 * @addtogroup peer_manager
 * @brief File containing definitions used solely inside the Peer Manager's modules.
 * @{
 */

ANON_UNIONS_ENABLE;

/**@brief One piece of data associated with a peer, together with its type.
 *
 * @note This type is deprecated.
 */
typedef struct
{
    uint16_t              length_words; /**< @brief The length of the data in words. */
    pm_peer_data_id_t     data_id;      /**< @brief ID that specifies the type of data (defines which member of the union is used). */
    union
    {
        pm_peer_data_bonding_t       * p_bonding_data;            /**< @brief The exchanged bond information in addition to metadata of the bonding. */
        uint32_t                     * p_peer_rank;               /**< @brief A value locally assigned to this peer. Its interpretation is up to the user. The rank is not set automatically by the Peer Manager, but it is assigned by the user using either @ref pm_peer_rank_highest or a @ref PM_PEER_DATA_FUNCTIONS function. */
        bool                         * p_service_changed_pending; /**< @brief Whether a service changed indication should be sent to the peer. */
        pm_peer_data_local_gatt_db_t * p_local_gatt_db;           /**< @brief Persistent information pertaining to a peer GATT client. */
        ble_gatt_db_srv_t            * p_remote_gatt_db;          /**< @brief Persistent information pertaining to a peer GATT server. */
        uint8_t                      * p_application_data;        /**< @brief Arbitrary data to associate with the peer. This data can be freely used by the application. */
        void                         * p_all_data;                /**< @brief Generic access pointer to the data. It is used only to handle the data without regard to type. */
    }; /**< @brief The data. */
} pm_peer_data_t;


/**@brief Immutable version of @ref pm_peer_data_t.
 *
 * @note This type is deprecated.
 */
typedef struct
{
    uint16_t                    length_words; /**< @brief The length of the data in words. */
    pm_peer_data_id_t           data_id;      /**< @brief ID that specifies the type of data (defines which member of the union is used). */
    union
    {
        pm_peer_data_bonding_t       const * p_bonding_data;            /**< @brief Immutable @ref pm_peer_data_t::p_bonding_data. */
        uint32_t                     const * p_peer_rank;               /**< @brief Immutable @ref pm_peer_data_t::p_peer_rank. */
        bool                         const * p_service_changed_pending; /**< @brief Immutable @ref pm_peer_data_t::p_service_changed_pending. */
        pm_peer_data_local_gatt_db_t const * p_local_gatt_db;           /**< @brief Immutable @ref pm_peer_data_t::p_local_gatt_db. */
        ble_gatt_db_srv_t            const * p_remote_gatt_db;          /**< @brief Immutable @ref pm_peer_data_t::p_remote_gatt_db. */
        uint8_t                      const * p_application_data;        /**< @brief Immutable @ref pm_peer_data_t::p_application_data. */
        void                         const * p_all_data;                /**< @brief Immutable @ref pm_peer_data_t::p_all_data. */
    }; /**< @brief The data. */
} pm_peer_data_const_t;

ANON_UNIONS_DISABLE;


/**@brief Version of @ref pm_peer_data_t that reflects the structure of peer data in flash.
 *
 * @note This type is deprecated.
 */
typedef pm_peer_data_const_t pm_peer_data_flash_t;


/**@brief Event handler for events from the @ref peer_manager module.
 *
 * @sa pm_register
 *
 * @param[in]  p_event  The event that has occurred.
 */
typedef void (*pm_evt_handler_internal_t)(pm_evt_t * p_event);


/**@brief Macro for calculating the flash size of bonding data.
 *
 * @return The number of words that the data takes in flash.
 */
#define PM_BONDING_DATA_N_WORDS() BYTES_TO_WORDS(sizeof(pm_peer_data_bonding_t))


/**@brief Macro for calculating the flash size of service changed pending state.
 *
 * @return The number of words that the data takes in flash.
 */
#define PM_SC_STATE_N_WORDS() BYTES_TO_WORDS(sizeof(bool))


/**@brief Macro for calculating the flash size of local GATT database data.
 *
 * @param[in]  local_db_len  The length, in bytes, of the database as reported by the SoftDevice.
 *
 * @return The number of words that the data takes in flash.
 */
#define PM_LOCAL_DB_N_WORDS(local_db_len) \
                                    BYTES_TO_WORDS((local_db_len) + PM_LOCAL_DB_LEN_OVERHEAD_BYTES)


/**@brief Macro for calculating the length of a local GATT database attribute array.
 *
 * @param[in]  n_words  The number of words that the data takes in flash.
 *
 * @return The length of the database attribute array.
 */
#define PM_LOCAL_DB_LEN(n_words) (((n_words) * BYTES_PER_WORD) - PM_LOCAL_DB_LEN_OVERHEAD_BYTES)


/**@brief Macro for calculating the flash size of remote GATT database data.
 *
 * @param[in]  service_count  The number of services in the service array.
 *
 * @return The number of words that the data takes in flash.
 */
#define PM_REMOTE_DB_N_WORDS(service_count) BYTES_TO_WORDS(sizeof(ble_gatt_db_srv_t) * (service_count))


/**@brief Macro for calculating the flash size of remote GATT database data.
 *
 * @param[in]  n_words  The length in number of words.
 *
 * @return The number of words that the data takes in flash.
 */
#define PM_REMOTE_DB_N_SERVICES(n_words) (((n_words) * BYTES_PER_WORD) / sizeof(ble_gatt_db_srv_t))


/**@brief Function for calculating the flash size of the usage index.
 *
 * @return The number of words that the data takes in flash.
 */
#define PM_USAGE_INDEX_N_WORDS() BYTES_TO_WORDS(sizeof(uint32_t))

/** @}
 * @endcond
 */


#ifdef NRF_PM_DEBUG

    #define NRF_PM_DEBUG_CHECK(condition)   \
        if (!(condition))                   \
        {                                   \
            __asm("bkpt #0");               \
        }

#else

    // Prevent "variable set but never used" compiler warnings.
    #define NRF_PM_DEBUG_CHECK(condition)   (void)(condition)

#endif


#ifdef __cplusplus
}
#endif

#endif /* PEER_MANAGER_INTERNAL_H__ */
