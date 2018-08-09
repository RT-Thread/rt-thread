/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
#include "ds1624.h"
#include "twi_master.h"
#include "nrf_delay.h"

/*lint ++flb "Enter library region" */

#define DS1634_BASE_ADDRESS 0x90 //!< 4 MSBs of the DS1624 TWI address

#define DS1624_ONESHOT_MODE    0x01 //!< Bit in configuration register for 1-shot mode
#define DS1624_CONVERSION_DONE 0x80 //!< Bit in configuration register to indicate completed temperature conversion

static uint8_t m_device_address; //!< Device address in bits [7:1]

const uint8_t command_access_memory      = 0x17; //!< Reads or writes to 256-byte EEPROM memory
const uint8_t command_access_config      = 0xAC; //!< Reads or writes configuration data to configuration register
const uint8_t command_read_temp          = 0xAA; //!< Reads last converted temperature value from temperature register
const uint8_t command_start_convert_temp = 0xEE; //!< Initiates temperature conversion.
const uint8_t command_stop_convert_temp  = 0x22; //!< Halts temperature conversion.

/**
 * @brief Function for reading the current configuration of the sensor.
 *
 * @return uint8_t Zero if communication with the sensor failed. Contents (always non-zero) of configuration register (@ref DS1624_ONESHOT_MODE and @ref DS1624_CONVERSION_DONE) if communication succeeded.
 */
static uint8_t ds1624_config_read(void)
{
    uint8_t config = 0;

    // Write: command protocol
    if (twi_master_transfer(m_device_address, (uint8_t*)&command_access_config, 1, TWI_DONT_ISSUE_STOP))
    {
        if (twi_master_transfer(m_device_address | TWI_READ_BIT, &config, 1, TWI_ISSUE_STOP)) // Read: current configuration
        {
            // Read succeeded, configuration stored to variable "config"
        }
        else
        {
            // Read failed
            config = 0;
        }
    }

    return config;
}

bool ds1624_init(uint8_t device_address)
{
    bool transfer_succeeded = true;
    m_device_address = DS1634_BASE_ADDRESS + (uint8_t)(device_address << 1);

    uint8_t config = ds1624_config_read();

    if (config != 0)
    {
        // Configure DS1624 for 1SHOT mode if not done so already.
        if (!(config & DS1624_ONESHOT_MODE))
        {
            uint8_t data_buffer[2];

            data_buffer[0] = command_access_config;
            data_buffer[1] = DS1624_ONESHOT_MODE;

            transfer_succeeded &= twi_master_transfer(m_device_address, data_buffer, 2, TWI_ISSUE_STOP);
        }
    }
    else
    {
        transfer_succeeded = false;
    }

    return transfer_succeeded;
}

bool ds1624_start_temp_conversion(void)
{
    return twi_master_transfer(m_device_address, (uint8_t*)&command_start_convert_temp, 1, TWI_ISSUE_STOP);
}

bool ds1624_is_temp_conversion_done(void)
{
    uint8_t config = ds1624_config_read();

    if (config & DS1624_CONVERSION_DONE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ds1624_temp_read(int8_t * temperature_in_celcius, int8_t * temperature_fraction)
{
    bool transfer_succeeded = false;

    // Write: Begin read temperature command
    if (twi_master_transfer(m_device_address, (uint8_t*)&command_read_temp, 1, TWI_DONT_ISSUE_STOP))
    {
        uint8_t data_buffer[2];

        // Read: 2 temperature bytes to data_buffer
        if (twi_master_transfer(m_device_address | TWI_READ_BIT, data_buffer, 2, TWI_ISSUE_STOP))
        {
            *temperature_in_celcius = (int8_t)data_buffer[0];
            *temperature_fraction   = (int8_t)data_buffer[1];

            transfer_succeeded = true;
        }
    }

    return transfer_succeeded;
}

/*lint --flb "Leave library region" */
