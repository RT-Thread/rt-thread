/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(SYSTICK)
#include "nrf_drv_systick.h"
#include "nrf_systick.h"
#include "nrf.h"
#include "nrf_assert.h"

/**
 * @brief Maximum number of ticks to delay
 *
 * The maximum number of ticks should be much lower than
 * Physical maximum count of the SysTick timer.
 * It is dictated by the fact that it would be impossible to detect delay
 * properly when the timer value warps around the starting point.
 */
#define NRF_DRV_SYSTICK_TICKS_MAX (NRF_SYSTICK_VAL_MASK / 2UL)

/**
 * @brief Number of milliseconds in a second
 */
#define NRF_DRV_SYSTICK_MS (1000UL)

/**
 * @brief Number of microseconds in a second
 */
#define NRF_DRV_SYSTICK_US (1000UL * NRF_DRV_SYSTICK_MS)

/**
 * @brief Number of milliseconds to wait in single loop
 *
 * Constant used by @ref nrd_drv_systick_delay_ms function
 * to split waiting into loops and rest.
 *
 * It describes the number of milliseconds to wait in single loop.
 *
 * See @ref nrf_drv_systick_delay_ms source code for details.
 */
#define NRF_DRV_SYSTICK_MS_STEP (64U)

/**
 * @brief Checks if the given time is in correct range
 *
 * Function tests given time is not to big for this library.
 * Assertion is used for testing.
 *
 * @param us Time in microseconds to check
 */
#define NRF_DRV_SYSTICK_ASSERT_TIMEOUT(us) \
    ASSERT(us <= (NRF_DRV_SYSTICK_TICKS_MAX / ((SystemCoreClock) / NRF_DRV_SYSTICK_US)));

/**
 * @brief Function that converts microseconds to ticks
 *
 * Function converts from microseconds to CPU ticks.
 *
 * @param us Number of microseconds
 *
 * @return Number of ticks
 *
 * @sa nrf_drv_systick_ms_tick
 */
static inline uint32_t nrf_drv_systick_us_tick(uint32_t us)
{
    return us * ((SystemCoreClock) / NRF_DRV_SYSTICK_US);
}

/**
 * @brief Function that converts milliseconds to ticks
 *
 * Function converts from milliseconds to CPU ticks.
 *
 * @param us Number of milliseconds
 *
 * @return Number of ticks
 *
 * @sa nrf_drv_systick_us_tick
 */
static inline uint32_t nrf_drv_systick_ms_tick(uint32_t ms)
{
    return ms * ((SystemCoreClock) / NRF_DRV_SYSTICK_MS);
}

void nrf_drv_systick_init(void)
{
    nrf_systick_load_set(NRF_SYSTICK_VAL_MASK);
    nrf_systick_csr_set(
        NRF_SYSTICK_CSR_CLKSOURCE_CPU |
        NRF_SYSTICK_CSR_TICKINT_DISABLE |
        NRF_SYSTICK_CSR_ENABLE);
}

void nrf_drv_systick_get(nrf_drv_systick_state_t * p_state)
{
    p_state->time = nrf_systick_val_get();
}

bool nrf_drv_systick_test(nrf_drv_systick_state_t const * p_state, uint32_t us)
{
    NRF_DRV_SYSTICK_ASSERT_TIMEOUT(us);

    const uint32_t diff = NRF_SYSTICK_VAL_MASK & ((p_state->time) - nrf_systick_val_get());
    return (diff >= nrf_drv_systick_us_tick(us));
}

void nrf_drv_systick_delay_ticks(uint32_t ticks)
{
    ASSERT(ticks <= NRF_DRV_SYSTICK_TICKS_MAX)

    const uint32_t start = nrf_systick_val_get();
    while((NRF_SYSTICK_VAL_MASK & (start - nrf_systick_val_get())) < ticks)
    {
        /* Nothing to do */
    }
}

void nrf_drv_systick_delay_us(uint32_t us)
{
    NRF_DRV_SYSTICK_ASSERT_TIMEOUT(us);
    nrf_drv_systick_delay_ticks(nrf_drv_systick_us_tick(us));
}

void nrf_drv_systick_delay_ms(uint32_t ms)
{
    uint32_t n = ms / NRF_DRV_SYSTICK_MS_STEP;
    uint32_t r = ms % NRF_DRV_SYSTICK_MS_STEP;
    while(0 != (n--))
    {
        nrf_drv_systick_delay_ticks(nrf_drv_systick_ms_tick(NRF_DRV_SYSTICK_MS_STEP));
    }
    nrf_drv_systick_delay_ticks(nrf_drv_systick_ms_tick(r));
}

#endif // NRF_MODULE_ENABLED(SYSTICK)
