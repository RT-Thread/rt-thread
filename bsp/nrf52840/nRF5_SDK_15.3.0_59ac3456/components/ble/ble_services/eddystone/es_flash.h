/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#ifndef ES_FLASH_H__
#define ES_FLASH_H__

#include <stdbool.h>
#include <stdint.h>
#include "es_slot.h"


/**
 * @file
 * @defgroup eddystone_flash Flash access
 * @brief Types and functions to access the flash of the Eddystone beacon.
 * @ingroup eddystone
 * @{
 */

#define WORD_SIZE 4

#define FLASH_ACCES_ERROR_CHECK_ALLOW_NOT_FOUND(err_code)                                          \
    if (err_code != (FDS_ERR_NOT_FOUND))                                                           \
        APP_ERROR_CHECK(err_code);

#define FLASH_OP_WAIT()                                                                            \
    uint32_t pending_ops = es_flash_num_pending_ops();                                             \
    while (pending_ops != 0)                                                                       \
    {                                                                                              \
        pending_ops = es_flash_num_pending_ops();                                                  \
    }

/**@brief Beacon configuration. */
typedef struct
{
    nrf_ble_escs_adv_interval_t    adv_interval;       //!< Advertising interval.
    bool                           remain_connectable; //!< Flag that specifies if the beacon should remain connectable.
} es_flash_beacon_config_t;

/**@brief Structure for keeping track of which slot has a configuration that must be restored upon reboot.
 * @details The size of this structure must be word aligned and match the flash block size of 32 bytes.
 */
typedef struct
{
    bool    slot_is_empty[APP_MAX_ADV_SLOTS];   //!< Flag that indicates whether the slot is empty.
    uint8_t padding[WORD_SIZE - ((APP_MAX_ADV_SLOTS + 1) % WORD_SIZE)]; //!< Padding used to ensure word alignment.
} es_flash_flags_t;

/**@brief Flash access types.
 */
typedef enum
{
    ES_FLASH_ACCESS_READ,  //!< Read data.
    ES_FLASH_ACCESS_WRITE, //!< Write data.
    ES_FLASH_ACCESS_CLEAR  //!< Clear data.
} es_flash_access_t;

/**@brief Function for accessing beacon configurations.
 *
 * @param[out,in]   p_config Pointer to the beacon configuration buffer.
 * @param[in]       access_type    Access type (see @ref es_flash_access_t).
 * @return          For possible return values, see:
 *                  - @ref fds_record_find_by_key
 *                  - @ref fds_record_open
 *                  - @ref fds_record_close
 *                  - @ref fds_record_write
 *                  - @ref fds_record_update
 *                  - @ref fds_record_delete
 */
ret_code_t es_flash_access_beacon_config(es_flash_beacon_config_t * p_config,
                                         es_flash_access_t          access_type);

/**@brief Function for accessing slot configuration from flash.
 *
 * @param[in]       slot_no        Slot index.
 * @param[out,in]   p_slot         Pointer to the slot configuration buffer.
 * @param[in]       access_type    Access type (see @ref es_flash_access_t).
 * @return          For possible return values, see:
 *                  - @ref fds_record_find_by_key
 *                  - @ref fds_record_open
 *                  - @ref fds_record_close
 *                  - @ref fds_record_write
 *                  - @ref fds_record_update
 *                  - @ref fds_record_delete
 */
ret_code_t es_flash_access_slot_configs(uint8_t           slot_no,
                                        es_slot_t   * p_slot,
                                        es_flash_access_t access_type);


/**@brief Function for accessing the beacon lock key from flash.
 *
 * @param[out,in]   p_lock_key     Pointer to the lock key buffer.
 * @param[in]       access_type    Access type (see @ref es_flash_access_t).
 * @return          For possible return values, see:
 *                  - @ref fds_record_find_by_key
 *                  - @ref fds_record_open
 *                  - @ref fds_record_close
 *                  - @ref fds_record_write
 *                  - @ref fds_record_update
 *                  - @ref fds_record_delete
 */
ret_code_t es_flash_access_lock_key(uint8_t * p_lock_key, es_flash_access_t access_type);

/**@brief Function for accessing the flash configuration flag from flash.
 *
 * @param[out,in]   p_flags        Pointer to the flag buffer.
 * @param[in]       access_type    Access type (see @ref es_flash_access_t).
 * @return          For possible return values, see:
 *                  - @ref fds_record_find_by_key
 *                  - @ref fds_record_open
 *                  - @ref fds_record_close
 *                  - @ref fds_record_write
 *                  - @ref fds_record_update
 *                  - @ref fds_record_delete
  */
ret_code_t es_flash_access_flags(es_flash_flags_t * p_flags, es_flash_access_t access_type);

/**@brief Function for retrieving the number of queued operations.
 * @return The number of operations that are queued.
 */
uint32_t es_flash_num_pending_ops(void);

/**@brief Function for performing a factory reset.
 * @return FDS return code.
 */
ret_code_t es_flash_factory_reset(void);

void es_flash_on_ble_evt(ble_evt_t const * p_evt);

/**@brief Function for initializing the flash module.
 *
 * @return See @ref fds_init for possible return values.
 */
ret_code_t es_flash_init(void);

/**
 * @}
 */

#endif // ES_FLASH_H__
