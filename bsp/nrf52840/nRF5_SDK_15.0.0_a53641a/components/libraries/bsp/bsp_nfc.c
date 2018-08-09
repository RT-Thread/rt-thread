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
#include "bsp_nfc.h"
#include "bsp.h"
#include "nrf.h"
#include "app_util_platform.h"

#ifndef BSP_SIMPLE
#define BTN_ACTION_SLEEP          BSP_BUTTON_ACTION_RELEASE    /**< Button action used to put the application into sleep mode. */

ret_code_t bsp_nfc_btn_init(uint32_t sleep_button)
{
    uint32_t err_code = bsp_event_to_button_action_assign(sleep_button,
                                                          BTN_ACTION_SLEEP,
                                                          BSP_EVENT_SLEEP);
    return err_code;
}

ret_code_t bsp_nfc_btn_deinit(uint32_t sleep_button)
{
    uint32_t err_code = bsp_event_to_button_action_assign(sleep_button,
                                                          BTN_ACTION_SLEEP,
                                                          BSP_EVENT_DEFAULT);
    return err_code;
}

ret_code_t bsp_nfc_sleep_mode_prepare(void)
{
#if defined(NFCT_PRESENT)
    // Check if peripheral is not used.
    CRITICAL_REGION_ENTER();
#ifdef NRF52832_XXAA
    if ((*(uint32_t *)0x40005410 & 0x07) == 0)
#else
    if ((NRF_NFCT->NFCTAGSTATE & NFCT_NFCTAGSTATE_NFCTAGSTATE_Msk)
        == NFCT_NFCTAGSTATE_NFCTAGSTATE_Disabled)
#endif // NRF52832_XXAA
    {
        NRF_NFCT->TASKS_SENSE = 1;
    }
    CRITICAL_REGION_EXIT();
    return NRF_SUCCESS;
#else
    return NRF_ERROR_NOT_SUPPORTED;
#endif
}
#endif //BSP_SIMPLE
