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
#ifndef HAL_ATOMIC_H_INCLUDED
#define HAL_ATOMIC_H_INCLUDED

#include <stdint.h>

/** @file
 * This file contains declarations of the Atomic section routines and necessary types.
 *
 * @defgroup hal_atomic HAL Atomic API
 * @ingroup hal_15_4
 * @{
 * @brief Module to declare HAL Atomic API
 * @details The Atomic module implements atomic section interface. This is made by disabling the global interrupts,
 * which is a hardware dependent feature. The user may call hal_atomic_start() to open an atomic section
 * (disable interrupts) and hal_atomic_end() to exit from the section (restore interrupts). The algorithm
 * supports nesting sections.
 */

typedef volatile uint32_t atomic_t;


/**@brief Enters atomic section.
 *
 * @details Disables global interrupts.
 *
 * @param[in] p_atomic  pointer to buffer to store current value of the status register.
 */
void hal_atomic_start(atomic_t * p_atomic);

/**
 * @brief Exits atomic section
 *
 * @details Restores status register
 *
 * @param[in] p_atomic  pointer to buffer to restore current value of the status register from.
 */
void hal_atomic_end(atomic_t * p_atomic);

/** @} */

#endif // HAL_ATOMIC_H_INCLUDED
