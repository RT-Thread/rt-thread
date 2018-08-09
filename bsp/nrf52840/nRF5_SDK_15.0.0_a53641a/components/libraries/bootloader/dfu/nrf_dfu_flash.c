/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#include "nrf_dfu_flash.h"
#include "nrf_dfu_types.h"

#include "nrf_fstorage.h"
#include "nrf_fstorage_sd.h"
#include "nrf_fstorage_nvmc.h"


#define NRF_LOG_MODULE_NAME nrf_dfu_flash
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


void dfu_fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);


NRF_FSTORAGE_DEF(nrf_fstorage_t m_fs) =
{
    .evt_handler = dfu_fstorage_evt_handler,
    .start_addr  = MBR_SIZE,
    .end_addr    = BOOTLOADER_SETTINGS_ADDRESS + BOOTLOADER_SETTINGS_PAGE_SIZE
};

static uint32_t m_flash_operations_pending;

void dfu_fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{
    if (NRF_LOG_ENABLED && (m_flash_operations_pending > 0))
    {
        m_flash_operations_pending--;
    }

    if (p_evt->result == NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("Flash %s success: addr=%p, pending %d",
                      (p_evt->id == NRF_FSTORAGE_EVT_WRITE_RESULT) ? "write" : "erase",
                      p_evt->addr, m_flash_operations_pending);
    }
    else
    {
        NRF_LOG_DEBUG("Flash %s failed (0x%x): addr=%p, len=0x%x bytes, pending %d",
                      (p_evt->id == NRF_FSTORAGE_EVT_WRITE_RESULT) ? "write" : "erase",
                      p_evt->result, p_evt->addr, p_evt->len, m_flash_operations_pending);
    }

    if (p_evt->p_param)
    {
        //lint -save -e611 (Suspicious cast)
        ((nrf_dfu_flash_callback_t)(p_evt->p_param))((void*)p_evt->p_src);
        //lint -restore
    }
}


ret_code_t nrf_dfu_flash_init(bool sd_irq_initialized)
{
    nrf_fstorage_api_t * p_api_impl;

    /* Setup the desired API implementation. */
#ifdef BLE_STACK_SUPPORT_REQD
    if (sd_irq_initialized)
    {
        NRF_LOG_DEBUG("Initializing nrf_fstorage_sd backend.");
        p_api_impl = &nrf_fstorage_sd;
    }
    else
#endif
    {
        NRF_LOG_DEBUG("Initializing nrf_fstorage_nvmc backend.");
        p_api_impl = &nrf_fstorage_nvmc;
    }

    return nrf_fstorage_init(&m_fs, p_api_impl, NULL);
}


ret_code_t nrf_dfu_flash_store(uint32_t                   dest,
                               void               const * p_src,
                               uint32_t                   len,
                               nrf_dfu_flash_callback_t   callback)
{
    ret_code_t rc;

    NRF_LOG_DEBUG("nrf_fstorage_write(addr=%p, src=%p, len=%d bytes), queue usage: %d",
                  dest, p_src, len, m_flash_operations_pending);

    //lint -save -e611 (Suspicious cast)
    rc = nrf_fstorage_write(&m_fs, dest, p_src, len, (void *)callback);
    //lint -restore

    if ((NRF_LOG_ENABLED) && (rc == NRF_SUCCESS))
    {
        m_flash_operations_pending++;
    }
    else
    {
        NRF_LOG_WARNING("nrf_fstorage_write() failed with error 0x%x.", rc);
    }

    return rc;
}


ret_code_t nrf_dfu_flash_erase(uint32_t                 page_addr,
                               uint32_t                 num_pages,
                               nrf_dfu_flash_callback_t callback)
{
    ret_code_t rc;

    NRF_LOG_DEBUG("nrf_fstorage_erase(addr=0x%p, len=%d pages), queue usage: %d",
                  page_addr, num_pages, m_flash_operations_pending);

    //lint -save -e611 (Suspicious cast)
    rc = nrf_fstorage_erase(&m_fs, page_addr, num_pages, (void *)callback);
    //lint -restore

    if ((NRF_LOG_ENABLED) && (rc == NRF_SUCCESS))
    {
        m_flash_operations_pending++;
    }
    else
    {
        NRF_LOG_WARNING("nrf_fstorage_erase() failed with error 0x%x.", rc);
    }

    return rc;
}
