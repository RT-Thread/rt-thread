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
#include <stdbool.h>
#include <stdint.h>

#include "twi_master.h"
#include "synaptics_touchpad.h"

/*lint ++flb "Enter library region" */

#define PRODUCT_ID_BYTES 10U //!< Number of bytes to expect to be in product ID

static uint8_t       m_device_address; // !< Device address in bits [7:1]
static const uint8_t expected_product_id[PRODUCT_ID_BYTES] = {'T', 'M', '1', '9', '4', '4', '-', '0', '0', '2'};  //!< Product ID expected to get from product ID query

bool touchpad_init(uint8_t device_address)
{
    bool transfer_succeeded = true;

    m_device_address = (uint8_t)(device_address << 1);

    // Do a soft reset
    uint8_t reset_command = 0x01;
    transfer_succeeded &= touchpad_write_register(TOUCHPAD_RESET, reset_command);

    // Page select 0
    uint8_t page_to_select = 0x00;
    transfer_succeeded &= touchpad_write_register(TOUCHPAD_PAGESELECT, page_to_select);

    // Read and verify product ID
    transfer_succeeded &= touchpad_product_id_verify();

    return transfer_succeeded;
}


bool touchpad_product_id_verify(void)
{
    bool    transfer_succeeded = true;
    uint8_t product_id[PRODUCT_ID_BYTES];
    transfer_succeeded &= touchpad_product_id_read(product_id, PRODUCT_ID_BYTES);

    for (uint8_t i = 0; i < 10; i++)
    {
        if (product_id[i] != expected_product_id[i])
        {
            transfer_succeeded = false;
        }
    }

    return transfer_succeeded;
}

bool touchpad_reset(void)
{
    uint8_t w2_data[2] = {TOUCHPAD_COMMAND, 0x01};

    return twi_master_transfer(m_device_address, w2_data, 2, TWI_ISSUE_STOP);
}

bool touchpad_interrupt_status_read(uint8_t *interrupt_status)
{
    return touchpad_read_register(TOUCHPAD_INT_STATUS, interrupt_status);
}

bool touchpad_set_sleep_mode(TouchpadSleepMode_t mode)
{
    return touchpad_write_register(TOUCHPAD_CONTROL, (uint8_t)mode);
}

bool touchpad_read_register(uint8_t register_address, uint8_t *value)
{
    bool transfer_succeeded = true;
    transfer_succeeded &= twi_master_transfer(m_device_address, &register_address, 1, TWI_DONT_ISSUE_STOP);
    if (transfer_succeeded)
    {
        transfer_succeeded &= twi_master_transfer(m_device_address | TWI_READ_BIT, value, 1, TWI_ISSUE_STOP);
    }
    return transfer_succeeded;
}

bool touchpad_write_register(uint8_t register_address, const uint8_t value)
{
    uint8_t w2_data[2];

    w2_data[0] = register_address;
    w2_data[1] = value;
    return twi_master_transfer(m_device_address, w2_data, 2, TWI_ISSUE_STOP);
}

bool touchpad_product_id_read(uint8_t * product_id, uint8_t product_id_bytes)
{
    uint8_t w2_data[1];
    bool transfer_succeeded = true;

    w2_data[0] = TOUCHPAD_PRODUCT_ID;
    transfer_succeeded &= twi_master_transfer(m_device_address, w2_data, 1, TWI_DONT_ISSUE_STOP);
    if (transfer_succeeded)
    {
        transfer_succeeded &= twi_master_transfer(m_device_address | TWI_READ_BIT, product_id, product_id_bytes, TWI_ISSUE_STOP);
    }
    return transfer_succeeded;
}

/*lint --flb "Leave library region" */
