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
#if NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)

#include "nrf.h"
#include "cc310_bl_backend_shared.h"
#include "nrf_crypto_error.h"


void cc310_bl_backend_enable(void)
{
    // Enable the cryptocell hardware
    NRF_CRYPTOCELL->ENABLE = 1;

#if defined(NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED == 1)

    // Enable the CryptoCell IRQ
    NVIC_EnableIRQ(CRYPTOCELL_IRQn);

#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED == 0)

    // Do nothing

#else

    #warning NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif

}


void cc310_bl_backend_disable(void)
{
    // Enable the cryptocell hardware
    NRF_CRYPTOCELL->ENABLE = 0;

#if defined(NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED == 1)

    // Disable the CryptoCell IRQ
    NVIC_DisableIRQ(CRYPTOCELL_IRQn);

#elif defined(NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED) && (NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED == 0)

    // Do nothing

#else

    #warning NRF_CRYPTO_BACKEND_CC310_BL_INTERRUPTS_ENABLED define not found in sdk_config.h (Is the sdk_config.h valid?).

#endif

}


#endif // NRF_MODULE_ENABLED(NRF_CRYPTO) && NRF_MODULE_ENABLED(NRF_CRYPTO_BACKEND_CC310_BL)
