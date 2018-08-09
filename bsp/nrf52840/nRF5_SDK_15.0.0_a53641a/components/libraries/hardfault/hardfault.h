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
#ifndef HARDFAULT_H__
#define HARDFAULT_H__
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup hardfault_default HardFault exception
 * @{
 * @brief Default HardFault exception implementation.
 * @ingroup app_common
 */

/**
 * @brief Contents of the stack.
 *
 * This structure is used to re-create the stack layout after a HardFault exception was raised.
 */
typedef struct HardFault_stack
{
    uint32_t r0;  ///< R0 register.
    uint32_t r1;  ///< R1 register.
    uint32_t r2;  ///< R2 register.
    uint32_t r3;  ///< R3 register.
    uint32_t r12; ///< R12 register.
    uint32_t lr;  ///< Link register.
    uint32_t pc;  ///< Program counter.
    uint32_t psr; ///< Program status register.
} HardFault_stack_t;

/**
 * @brief Function for processing HardFault exceptions.
 *
 * An application that needs to process HardFault exceptions should provide an implementation of this function.
 * It will be called from the HardFault handler.
 * If no implementation is provided, the library uses a default one, which just restarts the MCU.
 *
 * @note If the DEBUG_NRF macro is defined, the software breakpoint is set just before the call
 *       to this function.
 *
 * @param p_stack Pointer to the stack bottom.
 *                This pointer might be NULL if the HardFault was called when the main stack was
 *                the active stack and a stack overrun is detected.
 *                In such a situation, the stack pointer is reinitialized to the default position,
 *                and the stack content is lost.
 */
void HardFault_process(HardFault_stack_t * p_stack);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HARDFAULT_H__ */
