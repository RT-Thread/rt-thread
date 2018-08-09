/**
 * Copyright (c) 2009 - 2018, Nordic Semiconductor ASA
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
#ifndef SDIO_H
#define SDIO_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file
* @brief 2-wire serial interface driver (compatible with ADNS2080 mouse sensor driver)
*
*
* @defgroup nrf_drivers_sdio SDIO driver
* @{
* @ingroup nrf_drivers
* @brief 2-wire serial interface driver.
*/

/**
 * @brief Function for initializing 2-wire serial interface and trying to handle stuck slaves.
 *
 */
void sdio_init(void);

/**
 * @brief Function for reading a byte over 2-wire serial interface.
 *
 * Developer needs to implement this function in a way that suits the hardware.
 * @param address Register address to read from
 * @return Byte read
 */
uint8_t sdio_read_byte(uint8_t address);

/**
 * @brief Function for reading several bytes over 2-wire serial interface using burst mode.
 *
 * Developer needs to implement this function in a way that suits the hardware.
 * @param target_buffer Buffer location to store read bytes to
 * @param target_buffer_size Bytes allocated for target_buffer
 */
void sdio_read_burst(uint8_t *target_buffer, uint8_t target_buffer_size);

/**
 * @brief Function for writing a byte over 2-wire serial interface.
 *
 * Developer needs to implement this function in a way that suits the hardware.
 * @param address Register address to write to
 * @param data_byte Data byte to write
 */
void sdio_write_byte(uint8_t address, uint8_t data_byte);

/**
 *@}
 **/

/*lint --flb "Leave library region" */

#ifdef __cplusplus
}
#endif

#endif
