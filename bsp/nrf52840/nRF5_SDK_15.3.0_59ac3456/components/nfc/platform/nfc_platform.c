/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NFC_PLATFORM)

#include "nfc_platform.h"
#include "nrf_drv_clock.h"

#define NRF_LOG_MODULE_NAME nfc_platform
#if NFC_PLATFORM_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_PLATFORM_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_PLATFORM_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NFC_PLATFORM_DEBUG_COLOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#else // NFC_PLATFORM_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#include "nrf_log.h"
#endif // NFC_PLATFORM_LOG_ENABLED

/* Static data */
static nrf_drv_clock_handler_item_t m_clock_handler_item; /**< Clock event handler item structure. */

/**@brief Function for handling events from the Clock module.
 *
 * @param[in]  event  Clock event.
 *
 */
static inline void clock_event_handler(nrf_drv_clock_evt_type_t event)
{
    switch(event)
    {
        case NRF_DRV_CLOCK_EVT_HFCLK_STARTED:
            /* Activate NFCT only when HFXO is running */
            nrfx_nfct_state_force(NRFX_NFCT_STATE_ACTIVATED);
            break;

        default:
            /* No implementation required */
            break;
    }
}


nrfx_err_t nfc_platform_setup(void)
{
    nrfx_err_t err_code;

    /* Initialize the Clock module for handling high precision clock requests */
    m_clock_handler_item.event_handler = clock_event_handler;
    m_clock_handler_item.p_next        = NULL;

    err_code = nrf_drv_clock_init();
    if (err_code == NRF_ERROR_MODULE_ALREADY_INITIALIZED)
    {
        err_code = NRFX_SUCCESS;
    }
    else if (err_code != NRF_SUCCESS)
    {
        return NRFX_ERROR_INTERNAL;
    }

    NRF_LOG_DEBUG("Utils init");
    return err_code;
}


void nfc_platform_event_handler(nrfx_nfct_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case NRFX_NFCT_EVT_FIELD_DETECTED:
            NRF_LOG_DEBUG("Field detected");
            nrf_drv_clock_hfclk_request(&m_clock_handler_item);
            break;

        case NRFX_NFCT_EVT_FIELD_LOST:
            NRF_LOG_DEBUG("Field lost");
            nrf_drv_clock_hfclk_release();
            break;

        default:
            /* No implementation required */
            break;
    }
}

#endif // NRF_MODULE_ENABLED(NFC_PLATFORM)
