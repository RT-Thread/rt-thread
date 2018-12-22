/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#include "mcp4725.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_util_platform.h"

/*lint ++flb "Enter library region" */
#define MCP4725_BASE_ADDRESS    0x60        //!< MCP4725 base address

#define MCP4725_DAC_ADDRESS     0x40        //!< MCP4725 write-to-dac register
#define MCP4725_EEPROM_ADDRESS  0x60        //!< MCP4725 write-to-eeprom register

#define RDY_BIT_POS             0x07        //!< Position of RDY bit

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID_USED);

/* Twi transfer indicators. */
volatile bool m_xfer_done = false;
volatile bool m_read_done = false;

/**
 * @brief TWI events handler.
 */
static void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_TX)
            {
                m_xfer_done = true;
            }
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                m_read_done = true;
            }
            break;
        default:
            break;
    }
}

/**
 * @brief TWI initialization.
 *
 * @param[in] p_pins_config Pointer to structere holding pins numbers to be used by TWI.
 */
static ret_code_t twi_init(mcp4725_pins_config_t const * p_pins_config)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_mcp4725_config = {
       .scl                = p_pins_config->scl_pin,
       .sda                = p_pins_config->sda_pin,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_mcp4725_config, twi_handler, NULL);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    nrf_drv_twi_enable(&m_twi);
    return NRF_SUCCESS;
}

ret_code_t mcp4725_setup(mcp4725_pins_config_t const * p_pins_config)
{
    ret_code_t err_code = twi_init(p_pins_config);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

ret_code_t mcp4725_set_voltage(uint16_t val, bool write_eeprom)
{
    /* Shift parameter val to get 2 8-bits values. */
    uint8_t reg[3] = {write_eeprom ? MCP4725_EEPROM_ADDRESS : MCP4725_DAC_ADDRESS,
                      (val>>4), (val<<4)};

    m_xfer_done = false;

    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, MCP4725_BASE_ADDRESS, reg, sizeof(reg), false);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    while (m_xfer_done == false);

    return NRF_SUCCESS;
}

bool mcp4725_is_busy(void)
{
    uint8_t busy;
    m_read_done = false;

    ret_code_t err_code = nrf_drv_twi_rx(&m_twi, MCP4725_BASE_ADDRESS, &busy, sizeof(busy));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    while (m_read_done == false);

    return (bool)(!(busy >> RDY_BIT_POS));
}

/*lint --flb "Leave library region" */
