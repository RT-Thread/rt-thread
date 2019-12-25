/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef HAL_EXCEPTIONS_H_INCLUDED
#define HAL_EXCEPTIONS_H_INCLUDED

#include <stdint.h>

/**
 * @defgroup hal_15_4_nrf52 Chip-specific library interface
 * @ingroup hal_15_4
 *
 * @defgroup hal_nrf52_exceptions HAL exceptions
 * @ingroup hal_15_4_nrf52
 * @{
 */

/** @brief Size of stack dump in 4-byte words.*/
#define HAL_EXCEPTIONS_DUMP_SIZE            16
/** @brief Defines where to put a '\n' in stack dump.
 *
 * This value defines power of 2 items in one row.
 * E.g. 3 gives 2 ^ 3 = 8 items in a row.*/
#define HAL_EXCEPTIONS_ITEMS_IN_LINE        3

/** @brief This structure holds values of fault status registers.*/
typedef struct
{
    uint32_t CFSR; /*!< Configurable Fault Status Register.*/
    uint32_t HFSR; /*!< HardFault Status Register.*/
    uint32_t DFSR; /*!< Debug Fault Status Register.*/
    uint32_t AFSR; /*!< Auxiliary Fault Status Register.*/
} hal_exceptions_status_registers_t;

/** @brief This structure is put into dump monitor port and holds values of said
 * registers when exception has happen.*/
typedef struct
{
    uint32_t  R0;        /**< Register R0 (Argument 1 / word result).*/
    uint32_t  R1;        /**< Register R1 (Argument 2 / double-word result).*/
    uint32_t  R2;        /**< Register R2 (Argument 3).*/
    uint32_t  R3;        /**< Register R3 (Argument 4).*/
    uint32_t  R12;       /**< Register R12 (Scratch register (corruptible)).*/
    uint32_t  LR;        /**< Link register (R14).*/
    uint32_t  PC;        /**< Program counter (R15).*/
    uint32_t  PSR;       /**< Combined processor status register.*/
    uint32_t* FP;        /**< Value of register, which may be used as Frame Pointer.*/
} hal_exceptions_dump_t;

/** @} */

#endif // HAL_EXCEPTIONS_H_INCLUDED
