/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef NRF_SERIAL_FLASH_PARAMS_H__
#define NRF_SERIAL_FLASH_PARAMS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk_common.h"

/**@file
 *
 * @defgroup nrf_serial_flash_params Serial flash memory parameters
 * @ingroup nrf_block_dev
 * @{
 *
 */

/**
 * @brief Serial flash memory parameters
 *  */
typedef struct {
    uint8_t  read_id[3];    //!< Read identification command (0x9F) result
    uint8_t  capabilities;  //!< Serial flash memory capabilities
    uint32_t size;          //!< Serial flash memory size (bytes)
    uint32_t erase_size;    //!< Serial flash memory erase unit size (bytes)
    uint32_t program_size;  //!< Serial flash memory program size (bytes)
} nrf_serial_flash_params_t;


/**
 * @brief Returns serial flash memory identification descriptor
 *
 * @param p_read_params     Memory read identification command result
 *
 * @return Serial flash memory descriptor (NULL if not found)
 * */
nrf_serial_flash_params_t const * nrf_serial_flash_params_get(const uint8_t * p_read_params);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* NRF_SERIAL_FLASH_PARAMS_H__ */
