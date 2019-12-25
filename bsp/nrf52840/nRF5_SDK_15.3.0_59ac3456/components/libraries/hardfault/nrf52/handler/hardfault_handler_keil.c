/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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


//lint -save -e27

__ASM void HardFault_Handler(void)
{
    PRESERVE8
    EXTERN HardFault_c_handler
    EXTERN |STACK$$Base|
    EXTERN |STACK$$Limit|

    ldr r3, =HardFault_c_handler
    tst lr, #4

    /* PSP is quite simple and does not require additional handler */
    itt ne
    mrsne r0, psp
    /* Jump to the handler, do not store LR - returning from handler just exits exception */
    bxne  r3

    /* Processing MSP requires stack checking */
    mrs r0, msp

    ldr   r1, =|STACK$$Limit|
    ldr   r2, =|STACK$$Base|

    /* MSP is in the range of the stack area */
    cmp   r0, r1
    bhi   HardFault_MoveSP
    cmp   r0, r2
    bhi   HardFault_Handler_Continue

HardFault_MoveSP
    mov   sp, r1
    mov   r0, #0

HardFault_Handler_Continue
    bx r3

    ALIGN
}

//lint -restore
#endif //NRF_MODULE_ENABLED(HARDFAULT_HANDLER)
