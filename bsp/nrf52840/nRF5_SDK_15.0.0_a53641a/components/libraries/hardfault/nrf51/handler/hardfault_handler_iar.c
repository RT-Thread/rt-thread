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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(HARDFAULT_HANDLER)
#include <stdint.h>
#include "compiler_abstraction.h"

#pragma section = "CSTACK"
extern void HardFault_c_handler( uint32_t * );

__stackless void HardFault_Handler(void);

__stackless void HardFault_Handler(void)
{
    __ASM volatile(
    "   ldr   r0, 100f                         \n"
    "   cmp   r0, lr                           \n"
    "   bne   1f                               \n"
    /* Reading PSP into R0 */
    "   mrs   r0, PSP                          \n"
    "   b     3f                               \n"
    "1:                                        \n"
    /* Reading MSP into R0 */
    "   mrs   r0, MSP                          \n"
    /* -----------------------------------------------------------------
     * If we have selected MSP check if we may use stack safetly.
     * If not - reset the stack to the initial value. */
    "   ldr   r1, 101f                         \n"
    "   ldr   r2, 102f                         \n"

    /* MSP is in the range of the stack area */
    "   cmp   r0, r1                           \n"
    "   bhi   2f                               \n"
    "   cmp   r0, r2                           \n"
    "   bhi   3f                               \n"
    /* ----------------------------------------------------------------- */
    "2:                                        \n"
    "   mov   SP, r1                           \n"
    "   movs  r0, #0                           \n"

    "3:                                        \n"
    "   ldr r3, 103f                           \n"
    "   bx r3                                  \n"

    "DATA                                      \n"
    "100:                                      \n"
    "   DC32 0xFFFFFFFD                        \n"
    "101:                                      \n"
    "   DC32 %c0                               \n"
    "102:                                      \n"
    "   DC32 %c1                               \n"
    "103:                                      \n"
    "   DC32 %c2                               \n"
    : /* Outputs */
    : /* Inputs */
    "i"(__section_end("CSTACK")),
    "i"(__section_begin("CSTACK")),
    "i"(&HardFault_c_handler)
    );
}
#endif //NRF_MODULE_ENABLED(HARDFAULT_HANDLER)
