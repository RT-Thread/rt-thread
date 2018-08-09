/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_SDH_SOC)

#include "nrf_sdh_soc.h"

#include "nrf_sdh.h"
#include "nrf_soc.h"
#include "app_error.h"


#define NRF_LOG_MODULE_NAME nrf_sdh_soc
#if NRF_SDH_SOC_LOG_ENABLED
    #define NRF_LOG_LEVEL       NRF_SDH_SOC_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  NRF_SDH_SOC_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR NRF_SDH_SOC_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // NRF_SDH_SOC_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


// Create section set "sdh_soc_observers".
NRF_SECTION_SET_DEF(sdh_soc_observers, nrf_sdh_soc_evt_observer_t, NRF_SDH_SOC_OBSERVER_PRIO_LEVELS);


/**@brief   Function for polling SoC events.
 *
 * @param[in]   p_context   Context of the observer.
 */
static void nrf_sdh_soc_evts_poll(void * p_context)
{
    ret_code_t ret_code;

    UNUSED_VARIABLE(p_context);

    while (true)
    {
        uint32_t evt_id;

        ret_code = sd_evt_get(&evt_id);
        if (ret_code != NRF_SUCCESS)
        {
            break;
        }

        NRF_LOG_DEBUG("SoC event: 0x%x.", evt_id);

        // Forward the event to SoC observers.
        nrf_section_iter_t  iter;
        for (nrf_section_iter_init(&iter, &sdh_soc_observers);
             nrf_section_iter_get(&iter) != NULL;
             nrf_section_iter_next(&iter))
        {
            nrf_sdh_soc_evt_observer_t * p_observer;
            nrf_sdh_soc_evt_handler_t    handler;

            p_observer = (nrf_sdh_soc_evt_observer_t *) nrf_section_iter_get(&iter);
            handler    = p_observer->handler;

            handler(evt_id, p_observer->p_context);
        }
    }

    if (ret_code != NRF_ERROR_NOT_FOUND)
    {
        APP_ERROR_HANDLER(ret_code);
    }
}


NRF_SDH_STACK_OBSERVER(m_nrf_sdh_soc_evts_poll, NRF_SDH_SOC_STACK_OBSERVER_PRIO) =
{
    .handler   = nrf_sdh_soc_evts_poll,
    .p_context = NULL,
};

#endif // NRF_MODULE_ENABLED(NRF_SDH_SOC)
