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
#ifndef HARDFAULT_GENHF_H__
#define HARDFAULT_GENHF_H__

#include "compiler_abstraction.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup hardfault_genhf Generating HardFaults for testing
 * @{
 * @brief Macros and functions used to generate a HardFault in a selected place.
 * @ingroup hardfault_default
 *
 * This functionality is meant to be used while testing the @ref hardfault_default library functionality.
 */

/**
 * @brief Function for generating an invalid function pointer HardFault.
 *
 * Function tries to jump into illegal address.
 */
static inline void hardfault_genhf_invalid_fp(void);

/**
 * @brief Function for generating an undefined instruction HardFault.
 *
 * This function places the value in the code area that is not the legal instruction.
 */
static inline void hardfault_genhf_undefined_instr(void);

/**
 * @brief Function for generating an unaligned LDM access HardFault.
 *
 * This function generates fault exception loading values from an unaligned address.
 */
static inline void hardfault_genhf_ldm_align(void);

#if defined( __CC_ARM   )

static inline __ASM void hardfault_genhf_invalid_fp(void)
{
    MOVS r0, #0
    BLX  r0
}

static inline __ASM void hardfault_genhf_undefined_instr(void)
{
    DCI 0xf123
    DCI 0x4567
}

static inline __ASM void hardfault_genhf_ldm_align(void)
{
    MOVS r0,  #1
    LDM  r0!, {r1-r2}
}

#elif defined( __ICCARM__ )

#pragma inline=forced
static inline void hardfault_genhf_invalid_fp(void)
{
    __ASM volatile(
    "    movs r0, #0 \n"
    "    blx  r0     \n"
     );
}

#pragma inline=forced
static inline void hardfault_genhf_undefined_instr(void)
{
    __ASM volatile(
    "DATA           \n"
    "    DC16 0xf123 \n"
    "    DC16 0x4567 \n"
    );
}

#pragma inline=forced
static inline void hardfault_genhf_ldm_align(void)
{
    __ASM volatile(
    "    movs r0,  #1      \n"
    "    ldm  r0!, {r1-r2} \n"
    );
}

#elif defined(  __GNUC__  )

static inline void hardfault_genhf_invalid_fp(void)
{
    __ASM volatile(
    "    .syntax unified  \n"
    "    movs r0, #0 \n"
    "    blx  r0     \n"
     );
}

static inline void hardfault_genhf_undefined_instr(void)
{
    __ASM volatile(
    "    .hword 0xf123 \n"
    "    .hword 0x4567 \n"
    );
}

static inline void hardfault_genhf_ldm_align(void)
{
    __ASM volatile(
    "    .syntax unified  \n"
    "    movs r0,  #1      \n"
    "    ldm  r0!, {r1-r2} \n"
    );
}

#else
#error "Unsupported compiler"
#endif

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* HARDFAULT_GENHF_H__ */
