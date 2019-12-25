/**
 * Copyright (c) 2009 - 2019, Nordic Semiconductor ASA
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
#ifndef DS1624_H
#define DS1624_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file
* @brief DS1624 digital temperature sensor driver.
*
*
* @defgroup nrf_drivers_ds1624 DS1624 digital temperature sensor driver
* @{
* @ingroup ext_drivers
* @brief DS1624 digital temperature sensor driver.
*/

/**
 * @brief Function for initializing DS1624 temperature sensor to 1-shot mode.
 *
 * @note Before calling this function, you must initialize twi_master first.
 *
 * @param device_address Bits [2:0] for the device address. All other bits must be zero.
 * @return
 * @retval true If communication succeeded with the device.
 * @retval false If communication failed with the device.
 */
bool ds1624_init(uint8_t device_address);

/**
 * @brief Function for reading temperature from the sensor.
 *
 * @param temperature_in_celcius Memory location to store temperature in full celcius degrees.
 * @param temperature_fraction Memory location to store temperature's fraction part in 0.03125 celcius degree increments.
 * @return
 * @retval true Temperature was successfully read
 * @retval false Temperature reading failed or conversion was not yet complete
 */
bool ds1624_temp_read(int8_t *temperature_in_celcius, int8_t *temperature_fraction);

/**
 * @brief Function for starting temperature conversion. Valid data will be available 400 - 1000 milliseconds after exiting this function.
 *
 * @return
 * @retval true Temperature conversion started.
 * @retval false Temperature converion failed to start.
*/
bool ds1624_start_temp_conversion(void);

/**
 * @brief Function for checking if temperature conversion is done.
 *
 * @return
 * @retval true Temperature conversion done.
 * @retval false Temperature converion still in progress.
*/
bool ds1624_is_temp_conversion_done(void);

/**
 *@}
 **/

/*lint --flb "Leave library region" */

#ifdef __cplusplus
}
#endif

#endif
