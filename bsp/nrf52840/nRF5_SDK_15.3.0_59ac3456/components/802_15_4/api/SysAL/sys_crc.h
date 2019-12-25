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
#ifndef SYS_CRC_H_INCLUDED
#define SYS_CRC_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

/** @file
 * This file contains declarations of the CRC computing routines and necessary macros/types.
 *
 * @defgroup sys_crc System CRC API
 * @ingroup sys_15_4
 * @{
 * @brief Module to declare System CRC API.
 * @details The CRC module implements a set of routines to compute the 16-bit CRC value for octet arrays.
 */

/**
 * @brief Defines an initial value for the CRC sum.
 */
#define SYS_CRC_INIT              0

/**
 * @brief CRC value type. This module uses 16-bit CRC.
 */
typedef uint16_t sys_crc_t;

/**
 * @brief Function for computing CRC value for given data.
 *
 * @param[in] p_data   Pointer to data to compute.
 * @param[in] length   Length of data.
 *
 * @return Returns the CRC value for input data.
 */
sys_crc_t sys_crc_calc(const uint8_t * p_data, size_t length);

/**
 * @brief Function for updating the CRC value taking into the account the previously counted value.
 *
 * @details This function is used when input data is represented by several pieces.
 * Consequently, a call to this function for each piece will give a correct
 * total CRC value.
 *
 * @param[in] current_crc  Previously counted CRC value. Should be SYS_CRC_INIT for the first piece.
 * @param[in] p_data       Pointer to the current piece of data.
 * @param[in] length       Length of the current piece of data.
 *
 * @return Returns the updated CRC value.
 */
sys_crc_t sys_crc_continue(sys_crc_t current_crc, const uint8_t * p_data, size_t length);

/** @} */

#endif /* SYS_CRC_H_INCLUDED */
