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
#ifndef MCP4725_H
#define MCP4725_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>
#include "app_util_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @file
* @brief MCP4725 digital DAC driver.
*
*
* @defgroup mcp4725 MCP4725 digital DAC driver
* @{
* @ingroup ext_drivers
* @brief MCP4725 digital DAC driver.
*/

typedef struct
{
    uint8_t scl_pin;
    uint8_t sda_pin;
}mcp4725_pins_config_t;

/**
 * @brief Function for setting up the driver.
 *
 * @param[in] p_pins_config Pointer to structere holding pins numbers to be used by TWI.
 *
 * @return Values returned by @ref nrfx_twi_init.
 */
ret_code_t mcp4725_setup(mcp4725_pins_config_t const * p_pins_config);


/**
 * @brief Function for setting new value to DAC.
 *
 * @param[in] val               12-bit value. Base on it voltage is set (Vout = (val/4095) * Vcc).
 * @param[in] write_eeprom      Defines if value will be written to DAC only or to EEPROM memmory also.
 *
 * @return Values returned by @ref nrfx_twi_tx.
 */
ret_code_t mcp4725_set_voltage(uint16_t val, bool write_eeprom);

/**
 * @brief Function for checking if DAC is busy saving data in EEPROM.
 *
 * @retval true         If DAC is busy.
 * @retval false        If Dac is not busy.
 */
bool mcp4725_is_busy(void);

/**
 *@}
 **/

/*lint --flb "Leave library region" */

#ifdef __cplusplus
}
#endif

#endif //MCP4725_H
