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
#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_FSTORAGE)

#include "nrf_fstorage_nvmc.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "nrf_nvmc.h"
#include "nrf_atomic.h"


static nrf_fstorage_info_t m_flash_info =
{
#if   defined(NRF51)
    .erase_unit = 1024,
#elif defined(NRF52_SERIES)
    .erase_unit = 4096,
#endif
    .program_unit = 4,
    .rmap         = true,
    .wmap         = false,
};


 /* An operation initiated by fstorage is ongoing. */
static nrf_atomic_flag_t m_flash_operation_ongoing;


/* Send event to the event handler. */
static void event_send(nrf_fstorage_t        const * p_fs,
                       nrf_fstorage_evt_id_t         evt_id,
                       void const *                  p_src,
                       uint32_t                      addr,
                       uint32_t                      len,
                       void                        * p_param)
{
    if (p_fs->evt_handler == NULL)
    {
        /* Nothing to do. */
        return;
    }

    nrf_fstorage_evt_t evt =
    {
        .result  = NRF_SUCCESS,
        .id      = evt_id,
        .addr    = addr,
        .p_src   = p_src,
        .len     = len,
        .p_param = p_param,
    };

    p_fs->evt_handler(&evt);
}


static ret_code_t init(nrf_fstorage_t * p_fs, void * p_param)
{
    UNUSED_PARAMETER(p_param);

    p_fs->p_flash_info = &m_flash_info;

    return NRF_SUCCESS;
}


static ret_code_t uninit(nrf_fstorage_t * p_fs, void * p_param)
{
    UNUSED_PARAMETER(p_fs);
    UNUSED_PARAMETER(p_param);

    (void) nrf_atomic_flag_clear(&m_flash_operation_ongoing);

    return NRF_SUCCESS;
}


static ret_code_t read(nrf_fstorage_t const * p_fs, uint32_t src, void * p_dest, uint32_t len)
{
    UNUSED_PARAMETER(p_fs);

    memcpy(p_dest, (uint32_t*)src, len);

    return NRF_SUCCESS;
}


static ret_code_t write(nrf_fstorage_t const * p_fs,
                        uint32_t               dest,
                        void           const * p_src,
                        uint32_t               len,
                        void                 * p_param)
{
    if (nrf_atomic_flag_set_fetch(&m_flash_operation_ongoing))
    {
        return NRF_ERROR_BUSY;
    }

    nrf_nvmc_write_words(dest, (uint32_t*)p_src, (len / m_flash_info.program_unit));

    /* Clear the flag before sending the event, to allow API calls in the event context. */
    (void) nrf_atomic_flag_clear(&m_flash_operation_ongoing);

    event_send(p_fs, NRF_FSTORAGE_EVT_WRITE_RESULT, p_src, dest, len, p_param);

    return NRF_SUCCESS;
}


static ret_code_t erase(nrf_fstorage_t const * p_fs,
                        uint32_t               page_addr,
                        uint32_t               len,
                        void                 * p_param)
{
    uint32_t progress = 0;

    if (nrf_atomic_flag_set_fetch(&m_flash_operation_ongoing))
    {
        return NRF_ERROR_BUSY;
    }

    while (progress != len)
    {
        nrf_nvmc_page_erase(page_addr + (progress * m_flash_info.erase_unit));
        progress++;
    }

    /* Clear the flag before sending the event, to allow API calls in the event context. */
    (void) nrf_atomic_flag_clear(&m_flash_operation_ongoing);

    event_send(p_fs, NRF_FSTORAGE_EVT_ERASE_RESULT, NULL, page_addr, len, p_param);

    return NRF_SUCCESS;
}


static uint8_t const * rmap(nrf_fstorage_t const * p_fs, uint32_t addr)
{
    UNUSED_PARAMETER(p_fs);

    return (uint8_t*)addr;
}


static uint8_t * wmap(nrf_fstorage_t const * p_fs, uint32_t addr)
{
    UNUSED_PARAMETER(p_fs);
    UNUSED_PARAMETER(addr);

    /* Not supported. */
    return NULL;
}


static bool is_busy(nrf_fstorage_t const * p_fs)
{
    UNUSED_PARAMETER(p_fs);

    return m_flash_operation_ongoing;
}


/* The exported API. */
nrf_fstorage_api_t nrf_fstorage_nvmc =
{
    .init    = init,
    .uninit  = uninit,
    .read    = read,
    .write   = write,
    .erase   = erase,
    .rmap    = rmap,
    .wmap    = wmap,
    .is_busy = is_busy
};


#endif // NRF_FSTORAGE_ENABLED
