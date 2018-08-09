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
#include "uda1380.h"
#include <string.h>

ret_code_t uda1380_init(uda1380_iface_t const * p_iface,
                        uda1380_reg_t const * p_reg_config,
                        size_t reg_size)
{
    ret_code_t ret = NRF_SUCCESS;

    ret = nrf_drv_twi_init(&p_iface->twi, &p_iface->twi_cfg, NULL, NULL);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    nrf_drv_twi_enable(&p_iface->twi);

    /*Probe device*/
    uint8_t rx[] = {0};
    ret = nrf_drv_twi_rx(&p_iface->twi, p_iface->twi_addr, rx, sizeof(rx));
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    for (size_t i = 0; i < reg_size; ++i)
    {
        uint8_t p_dat[sizeof(uda1380_reg_t)];
        memcpy(p_dat, &p_reg_config[i], sizeof(uda1380_reg_t));
        ret = nrf_drv_twi_tx(&p_iface->twi, p_iface->twi_addr, p_dat, sizeof(uda1380_reg_t), false);
        if (ret != NRF_SUCCESS)
        {
            break;
        }
    }

    return ret;
}


ret_code_t uda1380_enable(uda1380_iface_t const * p_iface)
{
    ret_code_t ret = NRF_SUCCESS;

    static const uda1380_reg_t enable[] = {
            UDA1380_REG_INIT(UDA1380_REG_PWR, 0xA500),
            UDA1380_REG_INIT(UDA1380_REG_CLK, 0x0332),
    };

    for (size_t i = 0; i < ARRAY_SIZE(enable); ++i)
    {
        uint8_t p_dat[sizeof(uda1380_reg_t)];
        memcpy(p_dat, &enable[i], sizeof(uda1380_reg_t));
        ret = nrf_drv_twi_tx(&p_iface->twi, p_iface->twi_addr, p_dat, sizeof(uda1380_reg_t), false);
        if (ret != NRF_SUCCESS)
        {
            break;
        }
    }

    return ret;
}


ret_code_t uda1380_disable(uda1380_iface_t const * p_iface)
{
    ret_code_t ret = NRF_SUCCESS;

    static const uda1380_reg_t disable[] = {
            UDA1380_REG_INIT(UDA1380_REG_PWR, 0x0000),
            UDA1380_REG_INIT(UDA1380_REG_CLK, 0x0000),
    };

    for (size_t i = 0; i < ARRAY_SIZE(disable); ++i)
    {
        const uint8_t * p_dat = (const uint8_t *)&disable[i];
        ret = nrf_drv_twi_tx(&p_iface->twi, p_iface->twi_addr, p_dat, sizeof(uda1380_reg_t), false);
        if (ret != NRF_SUCCESS)
        {
            break;
        }
    }

    return ret;
}
