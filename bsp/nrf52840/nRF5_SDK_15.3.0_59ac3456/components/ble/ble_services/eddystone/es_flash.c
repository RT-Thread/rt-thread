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
#include <string.h>
#include "es_flash.h"
#include "es_util.h"
#include "app_scheduler.h"
#include "ble_hci.h"
#include "fds.h"
#include "nrf_nvic.h"

#define SIZE_OF_PRIV_KEY ESCS_ECDH_KEY_SIZE //!< Size of ECDH private key.
#define SIZE_OF_PUB_KEY ESCS_ECDH_KEY_SIZE  //!< Size of ECDH public key.
#define SIZE_OF_LOCK_KEY ESCS_AES_KEY_SIZE  //!< Size of lock key.
#define FILE_ID_ES_FLASH 0x1337             //!< File ID used for all flash access EXCEPT lock code.
#define FILE_ID_ES_FLASH_LOCK_KEY 0x1338    //!< File ID used for lock code flash access.
#define RECORD_KEY_FLAGS 0x1                //!< File record for flash flags.
#define RECORD_KEY_PRIV_KEY 0x2             //!< File record for private key.
#define RECORD_KEY_PUB_KEY 0x3              //!< File record for public key.
#define RECORD_KEY_LOCK_KEY 0x4             //!< File record for lock key.
#define RECORD_KEY_BEACON_CONFIG 0x5        //!< File record for lock key.

static uint16_t RECORD_KEY_SLOTS[5] = {0x6, 0x7, 0x8, 0x9, 0xa}; //!< File record for slots.

/**@brief Structure used for invoking flash access function. */
typedef struct
{
    uint16_t          record_key;
    uint16_t          file_id;
    uint8_t *         p_data_buf;
    uint8_t *         p_data;
    uint16_t          size_bytes;
    es_flash_access_t access_type;
} flash_access_params_t;

static volatile uint32_t m_num_pending_ops;                         //!< Current number of outstanding FDS operations.
static volatile bool     m_factory_reset_done;                      //!< Has a factory reset operation been completed.
static uint16_t          m_conn_handle = BLE_CONN_HANDLE_INVALID;   //!< Current connection handle.


#if APP_MAX_ADV_SLOTS > 32
#error "APP_MAX_ADV_SLOTS must be <= 32"
#endif

#define SLOT_DECL(i, _) __ALIGN(4) static uint8_t slot## i ##_buf[sizeof(es_slot_t)];
EVAL(REPEAT(APP_MAX_ADV_SLOTS, SLOT_DECL, ~))

__ALIGN(4) static uint8_t lock_key_buf[SIZE_OF_LOCK_KEY];   //!< Buffer for lock key flash access.

#define SLOT(i, _) slot## i ##_buf,
static uint8_t * slots_buf_p[APP_MAX_ADV_SLOTS] = {
    EVAL(REPEAT(APP_MAX_ADV_SLOTS, SLOT, ~))
};

__ALIGN(4) static uint8_t flash_flags_buf[sizeof(es_flash_flags_t)];            //!< Buffer for flash flags flash access.
__ALIGN(4) static uint8_t beacon_config_buf[sizeof(es_flash_beacon_config_t)];  //!< Buffer for beacon config flash access.

/**@brief Function handling scheduled FDS garbage collection. */
static void fds_gc_event(void * p_event_data, uint16_t event_size)
{
    ret_code_t fds_err_code;

    fds_err_code = fds_gc();
    if (fds_err_code != FDS_SUCCESS)
        APP_ERROR_CHECK_BOOL(NRF_ERROR_INTERNAL);
    m_num_pending_ops++;
}


/**@brief Function handling FDS events.
 *
 * @param[in] p_evt FDS event.
 */
static void fds_cb(fds_evt_t const * const p_evt)
{
    ret_code_t err_code;

    switch (p_evt->id)
    {
        case FDS_EVT_INIT:
            m_num_pending_ops = 0;
            break;
        case FDS_EVT_DEL_FILE:
            if (p_evt->del.file_id == FILE_ID_ES_FLASH)
            {
                m_factory_reset_done = true;
            }
            // Fall through
        case FDS_EVT_DEL_RECORD:
            // Schedule garbage collection
            err_code = app_sched_event_put(NULL, 0, fds_gc_event);
            APP_ERROR_CHECK(err_code);
            break;

        case FDS_EVT_GC:
            // During factory reset, a file is deleted, and garbage collection is scheduled
            // when the callback for that deletion is invoked.
            // So here we know that the factory reset is completed.
            if (m_factory_reset_done)
            {
                if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
                {
                    err_code =
                        sd_ble_gap_disconnect(m_conn_handle, 
                                              BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
                    APP_ERROR_CHECK(err_code);
                }
                else
                {
                    m_factory_reset_done = false;
                    (void)sd_nvic_SystemReset();
                }
            }
            // Fall through:
        case FDS_EVT_UPDATE:
            // Fall through:
        case FDS_EVT_WRITE:
            if (m_num_pending_ops > 0)
            {
                m_num_pending_ops--;
            }
            break;
    }
}


/**@brief Function performing flash access (read/write/clear).
 *
 * @param[in] p_params Flash access parameters.
 */
static ret_code_t access_flash_data(const flash_access_params_t * p_params)
{
    ret_code_t         err_code;
    fds_flash_record_t record = {0};
    fds_record_desc_t  desc   = {0};
    fds_find_token_t   ft     = {0};
    fds_record_t       record_to_write =
    {
        .data.p_data = p_params->p_data_buf,
        .file_id     = p_params->file_id
    };

    err_code = fds_record_find_by_key(p_params->record_key, &desc, &ft);

    // If its a read or clear, we can not accept errors on lookup
    if (p_params->access_type == ES_FLASH_ACCESS_READ)
    {
        RETURN_IF_ERROR(err_code);
    }

    if (p_params->access_type == ES_FLASH_ACCESS_CLEAR && err_code == FDS_ERR_NOT_FOUND)
    {
        return NRF_SUCCESS;
    }

    switch (p_params->access_type)
    {
        case ES_FLASH_ACCESS_READ:
            err_code = fds_record_open(&desc, &record);
            RETURN_IF_ERROR(err_code);

            memcpy(p_params->p_data, record.p_data, p_params->size_bytes);

            err_code = fds_record_close(&desc);
            RETURN_IF_ERROR(err_code);

            break;

        case ES_FLASH_ACCESS_WRITE:
            memcpy(p_params->p_data_buf, p_params->p_data, p_params->size_bytes);

            record_to_write.data.length_words = (p_params->size_bytes +3) / 4;
            record_to_write.key               = p_params->record_key;

            if (err_code == FDS_ERR_NOT_FOUND)
            {
                err_code = fds_record_write(&desc, &record_to_write);
            }

            else
            {
                err_code = fds_record_update(&desc, &record_to_write);
            }

            RETURN_IF_ERROR(err_code);
            m_num_pending_ops++;
            break;

        case ES_FLASH_ACCESS_CLEAR:
            err_code = fds_record_delete(&desc);
            RETURN_IF_ERROR(err_code);
            m_num_pending_ops++;
            break;

        default:
            break;
    }
    return NRF_SUCCESS;
}


ret_code_t es_flash_access_lock_key(uint8_t * p_lock_key, es_flash_access_t access_type)
{
    flash_access_params_t params = {.record_key  = RECORD_KEY_LOCK_KEY,
                                    .file_id     = FILE_ID_ES_FLASH_LOCK_KEY,
                                    .p_data_buf  = lock_key_buf,
                                    .p_data      = (uint8_t *)p_lock_key,
                                    .size_bytes  = SIZE_OF_LOCK_KEY,
                                    .access_type = access_type};

    return access_flash_data(&params);
}


ret_code_t es_flash_access_beacon_config(es_flash_beacon_config_t * p_config,
                                         es_flash_access_t          access_type)
{
    ret_code_t err_code;

    flash_access_params_t params = {.record_key  = RECORD_KEY_BEACON_CONFIG,
                                    .file_id     = FILE_ID_ES_FLASH,
                                    .p_data_buf  = beacon_config_buf,
                                    .p_data      = (uint8_t *)p_config,
                                    .size_bytes  = sizeof(es_flash_beacon_config_t),
                                    .access_type = access_type};

    err_code = access_flash_data(&params);

    return err_code;
}


ret_code_t es_flash_access_slot_configs(uint8_t           slot_no,
                                        es_slot_t       * p_slot,
                                        es_flash_access_t access_type)
{
    if (slot_no >= APP_MAX_ADV_SLOTS)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    flash_access_params_t params = {.record_key  = RECORD_KEY_SLOTS[slot_no],
                                    .file_id     = FILE_ID_ES_FLASH,
                                    .p_data_buf  = slots_buf_p[slot_no],
                                    .p_data      = (uint8_t *)p_slot,
                                    .size_bytes  = sizeof(es_slot_t),
                                    .access_type = access_type};

    return access_flash_data(&params);
}


ret_code_t es_flash_access_flags(es_flash_flags_t * p_flags, es_flash_access_t access_type)
{
    flash_access_params_t params = {.record_key  = RECORD_KEY_FLAGS,
                                    .file_id     = FILE_ID_ES_FLASH,
                                    .p_data_buf  = flash_flags_buf,
                                    .p_data      = (uint8_t *)p_flags,
                                    .size_bytes  = sizeof(es_flash_flags_t),
                                    .access_type = access_type};

    return access_flash_data(&params);
}


ret_code_t es_flash_factory_reset(void)
{
    // Delete everything except the lock key:
    ret_code_t ret_code = fds_file_delete(FILE_ID_ES_FLASH);

    return ret_code;
}


uint32_t es_flash_num_pending_ops(void)
{
    return m_num_pending_ops;
}


void es_flash_on_ble_evt(ble_evt_t const * p_evt)
{
    switch (p_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            m_conn_handle = p_evt->evt.common_evt.conn_handle;
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            m_conn_handle = BLE_CONN_HANDLE_INVALID;
            if (m_factory_reset_done)
            {
                m_factory_reset_done = false;
                (void)sd_nvic_SystemReset();
            }
            break;
    }
}


ret_code_t es_flash_init(void)
{
    ret_code_t err_code;

    m_num_pending_ops = 1; // Will be set to 0 when getting FDS_EVT_INIT event

    m_conn_handle = BLE_CONN_HANDLE_INVALID;

    m_factory_reset_done = false;

    err_code = fds_register(fds_cb);
    RETURN_IF_ERROR(err_code);

    err_code = fds_init();
    RETURN_IF_ERROR(err_code);

    return NRF_SUCCESS;
}

