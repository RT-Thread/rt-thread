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

#ifndef NFC_PLATFORM_H__
#define NFC_PLATFORM_H__

/** @file
 *
 * @addtogroup nfc_api
 *
 * @defgroup nfc_platform Platform-specific module for NFC
 * @{
 * @ingroup nfc_api
 * @brief @tagAPI52 Platform-specific module for Near Field Communication Tag (NFCT).
 *
 * This module is used to set up platform-specific components that are required for NFC, and to
 * activate NFCT peripheral when all necessary conditions are fulfilled.
 *
 * @note Before the NFCT peripheral enters the ACTIVATED state, the HFXO must be running. To fulfill
 *       this requirement, this module uses the clock management module.
 *
 */

#include "nrfx_nfct.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function for initializing platform-specific modules required by NFC.
 *
 * This function sets up clock managing interface and other platform specific components
 * that are required for NFC.
 *
 * @retval NRFX_SUCCESS If the NFC module is initialized successfully. If one
 *                      of the arguments is invalid, an error code is returned.
 */
nrfx_err_t nfc_platform_setup(void);


/**
 * @brief Function for handling NFCT events that require platform-specific actions.
 *
 * This function is used by the NFC platform module to observe NFC events. This event flow is
 * necessary to track in order to determine when HFXO must be running and when the NFCT peripheral must
 * be activated.
 *
 * @param[in] p_event NFCT driver event.
 */
void nfc_platform_event_handler(nrfx_nfct_evt_t const * p_event);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* NFC_PLATFORM_H__ */

