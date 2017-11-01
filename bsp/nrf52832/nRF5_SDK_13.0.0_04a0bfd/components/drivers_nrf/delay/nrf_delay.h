/**
 * Copyright (c) 2011 - 2017, Nordic Semiconductor ASA
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

#ifndef _NRF_DELAY_H
#define _NRF_DELAY_H

#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_FREQ_16MHz (16000000UL)

#ifdef NRF52_SERIES
  #define CPU_FREQ_64MHz
#endif

/**
 * @brief Function for delaying execution for number of microseconds.
 *
 * @note NRF52 has instruction cache and because of that delay is not precise.
 *
 * @param number_of_us
 *
 */
/*lint --e{438, 522, 40, 10, 563} "Variable not used" "Function lacks side-effects" */
__STATIC_INLINE void nrf_delay_us(uint32_t number_of_us);


/**
 * @brief Function for delaying execution for number of miliseconds.
 *
 * @note NRF52 has instruction cache and because of that delay is not precise.
 *
 * @note Function internally calls @ref nrf_delay_us so the maximum delay is the
 * same as in case of @ref nrf_delay_us, approx. 71 minutes.
 *
 * @param number_of_ms
 *
 */

/*lint --e{438, 522, 40, 10, 563} "Variable not used" "Function lacks side-effects" */
__STATIC_INLINE void nrf_delay_ms(uint32_t number_of_ms);

#if defined ( __CC_ARM   )
__STATIC_INLINE void nrf_delay_us(uint32_t number_of_us)
{
    if(!number_of_us)
        return;
__asm
    {
loop:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    CMP SystemCoreClock, CLOCK_FREQ_16MHz
    BEQ cond
    NOP
#ifdef  CPU_FREQ_64MHz
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
#endif //CPU_FREQ_64MHz
cond:
    SUBS number_of_us,number_of_us, #1
    BNE    loop
    }
}

#elif defined ( _WIN32 ) || defined ( __unix ) || defined( __APPLE__ )


#ifndef CUSTOM_NRF_DELAY_US
__STATIC_INLINE void nrf_delay_us(uint32_t number_of_us)
{}
#endif

#elif defined ( __GNUC__ ) || ( __ICCARM__ )

__STATIC_INLINE void nrf_delay_us(uint32_t number_of_us)
{
    const uint32_t clock16MHz = CLOCK_FREQ_16MHz;
    if (number_of_us)
    {
__ASM volatile (
#if ( defined(__GNUC__) && (__CORTEX_M == (0x00U) ) )
        ".syntax unified\n"
#endif
"1:\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " CMP %[SystemCoreClock],%[clock16MHz]\n"
       " BEQ.n 2f\n"
       " NOP\n"
#ifdef  CPU_FREQ_64MHz
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
       " NOP\n"
#endif //CPU_FREQ_64MHz
"2:\n"
       " SUBS %0, %0, #1\n"
       " BNE.n 1b\n"
#if __CORTEX_M == (0x00U)
#ifdef __GNUC__
    ".syntax divided\n"
#endif
    :"+l" (number_of_us) :
#else
    :"+r" (number_of_us) :
#endif
                [SystemCoreClock] "r" (SystemCoreClock),
                [clock16MHz] "r" (clock16MHz)
        );
#ifdef __ICCARM__
        __DMB();
#endif
    }
}
#endif

__STATIC_INLINE void nrf_delay_ms(uint32_t number_of_ms)
{
    nrf_delay_us(1000*number_of_ms);
}


#ifdef __cplusplus
}
#endif

#endif
